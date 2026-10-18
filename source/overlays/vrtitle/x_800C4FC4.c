#include "game/game.h"
#include "menu/radio.h"
#include "libgcl/libgcl.h"

char *vrtitle_800C3A5C( int id );

void vrtitle_800C4FC4( int arg0 )
{
    char *ptr;

    ptr = vrtitle_800C3A5C( 14 );
    ptr[ 0x13 ] = 1;
    ptr[ 0x1C ] = arg0;
}

void vrtitle_800C4FF8( void )
{
    char *ptr;

    ptr = vrtitle_800C3A5C( 14 );
    ptr[ 0x13 ] = 0;
}
