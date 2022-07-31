#include "gglsight.h"

extern short    word_8009F714[];

#pragma INCLUDE_ASM("asm/Equip/gglsight_act_helper_80077A24.s")
#pragma INCLUDE_ASM("asm/Equip/gglsight_act_helper_80077C6C.s")
#pragma INCLUDE_ASM("asm/Equip/gglsight_act_helper_80077D24.s")
#pragma INCLUDE_ASM("asm/Equip/gglsight_act_helper_80077F70.s")
#pragma INCLUDE_ASM("asm/Equip/gglsight_act_helper_80078054.s")
#pragma INCLUDE_ASM("asm/Equip/gglsight_act_80078228.s")

void gglsight_kill_800783F8(void)
{
    word_8009F714[0] = 0;
}

#pragma INCLUDE_ASM("asm/Equip/gglsight_loader1_80078404.s")
#pragma INCLUDE_ASM("asm/Equip/gglsight_loader2_80078444.s")
#pragma INCLUDE_ASM("asm/Equip/gglsight_init_80078520.s")
