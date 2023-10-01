#include "linker.h"
#include "psyq.h"
#include "libdg.h"

extern RECT rect_800AB3A8;
RECT SECTION(".sdata") rect_800AB3A8;

extern RECT rect_800AB3B0;
RECT SECTION(".sdata") rect_800AB3B0;

void DG_StorePalette_8001FC28(void) // different in VR
{
#ifndef VR_EXE
    MoveImage(&rect_800AB3A8, rect_800AB3B0.x, rect_800AB3B0.y);
#else
    TEMPORARY_VR_MATCHING_PLACEHOLDER(0, 0, 0, 9);
#endif
}

void DG_ReloadPalette_8001FC58(void) // different in VR
{
#ifndef VR_EXE
    MoveImage(&rect_800AB3B0, rect_800AB3A8.x, rect_800AB3A8.y);
#else
    TEMPORARY_VR_MATCHING_PLACEHOLDER(0, 0, 0, 9);
#endif
}

