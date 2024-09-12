#ifndef _LIBDG_H_
#define _LIBDG_H_

#include "libgv/libgv.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "inline_n.h"
#include <gtemac.h>

/*---------------------------------------------------------------------------*/

typedef struct DG_VECTOR
{
    int vx;
    int vy;
    int vz;
} DG_VECTOR;            /* long word type 3D vector (without padding) */

typedef struct DG_SVECTOR
{
    short vx;
    short vy;
    short vz;
} DG_SVECTOR;           /* short word type 3D vector (without padding) */

typedef struct DG_RVECTOR
{
    DG_SVECTOR  v;
    u_char      uv[2];
    CVECTOR     c;
    DVECTOR     sxy;
    u_long      sz;
} DG_RVECTOR;           /* division vertex data (without padding) */

typedef struct DG_PVECTOR
{
    long vxy;
    long vz;
} DG_PVECTOR;

/*---------------------------------------------------------------------------*/

typedef struct DG_TEX
{
    u_short id;
    u_char  used;
    u_char  col;
    u_short tpage;
    u_short clut;
    u_char  off_x;
    u_char  off_y;
    u_char  w;
    u_char  h;
} DG_TEX;

enum DG_MODEL_FLAGS {
    DG_MODEL_TRANS    = 0x00002,
    DG_MODEL_UNLIT    = 0x00004,
    DG_MODEL_BOTHFACE = 0x00400,
    DG_MODEL_INDIRECT = 0x10000,
};

typedef struct _DG_MDL
{
    int             flags;
    int             n_faces;
    DG_VECTOR       min;
    DG_VECTOR       max;
    DG_VECTOR       pos;
    int             parent;
    int             extend;
    int             n_verts;
    SVECTOR        *vertices;
    unsigned char  *vindices;
    int             n_normals;
    SVECTOR        *normals;
    unsigned char  *nindices;
    unsigned char  *texcoords;
    unsigned short *materials; // hashed texture names
    int             padding;
} DG_MDL;

typedef struct _DG_DEF
{
    int              num_bones_0; // or "model" count ?
    int              num_mesh_4;
    struct DG_VECTOR max;
    struct DG_VECTOR min;
    DG_MDL model [ 0 ];
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
    POLY_GT4       *packs[ 2 ]; // 0x54
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
    DG_OBJ   objs[ 0 ];  // 0x48
} DG_OBJS;


// It might be better to use a void * for this
union Prim_Union
{
    LINE_G2  line_g2;
    LINE_F2  line_f2;
    LINE_F4  line_f4;
    POLY_GT4 poly_gt4;
    POLY_FT4 poly_ft4;
    TILE     tiles;
    POLY_FT4 poly_ft4_multi[4][2];

    unsigned short u16_access[0];
    int            s32_access[0];
};

typedef struct _DG_PRIM_INFO
{
    unsigned char psize;
    unsigned char verts;
    unsigned char voffset;
    unsigned char vstep;
} DG_PRIM_INFO;

struct _DG_PRIM;
typedef POLY_FT4 * ( *TPrim_Fn )( struct _DG_PRIM *prim, POLY_FT4 *pPolys, int numPrims );

typedef struct _DG_PRIM
{
    MATRIX            world;
    MATRIX           *root;
    int               type;
    u_short           group_id;
    signed short      n_prims;
    short             chanl;
    short             field_2E_k500;
    short             psize;
    short             verts;
    short             voffset;
    short             vstep;
    SVECTOR          *vertices;
    RECT             *field_3C;
    union Prim_Union *packs[ 2 ];
    signed short      n_vertices;
    void             *userdata;
    TPrim_Fn          handler;
} DG_PRIM;

typedef struct DG_Bounds
{
    DG_VECTOR max;
    DG_VECTOR min;
} DG_Bounds;

typedef struct DG_LIT
{
    SVECTOR        pos;
    unsigned short field_8_brightness;
    unsigned short field_A_radius;
    CVECTOR        field_C_colour;
} DG_LIT;

typedef struct DG_FixedLight
{
    int       field_0_lightCount;
    DG_LIT *field_4_pLights;
} DG_FixedLight;

typedef struct DG_TmpLightList
{
    int      n_lights;
    DG_LIT lights[ 8 ];
} DG_TmpLightList;

typedef struct DG_LitVertex
{
    SVECTOR intensity[2];
    CVECTOR color[2];
} DG_LitVertex;

typedef struct DG_IMG_ATTRIB
{
    unsigned char texid;
    unsigned char xoff;
    unsigned char yoff;
    unsigned char unused;
} DG_IMG_ATTRIB;

typedef struct DG_IMG
{
    unsigned short  image_width;
    unsigned short  image_height;
    unsigned short  tile_width;
    unsigned short  tile_height;
    unsigned short *textures; // textures[0] = count
    DG_IMG_ATTRIB  *attribs;
    unsigned char  *tilemap;
} DG_IMG;

typedef struct DG_KMD
{
    unsigned int n_visible;
    unsigned int n_objects;
    DG_VECTOR    min;
    DG_VECTOR    max;
    DG_MDL       objects[ 0 ];
} DG_KMD;

typedef struct DG_ZmdEntry
{
    unsigned int id;
    DG_KMD       data;
} DG_ZmdEntry;

typedef struct DG_ZmdFile
{
    unsigned int magic;
    unsigned int numZmds;
    unsigned int vertOffset;
    unsigned int bodyLength;
    DG_ZmdEntry  zmdEntries[ 0 ];
} DG_ZmdFile;

/*---------------------------------------------------------------------------*/

typedef struct DG_NARS
{
    unsigned int   unknown0;
    unsigned char *unknown1;
} DG_NARS;

typedef unsigned short MOTION_ARCHIVE;
typedef unsigned short MOTION_TABLE;

typedef struct DG_OAR
{
    MOTION_ARCHIVE *archive;
    unsigned int   n_joint;
    unsigned int   n_motion;
    MOTION_TABLE   *table;
    char           oarData[ 0 ];
} DG_OAR;

typedef struct MOTION_SEGMENT
{
    SVECTOR         field_0;
    SVECTOR         field_8;
    int             field_10;
    unsigned short *field_14;
    short           field_18;
    short           field_1A;
    unsigned char   field_1C;
    char            field_1D[7];
} MOTION_SEGMENT;

/*---------------------------------------------------------------------------*/

typedef struct PCXINFO
{
    unsigned short  magic;      /* always 1234 */
    unsigned short  flags;
    unsigned short  px, py;     /* pixel X/Y coords */
    unsigned short  cx, cy;     /* CLUT  X/Y coords */
    unsigned short  n_colors;
} PCXINFO;

typedef struct PCXDATA
{
    unsigned char   manufacturer;
    unsigned char   version;
    unsigned char   encoding;
    unsigned char   bits_per_pixel;
    unsigned short  min_x, min_y;
    unsigned short  max_x, max_y;
    unsigned short  dpi_x, dpi_y;
    unsigned char   header_palette[ 48 ];
    unsigned char   reserved;
    unsigned char   n_planes;
    unsigned short  bytes_per_line;
    unsigned short  header_palette_class;
    unsigned short  screen_width, screen_height;
    PCXINFO         info;
    unsigned char   pad[ 54 - sizeof(PCXINFO) ];
    unsigned char   data[ 0 ];  /* image data */
} PCXDATA;

/*
typedef struct {
    u_char mode;
    u_char bit;
    u_short color;
    u_short width;
    u_short height;
    u_short flag;
    u_short px, py;
    u_short cx, cy;
    u_short n_data;
} PLL_HEADER;
*/

typedef struct DG_Image
{
    RECT          dim;
    unsigned char data[ 512 ];
} DG_Image;

// still figuring this one out
typedef struct DG_DivideFile
{
    short field_00;
    short field_02;
    short field_04;
    char  field_06;
    char  field_07;
    char  field_08;
    char  field_09;
    char  field_0A;
    char  field_0B;
    short field_0C;
    short field_0E;
    int   field_10;
} DG_DivideFile;

// MallocLog?
typedef struct DG_DivideMem         // private to libdg/divide.c
{
    long                *ot;         // 0x00
    short                field_04;   // 0x04
    unsigned short       raise;      // 0x06
    long                 opz;        // 0x08 outer product
    int                  field_0C;   // 0x0C  some sort of delta
    long                 field_10;   // 0x10
    long                 field_14;   // 0x14
    long                 field_18;   // 0x18
    POLY_GT4            *pack;       // 0x1C
    GV_HEAP             *pHeap;      // 0x20
    GV_ALLOC *pAlloc;     // 0x24
    int                  n_packs;    // 0x28
    void                *pDataStart; // 0x2C
    int                  size;       // 0x30
    DG_RVECTOR          *rvec;       // 0x34
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
    unsigned char *mOrderingTables[ 2 ]; // 257 pointers? // One for each active buffer
    short          word_6BC374_8;
    short          word_6BC376_16;
    short          word_6BC378_1;
    short          word_6BC37A_0_1EC_size;
    MATRIX         field_10_eye_inv;
    MATRIX         field_30_eye;
    short          field_50_clip_distance;
    short          mTotalQueueSize;
    short          mFreePrimCount;
    short          mTotalObjectCount;
    DG_OBJS      **mQueue; // queue can contain DG_PRIM as well, probably void*
    RECT           field_5C_clip_rect;
    RECT           field_64_rect;
    // One for each active buffer and for some reason passed as the root
    // to DrawOTag
    DR_ENV         field_6C_dr_env[ 2 ];
    DR_ENV         field_EC_dr_env[ 2 ];
    DR_ENV         field_16C_dr_env[ 2 ];
} DG_CHNL;

//Prim types
//0x12 = POLY_FT4
//0x15 = POLY_GT4?
//0x409 = TILE?

enum DG_FLAGS
{
    DG_FLAG_TEXT        = 0x0001,
    DG_FLAG_PAINT       = 0x0002,
    DG_FLAG_TRANS       = 0x0004,
    DG_FLAG_SHADE       = 0x0008,
    DG_FLAG_BOUND       = 0x0010,
    DG_FLAG_GBOUND      = 0x0020,
    DG_FLAG_ONEPIECE    = 0x0040,
    DG_FLAG_INVISIBLE   = 0x0080,
    DG_FLAG_AMBIENT     = 0x0100,
    DG_FLAG_IRTEXTURE   = 0x0200,
    DG_FLAG_UNKNOWN_400 = 0x0400,
};

enum DG_PRIM_FLAGS
{
    DG_PRIM_VISIBLE   = 0x0000,
    DG_PRIM_INVISIBLE = 0x0100,
    DG_PRIM_SCREEN    = 0x0200,
    DG_PRIM_OFFSET    = 0x0400,
    DG_PRIM_SORTONLY  = 0x0800,
    DG_PRIM_ONEFACE   = 0x1000,
    DG_PRIM_FREEPACKS = 0x2000,
    // ...
};

// TODO: make all DG_GetPrim calls use this enum
enum DG_PRIM_TYPE
{
    DG_PRIM_LINE_F2,
    DG_PRIM_LINE_F3,
    DG_PRIM_LINE_F4,
    DG_PRIM_LINE_G2,
    DG_PRIM_LINE_G3,
    DG_PRIM_LINE_G4,
    DG_PRIM_SPRT,
    DG_PRIM_SPRT_8,
    DG_PRIM_SPRT_16,
    DG_PRIM_TILE,
    DG_PRIM_TILE_1,
    DG_PRIM_TILE_8,
    DG_PRIM_TILE_16,
    DG_PRIM_POLY_F3,
    DG_PRIM_POLY_F4,
    DG_PRIM_POLY_G3,
    DG_PRIM_POLY_G4,
    DG_PRIM_POLY_FT3,
    DG_PRIM_POLY_FT4,
    DG_PRIM_POLY_GT3,
    DG_PRIM_POLY_GT4,
    DG_PRIM_LINE_FT2,
    DG_PRIM_LINE_GT2,
    DG_PRIM_FREE,
    DG_PRIM_MAX
};

enum DG_CHANL
{
    DG_CHANL_SCREEN,
    DG_CHANL_BOUND,
    DG_CHANL_TRANS,
    DG_CHANL_SHADE,
    DG_CHANL_PRIM,
    DG_CHANL_DIVIDE,
    DG_CHANL_SORT,
};

/*
    DG_PRIM_TILE_1, DG_PRIM_TILE_8, DG_PRIM_TILE_16,
    DG_PRIM_POLY_F3, DG_PRIM_POLY_F4, DG_PRIM_POLY_G3, DG_PRIM_POLY_G4,
    DG_PRIM_POLY_FT3, DG_PRIM_POLY_FT4, DG_PRIM_POLY_GT3, DG_PRIM_POLY_GT4,
    DG_PRIM_LINE_FT2, DG_PRIM_LINE_GT2,
    DG_PRIM_FREE
*/
#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE |\
                    DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE) // 0x32d

#define BODY_FLAG2  ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE) // 0x2d

#define SHADOW_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE |\
                    DG_FLAG_ONEPIECE | DG_FLAG_AMBIENT) // 0x16d

#define WEAPON_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE |\
                    DG_FLAG_ONEPIECE) // 0x6d

#define RevisionDir( a )  a &= 4095
#define INIT_VEC( vec,xx,yy,zz ) { (vec).vx = xx; (vec).vy = yy; (vec).vz = zz; }

/*---------------------------------------------------------------------------*/

static inline void DG_VisibleObjs( DG_OBJS *objs )
{
    objs->flag &= ~DG_FLAG_INVISIBLE;
}

static inline void DG_InvisibleObjs( DG_OBJS *objs )
{
    objs->flag |= DG_FLAG_INVISIBLE;
}

static inline void DG_UnAmbientObjs( DG_OBJS *objs )
{
    objs->flag &= ~DG_FLAG_AMBIENT;
}

static inline void DG_AmbientObjs( DG_OBJS *objs )
{
    objs->flag |= DG_FLAG_AMBIENT;
}

static inline void DG_GroupObjs( DG_OBJS *objs, int group_id )
{
    objs->group_id = group_id;
}

static inline void DG_GroupPrim( DG_PRIM *prim, int group_id )
{
    prim->group_id = group_id;
}

static inline void DG_VisiblePrim( DG_PRIM *prim )
{
    prim->type &= ~DG_PRIM_INVISIBLE;
}

static inline void DG_InvisiblePrim( DG_PRIM *prim )
{
    prim->type |= DG_PRIM_INVISIBLE;
}

static inline void DG_UnShadeObjs( DG_OBJS *objs )
{
    objs->flag &= ~DG_FLAG_SHADE;
}

static inline void DG_UnBoundObjs( DG_OBJS *objs )
{
    objs->flag &= ~DG_FLAG_BOUND;
}

static inline void DG_UnGBoundObjs( DG_OBJS *objs )
{
    objs->flag &= ~DG_FLAG_GBOUND;
}

static inline void DG_GBoundObjs( DG_OBJS *objs )
{
    objs->flag |= DG_FLAG_GBOUND;
}

/*---------------------------------------------------------------------------*/

typedef void (*TChanl_Fn)(DG_CHNL *chnl, int idx);

/* dgd.c */
int  DG_DrawSyncResetGraph( void );
void DG_StartFrame( GV_ACT *actor );
void DG_EndFrame( void );
void DG_ResetPipeline( void );
void DG_TextureCacheInit( void );
void DG_StartDaemon(void);

/* bound.c */
void DG_BoundStart( void );
void DG_BoundChanl( DG_CHNL *chnl, int idx );
void DG_BoundEnd( void );

/* chanl.c */
void DG_InitChanlSystem( int width );
void DG_DrawOTag( int activeBuffer );
void DG_ClearChanlSystem( int which );
void DG_RenderPipeline( int idx );
void DG_SetRenderChanlDrawEnv( int chanl, DRAWENV *pDrawEnv );
int  DG_QueueObjs( DG_OBJS *prim );
void DG_DequeueObjs( DG_OBJS *objs );
int  DG_QueuePrim( DG_PRIM *prim );
void DG_DequeuePrim( DG_PRIM *prim );
void DG_InitDrawEnv( DRAWENV *pDrawEnv, int clipX1, int clipY1, int clipX2, int clipY2 );
void DG_FreeObjectQueue( void );
void DG_ResetObjectQueue( void );
void DG_SetBackgroundRGB( int r, int g, int b );
void DG_SetRGB( int r, int b, int g );
void DG_BackGroundBlack( void );
void DG_BackGroundNormal( void );
void DG_InitBackgroundTile( TILE *tile );
TChanl_Fn DG_SetChanlSystemUnits( int idx, TChanl_Fn newFunc );

/* display.c */
void DG_InitDispEnv( int x, short y, short w, short h, int clipH );
void DG_ChangeReso( int );
void DG_RenderPipeline_Init( void );
void DG_SwapFrame( void );
void DG_RenderPipeline_800172A8( void );
void DG_LookAt( DG_CHNL *chnl, SVECTOR *eye, SVECTOR *center, int clip_distance );
void DG_AdjustOverscan( MATRIX *matrix );
void DG_Clip( RECT *clip_rect, int dist );
void DG_OffsetDispEnv( int offset );
void DG_ClipDispEnv( int x, int y );
void DG_DisableClipping( void );
DISPENV *DG_GetDisplayEnv( void );

/* divide.c */
void DG_DivideStart( void );
void DG_DivideChanl( DG_CHNL* chnl, int idx );
void DG_DivideEnd( void );

/* light.c */
void DG_InitLightSystem( void );
void DG_SetAmbient( int vx, int vy, int vz );
void DG_SetMainLightDir( int x, int y, int z );
void DG_SetMainLightCol( int r, int g, int b );
void DG_ResetFixedLight( void );
void DG_SetFixedLight( DG_LIT *light, int light_count );
void DG_ClearTmpLight( void );
int  DG_SetTmpLight( SVECTOR *svec, int brightness, int radius );
void DG_GetLightVector( VECTOR *in_vec, int divisor, SVECTOR *out_vec );
int  DG_GetLightMatrix( SVECTOR *vec, MATRIX *mtx );
void DG_SetLightMatrix( MATRIX* mtx, int trans_x );
int  DG_GetLightMatrix2( SVECTOR *vec, MATRIX *mtx );

/* loader.c */
int DG_LoadInitKmd( unsigned char *buf, int id );
int DG_LoadInitNar( unsigned char *buf, int id );
int DG_LoadInitOar( unsigned char *buf, int id );
int DG_LoadInitImg( unsigned char *buf, int id );
int DG_LoadInitSgt( unsigned char *buf, int id );
int DG_LoadInitLit( unsigned char *buf, int id );
int DG_LoadInitPcx( unsigned char *buf, int id );
int DG_LoadInitKmdar( unsigned char *buf, int id );

/* matrix.c */
void DG_MatrixRot( MATRIX *mat, SVECTOR *svec );
void DG_MatrixRotYXZ( MATRIX *mat, SVECTOR *svec );
void DG_MatrixRotZYX( MATRIX *mat, SVECTOR *vec );
void DG_TransposeMatrix( MATRIX *in, MATRIX *out );
void DG_ShadowMatrix( MATRIX *out, MATRIX *in, int param_3 );
void DG_ReflectVector( SVECTOR *in, SVECTOR *translation, SVECTOR *out );
void DG_ReflectMatrix( SVECTOR *svec, MATRIX *in, MATRIX *out );

/* o.c */
DG_OBJS *DG_MakeObjs( DG_DEF *def, int flag, int chanl );
void     DG_FreeObjs( DG_OBJS *objs );
void     DG_SetObjsRots( DG_OBJS *objs, SVECTOR *rot );
void     DG_SetObjsMovs( DG_OBJS *objs, SVECTOR *mov );

/* opack.c */
void DG_WriteObjPacketUV( DG_OBJ* obj, int idx );
void DG_WriteObjPacketRGB( DG_OBJ *obj, int idx );
int  DG_MakeObjPacket( DG_OBJ *obj, int idx, int flags );
void DG_FreeObjPacket( DG_OBJ *obj, int idx );
int  DG_MakeObjsPacket( DG_OBJS *objs, int idx );
void DG_FreeObjsPacket( DG_OBJS *objs, int idx );

/* palette.c */
void DG_StorePalette( void );
void DG_ReloadPalette( void );

/* prim.c */
void DG_PrimStart( void );
void DG_PrimChanl( DG_CHNL *chnl, int idx );
void DG_PrimEnd( void );
DG_PRIM *DG_MakePrim(int type, int prim_count, int chanl, SVECTOR *pVec, RECT *pRect);
void DG_FreePrim( DG_PRIM *prim );
void DG_SetFreePrimParam( int psize, int verts, int voffset, int vstep );

/* pshade.c */
int  DG_MakePreshade( DG_OBJS *prim, DG_LIT *light, int numLights );
void DG_FreePreshade( DG_OBJS *prim );

/* screen.c */
void DG_SetPos( MATRIX *matrix );
void DG_SetPos2( SVECTOR *svector, SVECTOR *svector2 );
void DG_MovePos( SVECTOR *svector );
void DG_RotatePos( SVECTOR *svector );
void DG_PutObjs( DG_OBJS *objs );
void DG_PutPrim( MATRIX *matrix );
void DG_PutVector( SVECTOR *svector, SVECTOR *svector2, int count );
void DG_RotVector( SVECTOR *svector, SVECTOR *svector2, int count );
void DG_PersVector( SVECTOR *svector, DVECTOR *dvector, int count );
void DG_PointCheck( SVECTOR *svector, int n_points );
int  DG_PointCheckOne( DVECTOR *line );
// void DG_ScreenModelsSingle( DG_OBJS *objs, int n_obj );
// void DG_ScreenModels( DG_OBJS *objs, int n_obj );
// void DG_ApplyMovs( DG_OBJS *objs, int n_obj );
// void DG_ApplyRots( DG_OBJS *objs, int n_obj );
void DG_ScreenChanl( DG_CHNL *chnl, int idx );

/* shade.c */
void DG_ShadeStart( void );
void DG_ShadeChanl(DG_CHNL *chnl, int idx);
void DG_ShadeEnd( void );

/* sort.c */
void DG_SortChanl( DG_CHNL *chnl, int idx );

/* text.c */
int  DG_SearchTexture( int hash, DG_TEX **ppFound );
void DG_InitTextureSystem( void );
DG_TEX *DG_GetTexture( int name );
void DG_SetTexture( int hash, int tp, int abr, DG_Image *a, DG_Image *b, int col );
void DG_GetTextureRect( DG_TEX* tex, RECT* rect );
void DG_GetClutRect( DG_TEX* tex, RECT* rect );
void DG_ClearResidentTexture( void );
void DG_SaveTexureCacheToResidentMem( void );
void DG_ResetResidentTexture( void );

/* trans.c */
void DG_TransStart( void );
void DG_TransChanl( DG_CHNL *chnl, int idx );
void DG_TransEnd( void );

/* ???.c */
void sub_80078F04( void );
void DG_StorePaletteEffect_80078F30( void );
void DG_ResetPaletteEffect_80078FF8( void );
void sub_80079004( unsigned short param_1 );
void sub_800790E8( void );
void sub_8007913C( void );
void set_pal_effect_fns_80079194( void (*param_1)(void), u_short (*param_2)(u_short) );
void DG_ResetExtPaletteMakeFunc_800791E4(void);
void DG_MakeEffectPalette_80079220( unsigned short *param_1, int param_2 );

// unsorted
void DG_FadeScreen(int amount);

static inline DG_CHNL *DG_Chanl( int idx )
{
    extern DG_CHNL DG_Chanls_800B1800[ 3 ];
    return &DG_Chanls_800B1800[ idx + 1 ];
}

static inline char *DG_ChanlOTag(int index)
{
    extern int GV_Clock_800AB920;
    return DG_Chanl(index)->mOrderingTables[GV_Clock_800AB920];
}

/*---------------------------------------------------------------------------*/

static inline DG_PRIM *DG_GetPrim( int type, int prim_count, int chanl, SVECTOR *vec, RECT *pRect )
{
    extern int  GM_CurrentMap_800AB9B0;
    DG_PRIM     *prim;

    prim = DG_MakePrim( type, prim_count, chanl, vec, pRect );
    if ( prim )
    {
        DG_QueuePrim( prim );
        DG_GroupPrim( prim, GM_CurrentMap_800AB9B0 );
    }
    return prim;
}

static inline void DG_SetPacketTexture( POLY_FT4 *packs0, DG_TEX *tex )
{
    int x, y, w, h;
    x = tex->off_x ;
    w = tex->w ;
    y = tex->off_y ;
    h = tex->h ;

    setUVWH( packs0, x, y, w, h ) ;
}

static inline void DG_SetPacketTexture4( POLY_FT4 *packs0, DG_TEX *tex )
{
    DG_SetPacketTexture( packs0, tex ) ;
    packs0->tpage = tex->tpage ;
    packs0->clut = tex->clut ;
}

// clang-format off
// gte_MulMatrix0 but without updating the current rotation matrix
#define DG_MulRotMatrix0(r1, r2) \
{                                \
    gte_ldclmv(r1);              \
    gte_rtir();                  \
    gte_stclmv(r2);              \
    gte_ldclmv((char *)r1 + 2);  \
    gte_rtir();                  \
    gte_stclmv((char *)r2 + 2);  \
    gte_ldclmv((char *)r1 + 4);  \
    gte_rtir();                  \
    gte_stclmv((char *)r2 + 4);  \
}

// gte_CompMatrix but without updating the current matrices
#define DG_CompMatrix(r1, r2)    \
{                                \
	gte_ldlv0((char *)r1 + 20);  \
	gte_rt();		             \
	gte_stlvnl((char *)r2 + 20); \
    DG_MulRotMatrix0(r1, r2);    \
}
// clang-format on

#endif // _LIBDG_H_
