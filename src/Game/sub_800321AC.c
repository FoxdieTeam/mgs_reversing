#include "psyq.h"

int sub_800321AC(int a1, int a2)
{
    int v2 = rcos_800925D8(a1 & 4095) * a2 / 4096;
    if (v2 < 0)
    {
        return v2 + 255;
    }
    return v2;
}