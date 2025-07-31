#include "equip.h"

#include "common.h"
#include "libgv/libgv.h"
#include "game/object.h"
#include "game/map.h"
#include "game/camera.h"
#include "linkvar.h"

extern int       DG_CurrentGroupID;
extern int       dword_8009F46C;
extern GM_Camera GM_Camera_800B77E8;

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL      GV_ACTOR_AFTER
#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE | DG_FLAG_ONEPIECE )

#define GASMASK_MODEL   GV_StrCode("gas_mask")

typedef struct _Work
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
} Work;

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
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
        GM_CurrentWeaponId != WP_Stinger &&
        GM_CurrentWeaponId != WP_Rifle &&
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

static void Die(Work *work)
{
    GM_FreeObject((OBJECT *)&work->object);
    EQ_VisibleHead(work->parent, &work->saved_packs, &work->saved_raise);

    if (work->sight)
    {
        GV_DestroyOtherActor(work->sight);
    }
}

static int GetResources(Work *work, OBJECT *parent, int num_parent)
{
    OBJECT_NO_ROTS *object = &work->object;

    work->parent = parent;
    work->num_parent = num_parent;

    work->time = 0;

    GM_InitObjectNoRots(object, GASMASK_MODEL, BODY_FLAG, 0);
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

void *NewGasMask(CONTROL *control, OBJECT *parent, int num_parent)
{
    Work *work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "gasmask.c");

        if (GetResources(work, parent, num_parent) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->control = control;
    }

    return (void *)work;
}
