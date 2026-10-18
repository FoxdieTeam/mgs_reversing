#include "game/game.h"
#include "libgcl/libgcl.h"

char *vrtitle_800C9DA8( int id );

void vrtitle_800C9DEC( int id, int mask )
{
    unsigned short *flags;

    flags = (unsigned short *)( vrtitle_800C9DA8( id ) + 0x1E );
    *flags &= ~mask;
}
