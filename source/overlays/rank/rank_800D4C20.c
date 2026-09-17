#include "game/game.h"

void rank_800D4C20(HZD_SEG *seg)
{
    int i;
    int round;

    for (i = 2; i > 0; i--)
    {
        round = (seg->p1.x >= 0) ? 62 : -62;
        seg->p1.x = ((seg->p1.x + round) / 125) * 125;

        round = (seg->p1.z >= 0) ? 62 : -62;
        seg->p1.z = ((seg->p1.z + round) / 125) * 125;
    }
}
