#include "Menu/menuman.h"
#include "psyq.h"

void sub_80046B10(face_anim_image *image, int idx)
{
    RECT rect;

    rect.x = idx * 32 + 960 + image->field_0_xpos / 2;
    rect.y = image->field_1_ypos + 336;
    rect.w = image->field_2_width / 2;
    rect.h = image->field_3_height;

    LoadImage(&rect, (u_long *)image->field_4_image);
}
