#include "game/game.h"

/*---------------------------------------------------------------------------*/

typedef struct _Work {
    GV_ACT   actor;
    int      map;
    SVECTOR  verts_r[ 4 ];
    SVECTOR  verts_l[ 4 ];
    char     unused[ 62 ];
    DG_PRIM *prim_r;
    DG_PRIM *prim_l;
    int      time;
    MATRIX  *root;
    int     *enable;
} Work;

SVECTOR SECTION(".bss") s12c_800DA418;
int SECTION(".bss") s12c_800DA420;
int SECTION(".bss") s12c_dword_800DA424;

void WolfEye_800D3518()
{
    s12c_800DA418 = DG_ZeroVector;
    s12c_800DA420 = 0;
}

void WolfEye_800D3554()
{
}

/*---------------------------------------------------------------------------*/

static void InitPacks( POLY_FT4 *packs, int n_packs, DG_TEX *tex )
{
    while ( --n_packs >= 0 )
    {
        setPolyFT4( packs );
        setSemiTrans( packs, 1 );
        setRGB0( packs, 255, 0, 0 );
        DG_SetPacketTexture4( packs, tex );
        packs->tpage |= ( 1 << 5 );
        packs++;
    }
}

static void Act( Work *work )
{
    GM_SetCurrentMap( work->map );

    if ( --work->time < 0 )
    {
        work->time = GV_RandU( 128 ) + 10;
    }

    if ( *work->enable == 0 || work->time < 5 )
    {
        DG_InvisiblePrim( work->prim_r );
        DG_InvisiblePrim( work->prim_l );
    }
    else
    {
        DG_VisiblePrim( work->prim_r );
        DG_VisiblePrim( work->prim_l );
    }
}

static void Die( Work *work )
{
    GM_FreePrim( work->prim_r );
    GM_FreePrim( work->prim_l );
}

static int GetResources( Work *work, MATRIX *root, int *enable )
{
    DG_TEX *tex;
    DG_PRIM *prim;

    work->root = root;
    work->map = GM_CurrentMap;

    tex = DG_GetTexture( GV_StrCode( "wolf_eye_r" ) );
    work->prim_r = prim = GM_MakePrim( DG_PRIM_ONESIDE | DG_PRIM_POLY_FT4, 1, work->verts_r, NULL );
    if ( prim == NULL ) return -1;
    DG_RaisePrim( prim, 300 );
    prim->root = root;

    InitPacks( prim->packs[ 0 ], 1, tex );
    InitPacks( prim->packs[ 1 ], 1, tex );

    tex = DG_GetTexture( GV_StrCode( "wolf_eye_l" ) );
    work->prim_l = prim = GM_MakePrim( DG_PRIM_ONESIDE | DG_PRIM_POLY_FT4, 1, work->verts_l, NULL );
    if ( prim == NULL ) return -1;
    DG_RaisePrim( prim, 300 );
    prim->root = root;

    InitPacks( prim->packs[ 0 ], 1, tex );
    InitPacks( prim->packs[ 1 ], 1, tex );

    work->verts_r[ 0 ].vx = -55;
    work->verts_r[ 0 ].vy = 50;
    work->verts_r[ 0 ].vz = 160;
    work->verts_r[ 1 ].vx = -30;
    work->verts_r[ 1 ].vy = 45;
    work->verts_r[ 1 ].vz = 170;
    work->verts_r[ 2 ].vx = -55;
    work->verts_r[ 2 ].vy = 10;
    work->verts_r[ 2 ].vz = 160;
    work->verts_r[ 3 ].vx = -30;
    work->verts_r[ 3 ].vy = 5;
    work->verts_r[ 3 ].vz = 170;

    work->verts_l[ 0 ].vx = 30;
    work->verts_l[ 0 ].vy = 45;
    work->verts_l[ 0 ].vz = 170;
    work->verts_l[ 1 ].vx = 55;
    work->verts_l[ 1 ].vy = 50;
    work->verts_l[ 1 ].vz = 160;
    work->verts_l[ 2 ].vx = 30;
    work->verts_l[ 2 ].vy = 5;
    work->verts_l[ 2 ].vz = 170;
    work->verts_l[ 3 ].vx = 55;
    work->verts_l[ 3 ].vy = 10;
    work->verts_l[ 3 ].vz = 160;

    work->enable = enable;
    work->time = 0;
    return 0;
}

void *NewWolfEye( MATRIX *root, int *enable )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_USER, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "wolf_eye.c" );
        if ( GetResources( work, root, enable ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
    }
    return (void *)work;
}
