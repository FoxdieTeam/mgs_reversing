// vrsave: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C6A40), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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

extern char *MGS_MemoryCardName; /* in main.c */

extern DATA_INFO *vrsave_dword_800D1BEC;
extern int        vrsave_dword_800D1BE8;
extern int        vrsave_dword_800C15D4;
extern char       vrsave_dword_800C1A40[];
extern char       vrsave_dword_800D13D8[]; // = "FILE %s\n";
extern char       vrsave_dword_800D13AC[]; // = "";

void vrsave_800C7E28(char *dst, char *src);
void vrsave_800C7ECC(VR_SELECT_INFO *info, int dir);

int vrsave_800C7F88(MenuWork *work, MEMCARD *pMemcard, const char *message, VR_SELECT_INFO *info)
{
    VR_MENU_CURPOS *pIter;
    MEMCARD_FILE   *pMcFile;
    int             i;

    pIter = info->menu;

    strcpy(vrsave_dword_800C1A40, MGS_MemoryCardName);
    vrsave_dword_800C1A40[12] = vrsave_dword_800D1BEC->field_0[0];

    for (i = 0; i < pMemcard->file_count; i++)
    {
        pMcFile = &pMemcard->files[i];
        printf(vrsave_dword_800D13D8, pMcFile->name);

        if (strncmp(pMcFile->name, vrsave_dword_800C1A40, 13) == 0)
        {
            vrsave_800C7E28(pIter->mes, pMcFile->name);
            pIter->num = i;
            pIter++;
        }
    }

    if ((vrsave_dword_800D1BE8 == 0 || vrsave_dword_800D1BE8 == 2) &&
        pMemcard->free_blocks >= vrsave_dword_800D1BEC->blocks_count)
    {
        memcpy(pIter->mes, vrsave_dword_800D13AC, 1);
        pIter->num = 16;
        pIter++;
    }

    info->kcb = work->field_214_font;
    info->max_num = pIter - info->menu;

    if (vrsave_dword_800D1BEC->field_0[0] != 'R')
    {
        if (info->max_num && pIter[-1].num == 16)
        {
            info->current = info->max_num - 1;
        }
        else
        {
            info->current = 0;
        }
    }
    else if (vrsave_dword_800C15D4 == -1 || vrsave_dword_800C15D4 >= info->max_num)
    {
        if ((vrsave_dword_800D1BE8 == 0 || vrsave_dword_800D1BE8 == 2) && info->max_num && pIter[-1].num == 16)
        {
            info->current = info->max_num - 1;
        }
        else
        {
            info->current = 0;
        }
    }
    else
    {
        info->current = vrsave_dword_800C15D4;
    }

    info->top = 0;
    info->message = message;
    info->field_E = -1;
    info->xofs = 40;
    info->yofs = 40;
    info->open_count = 8;
    info->move_dir = 0;
    info->field_18 = -1;
    info->height = 240;
    info->enable = 1;
    vrsave_800C7ECC(info, 0);
    return info->max_num != 0;
}
