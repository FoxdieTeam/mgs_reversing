#include "gasmask.h"
#include "gmsight.h"
#include "Equip/effect.h"
#include "Game/object.h"
#include "Game/map.h"
#include "Game/camera.h"
#include "Game/linkvarbuf.h"

typedef struct GasmaskWork
{
    GV_ACT         actor;
    OBJECT_NO_ROTS object;
    CONTROL       *control;
    OBJECT        *parent;
    int            num_parent;
    int            time;
    GV_ACT        *sight;
    short          unused;
    short          saved_packs;
    short          saved_raise;
} GasmaskWork;

extern int       DG_CurrentGroupID_800AB968;
extern int       dword_8009F46C;
extern GM_Camera GM_Camera_800B77E8;

void GasmaskAct_800609C0(GasmaskWork *work)
{
    int map;

    map = work->control->map->index;
    DG_GroupObjs(work->object.objs, DG_CurrentGroupID_800AB968);
    GM_CurrentMap_800AB9B0 = map;

    if (work->parent->objs->flag & DG_FLAG_INVISIBLE)
    {
        DG_InvisibleObjs(work->object.objs);
    }
    else
    {
        DG_VisibleObjs(work->object.objs);
    }

    if (GM_Camera_800B77E8.first_person &&
        (work->parent->objs->flag & DG_FLAG_INVISIBLE) &&
        GM_CurrentWeaponId != WEAPON_STINGER &&
        GM_CurrentWeaponId != WEAPON_PSG1 &&
        dword_8009F46C != 1)
    {
        work->time++;
        if (work->time >= 9 && !work->sight)
        {
            work->sight = NewGmsight_80063668();
        }
    }
    else
    {
        work->time = 0;

        if (work->sight)
        {
            GV_DestroyOtherActor(work->sight);
            work->sight = NULL;
        }
    }
}

void GasmaskKill_80060B0C(GasmaskWork *work)
{
    GM_FreeObject_80034BF8((OBJECT *)&work->object);
    EQ_VisibleHead_80060DF0(work->parent, &work->saved_packs, &work->saved_raise);

    if (work->sight)
    {
        GV_DestroyOtherActor(work->sight);
    }
}

int GasmaskGetResources_80060B5C(GasmaskWork *work, OBJECT *parent, int num_parent)
{
    OBJECT_NO_ROTS *object = &work->object;

    work->parent = parent;
    work->num_parent = num_parent;

    work->time = 0;

    GM_InitObjectNoRots_800349B0(object, GV_StrCode("gas_mask"), WEAPON_FLAG, 0);
    if (!work->object.objs)
    {
        return -1;
    }

    GM_ConfigObjectRoot_80034C5C((OBJECT *)object, parent, num_parent);
    GM_ConfigObjectLight_80034C44((OBJECT *)object, parent->light);

    EQ_InvisibleHead_80060D5C(parent, &work->saved_packs, &work->saved_raise);

    work->sight = NULL;
    return 0;
}

GV_ACT * NewGasmask_80060C14(CONTROL *control, OBJECT *parent, int num_parent)
{
    GasmaskWork *work = (GasmaskWork *)GV_NewActor(6, sizeof(GasmaskWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)GasmaskAct_800609C0,
                         (TActorFunction)GasmaskKill_80060B0C, "gasmask.c");

        if (GasmaskGetResources_80060B5C(work, parent, num_parent) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->control = control;
    }

    return (GV_ACT *)work;
}
