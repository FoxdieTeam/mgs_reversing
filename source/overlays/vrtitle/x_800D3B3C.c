// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800CBCC8), transplanted from the main-tree twin; offsets/constants adapted to the VR.
// Note that there are two "camera.c" actors,
// this is probably not the enemy/camera.c actor.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libpress.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libfs/libfs.h"
#include "menu/menuman.h"
#include "menu/radio.h"
#include "memcard/memcard.h"
#include "game/game.h"
#include "mts/mts.h"
#include "mts/taskid.h"
#include "overlays/camera/unknown/camera.h"

extern char                       *MGS_MemoryCardName; /* in main.c */

extern void vrtitle_800D06C0(Work *work, int x, int y, int w, int h, int color, int unused);

void vrtitle_800D3B3C(Work *work)
{
    GV_PAD   *pad   = work->pad;
    int       state = work->field_49BC;
    u_short   press = pad->press;

    switch (state)
    {
    case 0:
        if (press & PAD_RIGHT)
        {
            work->field_49BC = 1;
            vrtitle_800D06C0(work, 0x30, 0x5A, 0x26, 0xC, 0xFF, 0);
            GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
            break;
        }
        if (press & PAD_CIRCLE)
        {
            work->field_49B8 = 2;
            work->field_4938 = 0;
            vrtitle_800D0510(work);
            GM_SeSet2(0, 0x3F, 0xB1);
            break;
        }
        if (press & PAD_CROSS)
        {
            work->field_49B8 = 3;
            work->field_4938 = 0;
            vrtitle_800D0510(work);
            GM_SeSet2(0, 0x3F, SE_MENU_EXIT);
        }
        break;
    case 1:
        if (press & PAD_LEFT)
        {
            work->field_49BC = 0;
            vrtitle_800D06C0(work, 3, 0x5A, 0x1A, 0xC, 0xFF, 0);
            GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
            break;
        }
        if (press & PAD_CIRCLE)
        {
            work->field_49B8 = 3;
            work->field_4938 = 0;
            vrtitle_800D0510(work);
            GM_SeSet2(0, 0x3F, SE_MENU_EXIT);
            break;
        }
        if (press & PAD_CROSS)
        {
            work->field_49B8 = 3;
            work->field_4938 = 0;
            vrtitle_800D0510(work);
            GM_SeSet2(0, 0x3F, SE_MENU_EXIT);
        }
        break;
    }
}
