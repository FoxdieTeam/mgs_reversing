#include "strctrl.h"
#include "mts/mts_new.h"
#include "data/data/data.h"
#include "libgcl/gcl.h"
#include "libfs/libfs.h"

extern Actor_strctrl    strctrl_800B82B0;
extern int              GM_GameStatus_800AB3CC;
extern const char       aVoxstreamD[];
extern const char       aGmStreamplayst[];
extern const char       aStreamIsNotRea[];

extern int              str_sector_8009E280;
extern int              str_gcl_proc_8009E284;
extern int              str_8009E288;

Actor_strctrl           *strctrl_init_80037B64(int sector, int gcl_proc, int a3);
void                    srand_8008E6E8(int s);

//------------------------------------------------------------------------------

void            strctrl_act_helper_800377EC(Actor_strctrl *pActor)
{
    if ( !FS_StreamTaskState_80023E0C() )
    {
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
    }
}

#pragma INCLUDE_ASM("asm/Game/strctrl_act_80037820.s") // 708 bytes

void            strctrl_kill_80037AE4(Actor_strctrl *pActor)
{
    int field_38_proc; // $a1

    field_38_proc = pActor->field_38_proc;
    pActor->field_20_state = 0;
    GM_GameStatus_800AB3CC &= ~0x20u;
    if ( field_38_proc >= 0 )
    {
        pActor->field_38_proc = -1;
        GCL_ExecProc_8001FF2C( field_38_proc, 0);
        
    }
    if ( str_sector_8009E280 )
    {
        strctrl_init_80037B64(str_sector_8009E280, str_gcl_proc_8009E284, str_8009E288);
        str_sector_8009E280 = 0;
    }
}

#pragma INCLUDE_ASM("asm/Game/strctrl_init_80037B64.s") // 372 bytes
#pragma INCLUDE_ASM("asm/Game/GM_StreamStatus_80037CD8.s") // 68 bytes

void            GM_StreamPlayStart_80037D1C()
{
    // TODO: Probably a switch
    if ( (unsigned int)(unsigned short)strctrl_800B82B0.field_20_state - 1 < 2 )
    {
        strctrl_800B82B0.field_22_sub_state = 0;
    }
    else
    {
        mts_printf_8008BBA0(aStreamIsNotRea); 
    }
}

void            GM_StreamPlayStop_80037D64()
{
    mts_printf_8008BBA0(aGmStreamplayst);
    FS_StreamStop_80024028();

    // TODO: Probably a switch
    if ( (unsigned int)(unsigned short)strctrl_800B82B0.field_20_state - 1 < 2 )
    {
        GV_DestroyOtherActor_800151D8(&strctrl_800B82B0.field_0_actor);
    }
}

void            sub_80037DB8(void)
{
    strctrl_800B82B0.field_38_proc = -1;
}

int             GM_StreamGetLastCode_80037DC8(void)
{
    return strctrl_800B82B0.field_30_voxStream;
}

Actor_strctrl   *GCL_Command_demo_helper_80037DD8(int base_sector, int gcl_proc)
{
    int total_sector; // $s0

    strctrl_800B82B0.field_30_voxStream = base_sector;
    GM_GameStatus_800AB3CC |= 0x20u;
    total_sector = base_sector + FS_StreamGetTop_80023F94(1);
    do {} while (0);
    srand_8008E6E8(1);
    return strctrl_init_80037B64(total_sector, gcl_proc, 2);
}

Actor_strctrl   *GM_VoxStream_80037E40(int voxCode, int proc)
{
    strctrl_800B82B0.field_30_voxStream = voxCode;
    voxCode++; voxCode--;
    if (GM_GameStatus_800AB3CC & 0x4000000)
    {
        return 0;
    }
    
    mts_printf_8008BBA0(aVoxstreamD, voxCode);
    if (!(proc & 0x40000000))
    {
        GM_GameStatus_800AB3CC |= 0x20;
    }
    return strctrl_init_80037B64(voxCode + FS_StreamGetTop_80023F94(0), proc, 0);
}

Actor_strctrl   *sub_80037EE0(int voxStream, int gclProc)
{
    int pTop; // $v0

    strctrl_800B82B0.field_30_voxStream = voxStream;
    pTop = FS_StreamGetTop_80023F94(0);
    return strctrl_init_80037B64(voxStream + pTop, gclProc, 1);
}
