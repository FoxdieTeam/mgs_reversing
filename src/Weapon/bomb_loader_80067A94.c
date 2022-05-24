#include "bomb.h"

extern char aC4Bomb[];    // = "c4_bomb"

extern int GV_Strcode_80016CCC(const char *string);
extern void GM_ConfigObjectRoot_80034C5C(OBJECT *obj, OBJECT *parent_obj, int num_parent);
extern void GM_InitObjectNoRots_800349B0(OBJECT_NO_ROTS *obj, int model, int flag, int motion);

int bomb_loader_80067A94(Actor_Bomb *actor_bomb, OBJECT *parent_obj, int num_parent, int flag)
{
    OBJECT *obj = &actor_bomb->f28_obj;

    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS*)obj, GV_Strcode_80016CCC(aC4Bomb), 0x6d, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot_80034C5C(obj, parent_obj, num_parent);
    return 0;
}