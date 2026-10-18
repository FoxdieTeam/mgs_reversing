// vrsave: VR revision copy of takabe/ed_telop.c
// (EdTelopDie_800C54D4), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "takabe/ed_telop.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "menu/menuman.h"
#include "takabe/thing.h"

typedef struct _Work
{
    GV_ACT actor;
    int    f20;
    int    f24;
    int    f28;
    int    proc; /* 0x2C: smaller than the main-tree ed_telop Work */
} Work;

typedef struct _EdTelopPrims
{
    DR_TPAGE tpage[2];
    SPRT     sprt[2];
} EdTelopPrims;

void vrsave_800C4E44(Work* work)
{
    if (work->proc != 0)
    {
        GCL_ExecProc(work->proc, NULL);
    }
}
