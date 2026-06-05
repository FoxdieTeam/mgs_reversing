#include "dymc_seg.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libhzd/libhzd.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    HZD_HDL *hzd;
    HZD_SEG  seg;
    SVECTOR  min;
    SVECTOR  max;
    int      enable;
    int      state;
} Work;

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    HZD_SEG *seg;

    seg = &work->seg;
    if (work->state != 0)
    {
        if (work->enable == 0)
        {
            work->state = 0;
            seg->p1.y = work->min.vy - 10000;
            seg->p2.y = work->max.vy - 10000;
        }
    }
    else
    {
        if (work->enable != 0)
        {
            work->state = 1;
            seg->p1.y = work->min.vy;
            seg->p2.y = work->max.vy;
        }
    }
}

static void Die(Work *work)
{
    HZD_DequeueDynamicSegment(work->hzd, &work->seg);
}

static int GetResources(Work *work, int map, SVECTOR *min, SVECTOR *max, int minh, int maxh, int flag)
{
    HZD_SEG *seg;

    work->map = map;
    work->min = *min;
    work->max = *max;

    seg = &work->seg;
    seg->p1.x = min->vx;
    seg->p1.y = min->vy;
    seg->p1.z = min->vz;
    seg->p1.h = minh;

    seg->p2.x = max->vx;
    seg->p2.y = max->vy;
    seg->p2.z = max->vz;
    seg->p2.h = maxh;

    HZD_SetDynamicSegment(seg, seg);

    work->hzd = GM_FindMap(map)->hzd;
    HZD_QueueDynamicSegment2(work->hzd, seg, flag);
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewDynamicSegment(int map, SVECTOR *min, SVECTOR *max, int minh, int maxh, int flag, int **enable)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "dymc_seg.c");
        if (GetResources(work, map, min, max, minh, maxh, flag) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        if (enable != NULL) *enable = &work->enable;
        work->enable = 1;
        work->state = 1;
    }
    return (void *)work;
}
