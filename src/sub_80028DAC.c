#include "libhzd/libhzd.h"

int sub_80028930(void);
int sub_80028CF8(void);

static inline int sub_helper_80028DAC(HZD_SEG *pWall)
{
    int z1, z2;
    int tmp;
    int height;
    int y1, y2;

    if ((pWall->p1.x > *(short *)0x1F80001C) || (pWall->p2.x < *(short *)0x1F800014))
    {
        return 0;
    }

    z1 = pWall->p1.z;
    z2 = pWall->p2.z;

    if (z2 < z1)
    {
        tmp = z1;
        z1 = z2;
        z2 = tmp;
    }

    if ((z1 > *(short *)0x1F800020) || (z2 < *(short *)0x1F800018))
    {
        return 0;
    }

    height = *(short *)0x1F800016;

    y1 = pWall->p1.y;
    y2 = pWall->p2.y;

    if (height < y1 && height < y2)
    {
        return 0;
    }

    height = *(short *)0x1F80001E;

    y1 += pWall->p1.h;
    y2 += pWall->p2.h;

    if (height > y1 && height > y2)
    {
        return 0;
    }

    return 1;
}

void sub_80028DAC(HZD_SEG *pWall, int index, int flags)
{
    int *ptr;
    int  opz;
    int  height;
    int *ptr1, *ptr2, *ptr3;

    if (!sub_helper_80028DAC(pWall))
    {
        return;
    }

    *(HZD_SEG *)0x1F800024 = *pWall;

    ptr = (int *)0x1F800084;
    opz = sub_80028930();

    if (opz >= ptr[1])
    {
        return;
    }

    if (index > *(int *)0x1F800044)
    {
        sub_80028CF8();

        height = *(short *)0x1F800010 - ((HZD_SEG *)0x1F800024)->p1.y;

        if (height < 0 || height > ((HZD_SEG *)0x1F800024)->p1.h)
        {
            return;
        }
    }

    ptr1 = (int *)0x1F80004C;
    ptr2 = (int *)0x1F800068;
    ptr3 = (int *)0x1F800000;

    ptr1[2] = (int)pWall;
    ptr1[3] = (flags & 0x7F) | (*(int *)(ptr3 + 0x2C)) | (*(*(char **)(ptr3 + 0x2D) - index) << 8);

    if (opz < ptr2[1])
    {
        memcpy(ptr, ptr2, 28);
        memcpy(ptr2, ptr1, 28);
    }
    else if (*(int *)0x1F80005C != *(int *)0x1F800078)
    {
        memcpy(ptr, ptr1, 28);
    }
    else
    {
        return;
    }

    *(int *)0x1F800048 += 1;
}
