#include "aam.h"

extern void GM_FreeObject_80034BF8(OBJECT *obj);
extern void GV_DestroyOtherActor_800151D8(struct Actor *pActorToKill);

void aam_kill_800673B0(Actor_Aam *actor)
{
    GM_FreeObject_80034BF8(&actor->f20_obj);
    if (actor->f5c)
    {
        GV_DestroyOtherActor_800151D8(actor->f5c);
    }
}