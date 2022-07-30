#include "game.h"

extern void GM_FreeObject_80034BF8(OBJECT *obj);

#pragma INCLUDE_ASM("asm/shadow_act_helper_8005FD28.s")
#pragma INCLUDE_ASM("asm/shadow_act_helper_80060028.s")
#pragma INCLUDE_ASM("asm/shadow_act_800600E4.s")

void shadow_kill_80060190(int param_1)
{
    GM_FreeObject_80034BF8((OBJECT *)(param_1 + 0x28));
}

#pragma INCLUDE_ASM("asm/shadow_loader_800601B0.s")
#pragma INCLUDE_ASM("asm/shadow_init_800602CC.s")
#pragma INCLUDE_ASM("asm/shadow_init2_80060384.s")
