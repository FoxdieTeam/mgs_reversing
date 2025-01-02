#include "../../../s00a/Enemy/enemy.h"

#include <stdio.h>
#include "common.h"
#include "mts/mts.h" // for fprintf
#include "libhzd/libhzd.h"
#include "chara/snake/shadow.h"
#include "strcode.h"

/*
extern ENEMY_COMMAND EnemyCommand_800E0D98;
extern SVECTOR       ENEMY_TARGET_SIZE_800C35A4;
extern SVECTOR       ENEMY_TARGET_FORCE_800C35AC;
extern SVECTOR       ENEMY_ATTACK_SIZE_800C35B4;
extern SVECTOR       ENEMY_ATTACK_FORCE_800C35BC;
extern SVECTOR       ENEMY_TOUCH_SIZE_800C35C4;
extern SVECTOR       ENEMY_TOUCH_FORCE_800C35CC;
extern SVECTOR       COM_NO_POINT_800C35D4;
extern int           COM_EYE_LENGTH_800E0D8C;

extern GM_Camera      GM_Camera_800B77E8;
extern int            GM_PlayerMap_800ABA0C;
*/

extern SVECTOR ZAKO_TARGET_SIZE_800C38CC;
extern SVECTOR ZAKO_TARGET_FORCE_800C38D4;
extern SVECTOR ZAKO_ATTACK_SIZE_800C38DC;
extern SVECTOR ZAKO_ATTACK_FORCE_800C38E4;
extern SVECTOR ZAKO_TOUCH_SIZE_800C38EC;
extern SVECTOR ZAKO_TOUCH_FORCE_800C38F4;

extern int ZAKO11E_EYE_LENGTH_800C3904;
extern SVECTOR ZAKO11E_NO_POINT_800C38FC;

extern int  s11e_zk11ecom_800D9A20( ZakoWork *work );
extern int  Zako11EPushMove_800D889C( ZakoWork *work );
extern int  Zako11EActionMain_800D8830( ZakoWork *work );
extern void ZAKO11E_SetPutChar_800D8004( ZakoWork *work, int put );

extern void *NewGunLight_800D3AD4( MATRIX* mat, int **enable );
extern GV_ACT *NewKogaku2(CONTROL *pCtrl, OBJECT *pObj, int unit);

void RootFlagCheck_800D34C8( ZakoWork *work )
{
    /* do nothing */
}

void s11e_zako11e_800D34D0( DG_OBJS* objs, DG_DEF* def )
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

void s11e_zako11e_800D354C( ZakoWork *work )
{
    if ( work->visible )
    {
        if ( work->param_low_poly == 1 )
        {
            if ( GM_GameStatus & (GAME_FLAG_BIT_07 | STATE_BEHIND_CAMERA) || GM_Camera_800B77E8.first_person )
            {
                if ( work->field_180 != work->param_low_poly )
                {
                    work->field_180 = work->param_low_poly;
                    s11e_zako11e_800D34D0( work->body.objs, work->def );
                }
            }
            else if ( work->field_180 )
            {
                work->field_180 = 0;
                s11e_zako11e_800D34D0( work->body.objs, work->kmd );
            }
        }
        DG_VisibleObjs( work->body.objs );
        DG_VisibleObjs( work->field_7A4.objs );
        work->field_AF4[0] = 1;
        work->field_AFC[0] = 1;
    }
    else
    {
        DG_InvisibleObjs( work->body.objs );
        DG_InvisibleObjs( work->field_7A4.objs );
        work->field_AF4[0] = 0;
        work->field_AFC[0] = 0;
    }
}

extern int s11e_dword_800DF3B4;
extern ZAKO_COMMAND ZakoCommand_800DF280;

void ZakoAct_800D3684( ZakoWork *work )
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

    RootFlagCheck_800D34C8( work );
    if ( !work->faseout )
    {
        Zako11EPushMove_800D889C( work );
        GM_ActControl( ctrl );
        GM_ActObject2( &( work->body ) );
        GM_ActObject2( &( work->field_7A4 ) );

        DG_GetLightMatrix2( &( ctrl->mov ), &( work->field_888 ) );

        Zako11EActionMain_800D8830( work );
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

    s11e_zako11e_800D354C( work );
    *work->field_AFC = 0;
    *work->field_AF4 = 0;

    if ( s11e_dword_800DF3B4 == 0xF && ZakoCommand_800DF280.field_0x8C[work->field_B74].field_04 == 1 )
    {
         GV_DestroyActor( &( work->actor ) );
    }
}

void InitTarget_800D3800( ZakoWork *work )
{
    TARGET *target;
    TARGET *target2;
    int life;
    int faint;

    target = work->target;
    life   = work->param_life;
    faint  = work->param_faint;

    GM_SetTarget( target, ( TARGET_FLAG | TARGET_AVAIL ), ENEMY_SIDE, &ZAKO_TARGET_SIZE_800C38CC );
    GM_Target_8002DCCC( target, 1, -1, life, faint, &ZAKO_TARGET_FORCE_800C38D4 );
    GM_Target_8002DCB4( target, -1, faint, NULL, NULL);

    sub_8002DD14( target, &( work->body.objs->objs[1].world ) );

    work->local_data = work->param_life;
    target2 = &work->field_904;
    GM_SetTarget( target2, TARGET_POWER, PLAYER_SIDE, &ZAKO_ATTACK_SIZE_800C38DC );
    GM_Target_8002DCCC( target2, 7, 5, 0, 3, &ZAKO_ATTACK_FORCE_800C38E4 );

    target2 = &work->field_94C;
    GM_SetTarget( target2, ( TARGET_TOUCH ), ENEMY_SIDE, &ZAKO_TOUCH_SIZE_800C38EC );
    GM_Target_8002DCCC( target2, 7, 5, 0, 0, &ZAKO_TOUCH_FORCE_800C38F4 );
}

void s11e_zako11e_800D3934( ZakoWork* work )
{
    WatcherUnk *s;
    s = (WatcherUnk*)&work->field_8C8;

    GV_ZeroMemory(s, 0x24);
    s->field_00 = 0;
    s->field_1C = 0x1C2;
    s->field_1E = 1;

    work->action = 0;
    work->action2 = 0;
    work->time = 0;
    work->time2 = 0;
}

int s11e_zako11e_800D3990( ZakoWork* work, int name, int where )
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
    arm = &work->field_7A4;

    GM_InitObject( body, KMD_IPPANHEI, 0x32D, 0xA8A1 ) ;
    GM_ConfigObjectJoint( body ) ;
    GM_ConfigMotionControl( body, &work->m_ctrl, 0xA8A1, work->field_1DC, &work->field_1DC[17], ctrl, work->rots );
    GM_ConfigObjectLight( body, &work->field_888 );

    work->param_low_poly = 0;

    opt2 = GCL_GetOption( 'y' );
    if ( opt2 ) {
        work->param_low_poly = GCL_StrToInt( (char*)opt2 );
    }

    has_kmd = work->param_low_poly;
    if ( has_kmd == 1 )
    {
        work->def = body->objs->def;
        work->kmd = GV_GetCache( GV_CacheID( HASH_LOPRYHEI, 'k' ) );
        work->field_180 = has_kmd;
    }


    work->field_C40 = (int)NewKogaku2( ctrl, body, 0 );
    work->hom = GM_AllocHomingTarget( &body->objs->objs[6].world, ctrl );
    GM_InitObject( arm, KMD_FAMAS, 0x6D, 0 );
    GM_ConfigObjectLight( arm, &work->field_888 ) ;
    GM_ConfigObjectRoot( arm, body, 4 );
    work->field_C44 = (int)NewKogaku2( ctrl, arm, 0 );

    //did they just not remove this?
    for ( i = 0 ; i < 0 ; i++ )
    {
        work->field_B00[i] = 0;
    }
    shadow.vy  = 6;
    shadow.vz  = 12;
    shadow.pad = 15;
    shadow.vx  = 0;

    work->field_AF0 = (void*)NewShadow2_80060384( ctrl, body, shadow,  &work->field_AF4 ) ;
    work->field_AF8 = NewGunLight_800D3AD4( &( body->objs->objs[4].world ), &work->field_AFC ) ;

    ZAKO11E_SetPutChar_800D8004( work, 0 );
    s11e_zako11e_800D3934( work );

    return 0;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3BD8.s")
extern void s11e_zk11ecom_800D9A64( int );

void s11e_zako11e_800D3BD8( ZakoWork* work )
{
    s11e_zk11ecom_800D9A64( work->field_B74 );
    GM_FreeControl( &( work->control ) );
    GM_FreeObject( &( work->body ) );
    GM_FreeObject( &( work->field_7A4 ) );
    GM_FreeTarget( work->target );
    GV_DestroyActor( work->field_AF8 );
    GV_DestroyActor( work->field_AF0 );

    GM_FreeHomingTarget( work->hom );
    if ( work->field_C40 )
    {
        GV_DestroyActorQuick( (GV_ACT*)work->field_C40 );
        work->field_C40 = 0;
    }
    if ( work->field_C44 )
    {
        GV_DestroyActorQuick( (GV_ACT*)work->field_C44 );
        work->field_C44 = 0;
    }
}

void ZakoDie_800D3C84( ZakoWork* work )
{
    s11e_zako11e_800D3BD8( work );
}

int ReadNodes_800D3CA4( ZakoWork* work )
{
    int i;
    HZD_PAT *patrol;
    HZD_PTP *points;

    patrol = work->control.map->hzd->header->routes;
    patrol = &patrol[ work->param_root ];

    work->field_9E8 = patrol->n_points;

    if ( work->field_9E8 <= 0 ) return -1;

    points = patrol->points;
    for ( i = 0 ; i < work->field_9E8 ; i++ )
    {
        work->nodes[i].vx = points->x;
        work->nodes[i].vy = points->y;
        work->nodes[i].vz = points->z;
        work->nodes[i].pad = points->command;
        points++;
    }
    return 0;
}

int s11e_zako11e_800D3D40( char *opt, short* s )
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

int s11e_zako11e_800D3D98( char *opt, int* l )
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


extern unsigned short s11e_dword_800C35DC[8];

extern const char s11e_aErrerrerrsettimeover_800DEAE8[];
extern const char s11e_aErrerrerrsetdirover_800DEB04[];

int s11e_zako11e_800D3DF0( ZakoWork *work )
{
    int i;
    char *opt;
    int ret;

    for ( i = 0 ; i < 8 ; i++ )
    {
        work->field_BB0[i] = s11e_dword_800C35DC[i];
    }

    opt = GCL_GetOption( 't' );
    if ( opt )
    {
        ret = s11e_zako11e_800D3D98( opt, &work->field_BB0[1] );
        if ( ret > 4 )
        {
            printf( (char *)s11e_aErrerrerrsettimeover_800DEAE8 ) ;
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
        ret = s11e_zako11e_800D3D40( opt, work->field_BD0 );
        if ( ret > 4 )
        {
            printf( (char *)s11e_aErrerrerrsetdirover_800DEB04 ) ;
            return -1;
        }
    }

    return 0;
}


extern const char s11e_aErrnotenoughwork_800DEB20[];// = "Err not enough work !!\n";
extern const char s11e_aLowporyd_800DEB38[];// = " low[pory=%d\n";
extern const char s11e_aWatcharcactionpointerr_800DEB48[];// = "watchar.c : action point Err\n";

extern int s11e_dword_800C35BC[8];

// HACK: Oddball prototype using int for $a3 instead of unsigned short.
extern void GM_ConfigControlRadarparam(CONTROL *, u_short, u_short, int, u_short);

void ZakoGetResources_800D3EC8( ZakoWork *work, int name, int where )
{
    int addr;
    char *opt;
    int i;

    s11e_zako11e_800D3990( work, name, where ) ;
    work->field_B74 = s11e_zk11ecom_800D9A20( work ) ;

    if ( work->field_B74  << 24 < 0  )
    {
       printf( (char *)s11e_aErrnotenoughwork_800DEB20 ) ;
    }

    s11e_zako11e_800D3DF0( work ) ;

    //root
    work->param_root = 0;
    opt = GCL_GetOption( 'r' );
    if ( opt )
    {
        work->param_root = GCL_StrToInt( ( char* )opt );
    }

    //life
    work->param_life = 576;
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

    work->field_B84 = 64;
    opt = GCL_GetOption( 'z' );
    if ( opt )
    {
        work->field_B84 = GCL_StrToInt( ( char* )opt );
    }

    work->param_blood = 65;
    opt = GCL_GetOption( 'b' );
    if ( opt )
    {
        work->param_blood = GCL_StrToInt( ( char* )opt );
    }

    printf( (char *)s11e_aLowporyd_800DEB38, work->param_low_poly ) ;
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

    work->field_BFC = s11e_dword_800C35BC[ work->field_B74 ];
    work->field_C00 = work->field_B74;
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

    if ( work->param_area == 'S' ) ZAKO11E_SetPutChar_800D8004( work, PUTBREATH ) ; /* 白い息はく */
    work->scale = 4096 ;            /* スケール */

    if ( ( opt = GCL_GetOption( 's' ) ) != NULL ) work->scale += GCL_StrToInt( ( char* )opt );
    work->param_item = 1;

    //fprintf(0,"Life=%d Faint=%d Blood=%c Area=%c \n",
    //  work->param.life, work->param.faint, work->param.blood,work->param.area);

    opt = GCL_GetOption( 'o' );
    if ( opt )
    {
        work->field_C48 = GCL_StrToInt( GCL_GetParamResult() );
    }
    else
    {
        work->field_C48 = -1;
    }


    if( ReadNodes_800D3CA4( work ) < 0 ) fprintf( 1, s11e_aWatcharcactionpointerr_800DEB48 );

    /*
        当たりデータを初期化する
    */
    if( ( work->target =  GM_AllocTarget() ) != NULL ) InitTarget_800D3800( work ) ;

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
    work->target_map  = GM_CurrentMap_800AB9B0;
    work->alert_level = 0;
    work->visible = 1;
    work->vision.angle = 0x200;
    work->vision.facedir = 0;
    work->field_B94 = 0;
    work->pad.sound = 0;
    work->pad.time  = 0;
    work->vision.length = ZAKO11E_EYE_LENGTH_800C3904;
    work->field_BA4 = ZAKO11E_NO_POINT_800C38FC;
    work->subweapon = 0;


    work->control.mov = work->nodes[ 0 ] ;
    work->field_B7B = work->field_B78;
    work->field_C4C = 0;
    //work->faseout = 0;
    work->param_c_root = 0;

    for ( i = 0 ; i <= 7 ; i++ )
    {
        work->modetime[i] = 0;
    }

    work->field_BA3 =  7;
    work->field_BA0 = -1;

    GM_ConfigControlRadarparam( &work->control , 0, 0x200, ZAKO11E_EYE_LENGTH_800C3904, 0 );
    work->start_pos = work->nodes[ 0 ] ;
    work->start_map = GM_CurrentMap_800AB9B0;
    addr = HZD_GetAddress( work->control.map->hzd, &( work->control.mov ), -1 );

    work->start_addr = addr;
    work->field_C10  = addr;
    work->field_BF0  = addr;

    work->field_C1C = work->start_pos;
}

extern void ZakoAct_800D3684();
extern void ZakoDie_800D3C84();
extern const char s11e_aZakoec_800DEB68[];

void *s11e_zako11e_800D42E0( int name, int where, int argc, char **argv )
{
    ZakoWork *work ;

    work = (ZakoWork *)GV_NewActor( 4, sizeof( ZakoWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor( &( work->actor ), ( GV_ACTFUNC )ZakoAct_800D3684, ( GV_ACTFUNC )ZakoDie_800D3C84, s11e_aZakoec_800DEB68 );
        ZakoGetResources_800D3EC8( work, name, where );
    }
    return (void *)work ;
}
