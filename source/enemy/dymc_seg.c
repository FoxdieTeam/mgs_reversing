#include "dymc_seg.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libhzd/libhzd.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    HZD_HDL *hzd;
    HZD_SEG  seg;
    SVECTOR  min;
    SVECTOR  max;
    int      field_48;
    int      field_4C;
} Work;

/*---------------------------------------------------------------------------*/

extern char s07a_dword_800E2F10[];

static void Act(Work *work)
{
    HZD_SEG *seg;

    seg = &work->seg;
    if (work->field_4C != 0)
    {
        if (work->field_48 == 0)
        {
            work->field_4C = 0;
            seg->p1.y = work->min.vy - 10000;
            seg->p2.y = work->max.vy - 10000;
        }
    }
    else if (work->field_48 != 0)
    {
        work->field_4C = 1;
        seg->p1.y = work->min.vy;
        seg->p2.y = work->max.vy;
    }
}

static void Die(Work *work)
{
    HZD_DequeueDynamicSegment(work->hzd, &work->seg);
}

static int GetResources(Work *work, int map, SVECTOR *min, SVECTOR *max, int min_h, int max_h, int flag)
{
    HZD_SEG *seg;

    work->map = map;
    work->min = *min;
    work->max = *max;

    seg = &work->seg;
    seg->p1.x = min->vx;
    seg->p1.y = min->vy;
    seg->p1.z = min->vz;
    seg->p1.h = min_h;

    seg->p2.x = max->vx;
    seg->p2.y = max->vy;
    seg->p2.z = max->vz;
    seg->p2.h = max_h;

    HZD_SetDynamicSegment(seg, seg);
    work->hzd = GM_FindMap(map)->hzd;
    HZD_QueueDynamicSegment2(work->hzd, seg, flag);

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewDynamicSegment(int map, SVECTOR *min, SVECTOR *max, int min_h, int max_h, int flag, void **arg6)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, s07a_dword_800E2F10);
        if (GetResources(work, map, min, max, min_h, max_h, flag) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        if (arg6 != NULL)
        {
            *arg6 = &work->field_48;
        }
        work->field_48 = 1;
        work->field_4C = 1;
    }
    return (void *)work;
}
