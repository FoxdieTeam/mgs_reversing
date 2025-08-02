#include "../../_shared/enemy/enemy.h"

#include <stdio.h>
#include "common.h"
#include "mts/mts.h" // for fprintf
#include "libhzd/libhzd.h"
#include "chara/snake/shadow.h"
#include "game/camera.h"
#include "strcode.h"

extern ENEMY_COMMAND EnemyCommand_800E0D98;
extern SVECTOR       ENEMY_TARGET_SIZE_800C35A4;
extern SVECTOR       ENEMY_TARGET_FORCE_800C35AC;
extern SVECTOR       ENEMY_ATTACK_SIZE_800C35B4;
extern SVECTOR       ENEMY_ATTACK_FORCE_800C35BC;
extern SVECTOR       ENEMY_TOUCH_SIZE_800C35C4;
extern SVECTOR       ENEMY_TOUCH_FORCE_800C35CC;
extern SVECTOR       COM_NO_POINT_800C35D4;
extern unsigned short COM_EYE_LENGTH_800E0D8C;

extern GM_Camera      GM_Camera_800B77E8;

extern void *NewGunLight_800D3AD4( MATRIX* mat, int **enable );

/*  Modified version of RootFlagCheck_800C3EE8
    (last two switch cases removed)

    ルート変更フラグチェック
    指定フラグが立てば次のルートへ変更
    ここではコマンダーに変更ルートをセットする
    変更後の各敵兵はポイントアクションの時にルート変更する
    ついでにフェイズアウト、イン等のメッセージ処理も行う。
    */
int s07a_meryl7_800D50F8( WatcherWork* work )
{
    int count;
    GV_MSG *msg;
    SVECTOR svec;
    CONTROL *ctrl;

    ctrl = &work->control;
    ctrl->n_messages = GV_ReceiveMessage( ctrl->name, &work->control.messages );
    count = ctrl->n_messages;
    msg = ctrl->messages;

    if ( count <= 0 ) return 0 ;

    for ( ; count > 0 ; --count, msg++ )
    {
        switch ( msg->message[0] )
        {
        case 0x430F:
            work->param_c_root = msg->message[1];
            svec.vx = msg->message[2];
            svec.vy = msg->message[3];
            svec.vz = msg->message[4];

            if ( svec.vy < 0x7530 )
            {
                work->field_B7C = HZD_GetAddress( work->control.map->hzd, &svec, -1 );
            }
            else
            {
                work->field_B7C = -1;
            }
            return 1;
        case 0xF1BD:
            work->hom->flag = 0 ;
            work->alert_level = 0 ;
            GM_ConfigControlAttribute( &(work->control), 0 ) ;
            work->visible = 0 ;
            work->target->class = TARGET_AVAIL;

            work->faseout = 1 ;
            work->act_status = EN_FASEOUT ;
            break;
        case 0x1DC4:
            if ( EnemyCommand_800E0D98.field_0xC8[ work->field_B78 ].field_04 == 2 )
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

// Identical to s00a_watcher_800C409C
void s07a_meryl7_800D528C( WatcherWork* work )
{
    if ( GM_GameStatus & STATE_ENEMY_OFF )
    {
        if ( work->faseout == 0 )
        {
            work->hom->flag = 0 ;
            work->alert_level = 0 ;
            GM_ConfigControlAttribute( &(work->control), 0 ) ;
            work->visible = 0 ;
            work->target->class = TARGET_AVAIL;

            work->faseout = 1 ;
            work->act_status = EN_FASEOUT ;
        }
    }
}

// Identical to s00a_watcher_800C410C
void s07a_meryl7_800D52FC( WatcherWork* work )
{
    s07a_meryl7_800D50F8( work );
    s07a_meryl7_800D528C( work );
}

// Identical to s00a_watcher_800C4138
void s07a_meryl7_800D5328( DG_OBJS* objs, DG_DEF* def )
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

// Based on s00a_watcher_800C41B4, one "if" missing
void s07a_meryl7_800D53A4( WatcherWork *work )
{
    if ( work->visible )
    {
        if ( work->field_B7B == 1 )
        {
            if ( GM_GameStatus & (GAME_FLAG_BIT_07 | STATE_BEHIND_CAMERA) || GM_Camera_800B77E8.first_person )
            {
                if ( work->has_kmd != work->field_B7B )
                {
                    work->has_kmd = work->field_B7B;
                    s07a_meryl7_800D5328( work->body.objs, work->def );
                }
            }
            else if ( work->has_kmd )
            {
                work->has_kmd = 0;
                s07a_meryl7_800D5328( work->body.objs, work->kmd );
            }
        }
        DG_VisibleObjs( work->body.objs );
        DG_VisibleObjs( work->weapon.objs );
        work->field_AF4[0] = 1;
        work->field_AFC[0] = 1;
    }
    else
    {
        DG_InvisibleObjs( work->body.objs );
        DG_InvisibleObjs( work->weapon.objs );
        work->field_AF4[0] = 0;
        work->field_AFC[0] = 0;
    }
}

int s07a_meryl7_800D54DC( SVECTOR* svec )
{
    if ( ( svec->vx < 4000 )  ||  ( svec->vx > 9500 ) || ( svec->vz < -20500 ) || ( svec->vz > -12000 ) )
    {
        return 0;
    }

    return 1;
}

int s07a_meryl7_800D5520( SVECTOR* svec )
{
    if ( ( svec->vx < 7000 ) || ( svec->vx > 8500 ) || ( svec->vz < -20500 ) || ( svec->vz > -19000 ) )
    {
        return 0;
    }

    return 1;
}

int s07a_meryl7_800D5564( SVECTOR* svec )
{
    if ( ( svec->vx < 4000 )  ||  ( svec->vx > 9500 ) || ( svec->vz < -20500 ) || ( svec->vz > -16500 ) )
    {
        return 0;
    }

    return 1;
}



extern int *s07a_dword_800E3650;
extern int *s07a_dword_800E3654;

void s07a_meryl7_800D55A8(WatcherWork *work )
{
    if ( s07a_meryl7_800D54DC( &work->control.mov ) != 0 )
    {
        *s07a_dword_800E3650 = 0;
    } else
    {
        *s07a_dword_800E3650 = 1;
    }

    if ( s07a_meryl7_800D5564( &GM_PlayerPosition ) != 0)
    {
        *s07a_dword_800E3654 = 0;
    }
    else
    {
        *s07a_dword_800E3654 = 1;
    }
}

int s07a_meryl7_800D5614( WatcherWork *work )
{
    return s07a_meryl7_800D5520( &GM_PlayerPosition );
}

void EnemyPushMove_800DB23C( WatcherWork *work ); // EnemyPushMove_800CA0E8
void EnemyActionMain_800DB1D0( WatcherWork *work ); // EnemyActionMain_800CA07C

// Modified version of WatcherAct_800C430C
void EnemyMerylAct_800D5638( WatcherWork *work )
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

    s07a_meryl7_800D52FC( work );
    s07a_meryl7_800D55A8( work );
    s07a_meryl7_800D5614( work );
    if ( !work->faseout )
    {
        EnemyPushMove_800DB23C( work );
        GM_ActControl( ctrl );
        GM_ActObject2( &( work->body ) );
        GM_ActObject2( &( work->weapon ) );

        DG_GetLightMatrix2( &( ctrl->mov ), work->light );

        EnemyActionMain_800DB1D0( work );
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
    s07a_meryl7_800D53A4( work );
}

// Identical to InitTarget_800C444C
void s07a_meryl7_800D5780( WatcherWork *work )
{
    TARGET *target;
    TARGET *target2;
    int life;
    int faint;

    target = work->target;
    life   = work->param_life;
    faint  = work->param_faint;

    GM_SetTarget( target, TARGET_FLAG, ENEMY_SIDE, &ENEMY_TARGET_SIZE_800C35A4 );
    GM_Target_8002DCCC( target, 1, -1, life, faint, &ENEMY_TARGET_FORCE_800C35AC );
    GM_Target_8002DCB4( target, -1, faint, NULL, NULL);

    sub_8002DD14( target, &( work->body.objs->objs[1].world ) );

    target2 = &work->field_904;
    GM_SetTarget( target2, TARGET_POWER, PLAYER_SIDE, &ENEMY_ATTACK_SIZE_800C35B4 );
    GM_Target_8002DCCC( target2, 7, 5, 0, 3, &ENEMY_ATTACK_FORCE_800C35BC );

    target2 = &work->field_94C;
    GM_SetTarget( target2, ( TARGET_TOUCH ), ENEMY_SIDE, &ENEMY_TOUCH_SIZE_800C35C4 );
    GM_Target_8002DCCC( target2, 7, 5, 0, 0, &ENEMY_TOUCH_FORCE_800C35CC );
}

// Identical to s00a_watcher_800C4578
void s07a_meryl7_800D58AC( WatcherWork* work )
{
    WatcherUnk *s;
    s = &work->unknown;

    GV_ZeroMemory(s, 0x24);
    s->field_00 = 0;
    s->field_1C = 0x1C2;
    s->field_1E = 1;

    work->action = 0;
    work->action2 = 0;
    work->time = 0;
    work->time2 = 0;
}

int ENE_SetPutChar_800D9D6C( WatcherWork *work, int put ); // ENE_SetPutChar_800C979C

// Modified s00a_watcher_800C45D4
int s07a_meryl7_800D5908( WatcherWork* work, int name, int where )
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

    ctrl->exclude_flag = 2;

    GM_ConfigControlTrapCheck( ctrl );

    //ctrl->field_36 = -1;

    body  = &work->body;
    arm = &work->weapon;

    GM_InitObject( body, KMD_IPPANHEI, 0x32D, OAR_ENEMY ) ;
    GM_ConfigObjectJoint( body ) ;
    GM_ConfigMotionControl( body, &work->m_ctrl, OAR_ENEMY, work->m_segs1, work->m_segs2, ctrl, work->rots );
    GM_ConfigObjectLight( body, work->light );

    work->field_B7B = 0;

    opt2 = GCL_GetOption( 'y' );
    if ( opt2 ) {
        work->field_B7B = GCL_StrToInt( opt2 );
    }

    has_kmd = work->field_B7B;
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

    work->field_AF0 = (void*)NewShadow2_80060384( ctrl, body, shadow,  &work->field_AF4 ) ;
    work->field_AF8 = NewGunLight_800D3AD4( &( body->objs->objs[4].world ), &work->field_AFC ) ;

    ENE_SetPutChar_800D9D6C( work, 0 );
    s07a_meryl7_800D58AC ( work );

    return 0;
}

// Identical to s00a_watcher_800C4814
//FreeWatcher?
void s07a_meryl7_800D5B28( WatcherWork* work )
{
    GM_FreeHomingTarget( work->hom );
    GM_FreeControl( &( work->control ) );
    GM_FreeObject( &( work->body ) );
    GM_FreeObject( &( work->weapon ) );
    GM_FreeTarget( work->target );
    GV_DestroyOtherActor( work->field_AF8 );
    GV_DestroyOtherActor( work->field_AF0 );
}

// Identical to WatcherDie_800C487C
void EnemyMerylDie_800D5B90( WatcherWork* work )
{
    s07a_meryl7_800D5B28( work );
}

// Identical to ReadNodes_800C489C
int s07a_meryl7_800D5BB0( WatcherWork* work )
{
    int i;
    HZD_PAT *patrol;
    HZD_PTP *points;

    patrol = work->control.map->hzd->header->routes;
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

// Identical to s00a_watcher_800C4990
int s07a_meryl7_800D5C4C( char *opt, short* s )
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

// Identical to s00a_watcher_800C49E8
int s07a_meryl7_800D5CA4( char *opt, int* l )
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

extern unsigned short s07a_dword_800C3618[];
extern const char s07a_aErrerrerrsettimeover_800E2E40[];
extern const char s07a_aErrerrerrsetdirover_800E2E5C[];

int s07a_meryl7_800D5CFC( WatcherWork* work )
{
    int i;
    char *opt;
    int ret;

    for ( i = 0 ; i < 8 ; i++ )
    {
        work->field_BB0[i] = s07a_dword_800C3618[i];
    }

    opt = GCL_GetOption( 't' );
    if ( opt )
    {
        ret = s07a_meryl7_800D5CA4( opt, &work->field_BB0[1] );
        if ( ret > 4 )
        {
            printf( (char *)s07a_aErrerrerrsettimeover_800E2E40 ) ;
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
        ret = s07a_meryl7_800D5C4C( opt, work->field_BD0 );
        if ( ret > 4 )
        {
            printf( (char *)s07a_aErrerrerrsetdirover_800E2E5C ) ;
            return -1;
        }
    }

    return 0;
}

extern const char s07a_aErrerrerrsoundbuffover_800E2E78[];
int s07a_meryl7_800D5DD4( WatcherWork *work )
{
    char *opt;

    opt = GCL_GetOption('v');
    if (opt != NULL && s07a_meryl7_800D5CA4(opt, &work->field_C40) > 2)
    {
        fprintf(0, s07a_aErrerrerrsoundbuffover_800E2E78);
        return -1;
    }

    return 0;
}

extern const char s07a_dword_800E2E98[];
extern const char s07a_dword_800E2EA0[];

extern void *s07a_dymc_seg_800D65C8(int arg0, SVECTOR *min, SVECTOR *max, int min_h, int max_h, int flag, void **arg6);

void s07a_meryl7_800D5E34( WatcherWork *work )
{
    int flag;
    SVECTOR min, max;

    flag = 0xFE;

    min.vx = 0x157C;
    min.vy = 0;
    min.vz = -0x251C;

    max.vx = 0x1B58;
    max.vy = 0;
    max.vz = -0x251C;

    s07a_dymc_seg_800D65C8( GV_StrCode( s07a_dword_800E2E98 ), &min, &max, 3000, 3000, 0xFE, (void**)&s07a_dword_800E3650 );

    flag = 0xF7;

    min.vx = 0x1194;
    min.vy = 0;
    min.vz = -0x4844;

    max.vx = 0x1B58;
    max.vy = 0;
    max.vz = -0x4844;
    s07a_dymc_seg_800D65C8( GV_StrCode( s07a_dword_800E2EA0 ), &min, &max, 3000, 3000, 0xF7, (void**)&s07a_dword_800E3654 );
}

extern const char s07a_aErrnotenoughwork_800E2EAC[];// = "Err not enough work !!\n";
extern const char s07a_aMerylcactionpointerr_800E2EC4[];// = "meryl.c : action point Err\n";

extern int s07a_dword_800C35F8[8];
extern int s07a_dword_800E3658;
extern const char s07a_aAsiatoooo_800E2EE0[];

extern void GM_ConfigControlRadarparam(CONTROL *, u_short, u_short, u_short, u_short);

void EnemyMerylGetResources_800D5F24( WatcherWork *work, int name, int where )
{
    SVECTOR svec;
    int addr;
    char *opt;
    int i;

    s07a_meryl7_800D5908( work, name, where ) ;
    work->field_B78 = s00a_command_800CEA2C( work ) ;

    if ( work->field_B78  << 24 < 0  )
    {
       printf( (char *)s07a_aErrnotenoughwork_800E2EAC ) ;
    }

    s07a_meryl7_800D5CFC( work ) ;

    work->param_root = 0;
    opt = GCL_GetOption( 'r' );
    if ( opt )
    {
        work->param_root = GCL_StrToInt( ( char* )opt );
    }

    work->param_life = 192;
    opt = GCL_GetOption( 'l' );
    if ( opt )
    {
        work->param_life = GCL_StrToInt( ( char* )opt );
    }

    work->param_faint = 10;
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

    work->field_B81 = 0xFF;

    opt = GCL_GetOption('g');
    if ( opt )
    {
        work->field_B81 = GCL_StrToInt( ( char* )opt );
    }
    if ( work->param_blood == 'Z' )
    {
        work->field_B81 = 0;
    }


    work->field_C34 = 0;
    work->field_C35[0] = 0;

    opt = GCL_GetOption( 'e' );
    if ( opt )
    {
        work->field_C3C = GCL_StrToInt( GCL_GetParamResult() );
    }
    else
    {
        work->field_C3C = -1;
    }

    s07a_dword_800E3658 = -1;
    opt = GCL_GetOption( 'k' );
    if ( opt )
    {
        s07a_dword_800E3658 = GCL_StrToInt( GCL_GetParamResult() );
    }

    s07a_meryl7_800D5DD4( work );
    work->field_BFC = s07a_dword_800C35F8[ work->field_B78 ];
    work->field_C00 = work->field_B78;
    work->field_B7C = 0xFF;

    opt = GCL_GetOption( 'n' );
    if ( opt )
    {
        GCL_StrToSV( ( char* )opt, &svec );
        if ( svec.vy < 0x7530 )
        {
            work->field_B7C = HZD_GetAddress( work->control.map->hzd, &svec, -1 );
        }
        else
        {
            work->field_B7C = 0xFF;
        }
    }

    work->param_area = 'A';
    opt = GCL_GetOption( 'a' );
    if (opt != 0)
    {
        work->param_area = GCL_StrToInt( ( char* )opt );
    }

    if ( work->param_area == 'S' ) ENE_SetPutChar_800D9D6C( work, PUTBREATH ) ; /* 白い息はく */
    work->scale = 4096 ;            /* スケール */

    if ( ( opt = GCL_GetOption( 's' ) ) != NULL ) work->scale += GCL_StrToInt( ( char* )opt );
    work->param_item = 1;

    //fprintf(0,"Life=%d Faint=%d Blood=%c Area=%c \n",
    //  work->param.life, work->param.faint, work->param.blood,work->param.area);

    if( s07a_meryl7_800D5BB0( work ) < 0 ) printf( (char *)s07a_aMerylcactionpointerr_800E2EC4 );

    /*
        当たりデータを初期化する
    */
    if( ( work->target =  GM_AllocTarget() ) != NULL ) s07a_meryl7_800D5780( work ) ;

    /*
        思考ルーチン用データを初期化する
    */
    s07a_meryl7_800D5E34( work );
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
    work->vision.length = COM_EYE_LENGTH_800E0D8C;
    work->field_BA4 = COM_NO_POINT_800C35D4;

    work->subweapon = 0;

    work->control.mov = work->nodes[ 0 ] ;
    work->param_c_root = work->param_root;
    work->field_B7F = work->field_B7C;

    for ( i = 0 ; i <= 7 ; i++ )
    {
        work->modetime[i] = 0;
    }

    work->field_BA3 =  7;
    work->field_BA0 = -1;

    opt = GCL_GetOption( 'c' );
    if ( opt )
    {
        printf( (char *)s07a_aAsiatoooo_800E2EE0 );
        work->field_BA3 |= 0x10;
    }

    GM_ConfigControlRadarparam( &work->control , 0, 0x200, COM_EYE_LENGTH_800E0D8C, 0 );
    work->start_pos = work->nodes[ 0 ] ;
    work->start_map = GM_CurrentMap;
    addr = HZD_GetAddress( work->control.map->hzd, &( work->control.mov ), -1 );

    work->start_addr = addr;
    work->field_C08 = addr;
    work->field_BF0 = addr;

    work->field_C14 = work->start_pos;
}

#define EXEC_LEVEL GV_ACTOR_LEVEL4

extern const char s07a_aMeryl7_800E2F04[];
extern const char s07a_aEnemyworksized_800E2EEC[];

void *NewEnemyMeryl_800D63A4( int name, int where, int argc, char **argv )
{
    WatcherWork *work ;

    printf( (char *)s07a_aEnemyworksized_800E2EEC, sizeof( WatcherWork ) );
    work = GV_NewActor( EXEC_LEVEL, sizeof( WatcherWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor( &( work->actor ), EnemyMerylAct_800D5638, EnemyMerylDie_800D5B90, s07a_aMeryl7_800E2F04 );
        EnemyMerylGetResources_800D5F24( work, name, where );
    }
    return (void *)work ;
}
