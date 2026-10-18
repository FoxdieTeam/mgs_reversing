#include "vrbox2.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libetc.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "strcode.h"
#include "bullet/blast.h"
#include "takabe/thing.h"
#include "koba/vr/vr.h"

extern BLAST_DATA blast_data_8009F4B8[8];

// FIXME: splashvr.h lives in the splashvr branch; remove this prototype when merged
void *NewSplashVr(MATRIX *world, SVECTOR *size, short count, int param, u_short tex_name, int spread);

int printf(const char *fmt, ...);

/*---------------------------------------------------------------------------*/
// VR-DISC wall target ("ＶＲＢＯＸ２"): a plate or a box (kabe) that blocks the way with dynamic hazard walls/floors
// until it is shot, then bursts into pieces (koba/vr/splashvr.c)

#define OFFSET_PLATE        1000    // lifts a flat plate (option 'k') above the position
#define OFFSET_BOX          500     // lifts a box above the position
#define BOX_SIZE            525
#define BOX_HEIGHT          500
#define PLATE_SIZE          1000
#define SEG_HEIGHT_MARGIN   250     // the lower end of the dynamic walls reaches below the box
#define SIZE_MARGIN         50      // the target is a bit bigger than the box
#define DEFAULT_LIFE        150

// GCL options
#define OPT_POS             'p'
#define OPT_BOMB            'b'
#define OPT_HOMING          'h'
#define OPT_NO_SPLASH       'a'
#define OPT_LIFE            'l'
#define OPT_PROC            'e'
#define OPT_SOLID           'w'
#define OPT_TYPE            'm'
#define OPT_DEATH_FRAMES    'd'
#define OPT_PLATE           'k'
#define OPT_RAISE           'y'

// Sound effects
#define SE_SHOT             215
#define SE_BURST            201

#define HIT_FLASH_LIGHT     127

typedef struct _Vrbox2Flags
{
    unsigned int solid      : 1;    // bit 0: blocks the way (dynamic hazard)
    unsigned int plate      : 1;    // bit 1: flat plate ('k' option) instead of a box
    unsigned int turned     : 1;    // bit 2: plate is turned by 90 degrees
    unsigned int bomb       : 1;    // bit 3: 'b', explodes
    unsigned int has_life   : 1;    // bit 4: 'l' given
    unsigned int type       : 3;    // bit 5: model type 'm'
    unsigned int no_splash  : 1;    // bit 8: 'a', no debris
    unsigned int unused_9   : 23;
} Vrbox2Flags;

typedef struct _Work
{
    GV_ACT       actor;                 // 0x00
    int          where;                 // 0x20
    int          name;                  // 0x24
    OBJECT       object;                // 0x28
    MATRIX       light[2];              // 0x10C
    SVECTOR      size;                  // 0x14C
    TARGET      *target;                // 0x154
    HOMING      *homing;                // 0x158
    MATRIX       world;                 // 0x15C
    int          dying;                 // 0x17C
    int          proc;                  // 0x180
    int          n_segs;                // 0x184
    HZD_HDL     *hzd;                   // 0x188
    HZD_SEG      segs[4];               // 0x18C
    int          n_flrs;                // 0x1CC
    HZD_FLR      flrs[2];               // 0x1D0
    CONTROL      control;               // 0x230
    SVECTOR      pos;                   // 0x2AC
    Vrbox2Flags  flags;                 // 0x2B4
    u_char       hit_flash;             // 0x2B8
    u_char       splash_spread;         // 0x2B9
    char         death_frames;          // 0x2BA
    int          splash_tex;            // 0x2BC
} Work;                                 // 0x2C0

// Data in the scratchpad while the floor is built
typedef struct _FloorScratch
{
    SVECTOR in[4];
    SVECTOR out[4];
    SVECTOR min;
    SVECTOR max;
} FloorScratch;

/*---------------------------------------------------------------------------*/

static void GetBounds(SVECTOR *pts, int n, SVECTOR *min, SVECTOR *max)
{
    int min_x, min_z, max_x, max_z;

    max_z = -32000;
    max_x = max_z;
    min_z = 32000;
    min_x = min_z;

    for (; n > 0; n--, pts++)
    {
        if (pts->vx > max_x)
        {
            max_x = pts->vx;
        }

        if (pts->vx < min_x)
        {
            min_x = pts->vx;
        }

        if (pts->vz > max_z)
        {
            max_z = pts->vz;
        }

        if (pts->vz < min_z)
        {
            min_z = pts->vz;
        }
    }

    min->vx = min_x;
    min->vz = min_z;
    max->vx = max_x;
    max->vz = max_z;
}

// Transforms the four corners into world space and builds the hazard floor from them
static void SetFloor(HZD_FLR *flr, SVECTOR *p0, SVECTOR *p1, SVECTOR *p2, SVECTOR *p3)
{
    FloorScratch *spad;

    spad = (FloorScratch *)getScratchAddr(0);

    spad->in[0] = *p0;
    spad->in[1] = *p1;
    spad->in[2] = *p2;
    spad->in[3] = *p3;

    DG_PutVector(spad->in, spad->out, 4);

    flr->p1.x = spad->out[0].vx;
    flr->p1.y = spad->out[0].vy;
    flr->p1.z = spad->out[0].vz;
    flr->p2.x = spad->out[1].vx;
    flr->p2.y = spad->out[0].vy;
    flr->p2.z = spad->out[1].vz;
    flr->p3.x = spad->out[2].vx;
    flr->p3.y = spad->out[0].vy;
    flr->p3.z = spad->out[2].vz;
    flr->p4.x = spad->out[3].vx;
    flr->p4.y = spad->out[0].vy;
    flr->p4.z = spad->out[3].vz;
    flr->p1.h = 0;
    flr->p2.h = 0;
    flr->p3.h = 0xFF;

    GetBounds(spad->out, 4, &spad->min, &spad->max);

    flr->b1.x = spad->min.vx;
    flr->b1.y = flr->p1.y - 1;
    flr->b1.z = spad->min.vz;
    flr->b2.x = spad->max.vx;
    flr->b2.y = flr->p1.y + 1;
    flr->b2.z = spad->max.vz;
    flr->b1.h = 0;
}

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    TARGET  *target;
    MATRIX  *light;
    MATRIX   rot;
    SVECTOR  dir;

    GM_CurrentMap = work->where;

    if (GM_CheckMessage(&work->actor, work->name, HASH_KILL))
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    target = work->target;

    if (VR_Status == VR_STATUS_CLEAR)
    {
        work->proc = -1;
        GV_DestroyActor(&work->actor);
    }

    GM_MoveTarget(target, &work->pos);

    if (work->hit_flash)
    {
        light = work->object.objs->light;
        light->t[0] = light->t[1] = light->t[2] = GV_Clock * 255;

        work->hit_flash = (work->hit_flash + 1) & 0xF;

        if (work->hit_flash == 0)
        {
            light = work->object.objs->light;
            light->t[0] = light->t[1] = light->t[2] = HIT_FLASH_LIGHT;
        }
    }

    if (target->damaged & 4)
    {
        if ((u_short)(target->a_mode - 1) < 2U)
        {
            target->damaged &= ~4;
            work->hit_flash = 1;
            GM_SeSetMode(&work->pos, SE_SHOT, 1);
        }

        if (work->dying == 0)
        {
            if (target->vital < 0 || (target->a_mode == 2 && !work->flags.has_life))
            {
                if (!work->flags.bomb)
                {
                    work->dying = work->death_frames;
                }
                else
                {
                    work->dying = 1;
                }

                target->class = 1;
            }
        }
    }

    if (work->dying != 0)
    {
        if (work->dying < work->death_frames)
        {
            work->dying++;
            return;
        }

        // FIXME: dead stores, the rotation is overwritten by the zero vector
        dir.vx = 0xC00;
        dir.vy = 0x400;
        dir.vz = 0;
        dir = DG_ZeroVector;

        VR_TargetCount++;
        DG_SetPos2(&work->pos, &dir);
        ReadRotMatrix(&rot);
        GM_SeSetMode(&work->pos, SE_BURST, 1);

        if (work->flags.bomb)
        {
            if (!work->flags.no_splash)
            {
                NewSplashVr(&rot, &work->size, 32, 0, work->splash_tex, work->splash_spread);
            }

            NewBlast(&rot, blast_data_8009F4B8);
        }
        else
        {
            NewSplashVr(&rot, &work->size, 64, 0, work->splash_tex, work->splash_spread);
        }

        GV_DestroyActor(&work->actor);
    }
}

static void Die(Work *work)
{
    HZD_SEG *seg;
    HZD_FLR *flr;
    int      i;

    seg = work->segs;

    if (work->flags.solid)
    {
        flr = work->flrs;
        THING_Hzd_800C4874(work->n_segs, seg, work->n_flrs, flr);

        for (i = work->n_segs; i > 0; i--)
        {
            HZD_DequeueDynamicSegment(work->hzd, seg++);
        }

        for (i = work->n_flrs; i > 0; i--)
        {
            HZD_DequeueDynamicFloor(work->hzd, flr++);
        }
    }

    GM_ResetHomingTarget(work->homing);
    GM_FreeObject(&work->object);
    GM_FreeTarget(work->target);

    if (work->proc > 0)
    {
        GCL_ExecProc(work->proc, NULL);
    }
}

static void InitTarget(Work *work, SVECTOR *size, int vital)
{
    TARGET *target;

    target = GM_AllocTarget();
    work->target = target;

    work->size = *size;
    work->size.vx += SIZE_MARGIN;
    work->size.vz += SIZE_MARGIN;

    GM_SetTarget(target, 28, 2, &work->size);
    GM_SetPowerTarget(target, 1, -1, vital, 0, &DG_ZeroVector);
    GM_MoveTarget(target, &work->pos);
}

static int GetResources(Work *work, int name, int where)
{
    MATRIX   mat;
    SVECTOR  rot;
    SVECTOR  size;
    SVECTOR  corners[4];
    OBJECT  *object;
    char    *opt;
    int      value;
    int      vital;
    HZD_SEG *seg;
    HZD_FLR *flr;
    DG_OBJ  *objs;
    int      i;
    int      j;
    int      type;

    GM_CurrentMap = where;
    work->where = where;
    work->name = name;

    opt = GCL_GetOption(OPT_POS);
    if (opt)
    {
        GCL_StrToSV(opt, &rot.vx);
        work->pos = rot;
    }
    else
    {
        work->pos = DG_ZeroVector;
    }

    rot = DG_ZeroVector;

    work->flags.bomb = GCL_GetOption(OPT_BOMB) != 0;

    if (GCL_GetOption(OPT_HOMING))
    {
        work->control.map = GM_GetMap(where);

        if (!work->control.map)
        {
            printf("InitControl : no map %X\n", where);
        }

        work->homing = GM_SetHomingTarget(&work->world, &work->control);
        work->homing->flag = 1;
    }
    else
    {
        work->homing = NULL;
    }

    if (GCL_GetOption(OPT_NO_SPLASH))
    {
        work->flags.no_splash = 1;
    }
    else
    {
        work->flags.no_splash = 0;
    }

    opt = GCL_GetOption(OPT_LIFE);
    if (opt)
    {
        work->flags.has_life = 1;
        vital = GCL_StrToInt(opt);
    }
    else
    {
        vital = DEFAULT_LIFE;
        work->flags.has_life = 0;
    }

    if (GCL_GetOption(OPT_PROC))
    {
        work->proc = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->proc = -1;
    }

    opt = GCL_GetOption(OPT_SOLID);
    if (opt)
    {
        work->flags.solid = GCL_StrToInt(opt);
    }
    else
    {
        work->flags.solid = 1;
    }

    opt = GCL_GetOption(OPT_TYPE);
    if (opt)
    {
        work->flags.type = GCL_StrToInt(opt);
    }
    else
    {
        work->flags.type = 0;
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

    object = &work->object;

    if (work->flags.type == 0)
    {
        opt = GCL_GetOption(OPT_PLATE);
        if (opt)
        {
            work->flags.plate = 1;
            value = GCL_StrToInt(opt);

            if (value < 2)
            {
                work->flags.turned = value & 1;
                GM_InitObject(object, GV_StrCode("kabe_n"), 0x15D, 0);
            }
            else
            {
                work->flags.turned = 0;
                GM_InitObject(object, GV_StrCode("kabe_y"), 0x15D, 0);
            }

            work->flags.turned = GCL_StrToInt(opt) & 1;
            work->splash_tex = GV_StrCode("kabe_01add");
            work->splash_spread = 64;
        }
        else
        {
            if (!work->flags.bomb)
            {
                GM_InitObject(object, GV_StrCode("kt_n"), 0x15D, 0);
                work->splash_tex = GV_StrCode("mato_00add");
            }
            else
            {
                GM_InitObject(object, GV_StrCode("kt_b"), 0x15D, 0);
                work->splash_tex = GV_StrCode("mato_02add");
            }

            work->splash_spread = 64;
            work->flags.plate = 0;
            work->flags.turned = 0;
        }

        if (work->flags.turned)
        {
            RotMatrixY(0x400, &object->objs->world);
        }

        if (work->flags.plate)
        {
            work->pos.vy += OFFSET_PLATE;
            object->objs->world.t[0] = work->pos.vx;
            object->objs->world.t[1] = work->pos.vy;
            object->objs->world.t[2] = work->pos.vz;
            work->world = work->object.objs->world;
            work->world.t[1] += 200;
        }
        else
        {
            work->pos.vy += OFFSET_BOX;
            object->objs->world.t[0] = work->pos.vx;
            object->objs->world.t[1] = work->pos.vy - OFFSET_BOX;
            object->objs->world.t[2] = work->pos.vz;
            work->world = work->object.objs->world;
            work->world.t[1] += 700;
        }
    }
    else
    {
        work->flags.plate = 0;
        work->splash_spread = 64;

        type = work->flags.type;
        switch (type)
        {
        case 1:
            GM_InitObject(object, GV_StrCode("kt_n"), 0x15D, 0);
            work->splash_tex = GV_StrCode("mato_00add");
            break;

        case 2:
            GM_InitObject(object, GV_StrCode("kt_b"), 0x15D, 0);
            work->splash_tex = GV_StrCode("mato_02add");
            work->flags.bomb = 1;
            break;

        case 3:
            GM_InitObject(object, GV_StrCode("ice"), 0x15D, 0);
            break;
        }

        work->pos.vy += OFFSET_BOX;
        object->objs->world.t[0] = work->pos.vx;
        object->objs->world.t[1] = work->pos.vy - OFFSET_BOX;
        object->objs->world.t[2] = work->pos.vz;
        work->world = work->object.objs->world;
        work->world.t[1] += 700;
    }

    opt = GCL_GetOption(OPT_RAISE);
    if (opt)
    {
        objs = object->objs->objs;

        for (i = 0; i < object->objs->n_models; i++)
        {
            objs->raise += GCL_StrToInt(opt);
            objs++;
        }
    }

    GM_ConfigObjectLight(object, work->light);

    work->object.objs->light->t[0] = work->object.objs->light->t[1] = work->object.objs->light->t[2] = HIT_FLASH_LIGHT;

    work->dying = 0;
    work->hit_flash = 0;

    if (work->flags.plate)
    {
        if (work->flags.turned)
        {
            size.vx = 0;
            size.vy = PLATE_SIZE;
            size.vz = PLATE_SIZE;
        }
        else
        {
            size.vx = PLATE_SIZE;
            size.vy = PLATE_SIZE;
            size.vz = 0;
        }
    }
    else
    {
        size.vx = BOX_SIZE;
        size.vy = BOX_HEIGHT;
        size.vz = BOX_SIZE;
    }

    InitTarget(work, &size, vital);

    corners[0].vx = -size.vx;
    corners[0].vy = size.vy;
    corners[0].vz = -size.vz;
    corners[1].vx = size.vx;
    corners[1].vy = -size.vy;
    corners[1].vz = -size.vz;
    corners[2].vx = size.vx;
    corners[2].vy = size.vy;
    corners[2].vz = size.vz;
    corners[3].vx = -size.vx;
    corners[3].vy = -size.vy;
    corners[3].vz = size.vz;

    seg = work->segs;

    if (work->flags.solid)
    {
        work->hzd = GM_GetMap(where)->hzd;
        DG_SetPos2(&work->pos, &rot);
        ReadRotMatrix(&mat);

        if (!work->flags.plate)
        {
            work->n_segs = 4;

            for (i = 0; i < 4; i++)
            {
                SVECTOR *a;
                SVECTOR *b;

                a = &corners[i];
                b = &corners[(i + 1) & 3];

                a->vy = -size.vy - SEG_HEIGHT_MARGIN;
                b->vy = size.vy;
                THING_Hzd_800C45C4(seg, &mat, a, b);
                work->n_segs += HZD_QueueDynamicSegment2(work->hzd, seg, 0);
                seg++;
            }
        }
        else
        {
            SVECTOR *a;
            SVECTOR *b;

            work->n_segs = 1;
            i = work->flags.turned;
            a = &corners[i];
            a->vy = -size.vy;
            j = i + 1;
            b = &corners[j];
            b->vy = size.vy;
            THING_Hzd_800C45C4(seg, &mat, a, b);
            work->n_segs += HZD_QueueDynamicSegment2(work->hzd, seg, 0);
        }

        flr = work->flrs;

        if (!work->flags.plate)
        {
            work->n_flrs = 2;

            corners[0].vy = corners[1].vy = corners[2].vy = corners[3].vy = size.vy;
            SetFloor(flr, &corners[0], &corners[1], &corners[2], &corners[3]);
            work->n_flrs += HZD_QueueDynamicFloor(work->hzd, flr++);

            corners[0].vy = corners[1].vy = corners[2].vy = corners[3].vy = -size.vy - SEG_HEIGHT_MARGIN;
            SetFloor(flr, &corners[0], &corners[1], &corners[2], &corners[3]);
            work->n_flrs += HZD_QueueDynamicFloor(work->hzd, flr);
        }
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewVrBox2(int name, int where)
{
    Work *work;

    work = GV_NewActor(5, sizeof(Work));

    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "vrbox2.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return work;
}
