#include <stdio.h>
#include "common.h"
#include "mts/mts.h" // for fprintf
#include "chara/snake/shadow.h"
#include "libgv/libgv.h"
#include "libhzd/libhzd.h"
#include "Game/camera.h"
#include "Game/game.h"

#include "Game/linkvarbuf.h"
#include "strcode.h"

#include "meryl72.h"

extern SVECTOR          DG_ZeroVector;
extern int              GM_CurrentMap_800AB9B0;
extern int              GM_PlayerAddress_800AB9F0;
extern int              GM_PlayerMap_800ABA0C;
extern SVECTOR          GM_PlayerPosition_800ABA10;
extern GM_Camera        GM_Camera_800B77E8;
extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;

extern GM_Camera meryl72_camera_800D5278;
extern SVECTOR   meryl72_800D52F8;

extern void GM_ConfigControlRadarparam(CONTROL *, u_short, u_short, u_short, u_short);

void s07c_meryl72_unk1_800CBC44( Meryl72Work * );
void s07c_meryl72_unk1_800CBCD8( Meryl72Work * );

void s07c_meryl72_unk2_800D0220( void );
void s07c_meryl72_unk2_800D025C( void );

#define EXEC_LEVEL 4

void s07c_meryl72_800C6AF8( Meryl72Work *work )
{
    int lo, hi;

    lo = GM_PlayerAddress_800AB9F0 & 0xFF;
    hi = ( GM_PlayerAddress_800AB9F0 >> 8 ) & 0xFF;

    if ( lo == hi && lo != 0xFF )
    {
        work->fB84 = GM_PlayerAddress_800AB9F0;
        work->fB88 = GM_PlayerPosition_800ABA10;
        work->fB90 = GM_PlayerMap_800ABA0C;
    }
}

int RootFlagCheck_800C6B5C( Meryl72Work *work )
{
    SVECTOR  sp10;
    CONTROL *control;
    GV_MSG  *msg;
    int      i;

    control = &work->control;
    control->field_56 = GV_ReceiveMessage( control->name, &control->field_5C_mesg );

    msg = control->field_5C_mesg;
    for ( i = control->field_56; i > 0; i-- )
    {
        if ( msg->message[0] == GV_StrCode( "ルート変更" ) )
        {
            work->fB0B = msg->message[1];

            sp10.vx = msg->message[2];
            sp10.vy = msg->message[3];
            sp10.vz = msg->message[4];

            if ( sp10.vy < 30000 )
            {
                work->param.defends[0] = HZD_GetAddress( work->control.map->hzd, &sp10, -1 );
            }
            else
            {
                work->param.defends[0] = 255;
            }

            return 1;
        }

        msg++;
    }

    return 0;
}

MENU_BAR_CONF s07c_dword_800C32E4 = {"MERYL", {31, 191, 95}, {31, 191, 95}};

void s07c_meryl72_800C6C48( Meryl72Work *work )
{
    PARAM  *param;
    TARGET *target;

    param = &work->param;
    target = work->target;

    if ( param->life != target->field_26_hp )
    {
        param->life = target->field_26_hp;
        work->fC36 = 150;
    }

    if ( param->life < 0 )
    {
        param->life = 0;
    }

    if ( param->life < param->max_life )
    {
        param->max_life -= 4;
    }

    MENU_DrawBar2_80038DE0( 28, param->max_life, param->life, GM_SnakeMaxHealth, &s07c_dword_800C32E4 );

    if ( work->fC36 > 0 )
    {
        work->fC36--;
    }
    else if ( param->life > ( GM_SnakeMaxHealth / 2 ) )
    {
        GM_GameStatus &= ~STATE_SHOW_LIFEBAR;
    }
}

void Meryl72Act_800C6D54( Meryl72Work *work )
{
    CONTROL *control;
    TARGET  *target;

    control = &work->control;

    if ( GM_CheckMessage( &work->actor, control->name, HASH_KILL ) )
    {
        GV_DestroyActor( &work->actor );
        return;
    }

    s07c_meryl72_unk1_800CBCD8( work );

    GM_ActControl( control );
    GM_ActObject2( &work->body );
    GM_ActObject2( &work->weapon );

    DG_GetLightMatrix2( &control->mov, work->light );

    s07c_meryl72_800C6AF8( work );
    RootFlagCheck_800C6B5C( work );
    s07c_meryl72_unk1_800CBC44( work );

    target = work->target;
    GM_MoveTarget( target, &control->mov );
    GM_PushTarget( target );

    s07c_meryl72_800C6C48( work );
    work->fC04++;

    meryl72_800D52F8 = work->control.mov;
}

SVECTOR s07c_dword_800C32F0 = { 300, 1500, 300, 0 };
SVECTOR s07c_dword_800C32F8 = { 0, 0, 0, 0 };
SVECTOR s07c_dword_800C3300 = { 100, 300, 100, 0 };
SVECTOR s07c_dword_800C3308 = { 100, 0, 0, 0 };

void s07c_meryl72_800C6E48( Meryl72Work *work )
{
    TARGET *target;
    int     life;
    int     faint;

    target = work->target;
    life = work->param.life;
    faint = work->param.faint;

    GM_SetTarget( target, TARGET_FLAG, ENEMY_SIDE, &s07c_dword_800C32F0 );
    GM_Target_8002DCCC( target, 1, -1, life, faint, &s07c_dword_800C32F8 );
    GM_Target_8002DCB4( target, -1, faint, NULL, NULL );
    sub_8002DD14( target, &work->body.objs->objs[1].world );

    GM_SetTarget( &work->target2, TARGET_FLAG & ~( TARGET_SEEK | TARGET_PUSH | TARGET_CAPTURE ), PLAYER_SIDE, &s07c_dword_800C3300 );
    GM_Target_8002DCCC( &work->target2, 7, 5, 0, 0, &s07c_dword_800C3308 );
}

void s07c_meryl72_800C6F30( Meryl72Work *work )
{
    UNK *unk;

    unk = &work->f8BC;
    GV_ZeroMemory( unk, sizeof(UNK) );
    unk->field_00 = 0;
    unk->field_1A = 450;
    unk->field_1C = 1;

    work->action = 0;
    work->action2 = 0;
    work->time = 0;
    work->time2 = 0;
}

int s07c_meryl72_800C6F8C( Meryl72Work *work, int name, int map )
{
    SVECTOR  indices;
    CONTROL *control;
    char    *pos;
    char    *dir;
    OBJECT  *body;
    OBJECT  *weapon;
    int      motion;

    control = &work->control;

    if ( GM_InitControl( control, name, map ) < 0 )
    {
        return -1;
    }

    pos = GCL_GetOption( 'p' );
    dir = GCL_GetOption( 'd' );
    GM_ConfigControlString( control, pos, dir );
    GM_ConfigControlAttribute( control, RADAR_ALL_MAP | RADAR_SIGHT | RADAR_VISIBLE );
    GM_ConfigControlInterp( control, 4 );
    control->field_59 = 2;
    GM_ConfigControlTrapCheck( control );

    body = &work->body;
    weapon = &work->weapon;

    if ( work->fB94 == 0 )
    {
        motion = GV_StrCode( "mel_07a" );
    }
    else
    {
        motion = GV_StrCode( "mel_09a" );
    }

    GM_InitObject( body, GV_StrCode( "meryl" ), BODY_FLAG, motion );
    GM_ConfigObjectJoint( body );
    GM_ConfigMotionControl_80034F08( body, &work->m_ctrl, motion, work->m_segs1, work->m_segs2, control, work->rots );
    GM_ConfigObjectLight( body, work->light );

    work->homing = GM_AllocHomingTarget( &work->body.objs->objs[6].world, control );

    GM_InitObject( weapon, GV_StrCode( "desert" ), WEAPON_FLAG, 0 );
    GM_ConfigObjectLight( weapon, work->light );
    GM_ConfigObjectRoot( weapon, body, 4 );

    indices.vx = 0;
    indices.vy = 6;
    indices.vz = 12;
    indices.pad = 15;
    work->shadow = (GV_ACT *)NewShadow2_80060384( control, body, indices, &work->enable_shadow );

    ML72_SetPutChar_800CB584( work, 2 );

    if ( work->fB94 != 0 )
    {
        ML72_SetPutChar_800CB584( work, 4 );
    }

    s07c_meryl72_800C6F30( work );
    return 0;
}

void s07c_meryl72_800C7194( Meryl72Work *work )
{
    GCL_ARGS args;
    long     data[4];

    GM_FreeHomingTarget( work->homing );
    GM_FreeControl( &work->control );
    GM_FreeObject( &work->body );
    GM_FreeObject( &work->weapon );
    GM_FreeTarget( work->target );
    GV_DestroyActor( work->shadow );

    if ( work->fC3C >= 0 )
    {
        args.argc = 1;
        args.argv = data;

        data[0] = work->target->field_26_hp;
        GCL_ForceExecProc( work->fC3C, &args );
    }
}

void s07c_meryl72_800C722C( void )
{
    printf( " type=0x%x\n", gUnkCameraStruct2_800B7868.type );
    printf( " rotate x=%d y=%d z=%d\n",
            gUnkCameraStruct2_800B7868.rotate.vx,
            gUnkCameraStruct2_800B7868.rotate.vy,
            gUnkCameraStruct2_800B7868.rotate.vz );
    printf( " track=%d\n", gUnkCameraStruct2_800B7868.track );

    memcpy( &meryl72_camera_800D5278, &GM_Camera_800B77E8, sizeof(GM_Camera) );

    GM_Camera_800B77E8.rotate.vx = 480;
    GM_Camera_800B77E8.field_28 = 2;
    GM_Camera_800B77E8.field_2A = 2;
    GM_Camera_800B77E8.interp = 0;
    GM_Camera_800B77E8.flags |= 0x2;
}

void s07c_meryl72_800C730C(void)
{
    memcpy( &GM_Camera_800B77E8, &meryl72_camera_800D5278, sizeof(GM_Camera) );
}

void s07c_meryl72_800C7368( void )
{
    GM_Camera_800B77E8.track = GV_NearExp8( GM_Camera_800B77E8.track, 4000 );
    printf( " track=%d\n", GM_Camera_800B77E8.track );
}

void Meryl72Die_800C73AC( Meryl72Work *work )
{
    s07c_meryl72_800C7194( work );
}

int s07c_meryl72_800C73CC( Meryl72Work *work )
{
    PARAM   *param;
    int      c_root;
    HZD_PAT *pat;
    HZD_PTP *points;
    int      i;

    param = &work->param;
    c_root = param->c_root;

    pat = work->control.map->hzd->header->routes;
    pat += param->roots[ c_root ];

    fprintf( 1, "c_root= %d pat %d n_points = %d \n", c_root, (int)pat, pat->n_points );

    work->n_patrols = pat->n_points;
    if ( work->n_patrols <= 0 )
    {
        return -1;
    }

    points = pat->points;
    for ( i = 0; i < work->n_patrols; i++ )
    {
        work->nodes[ i ].vx = points->x;
        work->nodes[ i ].vy = points->y;
        work->nodes[ i ].vz = points->z;
        work->nodes[ i ].pad = points->command;
        points++;

        fprintf( 1, "action = 0x%x \n", work->nodes[ i ].pad );
    }

    return 0;
}

int s07c_meryl72_800C74E0( char *opt, char *roots )
{
    int   count;
    char *param;

    count = 0;
    while ( ( param = GCL_GetParamResult() ) )
    {
        *roots++ = GCL_StrToInt( param );
        count++;
    }

    return count;
}


int s07c_meryl72_800C7538( char *opt, int *voices )
{
    int   count;
    char *param;

    count = 0;
    while ( ( param = GCL_GetParamResult() ) )
    {
        *voices++ = GCL_StrToInt( param );
        count++;
    }

    return count;
}

int s07c_meryl72_800C7590( Meryl72Work *work )
{
    char *opt;

    opt = GCL_GetOption( 'v' );
    if ( opt && s07c_meryl72_800C7538( opt, work->voices ) > 25 )
    {
        fprintf( 0, "Err Err Err Sound Buff Over !!\n" );
        return -1;
    }

    return 0;
}

int s07c_meryl72_800C75F0( Meryl72Work *work, char *opt, char *defends )
{
    SVECTOR zone;
    int     count;
    char   *param;

    count = 0;
    while ( ( param = GCL_GetParamResult() ) )
    {
        *defends = GCL_StrToInt( param );
        GCL_StrToSV( param, &zone );

        if ( zone.vy < 30000 )
        {
            *defends = HZD_GetAddress( work->control.map->hzd, &zone, -1 );
        }
        else
        {
            *defends = 255;
        }

        printf( " defence zone =%d ", *defends );

        count++;
        defends++;
    }

    return count;
}

// unused for now
const char s07c_aErrnotenoughwork_800D4788[] = "Err not enough work !!\n";

int s07c_meryl72_800C76B0( Meryl72Work *work )
{
    int   i;
    char *opt;

    for ( i = 0; i < 6; i++ )
    {
        work->fC1C[ i ] = -1;
    }

    i = 0;

    opt = GCL_GetOption( 'a' );
    while ( opt )
    {
        if ( i >= 6 )
        {
            return -1;
        }

        work->fC1C[ i ] = GCL_StrToInt( opt );
        opt = GCL_GetParamResult();
        i++;
    }

    return i;
}

int Meryl72GetResources_800C7738( Meryl72Work *work, int arg1, int arg2 )
{
    char    *opt;
    int      i;
    CONTROL *control;
    int      addr;

    work->fB94 = 0;

    opt = GCL_GetOption( 's' );
    if ( opt )
    {
        work->fB94 = GCL_StrToInt( opt );
    }

    work->fB96 = 0;

    opt = GCL_GetOption( 'c' );
    if ( opt )
    {
        work->fB96 = GCL_StrToInt( opt );
    }

    if ( s07c_meryl72_800C6F8C( work, arg1, arg2 ) )
    {
        return -1;
    }

    if ( s07c_meryl72_800C7590( work ) < 0 )
    {
        return -1;
    }

    if ( s07c_meryl72_800C76B0( work ) < 0 )
    {
        return -1;
    }

    work->param.fAF8 = 0;
    work->param.roots[0] = 0;
    work->param.c_root = 0;

    opt = GCL_GetOption( 'r' );
    if ( opt && s07c_meryl72_800C74E0( opt, work->param.roots ) >= 4 )
    {
        fprintf( 0, "Err Err Err Change Root Num Over !!\n" );
    }

    work->fB58 = 2000;
    work->fB0B = work->param.roots[0];
    work->param.life = GM_SnakeMaxHealth;

    opt = GCL_GetOption( 'l' );
    if ( opt )
    {
        work->param.life = GCL_StrToInt( opt );
    }

    if ( work->param.life < 32 )
    {
        work->param.life = 512;
    }

    work->param.max_life = work->param.life;
    printf( "Meryl life = %d \n", work->param.max_life );

    work->param.faint = 20;

    opt = GCL_GetOption( 'f' );
    if ( opt )
    {
        work->param.faint = GCL_StrToInt( opt );
    }

    work->param.fAF9 = 65;

    opt = GCL_GetOption( 'b' );
    if ( opt )
    {
        work->param.fAF9 = GCL_StrToInt( opt );
    }

    work->param.defends[ work->param.c_root ] = 255;

    opt = GCL_GetOption( 'n' );
    if ( opt && s07c_meryl72_800C75F0( work, opt, work->param.defends ) >= 4 )
    {
        fprintf( 0, "Err Err Err Change Defend Num Over !!\n" );
    }

    work->param.fAFA = 65;

    opt = GCL_GetOption( 'a' );
    if ( opt )
    {
        work->param.fAFA = GCL_StrToInt( opt );
    }

    work->fB0A = 1;

    if ( s07c_meryl72_800C73CC( work ) < 0 )
    {
        fprintf( 1, "watchar.c : action point Err\n" );
    }

    if ( GCL_GetOption( 'e' ) )
    {
        work->fC3C = GCL_StrToInt( GCL_GetParamResult() );
    }
    else
    {
        work->fC3C = -1;
    }

    if ( GCL_GetOption( 'z' ) )
    {
        work->proc_id = GCL_StrToInt( GCL_GetParamResult() );
    }
    else
    {
        work->proc_id = -1;
    }

    work->target = GM_AllocTarget();
    if ( work->target )
    {
        s07c_meryl72_800C6E48( work );
    }

    GM_SetCameraCallbackFunc_8002FD84( 1, s07c_meryl72_800C7368 );

    work->fABC = 0;
    work->fABE = 0;
    work->fAC0 = 0;
    work->fAC2 = 0;
    work->fAC4 = 0;
    work->fAC8 = 0;

    work->target_pos = work->nodes[ 0 ];
    work->target_addr = HZD_GetAddress( work->control.map->hzd, &work->target_pos, -1 );
    work->target_map = GM_CurrentMap_800AB9B0;

    work->vision.angle = 2048; //vision length
    work->vision.length = 4000; //vision angle
    work->fB18 = 0;
    work->vision.facedir = 0;
    work->pad.sound = 0;
    work->pad.time = 0;
    work->fB28 = DG_ZeroVector;
    work->subweapon = 0;
    work->fB98 = 0;
    work->fC0A = 0;
    work->fC0C = 0;
    work->fC0E = 0;

    if ( work->fB96 != 0 )
    {
        work->control.mov = work->f9A4;
    }
    else
    {
        work->control.mov = work->nodes[ 0 ];
    }

    work->fC10[0] = work->fC10[1] = work->fC10[2] = 0;

    work->fC34 = 0;
    work->fC36 = 0;

    for ( i = 0; i < 8; i++ )
    {
        work->modetime[ i ] = 0;
    }

    work->modetime[ 7 ] = 23;
    work->modetime[ 4 ] = -1;

    control = &work->control;
    GM_ConfigControlRadarparam( control, 0, 4000, 2048, 0 );

    work->start_pos = work->nodes[ 0 ];
    work->start_map = GM_CurrentMap_800AB9B0;

    addr = HZD_GetAddress( work->control.map->hzd, &control->mov, -1 );
    work->start_addr = addr;
    work->fB60 = addr;
    work->fB4C = addr;

    work->fB6C = work->start_pos;
    work->fC04 = 0;
    work->fAF4 = 0;

    s07c_meryl72_unk2_800D025C();
    s07c_meryl72_unk2_800D0220();

    return 0;
}

GV_ACT *NewMeryl72_800C7BC4( int arg0, int arg1 )
{
    Meryl72Work *work;

    work = (Meryl72Work *)GV_NewActor( EXEC_LEVEL, sizeof(Meryl72Work) );
    if (work)
    {
        GV_SetNamedActor( &work->actor,
                          (GV_ACTFUNC)Meryl72Act_800C6D54,
                          (GV_ACTFUNC)Meryl72Die_800C73AC,
                          "meryl72.c" );

        if ( Meryl72GetResources_800C7738( work, arg0, arg1 ) < 0 )
        {
            GV_DestroyActor( &work->actor );
            return NULL;
        }
    }

    return (GV_ACT *)work;
}