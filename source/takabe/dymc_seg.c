#include "dymc_seg.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "strcode.h"
#include "takabe/thing.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct _Work
{
    GV_ACT      actor;
    int         map;
    int         name;
    HZD_HDL    *hzd;
    HZD_SEG     seg;
} Work;

/*---------------------------------------------------------------------------*/

static unsigned short mesg_list[] = {HASH_ON2, HASH_OFF2};

static void Act(Work *work)
{
    GM_SetCurrentMap(work->map);

    if (THING_Msg_CheckMessage(work->name, 2, mesg_list) == 1)
    {
        GV_DestroyActor(&work->actor);
    }
}

static void Die(Work *work)
{
    HZD_DequeueDynamicSegment(work->hzd, &work->seg);
}

static int GetResources(Work *work, int name, int where)
{
    SVECTOR min, max;
    int     height, flags;
    HZD_SEG *seg;
    SVECTOR *vec;

    GM_SetCurrentMap(where);

    work->map = where;
    work->name = name;

    if (GCL_GetOption('p'))
    {
        GCL_StrToSV(GCL_GetParamResult(), &min);
        GCL_StrToSV(GCL_GetParamResult(), &max);
    }

    height = THING_Gcl_GetInt('h');
    flags = THING_Gcl_GetInt('s');

    seg = &work->seg;

    vec = &min;
    seg->p1.x = vec->vx;
    seg->p1.y = vec->vy;
    seg->p1.z = vec->vz;
    seg->p1.h = height;

    vec = &max;
    seg->p2.x = vec->vx;
    seg->p2.y = vec->vy;
    seg->p2.z = vec->vz;
    seg->p2.h = height;

    HZD_SetDynamicSegment(seg, seg);

    work->hzd = GM_GetMap(where)->hzd;
    HZD_QueueDynamicSegment2(work->hzd, seg, flags);
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewDynamicWallSet(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "dymc_seg.c");
        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
