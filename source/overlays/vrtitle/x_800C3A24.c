// vrtitle: VR revision copy of overlays/rank/chara/pocket/entry.c
// (rank_800D2300), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "game/game.h"
#include "overlays/vrtitle/vrpocket.h"

void vrtitle_800C3A24( PocketObj *obj, int arg1 )
{
    unsigned short v;
    int            w; // FIXME: int copy of v steers the zero-extension (andi 0xffff)

    v = obj->field_14.half.field_16;
    w = v;
    obj->field_14.half.field_16 = ( w & 0x180 ) | ( ( arg1 & 3 ) << 5 ) | ( v & 0x10 ) | ( v & 0xF ) | ( w & 0x800 );
}
