#include "vrbox3.h"

#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libetc.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "strcode.h"
#include "enemy/enemy.h"
#include "koba/vr/vr.h"
#include "koba/vr/waracut.h"

/*---------------------------------------------------------------------------*/
// VR-DISC straw target ("ＶＲＢＯＸ３"): a target (nst_obj1) that is shot to pieces; when it dies it is replaced
// by the cut straw (koba/vr/waracut.c). Older, simpler revision of the VRBOX2 actor: no hazard walls, no splash.

#define BODY_FLAG           ( DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS | DG_FLAG_BOUND \
                            | DG_FLAG_ONEPIECE | DG_FLAG_AMBIENT )

#define OFFSET_POS          1140    // lifts the model above the position
#define OFFSET_FOG          250     // the dust cloud is created below the target
#define SIZE_X              250
#define SIZE_Y              500
#define SIZE_Z              250
#define SIZE_MARGIN         50      // the target is a bit bigger than the model
#define SIZE_DEAD           150
#define DEFAULT_LIFE        150
#define DEATH_FRAMES        4
#define VITAL_PROTECTED     255

// GCL options
#define OPT_POS             'p'
#define OPT_NO_SPLASH       'a'
#define OPT_LIFE            'l'
#define OPT_PROC            'e'
#define OPT_ANGLE           'd'
#define OPT_RAISE           'y'

// Sound effects
#define SE_BURST            213

typedef struct _Vrbox3Flags
{
    unsigned int unused_0   : 4;
    unsigned int has_life   : 1;    // bit 4: 'l' given
    unsigned int unused_5   : 3;
    unsigned int no_splash  : 1;    // bit 8: 'a', never used
    unsigned int unused_9   : 23;
} Vrbox3Flags;

typedef struct _Work
{
    GV_ACT       actor;                 // 0x00
    int          where;                 // 0x20
    int          name;                  // 0x24
    OBJECT       object;                // 0x28
    MATRIX       light[2];              // 0x10C
    SVECTOR      size;                  // 0x14C
    TARGET      *target;                // 0x154
    int          pad_158;               // 0x158
    MATRIX       world;                 // 0x15C
    int          dying;                 // 0x17C
    int          proc;                  // 0x180
    int          angle;                 // 0x184
    char         pad_188[0x7C];         // 0x188
    SVECTOR      pos;                   // 0x204
    Vrbox3Flags  flags;                 // 0x20C
    u_char       hit;                   // 0x210
    char         pad_211;               // 0x211
    char         death_frames;          // 0x212
    int          splash_tex;            // 0x214
} Work;                                 // 0x218

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    TARGET  *target;
    MATRIX   rot;
    SVECTOR  dir;

    // FIXME: rot and dir are unused here, they only widen the frame like in the VRBOX2 revision of this actor
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
    GM_PushTarget(target);

    if (target->damaged & 4)
    {
        if ((u_short)(target->a_mode - 1) < 2U)
        {
            target->damaged &= ~4;
            work->hit = 1;
        }

        if (work->dying == 0)
        {
            if (target->a_mode == 1)
            {
                work->dying = work->death_frames;
                target->class = 1;
            }
            else if (target->a_mode == 2)
            {
                target->vital = VITAL_PROTECTED;
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

        work->size.vx = SIZE_DEAD;
        work->size.vy = SIZE_DEAD;
        work->size.vz = SIZE_DEAD;

        VR_TargetCount++;
        NewWaraCut(&work->object.objs->world, work->angle);

        GM_SeSetMode(&work->pos, SE_BURST, 1);
        work->pos.vy -= OFFSET_FOG;
        AN_Fog(&work->pos);

        GV_DestroyActor(&work->actor);
    }
}

static void Die(Work *work)
{
    DG_FreePreshade(work->object.objs);
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
    MATRIX   mat;   // FIXME: unused, widens the frame like in the VRBOX2 revision of this actor
    SVECTOR  rot;
    SVECTOR  size;
    OBJECT  *object;
    char    *opt;
    int      vital;
    int      i;

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

    // FIXME: dead store, rot is never read again
    rot = DG_ZeroVector;

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

    work->death_frames = DEATH_FRAMES;

    opt = GCL_GetOption(OPT_ANGLE);
    if (opt)
    {
        work->angle = GCL_StrToInt(opt);
    }
    else
    {
        work->angle = 0;
    }

    object = &work->object;
    GM_InitObject(object, GV_StrCode("nst_obj1"), BODY_FLAG, 0);

    work->pos.vy += OFFSET_POS;
    object->objs->world.t[0] = work->pos.vx;
    object->objs->world.t[1] = work->pos.vy;
    object->objs->world.t[2] = work->pos.vz;
    RotMatrixY(work->angle, &object->objs->world);

    work->world = object->objs->world;
    work->world.t[1] += 200;

    work->splash_tex = GV_StrCode("nst_obj1_wara");

    opt = GCL_GetOption(OPT_RAISE);
    if (opt)
    {
        DG_OBJ *objs = object->objs->objs;

        for (i = 0; i < object->objs->n_models; i++)
        {
            objs->raise += GCL_StrToInt(opt);
            objs++;
        }
    }

    GM_ConfigObjectLight(object, work->light);
    GM_ReshadeObjs(object->objs);

    work->dying = 0;
    work->hit = 0;

    size.vx = SIZE_X;
    size.vy = SIZE_Y;
    size.vz = SIZE_Z;
    InitTarget(work, &size, vital);

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewVrBox3(int name, int where)
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
