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

// TODO: These structures should be unified with the other zakos, using stage
//       ifdefs to add or remove fields where necessary.

typedef struct _ACT {
    /* 0x8C8 */ int            field_00;
    /* 0x8CC */ short          field_04;
    /* 0x8CE */ short          field_06;
    /* 0x8D0 */ int            field_08;
    /* 0x8D4 */ SVECTOR        field_0C;
    /* 0x8DC */ int            field_14;
    /* 0x8E0 */ short          last_set;
    /* 0x8E2 */ short          last_unset;
    /* 0x8E4 */ short          field_1C;
    /* 0x8E6 */ short          field_1E;
    /* 0x8E8 */ short          field_20;
    /* 0x8EA */ short          field_22;
} ACT;

typedef struct _PARAM {
    /* 0xB74 */ signed char    index;
    /* 0xB75 */ signed char    blood;
    /* 0xB76 */ signed char    area;
    /* 0xB77 */ signed char    low_poly;
    /* 0xB78 */ char           next;   // guessed from option 'n'
    /* 0xB79 */ signed char    root;
    /* 0xB7A */ char           c_root;
    /* 0xB7B */ char           c_next; // guessed from option 'n'
    /* 0xB7C */ signed char    item;
    /* 0xB7D */ char           g_flag;
    /* 0xB7E */ short          life;
    /* 0xB80 */ short          faint;
    /* 0xB82 */ short          z_flag;
} PARAM;

typedef struct _Work {
    /* 0x000 */ GV_ACT         actor;
    /* 0x020 */ CONTROL        control;
    /* 0x09C */ OBJECT         body;
    /* 0x180 */ int            lod;
    /* 0x184 */ DG_DEF        *lod_models[ 2 ];
    /* 0x18C */ MOTION_CONTROL m_ctrl;
    /* 0x1DC */ MOTION_SEGMENT m_segs1[ 17 ];
    /* 0x440 */ MOTION_SEGMENT m_segs2[ 17 ];
    /* 0x6A4 */ SVECTOR        rots[ 16 ];
    /* 0x724 */ SVECTOR        adjust[ 16 ];
    /* 0x7A4 */ OBJECT         weapon;
    /* 0x888 */ MATRIX         light[ 2 ];
    /* 0x8C8 */ ACT            act;
    /* 0x8EC */ int            field_8EC;
    /* 0x8F0 */ int            field_8F0;
    /* 0x8F4 */ int            field_8F4;
    /* 0x8F8 */ int            field_8F8;
    /* 0x8FC */ char           pad8FC[ 0x4 ];
    /* 0x900 */ TARGET        *target;
    /* 0x904 */ TARGET         attack;
    /* 0x94C */ TARGET         touch;
    /* 0x994 */ char           pad994[ 0x48 ];
    /* 0x9DC */ HOMING        *hom;
    /* 0x9E0 */ int            scale;
    /* 0x9E4 */ int            field_9E4;
    /* 0x9E8 */ int            n_nodes;
    /* 0x9EC */ SVECTOR        nodes[ 32 ];
    /* 0xAEC */ int            search_flag;
    /* 0xAF0 */ void          *shadow;
    /* 0xAF4 */ int           *shadow_enable;
    /* 0xAF8 */ void          *glight;
    /* 0xAFC */ int           *glight_enable;
    /* 0xB00 */ void          *field_B00[ 8 ];
    /* 0xB20 */ short          think1;
    /* 0xB22 */ short          think2;
    /* 0xB24 */ short          think3;
    /* 0xB26 */ short          think4;
    /* 0xB28 */ int            count3;
    /* 0xB2C */ int            t_count;
    /* 0xB30 */ int            l_count;
    /* 0xB34 */ int            next_node;
    /* 0xB38 */ char           padB38[ 0xC ];
    /* 0xB44 */ int            field_B44;
    /* 0xB48 */ char           padB48[ 0x2 ];
    /* 0xB4A */ short          field_B4A;
    /* 0xB4C */ char           padB4C[ 0x8 ];
    /* 0xB54 */ int            field_B54;
    /* 0xB58 */ char           padB58[ 0x10 ];
    /* 0xB68 */ int            mark_time;
    /* 0xB6C */ int            act_status; // verify this
    /* 0xB70 */ char           padB70[ 0x4 ];
    /* 0xB74 */ PARAM          param;
    /* 0xB84 */ char           padB84[ 0x4 ];
    /* 0xB88 */ short          field_B88;
    /* 0xB8A */ short          field_B8A;
    /* 0xB8C */ short          field_B8C;
    /* 0xB8E */ char           padB8E[ 0x2 ];
    /* 0xB90 */ short          field_B90;
    /* 0xB92 */ char           padB92[ 0x2 ];
    /* 0xB94 */ int            alert_level;
    /* 0xB98 */ signed char    field_B98[ 8 ];
    /* 0xBA0 */ SVECTOR        field_BA0;
    /* 0xBA8 */ char           padBA8[ 0x4 ];
    /* 0xBAC */ int            time[ 8 ];
    /* 0xBCC */ short          dir[ 4 ];
    /* 0xBD4 */ int            field_BD4;
    /* 0xBD8 */ SVECTOR        field_BD8;
    /* 0xBE0 */ SVECTOR        target_pos;
    /* 0xBE8 */ int            field_BE8;
    /* 0xBEC */ int            field_BEC;
    /* 0xBE8 */ int            field_BF0;
    /* 0xBF4 */ int            target_addr;
    /* 0xBF8 */ int            target_map;
    /* 0xBFC */ int            field_BFC; // some distance flag
    /* 0xC00 */ int            field_C00; // some distance index
    /* 0xC04 */ char           padC04[ 0x8 ];
    /* 0xC0C */ int            field_C0C;
    /* 0xC10 */ int            field_C10;
    /* 0xC14 */ char           padC14[ 0x8 ];
    /* 0xC1C */ SVECTOR        field_C1C;
    /* 0xC24 */ char           padC24[ 0x14 ];
    /* 0xC38 */ int            field_C38;
    /* 0xC3C */ char           padC3C[ 0x8 ];
    /* 0xC44 */ short          field_C44;
    /* 0xC46 */ char           padC46[ 0x2 ];
} Work;

/*---------------------------------------------------------------------------*/

// rasen.c
extern int rasen_800C3404;
extern int rasen_800C3408;
extern u_short rasen_800D2CA4[];

// zk11aact.c
extern void s11a_800CE34C( Work *work, int ); // ZAKO11A_SetPutChar
extern void s11a_800CEB8C( Work *work ); // Zako11AActionMain
extern void s11a_800CEBF8( Work *work ); // Zako11APushMove

// zk11acom.c
extern SVECTOR ZAKO11A_TARGET_SIZE;
extern SVECTOR ZAKO11A_TARGET_FORCE;
extern SVECTOR ZAKO11A_ATTACK_SIZE;
extern SVECTOR ZAKO11A_ATTACK_FORCE;
extern SVECTOR ZAKO11A_TOUCH_SIZE;
extern SVECTOR ZAKO11A_TOUCH_FORCE;

extern SVECTOR ZAKO11A_NO_POINT;
extern u_short ZAKO11A_EYE_LENGTH;

extern int s11a_dword_800D8B8C;

extern int s11a_800D2010( Work *work );
extern void s11a_800D2054( int index );

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

    if ( rasen_800C3408 == 1 )
    {
        control = &work->control;
        control->map = GM_GetMap( rasen_800D2CA4[ rasen_800C3404 ] );

        if ( control->mov.vy <= 0 )
        {
            control->mov.vy = -32000;
        }
        else
        {
            control->mov.vy -= 32000;
        }

        work->field_C0C = -1;
        work->field_BF0 = -1;
        printf( "1ID[%d] %d %d %d\n", work->param.index, control->mov.vx, control->mov.vy, control->mov.vz );
    }
    else if ( rasen_800C3408 == 2 )
    {
        control = &work->control;
        control->map = GM_GetMap( rasen_800D2CA4[ rasen_800C3404 ] );

        if ( control->mov.vy < 0 )
        {
            control->mov.vy += 32000;
        }
        else
        {
            control->mov.vy = 32000;
        }

        work->field_C0C = -1;
        work->field_BF0 = -1;
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
        s11a_800CEBF8( work );

        GM_ActControl( control );
        GM_ActObject2( &work->body );
        GM_ActObject2( &work->weapon );
        DG_GetLightMatrix2( &control->mov, work->light );

         s11a_800CEB8C( work );

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
    if ( s11a_dword_800D8B8C == 16 ) GV_DestroyActor( work );
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
    GM_TargetBody( trg, &work->body.objs->objs[ 1 ].world );

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
    s11a_800D2054( work->param.index );
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

    work->param.index = s11a_800D2010( work );
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

    work->field_BFC = dist_data[ work->param.index ];
    work->field_C00 = work->param.index;

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
    work->field_B8A = 512;
    work->field_B88 = 0;
    work->field_B90 = 0;
    work->field_B4A = 0;
    work->field_B44 = 0;
    work->field_B8C = ZAKO11A_EYE_LENGTH;
    work->field_BA0 = ZAKO11A_NO_POINT;
    work->field_B54 = 0;
    work->control.mov = work->nodes[ 0 ];
    work->field_C44 = 0;
    work->param.c_root = work->param.root;
    work->param.c_next = work->param.next;

    for ( i = 0; i < 8; i++ )
    {
        work->field_B98[ i ] = 0;
    }

    work->field_B98[ 7 ] = 7;
    work->field_B98[ 4 ] = -1;

    GM_ConfigControlRadarparam( &work->control, 0, 512, ZAKO11A_EYE_LENGTH, 0 );

    work->field_BD8 = work->nodes[ 0 ];
    work->field_BEC = GM_CurrentMap;

    addr = HZD_GetAddress( work->control.map->hzd, &work->control.mov, -1 );
    work->field_BE8 = addr;
    work->field_C10 = addr;
    work->field_BF0 = addr;
    work->field_C1C = work->field_BD8;
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
