#include "game/game.h"
#include "menu/radio.h"
#include "libgcl/libgcl.h"

char *vrtitle_800C3A5C( int id );

void vrtitle_800C3AA0( int id, int mask )
{
    unsigned short *flags;

    flags = (unsigned short *)( vrtitle_800C3A5C( id ) + 0x1E );
    *flags |= mask;
}
