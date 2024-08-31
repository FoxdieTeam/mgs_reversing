#include "gasmask.h"
#include "Equip/effect.h"
#include "Game/object.h"
#include "Game/map.h"
#include "Game/camera.h"
#include "Game/linkvarbuf.h"

extern int       DG_CurrentGroupID_800AB968;
extern int       dword_8009F46C;
extern GM_Camera GM_Camera_800B77E8;

void gasmask_act_800609C0(GasMaskWork *work)
{
    int map;

    map = work->control->map->index;
    DG_GroupObjs(work->field_20_obj.objs, DG_CurrentGroupID_800AB968);
    GM_CurrentMap_800AB9B0 = map;
    if (work->field_48_pParent->objs->flag & DG_FLAG_INVISIBLE)
    {
        DG_InvisibleObjs(work->field_20_obj.objs);
    }
    else
    {
        DG_VisibleObjs(work->field_20_obj.objs);
    }

    if (GM_Camera_800B77E8.field_22 && (work->field_48_pParent->objs->flag & DG_FLAG_INVISIBLE) != 0 &&
        GM_CurrentWeaponId != WEAPON_STINGER &&
        GM_CurrentWeaponId != WEAPON_PSG1 && dword_8009F46C != 1)
    {
        work->field_50_count++;
        if (work->field_50_count >= 9 && !work->field_54_gmsight)
        {
            work->field_54_gmsight = NewGasmaskSight_80063668();
        }
    }
    else
    {
        work->field_50_count = 0;
        if (work->field_54_gmsight)
        {
            GV_DestroyOtherActor(&work->field_54_gmsight->actor);
            work->field_54_gmsight = 0;
        }
    }
}

void gasmask_kill_80060B0C(GasMaskWork *work)
{
    GM_FreeObject_80034BF8((OBJECT *)&work->field_20_obj);
    EQ_VisibleHead_80060DF0(work->field_48_pParent, &work->field_5A_head_saved_packs,
                            &work->field_5C_head_saved_raise);


    if (work->field_54_gmsight)
    {
        GV_DestroyOtherActor(&work->field_54_gmsight->actor);
    }
}

int gasmask_loader_80060B5C(GasMaskWork *work, OBJECT *pChild, int unit)
{
    OBJECT_NO_ROTS *obj = &work->field_20_obj;

    work->field_48_pParent = pChild;
    work->field_4C_unit = unit;
    work->field_50_count = 0;
    GM_InitObjectNoRots_800349B0(obj, GV_StrCode("gas_mask"), WEAPON_FLAG, 0);
    if (!work->field_20_obj.objs)
    {
        return -1;
    }
    GM_ConfigObjectRoot_80034C5C((OBJECT *)obj, pChild, unit);
    GM_ConfigObjectLight_80034C44((OBJECT *)obj, pChild->light);
    EQ_InvisibleHead_80060D5C(pChild, &work->field_5A_head_saved_packs, &work->field_5C_head_saved_raise);
    work->field_54_gmsight = 0;
    return 0;
}

GV_ACT * NewGasmask_80060C14(CONTROL *pCtrl, OBJECT *pParent, int unit)
{
    GasMaskWork *work = (GasMaskWork *)GV_NewActor(6, sizeof(GasMaskWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)gasmask_act_800609C0,
                         (TActorFunction)gasmask_kill_80060B0C, "gasmask.c");
        if (gasmask_loader_80060B5C(work, pParent, unit) < 0)
        {
            GV_DestroyActor(&work->actor);
            return 0;
        }
        work->control = pCtrl;
    }
    return &work->actor;
}
