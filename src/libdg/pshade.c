#include "linker.h"
#include "libdg.h"
#include "psyq.h"

extern MATRIX       DG_LightMatrix_8009D384;
extern MATRIX       DG_ColorMatrix_8009D3A4;

extern CVECTOR      DG_PacketCode_800AB394[2];

extern DG_LitVertex DG_LitVertices_800B7A50[84];

//there are a few of these that are close to gte_MulMatrix0 but with the first part changed
#define gte_Unknown(r1, r2)                                                                                            \
    {                                                                                                                  \
        gte_ldclmv(r1);                                                                                                \
        gte_rtir();                                                                                                    \
        gte_stclmv(r2);                                                                                                \
        gte_ldclmv((char *)r1 + 2);                                                                                    \
        gte_rtir();                                                                                                    \
        gte_stclmv((char *)r2 + 2);                                                                                    \
        gte_ldclmv((char *)r1 + 4);                                                                                    \
        gte_rtir();                                                                                                    \
        gte_stclmv((char *)r2 + 4);                                                                                    \
    }

void Prim_lighting_80031954(SVECTOR *pVerts, int numVerts, DG_LitVertex *pOut, DG_LIT *pLights, int numLights)
{
    VECTOR distance;
    VECTOR position;
    int remaining;
    int lights;
    DG_LIT *pLight;
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

        pLight = pLights;
        for (lights = numLights; lights > 0; lights--, pLight++)
        {
            radius = pLight->field_A_radius;

            distance.vx = position.vx - pLight->pos.vx;
            if ((distance.vx < -radius) || (distance.vx > radius))
            {
                continue;
            }

            distance.vy = position.vy - pLight->pos.vy;
            if ((distance.vy < -radius) || (distance.vy > radius))
            {
                continue;
            }

            distance.vz = position.vz - pLight->pos.vz;
            if ((distance.vz < -radius) || (distance.vz > radius))
            {
                continue;
            }

            brightness = pLight->field_8_brightness;

            if (--remaining == 0)
            {
                DG_GetLightVector_8001A1A8(&distance, pLight->field_8_brightness, &pOut->intensity[1]);
                LCOPY(&pLight->field_C_colour, &pOut->color[1]);
                break;
            }

            DG_GetLightVector_8001A1A8(&distance, brightness, &pOut->intensity[0]);
            LCOPY(&pLight->field_C_colour, &pOut->color[0]);
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

void Prim_80031B00(DG_MDL *pMdl, DG_LIT *pLights, int numLights)
{
    unsigned int  numVerts;
    SVECTOR      *pVerts;
    DG_LitVertex *pLitVertices;

    numVerts = pMdl->n_verts;
    pVerts = pMdl->vertices;
    pLitVertices = (DG_LitVertex *)getScratchAddr(0);

    // If there are many verts do the first patch in the SPAD
    if (numVerts > 42)
    {
        Prim_lighting_80031954(pVerts, 42, pLitVertices, pLights, numLights);
        pVerts += 42;
        numVerts -= 42;
        pLitVertices = DG_LitVertices_800B7A50;
    }

    Prim_lighting_80031954(pVerts, numVerts, pLitVertices, pLights, numLights);
}


CVECTOR * Prim_80031B88(DG_MDL *pMdl, CVECTOR *pRgbs)
{
    int colour;      // $v1
    int faceCounter; // $v0

    colour = 0x3C808080;
    if (pMdl->flags & DG_MODEL_TRANS)
    {
        colour = 0x3E808080;
    }

    for (faceCounter = 4 * pMdl->n_faces; faceCounter > 0; ++pRgbs, --faceCounter)
    {
        LSTORE(colour, pRgbs);
    }

    return pRgbs;
}

static inline void * DG_GetLightMatrix(void)
{
    return &DG_LightMatrix_8009D384;
}

CVECTOR * DG_MakePreshade_helper_80031BD4(DG_MDL *pMdl, CVECTOR *pRgbs, DG_OBJS *pObjs)
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

    memcpy(&light, DG_GetLightMatrix(), 8);

    color.m[0][0] = DG_ColorMatrix_8009D3A4.m[0][0];
    color.m[1][0] = DG_ColorMatrix_8009D3A4.m[1][0];
    color.m[2][0] = DG_ColorMatrix_8009D3A4.m[2][0];

    pPacketCode = &DG_PacketCode_800AB394[0];

    if (pMdl->flags & DG_MODEL_TRANS)
    {
        pPacketCode = &DG_PacketCode_800AB394[1];
    }

    gte_ldrgb(pPacketCode);

    pFio = pMdl->vertex_indices;
    pNfo = pMdl->normal_indices;
    pNio = pMdl->normals;

    for (faces = pMdl->n_faces * 4; faces > 0; faces--)
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
        gte_Unknown(&pObjs->world, &world_light);
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
        gte_strgb(pRgbs++);

        pFio++;
    }

    return pRgbs;
}

int Prim_Calc_CVECTOR_len_80031ED4(DG_DEF *pDef)
{
    int     totalFaceCount; // $a1
    int     meshCounter;    // $v1
    DG_MDL *pMdlIter;       // $a0

    totalFaceCount = 0;
    pMdlIter = (DG_MDL *)&pDef[1];
    for (meshCounter = pDef->num_mesh_4; meshCounter > 0; meshCounter--)
    {
        totalFaceCount += pMdlIter->n_faces;
        ++pMdlIter;
    }
    return 0x10 * totalFaceCount; // TODO: sizeof(CVECTOR) ??
}

int DG_MakePreshade_80031F04(DG_OBJS *pObjs, DG_LIT *pLights, int numLights)
{
    CVECTOR *pRgbs;
    DG_DEF *pDef;
    int size;
    MATRIX rotation;
    DG_OBJ *pObj;
    int iter;
    DG_MDL *pMdl;

    pRgbs = pObjs->objs[0].rgbs;
    pDef = pObjs->def;

    if (!pRgbs)
    {
        size = Prim_Calc_CVECTOR_len_80031ED4(pDef);
        pRgbs = GV_Malloc_8001620C(size);

        if (!pRgbs)
        {
            return -1;
        }
    }

    gte_ReadRotMatrix(&rotation);

    pObj = pObjs->objs;

    for (iter = pDef->num_mesh_4; iter > 0; iter--)
    {
        pObj->rgbs = pRgbs;
        pMdl = pObj->model;

        gte_SetRotMatrix(&pObjs->world);
        gte_SetTransMatrix(&pObjs->world);

        Prim_80031B00(pMdl, pLights, numLights);

        if (pMdl->flags & DG_MODEL_UNLIT)
        {
            pRgbs = Prim_80031B88(pMdl, pRgbs);
        }
        else
        {
            pRgbs = DG_MakePreshade_helper_80031BD4(pMdl, pRgbs, pObjs);
        }

        pObj++;
    }

    pObj = pObjs->objs;

    for (iter = pObjs->n_models; iter > 0; iter--)
    {
        if (pObj->packs[0])
        {
            DG_WriteObjPacketRGB_8001A9B8(pObj, 0);
        }

        if (pObj->packs[1])
        {
            DG_WriteObjPacketRGB_8001A9B8(pObj, 1);
        }

        pObj++;
    }

    gte_SetRotMatrix(&rotation);
    gte_SetTransMatrix(&rotation);
    return 0;
}

void DG_FreePreshade_80032110(DG_OBJS *pPrim)
{
    CVECTOR *pBuffer = pPrim->objs[0].rgbs;
    if (pBuffer)
    {
        GV_Free_80016230(pBuffer);
        pPrim->objs[0].rgbs = 0;
    }
}
