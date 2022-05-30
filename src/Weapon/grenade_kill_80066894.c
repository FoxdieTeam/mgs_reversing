#include "grenade.h"

extern void GM_FreeObject_80034BF8(OBJECT *obj);

void grenade_kill_80066894(Actor_Grenade *grenade)
{
    GM_FreeObject_80034BF8(&grenade->f28_obj);
}
