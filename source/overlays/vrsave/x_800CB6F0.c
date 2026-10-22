// vrsave: savemngr actor update function.
#include <stdio.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "overlays/vrsave/vrsave.h"

#define VR_SAVEMNGR_ITEM_COUNT 4

enum
{
    SAVEMNGR_STATE_IDLE = 0,
    SAVEMNGR_STATE_CHOSEN = 1,
    SAVEMNGR_STATE_EXEC = 2,
    SAVEMNGR_STATE_REPLAY = 3,
    SAVEMNGR_STATE_WAIT = 4,
    SAVEMNGR_STATE_EXIT = 5,
};

extern VR_SAVEMNGR_ITEM vrsave_dword_800C12CC[];
extern char             vrsave_dword_800D1664[]; // = "into replay save mode \n";

void vrsave_800C4E44(VR_SAVEMNGR_ITEM *item);
void vrsave_800C4E74(VR_SAVEMNGR_ITEM *item);
int  vrsave_800CA404(GV_PAD *pad);
void vrsave_800CA42C(void);
void vrsave_800CABFC(VR_SAVEMNGR_WORK *work);
void vrsave_800CAE98(VR_SAVEMNGR_WORK *work);
void vrsave_800CB118(VR_SAVEMNGR_WORK *work);
int  vrsave_800CB404();
int  vrsave_800CB6E0();

void vrsave_800CB6F0(VR_SAVEMNGR_WORK *work)
{
    int               i0;
    int               i1;
    int               i2;
    int               i3;
    int               i4;
    int               i5;
    VR_SAVEMNGR_ITEM *item;
    int               busy;
    int               a;

    vrsave_800CB118(work);

    switch (work->state)
    {
    case SAVEMNGR_STATE_IDLE:
        item = vrsave_dword_800C12CC;
        i0 = VR_SAVEMNGR_ITEM_COUNT;
        work->cur_item = work->next_item;
        do
        {
            vrsave_800C4E74(item);
            item++;
        } while (--i0 != 0);
        vrsave_800CABFC(work);
        vrsave_800CB404(work);
        break;

    case SAVEMNGR_STATE_REPLAY:
        item = vrsave_dword_800C12CC;
        i1 = VR_SAVEMNGR_ITEM_COUNT;
        do
        {
            vrsave_800C4E74(item);
            item++;
        } while (--i1 != 0);
        if (vrsave_800CA404(&GV_PadData[2]) != 0)
        {
            item = vrsave_dword_800C12CC;
            vrsave_800CA42C();
            i2 = VR_SAVEMNGR_ITEM_COUNT;
            printf(vrsave_dword_800D1664);
            for (; i2 != 0; i2--, item++)
            {
                if (item->flags & 0x20000000)
                {
                    item->state = 8;
                }
                else
                {
                    item->state = 3;
                }
                item->step = 0;
            }
            work->rect.x = 160;
            work->state = SAVEMNGR_STATE_IDLE;
            work->rect.y = 112;
            work->rect.w = 0;
            work->rect.h = 0;
        }
        break;

    case SAVEMNGR_STATE_CHOSEN:
    case SAVEMNGR_STATE_EXEC:
        busy = 0;
        item = vrsave_dword_800C12CC;
        i3 = VR_SAVEMNGR_ITEM_COUNT;
        do
        {
            vrsave_800C4E74(item);
            if (item != &vrsave_dword_800C12CC[work->cur_item])
            {
                a = 0;
                if (item->state != 8)
                {
                    a = item->state > 0;
                }
                busy |= a;
            }
            item++;
        } while (--i3 != 0);
        if (busy == 0 && work->state == SAVEMNGR_STATE_CHOSEN)
        {
            vrsave_800C4E44(&vrsave_dword_800C12CC[work->cur_item]);
            work->state = SAVEMNGR_STATE_EXEC;
        }
        vrsave_800CABFC(work);
        break;

    case SAVEMNGR_STATE_WAIT:
        work->timer++;
        if (work->timer == 10)
        {
            work->state = SAVEMNGR_STATE_EXIT;
            work->timer = 0;
        }
        item = vrsave_dword_800C12CC;
        i4 = VR_SAVEMNGR_ITEM_COUNT;
        do
        {
            vrsave_800C4E74(item);
            item++;
        } while (--i4 != 0);
        break;

    case SAVEMNGR_STATE_EXIT:
        GM_GameStatus &= ~STATE_PADRELEASE;
        item = vrsave_dword_800C12CC;
        i5 = VR_SAVEMNGR_ITEM_COUNT;
        do
        {
            vrsave_800C4E74(item);
            item++;
        } while (--i5 != 0);
        if (vrsave_800CB6E0(work) != 0)
        {
            work->state = SAVEMNGR_STATE_IDLE;
            work->timer = 0;
        }
        break;
    }

    if (work->state != SAVEMNGR_STATE_REPLAY)
    {
        vrsave_800CAE98(work);
    }
}
