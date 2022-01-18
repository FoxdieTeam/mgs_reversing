#include "game.h"

extern void GM_FreeObject_80034BF8(OBJECT *obj);

void bomb_kill_80067A74(int param_1)

{
    GM_FreeObject_80034BF8((OBJECT *)(param_1 + 0x28));
    return;
}
