#include "kcb.h"

int font_get_buffer_size_80044F38(KCB* kcb)
{
    short val_1 = (kcb->char_arr[2] + 0xc) * kcb->char_arr[0] - kcb->char_arr[2];
    int val_2 = (int)val_1 + 7;
    kcb->short_arr[1] = val_1;
    if (val_2 < 0)
    {
        val_2 = kcb->short_arr[1] + 14;
    }

    kcb->short_arr[0] = ((val_2>>3)<<2);
    kcb->short_arr[2] = (kcb->char_arr[3] + 12) * kcb->char_arr[1] + 2;
    kcb->font_rect.w = kcb->short_arr[0] / 2;
    kcb->font_rect.h = kcb->short_arr[2];

    return kcb->short_arr[0] * kcb->short_arr[2] + 32;
}