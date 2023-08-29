#include "unknown.h"

extern int dword_800AB9A8;

static inline void sub_80028454_copy_svector(SVECTOR *dst, SVECTOR *src)
{
    struct sub_80028454_copy_struct
    {
        int a, b;
    };
    *(struct sub_80028454_copy_struct *)dst = *(struct sub_80028454_copy_struct *)src;
}

static inline void sub_80028454_copy_svector_to_scratchpad(int offset, SVECTOR *svec)
{
    short *scratchpad;
    scratchpad = (short *)0x1F800000;

    scratchpad[offset + 0] = svec->vx;
    scratchpad[offset + 2] = svec->vy;
    scratchpad[offset + 1] = svec->vz;
}

int sub_80028454(HZD_MAP *pHzdMap, SVECTOR *a2, SVECTOR *a3, int flags, int flag)
{
    int       count;
    int       n_areas, n_areas2;
    int       bit1, bit2;
    HZD_AREA *pArea;
    int       dword_800AB9A8_copy;
    HZD_FLR  *pAltimetry;
    HZD_SEG  *pWall;
    HZD_SEG **ppSeg;
    HZD_SEG **ppWall;
    char     *pFlags;
    int       n_unknown;
    char     *pFlagsEnd;
    int       queue_size, idx;
    char     *pFlagsEnd2;
    HZD_MAP  *pNextMap;

    dword_800AB9A8_copy = dword_800AB9A8;

    sub_80028454_copy_svector_to_scratchpad(6, a2);

    *((int *)0x1F800064) = (*((int *)0x1F80006C) = 0);

    sub_80028454_copy_svector_to_scratchpad(10, a3);
    sub_80028454_copy_svector((SVECTOR *)0x1F800054, (SVECTOR *)0x1F800014);

    *((int *)0x1F80008C) = 0;

    sub_8002751C((SVECTOR *)0x1F80000C, (SVECTOR *)0x1F800054);

    *((int *)0x1F80005C) = sub_80027384();

    if (!(*(int *)0x1F80005C))
    {
        return 0;
    }

    if (flags & 4)
    {
        char *scratchpad;

        bit2 = 1;
        pArea = pHzdMap->f00_header->areas;
        for (n_areas2 = pHzdMap->f00_header->n_areas; n_areas2 > 0; n_areas2--, bit2 <<= 1, pArea++)
        {
            if (dword_800AB9A8_copy & bit2)
            {
                do
                {
                    pWall = pArea->walls;
                    pFlags = pArea->wallsFlags;
                    do {} while (0);
                    n_unknown = pArea->n_unknown;
                    pFlagsEnd = pFlags + 2 * pArea->n_walls;
                    scratchpad = (char *)0x1F800000;
                    *((short *)(scratchpad + 0x6A)) = 0;
                } while (0);

                *((char **)(scratchpad + 0x70)) = pFlagsEnd;
                *((int *)0x1F800060) = n_unknown;

                for (count = pArea->n_walls; count > 0; count--, pWall++, pFlags++)
                {
                    if (!((*pFlags) & flag))
                    {
                        sub_80027A94(pWall, count, *pFlags);
                    }
                }
            }
        }
    }

    if (flags & 8)
    {
        char *scratchpad;

        pNextMap = NULL;
        while ((pNextMap = Map_Enum_Get_Hzd_80031580(pNextMap)))
        {
            scratchpad = (char *)0x1F800000;
            do
            {
                ppWall = pNextMap->f20_pAfterStructure_24;
                pFlags = pNextMap->f20_pAfterStructure_48;
                queue_size = pNextMap->f12_queue_size;
                idx = pNextMap->f0A_idx;
                *((short *)(scratchpad + 0x6A)) = 0x80;
                do
                {
                } while (0);

                pFlagsEnd2 = (pFlags + queue_size) + idx;
                *((char **)(scratchpad + 0x70)) = pFlagsEnd2;
            } while (0); // TODO: Is it the same macro as above in "if (flags & 4)" case?

            count = pNextMap->f0A_idx;
            *((int *)0x1F800060) = 0;

            for (; count > 0; count--, ppWall++, pFlags++)
            {
                if (!((*pFlags) & flag))
                {
                    sub_80027A94(*ppWall, count, *pFlags);
                }
            }
        }
    }
    sub_8002751C((SVECTOR *)0x1F80000C, (SVECTOR *)0x1F800054);
    *((int *)0x1F80005C) = sub_80027BF8((SVECTOR *)0x1F800054);
    *((int *)0x1F800074) = 0xF4240;

    if (flags & 1)
    {
        bit1 = 1;
        pArea = pHzdMap->f00_header->areas;
        for (n_areas = pHzdMap->f00_header->n_areas; n_areas > 0; n_areas--, bit1 <<= 1, pArea++)
        {
            if (dword_800AB9A8_copy & bit1)
            {
                pAltimetry = pArea->altimetry;
                for (count = pArea->n_altimetry; count > 0; count--)
                {
                    sub_80027F10(pAltimetry);
                    pAltimetry++;
                }
            }
        }
    }

    if (flags & 2)
    {
        pNextMap = NULL;
        while ((pNextMap = Map_Enum_Get_Hzd_80031580(pNextMap)))
        {
            ppSeg = pNextMap->f1C_pEndOfHzdMap;
            for (count = pNextMap->f0C; count > 0; count--, ppSeg++)
            {
                sub_80027F10((HZD_FLR *)*ppSeg); // TODO: What's the correct argument type of sub_80027F10?
            }
        }
    }

    if (*(int *)0x1F80008C != 0)
    {
        gte_SetRotMatrix(0x1f800090);
    }

    if (*(int *)0x1F800064 != 0)
    {
        return *(int *)0x1F80006C;
    }
    return 0;
}
