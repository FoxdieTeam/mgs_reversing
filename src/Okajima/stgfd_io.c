#include "stgfd_io.h"

extern const char   aStgfdIoC[];

extern int          stgfd_io_act_80074F5C(int *a1);
extern int          stgfd_io_kill_80075164(int a1);
extern int          stgfd_io_loader_80075194(struct Actor *pActor);

extern int GV_PauseLevel_800AB928;
extern int GV_Clock_800AB920;

#pragma INCLUDE_ASM("asm/Okajima/stgfd_io_act_helper_80074DAC.s")
void stgfd_io_act_helper_80074DAC(Actor_stgfd_io *pActor);

void stgfd_io_act_helper_80074F44(Actor_stgfd_io *pActor, int a2, int x, int y, int z)
{
    pActor->field_24 = a2;
    pActor->field_34.vx = x;
    pActor->field_34.vy = y;
    pActor->field_34.vz = z;
}


#pragma INCLUDE_ASM("asm/Okajima/stgfd_io_act_80074F5C.s")

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
