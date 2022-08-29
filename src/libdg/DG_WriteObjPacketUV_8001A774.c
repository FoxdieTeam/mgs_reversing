#include "libdg.h"

extern DG_TEX dword_8009D3C4;

DG_TEX *DG_FindTexture_8001D830(int name);

// MSVC inline
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

void DG_WriteObjPacketUV_8001A774(DG_OBJ *pObj, int idx)
{
    DG_OBJ         *pMesh;
    POLY_GT4       *pPack;
    DG_TEX         *pTexture;
    unsigned short  last_tex_hash;
    unsigned short  next_tex_hash;
    DG_MDL         *pModel;
    unsigned short *materialOffset_50;
    unsigned char  *uvOffset_4C;
    unsigned int    new_var;
    int             n_packs;
    pMesh = pObj;
    pPack = pObj->packs[idx];
    if (pPack)
    {
        pTexture = &dword_8009D3C4;
        for (last_tex_hash = 0; pMesh; pMesh = pMesh->extend)
        {
            pModel = pMesh->model;
            materialOffset_50 = pModel->materialOffset_50;
            uvOffset_4C = pModel->uvOffset_4C;
            for (n_packs = pMesh->n_packs; n_packs > 0; n_packs--)
            {
                next_tex_hash = *(materialOffset_50++);
                if (next_tex_hash != last_tex_hash)
                {
                    new_var = (short)next_tex_hash;
                    last_tex_hash = new_var;
                    pTexture = DG_FindTexture_8001D830(next_tex_hash);
                }
                Apply(pTexture, uvOffset_4C, pPack);
                pPack++;
                uvOffset_4C += 8;
            }
        }
    }
}
