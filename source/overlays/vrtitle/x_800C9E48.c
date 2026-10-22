// vrtitle: VR revision copy of overlays/rank/chara/pocket/pkt_back.c
// (rank_800CF3C8), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "game/game.h"
#include "libgcl/libgcl.h"

typedef struct PocketBackWork
{
    /* 0x00 */ GV_ACT actor;
    /* 0x20 */ char   pad_20[ 0x44 ];
    /* 0x64 */ int    proc_id; // GCL proc executed on destroy
} PocketBackWork;

void vrtitle_800C9E48( PocketBackWork *work )
{
    GCL_ExecProc( work->proc_id, NULL );
    GV_DestroyActor( &work->actor );
}
