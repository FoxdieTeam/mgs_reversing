#include "bomb.h"
#include "Bullet/bakudan.h"
#include "Game/object.h"
#include "Game/linkvarbuf.h"
#include "Game/map.h"
#include "SD/g_sound.h"

// c4 (in hands)

extern short GM_Magazine_800AB9EC;
extern short GM_MagazineMax_800ABA2C;

extern int   DG_CurrentGroupID_800AB968;
extern void *GM_BombSeg_800ABBD8;
extern int   GM_CurrentMap_800AB9B0;
extern int   bakudan_count_8009F42C;

void bomb_act_8006788C( BombWork *actor )
{
    int ammo;
    int f50;
    MATRIX *world;
    DG_OBJS *parent;

    GM_CurrentMap_800AB9B0 = actor->control->map->index;
    DG_GroupObjs( actor->f28_obj.objs, DG_CurrentGroupID_800AB968 );
    if ( actor->parent_obj->objs->flag & DG_FLAG_INVISIBLE )
    {
        DG_InvisibleObjs( actor->f28_obj.objs );
    }
    else if ( actor->f54 == 0 )
    {
        DG_VisibleObjs( actor->f28_obj.objs );
    }

    ammo = GM_Weapons[ WEAPON_C4 ];
    parent = actor->parent_obj->objs;
    world = &parent->objs[ actor->num_parent ].world;

    f50 = *actor->f50;

    if ( ( f50 & 1 ) && ( ammo > 0 ) && ( bakudan_count_8009F42C < 16 ) )
    {
        if ( f50 & 2 )
        {
            if (NewBakudan_8006A6CC(
                world,
                NULL,
                0,
                actor->f58,
                GM_BombSeg_800ABBD8))
            {
                GM_Weapons[ WEAPON_C4 ] = --ammo;
                GM_SeSet_80032858( &actor->control->mov, SE_C4_PUT );
                actor->f54 = 0x18;
                DG_InvisibleObjs(  actor->f28_obj.objs );
            }

        }
        else if ( f50 & 4 )
        {
            GM_Weapons[ WEAPON_C4 ] = --ammo;
            actor->f54 = 0x18;
            DG_InvisibleObjs(  actor->f28_obj.objs );
        }
    }
    if ( ( actor->f54 > 0 ) && ( --actor->f54 == 0 ) )
    {
        DG_VisibleObjs(  actor->f28_obj.objs );
    }
    if ( ammo == 0 )
    {
        DG_InvisibleObjs(  actor->f28_obj.objs );
    }
}

void bomb_kill_80067A74(BombWork *actor)
{
    GM_FreeObject_80034BF8((OBJECT *)&actor->f28_obj);
}

int bomb_loader_80067A94(BombWork *actor_bomb, OBJECT *parent_obj, int num_parent)
{
    OBJECT_NO_ROTS *obj = &actor_bomb->f28_obj;

    GM_InitObjectNoRots_800349B0(obj, GV_StrCode("c4_bomb"), WEAPON_FLAG, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot_80034C5C((OBJECT *)obj, parent_obj, num_parent);
    return 0;
}

GV_ACT *NewBomb_80067B20(CONTROL *ctrl, OBJECT *parent_obj, int num_parent, unsigned int *a4, int a5)
{
    BombWork *actor = (BombWork *)GV_NewActor(6, sizeof(BombWork));
    if (actor)
    {
        GV_SetNamedActor(&actor->actor, (TActorFunction)bomb_act_8006788C,
                         (TActorFunction)bomb_kill_80067A74, "bomb.c");
        if (bomb_loader_80067A94(actor, parent_obj, num_parent) < 0)
        {
            GV_DestroyActor(&actor->actor);
            return 0;
        }

        actor->control = ctrl;
        actor->parent_obj = parent_obj;
        actor->num_parent = num_parent;
        actor->f50 = a4;
        actor->f54 = 0;
        actor->f58 = a5;
    }

    GM_MagazineMax_800ABA2C = 0;
    GM_Magazine_800AB9EC = 0;

    return &actor->actor;
}
