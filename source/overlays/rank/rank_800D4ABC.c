#include "game/game.h"

int rank_800D4ABC(HZD_FLR *find, int count, HZD_FLR *flrs)
{
    (int)find |= 0x80000000;

    for (; count > 0; count--, flrs++)
    {
        if (flrs == find)
        {
            return 1;
        }
    }

    return 0;
}
