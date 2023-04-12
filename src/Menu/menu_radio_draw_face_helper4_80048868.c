#include "menuman.h"
#include "libdg/libdg.h"

void menu_radio_draw_face_helper4_80048868(MenuPrim *prim, menu_chara_struct_sub *a2, int idx)
{
    LINE_F4 *line_f4;
    short    coord;

    if (a2->field_4 < 5)
    {
        coord = a2->field_4 * 14;
    }
    else
    {
        coord = 54;
    }

    _NEW_PRIM(line_f4, prim);

    LSTORE(0x1a1f13, &line_f4->r0);

    if (idx == 0)
    {
        line_f4->x0 = 83 - coord;
        line_f4->x3 = 83 - coord;
        line_f4->y0 = 30;
        line_f4->y1 = 30;
        coord = 78 - coord;
        line_f4->x1 = coord;
        line_f4->x2 = coord;
        line_f4->y2 = 118;
        line_f4->y3 = 118;
    }
    else
    {
        line_f4->x0 = coord + 236;
        line_f4->x3 = coord + 236;
        line_f4->y0 = 30;
        line_f4->y1 = 30;
        coord = coord + 241;
        line_f4->x1 = coord;
        line_f4->x2 = coord;
        line_f4->y2 = 118;
        line_f4->y3 = 118;
    }

    setLineF4(line_f4);
    addPrim(prim->mPrimBuf.mOt, line_f4);
}
