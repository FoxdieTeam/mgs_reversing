#include "libgv.h"

void GV_NearExp2PV_80026924(short *a,short *b, int count)
{
    int diff;
    int diff2;
    int mid;

    while (--count >= 0)
    {
        diff = *b + FP_Subtract(*a, *b);
        diff2 = *b - diff;

        if ((diff2 > -2) && (diff2 < 2))
        {
            mid = *b;
        }
        else
        {
            mid = diff + (diff2 / 2);
        }
        
        *a++ = mid;
        b++;
    }
}
