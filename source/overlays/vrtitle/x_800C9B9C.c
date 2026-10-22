// vrtitle: VR revision copy of overlays/rank/chara/pocket/entry.c
// (rank_800CF11C), adapted from the asm.
#include "overlays/vrtitle/vrpocket.h"

// Queues an (id, value) update for vrtitle_800C9BE0
void vrtitle_800C9B9C( PocketBackWork *work, short id, short value )
{
    if ( work->update_count != POCKET_UPDATE_MAX2 )
    {
        work->updates[ work->update_count ].id = id;
        work->updates[ work->update_count ].value = value;
        work->update_count++;
    }
}
