// vrtitle: VR revision copy of overlays/rank/chara/pocket/pkt_back.c
// (rank_800CF36C), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "game/game.h"
#include "libgcl/libgcl.h"
#include "overlays/vrtitle/vrpocket.h"

PocketObj *vrtitle_800C3A5C( int id );

void vrtitle_800C3AD4( int id, int mask )
{
    PocketObj *obj;

    obj = vrtitle_800C3A5C( id );
    obj->flags &= ~mask;
}
