#ifndef _DGD_H
#define _DGD_H

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

struct _DG_OBJS;
struct DG_OBJS;

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
    struct DG_OBJS      **mQueue;
    RECT                dword_6BC3C8_pStructure_rect;
    RECT                dword_6BC3D0_rect;
    DR_ENV              dword_6BC3D8_dst[2]; // One for each active buffer
    DR_ENV              dword_6BC458; // prob also an array of 2
    DR_ENV              dword_6BC498;
    DR_ENV              dword_6BC4D8_src_dr_env1[2];
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
