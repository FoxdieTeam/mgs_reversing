#include "Menu/menuman.h"
#include "psyq.h"

void sub_80046B10(face_anim_frame *frame, int idx)
{
    RECT rect;

    rect.x = idx * 32 + 960 + frame->field_0_xpos / 2;
    rect.y = frame->field_1_ypos + 336;
    rect.w = frame->field_2_width / 2;
    rect.h = frame->field_3_height;

    LoadImage_8008FB10(&rect, frame->field_4_image);
}
