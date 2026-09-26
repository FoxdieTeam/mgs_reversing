#include "game/game.h"

int rank_800D4A94(HZD_SEG *find, int count, HZD_SEG *segs)
{
    for (; count > 0; count--, segs++)
    {
        if (segs == find)
        {
            return 1;
        }
    }

    return 0;
}
