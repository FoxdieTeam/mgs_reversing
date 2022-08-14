#include "strctrl.h"

extern int dword_800B82E8;
extern int dword_800B82E0;

#pragma INCLUDE_ASM("asm/Game/strctrl_act_helper_800377EC.s")
#pragma INCLUDE_ASM("asm/Game/strctrl_act_80037820.s")
#pragma INCLUDE_ASM("asm/Game/strctrl_kill_80037AE4.s")
#pragma INCLUDE_ASM("asm/Game/strctrl_init_80037B64.s")
#pragma INCLUDE_ASM("asm/Game/GM_StreamStatus_80037CD8.s")
#pragma INCLUDE_ASM("asm/Game/GM_StreamPlayStart_80037D1C.s")
#pragma INCLUDE_ASM("asm/Game/GM_StreamPlayStop_80037D64.s")

void sub_80037DB8(void)
{
    dword_800B82E8 = -1;
}

int GM_StreamGetLastCode_80037DC8(void)
{
    return dword_800B82E0;
}

#pragma INCLUDE_ASM("asm/libgcl/commands/GCL_Command_demo_helper_80037DD8.s")
#pragma INCLUDE_ASM("asm/Game/GM_VoxStream_80037E40.s")
#pragma INCLUDE_ASM("asm/sub_80037EE0.s")
