#include "weapon.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "anime/animconv/anime.h"
#include "game/camera.h"
#include "game/game.h"
#include "game/object.h"
#include "game/target.h"
#include "linkvar.h"
#include "game/map.h"
#include "okajima/bullet.h"
#include "sd/g_sound.h"
#include "strcode.h"

extern GM_CAMERA GM_Camera;
extern int     DG_CurrentGroupID;

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL      GV_ACTOR_AFTER

#define SOCOM_MODEL     GV_StrCode("socom")
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
    CONTROL       *control;
    OBJECT        *parent;
    int            num_parent;
    int           *flags;
    short          bullet_type;
    short          field_56;
    DG_PRIM       *prim1;
    DG_TEX        *tex;
    SVECTOR        vertices[20]; // 2x10
    int            field_100;
    int            random;
    int            field_108;
    DG_PRIM       *prim2;
    SVECTOR        field_110[2];
} Work;

STATIC short word_800AB824 = -215;
STATIC RECT  stru_800AB828 = {0, 0, 2, 2};

STATIC SVECTOR stru_8009F3BC[] = {{20, -370, 60, 0}};
STATIC SVECTOR stru_8009F3C4[2] = {{0, -215, 32, 0}, {0, -10455, 32, 0}};
STATIC SVECTOR stru_8009F3D4[2] = {{0, 600, 32, 0}, {0, -9640, 32, 0}};

/*---------------------------------------------------------------------------*/

static void SocomSetPolyTexture( POLY_FT4 *poly, DG_TEX *tex )
{
    int       i;
    POLY_FT4 *pft4 = poly;

    for ( i = 10; i > 0; i-- )
    {
        setPolyFT4( pft4 );
        setSemiTrans( pft4, 1 );
        setRGB0( pft4, 16, 16, 16 );
        pft4->tpage = tex->tpage;
        pft4->clut = tex->clut;
        pft4++;
    }
}

static void SocomSetPolyUVs( POLY_FT4 *poly, DG_TEX *tex, int a3 )
{
    char offy = tex->off_y + ( a3 & 0x3f );
    char offx = tex->off_x;
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

    vp = work->vertices;
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
    int primsOrig =  work->field_100;
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

    work->prim1->n_prims = prims;

    pVec = work->vertices;
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
    int local_var = socom->field_100;

    if ( local_var == 0 )
    {
        socom->prim2->n_prims = 1;
        ( socom->field_110[0] ).vy = word_800AB824;
    }
    else
    {
        socom->prim2->n_prims = 2;
        ( socom->field_110[1] ).vy = -215 - (short)local_var;
        ( socom->field_110[0] ).vy = word_800AB824;
    }
}

static int socom_act_helper_80065408( Work *work )
{
    int         bCalcLen;
    MAP        *map;
    int         vecLen;
    SVECTOR     vecs[ 2 ];

    bCalcLen = 0;
    DG_SetPos( &work->parent->objs->objs[ work->num_parent ].world );
    DG_PutVector( stru_8009F3D4, vecs, 2 );
    map = work->control->map;
    if ( HZD_LineCheck( map->hzd, vecs, &vecs[ 1 ], HZD_CHECK_ALL, SEGMENT_ATR ) )
    {
        HZD_LineNearVec( &vecs[ 1 ] );
        bCalcLen = 1;
    }
    if ( GM_Target_8002E1B8( vecs, &vecs[ 1 ], map->index, &vecs[ 1 ], 1 ) )
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
    unsigned int flags;
    MATRIX  MStack48;
    MATRIX *world;
    int mag_size;
    int f108;

    if ( GM_SilencerFlag > 0 )
    {
        GM_WeaponChanged = 1;
        return;
    }

    GM_CurrentMap = work->control->map->index;

    DG_GroupObjs( work->object.objs, DG_CurrentGroupID );
    DG_GroupPrim( work->prim1, DG_CurrentGroupID );

    flags = *work->flags;

    if ( !GM_UnkFlagBE )
    {
        word_800AB824 = -215;

        if ( work->parent->objs->flag & DG_FLAG_INVISIBLE )
        {
            DG_InvisiblePrim( work->prim1 );
            DG_InvisiblePrim( work->prim2 );
            DG_InvisibleObjs( work->object.objs );
        }
        else
        {
            if ( flags & 1 )
            {
                DG_VisiblePrim( work->prim1 );
                DG_VisiblePrim( work->prim2 );
            }
            else
            {
                DG_InvisiblePrim( work->prim1 );
                DG_InvisiblePrim( work->prim2 );

            }

            DG_VisibleObjs( work->object.objs );
        }
    }
    else
    {
        word_800AB824 = GM_Camera.first_person ? 300 : -215;

        if ( flags & 1 )
        {
            DG_VisiblePrim( work->prim1 );
            DG_VisiblePrim( work->prim2 );
        }
        else
        {
            DG_InvisiblePrim( work->prim1 );
            DG_InvisiblePrim( work->prim2 );
        }

        if ( work->parent->objs->flag & DG_FLAG_INVISIBLE )
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
        work->field_100 = socom_act_helper_80065408( work );
        if ( !( GV_Time & 0x3f ) )
        {
            work->random = GV_RandU( 2 ) + 1;
        }

        f108 = work->field_108 + work->random;
        work->field_108 = f108;

        SocomSetPolyUVs( &work->prim1->packs[ 0 ]->poly_ft4, work->tex, f108 );
        SocomSetPolyUVs( &work->prim1->packs[ 1 ]->poly_ft4, work->tex, f108 );
        socom_act_helper_8006528C( work );

        color = work->parent->objs->objs[ work->num_parent ].screen.m[2][1] / 16;

        if ( color < 0 )
        {
            color = 0;
        }

        if ( color > 0xff )
        {
            color = 0xff;
        }

        SocomSetTilesColor( &work->prim2->packs[ 0 ]->tiles, color );
        SocomSetTilesColor( &work->prim2->packs[ 1 ]->tiles, color );
        socom_act_helper_800653B8( work );
    }

    mag_size = GM_Magazine;

    if ( ( mag_size == 0 ) && ( flags & 2 ) )
    {
        GM_SeSet( &work->control->mov, SE_KARASHT );
        GM_SetNoise(5, 2, &work->control->mov);
    }
    else if ( ( mag_size > 0 ) && ( flags & 2 ) )
    {
        world = &work->object.objs->world;

        DG_SetPos( world );
        DG_MovePos( &stru_8009F3BC[0] );
        ReadRotMatrix( &MStack48 );
        NewBullet( &MStack48, work->bullet_type, 0, 1 );

        if ( work->field_56 == 0 )
        {
            GM_SeSet( &work->control->mov, SE_SOCOM_SHOT );
            GM_SetNoise(200, 2, &work->control->mov);
            NewAnime_8005D988( world, &MStack48, 0 );
        }
        else
        {
            GM_SeSet( &work->control->mov, SE_SOCOM_SUPPRESSED );
            GM_SetNoise(5, 2, &work->control->mov);
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
    GM_FreePrim( work->prim1 );
    GM_FreePrim( work->prim2 );
}

static int GetResources( Work *actor, OBJECT *parent, int num_parent )
{
    DG_TEX         *tex;
    DG_PRIM        *newprim;
    DG_PRIM        *prim;
    OBJECT_NO_ROTS *obj;

    obj = &actor->object;
    if ( GM_SilencerFlag < 0 )
    {
        GM_InitObjectNoRots(obj, SOCOM_MODEL, BODY_FLAG, 0);
        actor->field_56 = 0;
    }
    else
    {
        GM_InitObjectNoRots(obj, SOCOM_MODEL2, BODY_FLAG, 0);
        actor->field_56 = 1;
        GM_SilencerFlag = 0;
        if ( GM_CurrentItemId == IT_Suppressor )
        {
            GM_CurrentItemId = IT_None;
        }
    }
    if ( obj->objs )
    {
        GM_ConfigObjectRoot( (OBJECT *)obj, parent, num_parent );
        prim = DG_GetPrim( DG_PRIM_LINE_FT2, 10, 0, actor->vertices, NULL );
        newprim = ( actor->prim1 = prim );
        prim = newprim;
        if ( newprim )
        {
            tex = DG_GetTexture( LASER_TEXTURE );
            actor->tex = tex;
            if ( tex )
            {
                SocomSetPolyTexture( &newprim->packs[ 0 ]->poly_ft4, tex );
                SocomSetPolyTexture( &newprim->packs[ 1 ]->poly_ft4, tex );
                SocomInitVectors( actor );
                newprim->root = &parent->objs->objs[ num_parent ].world;
                actor->prim2 = prim = DG_GetPrim(  DG_PRIM_OFFSET | DG_PRIM_TILE, 2, 0, actor->field_110, &stru_800AB828 );
                actor->field_110[0] = actor->field_110[1] = stru_8009F3C4[0];
                if ( prim )
                {
                    SocomInitLight( ( TILE* )&prim->packs[ 0 ]->tiles );
                    SocomInitLight( ( TILE* )&prim->packs[ 1 ]->tiles );
                    prim->field_2E_k500 = 0x1F4;
                    DG_InvisiblePrim( prim );
                    prim->root = &parent->objs->objs[ num_parent ].world;
                    return 0;
                }
            }
        }
    }
    return -1;
}

/*---------------------------------------------------------------------------*/

void *NewSOCOM( CONTROL *control, OBJECT *parent, int num_parent,  unsigned int *flags, int which_side )
{
    Work *work;
    int mag_size;
    int ammo;

    work = GV_NewActor( EXEC_LEVEL, sizeof( Work ) );
    if ( work )
    {
        GV_SetNamedActor( &work->actor, Act, Die, "socom.c" );
        if ( GetResources( work, parent, num_parent ) < 0 )
        {
            GV_DestroyActor( &work->actor );
            return NULL;
        }

        work->control = control;
        work->parent = parent;
        work->num_parent = num_parent;
        work->flags = flags;
        work->bullet_type = which_side;
        work->field_108 = 0;
        work->random = 1;
        work->field_100 = 1000;
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
