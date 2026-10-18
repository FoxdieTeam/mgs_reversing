// vrtitle: VR revision copy of menu/datasave.c
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

extern char *MGS_MemoryCardName; /* in main.c */

void vrtitle_800CEF74(MenuPrim *pGlue, SELECT_INFO *info);

void vrtitle_800CEF74(MenuPrim *pGlue, SELECT_INFO *info)
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
                vrtitle_800CD95C(textConfig.xpos, ypos, info->height, 12, 2);
            }
        }
        else
        {
            textConfig.color = 0x663d482e;
        }
        _menu_number_draw_string2(pGlue, &textConfig, info->menu[i].mes);
    }
}
