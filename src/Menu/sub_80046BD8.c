#include "psyq.h"

extern RECT rect_800AB6C8;
RECT        rect_800AB6C8;

extern RECT rect_800AB6D0;
RECT        rect_800AB6D0;

void sub_80046BD8(int off)
{
    RECT rect;

    rect = rect_800AB6C8;
    rect.y += off;
    rect.h = 1;
    MoveImage(&rect, rect.x, (rect.y * 65536) / 65536 + 2);

    rect.x = off * 32 + 960;
    rect.y = 336;
    rect.w = 32;
    rect.h = 96;
    MoveImage(&rect, rect_800AB6D0.x + off * 32, rect_800AB6D0.y);
}
