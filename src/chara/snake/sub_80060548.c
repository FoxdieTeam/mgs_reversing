#include "sna_init.h"

extern SVECTOR DG_ZeroVector_800AB39C;

void sub_80060548(SnaAutoMove *pAutoMove, HZD_HDL *arg1, SVECTOR *arg2)
{
    pAutoMove->field_0_ivec.vx = sub_8005C6C4(arg1, arg2, -1);
    pAutoMove->field_0_ivec.vy = -1;
    pAutoMove->field_0_ivec.vz = -1;
    pAutoMove->field_0_ivec.pad = pAutoMove->field_0_ivec.vx;
    pAutoMove->field_10_vec1 = DG_ZeroVector_800AB39C;
    pAutoMove->field_18_vec2 = DG_ZeroVector_800AB39C;
}
