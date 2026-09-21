#include "strcode.h"
#include "bullet/blast.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/vibrate.h" // for NewPadVibration
#include "okajima/spark.h"
#include "takabe/spark2.h"

/*---------------------------------------------------------------------------*/

#define MAX_TURN_X  768
#define MAX_TURN_Y  1024

#define ARM_DATA    GV_StrCode( "cam_arm" )

#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                    | DG_FLAG_GBOUND | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )

#define TARGET_FLAG ( TARGET_AVAIL | TARGET_POWER | TARGET_SEEK )

#define PRIM_TYPE   ( DG_PRIM_RECTANGLE | DG_PRIM_POLY_FT4 )

#define LED_TEXTURE GV_StrCode( "camera_l" )

typedef struct _Work {
    GV_ACT         actor;
    CONTROL        control;
    OBJECT_NO_ROTS body;
    OBJECT_NO_ROTS arm;
    SVECTOR        arm_pos;
    SVECTOR        arm_rot;
    MATRIX         arm_light[ 2 ];
    SVECTOR        rot[ 2 ];
    MATRIX         light[ 2 ];
    char           pad180[ 32 ];
    SVECTOR        vertices[ 2 ];
    DG_PRIM *      led_prim;
    DG_TEX  *      tex;
    short          field_1BC;
    short          field_1BE;
    SVECTOR        field_1C0[ 16 ];
    SVECTOR        field_240;
    char           pad248[ 32 ];
    SVECTOR        lens_pos;
    SVECTOR        lens_shift;
    SVECTOR        center_rot;
    char           pad278[ 32 ];
    TARGET *       target;
    int            target_enable;
    int            think1;
    char           pad2AC[ 4 ];
    int            state;
    int            time;
    int            damage_time;
    int            active;
    int            vibtime;
    char           pad2C4[ 4 ];
    SVECTOR        smoke_speed[ 8 ];
    SVECTOR        smoke_pos[ 8 ];
    u_short        mode;
    u_short        length;
    u_short        width;
    u_short        max_turn;
} Work;

/*---------------------------------------------------------------------------*/

static u_char VibH[] = {1, 1, 0, 0};
static u_char VibL[] = {255, 1, 0, 0};
static RECT Rect = {120, 120, 240, 240};
static SVECTOR Size = {301, 301, 301};

/*---------------------------------------------------------------------------*/

extern void AN_CameraSmoke( SVECTOR *pos );
extern void AN_HeadMark( MATRIX *world, int mark );

extern void COM_CallBikkuriSe( SVECTOR *pos, int flag );

/*---------------------------------------------------------------------------*/

static void ShadePacks( DG_PRIM *prim, DG_TEX *tex, int r, int g, int b )
{
    POLY_FT4 *packs;

    packs = (POLY_FT4 *)prim->packs[ 0 ];
    setRGB0( packs, r, g, b );

    packs = (POLY_FT4 *)prim->packs[ 1 ];
    setRGB0( packs, r, g, b );
}

static int GetSvecs( char *opt, SVECTOR *data )
{
    int count;
    char *str;

    count = 0;
    while ( ( str = GCL_NextStr() ) != NULL )
    {
        GCL_StrToSV( str, (short *)data );
        data++;
        count++;
    }

    return count;
}

static void GetDir( SVECTOR *from, SVECTOR *to, SVECTOR *dir )
{
    SVECTOR diff;
    int y;

    GV_SubVec3( to, from, &diff );
    dir->vy = ratan2( diff.vx, diff.vz ) & 4095;

    y = diff.vy;
    diff.vy = 0;

    dir->vx = ( ratan2( GV_VecLen3( &diff ), y ) & 4095 ) - 1024;
    if ( dir->vx < 0 ) dir->vx += 4096;
}

static int CheckVisible( Work *work )
{
    SVECTOR dir;
    SVECTOR *mov;
    int dy, dx;

    if ( !( work->control.map->index & GM_PlayerMap ) ) return 0;

    mov = &work->control.mov;
    GetDir( mov, &GM_PlayerPosition, &dir );
    dy = GV_DiffDirAbs( dir.vy, work->control.rot.vy );
    dx = GV_DiffDirAbs( dir.vx, work->control.rot.vx );

    if ( dx > work->width ) return 0;
    if ( dy > work->width ) return 0;
    if ( GV_DiffVec3( mov, &GM_PlayerPosition ) > work->length ) return 0;
    return HZD_OnlineHazardCheck( work->control.map->hzd, mov, &GM_PlayerPosition, HZD_CHK_ALL, HZD_SEG_NO_NAVIGATE ) == 0;
}

static void ClampTurn( SVECTOR *start, SVECTOR *turn )
{
    int diff;

    if ( turn->vx > MAX_TURN_X ) turn->vx = MAX_TURN_X;

    diff = GV_DiffDirS( start->vy, turn->vy );
    if ( diff > MAX_TURN_Y )
    {
        turn->vy = ( start->vy + MAX_TURN_Y ) & 4095;
    }
    else if ( diff < -MAX_TURN_Y )
    {
        turn->vy = ( start->vy - MAX_TURN_Y ) & 4095;
    }
}

static void SetVibrate( Work *work )
{
    if ( work->vibtime > 0 )
    {
        NewPadVibration( VibH, 1 );
        NewPadVibration( VibL, 2 );
        work->vibtime--;
    }
    else
    {
        work->vibtime = 0;
    }
}

static void FollowPlayerQuick( Work *work )
{
    GetDir( &work->control.mov, &GM_PlayerPosition, &work->control.turn );
    ClampTurn( &work->center_rot, &work->control.turn );
    work->control.rot = work->control.turn;
}

static void FollowPlayer( Work *work )
{
    GetDir( &work->control.mov, &GM_PlayerPosition, &work->control.turn );
    ClampTurn( &work->center_rot, &work->control.turn );
}

static int ActAlert( Work *work )
{
    int time;

    time = work->time;

    if ( time == 0 )
    {
        GM_SeSet( &work->control.mov, 95 );
        ShadePacks( work->led_prim, work->tex, 255, 0, 0 );
    }

    FollowPlayer( work );

    if ( time == 15 )
    {
        COM_CallBikkuriSe( &work->control.mov, 0x20 );
        AN_HeadMark( &work->body.objs->objs[ 0 ].world, 0 );
        work->vibtime = 10;
        FollowPlayerQuick( work );
    }

    if ( time == 35 )
    {
        GM_AlertLevel = 255;
        GM_AlertMode = 3;
        return 1;
    }

    work->time++;
    return 0;
}

static int TurnRight( Work *work )
{
    SVECTOR *turn;

    if ( work->time > 60 )
    {
        turn = &work->control.turn;
        turn->vy = ( turn->vy + 8 ) & 4095;
        if ( GV_DiffDirAbs( work->center_rot.vy, turn->vy ) > work->max_turn ) return 1;
    }

    work->time++;
    return 0;
}

static int TurnLeft( Work *work )
{
    SVECTOR *turn;

    if ( work->time > 60 )
    {
        turn = &work->control.turn;
        turn->vy = ( turn->vy - 8 ) & 4095;
        if ( GV_DiffDirAbs( work->center_rot.vy, turn->vy ) > work->max_turn ) return 1;
    }

    work->time++;
    return 0;
}

static void TurnRandom( Work *work )
{
    SVECTOR *turn;
    int vy;

    if ( ( work->time % 64 ) == 0 )
    {
        work->time += GV_RandU( 16 );
        work->control.interp = 48;

        turn = &work->control.turn;
        vy = work->center_rot.vy + ( GV_RandU( 2048 ) - 1024 );
        turn->vy = vy & 4095;
        turn->vx = GV_RandU( 768 );
        ClampTurn( &work->center_rot, turn );
    }

    work->time++;
}

static int TurnCenter( Work *work )
{
    SVECTOR *center, *turn;
    int diff;

    center = &work->center_rot;
    turn = &work->control.turn;

    diff = GV_DiffDirS( center->vy, turn->vy );
    if ( diff < -10 )
    {
        turn->vy += 8;
    }
    else if ( diff < 10 )
    {
        turn->vy = center->vy;
    }
    else
    {
        turn->vy -= 8;
    }
    turn->vy &= 4095;

    diff = GV_DiffDirS( center->vx, turn->vx );
    if ( diff < -10 )
    {
        turn->vx += 8;
    }
    else if ( diff < 10 )
    {
        turn->vx = center->vx;
    }
    else
    {
        turn->vx -= 8;
    }
    turn->vx &= 4095;

    if ( turn->vx == center->vx &&
         turn->vy == center->vy &&
         work->time > 96 ) return 1;

    work->time++;
    return 0;
}

static void Phase0( Work *work )
{
    switch ( work->state )
    {
    case 1:
        if ( TurnRight( work ) )
        {
            work->state = 2;
            work->time = 0;
        }

        if ( CheckVisible( work ) )
        {
            work->state = 7;
            work->time = 0;
        }
        break;
    case 2:
        if ( TurnLeft( work ) )
        {
            work->state = 1;
            work->time = 0;
        }

        if ( CheckVisible( work ) )
        {
            work->state = 7;
            work->time = 0;
        }
        break;
    case 3:
        work->state = 1;
        work->time = 0;
        break;
    case 7:
        if ( ActAlert( work ) )
        {
            work->target_enable = 1;
            work->think1 = 1;
            work->state = 4;
            work->time = 0;
            return;
        }
        break;
    }

    if ( GM_AlertMode == 3 )
    {
        work->target_enable = 1;
        work->think1 = 1;
        work->state = 0;
        work->time = 0;
        ShadePacks( work->led_prim, work->tex, 255, 0, 0 );
    }
}

static void Phase1( Work *work )
{
    switch ( work->state )
    {
    case 4:
        FollowPlayer( work );
        if ( !CheckVisible( work ) ) work->state = 0;
        break;
    case 0:
        if ( CheckVisible( work ) ) work->state = 4;
        break;
    }

    if ( GM_AlertMode != 3 )
    {
        work->think1 = 2;
        work->state = 5;
        work->time = 0;
        ShadePacks( work->led_prim, work->tex, 255, 255, 0 );
    }
}

static void Phase2( Work *work )
{
    switch ( work->state )
    {
    case 5:
        TurnRandom( work );
        if ( GM_AlertMode == 0 )
        {
            work->state = 6;
            work->time = 0;
        }
        break;
    case 6:
        if ( TurnCenter( work ) )
        {
            work->think1 = 0;

            if ( work->mode == 2 )
            {
                work->state = 3;
            }
            else
            {
                work->state = 1;
            }

            work->time = 0;
            work->active = 0;
            ShadePacks( work->led_prim, work->tex, 0, 255, 0 );
        }
        break;
    }

    if ( CheckVisible( work ) )
    {
        work->think1 = 1;
        work->state = 4;
        work->time = 0;
        ShadePacks( work->led_prim, work->tex, 255, 0, 0 );
    }
    else if ( GM_AlertMode == 3 )
    {
        work->think1 = 1;
        work->state = 0;
        work->time = 0;
        ShadePacks( work->led_prim, work->tex, 255, 0, 0 );
    }
}

static void Think( Work *work )
{
    switch ( work->think1 )
    {
    case 0:
        Phase0( work );
        break;
    case 1:
        Phase1( work );
        break;
    case 2:
        Phase2( work );
        break;
    }
}

static void Act( Work *work )
{
    TARGET *target;
    int i;

    if ( GM_CheckMessage( work, work->control.name, HASH_KILL ) )
    {
        GV_DestroyActor( work );
        return;
    }

    if ( work->target_enable != 0 )
    {
        work->target->class = ( TARGET_AVAIL | TARGET_POWER | TARGET_SEEK );
    }
    else
    {
        work->target->class = TARGET_AVAIL;
    }

    SetVibrate( work );

    if ( work->damage_time == 0 )
    {
        MATRIX mat;

        GM_ActControl( &work->control );
        GM_ActObject2( (OBJECT *)&work->body );

        DG_PutPrim( work->led_prim );
        DG_MovePos( &work->lens_shift );
        ReadRotMatrix( &mat );
        DG_COPY_VEC( &work->lens_pos, (VECTOR *)mat.t );

        DG_SetPos2( &work->control.mov, &work->arm_rot );
        DG_MovePos( &work->arm_pos );

        GM_ActObject2( (OBJECT *)&work->arm );

        DG_GetLightMatrix2( &work->control.mov, work->light );

        target = work->target;
        GM_MoveTarget( target, &work->control.mov );

        if ( target->damaged & TARGET_POWER )
        {
            if ( target->a_mode != 2 )
            {
                target->damage = 0;
                target->damaged = 0;
            }
            else
            {
                work->damage_time = 1;
                AN_Blast_Mini( &work->control.mov );

                for ( i = 0; i < 8; i++ )
                {
                    MATRIX mat;
                    SVECTOR rot, pos;

                    rot.vz = 0;

                    pos.vx = GV_RandS( 128 );
                    pos.vy = GV_RandU( 256 ) + 32;
                    pos.vz = 0;

                    rot.vx = GV_RandU( 256 ) + 64;
                    rot.vy = work->control.rot.vy + GV_RandS( 1024 );

                    RotMatrixYXZ_gte( &rot, &mat );
                    ApplyMatrixSV( &mat, &pos, &work->smoke_speed[ i ] );
                    work->smoke_pos[ i ] = work->control.mov;
                }
            }
        }
    }
    else
    {
        if ( ++work->damage_time >= 10 )
        {
            MATRIX mat;
            SVECTOR rot;

            rot.vx = GV_RandU( 1024 );
            rot.vy = GV_RandU( 2048 );
            rot.vz = 0;
            DG_SetPos2( &work->control.mov, &rot );
            ReadRotMatrix( &mat );

            if ( ( work->damage_time % 8 ) == 0 )
            {
                NewSpark( &mat, GV_RandU( 2 ) );
            }

            if ( ( work->damage_time % 12 ) == 0 )
            {
                NewSpark2_800CA714( &mat );
            }
        }

        DG_InvisibleObjs( work->body.objs );
        DG_InvisibleObjs( work->arm.objs );

        ShadePacks( work->led_prim, work->tex, 0, 0, 0 );

        for ( i = 0; i < 8; i++ )
        {
            work->smoke_speed[ i ].vy -= 15;
            work->smoke_pos[ i ].vx += work->smoke_speed[ i ].vx;
            work->smoke_pos[ i ].vy += work->smoke_speed[ i ].vy;
            work->smoke_pos[ i ].vz += work->smoke_speed[ i ].vz;
            AN_CameraSmoke( &work->smoke_pos[ i ] );
        }

        if ( work->damage_time >= 40 )
        {
            GV_DestroyActor( work );
        }
    }

    if ( work->active != 0 )
    {
        Think( work );
        DG_VisiblePrim( work->led_prim );
    }
    else
    {
        DG_InvisiblePrim( work->led_prim );
    }
}

static int InitOption( Work *work, int name, int where )
{
    char *opt;

    opt = GCL_GetOption( 'm' );
    if ( opt != NULL )
    {
        work->mode = GCL_StrToInt( opt );
    }
    else
    {
        work->mode = 0;
    }

    work->mode = 0;

    opt = GCL_GetOption( 'l' );
    if ( opt != NULL )
    {
        work->length = GCL_StrToInt( opt );
    }
    else
    {
        work->length = 0;
    }

    opt = GCL_GetOption( 'w' );
    if ( opt != NULL )
    {
        work->width = GCL_StrToInt( opt );
        if ( work->width > 512 ) work->width = 512;
    }
    else
    {
        work->width = 0;
    }

    opt = GCL_GetOption( 'x' );
    if ( opt != NULL )
    {
        work->max_turn = GCL_StrToInt( opt );
        if ( work->max_turn > 1024 ) work->max_turn = 1024;
    }
    else
    {
        work->max_turn = 0;
    }

    work->control.mov.vy += 25;
    work->control.mov.vz += 450;

    work->center_rot = work->arm_rot = work->control.rot;
    if ( work->center_rot.vx > 512 ) work->center_rot.vx = 512;

    work->arm_rot.vx = 0;

    ShadePacks( work->led_prim, work->tex, 0, 255, 0 );

    opt = GCL_GetOption( 'r' );
    if ( opt != NULL )
    {
        work->field_1BC = GetSvecs( opt, work->field_1C0 );
        work->field_1BE = 0;
    }
    else
    {
        work->field_1BC = 0;
    }

    opt = GCL_GetOption( 'o' );
    if ( opt != NULL )
    {
        work->active = 0;
    }
    else
    {
        work->active = 1;
    }

    if ( work->mode == 2 ) work->field_240 = work->field_1C0[ 0 ];

    work->think1 = 0;

    if ( work->mode == 2 )
    {
        work->state = 3;
    }
    else
    {
        work->state = 1;
    }

    work->time = 0;
    work->vibtime = 0;

    if ( work->active != 0 )
    {
        work->target_enable = 0;
    }
    else
    {
        work->target_enable = 1;
    }

    return 0;
}

static int InitArm( Work *work )
{
    OBJECT_NO_ROTS *arm;

    arm = &work->arm;
    GM_InitObjectNoRots( arm, ARM_DATA, BODY_FLAG, 0 );
    GM_ConfigObjectLight( (OBJECT *)arm, work->arm_light );
    work->arm_pos.vx = 0;
    work->arm_pos.vy = -25;
    work->arm_pos.vz = -450;
    return 0;
}

static void TextPacks( POLY_FT4 *packs, DG_TEX *tex, int v )
{
    setPolyFT4( packs );
    setRGB0( packs, v, v, v );
    setSemiTrans( packs, 1 );
    DG_SetPacketTexture4( packs, tex );
}

static int InitLed( Work *work )
{
    DG_PRIM *prim;
    DG_TEX *tex;

    work->vertices[ 0 ].vx = 50;
    work->vertices[ 0 ].vy = 300;
    work->vertices[ 0 ].vz = 350;

    work->led_prim = prim = GM_MakePrim( PRIM_TYPE, 1, work->vertices, &Rect );
    if ( prim == NULL ) return -1;
    DG_RaisePrim( prim, 500 );

    work->tex = tex = DG_GetTexture( LED_TEXTURE );
    if ( tex == NULL ) return -1;

    TextPacks( prim->packs[ 0 ], tex, 128 );
    TextPacks( prim->packs[ 1 ], tex, 100 );
    return 0;
}

static int GetResources( Work *work, int name, int where )
{
    CONTROL *ctrl;
    OBJECT_NO_ROTS *body;
    char *opt;
    TARGET *target;

    ctrl = &work->control;
    if ( GM_InitControl( ctrl, name, where ) < 0 ) return -1;
    GM_ConfigControlString( ctrl, GCL_GetOption( 'p' ), GCL_GetOption( 'd' ) );
    GM_ConfigControlAttribute( ctrl, 0xD );
    GM_ConfigControlHazard( ctrl, -1, -2, -1 );
    work->control.step = DG_ZeroVector;

    name = 'A';
    body = &work->body;

    opt = GCL_GetOption( 'n' );
    if ( opt != NULL ) name = GCL_StrToInt( opt );

    if ( name == 'A' )
    {
        opt = "s_camera";
    }
    else
    {
        opt = "s_camera";
    }

    GM_InitObjectNoRots( body, GV_StrCode( opt ), BODY_FLAG, 0 );
    body->objs->rots = work->rot;
    GM_ConfigObjectLight( (OBJECT *)body, work->light );
    GM_ConfigObjectStep( (OBJECT *)body, &work->control.step );

    work->lens_shift.vx = 0;
    work->lens_shift.vy = 175;
    work->lens_shift.vz = 600;

    InitArm( work );
    InitLed( work );

    work->target = target = GM_AllocTarget();
    if ( target != NULL )
    {
        GM_SetTarget( target, TARGET_FLAG, ENEMY_SIDE, &Size );
        return 0;
    }
    else
    {
        return -1;
    }
}

static void Die( Work *work )
{
    GM_FreeControl( &work->control );
    GM_FreeObject( (OBJECT *)&work->body );
    GM_FreeObject( (OBJECT *)&work->arm );
    GM_FreePrim( work->led_prim );
    GM_FreeTarget( work->target );
}

/*---------------------------------------------------------------------------*/

void *NewCamera2Set( int name, int where )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "camera2.c" );
        if ( GetResources( work, name, where ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
        InitOption( work, name, where );
    }
    return (void *)work;
}
