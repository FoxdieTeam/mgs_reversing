#include "libgv/libgv.h"
#include <LIBGPU.H>

extern char aFadeIo_800C5880[]; // = "fadeio.c";

typedef struct FadeIoPrims
{
    DR_TPAGE tpage;
    DR_TPAGE tpage2;
    TILE     tile1;
    TILE     tile2;
} FadeIoPrims;

typedef struct FadeIoWork
{
    GV_ACT       actor;
    int          field_20;
    FadeIoPrims *field_24_prims;
    int          field_28_where;
    int          field_2c;
    int          field_30;
    int          field_34_name;
    int          field_38;
} FadeIoWork;

void s16b_800C3E7C(FadeIoWork *);

void FadeIoDie_800C40D0(FadeIoWork *work)
{
    if (work->field_24_prims)
    {
        GV_DelayedFree_80016254(work->field_24_prims);
    }
}

int FadeIoGetResources_800C4100(FadeIoWork *work, int name, int where)
{
    FadeIoPrims *prims;

    prims = GV_Malloc_8001620C(0x30);
    work->field_24_prims = prims;
    if (prims == NULL)
    {
        return -1;
    }
    if (name & 2)
    {
        setDrawTPage(&prims->tpage, 0, 1, getTPage(0, 1, 0, 0));
        setDrawTPage(&prims->tpage2, 0, 1, getTPage(0, 1, 0, 0));
    }
    else
    {
        setDrawTPage(&prims->tpage, 0, 1, getTPage(0, 2, 0, 0));
        setDrawTPage(&prims->tpage2, 0, 1, getTPage(0, 2, 0, 0));
    }
    setTile(&prims->tile1);
    setSemiTrans(&prims->tile1, 1);

    prims->tile1.w = 0x140;
    prims->tile1.h = 0xE0;
    prims->tile1.x0 = 0;
    prims->tile1.y0 = 0;
    prims->tile2 = prims->tile1;
    if (!(name & 1))
    {
        prims->tile1.r0 = 0;
        prims->tile1.g0 = 0;
        prims->tile1.b0 = 0;
        prims->tile2.r0 = 0;
        prims->tile2.g0 = 0;
        prims->tile2.b0 = 0;
        work->field_30 = 0;
    }
    else
    {
        prims->tile1.r0 = 0xFF;
        prims->tile1.g0 = 0xFF;
        prims->tile1.b0 = 0xFF;
        prims->tile2.r0 = 0xFF;
        prims->tile2.g0 = 0xFF;
        prims->tile2.b0 = 0xFF;
        work->field_30 = 0xFF;
    }
    work->field_34_name = name;
    work->field_28_where = where;
    work->field_2c = 1;
    return 0;
}

GV_ACT *NewFadeIo_800C4224(int name, int where, int argc, char **argv)
{
    FadeIoWork *work;

    work = (FadeIoWork *)GV_NewActor_800150E4(3, sizeof(FadeIoWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s16b_800C3E7C, (TActorFunction)FadeIoDie_800C40D0,
                                  aFadeIo_800C5880);
        if (FadeIoGetResources_800C4100(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
        work->field_20 = 0x62FE;
    }
    return &work->actor;
}
