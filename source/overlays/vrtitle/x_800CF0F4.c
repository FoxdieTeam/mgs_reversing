#include <stdio.h>
#include "mts/mts.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "menu/radio.h"
#include "menu/menuman.h"

/*---------------------------------------------------------------------------*/

typedef struct _Work {
    GV_ACT    actor;
    KCB       kcb;
    int       proc_id;
    int       field_50;
    MenuPrim *prim_ptr;
    MenuPrim  prim;
    char      primbuf[ 2 ][ 0x2000 ];
} Work;

/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/

int vrtitle_800CF0F4( GV_PAD *pad, int *res, SELECT_INFO *info )
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
