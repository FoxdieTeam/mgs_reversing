#include "stgfd_io.h"
#include "libdg/libdg.h"
//#include "libdg/dgd.h"

extern int     GV_PauseLevel_800AB928;
extern int     GV_Clock_800AB920;
extern SVECTOR DG_ZeroVector_800AB39C;

void stgfd_io_act_helper_80074DAC(StgfdIoWork *work)
{
    short rgb[3]; // or RGB struct?
    if (!GV_PauseLevel_800AB928)
    {
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
        setRGB0(&work->field_20_pAlloc0x30->field_10_tile[GV_Clock_800AB920], rgb[0], rgb[1], rgb[2]);
    }
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
    addPrim(pOt, &work->field_20_pAlloc0x30->field_10_tile[GV_Clock_800AB920]);

    addPrim(pOt, &work->field_20_pAlloc0x30->field_0_dr_tpage[GV_Clock_800AB920]);

    stgfd_io_act_helper_80074DAC(work);

    if (work->field_28 == work->field_24)
    {
        work->field_28 = 0;
        work->field_2C = work->field_34;

        switch (work->field_3C_state)
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
            GV_DestroyActor_800151C8(&work->field_0_actor);
            break;
        }
        work->field_3C_state++;
    }
}

void stgfd_io_kill_80075164(StgfdIoWork *work)
{
    if (work->field_20_pAlloc0x30)
    {
        GV_DelayedFree_80016254(work->field_20_pAlloc0x30);
    }
}

int stgfd_io_loader_80075194(StgfdIoWork *work)
{
    StgfdIoWork_0x30 *pAlloc = GV_Malloc_8001620C(sizeof(StgfdIoWork_0x30));
    work->field_20_pAlloc0x30 = pAlloc;
    if (!pAlloc)
    {
        return -1;
    }

    setDrawTPage(&pAlloc->field_0_dr_tpage[0], 0, 1, 0x20);
    setDrawTPage(&pAlloc->field_0_dr_tpage[1], 0, 1, 0x20);

    setTile(&pAlloc->field_10_tile[0]);
    setSemiTrans(&pAlloc->field_10_tile[0], 1);
    setXY0(&pAlloc->field_10_tile[0], -160, -112);
    setWH(&pAlloc->field_10_tile[0], 320, 224);

    pAlloc->field_10_tile[1] = pAlloc->field_10_tile[0];
    setRGB0(&pAlloc->field_10_tile[0], 0, 0, 0);
    setRGB0(&pAlloc->field_10_tile[1], 0, 0, 0);

    work->field_28 = 0;
    work->field_2C = DG_ZeroVector_800AB39C;
    work->field_34.vx = 240;
    work->field_34.vy = 240;
    work->field_34.vz = 240;
    work->field_24 = 1;
    work->field_3C_state = 0;
    return 0;
}

GV_ACT *NewStnFade_800752A0(void)
{
    StgfdIoWork *work = (StgfdIoWork *)GV_NewActor_800150E4(3, sizeof(StgfdIoWork));
    if (work)
    {
        GV_SetNamedActor_8001514C(&work->field_0_actor,
                                  (TActorFunction)&stgfd_io_act_80074F5C,
                                  (TActorFunction)&stgfd_io_kill_80075164,
                                  "stgfd_io.c");

        if (stgfd_io_loader_80075194(work) < 0)
        {
            GV_DestroyActor_800151C8(&work->field_0_actor);
            return 0;
        }
    }

    return &work->field_0_actor;
}
