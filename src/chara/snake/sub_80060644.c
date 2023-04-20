#include "sna_init.h"

extern int     dword_800AB9F0;
extern SVECTOR svector_800ABA10;

void sub_80060644(SnaAutoMove *pAutoMove)
{
    pAutoMove->field_0_ivec.vy = dword_800AB9F0;
    pAutoMove->field_18_vec2 = svector_800ABA10;
}
