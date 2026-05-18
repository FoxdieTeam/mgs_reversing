#include "libhzd.h"
#include "private.h"

#include "common.h"
#include "inline_n.h"
#include "inline_x.h"
#include "psxdefs.h"            // for getScratchAddr2
#include "libdg/libdg.h"
#include "libgv/libgv.h"        // for GV_VecLen3

int HZD_HazardReaction( SVECTOR *vects, int n_vects, int range, SVECTOR *react )
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

    react->vz = 0;
    react->vy = 0;
    react->vx = 0;

    if ( n_vects == 0 )
    {
        return 1;
    }

    CopyToHzdVec(0x1F80000C, vects);
    area = Len2D((SVECTOR *)0x1F80000C);

    if ( area >= range )
    {
        return 1;
    }

    if ( area == 0 )
    {
        return 0;
    }

    if ( n_vects == 2 )
    {
        CopyToHzdVec(0x1F800010, &vects[1]);
        area2 = Len2D((SVECTOR *)0x1F800010);

        if ( area2 < range )
        {
            Mul2D((SVECTOR *)0x1F800014, (SVECTOR *)0x1F80000C, range, area);
            Mul2D((SVECTOR *)0x1F800018, (SVECTOR *)0x1F800010, range, area2);

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

                    react->vx = (temp - pVec2->vy * area3) / area6;

                    react->vz = (pVec2->vx * area3 - pVec1->vx * area4) / area6;

                    len = GV_VecLen3( react );

                    if ( len > (range << 2) )
                    {
                        GV_LenVec3( react, react, len, range << 2 );
                    }
                }

                return 1;
            }
        }
    }

    Mul2D((SVECTOR *)0x1F800014, (SVECTOR *)0x1F80000C, range, area);
    Sub2D((SVECTOR *)0x1F800014, (SVECTOR *)0x1F80000C, (SVECTOR *)0x1F800014);

    CopyFromHzdVec(react, (SVECTOR *)0x1F800014);
    return 1;
}

void HZD_GetNormal(void *hzd, SVECTOR *norm)
{
    HZD_SEG *seg;

    seg = hzd;
    if (seg->p1.h >= 0) // Wall
    {
        norm->vx = seg->p2.z - seg->p1.z;
        norm->vy = 0;
        norm->vz = seg->p1.x - seg->p2.x;
        GV_LenVec3(norm, norm, GV_VecLen3(norm), 4096);
    }
    else // Floor
    {
        HZD_FLR *flr;

        flr = hzd;
        norm->vx = flr->p1.h * 16;
        norm->vy = flr->p3.h * 16;
        norm->vz = flr->p2.h * 16;
    }
}
