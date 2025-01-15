#include "meryl72.h"

/****Inlines**********************************************************************************************/
static inline void UnsetAction( Meryl72Work *work, int n_action )
{
    extern short    ActTable_800C3310[];

    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3310[n_action], 0, ACTINTERP, 0x3FE );
}

static inline void UnsetMode( Meryl72Work *work )
{
    extern short    ActTable_800C3310[];
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3310[STANDSTILL], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}
/*********************************************************************************************************/

extern int GM_PlayerMap_800ABA0C;

void s07c_meryl72_unk1_800CAD30( Meryl72Work* work, int time )
{
    if ( time == 0 )
    {
        UnsetAction( work, ACTION14 );
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

void s07c_meryl72_unk1_800CADEC( Meryl72Work* work, int time)
{
    if ( time == 0 )
    {
        UnsetAction( work, ACTION15 );
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

void ActOverScoutD_800CAEA8( Meryl72Work* work, int time)
{
    work->vision.length = 2000;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION16 );
    }

    if ( !( work->pad.press & 0x4 ) )
    {
        UnsetMode( work );
    }
}

void s07c_meryl72_unk1_800CAF30( Meryl72Work* work, int time)
{
    work->vision.length = 2000;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION19 );
    }

    if ( !( work->pad.press & 0x2000 ) )
    {
        UnsetMode( work );
    }
}

void s07c_meryl72_unk1_800CAFB8( Meryl72Work* work, int time)
{
    work->vision.length = 0;
    if ( time == 0 )
    {
        UnsetAction( work, ACTION27 );
    }

    if ( work->body.time2 )
    {
        UnsetMode( work );
    }
}

void s07c_meryl72_unk1_800CB038( Meryl72Work* work, int time)
{
    work->vision.length = 0;
    if ( time == 0 )
    {
        UnsetAction( work, ACTION25 );
    }

    if ( work->body.time2 )
    {
        UnsetMode( work );
    }
}

void s07c_meryl72_unk1_800CB0B8( Meryl72Work* work, int time)
{
    if ( time == 0 )
    {
        UnsetAction( work, ACTION26 );
    }

    if ( work->body.time2 )
    {
        UnsetMode( work );
    }
}

void s07c_meryl72_unk1_800CB134( Meryl72Work* work, int time)
{
    work->vision.length = 0;
    if ( time == 0 )
    {
        UnsetAction( work, ACTION22 );
    }

    if ( work->body.time2 )
    {
        UnsetMode( work );
    }
}

extern void AN_Sleep_800CA7DC( SVECTOR *pos ) ;

void s07c_meryl72_unk1_800CB1B4( Meryl72Work *work, int time )
{
    SVECTOR mov;
    work->vision.length = 0;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION23 );
        if ( work->control.map->index & GM_PlayerMap_800ABA0C && GV_RandU( 12 ) > 4 )
        {
            work->pad.sound = 0xF0;
        }
    }

    if ( time == 20 )
    {
            mov = work->control.mov;
            mov.vy += 500;
            AN_Sleep_800CA7DC( &mov );
    }

    if ( work->pad.press & 0x1000 )
    {
        SetMode( work, s07c_meryl72_unk1_800C98E0 );
        UnsetMode( work );
        return;
    }

    if ( time == 130 )
    {
        UnsetMode( work );
    }
}