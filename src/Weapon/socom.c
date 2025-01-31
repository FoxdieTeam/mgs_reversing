#include "weapon.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Anime/animeconv/anime.h"
#include "Game/camera.h"
#include "Game/game.h"
#include "Game/object.h"
#include "Game/target.h"
#include "Game/linkvarbuf.h"
#include "Game/map.h"
#include "Okajima/bullet.h"
#include "SD/g_sound.h"
#include "strcode.h"

extern short GM_Magazine_800AB9EC;
extern short GM_MagazineMax_800ABA2C;
extern GM_Camera GM_Camera_800B77E8;

extern int     DG_CurrentGroupID;
extern short   GM_WeaponChanged_800AB9D8;

/*---------------------------------------------------------------------------*/

typedef struct _SocomWork
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
} SocomWork;

#define EXEC_LEVEL      GV_ACTOR_AFTER
#define MAGAZINE_SIZE   12
#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE | DG_FLAG_ONEPIECE )

STATIC short word_800AB824 = -215;
STATIC RECT  stru_800AB828 = {0, 0, 2, 2};

SVECTOR stru_8009F3BC[] = {{20, -370, 60, 0}};
SVECTOR stru_8009F3C4[2] = {{0, -215, 32, 0}, {0, -10455, 32, 0}};
SVECTOR stru_8009F3D4[2] = {{0, 600, 32, 0}, {0, -9640, 32, 0}};

/*---------------------------------------------------------------------------*/

STATIC void SocomSetPolyTexture( POLY_FT4 *poly, DG_TEX *tex )
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

STATIC void SocomSetPolyUVs( POLY_FT4 *poly, DG_TEX *tex, int a3 )
{
    char offy = tex->off_y + ( a3 & 0x3f );
    char offx = tex->off_x;
    int  i; // $t0

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

STATIC void SocomInitVectors( SocomWork *work )
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

STATIC void socom_act_helper_8006528C(SocomWork *work)
{
    int primsOrig =  work->field_100;
    int prims;
    SVECTOR *pVec;
    int iVar3;

    if (!primsOrig)
    {
        primsOrig = 10240;
    }

    if (GM_UnkFlagBE && GM_Camera_800B77E8.first_person)
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

STATIC void SocomInitLight( TILE *packs )
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

STATIC void SocomSetTilesColor( TILE *tile, int color )
{
    tile[ 0 ].r0 = color;
    tile[ 0 ].g0 = color / 4;
    tile[ 0 ].b0 = color / 4;
    tile[ 1 ].r0 = 255;
    tile[ 1 ].g0 = 63;
    tile[ 1 ].b0 = 63;
}

STATIC void socom_act_helper_800653B8( SocomWork *socom )
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

STATIC int socom_act_helper_80065408( SocomWork *work )
{
    int         bCalcLen;
    MAP        *map;
    int         vecLen;
    SVECTOR     vecs[ 2 ];

    bCalcLen = 0;
    DG_SetPos( &work->parent->objs->objs[ work->num_parent ].world );
    DG_PutVector( stru_8009F3D4, vecs, 2 );
    map = work->control->map;
    if ( HZD_80028454( map->hzd, vecs, &vecs[ 1 ], 15, 4 ) )
    {
        HZD_GetSpadVector( &vecs[ 1 ] );
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

STATIC void SocomAct( SocomWork *work )
{
    int color;
    unsigned int flags;
    MATRIX  MStack48;
    MATRIX *world;
    int mag_size;
    int f108;

    if ( GM_SilencerFlag > 0 )
    {
        GM_WeaponChanged_800AB9D8 = 1;
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
        word_800AB824 = GM_Camera_800B77E8.first_person ? 300 : -215;

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

    mag_size = GM_Magazine_800AB9EC;

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

        GM_Magazine_800AB9EC = --mag_size;
        GM_MagazineMax_800ABA2C = MAGAZINE_SIZE;
        --GM_Weapons[ WEAPON_SOCOM ];
    }
}

STATIC void SocomDie( SocomWork *work )
{
    DG_PRIM *prim1;
    DG_PRIM *prim2;

    GM_FreeObject( (OBJECT *)&work->object );
    prim1 = work->prim1;
    if ( prim1 )
    {
        DG_DequeuePrim( prim1 );
        DG_FreePrim( prim1 );
    }

    prim2 = work->prim2;
    if ( prim2 )
    {
        DG_DequeuePrim( prim2 );
        DG_FreePrim( prim2 );
    }
}

STATIC int SocomGetResources( SocomWork *actor, OBJECT *parent, int num_parent )
{
    DG_TEX         *tex;
    DG_PRIM        *newprim;
    DG_PRIM        *prim;
    OBJECT_NO_ROTS *obj;

    obj = &actor->object;
    if ( GM_SilencerFlag < 0 )
    {
        GM_InitObjectNoRots(obj, GV_StrCode( "socom" ), BODY_FLAG, 0);
        actor->field_56 = 0;
    }
    else
    {
        GM_InitObjectNoRots(obj, GV_StrCode( "socom2" ), BODY_FLAG, 0);
        actor->field_56 = 1;
        GM_SilencerFlag = 0;
        if ( GM_CurrentItemId == ITEM_SUPPR )
        {
            GM_CurrentItemId = ITEM_NONE;
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
            tex = DG_GetTexture( GV_StrCode( "lsight" ) );
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

GV_ACT *NewSOCOM( CONTROL *control, OBJECT *parent, int num_parent,  unsigned int *flags, int which_side )
{
    SocomWork *work;
    int mag_size;
    int ammo;

    work = (SocomWork *)GV_NewActor( EXEC_LEVEL, sizeof( SocomWork ) );
    if ( work )
    {
        GV_SetNamedActor( &work->actor, SocomAct, SocomDie, "socom.c" );
        if ( SocomGetResources( work, parent, num_parent ) < 0 )
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
    if ( GM_Magazine_800AB9EC )
    {
        mag_size++;
    }
    ammo = GM_Weapons[ WEAPON_SOCOM ];
    if ( mag_size > 0 && mag_size < ammo )
    {
        ammo = mag_size;
    }

    GM_MagazineMax_800ABA2C = mag_size;
    GM_Magazine_800AB9EC = ammo;

    return &work->actor;
}
