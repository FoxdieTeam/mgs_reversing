#include "libgv/libgv.h"

SVECTOR * sub_80034834(SVECTOR *arg0, SVECTOR *arg1, SVECTOR arg2)
{
    SVECTOR vec;

    // TODO: this should be able to be matched without casting to unsigned short
    vec.vx = FP_Subtract((unsigned short)arg2.vx, (unsigned short)arg1->vx);
    vec.vy = FP_Subtract((unsigned short)arg2.vy, (unsigned short)arg1->vy);
    vec.vz = FP_Subtract((unsigned short)arg2.vz, (unsigned short)arg1->vz);

    *arg0 = vec;
    return arg0;
}
