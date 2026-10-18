// vrtitle: VR revision copy of overlays/rank/chara/pocket/pkt_back.c
// (rank_800D3A28 die function and neighbours), adapted from the asm.
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "overlays/vrtitle/vrpocket.h"

extern int        vrtitle_dword_800D9CF4;
extern PocketObj *vrtitle_dword_800D9CF8;

void vrtitle_800C2F90( PocketObj *obj );
void vrtitle_800C27D0( PocketList *list, int idx );
void vrtitle_800C2944( PocketList *list, int idx );
void vrtitle_800C2DA0( PocketList *list, int idx, int arg );
void *vrtitle_800C2DF0( PocketListItem *item );

// Die function of the pocket actor
void vrtitle_800C8A74( PocketWork *work )
{
    DG_PRIM *prim;
    int      i;

    if ( vrtitle_dword_800D9CF4 > 0 )
    {
        do
        {
            vrtitle_800C2F90( vrtitle_dword_800D9CF8 );
        } while ( vrtitle_dword_800D9CF4 > 0 );
    }

    prim = work->prim1;
    if ( prim )
    {
        DG_DequeuePrim( prim );
        DG_FreePrim( prim );
    }

    prim = work->prim2;
    if ( prim )
    {
        DG_DequeuePrim( prim );
        DG_FreePrim( prim );
    }

    for ( i = 0; i < work->list.count; i++ )
    {
        GV_FreeMemory( 2, vrtitle_800C2DF0( &work->list.items[ i ] ) );
    }
}
