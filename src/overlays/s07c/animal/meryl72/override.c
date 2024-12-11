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