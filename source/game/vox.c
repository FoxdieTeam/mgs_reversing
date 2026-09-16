#include <stdio.h>
#include "game/game.h"

#define VOX_QUEUE_MAX   6

static int vox_queue[ VOX_QUEUE_MAX ];

static u_char num_queued = 0;
static int last_status = 0;
static int voxcode = -1;
static int last_voxcode = -1;
static char vox_end = 0;
static char playing = 0;
static int playtime = 0;
static int time = 0;
static int next_code = 0;
static int next_delay = 0;

void GM_VoxInit( void )
{
    num_queued = 0;
    last_status = -1;
    voxcode = -1;
    last_voxcode = -1;
    vox_end = 0;
    playing = 0;
    playtime = -1;
    time = -1;
    next_delay = 0;
    next_code = 0;
    if ( GM_StreamStatus() != -1 ) GM_StreamPlayStop();
}

int GM_VoxQueue( int code )
{
    if ( num_queued == VOX_QUEUE_MAX ) return -1;
    vox_queue[ num_queued ] = code;
    num_queued++;
    return 0;
}

void GM_VoxQueueDelay( int code, int delay )
{
    next_code = code;
    next_delay = delay;
}

void GM_VoxTick( void )
{
    int prev, curr;

    int timeout;
    int i;

    if ( next_delay != 0 && --next_delay <= 0 )
    {
        GM_VoxQueue( next_code );
        next_delay = 0;
    }

    prev = last_status;
    last_status = curr = GM_StreamStatus();

    vox_end = 0;
    playing = 0;

    if ( playtime >= 0 && num_queued != 0 && prev != -1 )
    {
        if ( prev == 2 ) playtime++;

        if ( ++time > 5400 )
        {
            timeout = 1;
            printf( "timeout %d\n", voxcode );
            GM_StreamPlayStop();
        }
        else
        {
            timeout = 0;
        }

        if ( curr == -1 || timeout == 1 )
        {
            voxcode = -1;
            last_voxcode = vox_queue[ 0 ];
            vox_end = 1;

            for ( i = 0; i < VOX_QUEUE_MAX - 1; i++ )
            {
                vox_queue[ i ] = vox_queue[ i + 1 ];
            }

            time = -1;
            playtime = -1;
            num_queued--;
        }
    }

    if ( curr == -1 && num_queued != 0 )
    {
        time = 0;
        playtime = 0;
        voxcode = vox_queue[ 0 ];
        playing = 1;
        GM_VoxStream( voxcode, 0 );
    }
}

int GM_VoxCurrent( void )
{
    return voxcode;
}

int GM_VoxEnd( void )
{
    return vox_end;
}

int GM_VoxPlaying( void )
{
    return playing;
}

int GM_VoxPlayTime( void )
{
    return playtime > 0;
}

int GM_VoxCodeStart( int code )
{
    if ( voxcode == code && playtime == 1 )
    {
        return 1;
    }

    return 0;
}

int GM_VoxCodeEnd( int code )
{
    if ( vox_end == 1 && last_voxcode == code )
    {
        last_voxcode = -1;
        return 1;
    }

    return 0;
}

int GM_VoxStatus( void )
{
    return last_status;
}
