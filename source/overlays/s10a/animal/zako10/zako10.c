#include "zako10.h"

#include <stdio.h>
#include "mts/mts.h" // for fprintf
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "strcode.h"

#include "chara/snake/shadow.h" // for NewShadow2
#include "enemy/glight.h"       // for NewGunLight

extern int     ZAKO10_GameFlag;          // s10a_dword_800E4A9C
extern int     ZAKO10_EYE_LENGTH;        // 800C364C
extern SVECTOR ZAKO10_NO_POINT;          // 800C3644
extern SVECTOR ZAKO10_TARGET_SIZE;       // 800C3614
extern SVECTOR ZAKO10_TARGET_FORCE;      // 800C361C
extern SVECTOR ZAKO10_ATTACK_SIZE;       // 800C3624
extern SVECTOR ZAKO10_ATTACK_FORCE;      // 800C362C
extern SVECTOR ZAKO10_TOUCH_SIZE;        // 800C3634
extern SVECTOR ZAKO10_TOUCH_FORCE;       // 800C363C

int ZAKO10_EyeLengthTable[8] =
{
    4000, 4000, 7000, 8000, 8000, 8000, 8000, 8000
};

unsigned short ZAKO10_SetTimeDefault[8] =
{
    300, 15, 30, 60, 90, 0, 32001, 30000
};

extern void Zako10PushMove( Zako10Work *work );
extern void Zako10ActionMain( Zako10Work *work );
extern void ZAKO10_SetPutChar( Zako10Work *work, int put );
extern int  ZAKO10_GetIndex( Zako10Work *work );
extern void ZAKO10_FreeIndex( int index );

/* fade in the guard when the stage flag says so */
void Zako10RootFlagCheck( Zako10Work *work )
{
    if ( work->faseout && ZAKO10_GameFlag > 0 )
    {
        work->visible = 1;
        GM_ConfigControlAttribute( &work->control, 13 );
        work->faseout = 0;
        work->act_status = 0;
    }
}

void Zako10ChangeModel( DG_OBJS* objs, DG_DEF* def )
{
    int i;
    DG_OBJ *obj;
    DG_FreeObjsPacket( objs, 0 );
    DG_FreeObjsPacket( objs, 1 );

    objs->def = def;
    obj = objs->objs;
    for ( i = 0 ; i < 16 ; i++ )
    {
        obj->model   = &def->models[ i ];
        obj->n_packs =  def->models[ i ].n_faces;
        obj++;
    }
}

void Zako10Visibility( Zako10Work *work )
{
    if ( work->visible )
    {
        if ( work->param_low_poly == 1 )
        {
            if ( GM_GameStatus & STATE_CAM_CHANGE || GM_Camera.first_person )
            {
                if ( work->has_kmd != work->param_low_poly )
                {
                    work->has_kmd = work->param_low_poly;
                    Zako10ChangeModel( work->body.objs, work->def );
                }
            }
            else if ( work->has_kmd )
            {
                work->has_kmd = 0;
                Zako10ChangeModel( work->body.objs, work->kmd );
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

void Zako10Act( Zako10Work *work )
{
    VECTOR   vec;
    TARGET  *trgt;
    CONTROL *ctrl;
    TARGET  *trgt2;

    ctrl = &( work->control ) ;
    if (GM_CheckMessage( &( work->actor ) , ctrl->name, HASH_KILL ) )
    {
        GV_DestroyActor( &( work->actor ) );
        return;
    }

    Zako10RootFlagCheck( work );
    if ( !work->faseout )
    {
        Zako10PushMove( work );
        GM_ActControl( ctrl );
        GM_ActObject2( &( work->body ) );
        GM_ActObject2( &( work->weapon ) );

        DG_GetLightMatrix2( &( ctrl->mov ), work->light );

        Zako10ActionMain( work );
        trgt = work->target;
        GM_MoveTarget( trgt, &( ctrl->mov ) );

        GM_PushTarget( trgt );

        if ( trgt->class & TARGET_TOUCH )
        {
            trgt2 = &work->field_94C;
            if ( trgt2->class & TARGET_TOUCH )
            {
                if ( trgt2->damaged & TARGET_TOUCH )
                {
                    trgt2->damaged &= ~TARGET_TOUCH;
                }
                GM_MoveTarget( &( work->field_94C ), &( ctrl->mov ) );
                GM_TouchTarget( &( work->field_94C ) );
            }
        }

        vec.vx = vec.vy = vec.vz = work->scale;
        ScaleMatrix( &( work->body.objs->world ), &vec );
    }

    Zako10Visibility( work );
}

void Zako10InitTarget( Zako10Work *work )
{
    TARGET *target;
    TARGET *target2;
    int life;
    int faint;

    target = work->target;
    life   = work->param_life;
    faint  = work->param_faint;

    GM_SetTarget( target, TARGET_FLAG, ENEMY_SIDE, &ZAKO10_TARGET_SIZE );
    GM_SetPowerTarget( target, POWER_DECREASE, -1, life, faint, &ZAKO10_TARGET_FORCE );
    GM_SetCaptureTarget( target, -1, faint, NULL, NULL);

    GM_SetC4Target( target, &( work->body.objs->objs[1].world ) );

    target2 = &work->field_904;
    GM_SetTarget( target2, TARGET_POWER, PLAYER_SIDE, &ZAKO10_ATTACK_SIZE );
    GM_SetPowerTarget( target2, POWER_CONST | POWER_EXPLODE, 5, 0, 3, &ZAKO10_ATTACK_FORCE );

    target2 = &work->field_94C;
    GM_SetTarget( target2, ( TARGET_TOUCH ), ENEMY_SIDE, &ZAKO10_TOUCH_SIZE );
    GM_SetPowerTarget( target2, POWER_CONST | POWER_EXPLODE, 5, 0, 0, &ZAKO10_TOUCH_FORCE );
}

void Zako10InitAction( Zako10Work* work )
{
    WatcherUnk *s;
    s = &work->unknown;

    GV_ZeroMemory(s, 0x24);
    s->field_00 = 0;
    s->field_1C = 450;
    s->field_1E = 1;

    work->action = 0;
    work->action2 = 0;
    work->time = 0;
    work->time2 = 0;
}

int Zako10InitObjects( Zako10Work* work, int name, int where )
{
    int i;
    int has_kmd;
    char *opt, *opt2;
    CONTROL *ctrl;
    OBJECT  *body;
    OBJECT  *arm;
    SVECTOR  shadow;

    ctrl = &work->control;
    if ( GM_InitControl( ctrl, name, where ) < 0 ) return -1;

    opt = GCL_GetOption( 'p' );

    GM_ConfigControlString( ctrl, (char*)opt, (char*)GCL_GetOption( 'd' ) ) ;
    GM_ConfigControlAttribute( ctrl, 13 );
    GM_ConfigControlInterp( ctrl, 4 );

    ctrl->seg_flag = 2;

    GM_ConfigControlTrapCheck( ctrl );

    body  = &work->body;
    arm = &work->weapon;

    GM_InitObject( body, KMD_IPPANHEI, 0x32D, OAR_ENEMY ) ;
    GM_ConfigObjectJoint( body ) ;
    GM_ConfigMotionControl( body, &work->m_ctrl, OAR_ENEMY, work->m_segs1, work->m_segs2, ctrl, work->rots );
    GM_ConfigObjectLight( body, work->light );

    work->param_low_poly = 0;

    opt2 = GCL_GetOption( 'y' );
    if ( opt2 ) {
        work->param_low_poly = GCL_StrToInt( (char*)opt2 );
    }

    has_kmd = work->param_low_poly;
    if ( has_kmd == 1 )
    {
        work->def = body->objs->def;
        work->kmd = GV_GetCache( GV_CacheID( KMD_LOPRYHEI, 'k' ) );
        work->has_kmd = has_kmd;
    }

    work->hom = GM_SetHomingTarget( &body->objs->objs[6].world, ctrl );
    GM_InitObject( arm, KMD_FAMAS, 0x6D, 0 );
    GM_ConfigObjectLight( arm, work->light ) ;
    GM_ConfigObjectRoot( arm, body, 4 );

    for ( i = 0 ; i < 0 ; i++ )
    {
        work->field_B00[i] = 0;
    }
    shadow.vy  = 6;
    shadow.vz  = 12;
    shadow.pad = 15;
    shadow.vx  = 0;

    work->shadow = NewShadow2( ctrl, body, shadow,  &work->shadow_enable ) ;
    work->glight = NewGunLight( &( body->objs->objs[4].world ), &work->glight_enable ) ;

    ZAKO10_SetPutChar( work, 0 );
    Zako10InitAction( work );

    return 0;
}

void Zako10Free( Zako10Work* work )
{
    ZAKO10_FreeIndex( work->field_B74 );
    GM_FreeControl( &( work->control ) );
    GM_FreeObject( &( work->body ) );
    GM_FreeObject( &( work->weapon ) );
    GM_FreeTarget( work->target );
    GV_DestroyActor( work->glight );
    GV_DestroyActor( work->shadow );
    GM_ResetHomingTarget( work->hom );
}

void Zako10Die( Zako10Work* work )
{
    Zako10Free( work );
}

int Zako10ReadNodes( Zako10Work* work )
{
    int i;
    HZD_PAT *patrol;
    HZD_PTP *points;

    patrol = work->control.map->hzd->def->routes;
    patrol = &patrol[ work->param_root ];

    work->n_nodes = patrol->n_points;

    if ( work->n_nodes <= 0 ) return -1;

    points = patrol->points;
    for ( i = 0 ; i < work->n_nodes ; i++ )
    {
        work->nodes[i].vx = points->x;
        work->nodes[i].vy = points->y;
        work->nodes[i].vz = points->z;
        work->nodes[i].pad = points->command;
        points++;
    }
    return 0;
}

int Zako10GetShorts( char *opt, short* s )
{
    int i;
    unsigned char *res;

    for ( i = 0 ; ( res = GCL_NextStr() ) ; i++ )
    {
        *s = GCL_StrToInt( res );
         s++;
    }

    return i;
}

int Zako10GetInts( char *opt, int* l )
{
    int i;
    unsigned char *res;

    for ( i = 0 ; ( res = GCL_NextStr() ) ; i++ )
    {
        *l = GCL_StrToInt( res );
         l++;
    }

    return i;
}

int Zako10ReadSetTimes( Zako10Work *work )
{
    int i;
    char *opt;
    int ret;

    for ( i = 0 ; i < 8 ; i++ )
    {
        work->field_BAC[i] = ZAKO10_SetTimeDefault[i];
    }

    opt = GCL_GetOption( 't' );
    if ( opt )
    {
        ret = Zako10GetInts( opt, &work->field_BAC[1] );
        if ( ret > 4 )
        {
            printf( "Err Err Err  Set time Over\n" ) ;
            return -1;
        }
    }

    for ( i = 0 ; i < 4 ; i++ )
    {
        work->field_BCC[i] = i * 1024;
    }

    opt = GCL_GetOption( 'i' );

    if ( opt )
    {
        ret = Zako10GetShorts( opt, work->field_BCC );
        if ( ret > 4 )
        {
            printf( "Err Err Err  Set Dir Over\n" ) ;
            return -1;
        }
    }

    return 0;
}

void Zako10GetResources( Zako10Work *work, int name, int where )
{
    int addr;
    char *opt;
    int i;

    Zako10InitObjects( work, name, where ) ;
    work->field_B74 = ZAKO10_GetIndex( work ) ;

    if ( work->field_B74  << 24 < 0  )
    {
       printf( "Err not enough work !!\n" ) ;
    }

    Zako10ReadSetTimes( work ) ;

    //root
    work->param_root = 0;
    opt = GCL_GetOption( 'r' );
    if ( opt )
    {
        work->param_root = GCL_StrToInt( ( char* )opt );
    }

    //life
    work->param_life = 192;
    opt = GCL_GetOption( 'l' );
    if ( opt )
    {
        work->param_life = GCL_StrToInt( ( char* )opt );
    }

    //faint
    work->param_faint = 7;
    opt = GCL_GetOption( 'f' );
    if ( opt )
    {
        work->param_faint = GCL_StrToInt( ( char* )opt );
    }

    work->param_blood = 65;
    opt = GCL_GetOption( 'b' );
    if ( opt )
    {
        work->param_blood = GCL_StrToInt( ( char* )opt );
    }

    printf( " low[pory=%d\n", work->param_low_poly ) ;
    work->field_B7D = 0xFF;

    opt = GCL_GetOption('g');
    if ( opt )
    {
        work->field_B7D = GCL_StrToInt( ( char* )opt );
    }
    if ( work->param_blood == 'Z' )
    {
        work->field_B7D = 0;
    }

    work->field_BF8 = ZAKO10_EyeLengthTable[ work->field_B74 ];
    work->field_BFC = work->field_B74;
    work->field_B78 = 0xFF;

    opt = GCL_GetOption( 'n' );
    if ( opt )
    {
        work->field_B78 = GCL_StrToInt( ( char* )opt );
    }

    work->param_area = 'A';
    opt = GCL_GetOption( 'a' );
    if (opt != 0)
    {
        work->param_area = GCL_StrToInt( ( char* )opt );
    }

    if ( work->param_area == 'S' ) ZAKO10_SetPutChar( work, PUTBREATH ) ; /* 白い息はく */
    work->scale = 4096 ;            /* スケール */

    if ( ( opt = GCL_GetOption( 's' ) ) != NULL ) work->scale += GCL_StrToInt( ( char* )opt );
    work->param_item = 1;

    if( Zako10ReadNodes( work ) < 0 ) fprintf( 1, "watchar.c : action point Err\n" );

    /*
        当たりデータを初期化する
    */
    if( ( work->target =  GM_AllocTarget() ) != NULL ) Zako10InitTarget( work ) ;

    /*
        思考ルーチン用データを初期化する
    */
    work->think1 = 0 ;
    work->think2 = 0 ;
    work->think3 = 0 ;
    work->think4 = 0 ;
    work->count3 = 0 ;
    work->l_count = 0 ;
    work->t_count = 0 ;
    work->mark_time = 0 ;
    work->next_node = 0 ;
    work->search_flag = 0 ;
    work->act_status = 0 ;
    work->target_pos = work->nodes[ 0 ] ;
    work->target_addr = HZD_GetAddress( work->control.map->hzd, &( work->target_pos ), -1 ) ;
    work->target_map  = GM_CurrentMap;
    work->alert_level = 0;
    work->visible = 1;
    work->vision.angle = 0x200;
    work->vision.facedir = 0;
    work->field_B90 = 0;
    work->pad.sound = 0;
    work->pad.time  = 0;
    work->vision.length = ZAKO10_EYE_LENGTH;
    work->field_BA0 = ZAKO10_NO_POINT;
    work->subweapon = NULL;

    work->control.mov = work->nodes[ 0 ] ;
    work->param_c_root = 0;
    work->field_B7B = work->field_B78;

    for ( i = 0 ; i <= 7 ; i++ )
    {
        work->modetime[i] = 0;
    }

    work->modetime[4] = -1;
    work->modetime[7] = 0;

    GM_ConfigControlRadarparam( &work->control , 0, 0x200, ZAKO10_EYE_LENGTH, 0 );
    work->start_pos = work->nodes[ 0 ] ;
    work->start_map = GM_CurrentMap;
    addr = HZD_GetAddress( work->control.map->hzd, &( work->control.mov ), -1 );

    work->start_addr = addr;
    work->field_C0C  = addr;
    work->field_BEC  = addr;

    work->field_C18 = work->start_pos;

    /* start faded out, Zako10RootFlagCheck brings the guard in */
    work->hom->flag = 0;
    work->alert_level = 0;
    GM_ConfigControlAttribute( &work->control, 0 );
    work->visible = 0;
    work->target->class = TARGET_AVAIL;
    work->faseout = 1;
    work->act_status = EN_FASEOUT;
}

void *NewZako10( int name, int where, int argc, char **argv )
{
    Zako10Work *work ;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof( Zako10Work ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor( &( work->actor ), Zako10Act, Zako10Die, "zako10.c" );
        Zako10GetResources( work, name, where );
    }
    return (void *)work ;
}
