#include "game/game.h"

typedef struct _Work
{
    /* +0x0000 */ GV_ACT actor;
    /* +0x0020 */ char   pad1[0x5D90];
} Work;

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C7AB0.s")
#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C7C0C.s")
#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C7CF4.s")
#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C85FC.s")

void *abst_800C864C(KCB *kcb)
{
    return kcb->cbuffer;
}

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C8658.s")
#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C877C.s")
#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C8A60.s")

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C8B58.s")
void abst_800C8B58(Work *work);

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C98B8.s")
void abst_800C98B8(Work *work);

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C9954.s")
#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C9A40.s")
#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C9AAC.s")

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C9C30.s")
int abst_800C9C30(Work *work, int where);

void *NewAbstractDemo1(int name, int where)
{
    Work *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = GV_NewActor(GV_ACTOR_MANAGER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, abst_800C8B58, abst_800C98B8, "ab_demo1.c");
        if (abst_800C9C30(work, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}
