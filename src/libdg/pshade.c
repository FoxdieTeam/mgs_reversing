#include "libdg.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "common.h"

extern MATRIX       DG_LightMatrix;
extern MATRIX       DG_ColorMatrix;

extern CVECTOR      DG_PacketCode[2];

extern DG_LitVertex DG_LitVertices_800B7A50[84];

//there are a few of these that are close to gte_MulMatrix0 but with the first part changed
// clang-format off
#define gte_Unknown(r1, r2)                                     \
    {                                                           \
        gte_ldclmv(r1);                                         \
        gte_rtir();                                             \
        gte_stclmv(r2);                                         \
        gte_ldclmv((char *)r1 + 2);                             \
        gte_rtir();                                             \
        gte_stclmv((char *)r2 + 2);                             \
        gte_ldclmv((char *)r1 + 4);                             \
        gte_rtir();                                             \
        gte_stclmv((char *)r2 + 4);                             \
    }
// clang-format on

STATIC void prim_lighting( SVECTOR *pVerts, int numVerts, DG_LitVertex *pOut, DG_LIT *light, int n_lights )
{
    VECTOR distance;
    VECTOR position;
    int remaining;
    int lights;
    DG_LIT *plit;
    int radius;
    int brightness;

    for (--numVerts; numVerts >= 0; pVerts++, pOut++, numVerts--)
    {
        gte_ldv0(pVerts);
        gte_rt();
        gte_stlvnl0(&position.vx);
        gte_stlvnl1(&position.vy);
        gte_stlvnl2(&position.vz);

        remaining = 2;

        plit = light;
        for (lights = n_lights; lights > 0; lights--, plit++)
        {
            radius = plit->field_A_radius;

            distance.vx = position.vx - plit->pos.vx;
            if ((distance.vx < -radius) || (distance.vx > radius))
            {
                continue;
            }

            distance.vy = position.vy - plit->pos.vy;
            if ((distance.vy < -radius) || (distance.vy > radius))
            {
                continue;
            }

            distance.vz = position.vz - plit->pos.vz;
            if ((distance.vz < -radius) || (distance.vz > radius))
            {
                continue;
            }

            brightness = plit->field_8_brightness;

            if (--remaining == 0)
            {
                DG_GetLightVector(&distance, plit->field_8_brightness, &pOut->intensity[1]);
                LCOPY(&plit->field_C_colour, &pOut->color[1]);
                break;
            }

            DG_GetLightVector(&distance, brightness, &pOut->intensity[0]);
            LCOPY(&plit->field_C_colour, &pOut->color[0]);
        }

        switch (remaining)
        {
        case 2:
            LSTORE(0, &pOut->color[0]);

        case 1:
            LSTORE(0, &pOut->color[1]);
            break;
        }
    }
}

STATIC void prim_80031B00( DG_MDL *mdl, DG_LIT *light, int n_lights )
{
    unsigned int  numVerts;
    SVECTOR      *pVerts;
    DG_LitVertex *pLitVertices;

    numVerts = mdl->n_verts;
    pVerts = mdl->vertices;
    pLitVertices = (DG_LitVertex *)getScratchAddr(0);

    // If there are many verts do the first patch in the SPAD
    if (numVerts > 42)
    {
        prim_lighting(pVerts, 42, pLitVertices, light, n_lights);
        pVerts += 42;
        numVerts -= 42;
        pLitVertices = DG_LitVertices_800B7A50;
    }

    prim_lighting(pVerts, numVerts, pLitVertices, light, n_lights);
}

STATIC CVECTOR *SetUnlitCVector( DG_MDL *mdl, CVECTOR *cvec )
{
    int colour;
    int i;

    colour = 0x3C808080;
    if (mdl->flags & DG_MODEL_TRANS)
    {
        colour = 0x3E808080;
    }

    for (i = 4 * mdl->n_faces; i > 0; ++cvec, --i)
    {
        LSTORE(colour, cvec);
    }

    return cvec;
}

static inline void *GetLightMatrix(void)
{
    return &DG_LightMatrix;
}

STATIC CVECTOR *DG_MakePreshade_helper( DG_MDL *mdl, CVECTOR *cvec, DG_OBJS *objs )
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
    DG_LitVertex *pLitVertex;

    memcpy(&light, GetLightMatrix(), 8);

    color.m[0][0] = DG_ColorMatrix.m[0][0];
    color.m[1][0] = DG_ColorMatrix.m[1][0];
    color.m[2][0] = DG_ColorMatrix.m[2][0];

    pPacketCode = &DG_PacketCode[0];

    if (mdl->flags & DG_MODEL_TRANS)
    {
        pPacketCode = &DG_PacketCode[1];
    }

    gte_ldrgb(pPacketCode);

    pFio = mdl->vindices;
    pNfo = mdl->nindices;
    pNio = mdl->normals;

    for (faces = mdl->n_faces * 4; faces > 0; faces--)
    {
        index = *pFio;

        if (index < 42)
        {
            pLitVertex = (DG_LitVertex *)getScratchAddr(0) + index;
        }
        else
        {
            pLitVertex = (DG_LitVertex *)&DG_LitVertices_800B7A50[index - 42];
        }

        *(SVECTOR *)&light.m[1] = pLitVertex->intensity[0];
        *(SVECTOR *)&light.m[2] = pLitVertex->intensity[1];

        gte_SetRotMatrix(&light);
        gte_Unknown(&objs->world, &world_light);
        gte_SetLightMatrix(&world_light);

        color.m[0][1] = pLitVertex->color[0].r << 4;
        color.m[1][1] = pLitVertex->color[0].g << 4;
        color.m[2][1] = pLitVertex->color[0].b << 4;
        color.m[0][2] = pLitVertex->color[1].r << 4;
        color.m[1][2] = pLitVertex->color[1].g << 4;
        color.m[2][2] = pLitVertex->color[1].b << 4;

        gte_SetColorMatrix(&color);
        gte_ldv0(pNio + *pNfo++);
        gte_ncs();
        gte_strgb(cvec++);

        pFio++;
    }

    return cvec;
}

STATIC int CalcCVecLen( DG_DEF *def )
{
    int     total_faces;
    int     i;
    DG_MDL *model;

    total_faces = 0;
    model = (DG_MDL *)&def[1];
    for (i = def->num_mesh_4; i > 0; i--)
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

    for (i = def->num_mesh_4; i > 0; i--)
    {
        obj->rgbs = cvec;
        model = obj->model;

        gte_SetRotMatrix(&objs->world);
        gte_SetTransMatrix(&objs->world);

        prim_80031B00(model, light, n_lights);

        if (model->flags & DG_MODEL_UNLIT)
        {
            cvec = SetUnlitCVector(model, cvec);
        }
        else
        {
            cvec = DG_MakePreshade_helper(model, cvec, objs);
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
    CVECTOR *pBuffer = objs->objs[0].rgbs;
    if (pBuffer)
    {
        GV_Free(pBuffer);
        objs->objs[0].rgbs = 0;
    }
}
