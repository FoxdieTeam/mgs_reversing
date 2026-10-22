// vrtitle: VR revision copy of overlays/rank/chara/pocket/pkt_back.c
// (rank_800CEF28), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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
