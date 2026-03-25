#include "game/game.h"

typedef struct _Work
{
    GV_ACT actor;
    char   pad1[0x3B7C];
} Work;

#define EXEC_LEVEL 4

const char s11g_aPlasma_800DCFD8[] = "plasma";
const char s11g_aStnfr_800DCFE0[] = "stn_fr";

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_11g_demo_800CB41C.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_11g_demo_800CB4B4.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_11g_demo_800CB534.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_11g_demo_800CB600.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_11g_demo_800CB67C.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_11g_demo_800CB764.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_11g_demo_800CB7FC.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_11g_demo_800CB858.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_11g_demo_800CB878.s")

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_11g_demo_800CB994.s")
int s11g_11g_demo_800CB994(Work *work);

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_11g_demo_800CC46C.s")
int s11g_11g_demo_800CC46C(Work *work);

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_11g_demo_800CC50C.s")
int s11g_11g_demo_800CC50C(Work *work, int name, int where);

void *NewStage11GDemo(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(work, s11g_11g_demo_800CB994, s11g_11g_demo_800CC46C, "11g_demo.c");

        if (s11g_11g_demo_800CC50C(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}
