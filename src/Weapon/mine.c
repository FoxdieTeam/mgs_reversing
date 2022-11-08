#include "mine.h"
#include "map/map.h"
#include "Game/target.h"
#include "Game/object.h"
#include "Bullet/jirai.h"

// claymore (in hands)

extern const char aClaymore_0[]; // = "claymore";
extern char       aMineC[];      // = "mine.c"
extern short      d_800AB9EC_mag_size;
extern short      d_800ABA2C_ammo;

extern int        DG_CurrentGroupID_800AB968;
extern int        counter_8009F448;
extern GM_Target *GM_BombSeg_800ABBD8;

#pragma INCLUDE_ASM("asm/Weapon/mine_act_80067558.s") // 440 bytes

void mine_kill_80067710(Actor_Mine *mine)
{
    GM_FreeObject_80034BF8(&mine->field_28_obj);
}

int mine_loader_80067730(Actor_Mine *actor_mine, OBJECT *parent_obj, int num_parent)
{
    OBJECT *obj = &actor_mine->field_28_obj;

    int id = GV_StrCode_80016CCC(aClaymore_0);
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)obj, id, 0x36d, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot_80034C5C(obj, parent_obj, num_parent);
    return 0;
}

Actor_Mine *mine_init_800677BC(GM_Control *a1, OBJECT *parent_object, int num_parent, int *a4)
{
    Actor_Mine *actor = (Actor_Mine *)GV_NewActor_800150E4(6, sizeof(Actor_Mine));
    if (actor)
    {
        GV_SetNamedActor_8001514C(&actor->field_0_actor, (TActorFunction)mine_act_80067558,
                                  (TActorFunction)mine_kill_80067710, aMineC);
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

    d_800ABA2C_ammo = 0;
    d_800AB9EC_mag_size = 0;

    return actor;
}
