#include "Game/linkvarbuf.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/object.h"
#include "Game/game.h"
#include "watcher.h"
#include "command.h"

#define EN_FASEOUT 0x10000000

void sub_800C409C( WatcherWork* work )
{
    if ( GM_GameStatus_800AB3CC & STATE_ENEMY_OFF )
    {
        if ( work->faseout == 0 )
        {
            work->hom->flag = 0 ;
            work->alert_level = 0 ;
            GM_ConfigControlAttribute_8002623C( &(work->control), 0 ) ;
            work->visible = 0 ;
            work->target->class = TARGET_AVAIL;

            work->faseout = 1 ;
            work->act_status = EN_FASEOUT ;
        }
    }
}

int	Think3_BikkuriGetUp_800CC568( WatcherWork* work )
{
    if( work->count3 == 0){
        work->pad.press |= 0x00001000  ;
    } else  if( work->count3 > 90 || work->actend ){

        return 1 ;
    }
    work->count3 ++ ;
    return 0 ;
}

extern int DirectTrace_800CC154( WatcherWork* work, int time );

int Think3_GoNext_800CC514( WatcherWork* work ) {
    if ( work->pad.time ) {
        (work->pad.press |= (  work->pad.tmp  )) ;
        work->pad.time -- ;
    }

    if ( DirectTrace_800CC154( work, 350 ) ) {
        return 1 ;
    }

    return 0 ;
}

#define T_NOISE 0
#define BW_MARK 4

extern void ENE_PutMark_800C9378( WatcherWork *work, int mark );

int	Think3_NoiseModeWatch( WatcherWork *work )
{
    if ( work->act_status & 0x00000080  )
    {
        work->pad.press |= 0x00800000  ;
    }

    if( work->count3 == 0)
    {
        if(	EnemyCommand_800E0D98.mode  == TOP_COMM_TRAVEL )
        {
            if( work->modetime[(  T_NOISE  )]  <= 1 )
            {
                work->pad.sound = (  0x88   ) ;
            }
            if( work->modetime[(  T_NOISE  )]  <= 3 )
            {
                ENE_PutMark_800C9378( work ,BW_MARK );
            }
            if ( !(work->act_status & 0x00000080 ) )
            {
                work->pad.dir = work->sn_dir;
            }
        }
        else
        {
            if( work->modetime[(  T_NOISE  )] ) return 1;
            work->pad.sound = 0x95;
            ENE_PutMark_800C9378( work ,BW_MARK );
            work->pad.dir = work->sn_dir;
        }
    }
    else
    {
        work->pad.dir = -1;
    }

    switch( work->modetime[(  T_NOISE  )] )
    {
        case 0:
            if( work->count3 >= 16)
            {
                if(	EnemyCommand_800E0D98.mode  == TOP_COMM_TRAVEL )
                {
                    if ( !(work->act_status & 0x00000080 ) )
                    {
                        work->pad.sound = 0xF1;
                    }
                }
                return 1;
            }
            break;
        case 1:
        case 2:
            if ( work->count3 >= 48 )
            {
                return 1;
            }
            break;
        case 3:
            return 1;
    }
    work->count3++;
    return 0;
}

extern int     dword_800C3328[];

extern void sub_800C45D4( WatcherWork *work );
extern void sub_800C4A40( WatcherWork *work );
extern void sub_800C4B18( WatcherWork *work );
extern char sub_800CEA2C( WatcherWork *work );

extern int  ReadNodes_800C489C( WatcherWork *work );
extern int  fprintf_8008BB98(int, const char *formatStr, ...);

#define PUTBREATH 1

extern int ENE_SetPutChar_800C979C( WatcherWork *work, int put ) ;
extern int HZD_GetAddress_8005C6C4( HZD_HDL *hzd, SVECTOR *svec, int a2 );
extern void GM_ConfigControlRadarparam_800262EC(CONTROL *pControl, short param_2, short param_3, short param_4, short param_5);

extern void sub_8002DD14(TARGET *pTarget, MATRIX *pMatrix) ;

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
    GM_SetTarget_8002DC74( target2, ( TARGET_DOWN | TARGET_SEEK | TARGET_CAPTURE ), 2, &ENEMY_TOUCH_SIZE_800C35C4 );
    GM_Target_8002DCCC( target2, 7, 5, 0, 0, &ENEMY_TOUCH_FORCE_800C35CC );
}

void WatcherGetResources_800C4B7C( WatcherWork *work, int name, int where )
{
    SVECTOR svec;
    int addr;
    int opt;
    int i;

    sub_800C45D4( work ) ;
    work->field_B78 = sub_800CEA2C( work ) ;

    if ( work->field_B78  << 24  )
    {
       printf( "Err not enough work !!\n" ) ;
    }

    sub_800C4A40( work ) ;

    work->field_B7D = 0;
    opt = GCL_GetOption_80020968( 'r' );
    if ( opt )
    {
        work->field_B7D = GCL_StrToInt_800209E8( ( char* )opt );
    }

    //life
    work->param_life = 192;
    opt = GCL_GetOption_80020968( 'l' );
    if ( opt )
    {
        work->param_life = GCL_StrToInt_800209E8( ( char* )opt );
    }

    //faint
    work->param_faint = 10;
    opt = GCL_GetOption_80020968( 'f' );
    if ( opt )
    {
        work->param_faint = GCL_StrToInt_800209E8( ( char* )opt );
    }

    //blood
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
    opt = GCL_GetOption_80020968(0x67);
    if ( opt )
    {
        work->field_B81 = GCL_StrToInt_800209E8( ( char* )opt );
    }
    if ( work->param_blood == 'Z' )
    {
        work->field_B81 = 0;
    }

    sub_800C4B18( work );
    opt = GCL_GetOption_80020968( 'e' );
    if ( opt )
    {
        work->field_C3C = GCL_StrToInt_800209E8( GCL_Get_Param_Result_80020AA4() );
    }
    else
    {
        work->field_C3C = -1;
    }

    work->field_BFC = dword_800C3328[ work->field_B78 ];
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

    //area
    work->param_area = 'A';
    opt = GCL_GetOption_80020968( 'a' );
    if (opt != 0)
    {
        work->param_area = GCL_StrToInt_800209E8( ( char* )opt );
    }

    //scale?
    if ( work->param_area == 'S' ) ENE_SetPutChar_800C979C( work, PUTBREATH ) ;
    work->scale = 4096 ;

    if ( ( opt = GCL_GetOption_80020968( 's' ) ) != NULL ) work->scale += GCL_StrToInt_800209E8( ( char* )opt );
    work->field_9E2 = work->scale; //line not in leak
    work->param_item = 1;

    //fprintf(0,"Life=%d Faint=%d Blood=%c Area=%c \n",
    //	work->param.life, work->param.faint, work->param.blood,work->param.area);

    if( ReadNodes_800C489C( work ) < 0 ) fprintf_8008BB98( 1,"watchar.c : action point Err\n" );

    if( ( work->target =  GM_AllocTarget_8002D400() ) != NULL ) InitTarget_800C444C( work ) ;

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
    work->vision_facedir = COM_EYE_LENGTH_800E0D8C;
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


extern void sub_800C4814();

void WatcherDie_800C487C(void)
{
    sub_800C4814();
}

extern void sub_800C410C( WatcherWork* work );
extern void sub_800CA0E8( WatcherWork* work );
extern void sub_800CA07C( WatcherWork* work );
extern void sub_800C41B4( WatcherWork* work );

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

    sub_800C410C( work );
    if ( !work->faseout )
    {
        sub_800CA0E8( work );
        GM_ActControl_80025A7C( ctrl );
        GM_ActObject2_80034B88( &( work->body ) );
        GM_ActObject2_80034B88( &( work->field_7A4 ) );

        DG_GetLightMatrix2_8001A5D8( &( ctrl->field_0_mov ), &( work->field_888 ) );

        sub_800CA07C( work );
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
    sub_800C41B4( work );
    vec.vx = vec.vz = work->scale;
    vec.vy = work->field_9E2;
    ScaleMatrix( &( work->body.objs->world ), &vec );
}

void *NewSnakeWatcher_800C5034( int name, int where, int argc, char **argv )
{
    WatcherWork *work ;

    work = (WatcherWork *)GV_NewActor_800150E4( 4, sizeof( WatcherWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor_8001514C( &( work->actor ), ( TActorFunction )WatcherAct_800C430C, ( TActorFunction )WatcherDie_800C487C, "watcher.c" );
        WatcherGetResources_800C4B7C( work, name, where );
    }
    return (void *)work ;
}