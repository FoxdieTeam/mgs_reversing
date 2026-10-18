// vrtitle: VR revision copy of menu/datasave.c
// (drawCaption_8004AE3C), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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

void vrtitle_800CDD10(MenuWork *menuWork, const char *caption)
{
    int height;
    KCB  *kcb;

    kcb = menuWork->field_214_font;

    height = kcb->height;
    kcb->height = 14;
    font_clear(kcb);
    kcb->height = height;

    font_draw_string(kcb, 0, 0, caption, 0);
    font_update(kcb);
}
