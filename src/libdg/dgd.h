#ifndef _DGD_H
#define _DGD_H

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

#include "libdg/libdg.h"

typedef struct          DG_CHNL
{
    unsigned char       *mOrderingTables[2]; // 257 pointers? // One for each active buffer
    short               word_6BC374_8;
    short               word_6BC376_16;
    short               word_6BC378_1;
    short               word_6BC37A_0_1EC_size;
    MATRIX              field_10_matrix;
    MATRIX              dword_6BC39C;
    short               word_6BC3BC; // Camera number?
    short               mTotalQueueSize;
    short               mFreePrimCount;
    short               mTotalObjectCount;
    DG_OBJS**           mQueue;
    RECT                field_5C_rect;
    RECT                field_64_rect;
    // One for each active buffer and for some reason passed as the root
    // to DrawOTag
    DR_ENV              field_6C_dr_env[2];
    DR_ENV              field_EC_dr_env[2];
    DR_ENV              field_16C_dr_env[2];
} DG_CHNL;

typedef struct          DG_Vec3
{
    int                 x, y, z;
} DG_Vec3;

typedef struct          DG_KmdObject
{
    int                 field_0_flags;
    int                 field_4_numFaces;
    DG_Vec3             boundingBox[2];
    DG_Vec3             translation;
    int                 mRef_2C_parentObjIndex;
    int                 mObjPosNum_30_translationUnk;

    int                 numVerts_34;
    SVECTOR             *vertOfs_38;
    unsigned char       *indexOfs_3C;

    int                 numNorms_40;
    SVECTOR             *normOfs_44;
    unsigned char       *normIndex_48;

    unsigned char       *ofsUV_4C;
    unsigned short int  *ofsTextureNameHashes_50;
    unsigned int        nullpad_54;
} DG_KmdObject;


typedef void    (*TChanl_Fn)(DG_CHNL *pOt, int idx);
typedef int     (*TFileExtHandler)(unsigned char *pFileData, int fileNameHashed);

void            DG_StartDaemon_8001F284(void);
void            GV_SetLoader_80015418(int fileExtChar, TFileExtHandler pFn);

#endif // _DGD_H
