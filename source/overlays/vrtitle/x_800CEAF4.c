// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C6CCC, camera_800C6E78, camera_800C703C), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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
extern DATA_INFO                  *vrtitle_dword_800D9D30;
extern int                         vrtitle_dword_800C1704;
extern int                         vrtitle_dword_800C170C;

extern int vrtitle_dword_800C1B5C;
extern const char *vrtitle_dword_800C1B9C[];
extern int vrtitle_dword_800C1708;
extern const int vrtitle_dword_800D9780[];

int vrtitle_800CEAF4(GV_PAD *pPad, int *pOut, SELECT_INFO *info)
{
    int newDir;
    int field_20;
    int press;
    int status;

    if (vrtitle_dword_800C170C != 0)
    {
        vrtitle_dword_800C170C = 0;
        pPad->press |= PAD_CIRCLE;
    }
    else
    {
        status = pPad->status;
        if (info->max_num != 0)
        {
            if (status & (PAD_DOWN | PAD_UP))
            {
                newDir = 1;
                if (status & PAD_UP)
                {
                    newDir = -1;
                }
                if (info->move_dir == newDir)
                {
                    if (--info->move_dir_delay < 0)
                    {
                        vrtitle_800CE764(info, newDir);
                        info->move_dir_delay = 2;
                    }
                }
                else
                {
                    vrtitle_800CE764(info, newDir);
                    info->move_dir_delay = 10;
                    info->move_dir = newDir;
                }
            }
            else
            {
                info->move_dir = 0;
            }
        }
    }

    press = pPad->press;
    if (press & PAD_CIRCLE)
    {
        GM_SeSet2(0, 0x3F, SE_MENU_SELECT);
        if (info->max_num == 0)
        {
            *pOut = -1;
            return 1;
        }
        field_20 = info->menu[info->current].num;
        *pOut = field_20;
        if (vrtitle_dword_800D9D30->field_0[0] == 71)
        {
            if (field_20 < 16)
            {
                vrtitle_dword_800C1704 = info->current;
            }
            else
            {
                vrtitle_dword_800C1704 = -1;
            }
        }
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

void vrtitle_800CECA0(MenuWork *work, char *param_2, SELECT_INFO *info)
{
    MENU_CURPOS *infoChild;
    int                  idx, idx_copy;
    int                  memoryCardNo;
    int                  bit;
    int                  minusOne;

    infoChild = info->menu;
    idx = -1;
    for (memoryCardNo = 0; memoryCardNo < 2; memoryCardNo++)
    {
        int *new_var;
        new_var = &vrtitle_dword_800C1B5C;
        bit = 1;
        bit <<= memoryCardNo;

        if (*new_var & bit)
        {
            strcpy(infoChild->mes, vrtitle_dword_800C1B9C[memoryCardNo]);
            infoChild->num = memoryCardNo;
            if (memoryCardNo == vrtitle_dword_800C1708)
            {
                idx = infoChild - info->menu;
            }
            infoChild++;
        }
    }

    idx_copy = idx;
    if (infoChild == info->menu)
    {
        memcpy(&info->menu[0].mes, vrtitle_dword_800D9780, 8);
        infoChild->num = 2;
        infoChild = &info->menu[1];
    }

    info->kcb = work->field_214_font;
    info->max_num = infoChild - info->menu;

    if (idx_copy < 0)
    {
        idx_copy = 0;
    }

    minusOne = -1;
    do {} while (0);

    info->xofs = 160;
    info->yofs = 100;
    info->current = idx_copy;
    info->top = 0;
    info->message = param_2;
    info->field_E = minusOne;
    info->width = 128;
    info->field_18 = minusOne;
    info->open_count = 4;
    info->height = 128;
    info->enable = 1;
    info->move_dir = 0;
}

void vrtitle_800CEE64(MenuWork *work, const char **srcs, int cnt, int field_4, const char *field_20,
                     SELECT_INFO *info)
{
    KCB                 *kcb;
    const char          *src;
    int                  i;
    MENU_CURPOS *dest;

    dest = info->menu;
    for (i = 0; i < cnt; i++, dest++)
    {
        src = srcs[i];
        strcpy(dest->mes, src);
        dest->num = i;
    }

    kcb = work->field_214_font;

    info->max_num = dest - info->menu;
    info->current = field_4;
    info->top = 0;
    info->message = field_20;
    info->field_E = 1;
    info->xofs = 160;
    info->move_dir = 0;
    info->enable = 1;
    info->yofs = 128;
    info->width = 64;
    info->height = 32;
    // info->field_16 = 4;
    info->kcb = kcb;
}
