#include "game/game.h"
#include "menu/radio.h"
#include "libgcl/libgcl.h"

void vrtitle_800C3C10( unsigned char *a0, unsigned int a1 )
{
    unsigned int v0;

    v0 = a0[ 7 ];
    v0 &= 2;
    v0 |= 0x2C;
    v0 <<= 24;
    a1 |= v0;
    *(unsigned int *)( a0 + 4 ) = a1;
}
