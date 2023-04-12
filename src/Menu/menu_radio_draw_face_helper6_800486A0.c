#include "Game/jimctrl.h"
#include "menuman.h"

void menu_radio_draw_face_helper6_800486A0( menu_chara_struct_sub *a1, int idx )
{
    int v1, v2, result;

    result = jimctrl_helper_80037F68( a1->field_2_chara );

    v2 = result >> 8;
    v1 = a1->field_E == 0;
    if ( v1 && v2 )
    {
        a1->field_E = 1;
    }
    v1 = (char)result;
    a1->field_4C_leftCodecPortraitFrame = v1;
}
