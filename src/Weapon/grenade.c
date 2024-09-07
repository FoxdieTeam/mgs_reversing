#include "Bullet/blast.h"
#include "Bullet/tenage.h"
#include "Game/object.h"
#include "Game/target.h"
#include "Game/linkvarbuf.h"
#include "Okajima/chafgrnd.h"
#include "Okajima/stngrnd.h"
#include "grenade.h"
#include "libdg/libdg.h"
#include "Game/map.h"
#include "strcode.h"

#include <libpad.h>

// grenade/stun/chaff (in hands)

extern short         GM_Magazine_800AB9EC;
extern short         GM_MagazineMax_800ABA2C;
extern SVECTOR       DG_ZeroVector_800AB39C;
extern SVECTOR       GM_PlayerPosition_800ABA10;
extern int           DG_CurrentGroupID_800AB968;
extern Blast_Data    blast_data_8009F4B8[8];
extern TBombFunction GM_lpfnBombHoming_800AB3E8;
extern int           GM_PlayerStatus_800ABA50;

//------------------------------------------------------------------------------

unsigned short grenade_model_8009F3E4[] = {KMD_GRENADE, KMD_CAN_GREN, KMD_CAN_GREN, KMD_C4_BOMB};

SVECTOR dword_8009F3EC[] = {
    {0, 128, 150, 0},
    {0, 50, 200, 0},
    {0, 32, 32, 0},
    {0, 280, 80, 0}
};

//------------------------------------------------------------------------------


void grenade_800663A0( void )
{
    TARGET target;
    SVECTOR   pos;

    pos.vz = 250;
    pos.vy = 250;
    pos.vx = 250;
    GM_SetTarget_8002DC74( &target, 4, NO_SIDE, &pos );
    GM_Target_8002DCCC( &target, 3, 1, TARGET_C4, -1, (SVECTOR *)&DG_ZeroVector_800AB39C );
    GM_MoveTarget_8002D500( &target, &GM_PlayerPosition_800ABA10 );
    GM_PowerTarget_8002D7DC( &target );
}

void grenade_act_8006641C( GrenadeWork *actor )
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
    GV_ACT       *tenage;

    GM_CurrentMap_800AB9B0 = actor->f20_ctrl->map->index;
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
                NewBlast_8006DFDC( world, &blast_data_8009F4B8[0] );
                break;
            case GRD_STUN:
                NewStunGrenade_80074B5C( world );
                grenade_800663A0();
                break;
            case GRD_CHAFF:
                NewChafgrnd_80077264( world );
                grenade_800663A0();
                break;
            default:
            }
            actor->f5c_timer = 168;
            if ( grenade_type != GRD_TBOMB )
            {
                --GM_CurrentWeapon;
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
            ammo = GM_CurrentWeapon;
        }
        if ( ( ammo > 0 ) && ( flags & ( 2 | 4 | 8 ) ) )
        {
            if ( actor->f64_has_exploded && ( flags & 8 ) )
            {
                actor->f64_has_exploded = FALSE;
                return;
            }
            ctrl_pos = &actor->f20_ctrl->mov;
            DG_SetPos2( &ctrl_pos[ 0 ], &ctrl_pos[ 1 ] );
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
                svector = dword_8009F3EC + 1;
            }
            if ( ( svector == dword_8009F3EC ) && GM_lpfnBombHoming_800AB3E8 )
            {
                svector += 3;
            }
            DG_RotVector( svector, &tenage_vec2, 1 );
            if ( GM_PlayerStatus_800ABA50 & PLAYER_MOVING )
            {
                tenage_vec2.vx += ctrl_pos->vx - actor->f54_pos.vx;
                tenage_vec2.vz += ctrl_pos->vz - actor->f54_pos.vz;
            }
            INIT_VEC( tenage_vec1, world->t[ 0 ], world->t[ 1 ], world->t[ 2 ] );
            tenage = NewTenage_8006A010( &tenage_vec1,
                                         &tenage_vec2,
                                         actor->f5c_timer,
                                         actor->f60_grenade_type,
                                         (int)grenade_model_8009F3E4[ actor->f60_grenade_type ] );
            if ( tenage )
            {
                DG_InvisibleObjs( actor->f28_obj.objs );
                actor->f5c_timer = 168;
                if ( grenade_type != GRD_TBOMB )
                {
                    GM_CurrentWeapon = --ammo;
                }
            }
        }
    }
    else if ( ( grenade_type == GRD_TBOMB ) || ( GM_CurrentWeapon > 0 ) )
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
    actor->f54_pos = actor->f20_ctrl->mov;
}

void grenade_kill_80066894( GrenadeWork *grenade )
{
    GM_FreeObject_80034BF8( (OBJECT *)&grenade->f28_obj );
}

int grenade_loader_800668B4( GrenadeWork *actor_grenade,
                             OBJECT        *parent_obj,
                             int            num_parent,
                             int            grd_type )
{
    OBJECT_NO_ROTS *obj;

    obj = &actor_grenade->f28_obj;
    GM_InitObjectNoRots_800349B0( obj, grenade_model_8009F3E4[ grd_type ], WEAPON_FLAG, 0 );

    if ( !obj->objs )
        return -1;

    GM_ConfigObjectRoot_80034C5C( (OBJECT *)obj, parent_obj, num_parent );
    return 0;
}

GV_ACT *grenade_init_80066944(
    CONTROL *ctrl, OBJECT *parent_obj, int num_parent, int *flags, int unused, int grd_type )
{
    GrenadeWork *actor_grenade;

    actor_grenade = (GrenadeWork *)GV_NewActor( 6, sizeof( GrenadeWork ) );
    if ( actor_grenade )
    {
        GV_SetNamedActor( &actor_grenade->actor,
                          (TActorFunction)&grenade_act_8006641C,
                          (TActorFunction)&grenade_kill_80066894,
                          "grenade.c");
        if ( grenade_loader_800668B4( actor_grenade, parent_obj, num_parent, grd_type ) < 0 )
        {
            GV_DestroyActor( &actor_grenade->actor );
            return 0;
        }

        actor_grenade->f20_ctrl = ctrl;
        actor_grenade->f24_parent_obj = parent_obj;
        actor_grenade->f4c_map_id = num_parent;
        actor_grenade->f50_flags = flags;
        actor_grenade->f5c_timer = 120;
        actor_grenade->f60_grenade_type = grd_type;
        actor_grenade->f64_has_exploded = FALSE;
        actor_grenade->f54_pos = ctrl->mov;
    }

    GM_MagazineMax_800ABA2C = 0;
    GM_Magazine_800AB9EC = 0;

    return &actor_grenade->actor;
}

GV_ACT *NewGrenade_80066A4C( CONTROL *ctrl, OBJECT *parent_obj, int num_parent, unsigned int *flags, int unused )
{
    return grenade_init_80066944( ctrl, parent_obj, num_parent, flags, unused, GRD_GRENADE );
}

GV_ACT *NewStanGrenade_80066A74( CONTROL *ctrl, OBJECT *parent_obj, int num_parent, unsigned int *flags, int unused )
{
    return grenade_init_80066944( ctrl, parent_obj, num_parent, flags, unused, GRD_STUN );
}

GV_ACT *NewChaffGrenade_80066AA0( CONTROL *ctrl, OBJECT *parent_obj, int num_parent, unsigned int *flags, int unused )
{
    return grenade_init_80066944( ctrl, parent_obj, num_parent, flags, unused, GRD_CHAFF );
}

GV_ACT *NewTimerBomb_80066ACC( CONTROL *ctrl, OBJECT *parent_obj, int num_parent, unsigned int *flags, int unused )
{
    return grenade_init_80066944( ctrl, parent_obj, num_parent, flags, unused, GRD_TBOMB );
}
