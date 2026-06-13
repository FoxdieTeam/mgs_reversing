#include "weapon.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "bullet/bakudan.h"
#include "game/game.h"
#include "linkvar.h"
#include "sound/g_sound.h"

extern void *GM_BombSeg;
extern int   bakudan_count_8009F42C;

/*---------------------------------------------------------------------------*/
// C4 Bomb

#define EXEC_LEVEL      GV_ACTOR_AFTER

#define C4BOMB_MODEL    GV_StrCode("c4_bomb")

#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                        | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

typedef struct _Work
{
    GV_ACT         actor;
    CONTROL       *root_ctrl;
    OBJECT        *root_obj;
    OBJECT_NO_ROTS object;
    int            unit;
    u_long        *flags;
    int            time;
    int            side;
} Work;

/*---------------------------------------------------------------------------*/

static void Act( Work *work )
{
    int ammo;
    u_long flags;
    MATRIX *world;
    DG_OBJS *root_obj;

    GM_CurrentMap = work->root_ctrl->map->index;
    DG_GroupObjsEx( work->object.objs );
    if ( work->root_obj->objs->flag & DG_FLAG_INVISIBLE )
    {
        DG_InvisibleObjs( work->object.objs );
    }
    else if ( work->time == 0 )
    {
        DG_VisibleObjs( work->object.objs );
    }

    ammo = GM_Weapons[ WP_C4 ];
    root_obj = work->root_obj->objs;
    world = &root_obj->objs[ work->unit ].world;

    flags = *work->flags;

    if ( ( flags & 1 ) && ( ammo > 0 ) && ( bakudan_count_8009F42C < 16 ) )
    {
        if ( flags & 2 )
        {
            if (NewBakudan(world, NULL, 0, work->side, GM_BombSeg))
            {
                GM_Weapons[ WP_C4 ] = --ammo;
                GM_SeSet( &work->root_ctrl->mov, SE_C4_PUT );
                work->time = 0x18;
                DG_InvisibleObjs( work->object.objs );
            }

        }
        else if ( flags & 4 )
        {
            GM_Weapons[ WP_C4 ] = --ammo;
            work->time = 0x18;
            DG_InvisibleObjs( work->object.objs );
        }
    }
    if ( ( work->time > 0 ) && ( --work->time == 0 ) )
    {
        DG_VisibleObjs( work->object.objs );
    }
    if ( ammo == 0 )
    {
        DG_InvisibleObjs( work->object.objs );
    }
}

static void Die(Work *work)
{
    GM_FreeObject((OBJECT *)&work->object);
}

static int GetResources(Work *work, OBJECT *root_obj, int unit)
{
    OBJECT_NO_ROTS *obj = &work->object;

    GM_InitObjectNoRots(obj, C4BOMB_MODEL, BODY_FLAG, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot((OBJECT *)obj, root_obj, unit);
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewBomb(CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *flags, int side)
{
    Work *work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "bomb.c");
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
        work->side = side;
    }

    GM_MagazineMax = 0;
    GM_Magazine = 0;

    return (void *)work;
}
