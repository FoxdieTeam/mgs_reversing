#include "stgfd_io.h"
#include "libdg/libdg.h"

typedef struct StgfdIoPrims
{
    DR_TPAGE tpage[2];
    TILE     tile[2];
} StgfdIoPrims;

typedef struct StgfdIoWork
{
    GV_ACT        actor;
    StgfdIoPrims *prims;
    int           field_24;
    int           field_28;
    SVECTOR       field_2C;
    SVECTOR       field_34;
    int           state;
} StgfdIoWork;

#define EXEC_LEVEL 3

extern int     GV_PauseLevel_800AB928;
extern int     GV_Clock_800AB920;

void stgfd_io_act_helper_80074DAC(StgfdIoWork *work)
{
    short rgb[3]; // or RGB struct?
    if (GV_PauseLevel_800AB928)
    {
        return;
    }

    work->field_28++;
    if (work->field_24 >= work->field_28)
    {
        rgb[0] = work->field_2C.vx +
                 (((work->field_34.vx - work->field_2C.vx) * work->field_28)) / work->field_24;
        rgb[1] = work->field_2C.vy +
                 (((work->field_34.vy - work->field_2C.vy) * work->field_28)) / work->field_24;
        rgb[2] = work->field_2C.vz +
                 (((work->field_34.vz - work->field_2C.vz) * work->field_28)) / work->field_24;
    }
    setRGB0(&work->prims->tile[GV_Clock_800AB920], rgb[0], rgb[1], rgb[2]);
}

void stgfd_io_act_helper_80074F44(StgfdIoWork *work, int a2, int x, int y, int z)
{
    work->field_24 = a2;
    work->field_34.vx = x;
    work->field_34.vy = y;
    work->field_34.vz = z;
}

void stgfd_io_act_80074F5C(StgfdIoWork *work)
{
    unsigned char *pOt = DG_ChanlOTag(0);

    addPrim(pOt, &work->prims->tile[GV_Clock_800AB920]);
    addPrim(pOt, &work->prims->tpage[GV_Clock_800AB920]);

    stgfd_io_act_helper_80074DAC(work);

    if (work->field_28 == work->field_24)
    {
        work->field_28 = 0;
        work->field_2C = work->field_34;

        switch (work->state)
        {
        case 0:
            stgfd_io_act_helper_80074F44(work, 4, 250, 250, 250);
            break;
        case 1:
            stgfd_io_act_helper_80074F44(work, 2, 190, 190, 170);
            break;
        case 2:
            stgfd_io_act_helper_80074F44(work, 2, 240, 240, 240);
            break;
        case 3:
            stgfd_io_act_helper_80074F44(work, 2, 190, 190, 60);
            break;
        case 4:
            stgfd_io_act_helper_80074F44(work, 2, 220, 220, 170);
            break;
        case 5:
            stgfd_io_act_helper_80074F44(work, 40, 220, 220, 170);
            break;
        case 6:
            stgfd_io_act_helper_80074F44(work, 80, 0, 0, 0);
            break;
        default:
            GV_DestroyActor(&work->actor);
            break;
        }
        work->state++;
    }
}

void stgfd_io_kill_80075164(StgfdIoWork *work)
{
    if (work->prims)
    {
        GV_DelayedFree(work->prims);
    }
}

int stgfd_io_loader_80075194(StgfdIoWork *work)
{
    StgfdIoPrims *pAlloc = GV_Malloc(sizeof(StgfdIoPrims));
    work->prims = pAlloc;
    if (!pAlloc)
    {
        return -1;
    }

    setDrawTPage(&pAlloc->tpage[0], 0, 1, 0x20);
    setDrawTPage(&pAlloc->tpage[1], 0, 1, 0x20);

    setTile(&pAlloc->tile[0]);
    setSemiTrans(&pAlloc->tile[0], 1);
    setXY0(&pAlloc->tile[0], -160, -112);
    setWH(&pAlloc->tile[0], 320, 224);

    pAlloc->tile[1] = pAlloc->tile[0];
    setRGB0(&pAlloc->tile[0], 0, 0, 0);
    setRGB0(&pAlloc->tile[1], 0, 0, 0);

    work->field_28 = 0;
    work->field_2C = DG_ZeroVector;
    work->field_34.vx = 240;
    work->field_34.vy = 240;
    work->field_34.vz = 240;
    work->field_24 = 1;
    work->state = 0;
    return 0;
}

GV_ACT *NewStnFade_800752A0(void)
{
    StgfdIoWork *work = (StgfdIoWork *)GV_NewActor(EXEC_LEVEL, sizeof(StgfdIoWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor,
                         (GV_ACTFUNC)&stgfd_io_act_80074F5C,
                         (GV_ACTFUNC)&stgfd_io_kill_80075164,
                         "stgfd_io.c");

        if (stgfd_io_loader_80075194(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return 0;
        }
    }

    return &work->actor;
}
