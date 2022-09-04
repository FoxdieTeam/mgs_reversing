#include "Bullet/blast.h"
#include "Bullet/tenage.h"
#include "Game/gamestate.h"
#include "Game/object.h"
#include "Game/target.h"
#include "grenade.h"
#include "libdg/libdg.h"
#include "map/map.h"

// grenade/stun/chaff (in hands)

extern const char         aGrenadeC[]; // = "grenade.c"
extern short              d_800AB9EC_mag_size;
extern short              d_800ABA2C_ammo;

extern SVECTOR            DG_ZeroVector_800AB39C;
extern SVECTOR            svector_800ABA10;

extern int                DG_CurrentGroupID_800AB968;
extern GameState gGameState_800B4D98;

extern Blast_Data         dword_8009F4B8;
extern ushort             dword_8009F3E4[];
extern SVECTOR            dword_8009F3EC[];
extern SVECTOR            dword_8009F3F4[];
extern int                GM_lpfnBombHoming_800AB3E8;
extern int                GM_PlayerStatus_800ABA50;

void                      NewChaffGrd_80077264( MATRIX *pMtx );

//------------------------------------------------------------------------------

void grenade_800663A0( void )
{
	GM_Target target;
	SVECTOR   pos;

	pos.vz = 250;
	pos.vy = 250;
	pos.vx = 250;
	GM_SetTarget_8002DC74( &target, 4, 0, &pos );
	GM_Target_8002DCCC( &target, 3, 1, TARGET_C4, -1, (SVECTOR *)&DG_ZeroVector_800AB39C );
	GM_Target_SetVector_8002D500( &target, &svector_800ABA10 );
	sub_8002D7DC( &target );
}

void grenade_act_8006641C( Actor_Grenade *actor )
{
	unsigned int  parent_objs_flag;
	SVECTOR      *svector;
	SVECTOR      *ctrl_pos;
	int           flags;
	int           grenade_type;
	int           ammo;
	MATRIX       *world;
	SVECTOR       tenage_vec1;
	SVECTOR       tenage_vec2;
	Actor_tenage *tenage;

	GM_CurrentMap_800AB9B0 = actor->f20_ctrl->field_2C_map->field_0_map_index_bit;
	DG_GroupObjs( actor->f28_obj.objs, DG_CurrentGroupID_800AB968 );
	parent_objs_flag = ( actor->f24_parent_obj->objs->flag & 0xFF ) >> 7;

	if ( !( parent_objs_flag ) )
	{
		DG_VisibleObjs( actor->f28_obj.objs );
	}

	flags = *actor->f50_flags;
	grenade_type = actor->f60_grenade_type;
	world = &actor->f24_parent_obj->objs->objs[ actor->f4c_map_id ].world;

	if ( flags & 1 )
	{
		DG_VisibleObjs( actor->f28_obj.objs );
		if ( --actor->f5c_timer < 1 )
		{
			switch ( grenade_type )
			{
			case GRD_GRENADE:
			case GRD_TBOMB:
				NewBlast_8006DFDC( world, &dword_8009F4B8 );
				break;
			case GRD_STUN:
				NewStanBlast_80074B5C( world );
				grenade_800663A0();
				break;
			case GRD_CHAFF:
				NewChaffGrd_80077264( world );
				grenade_800663A0();
				break;
			default:
			}
			actor->f5c_timer = 168;
			if ( grenade_type != GRD_TBOMB )
			{
				--*GM_GetCurrentWeapon();
			}
			actor->f64_has_exploded = TRUE;
			flags &= ~( 2 | 4 | 8 );
		}
		if ( grenade_type == GRD_TBOMB )
		{
			ammo = 1;
		}
		else
		{
			ammo = *GM_GetCurrentWeapon();
		}
		if ( ( ammo > 0 ) && ( flags & ( 2 | 4 | 8 ) ) )
		{
			if ( actor->f64_has_exploded && ( flags & 8 ) )
			{
				actor->f64_has_exploded = FALSE;
				return;
			}
			ctrl_pos = &actor->f20_ctrl->field_0_position;
			DG_SetPos2_8001BC8C( &ctrl_pos[ 0 ], &ctrl_pos[ 1 ] );
			if ( !( flags & 4 ) )
			{
				svector = dword_8009F3EC;
				if ( flags & 8 )
				{
					svector += 2;
				}
			}
			else
			{
				svector = dword_8009F3F4;
			}
			if ( ( svector == dword_8009F3EC ) && GM_lpfnBombHoming_800AB3E8 )
			{
				svector += 3;
			}
			DG_RotVector_8001BE98( svector, &tenage_vec2, 1 );
			if ( GM_PlayerStatus_800ABA50 & PLAYER_STATUS_MOVING )
			{
				tenage_vec2.vx += ctrl_pos->vx - actor->f54_pos.vx;
				tenage_vec2.vz += ctrl_pos->vz - actor->f54_pos.vz;
			}
			INIT_VEC( tenage_vec1, world->t[ 0 ], world->t[ 1 ], world->t[ 2 ] );
			tenage = NewTenage_8006A010( &tenage_vec1,
										 &tenage_vec2,
										 actor->f5c_timer,
										 actor->f60_grenade_type,
										 (int)dword_8009F3E4[ actor->f60_grenade_type ] );
			if ( tenage )
			{
				DG_InvisibleObjs( actor->f28_obj.objs );
				actor->f5c_timer = 168;
				if ( grenade_type != GRD_TBOMB )
				{
					*GM_GetCurrentWeapon() = --ammo;
				}
			}
		}
	}
	else if ( ( grenade_type == GRD_TBOMB ) || ( *GM_GetCurrentWeapon() > 0 ) )
	{
		if ( actor->f5c_timer > 120 )
		{
			actor->f5c_timer--;
			DG_InvisibleObjs( actor->f28_obj.objs );
		}
		else
		{
			DG_VisibleObjs( actor->f28_obj.objs );
			actor->f5c_timer = 120;
		}
	}
	else
	{
		DG_InvisibleObjs( actor->f28_obj.objs );
		actor->f5c_timer = 120;
	}
	if ( parent_objs_flag == 1 )
	{
		DG_InvisibleObjs( actor->f28_obj.objs );
	}
	actor->f54_pos = actor->f20_ctrl->field_0_position;
}

void grenade_kill_80066894( Actor_Grenade *grenade )
{
	GM_FreeObject_80034BF8( &grenade->f28_obj );
}

int grenade_loader_800668B4( Actor_Grenade *actor_grenade,
							 OBJECT        *parent_obj,
							 int            num_parent,
							 int            grd_type )
{
	OBJECT *obj;

	obj = &actor_grenade->f28_obj;
	GM_InitObjectNoRots_800349B0( (OBJECT_NO_ROTS *)obj, dword_8009F3E4[ grd_type ], WEAPON_FLAG, 0 );

	if ( !obj->objs )
		return -1;

	GM_ConfigObjectRoot_80034C5C( obj, parent_obj, num_parent );
	return 0;
}

Actor_Grenade *grenade_init_80066944(
	GM_Control *ctrl, OBJECT *parent_obj, int num_parent, int *flags, int unused, int grd_type )
{
	Actor_Grenade *actor_grenade;

	actor_grenade = (Actor_Grenade *)GV_NewActor_800150E4( 6, sizeof( Actor_Grenade ) );
	if ( actor_grenade )
	{
		GV_SetNamedActor_8001514C( (Actor *)actor_grenade,
								   (TActorFunction)&grenade_act_8006641C,
								   (TActorFunction)&grenade_kill_80066894,
								   aGrenadeC );
		if ( grenade_loader_800668B4( actor_grenade, parent_obj, num_parent, grd_type ) < 0 )
		{
			GV_DestroyActor_800151C8( (Actor *)actor_grenade );
			return 0;
		}

		actor_grenade->f20_ctrl = ctrl;
		actor_grenade->f24_parent_obj = parent_obj;
		actor_grenade->f4c_map_id = num_parent;
		actor_grenade->f50_flags = flags;
		actor_grenade->f5c_timer = 120;
		actor_grenade->f60_grenade_type = grd_type;
		actor_grenade->f64_has_exploded = FALSE;
		actor_grenade->f54_pos = ctrl->field_0_position;
	}

	d_800ABA2C_ammo = 0;
	d_800AB9EC_mag_size = 0;

	return actor_grenade;
}

<<<<<<< HEAD
Actor_Grenade *grenade_create_80066A4C( GM_Control *ctrl, OBJECT *parent_obj, int num_parent, int *flags, int unused )
{
	return grenade_init_80066944( ctrl, parent_obj, num_parent, flags, unused, GRD_GRENADE );
}

Actor_Grenade *NewStanGrenade_80066A74( GM_Control *ctrl, OBJECT *parent_obj, int num_parent, int *flags, int unused )
{
	return grenade_init_80066944( ctrl, parent_obj, num_parent, flags, unused, GRD_STUN );
}

Actor_Grenade *NewChaffGrenade_80066AA0( GM_Control *ctrl, OBJECT *parent_obj, int num_parent, int *flags, int unused )
{
	return grenade_init_80066944( ctrl, parent_obj, num_parent, flags, unused, GRD_CHAFF );
}

Actor_Grenade *NewTimerBomb_80066ACC( GM_Control *ctrl, OBJECT *parent_obj, int num_parent, int *flags, int unused )
{
	return grenade_init_80066944( ctrl, parent_obj, num_parent, flags, unused, GRD_TBOMB );
=======
Actor_Grenade *grenade_create_80066A4C( GM_Control *ctrl, OBJECT *a2, int num_parent, int *flags, int unused )
{
	return grenade_init_80066944( ctrl, a2, num_parent, flags, unused, GRD_GRENADE );
}

Actor_Grenade *NewStanGrenade_80066A74( GM_Control *ctrl, OBJECT *obj, int num_parent, int *flags, int unused )
{
	return grenade_init_80066944( ctrl, obj, num_parent, flags, unused, GRD_STUN );
}

Actor_Grenade *NewChaffGrenade_80066AA0( GM_Control *ctrl, OBJECT *a2, int num_parent, int *flags, int unused )
{
	return grenade_init_80066944( ctrl, a2, num_parent, flags, unused, GRD_CHAFF );
}

Actor_Grenade *NewTimerBomb_80066ACC( GM_Control *ctrl, OBJECT *a2, int num_parent, int *flags, int unused )
{
	return grenade_init_80066944( ctrl, a2, num_parent, flags, unused, GRD_TBOMB );
>>>>>>> 5327b862 (some norm and renames)
}
