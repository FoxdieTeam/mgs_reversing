#include "Game/game.h"

extern int GM_GameStatus_800AB3CC;
int        sub_80032748( DVECTOR *out, SVECTOR *pos );
int        sub_800327BC( DVECTOR *out, SVECTOR *pos );
int        sub_80032820( DVECTOR *out, SVECTOR *pos );
int        sub_800326D4( DVECTOR *out, SVECTOR *pos );

void       GM_Sound_800329C4( SVECTOR *arg0, int arg1, int arg2 )
{
    DVECTOR sp10;
    int     x, y, z;

    if ( arg0 )
    {
        switch ( arg2 )
        {
        case 1:
            if ( sub_80032748( &sp10, arg0 ) < 0 )
            {
                return;
            }
            break;

        case 2:
            if ( sub_800327BC( &sp10, arg0 ) < 0 )
            {
                return;
            }
            break;

        case 3:
            if ( sub_80032820( &sp10, arg0 ) < 0 )
            {
                return;
            }
            break;
        case 0:
            if ( sub_800326D4( &sp10, arg0 ) < 0 )
            {
                return;
            }
            break;
        }
    }
    else
    {
        sp10.vy = 0x3F;
        sp10.vx = 0;
    }
    
    x = sp10.vx;
    y = sp10.vy;
    if ( !( GM_GameStatus_800AB3CC & 0x84000000 ) )
    {
        y &= 0xFF;
        x &= 0xFF;
        if ( y >= 0x40 )
        {
            y = 0x3F;
        }
        z = arg1 & 0xff;
        sd_set_cli_800887EC( ( ( x << 0x10 ) | ( y << 8 ) ) | z, 0 );
    }
}
