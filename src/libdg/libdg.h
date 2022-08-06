#ifndef LIBDG_H
#define LIBDG_H

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "libgv/libgv.h"
#include "libgv/actor.h"

typedef struct DG_TEX
{
    unsigned short field_0_hash;
    union {
        short s;
        char  b1, b2;
    } field_2_bUsed;
    short field_4_tPage;
    short field_6_clut;
    char  field_8_offx;
    char  field_9_offy;
    char  field_A_width;
    char  field_B_height;
} DG_TEX;

typedef struct KmdVec3
{
    int field_0_x;
    int field_4_y;
    int field_8_z;
} KmdVec3;

typedef struct _DG_MDL
{
    int                 flags_0;
    int                 numFaces_4;
    struct KmdVec3      max_8;
    struct KmdVec3      min_14;
    struct KmdVec3      pos_20;
    int                 parent_2C;
    int                 unknownA_30;
    int                 numVertex_34;
    SVECTOR            *vertexIndexOffset_38;
    unsigned char      *faceIndexOffset_3C;
    int                 numNormals_40;
    SVECTOR            *normalIndexOffset_44;
    unsigned char      *normalFaceOffset_48;
    unsigned char      *uvOffset_4C;
    unsigned short int *materialOffset_50; // hashed texture names
    int                 pad_54;
} DG_MDL;

typedef struct _DG_DEF
{
    int            num_bones_0; // or "model" count ?
    int            num_mesh_4;
    struct KmdVec3 max;
    struct KmdVec3 min;
} DG_DEF;

typedef struct _DG_OBJ
{
    MATRIX          world;      // 0x00
    MATRIX          screen;     // 0x20
    DG_MDL         *model;      // 0x40
    CVECTOR        *rgbs;       // 0x44
    struct _DG_OBJ *extend;     // 0x48
    short           bound_mode; // 0x4C
    short           free_count; // 0x4E
    short           raise;      // 0x50
    short           n_packs;    // 0x52
    POLY_GT4       *packs[2];   // 0x54
} DG_OBJ;

typedef struct _DG_OBJS
{
    MATRIX   world;      // 0x00
    MATRIX  *root;       // 0x20
    DG_DEF  *def;        // 0x24
    u_long   flag;       // 0x28
    u_short  group_id;   // 0x2C
    short    n_models;   // 0x2E
    short    chanl;      // 0x30
    short    bound_mode; // 0x32
    MATRIX  *light;      // 0x34
    SVECTOR *rots;       // 0x38
    SVECTOR *adjust;     // 0x3C
    SVECTOR *waist_rot;  // 0x40
    SVECTOR *movs;       // 0x44
    DG_OBJ   objs[0];    // 0x48
} DG_OBJS;

union Prim_Union {
    LINE_G2  line_g2;
    LINE_F4  line_f4;
    POLY_FT4 poly_ft4;
    TILE    *tiles;
};

struct DG_Rec_Unknown
{
    unsigned char field_0_prim_size;
    unsigned char field_1;
    unsigned char field_2;
    unsigned char field_3;
};

struct DG_PRIM;
typedef void (*TPrim_Fn)(struct DG_PRIM *pVec, void *primBuffer, int numPrims);

typedef struct _DG_PRIM
{
    MATRIX            world;
    MATRIX           *root;
    int               type;
    u_short           group_id;
    signed short      n_prims;
    u_short           chanl;
    u_short           field_2E_k500;
    u_short           field_30_prim_size;
    u_short           field_32;
    u_short           field_34;
    u_short           field_36;
    SVECTOR          *field_38_pUnknown;
    RECT             *field_3C;
    union Prim_Union *field_40_pBuffers[2];
    signed short      field_48_prim_count;
    u_short           field_4A;
    int               field_4C;
    TPrim_Fn          field_50_pFn;
} DG_PRIM;

typedef struct DG_Bounds
{
    KmdVec3 max;
    KmdVec3 min;
} DG_Bounds;

typedef struct
{
    short int field_0_x;
    short int field_2_y;
    short int field_4_z;
    short int field_6_w; // padding?
    short int field_8_brightness;
    short int field_A_radius;
    CVECTOR   field_C_colour;
} Light;

typedef struct
{
    int    field_0_lightCount;
    Light *field_4_pLights;
} DG_FixedLight;

typedef struct ImgFile
{
    unsigned int   unknown0;
    unsigned int   unknown1;
    unsigned char *unknown2;
    unsigned char *unknown3;
    unsigned char *unknown4;
} ImgFile;

typedef struct DG_KmdFile
{
    int          unknown0;
    unsigned int num_objects;
    int          unknown1[6];
    DG_MDL       objects[0];
} DG_KmdFile;

typedef struct DG_Vec3
{
    int x, y, z;
} DG_Vec3;

typedef struct DG_ZmdObject
{
    unsigned int numFaces;
    unsigned int numMeshes;
    DG_Vec3      start;
    DG_Vec3      end;
    DG_MDL       kmdObjects[0];
} DG_ZmdObject;

typedef struct DG_ZmdEntry
{
    unsigned int fileNameHashed;
    DG_ZmdObject data;
} DG_ZmdEntry;

typedef struct DG_ZmdFile
{
    unsigned int magic;
    unsigned int numZmds;
    unsigned int vertOffset;
    unsigned int bodyLength;
    DG_ZmdEntry  zmdEntries[0];
} DG_ZmdFile;

typedef struct NFile
{
    unsigned int   unknown0;
    unsigned char *unknown1;
} NFile;

typedef struct OarFile
{
    unsigned char *deep;
    unsigned int   recordSize;
    unsigned int   count;
    unsigned char *start;
    char           oarData[0];
} OarFile;

typedef struct DG_PcxFile
{
    unsigned char  signature;
    unsigned char  version;
    unsigned char  encoding;
    unsigned char  bpp;
    unsigned short xMin, yMin;
    unsigned short xMax, yMax;
    unsigned short hDpi, vDpi;
    unsigned char  palette[48];
    unsigned char  reserved0;
    unsigned char  channels;
    unsigned short bytesPerLine;
    unsigned short paletteMode;
    unsigned short hres, vres;
    // Unused 54 bytes in official PCX file format
    // MGS HEADER
    unsigned short mgsMagic; // always 1234
    unsigned short flags;
    unsigned short px, py; // pixels
    unsigned short cx, cy; // clut
    unsigned short n_colors;
    unsigned char  unused1[40];
    // Image data
    unsigned char data[0];
} DG_PcxFile;

typedef struct DG_Image
{
    RECT          dim;
    unsigned char data[512];
} DG_Image;

#define SetPackedRGB(p, r, g, b) (p)->rgbc = ((r << 16) | (g << 8)) | b;

typedef struct
{
    u_long tag;
    long   rgbc;
    short  x0, y0;
    short  w, h;
} TILE_PACKED;

//still figuring this one out
typedef struct DG_DivideFile 
{
    short   field_00;
    short   field_02;
    short   field_04;
    char    field_06;
    char    field_07;
    char    field_08;
    char    field_09;
    char    field_0A;
    char    field_0B;
    short   field_0C;
    short   field_0E;
    int     field_10;
} DG_DivideFile;

//MallocLog?
typedef struct DG_DivideMem
{
    long                    pad[3];
    int                     field_0C;   //0x0C
    unsigned long           field_10[4];//0x10
    GV_Heap*                pHeap;      //0x20
    GV_MemoryAllocation*    pAlloc;     //0x24
    void*                   addr;       //0x28
    void*                   pDataStart; //0x2C
    int                     size;       //0x30
    DG_DivideFile*          divide_file;//0x34
} DG_DivideMem;

typedef struct SgtFile
{
    unsigned int   unknown0;
    unsigned char *unknown1;
    unsigned char *unknown2;
    unsigned char *unknown3;
    unsigned char *unknown4;
    unsigned char *unknown5;
} SgtFile;

typedef struct DG_CHNL
{
    unsigned char *mOrderingTables[2]; // 257 pointers? // One for each active buffer
    short          word_6BC374_8;
    short          word_6BC376_16;
    short          word_6BC378_1;
    short          word_6BC37A_0_1EC_size;
    MATRIX         field_10_matrix;
    MATRIX         dword_6BC39C;
    short          word_6BC3BC; // Camera number?
    short          mTotalQueueSize;
    short          mFreePrimCount;
    short          mTotalObjectCount;
    DG_OBJS      **mQueue;
    RECT           field_5C_rect;
    RECT           field_64_rect;
    // One for each active buffer and for some reason passed as the root
    // to DrawOTag
    DR_ENV field_6C_dr_env[2];
    DR_ENV field_EC_dr_env[2];
    DR_ENV field_16C_dr_env[2];
} DG_CHNL;

static inline u_long LLOAD(from) void *from;
{
    return *(u_long *)from;
}

static inline void LSTORE(from, to) u_long from;
void              *to;
{
    *(u_long *)to = from;
}

static inline u_short SLOADL(from) void *from;
{
    return *(u_short *)from;
}

static inline void SSTOREL(from, to) // name restored
    u_short from;
void *to;
{
    *(u_short *)to = from;
}

static inline void LCOPY(s1, d1) void *s1, *d1;
{
    *(u_long *)d1 = *(u_long *)s1;
}

static inline void LCOPY2(s1, d1, s2, d2) void *s1, *d1;
void              *s2, *d2;
{
    u_long r1, r2;

    r1 = *(u_long *)s1;
    r2 = *(u_long *)s2;
    *(u_long *)d1 = r1;
    *(u_long *)d2 = r2;
}

// TODO: There are others like this as seen in the memleak

// invented name
static inline void DG_SetObjectGroupId(DG_OBJS *objs, int id)
{
    objs->group_id = id;
}

// invented name
static inline void DG_SetPrimGroupId(DG_PRIM *pPrim, int id)
{
    pPrim->group_id = id;
}

DG_PRIM *DG_MakePrim_8001BABC(int type, int prim_count, int chanl, SVECTOR *pVec, RECT *pRect);
int      DG_QueuePrim_80018274(DG_OBJS *pPrim);
void     DG_DequeuePrim_800182E0(DG_OBJS *pObjs);
void     DG_FreePrim_8001BC04(DG_OBJS *pPrim);
void     DG_PutPrim_8001BE00(MATRIX *matrix);
void     DG_Init_DrawEnv_80018384(DRAWENV *pDrawEnv, short clipX1, short clipY1, short clipX2, short clipY2);

void DG_SetPos_8001BC44(MATRIX *matrix);
void DG_SetPos2_8001BC8C(SVECTOR *svector, SVECTOR *svector2);
void DG_PutVector_8001BE48(SVECTOR *svector, SVECTOR *svector2, int count);
void DG_FreeObjPacket_8001AAD0(DG_OBJ *pObj, int idx);
void DG_FreeObjsPacket_8001ABA8(DG_OBJS *pObjs, int idx);
void DG_MovePos_8001BD20(SVECTOR *svector);
void DG_RotatePos_8001BD64(SVECTOR *svector);
void DG_RotVector_8001BE98(SVECTOR *svector, SVECTOR *svector2, int count);

void DG_MatrixRotZYX_8001E92C(MATRIX *mat, SVECTOR *vec);
void DG_MatrixRotYXZ_8001E734(MATRIX *pMatrix, SVECTOR *pVector);
void DG_TransposeMatrix_8001EAD8(MATRIX *in, MATRIX *out);

int DG_LoadInitPcx_8001F920(unsigned char *pFileData, int fileNameHashed);
int DG_LoadInitKmd_8001F4EC(unsigned char *pFileData, int fileNameHashed);
int DG_LoadInitLit_8001F6B4(unsigned char *pFileData, int fileNameHashed);
int DG_LoadInitNar_8001F5F8(unsigned char *pFileData, int fileNameHashed);
int DG_LoadInitOar_8001F610(unsigned char *pFileData, int fileNameHashed);
int DG_LoadInitKmdar_8001FAD0(unsigned char *pFileData, int fileNameHashed);
int DG_LoadInitImg_8001F644(unsigned char *pFileData, int fileNameHashed);
int sgt_file_handler_8001F670(unsigned char *pFileData, int fileNameHashed);

void DG_ClearTmpLight_8001A0E4();
int  DG_SetTmpLight_8001A114(SVECTOR *a1, int a2, int a3);
void DG_InitLightSystem_80019F40(void);
void DG_SetAmbient_80019F80(int param_1, int param_2, int param_3);

DG_TEX *DG_FindTexture_8001D830(int name);
int     DG_SearchForTextureRecord_8001D778(int hash, DG_TEX **ppFound);
void    DG_ClearTextureRecs_8001D808();
void    DG_ResetResidentTexture_8001DBEC();
void    DG_SetMainLightCol_8001A048(int r, int g, int b);
void    DG_SetMainLightDir_80019FF8(int x, int y, int z);

// divide
void*   sub_800190A0( GV_Heap* heap, GV_MemoryAllocation** alloc_list, int* size );

// unsorted
int  DG_AllocPacks_8001A670(DG_OBJ *pObj, int idx);
int  DG_DrawSyncResetGraph_8001F014(void);
int  DG_MakeObjPacket_8001AA50(DG_OBJ *pPrim, int idx, int flags);
int  DG_MakeObjs_helper_80031710(DG_MDL *pMesh);
void DG_80017194(void);
void DG_800174DC(MATRIX *matrix);
void DG_8001F1DC(void);
void DG_BoundChanl_helper2_80018E5C(DG_CHNL *chnl, int idx);
void DG_ClearChanlSystem_80017E9C(int which);
void DG_ClearResidentTexture_8001DB10(void);
void DG_Clip_80017594(RECT *pClipRect, int dist);
void DG_DrawOTag_80017E4C(int activeBuffer);
void DG_FreePreshade_80032110(DG_OBJS *pPrim);
void DG_InitChanlSystem_80017B98(int width);
void DG_InitDispEnv_800170F0(int x, short y, short w, short h, int clipH);
void DG_InitPolyGT4Pack_8001A6E4(DG_OBJ *pObj, int idx);
void DG_LoadInitPcx_helper_8001D880(unsigned short param_1, unsigned short param_2, unsigned short param_3, DG_Image *param_4, DG_Image *param_5, short param_6);
void DG_MakePreshade_80031F04(DG_OBJS *pPrim, short *pData, int dataCount);
void DG_PutObjs_8001BDB8(DG_OBJS *objs);
void DG_ReloadPalette_8001FC58(void);
void DG_RenderPipeline_800172A8(void);
void DG_RenderPipeline_80018028(int idx);
void DG_RenderPipeline_Init_8001715C(void);
void DG_ResetExtPaletteMakeFunc_800791E4(void);
void DG_ResetPaletteEffect_80078FF8(void);
void DG_Set_RGB_800184F4(int r, int b, int g);
void DG_StorePaletteEffect_80078F30(void);
void DG_Update1_8001F1BC(void);
void DG_Update2_8001F078(Actor *pActor);
void DG_WriteObjPacketRGB_8001A9B8(DG_OBJ *pDGObj, int idx);
void DG_WriteObjPacketUV_8001A774(DG_OBJ *pObj, int idx);
int  DG_PointCheckOne_8001C18C(DVECTOR *line);
void DG_OffsetDispEnv_80017784(int offset);
void DG_TextureCacheInit_8001F25C(void);
DG_OBJS *DG_MakeObjs_80031760(DG_DEF *pFileData, int flag, int chanl);
int DG_QueueObjs_80018178(DG_OBJS *pPrim);
void DG_DequeueObjs_800181E4(DG_OBJS *objs);
void DG_FreeObjs_800318D0(DG_OBJS *pObjs);

void Prim_lighting_80031954(SVECTOR *pVerts, int numVerts, unsigned char *workBuf, short *pSrcData, int srcDataLen);
void kmd_file_handler_link_vertices_to_parent_8001F3CC(DG_MDL *, DG_MDL *);

void sub_8001C248(DG_OBJS *objs, int n_obj);
void sub_8001C460(DG_OBJS *objs, int n_obj);
void sub_8001C5CC(DG_OBJS *objs, int n_obj);
void sub_8001C708(DG_OBJS *objs, int n_obj);
// process vecs in spad
SVECTOR *sub_8001AD28(SVECTOR *a1, int count);
// read vecs from spad
unsigned short *sub_8001B1E8(DG_PRIM *pDGPrim, short *pPrims, int prim_count);

#endif // LIBDG_H
