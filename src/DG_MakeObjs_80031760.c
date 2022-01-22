#include "linker.h"
#include "map/map.h"
#include "libdg.h"
#include "dgd.h"

extern MATRIX DG_LightMatrix_8009D384;
extern MATRIX DG_ZeroMatrix_8009D430;

struct KmdVec3
{
    int field_0_x;
    int field_4_y;
    int field_8_z;
};

struct KmdMesh
{
    int flag;
    int numFace;
    struct KmdVec3 max;
    struct KmdVec3 min;
    struct KmdVec3 pos;
    int parent;
    int unknownA;
    int numVertex;
    int vertexIndexOffset;
    int faceIndexOffset;
    int numNormals;
    int normalIndexOffset;
    int normalFaceOffset;
    int uvOffset;
    int materialOffset;
    int pad;
};

int sub_80031710(struct KmdMesh *pMesh);
extern void *GV_Malloc_8001620C(int size);
extern void GV_ZeroMemory_8001619c(void *, int);


DG_OBJS *DG_MakeObjs_80031760(struct KmdAndLitHeader *pFileData, int flag, int chanl)
{
    struct KmdMesh *pMeshIter = (struct KmdMesh *)&pFileData[1];

    const int len = sizeof(DG_OBJS) + (sizeof(DG_OBJ) * pFileData->field_4_numMesh);
    DG_OBJS *pAlloc = (DG_OBJS *)GV_Malloc_8001620C(len);

    if (!pAlloc)
    {
        return 0;
    }
    else
    {
        int numMesh;
        DG_OBJ *pObjIter;

        GV_ZeroMemory_8001619c(pAlloc, len);
        pAlloc->world = DG_ZeroMatrix_8009D430;

        pAlloc->def = (DG_DEF *)pFileData;

        pAlloc->n_models = pFileData->field_0_numBones;

        pAlloc->flag = flag;
        pAlloc->chanl = chanl;
        pAlloc->light = &DG_LightMatrix_8009D384;

        pObjIter = &pAlloc->objs[0];
        for (numMesh = pFileData->field_4_numMesh; numMesh > 0; numMesh--)
        {
            pObjIter->model = (DG_MDL *)pMeshIter;
            if (pMeshIter->unknownA < 0)
            {
                pObjIter->extend = 0;
            }
            else
            {
                pObjIter->extend = &pAlloc->objs[pMeshIter->unknownA];
            }

            pObjIter->raise = sub_80031710(pMeshIter);

            pObjIter->n_packs = pMeshIter->numFace;
            pObjIter++;
            pMeshIter++;
        }
        return pAlloc;
    }
}
