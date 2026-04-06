#include "libhzd.h"

#include "common.h"
#include "inline_n.h"
#include "inline_x.h"
#include "psxdefs.h"            // for getScratchAddr2
#include "libdg/libdg.h"
#include "libgv/libgv.h"        // for GV_VecLen3

#define AssignVecXYXZ(dst, src)                    \
{                                                  \
    ((SVECTOR *)dst)->vx = ((SVECTOR *)src)->vx;   \
    ((SVECTOR *)dst)->vy = ((SVECTOR *)src)->vz;   \
}

#define AssignVecXZXY(dst, src)                    \
{                                                  \
    ((SVECTOR *)dst)->vx = ((SVECTOR *)src)->vx;   \
    ((SVECTOR *)dst)->vz = ((SVECTOR *)src)->vy;   \
}

static inline void SwapNegateVecXY(SVECTOR *dst, SVECTOR *src)
{
    dst->vx = -src->vy;
    dst->vy = src->vx;
}

static inline int get_area(SVECTOR *x, SVECTOR* y, SVECTOR *z)
{
    SwapNegateVecXY(x, y);
    gte_NormalClip(0, *(int *)y, *(int *)x, z);
    return SquareRoot0(*(int *)z);
}

static inline int get_area2(SVECTOR *x, SVECTOR* y, SVECTOR *z)
{
    gte_NormalClip(0, *(int *)x, *(int *)y, z);
    return *(int *)z;
}

static inline void IntVecXY(SVECTOR *dst, SVECTOR *src, int scale, int len)
{
    dst->vx = (src->vx * scale) / len;
    dst->vy = (src->vy * scale) / len;
}

static inline void SubVecXY(SVECTOR *dst, SVECTOR *a, SVECTOR *b)
{
    dst->vx = a->vx - b->vx;
    dst->vy = a->vy - b->vy;
}

static inline void SubVecXYZ(HZD_VEC *dst, HZD_FLR *a, HZD_VEC *b)
{
    dst->x = a->p1.x - b->x;
    dst->z = a->p1.y - b->y;
    dst->y = a->p1.z - b->z;
}

int HZD_StepCheck( SVECTOR *nears, int count, int scale, SVECTOR *out )
{
    int area;
    int area2;
    int area4;
    int area3;
    int area5;
    int area6;
    int len;

    SVECTOR *pVec1;
    SVECTOR *pVec2;

    int temp;

    out->vz = 0;
    out->vy = 0;
    out->vx = 0;

    if ( count == 0 )
    {
        return 1;
    }

    AssignVecXYXZ(0x1F80000C, nears);
    area = get_area((SVECTOR *)0x1F800004, (SVECTOR *)0x1F80000C, (SVECTOR *)0x1F800008);

    if ( area >= scale )
    {
        return 1;
    }

    if ( area == 0 )
    {
        return 0;
    }

    if ( count == 2 )
    {
        AssignVecXYXZ(0x1F800010, &nears[1]);
        area2 = get_area((SVECTOR *)0x1F800004, (SVECTOR *)0x1F800010, (SVECTOR *)0x1F800008);

        if ( area2 < scale )
        {
            IntVecXY((SVECTOR *)0x1F800014, (SVECTOR *)0x1F80000C, scale, area);
            IntVecXY((SVECTOR *)0x1F800018, (SVECTOR *)0x1F800010, scale, area2);

            SubVecXY((SVECTOR *)0x1F800014, (SVECTOR *)0x1F800014, (SVECTOR *)0x1F80000C);
            SubVecXY((SVECTOR *)0x1F800018, (SVECTOR *)0x1F800018, (SVECTOR *)0x1F800010);

            SwapNegateVecXY((SVECTOR *)0x1F800004, (SVECTOR *)0x1F800014);
            area3 = get_area2((SVECTOR *)0x1F800014, (SVECTOR *)0x1F800004, (SVECTOR *)0x1F800008);

            SwapNegateVecXY((SVECTOR *)0x1F800004, (SVECTOR *)0x1F800018);
            area4 = get_area2((SVECTOR *)0x1F800018, (SVECTOR *)0x1F800004, (SVECTOR *)0x1F800008);

            SwapNegateVecXY((SVECTOR *)0x1F800004, (SVECTOR *)0x1F800018);
            area5 = get_area2((SVECTOR *)0x1F800014, (SVECTOR *)0x1F800004, (SVECTOR *)0x1F800008);

            if ((area5 < area3) && (area5 < area4))
            {
                area6 = get_area2((SVECTOR *)0x1F800014, (SVECTOR *)0x1F800018, (SVECTOR *)0x1F800008);

                if ( area6 != 0 )
                {
                    pVec1 = (SVECTOR *)0x1F800014;

                    temp = pVec1->vy * area4;

                    pVec2 = (SVECTOR *)0x1F800018;

                    out->vx = (temp - pVec2->vy * area3) / area6;

                    out->vz = (pVec2->vx * area3 - pVec1->vx * area4) / area6;

                    len = GV_VecLen3( out );

                    if ( len > (scale << 2) )
                    {
                        GV_LenVec3( out, out, len, scale << 2 );
                    }
                }

                return 1;
            }
        }
    }

    IntVecXY((SVECTOR *)0x1F800014, (SVECTOR *)0x1F80000C, scale, area);
    SubVecXY((SVECTOR *)0x1F800014, (SVECTOR *)0x1F80000C, (SVECTOR *)0x1F800014);

    AssignVecXZXY(out, (SVECTOR *)0x1F800014);
    return 1;
}

void HZD_SurfaceNormal(HZD_FLR *floor, SVECTOR *out)
{
    if (floor->b1.h >= 0) // Wall
    {
        out->vx = floor->b2.z - floor->b1.z;
        out->vy = 0;
        out->vz = floor->b1.x - floor->b2.x;
        GV_LenVec3(out, out, GV_VecLen3(out), 4096);
    }
    else // Floor
    {
        out->vx = floor->p1.h * 16;
        out->vy = floor->p3.h * 16;
        out->vz = floor->p2.h * 16;
    }
}
