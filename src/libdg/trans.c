#include "libdg.h"
#include "common.h"
#include "inline_n.h"
#include "inline_x.h"

extern int GV_Clock_800AB920;

void DG_TransStart( void )
{
    /* do nothing */
}

STATIC unsigned int DG_TransChanl_helper_helper_helper( unsigned int normal_idx, POLY_GT4 *packs )
{
    int *pack_ptr;
    int a2, a3, t3, t5, num, stride;
    int i, temp;
    unsigned int scrpd_idx, scrpd_idx2;
    unsigned char t6;

    scrpd_idx = 0x1F800000;
    t3 = *( int* )(scrpd_idx + 0x3F8);
    if ( !t3 ) return 0;


    t5 = *( int* )( scrpd_idx + 0x3FC );
    num = 0;
    stride = 0;

    pack_ptr = ( int* )&packs->x0;
    a3 = 8;
    i = 4;
    t6 = 32;
    scrpd_idx2 = 0x1f800000;

    for ( ; i > 0; i-- )
    {
        a2 = normal_idx & 0x7f;

        if ((normal_idx & 0x80) == 0)
        {
            a2 = (a2 * 4) + scrpd_idx2;
            temp = ((unsigned int*)a2)[0x80];
            a2 = *( int* )a2;
            num = num + temp;
            stride++;
        }
        else
        {
            a2 = t5 + ( a2 << 3 );
            temp = ( ( unsigned short* )scrpd_idx2 )[0xFF];
            a2 = ( ( short* )a2 )[3];

            if (temp & 4)
            {
                * (pack_ptr - 1 ) = (t3 + a2) - 4;
            }

            a2 = *(int *)(t3 + a2);
        }

        *pack_ptr = a2;
        pack_ptr += 3;
        normal_idx = ( normal_idx << ( t6 - a3 ) ) | ( normal_idx >> a3 );
        a3 = a3 + 8;
    }

    if (stride == 2)
    {
        return num / 2;
    }
    else if (stride == 1)
    {
        return num;
    }
    else if (stride == 3)
    {
        return num / 3;
    }
    return 0;
}

STATIC POLY_GT4 *DG_TransChanl_helper_helper( unsigned int *pFaceIndices, POLY_GT4 *pPoly, int nPacks )
{
    unsigned char bVar1;
    int area;
    unsigned int uVar7;
    int count;
    unsigned int scratchpad;
    unsigned int uVar8;
    unsigned int *n0, *n1, *n2, *n3;

    for (count = nPacks - 1; count >= 0; (pPoly++)->tag = uVar7, pFaceIndices++, count--)
    {
        scratchpad = 0x1f800000;
        uVar7 = 0;
        uVar8 = 0xfffe0000;

        n0 = (unsigned int *)*pFaceIndices;

        if (*pFaceIndices & 0x80808080)
        {
            uVar7 = DG_TransChanl_helper_helper_helper(*pFaceIndices, pPoly);
            continue;
        }

        n1 = (unsigned int *)*pFaceIndices;
        n2 = (unsigned int *)*pFaceIndices;
        n3 = (unsigned int *)*pFaceIndices;

        n0 = (unsigned int *)((unsigned int)n0 << 2);
        n1 = (unsigned int *)((unsigned int)n1 >> 6);
        n2 = (unsigned int *)((unsigned int)n2 >> 22);
        n3 = (unsigned int *)((unsigned int)n3 >> 14);

        n0 = (unsigned int *)((int)n0 & 0x1fc);
        n1 = (unsigned int *)((int)n1 & 0x1fc);
        n2 = (unsigned int *)((int)n2 & 0x1fc);
        n3 = (unsigned int *)((int)n3 & 0x1fc);

        n0 = (unsigned int *)((int)n0 + scratchpad);
        n1 = (unsigned int *)((int)n1 + scratchpad);
        n2 = (unsigned int *)((int)n2 + scratchpad);
        n3 = (unsigned int *)((int)n3 + scratchpad);


        if ((*(unsigned short *)(scratchpad + 0x1fe) & 1))
        {
            bVar1 = 0;

            if (n0[0x80] >> 24)
            {
                bVar1 = n0[0x80] >> 24 & n1[0x80] >> 24 & n2[0x80] >> 24 & n3[0x80] >> 24;
            }

            if (bVar1)
            {
                continue;
            }
        }

        gte_ldsxy3(*n0, *n1, *n2);
        gte_nclip();

        LCOPY(n3, &pPoly->x3);

        gte_stopz((int *)0x1f8001f8);
        gte_stsxy3_gt3(&pPoly->tag);

        area = *(int *)(scratchpad + 0x1f8);

        if (area <= 0)
        {
            if (!(*(short *)(scratchpad + 0x1fc)) || area == 0)
            {
                continue;
            }

            uVar7 = (((-area) << 8) & uVar8) | 0x10000;
        }
        else
        {
            uVar7 = area << 8 & uVar8;
        }

        uVar7 |= (((int) (n0[0x80] + n3[0x80])) / 2) & 0xffff;
    }

    return pPoly;
}

//TODO: Needs to be fixed to matched without forcing registers and extra inlines
static inline void dg_trans_calculate_clipping( DVECTOR *verts )
{
    char res;

    res = 0;

    if ( verts->vx < -160 )
    {
        res = 1;
    }
    else if ( verts->vx > 160 )
    {
        res = 2;
    }

    if ( verts->vy < -112 )
    {
        res |= 4;
    }
    else if ( verts->vy > 112 )
    {
        res |= 8;
    }

    *((char *)(verts + 128) + 3) = res;
}

static inline void dg_trans_calculate_clipping_2( DVECTOR *verts )
{
    register char res asm("a0");

    res = 0;

    if ( verts->vx < -160 )
    {
        res = 1;
    }
    else if ( verts->vx > 160 )
    {
        res = 2;
    }

    if ( verts->vy < -112 )
    {
        res |= 4;
    }
    else if ( verts->vy > 112 )
    {
        res |= 8;
    }

    *((char *)(verts + 128) + 3) = res;
}

static inline void dg_trans_calculate_clipping_3( DVECTOR *verts )
{
    register char res asm("a2");

    res = 0;

    if ( verts->vx < -160 )
    {
        res = 1;
    }
    else if ( verts->vx > 160 )
    {
        res = 2;
    }

    if ( verts->vy < -112 )
    {
        res |= 4;
    }
    else if ( verts->vy > 112 )
    {
        res |= 8;
    }

    *((char *)(verts + 128) + 3) = res;
}

static inline void dg_trans_helper_complex( DG_PVECTOR *verts, int n_verts )
{
    int      vert_count;
    DVECTOR *results_xy;
    DVECTOR *results_z;
    int      z0;
    int      xy1, z1;
    int      xy2, z2;

    register int xy0 asm("t5");

    results_xy = (DVECTOR *)getScratchAddr(0);
    results_z  = (DVECTOR *)getScratchAddr(128);

    gte_ldv3c(verts);

    verts += 3;
    vert_count = n_verts - 3;

    gte_rtpt_b();

    xy0 = verts[0].vxy;
    z0 = verts[0].vz;

    xy1 = verts[1].vxy;
    z1 = verts[1].vz;

    xy2 = verts[2].vxy;
    z2 = verts[2].vz;

    gte_stsxy3c(results_xy);
    gte_stsz3c(results_z);

    results_xy += 3;
    results_z += 3;

    while ( vert_count > 0 )
    {
        gte_ldVXY0(xy0);
        gte_ldVZ0(z0);
        gte_ldVXY1(xy1);
        gte_ldVZ1(z1);
        gte_ldVXY2(xy2);
        gte_ldVZ2(z2);

        verts += 3;
        vert_count -= 3;

        gte_rtpt_b();

        dg_trans_calculate_clipping( results_xy - 3 );
        dg_trans_calculate_clipping( results_xy - 2 );
        dg_trans_calculate_clipping( results_xy - 1 );

        xy0 = verts[0].vxy;
        z0 = verts[0].vz;

        xy1 = verts[1].vxy;
        z1 = verts[1].vz;

        xy2 = verts[2].vxy;
        z2 = verts[2].vz;

        gte_stsxy3c(results_xy);
        gte_stsz3c(results_z);

        results_xy += 3;
        results_z += 3;
    }

    dg_trans_calculate_clipping_2( results_xy - 3 );
    dg_trans_calculate_clipping_3( results_xy - 2 );
    dg_trans_calculate_clipping_2( results_xy - 1 );
}

static inline void dg_trans_helper_simple( DG_PVECTOR *verts, int n_verts )
{
    int      vert_count;
    DVECTOR *results_xy;
    DVECTOR *results_z;
    int      xy0, z0;
    int      xy1, z1;
    int      xy2, z2;

    results_xy = (DVECTOR *)getScratchAddr(0);
    results_z  = (DVECTOR *)getScratchAddr(128);

    gte_ldv3c(verts);

    verts += 3;

    gte_rtpt_b();

    xy0 = verts[0].vxy;
    z0 = verts[0].vz;

    xy1 = verts[1].vxy;
    z1 = verts[1].vz;

    xy2 = verts[2].vxy;
    z2 = verts[2].vz;

    gte_stsxy3c(results_xy);
    gte_stsz3c(results_z);

    results_xy += 3;
    results_z += 3;

    vert_count = n_verts - 3;

    while ( vert_count > 0 )
    {
        gte_ldVXY0(xy0);
        gte_ldVZ0(z0);
        gte_ldVXY1(xy1);
        gte_ldVZ1(z1);
        gte_ldVXY2(xy2);
        gte_ldVZ2(z2);

        verts += 3;
        vert_count -= 3;

        gte_rtpt_b();

        xy0 = verts[0].vxy;
        z0 = verts[0].vz;

        xy1 = verts[1].vxy;
        z1 = verts[1].vz;

        xy2 = verts[2].vxy;
        z2 = verts[2].vz;

        gte_stsxy3c(results_xy);
        gte_stsz3c(results_z);

        results_xy += 3;
        results_z += 3;
    }
}

STATIC void DG_TransChanl_helper( DG_OBJ *obj, int idx )
{
    POLY_GT4   *packs;
    DG_MDL     *mdl;
    DG_PVECTOR *verts;

    packs = obj->packs[idx];

    while ( obj )
    {
        mdl = obj->model;
        verts = (DG_PVECTOR *)mdl->vertices;

        if ( *(unsigned short *)0x1F8001FE & 1 )
        {
            dg_trans_helper_complex( verts, mdl->n_verts );
        }
        else
        {
            dg_trans_helper_simple( verts, mdl->n_verts );
        }

        *(unsigned short *)0x1F8001FC = mdl->flags & DG_MODEL_BOTHFACE;
        do {} while (0);

        packs = DG_TransChanl_helper_helper( ( unsigned int * ) mdl->vindices, packs, obj->n_packs);
        obj = obj->extend;
    }
}

void DG_TransChanl( DG_CHNL *chnl, int idx )
{
    short *pScratchpad = (short *)getScratchAddr(0);
    DG_OBJS **ppObjs;
    int objects;
    DG_OBJS *pObjs;
    DG_OBJ *pObj;
    int uVar5;
    int models;
    DG_MDL *pMdl;
    DG_OBJ *pParent;
    short uVar1;

    DG_Clip(&chnl->field_5C_clip_rect, chnl->field_50_clip_distance);

    ppObjs = (DG_OBJS **)chnl->mQueue;

    for (objects = chnl->mTotalObjectCount; objects > 0; objects--)
    {
        pObjs = *ppObjs++;

        if (!pObjs->bound_mode)
        {
            continue;
        }

        pObj = pObjs->objs;
        uVar5 = !(pObjs->flag & DG_FLAG_GBOUND);

        for (models = pObjs->n_models; models > 0; pObj++, models--)
        {
            if (!pObj->bound_mode)
            {
                continue;
            }

            pMdl = pObj->model;
            pParent = &pObjs->objs[pMdl->parent];

            ((POLY_GT4 **)pScratchpad)[0xfe] = pParent->packs[GV_Clock_800AB920];
            ((SVECTOR **)pScratchpad)[0xff] = pMdl->vertices;

            gte_SetRotMatrix(&pObj->screen);
            gte_SetTransMatrix(&pObj->screen);

            uVar1 = 0;

            if (uVar5 != 0)
            {
                uVar1 = pObj->bound_mode == 1;
            }

            pScratchpad[0xff] = uVar1;

            if (pObjs->flag & DG_FLAG_SHADE)
            {
                pScratchpad[0xff] |= 4;
            }

            DG_TransChanl_helper(pObj, idx);
        }
    }
}

void DG_TransEnd( void )
{
    /* do nothing */
}
