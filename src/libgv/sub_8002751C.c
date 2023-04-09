#include "libgv.h"

void sub_8002751C(SVECTOR *svec1, SVECTOR *svec2)
{
    SVECTOR *scratchvec1, *scratchvec2;
    int      coord1, coord2, coord1_copy;

    coord1 = svec1->vx;
    coord2 = svec2->vx;
    if (coord2 < coord1)
    {
        coord1_copy = coord1;
        coord1 = coord2;
        coord2 = coord1_copy;
    }
    scratchvec1 = (SVECTOR *)getScratchAddr(0x9);
    scratchvec2 = (SVECTOR *)getScratchAddr(0xB);

    scratchvec1->vx = coord1;
    scratchvec2->vx = coord2;

    coord1 = svec1->vz;
    coord2 = svec2->vz;
    if (coord2 < coord1)
    {
        coord1_copy = coord1;
        coord1 = coord2;
        coord2 = coord1_copy;
    }

    scratchvec1->vy = coord1;
    scratchvec2->vy = coord2;

    coord1 = svec1->vy;
    coord2 = svec2->vy;
    if (coord2 < coord1)
    {
        coord1_copy = coord1;
        coord1 = coord2;
        coord2 = coord1_copy;
    }

    scratchvec1->vz = coord1;
    scratchvec2->vz = coord2;
}
