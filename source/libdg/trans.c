#include "libdg.h"
#include "common.h"
#include "inline_n.h"
#include "inline_x.h"
#include "libgv/libgv.h" // for GV_Clock

typedef struct _SCRATCH
{
    DVECTOR   xy[126];
    int       area;
    short     bothface;
    short     flags;
    DVECTOR   zf[126];
    POLY_GT4 *parent_packs;
    SVECTOR  *vertices;
} SCRATCH;

#define SPAD ((SCRATCH *)getScratchAddr(0))

void DG_TransStart( void )
{
    /* do nothing */
}

STATIC unsigned int DG_WriteObjVerticesIndirect( unsigned int vidx, POLY_GT4 *packs )
{
    int *pack_ptr;
    int a2, a3, t3, t5, num, stride;
    int i, temp;
    unsigned int scrpd_idx, scrpd_idx2;
    unsigned char t6;

    scrpd_idx = SCRPAD_ADDR;
    t3 = *( int* )(scrpd_idx + 0x3F8);
    if ( !t3 ) return 0;


    t5 = *( int* )( scrpd_idx + 0x3FC );
    num = 0;
    stride = 0;

    pack_ptr = ( int* )&packs->x0;
    a3 = 8;
    i = 4;
    t6 = 32;
    scrpd_idx2 = SCRPAD_ADDR;

    for ( ; i > 0; i-- )
    {
        a2 = vidx & 0x7f;

        if ((vidx & 0x80) == 0)
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
        vidx = ( vidx << ( t6 - a3 ) ) | ( vidx >> a3 );
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

STATIC POLY_GT4 *DG_WriteObjVertices( unsigned int *vindices, POLY_GT4 *packs, int n_packs )
{
    unsigned char bVar1;
    int area;
    unsigned int uVar7;
    int count;
    unsigned int scrpad_addr;
    unsigned int uVar8;
    unsigned int *n0, *n1, *n2, *n3;

    for (count = n_packs - 1; count >= 0; (packs++)->tag = uVar7, vindices++, count--)
    {
        scrpad_addr = SCRPAD_ADDR;
        uVar7 = 0;
        uVar8 = 0xfffe0000;

        n0 = (unsigned int *)*vindices;

        if (*vindices & 0x80808080)
        {
            uVar7 = DG_WriteObjVerticesIndirect(*vindices, packs);
            continue;
        }

        n1 = (unsigned int *)*vindices;
        n2 = (unsigned int *)*vindices;
        n3 = (unsigned int *)*vindices;

        n0 = (unsigned int *)((unsigned int)n0 << 2);
        n1 = (unsigned int *)((unsigned int)n1 >> 6);
        n2 = (unsigned int *)((unsigned int)n2 >> 22);
        n3 = (unsigned int *)((unsigned int)n3 >> 14);

        n0 = (unsigned int *)((int)n0 & 0x1fc);
        n1 = (unsigned int *)((int)n1 & 0x1fc);
        n2 = (unsigned int *)((int)n2 & 0x1fc);
        n3 = (unsigned int *)((int)n3 & 0x1fc);

        n0 = (unsigned int *)((int)n0 + scrpad_addr);
        n1 = (unsigned int *)((int)n1 + scrpad_addr);
        n2 = (unsigned int *)((int)n2 + scrpad_addr);
        n3 = (unsigned int *)((int)n3 + scrpad_addr);


        if ((*(unsigned short *)(scrpad_addr + 0x1fe) & 1))
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

        LCOPY(n3, &packs->x3);

        gte_stopz((int *)0x1f8001f8);
        gte_stsxy3_gt3(&packs->tag);

        area = *(int *)(scrpad_addr + 0x1f8);

        if (area <= 0)
        {
            if (!(*(short *)(scrpad_addr + 0x1fc)) || area == 0)
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

    return packs;
}

static inline void DG_BoundCheck( DVECTOR *vert )
{
    int clip;
    int val;

    clip = 0;

    val = vert->vx;
    if ( val < -160 )
    {
        clip = 1;
    }
    else if ( val > 160 )
    {
        clip = 2;
    }

    val = vert->vy;
    if ( val < -112 )
    {
        clip |= 4;
    }
    else if ( val > 112 )
    {
        clip |= 8;
    }

    *((char *)(vert + 128) + 3) = clip;
}

static inline void DG_TransVerticesBound( DG_PVECTOR *verts, int n_verts )
{
    SCRATCH     *scratch;
    DVECTOR     *xy;
    DVECTOR     *zf;
    int          vert_count;
    int          xy0, z0;
    int          xy1, z1;
    int          xy2, z2;

    scratch = (SCRATCH *)getScratchAddr(0);
    xy = scratch->xy;
    zf = scratch->zf;

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

    gte_stsxy3c(xy);
    gte_stsz3c(zf);

    xy += 3;
    zf += 3;

    while ( vert_count > 0 )
    {
        gte_ldVXYZ0(xy0, z0);
        gte_ldVXYZ1(xy1, z1);
        gte_ldVXYZ2(xy2, z2);

        verts += 3;
        vert_count -= 3;

        gte_rtpt_b();

        DG_BoundCheck( xy - 3 );
        DG_BoundCheck( xy - 2 );
        DG_BoundCheck( xy - 1 );

        xy0 = verts[0].vxy;
        z0 = verts[0].vz;

        xy1 = verts[1].vxy;
        z1 = verts[1].vz;

        xy2 = verts[2].vxy;
        z2 = verts[2].vz;

        gte_stsxy3c(xy);
        gte_stsz3c(zf);

        xy += 3;
        zf += 3;
    }

    DG_BoundCheck( xy - 3 );
    DG_BoundCheck( xy - 2 );
    DG_BoundCheck( xy - 1 );
}

static inline void DG_TransVertices( DG_PVECTOR *verts, int n_verts )
{
    SCRATCH *scratch;
    DVECTOR *xy;
    DVECTOR *zf;
    int      vert_count;
    int      xy0, z0;
    int      xy1, z1;
    int      xy2, z2;

    scratch = (SCRATCH *)getScratchAddr(0);
    xy = scratch->xy;
    zf = scratch->zf;

    gte_ldv3c(verts);

    verts += 3;
    vert_count = n_verts;

    gte_rtpt_b();

    xy0 = verts[0].vxy;
    z0 = verts[0].vz;

    xy1 = verts[1].vxy;
    z1 = verts[1].vz;

    xy2 = verts[2].vxy;
    z2 = verts[2].vz;

    gte_stsxy3c(xy);
    gte_stsz3c(zf);

    xy += 3;
    zf += 3;

    vert_count -= 3;

    while ( vert_count > 0 )
    {
        gte_ldVXYZ0(xy0, z0);
        gte_ldVXYZ1(xy1, z1);
        gte_ldVXYZ2(xy2, z2);

        verts += 3;
        vert_count -= 3;

        gte_rtpt_b();

        xy0 = verts[0].vxy;
        z0 = verts[0].vz;

        xy1 = verts[1].vxy;
        z1 = verts[1].vz;

        xy2 = verts[2].vxy;
        z2 = verts[2].vz;

        gte_stsxy3c(xy);
        gte_stsz3c(zf);

        xy += 3;
        zf += 3;
    }
}

STATIC void DG_TransObj( DG_OBJ *obj, int idx )
{
    POLY_GT4   *packs;
    DG_MDL     *model;
    DG_PVECTOR *vertices;

    packs = obj->packs[idx];

    while ( obj )
    {
        model = obj->model;
        vertices = (DG_PVECTOR *)model->vertices;

        if ( SPAD->flags & 0x1 )
        {
            DG_TransVerticesBound( vertices, model->n_verts );
        }
        else
        {
            DG_TransVertices( vertices, model->n_verts );
        }

        SPAD->bothface = model->flags & DG_MODEL_BOTHFACE;

        packs = DG_WriteObjVertices( ( unsigned int * ) model->vindices, packs, obj->n_packs );
        obj = obj->extend;
    }
}

void DG_TransChanl( DG_CHANL *chanl, int idx )
{
    SCRATCH  *work;
    DG_OBJS **queue;
    int       n_objects;
    DG_OBJS  *objs;
    DG_OBJ   *obj;
    int       no_gbound;
    int       n_models;
    DG_MDL   *model;
    DG_OBJ   *parent;

    work = (SCRATCH *)getScratchAddr(0);

    DG_Clip(&chanl->clip_rect, chanl->clip_distance);

    queue = (DG_OBJS **)chanl->mQueue;
    for (n_objects = chanl->mTotalObjectCount; n_objects > 0; n_objects--)
    {
        objs = *queue++;

        if (objs->bound_mode == 0)
        {
            continue;
        }

        obj = objs->objs;
        no_gbound = !(objs->flag & DG_FLAG_GBOUND);

        for (n_models = objs->n_models; n_models > 0; obj++, n_models--)
        {
            if (obj->bound_mode == 0)
            {
                continue;
            }

            model = obj->model;
            parent = &objs->objs[model->parent];


            work->parent_packs = parent->packs[GV_Clock];
            work->vertices = model->vertices;

            gte_SetRotMatrix(&obj->screen);
            gte_SetTransMatrix(&obj->screen);

            work->flags = no_gbound && obj->bound_mode == 1;
            if (objs->flag & DG_FLAG_SHADE)
            {
                work->flags |= 4;
            }

            DG_TransObj(obj, idx);
        }
    }
}

void DG_TransEnd( void )
{
    /* do nothing */
}
