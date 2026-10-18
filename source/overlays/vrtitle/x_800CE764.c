// vrtitle: VR revision copy of menu/datasave.c
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

//------------------------------------------------------------------------------
// gp
//------------------------------------------------------------------------------

extern char *MGS_MemoryCardName; /* in main.c */

// The small triangle above the files list suggesting that there are more entries.

// The small triangle below the files list suggesting that there are more entries.

//file may be split here

#define setRGB0_Fast(prim, rgbExtra) *(unsigned int *)&prim->r0 = rgbExtra

// See also drawCaption_800C5EB4() in camera.c

#define FONT_SIZE       14

#define SAVE_MES_X      160
#define SAVE_MES_Y      200

// clang-format on

// See also updateCurrentEntry_800C6984() in camera.c

// See also SelectAct_800C32D8() in select.c

/*
pAreaNameForMenu uses MGS custom encoding.
pAreaNameForSaveData uses Shift-JIS encoding.

Example for "Heliport":
MGS      : 80 48 80 65 80 6C 80 69 80 70 80 6F 80 72 80 74
Shift-JIS: 82 67 82 85 82 8C 82 89 82 90 82 8F 82 92 82 94
           Ｈ    ｅ    ｌ    ｉ    ｐ    ｏ    ｒ    ｔ
*/

// Called by data_info->make_title

// Called by data_info->make_menu

// Called by data_info->make_game_data

void vrtitle_800CE764(SELECT_INFO *info, int dir)
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
    vrtitle_800CDD7C(info);
}
