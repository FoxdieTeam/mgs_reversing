#include "libdg.h"
#include "common.h"
#include "game/game.h"

STATIC void DG_BoundIrTexture(DG_CHANL *chanl, int idx);

typedef struct {
    int vx, vy, vz;
} VECTOREX;

typedef	struct {
    VECTOREX bound_min;
    VECTOREX bound_max;
    SVECTOR  clip[ 3 ];
    DVECTOR  vxy[ 4 ][ 3 ];
    long     vzp[ 4 ][ 3 ];
} ScrPad;

#define SCRPAD      ((ScrPad *)SCRPAD_ADDR)

#define	BOUND_MIN   (&(SCRPAD->bound_min))
#define	BOUND_MAX   (&(SCRPAD->bound_max))
#define	CLIP        (SCRPAD->clip)
#define	VXY         (SCRPAD->vxy)
#define	VZP         (SCRPAD->vzp)

void DG_BoundStart( void )
{
    /* do nothing */
}

static inline void CopyBounds( int *input )
{
    BOUND_MIN->vx = input[ 0 ];
    BOUND_MIN->vy = input[ 1 ];
    BOUND_MIN->vz = input[ 2 ];
    BOUND_MAX->vx = input[ 3 ];
    BOUND_MAX->vy = input[ 4 ];
    BOUND_MAX->vz = input[ 5 ];
}

static inline void GetClipBounds( int flag, SVECTOR *clip )
{
    clip->vx = ( flag & 1 ) ? BOUND_MAX->vx : BOUND_MIN->vx;
    clip->vy = ( flag & 2 ) ? BOUND_MAX->vy : BOUND_MIN->vy;
    clip->vz = ( flag & 4 ) ? BOUND_MAX->vz : BOUND_MIN->vz;
}

static inline int GetDepthBoundMode( int xl, int yl, int xh, int yh )
{
    int i, mode;
    long *depth;

    if ( xh > 160 || xl < -160 || yh > 112 || yl < -112 )
    {
        /* prim partially on-screen */
        mode = 1;
    }
    else
    {
        /* prim entirely on-screen */
        mode = 2;
    }

    depth = VZP[ 1 ];
    for ( i = 8; i > 0; i-- )
    {
        if ( *depth != 0 ) return mode;
        depth++;
    }

    /* clip prim with zero depth */
    return 0;
}

static inline int GetBoundMode( DVECTOR *vert )
{
    int i, mode;
    int xl, yl, xh, yh;

    xh = xl = VXY[ 1 ][ 0 ].vx;
    yh = yl = VXY[ 1 ][ 0 ].vy;

    for ( i = 7; i > 0; i-- )
    {
        vert++;

        if ( vert->vx < xl )
        {
            xl = vert->vx;
        }
        else if ( vert->vx > xh )
        {
            xh = vert->vx;
        }

        if ( vert->vy < yl )
        {
            yl = vert->vy;
        }
        else if ( vert->vy > yh )
        {
            yh = vert->vy;
        }
    }

    if ( xl > 160 || xh < -160 || yl > 112 || yh < -112 )
    {
        /* prim completely off-screen */
        mode = 0;
    }
    else
    {
        /* prim on-screen, check against depth */
        mode = GetDepthBoundMode( xl, yl, xh, yh );
    }

    return mode;
}

STATIC void DG_BoundObjs( DG_OBJS *objs, int pack, int flag, int check )
{
    int i, j, mode, n_models;
    DG_OBJ *obj;
    SVECTOR *clip;
    DVECTOR *vxy;
    long *vzp;

    obj = objs->objs;
    for ( n_models = objs->n_models; n_models > 0; n_models-- )
    {
        mode = 0;

        if ( check )
        {
            mode = 2;

            if ( flag & DG_FLAG_BOUND )
            {
                gte_SetRotMatrix( &obj->screen );
                gte_SetTransMatrix( &obj->screen );

                CopyBounds( &obj->model->lx );
                clip = CLIP;
                vxy = VXY[ 0 ];
                vzp = VZP[ 0 ];

                for ( i = 9; i > 0; )
                {
                    for ( j = 3; j > 0; j-- )
                    {
                        GetClipBounds( i, clip );
                        clip++;
                        i--;
                    }

                    clip = CLIP;
                    gte_stsxy3c( vxy );
                    gte_stsz3c( vzp );

                    gte_ldv3c( CLIP );
                    vxy += 3;
                    vzp += 3;
                    gte_rtpt_b();
                }

                gte_stsxy3c( vxy );
                gte_stsz3c( vzp );

                mode = GetBoundMode( VXY[ 1 ] );
            }
        }

        obj->bound_mode = mode;
        if ( mode != 0 )
        {
            obj->free_count = 8;

            if ( obj->packs[ pack ] == NULL && DG_MakeObjPacket( obj, pack, flag ) < 0 )
            {
                obj->bound_mode = 0;

                if ( flag & DG_FLAG_GBOUND )
                {
                    objs->bound_mode = 0;
                    return;
                }
            }
        }
        else if ( obj->packs[ pack ] != NULL && --obj->free_count <= 0 )
        {
            DG_FreeObjPacket( obj, pack );
        }

        obj++;
    }
}

void DG_BoundChanl(DG_CHANL *chanl, int idx)
{
    int          i, i2, i3, xl, yl, xh, yh;
    int          n_objs;
    int          bound_mode;
    DG_OBJS    **objs;
    int          local_group_id;
    DVECTOR     *dvec;
    SVECTOR     *clip;
    DG_VECTOR   *vxy;
    DG_VECTOR   *vzp;
    int          j;
    long        *depth;
    unsigned int flag;

    DG_Clip(&chanl->clip_rect, chanl->clip_distance);

    objs = chanl->queue;
    n_objs = chanl->objs_index;
    local_group_id = DG_CurrentGroupID;

    for (; n_objs > 0; --n_objs)
    {
        DG_OBJS *current_objs = *objs;
        objs++;
        flag = current_objs->flag;

        bound_mode = 0;
        if (!(flag & DG_FLAG_INVISIBLE))
        {
            if (!current_objs->group_id || (current_objs->group_id & local_group_id))
            {
                bound_mode = 2;
                if (flag & DG_FLAG_GBOUND)
                {
                    gte_SetRotMatrix(&current_objs->objs->screen);
                    gte_SetTransMatrix(&current_objs->objs->screen);

                    clip = CLIP;
                    CopyBounds(&current_objs->def->lx);
                    vxy = (DG_VECTOR *)(SCRPAD_ADDR + 0x30);
                    vzp = (DG_VECTOR *)(SCRPAD_ADDR + 0x60);
                    i = 9;

                    while (i > 0)
                    {
                        j = 3;
                        do
                        {
                            GetClipBounds(i, clip);
                            ++clip;
                            --i;
                            --j;
                        } while (j > 0);

                        clip = CLIP;
                        gte_stsxy3c(vxy);
                        gte_stsz3c(vzp);

                        gte_ldv3c(CLIP);
                        vxy++;
                        vzp++;
                        gte_rtpt_b();
                    }

                    gte_stsxy3c(vxy);
                    gte_stsz3c(vzp);

                    // probably start of another inline func
                    xl = *(short *)(SCRPAD_ADDR + 0x3C);
                    yl = *(short *)(SCRPAD_ADDR + 0x3E);
                    xh = xl;
                    yh = yl;
                    dvec = (DVECTOR *)(SCRPAD_ADDR + 0x3C);

                    for (i2 = 7; i2 > 0; --i2)
                    {
                        dvec++;
                        if (dvec->vx < xl)
                        {
                            xl = dvec->vx;
                        }
                        else
                        {
                            if (xh < dvec->vx)
                                xh = dvec->vx;
                        }
                        if (dvec->vy < yl)
                        {
                            yl = dvec->vy;
                        }
                        else
                        {
                            if (yh < dvec->vy)
                                yh = dvec->vy;
                        }
                    }

                    if ((xl >= 0xA1) || (xh < -0xA0) || (yl >= 0x71) || (yh < -0x70))
                    {
                        bound_mode = 0;
                    }
                    else
                    {
                        bound_mode = ((xh >= 0xA1) || (xl < -0xA0) || (yh >= 0x71) || (yl < -0x70)) ? 1 : 2;
                        depth = (long *)(SCRPAD_ADDR + 0x6C);
                        i3 = 8;
                        while (i3 > 0)
                        {
                            --i3;
                            if (*depth)
                            {
                                goto END;
                            }
                            depth++;
                        }
                        bound_mode = 0;
                    }
                END:
                }
            }
        }
        // loc_80018CE0:
        current_objs->bound_mode = bound_mode;
        DG_BoundObjs(current_objs, idx, flag, bound_mode);
    }

    DG_BoundIrTexture(chanl, idx);
}

void DG_BoundEnd( void )
{
    /* do nothing */
}

// Possibly a different file.

STATIC DG_TEX DG_UnknownTexture = {0};

/* Replace the CLUT for this model with a plain white one for thermal goggles */
STATIC void DG_WriteObjClut(DG_OBJ *obj, int idx)
{
    int       n_packs;
    POLY_GT4 *pPack = obj->packs[idx];
    short     val = 0x3FFF;
    if (pPack && pPack->clut != val)
    {
        while (obj)
        {
            n_packs = obj->n_packs;
            while (n_packs > 0)
            {
                pPack->clut = val;

                ++pPack;
                --n_packs;
            }

            obj = obj->extend;
        }
    }
}

/* Restore the CLUT for this model */
STATIC void DG_WriteObjClutUV(DG_OBJ *obj, int idx)
{
    unsigned short id;
    POLY_GT4      *pack;
    int            n_packs;
    short         *tex_ids;
    DG_TEX        *texture;
    unsigned short current_id;

    pack = obj->packs[idx];

    if (pack && pack->clut == 0x3FFF)
    {
        texture = &DG_UnknownTexture;
        id = 0;
        while (obj)
        {
            tex_ids = obj->model->texids;
            for (n_packs = obj->n_packs; n_packs > 0; --n_packs)
            {
                current_id = *tex_ids;
                tex_ids++;
                if ((current_id & 0xFFFF) != id)
                {
                    id = current_id;
                    texture = DG_GetTexture(id);
                }
                pack->clut = texture->clut;
                pack++;
            }
            obj = obj->extend;
        }
    }
}

// there must be a way to match this without the repetition
STATIC void DG_BoundIrTexture(DG_CHANL *chanl, int idx)
{
    DG_OBJS **queue;
    int       n_objects;
    DG_OBJS  *objs;
    DG_OBJ   *obj;
    int       n_models;

    queue = chanl->queue;
    if (GM_GameStatus & STATE_THERMG)
    {
        for (n_objects = chanl->objs_index; n_objects > 0; n_objects--)
        {
            objs = *queue++;

            if (objs->flag & DG_FLAG_IRTEXTURE && objs->bound_mode != 0)
            {
                obj = objs->objs;

                for (n_models = objs->n_models; n_models > 0; n_models--)
                {
                    if (obj->bound_mode != 0)
                    {
                        DG_WriteObjClut(obj, idx);
                    }

                    obj++;
                }
            }
        }
    }
    else
    {
        for (n_objects = chanl->objs_index; n_objects > 0; n_objects--)
        {
            objs = *queue++;

            if (objs->flag & DG_FLAG_IRTEXTURE && objs->bound_mode != 0)
            {
                obj = objs->objs;

                for (n_models = objs->n_models; n_models > 0; n_models--)
                {
                    DG_WriteObjClutUV(obj, idx);
                    obj++;
                }
            }
        }
    }
}
