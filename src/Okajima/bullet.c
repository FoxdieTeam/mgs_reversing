#include "libdg.h"

#pragma INCLUDE_ASM("asm/Okajima/bullet_80075314.s") // 68 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_loader2_helper_80075358.s") // 188 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_act_helper_80075414.s") // 208 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_act_helper_800754E4.s") // 300 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_loader2_helper_80075610.s") // 332 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_loader3_8007575C.s") // 1656 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_act_80075DD4.s") // 912 bytes

void bullet_kill_80076164(int param_1)
{
    DG_OBJS *prim;

    prim = *(DG_OBJS **)(param_1 + 0x8c);
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
    return;
}

#pragma INCLUDE_ASM("asm/Okajima/bullet_loader_800761A0.s") // 212 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_loader2_80076274.s") // 428 bytes
#pragma INCLUDE_ASM("asm/Okajima/NewBulletEnemy_80076420.s") // 356 bytes
#pragma INCLUDE_ASM("asm/Okajima/bullet_init_80076584.s") // 388 bytes
#pragma INCLUDE_ASM("asm/Okajima/NewBulletEx_80076708.s") // 548 bytes
#pragma INCLUDE_ASM("asm/Okajima/sub_8007692C.s") // 192 bytes
