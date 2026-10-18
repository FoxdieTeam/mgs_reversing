// vrtitle: VR revision copy of overlays/rank/chara/pocket/pkt_back.c
// (rank_800CF3C8), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "game/game.h"
#include "libgcl/libgcl.h"

void vrtitle_800C9E48( char *work )
{
    GCL_ExecProc( *(int *)( work + 0x64 ), NULL );
    GV_DestroyActor( work );
}
