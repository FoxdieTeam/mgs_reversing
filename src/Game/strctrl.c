#include "strctrl.h"

extern Actor_strctrl strctrl_800B82B0;

int FS_StreamGetTop_80023F94(int is_movie);
Actor_strctrl* strctrl_init_80037B64(int sector, int gcl_proc, int a3);

#pragma INCLUDE_ASM("asm/Game/strctrl_act_helper_800377EC.s")
#pragma INCLUDE_ASM("asm/Game/strctrl_act_80037820.s")
#pragma INCLUDE_ASM("asm/Game/strctrl_kill_80037AE4.s")
#pragma INCLUDE_ASM("asm/Game/strctrl_init_80037B64.s")
#pragma INCLUDE_ASM("asm/Game/GM_StreamStatus_80037CD8.s")
#pragma INCLUDE_ASM("asm/Game/GM_StreamPlayStart_80037D1C.s")
#pragma INCLUDE_ASM("asm/Game/GM_StreamPlayStop_80037D64.s")

void sub_80037DB8(void)
{
    strctrl_800B82B0.field_38_proc = -1;
}

int GM_StreamGetLastCode_80037DC8(void)
{
    return strctrl_800B82B0.field_30_voxStream;
}

#pragma INCLUDE_ASM("asm/libgcl/commands/GCL_Command_demo_helper_80037DD8.s")
#pragma INCLUDE_ASM("asm/Game/GM_VoxStream_80037E40.s")

Actor_strctrl* sub_80037EE0(int voxStream, int gclProc)
{
    int pTop; // $v0

    strctrl_800B82B0.field_30_voxStream = voxStream;
    pTop = FS_StreamGetTop_80023F94(0);
    return strctrl_init_80037B64(voxStream + pTop, gclProc, 1);
}
