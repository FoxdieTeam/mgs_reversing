#include "libhzd/libhzd.h"

void HZD_SetDynamicSegment_8006FEE4(HZD_SEG *a1, HZD_SEG *a2)
{
    int sVar1;
    int sVar2;

    sVar2 = a1->p1.x;
    sVar1 = a1->p2.x;

    if (sVar2 >= sVar1)
    {
        if (sVar2 <= sVar1)
        {
            sVar2 = a1->p1.z;
            sVar1 = a1->p2.z;

            if (sVar2 >= sVar1)
            {
                if (sVar2 <= sVar1)
                {
                    a1->p2.x++;

                    if (a1 != a2)
                    {
                        *a2 = *a1;
                    }

                    return;
                }
            }
            else
            {
                if (a1 != a2)
                {
                    *a2 = *a1;
                }

                return;
            }
        }
    }
    else
    {
        if (a1 != a2)
        {
            *a2 = *a1;
        }

        return;
    }

    // Are those SCOPYL2 (or similar) inlines?
    sVar2 = a1->p1.x;
    sVar1 = a1->p2.x;
    a2->p2.x = sVar2;
    a2->p1.x = sVar1;
    sVar2 = a1->p1.y;
    sVar1 = a1->p2.y;
    a2->p2.y = sVar2;
    a2->p1.y = sVar1;
    sVar2 = a1->p1.z;
    sVar1 = a1->p2.z;
    a2->p2.z = sVar2;
    a2->p1.z = sVar1;
    sVar2 = a1->p1.h;
    sVar1 = a1->p2.h;
    a2->p2.h = sVar2;
    a2->p1.h = sVar1;
}
