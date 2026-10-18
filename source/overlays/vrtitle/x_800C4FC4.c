// vrtitle: VR revision copy of overlays/rank/chara/pocket/entry.c
// (rank_800D2830, rank_800D2864), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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
