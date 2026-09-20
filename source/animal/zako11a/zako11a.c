#include "zako.h"

#include <stdio.h>
#include "strcode.h"
#include "mts/mts.h" // for fprintf
#include "libgcl/libgcl.h"
#include "chara/snake/shadow.h"
#include "enemy/glight.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

#define MOTION_DATA GV_StrCode( "ene_11a" )

#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                    | DG_FLAG_GBOUND | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )
#define WEAPON_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                    | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

#define TARGET_FLAG ( TARGET_AVAIL | TARGET_CAPTURE | TARGET_POWER \
                    | TARGET_PUSH | TARGET_SEEK | TARGET_TOUCH )

/*---------------------------------------------------------------------------*/

// rasen.c
extern int     Rasen_MapSection;
extern int     Rasen_LookSection;
extern u_short Rasen_Maps[];

/*---------------------------------------------------------------------------*/

static int dist_data[] = {
    1000, 2000, 1000, 2000, 8000, 8000, 8000, 8000,
};

static u_short time_data[] = {
    300, 15, 30, 60, 90, 0, 32001, 30000,
};

/*---------------------------------------------------------------------------*/

static void CheckFlag( Work *work )
{
    /* do nothing */
}

static void CheckMap( Work *work )
{
    CONTROL *control;

    if ( Rasen_LookSection == 1 )
    {
        control = &work->control;
        control->map = GM_GetMap( Rasen_Maps[ Rasen_MapSection ] );

        if ( control->mov.vy <= 0 )
        {
            control->mov.vy = -32000;
        }
        else
        {
            control->mov.vy -= 32000;
        }

        work->current_addr = -1;
        work->last_addr = -1;
        printf( "1ID[%d] %d %d %d\n", work->param.index, control->mov.vx, control->mov.vy, control->mov.vz );
    }
    else if ( Rasen_LookSection == 2 )
    {
        control = &work->control;
        control->map = GM_GetMap( Rasen_Maps[ Rasen_MapSection ] );

        if ( control->mov.vy < 0 )
        {
            control->mov.vy += 32000;
        }
        else
        {
            control->mov.vy = 32000;
        }

        work->current_addr = -1;
        work->last_addr = -1;
        printf( "2ID[%d] %d %d %d\n", work->param.index, control->mov.vx, control->mov.vy, control->mov.vz );
    }
}

static void ChangeModel( DG_OBJS *objs, DG_DEF *def )
{
    DG_OBJ *obj;
    int i;

    DG_FreeObjsPacket( objs, 0 );
    DG_FreeObjsPacket( objs, 1 );

    objs->def = def;
    obj = objs->objs;
    for ( i = 0; i < 16; i++ )
    {
        obj->model = &def->models[ i ];
        obj->n_packs = def->models[ i ].n_faces;
        obj++;
    }
}

static void CheckModel( Work *work )
{
    if ( work->field_9E4 != 0 )
    {
        if ( work->param.low_poly == 1 )
        {
            if ( ( GM_GameStatus & STATE_CAM_CHANGE ) || GM_Camera.first_person )
            {
                if ( work->lod != 1 )
                {
                    work->lod = 1;
                    ChangeModel( work->body.objs, work->lod_models[ 1 ] );
                }
            }
            else
            {
                if ( work->lod != 0 )
                {
                    work->lod = 0;
                    ChangeModel( work->body.objs, work->lod_models[ 0 ] );
                }
            }
        }

        DG_VisibleObjs( work->body.objs );
        DG_VisibleObjs( work->weapon.objs );
        *work->shadow_enable = 1;
        *work->glight_enable = 1;
    }
    else
    {
        DG_InvisibleObjs( work->body.objs );
        DG_InvisibleObjs( work->weapon.objs );
        *work->shadow_enable = 0;
        *work->glight_enable = 0;
    }
}

static void Act( Work *work )
{
    VECTOR scale;
    CONTROL *control;
    TARGET *trg, *touch;

    control = &work->control;
    if ( GM_CheckMessage( work, control->name, HASH_KILL ) )
    {
        GV_DestroyActor( work );
        return;
    }

    CheckFlag( work );
    CheckMap( work );

    if ( work->field_C38 == 0 )
    {
        Zako11APushMove( work );

        GM_ActControl( control );
        GM_ActObject2( &work->body );
        GM_ActObject2( &work->weapon );
        DG_GetLightMatrix2( &control->mov, work->light );

        Zako11AActionMain( work );

        trg = work->target;
        GM_MoveTarget( trg, &control->mov );
        GM_PushTarget( trg );

        if ( trg->class & TARGET_TOUCH )
        {
            touch = &work->touch;
            if ( touch->class & TARGET_TOUCH )
            {
                if ( touch->damaged & TARGET_TOUCH ) touch->damaged &= ~TARGET_TOUCH;
                GM_MoveTarget( touch, &control->mov );
                GM_TouchTarget( touch );
            }
        }

        scale.vx = scale.vy = scale.vz = work->scale;
        ScaleMatrix( &work->body.objs->world, &scale );
    }

    CheckModel( work );
    if ( ZAKO11A_GameFlag == 16 ) GV_DestroyActor( work );
}

static void InitTarget( Work *work )
{
    TARGET *trg, *trg2;
    int life, faint;

    trg = work->target;
    life = work->param.life;
    faint = work->param.faint;
    GM_SetTarget( trg, TARGET_FLAG, ENEMY_SIDE, &ZAKO11A_TARGET_SIZE );
    GM_SetPowerTarget( trg, POWER_DECREASE, -1, life, faint, &ZAKO11A_TARGET_FORCE );
    GM_SetCaptureTarget( trg, -1, faint, NULL, NULL );
    GM_SetC4Target( trg, &work->body.objs->objs[ 1 ].world );

    trg2 = &work->attack;
    GM_SetTarget( trg2, TARGET_POWER, PLAYER_SIDE, &ZAKO11A_ATTACK_SIZE );
    GM_SetPowerTarget( trg2, POWER_CONST | POWER_EXPLODE, 5, 0, 3, &ZAKO11A_ATTACK_FORCE );

    trg2 = &work->touch;
    GM_SetTarget( trg2, TARGET_TOUCH, ENEMY_SIDE, &ZAKO11A_TOUCH_SIZE );
    GM_SetPowerTarget( trg2, POWER_CONST | POWER_EXPLODE, 5, 0, 0, &ZAKO11A_TOUCH_FORCE );
}

static void InitAct( Work *work )
{
    ACT *act;

    act = &work->act;
    GV_ZeroMemory( act, sizeof(ACT) );
    act->field_00 = 0;
    act->field_1C = 450;
    act->field_1E = 1;

    work->field_8EC = 0;
    work->field_8F0 = 0;
    work->field_8F4 = 0;
    work->field_8F8 = 0;
}

static int InitState( Work *work, int name, int where )
{
    SVECTOR indices;
    CONTROL *control;
    OBJECT *body, *weapon;
    int i;

    control = &work->control;
    if ( GM_InitControl( control, name, where ) < 0 ) return -1;

    GM_ConfigControlString( control, GCL_GetOption( 'p' ), GCL_GetOption( 'd' ) );
    GM_ConfigControlAttribute( control, RADAR_VISIBLE | RADAR_SIGHT | RADAR_ALL_MAP );
    GM_ConfigControlInterp( control, 4 );
    control->seg_flag = HZD_SEG_NO_NAVIGATE;
    GM_ConfigControlTrapCheck( control );

    body = &work->body;
    weapon = &work->weapon;

    GM_InitObject( body, KMD_IPPANHEI, BODY_FLAG, MOTION_DATA );
    GM_ConfigObjectJoint( body );
    GM_ConfigMotionControl( body, &work->m_ctrl, MOTION_DATA, work->m_segs1, work->m_segs2, control, work->rots );
    GM_ConfigObjectLight( body, work->light );

    work->param.low_poly = 1;
    work->lod_models[ 1 ] = body->objs->def;
    work->lod_models[ 0 ] = GV_GetCache( GV_CacheID( KMD_LOPRYHEI, 'k' ) );
    work->lod = 1;

    work->hom = GM_SetHomingTarget( &body->objs->objs[ 6 ].world, control );

    GM_InitObject( weapon, KMD_FAMAS, WEAPON_FLAG, 0 );
    GM_ConfigObjectLight( weapon, work->light );
    GM_ConfigObjectRoot( weapon, body, 4 );

    for ( i = 0; i < 0; i++ )
    {
        work->field_B00[ i ] = 0;
    }

    indices.vx = 0;
    indices.vy = 6;
    indices.vz = 12;
    indices.pad = 15;
    work->shadow = NewShadow2( control, body, indices, &work->shadow_enable );
    work->glight = NewGunLight( &body->objs->objs[ 4 ].world, &work->glight_enable );

    s11a_800CE34C( work, 0 );
    InitAct( work );
    return 0;
}

static void FreeState( Work *work )
{
    ZAKO11AResetWorkID( work->param.index );
    GM_FreeControl( &work->control );
    GM_FreeObject( &work->body );
    GM_FreeObject( &work->weapon );
    GM_FreeTarget( work->target );
    GV_DestroyActor( work->glight );
    GV_DestroyActor( work->shadow );
    GM_ResetHomingTarget( work->hom );
}

static void Die( Work *work )
{
    FreeState( work );
}

static int ReadNodes( Work *work )
{
    HZD_PAT *route;
    HZD_PTP *point;
    int i;

    route = work->control.map->hzd->def->routes;
    route += work->param.root;

    work->n_nodes = route->n_points;
    if ( work->n_nodes <= 0 ) return -1;

    point = route->points;
    for ( i = 0; i < work->n_nodes; i++ )
    {
        work->nodes[ i ].vx = point->x;
        work->nodes[ i ].vy = point->y;
        work->nodes[ i ].vz = point->z;
        work->nodes[ i ].pad = point->command;
        point++;
    }

    return 0;
}

static int ReadDir( char *opt, short *data )
{
    int count;
    char *str;

    count = 0;
    while ( ( str = GCL_NextStr() ) != NULL )
    {
        *data = GCL_StrToInt( str );
        data++;
        count++;
    }
    return count;
}

static int ReadTime( char *opt, int *data )
{
    int count;
    char *str;

    count = 0;
    while ( ( str = GCL_NextStr() ) != NULL )
    {
        *data = GCL_StrToInt( str );
        data++;
        count++;
    }

    return count;
}

static int InitTables( Work *work )
{
    int i;
    char *opt;

    for ( i = 0; i < 8; i++ )
    {
        work->time[ i ] = time_data[ i ];
    }

    opt = GCL_GetOption( 't' );
    if ( opt )
    {
        if ( ReadTime( opt, &work->time[ 1 ] ) > 4 )
        {
            printf( "Err Err Err  Set time Over\n" );
            return -1;
        }
    }

    for ( i = 0; i < 4; i++ )
    {
        work->dir[ i ] = i * 1024;
    }

    opt = GCL_GetOption( 'i' );
    if ( opt )
    {
        if ( ReadDir( opt, work->dir ) > 4 )
        {
            printf( "Err Err Err  Set Dir Over\n" );
            return -1;
        }
    }

    return 0;
}

static void GetResources( Work *work, int name, int where )
{
    SVECTOR pos;
    char *opt;
    int addr, i;

    InitState( work, name, where );

    work->param.index = ZAKO11ASetWorkID( work );
    if ( work->param.index < 0 ) printf( "Err not enough work !!\n" );

    InitTables( work );

    work->param.root = 0;
    opt = GCL_GetOption( 'r' );
    if ( opt ) work->param.root = GCL_StrToInt( opt );

    work->param.life = 384;
    opt = GCL_GetOption( 'l' );
    if ( opt ) work->param.life = GCL_StrToInt( opt );

    work->param.faint = 7;
    opt = GCL_GetOption( 'f' );
    if ( opt ) work->param.faint = GCL_StrToInt( opt );

    work->param.z_flag = 64;
    opt = GCL_GetOption( 'z' );
    if ( opt ) work->param.z_flag = GCL_StrToInt( opt );

    work->param.blood = 65;
    opt = GCL_GetOption( 'b' );
    if ( opt ) work->param.blood = GCL_StrToInt( opt );

    printf( " low[pory=%d\n", work->param.low_poly );

    work->param.g_flag = 255;
    opt = GCL_GetOption( 'g' );
    if ( opt ) work->param.g_flag = GCL_StrToInt( opt );

    if ( work->param.blood == 90 ) work->param.g_flag = 0;

    work->chase_dis = dist_data[ work->param.index ];
    work->chase_index = work->param.index;

    work->param.next = 255;
    opt = GCL_GetOption( 'n' );
    if ( opt )
    {
        GCL_StrToSV( opt, (short *)&pos );
        if ( pos.vy < 30000 )
        {
            work->param.next = HZD_GetAddress( work->control.map->hzd, &pos, -1 );
        }
        else
        {
            work->param.next = 255;
        }
    }

    work->param.area = 'A';
    opt = GCL_GetOption( 'a' );
    if ( opt ) work->param.area = GCL_StrToInt( opt );

    if ( work->param.area == 'S' ) s11a_800CE34C( work, 1 );

    work->scale = 4096;
    opt = GCL_GetOption( 's' );
    if ( opt ) work->scale += GCL_StrToInt( opt );

    work->param.item = 1;

    if ( ReadNodes( work ) < 0 ) fprintf( 1, "watchar.c : action point Err\n" );

    work->target = GM_AllocTarget();
    if ( work->target ) InitTarget( work );

    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->think4 = 0;
    work->count3 = 0;
    work->l_count = 0;
    work->t_count = 0;
    work->mark_time = 0;
    work->next_node = 0;
    work->search_flag = 0;
    work->act_status = 0;

    work->field_BD4 = 0;

    work->target_pos = work->nodes[ 0 ];
    work->target_addr = HZD_GetAddress( work->control.map->hzd, &work->target_pos, -1 );
    work->target_map = GM_CurrentMap;
    work->alert_level = 0;

    work->field_9E4 = 1;
    work->vision.range = 512;
    work->vision.facedir = 0;
    work->field_B90 = 0;
    work->pad.sound = 0;
    work->pad.field_C = 0;
    work->vision.length = ZAKO11A_EYE_LENGTH;
    work->player_pos = ZAKO11A_NO_POINT;
    work->field_B54 = 0;
    work->control.mov = work->nodes[ 0 ];
    work->field_C44 = 0;
    work->param.c_root = work->param.root;
    work->param.c_next = work->param.next;

    for ( i = 0; i < 8; i++ )
    {
        work->modetime[ i ] = 0;
    }

    work->modetime[ 7 ] = 0x7;
    work->modetime[ 4 ] = 0xFF;

    GM_ConfigControlRadarparam( &work->control, 0, 512, ZAKO11A_EYE_LENGTH, 0 );

    work->start_pos = work->nodes[ 0 ];
    work->start_map = GM_CurrentMap;

    addr = HZD_GetAddress( work->control.map->hzd, &work->control.mov, -1 );
    work->field_BE8 = addr;
    work->next_addr = addr;
    work->last_addr = addr;
    work->next_pos = work->start_pos;
}

void *NewZako11A( int name, int where )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "zako11a.c" );
        GetResources( work, name, where );
    }
    return (void *)work;
}
