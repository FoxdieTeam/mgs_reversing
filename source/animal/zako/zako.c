#include "zako.h"

#include "strcode.h"
#include "mts/mts.h" // for fprintf
#include "chara/snake/shadow.h" // for NewHumanShadow2
#include "enemy/glight.h" // for NewGunLight

/*---------------------------------------------------------------------------*/

#define BODY_DATA   GV_StrCode( "ippanhei" )
#define WEAPON_DATA GV_StrCode( "famas" )

#define MOTION_DATA GV_StrCode( "enemy" )

#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                    | DG_FLAG_GBOUND | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )
#define WEAPON_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                    | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

/*---------------------------------------------------------------------------*/

static SVECTOR NoPoint = {30000, 30000, 30000};

/*---------------------------------------------------------------------------*/

static void SwapModel( DG_OBJS *objs, DG_DEF *def )
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

static void CheckVisible( Work *work )
{
    if ( work->visible )
    {
        if ( ( GM_GameStatus & STATE_CAM_CHANGE ) || GM_Camera.first_person )
        {
            if ( work->lod != 1 )
            {
                work->lod = 1;
                SwapModel( work->body.objs, work->models[ 1 ] );
            }
        }
        else
        {
            if ( work->lod != 0 )
            {
                work->lod = 0;
                SwapModel( work->body.objs, work->models[ 0 ] );
            }
        }

        DG_VisibleObjs( work->body.objs );
        DG_VisibleObjs( work->weapon.objs );
        *work->enable_shadow = 1;
        *work->enable_glight = 1;
    }
    else
    {
        DG_InvisibleObjs( work->body.objs );
        DG_InvisibleObjs( work->weapon.objs );
        *work->enable_shadow = 0;
        *work->enable_glight = 0;
    }
}

static void Act( Work *work )
{
    GM_ActControl( &work->control );
    GM_ActObject2( &work->body );
    DG_GetLightMatrix2( &work->control.mov, work->light );

    ZakoActionMain( work );
    GM_MoveTarget( work->target, &work->control.mov );

    if ( ZAKO_GameFlag == 13 && ZAKOCommand.watchers[ work->param.index ].field_4 == 1 )
    {
        GV_DestroyActor( work );
    }

    CheckVisible( work );
}

static void InitTarget( Work *work )
{
    TARGET *trg;
    int life, faint;

    trg = work->target;
    life = work->param.life;
    faint = work->param.faint;

    GM_SetTarget( trg, TARGET_FLAG, ENEMY_SIDE, &ZAKO_TARGET_SIZE );
    GM_SetPowerTarget( trg, 1, -1, life, faint, &ZAKO_TARGET_FORCE );
    GM_SetCaptureTarget( trg, -1, faint, NULL, NULL );
    GM_SetC4Target( trg, &work->body.objs->objs[ 1 ].world );

    GM_SetTarget( &work->attack, TARGET_POWER, PLAYER_SIDE, &ZAKO_ATTACK_SIZE );
    GM_SetPowerTarget( &work->attack, POWER_CONST | POWER_EXPLODE, 5, 0, 3, &ZAKO_ATTACK_FORCE );
}

static void InitAction( Work *work )
{
    ACT *act;

    act = &work->act;
    GV_ZeroMemory( act, sizeof(ACT) );
    act->field_00 = 0;
    act->field_1A = 450;
    act->field_1C = 1;

    work->action = NULL;
    work->action2 = NULL;
    work->time = 0;
    work->time2 = 0;
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
    GM_ConfigControlAttribute( control, 5 );
    GM_ConfigControlInterp( control, 4 );

    body = &work->body;
    weapon = &work->weapon;

    GM_InitObject( body, BODY_DATA, BODY_FLAG, MOTION_DATA );
    GM_ConfigObjectJoint( body );
    GM_ConfigMotionControl( body, &work->m_ctrl, MOTION_DATA, work->m_segs1, work->m_segs2, control, work->rots );
    GM_ConfigObjectLight( body, work->light );

    work->models[ 1 ] = work->body.objs->def;
    work->models[ 0 ] = GV_GetCache( GV_CacheID( KMD_LOWHEI, 'k' ) );
    work->lod = 1;

    work->hom = GM_SetHomingTarget( &work->body.objs->objs[ 6 ].world, control );

    GM_InitObject( weapon, WEAPON_DATA, WEAPON_FLAG, 0 );
    GM_ConfigObjectLight( weapon, work->light );
    GM_ConfigObjectRoot( weapon, body, 4 );

    for ( i = 0; i < 0; i++ )
    {
        work->putchar[ i ] = NULL;
    }

    indices.vx = 0;
    indices.vy = 6;
    indices.vz = 12;
    indices.pad = 15;
    work->shadow = NewHumanShadow2( control, body, indices, &work->enable_shadow );
    work->glight = NewGunLight( &body->objs->objs[ 4 ].world, &work->enable_glight );

    ZAKO_SetPutChar( work, PUTFOOTNOISE );
    InitAction( work );
    return 0;
}

static void Die(Work *work)
{
    ZAKOResetWorkID(work->param.index);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeObject(&work->weapon);
    GM_FreeTarget(work->target);
    GV_DestroyActor(work->glight);
    GV_DestroyActor(work->shadow);
    GM_ResetHomingTarget(work->hom);
}

static int ReadNodes( Work *work )
{
    PARAM *param;
    HZD_PAT *patrol;
    HZD_PTP *points;
    int i;

    param = &work->param;

    patrol = work->control.map->hzd->def->routes;
    patrol += param->roots[ param->c_root ];

    work->n_nodes = patrol->n_points;
    if ( work->n_nodes <= 0 ) return -1;

    points = patrol->points;
    for ( i = 0; i < work->n_nodes; i++ )
    {
        work->nodes[ i ].vx = points->x;
        work->nodes[ i ].vy = points->y;
        work->nodes[ i ].vz = points->z;
        work->nodes[ i ].pad = points->command;
        points++;
    }

    return 0;
}

static int ReadChars( char *opt, char *out )
{
    int i;
    char *str;

    i = 0;
    while ( ( str = GCL_NextStr() ) != NULL )
    {
        *out++ = GCL_StrToInt( str );
        i++;
    }

    return i;
}

static void GetResources( Work *work, int name, int where )
{
    char *opt;
    int i;

    InitState( work, name, where );

    work->param.index = ZAKOSetWorkID( work );
    if ( work->param.index < 0 )
    {
        fprintf( 0, "Err not enough work !!\n" );
    }

    work->n_dead = ZAKOSetDead();
    work->param.roots[ 0 ] = 0;
    work->param.c_root = 0;

    opt = GCL_GetOption( 'r' );
    if ( opt != NULL )
    {
        if ( ReadChars( opt, work->param.roots ) > 3 )
        {
            fprintf( 0, "Err Err Err Change Root Num Over !!\n" );
        }
    }

    switch ( work->param.index )
    {
    case 0:
        work->chase_dis = 3000;
        break;
    case 1:
        work->chase_dis = 4000;
        break;
    case 2:
        work->chase_dis = 7000;
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        work->chase_dis = 8000;
        break;
    }

    work->param.life = 192;
    opt = GCL_GetOption( 'l' );
    if ( opt != NULL )
    {
        work->param.life = GCL_StrToInt( opt );
    }

    work->param.faint = 255;
    opt = GCL_GetOption( 'f' );
    if ( opt != NULL )
    {
        work->param.faint = GCL_StrToInt( opt );
    }

    work->param.damage = 40;
    opt = GCL_GetOption( 'z' );
    if ( opt != NULL )
    {
        work->param.damage = GCL_StrToInt( opt );
    }

    work->param.blood = 'A';
    opt = GCL_GetOption( 'b' );
    if ( opt != NULL )
    {
        work->param.blood = GCL_StrToInt( opt );
    }

    work->param.defends[ work->param.c_root ] = 255;

    opt = GCL_GetOption( 'n' );
    if ( opt != NULL )
    {
        if ( ReadChars( opt, work->param.defends ) > 3 )
        {
            fprintf( 0, "Err Err Err Change Defend Num Over !!\n" );
        }
    }

    work->param.area = 'A';
    opt = GCL_GetOption('a');
    if ( opt != NULL )
    {
        work->param.area = GCL_StrToInt( opt );
    }

    if ( work->param.area == 'S' )
    {
        ZAKO_SetPutChar( work, PUTBREATH );
    }

    fprintf( 0, "Life=%d Faint=%d Blood=%c Area=%c \n",
             work->param.life,
             work->param.faint,
             work->param.blood,
             work->param.area );

    if ( ReadNodes( work ) < 0 )
    {
        fprintf( 1, "watchar.c : action point Err\n" );
    }

    work->target = GM_AllocTarget();
    if ( work->target != NULL )
    {
        InitTarget( work );
    }

    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->think4 = 0;
    work->count3 = 0;
    work->next_node = 0;
    work->target_pos = work->nodes[ 0 ];
    work->target_addr = HZD_GetAddress( work->control.map->hzd, &work->target_pos, -1 );
    work->target_map = GM_CurrentMap;
    work->alert_level = 0;
    work->vision.facedir = 0;
    work->vision.range = 512;
    work->vision.length = 4000;
    work->pad.sound = 0;
    work->pad.time = 0;
    work->player_pos = NoPoint;
    work->subweapon = NULL;
    work->control.mov = work->nodes[ 0 ];
    work->field_AF6 = 0;
    work->field_AF8 = 0;
    work->visible = 1;
    work->in_grip = 0;

    for ( i = 0; i < 8; i++ )
    {
        work->modetime[ i ] = 0;
    }

    work->modetime[ 7 ] = 0x17;
    work->modetime[ 4 ] = 0xFF;

    GM_ConfigControlRadarparam( &work->control, 0, 512, 4000, 0 );

    work->start_pos = work->nodes[ 0 ];
    work->start_map = GM_CurrentMap;
    work->last_addr = work->next_addr = work->start_addr =
        HZD_GetAddress( work->control.map->hzd, &work->control.mov, -1 );
    work->next_pos = work->start_pos;
}

/*---------------------------------------------------------------------------*/

void *NewZako( int name, int where )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "zako.c" );
        GetResources( work, name, where );
    }
    return (void *)work;
}
