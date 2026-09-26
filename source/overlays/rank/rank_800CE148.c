#include "libgv/libgv.h"
#include "game/game.h"
#include "rank.h"

int rank_800CE148(GV_PAD *pPad, int *pOut, SELECT_INFO *info)
{
    int status;
    int press;

    status = pPad->status;
    if (info->max_num >= 2)
    {
        if (status & PAD_LEFT)
        {
            if (info->current_index != 0)
            {
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                info->current_index = 0;
            }
        }
        else if ((status & PAD_RIGHT) && info->current_index == 0)
        {
            GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
            info->current_index = 1;
        }
    }

    press = pPad->press;
    if (press & PAD_CIRCLE)
    {
        *pOut = info->menu[info->current_index].field_20;
        GM_SeSet2(0, 0x3F, SE_MENU_SELECT);
        return 1;
    }

    if (press & PAD_CROSS)
    {
        GM_SeSet2(0, 0x3F, SE_MENU_EXIT);
        *pOut = info->field_E;
        return 1;
    }

    return 0;
}
