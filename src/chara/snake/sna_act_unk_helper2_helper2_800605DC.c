#include "sna_init.h"

void sna_act_unk_helper2_helper2_800605DC(SnaAutoMove *autoMove, HZD_HDL *pHzd, SVECTOR *pVec)
{
    autoMove->field_0_ivec.vy = sub_8005C6C4(pHzd, pVec, -1);
    autoMove->field_18_vec2 = *pVec;
    autoMove->field_0_ivec.vz = -1;
}
