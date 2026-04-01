#include "kojo/demo.h"

#define __detx(a, b, c) (((b).y - (a).y) * ((c).z - (b).z) - ((b).z - (a).z) * ((c).y - (b).y))
#define __dety(a, b, c) (((b).z - (a).z) * ((c).x - (b).x) - ((b).x - (a).x) * ((c).z - (b).z))
#define __detz(a, b, c) (((b).x - (a).x) * ((c).y - (b).y) - ((b).y - (a).y) * ((c).x - (b).x))

void sub_8007E1C0(HZD_VEC *pOut, HZD_VEC *pOut2, MATRIX *pTransform, SVECTOR *pMin, SVECTOR *pMax)
{
    VECTOR   cross;
    SVECTOR *va;
    SVECTOR *vb;
    int      idx;
    int      i;
    int      len;
    int      min, max;

    va = (SVECTOR *)getScratchAddr(0);
    vb = (SVECTOR *)getScratchAddr(16);

    va[0].vx = pMin->vx;
    va[0].vy = pMin->vy;
    va[0].vz = pMin->vz;

    va[1].vx = pMin->vx;
    va[1].vy = pMin->vy;
    va[1].vz = pMax->vz;

    va[2].vx = pMax->vx;
    va[2].vy = pMin->vy;
    va[2].vz = pMax->vz;

    va[3].vx = pMax->vx;
    va[3].vy = pMin->vy;
    va[3].vz = pMin->vz;

    va[4].vx = pMin->vx;
    va[4].vy = pMax->vy;
    va[4].vz = pMin->vz;

    va[5].vx = pMin->vx;
    va[5].vy = pMax->vy;
    va[5].vz = pMax->vz;

    va[6].vx = pMax->vx;
    va[6].vy = pMax->vy;
    va[6].vz = pMax->vz;

    va[7].vx = pMax->vx;
    va[7].vy = pMax->vy;
    va[7].vz = pMin->vz;

    DG_SetPos(pTransform);
    DG_PutVector(va, va, 8);

    vb[0] = va[0];

    idx = 0;
    for (i = 0; i < 8; i++)
    {
        if ((va[i].vx < vb[0].vx) || ((va[i].vx == vb[0].vx) && (va[i].vz < vb[0].vz)))
        {
            idx = i;
            vb[0] = va[i];
        }
    }

    if (idx >= 4)
    {
        idx -= 4;
    }

    vb[4] = vb[0];

    vb[0].vy = MIN(va[idx].vy, va[idx + 4].vy);
    vb[4].vy = MAX(va[idx].vy, va[idx + 4].vy);

    if (++idx >= 4)
    {
        idx = 0;
    }

    vb[1] = (va[idx].vz >= va[idx + 4].vz) ? va[idx] : va[idx + 4];
    vb[5] = vb[1];
    vb[1].vy = MIN(va[idx].vy, va[idx + 4].vy);
    vb[5].vy = MAX(va[idx].vy, va[idx + 4].vy);

    if (++idx >= 4)
    {
        idx = 0;
    }

    vb[2] = (va[idx].vx >= va[idx + 4].vx) ? va[idx] : va[idx + 4];
    vb[6] = vb[2];
    vb[2].vy = MIN(va[idx].vy, va[idx + 4].vy);
    vb[6].vy = MAX(va[idx].vy, va[idx + 4].vy);

    if (++idx >= 4)
    {
        idx = 0;
    }

    vb[3] = (va[idx].vz <= va[idx + 4].vz) ? va[idx] : va[idx + 4];
    vb[7] = vb[3];
    vb[3].vy = MIN(va[idx].vy, va[idx + 4].vy);
    vb[7].vy = MAX(va[idx].vy, va[idx + 4].vy);

    pOut[0].x = vb[0].vx;
    pOut[0].z = vb[0].vz;
    pOut[0].y = vb[0].vy;
    pOut[0].h = vb[4].vy - vb[0].vy;

    pOut[1].x = vb[1].vx;
    pOut[1].z = vb[1].vz;
    pOut[1].y = vb[1].vy;
    pOut[1].h = vb[5].vy - vb[1].vy;

    pOut[2].x = vb[1].vx;
    pOut[2].z = vb[1].vz;
    pOut[2].y = vb[1].vy;
    pOut[2].h = vb[5].vy - vb[1].vy;

    pOut[3].x = vb[2].vx;
    pOut[3].z = vb[2].vz;
    pOut[3].y = vb[2].vy;
    pOut[3].h = vb[6].vy - vb[2].vy;

    pOut[4].x = vb[3].vx;
    pOut[4].z = vb[3].vz;
    pOut[4].y = vb[3].vy;
    pOut[4].h = vb[7].vy - vb[3].vy;

    pOut[5].x = vb[2].vx;
    pOut[5].z = vb[2].vz;
    pOut[5].y = vb[2].vy;
    pOut[5].h = vb[6].vy - vb[2].vy;

    pOut[6].x = vb[0].vx;
    pOut[6].z = vb[0].vz;
    pOut[6].y = vb[0].vy;
    pOut[6].h = vb[4].vy - vb[0].vy;

    pOut[7].x = vb[3].vx;
    pOut[7].z = vb[3].vz;
    pOut[7].y = vb[3].vy;
    pOut[7].h = vb[7].vy - vb[3].vy;

    pOut2[2].x = vb[0].vx;
    pOut2[2].z = vb[0].vz;
    pOut2[2].y = vb[0].vy;

    pOut2[3].x = vb[3].vx;
    pOut2[3].z = vb[3].vz;
    pOut2[3].y = vb[3].vy;

    pOut2[4].x = vb[2].vx;
    pOut2[4].z = vb[2].vz;
    pOut2[4].y = vb[2].vy;

    pOut2[5].x = vb[1].vx;
    pOut2[5].z = vb[1].vz;
    pOut2[5].y = vb[1].vy;
    pOut2[5].h = 0;

    pOut2[0] = pOut2[2];
    pOut2[0].h = 0;

    pOut2[0].x = MIN(pOut2[0].x, pOut2[3].x);
    pOut2[0].x = MIN(pOut2[0].x, pOut2[4].x);
    pOut2[0].x = MIN(pOut2[0].x, pOut2[5].x);

    pOut2[0].z = MIN(pOut2[0].z, pOut2[3].z);
    pOut2[0].z = MIN(pOut2[0].z, pOut2[4].z);
    pOut2[0].z = MIN(pOut2[0].z, pOut2[5].z);

    pOut2[0].y = MIN(pOut2[0].y, pOut2[3].y);
    pOut2[0].y = MIN(pOut2[0].y, pOut2[4].y);
    pOut2[0].y = MIN(pOut2[0].y, pOut2[5].y);

    pOut2[1] = pOut2[2];
    pOut2[1].h = 0;

    pOut2[1].x = MAX(pOut2[1].x, pOut2[3].x);
    pOut2[1].x = MAX(pOut2[1].x, pOut2[4].x);
    pOut2[1].x = MAX(pOut2[1].x, pOut2[5].x);

    pOut2[1].z = MAX(pOut2[1].z, pOut2[3].z);
    pOut2[1].z = MAX(pOut2[1].z, pOut2[4].z);
    pOut2[1].z = MAX(pOut2[1].z, pOut2[5].z);

    pOut2[1].y = MAX(pOut2[1].y, pOut2[3].y);
    pOut2[1].y = MAX(pOut2[1].y, pOut2[4].y);
    pOut2[1].y = MAX(pOut2[1].y, pOut2[5].y);

    cross.vx = __detx(pOut2[2], pOut2[3], pOut2[4]) >> 16;
    cross.vy = __dety(pOut2[2], pOut2[3], pOut2[4]) >> 16;
    cross.vz = __detz(pOut2[2], pOut2[3], pOut2[4]) >> 16;

    len = cross.vx * cross.vx + cross.vy * cross.vy + cross.vz * cross.vz;
    len = SquareRoot0(len);
    if (len == 0)
    {
        len = 1;
    }

    pOut2[2].h = (cross.vx * 255) / len;
    pOut2[3].h = (cross.vz * 255) / len;
    pOut2[4].h = (cross.vy * 255) / len;
    if (pOut2[4].h == 0)
    {
        pOut2[4].h = 1;
    }

    pOut2[8].x = vb[4].vx;
    pOut2[8].z = vb[4].vz;
    pOut2[8].y = vb[4].vy;

    pOut2[9].x = vb[7].vx;
    pOut2[9].z = vb[7].vz;
    pOut2[9].y = vb[7].vy;

    pOut2[10].x = vb[6].vx;
    pOut2[10].z = vb[6].vz;
    pOut2[10].y = vb[6].vy;

    pOut2[11].x = vb[5].vx;
    pOut2[11].z = vb[5].vz;
    pOut2[11].y = vb[5].vy;
    pOut2[11].h = 0;

    pOut2[6].x = pOut2[0].x;
    pOut2[6].z = pOut2[0].z;
    pOut2[6].h = 0;

    min = MIN(pOut2[8].y, pOut2[9].y);
    min = MIN(min, pOut2[10].y);
    min = MIN(min, pOut2[11].y);
    pOut2[6].y = min;

    pOut2[7].x = pOut2[1].x;
    pOut2[7].z = pOut2[1].z;
    pOut2[7].h = 0;

    max = MAX(pOut2[8].y, pOut2[9].y);
    max = MAX(max, pOut2[10].y);
    max = MAX(max, pOut2[11].y);
    pOut2[7].y = max;

    pOut2[8].h = pOut2[2].h;
    pOut2[9].h = pOut2[3].h;
    pOut2[10].h = pOut2[4].h;
}

void sub_8007EF34(SVECTOR *pOutVec1, SVECTOR *pOutVec2, MATRIX *pInMtx)
{
    int tmp;
    int distance;
    MATRIX rotMtx;
    SVECTOR vec1;
    SVECTOR vec2;
    ReadRotMatrix(&rotMtx);
    pOutVec1->vx = pInMtx->t[0];
    pOutVec1->vy = pInMtx->t[1];
    pOutVec1->vz = pInMtx->t[2];
    DG_SetPos(pInMtx);
    vec1.vx = 0;
    vec1.vy = 0;
    vec1.vz = 0;
    vec2.vx = 0;
    vec2.vy = 0;
    vec2.vz = 100;
    DG_PutVector(&vec1, &vec1, 1);
    DG_PutVector(&vec2, &vec2, 1);
    tmp = (short) (vec2.vx - vec1.vx) * (short) (vec2.vx - vec1.vx);
    vec2.vx -= vec1.vx;
    vec2.vy -= vec1.vy;
    vec2.vz -= vec1.vz;
    distance = SquareRoot0(tmp + (vec2.vz * vec2.vz));
    pOutVec2->vx = -((short) ratan2(vec2.vy, distance));
    pOutVec2->vy = ratan2(vec2.vx, vec2.vz);
    pOutVec2->vz = 0;
    DG_SetPos(&rotMtx);
}

void sub_8007F06C(DG_VECTOR *param_1, VECTOR *param_2, VECTOR *param_3)
{
    param_1[0].vx = param_2->vx;
    param_1[0].vy = param_2->vy;
    param_1[0].vz = param_2->vz;
    param_1[1].vx = param_3->vx - param_2->vx;
    param_1[1].vy = param_3->vy - param_2->vy;
    param_1[1].vz = param_3->vz - param_2->vz;
}

void sub_8007F0D0(VECTOR *out, VECTOR *a, VECTOR *b, VECTOR *c)
{
    out->vx = (b->vy - a->vy) * (c->vz - b->vz) - (b->vz - a->vz) * (c->vy - b->vy);
    out->vy = (b->vz - a->vz) * (c->vx - b->vx) - (b->vx - a->vx) * (c->vz - b->vz);
    out->vz = (b->vx - a->vx) * (c->vy - b->vy) - (b->vy - a->vy) * (c->vx - b->vx);
    out->pad = out->vx * -a->vx + out->vy * -a->vy + out->vz * -a->vz;
}

VECTOR * sub_8007F1DC(VECTOR *out, DG_VECTOR *arg1, VECTOR *arg2)
{
    VECTOR vec;
    int    area;
    int    weight;

    area = arg2->vx * arg1[1].vx + arg2->vy * arg1[1].vy + arg2->vz * arg1[1].vz;
    if (area == 0)
    {
        vec.vx = 0x7FFFFFFF;
        vec.vy = 0x7FFFFFFF;
        vec.vz = 0x7FFFFFFF;
    }
    else
    {
        weight = ((-arg2->vx * arg1[0].vx - arg2->vy * arg1[0].vy - arg2->vz * arg1[0].vz - arg2->pad) << 12) / area;
        vec.vx = arg1->vx + ((arg1[1].vx * weight) >> 12);
        vec.vy = arg1->vy + ((arg1[1].vy * weight) >> 12);
        vec.vz = arg1->vz + ((arg1[1].vz * weight) >> 12);
    }

    *out = vec;
    return out;
}

void InitChain(ACTNODE *root)
{
    if (root)
    {
        root->prev = root;
        root->next = root;
    }
}

void InsertChain(ACTNODE *root, ACTNODE *node)
{
    if (root && node)
    {
        node->prev = root->prev;
        node->next = root;
            
        if (root->prev == root)
        {
            root->next = node;
        }
        else
        {
            root->prev->next = node;
        }

        root->prev = node;
    }
}

void RemoveChain(ACTNODE *root, ACTNODE *node)
{
    int equal;

    if (root && node)
    {
        /* compiler removes the check if inlined */
        equal = node->prev == root;

        if (equal)
        {
            root->next = node->next;
        }
        else
        {
            node->prev->next = node->next;
        }

        node->next->prev = node->prev;
        InitChain(node);
    }
}

typedef struct
{
    char    pad[16];
    SVECTOR pre[8];
    SVECTOR post[8];
    HZD_SEG segment;
    SVECTOR unknown;
} SCRPAD_DATA_8007F3F8;

SVECTOR svector_8009F7AC = {0, 255, 0, 0};

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
