// vrtitle: VR revision copy of overlays/rank/chara/pocket/entry.c
// (no C twin in the main tree, rank overlay asm: rank_800D21DC area), VR revision adapted from the asm
#include "game/game.h"
#include "overlays/vrtitle/vrpocket.h"

PocketObj *vrtitle_800C3A5C( int id );

void vrtitle_800C3B08( int id, int value )
{
    vrtitle_800C3A5C( id )->field_28 = value;
}
