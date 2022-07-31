#include "shadow.h"

extern void GM_FreeObject_80034BF8(OBJECT *obj);

#pragma INCLUDE_ASM("asm/shadow_act_helper_8005FD28.s") // 768 bytes

MATRIX* RotMatrixY_80093BC8(long r, MATRIX *m);
int GV_NearExp8_800263E4(int arg0, int arg1);

void shadow_act_helper_80060028(Actor_Shadow *pActor)
{
    DG_OBJS *objs = pActor->field_28_obj.objs;
    RotMatrixY_80093BC8(pActor->field_20_ctrl->field_8_vec.vy, &objs->world);
    objs->world.t[0] = pActor->field_24_pObj->objs->world.t[0];
    objs->world.t[2] = pActor->field_24_pObj->objs->world.t[2];
    objs->world.t[1] = pActor->field_20_ctrl->field_78;

    if ( pActor->field_20_ctrl->field_0_position.vy - pActor->field_20_ctrl->field_78 < 450 )
    {
        objs->objs[0].raise = -500;
    } 
    else
    {
        objs->objs[0].raise = GV_NearExp8_800263E4(objs->objs[0].raise, 150);
    }
}

void shadow_act_helper_8005FD28(Actor_Shadow *pShadow); // dummy signature
void shadow_act_800600E4(Actor_Shadow *pActor)
{
    if ( (pActor->field_24_pObj->objs->flag & 0x80) != 0 || !pActor->field_90_bEnable )
    {
        pActor->field_28_obj.objs->flag |= 0x80u;
    }
    else
    {
        pActor->field_28_obj.objs->flag &= ~0x80u;
        shadow_act_helper_8005FD28(pActor);
        shadow_act_helper_80060028(pActor);
        DG_SetObjectGroupId(pActor->field_28_obj.objs,pActor->field_24_pObj->map_name);
    }
}


void shadow_kill_80060190(int param_1)
{
    GM_FreeObject_80034BF8((OBJECT *)(param_1 + 0x28));
}

#pragma INCLUDE_ASM("asm/shadow_loader_800601B0.s") // 284 bytes
#pragma INCLUDE_ASM("asm/shadow_init_800602CC.s") // 184 bytes
#pragma INCLUDE_ASM("asm/shadow_init2_80060384.s") // 104 bytes
