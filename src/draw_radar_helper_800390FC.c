#include "menuMan.h"

extern void sub_8003DB2C(struct Menu_Prim_Buffer *prim_buffer, int x0, int y0, int w, int h, unsigned int param_6);

void draw_radar_helper_800390FC(struct Actor_MenuMan *menuMan)
{
    int x1, y1, x2, y2;

    x1 = menuMan->field_1D4_clipX1;
    y1 = menuMan->field_1D6_clipY1;
    x2 = x1 + 0xea;
    y2 = y1 + 0xf;
    sub_8003DB2C(menuMan->field_20_otBuf, x2, y2, 1, 0x35, 0);
    sub_8003DB2C(menuMan->field_20_otBuf, x2, y2, 0x46, 1, 0);
    sub_8003DB2C(menuMan->field_20_otBuf, x1 + 0x130, y2, 1, 0x36, 0);
    sub_8003DB2C(menuMan->field_20_otBuf, x2, y1 + 0x44, 0x46, 1, 0);
}
