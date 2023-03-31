#include "linker.h"
#include "libdg/libdg.h"

extern DG_LitVertex dg_lit_vertices_800B7A50[84];

void Prim_80031B00(DG_MDL *pMdl, DG_Light *pLights, int numLights)
{
    unsigned int  numVerts;
    SVECTOR      *pVerts;
    DG_LitVertex *pLitVertices;

    numVerts = pMdl->numVertex_34;
    pVerts = pMdl->vertexIndexOffset_38;
    pLitVertices = (DG_LitVertex *)getScratchAddr(0);

    // If there are many verts do the first patch in the SPAD
    if (numVerts > 42)
    {
        Prim_lighting_80031954(pVerts, 42, pLitVertices, pLights, numLights);
        pVerts += 42;
        numVerts -= 42;
        pLitVertices = dg_lit_vertices_800B7A50;
    }

    Prim_lighting_80031954(pVerts, numVerts, pLitVertices, pLights, numLights);
}
