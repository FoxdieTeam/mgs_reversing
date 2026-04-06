#include "libhzd.h"
#include "private.h"

#include "common.h"
#include "inline_n.h"
#include "inline_x.h"
#include "psxdefs.h"            // for getScratchAddr2
#include "libdg/libdg.h"
#include "libgv/libgv.h"        // for GV_VecLen3

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

    CopyToHzdVec(0x1F80000C, nears);
    area = Len2D((SVECTOR *)0x1F80000C);

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
        CopyToHzdVec(0x1F800010, &nears[1]);
        area2 = Len2D((SVECTOR *)0x1F800010);

        if ( area2 < scale )
        {
            Mul2D((SVECTOR *)0x1F800014, (SVECTOR *)0x1F80000C, scale, area);
            Mul2D((SVECTOR *)0x1F800018, (SVECTOR *)0x1F800010, scale, area2);

            Sub2D((SVECTOR *)0x1F800014, (SVECTOR *)0x1F800014, (SVECTOR *)0x1F80000C);
            Sub2D((SVECTOR *)0x1F800018, (SVECTOR *)0x1F800018, (SVECTOR *)0x1F800010);

            area3 = Dot2D((SVECTOR *)0x1F800014, (SVECTOR *)0x1F800014);
            area4 = Dot2D((SVECTOR *)0x1F800018, (SVECTOR *)0x1F800018);
            area5 = Dot2D((SVECTOR *)0x1F800014, (SVECTOR *)0x1F800018);

            if ((area5 < area3) && (area5 < area4))
            {
                area6 = Det2D((SVECTOR *)0x1F800014, (SVECTOR *)0x1F800018);

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

    Mul2D((SVECTOR *)0x1F800014, (SVECTOR *)0x1F80000C, scale, area);
    Sub2D((SVECTOR *)0x1F800014, (SVECTOR *)0x1F80000C, (SVECTOR *)0x1F800014);

    CopyFromHzdVec(out, (SVECTOR *)0x1F800014);
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
