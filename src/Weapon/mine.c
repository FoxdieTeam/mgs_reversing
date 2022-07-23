#include "mine.h"

extern const char aClaymore_0[]; // = "claymore";
extern char aMineC[];            // = "mine.c"
extern short d_800AB9EC_mag_size;
extern short dword_800ABA2C;

extern void mine_act_80067558(int param_1);
extern void GM_FreeObject_80034BF8(OBJECT *obj);
extern int GV_StrCode_80016CCC(const char *string);
extern void GM_ConfigObjectRoot_80034C5C(OBJECT *obj, OBJECT *parent_obj, int num_parent);
extern void GM_InitObjectNoRots_800349B0(OBJECT_NO_ROTS *obj, int model, int flag, int motion);

#pragma INCLUDE_ASM("asm/Weapon/mine_act_80067558.s")

void mine_kill_80067710(Actor_Mine* mine)
{
    GM_FreeObject_80034BF8(&mine->f28_obj);
}

int mine_loader_80067730(Actor_Mine *actor_mine, OBJECT *parent_obj, int num_parent)
{
    OBJECT *obj = &actor_mine->f28_obj;

    int id = GV_StrCode_80016CCC(aClaymore_0);
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS*)obj, id, 0x36d, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot_80034C5C(obj, parent_obj, num_parent);
    return 0;
}

Actor_Mine *mine_init_800677BC(int a1, OBJECT *parent_object, int num_parent, int a4)
{
    Actor_Mine *actor = (Actor_Mine*)GV_NewActor_800150E4(6, sizeof(Actor_Mine));
    if (actor)
    {
        GV_SetNamedActor_8001514C(&actor->field_0_actor, (TActorFunction)mine_act_80067558,
            (TActorFunction)mine_kill_80067710, aMineC);
        if (mine_loader_80067730(actor, parent_object, num_parent) < 0)
        {
            GV_DestroyActor_800151C8(&actor->field_0_actor);
            return 0;
        }
        
        actor->f20 = a1;
        actor->parent_object = parent_object;
        actor->num_parent = num_parent;
        actor->f40 = a4;
        actor->f54 = 0;
    }
    
    dword_800ABA2C = 0;
    d_800AB9EC_mag_size = 0;
    
    return actor;
}

