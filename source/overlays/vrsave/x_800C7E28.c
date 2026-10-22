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

extern char *MGS_MemoryCardName; /* in main.c */

void vrsave_800C7E28(char *param_1, char *param_2)
{
    strcpy(param_1, param_2 + 0xc);
}
