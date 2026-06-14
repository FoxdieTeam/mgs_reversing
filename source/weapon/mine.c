#include "weapon.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "bullet/jirai.h"
#include "linkvar.h"
#include "sound/g_sound.h"

extern int        counter_8009F448;
extern void      *GM_BombSeg;

/*---------------------------------------------------------------------------*/
// Claymore Mine

#define EXEC_LEVEL      GV_ACTOR_AFTER

#define CLAYMORE_MODEL  GV_StrCode("claymore")

#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                        | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE \
                        | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )

typedef struct _Work
{
    GV_ACT         actor;
    CONTROL       *root_ctrl;
    OBJECT        *root_obj;
    OBJECT_NO_ROTS object;
    int            unit;
    u_long        *flags;
    int            time;
} Work;

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    int map;
    int weapon_state;
    int weapon_flags;
    int local_54;
    DG_OBJ *obj;

    map = work->root_ctrl->map->index;
    DG_GroupObjsEx(work->object.objs);

    GM_CurrentMap = map;
    if ( (work->root_obj->objs->flag & DG_FLAG_INVISIBLE) != 0 )
    {
        DG_InvisibleObjs(work->object.objs);
    }
    else if ( !work->time )
    {
        DG_VisibleObjs(work->object.objs);
    }
    obj = &work->root_obj->objs->objs[work->unit];

    weapon_state = GM_Weapons[ WP_Claymore ];
    weapon_flags = *work->flags;

    if ((weapon_flags & 1) != 0
      && weapon_state > 0
      && (weapon_flags & 2) != 0
      && counter_8009F448 < 8
      && NewJirai(&obj->world, GM_BombSeg))
    {
        GM_SeSet(&work->root_ctrl->mov, SE_C4_PUT);
        GM_Weapons[ WP_Claymore ] = --weapon_state;

        work->time = 21;
        DG_InvisibleObjs(work->object.objs);
    }

    local_54 = work->time;

    //new_54 = local_54 - 1;
    if ( local_54 > 0 )
    {
        work->time = local_54 - 1;
        if ( !work->time )
        {
            DG_VisibleObjs(work->object.objs);
        }
    }
    if ( !weapon_state )
    {
        DG_InvisibleObjs(work->object.objs);
    }
}

static void Die(Work *work)
{
    GM_FreeObject((OBJECT *)&work->object);
}

static int GetResources(Work *work, OBJECT *root_obj, int unit)
{
    OBJECT_NO_ROTS *obj = &work->object;

    GM_InitObjectNoRots(obj, CLAYMORE_MODEL, BODY_FLAG, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot((OBJECT *)obj, root_obj, unit);
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewMine(CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *flags, int side)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "mine.c");
        if (GetResources(work, root_obj, unit) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->root_ctrl = root_ctrl;
        work->root_obj = root_obj;
        work->unit = unit;
        work->flags = flags;
        work->time = 0;
    }

    GM_MagazineMax = 0;
    GM_Magazine = 0;

    return (void *)work;
}
