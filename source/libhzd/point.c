#include "libhzd.h"

#include "common.h"
#include "inline_n.h"
#include "inline_x.h"
#include "inline_hzd.h"
#include "psxdefs.h"    // for getScratchAddr2
#include "libdg/libdg.h"

static void CopyVector(SVECTOR *src, HZD_VEC *dst)
{
    dst->x = src->vx;
    dst->y = src->vy;
    dst->z = src->vz;
}

static void CreateBoundingBox(HZD_VEC *vec, int range)
{
    SVECTOR *min;
    SVECTOR *max;
    int      comp;

    min = (SVECTOR *)(SCRPAD_ADDR + 0x14);
    max = (SVECTOR *)(SCRPAD_ADDR + 0x1C);

    comp = vec->x;
    min->vx = comp - range;
    max->vx = comp + range;

    comp = vec->z;
    min->vz = comp - range;
    max->vz = comp + range;

    comp = vec->y;
    max->vy = comp;
    min->vy = comp;
}

STATIC int HZD_80028930(void)
{
    int   lzcnt;
    int   num;
    int   opz, opz2, opz3;

    short *ptr1;
    short *ptr2;

    Sub2D((SVECTOR *)0x1F800038, (SVECTOR *)0x1F80002C, (SVECTOR *)0x1F800024);
    Sub2D((SVECTOR *)0x1F800034, (SVECTOR *)0x1F80000C, (SVECTOR *)0x1F800024);

    opz = Dot2D((SVECTOR *)0x1F800038, (SVECTOR *)0x1F800034);

    *(int *)0x1F80004C = 1;
    *(int *)0x1F8000AC = 1;

    if (opz < 0)
    {
        *(int *)0x1F8000A8 = 0;
        Sub2D((SVECTOR *)0x1F80005C, (SVECTOR *)0x1F800024, (SVECTOR *)0x1F80000C);
    }
    else
    {
        opz2 = Dot2D((SVECTOR *)0x1F800038, (SVECTOR *)0x1F800038);

        if (opz2 < opz)
        {
            *(int *)0x1F8000A8 = 1;
            Sub2D((SVECTOR *)0x1F80005C, (SVECTOR *)0x1F80002C, (SVECTOR *)0x1F80000C);
        }
        else
        {
            opz3 = Det2D((SVECTOR *)0x1F800038, (SVECTOR *)0x1F800034);

            gte_ldlzc(opz2);
            gte_stlzc(0x1F8000A4);

            lzcnt = 16 - *(int *)0x1F8000A4;

            if (lzcnt > 0)
            {
                opz >>= lzcnt;
                opz3 >>= lzcnt;
                opz2 >>= lzcnt;
            }

            *(int *)0x1F8000A8 = opz;
            *(int *)0x1F8000AC = opz2;

            num = *(short *)0x1F80003A * opz3;

            ptr1 = (short *)0x1F80004C;
            ptr1[8] = num / opz2;

            if ((ptr1[8] == 0) && (num != 0))
            {
                ptr1[8] = (num > 0) ? 1 : -1;
            }

            num = -*(short *)0x1F800038 * opz3;

            ptr2 = (short*)0x1F80004C;
            ptr2[9] = num / opz2;

            if ((ptr2[9] == 0) && (num != 0))
            {
                ptr2[9] = (num > 0) ? 1 : -1;
            }

            *(int *)0x1F80004C = 0;
            *(int *)0x1F800060 = *(int *)0x1F800024;
            *(int *)0x1F800064 = *(int *)0x1F80002C;
        }
    }

    *(int *)0x1F800050 = Dot2D((SVECTOR *)0x1F80005C, (SVECTOR *)0x1F80005C);
    return *(int *)0x1F800050;
}

STATIC void HZD_80028CF8(void)
{
    gte_lddp((*(int *)0x1F8000A8 * 4096) / *(int *)0x1F8000AC);
    gte_ld_intpol_sv0((SVECTOR *)0x1F800030);
    gte_ldopv2SV((SVECTOR *)0x1F800028);
    gte_intpl();
    gte_stsv((SVECTOR *)0x1F800028);

    return;
}

static inline int PointTestSegment_inline(HZD_SEG *wall)
{
    int z1, z2;
    int tmp;
    int height;
    int y1, y2;

    if ((wall->p1.x > *(short *)0x1F80001C) || (wall->p2.x < *(short *)0x1F800014))
    {
        return 0;
    }

    z1 = wall->p1.z;
    z2 = wall->p2.z;

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

    y1 = wall->p1.y;
    y2 = wall->p2.y;

    if (height < y1 && height < y2)
    {
        return 0;
    }

    height = *(short *)0x1F80001E;

    y1 += wall->p1.h;
    y2 += wall->p2.h;

    if (height > y1 && height > y2)
    {
        return 0;
    }

    return 1;
}

STATIC void PointTestSegment(HZD_SEG *wall, int index, int flags)
{
    int *ptr;
    int  opz;
    int  height;
    int *ptr1, *ptr2, *ptr3;

    if (!PointTestSegment_inline(wall))
    {
        return;
    }

    *(HZD_SEG *)0x1F800024 = *wall;

    ptr = (int *)0x1F800084;
    opz = HZD_80028930();

    if (opz >= ptr[1])
    {
        return;
    }

    if (index > *(int *)0x1F800044)
    {
        HZD_80028CF8();

        height = *(short *)0x1F800010 - ((HZD_SEG *)0x1F800024)->p1.y;

        if (height < 0 || height > ((HZD_SEG *)0x1F800024)->p1.h)
        {
            return;
        }
    }

    ptr1 = (int *)0x1F80004C;
    ptr2 = (int *)0x1F800068;
    ptr3 = (int *)0x1F800000;

    ptr1[2] = (int)wall;
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
        Add2D((SVECTOR *)0x1F8000A0, (SVECTOR *)0x1F80000C, (SVECTOR *)0x1F800094);

        if (*(int *)0x1F8000A0 != *(int *)0x1F80007C && *(int *)0x1F8000A0 != *(int *)0x1F800080)
        {
            return;
        }
    }

    *(int *)0x1F800048 = 1;
}

int HZD_PointCheck(HZD_HDL *hzd, SVECTOR *point, int range, int flag, int exclude)
{
    HZD_GRP *pArea;
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

    pArea = hzd->group;

    CopyVector(point, (HZD_VEC *)0x1F80000C);
    CreateBoundingBox((HZD_VEC *)0x1F80000C, range);

    *(int *)0x1F800048 = 0;

    if (flag & HZD_CHECK_SEG)
    {
        n_unknown = pArea->n_flat_walls;

        *(int *)0x1F800088 = range * range;
        *(int *)0x1F80006C = range * range;

        do {} while (0);

        pWalls = pArea->walls;
        pFlags = pArea->wallsFlags;
        wall_count = pArea->n_walls;

        ptr = (char **)SCRPAD_ADDR;
        ptr[0x2C] = (char *)0;
        ptr[0x2D] = pFlags + wall_count * 2;

        *(int *)0x1F800044 = n_unknown;

        for (i = pArea->n_walls; i > 0; i--, pWalls++, pFlags++)
        {
            if ((*pFlags & exclude) == 0)
            {
                PointTestSegment(pWalls, i, *pFlags);
            }
        }
    }

    if (flag & HZD_CHECK_DYNSEG)
    {
        ppWalls = hzd->dynamic_segments;
        pFlags = hzd->dynamic_flags;
        queue_size = hzd->max_dynamic_segments;
        idx = hzd->dynamic_queue_index;

        ptr2 = (char **)SCRPAD_ADDR;
        ptr2[0x2C] = (char *)0x80;
        ptr2[0x2D] = pFlags + queue_size + idx;

        *(int *)0x1F800044 = 0;

        for (i = hzd->dynamic_queue_index; i > 0; i--, ppWalls++, pFlags++)
        {
            if ((*pFlags & exclude) == 0)
            {
                PointTestSegment(*ppWalls, i, *pFlags);
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

/**
 * Used in collision detection (ie, called when Snake nears an obstacle or an edge).
 *
 * This function is called with the VECTOR[2]* snake->control->nears as its argument. Disabling it has no
 * obvious effects on collision or gameplay.
 */
void HZD_PointNearSurface(void **surface)
{
    surface[0] = *(void **)(SCRPAD_ADDR + 0x70);
    surface[1] = *(void **)(SCRPAD_ADDR + 0x8c);
}

/**
 * Used in collision detection (ie, called when Snake nears an obstacle or an edge).
 *
 * This function is called with the char[2] snake->control->nearflags as its argument. Disabling it makes Snake
 * treat edges as if they were walls, eg in Dock he turns his back towards the water instead of running towards it on
 * the spot, except if one approaches it while running where he is programmed to dive into it.
 */
void HZD_PointNearFlag(char *flags)
{
    flags[0] = *getScratchAddr2(char, 0x74);
    flags[1] = *getScratchAddr2(char, 0x90);
}

/**
 * Fundamental function in collision detection, called when Snake nears an obstacle or an edge.
 *
 * This function is called with the SVECTOR[2] snake->control->nearvecs as an argument. Disabling it
 * disables collision for Snake, seemingly as those vectors are then passed to HZD_StepCheck() as its
 * first argument and used by it to determine values in the scratchpad which are then used at the end of that function
 * to create Snake's movement vector.
 */
void HZD_PointNearVec(SVECTOR *points)
{
    HZD_SEG *wall1;
    HZD_SEG *wall2;

    wall1 = getScratchAddr2(HZD_SEG, 0x68);
    points[0].vx = wall1[1].p1.x;
    points[0].vy = 0;
    points[0].vz = wall1[1].p1.z;

    wall2 = getScratchAddr2(HZD_SEG, 0x84);
    points[1].vx = wall2[1].p1.x;
    points[1].vy = 0;
    points[1].vz = wall2[1].p1.z;
}
