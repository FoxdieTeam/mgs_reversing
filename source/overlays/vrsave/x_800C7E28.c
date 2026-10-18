// vrsave: VR revision copy of menu/datasave.c
// (menu_radio_do_file_mode_helper12_helper_8004B8FC), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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

void vrsave_800C7E28(char *param_1, char *param_2)
{
    strcpy(param_1, param_2 + 0xc);
}
