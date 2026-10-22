// vrsave: VR revision copy of overlays/rank/menu/pocket.c
// (rank_800CE148), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "game/game.h"
#include "libgcl/libgcl.h"
#include "overlays/vrsave/vrsave.h"

int vrsave_800C8820( GV_PAD *pad, int *res, VR_SELECT_INFO *info )
{
    u_short status;

    status = pad->status;
    if ( info->max_num > 1 )
    {
        if ( status & PAD_LEFT )
        {
            if ( info->current != 0 )
            {
                GM_SeSet2( 0, 63, SE_MENU_CURSOR );
                info->current = 0;
            }
        }
        else if ( status & PAD_RIGHT )
        {
            if ( info->current == 0 )
            {
                GM_SeSet2( 0, 63, SE_MENU_CURSOR );
                info->current = 1;
            }
        }
    }

    if ( pad->press & PAD_CIRCLE )
    {
        *res = info->menu[ info->current ].num;
        GM_SeSet2( 0, 63, SE_MENU_SELECT );
        return 1;
    }

    if ( pad->press & PAD_CROSS )
    {
        GM_SeSet2( 0, 63, SE_MENU_EXIT );
        *res = info->field_E;
        return 1;
    }

    return 0;
}
