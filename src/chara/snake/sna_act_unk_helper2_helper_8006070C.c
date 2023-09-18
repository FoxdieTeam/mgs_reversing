#include "sna_init.h"

int sna_unk_helper2_helper_8006070C(SnaAutoMove *pAutoMove, CONTROL *pControl)
{
    SVECTOR vec;
    SVECTOR *pPosition;
    HZD_HDL *pHzd;
    int x, y, z;
    int reach;
    int zon;
    HZD_ZON *pZon;

    pPosition = &pControl->field_0_mov;
    pHzd = pControl->field_2C_map->field_8_hzd;

    x = pAutoMove->field_0_ivec.vx;
    z = pAutoMove->field_0_ivec.vz;
    y = pAutoMove->field_0_ivec.vy;

    reach = HZD_ReachTo_8005C89C(pHzd, x, pAutoMove->field_0_ivec.pad);

    if ((y != z) || (reach <= 0))
    {
        pAutoMove->field_0_ivec.vz = y;

        if (HZD_ReachTo_8005C89C(pHzd, x, y) < 2)
        {
            pAutoMove->field_10_vec1 = pAutoMove->field_18_vec2;
            pAutoMove->field_0_ivec.pad = y;

            GV_SubVec3_80016D40(&pAutoMove->field_18_vec2, pPosition, &vec);
            pControl->field_4C_turn_vec.vy = GV_VecDir2_80016EF8(&vec);
            return -1;
        }

        zon = sna_act_unk_helper2_helper_helper_8005C974(pHzd, x, y, pControl);
        pZon = &pHzd->f00_header->navmeshes[zon];

        pAutoMove->field_10_vec1.vx = pZon->x;
        pAutoMove->field_10_vec1.vy = pZon->y;
        pAutoMove->field_10_vec1.vz = pZon->z;

        pAutoMove->field_0_ivec.pad = (char)zon | ((char)zon << 8);
    }

    GV_SubVec3_80016D40(&pAutoMove->field_10_vec1, pPosition, &vec);
    pControl->field_4C_turn_vec.vy = GV_VecDir2_80016EF8(&vec);
    return 0;
}
