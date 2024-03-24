#include "Bullet/jirai.h"
#include "Game/target.h"
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

extern int GM_CurrentMap_800AB9B0;

unsigned short dymc_seg_hashes[] = {0xD182, 0x006B};

#define EXEC_LEVEL 5

void DymcSegAct_800C4A44(DymcSegWork *work)
{
    GM_CurrentMap_800AB9B0 = work->map;

    if (THING_Msg_CheckMessage(work->name, 2, dymc_seg_hashes) == 1)
    {
        GV_DestroyActor_800151C8(&work->actor);
    }
}

void DymcSegDie_800C4A98(DymcSegWork *work)
{
    HZD_DequeueDynamicSegment2_8006FE44(work->hzd, &work->seg);
}

int DymcSegGetResources_800C4AC0(DymcSegWork *work, int name, int where)
{
    SVECTOR  min, max;
    int      height;
    int      flags;
    HZD_SEG *seg;
    SVECTOR *vec;

    GM_CurrentMap_800AB9B0 = where;

    work->map = where;
    work->name = name;

    if (GCL_GetOption_80020968('p'))
    {
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &min);
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &max);
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

    HZD_SetDynamicSegment_8006FEE4(seg, seg);

    work->hzd = Map_FromId_800314C0(where)->field_8_hzd;
    HZD_QueueDynamicSegment2_8006FDDC(work->hzd, seg, flags);
    return 0;
}

GV_ACT *NewDymcSeg_800C4BCC(int name, int where, int argc, char **argv)
{
    DymcSegWork *work;

    work = (DymcSegWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(DymcSegWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)DymcSegAct_800C4A44, (TActorFunction)DymcSegDie_800C4A98, "dymc_seg.c");

        if (DymcSegGetResources_800C4AC0(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
