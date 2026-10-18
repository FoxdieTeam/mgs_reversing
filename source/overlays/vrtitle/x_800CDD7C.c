// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C5F20), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "menu/menuman.h"
#include "menu/radio.h"
#include "memcard/memcard.h"
#include "font/font.h"

extern DATA_INFO *vrtitle_dword_800D9D30;
extern int        vrtitle_dword_800D9D60;

void vrtitle_800CDD7C(SELECT_INFO *info)
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
    vrtitle_dword_800D9D60 = 0;
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
        if (i == 4)
        {
            x = 128;
            y = val2;
        }

        name = info->menu[i + top].mes;
        if (name[0] != '\0')
        {
            vrtitle_dword_800D9D30->make_menu(mes, name);
            font_draw_string(kcb, x, y, mes, 2);
        }
    }

    font_draw_string(kcb, 0, 0, info->message, 0);
    font_update(kcb);
}
