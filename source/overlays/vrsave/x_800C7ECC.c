// vrsave: VR revision copy of menu/datasave.c
// (updateCurrentEntry_8004B9C4), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "menu/menuman.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "menu/radio.h"
#include "memcard/memcard.h"
#include "mts/mts.h"
#include "mts/taskid.h"

extern char *MGS_MemoryCardName; /* in main.c */

void vrsave_800C7ECC(SELECT_INFO *info, int dir)
{
    short top;
    short newIndex;
    int   previousIndex;

    previousIndex = info->current;
    newIndex = info->current + dir;
    info->current = newIndex;
    if (newIndex < 0)
    {
        info->current = 0;
    }
    else if (newIndex >= info->max_num)
    {
        info->current = info->max_num - 1;
    }
    else
    {
        top = info->top;
        if (newIndex < top)
        {
            info->top = newIndex;
        }
        else if (newIndex >= (top + 6))
        {
            info->top = newIndex - 5;
        }
    }
    if (info->current != previousIndex)
    {
        GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
    }
    vrsave_800C70B4(info);
}
