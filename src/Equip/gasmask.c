#include "gasmask.h"
#include "Game/object.h"
#include "map/map.h"
#include "unknown.h"
#include "Game/camera.h"
#include "Game/linkvarbuf.h"

extern const char aGasmaskC[];
extern const char aGasMask_DUP[];

extern int       DG_CurrentGroupID_800AB968;
extern int       dword_8009F46C;
extern GM_Camera GM_Camera_800B77E8;

void gasmask_act_800609C0(Actor_gasmask *pActor)
{
    int map;

    map = pActor->field_44_pCtrl->field_2C_map->field_0_map_index_bit;
    DG_GroupObjs(pActor->field_20_obj.objs, DG_CurrentGroupID_800AB968);
    GM_CurrentMap_800AB9B0 = map;
    if (pActor->field_48_pParent->objs->flag & DG_FLAG_INVISIBLE)
    {
        DG_InvisibleObjs(pActor->field_20_obj.objs);
    }
    else
    {
        DG_VisibleObjs(pActor->field_20_obj.objs);
    }

    if (GM_Camera_800B77E8.field_22 && (pActor->field_48_pParent->objs->flag & DG_FLAG_INVISIBLE) != 0 &&
        GM_CurrentWeaponId != WEAPON_STINGER &&
        GM_CurrentWeaponId != WEAPON_PSG1 && dword_8009F46C != 1)
    {
        pActor->field_50_count++;
        if (pActor->field_50_count >= 9 && !pActor->field_54_gmsight)
        {
            pActor->field_54_gmsight = NewGasmaskSight_80063668();
        }
    }
    else
    {
        pActor->field_50_count = 0;
        if (pActor->field_54_gmsight)
        {
            GV_DestroyOtherActor_800151D8(&pActor->field_54_gmsight->field_0_actor);
            pActor->field_54_gmsight = 0;
        }
    }
}

void gasmask_kill_80060B0C(Actor_gasmask *pActor)
{
    GM_FreeObject_80034BF8(&pActor->field_20_obj);
    EQ_VisibleHead_80060DF0(pActor->field_48_pParent, &pActor->field_5A_head_saved_packs,
                            &pActor->field_5C_head_saved_raise);


    if (pActor->field_54_gmsight)
    {
        GV_DestroyOtherActor_800151D8(&pActor->field_54_gmsight->field_0_actor);
    }
}

int gasmask_loader_80060B5C(Actor_gasmask *pActor, OBJECT *pChild, int unit)
{
    OBJECT *obj = &pActor->field_20_obj;

    pActor->field_48_pParent = pChild;
    pActor->field_4C_unit = unit;
    pActor->field_50_count = 0;
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)obj, GV_StrCode_80016CCC(aGasMask_DUP), WEAPON_FLAG, 0);
    if (!pActor->field_20_obj.objs)
    {
        return -1;
    }
    GM_ConfigObjectRoot_80034C5C(obj, pChild, unit);
    GM_ConfigObjectLight_80034C44(obj, pChild->light);
    EQ_InvisibleHead_80060D5C(pChild, &pActor->field_5A_head_saved_packs, &pActor->field_5C_head_saved_raise);
    pActor->field_54_gmsight = 0;
    return 0;
}

GV_ACT * NewGasmask_80060C14(CONTROL *pCtrl, OBJECT *pParent, int unit)
{
    Actor_gasmask *pActor = (Actor_gasmask *)GV_NewActor_800150E4(6, sizeof(Actor_gasmask));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)gasmask_act_800609C0,
                                  (TActorFunction)gasmask_kill_80060B0C, aGasmaskC);
        if (gasmask_loader_80060B5C(pActor, pParent, unit) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }
        pActor->field_44_pCtrl = pCtrl;
    }
    return &pActor->field_0_actor;
}
