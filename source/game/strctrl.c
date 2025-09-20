#include "strctrl.h"

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "sd/sd_cli.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/jimctrl.h"
#include "kojo/demo.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_MANAGER

extern StreamCtrlWork strctrl_work;

/*---------------------------------------------------------------------------*/

int str_sector_8009E280 = 0;
int str_gcl_proc_8009E284 = 0;
int str_8009E288 = 0;

static void Act2( StreamCtrlWork *work )
{
    if ( !FS_StreamTaskState() )
    {
        GV_DestroyActor( &work->actor );
    }
}

static void Act( StreamCtrlWork *work )
{
    int sd_code;
    int stream_data;

    GM_CurrentMap = work->map;
    FS_StreamSync();
    switch ( work->field_20_state )
    {
    case 1:
        if ( FS_StreamTaskState() < 0 )
        {
            return;
        }
        work->field_20_state = 2;

    case 2:
        if ( !work->field_22_sub_state )
        {
            work->field_20_state = 3;
            GM_GameStatus |= STATE_VOX_STREAM;
            work->field_34_pStreamData = ( int* )FS_StreamGetData( 0x10 );
            FS_StreamTickStart();
            work->field_22_sub_state = 1;
            return;
        }
        break;

    case 3:
loop_case3:
        if ( work->field_34_pStreamData ||
            ( work->field_34_pStreamData = ( int* )FS_StreamGetData( 0x10 ) ) )
        {
            stream_data = *work->field_34_pStreamData;
            if ( ( FS_StreamGetTick() >= ( stream_data >> 8 ) ) &&
                !FS_StreamIsForceStop() )
            {
                switch ( stream_data & 0xFF )
                {
                case 1:
                    if ( !sd_str_play() )
                    {
                        FS_StreamClearType( work->field_34_pStreamData, 1 );
                        FS_StreamSoundMode();
                        sd_code = 0xE0000000;
                        if ( !work->field_26_flags )
                        {
                            sd_code++;
                        }
                        GM_SetSound( sd_code, SD_ASYNC );
                        break;
                    }
                    printf( "Double Pcm !!\n" );
                    return;
                case 5:
                    DG_UnDrawFrameCount = 3;
                    DM_ThreadStream( 1, 0 );
                    work->field_24 = 1;
                    break;
                case 3:
                    NewJimakuControl( work->field_26_flags );
                    break;
                case 6:
                    NewJimakuControl( work->field_26_flags | 0x80 );
                    break;
                default:
                    printf( "??? WRONG TYPE HEADER!!\n" );
                    break;
                }
                FS_StreamClear( work->field_34_pStreamData );
                work->field_34_pStreamData = NULL;
                work->field_22_sub_state = 2;
                goto loop_case3;
            }
        }
        if ( work->field_22_sub_state == 2 && !FS_StreamIsEnd() )
        {
            work->field_22_sub_state = 0;
        }
        if ( ( !work->field_22_sub_state || FS_StreamIsForceStop() )
            && FS_StreamIsEnd() && !FS_StreamSync() )
        {
            printf( "StreamPlay end\n" );
            if ( work->field_24 )
            {
                DG_UnDrawFrameCount = 0x7FFF0000;
            }
            work->actor.act = ( GV_ACTFUNC )&Act2;
        }
        break;
    }
}

static void Die( StreamCtrlWork *work )
{
    int cb_proc;

    cb_proc = work->field_38_proc;
    work->field_20_state = 0;
    GM_GameStatus &= ~STATE_VOX_STREAM;
    if ( cb_proc >= 0 )
    {
        work->field_38_proc = -1;
        GCL_ExecProc( cb_proc, 0 );

    }
    if ( str_sector_8009E280 )
    {
        NewStreamControl( str_sector_8009E280, str_gcl_proc_8009E284, str_8009E288 );
        str_sector_8009E280 = 0;
    }
}

void *NewStreamControl( int stream_code, int gcl_proc, int flags )
{
    printf( "NewStream %d\n", stream_code );

    if ( strctrl_work.field_20_state )
    {
        printf( "pend!!\n" );
        if ( str_sector_8009E280 )
        {
            if ( str_gcl_proc_8009E284 < 0 )
            {
                GCL_ExecProc( str_gcl_proc_8009E284 & 0xFFFF, 0 );
            }
        }
        GM_StreamPlayStop();
        str_sector_8009E280 = stream_code;
        str_gcl_proc_8009E284 = gcl_proc;
        str_8009E288 = flags;
        return (void *)&strctrl_work;
    }

    FS_StreamInit( ( void * )0x801E7800, FS_CDLOAD_BUF_SIZE );
    GV_InitActor( EXEC_LEVEL, ( GV_ACT * )&strctrl_work, NULL );
    GV_SetNamedActor( ( GV_ACT * )&strctrl_work, &Act, &Die, "strctrl.c" );

    strctrl_work.field_20_state = 1;
    strctrl_work.field_38_proc = ( gcl_proc < 0 ) ? ( gcl_proc & 0xFFFF ) : -1;
    if ( gcl_proc & 0x40000000 )
    {
        strctrl_work.field_22_sub_state = 1;
    }
    else
    {
        strctrl_work.field_22_sub_state = 0;
    }
    strctrl_work.field_26_flags = flags;
    strctrl_work.field_24 = 0;
    strctrl_work.map = GM_CurrentMap;

    FS_StreamTaskStart( stream_code );
    return (void *)&strctrl_work;
}

/*---------------------------------------------------------------------------*/

int GM_StreamStatus( void )
{
    int state;

    state = strctrl_work.field_20_state - 1;
    if ( !(strctrl_work.field_20_state || !FS_StreamTaskState()) )
    {
        return 2;
    }
    return state;
}

void GM_StreamPlayStart( void )
{
    // TODO: Probably a switch
    if ( (u_int)(u_short)strctrl_work.field_20_state - 1 < 2 )
    {
        strctrl_work.field_22_sub_state = 0;
    }
    else
    {
        printf( "stream is not ready\n" );
    }
}

void GM_StreamPlayStop( void )
{
    printf( "GM_StreamPlayStop\n" );
    FS_StreamStop();

    // TODO: Probably a switch
    if ( (u_int)(u_short)strctrl_work.field_20_state - 1 < 2 )
    {
        GV_DestroyOtherActor( &strctrl_work.actor );
    }
}

void GM_StreamCancelCallback( void )
{
    strctrl_work.field_38_proc = -1;
}

int GM_StreamGetLastCode( void )
{
    return strctrl_work.field_30_voxStream;
}

void *GM_DemoStream( int base_sector, int gcl_proc )
{
    int total_sector;

    strctrl_work.field_30_voxStream = base_sector;
    GM_GameStatus |= STATE_VOX_STREAM;
    total_sector = base_sector + FS_StreamGetTop( 1 );
    do {} while (0);
    srand( 1 );
    return NewStreamControl( total_sector, gcl_proc, 2 );
}

void *GM_VoxStream( int vox_code, int proc )
{
    strctrl_work.field_30_voxStream = vox_code;
    vox_code++; vox_code--;
    if ( GM_GameStatus & STATE_GAME_OVER )
    {
        return 0;
    }

    printf( "VoxStream %d\n", vox_code );
    if ( !(proc & 0x40000000) )
    {
        GM_GameStatus |= STATE_VOX_STREAM;
    }
    return NewStreamControl( vox_code + FS_StreamGetTop(0), proc, 0 );
}

void *sub_80037EE0( int vox_stream, int gcl_proc )
{
    strctrl_work.field_30_voxStream = vox_stream;
    return NewStreamControl( vox_stream + FS_StreamGetTop(0), gcl_proc, 1 );
}
