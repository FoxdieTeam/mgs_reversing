#include "Game/game.h"

extern GM_Camera GM_Camera_800B77E8;

void sub_8002FD84(int index, int value)
{
    GM_Camera_800B77E8.field_74_2Array[index] = value;
}
