#include "linker.h"
#include "psyq.h"
#include "libdg.h"

extern RECT rect_800AB3A8;
RECT SECTION(".sdata") rect_800AB3A8;

extern RECT rect_800AB3B0;
RECT SECTION(".sdata") rect_800AB3B0;

void DG_StorePalette_8001FC28(void)
{
    MoveImage_8008FBD0(&rect_800AB3A8, rect_800AB3B0.x, rect_800AB3B0.y);
}

void DG_ReloadPalette_8001FC58(void)
{
    MoveImage_8008FBD0(&rect_800AB3B0, rect_800AB3A8.x, rect_800AB3A8.y);
}

