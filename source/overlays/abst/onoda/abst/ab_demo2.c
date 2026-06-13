#include "game/game.h"

typedef struct _Work
{
    /* +0x0000 */ GV_ACT actor;
    /* +0x0020 */ char   pad1[0x7864];
} Work;

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800CA568.s")
#pragma INCLUDE_ASM("asm/overlays/abst/abst_800CA6FC.s")
#pragma INCLUDE_ASM("asm/overlays/abst/abst_800CA7F0.s")
#pragma INCLUDE_ASM("asm/overlays/abst/abst_800CB1E0.s")

void *abst_800CB230(KCB *kcb)
{
    return kcb->cbuffer;
}

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800CB23C.s")
#pragma INCLUDE_ASM("asm/overlays/abst/abst_800CB360.s")
#pragma INCLUDE_ASM("asm/overlays/abst/abst_800CB644.s")
#pragma INCLUDE_ASM("asm/overlays/abst/abst_800CB73C.s")

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800CB8A4.s")
void abst_800CB8A4(Work *work);

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800CCC20.s")
void abst_800CCC20(Work *work);

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800CCCBC.s")
#pragma INCLUDE_ASM("asm/overlays/abst/abst_800CCDA8.s")
#pragma INCLUDE_ASM("asm/overlays/abst/abst_800CCE14.s")

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800CCF98.s")
int abst_800CCF98(Work *work, int where);

void *NewAbstractDemo2(int name, int where)
{
    Work *work;

    GM_GameStatus |= STATE_ALL_OFF;
    
    work = GV_NewActor(GV_ACTOR_MANAGER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, abst_800CB8A4, abst_800CCC20, "ab_demo2.c");
        if (abst_800CCF98(work, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}
