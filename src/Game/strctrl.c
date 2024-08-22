#include "game.h"
#include "SD/sound.h"
#include "unknown.h"
#include "Kojo/demothrd.h"
#include "strctrl.h"
#include "jimctrl.h"
#include "psyq.h"
#include "mts/mts_new.h"
#include "libgcl/libgcl.h"
#include "libfs/libfs.h"

//------------------------------------------------------------------------------

extern int              GM_GameStatus_800AB3CC;
extern StreamCtrlWork   strctrl_800B82B0;
extern int              DG_UnDrawFrameCount_800AB380;

//------------------------------------------------------------------------------

int str_sector_8009E280 = 0;
int str_gcl_proc_8009E284 = 0;
int str_8009E288 = 0;

void strctrl_act_helper_800377EC( StreamCtrlWork *work )
{
    if ( !FS_StreamTaskState_80023E0C() )
    {
        GV_DestroyActor_800151C8( &work->field_0_actor );
    }
}

void strctrl_act_80037820( StreamCtrlWork *work )
{
    int sd_code;
    int stream_data;

    GM_CurrentMap_800AB9B0 = work->map;
    FS_StreamSync_80023E24();
    switch ( work->field_20_state )
    {
    case 1:
        if ( FS_StreamTaskState_80023E0C() < 0 )
        {
            return;
        }
        work->field_20_state = 2;

    case 2:
        if ( !work->field_22_sub_state )
        {
            work->field_20_state = 3;
            GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_06;
            work->field_34_pStreamData = ( int* )FS_StreamGetData_800240E0( 0x10 );
            FS_StreamTickStart_800243D8();
            work->field_22_sub_state = 1;
            return;
        }
        break;

    case 3:
loop_case3:
        if ( work->field_34_pStreamData ||
            ( work->field_34_pStreamData = ( int* )FS_StreamGetData_800240E0( 0x10 ) ) )
        {
            stream_data = *work->field_34_pStreamData;
            if ( ( FS_StreamGetTick_80024420() >= ( stream_data >> 8 ) ) &&
                !FS_StreamIsForceStop_800243C8() )
            {
                switch ( stream_data & 0xFF )
                {
                case 1:
                    if ( !sd_str_play_800886DC() )
                    {
                        sub_800241C8( (char *)work->field_34_pStreamData, 1 );
                        FS_StreamSoundMode_80024404();
                        sd_code = 0xE0000000;
                        if ( !work->field_26_flags )
                        {
                            sd_code++;
                        }
                        GM_Sound_80032C48( sd_code, 0 );
                        break;
                    }
                    printf( "Double Pcm !!\n" );
                    return;
                case 5:
                    DG_UnDrawFrameCount_800AB380 = 3;
                    DM_ThreadStream_80079460( 1, 0 );
                    work->field_24 = 1;
                    break;
                case 3:
                    jimctrl_init_80038568( work->field_26_flags );
                    break;
                case 6:
                    jimctrl_init_80038568( work->field_26_flags | 0x80 );
                    break;
                default:
                    printf( "??? WRONG TYPE HEADER!!\n" );
                    break;
                }
                sub_800241B4( work->field_34_pStreamData );
                work->field_34_pStreamData = NULL;
                work->field_22_sub_state = 2;
                goto loop_case3;
            }
        }
        if ( work->field_22_sub_state == 2 && !FS_StreamIsEnd_800240D0() )
        {
            work->field_22_sub_state = 0;
        }
        if ( ( !work->field_22_sub_state || FS_StreamIsForceStop_800243C8() )
            && FS_StreamIsEnd_800240D0() && !FS_StreamSync_80023E24() )
        {
            printf( "StreamPlay end\n" );
            if ( work->field_24 )
            {
                DG_UnDrawFrameCount_800AB380 = 0x7FFF0000;
            }
            work->field_0_actor.act = ( TActorFunction )&strctrl_act_helper_800377EC;
        }
        break;
    }
}

void strctrl_kill_80037AE4( StreamCtrlWork *work )
{
    int cb_proc;

    cb_proc = work->field_38_proc;
    work->field_20_state = 0;
    GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_06;
    if ( cb_proc >= 0 )
    {
        work->field_38_proc = -1;
        GCL_ExecProc_8001FF2C( cb_proc, 0 );

    }
    if ( str_sector_8009E280 )
    {
        strctrl_init_80037B64( str_sector_8009E280, str_gcl_proc_8009E284, str_8009E288 );
        str_sector_8009E280 = 0;
    }
}

StreamCtrlWork *strctrl_init_80037B64( int stream_code, int gcl_proc, int flags )
{
    printf( "NewStream %d\n", stream_code );

    if ( strctrl_800B82B0.field_20_state )
    {
        printf( "pend!!\n" );
        if ( str_sector_8009E280 )
        {
            if ( str_gcl_proc_8009E284 < 0 )
            {
                GCL_ExecProc_8001FF2C( str_gcl_proc_8009E284 & 0xFFFF, 0 );
            }
        }
        GM_StreamPlayStop_80037D64();
        str_sector_8009E280 = stream_code;
        str_gcl_proc_8009E284 = gcl_proc;
        str_8009E288 = flags;
        return &strctrl_800B82B0;
    }

    FS_StreamInit_80023FD4( ( void * )0x801E7800, 0x18000 );
    GV_InitActor_800150A8( 1, ( GV_ACT * )&strctrl_800B82B0, 0 );
    GV_SetNamedActor_8001514C(  ( GV_ACT * )&strctrl_800B82B0,
                                ( TActorFunction )&strctrl_act_80037820,
                                ( TActorFunction )&strctrl_kill_80037AE4,
                                "strctrl.c" );

    strctrl_800B82B0.field_20_state = 1;
    strctrl_800B82B0.field_38_proc = ( gcl_proc < 0 )
                                    ? ( gcl_proc & 0xFFFF )
                                    : -1;
    if ( gcl_proc & 0x40000000 )
    {
        strctrl_800B82B0.field_22_sub_state = 1;
    }
    else
    {
        strctrl_800B82B0.field_22_sub_state = 0;
    }
    strctrl_800B82B0.field_26_flags = flags;
    strctrl_800B82B0.field_24 = 0;
    strctrl_800B82B0.map = GM_CurrentMap_800AB9B0;

    FS_StreamTaskStart_80023D94( stream_code );
    return &strctrl_800B82B0;
}

int GM_StreamStatus_80037CD8( void )
{
    int state;

    state = strctrl_800B82B0.field_20_state - 1;
    if ( !(strctrl_800B82B0.field_20_state || !FS_StreamTaskState_80023E0C()) )
    {
        return 2;
    }
    return state;
}

void GM_StreamPlayStart_80037D1C()
{
    // TODO: Probably a switch
    if ( (u_int)(u_short)strctrl_800B82B0.field_20_state - 1 < 2 )
    {
        strctrl_800B82B0.field_22_sub_state = 0;
    }
    else
    {
        printf( "stream is not ready\n" );
    }
}

void GM_StreamPlayStop_80037D64()
{
    printf( "GM_StreamPlayStop\n" );
    FS_StreamStop_80024028();

    // TODO: Probably a switch
    if ( (u_int)(u_short)strctrl_800B82B0.field_20_state - 1 < 2 )
    {
        GV_DestroyOtherActor_800151D8( &strctrl_800B82B0.field_0_actor );
    }
}

void GM_StreamCancelCallback_80037DB8( void )
{
    strctrl_800B82B0.field_38_proc = -1;
}

int GM_StreamGetLastCode_80037DC8( void )
{
    return strctrl_800B82B0.field_30_voxStream;
}

StreamCtrlWork *GCL_Command_demo_helper_80037DD8( int base_sector, int gcl_proc )
{
    int total_sector; // $s0

    strctrl_800B82B0.field_30_voxStream = base_sector;
    GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_06;
    total_sector = base_sector + FS_StreamGetTop_80023F94( 1 );
    do {} while (0);
    srand( 1 );
    return strctrl_init_80037B64( total_sector, gcl_proc, 2 );
}

StreamCtrlWork *GM_VoxStream_80037E40( int vox_code, int proc )
{
    strctrl_800B82B0.field_30_voxStream = vox_code;
    vox_code++; vox_code--;
    if ( GM_GameStatus_800AB3CC & GAME_FLAG_BIT_27 )
    {
        return 0;
    }

    printf( "VoxStream %d\n", vox_code );
    if ( !(proc & 0x40000000) )
    {
        GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_06;
    }
    return strctrl_init_80037B64( vox_code + FS_StreamGetTop_80023F94(0), proc, 0 );
}

StreamCtrlWork *sub_80037EE0(int vox_stream, int gcl_proc)
{
    strctrl_800B82B0.field_30_voxStream = vox_stream;
    return strctrl_init_80037B64( vox_stream + FS_StreamGetTop_80023F94(0), gcl_proc, 1 );
}
