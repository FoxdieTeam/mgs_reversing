#include "libgv.h"

void GV_NearExp8PV_80026A24(short *a,short *b, int count)
{
    int diff;
    int diff2;
    int mid;

    while (--count >= 0)
    {
        diff = *b + FP_Subtract(*a, *b);
        diff2 = *b - diff;

        if ((diff2 > -8) && (diff2 < 8))
        {
            mid = *b;
        }
        else
        {
            mid = diff + (diff2 / 8);
        }
        
        *a++ = mid;
        b++;
    }
}
