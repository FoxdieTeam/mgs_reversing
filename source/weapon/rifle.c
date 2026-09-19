#include "weapon.h"

#include "mgstype.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "okajima/bullet.h"

/*---------------------------------------------------------------------------*/
// PSG1 Rifle

#define BODY_DATA       GV_StrCode( "rifle" )
#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                        | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

#define SEGMENT_ATR     ( HZD_SEG_NO_PLAYER )

#define MAGAZINE_SIZE   5

typedef struct _Work {
    GV_ACT         actor;
    OBJECT_NO_ROTS body;
    CONTROL       *root_ctrl;
    OBJECT        *root_obj;
    int            unit;
    u_long        *flag;
    int            side;
    int            time;
    void          *sight;
} Work;

/*---------------------------------------------------------------------------*/

static SVECTOR ScopePos[ 2 ] = { { 0, 0, 0 }, { 0, 0, 3000 } };
static SVECTOR BulletPos = { 5, 300, 80 };

static int GetZoomLimit( void )
{
    MATRIX world;
    SVECTOR pos[ 2 ];
    MATRIX *eye;
    int hit, length;

    if ( ( GM_GameStatus & STATE_DEMO ) || GM_PlayerControl == NULL )
    {
        eye = &DG_Chanl( 0 )->eye;
    }
    else
    {
        eye = &world;
        world = GM_PlayerBody->objs->world;
        DG_COPY_VEC( (VECTOR *)world.t, &GM_SnakeCamera.position );
    }

    DG_SetPos( eye );
    DG_PutVector( ScopePos, pos, 2 );

    hit = 0;
    if ( HZD_OnlineHazardCheck( GM_PlayerControl->map->hzd, &pos[ 0 ], &pos[ 1 ], HZD_CHK_ALL, SEGMENT_ATR ) )
    {
        HZD_GetOnlinePoint( &pos[ 1 ] );
        hit = 1;
    }

    length = 3000;
    if ( hit )
    {
        GV_SubVec3( &pos[ 1 ], &pos[ 0 ], &pos[ 0 ] );
        length = GV_VecLen3( &pos[ 0 ] );
    }

    if ( length < 1000 ) length = 320;
    return length;
}

/*---------------------------------------------------------------------------*/

static void Act( Work *work )
{
    MATRIX world, pos;
    SVECTOR rot;
    u_long flag;
    int time, limit, bullets;

    GM_SetCurrentMap( work->root_ctrl->map->index );
    DG_GroupObjsEx( work->body.objs );

    if ( !( work->root_obj->objs->flag & DG_FLAG_INVISIBLE ) )
    {
        DG_VisibleObjs( work->body.objs );
        GM_Camera.zoom = 320;
        return;
    }

    DG_InvisibleObjs( work->body.objs );

    flag = *work->flag;

    if ( GM_Camera.first_person == 1 &&
         work->sight == NULL &&
         ( flag & 1 ) &&
         ( work->root_obj->objs->flag & DG_FLAG_INVISIBLE ) )
    {
        work->sight = (void *)NewRifleSight( 1 );
        sd_set_cli( 0x01ffff20, SD_ASYNC );
    }

    if ( flag & 1 )
    {
        time = work->time;
        work->time++;

        if ( time >= 9 )
        {
            limit = GetZoomLimit();
            if ( GM_Camera.zoom < limit )
            {
                GM_Camera.zoom += GM_Camera.zoom / 3;
                if ( GM_Camera.zoom > limit ) GM_Camera.zoom = limit;
            }
            else
            {
                GM_Camera.zoom = GV_NearExp4( GM_Camera.zoom, limit );
            }
        }
    }

    bullets = GM_Magazine;

    if ( bullets == 0 && ( flag & 2 ) )
    {
        GM_SeSet( &work->root_ctrl->mov, SE_KARASHT );
        GM_SetNoise( 5, 2, &work->root_ctrl->mov );
    }
    else if ( bullets > 0 && ( flag & 2 ) )
    {
        rot.vx = work->root_ctrl->rot.vx - 1024;
        rot.vy = work->root_ctrl->rot.vy;
        rot.vz = 0;

        RotMatrixYXZ( &rot, &world );

        DG_SetPos( &work->root_obj->objs->objs[ work->unit ].world );
        DG_MovePos( &BulletPos );

        ReadRotMatrix( &pos );
        DG_COPY_VEC( (VECTOR *)world.t, (VECTOR *)pos.t );

        NewBullet( &world, work->side, 0, 2 );
        GM_SeSet2( 0, 63, SE_PSG1_SHOT );
        GM_SetNoise( 100, 2, &work->root_ctrl->mov );

        bullets--;
        GM_Magazine = bullets;
        GM_Weapons[ WP_Rifle ]--;
    }
}

static void Die( Work *work )
{
    GM_FreeObject( (OBJECT *)&work->body );
    if ( GM_Weapon != WP_Rifle ) GM_Camera.zoom = 320;
    sd_set_cli( 0x01ffff21, SD_ASYNC );
    if ( work->sight != NULL ) GV_DestroyOtherActor( work->sight );
}

static int GetResources( Work *work, OBJECT *root_obj, int unit )
{
    OBJECT_NO_ROTS *body;

    body = &work->body;
    GM_InitObjectNoRots( body, BODY_DATA, BODY_FLAG, 0 );
    if ( body->objs == NULL ) return -1;
    GM_ConfigObjectRoot( (OBJECT *)body, root_obj, unit );

    work->sight = NULL;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewRifle( CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *flag, int side )
{
    Work *work;
    int max, ammo;

    work = GV_NewActor( GV_ACTOR_AFTER, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "rifle.c" );
        if ( GetResources( work, root_obj, unit ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }

        work->root_ctrl = root_ctrl;
        work->root_obj = root_obj;
        work->unit = unit;
        work->flag = flag;
        work->side = side;
        work->time = 0;
    }

    max = GM_Magazine ? ( MAGAZINE_SIZE + 1 ) : MAGAZINE_SIZE;
    ammo = GM_Weapons[ WP_Rifle ];
    if ( max > 0 && ammo > max ) ammo = max;

    GM_MagazineMax = max;
    GM_Magazine = ammo;

    return (void *)work;
}
