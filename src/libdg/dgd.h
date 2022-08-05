#ifndef _DGD_H
#define _DGD_H

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

#include "libdg/libdg.h"

typedef struct DG_KmdObject
{
    int     field_0_flags;
    int     field_4_numFaces;
    DG_Vec3 boundingBox[2];
    DG_Vec3 translation;
    int     mRef_2C_parentObjIndex;
    int     mObjPosNum_30_translationUnk;

    int            numVerts_34;
    SVECTOR       *vertOfs_38;
    unsigned char *indexOfs_3C;

    int            numNorms_40;
    SVECTOR       *normOfs_44;
    unsigned char *normIndex_48;

    unsigned char      *ofsUV_4C;
    unsigned short int *ofsTextureNameHashes_50;
    unsigned int        nullpad_54;
} DG_KmdObject;

typedef void (*TChanl_Fn)(DG_CHNL *pOt, int idx);

void DG_StartDaemon_8001F284(void);

#endif // _DGD_H
