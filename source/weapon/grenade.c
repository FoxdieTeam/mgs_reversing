#include "weapon.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libpad.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "bullet/blast.h"
#include "bullet/tenage.h"
#include "game/object.h"
#include "game/target.h"
#include "linkvar.h"
#include "okajima/chafgrnd.h"
#include "okajima/stngrnd.h"
#include "game/map.h"
#include "strcode.h"

extern int           DG_CurrentGroupID;
extern BLAST_DATA    blast_data_8009F4B8[8];

/*---------------------------------------------------------------------------*/
// Grenade (frag/stun/chaff)

#define EXEC_LEVEL      GV_ACTOR_AFTER

#define GRENADE_MODEL   0x3b88  // GV_StrCode("grenade")
#define CANISTER_MODEL  0x7a64  // GV_StrCode("can_gren")
#define C4BOMB_MODEL    0xf83d  // GV_StrCode("c4_bomb")

#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                        | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

typedef struct _Work
{
    GV_ACT         actor;
    CONTROL       *control;
    OBJECT        *parent;
    OBJECT_NO_ROTS object;
    int            num_parent;
    int           *flags;
    SVECTOR        pos;
    int            timer;
    int            grenade_type;
    int            has_exploded;
} Work;

/*---------------------------------------------------------------------------*/

STATIC unsigned short grenade_model_8009F3E4[] = {
    GRENADE_MODEL,      // 0: GRD_GRENADE
    CANISTER_MODEL,     // 1: GRD_STUN
    CANISTER_MODEL,     // 2: GRD_CHAFF
    C4BOMB_MODEL        // 3: GRD_TBOMB
};

STATIC SVECTOR dword_8009F3EC[] = {
    { 0, 128, 150, 0 }, // 0: GRD_GRENADE
    { 0,  50, 200, 0 }, // 1: GRD_STUN
    { 0,  32,  32, 0 }, // 2: GRD_CHAFF
    { 0, 280,  80, 0 }  // 3: GRD_TBOMB
};

/*---------------------------------------------------------------------------*/

static void SetGrenadeTarget( void )
{
    TARGET target;
    SVECTOR pos;

    pos.vz = 250;
    pos.vy = 250;
    pos.vx = 250;
    GM_SetTarget( &target, 4, NO_SIDE, &pos );
    GM_Target_8002DCCC( &target, 3, 1, TARGET_C4, -1, (SVECTOR *)&DG_ZeroVector );
    GM_MoveTarget( &target, &GM_PlayerPosition );
    GM_PowerTarget( &target );
}

static void Act( Work *work )
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

    GM_CurrentMap = work->control->map->index;
    DG_GroupObjs( work->object.objs, DG_CurrentGroupID );
    parent_objs_flag = ( work->parent->objs->flag & 0xFF ) >> 7;

    if ( !( parent_objs_flag ) )
    {
        DG_VisibleObjs( work->object.objs );
    }

    flags = *work->flags;
    grenade_type = work->grenade_type;
    world = &work->parent->objs->objs[ work->num_parent ].world;

    if ( flags & 1 )
    {
        DG_VisibleObjs( work->object.objs );
        if ( --work->timer < 1 )
        {
            switch ( grenade_type )
            {
            case GRD_GRENADE:
            case GRD_TBOMB:
                NewBlast( world, &blast_data_8009F4B8[0] );
                break;
            case GRD_STUN:
                NewStanBlast( world );
                SetGrenadeTarget();
                break;
            case GRD_CHAFF:
                NewChaffGrd( world );
                SetGrenadeTarget();
                break;
            default:
            }
            work->timer = 168;
            if ( grenade_type != GRD_TBOMB )
            {
                --GM_CurrentWeapon;
            }
            work->has_exploded = TRUE;
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
            if ( work->has_exploded && ( flags & 8 ) )
            {
                work->has_exploded = FALSE;
                return;
            }
            ctrl_pos = &work->control->mov;
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
            if ( ( svector == dword_8009F3EC ) && GM_lpfnBombHoming )
            {
                svector += 3;
            }
            DG_RotVector( svector, &tenage_vec2, 1 );
            if ( GM_PlayerStatus & PLAYER_MOVE )
            {
                tenage_vec2.vx += ctrl_pos->vx - work->pos.vx;
                tenage_vec2.vz += ctrl_pos->vz - work->pos.vz;
            }
            INIT_VEC( tenage_vec1, world->t[ 0 ], world->t[ 1 ], world->t[ 2 ] );
            tenage = NewTenage( &tenage_vec1,
                                &tenage_vec2,
                                work->timer,
                                work->grenade_type,
                                (int)grenade_model_8009F3E4[ work->grenade_type ] );
            if ( tenage )
            {
                DG_InvisibleObjs( work->object.objs );
                work->timer = 168;
                if ( grenade_type != GRD_TBOMB )
                {
                    GM_CurrentWeapon = --ammo;
                }
            }
        }
    }
    else if ( ( grenade_type == GRD_TBOMB ) || ( GM_CurrentWeapon > 0 ) )
    {
        if ( work->timer > 120 )
        {
            work->timer--;
            DG_InvisibleObjs( work->object.objs );
        }
        else
        {
            DG_VisibleObjs( work->object.objs );
            work->timer = 120;
        }
    }
    else
    {
        DG_InvisibleObjs( work->object.objs );
        work->timer = 120;
    }
    if ( parent_objs_flag == 1 )
    {
        DG_InvisibleObjs( work->object.objs );
    }
    work->pos = work->control->mov;
}

static void Die( Work *work )
{
    GM_FreeObject( (OBJECT *)&work->object );
}

static int GetResources( Work *work, OBJECT *parent, int num_parent, int grd_type )
{
    OBJECT_NO_ROTS *obj;

    obj = &work->object;
    GM_InitObjectNoRots( obj, grenade_model_8009F3E4[ grd_type ], BODY_FLAG, 0 );

    if ( !obj->objs )
        return -1;

    GM_ConfigObjectRoot( (OBJECT *)obj, parent, num_parent );
    return 0;
}

/*---------------------------------------------------------------------------*/

static void *InitGrenade( CONTROL *control, OBJECT *parent, int num_parent,
                          int *flags, int which_side, int grd_type )
{
    Work *work;

    work = GV_NewActor( EXEC_LEVEL, sizeof( Work ) );
    if ( work )
    {
        GV_SetNamedActor( &work->actor, &Act, &Die, "grenade.c");
        if ( GetResources( work, parent, num_parent, grd_type ) < 0 )
        {
            GV_DestroyActor( &work->actor );
            return NULL;
        }

        work->control = control;
        work->parent = parent;
        work->num_parent = num_parent;
        work->flags = flags;
        work->timer = 120;
        work->grenade_type = grd_type;
        work->has_exploded = FALSE;
        work->pos = control->mov;
    }

    GM_MagazineMax = 0;
    GM_Magazine = 0;

    return (void *)work;
}

void *NewGrenade( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side )
{
    return InitGrenade( control, parent, num_parent, flags, which_side, GRD_GRENADE );
}

void *NewStanGrenade( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side )
{
    return InitGrenade( control, parent, num_parent, flags, which_side, GRD_STUN );
}

void *NewChaffGrenade( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side )
{
    return InitGrenade( control, parent, num_parent, flags, which_side, GRD_CHAFF );
}

void *NewTimerBomb( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side )
{
    return InitGrenade( control, parent, num_parent, flags, which_side, GRD_TBOMB );
}
