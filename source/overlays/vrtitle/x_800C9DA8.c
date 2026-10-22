// vrtitle: VR revision copy of overlays/rank/chara/pocket/pkt_back.c
// (rank_800CF328), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "game/game.h"
#include "libgcl/libgcl.h"
#include "overlays/vrtitle/vrpocket.h"

extern PocketObj *vrtitle_dword_800D9D00;

// Finds the pocket object with the given id
PocketObj *vrtitle_800C9DA8( int id )
{
    PocketObj *iter;

    for ( iter = vrtitle_dword_800D9D00; iter; iter = iter->next )
    {
        if ( iter->id == id )
        {
            return iter;
        }
    }

    return 0;
}
