#include "game/game.h"

#define EXEC_LEVEL 5

typedef struct _Work
{
    GV_ACT actor;
    char   pad1[0x144];
} Work;

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jdrumfir_800CA13C.s")
void s19b_jdrumfir_800CA13C(Work *work);

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jdrumfir_800CA280.s")
void s19b_jdrumfir_800CA280(Work *work);

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jdrumfir_800CA2BC.s")
int s19b_jdrumfir_800CA2BC(Work *work, MATRIX *world, int, int);

void *NewJeepDrumFire(MATRIX *world, int arg1, int arg2)
{
    Work* work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL) {
        GV_SetNamedActor(work, s19b_jdrumfir_800CA13C, s19b_jdrumfir_800CA280, "jdrumfir.c");
        if (s19b_jdrumfir_800CA2BC(work, world, arg1, arg2) < 0) {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return work;
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jdrumfir_800CA3E8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jdrumfir_800CA4A0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jdrumfir_800CA564.s")
