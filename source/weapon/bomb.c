#include "weapon.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "bullet/bakudan.h"
#include "game/object.h"
#include "linkvar.h"
#include "game/map.h"
#include "sd/g_sound.h"

extern int   DG_CurrentGroupID;
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
    CONTROL       *control;
    OBJECT        *parent;
    OBJECT_NO_ROTS object;
    int            num_parent;
    int           *flags;
    int            f54;
    int            which_side;
} Work;

/*---------------------------------------------------------------------------*/

static void Act( Work *work )
{
    int ammo;
    int flags;
    MATRIX *world;
    DG_OBJS *parent;

    GM_CurrentMap = work->control->map->index;
    DG_GroupObjs( work->object.objs, DG_CurrentGroupID );
    if ( work->parent->objs->flag & DG_FLAG_INVISIBLE )
    {
        DG_InvisibleObjs( work->object.objs );
    }
    else if ( work->f54 == 0 )
    {
        DG_VisibleObjs( work->object.objs );
    }

    ammo = GM_Weapons[ WP_C4 ];
    parent = work->parent->objs;
    world = &parent->objs[ work->num_parent ].world;

    flags = *work->flags;

    if ( ( flags & 1 ) && ( ammo > 0 ) && ( bakudan_count_8009F42C < 16 ) )
    {
        if ( flags & 2 )
        {
            if (NewBakudan(world, NULL, 0, work->which_side, GM_BombSeg))
            {
                GM_Weapons[ WP_C4 ] = --ammo;
                GM_SeSet( &work->control->mov, SE_C4_PUT );
                work->f54 = 0x18;
                DG_InvisibleObjs( work->object.objs );
            }

        }
        else if ( flags & 4 )
        {
            GM_Weapons[ WP_C4 ] = --ammo;
            work->f54 = 0x18;
            DG_InvisibleObjs( work->object.objs );
        }
    }
    if ( ( work->f54 > 0 ) && ( --work->f54 == 0 ) )
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

static int GetResources(Work *work, OBJECT *parent, int num_parent)
{
    OBJECT_NO_ROTS *obj = &work->object;

    GM_InitObjectNoRots(obj, C4BOMB_MODEL, BODY_FLAG, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot((OBJECT *)obj, parent, num_parent);
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewBomb(CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side)
{
    Work *work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "bomb.c");
        if (GetResources(work, parent, num_parent) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->control = control;
        work->parent = parent;
        work->num_parent = num_parent;
        work->flags = flags;
        work->f54 = 0;
        work->which_side = which_side;
    }

    GM_MagazineMax = 0;
    GM_Magazine = 0;

    return (void *)work;
}
