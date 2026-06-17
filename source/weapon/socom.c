#include "weapon.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "anime/animconv/anime.h"
#include "game/game.h"
#include "linkvar.h"
#include "okajima/bullet.h"
#include "sound/g_sound.h"
#include "strcode.h"

extern GM_CameraSystemWork GM_Camera;

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL      GV_ACTOR_AFTER

#define SOCOM_MODEL     GV_StrCode("socom")     /* no suppressor */
#define SOCOM_MODEL2    GV_StrCode("socom2")    /* w/ suppressor */
#define LASER_TEXTURE   GV_StrCode("lsight")

#define SEGMENT_ATR     ( HZD_SEG_NO_PLAYER )

#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                        | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

#define MAGAZINE_SIZE   12

typedef struct _Work
{
    GV_ACT         actor;
    OBJECT_NO_ROTS object;
    CONTROL       *root_ctrl;
    OBJECT        *root_obj;
    int            unit;
    u_long        *flags;
    short          side;
    short          supressor;
    DG_PRIM       *laser_prim;
    DG_TEX        *laser_tex;
    SVECTOR        laser_verts[20];
    int            laser_len;
    int            jitter;
    int            time;
    DG_PRIM       *light_prim;
    SVECTOR        light_verts[2];
} Work;

STATIC short word_800AB824 = -215;
STATIC RECT  stru_800AB828 = {0, 0, 2, 2};

STATIC SVECTOR stru_8009F3BC[] = {{20, -370, 60, 0}};
STATIC SVECTOR stru_8009F3C4[2] = {{0, -215, 32, 0}, {0, -10455, 32, 0}};
STATIC SVECTOR stru_8009F3D4[2] = {{0, 600, 32, 0}, {0, -9640, 32, 0}};

/*---------------------------------------------------------------------------*/

static void SocomSetPolyTexture( POLY_FT4 *poly, DG_TEX *laser_tex )
{
    int       i;
    POLY_FT4 *pft4 = poly;

    for ( i = 10; i > 0; i-- )
    {
        setPolyFT4( pft4 );
        setSemiTrans( pft4, 1 );
        setRGB0( pft4, 16, 16, 16 );
        pft4->tpage = laser_tex->tpage;
        pft4->clut = laser_tex->clut;
        pft4++;
    }
}

static void SocomSetPolyUVs( POLY_FT4 *poly, DG_TEX *laser_tex, int a3 )
{
    char offy = laser_tex->off_y + ( a3 & 0x3f );
    char offx = laser_tex->off_x;
    int  i;

    for ( i = 10; i > 0; i-- )
    {
        setUVWH( poly, offx, offy, 8 - 1, 0 );

        // TODO: Fake match/hack no reason to assign these again but no match if we don't
        poly->u3 = offx + 7;
        poly->v3 = offy;

        offx += 8;

        poly++;
    }
}

static void SocomInitVectors( Work *work )
{
    int      i;
    SVECTOR *vp;

    vp = work->laser_verts;
    for ( i = 20; i > 0; i-- )
    {
        vp->vx = 0;
        vp->vy = -215;
        vp->vz = 32;
        ++vp;
    }
}

static void socom_act_helper_8006528C(Work *work)
{
    int primsOrig =  work->laser_len;
    int prims;
    SVECTOR *pVec;
    int iVar3;

    if (!primsOrig)
    {
        primsOrig = 10240;
    }

    if (GM_UnkFlagBE && GM_Camera.first_person)
    {
        primsOrig += 515;
    }

    prims = (primsOrig + 1023) / 1024;

    if (prims > 10)
    {
        prims = 10;
    }

    work->laser_prim->prim_count = prims;

    pVec = work->laser_verts;
    iVar3 = word_800AB824;

    for(--prims; prims >= 0; --prims)
    {
        pVec[0].vy = iVar3;
        iVar3 -= 1024;
        pVec[1].vy = iVar3;
        pVec += 2;
    }

    pVec[-1].vy = word_800AB824 - primsOrig;
}

static void SocomInitLight( TILE *packs )
{
    int i;

    for ( i = 2; i > 0; --i )
    {
        setTile( packs );
        setRGB0( packs, 255, 63, 63 );
        setWH( packs, 2, 2 );
        packs++;
    }
}

static void SocomSetTilesColor( TILE *tile, int color )
{
    tile[ 0 ].r0 = color;
    tile[ 0 ].g0 = color / 4;
    tile[ 0 ].b0 = color / 4;
    tile[ 1 ].r0 = 255;
    tile[ 1 ].g0 = 63;
    tile[ 1 ].b0 = 63;
}

static void socom_act_helper_800653B8( Work *socom )
{
    int local_var = socom->laser_len;

    if ( local_var == 0 )
    {
        socom->light_prim->prim_count = 1;
        ( socom->light_verts[0] ).vy = word_800AB824;
    }
    else
    {
        socom->light_prim->prim_count = 2;
        ( socom->light_verts[1] ).vy = -215 - (short)local_var;
        ( socom->light_verts[0] ).vy = word_800AB824;
    }
}

static int socom_act_helper_80065408( Work *work )
{
    int         bCalcLen;
    MAP        *map;
    int         vecLen;
    SVECTOR     vecs[ 2 ];

    bCalcLen = 0;
    DG_SetPos( &work->root_obj->objs->objs[ work->unit ].world );
    DG_PutVector( stru_8009F3D4, vecs, 2 );
    map = work->root_ctrl->map;
    if ( HZD_OnlineHazardCheck( map->hzd, vecs, &vecs[ 1 ], HZD_CHK_ALL, SEGMENT_ATR ) )
    {
        HZD_GetOnlinePoint( &vecs[ 1 ] );
        bCalcLen = 1;
    }
    if ( GM_OnlineTargetCheck( vecs, &vecs[ 1 ], map->index, &vecs[ 1 ], 1 ) )
    {
        bCalcLen = 1;
    }
    vecLen = 0;
    if ( bCalcLen )
    {
        GV_SubVec3( &vecs[ 1 ], vecs, vecs );
        vecLen = GV_VecLen3( vecs );
        if ( vecLen >= 816 )
        {
            vecLen -= 815;
        }
    }
    return vecLen;
}

/*---------------------------------------------------------------------------*/

static void Act( Work *work )
{
    int color;
    u_long flags;
    MATRIX  MStack48;
    MATRIX *world;
    int mag_size;
    int f108;

    if ( GM_SilencerFlag > 0 )
    {
        GM_WeaponChanged = 1;
        return;
    }

    GM_CurrentMap = work->root_ctrl->map->index;

    DG_GroupObjsEx( work->object.objs );
    DG_GroupPrim( work->laser_prim, DG_CurrentGroupID );

    flags = *work->flags;

    if ( !GM_UnkFlagBE )
    {
        word_800AB824 = -215;

        if ( work->root_obj->objs->flag & DG_FLAG_INVISIBLE )
        {
            DG_InvisiblePrim( work->laser_prim );
            DG_InvisiblePrim( work->light_prim );
            DG_InvisibleObjs( work->object.objs );
        }
        else
        {
            if ( flags & 1 )
            {
                DG_VisiblePrim( work->laser_prim );
                DG_VisiblePrim( work->light_prim );
            }
            else
            {
                DG_InvisiblePrim( work->laser_prim );
                DG_InvisiblePrim( work->light_prim );

            }

            DG_VisibleObjs( work->object.objs );
        }
    }
    else
    {
        word_800AB824 = GM_Camera.first_person ? 300 : -215;

        if ( flags & 1 )
        {
            DG_VisiblePrim( work->laser_prim );
            DG_VisiblePrim( work->light_prim );
        }
        else
        {
            DG_InvisiblePrim( work->laser_prim );
            DG_InvisiblePrim( work->light_prim );
        }

        if ( work->root_obj->objs->flag & DG_FLAG_INVISIBLE )
        {
            DG_InvisibleObjs( work->object.objs );
        }
        else
        {
            DG_VisibleObjs( work->object.objs );
        }
    }

    if ( flags & 1 )
    {
        work->laser_len = socom_act_helper_80065408( work );
        if ( !( GV_Time & 0x3f ) )
        {
            work->jitter = GV_RandU( 2 ) + 1;
        }

        f108 = work->time + work->jitter;
        work->time = f108;

        SocomSetPolyUVs( work->laser_prim->packs[ 0 ], work->laser_tex, f108 );
        SocomSetPolyUVs( work->laser_prim->packs[ 1 ], work->laser_tex, f108 );
        socom_act_helper_8006528C( work );

        color = work->root_obj->objs->objs[ work->unit ].screen.m[2][1] / 16;

        if ( color < 0 )
        {
            color = 0;
        }

        if ( color > 0xff )
        {
            color = 0xff;
        }

        SocomSetTilesColor( work->light_prim->packs[ 0 ], color );
        SocomSetTilesColor( work->light_prim->packs[ 1 ], color );
        socom_act_helper_800653B8( work );
    }

    mag_size = GM_Magazine;

    if ( ( mag_size == 0 ) && ( flags & 2 ) )
    {
        GM_SeSet( &work->root_ctrl->mov, SE_KARASHT );
        GM_SetNoise(5, 2, &work->root_ctrl->mov);
    }
    else if ( ( mag_size > 0 ) && ( flags & 2 ) )
    {
        world = &work->object.objs->world;

        DG_SetPos( world );
        DG_MovePos( &stru_8009F3BC[0] );
        ReadRotMatrix( &MStack48 );
        NewBullet( &MStack48, work->side, 0, 1 );

        if ( work->supressor == 0 )
        {
            GM_SeSet( &work->root_ctrl->mov, SE_SOCOM_SHOT );
            GM_SetNoise(200, 2, &work->root_ctrl->mov);
            NewAnime_8005D988( world, &MStack48, 0 );
        }
        else
        {
            GM_SeSet( &work->root_ctrl->mov, SE_SOCOM_SUPPRESSED );
            GM_SetNoise(5, 2, &work->root_ctrl->mov);
            NewAnime_8005D988( world, &MStack48, 1 );
        }

        GM_Magazine = --mag_size;
        GM_MagazineMax = MAGAZINE_SIZE;
        --GM_Weapons[ WP_Socom ];
    }
}

static void Die( Work *work )
{
    GM_FreeObject( (OBJECT *)&work->object );
    GM_FreePrim( work->laser_prim );
    GM_FreePrim( work->light_prim );
}

static int GetResources( Work *actor, OBJECT *root_obj, int unit )
{
    DG_TEX         *laser_tex;
    DG_PRIM        *newprim;
    DG_PRIM        *prim;
    OBJECT_NO_ROTS *obj;

    obj = &actor->object;
    if ( GM_SilencerFlag < 0 )
    {
        GM_InitObjectNoRots(obj, SOCOM_MODEL, BODY_FLAG, 0);
        actor->supressor = 0;
    }
    else
    {
        GM_InitObjectNoRots(obj, SOCOM_MODEL2, BODY_FLAG, 0);
        actor->supressor = 1;
        GM_SilencerFlag = 0;
        if ( GM_CurrentItemId == IT_Suppressor )
        {
            GM_CurrentItemId = IT_None;
        }
    }
    if ( obj->objs )
    {
        GM_ConfigObjectRoot( (OBJECT *)obj, root_obj, unit );
        prim = GM_MakePrim( DG_PRIM_LINE_FT2, 10, actor->laser_verts, NULL );
        newprim = ( actor->laser_prim = prim );
        prim = newprim;
        if ( newprim )
        {
            laser_tex = DG_GetTexture( LASER_TEXTURE );
            actor->laser_tex = laser_tex;
            if ( laser_tex )
            {
                SocomSetPolyTexture( newprim->packs[ 0 ], laser_tex );
                SocomSetPolyTexture( newprim->packs[ 1 ], laser_tex );
                SocomInitVectors( actor );
                newprim->root = &root_obj->objs->objs[ unit ].world;
                actor->light_prim = prim = GM_MakePrim( DG_PRIM_RECTANGLE | DG_PRIM_TILE, 2, actor->light_verts, &stru_800AB828 );
                actor->light_verts[0] = actor->light_verts[1] = stru_8009F3C4[0];
                if ( prim )
                {
                    SocomInitLight( ( TILE* )prim->packs[ 0 ] );
                    SocomInitLight( ( TILE* )prim->packs[ 1 ] );
                    prim->raise = 0x1F4;
                    DG_InvisiblePrim( prim );
                    prim->root = &root_obj->objs->objs[ unit ].world;
                    return 0;
                }
            }
        }
    }
    return -1;
}

/*---------------------------------------------------------------------------*/

void *NewSOCOM( CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *flags, int side )
{
    Work *work;
    int mag_size;
    int ammo;

    work = GV_NewActor( EXEC_LEVEL, sizeof( Work ) );
    if ( work )
    {
        GV_SetNamedActor( &work->actor, Act, Die, "socom.c" );
        if ( GetResources( work, root_obj, unit ) < 0 )
        {
            GV_DestroyActor( &work->actor );
            return NULL;
        }

        work->root_ctrl = root_ctrl;
        work->root_obj = root_obj;
        work->unit = unit;
        work->flags = flags;
        work->side = side;
        work->time = 0;
        work->jitter = 1;
        work->laser_len = 1000;
    }

    mag_size = MAGAZINE_SIZE;
    if ( GM_Magazine )
    {
        mag_size++;
    }
    ammo = GM_Weapons[ WP_Socom ];
    if ( mag_size > 0 && mag_size < ammo )
    {
        ammo = mag_size;
    }

    GM_MagazineMax = mag_size;
    GM_Magazine = ammo;

    return (void *)work;
}
