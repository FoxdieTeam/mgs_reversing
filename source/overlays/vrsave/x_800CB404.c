// vrsave: savemngr actor, pad input of the menu.
#include <stdio.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "overlays/vrsave/vrsave.h"

#define VR_SAVEMNGR_ITEM_COUNT 4

#define SAVEMNGR_ITEM_SELECTABLE 0x40000000
#define SAVEMNGR_ITEM_REPLAY     0x00800000
#define SAVEMNGR_ITEM_HIDDEN     0x20000000
#define SAVEMNGR_ITEM_LONG_SE    0x00100000

extern VR_SAVEMNGR_ITEM vrsave_dword_800C12CC[];
extern char             vrsave_dword_800D1624[]; // = "***************** into replay save mode ! ******************\n"
extern DATA_INFO        vrsave_dword_800C1B1C;

void vrsave_800CA3A8(DATA_INFO *info, int mission, short score);

int vrsave_800CB404(VR_SAVEMNGR_WORK *work)
{
    GV_PAD           *pad;
    VR_SAVEMNGR_ITEM *item;
    VR_SAVEMNGR_ITEM *items;
    unsigned int      status;
    int               dir;
    int               code;
    int               i;
    int               j;

    pad = &GV_PadData[2];
    status = pad->status;
    dir = status & (PAD_UP | PAD_DOWN | PAD_LEFT | PAD_RIGHT);
    if (dir == work->repeat_dir)
    {
        if (work->repeat_delay-- > 0)
        {
            status &= 0xFFF;
        }
        else
        {
            work->repeat_delay = 1;
        }
    }
    else
    {
        work->repeat_dir = dir;
        work->repeat_delay = 10;
    }

    if (status & (PAD_UP | PAD_DOWN | PAD_LEFT | PAD_RIGHT))
    {
        code = 1;
        if (!(status & PAD_LEFT))
        {
            code = 2;
            if (!(status & PAD_DOWN))
            {
                code = 0;
                if (status & PAD_RIGHT)
                {
                    code = 3;
                }
            }
        }

        if ((short)vrsave_dword_800C12CC[0].link[code + work->cur_item * 35] != -1)
        {
            work->next_item = vrsave_dword_800C12CC[0].link[code + work->cur_item * 35];
            work->field_2DC = 3;
            GM_SeSet2(0, 0x3F, 0x1F);
            return 0;
        }
    }

    status = pad->press;
    if (status & PAD_CIRCLE)
    {
        items = vrsave_dword_800C12CC;
        item = &items[work->cur_item];
        if (item->flags & SAVEMNGR_ITEM_SELECTABLE)
        {
            if (item->flags & SAVEMNGR_ITEM_REPLAY)
            {
                if (!((work->flags >> 2) & 1))
                {
                    if (work->field_318 == 0)
                    {
                        return 0;
                    }
                    GCL_ExecProc(work->field_318, NULL);
                    work->state = 4;
                    work->timer = 0;
                    GM_GameStatus |= STATE_PADRELEASE;
                    return 0;
                }

                printf(vrsave_dword_800D1624);
                vrsave_800CA3A8(&vrsave_dword_800C1B1C, work->mission, work->score);
                item = items;
                // FIXME: the loop counters are shared with 'code' / 'j' to steer register allocation
                code = VR_SAVEMNGR_ITEM_COUNT;
                do
                {
                    code--;
                    item->state = 5;
                    item->step = 0;
                    item++;
                } while (code != 0);
                work->state = 3;
            }
            else if (item->proc != 0)
            {
                item = items;
                for (j = VR_SAVEMNGR_ITEM_COUNT; j != 0; j--, item++)
                {
                    if (item->flags & SAVEMNGR_ITEM_HIDDEN)
                    {
                        item->state = 8;
                    }
                    else
                    {
                        item->state = 5;
                    }
                }
                work->state = 1;
                vrsave_dword_800C12CC[work->cur_item].state = 0;
                if (vrsave_dword_800C12CC[work->cur_item].flags & SAVEMNGR_ITEM_LONG_SE)
                {
                    GM_SeSet2(0, 0x3F, 0x21);
                }
                else
                {
                    GM_SeSet2(0, 0x3F, 0x66);
                }
                GM_SetSound(0x01FFFF06, 0);
            }
        }
    }
    return 0;
}
