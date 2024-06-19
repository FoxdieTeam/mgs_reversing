#include "libdg.h"

DG_TEX dword_8009D3C4 = {0};

int DG_AllocPacks_8001A670(DG_OBJ *pObj, int idx)
{
    int     totalPolys = 0;
    DG_OBJ *pObjIter = pObj;
    while (pObjIter)
    {
        totalPolys += pObjIter->n_packs;
        pObjIter = pObjIter->extend;
    }

    if (!GV_AllocMemory2_80015ED8(idx, totalPolys * sizeof(POLY_GT4), (void **)&pObj->packs[idx]))
    {
        return -1;
    }
    return 0;
}

void DG_InitPolyGT4Pack_8001A6E4(DG_OBJ *pObj, int idx)
{
    POLY_GT4 *pPack;

    int rgbCode = 0x3E808080;

    if ((pObj->model->flags & DG_MODEL_TRANS) == 0)
    {
        rgbCode = 0x3C808080;
    }

    pPack = pObj->packs[idx];
    while (pObj)
    {
        int n_packs;
        for (n_packs = pObj->n_packs; n_packs > 0; n_packs--)
        {
            setPolyGT4(pPack);

            *(int *)&pPack->r0 = rgbCode;
            *(int *)&pPack->r1 = rgbCode;
            *(int *)&pPack->r2 = rgbCode;
            *(int *)&pPack->r3 = rgbCode;
            pPack++;
        }
        pObj = pObj->extend;
    }
}

static inline void Apply(DG_TEX *pTexture, unsigned char *pUV, POLY_GT4 *pPack)
{
    unsigned int u0 = pTexture->field_8_offx;
    unsigned int v0 = pTexture->field_9_offy;
    int          u11 = pTexture->field_A_width + 1;
    int          v11 = pTexture->field_B_height + 1;

    pPack->u0 = ((pUV[0] * u11) / 256) + u0;
    pPack->v0 = ((pUV[1] * v11) / 256) + v0;
    pPack->u1 = ((pUV[2] * u11) / 256) + u0;
    pPack->v1 = ((pUV[3] * v11) / 256) + v0;
    pPack->u2 = ((pUV[6] * u11) / 256) + u0;
    pPack->v2 = ((pUV[7] * v11) / 256) + v0;
    pPack->u3 = ((pUV[4] * u11) / 256) + u0;
    pPack->v3 = ((pUV[5] * v11) / 256) + v0;
    pPack->tpage = pTexture->field_4_tPage;
    pPack->clut = pTexture->field_6_clut;
}

void DG_WriteObjPacketUV_8001A774( DG_OBJ* obj, int idx )
{
    unsigned short  id;
    POLY_GT4       *pack;
    int             n_packs;
    short          *tex_ids;
    DG_TEX         *texture;
    unsigned short  current_id;
    unsigned char  *uv;

    pack = obj->packs[ idx ];

    if ( pack )
    {
        texture = &dword_8009D3C4;
        id = 0;

        while ( obj )
        {
            tex_ids = obj->model->materials;
            uv = obj->model->texcoords;
            for (n_packs = obj->n_packs; n_packs > 0 ; --n_packs )
            {
                current_id = *tex_ids;
                tex_ids++;

                if ( current_id != id )
                {
                    id = current_id;
                    texture = DG_GetTexture_8001D830( current_id );
                }

                Apply(texture, uv, pack);
                pack++;
                uv += 8;
            }
            obj = obj->extend;
        }
    }
}

void DG_WriteObjPacketRGB_8001A9B8(DG_OBJ *pDGObj, int idx)
{
    POLY_GT4 *pPack = pDGObj->packs[idx];
    if (pPack && pDGObj)
    {
        do
        {
            CVECTOR *pack_rgbs = pDGObj->rgbs;
            if (pack_rgbs)
            {
                int n_packs;
                for (n_packs = pDGObj->n_packs; n_packs > 0; --n_packs)
                {
                    LCOPY2(&pack_rgbs[0], &pPack->r0, &pack_rgbs[1], &pPack->r1);
                    LCOPY2(&pack_rgbs[3], &pPack->r2, &pack_rgbs[2], &pPack->r3);

                    ++pPack;
                    pack_rgbs += 4; // to next set of rgb
                }
            }
            pDGObj = pDGObj->extend;
        } while (pDGObj);
    }
}

int DG_MakeObjPacket_8001AA50(DG_OBJ *pPrim, int idx, int flags)
{
    if (DG_AllocPacks_8001A670(pPrim, idx) < 0)
    {
        return -1;
    }

    DG_InitPolyGT4Pack_8001A6E4(pPrim, idx);

    if ((flags & DG_FLAG_TEXT) != 0)
    {
        DG_WriteObjPacketUV_8001A774(pPrim, idx);
    }

    if ((flags & DG_FLAG_PAINT) != 0)
    {
        DG_WriteObjPacketRGB_8001A9B8(pPrim, idx);
    }

    return 0;
}

void DG_FreeObjPacket_8001AAD0(DG_OBJ *pObj, int idx)
{
    POLY_GT4 **ppPack;

    ppPack = &pObj->packs[idx];
    if (*ppPack)
    {
        GV_FreeMemory2_80016078(idx, (void **)ppPack);
        *ppPack = 0;
    }
}

int DG_MakeObjsPacket_8001AB14(DG_OBJS *pObjs, int idx)
{

    int flag = pObjs->flag;
    int n_models = pObjs->n_models;

    DG_OBJ *pObj = pObjs->objs;
    while (n_models > 0)
    {
        if (!pObj->packs[idx])
        {
            if (DG_MakeObjPacket_8001AA50(pObj, idx, flag) < 0)
            {
                return -1;
            }
        }
        pObj++;
        n_models--;
    }
    return 0;
}

void DG_FreeObjsPacket_8001ABA8(DG_OBJS *pObjs, int idx)
{
    int     n_models;
    DG_OBJ *pObj;

    n_models = pObjs->n_models;
    for (pObj = pObjs->objs; n_models > 0; ++pObj)
    {
        DG_FreeObjPacket_8001AAD0(pObj, idx);
        --n_models;
    }
}
