#include "libdg.h"
#include "common.h"

extern GV_HEAP       MemorySystems_800AD2F0[3];
extern unsigned int *ptr_800B1400[256];

#define SCRPAD_ADDR 0x1F800000

static inline DG_DivideMem *GetDivideMem()
{
    return (DG_DivideMem *)(SCRPAD_ADDR);
}

STATIC void *DG_SplitMemory( int memIdx, int* n_split, int size );
STATIC POLY_GT4 *DG_InitDividePacks( int memIdx );
STATIC void *DG_AllocDividePackMem( GV_HEAP *heap, GV_ALLOC **alloc_list, int *size );
STATIC POLY_GT4 *DG_GetDividePacks( void );
STATIC int  DG_GetRVectorCode( DG_RVECTOR *rvec );
STATIC void DG_SetRVectorCode( DG_RVECTOR *rvec );
STATIC void DG_SubdivideRVectorPoints( DG_RVECTOR *rvec1, DG_RVECTOR *rvec2, DG_RVECTOR *rvec3 );
STATIC void DG_SetRVectorDelta( DG_RVECTOR *rvec1, DG_RVECTOR *rvec2, DG_RVECTOR *rvec3 );
STATIC int  DG_CopyPackToRVector( DG_RVECTOR *rvec );
STATIC void DG_SubDivideRVectors( void );
STATIC void DG_InitRVector( DG_OBJ *obj,  int idx );
STATIC void DG_AddSubdividedPrim( DG_OBJ *obj, int idx );

STATIC void *DG_SplitMemory( int memIdx, int *n_split, int size )
{
    int i, split_count;
    GV_HEAP *heap;
    GV_ALLOC *alloc;

    split_count = 0;
    heap = &MemorySystems_800AD2F0[ memIdx ];

    alloc = heap->units;
    i = heap->used;
    while ( i > 0 )
    {
        if (alloc->state == GV_ALLOC_STATE_FREE)
        {
            split_count += (alloc[1].start - alloc[0].start ) / size;
        }
        --i;
        alloc++;
    }

    *n_split = split_count;
    return heap;
}

STATIC POLY_GT4 *DG_InitDividePacks( int memIdx )
{
    POLY_GT4 *pack;
    GV_HEAP  *heap;

    DG_DivideMem *divide_mem = GetDivideMem();

    heap = DG_SplitMemory( memIdx, &divide_mem->n_packs, 0x34 );

    divide_mem->pHeap = heap;
    divide_mem->pAlloc = 0;
    pack = DG_AllocDividePackMem( heap, &divide_mem->pAlloc, &divide_mem->size );

    divide_mem->pDataStart = pack;
    return pack;
}

void DG_DivideStart( void )
{
    /* do nothing */
}

STATIC void *DG_AllocDividePackMem( GV_HEAP *heap, GV_ALLOC **alloc_list, int *size )
{
    int i;
    int alloc_idx;
    GV_ALLOC *allocs;

    allocs = *alloc_list;

    if (!allocs)
    {
        allocs = heap->units;
    }
    else
    {
        allocs++;
    }

    //gets the number of allocs between the current one and the total
    alloc_idx  = (int)(allocs - 2);
    alloc_idx -= (int)heap;
    alloc_idx >>= 3;

    i = heap->used - alloc_idx;

    for ( ; i > 0 ; --i )
    {
        if ( allocs->state == GV_ALLOC_STATE_FREE )
        {
            alloc_list[0] = allocs;
            *size = allocs[1].start - allocs[0].start;
            return allocs->start;
        }
        allocs++;
    }

    *size = 0;
    return  0;
}

STATIC POLY_GT4 *DG_GetDividePacks( void )
{
    POLY_GT4        *pack_addr;
    DG_DivideMem    *divide_mem;

    divide_mem = GetDivideMem();

    divide_mem->size = divide_mem->size - 0x34;

    if (divide_mem->size < 0)
    {
        divide_mem->pDataStart = DG_AllocDividePackMem( divide_mem->pHeap, &divide_mem->pAlloc, &divide_mem->size );
    }
    else
    {
        divide_mem->n_packs -= 1;
        pack_addr = divide_mem->pDataStart;
        divide_mem->pDataStart += 0x34;
        return pack_addr;
    }

    if ( divide_mem->pDataStart )
    {
        return DG_GetDividePacks();
    }
    else
    {
        divide_mem->n_packs = 0;
        return 0;
    }
}

STATIC int DG_GetRVectorCode( DG_RVECTOR *rvec )
{
    int code;

    if ( !rvec->c.cd ) return 0;

    code = rvec[3].c.cd;

    return rvec->c.cd & rvec[1].c.cd & code & rvec[4].c.cd;
}

STATIC void DG_SetRVectorCode( DG_RVECTOR *rvec )
{
    char code = 0;

    if ( rvec->sxy.vx < -160 )
    {
        code = 1;
    }
    else if ( 160 < rvec->sxy.vx  )
    {
        code = 2;
    }

    if ( rvec->sxy.vy < -112 )
    {
        code |= 4;
    }
    else if ( 112 < rvec->sxy.vy )
    {
        code |= 8;
    }

    if ( !rvec->sz )
    {
        code |= 16;
    }

    rvec->c.cd = code;
}

STATIC void DG_SubdivideRVectorPoints( DG_RVECTOR *rvec1, DG_RVECTOR *rvec2, DG_RVECTOR *rvec3 )
{
    rvec3->v.vx = (rvec1->v.vx + rvec2->v.vx) / 2;
    rvec3->v.vy = (rvec1->v.vy + rvec2->v.vy) / 2;
    rvec3->v.vz = (rvec1->v.vz + rvec2->v.vz) / 2;

    rvec3->uv[0] = (rvec1->uv[0] + rvec2->uv[0]) / 2;
    rvec3->uv[1] = (rvec1->uv[1] + rvec2->uv[1]) / 2;

    rvec3->c.r = (rvec1->c.r + rvec2->c.r) / 2;
    rvec3->c.g = (rvec1->c.g + rvec2->c.g) / 2;
    rvec3->c.b = (rvec1->c.b + rvec2->c.b) / 2;
}

STATIC void DG_SetRVectorDelta( DG_RVECTOR *rvec1, DG_RVECTOR *rvec2, DG_RVECTOR *rvec3 )
{
    int vy_diff, vx_diff, delta;

    vy_diff = rvec2->sxy.vy - rvec1->sxy.vy;
    vx_diff = rvec1->sxy.vx - rvec2->sxy.vx;
    delta = GetDivideMem()->field_0C;

    if ( vy_diff >= 0 )
    {
        if (vx_diff >= 0)
        {
            if ( vx_diff / 2 < vy_diff )
            {
                rvec3->sxy.vx += delta;
            }
            //loc_80019370:
            if (vy_diff / 2 < vx_diff)
            {
                rvec3->sxy.vy += delta;
            }
        }
        else
        {
            //loc_80019398
            vx_diff = -vx_diff;
            if ( vx_diff / 2 < vy_diff )
            {
                rvec3->sxy.vx += delta;
            }
            //loc_8001941C:
            if (vy_diff / 2 < vx_diff)
            {
                rvec3->sxy.vy -= delta;
            }
        }
    }
    else
    {
        vy_diff = -vy_diff;
        if (vx_diff >= 0)
        {
            if ( vx_diff / 2 < vy_diff )
            {
                rvec3->sxy.vx -= delta;
            }
            //loc_80019370:
            if (vy_diff / 2 < vx_diff)
            {
                rvec3->sxy.vy += delta;
            }
        }
        else
        {
            //loc_800193EC
            vx_diff = -vx_diff;
            if ( vx_diff / 2 < vy_diff )
            {
                rvec3->sxy.vx -= delta;
            }
            //loc_8001941C:
            if (vy_diff / 2 < vx_diff)
            {
                rvec3->sxy.vy -= delta;
            }
        }
    }
}

STATIC int DG_CopyPackToRVector( DG_RVECTOR *rvec )
{
    int v1;
    DG_DivideMem    *divide_mem;
    DG_DivideMem    *divide_mem2;
    POLY_GT4        *pack;
    POLY_GT4        *pack2;
    long            *ot;
    int              z_idx;

    if ( DG_GetRVectorCode( rvec ) ) return 0;

    divide_mem = GetDivideMem();

    if ( ( (unsigned int)divide_mem->rvec < 0x1f800254 ) && ( divide_mem->n_packs >= 4 ) )
    {
        gte_NormalClip( *(int*)&rvec->sxy, *(int*)&rvec[1].sxy, *(int*)&rvec[3].sxy, &divide_mem->opz );
        v1 = divide_mem->opz;

        if ( v1 < 0 ) v1 = -v1;

        if ( divide_mem->field_14 < v1 )
        {
            DG_RVECTOR *rvec_temp = divide_mem->rvec;
            rvec_temp[0] = rvec[0];
            rvec_temp[2] = rvec[1];
            rvec_temp[6] = rvec[3];
            rvec_temp[8] = rvec[4];
            return 1;
        }
    }

    pack = DG_GetDividePacks();

    if ( !pack ) return 0;

    divide_mem2 = GetDivideMem();

    z_idx = (unsigned short)( ( ( rvec->sz + rvec[4].sz ) / 2 ) - divide_mem2->raise );

    if ( z_idx < 0 ) z_idx = 0;

    //loc_800195F0
    LCOPY2( &rvec[0].sxy, &pack->x0, &rvec[1].sxy, &pack->x1 );
    LCOPY2( &rvec[3].sxy, &pack->x2, &rvec[4].sxy, &pack->x3 );

    SCOPYL2( &rvec[0].uv, &pack->u0, &rvec[1].uv, &pack->u1 );
    SCOPYL2( &rvec[3].uv, &pack->u2, &rvec[4].uv, &pack->u3 );

    LCOPY2( &rvec[0].c, &pack->r0, &rvec[1].c, &pack->r1 );
    LCOPY2( &rvec[3].c, &pack->r2, &rvec[4].c, &pack->r3 );

    pack2 = divide_mem2->pack;
    pack->code = pack2->code;

    SCOPYL( &pack2->clut,  &pack->clut );
    SCOPYL( &pack2->tpage, &pack->tpage );

    ot = divide_mem2->ot;
    ot = &ot[ ( unsigned char ) z_idx ];

    //should be addPrim but has extra  stuff in there
    pack->tag = ( ( z_idx & 0xFF00 ) << 16 ) | ot[0];
    ot[0] = ( int )pack & 0xFFFFFF;
    return 0;
}

static inline void divide_setup( void )
{
    DG_RVECTOR *rvec;
    rvec = GetDivideMem()->rvec;

    DG_SubdivideRVectorPoints( &rvec[0], &rvec[2], &rvec[1] );
    DG_SubdivideRVectorPoints( &rvec[6], &rvec[8], &rvec[7] );

    gte_ldv3( &rvec[1], &rvec[1], &rvec[7] );
    gte_rtpt();

    DG_SubdivideRVectorPoints( &rvec[0], &rvec[6], &rvec[3] );
    DG_SubdivideRVectorPoints( &rvec[1], &rvec[7], &rvec[4] );
    DG_SubdivideRVectorPoints( &rvec[2], &rvec[8], &rvec[5] );

    gte_stsxy3( &rvec[1].sxy, &rvec[1].sxy, &rvec[7].sxy );
    gte_stsz3(  &rvec[1].sz, &rvec[1].sz, &rvec[7].sz );
    gte_ldv3( &rvec[3], &rvec[4] , &rvec[5] );
    gte_rtpt();

    DG_SetRVectorCode( &rvec[1] );
    DG_SetRVectorCode( &rvec[7] );
    DG_SetRVectorDelta( &rvec[0], &rvec[2], &rvec[1] );
    DG_SetRVectorDelta( &rvec[8], &rvec[6], &rvec[7] );

    gte_stsxy3( &rvec[3].sxy, &rvec[4].sxy, &rvec[5].sxy );
    gte_stsz3(  &rvec[3].sz, &rvec[4].sz, &rvec[5].sz );

    DG_SetRVectorCode( &rvec[3] );
    DG_SetRVectorCode( &rvec[4] );
    DG_SetRVectorCode( &rvec[5] );
    DG_SetRVectorDelta( &rvec[2], &rvec[8], &rvec[5] );
    DG_SetRVectorDelta( &rvec[6], &rvec[0], &rvec[3] );
}

//todo: odd function requires do while hack, need to revisit
STATIC void DG_SubDivideRVectors( void )
{
    int mask = 1;
    DG_DivideMem *divide_mem;

    divide_setup();
    do {} while (0); //hack thats needed to make it use the right registers

    divide_mem = GetDivideMem();

    divide_mem->rvec += 9;

    if ( DG_CopyPackToRVector( &divide_mem->rvec[-9] ) ) DG_SubDivideRVectors();
    if ( DG_CopyPackToRVector( &divide_mem->rvec[-8] ) ) DG_SubDivideRVectors();
    if ( DG_CopyPackToRVector( &divide_mem->rvec[-6] ) && mask ) DG_SubDivideRVectors();
    if ( DG_CopyPackToRVector( &divide_mem->rvec[-5] ) ) DG_SubDivideRVectors();

    divide_mem->rvec -= 9;
}

typedef struct cpystrct {
    unsigned long cpy[2];
} cpystrct;

static inline void copy_verts(unsigned char *faceIndexOffset, SVECTOR *vertexIndexOffset)
{
    *(cpystrct*)0x1F800038 = *(cpystrct*)&vertexIndexOffset[faceIndexOffset[0]];
    *(cpystrct*)0x1F800060 = *(cpystrct*)&vertexIndexOffset[faceIndexOffset[1]];
    *(cpystrct*)0x1F8000B0 = *(cpystrct*)&vertexIndexOffset[faceIndexOffset[3]];
    *(cpystrct*)0x1F8000D8 = *(cpystrct*)&vertexIndexOffset[faceIndexOffset[2]];
}

//function seems to call scratchpad addresses directly rather than through a struct
STATIC void DG_InitRVector( DG_OBJ *obj,  int idx )
{
    POLY_GT4     *pack;
    POLY_GT4     *org_pack;
    int           n_packs;

    org_pack = obj->packs[ idx ];
    *(short*)0x1F800006 = obj->raise;

    while ( obj )
    {
        unsigned char *faceIndexOffset   = obj->model->vindices;
        SVECTOR       *vertexIndexOffset = obj->model->vertices;
        n_packs = obj->n_packs;
        pack = org_pack;

        for ( --n_packs ; n_packs >= 0 ; --n_packs )
        {
            int pack_raise = pack->tag & 0xFFFF;
            int pack_addr  = pack->tag >> 8;

            if ( ( *(unsigned int*)0x1F800014 < pack_addr ) &&
                 ( pack_raise < *(int*)0x1F800018 )         &&
                 ( *(int*)0x1F800028 >= 4 ) )
            {
                *(short*)pack = 0;
                *(int*)0x1F80001C = (int)pack;

                if ( pack_addr & 0x100 )
                {
                    *(int*)0x1F80000C = -*(int*)0x1F800010;
                }
                else
                {
                    *(int*)0x1F80000C = *(int*)0x1F800010;
                }

                //loc_80019A04:
                *(int*)0x1F800034 = (int)0x1F800038;

                copy_verts( faceIndexOffset, vertexIndexOffset );

                LCOPY2(  &pack->x0 , (void*)0x1F800044 , &pack->x1 , (void*)0x1F80006C );
                LCOPY2(  &pack->x2 , (void*)0x1F8000BC , &pack->x3 , (void*)0x1F8000E4 );
                SCOPYL2( &pack->u0 , (void*)0x1F80003E , &pack->u1 , (void*)0x1F800066 );
                SCOPYL2( &pack->u2 , (void*)0x1F8000B6 , &pack->u3 , (void*)0x1F8000DE );
                LCOPY2(  &pack->r0 , (void*)0x1F800040 , &pack->r1 , (void*)0x1F800068 );
                LCOPY2(  &pack->r2 , (void*)0x1F8000B8 , &pack->r3 , (void*)0x1F8000E0 );

                gte_ldv3( 0x1F800060 , 0x1F8000B0 , 0x1F8000D8 );
                gte_rtpt();
                gte_stsz3( 0x1F800070 , 0x1F8000C0 , 0x1F8000E8 );

                gte_ldv0( 0x1F800038 );
                gte_rtps();
                gte_stsz( 0x1F800048 );

                DG_SetRVectorCode( (DG_RVECTOR*)0x1F800038 );
                DG_SetRVectorCode( (DG_RVECTOR*)0x1F800060 );
                DG_SetRVectorCode( (DG_RVECTOR*)0x1F8000B0 );
                DG_SetRVectorCode( (DG_RVECTOR*)0x1F8000D8 );
                DG_SubDivideRVectors();

            }
            else
            {
                if ( pack_raise )
                {
                    unsigned int  *ot;
                    unsigned short raise;

                    ot = (unsigned int *)(*(unsigned int *)0x1F800000);
                    raise = *(unsigned short *)0x1F800006;

                    raise = pack_raise - raise;
                    pack_raise = raise;
                    ot = &ot[ ( unsigned char ) pack_raise ];

                    //should be addPrim but has extra value
                    pack->tag = ( ( pack_raise & 0xFF00 ) << 16 ) | ( int )*ot;
                    *ot = ( int )pack & 0xFFFFFF;
                }
            }
            pack++;
            faceIndexOffset += 4;
        }

        obj = obj->extend;
        org_pack = pack;
    }
}

static inline void add_prim_mid( unsigned long *ot, POLY_GT4 *pack, int z_idx, int raise )
{
    unsigned long *temp;
    z_idx = (z_idx - raise);
    z_idx &= 0xFFFF;

    temp = &ot[ ( unsigned char ) z_idx ];

    //should be addPrim but has extra value
    pack->tag = ( ( z_idx & 0xFF00 ) << 16 ) | ( int )*temp;
    *temp = ( int )pack;
}

STATIC void DG_AddSubdividedPrim( DG_OBJ *obj, int idx )
{
    POLY_GT4      *org_pack;
    POLY_GT4      *pack;
    int            raise;
    int            n_packs;
    unsigned long *ot;
    unsigned long *ot_temp;
    unsigned short pack_raise;

    org_pack  = obj->packs[ idx ];
    raise = obj->raise; //t1

    while ( obj )
    {
        n_packs = obj->n_packs;
        pack = (POLY_GT4*)getaddr( &org_pack );

        //TODO: below three lines don't seem right but provide fake match
        ot = (unsigned long*)0x1F800000;
        ot = (unsigned long*)ot[0];
        ot_temp = ot;

        for ( --n_packs ; n_packs >= 0 ; --n_packs )
        {
            pack_raise = pack->tag;
            if ( pack_raise )
            {
                add_prim_mid( ot_temp, pack, pack_raise, raise );
            }
            pack++;
        }
        obj = obj->extend;
        org_pack = pack;
    }
}

void DG_DivideChanl( DG_CHANL *chanl, int idx )
{
    int i, j, x;
    DG_OBJS **objs_queue;
    DG_OBJS  *objs;
    DG_OBJ   *obj;
    DG_DivideMem *divide_mem;

    if ( !DG_InitDividePacks( idx ) ) return;

    DG_Clip( &chanl->field_5C_clip_rect, chanl->field_50_clip_distance );

    divide_mem = GetDivideMem();
    divide_mem->ot = (long *)ptr_800B1400;
    divide_mem->field_14 = 0x800;

    if ( chanl->field_50_clip_distance > 1000)
    {
        divide_mem->field_18 = 60000;
    }
    else
    {
        divide_mem->field_18 = 8192;
    }

    objs_queue = chanl->mQueue;
    //s6 = 1
    x = 1;
    for ( i = chanl->mTotalObjectCount ; i > 0 ; --i )
    {
        objs = *objs_queue;
        objs_queue++;

        if ( !objs->bound_mode ) continue;

        obj = objs->objs;
        if ( !( objs->flag & DG_FLAG_GBOUND ) )
        {
            for ( j = objs->n_models ; j > 0 ; --j )
            {
                if (obj->bound_mode)
                {
                    gte_SetRotMatrix( &obj->screen );
                    gte_SetTransMatrix( &obj->screen );

                    if ( obj->model->flags & DG_MODEL_TRANS )
                    {
                        GetDivideMem()->field_10 = 0;
                    }
                    else
                    {
                        GetDivideMem()->field_10 = x;
                    }

                    SetSpadStack( SPAD_STACK_ADDR );
                    DG_InitRVector( obj, idx );
                    ResetSpadStack();

                }
                obj++;
            }
        }
        else
        {
            for ( j = objs->n_models ; j > 0 ; --j )
            {
                if (obj->bound_mode)
                {
                    DG_AddSubdividedPrim( obj, idx );
                }
                obj++;
            }
        }
    }
}

void DG_DivideEnd( void )
{
    /* do nothing */
}
