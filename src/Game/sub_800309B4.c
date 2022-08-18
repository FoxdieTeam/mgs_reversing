#include "game.h"
#include "Camera.h"

extern SVECTOR dword_800ABA88;
extern GM_Camera GM_Camera_800B77E8;

void sub_800309B4(int param_1, int param_2)
{
    GM_Camera_800B77E8.field_2A = param_1;
    GM_Camera_800B77E8.field_26 = param_2;
    dword_800ABA88 = GM_Camera_800B77E8.field_0;
}
