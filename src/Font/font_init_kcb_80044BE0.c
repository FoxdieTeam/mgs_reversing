#include "kcb.h"

extern void* memset_8008E688(void *pSrc, int value, int len);
extern int font_set_kcb_80044C90(KCB* kcb, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5);

int font_init_kcb_80044BE0(KCB* kcb, RECT* rect_data, short x, short y)
{
    memset_8008E688((char*)kcb, 0, 44);
    kcb->rect_data = rect_data;
    kcb->font_rect = *rect_data;
    kcb->font_clut_rect.w = 16;
    kcb->font_clut_rect.h = 1;
    kcb->font_clut_rect.x = x;
    kcb->font_clut_rect.y = y;
    return font_set_kcb_80044C90(kcb, -1, -1, 0, 0, 4, 0);
}