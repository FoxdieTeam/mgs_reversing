#include "shadow.h"
#include "Game/object.h"
#include "psyq.h"

// https://decomp.me/scratch/rSxGN
#pragma INCLUDE_ASM("asm/shadow_act_helper_8005FD28.s") // 768 bytes

void shadow_act_helper_80060028(Actor_Shadow *pActor)
{
    DG_OBJS *objs = pActor->field_28_obj.objs;
    RotMatrixY_80093BC8(pActor->field_20_ctrl->field_8_rotator.vy, &objs->world);
    objs->world.t[0] = pActor->field_24_pObj->objs->world.t[0];
    objs->world.t[2] = pActor->field_24_pObj->objs->world.t[2];
    objs->world.t[1] = pActor->field_20_ctrl->field_78;

    if (pActor->field_20_ctrl->field_0_position.vy - pActor->field_20_ctrl->field_78 < 450)
    {
        objs->objs[0].raise = -500;
    }
    else
    {
        objs->objs[0].raise = GV_NearExp8_800263E4(objs->objs[0].raise, 150);
    }
}

void shadow_act_800600E4(Actor_Shadow *pActor)
{
    if ((pActor->field_24_pObj->objs->flag & DG_FLAG_INVISIBLE) != 0 || !pActor->field_90_bEnable)
    {
        DG_InvisibleObjs(pActor->field_28_obj.objs);
    }
    else
    {
        DG_VisibleObjs(pActor->field_28_obj.objs);
        shadow_act_helper_8005FD28(pActor);
        shadow_act_helper_80060028(pActor);
        DG_GroupObjs(pActor->field_28_obj.objs, pActor->field_24_pObj->map_name);
    }
}

void shadow_kill_80060190(Actor_Shadow *pActor)
{
    GM_FreeObject_80034BF8(&pActor->field_28_obj);
}

extern char aKage[];     // = "kage"
extern char aShadow_0[]; // = "shadow"

int shadow_loader_800601B0(Actor_Shadow *pActor, GM_Control *pCtrl, OBJECT *pObj, Shadow_94 field_94)
{
    int map_name;

    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)&pActor->field_28_obj, GV_StrCode_80016CCC(aKage), 0x16d, 0);
    GM_ConfigObjectLight_80034C44(&pActor->field_28_obj, &pActor->field_4C_mtx);

    map_name = pObj->map_name;

    pActor->field_28_obj.objs->group_id = map_name;
    pActor->field_4C_mtx.m[1][1] = -0x1000;
    pActor->field_6E = 0x480;
    pActor->field_74 = 0x480;
    pActor->field_7A = 0x480;
    pActor->field_4C_mtx.t[0] = 0;
    pActor->field_4C_mtx.t[1] = 0;
    pActor->field_4C_mtx.t[2] = 0;
    pActor->field_28_obj.objs->objs->model->flags_0 |= 2;
    *pActor->field_28_obj.objs->objs->model->materialOffset_50 = GV_StrCode_80016CCC(aShadow_0);
    pActor->field_20_ctrl = pCtrl;
    pActor->field_24_pObj = pObj;
    pActor->field_94 = field_94;
    pActor->field_8C = 0x2c484848;
    pActor->field_90_bEnable = 1;
    return 0;
}

extern const char aShadowC[]; // = "shadow.c"

Actor_Shadow *shadow_init_800602CC(GM_Control *pCtrl, OBJECT *pObj, Shadow_94 field_94)
{
    Actor_Shadow *pActor;

    pActor = (Actor_Shadow *)GV_NewActor_800150E4(5, sizeof(Actor_Shadow));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)shadow_act_800600E4,
                                  (TActorFunction)shadow_kill_80060190, aShadowC);
        if (shadow_loader_800601B0(pActor, pCtrl, pObj, field_94) >= 0)
        {
            return pActor;
        }
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
    }
    return NULL;
}

Actor_Shadow *shadow_init2_80060384(GM_Control *pCtrl, OBJECT *pObj, Shadow_94 field_94, int **field_90_bEnable)
{
    Actor_Shadow *pActor;

    pActor = shadow_init_800602CC(pCtrl, pObj, field_94);
    if (pActor && field_90_bEnable)
    {
        *field_90_bEnable = &pActor->field_90_bEnable;
    }
    return pActor;
}
