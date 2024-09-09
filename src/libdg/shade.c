#include "libdg.h"
#include "common.h"

/**gp*******************************************/
extern unsigned long DG_PacketCode_800AB394[2];
/***********************************************/

/**data*******************************/
extern SVECTOR DG_Ambient_800AB38C;
/*************************************/

void DG_ShadeStart( void )
{
    /* do nothing */
}

//just an index using an int shifted to get each byte of the face normal idx, but didnt match that way
static inline void DG_ShadePack( unsigned int *nindices, POLY_GT4 *packs, char *colors )
{
    unsigned int f0, f1, f2, f3;

    f0 = *nindices;
    f1 = *nindices;
    f2 = *nindices;
    f3 = *nindices;

    f0 <<= 2;
    f1 >>= 6;
    f2 >>= 22;
    f3 >>= 14;

    f0 &= 0x3FC;
    f1 &= 0x3FC;
    f2 &= 0x3FC;
    f3 &= 0x3FC;

    f0 = (int)(colors + f0);
    f1 = (int)(colors + f1);
    f2 = (int)(colors + f2);
    f3 = (int)(colors + f3);

    LCOPY2( (void *)f0, &packs->r0, (void *)f1, &packs->r1 );
    LCOPY2( (void *)f2, &packs->r2, (void *)f3, &packs->r3 );
}

STATIC POLY_GT4 *DG_ShadePacks( unsigned int *nindices, POLY_GT4 *packs, int n_packs )
{
    void *colors;

    for ( n_packs--; n_packs >= 0; n_packs-- )
    {
        colors = getScratchAddr(8);

        if ( packs->tag & 0xFFFF )
        {
            DG_ShadePack( nindices, packs, colors );
        }

        packs++;
        nindices++;
    }

    return packs;
}

STATIC POLY_GT4 *DG_ShadePacksIndirect( unsigned int *nindices, POLY_GT4 *packs, int n_packs, unsigned int *vindices )
{
    void        *colors;
    unsigned int mask;
    unsigned int f0, f1, f2, f3;
    unsigned int v0123;
    int          color;

    for ( n_packs--; n_packs >= 0; packs++, nindices++, vindices++, n_packs-- )
    {
        mask = 0x80808080;

        colors = getScratchAddr(8);

        f0 = *nindices;

        if ( !( packs->tag & 0xFFFF ) && !( *nindices & mask ) ) continue;

        v0123 = *vindices;
        f3 = *nindices;
        f0 = *nindices << 2;
        f1 = *nindices >> 6;
        f2 = *nindices >> 22;
        f3 = *nindices >> 14;

        f0 &= 0x1FC;
        f1 &= 0x1FC;
        f2 &= 0x1FC;
        f3 &= 0x1FC;

        f0 += (unsigned int)colors;
        f1 += (unsigned int)colors;
        f2 += (unsigned int)colors;
        f3 += (unsigned int)colors;

        if ( v0123 & mask )
        {
            if ( v0123 & 0x80 )
            {
                color = **(int **)&packs->r0;
            }
            else
            {
                color = *(int *)f0;
            }
            v0123 >>= 8;
            *(int *)&packs->r0 = color;

            if ( v0123 & 0x80 )
            {
                color = **(int **)&packs->r1;
            }
            else
            {
                color = *(int *)f1;
            }
            v0123 >>= 8;
            *(int *)&packs->r1 = color;

            if ( v0123 & 0x80 )
            {
                color = **(int **)&packs->r3;
            }
            else
            {
                color = *(int *)f3;
            }
            v0123 >>= 8;
            *(int *)&packs->r3 = color;

            if ( v0123 & 0x80 )
            {
                color = **(int **)&packs->r2;
            }
            else
            {
                color = *(int *)f2;
            }
            v0123 >>= 8;
            *(int *)&packs->r2 = color;

        }
        else
        {
            LCOPY2( (void *)f0, &packs->r0, (void *)f1, &packs->r1 );
            LCOPY2( (void *)f2, &packs->r2, (void *)f3, &packs->r3 );
        }
    }

    return packs;
}

STATIC void DG_ShadeObj( DG_OBJ *obj, int idx )
{
    typedef struct { int d0, d1, d2; } Unit;

    POLY_GT4 *packs;
    DG_MDL   *model;
    Unit     *normals;
    int       n_normals;
    Unit     *scratch;

    for ( packs = obj->packs[ idx ]; obj; obj = obj->extend )
    {
        model = obj->model;

        gte_ldrgb( ( model->flags & DG_MODEL_TRANS ) ?
                   &DG_PacketCode_800AB394[1] :
                   &DG_PacketCode_800AB394[0] );

        normals = (Unit *)model->normals;
        n_normals = model->n_normals;

        *(Unit *)getScratchAddr(8) = normals[0];
        *(Unit *)getScratchAddr(11) = normals[1];

        scratch = (Unit *)getScratchAddr(8);
        while ( n_normals > 0 )
        {
            gte_ldv3c( scratch );

            n_normals -= 3;
            normals += 2;

            gte_nct_b();
            scratch++;

            scratch[0] = normals[0];
            scratch[1] = normals[1];

            gte_strgb3( &scratch[-1].d0, &scratch[-1].d1, &scratch[-1].d2 );
        }

        if ( !( model->flags & DG_MODEL_INDIRECT ) )
        {
            packs = DG_ShadePacks( (unsigned int *)model->nindices, packs, obj->n_packs );
        }
        else
        {
            packs = DG_ShadePacksIndirect( (unsigned int *)model->nindices, packs, obj->n_packs, (unsigned int *)model->vindices );
        }
    }
}

void DG_ShadeChanl( DG_CHNL *chnl, int idx )
{
    DG_OBJS **queue;
    int       n_objs;
    DG_OBJS  *objs;
    DG_OBJ   *obj;
    int       n_models;

    queue = chnl->mQueue;
    for ( n_objs = chnl->mTotalObjectCount; n_objs > 0 ; n_objs-- )
    {
        objs = *queue++;

        // TODO: figure out the values for bound_mode
        if ( objs->bound_mode == 0 )
        {
            continue;
        }

        if ( !( objs->flag & DG_FLAG_SHADE ) )
        {
            continue;
        }

        gte_SetRotMatrix( objs->light );
        gte_SetColorMatrix( objs->light + 1 );

        if ( objs->flag & DG_FLAG_AMBIENT )
        {
            gte_SetBackColor( objs->light->t[0], objs->light->t[1], objs->light->t[2] );
        }

        obj = objs->objs;
        for ( n_models = objs->n_models; n_models > 0 ; n_models-- )
        {
            if ( obj->bound_mode != 0 )
            {
                DG_MulRotMatrix0( &obj->world, getScratchAddr(0) );
                gte_SetLightMatrix( getScratchAddr(0) );

                DG_ShadeObj( obj, idx );
            }

            obj++;
        }

        if ( objs->flag & DG_FLAG_AMBIENT )
        {
            gte_SetBackColor( DG_Ambient_800AB38C.vx, DG_Ambient_800AB38C.vy, DG_Ambient_800AB38C.vz );
        }
    }
}

void DG_ShadeEnd( void )
{
    /* do nothing */
}
