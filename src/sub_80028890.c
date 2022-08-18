#include <SYS/TYPES.H>
#include <LIBGTE.H>

#define SCRPAD_ADDR 0x1F800000

void sub_80028890(SVECTOR *pVec)
{
    SVECTOR *vec = (SVECTOR *)(SCRPAD_ADDR + 0x54);

    pVec->vx = vec->vx;
    pVec->vy = vec->vz;
    pVec->vz = vec->vy;
}
