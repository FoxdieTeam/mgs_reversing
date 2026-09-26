#include "libgv/libgv.h"

void *rank_800CEF28(int count, int flag)
{
    int size;

    if (!flag)
    {
        size = 0x28;
    }
    else
    {
        size = 0x34;
    }
    return GV_Malloc(count * size);
}
