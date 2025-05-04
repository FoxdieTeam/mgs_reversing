#include "weapon.h"

#include "common.h"
#include "Bullet/bakudan.h"
#include "Game/object.h"
#include "linkvar.h"
#include "Game/map.h"
#include "SD/g_sound.h"

extern int   DG_CurrentGroupID;
extern void *GM_BombSeg;
extern int   bakudan_count_8009F42C;

/*---------------------------------------------------------------------------*/
// C4 Bomb

typedef struct _BombWork
{
    GV_ACT         actor;
    CONTROL       *control;
    OBJECT        *parent;
    OBJECT_NO_ROTS object;
    int            num_parent;
    int           *flags;
    int            f54;
    int            which_side;
} BombWork;

#define EXEC_LEVEL GV_ACTOR_AFTER
#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE | DG_FLAG_ONEPIECE )

/*---------------------------------------------------------------------------*/

STATIC void BombAct( BombWork *work )
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

STATIC void BombDie(BombWork *work)
{
    GM_FreeObject((OBJECT *)&work->object);
}

STATIC int BombGetResources(BombWork *work, OBJECT *parent, int num_parent)
{
    OBJECT_NO_ROTS *obj = &work->object;

    GM_InitObjectNoRots(obj, GV_StrCode("c4_bomb"), BODY_FLAG, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot((OBJECT *)obj, parent, num_parent);
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewBomb(CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side)
{
    BombWork *work = GV_NewActor(EXEC_LEVEL, sizeof(BombWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, BombAct, BombDie, "bomb.c");
        if (BombGetResources(work, parent, num_parent) < 0)
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
