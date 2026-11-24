#include "zako.h"

/*---------------------------------------------------------------------------*/

extern void AN_Sleep( SVECTOR *pos );

/*---------------------------------------------------------------------------*/

void ActOverScoutR( Work *work, int time )
{
    if ( time == 0 )
    {
        SetAction2( work, 9, 4, 0x3FE );
    }

    if ( !(work->pad.press & 0x1) )
    {
        UnsetMode( work );
    }
    else if ( time < 4 )
    {
        work->vision.facedir = ( work->control.rot.vy - time * 256 ) & 4095;
    }
    else
    {
        work->vision.facedir = ( work->control.rot.vy - 1024 ) & 4095;
    }
}

void ActOverScoutL( Work *work, int time )
{
    if ( time == 0 )
    {
        SetAction2( work, 10, 4, 0x3FE );
    }

    if ( !(work->pad.press & 0x2) )
    {
        UnsetMode( work );
    }
    else if ( time < 4 )
    {
        work->vision.facedir = (*(unsigned short *)&work->control.rot.vy + (time << 8)) & 4095;
    }
    else
    {
        work->vision.facedir = (*(unsigned short *)&work->control.rot.vy + 1024) & 4095;
    }
}

void s03d_800D0754( Work *work, int time )
{
    work->vision.length = 2000;

    if ( time == 0 )
    {
        SetAction2( work, 11, 4, 0x3FE );
    }

    if ( !(work->pad.press & 0x4) )
    {
        UnsetMode( work );
    }
}

void s03d_800D07DC( Work *work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        SetAction2( work, 22, 4, 0x3FE );
    }

    if ( work->body.time2 != 0 )
    {
        UnsetMode( work );
    }
}

void s03d_800D085C( Work *work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        SetAction2( work, 20, 4, 0x3FE );
    }

    if ( work->body.time2 != 0 )
    {
        UnsetMode( work );
    }
}

void s03d_800D08DC( Work *work, int time )
{
    if ( time == 0 )
    {
        SetAction2( work, 21, 4, 0x3FE );
    }

    if ( work->body.time2 != 0 )
    {
        UnsetMode( work );
    }
}

void s03d_800D0958( Work *work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        SetAction2( work, 17, 4, 0x3FE );
    }

    if ( work->body.time2 != 0 )
    {
        UnsetMode( work );
    }
}

void s03d_800D09D8( Work *work, int time )
{
    SVECTOR pos;

    work->vision.length = 0;

    if ( time == 0 )
    {
        SetAction2( work, 18, 4, 0x3FE );

        if ( work->control.map->index == GM_PlayerMap && GV_RandU( 12 ) > 4 )
        {
            work->pad.sound = 240;
        }
    }

    if ( time == 20 )
    {
        pos = work->control.mov;
        pos.vy += 500;
        AN_Sleep( &pos );
    }

    if ( work->pad.press & 0x1000 )
    {
        SetMode( work, s03d_800CED94 );
        UnsetMode( work );
    }
    else if ( time == 130 )
    {
        UnsetMode( work );
    }
}
