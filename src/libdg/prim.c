#include "libdg.h"
#include "common.h"

extern int GV_Clock_800AB920;
extern int DG_CurrentGroupID_800AB968;

SVECTOR DG_ZeroVector_800AB39C = { 0, 0, 0, 0 };

/*** data *******************************************************/

// psize, verts, voffset, vstep
DG_PRIM_INFO DG_PrimInfos_8009D3D0[DG_PRIM_MAX] = {
    { 16, 2, 8,  4 }, // DG_PRIM_LINE_F2
    { 24, 3, 8,  4 }, // DG_PRIM_LINE_F3
    { 28, 4, 8,  4 }, // DG_PRIM_LINE_F4
    { 20, 2, 8,  8 }, // DG_PRIM_LINE_G2
    { 32, 3, 8,  8 }, // DG_PRIM_LINE_G3
    { 40, 4, 8,  8 }, // DG_PRIM_LINE_G4
    { 20, 1, 8,  0 }, // DG_PRIM_SPRT
    { 16, 1, 8,  0 }, // DG_PRIM_SPRT_8
    { 16, 1, 8,  0 }, // DG_PRIM_SPRT_16
    { 16, 1, 8,  0 }, // DG_PRIM_TILE
    { 12, 1, 8,  0 }, // DG_PRIM_TILE_1
    { 12, 1, 8,  0 }, // DG_PRIM_TILE_8
    { 12, 1, 8,  0 }, // DG_PRIM_TILE_16
    { 20, 3, 8,  4 }, // DG_PRIM_POLY_F3
    { 24, 4, 8,  4 }, // DG_PRIM_POLY_F4
    { 28, 3, 8,  8 }, // DG_PRIM_POLY_G3
    { 36, 4, 8,  8 }, // DG_PRIM_POLY_G4
    { 32, 3, 8,  8 }, // DG_PRIM_POLY_FT3
    { 40, 4, 8,  8 }, // DG_PRIM_POLY_FT4
    { 40, 3, 8, 12 }, // DG_PRIM_POLY_GT3
    { 52, 4, 8, 12 }, // DG_PRIM_POLY_GT4
    { 40, 2, 8,  8 }, // DG_PRIM_LINE_FT2
    { 52, 2, 8, 12 }, // DG_PRIM_LINE_GT2
    { 12, 1, 8,  0 }  // DG_PRIM_FREE
};

MATRIX DG_ZeroMatrix_8009D430 = {
    {{0x1000, 0x0000, 0x0000},
     {0x0000, 0x1000, 0x0000},
     {0x0000, 0x0000, 0x1000}},
    {0, 0, 0}};

/****************************************************************/

// Number of vertices to process at once
// ( 1024 / sizeof(SVECTOR) ) - 2
#define BATCH_SIZE 126

void DG_PrimStart( void )
{
    /* do nothing */
}

STATIC void DG_AdjustLaserPrim( DVECTOR *xy0, DVECTOR *xy1, DVECTOR *xy2, DVECTOR *xy3 )
{
    int x0 = xy0->vx;
    int x1 = xy1->vx;
    int y0 = xy0->vy;
    int y1 = xy1->vy;

    int dx = x1 - x0;
    int dy = y1 - y0;

    if ( dx < 0 )
    {
        dx = -dx;
    }

    if ( dy < 0 )
    {
        dy = -dy;
    }

    if ( dy >= dx )
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

STATIC void DG_AdjustLaserPrims( DG_PRIM *prim, int type )
{
    POLY_FT4 *ft2;
    POLY_GT4 *gt2;
    int       i;

    if ( type == DG_PRIM_LINE_FT2 )
    {
        ft2 = (POLY_FT4 *)prim->packs[GV_Clock_800AB920];

        for (i = prim->n_prims ; i > 0; --i )
        {
            DG_AdjustLaserPrim((DVECTOR *)&ft2->x0, (DVECTOR *)&ft2->x1, (DVECTOR *)&ft2->x2, (DVECTOR *)&ft2->x3);
            ft2++;
        }
    }
    else // type == DG_PRIM_LINE_GT2
    {
        gt2 = (POLY_GT4 *)prim->packs[GV_Clock_800AB920];

        for (i = prim->n_prims ; i > 0; --i )
        {
            DG_AdjustLaserPrim((DVECTOR *)&gt2->x0, (DVECTOR *)&gt2->x1, (DVECTOR *)&gt2->x2, (DVECTOR *)&gt2->x3);
            gt2++;
        }
    }
}

// process vecs in spad
STATIC SVECTOR *DG_TransformVertices( SVECTOR *in, int n_verts )
{
    SVECTOR *out;

    out = (SVECTOR *)getScratchAddr(0);
    for ( --n_verts ; n_verts >= 0 ; n_verts-- )
    {
        gte_ldv3c( in );
        gte_rtpt();
        gte_stsxy3( &out[0].vx, &out[1].vx, &out[2].vx );
        gte_stsz3(  &out[0].vz, &out[1].vz, &out[2].vz );
        in += 3;
        out += 3;
    }

    return in;
}

STATIC char *DG_WritePrimVertices( DG_PRIM *prim, char *out, int n_prims )
{
    int      psize;
    int      verts;
    int      voffset;
    int      vstep;
    SVECTOR *in;
    char    *vert;

    psize = prim->psize;
    verts = prim->verts;
    voffset = prim->voffset;
    vstep = prim->vstep;

    in = (SVECTOR *)getScratchAddr(0);

    for ( n_prims--; n_prims >= 0; n_prims-- )
    {
        vert = out + voffset;

        SCOPYL(&in->vz, out);

        switch( verts )
        {
        case 4:
            LCOPY(in, vert);
            vert += vstep;
            in++;

        case 3:
            LCOPY(in, vert);
            vert += vstep;
            in++;

        case 2:
            LCOPY(in, vert);
            vert += vstep;
            in++;

        case 1:
            LCOPY(in, vert);
            in++;
        }

        out += psize;
    }

    return out;
}

STATIC void DG_TransformPrim( DG_PRIM *prim )
{
    int      n_verts;
    int      vert_batch;
    int      prim_batch;
    SVECTOR *verts;
    char    *packs;
    int      n_prims;

    n_verts = prim->verts;

    if ( n_verts == 4 )
    {
        vert_batch = 40;
        prim_batch = 30;
    }
    else
    {
        vert_batch = 42;
        prim_batch = BATCH_SIZE / n_verts;
    }

    verts = prim->vertices;
    packs = (char *)prim->packs[ GV_Clock_800AB920 ];

    for ( n_prims = prim->n_prims; n_prims > prim_batch; n_prims -= prim_batch )
    {
        verts = DG_TransformVertices( verts, vert_batch );
        packs = DG_WritePrimVertices( prim, packs, prim_batch );
    }

    DG_TransformVertices( verts, ( n_prims * n_verts + 2 ) / 3 );
    DG_WritePrimVertices( prim, packs, n_prims );
}

STATIC char *DG_WritePrimVerticesOneFace( DG_PRIM *prim, char *out, int n_prims )
{
    int      psize;
    int      verts;
    int      voffset;
    int      vstep;
    SVECTOR *in;
    char    *vert;
    int     *area;

    psize = prim->psize;
    verts = prim->verts;
    voffset = prim->voffset;
    vstep = prim->vstep;

    in = (SVECTOR *)getScratchAddr(0);

    for ( n_prims--; n_prims >= 0; n_prims-- )
    {
        area = (int *)getScratchAddr(252);
        gte_NormalClip( *(int *)&in[0].vx, *(int *)&in[1].vx, *(int *)&in[2].vx, getScratchAddr(252) );

        vert = out + voffset;

        if ( *area <= 0 )
        {
            SSTOREL(0, out);
            in += verts;
        }
        else
        {
            SCOPYL(&in->vz, out);

            switch( verts )
            {
            case 4:
                gte_stsxy0( vert );
                vert += vstep;
                in++;

            case 3:
                gte_stsxy1( vert );
                vert += vstep;
                in++;

            case 2:
                gte_stsxy2( vert );
                vert += vstep;
                in++;

            case 1:
                LCOPY(in, vert);
                in++;
            }
        }

        out += psize;
    }

    return out;
}

STATIC void DG_TransformPrimOneFace( DG_PRIM *prim )
{
    int      n_verts;
    int      vert_batch;
    int      prim_batch;
    SVECTOR *verts;
    char    *packs;
    int      n_prims;

    n_verts = prim->verts;

    if ( n_verts == 4 )
    {
        vert_batch = 40;
        prim_batch = 30;
    }
    else
    {
        vert_batch = 42;
        prim_batch = BATCH_SIZE / n_verts;
    }

    verts = prim->vertices;
    packs = (char *)prim->packs[ GV_Clock_800AB920 ];

    for ( n_prims = prim->n_prims; n_prims > prim_batch; n_prims -= prim_batch )
    {
        verts = DG_TransformVertices( verts, vert_batch );
        packs = DG_WritePrimVerticesOneFace( prim, packs, prim_batch );
    }

    DG_TransformVertices( verts, ( n_prims * n_verts + 2 ) / 3 );
    DG_WritePrimVerticesOneFace( prim, packs, n_prims );
}

STATIC char *DG_WritePrimVerticesOffsetSingle( DG_PRIM *prim, char *out, int n_prims )
{
    RECT    *rect;
    int      psize;
    int      x, y;
    SVECTOR *in;

    rect = prim->field_3C;
    psize = prim->psize;

    x = rect->x;
    y = rect->y;

    in = (SVECTOR *)getScratchAddr(0);

    for ( n_prims--; n_prims >= 0; n_prims-- )
    {
        SCOPYL(&in->vz, out);
        SSTOREL(in->vx - x, out + 8);
        SSTOREL(in->vy - y, out + 10);

        in++;
        out += psize;
    }

    return out;
}

STATIC void DG_TransformPrimOffsetSingle( DG_PRIM *prim )
{
    SVECTOR *verts;
    char    *packs;
    int      n_prims;

    verts = prim->vertices;
    packs = (char *)prim->packs[GV_Clock_800AB920];

    for ( n_prims = prim->n_prims; n_prims > BATCH_SIZE; n_prims -= BATCH_SIZE )
    {
        verts = DG_TransformVertices(verts, BATCH_SIZE / 3);
        packs = DG_WritePrimVerticesOffsetSingle(prim, packs, BATCH_SIZE);
    }

    DG_TransformVertices(verts, ( n_prims + 2 ) / 3);
    DG_WritePrimVerticesOffsetSingle(prim, packs, n_prims);
}

#define INIT_GEOM_OFFSET( addr ) \
    ((VECTOR *)(addr))->vy = 0;  \
    ((VECTOR *)(addr))->vx = 0;

#define SET_GEOM_OFFSET( vec, addr )             \
    gte_SetGeomOffset( (vec)->vx , (vec)->vy );  \
    ((VECTOR *)(addr))->vz = *(int *)&(vec)->vz; \
    gte_SetTransVector( addr );

STATIC char *DG_WritePrimVerticesOffset( DG_PRIM *prim, char *out, int n_prims )
{
    SVECTOR  bound[2];
    RECT    *rect;
    int      x, y;
    int      psize;
    int      voffset;
    int      vstep;
    SVECTOR *in;
    DVECTOR *processed;
    char    *vert;

    rect = prim->field_3C;

    x = -rect->x;
    bound[0].vx = x;

    y = -rect->y;
    bound[0].vy = y;
    bound[0].vz = 0;

    bound[1].vx = rect->w + x;
    bound[1].vy = rect->h + y;
    bound[1].vz = 0;

    gte_ldv01c ( bound );
    gte_SetRotMatrix( &DG_ZeroMatrix_8009D430 );

    psize = prim->psize;
    voffset = prim->voffset;
    vstep = prim->vstep;

    INIT_GEOM_OFFSET( getScratchAddr(252) );

    in = (SVECTOR *)getScratchAddr(0);
    processed = (DVECTOR *)getScratchAddr(246);

    SET_GEOM_OFFSET( in, (VECTOR *)getScratchAddr(252) );
    gte_rtpt();

    in++;

    gte_stsxy01( &processed[0] , &processed[1] );

    for ( n_prims--; n_prims >= 0; n_prims-- )
    {
        SET_GEOM_OFFSET( in, (VECTOR *)getScratchAddr(252) );
        gte_rtpt();

        vert = out + voffset;

        SSTOREL( in[-1].vz, out );

        LCOPY( &processed[0], vert );
        vert += vstep;

        SSTOREL( processed[1].vx, vert + 0 );
        SSTOREL( processed[0].vy, vert + 2 );
        vert += vstep;

        SSTOREL( processed[0].vx, vert + 0 );
        SSTOREL( processed[1].vy, vert + 2 );
        vert += vstep;

        LCOPY( &processed[1], vert );

        in++;
        out += psize;

        gte_stsxy01( &processed[0] , &processed[1] );
    }

    gte_SetGeomOffset( 0, 0 );
    return out;
}

STATIC void DG_TransformPrimOffset( DG_PRIM *prim )
{
    SVECTOR *verts;
    char    *packs;
    int      n_prims;

    verts = prim->vertices;
    packs = (char *)prim->packs[GV_Clock_800AB920];

    for ( n_prims = prim->n_prims; n_prims > (BATCH_SIZE - 3); n_prims -= (BATCH_SIZE - 3) )
    {
        verts = DG_TransformVertices(verts, (BATCH_SIZE - 3) / 3);
        packs = DG_WritePrimVerticesOffset(prim, packs, (BATCH_SIZE - 3));
    }

    DG_TransformVertices(verts, ( n_prims + 2 ) / 3);
    DG_WritePrimVerticesOffset(prim, packs, n_prims);
}

STATIC void DG_TransformPrimFreePacks( DG_PRIM *prim )
{
    int       n_prims;
    POLY_FT4 *packs;

    n_prims = prim->n_prims;
    packs = (POLY_FT4 *)prim->packs[GV_Clock_800AB920];

    DG_TransformVertices(prim->vertices, prim->n_vertices);
    prim->handler(prim, packs, n_prims);
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

        if ( !( type & DG_PRIM_SCREEN ) )
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

        if ( !( type & DG_PRIM_FREEPACKS ) )
        {
            if ( !( type & DG_PRIM_OFFSET ) )
            {
                if ( type & DG_PRIM_ONEFACE )
                {
                    DG_TransformPrimOneFace( prim );
                }
                else
                {
                    DG_TransformPrim( prim );
                }
            }
            else
            {
                if ( prim->verts == 1 )
                {
                    DG_TransformPrimOffsetSingle( prim );
                }
                else
                {
                    DG_TransformPrimOffset( prim );
                }
            }
        }
        else
        {
            DG_TransformPrimFreePacks( prim );
        }

        type &= 0x1F;
        if ( type == DG_PRIM_LINE_FT2 || type == DG_PRIM_LINE_GT2 )
        {
            DG_AdjustLaserPrims( prim, type );
        }
    }
}

void DG_PrimEnd( void )
{
    /* do nothing */
}

DG_PRIM *DG_MakePrim( int type, int prim_count, int chanl, SVECTOR *vertices, RECT *rect )
{
    const DG_PRIM_INFO *pRec = &DG_PrimInfos_8009D3D0[type & 31];
    const int prim_size = pRec->psize * prim_count;

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
    prim->vertices = vertices;
    prim->field_3C = rect;

    // copy prim info
    prim->psize = pRec->psize;
    prim->verts = pRec->verts;
    prim->voffset = pRec->voffset;
    prim->vstep = pRec->vstep;

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
    DG_PRIM_INFO *info;

    info = &DG_PrimInfos_8009D3D0[DG_PRIM_FREE];
    info->psize = psize;
    info->verts = verts;
    info->voffset = voffset;
    info->vstep = vstep;
}
