// vrsave: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C6CCC), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "game/game.h"
#include "libgcl/libgcl.h"
#include "memcard/memcard.h"
#include "overlays/vrsave/vrsave.h"

extern DATA_INFO *vrsave_dword_800D1BEC;
extern int        vrsave_dword_800C15D4;
extern int        vrsave_dword_800C15DC;

void vrsave_800C7ECC(VR_SELECT_INFO *info, int dir);

int vrsave_800C8224(GV_PAD *pPad, int *pOut, VR_SELECT_INFO *info)
{
    int newDir;
    int field_20;
    int press;
    int status;

    if (vrsave_dword_800C15DC != 0)
    {
        vrsave_dword_800C15DC = 0;
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
                        vrsave_800C7ECC(info, newDir);
                        info->move_dir_delay = 2;
                    }
                }
                else
                {
                    vrsave_800C7ECC(info, newDir);
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
        if (vrsave_dword_800D1BEC->field_0[0] == 0x56)
        {
            if (field_20 < 16)
            {
                vrsave_dword_800C15D4 = info->current;
            }
            else
            {
                vrsave_dword_800C15D4 = -1;
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

