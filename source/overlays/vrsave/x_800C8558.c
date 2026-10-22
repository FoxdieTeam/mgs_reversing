// vrsave: VR revision copy of menu/datasave.c
// (menu_radio_do_file_mode_helper15_8004C04C),
// transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "menu/menuman.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "menu/radio.h"
#include "memcard/memcard.h"
#include "overlays/vrsave/vrsave.h"


void vrsave_800C8558(MenuWork *work, const char **srcs, int cnt, int index, const char *message, VR_SELECT_INFO *info)
{
    KCB            *kcb;
    const char     *src;
    int             i;
    VR_MENU_CURPOS *dest;

    dest = info->menu;
    for (i = 0; i < cnt; dest++, i++)
    {
        src = srcs[i];
        strcpy(dest->mes, src);
        dest->num = i;
        if (i == 1)
        {
            dest->field_24 = 0x21;
        }
        else
        {
            dest->field_24 = 0x20;
        }
    }

    kcb = work->field_214_font;

    info->max_num = dest - info->menu;
    info->current = index;
    info->top = 0;
    info->message = message;
    info->field_E = 1;
    info->xofs = 160;
    info->move_dir = 0;
    info->enable = 1;
    info->yofs = 128;
    info->width = 64;
    info->height = 32;
    info->kcb = kcb;
}
