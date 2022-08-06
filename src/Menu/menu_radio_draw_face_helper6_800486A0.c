#include "jimctrl.h"

int menu_radio_draw_face_helper6_800486A0(unsigned short *a1)
{
    int new_var;
    int new_var2;
    int result;
    result = jimctrl_helper_80037F68(a1[1]);

    new_var2 = result >> 8;
    new_var = (short)a1[7] == 0;
    if (new_var && new_var2)
    {
        a1[7] = 1;
    }
    new_var = (char)result;
    a1[8] = new_var;
    return new_var;
}
