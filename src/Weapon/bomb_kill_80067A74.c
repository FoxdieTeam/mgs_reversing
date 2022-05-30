#include "bomb.h"

extern void GM_FreeObject_80034BF8(OBJECT *obj);

void bomb_kill_80067A74(Actor_Bomb *actor)
{
    GM_FreeObject_80034BF8(&actor->f28_obj);
}
