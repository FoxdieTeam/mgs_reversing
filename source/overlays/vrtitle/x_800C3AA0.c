// vrtitle: VR revision copy of overlays/rank/chara/pocket/entry.c
// (rank_800D2188), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "game/game.h"
#include "libgcl/libgcl.h"
#include "overlays/vrtitle/vrpocket.h"

PocketObj *vrtitle_800C3A5C( int id );

void vrtitle_800C3AA0( int id, int mask )
{
    PocketObj *obj;

    obj = vrtitle_800C3A5C( id );
    obj->flags |= mask;
}
