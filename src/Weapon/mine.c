#include "weapon.h"

#include "common.h"
#include "Game/map.h"
#include "Game/target.h"
#include "Game/object.h"
#include "Bullet/jirai.h"
#include "Game/linkvarbuf.h"
#include "SD/g_sound.h"

extern short      GM_Magazine_800AB9EC;
extern short      GM_MagazineMax_800ABA2C;

extern int        GM_CurrentMap;
extern int        DG_CurrentGroupID;
extern int        counter_8009F448;
extern void      *GM_BombSeg;

/*---------------------------------------------------------------------------*/
// Claymore Mine

typedef struct MineWork
{
    GV_ACT         actor;
    CONTROL       *control;
    OBJECT        *parent;
    OBJECT_NO_ROTS object;
    int            num_parent;
    int           *flags;
    int            counter;
} MineWork;

#define EXEC_LEVEL GV_ACTOR_AFTER

/*---------------------------------------------------------------------------*/

STATIC void MineAct(MineWork *work)
{
    int map; // $v1
    int weapon_state; // $s1
    int weap_flags; // $a0
    int local_54; // $v0
    DG_OBJ *obj;

    map = work->control->map->index;
    DG_GroupObjs(work->object.objs, DG_CurrentGroupID);

    GM_CurrentMap = map;
    if ( (work->parent->objs->flag & DG_FLAG_INVISIBLE) != 0 )
    {
        DG_InvisibleObjs(work->object.objs);
    }
    else if ( !work->counter )
    {
        DG_VisibleObjs(work->object.objs);
    }
    obj = &work->parent->objs->objs[work->num_parent];

    weapon_state = GM_Weapons[ WEAPON_CLAYMORE ];
    weap_flags = *work->flags;

    if ((weap_flags & 1) != 0
      && weapon_state > 0
      && (weap_flags & 2) != 0
      && counter_8009F448 < 8
      && NewJirai(&obj->world, GM_BombSeg))
    {
        GM_SeSet(&work->control->mov, SE_C4_PUT);
        GM_Weapons[ WEAPON_CLAYMORE ] = --weapon_state;

        work->counter = 21;
        DG_InvisibleObjs(work->object.objs);
    }

    local_54 = work->counter;

    //new_54 = local_54 - 1;
    if ( local_54 > 0 )
    {
        work->counter = local_54 - 1;
        if ( !work->counter )
        {
            DG_VisibleObjs(work->object.objs);
        }
    }
    if ( !weapon_state )
    {
        DG_InvisibleObjs(work->object.objs);
    }
}

STATIC void MineDie(MineWork *work)
{
    GM_FreeObject((OBJECT *)&work->object);
}

STATIC int MineGetResources(MineWork *work, OBJECT *parent, int num_parent)
{
    OBJECT_NO_ROTS *obj = &work->object;

    int id = GV_StrCode("claymore");
    GM_InitObjectNoRots(obj, id, 0x36d, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot((OBJECT *)obj, parent, num_parent);
    return 0;
}

/*---------------------------------------------------------------------------*/

GV_ACT *NewMine(CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side)
{
    MineWork *work = (MineWork *)GV_NewActor(EXEC_LEVEL, sizeof(MineWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)MineAct,
                         (GV_ACTFUNC)MineDie, "mine.c");
        if (MineGetResources(work, parent, num_parent) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->control = control;
        work->parent = parent;
        work->num_parent = num_parent;
        work->flags = flags;
        work->counter = 0;
    }

    GM_MagazineMax_800ABA2C = 0;
    GM_Magazine_800AB9EC = 0;

    return &work->actor;
}
