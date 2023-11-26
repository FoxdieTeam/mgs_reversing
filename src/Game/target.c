#include "linker.h"
#include "target.h"
#include "Game/game.h"

extern TARGET gTargets_800B64E0[64];

extern int gTargets_down_count_800ABA68;
int        SECTION(".sbss") gTargets_down_count_800ABA68;

extern int gTargets_up_count_800ABA6C;
int        SECTION(".sbss") gTargets_up_count_800ABA6C;

extern int     GM_PlayerMap_800ABA0C;
extern SVECTOR DG_ZeroVector_800AB39C;

static inline int range_check(int a, int b, int c, int d)
{
    return (d >= (c - (a + b))) && (c >= (d - (a + b)));
}

static inline int map_check(int a, int b)
{
    return (GM_PlayerMap_800ABA0C & a) && (GM_PlayerMap_800ABA0C & b);
}

int sub_8002D208(TARGET *a, TARGET *b)
{
    return (((a->field_2_side & b->field_2_side) == 0) &&
            range_check(a->field_10_size.vx, b->field_10_size.vx, a->field_8_vec.vx, b->field_8_vec.vx) &&
            range_check(a->field_10_size.vz, b->field_10_size.vz, a->field_8_vec.vz, b->field_8_vec.vz) &&
            range_check(a->field_10_size.vy, b->field_10_size.vy, a->field_8_vec.vy, b->field_8_vec.vy) &&
            map_check(a->field_4_map, b->field_4_map));
}

int sub_8002D300(TARGET *a, TARGET *b)
{
    return ((a->field_2_side == 0) &&
            range_check(a->field_10_size.vx, b->field_10_size.vx, a->field_8_vec.vx, b->field_8_vec.vx) &&
            range_check(a->field_10_size.vz, b->field_10_size.vz, a->field_8_vec.vz, b->field_8_vec.vz) &&
            range_check(a->field_10_size.vy, b->field_10_size.vy, a->field_8_vec.vy, b->field_8_vec.vy) &&
            map_check(a->field_4_map, b->field_4_map));
}

void GM_Targets_Reset_8002D3F0()
{
    gTargets_down_count_800ABA68 = 0;
    gTargets_up_count_800ABA6C = 0;
}

TARGET *GM_AllocTarget_8002D400()
{
    TARGET *target;
    int        i;

    if (gTargets_up_count_800ABA6C == 0)
    {
        if (gTargets_down_count_800ABA68 > 63)
        {
            return NULL;
        }

        target = &gTargets_800B64E0[gTargets_down_count_800ABA68];
        target->class = 1;
        gTargets_down_count_800ABA68++;
        return target;
    }

    target = gTargets_800B64E0;
    if (gTargets_down_count_800ABA68 > 0)
    {
        for (i = gTargets_down_count_800ABA68; i > 0; i--, target++)
        {
            if (target->class == 0)
            {
                target->class = 1;
                gTargets_up_count_800ABA6C--;
                return target;
            }
        }
    }
    gTargets_up_count_800ABA6C = 0;
    return NULL;
}

void GM_FreeTarget_8002D4B0(TARGET *pTarget)
{
    if (pTarget)
    {
        if (pTarget == &gTargets_800B64E0[gTargets_down_count_800ABA68 - 1])
        {
            --gTargets_down_count_800ABA68;
        }
        else
        {
            ++gTargets_up_count_800ABA6C;
        }
        pTarget->class = 0;
    }
}

void GM_Target_SetVector_8002D500(TARGET *pTarget, SVECTOR *pVec)
{
    short cur_map = GM_CurrentMap_800AB9B0;
    pTarget->field_8_vec = *pVec;
    pTarget->field_4_map = cur_map;
}

TARGET *GM_CaptureTarget_8002D530(TARGET *pTarget)
{
    int        i = gTargets_down_count_800ABA68;
    TARGET *pIter = gTargets_800B64E0;
    for (i = gTargets_down_count_800ABA68; i > 0; --i)
    {
        if (pTarget != pIter && (pIter->class & 2) != 0)
        {
            if (sub_8002D208(pIter, pTarget))
            {
                if ((pIter->field_6_flags & 2) == 0)
                {
                    pIter->field_6_flags |= 2;
                    pIter->field_3E = pTarget->field_3E;
                    pIter->field_18 = pTarget->field_18;
                    pIter->field_1C = pTarget->field_1C;
                    pIter->field_2A -= pTarget->field_2A;
                    pIter->field_42 = 1;
                    pTarget->field_6_flags |= 2u;
                    return pIter;
                }
            }
        }
        pIter++;
    }
    return 0;
}

TARGET *GM_C4Target_8002D620(TARGET *pTarget)
{
    int        i;
    TARGET *pIter = gTargets_800B64E0;
    for (i = gTargets_down_count_800ABA68; i > 0; --i)
    {
        if (pTarget != pIter && (pIter->class & TARGET_C4) && sub_8002D208(pIter, pTarget) &&
            !(pIter->field_6_flags & TARGET_C4))
        {
            pIter->field_6_flags |= TARGET_C4;
            pTarget->field_6_flags |= TARGET_C4;
            return pIter;
        }
        ++pIter;
    }

    return 0;
}

int GM_TouchTarget_8002D6D8(TARGET *pTarget)
{
    TARGET *pIter;
    int count;
    int hp, oldhp;

    if (!(pTarget->class & 0x80))
    {
        return 0;
    }

    if (pTarget->field_6_flags & 0x80)
    {
        return 1;
    }

    pIter = gTargets_800B64E0;
    count = gTargets_down_count_800ABA68;

    hp = pTarget->field_26_hp;

    while (count > 0)
    {
        if ((pTarget != pIter) && (pIter->class & 0x80) && sub_8002D208(pIter, pTarget))
        {
            oldhp = pIter->field_26_hp;
            pIter->field_26_hp -= hp;
            pIter->field_28 += oldhp - pIter->field_26_hp;

            pIter->field_6_flags |= 0x80;
            pTarget->field_6_flags |= 0x80;
        }

        pIter++;
        count--;
    }

    return (pTarget->field_6_flags & 0x80) >> 7;
}

static inline int sub_helper_8002D7DC(int which, int a, int b)
{
    switch (which & 0x3)
    {
    case 0:
        return 0;

    case 1:
        return a - b;

    case 2:
        return (a > b) ? a : 0;

    default:
        return a;
    }
}

#define SCALE_VXZ(in, scale, out)           \
do                                          \
{                                           \
    int angle;                              \
    angle = GV_VecDir2_80016EF8(in);        \
    GV_DirVec2_80016F24(angle, scale, out); \
} while (0)

int sub_8002D7DC(TARGET *pTarget)
{
    SVECTOR dist;
    SVECTOR scaled;
    int     hp, hp2;
    int     f24;
    TARGET *pIter;
    int     count;
    int     hp_diff;

    hp = pTarget->field_26_hp;
    f24 = pTarget->field_24;

    pIter = gTargets_800B64E0;
    for (count = gTargets_down_count_800ABA68; count > 0; pIter++, count--)
    {
        if ((pTarget == pIter) || !(pIter->class & 0x4) || !sub_8002D208(pIter, pTarget))
        {
            continue;
        }

        pIter->field_6_flags |= 0x4;

        hp2 = pIter->field_26_hp;
        pIter->field_26_hp = sub_helper_8002D7DC(pIter->field_24, hp2, hp);
        hp = sub_helper_8002D7DC(f24, hp, hp2);


        pIter->field_28 += hp2 - pIter->field_26_hp;
        pIter->field_2A -= pTarget->field_2A;
        pIter->field_3E = pTarget->field_3E;
        pIter->field_44 = pTarget->field_44;

        if (f24 & 0x4)
        {
            GV_SubVec3_80016D40(&pIter->field_8_vec, &pTarget->field_8_vec, &dist);
            SCALE_VXZ(&dist, pTarget->field_2C_vec.vx, &scaled);
            GV_AddVec3_80016D00(&pIter->field_2C_vec, &scaled, &pIter->field_2C_vec);
        }
        else
        {
            GV_AddVec3_80016D00(&pIter->field_2C_vec, &pTarget->field_2C_vec, &pIter->field_2C_vec);
        }

        if (hp < 0)
        {
            break;
        }
    }

    hp_diff = pTarget->field_26_hp - hp;
    pTarget->field_26_hp = hp;

    if (hp_diff > 0)
    {
        pTarget->field_6_flags |= 0x4;
    }

    return hp_diff;
}

static inline int sub_helper2_8002DA14( TARGET *pTarget, TARGET *pTarget2, int use_z )
{
    int a, b;
    int v0, v1;

    b = use_z ? pTarget2->field_10_size.vz : pTarget2->field_10_size.vx;
    a = use_z ? pTarget->field_10_size.vz : pTarget->field_10_size.vx;

    v1 = use_z ? pTarget2->field_8_vec.vz : pTarget2->field_8_vec.vx;
    v0 = use_z ? pTarget->field_8_vec.vz : pTarget->field_8_vec.vx;

    b = b + a;
    a = v0 - v1;


    if (a >= 0)
    {
        b -= a;
        if (b < 0)
        {
            b = 0;
        }
        return b;
    }
    else
    {
        a += b;
        if (a < 0)
        {
            a = 0;
        }
        return -a;
    }
}

static inline int sub_helper_8002DA14(TARGET *pTarget, TARGET *pIter)
{
    int val, val2;
    int which;

    val = sub_helper2_8002DA14(pTarget, pIter, 0);
    if (val == 0)
    {
        return 0;
    }

    val2 = sub_helper2_8002DA14(pTarget, pIter, 1);
    if (val2 == 0)
    {
        return 0;
    }

    if (!(pIter->field_3C & 2))
    {
        // this is NOT an inline, /= 2 does not work otherwise
        if (abs(val) <= abs(val2))
        {
            val /= 2;
            pTarget->field_34_vec.vx += val;
            pIter->field_34_vec.vx -= val;

            if (val > 0)
            {
                which = 2;
            }
            else
            {
                which = 4;
            }
        }
        else
        {
            val2 /= 2;
            pTarget->field_34_vec.vz += val2;
            pIter->field_34_vec.vz -= val2;

            if (val2 > 0)
            {
                which = 1;
            }
            else
            {
                which = 3;
            }
        }

        if (pIter->field_3C & 1)
        {
            pTarget->field_34_vec.pad = which;
        }
    }

    return 1;
}

int sub_8002DA14(TARGET *pTarget)
{
    TARGET *pIter;
    int        count;

    if (!(pTarget->class & 0x8))
    {
        return 0;
    }

    pTarget->field_34_vec = DG_ZeroVector_800AB39C;
    pTarget->field_34_vec.pad = 0;

    pIter = gTargets_800B64E0;

    for (count = gTargets_down_count_800ABA68; count > 0; pIter++, count--)
    {
        pIter->field_40 = 0;

        if ((pTarget == pIter) || !(pIter->class & 0x8) || !sub_8002D300(pIter, pTarget))
        {
            continue;
        }

        if (sub_helper_8002DA14(pTarget, pIter))
        {
            pIter->field_6_flags |= 0x8;
            pTarget->field_6_flags |= 0x8;
            pIter->field_40 = pTarget->field_2_side;
        }
    }


    return (short)(pTarget->field_6_flags & 0x8) > 0;
}

void GM_SetTarget_8002DC74(TARGET *pTarget, int targetFlags, int whichSide, SVECTOR *pSize)
{
    short cur_map = GM_CurrentMap_800AB9B0;
    pTarget->class = targetFlags;
    pTarget->field_2_side = whichSide;
    pTarget->field_6_flags = 0;
    pTarget->field_4_map = cur_map;
    pTarget->field_10_size = *pSize;
    pTarget->field_3C = 0;
}

void GM_Target_8002DCB4(TARGET *pTarget, int a2, int a3, int *a4, SVECTOR *a5)
{
    pTarget->field_18 = a4;
    pTarget->field_3E = a2;
    pTarget->field_2A = a3;
    pTarget->field_1C = a5;
}

void GM_Target_8002DCCC(TARGET *pTarget, int a2, int a3, int hp, int a5, SVECTOR *a6)
{
    pTarget->field_24 = a2;
    pTarget->field_3E = a3;
    pTarget->field_26_hp = hp;
    pTarget->field_28 = 0;
    pTarget->field_2A = a5;
    pTarget->field_2C_vec = *a6;
    pTarget->field_44 = -1;
}

void sub_8002DD14(TARGET *pTarget, MATRIX *pMatrix)
{
    pTarget->field_20 = pMatrix;
}

void sub_8002DD1C(SVECTOR *svec1, SVECTOR *svec2, TARGET *pTarget)
{
    int coord1, coord2;
    int diff;

    coord1 = svec1->vx;
    coord2 = svec2->vx;
    diff = (coord1 - coord2) / 2;
    pTarget->field_8_vec.vx = (coord1 + coord2) / 2;
    pTarget->field_10_size.vx = abs(diff);

    coord1 = svec1->vy;
    coord2 = svec2->vy;
    diff = (coord1 - coord2) / 2;
    pTarget->field_8_vec.vy = (coord1 + coord2) / 2;
    pTarget->field_10_size.vy = abs(diff);

    coord1 = svec1->vz;
    coord2 = svec2->vz;
    diff = (coord1 - coord2) / 2;
    pTarget->field_8_vec.vz = (coord1 + coord2) / 2;
    pTarget->field_10_size.vz = abs(diff);
}

#define sub_8002DDE0_helper(AXIS1, AXIS2, AXIS3)                                                                       \
    {                                                                                                                  \
        int vec1_axis1, vec1_axis2, vec1_axis3;                                                                        \
        int outvec_axis1, outvec_axis3;                                                                                \
        int outvec_addend_axis2;                                                                                       \
        int multiplier;                                                                                                \
        int target_field_10_axis1;                                                                                     \
        vec1_axis1 = vec1->AXIS1;                                                                                      \
        divisor = vec2->AXIS1 - vec1_axis1;                                                                            \
        if (divisor != 0)                                                                                              \
        {                                                                                                              \
            outvec_axis1 = target->field_8_vec.AXIS1;                                                                  \
            target_field_10_axis1 = target->field_10_size.AXIS1;                                                       \
            if (target->field_8_vec.AXIS1 < vec1_axis1)                                                                \
            {                                                                                                          \
                outvec_axis1 += target_field_10_axis1;                                                                 \
                if (vec1_axis1 < outvec_axis1)                                                                         \
                {                                                                                                      \
                    outvec_axis1 = vec1_axis1;                                                                         \
                }                                                                                                      \
            }                                                                                                          \
            else                                                                                                       \
            {                                                                                                          \
                outvec_axis1 -= target_field_10_axis1;                                                                 \
                if (outvec_axis1 < vec1_axis1)                                                                         \
                {                                                                                                      \
                    outvec_axis1 = vec1_axis1;                                                                         \
                }                                                                                                      \
            }                                                                                                          \
            multiplier = outvec_axis1 - vec1_axis1;                                                                    \
            vec1_axis2 = vec1->AXIS2;                                                                                  \
            outvec_addend_axis2 = (vec2->AXIS2 - vec1_axis2) * multiplier / divisor;                                   \
            if (vec1_axis2 + outvec_addend_axis2 >= target->field_8_vec.AXIS2 - target->field_10_size.AXIS2 &&         \
                target->field_8_vec.AXIS2 + target->field_10_size.AXIS2 >= vec1_axis2 + outvec_addend_axis2)           \
            {                                                                                                          \
                vec1_axis3 = vec1->AXIS3;                                                                              \
                outvec_axis3 = vec1_axis3;                                                                             \
                outvec_axis3 += (vec2->AXIS3 - outvec_axis3) * multiplier / divisor;                                   \
                if (outvec_axis3 >= target->field_8_vec.AXIS3 - target->field_10_size.AXIS3 &&                         \
                    target->field_8_vec.AXIS3 + target->field_10_size.AXIS3 >= outvec_axis3)                           \
                {                                                                                                      \
                    do                                                                                                 \
                    {                                                                                                  \
                        outvec->AXIS1 = outvec_axis1;                                                                  \
                        outvec->AXIS2 = vec1_axis2 + outvec_addend_axis2;                                              \
                        outvec->AXIS3 = outvec_axis3;                                                                  \
                    } while (0);                                                                                       \
                    return 1;                                                                                          \
                }                                                                                                      \
            }                                                                                                          \
        }                                                                                                              \
    }

int sub_8002DDE0(SVECTOR *vec1, SVECTOR *vec2, TARGET *target, SVECTOR *outvec)
{
    int divisor;
    sub_8002DDE0_helper(vx, vy, vz);
    sub_8002DDE0_helper(vy, vz, vx);
    sub_8002DDE0_helper(vz, vx, vy);
    return 0;
}

int GM_Target_8002E1B8(SVECTOR *pVec, SVECTOR *pVec1, int map_bit, SVECTOR *pVec2, int side)
{
    TARGET *pIter;
    int        i;
    int        bResult;
    TARGET  target;

    target.field_4_map = map_bit;
    target.field_2_side = 0;
    sub_8002DD1C(pVec, pVec1, &target);

    pIter = gTargets_800B64E0;
    i = gTargets_down_count_800ABA68;
    for (bResult = 0; i > 0; ++pIter)
    {
        if (pIter->field_2_side != side && (pIter->class & TARGET_SEEK) != 0)
        {
            if (sub_8002D208(pIter, &target))
            {
                if (sub_8002DDE0(pVec, pVec1, pIter, pVec2))
                {
                    sub_8002DD1C(pVec, pVec2, &target);
                    bResult = 1;
                }
            }
        }
        --i;
    }
    return bResult;
}

int sub_8002E2A8(SVECTOR *arg0, SVECTOR *arg1, int map, SVECTOR *arg3)
{
    TARGET target;
    TARGET *pTarget;
    int count;

    target.field_4_map = map;
    target.field_2_side = 0;

    sub_8002DD1C(arg0, arg1, &target);

    pTarget = gTargets_800B64E0;
    count = gTargets_down_count_800ABA68;

    while (count > 0)
    {
        if (((pTarget->field_3C & 0x1) != 0) &&
            ((pTarget->class & 0x10) != 0) &&
            sub_8002D208(pTarget, &target) &&
            sub_8002DDE0(arg0, arg1, pTarget, arg3))
        {
            return 1;
        }

        pTarget++;
        count--;
    }

    return 0;
}

void GM_Target_8002E374(int *ppDownCount, TARGET **ppTargets)
{
    *ppDownCount = gTargets_down_count_800ABA68;
    *ppTargets = gTargets_800B64E0;
}
