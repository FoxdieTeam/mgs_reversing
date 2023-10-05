#include "enemy.h"

extern const char aWatcherc_800DFCEC[];                 //watcher.c
extern const char aErrnotenoughwork_800DFCB4[];         //Err not enough work !!\n
extern const char aWatcharcactionpointerr_800DFCCC[];   //watchar.c : action point Err\n
extern const char aErrerrerrsettimeover_800DFC7C[];     //Err Err Err  Set time Over\n
extern const char aErrerrerrsetdirover_800DFC98[];      //Err Err Err  Set Dir Over\n

//will remove these as and when they are reversed
extern void s00a_watcher_800C4814( void );
extern void s00a_watcher_800C45D4( WatcherWork *work );
extern void s00a_watcher_800C410C( WatcherWork* work );
extern void s00a_watcher_800C41B4( WatcherWork* work );
extern int  s00a_watcher_800C4938( int opt, char *p );
extern int  s00a_watcher_800C49E8( int opt, int *l );
extern int  s00a_watcher_800C4990( int opt, short *s );

extern int  ReadNodes_800C489C( WatcherWork *work ); //ReadNodes_800C489C

extern int HZD_GetAddress_8005C6C4( HZD_HDL *hzd, SVECTOR *svec, int a2 );
extern void GM_ConfigControlRadarparam_800262EC( CONTROL *pControl, unsigned short param_2, unsigned short param_3, unsigned short param_4, unsigned short param_5 );

extern unsigned short s00a_dword_800C3348[8];

#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_watcher_800C3EE8.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_watcher_800C409C.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_watcher_800C410C.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_watcher_800C4138.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_watcher_800C41B4.s")


void WatcherAct_800C430C( WatcherWork *work )
{
    VECTOR   vec;
    TARGET  *trgt;
    CONTROL *ctrl;
    TARGET  *trgt2;

    ctrl = &( work->control ) ;
    if (GM_CheckMessage_8002631C( &( work->actor ) , ctrl->field_30_scriptData, 0x3223 ) )
    {
        GV_DestroyActor_800151C8( &( work->actor ) );
        return;
    }

    s00a_watcher_800C410C( work );
    if ( !work->faseout )
    {
        s00a_command_800CA0E8( work );
        GM_ActControl_80025A7C( ctrl );
        GM_ActObject2_80034B88( &( work->body ) );
        GM_ActObject2_80034B88( &( work->field_7A4 ) );

        DG_GetLightMatrix2_8001A5D8( &( ctrl->field_0_mov ), &( work->field_888 ) );

        s00a_command_800CA07C( work );
        trgt = work->target;
        GM_Target_SetVector_8002D500( trgt, &( ctrl->field_0_mov ) );

        sub_8002DA14( trgt );

        if ( trgt->class & TARGET_TOUCH )
        {
            trgt2 = &work->field_94C;
            if ( trgt2->class & TARGET_TOUCH )
            {
                if ( trgt2->field_6_flags & TARGET_TOUCH )
                {
                    trgt2->field_6_flags &= ~TARGET_TOUCH;
                }
                GM_Target_SetVector_8002D500( &( work->field_94C ), &( ctrl->field_0_mov ) );
                GM_TouchTarget_8002D6D8( &( work->field_94C ) );
            }
        }
    }
    s00a_watcher_800C41B4( work );
    vec.vx = vec.vz = work->scale;
    vec.vy = work->field_9E2;
    ScaleMatrix( &( work->body.objs->world ), &vec );
}

void InitTarget_800C444C( WatcherWork *work )
{
    TARGET *target;
    TARGET *target2;
    int life;
    int faint;

    target = work->target;
    life   = work->param_life;
    faint  = work->param_faint;

    GM_SetTarget_8002DC74( target, ( TARGET_FLAG | TARGET_AVAIL ), 2, &ENEMY_TARGET_SIZE_800C35A4 );
    GM_Target_8002DCCC( target, 1, -1, life, faint, &ENEMY_TARGET_FORCE_800C35AC );
    GM_Target_8002DCB4( target, -1, faint, NULL, NULL);

    sub_8002DD14( target, &( work->body.objs->objs[1].world ) );

    target2 = &work->field_904;
    GM_SetTarget_8002DC74( target2, TARGET_POWER, 1, &ENEMY_ATTACK_SIZE_800C35B4 );
    GM_Target_8002DCCC( target2, 7, 5, 0, 3, &ENEMY_ATTACK_FORCE_800C35BC );

    target2 = &work->field_94C;
    GM_SetTarget_8002DC74( target2, ( TARGET_TOUCH ), 2, &ENEMY_TOUCH_SIZE_800C35C4 );
    GM_Target_8002DCCC( target2, 7, 5, 0, 0, &ENEMY_TOUCH_FORCE_800C35CC );
}

#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_watcher_800C4578.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_watcher_800C45C4.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_watcher_800C45D4.s")

#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_watcher_800C4814.s")

void WatcherDie_800C487C(void)
{
    s00a_watcher_800C4814();
}

int ReadNodes_800C489C( WatcherWork* work ) 
{
    int i;
    HZD_PAT *patrol;
    HZD_PTP *points;

    patrol = work->control.field_2C_map->field_8_hzd->f00_header->routes;
    patrol = &patrol[ work->field_B7D ];

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

int s00a_watcher_800C4938( int opt, char* c )
{
    int i;
    unsigned char *res;

    for ( i = 0 ; ( res = GCL_Get_Param_Result_80020AA4() ) ; i++ )
    {
        *c = GCL_StrToInt_800209E8( res );
         c++;
    }

    return i;
}

int s00a_watcher_800C4990( int opt, short* s )
{
    int i;
    unsigned char *res;

    for ( i = 0 ; ( res = GCL_Get_Param_Result_80020AA4() ) ; i++ )
    {
        *s = GCL_StrToInt_800209E8( res );
         s++;
    }

    return i;
}

int s00a_watcher_800C49E8( int opt, int* l )
{
    int i;
    unsigned char *res;

    for ( i = 0 ; ( res = GCL_Get_Param_Result_80020AA4() ) ; i++ )
    {
        *l = GCL_StrToInt_800209E8( res );
         l++;
    }

    return i;
}


int s00a_watcher_800C4A40( WatcherWork *work )
{
    int i;
    int opt;
    int ret;

    for ( i = 0 ; i < 8 ; i++ )
    {
        work->field_BB0[i] = s00a_dword_800C3348[i];
    }

    opt = GCL_GetOption_80020968( 't' );
    if ( opt )
    {
        ret = s00a_watcher_800C49E8( opt, &work->field_BB0[1] );
        if ( ret >= 5 )
        {
            printf( aErrerrerrsettimeover_800DFC7C ) ;
            return -1;
        }
    }

    for ( i = 0 ; i < 4 ; i++ )
    {
        work->field_BD0[i] = i * 1024;
    }    

    opt = GCL_GetOption_80020968( 'i' );

    if ( opt )
    {
        ret = s00a_watcher_800C4990( opt, work->field_BD0 );
        if ( ret >= 5 )
        {
            printf( aErrerrerrsetdirover_800DFC98 ) ;
            return -1;
        }
    }
    
    return 0;
}

int s00a_watcher_800C4B18( WatcherWork* work )
{
    int res;
    int opt;
    work->field_C34 = 0;

    opt = GCL_GetOption_80020968( 'j' );
    if ( opt )
    {
        res = s00a_watcher_800C4938( opt, &work->field_C35 );
        if ( res >= 8 )
        {
            printf( aErrerrerrsettimeover_800DFC7C );
            return -1;
        }
        work->field_C34 = res;
    }
    return 0;   
}

void WatcherGetResources_800C4B7C( WatcherWork *work, int name, int where )
{
    SVECTOR svec;
    int addr;
    int opt;
    int i;

    s00a_watcher_800C45D4( work ) ;
    work->field_B78 = s00a_command_800CEA2C( work ) ;

    if ( work->field_B78  << 24 < 0  )
    {
       printf( aErrnotenoughwork_800DFCB4 ) ;
    }

    s00a_watcher_800C4A40( work ) ;

    work->field_B7D = 0;
    opt = GCL_GetOption_80020968( 'r' );
    if ( opt )
    {
        work->field_B7D = GCL_StrToInt_800209E8( ( char* )opt );
    }

    work->param_life = 192;
    opt = GCL_GetOption_80020968( 'l' );
    if ( opt )
    {
        work->param_life = GCL_StrToInt_800209E8( ( char* )opt );
    }

    work->param_faint = 10;
    opt = GCL_GetOption_80020968( 'f' );
    if ( opt )
    {
        work->param_faint = GCL_StrToInt_800209E8( ( char* )opt );
    }

    work->param_blood = 65;
    opt = GCL_GetOption_80020968( 'b' );
    if ( opt )
    {
        work->param_blood = GCL_StrToInt_800209E8( ( char* )opt );
    }

    work->local_data = 0;
    work->local_data2 = 0;
    //work->local_data = work->local_data2 = 0 ;
    opt = GCL_GetOption_80020968( 'h' );
    if ( opt )
    {
        work->local_data = GCL_StrToInt_800209E8( ( char* )opt );
    }

    if ( work->local_data == 3 )
    {
        opt = ( int )GCL_Get_Param_Result_80020AA4();
        if ( opt )
        {
            work->local_data2 = GCL_StrToInt_800209E8( ( char* )opt );
        }
    }

    work->field_B81 = 0xFF;
    opt = GCL_GetOption_80020968('g');
    if ( opt )
    {
        work->field_B81 = GCL_StrToInt_800209E8( ( char* )opt );
    }
    if ( work->param_blood == 'Z' )
    {
        work->field_B81 = 0;
    }

    s00a_watcher_800C4B18( work );
    opt = GCL_GetOption_80020968( 'e' );
    if ( opt )
    {
        work->field_C3C = GCL_StrToInt_800209E8( GCL_Get_Param_Result_80020AA4() );
    }
    else
    {
        work->field_C3C = -1;
    }

    work->field_BFC = s00a_dword_800C3328[ work->field_B78 ];
    work->field_C00 = work->field_B78;
    work->field_B7C = 0xFF;

    opt = GCL_GetOption_80020968( 'n' );
    if ( opt )
    {
        GCL_StrToSV_80020A14( ( char* )opt, &svec );
        if ( svec.vy < 0x7530 )
        {
            work->field_B7C = HZD_GetAddress_8005C6C4( work->control.field_2C_map->field_8_hzd, &svec, -1 );
        }
        else
        {
            work->field_B7C = 0xFF;
        }
    }

    work->param_area = 'A';
    opt = GCL_GetOption_80020968( 'a' );
    if (opt != 0)
    {
        work->param_area = GCL_StrToInt_800209E8( ( char* )opt );
    }

    if ( work->param_area == 'S' ) ENE_SetPutChar_800C979C( work, PUTBREATH ) ; /* 白い息はく */
    work->scale = 4096 ;            /* スケール */

    if ( ( opt = GCL_GetOption_80020968( 's' ) ) != NULL ) work->scale += GCL_StrToInt_800209E8( ( char* )opt );
    work->field_9E2 = work->scale; //line not in leak
    work->param_item = 1;

    //fprintf(0,"Life=%d Faint=%d Blood=%c Area=%c \n",
    //	work->param.life, work->param.faint, work->param.blood,work->param.area);

    if( ReadNodes_800C489C( work ) < 0 ) fprintf_8008BB98( 1, aWatcharcactionpointerr_800DFCCC );

    /*
        当たりデータを初期化する
    */
    if( ( work->target =  GM_AllocTarget_8002D400() ) != NULL ) InitTarget_800C444C( work ) ;

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
	work->field_B68 = 0 ;

    work->pad.field_00 = 0; //line not in leak
    work->field_AEC    = 0; //line not in leak
    work->act_status    = 0; //line not in leak

	work->target_pos = work->nodes[ 0 ] ;
    work->target_addr = HZD_GetAddress_8005C6C4( work->control.field_2C_map->field_8_hzd, &( work->target_pos ), -1 ) ;
    work->target_map  = GM_CurrentMap_800AB9B0;

    work->alert_level = 0;
    work->visible = 1;
    work->field_B8E = 0x200;
    work->field_9E6 = 0;
    work->vision_facedir = 0;
    work->field_B94 = 0;
    work->field_B96 = 0;
    work->pad.sound = 0;
    work->pad.time  = 0;
    work->vision_length = COM_EYE_LENGTH_800E0D8C;
    work->field_BA4 = COM_NO_POINT_800C35D4;
    work->subweapon = 0;
    work->field_C48 = 0;
    work->faseout = 0;
    work->field_C2E = 1;

    work->control.field_0_mov = work->nodes[ 0 ] ;
    work->field_B7E = work->field_B7D;
    work->field_B7F = work->field_B7C;

    for ( i = 0 ; i <= 4 ; i++ )
    {
        work->modetime[i] = 0;
    }

    work->field_BA3 =  7;
    work->field_BA2 =  0;
    work->field_BA0 = -1;

    opt = GCL_GetOption_80020968( 'c' );
    if ( opt )
    {
        work->field_BA3 |= 0x10;
    }

    GM_ConfigControlRadarparam_800262EC( &work->control , 0, 0x200, COM_EYE_LENGTH_800E0D8C, 0 );
    work->start_pos = work->nodes[ 0 ] ;
    work->field_BEC = GM_CurrentMap_800AB9B0;
    addr = HZD_GetAddress_8005C6C4( work->control.field_2C_map->field_8_hzd, &( work->control.field_0_mov ), -1 );

    work->field_BE8 = addr;
    work->field_C08 = addr;
    work->field_BF0 = addr;

    work->field_C14 = work->start_pos;
}

void *NewSnakeWatcher_800C5034( int name, int where, int argc, char **argv )
{
    WatcherWork *work ;

    work = (WatcherWork *)GV_NewActor_800150E4( 4, sizeof( WatcherWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor_8001514C( &( work->actor ), ( TActorFunction )WatcherAct_800C430C, ( TActorFunction )WatcherDie_800C487C, aWatcherc_800DFCEC );
        WatcherGetResources_800C4B7C( work, name, where );
    }
    return (void *)work ;
}