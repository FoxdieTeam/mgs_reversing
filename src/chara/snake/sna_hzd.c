#include "sna_init.h"

//TODO: remove sna_init inclusion as SnaAutoMove isn't coupled with Snake

extern SVECTOR DG_ZeroVector_800AB39C;

extern int     GM_PlayerAddress_800AB9F0;
extern SVECTOR GM_PlayerPosition_800ABA10;

void sub_80060548(SnaAutoMove *pAutoMove, HZD_HDL *arg1, SVECTOR *arg2)
{
    pAutoMove->field_0_ivec.vx = HZD_GetAddress_8005C6C4(arg1, arg2, -1);
    pAutoMove->field_0_ivec.vy = -1;
    pAutoMove->field_0_ivec.vz = -1;
    pAutoMove->field_0_ivec.pad = pAutoMove->field_0_ivec.vx;
    pAutoMove->field_10_vec1 = DG_ZeroVector_800AB39C;
    pAutoMove->field_18_vec2 = DG_ZeroVector_800AB39C;
}

void sna_act_unk_helper2_helper2_800605DC(SnaAutoMove *autoMove, HZD_HDL *pHzd, SVECTOR *pVec)
{
    autoMove->field_0_ivec.vy = HZD_GetAddress_8005C6C4(pHzd, pVec, -1);
    autoMove->field_18_vec2 = *pVec;
    autoMove->field_0_ivec.vz = -1;
}

void sub_80060644(SnaAutoMove *pAutoMove)
{
    pAutoMove->field_0_ivec.vy = GM_PlayerAddress_800AB9F0;
    pAutoMove->field_18_vec2 = GM_PlayerPosition_800ABA10;
}

int sna_act_unk_helper2_helper3_80060684(SnaAutoMove *pAutoMove, SVECTOR *param_2)
{
    SVECTOR vec;
    SVECTOR vec2;

    vec = *param_2;
    vec.vy = pAutoMove->field_18_vec2.vy;

    GV_SubVec3(&pAutoMove->field_18_vec2, &vec, &vec2);
    return GV_VecLen3(&vec2);
}

int sub_800606E4(SnaAutoMove *param_1, SVECTOR *param_2, int param_3)
{
    return sna_act_unk_helper2_helper3_80060684(param_1, param_2) < param_3;
}

int sna_unk_helper2_helper_8006070C(SnaAutoMove *pAutoMove, CONTROL *pControl)
{
    SVECTOR vec;
    SVECTOR *pPosition;
    HZD_HDL *pHzd;
    int x, y, z;
    int reach;
    int zon;
    HZD_ZON *pZon;

    pPosition = &pControl->mov;
    pHzd = pControl->map->hzd;

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

            GV_SubVec3(&pAutoMove->field_18_vec2, pPosition, &vec);
            pControl->turn.vy = GV_VecDir2(&vec);
            return -1;
        }

        zon = HZD_LinkRoute_8005C974(pHzd, x, y, &pControl->mov);
        pZon = &pHzd->f00_header->navmeshes[zon];

        pAutoMove->field_10_vec1.vx = pZon->x;
        pAutoMove->field_10_vec1.vy = pZon->y;
        pAutoMove->field_10_vec1.vz = pZon->z;

        pAutoMove->field_0_ivec.pad = (char)zon | ((char)zon << 8);
    }

    GV_SubVec3(&pAutoMove->field_10_vec1, pPosition, &vec);
    pControl->turn.vy = GV_VecDir2(&vec);
    return 0;
}