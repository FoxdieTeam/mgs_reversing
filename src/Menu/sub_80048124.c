#include "Menu/menuman.h"
#include "psyq.h"

extern RECT rect_800AB6D8;
RECT        rect_800AB6D8;

extern int dword_800ABB3C;
int        dword_800ABB3C;

void sub_80048124()
{
    PANEL_TEXTURE pPanelTex;
    RECT          rect;

    menu_init_rpk_item_8003DDCC(&pPanelTex, 43, 42);
    LoadImage(&rect_800AB6D8, pPanelTex.field_0_pixels);

    rect = rect_800AB6D8;
    rect.w = 16;
    rect.h = 1;
    rect.y += rect_800AB6D8.h;

    LoadImage(&rect, pPanelTex.field_4_word_ptr_pixels);
    dword_800ABB3C = (rect.y << 6) | (rect.x >> 4 & 0x3f);
}
