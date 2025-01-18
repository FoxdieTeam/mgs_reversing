#include "../../../s00a/Enemy/enemy.h"
#include <stdio.h>
#include "mts/mts.h" // for fprintf
#include "chara/snake/shadow.h"

void RootFlagCheck_800C86F0( Zako11FWork *work )
{
    /* do nothing */
}

void s11i_zako11f_800C86F8( DG_OBJS* objs, DG_DEF* def )
{
    int i;
    DG_OBJ *obj;
    DG_FreeObjsPacket( objs, 0 );
    DG_FreeObjsPacket( objs, 1 );

    objs->def = def;
    obj = objs->objs;
    for ( i = 0 ; i < 16 ; i++ )
    {
        obj->model   = &def->model[ i ];
        obj->n_packs =  def->model[ i ].n_faces;
        obj++;
    }
}

extern GM_Camera GM_Camera_800B77E8;
extern int GM_PlayerMap_800ABA0C;

void s11i_zako11f_800C8774( Zako11FWork *work )
{
    if ( work->visible )
    {
        if ( work->param.low_poly == 1 )
        {
            if ( GM_GameStatus & (GAME_FLAG_BIT_07 | STATE_BEHIND_CAMERA) || GM_Camera_800B77E8.first_person )
            {
                if ( work->has_kmd != work->param.low_poly )
                {
                    work->has_kmd = work->param.low_poly;
                    s11i_zako11f_800C86F8( work->body.objs, work->def );
                }
            }
            else if ( work->has_kmd )
            {
                work->has_kmd = 0;
                s11i_zako11f_800C86F8( work->body.objs, work->kmd );
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

extern int ZAKO11F_GameFlag_800D5C4C;
extern ZAKO11F_COMMAND Zako11FCommand_800D5AF8;

extern void Zako11FPushMove_800CDFAC( Zako11FWork *work );
extern void Zako11FActionMain_800CDF40( Zako11FWork *work );

void ZAKO11FAct_800C88AC( Zako11FWork *work )
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

    RootFlagCheck_800C86F0( work );
    if ( !work->faseout )
    {
        Zako11FPushMove_800CDFAC( work );
        GM_ActControl( ctrl );
        GM_ActObject2( &( work->body ) );
        GM_ActObject2( &( work->weapon ) );

        DG_GetLightMatrix2( &( ctrl->mov ), work->light );

        Zako11FActionMain_800CDF40( work );
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

    s11i_zako11f_800C8774( work );

    if ( ZAKO11F_GameFlag_800D5C4C == 0xF && Zako11FCommand_800D5AF8.watchers[work->param.index].field_04 == 1 )
    {
         GV_DestroyActor( &( work->actor ) );
    }
}

extern SVECTOR ZAKO11F_TARGET_SIZE_800C365C;
extern SVECTOR ZAKO11F_TARGET_FORCE_800C3664;
extern SVECTOR ZAKO11F_ATTACK_SIZE_800C366C;
extern SVECTOR ZAKO11F_ATTACK_FORCE_800C3674;
extern SVECTOR ZAKO11F_TOUCH_SIZE_800C367C;
extern SVECTOR ZAKO11F_TOUCH_FORCE_800C3684;
extern SVECTOR ZAKO11F_NO_POINT_800C368C;

extern int ZAKO11F_EYE_LENGTH_800C3694;

void InitTarget_800C8A10( Zako11FWork *work )
{
    TARGET *target;
    TARGET *target2;
    int life;
    int faint;

    target = work->target;
    life   = work->param.life;
    faint  = work->param.faint;

    GM_SetTarget( target, ( TARGET_FLAG | TARGET_AVAIL ), ENEMY_SIDE, &ZAKO11F_TARGET_SIZE_800C365C );
    GM_Target_8002DCCC( target, 1, -1, life, faint, &ZAKO11F_TARGET_FORCE_800C3664 );
    GM_Target_8002DCB4( target, -1, faint, NULL, NULL);

    sub_8002DD14( target, &( work->body.objs->objs[1].world ) );

    target2 = &work->field_904;
    GM_SetTarget( target2, TARGET_POWER, PLAYER_SIDE, &ZAKO11F_ATTACK_SIZE_800C366C );
    GM_Target_8002DCCC( target2, 7, 5, 0, 3, &ZAKO11F_ATTACK_FORCE_800C3674 );

    target2 = &work->field_94C;
    GM_SetTarget( target2, ( TARGET_TOUCH ), ENEMY_SIDE, &ZAKO11F_TOUCH_SIZE_800C367C );
    GM_Target_8002DCCC( target2, 7, 5, 0, 0, &ZAKO11F_TOUCH_FORCE_800C3684 );
}

void s11i_zako11f_800C8B3C( Zako11FWork* work )
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

extern void *NewGunLight_800D3AD4( MATRIX* mat, int **enable );

extern GV_ACT *NewKogaku2(CONTROL *pCtrl, OBJECT *pObj, int unit);
extern void ZAKO11F_SetPutChar_800CD700( Zako11FWork *work, int put );

int s11i_zako11f_800C8B98( Zako11FWork* work, int name, int where )
{
    int i;
    int has_kmd;
    char *opt, *opt2;
    CONTROL *ctrl;
    OBJECT  *body;
    OBJECT  *arm; //?
    SVECTOR  shadow;

    ctrl = &work->control;
    if ( GM_InitControl( ctrl, name, where ) < 0 ) return -1;

    opt = GCL_GetOption( 'p' );

    GM_ConfigControlString( ctrl, (char*)opt, (char*)GCL_GetOption( 'd' ) ) ;
    GM_ConfigControlAttribute( ctrl, 13 );
    GM_ConfigControlInterp( ctrl, 4 );

    ctrl->field_59 = 2;

    GM_ConfigControlTrapCheck( ctrl );

    body  = &work->body;
    arm = &work->weapon;

    GM_InitObject( body, KMD_IPPANHEI, 0x32D, 0xA8A1 ) ;
    GM_ConfigObjectJoint( body ) ;
    GM_ConfigMotionControl( body, &work->m_ctrl, 0xA8A1, work->m_segs1, work->m_segs2, ctrl, work->rots );
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
        work->kmd = GV_GetCache( GV_CacheID( HASH_LOPRYHEI, 'k' ) );
        work->has_kmd = has_kmd;
    }

    work->hom = GM_AllocHomingTarget( &body->objs->objs[6].world, ctrl );
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

    work->shadow = NewShadow2_80060384( ctrl, body, shadow,  &work->shadow_enable ) ;
    work->glight = NewGunLight_800D3AD4( &( body->objs->objs[4].world ), &work->glight_enable ) ;

    ZAKO11F_SetPutChar_800CD700( work, 0 );
    s11i_zako11f_800C8B3C( work );

    return 0;
}

extern void s11i_zk11fcom_800D0C38( int );

void s11i_zako11f_800C8DB8( Zako11FWork* work )
{
    s11i_zk11fcom_800D0C38( work->param.index );
    GM_FreeControl( &( work->control ) );
    GM_FreeObject( &( work->body ) );
    GM_FreeObject( &( work->weapon ) );
    GM_FreeTarget( work->target );
    GV_DestroyActor( work->glight );
    GV_DestroyActor( work->shadow );
    GM_FreeHomingTarget( work->hom );
}

void ZAKO11FDie_800C8E2C( Zako11FWork* work )
{
    s11i_zako11f_800C8DB8( work );
}

int ReadNodes_800C8E4C( Zako11FWork* work )
{
    int i;
    HZD_PAT *patrol;
    HZD_PTP *points;

    patrol = work->control.map->hzd->header->routes;
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

int s11i_zako11f_800C8EE8( char *opt, short* s )
{
    int i;
    unsigned char *res;

    for ( i = 0 ; ( res = GCL_GetParamResult() ) ; i++ )
    {
        *s = GCL_StrToInt( res );
         s++;
    }

    return i;
}

int s11i_zako11f_800C8F40( char *opt, int* l )
{
    int i;
    unsigned char *res;

    for ( i = 0 ; ( res = GCL_GetParamResult() ) ; i++ )
    {
        *l = GCL_StrToInt( res );
         l++;
    }

    return i;
}

int s11i_dword_800C32F0[8] =
{
    3000, 4000, 4000, 8000, 8000, 8000, 8000, 8000
};

unsigned short s11i_dword_800C3310[8] =
{
    300, 15, 30, 60, 90, 0, 32001, 30000
};

int s11i_zako11f_800C8F98( Zako11FWork *work )
{
    int i;
    char *opt;
    int ret;

    for ( i = 0 ; i < 8 ; i++ )
    {
        work->field_BB0[i] = s11i_dword_800C3310[i];
    }

    opt = GCL_GetOption( 't' );
    if ( opt )
    {
        ret = s11i_zako11f_800C8F40( opt, &work->field_BB0[1] );
        if ( ret > 4 )
        {
            printf( "Err Err Err  Set time Over\n" ) ;
            return -1;
        }
    }

    for ( i = 0 ; i < 4 ; i++ )
    {
        work->field_BD0[i] = i * 1024;
    }

    opt = GCL_GetOption( 'i' );

    if ( opt )
    {
        ret = s11i_zako11f_800C8EE8( opt, work->field_BD0 );
        if ( ret > 4 )
        {
            printf( "Err Err Err  Set Dir Over\n" ) ;
            return -1;
        }
    }

    return 0;
}

extern int  s11i_zk11fcom_800D0BF4( Zako11FWork *work );

// HACK: Oddball prototype using int for $a3 instead of unsigned short.
extern void GM_ConfigControlRadarparam(CONTROL *, u_short, u_short, int, u_short);

void Zako11FGetResources_800C9070( Zako11FWork *work, int name, int where )
{
    int addr;
    char *opt;
    int i;
    SVECTOR svec;

    s11i_zako11f_800C8B98( work, name, where ) ;
    work->param.index = s11i_zk11fcom_800D0BF4( work ) ;

    if ( work->param.index  << 24 < 0  )
    {
       printf( "Err not enough work !!\n" ) ;
    }

    s11i_zako11f_800C8F98( work ) ;

    //root
    work->param.root = 0;
    opt = GCL_GetOption( 'r' );
    if ( opt )
    {
        work->param.root = GCL_StrToInt( ( char* )opt );
    }

    //life
    work->param.life = 384;
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

    work->field_B84 = 64;
    opt = GCL_GetOption( 'z' );
    if ( opt )
    {
        work->field_B84 = GCL_StrToInt( ( char* )opt );
    }

    work->field_B86 = 96;
    opt = GCL_GetOption( 'w' );
    if ( opt )
    {
        work->field_B86 = GCL_StrToInt( ( char* )opt );
    }


    work->param.blood = 65;
    opt = GCL_GetOption( 'b' );
    if ( opt )
    {
        work->param.blood = GCL_StrToInt( ( char* )opt );
    }

    printf( " low[pory=%d\n", work->param.low_poly ) ;
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

    work->field_BFC = s11i_dword_800C32F0[ work->param.index ];
    work->field_C00 = work->param.index;
    work->param.field_B7C = 0xFF;

    opt = GCL_GetOption( 'n' );
    if ( opt )
    {
        GCL_StrToSV( ( char* )opt, &svec );
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

    if ( work->param.area == 'S' ) ZAKO11F_SetPutChar_800CD700( work, PUTBREATH ) ; /* 白い息はく */
    work->scale = 4096 ;            /* スケール */

    if ( ( opt = GCL_GetOption( 's' ) ) != NULL ) work->scale += GCL_StrToInt( ( char* )opt );
    work->param.item = 1;

    //fprintf(0,"Life=%d Faint=%d Blood=%c Area=%c \n",
    //  work->param.life, work->param.faint, work->param.blood,work->param.area);

    if( ReadNodes_800C8E4C( work ) < 0 ) fprintf( 1, "watchar.c : action point Err\n" );

    /*
        当たりデータを初期化する
    */
    if( ( work->target =  GM_AllocTarget() ) != NULL ) InitTarget_800C8A10( work ) ;

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
    work->field_B94 = 0;
    work->pad.sound = 0;
    work->pad.time  = 0;
    work->vision.length = ZAKO11F_EYE_LENGTH_800C3694;
    work->field_BA4 = ZAKO11F_NO_POINT_800C368C;
    work->subweapon = NULL;

    work->control.mov = work->nodes[ 0 ] ;
    work->field_C40 = 0;
    work->param.c_root = work->param.root;
    work->param.field_B7F = work->param.field_B7C;

    for ( i = 0 ; i <= 7 ; i++ )
    {
        work->modetime[i] = 0;
    }

    work->modetime[7] = 7;
    work->modetime[4] = -1;

    opt = GCL_GetOption( 'c' );
    if ( opt )
    {
        printf( "asiatoooo" );
        work->modetime[7] |= 0x10;
    }

    GM_ConfigControlRadarparam( &work->control , 0, 0x200, ZAKO11F_EYE_LENGTH_800C3694, 0 );
    work->start_pos = work->nodes[ 0 ] ;
    work->start_map = GM_CurrentMap;
    addr = HZD_GetAddress( work->control.map->hzd, &( work->control.mov ), -1 );

    work->start_addr = addr;
    work->field_C10  = addr;
    work->field_BF0  = addr;

    work->field_C1C = work->start_pos;
}

void *NewZako11F( int name, int where, int argc, char **argv )
{
    Zako11FWork *work ;

    work = (Zako11FWork *)GV_NewActor( 4, sizeof( Zako11FWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor( &( work->actor ), ( GV_ACTFUNC )ZAKO11FAct_800C88AC, ( GV_ACTFUNC )ZAKO11FDie_800C8E2C, "zako11f.c" );
        Zako11FGetResources_800C9070( work, name, where );
    }
    return (void *)work ;
}