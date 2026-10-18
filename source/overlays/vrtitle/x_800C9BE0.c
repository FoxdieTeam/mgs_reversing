// vrtitle: VR revision copy of overlays/rank/chara/pocket/pkt_back.c
// (rank_800CF160, rank_800CF1D4), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "game/game.h"
#include "libgcl/libgcl.h"
#include "overlays/vrtitle/vrpocket.h"

extern PocketObj *vrtitle_dword_800D9D00;

void vrtitle_800C9BE0( PocketBackWork *work )
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
            for ( iter = vrtitle_dword_800D9D00; iter; iter = iter->next )
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

void vrtitle_800C9C54( PocketObj *obj )
{
    obj->enabled = 0;
    obj->value = 0;
    obj->field_E = 0;
    obj->field_C = 0;
    obj->field_18 = 0;
    obj->field_14.word = 0;
    obj->flags = 0;
}
