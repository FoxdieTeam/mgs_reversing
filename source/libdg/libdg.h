/**
 * @file    libdg.h
 * @brief   Display Generator library header
 */

#ifndef __MGS_LIBDG_H__
#define __MGS_LIBDG_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "inline_n.h"
#include <gtemac.h>

#include "libgv/libgv.h"
#include "fmt_img.h"
#include "fmt_kmd.h"
#include "fmt_lit.h"
#include "fmt_mot.h"
#include "fmt_tex.h"

#define DG_MAX_JOINTS 24

/*---------------------------------------------------------------------------*/

/* TODO: Remove */
typedef struct DG_VECTOR
{
    int vx;
    int vy;
    int vz;
} DG_VECTOR;            /* long word type 3D vector (without padding) */

/* TODO: Remove */
typedef struct DG_SVECTOR
{
    short vx;
    short vy;
    short vz;
} DG_SVECTOR;           /* short word type 3D vector (without padding) */

/* TODO: Remove */
typedef struct DG_RVECTOR
{
    DG_SVECTOR  v;
    u_char      uv[2];
    CVECTOR     c;
    DVECTOR     sxy;
    u_long      sz;
} DG_RVECTOR;           /* division vertex data (without padding) */

/* TODO: Remove */
typedef struct DG_PVECTOR
{
    long vxy;
    long vz;
} DG_PVECTOR;

/*---------------------------------------------------------------------------*/

#define DG_MAX_TEXTURES 512

// clang-format off
typedef struct _DG_TEX {
        u_short         id;             //
        u_char          used;           //
        u_char          col;            //
        u_short         tpage;          //
        u_short         clut;           //
        u_char          off_x;          //
        u_char          off_y;          //
        u_char          w;              //
        u_char          h;              //
} DG_TEX;

typedef struct _DG_OBJ {
        MATRIX          world;          // 0x00
        MATRIX          screen;         // 0x20
        DG_MDL          *model;         // 0x40
        CVECTOR         *rgbs;          // 0x44
        struct _DG_OBJ  *extend;        // 0x48
        short           bound_mode;     // 0x4C
        short           free_count;     // 0x4E
        short           raise;          // 0x50
        short           n_packs;        // 0x52
        POLY_GT4        *packs[ 2 ];    // 0x54
} DG_OBJ;

typedef struct _DG_OBJS {
        MATRIX          world;          // 0x00
        MATRIX          *root;          // 0x20
        DG_DEF          *def;           // 0x24
        u_long          flag;           // 0x28
        u_short         group_id;       // 0x2C
        short           n_models;       // 0x2E
        short           chanl;          // 0x30
        short           bound_mode;     // 0x32
        MATRIX          *light;         // 0x34
        SVECTOR         *rots;          // 0x38
        SVECTOR         *adjust;        // 0x3C
        SVECTOR         *waist_rot;     // 0x40
        SVECTOR         *movs;          // 0x44
        DG_OBJ          objs[ 0 ];      // 0x48
} DG_OBJS;

enum {
        DG_FLAG_TEXT            = 0x0001,       //
        DG_FLAG_PAINT           = 0x0002,       //
        DG_FLAG_TRANS           = 0x0004,       //
        DG_FLAG_SHADE           = 0x0008,       //
        DG_FLAG_BOUND           = 0x0010,       //
        DG_FLAG_GBOUND          = 0x0020,       //
        DG_FLAG_ONEPIECE        = 0x0040,       //
        DG_FLAG_INVISIBLE       = 0x0080,       //
        DG_FLAG_AMBIENT         = 0x0100,       //
        DG_FLAG_IRTEXTURE       = 0x0200,       //
        DG_FLAG_ENVMAP          = 0x0400,       //
};
// clang-format on

typedef struct _DG_PRIM {
    MATRIX   world;
    MATRIX  *root;
    int      type;
    u_short  group_id;
    short    prim_count;
    short    chanl;
    short    raise;
    short    psize;
    short    verts;
    short    voffset;
    short    vstep;
    SVECTOR *pos;
    RECT    *rect;
    void    *packs[ 2 ];
    short    n_prims;
    void    *userdata;
    void    *(*callback)(struct _DG_PRIM *, POLY_FT4 *, int);
} DG_PRIM;

#define MAX_TMPLIGHTS  8
#define MAX_FIX_LIGHTS 8

/* Should be local to light.c */
typedef struct _TLIGHT {
    int    n_lights;
    DG_LIT lights[ MAX_TMPLIGHTS ];
} TLIGHT;

/* Should be local to light.c */
typedef struct _FIXLIGHT {
    int     n_lights;
    DG_LIT *lights;
} FIXLIGHT;

/* Should be local to pshade.c */
typedef struct _PLIGHT {
    SVECTOR point[2];
    CVECTOR color[2];
} PLIGHT;

/*---------------------------------------------------------------------------*/

typedef struct _DG_IMAGE {
    RECT          dim;
    unsigned char data[ 512 ];
} DG_IMAGE;

typedef struct _DG_CHANL {
    u_long   *ot[ 2 ]; // 257 pointers? // One for each active buffer
    short     ot_size;
    short     link;
    short     dblbuf; /* double buffer */
    short     dirty;
    MATRIX    eye_inv;
    MATRIX    eye;
    short     screen;
    short     queue_size;
    short     prim_index;
    short     objs_index;

    /* TODO: retype as (void **) */
    DG_OBJS **queue; // queue of DG_OBJS followed by DG_PRIM

    RECT      clip_rect;
    RECT      new_clip_rect;
    DR_ENV    env1[ 2 ]; // used when entering the channel
    DR_ENV    env2[ 2 ]; // used when returning to the background channel
    DR_ENV    new_env[ 2 ];
} DG_CHANL;

enum {
    DG_PRIM_LINE_F2,    // 0
    DG_PRIM_LINE_F3,    // 1
    DG_PRIM_LINE_F4,    // 2
    DG_PRIM_LINE_G2,    // 3
    DG_PRIM_LINE_G3,    // 4
    DG_PRIM_LINE_G4,    // 5
    DG_PRIM_SPRT,       // 6
    DG_PRIM_SPRT_8,     // 7
    DG_PRIM_SPRT_16,    // 8
    DG_PRIM_TILE,       // 9
    DG_PRIM_TILE_1,     // 10
    DG_PRIM_TILE_8,     // 11
    DG_PRIM_TILE_16,    // 12
    DG_PRIM_POLY_F3,    // 13
    DG_PRIM_POLY_F4,    // 14
    DG_PRIM_POLY_G3,    // 15
    DG_PRIM_POLY_G4,    // 16
    DG_PRIM_POLY_FT3,   // 17
    DG_PRIM_POLY_FT4,   // 18
    DG_PRIM_POLY_GT3,   // 19
    DG_PRIM_POLY_GT4,   // 20
    DG_PRIM_LINE_FT2,   // 21
    DG_PRIM_LINE_GT2,   // 22
    DG_PRIM_FREE,       // 23
    DG_PRIM_MAX         // 24
};

// clang-format off
enum {
        DG_PRIM_VISIBLE         = 0x0000,
        DG_PRIM_INVISIBLE       = 0x0100,

        DG_PRIM_ON_WORLD        = 0x0000,
        DG_PRIM_ON_CAMERA       = 0x0200,

        DG_PRIM_VERTICES        = 0x0000,
        DG_PRIM_RECTANGLE       = 0x0400,

        DG_PRIM_SORTONLY        = 0x0800,
        DG_PRIM_ONESIDE         = 0x1000,
        DG_PRIM_FREEPACKS       = 0x2000,
};
// clang-format on

enum {
    DG_SCREEN_CHANL,
    DG_BOUND_CHANL,
    DG_TRANS_CHANL,
    DG_SHADE_CHANL,
    DG_PRIM_CHANL,
    DG_DIVIDE_CHANEL,
    DG_SORT_CHANL,
    DG_CHANL_UNIT_MAX
};

/*---------------------------------------------------------------------------*/

static inline void DG_GroupObjs( DG_OBJS *objs, int group_id )
{
    objs->group_id = group_id;
}

#ifndef __LIBDG_DISPLAY_C__
static inline void DG_GroupObjsEx( DG_OBJS *objs )
{
    extern int DG_CurrentGroupID;

    DG_GroupObjs( objs, DG_CurrentGroupID );
}
#endif

static inline void DG_VisibleObjs( DG_OBJS *objs )
{
    objs->flag &= ~DG_FLAG_INVISIBLE;
}

static inline void DG_InvisibleObjs( DG_OBJS *objs )
{
    objs->flag |= DG_FLAG_INVISIBLE;
}

#ifndef __LIBDG_DISPLAY_C__
static inline void DG_SetCurrentGroup( int group_id )
{
    extern int DG_CurrentGroupID;

    DG_CurrentGroupID = group_id;
}
#endif

static inline void DG_UnAmbientObjs( DG_OBJS *objs )
{
    objs->flag &= ~DG_FLAG_AMBIENT;
}

static inline void DG_AmbientObjs( DG_OBJS *objs )
{
    objs->flag |= DG_FLAG_AMBIENT;
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

static inline void DG_RaisePrim( DG_PRIM *prim, int raise )
{
    prim->raise = raise;
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

typedef void (*DG_CHANLFUNC)(DG_CHANL *chanl, int idx);

/* dgd.c */
extern int DG_FrameRate;
extern int DG_HikituriFlag;
extern int DG_HikituriFlagOld;

void DG_ResetSystem( void );
void DG_ResetTexture( void );
void DG_StartDaemon(void);

/* bound.c */
void DG_BoundStart( void );
void DG_BoundChanl( DG_CHANL *chanl, int idx );
void DG_BoundEnd( void );

/* chanl.c */
#ifndef __LIBDG_CHANL_C__
extern short DG_ChanlTimeMax;
extern short DG_EndTime;
#endif

void DG_InitChanlSystem( int shift );
void DG_DrawChanlSystem( int which );
void DG_ClearChanlSystem( int which );
void DG_SortChanlSystem( int which );
void DG_SetDrawEnv( int chanl, DRAWENV *env );
int  DG_QueueObjs( DG_OBJS *objs );
void DG_DequeueObjs( DG_OBJS *objs );
int  DG_QueuePrim( DG_PRIM *prim );
void DG_DequeuePrim( DG_PRIM *prim );
void DG_SetDefDrawEnv( DRAWENV *env, int x, int y, int w, int h );
void DG_StopMainChanlSystem( void );
void DG_RestartMainChanlSystem( void );
void DG_SetBackGroundColor( int r, int b, int g );
void DG_ClearBackGroundColor( void );
void DG_RestoreBackGroundColor( void );
void DG_SetBackgroundPrim( void *prim );
DG_CHANLFUNC DG_SetChanlSystemUnits( int num, DG_CHANLFUNC addr );

/* frame.c */
extern int DG_UnDrawFrameCount;
#ifndef __LIBDG_DISPLAY_C__
extern int DG_CurrentGroupID;
extern short DG_ClipMin[2];
extern short DG_ClipMax[2];
#endif

void DG_InitDisplay( int x, int y, int w, int h, int shift );
void DG_ChangeReso( int );
void DG_InitFrameSystem( void );
void DG_StartFrame( void );
void DG_EndFrame( void );
void DG_MakeCameraMatrix( DG_CHANL *chanl, SVECTOR *from, SVECTOR *to, int screen );
void DG_AdjustOverscan( MATRIX *matrix );
void DG_Clip( RECT *clip_rect, int dist );
void DG_OffsetDispEnv( int offset );
void DG_ClipDispEnv( int x, int y );
void DG_DisableClipping( void );
void DG_FadeScreen( int amount );
DISPENV *DG_GetDisplayEnv( void );

/* divide.c */
void DG_DivideStart( void );
void DG_DivideChanl( DG_CHANL *chanl, int idx );
void DG_DivideEnd( void );

/* light.c */
extern MATRIX DG_LightMatrix;
extern MATRIX DG_ColorMatrix;

extern SVECTOR DG_Ambient;
extern u_long DG_PacketCode[2];

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
int DG_LoadInitKmd( void *buf, int id );
int DG_LoadInitNar( void *buf, int id );
int DG_LoadInitOar( void *buf, int id );
int DG_LoadInitImg( void *buf, int id );
int DG_LoadInitSgt( void *buf, int id );
int DG_LoadInitLit( void *buf, int id );
int DG_LoadInitPcx( void *buf, int id );
int DG_LoadInitKmdar(void *buf, int id );

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
void     DG_SetJointFrame( DG_OBJS *objs, SVECTOR *rots );
void     DG_SetSlideFrame( DG_OBJS *objs, SVECTOR *movs );

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
extern MATRIX DG_ZeroMatrix;
extern SVECTOR DG_ZeroVector;

void DG_PrimStart( void );
void DG_PrimChanl( DG_CHANL *chanl, int idx );
void DG_PrimEnd( void );
DG_PRIM *DG_MakePrim(int type, int prim_count, int chanl, SVECTOR *pos, RECT *rect);
void DG_FreePrim( DG_PRIM *prim );
void DG_SetFreePrimParam( int psize, int verts, int voffset, int vstep );

/* pshade.c */
int  DG_MakePreshade( DG_OBJS *prim, DG_LIT *light, int numLights );
void DG_FreePreshade( DG_OBJS *prim );

/* pos.c */
void DG_SetPos( MATRIX *world );
void DG_SetPos2( SVECTOR *mov, SVECTOR *rot );
void DG_MovePos( SVECTOR *mov );
void DG_RotatePos( SVECTOR *rot );
void DG_PutObjs( DG_OBJS *objs );
void DG_PutPrim( DG_PRIM *prim );
void DG_PutVector( SVECTOR *from, SVECTOR *to, int n );
void DG_RotVector( SVECTOR *from, SVECTOR *to, int n );
void DG_PersVector( SVECTOR *from, DVECTOR *to, int n );
void DG_PointCheck( SVECTOR *svector, int n_points );
int  DG_PointCheckOne( DVECTOR *line );

/* screen.c */
// void DG_ScreenModelsSingle( DG_OBJS *objs, int n_obj );
// void DG_ScreenModels( DG_OBJS *objs, int n_obj );
// void DG_ApplyMovs( DG_OBJS *objs, int n_obj );
// void DG_ApplyRots( DG_OBJS *objs, int n_obj );
void DG_ScreenChanl( DG_CHANL *chanl, int idx );

/* shade.c */
void DG_ShadeStart( void );
void DG_ShadeChanl(DG_CHANL *chanl, int idx);
void DG_ShadeEnd( void );

/* sort.c */
void DG_SortChanl( DG_CHANL *chanl, int idx );

/* text.c */
void DG_InitTextureSystem( void );
DG_TEX *DG_GetTexture( int id );
void DG_SetTexture( int id, int tp, int abr, RECT *img, RECT *pal, int col );
void DG_GetTextureRect( DG_TEX *tex, RECT *rect );
void DG_GetClutRect( DG_TEX *tex, RECT *rect );
void DG_ClearResidentTexture( void );
void DG_SaveResidentTexture( void );
void DG_ResetResidentTexture( void );

/* trans.c */
void DG_TransStart( void );
void DG_TransChanl( DG_CHANL *chanl, int idx );
void DG_TransEnd( void );

/* palette.c */
void DG_StorePalette2( void );
void DG_StorePaletteEffect( void );
void DG_ResetPaletteEffect( void );
void sub_80079004( unsigned short param_1 );
void sub_800790E8( void );
void sub_8007913C( void );
void DG_SetExtPaletteMakeFunc( void (*param_1)(void), u_short (*param_2)(u_short) );
void DG_ResetExtPaletteMakeFunc(void);
void DG_MakeEffectPalette( unsigned short *param_1, int param_2 );

/*---------------------------------------------------------------------------*/

static inline DG_CHANL *DG_Chanl( int idx )
{
    extern DG_CHANL DG_Chanls[ 3 ];
    return &DG_Chanls[ idx + 1 ];
}

static inline u_long *DG_ChanlOTag(int index)
{
    extern int GV_Clock;
    return DG_Chanl(index)->ot[GV_Clock];
}

static inline void DG_SetPacketTexture( POLY_FT4 *packs, DG_TEX *tex )
{
    int x, y, w, h;
    x = tex->off_x ;
    w = tex->w ;
    y = tex->off_y ;
    h = tex->h ;

    setUVWH( packs, x, y, w, h ) ;
}

static inline void DG_SetPacketTexture4( POLY_FT4 *packs, DG_TEX *tex )
{
    DG_SetPacketTexture( packs, tex ) ;
    packs->tpage = tex->tpage ;
    packs->clut = tex->clut ;
}

/*---------------------------------------------------------------------------*/

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

#endif // __MGS_LIBDG_H__
