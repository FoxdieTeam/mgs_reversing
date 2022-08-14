#include "strctrl.h"
#include "mts/mts_new.h"

extern Actor_strctrl strctrl_800B82B0;
extern int GM_GameStatus_800AB3CC;
extern const char aVoxstreamD[];
extern const char aGmStreamplayst[];

int FS_StreamGetTop_80023F94(int is_movie);
Actor_strctrl* strctrl_init_80037B64(int sector, int gcl_proc, int a3);
void srand_8008E6E8(int s);

#pragma INCLUDE_ASM("asm/Game/strctrl_act_helper_800377EC.s")
#pragma INCLUDE_ASM("asm/Game/strctrl_act_80037820.s")
#pragma INCLUDE_ASM("asm/Game/strctrl_kill_80037AE4.s")
#pragma INCLUDE_ASM("asm/Game/strctrl_init_80037B64.s")
#pragma INCLUDE_ASM("asm/Game/GM_StreamStatus_80037CD8.s")
#pragma INCLUDE_ASM("asm/Game/GM_StreamPlayStart_80037D1C.s")

void GM_StreamPlayStop_80037D64()
{
    mts_printf_8008BBA0(aGmStreamplayst);
    FS_StreamStop_80024028();

    // TODO: Probably a switch
    if ( (unsigned int)(unsigned short)strctrl_800B82B0.field_20_state - 1 < 2 )
    {
        GV_DestroyOtherActor_800151D8(&strctrl_800B82B0.field_0_actor);
    }
}

void sub_80037DB8(void)
{
    strctrl_800B82B0.field_38_proc = -1;
}

int GM_StreamGetLastCode_80037DC8(void)
{
    return strctrl_800B82B0.field_30_voxStream;
}

Actor_strctrl* GCL_Command_demo_helper_80037DD8(int base_sector, int gcl_proc)
{
    int total_sector; // $s0

    strctrl_800B82B0.field_30_voxStream = base_sector;
    GM_GameStatus_800AB3CC |= 0x20u;
    total_sector = base_sector + FS_StreamGetTop_80023F94(1);
    do {} while (0);
    srand_8008E6E8(1);
    return strctrl_init_80037B64(total_sector, gcl_proc, 2);
}

#pragma INCLUDE_ASM("asm/Game/GM_VoxStream_80037E40.s")

Actor_strctrl* sub_80037EE0(int voxStream, int gclProc)
{
    int pTop; // $v0

    strctrl_800B82B0.field_30_voxStream = voxStream;
    pTop = FS_StreamGetTop_80023F94(0);
    return strctrl_init_80037B64(voxStream + pTop, gclProc, 1);
}
