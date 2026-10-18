// vrtitle: VR revision copy of overlays/rank/chara/pocket/pkt_back.c
// (rank_800CF1D4), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "game/game.h"
#include "libgcl/libgcl.h"

void vrtitle_800C3908( char *work )
{
    work[ 0x13 ] = 0;
    *(short *)( work + 0x26 ) = 0;
    *(short *)( work + 0x0E ) = 0;
    *(short *)( work + 0x0C ) = 0;
    *(int *)( work + 0x18 ) = 0;
    *(int *)( work + 0x14 ) = 0;
    *(short *)( work + 0x1E ) = 0;
}
