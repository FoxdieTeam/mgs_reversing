#include "menuman.h"
#include "psyq.h"

extern int GV_Clock_800AB920;

void menu_radio_draw_face_helper3_800487DC(menu_chara_struct *pStru, int x)
{
    RECT rect;

    menu_radio_load_palette_80046B74(pStru->field_24_pImgData256, x);
    rect.x = x * 32 + 960;
    rect.y = 336;
    rect.w = 26;
    rect.h = 89;

    // TODO: the following code loads
    // an image from a random area of the memory.
    // It looks like this is a trick to quickly get
    // a pseudorandom noise. But, maybe this match is not correct
    // and 0x80010000 should not be hardcoded.
    LoadImage_8008FB10(&rect,
                       (unsigned char *)(0x80010000 + (rand_8008E6B8() % 32) * 0x2000 + GV_Clock_800AB920 * 0x1000));
}
