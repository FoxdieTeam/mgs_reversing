#include "sgtrect3.h"
#include "libdg/dgd.h"
#include <LIBGTE.H>
#include "psyq.h"
#include "Game/target.h"

// stinger missile first person HUD + stinger HUD?

extern DG_CHNL          DG_Chanls_800B1800[3];
extern char             byte_8009F5F8[];
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;

void sgtrect3_act_helper_helper_80070040(void *ot, void *prim)
{
    if (!(GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK4000000))
    {
        addPrim(ot, prim);
    }
}

void sgtrect3_act_helper_8007009C()
{
    DG_CHNL *chnl = &DG_Chanls_800B1800[1];
    DG_Clip_80017594(&chnl->field_5C_clip_rect, chnl->field_4C_clip_distance);
    SetRotMatrix_80093218(&chnl->field_10_transformation_matrix);
    SetTransMatrix_80093248(&chnl->field_10_transformation_matrix);
}

unsigned int sgtrect3_act_helper_helper_800700E0(GM_Target *target, DVECTOR *vector)
{
    int     vyAddend;
    int     vyDiff;
    DVECTOR screenCoordinates;
    SVECTOR vertexCoordinateVector;
    long    interpolatedValue;
    long    flag;

    vyAddend = (target->field_10_size.vy * 3) / 5;
    if (vyAddend < 500)
    {
        vyAddend = 500;
    }
    vertexCoordinateVector = target->field_8_vec;
    vertexCoordinateVector.vy += vyAddend;
    RotTransPers_80093478(&vertexCoordinateVector, (long *)&screenCoordinates, &interpolatedValue, &flag);
    vyDiff = vector->vy - screenCoordinates.vy;
    if (vyDiff < 0)
    {
        vyDiff = 0;
    }
    if (vyDiff >= 0xe1)
    {
        vyDiff = 0;
    }
    return vyDiff & 0xffff;
}

extern int dword_800ABA0C;

int sgtrect3_act_helper_800701A8(GM_Target *target)
{
    if (!((((target->field_0_flags & 0xfffe) != 0 && (target->field_4_map & dword_800ABA0C) != 0) &&
           target->field_2_side == 2) &&
          target->field_6_flags == 0 && ((target->field_0_flags & 0x220) == 0)))
    {
        return 0;
    }

    return 1;
}

extern int     dword_8009F46C;
extern int     dword_8009F490;
extern SVECTOR stru_800ABA10;
extern SVECTOR svector_8009F478;

void sgtrect3_act_helper_8007020C(Actor_sgtrect3 *sgtrect3, DVECTOR *outScreenCoordsArray, GM_Target **outTargetsArray,
                                  ushort *outResultsArray)
{
    int         downCount;
    GM_Target  *targets, *currentTarget;
    SVECTOR     vector, vector2;
    int         targetCount;
    DVECTOR     screenCoordinates;
    long        interpolatedValue;
    long        flag;
    int         result;
    int         shortestVecLen;
    int         vecLen;
    int         vx, vy;
    DVECTOR    *outScreenCoordsIter;
    GM_Target **outTargetsIter;
    ushort     *outResultsIter;

    targets = (GM_Target *)0x0;
    GM_Target_8002E374(&downCount, &targets);
    if (downCount != 1)
    {
        GM_Target *lastTarget;

        if (dword_8009F46C != 0)
        {
            vector = svector_8009F478;
        }
        else
        {
            vector = stru_800ABA10;
        }

        targetCount = 0;
        shortestVecLen = -1;
        lastTarget = (GM_Target *)0x0;
        outScreenCoordsIter = outScreenCoordsArray;
        outTargetsIter = outTargetsArray;
        outResultsIter = outResultsArray;

        while (--downCount >= 0)
        {
            currentTarget = targets;
            targets++;
            if (sgtrect3_act_helper_800701A8(currentTarget))
            {
                if (RotTransPers_80093478(&currentTarget->field_8_vec, (long *)&screenCoordinates, &interpolatedValue,
                                          &flag) > 0)
                {
                    vx = screenCoordinates.vx;
                    vy = screenCoordinates.vy;
                    result = sgtrect3_act_helper_helper_800700E0(currentTarget, &screenCoordinates) & 0xffff;
                    if (result != 0 && vx + result >= -160 && vx - result < 161 && vy + result >= -112 &&
                        vy - result < 113)
                    {
                        if (vx < result && -result < vx && vy < result && -result < vy)
                        {
                            vector2.vx = vx;
                            vector2.vy = vy;
                            vector2.vz = 0;

                            if (shortestVecLen < 0)
                            {
                                shortestVecLen = 60000;
                            }

                            GV_SubVec3_80016D40(&currentTarget->field_8_vec, &vector, &vector2);
                            vecLen = GV_VecLen3_80016D80(&vector2);
                            if (vecLen < shortestVecLen && vecLen >= 2401)
                            {
                                shortestVecLen = vecLen;
                                lastTarget = currentTarget;
                            }
                        }

                        targetCount++;
                        *outScreenCoordsIter++ = screenCoordinates;
                        *outResultsIter++ = result;
                        *outTargetsIter++ = currentTarget;
                        if (targetCount == 0x1f)
                        {
                            break;
                        }
                    }
                }
            }
        }

        if (dword_8009F490 == 0)
        {
            if (lastTarget == (GM_Target *)0x0)
            {
                if (sgtrect3->field_30_target != (GM_Target *)0x0)
                {
                    sgtrect3->field_34_count++;
                    sgtrect3->field_38++;
                    if (sgtrect3->field_38 >= 24)
                    {
                        sgtrect3->field_34_count = 0;
                        sgtrect3->field_38 = 0;
                        sgtrect3->field_30_target = (GM_Target *)0x0;
                    }
                }
            }
            else
            {
                sgtrect3->field_38 = 0;
                if (sgtrect3->field_30_target == lastTarget)
                {
                    sgtrect3->field_34_count++;
                }
                else
                {
                    sgtrect3->field_34_count = 0;
                }
                sgtrect3->field_30_target = lastTarget;
            }
        }
        else if (sgtrect3->field_30_target != (GM_Target *)0x0)
        {
            if (!sgtrect3_act_helper_800701A8(sgtrect3->field_30_target))
            {
                sgtrect3->field_34_count = 0;
                sgtrect3->field_38 = 0;
                sgtrect3->field_30_target = (GM_Target *)0x0;
            }
            else
            {
                sgtrect3->field_34_count++;
                sgtrect3->field_38 = 24;
            }
        }

        sgtrect3->field_21AC_target_count = targetCount;
    }
}

#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_helper_80070568.s") // 696 bytes
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_helper_80070820.s") // 656 bytes
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_helper_80070AB0.s") // 508 bytes
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_helper_80070CAC.s") // 360 bytes
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_80070E14.s")        // 172 bytes

void sgtrect3_kill_80070EC0(Actor_sgtrect3 *actor_sgtrect3)
{
    byte_8009F5F8[0] = 0;
}

#pragma INCLUDE_ASM("asm/Thing/sgtrect3_loader_helper_80070ECC.s") // 128 bytes
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_loader_80070F4C.s")        // 196 bytes
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_init_80071010.s")          // 268 bytes
