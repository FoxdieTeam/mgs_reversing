#include "sgtrect3.h"
#include <libgte.h>
#include "psyq.h"
#include "Game/target.h"
#include "SD/g_sound.h"

// stinger missile first person HUD + stinger HUD?

extern PlayerStatusFlag GM_PlayerStatus_800ABA50;

char byte_8009F5F8[] = {0, 0, 0, 0};

void sgtrect3_act_helper_helper_80070040(void *ot, void *prim)
{
    if (!(GM_PlayerStatus_800ABA50 & PLAYER_UNK4000000))
    {
        addPrim(ot, prim);
    }
}

void sgtrect3_act_helper_8007009C()
{
    DG_Clip_80017594(&DG_Chanl(0)->field_5C_clip_rect, DG_Chanl(0)->field_50_clip_distance);
    SetRotMatrix(&DG_Chanl(0)->field_10_eye_inv);
    SetTransMatrix(&DG_Chanl(0)->field_10_eye_inv);
}

unsigned int sgtrect3_act_helper_helper_800700E0(TARGET *target, DVECTOR *vector)
{
    int     vyAddend;
    int     vyDiff;
    DVECTOR screenCoordinates;
    SVECTOR vertexCoordinateVector;
    long    interpolatedValue;
    long    flag;

    vyAddend = (target->size.vy * 3) / 5;
    if (vyAddend < 500)
    {
        vyAddend = 500;
    }
    vertexCoordinateVector = target->center;
    vertexCoordinateVector.vy += vyAddend;
    RotTransPers(&vertexCoordinateVector, (long *)&screenCoordinates, &interpolatedValue, &flag);
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

extern int GM_PlayerMap_800ABA0C;

int sgtrect3_act_helper_800701A8(TARGET *target)
{
    if (!((((target->class & 0xfffe) != 0 && (target->map & GM_PlayerMap_800ABA0C) != 0) &&
           target->side == 2) &&
          target->damaged == 0 && ((target->class & 0x220) == 0)))
    {
        return 0;
    }

    return 1;
}

extern int     dword_8009F46C;
extern int     amissile_alive_8009F490;
extern SVECTOR GM_PlayerPosition_800ABA10;
extern SVECTOR svector_8009F478;

void sgtrect3_act_helper_8007020C(SgtRect3Work *work, DVECTOR *outScreenCoordsArray, TARGET **outTargetsArray,
                                  ushort *outResultsArray)
{
    int         downCount;
    TARGET *targets, *currentTarget;
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
    TARGET **outTargetsIter;
    ushort     *outResultsIter;

    targets = NULL;
    GM_Target_8002E374(&downCount, &targets);
    if (downCount != 1)
    {
        TARGET *lastTarget;

        vector = (dword_8009F46C != 0) ? svector_8009F478 : GM_PlayerPosition_800ABA10;

        targetCount = 0;
        shortestVecLen = -1;
        lastTarget = NULL;
        outScreenCoordsIter = outScreenCoordsArray;
        outTargetsIter = outTargetsArray;
        outResultsIter = outResultsArray;

        while (--downCount >= 0)
        {
            currentTarget = targets;
            targets++;
            if (sgtrect3_act_helper_800701A8(currentTarget))
            {
                if (RotTransPers(&currentTarget->center, (long *)&screenCoordinates, &interpolatedValue,
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

                            GV_SubVec3(&currentTarget->center, &vector, &vector2);
                            vecLen = GV_VecLen3(&vector2);
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

        if (amissile_alive_8009F490 == 0)
        {
            if (!lastTarget)
            {
                if (work->field_30_target)
                {
                    work->field_34_count++;
                    work->field_38++;
                    if (work->field_38 >= 24)
                    {
                        work->field_34_count = 0;
                        work->field_38 = 0;
                        work->field_30_target = NULL;
                    }
                    #ifdef VR_EXE
                        if (work->field_30_target->class & TARGET_NO_LOCKON)
                        {
                            work->field_34_count = 0;
                            work->field_38 = 0;
                            work->field_30_target = NULL;
                        }
                    #endif
                }
            }
            else
            {
                work->field_38 = 0;
                if (work->field_30_target == lastTarget)
                {
                    work->field_34_count++;
                }
                else
                {
                    work->field_34_count = 0;
                }
                work->field_30_target = lastTarget;
            }
        }
        else if (work->field_30_target)
        {
            if (!sgtrect3_act_helper_800701A8(work->field_30_target))
            {
                work->field_34_count = 0;
                work->field_38 = 0;
                work->field_30_target = NULL;
            }
            else
            {
                work->field_34_count++;
                work->field_38 = 24;
            }
        }

        work->field_21AC_target_count = targetCount;
    }
}

extern int GV_Clock_800AB920;

void sgtrect3_act_helper_80070568(SgtRect3Work *work, void *ot, LINE_F3 *lineF3Arr)
{
    int count;
    int index;

    LINE_F4 *firstLineF4;
    LINE_F4 *secondLineF4;

    int   firstLineX_0_3;
    int   firstLineX_1_2;
    int   secondLineX_0_3;
    int   secondLineX_1_2;
    int   xOffset;
    short yCoord_0_1;
    short yCoord_2_3;

    int multiplicand;

    count = work->field_34_count;
    if (0xc < count)
    {
        count = 0xc;
    }

    firstLineF4 = work->field_1C3C_lines[GV_Clock_800AB920].field_0;
    secondLineF4 = firstLineF4 + 1;
    for (index = 0; index < count; index++)
    {
        firstLineX_1_2 = (lineF3Arr->x0 * index) / 12;
        secondLineX_1_2 = ((lineF3Arr->x1 - 319) * index) / 12 + 319;
        yCoord_0_1 = (((lineF3Arr->y0 - 29) * index) / 12) + 29;
        yCoord_2_3 = (((lineF3Arr->y2 - 210) * index) / 12) + 210;

        xOffset = ((secondLineX_1_2 - firstLineX_1_2) / 6);
        firstLineX_0_3 = firstLineX_1_2 + xOffset;
        secondLineX_0_3 = secondLineX_1_2 - xOffset;

        firstLineF4->x0 = firstLineF4->x3 = firstLineX_0_3;
        secondLineF4->x0 = secondLineF4->x3 = secondLineX_0_3;
        firstLineF4->x1 = firstLineF4->x2 = firstLineX_1_2;
        secondLineF4->x1 = secondLineF4->x2 = secondLineX_1_2;
        firstLineF4->y0 = firstLineF4->y1 = secondLineF4->y0 = secondLineF4->y1 = yCoord_0_1;
        firstLineF4->y2 = firstLineF4->y3 = secondLineF4->y2 = secondLineF4->y3 = yCoord_2_3;

        if (index != 11)
        {
            multiplicand = 16 - (work->field_34_count - index);

            if (multiplicand < 0)
            {
                multiplicand = 0;
            }

            firstLineF4->r0 = (unsigned int)(work->field_2C_rgb.rgbChars[0] * multiplicand) >> 4;
            firstLineF4->g0 = (unsigned int)(work->field_2C_rgb.rgbChars[1] * multiplicand) >> 4;
            firstLineF4->b0 = (unsigned int)(work->field_2C_rgb.rgbChars[2] * multiplicand) >> 4;
            secondLineF4->r0 = firstLineF4->r0;
            secondLineF4->g0 = firstLineF4->g0;
            secondLineF4->b0 = firstLineF4->b0;
        }

        sgtrect3_act_helper_helper_80070040(ot, firstLineF4);
        sgtrect3_act_helper_helper_80070040(ot, secondLineF4);
        firstLineF4 += 2;
        secondLineF4 += 2;
    }

    sgtrect3_act_helper_helper_80070040(ot, &work->field_23B8_prim[GV_Clock_800AB920]);
}

void sgtrect3_act_helper_80070820(void *ot, LINE_F3 *lineF3Arr, LINE_F2 *lineF2Arr, DVECTOR *screenCoords,
                                  ushort currentOffset, unsigned int rgb)
{
    short sVar1;

    LINE_F3 *firstLineF3;
    LINE_F3 *secondLineF3;

    LINE_F2 *firstLineF2;
    LINE_F2 *secondLineF2;

    firstLineF3 = lineF3Arr;
    secondLineF3 = lineF3Arr + 1;
    *(unsigned int *)&lineF3Arr[0].r0 = rgb;
    *(unsigned int *)&lineF3Arr[1].r0 = rgb;
    setLineF3(firstLineF3);
    setLineF3(secondLineF3);
    setSemiTrans(firstLineF3, 1);
    setSemiTrans(secondLineF3, 1);

    firstLineF3->x0 = secondLineF3->x0 = secondLineF3->x1 = screenCoords->vx - currentOffset;
    firstLineF3->y0 = secondLineF3->y0 = firstLineF3->y1 = screenCoords->vy - currentOffset;
    firstLineF3->x2 = secondLineF3->x2 = firstLineF3->x1 = screenCoords->vx + currentOffset;
    firstLineF3->y2 = secondLineF3->y2 = secondLineF3->y1 = screenCoords->vy + currentOffset;
    sgtrect3_act_helper_helper_80070040(ot, firstLineF3);
    sgtrect3_act_helper_helper_80070040(ot, secondLineF3);

    firstLineF2 = lineF2Arr;
    secondLineF2 = lineF2Arr + 1;
    *(unsigned int *)&lineF2Arr[0].r0 = rgb;
    *(unsigned int *)&lineF2Arr[1].r0 = rgb;
    setLineF2(firstLineF2);
    setLineF2(secondLineF2);
    setSemiTrans(firstLineF2, 1);
    setSemiTrans(secondLineF2, 1);

    firstLineF2->x0 = firstLineF2->x1 = secondLineF2->x0 = secondLineF2->x1 = screenCoords->vx;

    sVar1 = ((currentOffset >> 2) << 2) + (currentOffset >> 2);
    firstLineF2->y0 = screenCoords->vy - sVar1;
    firstLineF2->y1 = screenCoords->vy - currentOffset;
    secondLineF2->y0 = screenCoords->vy + sVar1;
    secondLineF2->y1 = screenCoords->vy + currentOffset;
    sgtrect3_act_helper_helper_80070040(ot, firstLineF2);
    sgtrect3_act_helper_helper_80070040(ot, secondLineF2);

    firstLineF2 = lineF2Arr + 2;
    ++lineF2Arr;
    --lineF2Arr;
    while (0)
        ;
    secondLineF2 = lineF2Arr + 3;
    *(unsigned int *)&firstLineF2->r0 = rgb;
    *(unsigned int *)&secondLineF2->r0 = rgb;

    setLineF2(firstLineF2);
    setLineF2(secondLineF2);
    setSemiTrans(firstLineF2, 1);
    setSemiTrans(secondLineF2, 1);

    firstLineF2->y0 = firstLineF2->y1 = secondLineF2->y0 = secondLineF2->y1 = screenCoords->vy;
    firstLineF2->x0 = screenCoords->vx - sVar1;
    firstLineF2->x1 = screenCoords->vx - currentOffset;
    secondLineF2->x0 = screenCoords->vx + sVar1;
    secondLineF2->x1 = screenCoords->vx + currentOffset;
    sgtrect3_act_helper_helper_80070040(ot, firstLineF2);
    sgtrect3_act_helper_helper_80070040(ot, secondLineF2);
}

void sgtrect3_act_helper_80070AB0(SgtRect3Work *work, DVECTOR *screenCoordsArray, TARGET **inTargets,
                                  unsigned short *offsets)
{
    unsigned int  rgb;
    unsigned int *rgbFields;

    int            field_21B4;
    DVECTOR        screenCoords;
    int            targetCount;
    TARGET *field_30_target;
    TARGET *currentTarget;
    unsigned short currentOffset;

    void     *ot;
    LINE_F3  *lineF3Arr;
    LINE_F2  *lineF2Arr;
    DR_TPAGE *tPageArr;

    rgbFields = &work->field_28_rgb.rgbWord;
    targetCount = work->field_21AC_target_count;
    field_21B4 = work->field_21B4;
    lineF3Arr = work->field_3C[GV_Clock_800AB920].field_0;
    lineF2Arr = work->field_C3C[GV_Clock_800AB920].field_0;
    tPageArr = work->field_21B8[GV_Clock_800AB920].field_0;
    ot = DG_ChanlOTag(1);
    field_30_target = work->field_30_target;

    for (targetCount--; targetCount >= 0; screenCoordsArray++, inTargets++, offsets++, targetCount--)
    {
        currentOffset = *offsets;
        currentTarget = *inTargets;

        if ((currentTarget != field_30_target) || (field_21B4 == 0))
        {
            rgb = rgbFields[0];
        }
        else if ((((unsigned short)(screenCoordsArray->vx + 160) < 321) && (-113 < screenCoordsArray->vy)) &&
                 (screenCoordsArray->vy < 113))
        {
            rgb = rgbFields[1];
        }
        else
        {
            continue;
        }

        screenCoords = *screenCoordsArray;
        screenCoords.vx += 160;
        screenCoords.vy += 112;
        sgtrect3_act_helper_80070820(ot, lineF3Arr, lineF2Arr, &screenCoords, currentOffset, rgb);
        sgtrect3_act_helper_helper_80070040(ot, tPageArr);

        if ((currentTarget == field_30_target) && (field_21B4 != 0))
        {
            sgtrect3_act_helper_80070568(work, ot, lineF3Arr);
        }

        lineF3Arr += 2;
        lineF2Arr += 4;
        tPageArr++;
    }
}

extern int GV_PauseLevel_800AB928;

void sgtrect3_act_helper_80070CAC(SgtRect3Work *work)
{
    int     vecLen;
    SVECTOR vector2;
    SVECTOR vector;

    if (GV_PauseLevel_800AB928 != 0)
    {
        return;
    }
    if (work->field_21B4 == 0)
    {
        work->field_21B0++;
        if (!work->field_30_target)
        {
            return;
        }

        vector = (dword_8009F46C != 0) ? svector_8009F478 : GM_PlayerPosition_800ABA10;

        GV_SubVec3(&work->field_30_target->center, &vector, &vector2);
        vecLen = GV_VecLen3(&vector2);
        vecLen = (vecLen * 3) / 2000;
        if (vecLen == 0)
        {
            vecLen = 1;
        }
        if (work->field_21B0 % vecLen != 0)
        {
            return;
        }
    }
    else if (!work->field_30_target)
    {
        return;
    }
    GM_SeSet2_80032968(0, 0x3f, SE_STINGER_LOCKON);
}

extern TARGET *target_800BDF00;

void sgtrect3_act_80070E14(SgtRect3Work *work)
{
    DVECTOR    screenCoords[32];
    TARGET *targets[32];
    ushort     offsets[32];

    if (work->field_24 != *work->field_20)
    {
        GV_DestroyActor((GV_ACT *)work);
        return;
    }

    target_800BDF00 = NULL;
    sgtrect3_act_helper_8007009C();
    sgtrect3_act_helper_8007020C(work, screenCoords, targets, offsets);
    sgtrect3_act_helper_80070AB0(work, screenCoords, targets, offsets);
    sgtrect3_act_helper_80070CAC(work);
    target_800BDF00 = work->field_30_target;
}

void sgtrect3_kill_80070EC0(SgtRect3Work *actor_sgtrect3)
{
    byte_8009F5F8[0] = 0;
}

void sgtrect3_loader_helper_80070ECC(SgtRect3Work *work, unsigned int rgb)
{
    int      index;
    int      lineIndex;
    LINE_F4 *line;

    for (index = 0; index < 2; index++)
    {
        line = work->field_1C3C_lines[index].field_0;
        for (lineIndex = 0; lineIndex < 24; lineIndex++, line++)
        {
            *(unsigned int *)&line->r0 = rgb; // LCOPY() doesn't work here.
            setLineF4(line);
            setSemiTrans(line, 1);
        }
    }

    for (index = 0; index < 12; index++)
    {
        work->field_217C[index] = 0;
    }
}

int sgtrect3_loader_80070F4C(SgtRect3Work *work, unsigned int *rgb2)
{
    int       outerIndex;
    int       innerIndex;
    DR_TPAGE *tPageIter_21B8;
    DR_TPAGE *tPageIter_23B8;

    tPageIter_23B8 = &work->field_23B8_prim[0];

    for (outerIndex = 0; outerIndex < 2; outerIndex++, tPageIter_23B8++)
    {
        tPageIter_21B8 = work->field_21B8[outerIndex].field_0;

        for (innerIndex = 0; innerIndex < 32; innerIndex++, tPageIter_21B8++)
        {
            SetDrawTPage(tPageIter_21B8, 0, 1, 0);
        }

        SetDrawTPage(tPageIter_23B8, 0, 1, 32);
    }

    sgtrect3_loader_helper_80070ECC(work, rgb2[1]);

    return 0;
}

SgtRect3Work *NewSgtRect3_80071010(short *param_1, short param_2, unsigned int *rgb2, int param_4)
{
    SgtRect3Work *work;

    if (byte_8009F5F8[0])
    {
        return NULL;
    }

    work = (SgtRect3Work *)GV_NewActor(7, sizeof(SgtRect3Work));
    if (!work)
    {
        return NULL;
    }

    GV_SetNamedActor((GV_ACT *)work, (TActorFunction)sgtrect3_act_80070E14,
                     (TActorFunction)sgtrect3_kill_80070EC0, "sgtrect3.c");

    if (sgtrect3_loader_80070F4C(work, rgb2) < 0)
    {
        GV_DestroyActor((GV_ACT *)work);
        return NULL;
    }

    byte_8009F5F8[0] = 1;
    work->field_28_rgb.rgbWord = rgb2[0];
    work->field_2C_rgb.rgbWord = rgb2[1];
    work->field_20 = param_1;
    work->field_24 = param_2;

    if (amissile_alive_8009F490 == 0)
    {
        target_800BDF00 = NULL;
    }

    work->field_34_count = 0;
    work->field_38 = 0;
    work->field_21B4 = param_4;
    work->field_21B0 = 0;
    work->field_30_target = target_800BDF00;

    return work;
}
