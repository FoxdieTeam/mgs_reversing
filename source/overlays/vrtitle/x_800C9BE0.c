#include "game/game.h"
#include "libgcl/libgcl.h"

extern int vrtitle_dword_800D9D00;

void vrtitle_800C9BE0( char *work )
{
    unsigned short *update;
    char           *iter;
    int             i;

    update = (unsigned short *)( work + 0x38 );
    i = 0;
    if ( *(int *)( work + 0x34 ) > 0 )
    {
        do
        {
            for ( iter = (char *)vrtitle_dword_800D9D00; iter; iter = *(char **)( iter + 4 ) )
            {
                if ( *(unsigned short *)( iter + 0x24 ) == update[ 0 ] )
                {
                    *(short *)( iter + 0x26 ) = update[ 1 ];
                    break;
                }
            }
            update += 2;
        } while ( *(int *)( work + 0x34 ) > ++i );
    }
    *(int *)( work + 0x34 ) = 0;
}

void vrtitle_800C9C54( char *work )
{
    work[ 0x13 ] = 0;
    *(short *)( work + 0x26 ) = 0;
    *(short *)( work + 0x0E ) = 0;
    *(short *)( work + 0x0C ) = 0;
    *(int *)( work + 0x18 ) = 0;
    *(int *)( work + 0x14 ) = 0;
    *(short *)( work + 0x1E ) = 0;
}
