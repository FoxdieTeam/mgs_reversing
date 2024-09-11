#include "socom.h"

#include <stddef.h> // for NULL
#include "Anime/animeconv/anime.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/camera.h"
#include "Game/game.h"
#include "Game/object.h"
#include "Game/target.h"
#include "Game/linkvarbuf.h"
#include "Game/map.h"
#include "Okajima/bullet.h"
#include "SD/g_sound.h"
#include "strcode.h"

short word_800AB824 = -215;
RECT  stru_800AB828 = {0, 0, 2, 2};

extern short GM_Magazine_800AB9EC;
extern short GM_MagazineMax_800ABA2C;

//------------------------------------------------------------------------------

SVECTOR stru_8009F3BC[] = {{20, -370, 60, 0}};
SVECTOR stru_8009F3C4[2] = {{0, -215, 32, 0}, {0, -10455, 32, 0}};
SVECTOR stru_8009F3D4[2] = {{0, 600, 32, 0}, {0, -9640, 32, 0}};

//------------------------------------------------------------------------------

void socom_set_poly_texture_800651B0( POLY_FT4 *a1, DG_TEX *pTexture )
{
    int       i;
    POLY_FT4 *pIter = a1;
    for ( i = 10; i > 0; i-- )
    {
        setPolyFT4( pIter );
        setSemiTrans( pIter, 1 );
        setRGB0( pIter, 16, 16, 16 );
        pIter->tpage = pTexture->tpage;
        pIter->clut = pTexture->clut;
        pIter++;
    }
}

void socom_set_poly_uvs_80065200( POLY_FT4 *pIter, DG_TEX *pTexture, int a3 )
{
    char yOff = pTexture->off_y + ( a3 & 63 );
    char xOff = pTexture->off_x;
    int  i; // $t0

    for ( i = 10; i > 0; i-- )
    {
        setUVWH( pIter, xOff, yOff, 8 - 1, 0 );

        // TODO: Fake match/hack no reason to assign these again but no match if we don't
        pIter->u3 = xOff + 7;
        pIter->v3 = yOff;

        xOff += 8;

        pIter++;
    }
}

void socom_init_vectors_80065254( SocomWork *work )
{
    int      i;
    SVECTOR *pIter;
    pIter = work->vertices;
    for ( i = 20; i > 0; i-- )
    {
        pIter->vx = 0;
        pIter->vy = -215;
        pIter->vz = 32;
        ++pIter;
    }
}

extern GM_Camera GM_Camera_800B77E8;

void socom_act_helper_8006528C(SocomWork *work)
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

    work->field_58_prim->n_prims = prims;

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

void socom_InitLight_80065338( TILE *packs )
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

void socom_set_tiles_colour_80065384( TILE *pPrim, int colour )
{
    pPrim[ 0 ].r0 = colour;
    pPrim[ 0 ].g0 = colour / 4;
    pPrim[ 0 ].b0 = colour / 4;
    pPrim[ 1 ].r0 = 255;
    pPrim[ 1 ].g0 = 63;
    pPrim[ 1 ].b0 = 63;
}

void socom_act_helper_800653B8( SocomWork *socom )
{
    int local_var = socom->field_100;

    if ( local_var == 0 )
    {
        socom->field_10C_pPrim->n_prims = 1;
        ( socom->field_110[0] ).vy = word_800AB824;
    }
    else
    {
        socom->field_10C_pPrim->n_prims = 2;
        ( socom->field_110[1] ).vy = -215 - (short)local_var;
        ( socom->field_110[0] ).vy = word_800AB824;
    }
}

int socom_act_helper_80065408( SocomWork *work )
{
    int         bCalcLen;
    MAP *map;
    int         vecLen;
    SVECTOR     vecs[ 2 ];

    bCalcLen = 0;
    DG_SetPos( &work->field_48_parent_object->objs->objs[ work->field_4C_obj_idx ].world );
    DG_PutVector( stru_8009F3D4, vecs, 2 );
    map = work->control->map;
    if ( sub_80028454( map->hzd, vecs, &vecs[ 1 ], 15, 4 ) )
    {
        sub_80028890( &vecs[ 1 ] );
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

extern int     GV_Time;
extern int     DG_CurrentGroupID_800AB968;
extern short   GM_WeaponChanged_800AB9D8;

void socom_act_80065518( SocomWork *a1 )
{
    int colour;
    unsigned int flags;
    MATRIX  MStack48;
    MATRIX *world;
    int magSize;
    int f108;

    if ( GM_SilencerFlag > 0 )
    {
        GM_WeaponChanged_800AB9D8 = 1;
        return;
    }

    GM_CurrentMap_800AB9B0 = a1->control->map->index;

    DG_GroupObjs( a1->field_20.objs, DG_CurrentGroupID_800AB968 );
    DG_GroupPrim( a1->field_58_prim, DG_CurrentGroupID_800AB968 );

    flags = *a1->field_50_ptr;

    if ( !GM_UnkFlagBE )
    {
        word_800AB824 = -215;

        if ( a1->field_48_parent_object->objs->flag & DG_FLAG_INVISIBLE )
        {
            DG_InvisiblePrim( a1->field_58_prim );
            DG_InvisiblePrim( a1->field_10C_pPrim );
            DG_InvisibleObjs( a1->field_20.objs );
        }
        else
        {
            if ( flags & 1 )
            {
                DG_VisiblePrim( a1->field_58_prim );
                DG_VisiblePrim( a1->field_10C_pPrim );
            }
            else
            {
                DG_InvisiblePrim( a1->field_58_prim );
                DG_InvisiblePrim( a1->field_10C_pPrim );

            }

            DG_VisibleObjs( a1->field_20.objs );
        }
    }
    else
    {
        word_800AB824 = GM_Camera_800B77E8.first_person ? 300 : -215;

        if ( flags & 1 )
        {
            DG_VisiblePrim( a1->field_58_prim );
            DG_VisiblePrim( a1->field_10C_pPrim );
        }
        else
        {
            DG_InvisiblePrim( a1->field_58_prim );
            DG_InvisiblePrim( a1->field_10C_pPrim );
        }

        if ( a1->field_48_parent_object->objs->flag & DG_FLAG_INVISIBLE )
        {
            DG_InvisibleObjs( a1->field_20.objs );
        }
        else
        {
            DG_VisibleObjs( a1->field_20.objs );
        }
    }

    if ( flags & 1 )
    {
        a1->field_100 = socom_act_helper_80065408( a1 );
        if ( !( GV_Time & 0x3f ) )
        {
            a1->field_104_rnd = GV_RandU( 2 ) + 1;
        }

        f108 = a1->field_108 + a1->field_104_rnd;
        a1->field_108 = f108;

        socom_set_poly_uvs_80065200( &a1->field_58_prim->packs[ 0 ]->poly_ft4, a1->field_5C_pTexture, f108 );
        socom_set_poly_uvs_80065200( &a1->field_58_prim->packs[ 1 ]->poly_ft4, a1->field_5C_pTexture, f108 );
        socom_act_helper_8006528C( a1 );

        colour = a1->field_48_parent_object->objs->objs[ a1->field_4C_obj_idx ].screen.m[2][1] / 16;

        if ( colour < 0 )
        {
            colour = 0;
        }

        if ( colour > 0xff )
        {
            colour = 0xff;
        }

        socom_set_tiles_colour_80065384( &a1->field_10C_pPrim->packs[ 0 ]->tiles, colour );
        socom_set_tiles_colour_80065384( &a1->field_10C_pPrim->packs[ 1 ]->tiles, colour );
        socom_act_helper_800653B8( a1 );
    }

    magSize = GM_Magazine_800AB9EC;

    if ( ( magSize == 0 ) && ( flags & 2 ) )
    {
        GM_SeSet_80032858( &a1->control->mov, SE_KARASHT );
        GM_SetNoise(5, 2, &a1->control->mov);
    }
    else if ( ( magSize > 0 ) && ( flags & 2 ) )
    {
        world = &a1->field_20.objs->world;

        DG_SetPos( world );
        DG_MovePos( &stru_8009F3BC[0] );
        ReadRotMatrix( &MStack48 );
        bullet_init_80076584( &MStack48, a1->field_54_bullet_type, 0, 1 );

        if ( a1->field_56 == 0 )
        {
            GM_SeSet_80032858( &a1->control->mov, SE_SOCOM_SHOT );
            GM_SetNoise(200, 2, &a1->control->mov);
            NewAnime_8005D988( world, &MStack48, 0 );
        }
        else
        {
            GM_SeSet_80032858( &a1->control->mov, SE_SOCOM_SUPPRESSED );
            GM_SetNoise(5, 2, &a1->control->mov);
            NewAnime_8005D988( world, &MStack48, 1 );
        }

        GM_Magazine_800AB9EC = --magSize;
        GM_MagazineMax_800ABA2C = 12;
        --GM_Weapons[ WEAPON_SOCOM ];
    }
}

void socom_kill_80065A94( SocomWork *a1 )
{
    DG_PRIM *field_58_prim;
    DG_PRIM *field_10C_pPrim;

    GM_FreeObject( (OBJECT *)&a1->field_20 );
    field_58_prim = a1->field_58_prim;
    if ( field_58_prim )
    {
        DG_DequeuePrim( field_58_prim );
        DG_FreePrim( field_58_prim );
    }

    field_10C_pPrim = a1->field_10C_pPrim;
    if ( field_10C_pPrim )
    {
        DG_DequeuePrim( field_10C_pPrim );
        DG_FreePrim( field_10C_pPrim );
    }
}

int socom_loader_80065B04( SocomWork *actor, OBJECT *arg1, int unit )
{
    DG_TEX         *pTexture;
    DG_PRIM        *pNewPrim;
    DG_PRIM        *prim;
    OBJECT_NO_ROTS *obj;

    obj = &actor->field_20;
    if ( GM_SilencerFlag < 0 )
    {
        GM_InitObjectNoRots(obj, GV_StrCode( "socom" ), WEAPON_FLAG, 0);
        actor->field_56 = 0;
    }
    else
    {
        GM_InitObjectNoRots(obj, GV_StrCode( "socom2" ), WEAPON_FLAG, 0);
        actor->field_56 = 1;
        GM_SilencerFlag = 0;
        if ( GM_CurrentItemId == ITEM_SUPPR )
        {
            GM_CurrentItemId = ITEM_NONE;
        }
    }
    if ( obj->objs )
    {
        GM_ConfigObjectRoot( (OBJECT *)obj, arg1, unit );
        prim = DG_GetPrim( DG_PRIM_LINE_FT2, 10, 0, actor->vertices, NULL );
        pNewPrim = ( actor->field_58_prim = prim );
        prim = pNewPrim;
        if ( pNewPrim )
        {
            pTexture = DG_GetTexture( GV_StrCode( "lsight" ) );
            actor->field_5C_pTexture = pTexture;
            if ( pTexture )
            {
                socom_set_poly_texture_800651B0( &pNewPrim->packs[ 0 ]->poly_ft4, pTexture );
                socom_set_poly_texture_800651B0( &pNewPrim->packs[ 1 ]->poly_ft4, pTexture );
                socom_init_vectors_80065254( actor );
                pNewPrim->root = &arg1->objs->objs[ unit ].world;
                actor->field_10C_pPrim = prim = DG_GetPrim(  DG_PRIM_OFFSET | DG_PRIM_TILE, 2, 0, actor->field_110, &stru_800AB828 );
                actor->field_110[0] = actor->field_110[1] = stru_8009F3C4[0];
                if ( prim )
                {
                    socom_InitLight_80065338( ( TILE* )&prim->packs[ 0 ]->tiles );
                    socom_InitLight_80065338( ( TILE* )&prim->packs[ 1 ]->tiles );
                    prim->field_2E_k500 = 0x1F4;
                    DG_InvisiblePrim( prim );
                    prim->root = &arg1->objs->objs[ unit ].world;
                    return 0;
                }
            }
        }
    }
    return -1;
}

GV_ACT *NewSOCOM_80065D74(CONTROL *a1, OBJECT *parentObj, int unit,  unsigned int *a4, int a5 )
{
    SocomWork *work;
    int          mag;
    int          ammo;

    work = (SocomWork *)GV_NewActor( 6, sizeof( SocomWork ) );
    if ( work )
    {
        GV_SetNamedActor( &work->actor,
                          (TActorFunction)socom_act_80065518,
                          (TActorFunction)socom_kill_80065A94,
                          "socom.c" );
        if ( socom_loader_80065B04( work, parentObj, unit ) < 0 )
        {
            GV_DestroyActor( &work->actor );
            return 0;
        }
        work->control = a1;
        work->field_48_parent_object = parentObj;
        work->field_4C_obj_idx = unit;
        work->field_50_ptr = a4;
        work->field_54_bullet_type = a5;
        work->field_108 = 0;
        work->field_104_rnd = 1;
        work->field_100 = 1000;
    }
    mag = 12;
    if ( GM_Magazine_800AB9EC )
    {
        mag++;
    }
    ammo = GM_Weapons[ WEAPON_SOCOM ];
    if ( mag > 0 && mag < ammo )
    {
        ammo = mag;
    }
    GM_MagazineMax_800ABA2C = mag;
    GM_Magazine_800AB9EC = ammo;
    return &work->actor;
}
