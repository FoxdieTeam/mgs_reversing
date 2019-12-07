#include "linker.h"
#include "GM_Control.h"
#include "gcl.h"

void DG_MatrixRotYXZ_8001E734(MATRIX *pMatrix, SVECTOR *pVector);

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
