#include "game.h"

void sub_8002E508(int a1)
{
    if (a1 == 0)
    {
        GM_Sound_80032C48(0x1ffffff, 0);
    }
    else
    {
        GM_Sound_80032C48(a1 | 0x1000000, 0);
    }
}
