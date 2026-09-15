#include "rank.h"

void rank_800D128C(int r, int g, int b, int flag)
{
    TextConfig *config = &rank_dword_800E1998;

    if (flag == 0)
    {
        config->color = r | (g << 8) | (b << 16) | 0x64000000;
    }
    else
    {
        config->color = r | (g << 8) | (b << 16) | 0x2C000000;
    }
}
