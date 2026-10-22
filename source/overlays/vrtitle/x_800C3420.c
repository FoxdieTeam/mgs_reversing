// vrtitle: VR revision copy of overlays/rank/chara/pocket/pkt_back.c
// (rank_800CF160), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "game/game.h"
#include "libgcl/libgcl.h"
#include "overlays/vrtitle/vrpocket.h"

extern PocketObj *vrtitle_dword_800D9CF8;

void vrtitle_800C3420( PocketWork *work )
{
    PocketUpdate *update;
    PocketObj    *iter;
    int           i;

    update = work->updates;
    i = 0;
    if ( work->update_count > 0 )
    {
        do
        {
            for ( iter = vrtitle_dword_800D9CF8; iter; iter = iter->next )
            {
                if ( iter->id == update->id )
                {
                    iter->value = update->value;
                    break;
                }
            }
            update++;
        } while ( work->update_count > ++i );
    }
    work->update_count = 0;
}
