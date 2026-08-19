#include "libdg.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "common.h"

extern PLIGHT pshade_buffer[84];

static void MakeLight( SVECTOR *verts, int n_verts, PLIGHT *buffer, DG_LIT *lights, int n_lights )
{
    VECTOR dist, vert;
    DG_LIT *lit;
    int i, count;

    while ( --n_verts >= 0 )
    {
        gte_ldv0( verts );
        gte_rt();
        gte_stlvnl0( &vert.vx );
        gte_stlvnl1( &vert.vy );
        gte_stlvnl2( &vert.vz );

        count = 2;
        lit = lights;
        for ( i = n_lights; i > 0; i--, lit++ )
        {
            int e, r;

            e = lit->e_range;
            dist.vx = vert.vx - lit->point.vx;
            if ( dist.vx < -e || dist.vx > e ) continue;
            dist.vy = vert.vy - lit->point.vy;
            if ( dist.vy < -e || dist.vy > e ) continue;
            dist.vz = vert.vz - lit->point.vz;
            if ( dist.vz < -e || dist.vz > e ) continue;

            r = lit->r_range;
            if ( --count )
            {
                DG_GetLightVector( &dist, r, &buffer->point[ 0 ] );
                LCOPY(&lit->color, &buffer->color[ 0 ]);
            }
            else
            {
                DG_GetLightVector( &dist, r, &buffer->point[ 1 ] );
                LCOPY( &lit->color, &buffer->color[ 1 ] );
                break;
            }
        }

        switch ( count )
        {
        case 2:
            LSTORE( 0, &buffer->color[ 0 ] );
            /* fallthrough*/
        case 1:
            LSTORE( 0, &buffer->color[ 1 ] );
            break;
        }

        verts++;
        buffer++;
    }
}

static void MakeLights( DG_MDL *mdl, DG_LIT *lights, int n_lights )
{
    u_int n_verts;
    SVECTOR *verts;
    PLIGHT *buffer;

    n_verts = mdl->n_verts;
    verts = mdl->verts;
    buffer = (PLIGHT *)getScratchAddr( 0 );

    // If there are many verts do the first patch in the SPAD
    if ( n_verts > 42 )
    {
        MakeLight( verts, 42, buffer, lights, n_lights );
        verts += 42;
        n_verts -= 42;
        buffer = pshade_buffer;
    }

    MakeLight( verts, n_verts, buffer, lights, n_lights );
}

static CVECTOR *NoShadeRGB( DG_MDL *mdl, CVECTOR *rgbs )
{
    int color;
    int i;

    color = 0x3C808080;
    if (mdl->flags & DG_MODEL_TRANS)
    {
        color = 0x3E808080;
    }

    for (i = mdl->n_faces * 4; i > 0; i--)
    {
        LSTORE(color, rgbs);
        rgbs++;
    }

    return rgbs;
}

static inline void *GetLightMatrix(void)
{
    return &DG_LightMatrix;
}

static CVECTOR *ShadeRGB( DG_MDL *mdl, CVECTOR *cvec, DG_OBJS *objs )
{
    MATRIX light;
    MATRIX color;
    MATRIX world_light;
    CVECTOR *pPacketCode;
    int faces;
    unsigned char *pFio;
    unsigned char *pNfo;
    SVECTOR *pNio;
    unsigned int index;
    PLIGHT *buffer;

    memcpy(&light, GetLightMatrix(), 8);

    color.m[0][0] = DG_ColorMatrix.m[0][0];
    color.m[1][0] = DG_ColorMatrix.m[1][0];
    color.m[2][0] = DG_ColorMatrix.m[2][0];

    pPacketCode = (CVECTOR *)&DG_PacketCode[0];

    if (mdl->flags & DG_MODEL_TRANS)
    {
        pPacketCode = (CVECTOR *)&DG_PacketCode[1];
    }

    gte_ldrgb(pPacketCode);

    pFio = mdl->vindices;
    pNfo = mdl->nindices;
    pNio = mdl->norms;

    for (faces = mdl->n_faces * 4; faces > 0; faces--)
    {
        index = *pFio;

        if (index < 42)
        {
            buffer = (PLIGHT *)getScratchAddr(0) + index;
        }
        else
        {
            buffer = &pshade_buffer[index - 42];
        }

        *(SVECTOR *)&light.m[1] = buffer->point[0];
        *(SVECTOR *)&light.m[2] = buffer->point[1];

        gte_SetRotMatrix(&light);
        DG_MulRotMatrix0(&objs->world, &world_light);
        gte_SetLightMatrix(&world_light);

        color.m[0][1] = buffer->color[0].r << 4;
        color.m[1][1] = buffer->color[0].g << 4;
        color.m[2][1] = buffer->color[0].b << 4;
        color.m[0][2] = buffer->color[1].r << 4;
        color.m[1][2] = buffer->color[1].g << 4;
        color.m[2][2] = buffer->color[1].b << 4;

        gte_SetColorMatrix(&color);
        gte_ldv0(pNio + *pNfo++);
        gte_ncs();
        gte_strgb(cvec++);

        pFio++;
    }

    return cvec;
}

static int CalcCVecLen( DG_DEF *def )
{
    int     total_faces;
    int     i;
    DG_MDL *model;

    total_faces = 0;
    model = (DG_MDL *)&def[1];
    for (i = def->n_x_models; i > 0; i--)
    {
        total_faces += model->n_faces;
        ++model;
    }
    return 0x10 * total_faces; // TODO: sizeof(CVECTOR) ??
}

int DG_MakePreshade( DG_OBJS *objs, DG_LIT *light, int n_lights )
{
    CVECTOR *cvec;
    DG_DEF  *def;
    int      size;
    MATRIX   rotation;
    DG_OBJ  *obj;
    int      i;
    DG_MDL  *model;

    cvec = objs->objs[0].rgbs;
    def = objs->def;

    if (!cvec)
    {
        size = CalcCVecLen(def);
        cvec = GV_Malloc(size);

        if (!cvec)
        {
            return -1;
        }
    }

    gte_ReadRotMatrix(&rotation);

    obj = objs->objs;

    for (i = def->n_x_models; i > 0; i--)
    {
        obj->rgbs = cvec;
        model = obj->model;

        gte_SetRotMatrix(&objs->world);
        gte_SetTransMatrix(&objs->world);

        MakeLights(model, light, n_lights);

        if (model->flags & DG_MODEL_UNLIT)
        {
            cvec = NoShadeRGB(model, cvec);
        }
        else
        {
            cvec = ShadeRGB(model, cvec, objs);
        }

        obj++;
    }

    obj = objs->objs;

    for (i = objs->n_models; i > 0; i--)
    {
        if (obj->packs[0])
        {
            DG_WriteObjPacketRGB(obj, 0);
        }

        if (obj->packs[1])
        {
            DG_WriteObjPacketRGB(obj, 1);
        }

        obj++;
    }

    gte_SetRotMatrix(&rotation);
    gte_SetTransMatrix(&rotation);
    return 0;
}

void DG_FreePreshade( DG_OBJS *objs )
{
    CVECTOR *rgbs;

    rgbs = objs->objs[ 0 ].rgbs;
    if ( rgbs != NULL )
    {
        GV_Free( rgbs );
        objs->objs[ 0 ].rgbs = NULL;
    }
}
