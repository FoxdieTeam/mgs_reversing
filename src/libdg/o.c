#include "linker.h"
#include "Game/map.h"
#include "libdg.h"

extern MATRIX DG_LightMatrix_8009D384;
extern MATRIX DG_ZeroMatrix_8009D430;

int DG_MakeObjs_helper_80031710(DG_MDL *pMesh)

{
    int          val;
    int          mask;
    unsigned int flags;

    flags = pMesh->flags;
    val = 0;

    if ((flags & 0x300) != 0)
    {
        mask = 4 - (flags >> 12 & 3);
        val = mask * 0xfa;
        if ((flags & 0x100) == 0)
        {
            val = mask * -0xfa;
        }
    }

    return val;
}

DG_OBJS *DG_MakeObjs_80031760(DG_DEF *pFileData, int flag, int chanl)
{
    DG_MDL *pMeshIter = (DG_MDL *)&pFileData[1];

    const int len = sizeof(DG_OBJS) + (sizeof(DG_OBJ) * pFileData->num_mesh_4);
    DG_OBJS  *pAlloc = (DG_OBJS *)GV_Malloc_8001620C(len);

    if (!pAlloc)
    {
        return 0;
    }
    else
    {
        int     numMesh;
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
            if (pMeshIter->extend < 0)
            {
                pObjIter->extend = 0;
            }
            else
            {
                pObjIter->extend = &pAlloc->objs[pMeshIter->extend];
            }

            pObjIter->raise = DG_MakeObjs_helper_80031710(pMeshIter);

            pObjIter->n_packs = pMeshIter->n_faces;
            pObjIter++;
            pMeshIter++;
        }
        return pAlloc;
    }
}

void DG_FreeObjs_800318D0(DG_OBJS *pObjs)
{
    int     n_models;
    DG_OBJ *pObj;

    n_models = pObjs->n_models;
    pObj = pObjs->objs;
    while (n_models > 0)
    {
        DG_FreeObjPacket_8001AAD0(pObj, 0);
        DG_FreeObjPacket_8001AAD0(pObj, 1);
        --n_models;
        ++pObj;
    }
    DG_FreePreshade_80032110(pObjs);
    GV_Free_80016230(pObjs);
}

void DG_SetObjsRots_80031944( DG_OBJS *objs, SVECTOR *rot )
{
    objs->rots = rot;
}

//DG_SetObjsMovs
void DG_SetObjsMovs_8003194C( DG_OBJS *objs, SVECTOR *mov )
{
    objs->movs = mov;
}

