#include "mine.h"

extern const char aClaymore_0[]; // = "claymore";

extern int GV_Strcode_80016CCC(const char *string);
extern void GM_ConfigObjectRoot_80034C5C(OBJECT *obj, OBJECT *parent_obj, int num_parent);
extern void GM_InitObjectNoRots_800349B0(OBJECT_NO_ROTS *obj, int model, int flag, int motion);

int mine_loader_80067730(Actor_Mine *actor_mine, OBJECT *parent_obj, int num_parent)
{
    OBJECT *obj = &actor_mine->f28_obj;

    int id = GV_Strcode_80016CCC(aClaymore_0);
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS*)obj, id, 0x36d, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot_80034C5C(obj, parent_obj, num_parent);
    return 0;
}