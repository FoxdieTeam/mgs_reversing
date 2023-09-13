#include "psyq.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"

typedef struct SCRPAD_80027384
{
    char    pad[4];
    HZD_VEC vec[4];
} SCRPAD_80027384;

#define S ((SCRPAD_80027384 *)getScratchAddr(0))

static inline void sub_helper_80027384(void)
{
    *(short *)0x1F800004 = -*(short *)0x1F80001E;
    *(short *)0x1F800006 = *(short *)0x1F80001C;
}

int sub_80027384(void)
{
    HZD_VEC *pVec1 = &S->vec[3];
    HZD_VEC *pVec2 = &S->vec[2];
    HZD_VEC *pVec3 = &S->vec[1];
    int      area;

    pVec1->x = pVec2->x - pVec3->x;
    pVec1->y = pVec2->y - pVec3->y;
    pVec1->z = pVec2->z - pVec3->z;

    sub_helper_80027384();

    gte_NormalClip(0, S->vec[3].long_access[0], S->vec[0].long_access[0], &S->vec[0].long_access[1]);

    area = SquareRoot0(*(long *)getScratchAddr(2));
    if (area == 0)
    {
        return 0;
    }

    pVec1->x = (pVec1->x * 256) / area;
    pVec1->y = (pVec1->y * 256) / area;
    pVec1->z = (pVec1->z * 256) / area;

    return area;
}
