#include "Game/linkvarbuf.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/object.h"
#include "Game/game.h"
#include "watcher.h"
#include "command.h"

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

extern ENEMY_COMMAND EnemyCommand_800E0D98;

#define TOP_COMM_TRAVEL 0
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
extern short   word_800E0D8C;
extern SVECTOR svec_800C35D4;

extern void sub_800C45D4( WatcherWork *work );
extern void sub_800C4A40( WatcherWork *work );
extern void sub_800C4B18( WatcherWork *work );
extern char sub_800CEA2C( WatcherWork *work );

extern int  ReadNodes_800C489C( WatcherWork *work );
extern void InitTarget_800C444C( WatcherWork *work );
extern int  fprintf_8008BB98(int, const char *formatStr, ...); 

#define PUTBREATH 1

extern int ENE_SetPutChar_800C979C( WatcherWork *work, int put ) ;
extern int HZD_GetAddress_8005C6C4( HZD_HDL *hzd, SVECTOR *svec, int a2 );
extern void GM_ConfigControlRadarparam_800262EC(CONTROL *pControl, short param_2, short param_3, short param_4, short param_5);

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
    opt = GCL_GetParam_80020968( 'r' );
    if ( opt )
    {
        work->field_B7D = GCL_GetNextInt_800209E8( ( char* )opt );
    }

    work->field_B82 = 0xC0;
    opt = GCL_GetParam_80020968( 'l' );
    if ( opt )
    {
        work->field_B82 = GCL_GetNextInt_800209E8( ( char* )opt );
    }

    work->field_B84 = 0xA;
    opt = GCL_GetParam_80020968( 'f' );
    if ( opt )
    {
        work->field_B84 = GCL_GetNextInt_800209E8( ( char* )opt );
    }

    work->field_B79 = 0x41;
    opt = GCL_GetParam_80020968( 'b' );
    if ( opt )
    {
        work->field_B79 = GCL_GetNextInt_800209E8( ( char* )opt );
    }

    work->local_data = 0;
    work->local_data2 = 0; 
    //work->local_data = work->local_data2 = 0 ;
    opt = GCL_GetParam_80020968( 'h' );
    if ( opt )
    {
        work->local_data = GCL_GetNextInt_800209E8( ( char* )opt );
    }

    if ( work->local_data == 3 )
    {
        opt = ( int )GCL_Get_Param_Result_80020AA4();
        if ( opt )
        {
            work->local_data2 = GCL_GetNextInt_800209E8( ( char* )opt );
        }
    }

    work->field_B81 = 0xFF;
    opt = GCL_GetParam_80020968(0x67);
    if ( opt )
    {
        work->field_B81 = GCL_GetNextInt_800209E8( ( char* )opt );
    }
    if ( work->field_B79 == 'Z' )
    {
        work->field_B81 = 0;
    }

    sub_800C4B18( work );
    opt = GCL_GetParam_80020968( 'e' );
    if ( opt )
    {
        work->field_C3C = GCL_GetNextInt_800209E8( GCL_Get_Param_Result_80020AA4() );
    }
    else
    {
        work->field_C3C = -1;
    }

    work->field_BFC = dword_800C3328[ work->field_B78 ];
    work->field_C00 = work->field_B78;
    work->field_B7C = 0xFF;
    
    
    opt = GCL_GetParam_80020968( 'n' );
    if ( opt )
    {
        GCL_GetSV_80020A14( ( char* )opt, &svec );
        if ( svec.vy < 0x7530 )
        {
            work->field_B7C = HZD_GetAddress_8005C6C4( work->control.field_2C_map->field_8_hzd, &svec, -1 );
        }
        else 
        {
            work->field_B7C = 0xFF;
        }
    }

    work->field_B7A = 'A';
    opt = GCL_GetParam_80020968( 'a' );
    if (opt != 0)
    {
        work->field_B7A = GCL_GetNextInt_800209E8( ( char* )opt );
    }

    if ( work->field_B7A == 'S' ) ENE_SetPutChar_800C979C( work, PUTBREATH ) ;
    work->scale = 4096 ;

    if ( ( opt = GCL_GetParam_80020968( 's' ) ) != NULL ) work->scale += GCL_GetNextInt_800209E8( ( char* )opt );
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
    work->field_9E4 = 1;
    work->field_B8E = 0x200;
    work->field_9E6 = 0;
    work->vision_facedir = 0;
    work->field_B94 = 0;
    work->field_B96 = 0;
    work->pad.sound = 0;
    work->pad.time  = 0;
    work->field_B90 = word_800E0D8C;
    work->field_BA4 = svec_800C35D4;
    work->field_B54 = 0;
    work->field_C48 = 0;
    work->field_C2C = 0;
    work->field_C2E = 1;

    work->control.field_0_mov = work->nodes[ 0 ] ;
    work->field_B7E = work->field_B7D;
    work->field_B7F = work->field_B7C;
    
    for ( i = 0 ; i < 5 ; i++ )
    {
        work->modetime[i] = 0;
    } 

    work->field_BA3 =  7;
    work->field_BA2 =  0;
    work->field_BA0 = -1;

    opt = GCL_GetParam_80020968( 'c' );
    if ( opt )
    {
        work->field_BA3 |= 0x10;
    }

    GM_ConfigControlRadarparam_800262EC( &work->control , 0, 0x200, word_800E0D8C, 0 );
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
    if ( !work->field_C2C )
    {
        sub_800CA0E8( work );
        GM_ActControl_80025A7C( ctrl );
        GM_ActObject2_80034B88( &( work->object ) );
        GM_ActObject2_80034B88( &( work->field_7A4 ) );
        
        DG_GetLightMatrix2_8001A5D8( &( ctrl->field_0_mov ), &( work->field_888 ) );
        
        sub_800CA07C( work );
        trgt = work->target;
        GM_Target_SetVector_8002D500( trgt, &( ctrl->field_0_mov ) );
        
        sub_8002DA14( trgt );

        if ( trgt->field_0_flags & TARGET_TOUCH )
        {
            trgt2 = &work->field_94C;
            if ( trgt2->field_0_flags & TARGET_TOUCH )
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
    ScaleMatrix( &( work->object.objs->world ), &vec );
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