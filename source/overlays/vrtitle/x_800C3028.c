#include "game/game.h"
#include "libgcl/libgcl.h"

void *vrtitle_800C3028( int count, int flag )
{
    int size;

    size = 0x34;
    if ( flag == 0 )
    {
        size = 0x28;
    }

    return GV_Malloc( count * size );
}
