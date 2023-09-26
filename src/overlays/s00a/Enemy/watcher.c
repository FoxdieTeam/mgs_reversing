#include "Game/linkvarbuf.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/object.h"
#include "Game/game.h"

typedef struct _PadWork
{
    int field_00;
    int press;
    int field_08;
    int tmp;
    int time;
} PadWork;

typedef struct _Work
{
    GV_ACT       actor;
    CONTROL      control;                    //0x20
    OBJECT       object;                     //0x9C
    char         field_C0_padding[0x820];
    short        field_8E0;
    short        field_8E2;
    short        field_8E4;
    short        field_8E6;
    char         field_8E8_padding[0x04];
    void*        field_8EC_func;
    void*        field_8F0_func;
    int          field_8F4;
    int          field_8F8;
    int          actend;                     //0x8FC
    TARGET      *target;                     //0x900
    char         field_904_padding[0xDC];
    short        scale;                      //0x9E0
    short        field_9E2;                  //0x9E2
    short        field_9E4;                  //0x9E4
    short        field_9E6;                  //0x9E6
    int          field_9E8;                  //0x9E8
    SVECTOR      nodes[0x20];                //0x9EC
    int          field_AEC;                  //0xAEC
    char         field_AF0_padding[0x2C];    //0xAF0
    int          field_B1C;                  //0xB1C
    short        think1;                     //0xB20
    short        think2;                     //0xB22
    short        think3;                     //0xB24
    short        think4;                     //0xB26
    unsigned int count3;                     //0xB28
    int          t_count;                    //0xB2C
    int          l_count;                    //0xB30
    PadWork      pad;                        //0xB34
    short        field_B48;                  //0xB48
    short        field_B4A;                  //0xB48
    short        field_B4C;                  //0xB48
    short        field_B4E;                  //0xB48
    int          field_B50;                  //0xB50
    int          field_B54;                  //0xB54
    int          field_B58;                  //0xB58
    int          field_B5C;                  //0xB5C
    int          next_node;                  //0xB60
    int          search_flag;                //0xB64
    GV_ACT      *act_status;                 //0xB68
    int          mark_time;                  //0xB6C
    int          field_B70;                  //0xB70
    int          field_B74;                  //0xB74
    signed char  field_B78;                  //0xB78
    signed char  field_B79;                  //0xB79
    signed char  field_B7A;                  //0xB7A
    char         field_B7B;                  //0xB7B
    char         field_B7C;                  //0xB7C
    char         field_B7D;                  //0xB7D
    char         field_B7E;                  //0xB7E
    char         field_B7F;                  //0xB7F
    char         param_item;                 //0xB80  //param.item (should be struct)
    char         field_B81;                  //0xB81
    short        field_B82;                  //0xB82
    short        field_B84;                  //0xB84
    char         local_data;                 //0xB86
    char         local_data2;                //0xB87
    int          field_B88;                  //0xB88
    short        vision_facedir;             //0xB8C  //vision.facedir (should be struct)
    short        field_B8E;
    short        field_B90;
    short        field_B92;
    short        field_B94;
    short        field_B96;
    int          alert_level;                //0xB98
    char         field_B9C[4];
    signed char  field_BA0;                  //0xBA0
    char         field_BA1;                  //0xBA1
    char         field_BA2;                  //0xBA2
    char         field_BA3;                  //0xBA3
    SVECTOR      field_BA4;                  //0xBA4
    char         field_BAC_padding[0x2C];    //0xBAC
    SVECTOR      start_pos;                  //0xBD8
    SVECTOR      target_pos;                 //0xBE0
    int          field_BE8;                  //0xBE8
    int          field_BEC;                  //0xBEC
    int          field_BF0;                  //0xBF0
    int          target_addr;                //0xBF4
    int          target_map;                 //0xBF8
    int          field_BFC;                  //0xBFC
    int          field_C00;                  //0xC00
    int          field_C04;                  //0xC04
    int          field_C08;                  //0xC08
    int          field_C0C;                  //0xC0C
    int          field_C10;                  //0xC10
    SVECTOR      field_C14;                  //0xC14
    int          field_C1C;                  //0xC1C
    int          field_C20;                  //0xC20
    int          field_C24;                  //0xC24
    int          sn_dir;                     //0xC28
    short        field_C2C;                  //0xC2C
    short        field_C2E;                  //0xC2E
    int          field_C30;                  //0xC30
    int          field_C34;                  //0xC34
    int          field_C38;                  //0xC38
    int          field_C3C;                  //0xC3C
    int          field_C40;                  //0xC40
    int          field_C44;                  //0xC44
    short        field_C48;                  //0xC48
    short        field_C4A;                  //0xC4A
} Work;

int	Think3_BikkuriGetUp_800CC568( Work* work )
{
    if( work->count3 == 0){
        work->pad.press |= 0x00001000  ;
    } else  if( work->count3 > 90 || work->actend ){
 
        return 1 ;
    }
    work->count3 ++ ;
    return 0 ;
}

extern int DirectTrace_800CC154( Work* work, int time );

int Think3_GoNext_800CC514( Work* work ) {
    if ( work->pad.time ) {
        (work->pad.press |= (  work->pad.tmp  )) ;
        work->pad.time -- ;
    }

    if ( DirectTrace_800CC154( work, 350 ) ) {
        return 1 ;
    }

    return 0 ;
}

extern int     dword_800C3328[];
extern short   word_800E0D8C;
extern SVECTOR svec_800C35D4;

extern void sub_800C45D4( Work *work );
extern void sub_800C4A40( Work *work );
extern void sub_800C4B18( Work *work );
extern char sub_800CEA2C( Work *work );

extern int  ReadNodes_800C489C( Work *work );
extern void InitTarget_800C444C( Work *work );
extern int  fprintf_8008BB98(int, const char *formatStr, ...); 

#define PUTBREATH 1

extern int ENE_SetPutChar_800C979C( Work *work, int put ) ;
extern int HZD_GetAddress_8005C6C4( HZD_HDL *hzd, SVECTOR *svec, int a2 );
extern void GM_ConfigControlRadarparam_800262EC(CONTROL *pControl, short param_2, short param_3, short param_4, short param_5);

void WatcherGetResources_800C4B7C( Work *work, int name, int where )
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
	work->act_status = 0 ;
    
    work->pad.field_00 = 0; //line not in leak
    work->field_AEC    = 0; //line not in leak
    work->field_B70    = 0; //line not in leak  
    
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
    work->field_B4A = 0;
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
        work->field_B9C[i] = 0;
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

extern int WatcherAct_800C430C( Work *work );

void *NewSnakeWatcher_800C5034( int name, int where, int argc, char **argv )
{
    Work *work ;

    work = (Work *)GV_NewActor_800150E4( 4, sizeof( Work ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor_8001514C( &( work->actor ), ( TActorFunction )WatcherAct_800C430C, ( TActorFunction )WatcherDie_800C487C, "watcher.c" );
        WatcherGetResources_800C4B7C( work, name, where );
    }
    return (void *)work ;
}