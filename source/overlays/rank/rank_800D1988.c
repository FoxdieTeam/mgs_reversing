#include "font/font.h"

typedef struct _Work
{
    char pad_0[0x10];
    KCB  kcb[0];
} Work;

void rank_800D1988(Work *work, int index, int col)
{
    font_set_color(&work->kcb[index], 0, col, 0);
    font_clut_update(&work->kcb[index]);
}
