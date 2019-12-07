#include "linker.h"
#include "GM_Control.h"
#include "gcl.h"

void GM_ControlRemove_80025904(Res_Control *pControl);

void DG_MatrixRotYXZ_8001E734(MATRIX *pMatrix, SVECTOR *pVector);

void GM_Control_RemoveIfScriptData_800260CC(Res_Control *pControl)
{
    if (pControl->field_30_scriptData)
    {
        GM_ControlRemove_80025904(pControl);
    }
}

void GM_Control_SetVectors_800260FC(Res_Control *pControl, SVECTOR *pVec1, SVECTOR *pVec2)
{
    if (pVec1)
    {
        pControl->field_0_vec = *pVec1;
    }

    if (pVec2)
    {
        pControl->field_8_vec = *pVec2;
    }
}

void GM_Control_RotateByMatrix_80026154(Res_Control *pControl, MATRIX *pMatrix)
{
    pControl->field_0_vec.vx = pMatrix->t[0];
    pControl->field_0_vec.vy = pMatrix->t[1];
    pControl->field_0_vec.vz = pMatrix->t[2];

    DG_MatrixRotYXZ_8001E734(pMatrix, &pControl->field_8_vec);

    pControl->field_4C_turn_vec = pControl->field_8_vec;
}

void GM_ConfigControl_SetVectorsGCL_800261C0(Res_Control *pControl, char *bReadVec1, char *bReadVec2)
{
    if (bReadVec1)
    {
        GCL_ReadVector_80020A14(bReadVec1, &pControl->field_0_vec.vx);
    }

    if (bReadVec2)
    {
        GCL_ReadVector_80020A14(bReadVec2, &pControl->field_8_vec.vx);
    }

    pControl->field_4C_turn_vec = pControl->field_8_vec;
}

void GM_ConfigControlHazard_8002622C(Res_Control *pControl, short height, short f36, short f38)
{
    pControl->field_32_height = height;
    pControl->field_36 = f36;
    pControl->field_38 = f38;
}

void GM_ConfigControlAttribute_8002623C(Res_Control *pControl, short f3a)
{
    pControl->field_3A = f3a;
}

void GM_ConfigControl_F5A_80026244(Res_Control *pControl, char f5a)
{
    pControl->field_54 = f5a;
}

int sub_80016D80(SVECTOR *pVec);

int GM_CheckControlTouches_8002624C(Res_Control *pControl, int param_2)
{
    if (pControl->field_58 == 0)
    {
        return 0;
    }

    if (pControl->field_58 == 2)
    {
        if (pControl->field_70[1]->pad < 0 || sub_80016D80(&pControl->field_60_vecs_ary[1]) <= param_2)
        {
            return 2;
        }
    }

    if (pControl->field_70[0]->pad < 0 || sub_80016D80(&pControl->field_60_vecs_ary[0]) <= param_2)
    {
        return 1;
    }

    return 0;
}

void GM_Control_Set_Unknown_800262EC(Res_Control *pControl, short param_2, short param_3, short param_4, short param_5)
{
    SVECTOR* pVec ;
    pVec = &pControl->field_3C;
    pVec->vx = param_2;
    pVec->vy = param_3;
    pVec->vz = param_4;
    pVec->pad = param_5;
}

void GM_Control_UnSetFlag2_80026308(Res_Control *pControl)
{
    pControl->field_55_flags &= ~0x02;
}
