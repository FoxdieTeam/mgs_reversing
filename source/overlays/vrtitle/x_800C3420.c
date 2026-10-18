#include "game/game.h"
#include "libgcl/libgcl.h"

extern int vrtitle_dword_800D9CF8;

void vrtitle_800C3420( char *work )
{
    unsigned short *update;
    char           *iter;
    int             i;

    update = (unsigned short *)( work + 0x1998 );
    i = 0;
    if ( *(int *)( work + 0x1994 ) > 0 )
    {
        do
        {
            for ( iter = (char *)vrtitle_dword_800D9CF8; iter; iter = *(char **)( iter + 4 ) )
            {
                if ( *(unsigned short *)( iter + 0x24 ) == update[ 0 ] )
                {
                    *(short *)( iter + 0x26 ) = update[ 1 ];
                    break;
                }
            }
            update += 2;
        } while ( *(int *)( work + 0x1994 ) > ++i );
    }
    *(int *)( work + 0x1994 ) = 0;
}
