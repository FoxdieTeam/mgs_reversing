#include "linker.h"
#include "psyq.h"
#include "libdg.h"

RECT rect_800AB3A8 = {768, 226, 256, 30};
RECT rect_800AB3B0 = {768, 196, 256, 30};

void DG_StorePalette_8001FC28()
{
    MoveImage(&rect_800AB3A8, rect_800AB3B0.x, rect_800AB3B0.y);
}

void DG_ReloadPalette_8001FC58()
{
    MoveImage(&rect_800AB3B0, rect_800AB3A8.x, rect_800AB3A8.y);
}

