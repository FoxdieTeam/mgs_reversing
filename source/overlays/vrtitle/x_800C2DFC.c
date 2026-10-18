// vrtitle: VR revision copy of overlays/rank/chara/pocket/entry.c
// (rank_800D19E4), adapted from the asm.
#include "overlays/vrtitle/vrpocket.h"

void vrtitle_800C2DA0( PocketList *list, int idx, int arg );

// Resets all items of the list
void vrtitle_800C2DFC( PocketList *list )
{
    int i;

    for ( i = 0; i < list->count; i++ )
    {
        vrtitle_800C2DA0( list, i, 0 );
    }
}
