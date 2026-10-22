#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"

/******************************************************************************
 * definitions and typedefs and structures
 */

typedef struct
{
    char    pad[16];
    SVECTOR pre[8];
    SVECTOR post[8];
    HZD_SEG segment;
    SVECTOR unknown;
} SCRPAD_DATA_8007F3F8;

SVECTOR svector_8009F7AC = {0, 255, 0, 0};

/******************************************************************************
 * publics
 */

void sub_8007F3F8(HZD_SEG *pIn, HZD_FLR *pOut, MATRIX *pTransform, SVECTOR *pMin, SVECTOR *pMax)
{
    SCRPAD_DATA_8007F3F8 *scrpad;
    SVECTOR              *pIter;
    int                   count;
    int                   a, b, c, d;
    int                   hzd_h;
    int                   min, v1, v2;

    scrpad = (SCRPAD_DATA_8007F3F8 *)getScratchAddr(0);

    DG_SetPos(pTransform);
    DG_RotVector(&svector_8009F7AC, &scrpad->unknown, 1);

    scrpad->pre[0].vx = pMin->vx;
    scrpad->pre[0].vy = pMin->vy;
    scrpad->pre[0].vz = pMin->vz;

    scrpad->pre[1].vx = pMin->vx;
    scrpad->pre[1].vy = pMin->vy;
    scrpad->pre[1].vz = pMax->vz;

    scrpad->pre[2].vx = pMax->vx;
    scrpad->pre[2].vy = pMin->vy;
    scrpad->pre[2].vz = pMax->vz;

    scrpad->pre[3].vx = pMax->vx;
    scrpad->pre[3].vy = pMin->vy;
    scrpad->pre[3].vz = pMin->vz;

    scrpad->pre[4].vx = pMin->vx;
    scrpad->pre[4].vy = pMax->vy;
    scrpad->pre[4].vz = pMin->vz;

    scrpad->pre[5].vx = pMin->vx;
    scrpad->pre[5].vy = pMax->vy;
    scrpad->pre[5].vz = pMax->vz;

    scrpad->pre[6].vx = pMax->vx;
    scrpad->pre[6].vy = pMax->vy;
    scrpad->pre[6].vz = pMax->vz;

    scrpad->pre[7].vx = pMax->vx;
    scrpad->pre[7].vy = pMax->vy;
    scrpad->pre[7].vz = pMin->vz;

    DG_PutVector(scrpad->pre, scrpad->post, 8);

    pIter = scrpad->post;
    for (count = 4; count > 0; count--, pIter++)
    {
        a = pIter[0].vx;
        b = pIter[4].vx;
        c = pIter[0].vz;
        d = pIter[4].vz;

        pIter[0].vx = pIter[4].vx = (a + b) / 2;
        pIter[0].vz = pIter[4].vz = (c + d) / 2;
    }

    hzd_h = scrpad->post[4].vy - scrpad->post[0].vy;

    scrpad->segment.p1.x = scrpad->post[0].vx;
    scrpad->segment.p1.z = scrpad->post[0].vz;
    scrpad->segment.p1.y = scrpad->post[0].vy;
    scrpad->segment.p1.h = hzd_h;

    scrpad->segment.p2.x = scrpad->post[1].vx;
    scrpad->segment.p2.z = scrpad->post[1].vz;
    scrpad->segment.p2.y = scrpad->post[1].vy;
    scrpad->segment.p2.h = hzd_h;

    HZD_SetDynamicSegment(&scrpad->segment, pIn);

    scrpad->segment.p1.x = scrpad->post[1].vx;
    scrpad->segment.p1.z = scrpad->post[1].vz;
    scrpad->segment.p1.y = scrpad->post[1].vy;
    scrpad->segment.p1.h = hzd_h;

    scrpad->segment.p2.x = scrpad->post[2].vx;
    scrpad->segment.p2.z = scrpad->post[2].vz;
    scrpad->segment.p2.y = scrpad->post[2].vy;
    scrpad->segment.p2.h = hzd_h;

    HZD_SetDynamicSegment(&scrpad->segment, pIn + 1);

    scrpad->segment.p1.x = scrpad->post[3].vx;
    scrpad->segment.p1.z = scrpad->post[3].vz;
    scrpad->segment.p1.y = scrpad->post[3].vy;
    scrpad->segment.p1.h = hzd_h;

    scrpad->segment.p2.x = scrpad->post[2].vx;
    scrpad->segment.p2.z = scrpad->post[2].vz;
    scrpad->segment.p2.y = scrpad->post[2].vy;
    scrpad->segment.p2.h = hzd_h;

    HZD_SetDynamicSegment(&scrpad->segment, pIn + 2);

    scrpad->segment.p1.x = scrpad->post[0].vx;
    scrpad->segment.p1.z = scrpad->post[0].vz;
    scrpad->segment.p1.y = scrpad->post[0].vy;
    scrpad->segment.p1.h = hzd_h;

    scrpad->segment.p2.x = scrpad->post[3].vx;
    scrpad->segment.p2.z = scrpad->post[3].vz;
    scrpad->segment.p2.y = scrpad->post[3].vy;
    scrpad->segment.p2.h = hzd_h;

    HZD_SetDynamicSegment(&scrpad->segment, pIn + 3);

    pOut[0].p1.x = scrpad->post[0].vx;
    pOut[0].p1.z = scrpad->post[0].vz;
    pOut[0].p1.y = scrpad->post[0].vy;

    pOut[0].p2.x = scrpad->post[3].vx;
    pOut[0].p2.z = scrpad->post[3].vz;
    pOut[0].p2.y = scrpad->post[3].vy;

    pOut[0].p3.x = scrpad->post[2].vx;
    pOut[0].p3.z = scrpad->post[2].vz;
    pOut[0].p3.y = scrpad->post[2].vy;

    pOut[0].p4.x = scrpad->post[1].vx;
    pOut[0].p4.z = scrpad->post[1].vz;
    pOut[0].p4.y = scrpad->post[1].vy;
    pOut[0].p4.h = 0;

    pOut[1].p1.x = scrpad->post[4].vx;
    pOut[1].p1.z = scrpad->post[4].vz;
    pOut[1].p1.y = scrpad->post[4].vy;

    pOut[1].p2.x = scrpad->post[7].vx;
    pOut[1].p2.z = scrpad->post[7].vz;
    pOut[1].p2.y = scrpad->post[7].vy;

    pOut[1].p3.x = scrpad->post[6].vx;
    pOut[1].p3.z = scrpad->post[6].vz;
    pOut[1].p3.y = scrpad->post[6].vy;

    pOut[1].p4.x = scrpad->post[5].vx;
    pOut[1].p4.z = scrpad->post[5].vz;
    pOut[1].p4.y = scrpad->post[5].vy;
    pOut[1].p4.h = 0;

    pOut[0].b1.h = 0;
    pOut[0].b2.h = 0;
    pOut[1].b1.h = 0;
    pOut[1].b2.h = 0;

    //start
    v1 = scrpad->post[0].vx;

    min = scrpad->post[1].vx;
    if (min > v1)
    {
        min = v1;
    }

    v2 = scrpad->post[1].vx;
    if (v2 < v1)
    {
        v2 = v1;
    }
    v1 = v2;

    v2 = scrpad->post[2].vx;
    if (v2 > min)
    {
        v2 = min;
    }
    min = v2;

    v2 = scrpad->post[2].vx;
    if (v1 > v2)
    {
        v2 = v1;
    }
    v1 = v2;

    v2 = scrpad->post[3].vx;
    if (v2 > min)
    {
        v2 = min;
    }
    min = v2;

    v2 = scrpad->post[3].vx;
    if (v1 > v2)
    {
        v2 = v1;
    }
    v1 = v2;

    pOut[0].b1.x = min;
    pOut[1].b1.x = min;
    pOut[0].b2.x = v1;
    pOut[1].b2.x = v1;


    //next
    v1 = scrpad->post[0].vy;

    min = scrpad->post[1].vy;
    if (min > v1)
    {
        min = v1;
    }

    v2 = scrpad->post[1].vy;
    if (v2 < v1)
    {
        v2 = v1;
    }
    v1 = v2;

    v2 = scrpad->post[2].vy;
    if (v2 > min)
    {
        v2 = min;
    }
    min = v2;

    v2 = scrpad->post[2].vy;
    if (v1 > v2)
    {
        v2 = v1;
    }
    v1 = v2;

    v2 = scrpad->post[3].vy;
    if (v2 > min)
    {
        v2 = min;
    }
    min = v2;

    v2 = scrpad->post[3].vy;
    if (v1 > v2)
    {
        v2 = v1;
    }
    v1 = v2;

    pOut[0].b1.y = min;
    pOut[0].b2.y = v1;

    //next
    v1 = scrpad->post[0].vz;

    min = scrpad->post[1].vz;
    if (min > v1)
    {
        min = v1;
    }

    v2 = scrpad->post[1].vz;
    if (v2 < v1)
    {
        v2 = v1;
    }
    v1 = v2;

    v2 = scrpad->post[2].vz;
    if (v2 > min)
    {
        v2 = min;
    }
    min = v2;

    v2 = scrpad->post[2].vz;
    if (v1 > v2)
    {
        v2 = v1;
    }
    v1 = v2;

    v2 = scrpad->post[3].vz;
    if (v2 > min)
    {
        v2 = min;
    }
    min = v2;

    v2 = scrpad->post[3].vz;
    if (v1 > v2)
    {
        v2 = v1;
    }
    v1 = v2;

    pOut[0].b1.z = min;
    pOut[1].b1.z = min;
    pOut[0].b2.z = v1;
    pOut[1].b2.z = v1;

    //next
    v1 = scrpad->post[4].vy;
    min = scrpad->post[5].vy;
    if (min > v1)
    {
        min = v1;
    }

    v2 = scrpad->post[5].vy;
    if (v2 < v1)
    {
        v2 = v1;
    }
    v1 = v2;

    v2 = scrpad->post[6].vy;
    if (v2 > min)
    {
       v2 = min;
    }
    min = v2;

    v2 = scrpad->post[6].vy;
    if (v1 > v2)
    {
        v2 = v1;
    }
    v1 = v2;

    v2 = scrpad->post[7].vy;
    if (v2 > min)
    {
        v2 = min;
    }
    min = v2;

    v2 = scrpad->post[7].vy;
    if (v1 > v2)
    {
        v2 = v1;
    }
    v1 = v2;

    pOut[1].b1.y = min;
    pOut[1].b2.y = v1;

    if (scrpad->unknown.vy == 0)
    {
        scrpad->unknown.vy = 1;
    }

    pOut[0].p1.h = scrpad->unknown.vx;
    pOut[0].p2.h = scrpad->unknown.vz;
    pOut[0].p3.h = scrpad->unknown.vy;

    pOut[1].p1.h = scrpad->unknown.vx;
    pOut[1].p2.h = scrpad->unknown.vz;
    pOut[1].p3.h = scrpad->unknown.vy;
}
