#include "game.h"

extern void GM_FreeObject_80034BF8(OBJECT *obj);

void famas_act_80066188(int param_1)

{
    GM_FreeObject_80034BF8((OBJECT *)(param_1 + 0x20));
    return;
}
