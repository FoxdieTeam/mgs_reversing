#include "game.h"

extern GM_Camera GM_Camera_800B77E8;

void GM_CameraLimitTrace_80030AC4(int param_1)
{
    sub_8002EBE8(&GM_Camera_800B77E8.field_8, param_1);
}
