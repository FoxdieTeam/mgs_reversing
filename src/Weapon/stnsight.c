#include "Game/game.h"

// stinger first person HUD?

extern PlayerStatusFlag GM_PlayerStatus_800ABA50;

void stnsight_act_helper_helper_80068320(unsigned int *ot, unsigned int *prim)
{
    if (!(GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK4000000))
    {
        addPrim(ot, prim);
    }
}

#pragma INCLUDE_ASM("asm/Weapon/stnsight_act_helper_8006837C.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_act_helper_80068420.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_act_helper_80068798.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_act_helper_80068A24.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_act_helper_80068BF4.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_act_80068D0C.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_kill_80068ED8.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_init_helper_helper_80068F74.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_init_helper_helper_80069100.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_init_helper_helper_80069184.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_init_helper_helper_80069234.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_init_helper_800692D0.s")
#pragma INCLUDE_ASM("asm/Weapon/NewStnSight_800693E0.s")
