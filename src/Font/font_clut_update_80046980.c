#include "kcb.h"

extern void LoadImage_8008FB10(RECT *, unsigned char *);

void font_clut_update_80046980(KCB* kcb)
{
    LoadImage_8008FB10(&kcb->font_clut_rect, kcb->font_clut_buffer);
}