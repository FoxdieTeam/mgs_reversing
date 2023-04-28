#include "libhzd/libhzd.h"
#include "unknown.h"


void sub_80027A94(HZD_SEG *pHzdSeg, int a2, int a3)
{
    struct copier
    {
        int a, b;
    };

    short   *scratch1;
    HZD_SEG *scratch2;
    char    *scratch3;

    int      tmp1;
    int      tmp2;
    int      tmp3;
    int      tmp4;
    char    *tmp5;
    short    tmp6;

    *((HZD_SEG *)0x1F800034) = *pHzdSeg;
    if (sub_800275A8())
    {
        tmp1 = sub_800276B4();
        tmp4 = sub_80027850(tmp1);
        if (tmp4)
        {
            if (*(int *)0x1F800060 < a2)
            {
                sub_8002799C(tmp4);
            }
            scratch1 = (short *)0x1F80004C;
            scratch2 = (HZD_SEG *)0x1F800034;
            tmp2 = scratch1[2] - scratch2->p1.y;
            if (tmp2 >= 0 && scratch2->p1.h >= tmp2)
            {
                *(int *)0x1F80006C += 1;
                if (*(int *)0x1F80005C >= tmp1)
                {
                    scratch3 = (char *)0x1F800000;

                    *(struct copier *)0x1F800054 = *(struct copier *)scratch1;
                    do
                    {
                    } while (0);

                    *(int *)0x1F80005C = tmp1;
                    tmp5 = *(char **)(scratch3 + 0x70);
                    tmp6 = *(short *)(scratch3 + 0x6A);
                    tmp4 = a3 & 127;
                    do
                    {
                    } while (0);

                    *(HZD_SEG **)0x1F800064 = pHzdSeg;
                    tmp3 = *(tmp5 - a2);
                    tmp3 <<= 8;
                    *(short *)0x1F800068 = tmp6 | tmp4 | tmp3;
                }
            }
        }
    }
}
