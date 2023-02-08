#include "libgv.h"

void GV_NearExp4PV_800269A0(short *a, short *b, int count)
{
    int diff;
    int diff2;
    int mid;

    while (--count >= 0)
    {
        diff = *b + FP_Subtract(*a, *b);
        diff2 = *b - diff;

        if ((diff2 > -4) && (diff2 < 4))
        {
            mid = *b;
        }
        else
        {
            mid = diff + (diff2 / 4);
        }
        
        *a++ = mid;
        b++;
    }
}
