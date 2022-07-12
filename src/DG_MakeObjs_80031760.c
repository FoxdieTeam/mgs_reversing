#include "linker.h"
#include "map/map.h"
#include "libdg.h"
#include "dgd.h"

extern MATRIX DG_LightMatrix_8009D384;
extern MATRIX DG_ZeroMatrix_8009D430;

int DG_MakeObjs_helper_80031710(DG_MDL *pMesh);
extern void *GV_Malloc_8001620C(int size);
extern void GV_ZeroMemory_8001619C(void *, int);

DG_OBJS *DG_MakeObjs_80031760(DG_DEF *pFileData, int flag, int chanl)
{
    DG_MDL *pMeshIter = (DG_MDL *)&pFileData[1];

    const int len = sizeof(DG_OBJS) + (sizeof(DG_OBJ) * pFileData->num_mesh_4);
    DG_OBJS *pAlloc = (DG_OBJS *)GV_Malloc_8001620C(len);

    if (!pAlloc)
    {
        return 0;
    }
    else
    {
        int numMesh;
        DG_OBJ *pObjIter;

        GV_ZeroMemory_8001619C(pAlloc, len);
        pAlloc->world = DG_ZeroMatrix_8009D430;

        pAlloc->def = pFileData;

        pAlloc->n_models = pFileData->num_bones_0;

        pAlloc->flag = flag;
        pAlloc->chanl = chanl;
        pAlloc->light = &DG_LightMatrix_8009D384;

        pObjIter = &pAlloc->objs[0];
        for (numMesh = pFileData->num_mesh_4; numMesh > 0; numMesh--)
        {
            pObjIter->model = pMeshIter;
            if (pMeshIter->unknownA_30 < 0)
            {
                pObjIter->extend = 0;
            }
            else
            {
                pObjIter->extend = &pAlloc->objs[pMeshIter->unknownA_30];
            }

            pObjIter->raise = DG_MakeObjs_helper_80031710(pMeshIter);

            pObjIter->n_packs = pMeshIter->numFaces_4;
            pObjIter++;
            pMeshIter++;
        }
        return pAlloc;
    }
}
