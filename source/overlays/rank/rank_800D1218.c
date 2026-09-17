#include "rank.h"

void rank_800D1218(int xpos, int ypos, int flags)
{
    TextConfig *config = &rank_dword_800E1998;

    config->xpos = xpos;
    config->ypos = ypos;
    config->flags = flags;
}
