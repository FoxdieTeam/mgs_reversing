#include "game.h"

extern GM_Camera GM_Camera_800B77E8;

void sub_800309F8(int param_1, int param_2)
{
    sub_800309B4(param_1, param_2);
    GM_Camera_800B77E8.field_18_flags |= 2;
}
