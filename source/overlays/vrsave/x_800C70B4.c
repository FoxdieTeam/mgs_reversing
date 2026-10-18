// vrsave: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C5F20), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "menu/menuman.h"
#include "menu/radio.h"
#include "memcard/memcard.h"
#include "font/font.h"
#include "overlays/vrsave/vrsave.h"

extern DATA_INFO *vrsave_dword_800D1BEC;

void vrsave_800C70B4(VR_SELECT_INFO *info)
{
    int   top;
    int   i, y;
    int   count;
    int   x, val2;
    KCB  *kcb;
    char  mes[32];
    char *name;

    kcb = info->kcb;
    x = 0;
    font_clear(kcb);

    val2 = 14;
    y = val2;
    count = info->max_num - info->top;
    if (count > 6)
    {
        count = 6;
    }

    top = info->top;
    for (i = 0; i < count; i++, y += 14)
    {
        if (i == 6) // FIXME: never true (count <= 6); kept because it steers register allocation
        {
            x = 160;
            y = val2;
        }

        name = info->menu[i + top].mes;
        if (name[0] != '\0')
        {
            vrsave_dword_800D1BEC->make_menu(mes, name);
            font_draw_string(kcb, x, y, mes, 0);
        }
    }

    font_draw_string(kcb, 0, 0, info->message, 0);
    font_update(kcb);
}
