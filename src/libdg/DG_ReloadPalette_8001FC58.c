#include "linker.h"
#include "psyq.h"
#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

extern short word_800AB3A8; // x
short SECTION(".sdata") word_800AB3A8;

extern short word_800AB3AA; // y
short SECTION(".sdata") word_800AB3AA;

extern RECT rect_800AB3B0;

void DG_ReloadPalette_8001FC58(void)
{
    MoveImage_8008FBD0(&rect_800AB3B0, word_800AB3A8, word_800AB3AA);
}
