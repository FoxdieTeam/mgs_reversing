#include "vrbox4.h"

#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "menu/menuman.h"
#include "game/vibrate.h"
#include "game/game.h"
#include <string.h>
#include "strcode.h"
#include "bullet/blast.h"
#include "linkvar.h"
#include "koba/vr/vr.h"
#include "koba/vr/splashvr.h"

extern BLAST_DATA blast_data_8009F4B8[8];

// okajima/p_sphere.c
extern void *s08b_p_sphere_800D9834(DG_OBJS **pobjs, int *state);

/*---------------------------------------------------------------------------*/
// VR-DISC target ("ＶＲＢＯＸ４", UFO mission revision of koba/vr/vrbox.c): a model (target board, UFO, ...) that walks
// along a patrol route (HZD route 'r'), can be shot and bursts into pieces. The big UFO (type 7) is a boss with a life
// bar, a glowing shell, pad vibration and a chain of explosions when it is beaten.

#define BODY_FLAG           ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_BOUND \
                            | DG_FLAG_ONEPIECE | DG_FLAG_AMBIENT )
#define SHELL_FLAG          ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND \
                            | DG_FLAG_ONEPIECE | DG_FLAG_AMBIENT )

#define MAX_NODES           32
#define SHADOW_SIZE         256
#define SHADOW_RAISE        500
#define SHADOW_COLOR        0x50
#define SHADOW_PRIM         (DG_PRIM_ONESIDE | DG_PRIM_POLY_FT4)
// Route node flags (the pad field of the route point)
#define NODE_SOUND_MASK     0x001F  // bit 0: target is shown after the node; any bit: show/hide sound
#define NODE_WAIT_MASK      0x00E0  // seconds to wait at the node
#define NODE_WAIT_SHIFT     5
#define NODE_WAIT_UNIT      30      // frames per second
#define NODE_SPEED_MASK     0x1C00  // speed in steps of 20
#define NODE_SPEED_SHIFT    10
#define NODE_SPEED_UNIT     20
#define NODE_SPEED_UNIT_UFO2 200
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
#define OPT_PROC_BEATEN     'c'
#define OPT_LIFE            'l'
#define OPT_RESPAWN_TIME    't'
#define OPT_RESPAWN_SEC     'u'
#define OPT_KEEP_POS        'n'

// Messages
#define MSG_KILL            HASH_KILL   // GV_StrCode("kill")
#define MSG_START           HASH_START  // GV_StrCode("start")
#define MSG_RESET           0xC39B      // restart the respawn timer, play the death
#define MSG_DIE             0x43FD      // play the death
#define MSG_SPHERE          0x905F      // surround the player with the electric sphere (p_sphere.c)
#define MSG_GLOW            0x68DF      // the shell of the boss starts to glow

// Sound effects
#define SE_HIT_DAMAGED      52
#define SE_SHOT             215
#define SE_NODE_ON          176
#define SE_NODE_OFF         178
#define SE_BURST_UFO        201
#define SE_BOSS_DOWN        214

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
    unsigned int blast_wait : 4;    // bit 11: frames until the next explosion of the dying boss
    unsigned int blast_se   : 2;    // bit 15: last explosion sound
    unsigned int glowing    : 1;    // bit 17: the shell of the boss lights up ("68DF" message)
    unsigned int glow       : 8;    // bit 18: brightness of the shell
    unsigned int sound      : 1;    // bit 26
    unsigned int unused_27  : 5;    // bit 27
} VrBoxFlags;

typedef struct _Work
{
    GV_ACT         actor;                  // 0x00
    int            where;                  // 0x20
    CONTROL        control;                // 0x24
    OBJECT         object;                 // 0xA0
    MATRIX         light[2];               // 0x184
    OBJECT         shell;                  // 0x1C4 (type 7 only)
    MATRIX         shell_light[2];         // 0x2A8
    int            n_nodes;                // 0x2E8
    SVECTOR        nodes[MAX_NODES];       // 0x2EC
    int            node_index;             // 0x3EC
    SVECTOR        node;                   // 0x3F0
    SVECTOR        box_size;               // 0x3F8
    TARGET        *target;                 // 0x400
    MATRIX         world;                  // 0x404
    HOMING        *homing;                 // 0x424
    int            dying;                  // 0x428
    VrBoxFlags     flags;                  // 0x42C
    int            speed;                  // 0x430
    u_short        wait;                   // 0x434
    signed char    route;                  // 0x436
    u_char         death_frames;           // 0x437
    short          respawn_count;          // 0x438
    short          respawn_time;           // 0x43A
    int            vital;                  // 0x43C
    int            pad_440;                // 0x440
    int            proc;                   // 0x444
    DG_PRIM       *shadow;                 // 0x448
    SVECTOR        shadow_verts[4];        // 0x44C
    int            hit_flash;              // 0x46C
    int            scale;                  // 0x470
    int            splash_tex;             // 0x474
    int            splash_spread;          // 0x478
    MENU_BAR_CONF  lifebar;                // 0x47C
    int            pad_488;                // 0x488
    int            life_rest;              // 0x48C
    int            proc_beaten;            // 0x490
    int            sphere_state;           // 0x494
    int            pad_498;                // 0x498
} Work;                                    // 0x49C

/*---------------------------------------------------------------------------*/

static char SECTION(".bss") ufo_name[4];

// (not static: the relocatable asm of Act refers to them)
// Pad vibration patterns (pairs of strength and duration, closed by 0, 0)
u_char vib_boss_hit[] = { 0xF0, 0x02, 0xFF, 0x02, 0x64, 0x05, 0x5A, 0x05, 0x50, 0x05, 0x40, 0x0A, 0x00, 0x00 };
u_char vib_boss_hit2[] = { 0x7F, 0x0F, 0x00, 0x00 };
u_char vib_boss_down[] = { 0xC8, 0x02, 0x17, 0x05, 0x78, 0x02, 0x00, 0x00 };
u_char vib_blast[] = { 0x7F, 0x02, 0x00, 0x00 };
static u_char vib_start[] = { 0x50, 0x32, 0x64, 0x0A, 0x78, 0x0A, 0x8C, 0x0A, 0xA0, 0x0A, 0xB4, 0x0A, 0xC8, 0x0A, 0xDC, 0x0A,
                              0xFF, 0x02, 0x3C, 0x02, 0xFF, 0x02, 0x3C, 0x02, 0xFF, 0x02, 0x3C, 0x02, 0xFF, 0x02, 0xB4, 0x0A,
                              0xA0, 0x0A, 0x8C, 0x0A, 0x64, 0x0A, 0x50, 0x0A, 0x3C, 0x0A, 0x00, 0x00 };
static u_char vib_none[] = { 0x00, 0x00 };
u_char blast_se_table[4] = { 0xCA, 0xCB, 0xCC, 0xCD };

/*---------------------------------------------------------------------------*/

// Life bar of the boss (like mel10.c)
static void DrawLife(Work *work)
{
    int now;
    int rest;
    int fill;

    now = work->target->vital;
    rest = work->life_rest;
    fill = 255;

    if (work->dying != 0)
    {
        now = 0;
        fill = 0;
    }

    MENU_DrawBar2(32, rest + fill, now + fill, work->vital + 255, &work->lifebar);

    if (now < rest)
    {
        work->life_rest -= 8;
    }

    if (work->life_rest <= 0)
    {
        work->life_rest = 0;
    }
}

static void InitLife(Work *work)
{
    MENU_BAR_CONF *lifebar;

    strcpy(ufo_name, "UFO");
    lifebar = &work->lifebar;
    lifebar->name = ufo_name;
    lifebar->left[0] = 31;
    lifebar->left[1] = 191;
    lifebar->left[2] = 95;
    lifebar->right[0] = 31;
    lifebar->right[1] = 191;
    lifebar->right[2] = 95;
    lifebar->height = 1;
    work->life_rest = work->target->vital;
}

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

// InitShadow does not byte-match from C: the original keeps the result in the branch delay slots of both early returns
// (the C code below compiles to the same instructions, only the delay slot filling differs). The original code is kept as
// RELOCATABLE asm (build/symbolize_asm.py, see reloc/gen.sh), which keeps this object shareable.
int VrBox4InitShadow(Work *work);
#pragma INCLUDE_ASM_RELOC("source/koba/vr/reloc/VrBox4InitShadow.s")

#if 0 /* NON_MATCHING best C attempt */
// NON_MATCHING: same instructions, "return -1" delay slot filling differs
static int InitShadow(Work *work)
{
    DG_PRIM *prim;
    DG_TEX  *tex;
    SVECTOR *verts;
    SVECTOR *mov;
    SVECTOR *v1;
    SVECTOR *v3;

    v3 = &work->shadow_verts[3];
    v1 = &work->shadow_verts[1];
    verts = work->shadow_verts;
    mov = &work->control.mov;

    verts->vy = v1->vy = work->shadow_verts[2].vy = v3->vy = 0;

    work->shadow_verts[0].vx = work->shadow_verts[2].vx = mov->vx + SHADOW_SIZE;
    verts->vz = v1->vz = mov->vz + SHADOW_SIZE;
    verts[1].vx = work->shadow_verts[3].vx = mov->vx - SHADOW_SIZE;
    verts[2].vz = v3->vz = mov->vz - SHADOW_SIZE;

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
    sound = node_flags & NODE_SOUND_MASK;
    speed = (node_flags & NODE_SPEED_MASK) >> NODE_SPEED_SHIFT;

    work->wait = ((node_flags & NODE_WAIT_MASK) >> NODE_WAIT_SHIFT) * NODE_WAIT_UNIT;

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
        if (work->flags.type == TYPE_UFO2)
        {
            work->speed = speed * NODE_SPEED_UNIT_UFO2;
        }
        else
        {
            work->speed = speed * NODE_SPEED_UNIT;
        }
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
    target->class = TARGET_AVAIL | TARGET_NO_LOCKON;
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

// Act does not byte-match from C (register allocation of the pad-vibration/blast code, see the C version below), so the
// original code is kept as RELOCATABLE asm (build/symbolize_asm.py, see reloc/gen.sh).
void VrBox4Act(Work *work);
#pragma INCLUDE_ASM_RELOC("source/koba/vr/reloc/VrBox4Act.s")

#if 0 /* NON_MATCHING best C attempt */
// NON_MATCHING: the shell light loads are scheduled in another order and the blast position uses other registers
static void Act(Work *work)
{
    TARGET  *target;
    CONTROL *control;
    MATRIX  *light;
    MATRIX  *shell_light;
    MATRIX  *shell_light2;
    int      glow;
    VECTOR   scale;
    MATRIX   rot;
    SVECTOR  zero;
    SVECTOR  diff;
    SVECTOR  pos;
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

        case MSG_SPHERE:
            work->sphere_state = 1;
            s08b_p_sphere_800D9834(&GM_PlayerBody->objs, &work->sphere_state);
            break;

        case MSG_GLOW:
            work->flags.glowing = 1;
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

    if (work->flags.type == TYPE_UFO2)
    {
        work->shell.objs->world = work->object.objs->world;

        if (work->flags.glowing)
        {
            work->flags.glow += 2;

            if (work->flags.glow > 128)
            {
                work->flags.glow = 128;
            }
        }

        glow = work->flags.glow;
        shell_light = work->shell.objs->light;
        shell_light2 = shell_light + 1;
        shell_light2->t[0] = shell_light2->t[1] = shell_light2->t[2] = glow;
        shell_light->t[0] = shell_light->t[1] = shell_light->t[2] = glow;

        DrawLife(work);

        if (work->dying != 0)
        {
            pos = work->control.mov;

            if (work->sphere_state != -1)
            {
                work->sphere_state = 3;
            }

            work->control.step.vx = work->control.step.vz = 0;
            work->control.step.vy = -work->dying * 5;

            if (work->dying == 2)
            {
                if (work->proc_beaten > 0)
                {
                    GCL_ExecProc(work->proc_beaten, NULL);
                    work->proc_beaten = 0;
                }
            }

            if (work->control.mov.vy < work->shadow_verts[0].vy + 2500)
            {
                work->control.step.vy = 0;
                work->dying = work->death_frames;
                NewPadVibration(vib_boss_hit2, 1);
                NewPadVibration(vib_boss_hit, 0);
                GM_SeSetMode(&pos, SE_BOSS_DOWN, 1);
            }

            work->target->class = TARGET_AVAIL | TARGET_NO_LOCKON;

            if (work->dying & 1)
            {
                pos.vy += 5000;
                AN_Blast_Single(&pos);
            }

            if (work->flags.blast_wait == 0)
            {
                short index;

                pos.vx = work->control.mov.vx - GM_PlayerPosition.vx;
                pos.vz = work->control.mov.vz - GM_PlayerPosition.vz;
                pos.vx = GM_PlayerPosition.vx + (pos.vx >> 2);
                pos.vz = GM_PlayerPosition.vz + (pos.vz >> 2);
                pos.vy = work->control.mov.vy;

                index = GV_RandU(4);

                if (work->flags.blast_se == index)
                {
                    index++;
                }

                work->flags.blast_se = index;
                GM_SeSetMode(&pos, blast_se_table[work->flags.blast_se], 1);

                pos.vx = work->control.mov.vx + GV_RandS(0x2000);
                pos.vy = work->control.mov.vy + GV_RandS(0x800);
                pos.vz = work->control.mov.vz + GV_RandS(0x2000);
                AN_Blast_Single(&pos);

                NewPadVibration(vib_blast, 1);
                NewPadVibration(vib_boss_down, 0);

                work->flags.blast_wait = GV_RandU(8) + GV_RandU(4) + 4;
            }
            else
            {
                work->flags.blast_wait--;
            }
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
                work->target->class = TARGET_AVAIL | TARGET_NO_LOCKON;

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
        // FIXME: a_mode is read as an unsigned short and compared as a short to match the original
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
                    target->class = TARGET_AVAIL | TARGET_NO_LOCKON;
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

#endif

static void Die(Work *work)
{
    DG_PRIM *prim;

    GM_FreeControl(&work->control);
    GM_FreeObject(&work->object);

    if (work->flags.type == TYPE_UFO2)
    {
        GM_FreeObject(&work->shell);
    }

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
        case 4:
            work->box_size.vx = 1250;
            work->box_size.vy = 1250;
            work->box_size.vz = 1000;
            work->splash_spread = 256;
            break;

        case TYPE_UFO2:
            work->box_size.vx = 10000;
            work->box_size.vy = 5000;
            work->box_size.vz = 10000;
            work->splash_spread = 512;
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
    MATRIX  *shell_light2;
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

    if (GCL_GetOption(OPT_PROC_BEATEN))
    {
        work->proc_beaten = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->proc_beaten = -1;
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
            GM_InitObject(object, GV_StrCode("id_b"), BODY_FLAG, 0);
            work->splash_tex = GV_StrCode("mato_06add");
        }
        else
        {
            GM_InitObject(object, GV_StrCode("id_n"), BODY_FLAG, 0);
            work->splash_tex = GV_StrCode("mato_04add");
        }
    }
    else
    {
        GM_InitObject(object, models[work->flags.type - 1], BODY_FLAG, 0);
        work->splash_tex = textures[work->flags.type - 1];

        if (work->flags.type >= 2 && work->flags.type <= 4)
        {
            work->flags.box = 1;
        }

        if (work->flags.type == TYPE_UFO2)
        {
            work->death_frames = 255;

            GM_InitObject(&work->shell, GV_StrCode("u_light"), SHELL_FLAG, 0);
            GM_ConfigObjectLight(&work->shell, work->shell_light);

            light = work->shell.objs->light;
            shell_light2 = light + 1;
            shell_light2->t[0] = shell_light2->t[1] = shell_light2->t[2] = 0;
            light->t[0] = light->t[1] = light->t[2] = 0;
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
    work->flags.blast_wait = 0;
    work->flags.blast_se = 0;
    work->flags.glowing = 0;
    work->flags.glow = 0;

    VrBox4InitShadow(work);
    GM_ConfigControlAttribute(&work->control, 1);
    GM_ActControl(control);
    GM_ActObject2(&work->object);
    GM_ConfigControlTrapCheck(control);

    light = work->object.objs->light;
    light->t[0] = light->t[1] = light->t[2] = 127;

    if (work->flags.type == TYPE_UFO2)
    {
        InitLife(work);
        NewPadVibration(vib_none, 1);
        NewPadVibration(vib_start, 0);
        work->sphere_state = 1;
        work->pad_498 = 0;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewVrBox4(int name, int where)
{
    Work *work;

    work = GV_NewActor(5, sizeof(Work));

    if (work)
    {
        GV_SetNamedActor(&work->actor, VrBox4Act, Die, "vrbox.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return work;
}
