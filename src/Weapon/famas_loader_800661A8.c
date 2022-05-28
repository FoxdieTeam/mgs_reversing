#include "famas.h"

extern char aFamas[];   // = "famas"
extern char aMpfive[];  // = "mpfive"

extern int GV_Strcode_80016CCC(const char *string);
extern void GM_ConfigObjectRoot_80034C5C(OBJECT *obj, OBJECT *parent_obj, int num_parent);
extern void GM_InitObjectNoRots_800349B0(OBJECT_NO_ROTS *obj, int model, int flag, int motion);

int famas_loader_800661A8(Actor_Famas *actor_famas, OBJECT *parent_obj, int num_parent, int flag)
{
    OBJECT *obj = &actor_famas->f20_obj;
    int id;

    if (flag == 0)
        id = GV_Strcode_80016CCC(aFamas);
    else
        id = GV_Strcode_80016CCC(aMpfive);

    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS*)obj, id, 0x6d, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot_80034C5C(obj, parent_obj, num_parent);
    return 0;
}