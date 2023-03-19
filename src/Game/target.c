#include "linker.h"
#include "target.h"
#include "Game/game.h"

extern TARGET gTargets_800B64E0[64];

extern int gTargets_down_count_800ABA68;
int        SECTION(".sbss") gTargets_down_count_800ABA68;

extern int gTargets_up_count_800ABA6C;
int        SECTION(".sbss") gTargets_up_count_800ABA6C;

extern int dword_800ABA0C;

// TODO: This probably has an inline that will clean it up
int sub_8002D208(TARGET *arg0, TARGET *arg1)
{
    int temp_a2;
    int temp_a2_2;
    int temp_a2_3;
    int temp_a3;
    int temp_a3_2;
    int temp_a3_3;
    int temp_v1;
    int temp_v1_2;
    int temp_v1_3;
    int var_t0;
    int var_t0_2;
    int var_t0_3;
    int var_t1;
    int var_v1;

    int map0;
    int map1;

    var_t1 = 0;

    if (!(arg0->field_2_side & arg1->field_2_side))
    {
        temp_a3 = arg0->field_8_vec.vx;
        temp_a2 = arg1->field_8_vec.vx;
        temp_v1 = arg0->field_10_size.vx + arg1->field_10_size.vx;
        var_t0 = 0;

        if (temp_a2 >= (temp_a3 - temp_v1))
        {
            var_t0 = (temp_a3 < (temp_a2 - temp_v1)) ^ 1;
        }

        if (var_t0 != 0)
        {
            temp_a3_2 = arg0->field_8_vec.vz;
            temp_a2_2 = arg1->field_8_vec.vz;
            temp_v1_2 = arg0->field_10_size.vz + arg1->field_10_size.vz;
            var_t0_2 = 0;

            if (temp_a2_2 >= (temp_a3_2 - temp_v1_2))
            {
                var_t0_2 = (temp_a3_2 < (temp_a2_2 - temp_v1_2)) ^ 1;
            }

            if (var_t0_2 != 0)
            {
                temp_a3_3 = arg0->field_8_vec.vy;
                temp_a2_3 = arg1->field_8_vec.vy;
                temp_v1_3 = arg0->field_10_size.vy + arg1->field_10_size.vy;
                var_t0_3 = 0;

                if (temp_a2_3 >= (temp_a3_3 - temp_v1_3))
                {
                    var_t0_3 = (temp_a3_3 < (temp_a2_3 - temp_v1_3)) ^ 1;
                }

                if (var_t0_3 != 0)
                {
                    var_v1 = 0;

                    map0 = arg0->field_4_map;
                    map1 = arg1->field_4_map;

                    if ((dword_800ABA0C & map0) && (dword_800ABA0C & map1))
                    {
                        var_v1 = 1;
                    }

                    if (var_v1 != 0)
                    {
                        var_t1 = 1;
                    }
                }
            }
        }
    }

    return var_t1;
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper_helper_8002D300.s") // 240 bytes

void GM_Targets_Reset_8002D3F0(void)
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
        target->field_0_flags = 1;
        gTargets_down_count_800ABA68++;
        return target;
    }

    target = gTargets_800B64E0;
    if (gTargets_down_count_800ABA68 > 0)
    {
        for (i = gTargets_down_count_800ABA68; i > 0; i--, target++)
        {
            if (target->field_0_flags == 0)
            {
                target->field_0_flags = 1;
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
        pTarget->field_0_flags = 0;
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
        if (pTarget != pIter && (pIter->field_0_flags & 2) != 0)
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
        if (pTarget != pIter && (pIter->field_0_flags & TARGET_C4) && sub_8002D208(pIter, pTarget) &&
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

#pragma INCLUDE_ASM("asm/Game/sub_8002D6D8.s") // 260 bytes

#pragma INCLUDE_ASM("asm/sub_8002D7DC.s") // 568 bytes
// int GM_Target_8002D7DC(TARGET *pTarget);

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper_8002DA14.s") // 608 bytes

void GM_SetTarget_8002DC74(TARGET *pTarget, int targetFlags, int whichSide, SVECTOR *pSize)
{
    short cur_map = GM_CurrentMap_800AB9B0;
    pTarget->field_0_flags = targetFlags;
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

void sub_8002DD14(int param_1, int param_2)
{
    *(int *)(param_1 + 0x20) = param_2;
    return;
}

#pragma INCLUDE_ASM("asm/sub_8002DD1C.s") // 196 bytes
#pragma INCLUDE_ASM("asm/sub_8002DDE0.s") // 984 bytes

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
        if (pIter->field_2_side != side && (pIter->field_0_flags & TARGET_SEEK) != 0)
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

#pragma INCLUDE_ASM("asm/sub_8002E2A8.s") // 204 bytes

void GM_Target_8002E374(int *ppDownCount, TARGET **ppTargets)
{
    *ppDownCount = gTargets_down_count_800ABA68;
    *ppTargets = gTargets_800B64E0;
}
