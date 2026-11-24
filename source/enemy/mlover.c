#include "enemy/enemy.h"

#include "takabe/mosaic.h"

/*---------------------------------------------------------------------------*/

extern void *AN_Sleep( SVECTOR *pos );
extern void *AN_Unknown_800C3B7C( MATRIX *world );

void s07a_meryl_unk_800D7EC8( WatcherWork* work, int time );

static inline void UnsetAction( WatcherWork *work, int n_action )
{
    extern short    ActTable_800C3628[];

    work->unknown.last_unset = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3628[ n_action ], 0, ACTINTERP, 0x3FE );
}

static inline void UnsetActionManual( WatcherWork *work, int n_action, int a4 )
{
    extern short    ActTable_800C3628[];

    work->unknown.last_unset = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3628[ n_action ], 0, ACTINTERP, a4 );
}

static inline void UnsetMode( WatcherWork *work )
{
    extern short    ActTable_800C3628[];
    work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3628[ STANDSTILL ], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->unknown.last_unset = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

SVECTOR s07a_dword_800C36E0 = {0, -550, 950};

/*---------------------------------------------------------------------------*/

void s07a_meryl_unk_800D9E48( WatcherWork* work, int time )
{
    if ( time == 0 )
    {
        UnsetAction( work, ACTION9 );
    }

    if ( !( work->pad.press & 1 ) )
    {
        UnsetMode( work );
    }
    else
    {
        if ( time < 4 )
        {
            work->vision.facedir = ( work->control.rot.vy - ( time * 256 ) ) & 0xFFF;
        }
        else
        {
            work->vision.facedir = ( work->control.rot.vy - 1024 ) & 0xFFF;
        }
    }
}

void s07a_meryl_unk_800D9F14( WatcherWork* work, int time)
{
    if ( time == 0 )
    {
        UnsetAction( work, ACTION10 );
    }

    if ( !( work->pad.press & 2 ) )
    {
        UnsetMode( work );
    }
    else
    {
        if ( time < 4 )
        {
            work->vision.facedir = ( work->control.rot.vy + ( time * 256 ) ) & 0xFFF;
        }
        else
        {
            work->vision.facedir = ( work->control.rot.vy + 1024 ) & 0xFFF;
        }
    }
}

void ActOverScoutD_800D9FE0( WatcherWork* work, int time )
{
    work->vision.length = 3000;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION11 );
    }

    if ( !( work->pad.press & 4 ) )
    {
        UnsetMode( work );
    }
}

void s07a_meryl_unk_800DA078( WatcherWork* work, int time )
{
    work->vision.length = 3000;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION14 );
    }

    if ( !( work->pad.press & 0x2000 ) )
    {
        UnsetMode( work );
    }
}

void s07a_meryl_unk_800DA110( WatcherWork* work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION24 );
        GM_SeSet( &work->control.mov, 0x94 );
    }

    if ( work->body.time2 || !( work->pad.press & 0x40 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

void s07a_meryl_unk_800DA1C4( WatcherWork* work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION22 );
    }

    if ( time == 60 )
    {
        GM_SeSet( &work->control.mov, 0x92 );
    }

    if ( work->body.time2 || !( work->pad.press & 0x80 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

void s07a_meryl_unk_800DA28C( WatcherWork* work, int time )
{
    if ( time == 0 )
    {
        UnsetAction( work, ACTION23 );
    }

    if ( work->body.time2 || !( work->pad.press & 0x400 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

void s07a_meryl_unk_800DA330( WatcherWork* work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION19 );
    }

    if ( time == 90 )
    {
        GM_SeSet( &work->control.mov, 0x92 );
    }

    if ( work->body.time2 || !( work->pad.press & 0x800 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

void s07a_meryl_unk_800DA3F8( WatcherWork *work, int time )
{
    SVECTOR mov;
    work->vision.length = 0;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION19 );
    }

    if ( time == 90 )
    {
        GM_SeSet( &work->control.mov, 0x92 );
    }

    if ( time == 110 )
    {
        UnsetAction( work, ACTION20 );
    }


    if ( time > 110 )
    {
        work->act_status |= 0x10;
        if ( work->m_ctrl.info2.frame == 30 )
        {
            mov = work->control.mov;
            mov.vy += 500;
            AN_Sleep( &mov );
            GM_SeSet( &work->control.mov, 0x93 );

            if ( work->sn_dis < 1000 && ( GM_PlayerStatus & PLAYER_WATCH ) )
            {
                int res = GV_RandU( 12 );
                if ( res > 10 )
                {
                    work->pad.sound = 240;
                }
            }
        }
        if ( work->pad.press & 0x1000 )
        {
            SetMode( work, s07a_meryl_unk_800D7EC8 );
            UnsetMode( work );
            return;
        }
    }

    if ( !( work->pad.press & 0x200 ) )
    {
        UnsetMode( work );
    }
}

void s07a_meryl_unk_800DA5D0( WatcherWork *work )
{
    MATRIX world;

    DG_SetPos( &work->body.objs->objs[ 6 ].world );
    DG_MovePos( &s07a_dword_800C36E0 );
    ReadRotMatrix( &world );
    AN_Unknown_800C3B7C( &world );
}

void s07a_meryl_unk_800DA610( WatcherWork *work, int time )
{
    work->vision.length = 3000;
    work->act_status |= 0x80;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION25 );
        if ( work->mosaic == NULL )
        {
            work->mosaic = NewMosaic(&work->body.objs->objs[0].world, 300, 4, -250 );
        }
        GM_SeSet( &work->control.mov, 0xB9 );
    }

    if ( time > 30 )
    {
        GV_RandU( 4 );
        if ( time == ( ( time / 5 ) * 5 ) )
        {
            GM_SeSet( &work->control.mov, 0xB1 );
        }
        if ( (time & 3) && time > 45 )
        {
            s07a_meryl_unk_800DA5D0( work );
        }
    }

    if ( !( work->pad.press & 0x800000 ) )
    {
        UnsetMode( work );
    }
}

void s07a_meryl_unk_800DA75C( WatcherWork *work, int time )
{
    work->vision.length = 3000;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION25 );
        if ( work->mosaic == NULL )
        {
            work->mosaic = NewMosaic(&work->body.objs->objs[0].world, 300, 4, -250 );
        }
    }

    if ( time == 186 )
    {
        UnsetActionManual( work, ACTION26, 0xFFFF );
    }

    if ( time == 320 )
    {
        GM_SeSet( &work->control.mov, 0xB9 );
    }

    //?
    if ( time == 0   || time == 4   || time == 8   || time == 12  ||
         time == 20  || time == 28  || time == 36  || time == 48  ||
         time == 60  || time == 120 || time == 122 || time == 124 ||
         time == 126 || time == 180 || time == 182 || time == 184 ||
         time == 186 )
    {
        GM_SeSet( &work->control.mov, 0xB1 );
        s07a_meryl_unk_800DA5D0( work );
    }

    if ( ( time > 186 && work->body.time2 ) || !( work->pad.press & 0x1000000 ) )
    {
        GM_SeSet( &work->control.mov, 0xB4 );
        work->pad.time = 0;
        UnsetMode( work );
    }
}
