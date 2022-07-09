#include "game.h"

extern void GM_ConfigObjectAction_80034CD4( OBJECT *obj, int action_flag, int motion, int interp );

void sub_8004E22C(int param_1, int param_2, int param_3)
{
    if (*(short *)(param_1 + 0xaa) != param_2)
    {
        GM_ConfigObjectAction_80034CD4((OBJECT *)(param_1 + 0x9c), param_2, 0, param_3);
    }
    return;
}
