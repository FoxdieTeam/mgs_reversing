// (VR only) this file is empty in the main executable build
#ifdef VR_EXE
#include "godzila.h"

#include <stdio.h>
#include "mts/mts.h" // for fprintf
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "strcode.h"

#include "chara/snake/shadow.h" // for NewShadow2
#include "enemy/glight.h"       // for NewGunLight

extern GODZ_COMMAND GodzCommand;
extern int     GODZ_EYE_LENGTH;
extern SVECTOR GODZ_NO_POINT;
extern SVECTOR GODZ_TARGET_SIZE;
extern SVECTOR GODZ_TARGET_FORCE;
extern SVECTOR GODZ_ATTACK_SIZE;
extern SVECTOR GODZ_ATTACK_FORCE;
extern SVECTOR GODZ_TOUCH_SIZE;
extern SVECTOR GODZ_TOUCH_FORCE;

// eye length of the soldiers, indexed by the watcher index
int GodzEyeLengthTable[8] =
{
    4000, 4000, 7000, 8000, 8000, 8000, 8000, 8000
};

unsigned short GodzSetTimeDefault[8] =
{
    300, 15, 30, 60, 90, 0, 32001, 30000
};

extern void GodzPushMove( GodzWork *work );
extern void GodzActionMain( GodzWork *work );
extern void GODZ_SetPutChar( GodzWork *work, int put );
extern int  GODZ_GetIndex( GodzWork *work );
extern void GODZ_FreeIndex( int index );

// Modified version of the meryl7 root flag check: handles the stage messages
int GodzCheckMessages( GodzWork *work )
{
    int count;
    GV_MSG *msg;
    SVECTOR svec;
    CONTROL *ctrl;

    ctrl = &work->control;
    ctrl->n_msg = GV_ReceiveMessage( ctrl->name, &work->control.msg );
    count = ctrl->n_msg;
    msg = ctrl->msg;

    if ( count <= 0 ) return 0 ;

    for ( ; count > 0 ; --count, msg++ )
    {
        switch ( msg->message[0] )
        {
        case 0x430F:
            work->param.c_root = msg->message[1];
            svec.vx = msg->message[2];
            svec.vy = msg->message[3];
            svec.vz = msg->message[4];

            if ( svec.vy < 0x7530 )
            {
                work->param.field_B7C = HZD_GetAddress( work->control.map->hzd, &svec, -1 );
            }
            else
            {
                work->param.field_B7C = -1;
            }
            return 1;
        case 0xF1BD:
            work->hom->flag = FALSE ;
            work->alert_level = 0 ;
            GM_ConfigControlAttribute( &(work->control), 0 ) ;
            work->visible = 0 ;
            work->targets[0]->class = TARGET_AVAIL;

            work->faseout = 1 ;
            work->act_status = EN_FASEOUT ;
            break;
        case 0x1DC4:
            if ( GodzCommand.watchers[ work->param.index ].field_04 == 2 )
            {
                work->visible = 1;
            }
            GM_ConfigControlAttribute( ctrl, 13 );
            work->faseout = 0;
            work->act_status = 0;
            break;
        }
    }
    return 0;
}

void GodzRootFlagCheck( GodzWork *work )
{
    GodzCheckMessages( work );
}

void GodzChangeModel( DG_OBJS* objs, DG_DEF* def )
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

void GodzVisibility( GodzWork *work )
{
    if ( work->visible )
    {
        if ( work->param.low_poly == 1 )
        {
            if ( GM_GameStatus & STATE_CAM_CHANGE || GM_Camera.first_person )
            {
                if ( work->has_kmd != work->param.low_poly )
                {
                    work->has_kmd = work->param.low_poly;
                    GodzChangeModel( work->body.objs, work->def );
                }
            }
            else if ( work->has_kmd )
            {
                work->has_kmd = 0;
                GodzChangeModel( work->body.objs, work->kmd );
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

// Moves the main target and the four body part hit boxes
void GodzMoveTargets( GodzWork *work )
{
    SVECTOR pos;
    TARGET *trgt;

    trgt = work->targets[ 0 ];
    GM_MoveTarget( trgt, &work->control.mov );
    GM_PushTarget( trgt );

    trgt = work->targets[ 1 ];
    pos.vx = work->body.objs->objs[ 1 ].world.t[ 0 ];
    pos.vy = work->body.objs->objs[ 1 ].world.t[ 1 ];
    pos.vz = work->body.objs->objs[ 1 ].world.t[ 2 ];
    GM_MoveTarget( trgt, &pos );
    trgt = work->targets[ 2 ];
    pos.vx = work->body.objs->objs[ 6 ].world.t[ 0 ];
    pos.vy = work->body.objs->objs[ 6 ].world.t[ 1 ];
    pos.vz = work->body.objs->objs[ 6 ].world.t[ 2 ];
    GM_MoveTarget( trgt, &pos );
    trgt = work->targets[ 3 ];
    pos.vx = work->body.objs->objs[ 11 ].world.t[ 0 ];
    pos.vy = work->body.objs->objs[ 11 ].world.t[ 1 ];
    pos.vz = work->body.objs->objs[ 11 ].world.t[ 2 ];
    GM_MoveTarget( trgt, &pos );
    trgt = work->targets[ 4 ];
    pos.vx = work->body.objs->objs[ 14 ].world.t[ 0 ];
    pos.vy = work->body.objs->objs[ 14 ].world.t[ 1 ];
    pos.vz = work->body.objs->objs[ 14 ].world.t[ 2 ];
    GM_MoveTarget( trgt, &pos );
}

void GodzAct( GodzWork *work )
{
    VECTOR   vec;
    CONTROL *ctrl;
    TARGET  *trgt2;

    ctrl = &( work->control ) ;
    if (GM_CheckMessage( &( work->actor ) , ctrl->name, HASH_KILL ) )
    {
        GV_DestroyActor(work);
        return;
    }

    GodzRootFlagCheck( work );
    if ( !work->faseout )
    {
        GodzPushMove( work );
        GM_ActControl( ctrl );
        GM_ActObject2( &( work->body ) );
        GM_ActObject2( &( work->weapon ) );

        DG_GetLightMatrix2( &( ctrl->mov ), work->light );

        GodzActionMain( work );
        GodzMoveTargets( work );

        if ( work->targets[0]->class & TARGET_TOUCH )
        {
            trgt2 = &work->field_95C;
            if ( trgt2->class & TARGET_TOUCH )
            {
                if ( trgt2->damaged & TARGET_TOUCH )
                {
                    trgt2->damaged &= ~TARGET_TOUCH;
                }
                GM_MoveTarget( &( work->field_95C ), &( ctrl->mov ) );
                GM_TouchTarget( &( work->field_95C ) );
            }
        }

        vec.vx = vec.vy = vec.vz = work->scale;
        ScaleMatrix( &( work->body.objs->world ), &vec );
    }

    GodzVisibility( work );
}

void GodzInitTarget( GodzWork *work )
{
    TARGET *target;
    TARGET *target2;
    int life;
    int faint;
    int i;

    life   = work->param.life;
    faint  = work->param.faint;

    for ( i = 0 ; i < 5 ; i++ )
    {
        target = GM_AllocTarget();
        work->targets[i] = target;

        GM_SetTarget( target, TARGET_FLAG, ENEMY_SIDE, &GODZ_TARGET_SIZE );
        GM_SetPowerTarget( target, POWER_DECREASE, -1, life, faint, &GODZ_TARGET_FORCE );
        GM_SetCaptureTarget( target, -1, faint, NULL, NULL);

        GM_SetC4Target( target, &( work->body.objs->objs[1].world ) );
    }

    target2 = &work->field_914;
    GM_SetTarget( target2, TARGET_POWER, PLAYER_SIDE, &GODZ_ATTACK_SIZE );
    GM_SetPowerTarget( target2, POWER_CONST | POWER_EXPLODE, 5, 0, 3, &GODZ_ATTACK_FORCE );

    target2 = &work->field_95C;
    GM_SetTarget( target2, ( TARGET_TOUCH ), ENEMY_SIDE, &GODZ_TOUCH_SIZE );
    GM_SetPowerTarget( target2, POWER_CONST | POWER_EXPLODE, 5, 0, 0, &GODZ_TOUCH_FORCE );
}

void GodzInitAction( GodzWork* work )
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

int GodzInitObjects( GodzWork* work, int name, int where )
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
    GM_ConfigControlInterp( ctrl, 8 );

    ctrl->seg_flag = 2;

    GM_ConfigControlTrapCheck( ctrl );

    body  = &work->body;
    arm = &work->weapon;

    GM_InitObject( body, KMD_IPPANHEI, 0x32D, OAR_GODZ ) ;
    GM_ConfigObjectJoint( body ) ;
    GM_ConfigMotionControl( body, &work->m_ctrl, OAR_GODZ, work->m_segs1, work->m_segs2, ctrl, work->rots );
    GM_ConfigObjectLight( body, work->light );

    work->param.low_poly = 0;

    opt2 = GCL_GetOption( 'y' );
    if ( opt2 ) {
        work->param.low_poly = GCL_StrToInt( (char*)opt2 );
    }

    has_kmd = work->param.low_poly;
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
        work->field_B10[i] = 0;
    }
    shadow.vy  = 6;
    shadow.vz  = 12;
    shadow.pad = 15;
    shadow.vx  = 0;

    work->shadow = NewShadow2( ctrl, body, shadow,  &work->shadow_enable ) ;
    work->glight = NewGunLight( &( body->objs->objs[4].world ), &work->glight_enable ) ;

    GODZ_SetPutChar( work, 0 );
    GodzInitAction( work );

    return 0;
}

void GodzFree( GodzWork* work )
{
    int i;

    GODZ_FreeIndex( work->param.index );
    GM_FreeControl( &( work->control ) );
    GM_FreeObject( &( work->body ) );
    GM_FreeObject( &( work->weapon ) );
    for ( i = 0 ; i < 5 ; i++ )
    {
        GM_FreeTarget( work->targets[i] );
    }
    GV_DestroyActor( work->glight );
    GV_DestroyActor( work->shadow );
    GM_ResetHomingTarget( work->hom );
}

void GodzDie( GodzWork* work )
{
    GodzFree( work );
}

int GodzReadNodes( GodzWork* work )
{
    int i;
    HZD_PAT *patrol;
    HZD_PTP *points;

    patrol = work->control.map->hzd->def->routes;
    patrol = &patrol[ work->param.root ];

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

int GodzGetBytes( char *opt, signed char* c )
{
    int i;
    unsigned char *res;

    for ( i = 0 ; ( res = GCL_NextStr() ) ; i++ )
    {
        *c = GCL_StrToInt( res );
         c++;
    }

    return i;
}

int GodzGetShorts( char *opt, short* s )
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

int GodzGetInts( char *opt, int* l )
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

int GodzReadSetTimes( GodzWork *work )
{
    int i;
    char *opt;
    int ret;

    for ( i = 0 ; i < 8 ; i++ )
    {
        work->field_BBC[i] = GodzSetTimeDefault[i];
    }

    opt = GCL_GetOption( 't' );
    if ( opt )
    {
        ret = GodzGetInts( opt, &work->field_BBC[1] );
        if ( ret > 4 )
        {
            printf( "Err Err Err  Set time Over\n" ) ;
            return -1;
        }
    }

    for ( i = 0 ; i < 4 ; i++ )
    {
        work->field_BDC[i] = i * 1024;
    }

    opt = GCL_GetOption( 'i' );

    if ( opt )
    {
        ret = GodzGetShorts( opt, work->field_BDC );
        if ( ret > 4 )
        {
            printf( "Err Err Err  Set Dir Over\n" ) ;
            return -1;
        }
    }

    return 0;
}

void GodzGetResources( GodzWork *work, int name, int where )
{
    SVECTOR svec;
    int addr;
    char *opt;
    int i;

    GodzInitObjects( work, name, where ) ;
    work->param.index = GODZ_GetIndex( work ) ;

    if ( work->param.index  << 24 < 0  )
    {
       printf( "Err not enough work !!\n" ) ;
    }

    GodzReadSetTimes( work ) ;

    //root
    work->param.root = 0;
    opt = GCL_GetOption( 'r' );
    if ( opt )
    {
        work->param.root = GCL_StrToInt( ( char* )opt );
    }

    //life
    work->param.life = 192;
    opt = GCL_GetOption( 'l' );
    if ( opt )
    {
        work->param.life = GCL_StrToInt( ( char* )opt );
    }

    //faint
    work->param.faint = 7;
    opt = GCL_GetOption( 'f' );
    if ( opt )
    {
        work->param.faint = GCL_StrToInt( ( char* )opt );
    }

    work->param.blood = 65;
    opt = GCL_GetOption( 'b' );
    if ( opt )
    {
        work->param.blood = GCL_StrToInt( ( char* )opt );
    }

    work->param.field_B81 = 0xFF;

    opt = GCL_GetOption('g');
    if ( opt )
    {
        work->param.field_B81 = GCL_StrToInt( ( char* )opt );
    }
    if ( work->param.blood == 'Z' )
    {
        work->param.field_B81 = 0;
    }

    opt = GCL_GetOption( 'e' );
    if ( opt )
    {
        work->field_C4C = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        work->field_C4C = -1;
    }

    work->field_C08 = GodzEyeLengthTable[ work->param.index ];
    work->field_C0C = work->param.index;
    work->param.field_B7C = 0xFF;

    opt = GCL_GetOption( 'n' );
    if ( opt )
    {
        GCL_StrToSV( ( char* )opt, (short *)&svec );
        if ( svec.vy < 0x7530 )
        {
            work->param.field_B7C = HZD_GetAddress( work->control.map->hzd, &svec, -1 );
        }
        else
        {
            work->param.field_B7C = 0xFF;
        }
    }

    work->param.area = 'A';
    opt = GCL_GetOption( 'a' );
    if (opt != 0)
    {
        work->param.area = GCL_StrToInt( ( char* )opt );
    }

    if ( work->param.area == 'S' ) GODZ_SetPutChar( work, PUTBREATH ) ; /* 白い息はく */
    work->scale = 4096 ;            /* スケール */

    if ( ( opt = GCL_GetOption( 's' ) ) != NULL ) work->scale += GCL_StrToInt( ( char* )opt );
    work->param.item = 1;

    if( GodzReadNodes( work ) < 0 ) fprintf( 1, "watchar.c : action point Err\n" );

    /*
        当たりデータを初期化する
    */
    GodzInitTarget( work ) ;

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
    work->field_BA0 = 0;
    work->pad.sound = 0;
    work->pad.time  = 0;
    work->vision.length = GODZ_EYE_LENGTH;
    work->field_BB0 = GODZ_NO_POINT;
    work->subweapon = NULL;

    work->control.mov = work->nodes[ 0 ] ;
    work->faseout = 0;
    work->param.c_root = work->param.root;
    work->param.field_B7F = work->param.field_B7C;

    for ( i = 0 ; i <= 7 ; i++ )
    {
        work->modetime[i] = 0;
    }

    work->modetime[7] = 4;
    work->modetime[4] = -1;

    GM_ConfigControlRadarparam( &work->control , 0, 0x200, GODZ_EYE_LENGTH, 0 );
    work->start_pos = work->nodes[ 0 ] ;
    work->start_map = GM_CurrentMap;
    addr = HZD_GetAddress( work->control.map->hzd, &( work->control.mov ), -1 );

    work->start_addr = addr;
    work->field_C1C  = addr;
    work->field_BFC  = addr;

    work->field_C28 = work->start_pos;
}

void *NewGodz( int name, int where, int argc, char **argv )
{
    GodzWork *work ;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof( GodzWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor( &( work->actor ), GodzAct, GodzDie, "godzila.c" );
        GodzGetResources( work, name, where );
    }
    return (void *)work ;
}
#endif
