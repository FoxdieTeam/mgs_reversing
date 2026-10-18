// vrtitle: VR revision copy of overlays/rank/chara/pocket/pkt_back.c
// (rank_800CF1D4), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "game/game.h"
#include "libgcl/libgcl.h"
#include "overlays/vrtitle/vrpocket.h"

void vrtitle_800C3908( PocketObj *obj )
{
    obj->enabled = 0;
    obj->value = 0;
    obj->field_E = 0;
    obj->field_C = 0;
    obj->field_18 = 0;
    obj->field_14 = 0;
    obj->flags = 0;
}
