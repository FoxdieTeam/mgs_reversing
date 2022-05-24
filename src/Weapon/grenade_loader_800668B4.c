#include "grenade.h"

extern unsigned short dword_8009F3E4[];

extern int GV_Strcode_80016CCC(const char *string);
extern void GM_ConfigObjectRoot_80034C5C(OBJECT *obj, OBJECT *parent_obj, int num_parent);
extern void GM_InitObjectNoRots_800349B0(OBJECT_NO_ROTS *obj, int model, int flag, int motion);

int grenade_loader_800668B4(Actor_Grenade *actor_grenade, OBJECT *parent_obj, int num_parent, int index)
{
    OBJECT *obj = &actor_grenade->f28_obj;

    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS*)obj, dword_8009F3E4[index], 0x6d, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot_80034C5C(obj, parent_obj, num_parent);
    return 0;
}