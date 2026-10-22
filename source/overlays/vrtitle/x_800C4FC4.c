// vrtitle: VR revision copy of overlays/rank/chara/pocket/entry.c
// (rank_800D2830, rank_800D2864), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "game/game.h"
#include "menu/radio.h"
#include "libgcl/libgcl.h"
#include "overlays/vrtitle/vrpocket.h"

PocketObj *vrtitle_800C3A5C( int id );

void vrtitle_800C4FC4( int arg0 )
{
    PocketObj *obj;

    obj = vrtitle_800C3A5C( 14 );
    obj->enabled = 1;
    obj->field_1C = arg0;
}

void vrtitle_800C4FF8( void )
{
    PocketObj *obj;

    obj = vrtitle_800C3A5C( 14 );
    obj->enabled = 0;
}
