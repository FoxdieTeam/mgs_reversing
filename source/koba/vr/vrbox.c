#include "vrbox.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "strcode.h"
#include "bullet/blast.h"
#include "koba/vr/vr.h"
#include "koba/vr/splashvr.h"

int printf(const char *fmt, ...);

extern BLAST_DATA blast_data_8009F4B8[8];

/*---------------------------------------------------------------------------*/
// VR-DISC target: a model (target board, UFO, ...) that walks along a patrol
// route (HZD route 'r'), can be shot and bursts into pieces

#define MAX_NODES           32
#define SHADOW_SIZE         256
#define SHADOW_RAISE        500
#define SHADOW_COLOR        0x50
#define SHADOW_PRIM         (DG_PRIM_ONESIDE | DG_PRIM_POLY_FT4)
#define NODE_REACHED_DIST   25      // added to the speed

// Target types ('m' option)
#define TYPE_DEFAULT        0       // "id_n" / "id_b" depending on the 'b' option
#define TYPE_UFO2           7       // never rotates sideways, bigger burst, always dies after 255 frames

// GCL options
#define OPT_ROUTE           'r'
#define OPT_DEATH_FRAMES    'd'
#define OPT_SOUND           'v'
#define OPT_HOMING          'h'
#define OPT_TYPE            'm'
#define OPT_BOX             'b'
#define OPT_SPEED           's'
#define OPT_STARTED         'i'
#define OPT_AUTO            'a'
#define OPT_PROC            'e'
#define OPT_LIFE            'l'
#define OPT_RESPAWN_TIME    't'
#define OPT_RESPAWN_SEC     'u'
#define OPT_KEEP_POS        'n'

// Messages
#define MSG_KILL            HASH_KILL   // GV_StrCode("kill")
#define MSG_START           HASH_START  // GV_StrCode("start")
#define MSG_RESET           0xC39B      // restart the respawn timer, play the death
#define MSG_DIE             0x43FD      // play the death

// Sound effects
#define SE_HIT_DAMAGED      52
#define SE_SHOT             215
#define SE_NODE_ON          176
#define SE_NODE_OFF         178
#define SE_BURST            63
#define SE_BURST_UFO        201

typedef struct _VrBoxFlags
{
    unsigned int automatic  : 1;    // bit 0: node flags switch the target on and off
    unsigned int started    : 1;    // bit 1: waits for the "start" message
    unsigned int has_speed  : 1;    // bit 2: speed given by option, not by the nodes
    unsigned int shown      : 1;    // bit 3
    unsigned int box        : 1;    // bit 4: explodes
    unsigned int homing     : 1;    // bit 5: can be locked on
    unsigned int has_life   : 1;    // bit 6: life given by option
    unsigned int keep_pos   : 1;    // bit 7: do not move to the first node when shown
    unsigned int type       : 3;    // bit 8
    unsigned int unused_11  : 4;    // bit 11
    unsigned int unused_15  : 2;    // bit 15
    unsigned int unused_17  : 1;    // bit 17
    unsigned int unused_18  : 8;    // bit 18
    unsigned int sound      : 1;    // bit 26
    unsigned int unused_27  : 5;    // bit 27
} VrBoxFlags;

typedef struct _Work
{
    GV_ACT      actor;                  // 0x00
    int         where;                  // 0x20
    CONTROL     control;                // 0x24
    OBJECT      object;                 // 0xA0
    MATRIX      light[2];               // 0x184
    int         n_nodes;                // 0x1C4
    SVECTOR     nodes[MAX_NODES];       // 0x1C8
    int         node_index;             // 0x2C8
    SVECTOR     node;                   // 0x2CC
    SVECTOR     box_size;               // 0x2D4
    TARGET     *target;                 // 0x2DC
    MATRIX      world;                  // 0x2E0
    HOMING     *homing;                 // 0x300
    int         dying;                  // 0x304
    VrBoxFlags  flags;                  // 0x308
    int         speed;                  // 0x30C
    u_short     wait;                   // 0x310
    signed char route;                  // 0x312
    u_char      death_frames;           // 0x313
    short       respawn_count;          // 0x314
    short       respawn_time;           // 0x316
    int         vital;                  // 0x318
    int         pad_31C;
    int         proc;                   // 0x320
    DG_PRIM    *shadow;                 // 0x324
    SVECTOR     shadow_verts[4];        // 0x328
    int         hit_flash;              // 0x348
    int         scale;                  // 0x34C
    int         splash_tex;             // 0x350
    int         splash_spread;          // 0x354
} Work;                                 // 0x358

/*---------------------------------------------------------------------------*/

static void InitShadowPoly(POLY_FT4 *poly, DG_TEX *tex)
{
    int x, y, x2, y2;

    setPolyFT4(poly);
    setSemiTrans(poly, 1);

    x = tex->off_x;
    x2 = x + tex->w;
    y = tex->off_y;
    y2 = y + tex->h;
    setUV4(poly, x, y, x2, y, x, y2, x2, y2);
    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}

// InitShadow does not byte-match from C (the original addresses the four corners of the shadow quad through a mix of
// base registers), so the original code is kept as RELOCATABLE asm (build/symbolize_asm.py, see reloc/gen.sh)
// which keeps this object shareable between overlays.
int VrBoxInitShadow(Work *work);
#pragma INCLUDE_ASM_RELOC("source/koba/vr/reloc/VrBoxInitShadow.s")

#if 0 /* NON_MATCHING best C attempt */
// NON_MATCHING: same instructions and values, only the base registers of the quad stores differ.
static int InitShadow(Work *work)
{
    DG_PRIM *prim;
    DG_TEX  *tex;
    SVECTOR *verts;
    SVECTOR *mov;
    SVECTOR *v1;
    SVECTOR *v3;

    verts = work->shadow_verts;
    v1 = &work->shadow_verts[1];
    v3 = &work->shadow_verts[3];
    mov = &work->control.mov;

    v3->vy = work->shadow_verts[2].vy = v1->vy = verts->vy = 0;

    work->shadow_verts[2].vx = work->shadow_verts[0].vx = mov->vx + SHADOW_SIZE;
    v1->vz = verts->vz = mov->vz + SHADOW_SIZE;
    work->shadow_verts[3].vx = verts[1].vx = mov->vx - SHADOW_SIZE;
    v3->vz = verts[2].vz = mov->vz - SHADOW_SIZE;

    prim = DG_MakePrim(SHADOW_PRIM, 1, 0, verts, NULL);

    if (prim)
    {
        DG_QueuePrim(prim);
        DG_GroupPrim(prim, GM_CurrentMap);
    }

    work->shadow = prim;

    if (!prim)
    {
        return -1;
    }

    prim->raise = SHADOW_RAISE;

    tex = DG_GetTexture(GV_StrCode("shadow"));

    if (!tex)
    {
        return -1;
    }

    InitShadowPoly(prim->packs[0], tex);
    InitShadowPoly(prim->packs[1], tex);

    setRGB0((POLY_FT4 *)prim->packs[0], SHADOW_COLOR, SHADOW_COLOR, SHADOW_COLOR);
    setRGB0((POLY_FT4 *)prim->packs[1], SHADOW_COLOR, SHADOW_COLOR, SHADOW_COLOR);

    return 0;
}

#endif

// Reads the flags of the node that has been reached
static int ReadNodeFlags(Work *work)
{
    int node_flags;
    int sound;
    int speed;

    node_flags = work->node.pad;
    sound = node_flags & 0x1F;
    speed = (node_flags & 0x1C00) >> 10;

    work->wait = ((node_flags & 0xE0) >> 5) * 30;

    if (work->flags.automatic)
    {
        if (work->flags.sound)
        {
            if (work->flags.shown)
            {
                if (sound == 0)
                {
                    GM_SeSetMode(&work->control.mov, SE_NODE_OFF, 1);
                }
            }
            else
            {
                if (sound != 0)
                {
                    GM_SeSetMode(&work->control.mov, SE_NODE_ON, 1);
                }
            }
        }

        work->flags.shown = sound & 1;
    }

    if (!work->flags.has_speed)
    {
        work->speed = speed * 20;
    }

    return 1;
}

static int ReadNodes(Work *work)
{
    HZD_PAT *route;
    HZD_PTP *points;
    int      i;

    route = work->control.map->hzd->def->routes;
    route = &route[work->route];

    work->n_nodes = route->n_points;

    if (work->n_nodes <= 0)
    {
        return -1;
    }

    points = route->points;

    for (i = 0; i < work->n_nodes; i++)
    {
        work->nodes[i].vx = points->x;
        work->nodes[i].vy = points->y;
        work->nodes[i].vz = points->z;
        work->nodes[i].pad = points->command;
        points++;
    }

    return 0;
}

static void NextNode(Work *work)
{
    int index;

    index = work->node_index + 1;

    if (index >= work->n_nodes)
    {
        index = 0;
    }

    work->node_index = index;
    work->node = work->nodes[index];
}

// Walks towards the current node, returns 1 when it has been reached
static int MoveToNode(Work *work, int dist)
{
    SVECTOR diff;
    int     reached;

    GV_SubVec3(&work->node, &work->control.mov, &diff);

    if (GV_VecLen3(&diff) >= dist)
    {
        GV_LenVec3(&diff, &work->control.step, GV_VecLen3(&diff), work->speed);
        reached = 0;
    }
    else
    {
        reached = 1;
    }

    return reached;
}

// Floor height under the target and the shadow polygon
static void UpdateShadow(Work *work)
{
    CONTROL *control;
    SVECTOR *verts;
    int      level;
    int      size;

    control = &work->control;
    verts = work->shadow_verts;

    HZD_LevelHazardCheck(control->map->hzd, &control->mov, 3);
    HZD_GetLevelHeight(&level);

    work->shadow_verts[3].vy = level;
    work->shadow_verts[2].vy = level;
    work->shadow_verts[1].vy = level;
    verts->vy = level;

    if (level == -30000 || work->flags.type == TYPE_UFO2)
    {
        size = 0;
    }
    else
    {
        size = work->scale * 32 + 128;
    }

    verts[2].vx = control->mov.vx + size;
    verts[0].vx = verts[2].vx;
    verts[1].vz = control->mov.vz + size;
    verts[0].vz = verts[1].vz;
    verts[3].vx = control->mov.vx - size;
    verts[1].vx = verts[3].vx;
    verts[3].vz = control->mov.vz - size;
    verts[2].vz = verts[3].vz;
}

// Shows the target (respawn)
static void Appear(Work *work)
{
    TARGET  *target;
    CONTROL *control;
    MATRIX  *light;

    target = work->target;
    target->class = 0x1C;
    target->damaged = 0;
    target->vital = work->vital;

    work->flags.shown = 1;
    control = &work->control;
    work->dying = 0;
    work->hit_flash = 0;
    work->scale = 0;

    if (!work->flags.keep_pos)
    {
        work->control.mov = work->nodes[0];
        work->node_index = 0;
        work->node = work->nodes[0];
    }

    if (work->flags.homing)
    {
        work->homing->used = 1;
    }

    work->world = work->object.objs->world;
    work->world.t[1] += 200;

    GM_ConfigControlAttribute(control, 1);
    DG_VisibleObjs(work->object.objs);
    DG_VisiblePrim(work->shadow);

    light = work->object.objs->light;
    light->t[0] = light->t[1] = light->t[2] = 127;

    if (work->flags.sound)
    {
        GM_SeSetMode(&control->mov, SE_NODE_ON, 1);
    }
}

// Hides the target until it respawns
static void Disappear(Work *work)
{
    TARGET  *target;
    CONTROL *control;

    target = work->target;
    work->dying = 0;
    work->flags.shown = 0;
    work->respawn_count = work->respawn_time;
    target->class = 0x201;
    target->damaged = 0;
    control = &work->control;
    work->hit_flash = 0;

    if (work->flags.homing)
    {
        work->homing->used = 0;
    }

    GM_ConfigControlAttribute(control, 0);
    DG_InvisibleObjs(work->object.objs);
    DG_InvisiblePrim(work->shadow);
}

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    CONTROL *control;
    TARGET  *target;
    MATRIX  *light;
    VECTOR   scale;
    MATRIX   rot;
    SVECTOR  zero;
    SVECTOR  diff;
    int      burst;
    u_short  a_mode;

    if (VR_Status == VR_STATUS_CLEAR)
    {
        GV_DestroyActor(&work->actor);
    }

    control = &work->control;
    target = work->target;

    GM_CurrentMap = work->where;

    control->n_msg = GV_ReceiveMessage(control->name, &control->msg);

    if (control->n_msg)
    {
        switch (control->msg->message[0])
        {
        case MSG_KILL:
            GV_DestroyActor(&work->actor);
            break;

        case MSG_RESET:
            work->respawn_time = 0;
            work->dying = work->death_frames;
            break;

        case MSG_DIE:
            work->dying = work->death_frames;
            break;
        }
    }

    if (!work->flags.started)
    {
        work->flags.started = control->n_msg && control->msg->message[0] == MSG_START;

        GM_ActControl(control);
        GM_ActObject2(&work->object);
        GM_MoveTarget(target, &control->mov);
        GM_PushTarget(target);
        UpdateShadow(work);
        return;
    }

    if (work->flags.type == TYPE_UFO2)
    {
        control->turn.vy += 128;

        if (work->dying)
        {
            control->turn.vx += 8;
        }
    }
    else
    {
        control->turn.vy += 64;
    }

    control->turn.vy &= 0xFFF;

    if (work->wait == 0)
    {
        if (MoveToNode(work, work->speed + NODE_REACHED_DIST))
        {
            ReadNodeFlags(work);
            NextNode(work);

            if (work->wait == 0)
            {
                GV_SubVec3(&work->node, &work->control.mov, &diff);
                GV_LenVec3(&diff, &work->control.step, GV_VecLen3(&diff), work->speed);
            }
            else
            {
                work->wait--;
                work->control.step = DG_ZeroVector;
            }
        }
    }
    else
    {
        work->wait--;
    }

    if (work->respawn_time != 0)
    {
        if (work->respawn_count >= 2)
        {
            work->respawn_count--;
        }
        else if (work->respawn_count == 1)
        {
            Appear(work);
            work->respawn_count = 0;
        }
    }

    GM_ActControl(control);
    control->mov.vy += control->step.vy;
    UpdateShadow(work);
    GM_MoveTarget(target, &control->mov);
    GM_PushTarget(target);
    GM_ActObject2(&work->object);

    work->world = work->object.objs->world;
    work->world.t[1] += 200;

    if (work->respawn_count == 0 && work->dying == 0)
    {
        if (work->flags.shown)
        {
            if (work->scale < 8)
            {
                work->scale++;
                scale.vx = scale.vy = scale.vz = work->scale << 9;
                ScaleMatrix(&work->object.objs->world, &scale);
            }

            work->target->class = 0x1C;

            if (work->flags.homing)
            {
                work->homing->used = 1;
            }
        }
        else if (work->scale > 0)
        {
            if (work->hit_flash == 0)
            {
                work->scale--;
                scale.vx = scale.vy = scale.vz = work->scale << 9;
                ScaleMatrix(&work->object.objs->world, &scale);
            }

            if (work->scale == 0)
            {
                work->target->class = 0x201;

                if (work->flags.homing)
                {
                    work->homing->used = 0;
                }
            }
        }

        if (work->scale == 0)
        {
            DG_InvisibleObjs(work->object.objs);
        }
        else
        {
            DG_VisibleObjs(work->object.objs);
        }
    }

    if (work->hit_flash)
    {
        light = work->object.objs->light;
        light->t[0] = light->t[1] = light->t[2] = GV_Clock * 255;

        work->hit_flash = (work->hit_flash + 1) & 0xF;

        if (work->hit_flash == 0)
        {
            light = work->object.objs->light;
            light->t[0] = light->t[1] = light->t[2] = 127;
        }
    }

    if (target->damaged & 4)
    {
        target->damaged &= ~4;
        a_mode = target->a_mode;

        if ((a_mode - 3) < 2U)
        {
            if (work->flags.type == 6)
            {
                target->vital -= 2;

                if (target->vital >= 0)
                {
                    GM_SeSetMode(&control->mov, SE_HIT_DAMAGED, 1);
                }

                work->hit_flash = 1;
            }
        }
        else
        {
            if ((short)a_mode != 2)
            {
                if (target->vital >= 0)
                {
                    GM_SeSetMode(&control->mov, SE_SHOT, 1);
                }
            }

            work->hit_flash = 1;
        }

        if (work->dying == 0)
        {
            if (target->vital < 0 || (target->a_mode == 2 && !work->flags.has_life))
            {
                if (work->respawn_count == 0)
                {
                    if (work->flags.box)
                    {
                        work->dying = 1;
                    }
                    else
                    {
                        work->dying = work->death_frames;
                    }

                    target->vital = 255;
                    target->class = 0x201;
                }
            }
        }
    }

    if (work->dying == 0)
    {
        return;
    }

    if (work->dying != work->death_frames)
    {
        work->dying++;
        return;
    }

    if (work->flags.box)
    {
        NewBlast(&work->object.objs->world, blast_data_8009F4B8);
        burst = 32;
    }
    else
    {
        burst = 64;
    }

    if (work->flags.type == TYPE_UFO2)
    {
        burst = 128;
    }

    zero = DG_ZeroVector;
    VR_TargetCount++;
    DG_SetPos2(&control->mov, &zero);
    ReadRotMatrix(&rot);

    NewSplashVr(&rot, &work->box_size, burst, 0, work->splash_tex, work->splash_spread);

    if (work->flags.type == 4)
    {
        GM_SeSetMode(&control->mov, SE_BURST_UFO, 1);
    }
    else
    {
        GM_SeSetMode(&control->mov, SE_BURST, 1);
    }

    if (work->respawn_time == 0)
    {
        GV_DestroyActor(&work->actor);
    }
    else
    {
        Disappear(work);
    }

    if (work->proc > 0)
    {
        GCL_ExecProc(work->proc, NULL);
    }
}

static void Die(Work *work)
{
    DG_PRIM *prim;

    GM_FreeControl(&work->control);
    GM_FreeObject(&work->object);
    GM_FreeTarget(work->target);

    prim = work->shadow;

    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    if (work->homing)
    {
        GM_ResetHomingTarget(work->homing);
    }
}

static void InitTarget(Work *work)
{
    TARGET *target;

    target = GM_AllocTarget();
    work->target = target;

    if (work->flags.type == TYPE_DEFAULT)
    {
        if (work->flags.box)
        {
            work->box_size.vx = 400;
            work->box_size.vy = 500;
            work->box_size.vz = 400;
            work->splash_spread = 64;
        }
        else
        {
            work->box_size.vx = 400;
            work->box_size.vy = 400;
            work->box_size.vz = 400;
            work->splash_spread = 64;
        }
    }
    else
    {
        switch (work->flags.type)
        {
        case 1:
            work->box_size.vx = 400;
            work->box_size.vy = 400;
            work->box_size.vz = 400;
            work->splash_spread = 64;
            break;

        case 2:
            work->box_size.vx = 510;
            work->box_size.vy = 510;
            work->box_size.vz = 510;
            work->splash_spread = 64;
            break;

        case 3:
            work->box_size.vx = 400;
            work->box_size.vy = 500;
            work->box_size.vz = 400;
            work->splash_spread = 64;
            break;

        case 4:
            work->box_size.vx = 1250;
            work->box_size.vy = 1250;
            work->box_size.vz = 1000;
            work->splash_spread = 256;
            break;

        case 5:
        case 6:
            work->box_size.vx = 250;
            work->box_size.vy = 800;
            work->box_size.vz = 250;
            work->splash_spread = 64;
            break;
        }
    }

    GM_SetTarget(target, 28, 2, &work->box_size);
    target->flag |= 2;
    GM_SetPowerTarget(target, 1, -1, work->vital, 0, &DG_ZeroVector);
}

static int GetResources(Work *work, int name, int where)
{
    int      models[7];
    int      textures[7];
    CONTROL *control;
    OBJECT  *object;
    MATRIX  *light;
    char    *opt;
    int      value;

    models[0] = GV_StrCode("id_n");
    models[1] = GV_StrCode("id_b");
    models[2] = GV_StrCode("id_b");
    models[3] = GV_StrCode("ufo");
    models[4] = GV_StrCode("kokesi_c");
    models[5] = GV_StrCode("kokesi_s");
    models[6] = GV_StrCode("ufo2");

    textures[0] = GV_StrCode("mato_04add");
    textures[1] = GV_StrCode("mato_06add");
    textures[2] = GV_StrCode("mato_06add");
    textures[3] = GV_StrCode("mato_08add");
    textures[4] = GV_StrCode("mato_09add");
    textures[5] = GV_StrCode("mato_14add");
    textures[6] = GV_StrCode("ufo2");

    control = &work->control;

    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    GM_CurrentMap = where;
    work->where = where;
    GM_ConfigControlHazard(control, -1, -2, -1);

    work->respawn_count = 0;
    work->flags.shown = 1;
    work->flags.homing = 0;
    work->flags.has_life = 0;

    opt = GCL_GetOption(OPT_ROUTE);
    if (opt)
    {
        work->route = GCL_StrToInt(opt);
    }

    opt = GCL_GetOption(OPT_DEATH_FRAMES);
    if (opt)
    {
        work->death_frames = GCL_StrToInt(opt);
    }
    else
    {
        work->death_frames = 4;
    }

    opt = GCL_GetOption(OPT_SOUND);
    if (opt)
    {
        work->flags.sound = GCL_StrToInt(opt);
    }
    else
    {
        work->flags.sound = 1;
    }

    work->flags.homing = GCL_GetOption(OPT_HOMING) != 0;

    opt = GCL_GetOption(OPT_TYPE);
    if (opt)
    {
        work->flags.type = GCL_StrToInt(opt);
    }
    else
    {
        work->flags.type = 0;
    }

    if (work->flags.type == 6)
    {
        work->flags.homing = 1;
    }

    if (work->flags.homing)
    {
        work->homing = GM_SetHomingTarget(&work->world, &work->control);
        work->homing->flag = 1;
    }

    work->flags.box = GCL_GetOption(OPT_BOX) != 0;

    opt = GCL_GetOption(OPT_SPEED);
    if (opt)
    {
        work->flags.has_speed = 1;
        work->speed = GCL_StrToInt(opt);
    }

    work->flags.started = GCL_GetOption(OPT_STARTED) != 0;
    work->flags.automatic = GCL_GetOption(OPT_AUTO) != 0;

    if (GCL_GetOption(OPT_PROC))
    {
        work->proc = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->proc = -1;
    }

    opt = GCL_GetOption(OPT_LIFE);
    if (opt)
    {
        work->flags.has_life = 1;
        work->vital = GCL_StrToInt(opt);
    }
    else
    {
        work->vital = 150;
    }

    opt = GCL_GetOption(OPT_RESPAWN_TIME);
    if (opt)
    {
        work->respawn_time = GCL_StrToInt(opt);

        if (work->respawn_time < 31)
        {
            work->respawn_time = 30;
        }
    }
    else
    {
        work->respawn_time = 0;
    }

    opt = GCL_GetOption(OPT_RESPAWN_SEC);
    if (opt)
    {
        value = GCL_StrToInt(opt);
        work->respawn_time = value * 30;

        if (work->respawn_time < 31)
        {
            work->respawn_time = 30;
        }
    }

    work->flags.keep_pos = GCL_GetOption(OPT_KEEP_POS) != 0;

    object = &work->object;

    if (work->flags.type == TYPE_DEFAULT)
    {
        if (work->flags.box)
        {
            GM_InitObject(object, GV_StrCode("id_b"), 0x15D, 0);
            work->splash_tex = GV_StrCode("mato_06add");
        }
        else
        {
            GM_InitObject(object, GV_StrCode("id_n"), 0x15D, 0);
            work->splash_tex = GV_StrCode("mato_04add");
        }
    }
    else
    {
        GM_InitObject(object, models[work->flags.type - 1], 0x15D, 0);
        work->splash_tex = textures[work->flags.type - 1];

        if (work->flags.type >= 2 && work->flags.type <= 4)
        {
            work->flags.box = 1;
        }

        if (work->flags.type == TYPE_UFO2)
        {
            work->death_frames = 255;
        }
    }

    InitTarget(work);
    GM_ConfigObjectLight(object, work->light);

    if (ReadNodes(work) < 0)
    {
        printf("root not found\n");
    }

    work->wait = 0;
    work->dying = 0;
    work->control.mov = work->nodes[0];
    work->node_index = 0;
    work->node = work->nodes[0];
    work->scale = 8;
    work->hit_flash = 0;
    work->flags.unused_11 = 0;
    work->flags.unused_15 = 0;
    work->flags.unused_17 = 0;
    work->flags.unused_18 = 0;

    VrBoxInitShadow(work);
    GM_ConfigControlAttribute(&work->control, 1);
    GM_ActControl(control);
    GM_ActObject2(&work->object);
    GM_ConfigControlTrapCheck(control);

    light = work->object.objs->light;
    light->t[0] = light->t[1] = light->t[2] = 127;

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewVrBox(int name, int where)
{
    Work *work;

    work = GV_NewActor(5, sizeof(Work));

    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "vrbox.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return work;
}
