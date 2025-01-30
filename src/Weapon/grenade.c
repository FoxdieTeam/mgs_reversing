#include "weapon.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libpad.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Bullet/blast.h"
#include "Bullet/tenage.h"
#include "Game/object.h"
#include "Game/target.h"
#include "Game/linkvarbuf.h"
#include "Okajima/chafgrnd.h"
#include "Okajima/stngrnd.h"
#include "Game/map.h"
#include "strcode.h"

extern short         GM_Magazine_800AB9EC;
extern short         GM_MagazineMax_800ABA2C;
extern SVECTOR       GM_PlayerPosition_800ABA10;
extern int           DG_CurrentGroupID;
extern BLAST_DATA    blast_data_8009F4B8[8];
extern int           GM_PlayerStatus;

/*---------------------------------------------------------------------------*/
// Grenade (frag/stun/chaff)

typedef struct _GrenadeWork
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
} GrenadeWork;

#define EXEC_LEVEL GV_ACTOR_AFTER
#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE | DG_FLAG_ONEPIECE )

unsigned short grenade_model_8009F3E4[] = {
    KMD_GRENADE,    // GV_StrCode("grenade")
    KMD_CAN_GREN,   // GV_StrCode("can_gren")
    KMD_CAN_GREN,   // GV_StrCode("stn_ba")
    KMD_C4_BOMB     // GV_StrCode("c4_bomb")
};

SVECTOR dword_8009F3EC[] = {
    { 0, 128, 150, 0 },
    { 0,  50, 200, 0 },
    { 0,  32,  32, 0 },
    { 0, 280,  80, 0 }
};

/*---------------------------------------------------------------------------*/

STATIC void grenade_800663A0( void )
{
    TARGET target;
    SVECTOR pos;

    pos.vz = 250;
    pos.vy = 250;
    pos.vx = 250;
    GM_SetTarget( &target, 4, NO_SIDE, &pos );
    GM_Target_8002DCCC( &target, 3, 1, TARGET_C4, -1, (SVECTOR *)&DG_ZeroVector );
    GM_MoveTarget( &target, &GM_PlayerPosition_800ABA10 );
    GM_PowerTarget( &target );
}

STATIC void GrenadeAct( GrenadeWork *work )
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
                grenade_800663A0();
                break;
            case GRD_CHAFF:
                NewChaffGrd( world );
                grenade_800663A0();
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

STATIC void GrenadeDie( GrenadeWork *work )
{
    GM_FreeObject( (OBJECT *)&work->object );
}

STATIC int GrenadeGetResources( GrenadeWork *work, OBJECT *parent, int num_parent, int grd_type )
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

STATIC GV_ACT *InitGrenade( CONTROL *control, OBJECT *parent, int num_parent,
                            int *flags, int which_side, int grd_type )
{
    GrenadeWork *work;

    work = (GrenadeWork *)GV_NewActor( EXEC_LEVEL, sizeof( GrenadeWork ) );
    if ( work )
    {
        GV_SetNamedActor( &work->actor,
                          (GV_ACTFUNC)&GrenadeAct,
                          (GV_ACTFUNC)&GrenadeDie,
                          "grenade.c");
        if ( GrenadeGetResources( work, parent, num_parent, grd_type ) < 0 )
        {
            GV_DestroyActor( &work->actor );
            return 0;
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

    GM_MagazineMax_800ABA2C = 0;
    GM_Magazine_800AB9EC = 0;

    return &work->actor;
}

GV_ACT *NewGrenade( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side )
{
    return InitGrenade( control, parent, num_parent, flags, which_side, GRD_GRENADE );
}

GV_ACT *NewStanGrenade( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side )
{
    return InitGrenade( control, parent, num_parent, flags, which_side, GRD_STUN );
}

GV_ACT *NewChaffGrenade( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side )
{
    return InitGrenade( control, parent, num_parent, flags, which_side, GRD_CHAFF );
}

GV_ACT *NewTimerBomb( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side )
{
    return InitGrenade( control, parent, num_parent, flags, which_side, GRD_TBOMB );
}
