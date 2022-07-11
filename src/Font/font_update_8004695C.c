#include "kcb.h"

extern void LoadImage_8008FB10(RECT *, unsigned char *);

void font_update_8004695C(KCB* kcb)
{
    LoadImage_8008FB10(&kcb->font_rect, kcb->font_buffer);
}