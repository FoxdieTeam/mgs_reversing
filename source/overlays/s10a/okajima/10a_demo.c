#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/camera.h"
#include "linkvar.h"
#include "weapon/weapon.h"

// Opening demo of s10a: the camera follows snake (who is looking
// through the sniper rifle) with a shaking motion.
typedef struct _Work
{
    GV_ACT  actor;
    int     name;       /* 0x20 */
    int     map;        /* 0x24 */
    SVECTOR eye;        /* 0x28 */
    SVECTOR target;     /* 0x30 */
    SVECTOR center;     /* 0x38 */
    char    pad40[0x10];
    int     time;       /* 0x50 */
    int     item;       /* 0x54 */
    int     weapon;     /* 0x58 */
    int     proc;       /* 0x5C */
} Work;

void s10a_10a_demo_800D5F78( SVECTOR *vec, SVECTOR *pos, int len )
{
    vec->vx = ( vec->vx * ( len - 1 ) + pos->vx ) / len;
    vec->vy = ( vec->vy * ( len - 1 ) + pos->vy ) / len;
    vec->vz = ( vec->vz * ( len - 1 ) + pos->vz ) / len;
}

void s10a_10a_demo_800D6060( Work *work )
{
    SVECTOR eye;
    SVECTOR center;
    SVECTOR pos;

    GV_PadData[0].status &= ~PAD_UP;
    GV_PadData[0].press = GV_PadData[0].status;
    GV_PadData[1].status &= ~PAD_UP;
    GV_PadData[1].press = GV_PadData[1].status;

    pos.vy = work->center.vy + ( rsin( GV_Time * 64 ) - rsin( GV_Time * 31 ) / 2 - rsin( GV_Time * 180 ) / 2 ) / 32;
    pos.vx = work->center.vx + ( rsin( GV_Time * 23 ) - rsin( GV_Time * 45 ) / 2 - rsin( GV_Time * 139 ) / 2 ) / 32;
    pos.vz = work->center.vz;

    eye = work->eye;
    center.vx = eye.vx + ( pos.vx - eye.vx ) / 8;
    center.vy = eye.vy + ( pos.vy - eye.vy ) / 8;
    center.vz = eye.vz + ( pos.vz - eye.vz ) / 8;

    DG_MakeCameraMatrix( DG_Chanl( 0 ), &eye, &center, 5000 );

    GM_Camera.interp_mode = 0;
    GM_Camera.zoom = 5000;

    gUnkCameraStruct2_800B7868.position = eye;
    gUnkCameraStruct2_800B7868.target = center;
}

void s10a_10a_demo_800D62F0( Work *work )
{
    GM_CurrentMap = work->map;

    if ( ( GV_Time % 60 ) == 0 )
    {
        GM_SeSet2( 0, 63, SE_V_ENE_NOISE);
    }

    if ( work->time == 0 )
    {
        work->item = GM_Item;
        work->weapon = GM_Weapon;

        if ( GM_Item == IT_Scope || GM_Item == IT_Camera || GM_Item == IT_NVG || GM_Item == IT_ThermG )
        {
            GM_Item = IT_None;
        }

        if ( GM_Weapon == WP_Rifle || GM_Weapon == WP_Stinger )
        {
            GM_Weapon = WP_None;
        }

        work->center = GM_PlayerPosition;
        work->center.vy += 10000;
        work->target = work->center;
    }
    else if ( work->time < 20 )
    {
        work->target = GM_PlayerPosition;
        s10a_10a_demo_800D5F78( &work->center, &work->target, 16 );
    }
    else if ( work->time < 100 )
    {
        work->target = GM_PlayerPosition;
        s10a_10a_demo_800D5F78( &work->center, &work->target, 8 );
    }
    else if ( work->time < 190 )
    {
        work->target.vx = 1000;
        work->target.vy = -29000;
        work->target.vz = 20500;
        s10a_10a_demo_800D5F78( &work->center, &work->target, 8 );
    }
    else
    {
        GV_DestroyActor(work);
    }

    s10a_10a_demo_800D6060( work );
    work->time++;
}

void s10a_10a_demo_800D6534( Work *work )
{
    GM_GameStatus &= ~STATE_PADRELEASE;

    if ( work->weapon == WP_Rifle || work->weapon == WP_Stinger )
    {
        GM_Weapon = work->weapon;
    }

    if ( work->item == IT_Scope || work->item == IT_Camera || work->item == IT_NVG || work->item == IT_ThermG )
    {
        GM_Item = work->item;
    }

    GCL_ForceExecProc( work->proc, NULL );
}

int s10a_10a_demo_800D65CC( Work *work, int name, int where )
{
    char *opt;

    work->name = name;
    work->map = where;
    GM_CurrentMap = where;

    opt = GCL_GetOption( 'p' );
    if ( opt )
    {
        work->proc = GCL_StrToInt( opt );
    }

    work->eye.vy = -28000;
    work->time = 0;
    work->eye.vx = 0;
    work->eye.vz = -23000;

    NewRifleSightFast();

    GM_GameStatus |= STATE_PADRELEASE;
    GM_GameStatus |= STATE_RADAR_OFF | STATE_MENU_DISABLE | STATE_LIFE_OFF;
    return 0;
}

void *NewStage10ADemo( int name, int where, int argc, char **argv )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof( Work ) );
    if ( work != NULL )
    {
        GV_SetNamedActor( &work->actor, s10a_10a_demo_800D62F0, s10a_10a_demo_800D6534, "10a_demo.c" );
        if ( s10a_10a_demo_800D65CC( work, name, where ) < 0 )
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return (void *)work;
}
