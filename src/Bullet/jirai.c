#include "jirai.h"
#include "libgcl/gcl.h"
#include "Game/object.h"
#include "libdg/libdg.h"
#include "chara/snake/sna_init.h"
#include "unknown.h"
#include "psyq.h"

// claymore (on ground)

extern const char aJiraiC[];

extern int         counter_8009F448;
extern int         dword_8009F444;
extern int         dword_8009F440;
extern GM_Control *gSnaControl_800AB9F4;

#pragma INCLUDE_ASM("asm/jirai_loader_helper_8006A798.s") // 348 bytes

extern int     GM_PlayerStatus_800ABA50;
extern SVECTOR svector_800ABA10;

int jirai_act_helper_8006A8F4(Actor_Jirai *pActor)
{
    int         local_10E;       // $v1
    GM_Control *p_field_20_ctrl; // $a0
    SVECTOR     v;

    if ((GM_PlayerStatus_800ABA50 & 0x40) == 0)
    {
        return 0;
    }

    local_10E = pActor->field_10E;
    p_field_20_ctrl = &pActor->field_20_ctrl;
    if (local_10E == 1)
    {
        return 0;
    }
    GV_SubVec3_80016D40(&p_field_20_ctrl->field_0_position, &svector_800ABA10, &v);
    return GV_VecLen3_80016D80(&v) < 800;
}

#pragma INCLUDE_ASM("asm/jirai_act_helper_8006A950.s") // 524 bytes
#pragma INCLUDE_ASM("asm/jirai_act_8006AB5C.s")        // 1280 bytes

extern Jirai_unknown stru_800BDE78[8];

// A different version of ExecProc is used here, which checks for a proccess ID less than zero.
#define ExecProc(proc_id, mode)            \
{                                          \
    GCL_ARGS args;                         \
    long data;                             \
                                           \
    if (proc_id < 0) goto skip;            \
                                           \
    args.argc = 1;                         \
    args.argv = &data;                     \
    data = mode;                           \
    do {} while (0);                       \
    GCL_ExecProc_8001FF2C(proc_id, &args); \
skip:                                      \
}

void jirai_kill_8006B05C(Actor_Jirai *pActor)
{
    sub_8007913C();
    GM_FreeControl_800260CC(&pActor->field_20_ctrl);
    GM_FreeObject_80034BF8(&pActor->field_9C_obj);
    GM_FreeTarget_8002D4B0(pActor->field_100_pTarget);

    if (pActor->field_13C_idx >= 0)
    {
        GM_ClearBulName_8004FBE4(pActor->field_20_ctrl.field_30_scriptData);
        stru_800BDE78[pActor->field_13C_idx].field_4_pActor = 0;
        counter_8009F448 = counter_8009F448 - 1;
    }

    ExecProc(pActor->field_138_gcl, pActor->field_134_gcl_arg);

    dword_8009F444 = 0;
    dword_8009F440 = 0;
}

extern SVECTOR svec_8009F44C;
extern SVECTOR svec_8009F454;
extern SVECTOR svec_8009F45C;
extern SVECTOR svec_8009F464;

int jirai_loader_helper_8006B124(Actor_Jirai *pActor, MATRIX *pMtx, int a3)
{
    GM_Target *pNewTarget;
    SVECTOR    v12;
    SVECTOR   *v8;

    pNewTarget = GM_AllocTarget_8002D400();
    pActor->field_100_pTarget = pNewTarget;
    if (!pNewTarget)
    {
        return -1;
    }

    if (a3)
    {
        v12 = svec_8009F45C;
    }
    else
    {
        v12 = svec_8009F464;
    }

    if (a3)
    {
        v8 = &svec_8009F454;
    }
    else
    {
        v8 = &svec_8009F44C;
    }

    if (GCL_GetParam_80020968('t'))
    {
        GCL_GetSV_80020A14(GCL_Get_Param_Result_80020AA4(), &v12);
    }
    GM_SetTarget_8002DC74(pNewTarget, 9, 0, &v12);
    pNewTarget->field_3C |= 2;
    DG_SetPos_8001BC44(pMtx);
    DG_PutVector_8001BE48(v8, &v12, 1);
    GM_Target_SetVector_8002D500(pNewTarget, &v12);
    pActor->field_10C = 8;
    pActor->field_10E = 0;
    return 0;
}

int jirai_get_free_item_8006B268()
{
    int i; // $v1
    for (i = 0; i < 8; i++)
    {
        if (!stru_800BDE78[i].field_4_pActor)
        {
            return i;
        }
    }
    return -1;
}

extern const char aClaymore_2[];

extern int dword_800ABA0C;

int jirai_loader_8006B2A4(Actor_Jirai *pActor, MATRIX *pMtx, GM_Target *pTarget)
{
    int            map;      // $v1
    GM_Control    *pCtrl;    // $s2
    Jirai_unknown *pUnknown; // $a0
    MATRIX         matrix;   // [sp+10h] [-20h] BYREF
    SVECTOR       *vec;
    OBJECT        *obj;

    map = dword_800ABA0C;
    pCtrl = &pActor->field_20_ctrl;
    pActor->field_138_gcl = -1;
    pActor->field_13C_idx = -1;
    GM_CurrentMap_800AB9B0 = map;
    pActor->field_14C = map;
    if (Res_Control_init_loader_8002599C(pCtrl, GM_Next_BulName_8004FBA0(), 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard_8002622C(pCtrl, 0, 0, 0);
    jirai_loader_helper_8006A798(&matrix, pMtx, pTarget);
    GM_ConfigControlMatrix_80026154(pCtrl, pMtx);
    pActor->field_144_vec.vy = ratan2_80094308(-matrix.m[0][0], -matrix.m[2][0]) & 4095;
    pActor->field_144_vec.vx = ratan2_80094308(matrix.m[1][0], 4096) & 4095;
    pActor->field_144_vec.vz = 0;
    GM_ConfigControlAttribute_8002623C(pCtrl, 0);
    obj = &pActor->field_9C_obj;
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)obj, GV_StrCode_80016CCC(aClaymore_2), 877, 0);
    if (!obj->objs)
    {
        return -1;
    }

    DG_SetPos2_8001BC8C(&pCtrl->field_0_position, &pActor->field_20_ctrl.field_8_rotator);
    DG_PutObjs_8001BDB8(obj->objs);
    GM_ConfigObjectLight_80034C44(obj, &pActor->field_C0_mtx);

    pActor->field_130 = 0;
    pActor->field_138_gcl = -1;
    pActor->field_134_gcl_arg = 0;
    pActor->field_140 = 0;

    if (jirai_loader_helper_8006B124(pActor, pMtx, 0) < 0)
    {
        return -1;
    }

    pActor->field_13C_idx = jirai_get_free_item_8006B268();
    if (pActor->field_13C_idx < 0)
    {
        return -1;
    }

    pUnknown = &stru_800BDE78[pActor->field_13C_idx];
    pUnknown->field_4_pActor = pActor;
    pUnknown->field_8_pCtrl = pCtrl;
    pUnknown->field_C_pTarget = pTarget;

    vec = &pActor->field_20_ctrl.field_3C;
    vec->vy = 2000;
    vec->vz = 1024;
    ++counter_8009F448;
    vec->vx = gSnaControl_800AB9F4->field_8_rotator.vy;
    return 0;
}

Actor_Jirai *NewJirai_8006B48C(DG_OBJ *pObj, GM_Target *pTarget)
{
    Actor_Jirai *pActor; // $s0

    if (counter_8009F448 == 8)
    {
        return 0;
    }

    pActor = (Actor_Jirai *)GV_NewActor_800150E4(5, sizeof(Actor_Jirai));
    if (pActor)
    {
        pActor->field_104_vec = gSnaControl_800AB9F4->field_8_rotator;
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)jirai_act_8006AB5C,
                                  (TActorFunction)jirai_kill_8006B05C, aJiraiC);

        if (jirai_loader_8006B2A4(pActor, &pObj->world, pTarget) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }
    }

    return pActor;
}

int jirai_loader_8006B564(Actor_Jirai *pActor, int _matrix, int where)
{
    MATRIX      matrix;
    GM_Control *ctrl;
    SVECTOR    *vec;
    OBJECT     *obj;

    pActor->field_14C = where;

    ctrl =  &pActor->field_20_ctrl;
    if (Res_Control_init_loader_8002599C(ctrl, GV_StrCode_80016CCC(aClaymore_2), where) < 0)
    {
        return -1;
    }

    GM_ConfigControlString_800261C0(ctrl, (char *)GCL_GetParam_80020968('p'), (char *)GCL_GetParam_80020968('d'));
    GM_ConfigControlHazard_8002622C(ctrl, 0, -2, -2);
    GM_ConfigControlAttribute_8002623C(ctrl, 0);

    pActor->field_144_vec = ctrl->field_8_rotator;
    obj = &pActor->field_9C_obj;
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)obj, GV_StrCode_80016CCC(aClaymore_2), 877, 0);
    GM_ConfigObjectLight_80034C44(obj, &pActor->field_C0_mtx);

    pActor->field_104_vec = ctrl->field_8_rotator;

    ctrl->field_8_rotator.vx = ctrl->field_4C_turn_vec.vx = -1024;
    ctrl->field_8_rotator.vy = ctrl->field_4C_turn_vec.vy += 1024;
    ctrl->field_0_position.vy += 500;

    DG_SetPos2_8001BC8C(&ctrl->field_0_position, &ctrl->field_8_rotator);

    ReadRotMatrix_80092DD8(&matrix);

    if (jirai_loader_helper_8006B124(pActor, &matrix, 1) < 0)
    {
        return -1;
    }

    ctrl->field_0_position.vy -= 500;
    obj->objs->flag |= 0x80;
    pActor->field_130 = 64;

    if (GCL_GetParam_80020968('e'))
    {
        pActor->field_138_gcl = GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        pActor->field_138_gcl = -1;
    }

    pActor->field_134_gcl_arg = 0;
    pActor->field_13C_idx = -1;
    pActor->field_140 = 0;

    vec = &ctrl->field_3C;
    vec->vy = 2000;
    vec->vz = 1024;
    vec->vx = ctrl->field_8_rotator.vy - 1024;

    return 0;
}

Actor *NewScenarioJirai_8006B76C(int a1, int where)
{
    Actor_Jirai *pActor = (Actor_Jirai *)GV_NewActor_800150E4(6, sizeof(Actor_Jirai));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)jirai_act_8006AB5C,
                                  (TActorFunction)jirai_kill_8006B05C, aJiraiC);
        if (jirai_loader_8006B564(pActor, a1, where) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }
    }
    return &pActor->field_0_actor;
}
