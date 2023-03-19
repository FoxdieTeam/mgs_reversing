#include "linker.h"
#include "control.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "libdg/libdg.h"
#include "game.h"

void GM_FreeControl_800260CC(CONTROL *pControl)
{
    if (pControl->field_30_scriptData)
    {
        GM_ControlRemove_80025904(pControl);
    }
}

void GM_ConfigControlVector_800260FC(CONTROL *pControl, SVECTOR *pVec1, SVECTOR *pVec2)
{
    if (pVec1)
    {
        pControl->field_0_mov = *pVec1;
    }

    if (pVec2)
    {
        pControl->field_8_rotator = *pVec2;
    }
}

void GM_ConfigControlMatrix_80026154(CONTROL *pControl, MATRIX *pMatrix)
{
    pControl->field_0_mov.vx = pMatrix->t[0];
    pControl->field_0_mov.vy = pMatrix->t[1];
    pControl->field_0_mov.vz = pMatrix->t[2];

    DG_MatrixRotYXZ_8001E734(pMatrix, &pControl->field_8_rotator);

    pControl->field_4C_turn_vec = pControl->field_8_rotator;
}

void GM_ConfigControlString_800261C0(CONTROL *pControl, char *param_pos, char *param_dir)
{
    if (param_pos)
    {
        GCL_GetSV_80020A14(param_pos, &pControl->field_0_mov);
    }

    if (param_dir)
    {
        GCL_GetSV_80020A14(param_dir, &pControl->field_8_rotator);
    }

    pControl->field_4C_turn_vec = pControl->field_8_rotator;
}

void GM_ConfigControlHazard_8002622C(CONTROL *pControl, short height, short f36, short f38)
{
    pControl->field_32_height = height;
    pControl->field_36 = f36;
    pControl->field_38 = f38;
}

void GM_ConfigControlAttribute_8002623C(CONTROL *pControl, short f3a)
{
    pControl->field_3A = f3a;
}

void GM_ConfigControlInterp_80026244(CONTROL *pControl, char f5a)
{
    pControl->field_54 = f5a;
}

int GM_CheckControlTouches_8002624C(CONTROL *pControl, int param_2)
{
    if (pControl->field_58 == 0)
    {
        return 0;
    }

    if (pControl->field_58 == 2)
    {
        if (pControl->field_70[1]->pad < 0 || GV_VecLen3_80016D80(&pControl->field_60_vecs_ary[1]) <= param_2)
        {
            return 2;
        }
    }

    if (pControl->field_70[0]->pad < 0 || GV_VecLen3_80016D80(&pControl->field_60_vecs_ary[0]) <= param_2)
    {
        return 1;
    }

    return 0;
}

void GM_ConfigControlRadarparam_800262EC(CONTROL *pControl, short param_2, short param_3, short param_4,
                                         short param_5)
{
    SVECTOR *pVec;

    pVec = &pControl->field_3C;
    pVec->vx = param_2;
    pVec->vy = param_3;
    pVec->vz = param_4;
    pVec->pad = param_5;
}

void GM_ConfigControlTrapCheck_80026308(CONTROL *pControl)
{
    pControl->field_55_skip_flag &= ~CONTROL_FLAG_UNK2;
}
