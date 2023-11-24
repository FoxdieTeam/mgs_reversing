#include "mine.h"
#include "Game/map.h"
#include "Game/target.h"
#include "Game/object.h"
#include "Bullet/jirai.h"
#include "Game/linkvarbuf.h"

// claymore (in hands)

extern short      GM_Magazine_800AB9EC;
extern short      GM_MagazineMax_800ABA2C;

extern int        GM_CurrentMap_800AB9B0;
extern int        DG_CurrentGroupID_800AB968;
extern int        counter_8009F448;
extern TARGET *GM_BombSeg_800ABBD8;

void mine_act_80067558(MineWork *work)
{
    int map; // $v1
    int weapon_state; // $s1
    int weap_flags; // $a0
    int local_54; // $v0
    DG_OBJ *obj;

    map = work->field_20_pCtrl->field_2C_map->field_0_map_index_bit;
    DG_GroupObjs(work->field_28_obj.objs, DG_CurrentGroupID_800AB968);

    GM_CurrentMap_800AB9B0 = map;
    if ( (work->field_24_pObj->objs->flag & DG_FLAG_INVISIBLE) != 0 )
    {
        DG_InvisibleObjs(work->field_28_obj.objs);
    }
    else if ( !work->field_54_counter )
    {
        DG_VisibleObjs(work->field_28_obj.objs);
    }
    obj = &work->field_24_pObj->objs->objs[work->field_4C_unit];

    weapon_state = GM_Weapons[ WEAPON_CLAYMORE ];
    weap_flags = *work->field_50_pFlags;

    if ((weap_flags & 1) != 0
      && weapon_state > 0
      && (weap_flags & 2) != 0
      && counter_8009F448 < 8
      && NewJirai_8006B48C(obj, GM_BombSeg_800ABBD8))
    {
        GM_SeSet_80032858(&work->field_20_pCtrl->field_0_mov, 49);
        GM_Weapons[ WEAPON_CLAYMORE ] = --weapon_state;

        work->field_54_counter = 21;
        DG_InvisibleObjs(work->field_28_obj.objs);
    }

    local_54 = work->field_54_counter;

    //new_54 = local_54 - 1;
    if ( local_54 > 0 )
    {
        work->field_54_counter = local_54 - 1;
        if ( !work->field_54_counter )
        {
            DG_VisibleObjs(work->field_28_obj.objs);
        }
    }
    if ( !weapon_state )
    {
        DG_InvisibleObjs(work->field_28_obj.objs);
    }
}

void mine_kill_80067710(MineWork *mine)
{
    GM_FreeObject_80034BF8((OBJECT *)&mine->field_28_obj);
}

int mine_loader_80067730(MineWork *actor_mine, OBJECT *parent_obj, int num_parent)
{
    OBJECT_NO_ROTS *obj = &actor_mine->field_28_obj;

    int id = GV_StrCode_80016CCC("claymore");
    GM_InitObjectNoRots_800349B0(obj, id, 0x36d, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot_80034C5C((OBJECT *)obj, parent_obj, num_parent);
    return 0;
}

GV_ACT *mine_init_800677BC(CONTROL *a1, OBJECT *parent_object, int num_parent, int *a4)
{
    MineWork *actor = (MineWork *)GV_NewActor_800150E4(6, sizeof(MineWork));
    if (actor)
    {
        GV_SetNamedActor_8001514C(&actor->field_0_actor, (TActorFunction)mine_act_80067558,
                                  (TActorFunction)mine_kill_80067710, "mine.c");
        if (mine_loader_80067730(actor, parent_object, num_parent) < 0)
        {
            GV_DestroyActor_800151C8(&actor->field_0_actor);
            return 0;
        }

        actor->field_20_pCtrl = a1;
        actor->field_24_pObj = parent_object;
        actor->field_4C_unit = num_parent;
        actor->field_50_pFlags = a4;
        actor->field_54_counter = 0;
    }

    GM_MagazineMax_800ABA2C = 0;
    GM_Magazine_800AB9EC = 0;

    return &actor->field_0_actor;
}
