#include "aam.h"

extern char aStinger_0[]; // = "stinger"

extern int GV_Strcode_80016CCC(const char *string);
extern void GM_ConfigObjectRoot_80034C5C(OBJECT *obj, OBJECT *parent_obj, int num_parent);
extern void GM_InitObjectNoRots_800349B0(OBJECT_NO_ROTS *obj, int model, int flag, int motion);

int aam_loader_800673F0(Actor_Aam *actor_aam, OBJECT *parent_obj, int num_parent)
{
    OBJECT *obj = &actor_aam->f20_obj;
    
    int id;
    actor_aam->f5c = 0;
    
    id = GV_Strcode_80016CCC(aStinger_0);
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS*)obj, id, 0x6d, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot_80034C5C(obj, parent_obj, num_parent);
    return 0;
}