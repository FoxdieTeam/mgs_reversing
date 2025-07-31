#include "libdg.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "common.h"

STATIC RECT palette1 = { 768, 226, 256, 30 };
STATIC RECT palette2 = { 768, 196, 256, 30 };

void DG_StorePalette(void)
{
    MoveImage(&palette1, palette2.x, palette2.y);
}

void DG_ReloadPalette(void)
{
    MoveImage(&palette2, palette1.x, palette1.y);
}

