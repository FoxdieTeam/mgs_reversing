#include "libhzd/libhzd.h"

int sub_80029A2C()
{
    HZD_FLR *hzdFlr;
    int      h;

    // Only a single place in code writes a pointer to 0x1F80003C
    // (in sub_80029604) and it's a HZD_FLR pointer.
    hzdFlr = *(HZD_FLR **)0x1F80003C;
    if (!hzdFlr)
    {
        return 0;
    }

    h = hzdFlr->b1.h;
    return h >> 8;
}
