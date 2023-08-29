#include "libhzd/libhzd.h"

void CopyVectorToScratchpad_800288BC(SVECTOR *vec_1, SVECTOR *vec_2);
void sub_800288E0(SVECTOR *vec, int delta);
void sub_80028DAC(HZD_SEG *pWall, int, char);

static inline void AddVecXY(SVECTOR *dst, SVECTOR *a, SVECTOR *b)
{
    dst->vx = a->vx + b->vx;
    dst->vy = a->vy + b->vy;
}

static inline void sub_helper_80029098(void)
{
    if (*(int *)0x1F800084 == 0)
    {
        return;
    }

    if (*(int *)0x1F800068 != 0)
    {
        if (*(int *)0x1F800078 != *(int *)0x1F800094)
        {
            return;
        }
    }
    else
    {
        AddVecXY((SVECTOR *)0x1F8000A0, (SVECTOR *)0x1F80000C, (SVECTOR *)0x1F800094);

        if (*(int *)0x1F8000A0 != *(int *)0x1F80007C && *(int *)0x1F8000A0 != *(int *)0x1F800080)
        {
            return;
        }
    }

    *(int *)0x1F800048 = 1;
}

int sub_80029098(HZD_MAP *pMap, SVECTOR *pPosition, int delta, int flags, unsigned int mask)
{
    HZD_AREA *pArea;
    int       n_unknown;
    HZD_SEG  *pWalls;
    char     *pFlags;
    int       wall_count;
    char    **ptr;
    char    **ptr2;
    int       i;
    HZD_SEG **ppWalls;
    int       idx;
    int       queue_size;

    pArea = pMap->f04_area;

    CopyVectorToScratchpad_800288BC(pPosition, (SVECTOR *)0x1F80000C);
    sub_800288E0((SVECTOR *)0x1F80000C, delta);

    *(int *)0x1F800048 = 0;

    if (flags & 0x4)
    {
        n_unknown = pArea->n_unknown;

        *(int *)0x1F800088 = delta * delta;
        *(int *)0x1F80006C = delta * delta;

        do {} while (0);

        pWalls = pArea->walls;
        pFlags = pArea->wallsFlags;
        wall_count = pArea->n_walls;

        ptr = (char **)0x1F800000;
        ptr[0x2C] = (char *)0;
        ptr[0x2D] = pFlags + wall_count * 2;

        *(int *)0x1F800044 = n_unknown;

        for (i = pArea->n_walls; i > 0; i--, pWalls++, pFlags++)
        {
            if ((*pFlags & mask) == 0)
            {
                sub_80028DAC(pWalls, i, *pFlags);
            }
        }
    }

    if (flags & 0x8)
    {
        ppWalls = pMap->f20_pAfterStructure_24;
        pFlags = pMap->f20_pAfterStructure_48;
        queue_size = pMap->f12_queue_size;
        idx = pMap->f0A_idx;

        ptr2 = (char **)0x1F800000;
        ptr2[0x2C] = (char *)0x80;
        ptr2[0x2D] = pFlags + queue_size + idx;

        *(int *)0x1F800044 = 0;

        for (i = pMap->f0A_idx; i > 0; i--, ppWalls++, pFlags++)
        {
            if ((*pFlags & mask) == 0)
            {
                sub_80028DAC(*ppWalls, i, *pFlags);
            }
        }
    }

    if (*(int *)0x1F800048 > 1)
    {
        *(int *)0x1F800048 = 2;
        sub_helper_80029098();
    }

    return *(int *)0x1F800048;
}
