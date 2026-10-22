// vrtitle: VR revision copy of overlays/rank/chara/pocket/pkt_back.c
// (rank_800CF3A0), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "game/game.h"
#include "libgcl/libgcl.h"
#include "overlays/vrtitle/vrpocket.h"

PocketObj *vrtitle_800C9DA8( int id );
void       vrtitle_800C9C54( PocketObj *obj );

void vrtitle_800C9E20( int id )
{
    vrtitle_800C9C54( vrtitle_800C9DA8( id ) );
}
