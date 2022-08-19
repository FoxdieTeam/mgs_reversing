#include "psyq.h"

extern RECT rect_800AB6C8;

void sub_80046B74(void *a1, short a2)
{
    RECT v3;

    v3 = rect_800AB6C8;
    v3.h = 1;
    v3.y += a2;

    LoadImage_8008FB10(&v3, a1);
}
