// vrtitle: VR revision copy of overlays/rank/chara/pocket/pkt_back.c
// (rank_800D0B54, rank_800D0BC0 and neighbours), adapted from the asm.
#include "game/game.h"
#include "overlays/vrtitle/vrpocket.h"

PocketObj *vrtitle_800C3928( int id, int count, int kind, int arg3 );

void vrtitle_800C7E74();

int vrtitle_800C9320( void *work )
{
    PocketObj *obj;

    obj = vrtitle_800C3928( 15, 1, 0, 1 );
    if ( obj == NULL )
    {
        return -1;
    }
    obj->update = vrtitle_800C7E74;
    return 0;
}
