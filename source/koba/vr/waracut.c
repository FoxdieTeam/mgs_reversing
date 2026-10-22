#include "waracut.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "enemy/enemy.h"

/*---------------------------------------------------------------------------*/
// VR-DISC cut straw (nst_obj2/nst_obj3): the top half of a destroyed straw target (koba/vr/vrbox3.c) is thrown
// off the stump, tumbles away and blinks out.

#define BODY_FLAG           ( DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS | DG_FLAG_BOUND \
                            | DG_FLAG_ONEPIECE | DG_FLAG_AMBIENT )

#define TOTAL_FRAMES        55      // lifetime
#define PHASE_LAUNCH        34      // frames left: the half is pushed up
#define PHASE_TUMBLE        24      // frames left: the half tumbles
#define PHASE_FALL          -4      // frames left: the half falls
#define FRAME_FOG           23      // frame that raises a dust cloud
#define BLINK_FRAMES        20      // frames left: starts blinking

#define SE_FOG              215

typedef struct _Work
{
    GV_ACT       actor;                 // 0x00
    int          where;                 // 0x20
    int          count;                 // 0x24
    int          speed;                 // 0x28
    int          dir;                   // 0x2C
    OBJECT       stump;                 // 0x30
    OBJECT       top;                   // 0x114
    MATRIX       light[2];              // 0x1F8
    SVECTOR      step;                  // 0x238
} Work;                                 // 0x240

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    SVECTOR  tumble;
    SVECTOR  fog;

    GM_CurrentMap = work->where;

    if (work->count != 0)
    {
        work->count--;

        if (work->count >= PHASE_LAUNCH)
        {
            GV_DirVec2(work->dir, TOTAL_FRAMES - work->count, &work->step);
            work->speed = TOTAL_FRAMES + 2 - work->count;
            work->top.objs->world.t[0] += work->step.vx;
            work->top.objs->world.t[1] -= work->speed;
            work->top.objs->world.t[2] += work->step.vz;
        }
        else if (work->count >= PHASE_TUMBLE)
        {
            work->speed += 12;
            work->top.objs->world.t[0] += work->step.vx;
            work->top.objs->world.t[1] -= work->speed;
            work->top.objs->world.t[2] += work->step.vz;

            GV_DirVec2(work->dir - 0x400, 33 - work->count, &tumble);
            RotMatrixX(-(tumble.vx * 22), &work->top.objs->world);
            RotMatrixZ(-(tumble.vz * 22), &work->top.objs->world);
        }
        else if (work->count >= PHASE_FALL)
        {
            if (work->count == FRAME_FOG)
            {
                fog.vx = work->top.objs->world.t[0] + work->step.vx * 16;
                fog.vy = work->top.objs->world.t[1];
                fog.vz = work->top.objs->world.t[2] + work->step.vz * 16;
                work->speed = 85;
                AN_Fog(&fog);
                GM_SeSetMode(&fog, SE_FOG, 1);
            }

            work->speed -= 8;
            work->top.objs->world.t[0] += work->step.vx;
            work->top.objs->world.t[1] += work->speed;
            work->top.objs->world.t[2] += work->step.vz;
        }

        if (work->count < BLINK_FRAMES)
        {
            if (work->count & 1)
            {
                DG_VisibleObjs(work->top.objs);
            }
            else
            {
                DG_InvisibleObjs(work->top.objs);
            }
        }
    }
    else
    {
        DG_InvisibleObjs(work->top.objs);
    }
}

static void Die(Work *work)
{
    DG_FreePreshade(work->stump.objs);
    DG_FreePreshade(work->top.objs);
    GM_FreeObject(&work->stump);
    GM_FreeObject(&work->top);
}

static int GetResources(Work *work, MATRIX *world, int dir)
{
    work->count = TOTAL_FRAMES;
    work->speed = 0;
    work->dir = dir + 0x400;

    GM_InitObject(&work->stump, GV_StrCode("nst_obj2"), BODY_FLAG, 0);
    GM_InitObject(&work->top, GV_StrCode("nst_obj3"), BODY_FLAG, 0);

    work->stump.objs->world = *world;
    work->top.objs->world = *world;

    GM_ConfigObjectLight(&work->stump, work->light);
    GM_ConfigObjectLight(&work->top, work->light);

    GM_ReshadeObjs(work->stump.objs);
    GM_ReshadeObjs(work->top.objs);

    return 1;
}

/*---------------------------------------------------------------------------*/

void *NewWaraCut(MATRIX *world, int dir)
{
    Work *work;

    work = GV_NewActor(5, sizeof(Work));

    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "waracut.c");

        if (GetResources(work, world, dir) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return work;
}
