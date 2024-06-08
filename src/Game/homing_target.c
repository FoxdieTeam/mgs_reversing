#include "linker.h"
#include "homing_target.h"
#include "mts/mts_new.h"
#include "Game/map.h"
#include "libgv/libgv.h"
#include "psyq.h"

extern HOMING gHomingTargets_800B8230[HOMING_TARGET_ARRAY_LENGTH];

void HomingTarget_Clear_All_80032C68()
{
    HOMING *pIter; // $v0
    int            i;     // $v1

    pIter = gHomingTargets_800B8230;
    for (i = HOMING_TARGET_ARRAY_LENGTH; i > 0; --i)
    {
        pIter->field_C_bUsed = 0;
        ++pIter;
    }
}

HOMING *HomingTarget_Alloc_80032C8C(MATRIX *a1, CONTROL *a2)
{
    int            pos; // $v1
    HOMING *pIter = gHomingTargets_800B8230;
    for (pos = HOMING_TARGET_ARRAY_LENGTH; pos > 0; --pos)
    {
        if (!pIter->field_C_bUsed)
        {
            break;
        }
        ++pIter;
    }

    if (!pos)
    {
        printf("Homing target over !!!\n");
        return 0;
    }

    pIter->field_0 = a1;
    pIter->field_4 = a2;
    pIter->flag = 0;
    pIter->field_C_bUsed = 1;
    return pIter;
}

void HomingTarget_Free_80032CFC(HOMING *pTarget)
{
    if (pTarget)
    {
        pTarget->field_C_bUsed = 0;
    }
}

void HomingTarget_1_80032D10(MATRIX *pMtx, int vecY, int *pRetY, int *pRetX, int mapBit)
{
    int            smallest_len; // $s6
    HOMING *pTargetIter;  // $s3
    int            i;            // $s5
    int            len;          // $s1
    int            retY;         // $s0
    SVECTOR        vec1;
    SVECTOR        vec2;
    SVECTOR        vec3;

    smallest_len = 6100;
    pTargetIter = &gHomingTargets_800B8230[0];
    vec1.vx = pMtx->t[0];
    vec1.vy = pMtx->t[1];
    vec1.vz = pMtx->t[2];
    *pRetY = -1;
    *pRetX = 0;
    for (i = HOMING_TARGET_ARRAY_LENGTH; i > 0; pTargetIter++, i--)
    {
        if (!pTargetIter->field_C_bUsed)
        {
            continue;
        }

        if ((pTargetIter->field_4->map->index & mapBit) && pTargetIter->flag == 1)
        {
            vec2.vx = pTargetIter->field_0->t[0];
            vec2.vy = pTargetIter->field_0->t[1];
            vec2.vz = pTargetIter->field_0->t[2];
            GV_SubVec3_80016D40(&vec2, &vec1, &vec3);
            len = GV_VecLen3_80016D80(&vec3);
            if (len < smallest_len)
            {
                retY = GV_VecDir2_80016EF8(&vec3);
                if (GV_DiffDirAbs_8001706C(vecY, retY) < 512)
                {
                    smallest_len = len;
                    *pRetY = retY;
                    *pRetX = (ratan2(len, vec2.vy - vec1.vy) & 4095) - 1024;
                }
            }
        }
    }
}

void HomingTarget_2_80032EAC(MATRIX *pMtx, int vecY, int *pRetY, int *pRetX, int mapBit, int max_dist, int min_angle)
{
    int            smallest_len; // $s6
    HOMING *pTargetIter;  // $s3
    int            i;            // $s5
    int            len;          // $s1
    int            retY;         // $s0
    SVECTOR        vec1;
    SVECTOR        vec2;
    SVECTOR        vec3;

    smallest_len = max_dist + 100;
    pTargetIter = &gHomingTargets_800B8230[0];
    vec1.vx = pMtx->t[0];
    vec1.vy = pMtx->t[1];
    vec1.vz = pMtx->t[2];
    *pRetY = -1;
    *pRetX = 0;

    for (i = HOMING_TARGET_ARRAY_LENGTH; i > 0; pTargetIter++, i--)
    {
        if (!pTargetIter->field_C_bUsed)
        {
            continue;
        }

        if ((pTargetIter->field_4->map->index & mapBit) && pTargetIter->flag == 1)
        {
            vec2.vx = pTargetIter->field_0->t[0];
            vec2.vy = pTargetIter->field_0->t[1];
            vec2.vz = pTargetIter->field_0->t[2];
            GV_SubVec3_80016D40(&vec2, &vec1, &vec3);
            len = GV_VecLen3_80016D80(&vec3);
            if (len < smallest_len)
            {
                retY = GV_VecDir2_80016EF8(&vec3);
                if (GV_DiffDirAbs_8001706C(vecY, retY) < min_angle)
                {
                    smallest_len = len;
                    *pRetY = retY;
                    *pRetX = (ratan2(len, vec2.vy - vec1.vy) & 4095) - 1024;
                }
            }
        }
    }
}
