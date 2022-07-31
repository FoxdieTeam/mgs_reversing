#include "linker.h"
#include "libdg.h"

extern SVECTOR stru_8009F630[4];

void claymore_800731CC(SVECTOR *param_1)
{
    DG_PutVector_8001BE48(stru_8009F630, param_1, 4); // 4 = sizeof?
}

#pragma INCLUDE_ASM("asm/Okajima/claymore_loader_helper2_800731F8.s") // 184 bytes
#pragma INCLUDE_ASM("asm/Okajima/claymore_act_helper_800732B0.s") // 180 bytes
#pragma INCLUDE_ASM("asm/Okajima/claymore_act_helper_80073364.s") // 300 bytes
#pragma INCLUDE_ASM("asm/Okajima/claymore_loader_helper_80073490.s") // 272 bytes
#pragma INCLUDE_ASM("asm/Okajima/claymore_loader_helper_800735A0.s") // 272 bytes
#pragma INCLUDE_ASM("asm/Okajima/claymore_act_800736B0.s") // 580 bytes

void claymore_kill_800738F4(int param_1)
{
    DG_OBJS *prim;

    prim = *(DG_OBJS **)(param_1 + 0x84);
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
    return;
}

#pragma INCLUDE_ASM("asm/Okajima/claymore_loader_80073930.s") // 188 bytes
#pragma INCLUDE_ASM("asm/Okajima/claymore_loader_800739EC.s") // 416 bytes
#pragma INCLUDE_ASM("asm/Okajima/NewClaymore_80073B8C.s") // 548 bytes
