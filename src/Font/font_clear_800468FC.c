#include "kcb.h"

void font_clear_800468FC(KCB* kcb) {
    int* font_buffer;
    unsigned var_v1;

    if ((kcb->char_arr[6] & 0x10) == 0) {
        font_buffer = kcb->font_buffer;
        var_v1 = (unsigned)(kcb->width_info * kcb->height_info) / 4;
        if ((signed)var_v1 > 0) {
            do {
                *font_buffer = 0;
                --var_v1;
                ++font_buffer;
            } while ((signed)var_v1 > 0);
        }
        kcb->char_arr[6] |= 0x10;
    }
}