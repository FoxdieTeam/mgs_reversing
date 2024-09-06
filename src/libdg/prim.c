#include "libdg.h"
#include "common.h"

extern int GV_Clock_800AB920;
extern int DG_CurrentGroupID_800AB968;

SVECTOR DG_ZeroVector_800AB39C = { 0, 0, 0, 0 };

/*** data *******************************************************/

//  DG_PRIM_LINE_FT2, DG_PRIM_LINE_GT2,
//  DG_PRIM_FREE
//  DG_PRIM_TILE_1  DG_PRIM_TILE_8, DG_PRIM_TILE_16

//  int psize, int verts, int voffset, int vstep ??
struct DG_Rec_Unknown stru_8009D3D0[24] = {
    { 16, 2, 8,  4 },   // LINE_F2 DG_PRIM_LINE_FT2
    { 24, 3, 8,  4 },   // LINE_F3
    { 28, 4, 8,  4 },   // LINE_F4
    { 20, 2, 8,  8 },   // LINE_G2
    { 32, 3, 8,  8 },   // LINE_G3
    { 40, 4, 8,  8 },   // LINE_G4
    { 20, 1, 8,  0 },   // SPRT
    { 16, 1, 8,  0 },   // SPRT_16  ?
    { 16, 1, 8,  0 },   // SPRT_8  ?
    { 16, 1, 8,  0 },   // TILE ?
    { 12, 1, 8,  0 },   // TILE_16  ?
    { 12, 1, 8,  0 },   // TILE_8 ?
    { 12, 1, 8,  0 },   // TILE_1 ?
    { 20, 3, 8,  4 },   // POLY_F3 DG_PRIM_POLY_F3
    { 24, 4, 8,  4 },   // POLY_F4 DG_PRIM_POLY_F4
    { 28, 3, 8,  8 },   // POLY_G3 DG_PRIM_POLY_G3
    { 36, 4, 8,  8 },   // POLY_G4 DG_PRIM_POLY_G4
    { 32, 3, 8,  8 },   // POLY_FT3 DG_PRIM_POLY_FT3
    { 40, 4, 8,  8 },   // POLY_FT4 DG_PRIM_POLY_FT4
    { 40, 3, 8, 12 },   // POLY_GT3 DG_PRIM_POLY_GT3
    { 52, 4, 8, 12 },   // POLY_GT4 DG_PRIM_POLY_GT4
    { 40, 2, 8,  8 },
    { 52, 2, 8, 12 },
    { 12, 1, 8,  0 }
};

MATRIX DG_ZeroMatrix_8009D430 = {
    {{0x1000, 0x0000, 0x0000},
     {0x0000, 0x1000, 0x0000},
     {0x0000, 0x0000, 0x1000}},
    {0, 0, 0}};

/****************************************************************/

#define STATIC
// #define STATIC static

// todo: rename all of these
STATIC void DG_8001AC08( DVECTOR *xy0, DVECTOR *xy1, DVECTOR *xy2, DVECTOR *xy3 );
STATIC void DG_8001AC74( DG_PRIM *prim, int prim_type );
STATIC SVECTOR *DG_8001AD28( SVECTOR *svec, int n_svec );
STATIC char *DG_PrimChanl_helper_helper( DG_PRIM *prim, char *ptr, int count );
STATIC void DG_PrimChanl_helper( DG_PRIM *prim );
STATIC char *DG_PrimChanl_helper2_helper_8001AF90( DG_PRIM *prim, char *ptr, int count );
STATIC void DG_PrimChanl_helper2( DG_PRIM *prim );
STATIC char *DG_8001B1E8( DG_PRIM *prim, char *ptr, int count );
STATIC void DG_8001B254( DG_PRIM *prim );
STATIC char *DG_PrimChanl_helper3_helper( DG_PRIM *prim, char *ptr, int count );
STATIC void DG_PrimChanl_helper3( DG_PRIM *prim );
STATIC void DG_8001B5FC( DG_PRIM *prim );

void DG_PrimStart( void )
{
    /* do nothing */
}

STATIC void DG_8001AC08( DVECTOR *xy0, DVECTOR *xy1, DVECTOR *xy2, DVECTOR *xy3 )
{
    int x0 = xy0->vx;
    int x1 = xy1->vx;
    int y0 = xy0->vy;
    int y1 = xy1->vy;
    int x1_x0_diff = x1 - x0;
    int y1_y0_diff = y1 - y0;

    if ( x1_x0_diff < 0 )
    {
        x1_x0_diff = -x1_x0_diff;
    }

    if ( y1_y0_diff < 0 )
    {
        y1_y0_diff = -y1_y0_diff;
    }

    if ( y1_y0_diff >= x1_x0_diff )
    {
        xy2->vx = x0 + 2;
        xy2->vy = y0;
        xy3->vx = x1 + 2;
        xy3->vy = y1;
    }
    else
    {
        xy2->vy = y0 + 1;
        xy2->vx = x0;
        xy3->vx = x1;
        xy3->vy = y1 + 1;
    }
}

STATIC void DG_8001AC74( DG_PRIM *prim, int prim_type )
{
    // TODO: Check if these prim types are actually correct when we have more context
    if ( prim_type == 21 )
    {
        int n_prims;
        POLY_FT4 *i = (POLY_FT4 *)prim->packs[GV_Clock_800AB920];
        for (n_prims = (signed short)prim->n_prims ; n_prims > 0; --n_prims )
        {
            DG_8001AC08((DVECTOR *)&i->x0, (DVECTOR *)&i->x1, (DVECTOR *)&i->x2, (DVECTOR *)&i->x3);
            i++;
        }
    }
    else // prim_type == 22 ?
    {
        int n_prims;
        POLY_GT4 *i = (POLY_GT4 *)prim->packs[GV_Clock_800AB920];
        for (n_prims = (signed short)prim->n_prims ; n_prims > 0; --n_prims )
        {
            DG_8001AC08((DVECTOR *)&i->x0, (DVECTOR *)&i->x1, (DVECTOR *)&i->x2, (DVECTOR *)&i->x3);
            i++;
        }
    }
}

// process vecs in spad
STATIC SVECTOR *DG_8001AD28( SVECTOR *svec, int n_svec )
{
  int      i;
  SVECTOR *svec2;

  svec2 = (SVECTOR*)0x1F800000;

  for ( i = n_svec - 1 ; i >= 0 ; --i )
  {
    gte_ldv3c( svec );
    gte_rtpt();
    gte_stsxy3( &svec2[0].vx, &svec2[1].vx, &svec2[2].vx );
    gte_stsz3(  &svec2[0].vz, &svec2[1].vz, &svec2[2].vz );
    svec  += 3;
    svec2 += 3;
  }

  return svec;
}

STATIC char *DG_PrimChanl_helper_helper( DG_PRIM *prim, char *ptr, int count )
{
    char *p;
    int t3, t2, t0, a0;
    SVECTOR *svec;
    count--;

    t3 = prim->field_30_prim_size;
    t0 = prim->field_32;
    t2 = prim->field_34;
    a0 = prim->field_36;

    svec = (SVECTOR*)0x1F800000;
    for ( ; count >= 0; --count )
    {
        p = ptr + t2;
        *(short*)ptr = svec->vz;

        switch( t0 )
        {
        case 4:
            LCOPY(svec, p);
            svec++;
            p += a0;
        case 3:
            LCOPY(svec, p);
            svec++;
            p += a0;
        case 2:
            LCOPY(svec, p);
            svec++;
            p += a0;
        case 1:
            LCOPY(svec, p);
            svec++;
        }
        ptr += t3;
    }
    return ptr;
}

STATIC void DG_PrimChanl_helper( DG_PRIM *prim )
{
    SVECTOR *svec;
    unsigned char *prims;
    int count, s4, n_svec, n_prims;

    s4 = prim->field_32;

    if ( s4 == 4 )
    {
        n_svec = 40;
        count  = 30;
    }
    else
    {
        n_svec = 42;
        count  = 126 / s4;
    }

    svec = prim->field_38_pUnknown;
    n_prims = prim->n_prims;
    prims = (unsigned char*)prim->packs[ GV_Clock_800AB920 ];

    if ( count < n_prims )
    {
        do
        {
            svec = DG_8001AD28( svec, n_svec );
            prims = DG_PrimChanl_helper_helper( prim, prims, count );
            n_prims -= count;
        } while ( count < n_prims );
    }

    DG_8001AD28( svec, ( ( n_prims * s4 ) + 2 ) / 3 );
    DG_PrimChanl_helper_helper( prim, prims, n_prims );
}

STATIC char *DG_PrimChanl_helper2_helper_8001AF90( DG_PRIM *prim, char *ptr, int count )
{
    char *p;
    int prim_size, t2, t0, a0;
    int *t3;
    SVECTOR *svec;
    count--;

    prim_size = prim->field_30_prim_size;
    t0 = prim->field_32;
    t2 = prim->field_34;
    a0 = prim->field_36;

    svec = (SVECTOR*)0x1F800000;

    for ( ; count >= 0; --count )
    {
        t3 = (int*)0x1F8003F0;
        gte_NormalClip( *(int*)&svec[0].vx, *(int*)&svec[1].vx, *(int*)&svec[2].vx, 0x1F8003F0 );
        p = ptr + t2;

        if (*t3 <= 0)
        {
            *(short*)ptr = 0;
            svec += t0;
        }
        else
        {
            SCOPYL(&svec->vz, ptr);
            switch( t0 )
            {
            case 4:
                gte_stsxy0( p );
                p += a0;
                svec++;
            case 3:
                gte_stsxy1( p );
                p += a0;
                svec++;
            case 2:
                gte_stsxy2( p );
                p += a0;
                svec++;
            case 1:
                LCOPY( svec, p );
                svec++;
            }
        }
        ptr += prim_size;
    }
    return ptr;
}

STATIC void DG_PrimChanl_helper2( DG_PRIM *prim )
{
    SVECTOR *svec;
    unsigned char *prims;
    int count, s4, n_svec, n_prims;

    s4 = prim->field_32;

    if ( s4 == 4 )
    {
        n_svec = 0x28;
        count  = 0x1E;
    }
    else
    {
        n_svec = 0x2A;
        count  = 126 / s4;
    }

    svec = prim->field_38_pUnknown; //s2
    n_prims = prim->n_prims; //s1
    prims = (unsigned char*)prim->packs[ GV_Clock_800AB920 ];

    if ( count < n_prims )
    {
        do
        {
            svec = DG_8001AD28( svec, n_svec );
            prims = DG_PrimChanl_helper2_helper_8001AF90( prim, prims, count );
            n_prims -= count;
        } while ( count < n_prims );
    }
    DG_8001AD28( svec, ((n_prims * s4) + 2) / 3 );
    DG_PrimChanl_helper2_helper_8001AF90( prim, prims, n_prims );
}

// read vecs from spad
STATIC char *DG_8001B1E8( DG_PRIM *prim, char *ptr, int count )
{
    //ptr = prim pointer
    RECT *rect;
    int prim_size;
    SVECTOR *svec;
    int rect_x, rect_y;

    rect = prim->field_3C;
    prim_size = prim->field_30_prim_size;
    rect_x = rect->x;
    rect_y = rect->y;

    svec = (SVECTOR*)0x1F800000;
    for ( --count ; count >= 0; --count )
    {
        *(short*)(ptr + 0x00) =  svec->vz;
        *(short*)(ptr + 0x08) = (svec->vx - rect_x);
        *(short*)(ptr + 0x0A) = (svec->vy - rect_y);

        svec++;
        ptr += prim_size;
    }

    return ptr;
}

// scratch pad memory max size in bytes
#define SPAD_SIZE 1024

// how many SVECTORS we can fit in the scratch pad bar one
#define MAX_SPAD_SVECTORS ((int)(SPAD_SIZE / sizeof(SVECTOR)) - 1)

// how many SVECTORS to process each iteration
#define BATCH_SIZE (MAX_SPAD_SVECTORS - 1)

STATIC void DG_8001B254( DG_PRIM *prim )
{
    SVECTOR *pVec = prim->field_38_pUnknown;
    int      n_prims = (signed short)prim->n_prims;
    short   *pPrims = (short *)prim->packs[GV_Clock_800AB920];

    // Process in batches if too big to fit in the scratch pad in one go
    if (n_prims >= MAX_SPAD_SVECTORS)
    {
        pVec = prim->field_38_pUnknown;
        do
        {
            pVec = DG_8001AD28(pVec, BATCH_SIZE / 3);
            pPrims = (short*)DG_8001B1E8(prim, (char*)pPrims, BATCH_SIZE);
            n_prims -= BATCH_SIZE;
        } while (n_prims >= MAX_SPAD_SVECTORS);
    }

    DG_8001AD28(pVec, (n_prims + 2) / 3);
    DG_8001B1E8(prim, (char*)pPrims, n_prims);
}

STATIC char *DG_PrimChanl_helper3_helper( DG_PRIM *prim, char *ptr, int count )
{
    char    *p;
    RECT    *rect;
    SVECTOR *svec;
    SVECTOR *svec_last;
    VECTOR  *vec;
    VECTOR  *vec_inner;
    int neg_x, neg_y, prim_size, t7, t1, i;
    SVECTOR local_svec[2];

    i = count;
    rect = prim->field_3C;

    neg_x = -rect->x;
    local_svec[0].vx = neg_x;
    neg_y = -rect->y;
    local_svec[0].vy = neg_y;
    local_svec[0].vz = 0;

    local_svec[1].vx = rect->w + neg_x;
    local_svec[1].vy = rect->h + neg_y;
    local_svec[1].vz = 0;

    gte_ldv01c ( local_svec );
    gte_SetRotMatrix( &DG_ZeroMatrix_8009D430 );

    vec = (VECTOR*)0x1F8003F0;
    svec = (SVECTOR*)0x1F800000;
    svec_last = (SVECTOR*)0x1F8003D8;
    prim_size = prim->field_30_prim_size;
    t7 = prim->field_34;
    t1 = prim->field_36;

    vec->vy = 0;
    vec->vx = 0;

    gte_SetGeomOffset( svec->vx , svec->vy );
    vec->vz = *(int*)&svec->vz;
    gte_SetTransVector( 0x1F8003F0 );
    gte_rtpt();

    svec++;
    gte_stsxy01( &svec_last->vx , &svec_last->vz );

    for ( --i ; i >= 0; --i )
    {
        vec_inner = (VECTOR*)0x1F8003F0;
        gte_SetGeomOffset( svec->vx , svec->vy );
        vec_inner->vz = *(int*)&svec->vz;
        gte_SetTransVector( 0x1F8003F0 );
        gte_rtpt();


        p = ptr + t7;
        *(short*)ptr = svec[-1].vz;
        svec++;

        *(long*)p = *(long*)&svec_last->vx;

        p += t1;
        *(short*)(p + 0) = svec_last->vz;
        *(short*)(p + 2) = svec_last->vy;

        p += t1;
        *(short*)(p + 0) = svec_last->vx;
        *(short*)(p + 2) = svec_last->pad;

        ptr += prim_size;
        p += t1;
        *(long*)p = *(long*)&svec_last->vz;

        gte_stsxy01( &svec_last->vx , &svec_last->vz );
    }

    gte_SetGeomOffset(0,0);
    return ptr;
}


// how many SVECTORS we can fit in the scratch pad bar four
#define MAX_SPAD_SVECTORS2 (int)(SPAD_SIZE / sizeof(SVECTOR))-4

// how many SVECTORS to process each iteration
#define BATCH_SIZE2 (MAX_SPAD_SVECTORS2-1)

STATIC void DG_PrimChanl_helper3( DG_PRIM *prim )
{
    SVECTOR *pVec = prim->field_38_pUnknown;
    int n_prims = (signed short)prim->n_prims;
    unsigned char *pPrims = (unsigned char*)prim->packs[GV_Clock_800AB920];

    // Process in batches if too big to fit in the scratch pad in one go
    if (n_prims >= MAX_SPAD_SVECTORS2)
    {
        pVec = prim->field_38_pUnknown;
        do
        {
            pVec = DG_8001AD28(pVec, BATCH_SIZE2 / 3);
            pPrims = DG_PrimChanl_helper3_helper(prim, pPrims, BATCH_SIZE2);
            n_prims -= BATCH_SIZE2;
        } while (n_prims >= MAX_SPAD_SVECTORS2);
    }

    DG_8001AD28(pVec, (n_prims + 2) / 3);
    DG_PrimChanl_helper3_helper(prim, pPrims, n_prims);
}

STATIC void DG_8001B5FC( DG_PRIM *prim )
{
    int       n_prims = prim->n_prims;
    POLY_FT4 *prims = &prim->packs[GV_Clock_800AB920]->poly_ft4;

    DG_8001AD28(prim->field_38_pUnknown, prim->field_48_prim_count);
    prim->field_50_pFn(prim, prims, n_prims);
}

//todo: this is dumb, must be something else
static inline void div_mtx( MATRIX *matrix, int val )
{
    matrix->m[1][0] = val;
    //matrix->m[1][0] = (matrix->m[1][0] * 58) / 64;
    matrix->m[1][1] = (matrix->m[1][1] * 58) / 64;
    matrix->m[1][2] = (matrix->m[1][2] * 58) / 64;

    matrix->t[1]    = (matrix->t[1]    * 58) / 64;
}

void DG_PrimChanl( DG_CHNL *chnl, int idx )
{
    int       i, type, group_id;
    MATRIX    local_mtx;
    MATRIX   *eye;
    DG_PRIM  *prim;
    DG_PRIM **prim_queue;
    RECT     *rect;
    int x;
    //s0 = chnl;

    i = chnl->mTotalQueueSize - chnl->mFreePrimCount;

    rect = &chnl->field_5C_clip_rect;
    if ( !i ) return;

    DG_Clip( rect, chnl->field_50_clip_distance );
    group_id = DG_CurrentGroupID_800AB968;
    eye = &chnl->field_10_eye_inv;
    prim_queue = (DG_PRIM**)&chnl->mQueue[ chnl->mFreePrimCount ];

    for ( ; i > 0 ; i-- )
    {
        prim = *prim_queue;
        prim_queue++;
        type = prim->type;

        if ( type & ( DG_PRIM_INVISIBLE | DG_PRIM_SORTONLY ) ) continue;

        if ( prim->group_id && !( prim->group_id & group_id ) ) continue;

        if ( ! ( type & DG_PRIM_UNKNOWN_200 ) )
        {
            if ( prim->root )
            {
                prim->world = *prim->root;
            }

            gte_CompMatrix( eye, &prim->world, &local_mtx );
            x = (local_mtx.m[1][0] * 58) / 64;
            div_mtx( &local_mtx, x );
            gte_SetRotMatrix( &local_mtx );
            gte_SetTransMatrix( &local_mtx );
        }
        else
        {
            gte_SetRotMatrix( &DG_ZeroMatrix_8009D430 );
            gte_SetTransMatrix( &DG_ZeroMatrix_8009D430 );
        }

        if ( ! ( type & DG_PRIM_FREEPACKS ) )
        {
            if ( ! ( type & DG_PRIM_UNKNOWN_400 ) )
            {
                if (  ( type & DG_PRIM_ONEFREE ) )
                {
                    DG_PrimChanl_helper2( prim );
                }
                else
                {
                    DG_PrimChanl_helper( prim );
                }
            }
            else
            {
                if ( prim->field_32 == 1 )
                {
                    DG_8001B254( prim );
                }
                else
                {
                    DG_PrimChanl_helper3( prim );
                }
            }
        }
        else
        {
            DG_8001B5FC( prim );
        }

        type &= 0x1F;
        if ( type - 0x15 < 2u )
        {
            DG_8001AC74( prim, type );
        }
    }
}

void DG_PrimEnd( void )
{
    /* do nothing */
}

DG_PRIM *DG_MakePrim( int type, int prim_count, int chanl, SVECTOR *svec, RECT *rect )
{
    const struct DG_Rec_Unknown *pRec = &stru_8009D3D0[type & 31];
    const int prim_size = pRec->field_0_prim_size * prim_count;

    DG_PRIM *prim = GV_Malloc(sizeof(DG_PRIM) + (prim_size * 2));
    if (!prim)
    {
        return 0;
    }

    GV_ZeroMemory(prim, sizeof(DG_PRIM));
    prim->world = DG_ZeroMatrix_8009D430;

    prim->type = type;
    prim->n_prims = prim_count;
    prim->chanl = chanl;
    prim->field_38_pUnknown = svec;
    prim->field_3C = rect;

    // Copy struct
    prim->field_30_prim_size = pRec->field_0_prim_size;
    prim->field_32 = pRec->field_1;
    prim->field_34 = pRec->field_2;
    prim->field_36 = pRec->field_3;

    // Point to data after the end of the structure
    prim->packs[0] = (union Prim_Union *)&prim[1];
    prim->packs[1] = (union Prim_Union *)((char *)&prim[1] + prim_size);

    return prim;
}

void DG_FreePrim( DG_PRIM *prim )
{
    if (prim)
    {
        GV_DelayedFree(prim);
    }
}

void DG_SetFreePrimParam( int psize, int verts, int voffset, int vstep )
{
    struct DG_Rec_Unknown *pRec = &stru_8009D3D0[23];
    pRec->field_0_prim_size = psize;
    pRec->field_1 = verts;
    pRec->field_2 = voffset;
    pRec->field_3 = vstep;
}
