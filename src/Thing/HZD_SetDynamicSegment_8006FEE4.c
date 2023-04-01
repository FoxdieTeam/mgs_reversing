#include "libhzd/libhzd.h"

void HZD_SetDynamicSegment_8006FEE4(Actor_Door_TParam_sub *a1, Actor_Door_TParam_sub *a2)
{
    int sVar1;
    int sVar2;

    sVar2 = a1->vec[0].x;
    sVar1 = a1->vec[1].x;

    if (sVar2 >= sVar1)
    {
        if (sVar2 <= sVar1)
        {
            sVar2 = a1->vec[0].z;
            sVar1 = a1->vec[1].z;

            if (sVar2 >= sVar1)
            {
                if (sVar2 <= sVar1)
                {
                    a1->vec[1].x++;

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
    sVar2 = a1->vec[0].x;
    sVar1 = a1->vec[1].x;
    a2->vec[1].x = sVar2;
    a2->vec[0].x = sVar1;
    sVar2 = a1->vec[0].y;
    sVar1 = a1->vec[1].y;
    a2->vec[1].y = sVar2;
    a2->vec[0].y = sVar1;
    sVar2 = a1->vec[0].z;
    sVar1 = a1->vec[1].z;
    a2->vec[1].z = sVar2;
    a2->vec[0].z = sVar1;
    sVar2 = a1->vec[0].h;
    sVar1 = a1->vec[1].h;
    a2->vec[1].h = sVar2;
    a2->vec[0].h = sVar1;
}
