#include "dymc_seg.h"

#include "common.h"
#include "Bullet/jirai.h"
#include "Game/game.h"
#include "Takabe/thing.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "libhzd/libhzd.h"

typedef struct DymcSegWork
{
    GV_ACT   actor;
    int      map;
    int      name;
    HZD_HDL *hzd;
    HZD_SEG  seg;
} DymcSegWork;

unsigned short dymc_seg_hashes[] = {HASH_ON2, HASH_OFF2};

#define EXEC_LEVEL GV_ACTOR_LEVEL5

void DymcSegAct_800C4A44(DymcSegWork *work)
{
    GM_CurrentMap = work->map;

    if (THING_Msg_CheckMessage(work->name, 2, dymc_seg_hashes) == 1)
    {
        GV_DestroyActor(&work->actor);
    }
}

void DymcSegDie_800C4A98(DymcSegWork *work)
{
    HZD_DequeueDynamicSegment(work->hzd, &work->seg);
}

int DymcSegGetResources_800C4AC0(DymcSegWork *work, int name, int where)
{
    SVECTOR  min, max;
    int      height;
    int      flags;
    HZD_SEG *seg;
    SVECTOR *vec;

    GM_CurrentMap = where;

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

void *NewDymcSeg_800C4BCC(int name, int where, int argc, char **argv)
{
    DymcSegWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(DymcSegWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, DymcSegAct_800C4A44, DymcSegDie_800C4A98, "dymc_seg.c");

        if (DymcSegGetResources_800C4AC0(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
