#include "equip.h"

#include "common.h"
#include "libgv/libgv.h"
#include "Game/object.h"
#include "Game/map.h"
#include "Game/camera.h"
#include "Game/linkvarbuf.h"

extern int       DG_CurrentGroupID;
extern int       dword_8009F46C;
extern GM_Camera GM_Camera_800B77E8;

/*---------------------------------------------------------------------------*/

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

#define EXEC_LEVEL 6

/*---------------------------------------------------------------------------*/

STATIC void GasmaskAct(GasmaskWork *work)
{
    int map;

    map = work->control->map->index;
    DG_GroupObjs(work->object.objs, DG_CurrentGroupID);
    GM_CurrentMap = map;

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
            work->sight = NewGasmaskSight();
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

STATIC void GasmaskDie(GasmaskWork *work)
{
    GM_FreeObject((OBJECT *)&work->object);
    EQ_VisibleHead(work->parent, &work->saved_packs, &work->saved_raise);

    if (work->sight)
    {
        GV_DestroyOtherActor(work->sight);
    }
}

STATIC int GasmaskGetResources(GasmaskWork *work, OBJECT *parent, int num_parent)
{
    OBJECT_NO_ROTS *object = &work->object;

    work->parent = parent;
    work->num_parent = num_parent;

    work->time = 0;

    GM_InitObjectNoRots(object, GV_StrCode("gas_mask"), WEAPON_FLAG, 0);
    if (!work->object.objs)
    {
        return -1;
    }

    GM_ConfigObjectRoot((OBJECT *)object, parent, num_parent);
    GM_ConfigObjectLight((OBJECT *)object, parent->light);

    EQ_InvisibleHead(parent, &work->saved_packs, &work->saved_raise);

    work->sight = NULL;
    return 0;
}

/*---------------------------------------------------------------------------*/

GV_ACT *NewGasmask(CONTROL *control, OBJECT *parent, int num_parent)
{
    GasmaskWork *work = (GasmaskWork *)GV_NewActor(EXEC_LEVEL, sizeof(GasmaskWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)GasmaskAct,
                         (GV_ACTFUNC)GasmaskDie, "gasmask.c");

        if (GasmaskGetResources(work, parent, num_parent) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->control = control;
    }

    return (GV_ACT *)work;
}
