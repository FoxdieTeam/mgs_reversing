#include "Game/game.h"
#include "Game/object.h"
#include "Game/target.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "map/map.h"
#include "socom.h"
#include "unknown.h"

extern const char      aSocom_0[];
extern const char      aSocom2[];
extern const char      aLsight[];
extern char            aSocomC[]; // = "socom.c"

extern int     dword_800AB824;
int            SECTION( ".sdata" ) dword_800AB824;

extern RECT    stru_800AB828;
extern SVECTOR stru_8009F3C4[ 2 ];
extern SVECTOR stru_8009F3D4[ 2 ];
extern short   d_800AB9EC_mag_size;
extern short   d_800ABA2C_ammo;

//------------------------------------------------------------------------------

void             socom_set_poly_texture_800651B0( POLY_FT4 *a1, DG_TEX *pTexture )
{
	int       i;
	POLY_FT4 *pIter = a1;
	for ( i = 10; i > 0; i-- )
	{
		setPolyFT4( pIter );
		setSemiTrans( pIter, 1 );
		setRGB0( pIter, 16, 16, 16 );
		pIter->tpage = pTexture->field_4_tPage;
		pIter->clut = pTexture->field_6_clut;
		pIter++;
	}
}

void socom_set_poly_uvs_80065200( POLY_FT4 *pIter, DG_TEX *pTexture, char a3 )
{
	char yOff = pTexture->field_9_offy + ( a3 & 63 );
	char xOff = pTexture->field_8_offx;
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

void socom_init_vectors_80065254( Actor_Socom *pActor )
{
	int      i;
	SVECTOR *pIter;
	pIter = pActor->field_60_array;
	for ( i = 20; i > 0; i-- )
	{
		pIter->vx = 0;
		pIter->vy = -215;
		pIter->vz = 32;
		++pIter;
	}
}

#pragma INCLUDE_ASM( "asm/Weapon/socom_act_helper_8006528C.s" ) // 172 bytes

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

void socom_act_helper_800653B8( Actor_Socom *socom )
{
	int local_var = socom->field_100;

	if ( local_var == 0 )
	{
		socom->field_10C_pPrim->n_prims = 1;
		( socom->field_110 ).vy = (short)dword_800AB824;
	}
	else
	{
		socom->field_10C_pPrim->n_prims = 2;
		( socom->field_118 ).vy = -0xd7 - (short)local_var;
		( socom->field_110 ).vy = (short)dword_800AB824;
	}
}

int socom_act_helper_80065408( Actor_Socom *pActor )
{
	int         bCalcLen;
	map_record *field_2C_map;
	int         vecLen;
	SVECTOR     vecs[ 2 ];

	bCalcLen = 0;
	DG_SetPos_8001BC44( &pActor->field_48_parent_object->objs->objs[ pActor->field_4C_obj_idx ].world );
	DG_PutVector_8001BE48( stru_8009F3D4, vecs, 2 );
	field_2C_map = pActor->field_44_pCtrl->field_2C_map;
	if ( sub_80028454( field_2C_map->field_8_hzd, vecs, &vecs[ 1 ], 15, 4 ) )
	{
		sub_80028890( &vecs[ 1 ] );
		bCalcLen = 1;
	}
	if ( GM_Target_8002E1B8( vecs, &vecs[ 1 ], field_2C_map->field_0_map_index_bit, &vecs[ 1 ], 1 ) )
	{
		bCalcLen = 1;
	}
	vecLen = 0;
	if ( bCalcLen )
	{
		GV_SubVec3_80016D40( &vecs[ 1 ], vecs, vecs );
		vecLen = GV_VecLen3_80016D80( vecs );
		if ( vecLen >= 816 )
		{
			vecLen -= 815;
		}
	}
	return vecLen;
}

#pragma INCLUDE_ASM( "asm/Weapon/socom_act_80065518.s" ) // 1404 bytes

extern short gGameState_800B4D98[0x60];
extern short gGcl_gameStateVars_800B44C8[0x60];

void socom_kill_80065A94( Actor_Socom *a1 )
{
	DG_PRIM *field_58_prim;
	DG_PRIM *field_10C_pPrim;

	GM_FreeObject_80034BF8( &a1->field_20 );
	field_58_prim = a1->field_58_prim;
	if ( field_58_prim )
	{
		DG_DequeuePrim_800182E0( (DG_OBJS *)field_58_prim );
		DG_FreePrim_8001BC04( (DG_OBJS *)field_58_prim );
	}

	field_10C_pPrim = a1->field_10C_pPrim;
	if ( field_10C_pPrim )
	{
		DG_DequeuePrim_800182E0( (DG_OBJS *)field_10C_pPrim );
		DG_FreePrim_8001BC04( (DG_OBJS *)field_10C_pPrim );
	}
}

int socom_loader_80065B04( Actor_Socom *actor, OBJECT *arg1, int unit )
{
	DG_TEX  *pTexture;
	DG_PRIM *pNewPrim;
	DG_PRIM *prim;
	OBJECT  *obj;

	obj = &actor->field_20;
	if ( gGameState_800B4D98[GM_ItemSilencer] < 0 )
	{
		GM_InitObjectNoRots_800349B0( (OBJECT_NO_ROTS *)obj,
									GV_StrCode_80016CCC( aSocom_0 ),
									WEAPON_FLAG,
									0 );
		actor->field_56 = 0;
	}
	else
	{
		GM_InitObjectNoRots_800349B0( (OBJECT_NO_ROTS *)obj,
									GV_StrCode_80016CCC( aSocom2 ),
									WEAPON_FLAG,
									0 );
		actor->field_56 = 1;
		gGameState_800B4D98[GM_ItemSilencer] = 0;
		if ( gGameState_800B4D98[GM_CurrentItem] == eSUPPR )
		{
			gGameState_800B4D98[GM_CurrentItem] = ITEM_NONE;
		}
	}
	if ( obj->objs )
	{
		GM_ConfigObjectRoot_80034C5C( obj, arg1, unit );
		prim = DG_GetPrim( 0x15, 0xA, 0, &actor->field_60_array[ 0 ], 0 );
		pNewPrim = ( actor->field_58_prim = prim );
		prim = pNewPrim;
		if ( pNewPrim )
		{
			pTexture = DG_GetTexture_8001D830( GV_StrCode_80016CCC( aLsight ) );
			actor->field_5C_pTexture = pTexture;
			if ( pTexture )
			{
				socom_set_poly_texture_800651B0( &pNewPrim->field_40_pBuffers[ 0 ]->poly_ft4, pTexture );
				socom_set_poly_texture_800651B0( &pNewPrim->field_40_pBuffers[ 1 ]->poly_ft4, pTexture );
				socom_init_vectors_80065254( actor );
				pNewPrim->root = &arg1->objs->objs[ unit ].world;
				actor->field_10C_pPrim = prim = DG_GetPrim( 0x409, 2, 0, &actor->field_110, &stru_800AB828 );
				actor->field_110 = actor->field_118 = stru_8009F3C4[ 0 ];
				if ( prim )
				{
					socom_InitLight_80065338( ( TILE* )&prim->field_40_pBuffers[ 0 ]->tiles );
					socom_InitLight_80065338( ( TILE* )&prim->field_40_pBuffers[ 1 ]->tiles );
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

Actor_Socom *NewSOCOM_80065D74( void *a1, OBJECT *parentObj, int unit, int a4, int a5 )
{
	Actor_Socom *pActor;
	int          mag;
	int          ammo;

	pActor = (Actor_Socom *)GV_NewActor_800150E4( 6, sizeof( Actor_Socom ) );
	if ( pActor )
	{
		GV_SetNamedActor_8001514C( &pActor->field_0_actor,
								   (TActorFunction)socom_act_80065518,
								   (TActorFunction)socom_kill_80065A94,
								   aSocomC );
		if ( socom_loader_80065B04( pActor, parentObj, unit ) < 0 )
		{
			GV_DestroyActor_800151C8( &pActor->field_0_actor );
			return 0;
		}
		pActor->field_44_pCtrl = a1;
		pActor->field_48_parent_object = parentObj;
		pActor->field_4C_obj_idx = unit;
		pActor->field_50_ptr = a4;
		pActor->field_54_bullet_type = a5;
		pActor->field_108 = 0;
		pActor->field_104_rnd = 1;
		pActor->field_100 = 1000;
	}
	mag = 12;
	if ( d_800AB9EC_mag_size )
	{
		mag++;
	}
	ammo = gGameState_800B4D98[ GM_WeaponSocom ];
	if ( mag > 0 && mag < ammo )
	{
		ammo = mag;
	}
	d_800ABA2C_ammo = mag;
	d_800AB9EC_mag_size = ammo;
	return pActor;
}
