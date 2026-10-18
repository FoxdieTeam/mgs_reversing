// vrtitle: VR revision copy of onoda/abst/abst.c
// (abst_800C5198), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "game/game.h"
#include "libgcl/libgcl.h"
#include "libfs/libfs.h"
#include "mts/mts.h"

#include <stdio.h>

#include "onoda/abst/abst.h"

/* VR revision: the KCB array sits 0x10 into the owner, unlike abst.c's Work. */
typedef struct VrKcbWork
{
    char pad_00[0x10];
    KCB  kcb[ 1 ];
} VrKcbWork;

// TODO: give these proper names

void vrtitle_800C2DA0(VrKcbWork *work, int index, int col)
{
    font_set_color(&work->kcb[index], 0, col, 0);
    font_clut_update(&work->kcb[index]);
}
