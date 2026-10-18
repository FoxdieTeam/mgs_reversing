// vrtitle: VR revision copy of overlays/rank/chara/pocket/entry.c
// (no C twin in the main tree, rank overlay asm: rank_800D21DC), VR revision adapted from the asm
#include "game/game.h"

unsigned int vrtitle_800C3BC8( unsigned int r, unsigned int g, unsigned int b );
void         vrtitle_800C38E0( int task_id, int *msg, int size );

// Gradient color for entry cur of max: grey blue for the first entries, white at the end
int vrtitle_800C3C30( int cur, int max )
{
    int t;

    if ( cur >= max )
    {
        return 0x80C080;
    }

    if ( cur <= 0 )
    {
        return 0;
    }

    t = ( ( cur << 7 ) / max ) & 0xFF;
    return vrtitle_800C3BC8( t, ( ( cur * 0xC0 ) / max ) & 0xFF, t );
}

typedef struct PocketMsgWork
{
    /* 0x0000 */ GV_ACT       actor;
    /* 0x0020 */ char         pad_0020[ 0x19FC ];
    /* 0x1A1C */ int          flags;
    /* 0x1A20 */ char         pad_1A20[ 0x20 ];
    /* 0x1A40 */ int          task_id;
    /* 0x1A44 */ int          arg;
} PocketMsgWork;

void vrtitle_800C3CEC( PocketMsgWork *work )
{
    int msg[ 4 ];
    int mask1, mask2; // FIXME: variable masks stop gcc turning (x & bit) != 0 into a shift

    mask1 = 0x10000000;
    mask2 = 0x20000000;

    msg[ 0 ] = ( work->flags & mask1 ) != 0;
    msg[ 1 ] = ( work->flags & mask2 ) != 0;
    msg[ 2 ] = work->flags & 0xFFF;
    msg[ 3 ] = work->arg;
    vrtitle_800C38E0( work->task_id, msg, 4 );
    GV_DestroyActor( &work->actor );
}
