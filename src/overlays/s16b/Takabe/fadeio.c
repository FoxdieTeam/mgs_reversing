#include "libdg/libdg.h"
#include "libgcl/hash.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "fadeio.h"
#include "Takabe/thing.h"

typedef struct FadeIoPrims
{
    DR_TPAGE tpage[2];
    TILE     tile[2];
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

extern int GV_Clock_800AB920;
extern int GV_PassageTime_800AB924;
extern int GV_PauseLevel_800AB928;
extern int GM_GameStatus_800AB3CC;

unsigned short fadeio_msgs[] = {HASH_KILL, 0x71F1};

#define EXEC_LEVEL 3

void FadeIoAct_800C3E7C(FadeIoWork *work)
{
    int   status;
    char *ot;
    int   shade;

    if (GV_PauseLevel_800AB928 == 0)
    {
        status = THING_Msg_CheckMessage(work->field_20, 2, fadeio_msgs);
        if (status == 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return;
        }

        if (status == 1)
        {
            work->field_2c = 0;
            work->field_34_name |= 0x1;
        }
    }

    ot = DG_ChanlOTag(1);
    addPrim(ot, &work->field_24_prims->tile[GV_Clock_800AB920]);
    addPrim(ot, &work->field_24_prims->tpage[GV_Clock_800AB920]);

    if (work->field_2c > work->field_28_where)
    {
        work->field_2c = work->field_28_where;
    }

    shade = (work->field_2c * 255) / work->field_28_where;
    if (work->field_34_name & 0x1)
    {
        shade = 255 - shade;
    }

    if (GV_PauseLevel_800AB928 == 0)
    {
        if (!(GM_GameStatus_800AB3CC & GAME_FLAG_BIT_32))
        {
            work->field_2c++;
        }
        else
        {
            work->field_38 += GV_PassageTime_800AB924;
            work->field_2c += work->field_38 >> 1;
            work->field_38 &= 0x1;
        }
    }

    work->field_30 = shade;
    setRGB0(&work->field_24_prims->tile[GV_Clock_800AB920], shade, shade, shade);

    if ((work->field_34_name & 0x1) && (work->field_2c >= work->field_28_where))
    {
        GV_DestroyActor_800151C8(&work->actor);
    }
}

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

    prims = GV_Malloc_8001620C(sizeof(FadeIoPrims));
    work->field_24_prims = prims;
    if (prims == NULL)
    {
        return -1;
    }
    if (name & 2)
    {
        setDrawTPage(&prims->tpage[0], 0, 1, getTPage(0, 1, 0, 0));
        setDrawTPage(&prims->tpage[1], 0, 1, getTPage(0, 1, 0, 0));
    }
    else
    {
        setDrawTPage(&prims->tpage[0], 0, 1, getTPage(0, 2, 0, 0));
        setDrawTPage(&prims->tpage[1], 0, 1, getTPage(0, 2, 0, 0));
    }
    setTile(&prims->tile[0]);
    setSemiTrans(&prims->tile[0], 1);

    prims->tile[0].w = 0x140;
    prims->tile[0].h = 0xE0;
    prims->tile[0].x0 = 0;
    prims->tile[0].y0 = 0;
    prims->tile[1] = prims->tile[0];
    if (!(name & 1))
    {
        prims->tile[0].r0 = 0;
        prims->tile[0].g0 = 0;
        prims->tile[0].b0 = 0;
        prims->tile[1].r0 = 0;
        prims->tile[1].g0 = 0;
        prims->tile[1].b0 = 0;
        work->field_30 = 0;
    }
    else
    {
        prims->tile[0].r0 = 0xFF;
        prims->tile[0].g0 = 0xFF;
        prims->tile[0].b0 = 0xFF;
        prims->tile[1].r0 = 0xFF;
        prims->tile[1].g0 = 0xFF;
        prims->tile[1].b0 = 0xFF;
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

    work = (FadeIoWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(FadeIoWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)FadeIoAct_800C3E7C, (TActorFunction)FadeIoDie_800C40D0,
                                  "fadeio.c");
        if (FadeIoGetResources_800C4100(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        work->field_20 = 0x62FE;
    }
    return &work->actor;
}

GV_ACT *NewFadeIo_800C42BC(int name, int where, int argc, char **argv)
{
    FadeIoWork *work;

    work = (FadeIoWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(FadeIoWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)FadeIoAct_800C3E7C, (TActorFunction)FadeIoDie_800C40D0, "fadeio.c");

        if (FadeIoGetResources_800C4100(work, THING_Gcl_GetInt('m'), THING_Gcl_GetInt('s')) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        work->field_20 = name;
    }

    return &work->actor;
}
