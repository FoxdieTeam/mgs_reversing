#include "stgfd_io.h"
#include "libdg.h"
#include "dgd.h"

extern const char   aStgfdIoC[];

extern int          stgfd_io_act_80074F5C(Actor_stgfd_io *pActor);
extern int          stgfd_io_kill_80075164(Actor_stgfd_io *pActor);
extern int          stgfd_io_loader_80075194(struct Actor *pActor);

extern int GV_PauseLevel_800AB928;
extern int GV_Clock_800AB920;

void stgfd_io_act_helper_80074DAC(Actor_stgfd_io *pActor)
{
    short rgb[3]; // or RGB struct?
    if ( !GV_PauseLevel_800AB928 )
    {
        pActor->field_28++;
        if ( pActor->field_24 >= pActor->field_28 )
        {
            rgb[0] = pActor->field_2C.vx + (((pActor->field_34.vx - pActor->field_2C.vx) * pActor->field_28)) / pActor->field_24;
            rgb[1] = pActor->field_2C.vy + (((pActor->field_34.vy - pActor->field_2C.vy) * pActor->field_28)) / pActor->field_24;
            rgb[2] = pActor->field_2C.vz + (((pActor->field_34.vz - pActor->field_2C.vz) * pActor->field_28)) / pActor->field_24;
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


#pragma INCLUDE_ASM("asm/Okajima/stgfd_io_act_80074F5C.s")
extern DG_CHNL DG_Chanls_800B1800[3];


#pragma INCLUDE_ASM("asm/Okajima/stgfd_io_kill_80075164.s")
#pragma INCLUDE_ASM("asm/Okajima/stgfd_io_loader_80075194.s")

struct Actor *NewStnFade_800752A0(void)
{
    struct Actor *actor;

    actor = GV_NewActor_800150E4(3, 0x40);
    if (actor)
    {
        GV_SetNamedActor_8001514C(actor,
                            (TActorFunction)&stgfd_io_act_80074F5C,
                            (TActorFunction)&stgfd_io_kill_80075164,
                            aStgfdIoC);
        if (stgfd_io_loader_80075194(actor) < 0)
        {
            GV_DestroyActor_800151C8(actor);
            return 0;
        }
    }
    return actor;
}
