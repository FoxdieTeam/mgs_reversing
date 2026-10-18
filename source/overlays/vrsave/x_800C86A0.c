// vrsave: VR revision copy of menu/datasave.c
// (menu_radio_do_file_mode_helper16_8004C164), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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

/* VR revision of the SELECT_INFO menu entry: 0x28 bytes instead of 0x24. */
typedef struct VR_MENU_CURPOS
{
    char mes[ 32 ];
    int  num;
    int  field_24;
} VR_MENU_CURPOS;

typedef struct VR_SELECT_INFO
{
    short       xofs;
    short       yofs;
    short       current;
    short       top;
    char        max_num;
    short       move_dir;
    short       move_dir_delay;
    short       field_E;
    short       width;
    short       height;
    short       enable;
    short       open_count;
    short       field_18;
    KCB        *kcb;
    const char *message;
    VR_MENU_CURPOS menu[ 0 ];
} VR_SELECT_INFO;

void vrsave_800C86A0(MenuPrim *pGlue, VR_SELECT_INFO *info);

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

void vrsave_800C86A0(MenuPrim *pGlue, VR_SELECT_INFO *info)
{
    int        i;
    int        xpos, ypos;
    TextConfig textConfig;

    textConfig.flags = 0x12;
    if (info->enable != 0)
    {
        textConfig.color = 0x66748956;
    }
    else
    {
        textConfig.color = 0x663d482e;
    }
    textConfig.xpos = info->xofs;
    textConfig.ypos = info->yofs;
    _menu_number_draw_string2(pGlue, &textConfig, info->message);
    if (info->max_num == 1)
    {
        xpos = info->xofs;
    }
    else
    {
        xpos = info->xofs - info->width / 2;
    }
    for (i = 0; i < info->max_num; i++, xpos += info->width)
    {
        textConfig.xpos = xpos;
        ypos = info->yofs;
        textConfig.ypos = ypos + 12;

        if (i == info->current)
        {
            textConfig.color = 0x66748956;
            if (info->enable != 0)
            {
                ypos += 16;
                vrsave_800C6DF4(textConfig.xpos, ypos, info->height, 12, 2);
            }
        }
        else
        {
            textConfig.color = 0x663d482e;
        }
        _menu_number_draw_string2(pGlue, &textConfig, info->menu[i].mes);
    }
}
