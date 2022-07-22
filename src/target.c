#include "linker.h"
#include "target.h"
#include "game.h"

GM_Target SECTION(".gTargets_800B64E0") gTargets_800B64E0[64];

extern int gTargets_down_count_800ABA68;
int SECTION(".sbss") gTargets_down_count_800ABA68;

extern int dword_800ABA6C;
int SECTION(".sbss") dword_800ABA6C;

#pragma INCLUDE_ASM("asm/sub_8002D208.s")

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper_helper_8002D300.s")

void GM_Reset_helper2_8002D3F0(void)
{
    gTargets_down_count_800ABA68 = 0;
    dword_800ABA6C = 0;
}

#pragma INCLUDE_ASM("asm/Game/GM_AllocTarget_8002D400.s")

#pragma INCLUDE_ASM("asm/Game/GM_FreeTarget_8002D4B0.s")

#pragma INCLUDE_ASM("asm/Game/GM_Target_SetVector_8002D500.s")

#pragma INCLUDE_ASM("asm/Game/GM_CaptureTarget_8002D530.s")

#pragma INCLUDE_ASM("asm/Game/GM_C4Target_8002D620.s")

#pragma INCLUDE_ASM("asm/Game/sub_8002D6D8.s")

#pragma INCLUDE_ASM("asm/sub_8002D7DC.s")

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper_8002DA14.s")

void GM_SetTarget_8002DC74(GM_Target *pTarget, int targetFlags, int whichSide, SVECTOR *pSize)
{
    short cur_map = GM_CurrentMap_800AB9B0;
    pTarget->field_0_flags = targetFlags;
    pTarget->field_2_side = whichSide;
    pTarget->field_6_flags = 0;
    pTarget->field_4_map = cur_map;
    pTarget->field_10_size = *pSize;
    pTarget->field_3C = 0;
}

void GM_Target_8002DCB4(char* arg0, short arg1, short arg2, int arg3, int arg4) {
    *(int*)(arg0 + 0x18) = arg3;
    *(short*)(arg0 + 0x3e) = arg1;
    *(short*)(arg0 + 0x2a) = arg2;
    *(int*)(arg0 + 0x1c) = arg4;
}

#pragma INCLUDE_ASM("asm/Game/GM_Target_8002DCCC.s")

void sub_8002DD14(int param_1, int param_2)
{
  *(int *)(param_1 + 0x20) = param_2;
  return;
}

#pragma INCLUDE_ASM("asm/sub_8002DD1C.s")

#pragma INCLUDE_ASM("asm/sub_8002DDE0.s")

#pragma INCLUDE_ASM("asm/GM_Target_8002E1B8.s")

#pragma INCLUDE_ASM("asm/sub_8002E2A8.s")

void GM_Target_8002E374(int *ppDownCount, GM_Target **ppTargets)
{
    *ppDownCount = gTargets_down_count_800ABA68;
    *ppTargets = gTargets_800B64E0;
}
