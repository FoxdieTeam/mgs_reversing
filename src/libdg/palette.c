#include "linker.h"
#include "psyq.h"
#include "libdg.h"

// #define STATIC static
#define STATIC

STATIC RECT rect_800AB3A8 = { 768, 226, 256, 30 };
STATIC RECT rect_800AB3B0 = { 768, 196, 256, 30 };

void DG_StorePalette(void)
{
    MoveImage(&rect_800AB3A8, rect_800AB3B0.x, rect_800AB3B0.y);
}

void DG_ReloadPalette(void)
{
    MoveImage(&rect_800AB3B0, rect_800AB3A8.x, rect_800AB3A8.y);
}

