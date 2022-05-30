#include "mine.h"

extern void GM_FreeObject_80034BF8(OBJECT *obj);

void mine_kill_80067710(Actor_Mine* mine)
{
    GM_FreeObject_80034BF8(&mine->f28_obj);
}
