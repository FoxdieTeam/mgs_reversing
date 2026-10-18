// vrtitle: VR revision copy of overlays/rank/chara/pocket/entry.c
// (no C twin in the main tree, rank overlay asm: rank_800D2218 area), VR revision adapted from the asm
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "game/game.h"
#include "overlays/vrtitle/vrpocket.h"

#define POCKET_OBJ_BACKGROUND 0x81

PocketObj *vrtitle_800C3A5C( int id );

void *vrtitle_800C3B58( void )
{
    return &vrtitle_800C3A5C( POCKET_OBJ_BACKGROUND )->count;
}

void *vrtitle_800C3B78( void )
{
    return &vrtitle_800C3A5C( POCKET_OBJ_BACKGROUND )->entries;
}

void vrtitle_800C3B98( void )
{
    PocketObj *obj;

    obj = vrtitle_800C3A5C( POCKET_OBJ_BACKGROUND );
    obj->field_14.word = 0;
    obj->field_E = 0;
    obj->field_C = 0;
    obj->value = 0;
}

// Packs r, g, b into a 0x00BBGGRR color word
unsigned int vrtitle_800C3BC8( unsigned int r, unsigned int g, unsigned int b )
{
    return ( r & 0xFF ) | ( ( g & 0xFF ) << 8 ) | ( ( b & 0xFF ) << 16 );
}

// Vertical gradient of a GT4: rgb0/rgb1 = top, rgb2/rgb3 = bottom
void vrtitle_800C3BE8( POLY_GT4 *prim, unsigned int top, unsigned int bottom )
{
    *(unsigned int *)&prim->r1 = top;
    *(unsigned int *)&prim->r2 = bottom;
    *(unsigned int *)&prim->r3 = bottom;
    // FIXME: word store of r0/g0/b0/code, keeps the existing code byte bit 1 (semi-transparency)
    *(unsigned int *)&prim->r0 = top | ( ( ( prim->code & 2 ) | 0x3C ) << 24 );
}
