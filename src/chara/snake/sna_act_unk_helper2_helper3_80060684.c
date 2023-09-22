#include "sna_init.h"

int sna_act_unk_helper2_helper3_80060684(SnaAutoMove *pAutoMove, SVECTOR *param_2)
{
    SVECTOR vec;
    SVECTOR vec2;

    vec = *param_2;
    vec.vy = pAutoMove->field_18_vec2.vy;

    GV_SubVec3_80016D40(&pAutoMove->field_18_vec2, &vec, &vec2);
    return GV_LengthVec3_80016D80(&vec2);
}
