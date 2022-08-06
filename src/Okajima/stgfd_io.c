#include "stgfd_io.h"
#include "libdg/dgd.h"

// extern const char   aStgfdIoC[];

extern int     GV_PauseLevel_800AB928;
extern int     GV_Clock_800AB920;
extern SVECTOR DG_ZeroVector_800AB39C;

extern DG_CHNL DG_Chanls_800B1800[3];

// for switch in stgfd_io_act_80074F5C
// const int SECTION(".rdata") dword_80012F74[] = {0x80075084, 0x80075098, 0x800750B0, 0x800750D4, 0x800750EC,
// 0x80075104, 0x8007511C};

void stgfd_io_act_helper_80074DAC(Actor_stgfd_io *pActor)
{
    short rgb[3]; // or RGB struct?
    if (!GV_PauseLevel_800AB928)
    {
        pActor->field_28++;
        if (pActor->field_24 >= pActor->field_28)
        {
            rgb[0] = pActor->field_2C.vx +
                     (((pActor->field_34.vx - pActor->field_2C.vx) * pActor->field_28)) / pActor->field_24;
            rgb[1] = pActor->field_2C.vy +
                     (((pActor->field_34.vy - pActor->field_2C.vy) * pActor->field_28)) / pActor->field_24;
            rgb[2] = pActor->field_2C.vz +
                     (((pActor->field_34.vz - pActor->field_2C.vz) * pActor->field_28)) / pActor->field_24;
        }
        setRGB0(&pActor->field_20_pAlloc0x30->field_10_tile[GV_Clock_800AB920], rgb[0], rgb[1], rgb[2]);
    }
}

void stgfd_io_act_helper_80074F44(Actor_stgfd_io *pActor, int a2, int x, int y, int z)
{
    pActor->field_24 = a2;
    pActor->field_34.vx = x;
    pActor->field_34.vy = y;
    pActor->field_34.vz = z;
}

void stgfd_io_act_80074F5C(Actor_stgfd_io *pActor)
{
    DG_CHNL       *p = &DG_Chanls_800B1800[1];
    unsigned char *pOt = p->mOrderingTables[GV_Clock_800AB920];
    addPrim(pOt, &pActor->field_20_pAlloc0x30->field_10_tile[GV_Clock_800AB920]);

    addPrim(pOt, &pActor->field_20_pAlloc0x30->field_0_dr_tpage[GV_Clock_800AB920]);

    stgfd_io_act_helper_80074DAC(pActor);

    if (pActor->field_28 == pActor->field_24)
    {
        pActor->field_28 = 0;
        pActor->field_2C = pActor->field_34;

        switch (pActor->field_3C_state)
        {
        case 0:
            stgfd_io_act_helper_80074F44(pActor, 4, 250, 250, 250);
            break;
        case 1:
            stgfd_io_act_helper_80074F44(pActor, 2, 190, 190, 170);
            break;
        case 2:
            stgfd_io_act_helper_80074F44(pActor, 2, 240, 240, 240);
            break;
        case 3:
            stgfd_io_act_helper_80074F44(pActor, 2, 190, 190, 60);
            break;
        case 4:
            stgfd_io_act_helper_80074F44(pActor, 2, 220, 220, 170);
            break;
        case 5:
            stgfd_io_act_helper_80074F44(pActor, 40, 220, 220, 170);
            break;
        case 6:
            stgfd_io_act_helper_80074F44(pActor, 80, 0, 0, 0);
            break;
        default:
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            break;
        }
        pActor->field_3C_state++;
    }
}

void stgfd_io_kill_80075164(Actor_stgfd_io *pActor)
{
    if (pActor->field_20_pAlloc0x30)
    {
        GV_DelayedFree_80016254(pActor->field_20_pAlloc0x30);
    }
}

int stgfd_io_loader_80075194(Actor_stgfd_io *pActor)
{
    Actor_stgfd_io_0x30 *pAlloc = GV_Malloc_8001620C(sizeof(Actor_stgfd_io_0x30));
    pActor->field_20_pAlloc0x30 = pAlloc;
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

    pActor->field_28 = 0;
    pActor->field_2C = DG_ZeroVector_800AB39C;
    pActor->field_34.vx = 240;
    pActor->field_34.vy = 240;
    pActor->field_34.vz = 240;
    pActor->field_24 = 1;
    pActor->field_3C_state = 0;
    return 0;
}

const char SECTION(".rdata") aStgfdIoC[] = "stgfd_io.c"; // 80012F90

struct Actor *NewStnFade_800752A0(void)
{
    Actor_stgfd_io *actor = (Actor_stgfd_io *)GV_NewActor_800150E4(3, sizeof(Actor_stgfd_io));
    if (actor)
    {
        GV_SetNamedActor_8001514C(&actor->field_0_actor, (TActorFunction)stgfd_io_act_80074F5C,
                                  (TActorFunction)stgfd_io_kill_80075164, aStgfdIoC);
        if (stgfd_io_loader_80075194(actor) < 0)
        {
            GV_DestroyActor_800151C8(&actor->field_0_actor);
            return 0;
        }
    }
    return &actor->field_0_actor;
}
