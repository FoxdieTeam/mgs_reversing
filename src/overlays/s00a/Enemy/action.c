#include "Game/linkvarbuf.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/object.h"
#include "Game/game.h"

#define COM_ST_DANBOWL 0x2000
#define SP_DANBOWLKERI 0x400000

#define ACTINTERP   4

#define STANDSTILL  0
#define DANBOWLKERI 17
#define DANBOWLPOSE 18

typedef struct _WatcherPad
{
    int field_00;
    int press;
    int field_08;
    int tmp;
    int time;
} WatcherPad;

typedef struct _WatcherWork
{
    GV_ACT       actor;
    CONTROL      control;                    //0x20
    OBJECT       object;                     //0x9C
    char         field_C0_padding[0x674];    //0xC0
    short        field_734;                  //0x734
    short        field_736;                  //0x736
    char         field_738[0x6C];            //0x738
    OBJECT       field_7A4;                  //0x7A4
    char         field_7C8_padding[0xC0];    //0x7C8
    MATRIX       field_888;                  //0x888
    int          field_8A8;                  //0x8A8
    int          field_8AC;                  //0x8AC
    int          field_8B0;                  //0x8B0
    int          field_8B4;                  //0x8B4
    int          field_8B8;                  //0x8B8
    int          field_8BC;                  //0x8BC
    int          field_8C0;                  //0x8C0
    int          field_8C4;                  //0x8C4
    int          field_8C8;                  //0x8C8
    int          field_8CC;                  //0x8CC
    int          field_8D0;                  //0x8D0
    int          field_8D4;                  //0x8D4
    int          field_8D8;                  //0x8D8
    int          field_8DC;                  //0x8DC
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
    char         field_904_padding[0x48];
    TARGET       field_94C;                  //0x94C
    char         field_994_padding[0x4C];    //0x994
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
    WatcherPad   pad;                        //0xB34
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
} WatcherWork;

extern unsigned int COM_GameStatus_800E0F3C;

extern void     UnsetCameraActCall_800D047C();
extern void     SetCameraActCall_800D043C();

extern int      sub_800C5424( WatcherWork * work );

extern OBJECT   *GM_PlayerBody_800ABA20;

extern short    dword_800E0D8C;
extern short    ActTable_800C3358[];

extern void ActionUnknown1_800C841C();
extern void ActionUnknown2_800C84FC();
extern void ActOverScoutD_800C85DC();
extern void ActionUnknown4_800C8688();
extern void ActionUnknown5_800C8734();
extern void ActionUnknown6_800C87FC();
extern void ActionUnknown7_800C88D8();
extern void ActionUnknown8_800C8990();
extern void ActionUnknown9_800C8A6C();
extern void ActionUnknown10_800C8C98();
extern void ActionUnknown11_800C8DF8();
extern void ActionUnknown12_800C615C(); 
extern void ActionUnknown13_800C6164();
extern void ActionUnknown14_800C624C();
extern void ActionUnknown15_800C6320();
extern void ActionUnknown16_800C65A8();

extern void ActStandStill_800C5C84();



static inline void SetMode( WatcherWork *work, void *func )
{
    work->field_8EC_func = func;
    work->field_8F4 = 0;
    work->control.field_4C_turn_vec.vz = 0;
    work->control.field_4C_turn_vec.vx = 0;
    GM_ConfigMotionAdjust_80035008( &( work->object ), 0 );
}

static inline void SetMode2( WatcherWork *work, void *func )
{
    if ( work->field_8F0_func == NULL )
    {
        work->field_8F0_func = func;
        work->field_8F8 = 0;
    }

    work->control.field_4C_turn_vec.vz = 0;
    work->control.field_4C_turn_vec.vx = 0;
    GM_ConfigMotionAdjust_80035008( &( work->object ), 0 );
}

static inline void UnsetMode2( WatcherWork *work )
{
    work->field_8E2 = 0;
    GM_ConfigObjectOverride_80034D30( &( work->object ), ActTable_800C3358[STANDSTILL], 0, ACTINTERP, 0 );
    
    work->field_8F0_func = 0;
    work->field_8F8 = 0;
    work->field_8E2 = 0;
    work->control.field_4C_turn_vec.vz = 0;
    work->control.field_4C_turn_vec.vx = 0;
    
    if ( work->act_status )
    {
        GV_DestroyOtherActor_800151D8( work->act_status );
        work->act_status = 0;
    }
    
}

static inline void SetAction( WatcherWork *work, int n_action, int interp )
{
    work->field_8E0 = n_action ;
    GM_ConfigObjectAction_80034CD4( &( work->object ), ActTable_800C3358[n_action], 0, interp );
}

int CheckPad_800C5A60( WatcherWork *work )
{
    int press = work->pad.press;

    if ( press & 0x01 )
    {
        SetMode2( work, ActionUnknown1_800C841C );
        return 0;
    }

    if ( press & 0x02 )
    {
        SetMode2( work, ActionUnknown2_800C84FC );
        return 0;
    }

    if ( press & 0x04 )
    {
        SetMode2( work, ActOverScoutD_800C85DC );
        return 0;
    }

    if ( press & 0x2000 )
    {
        SetMode2( work, ActionUnknown4_800C8688 );
        return 0;
    }

    if ( press & 0x40 )
    {
        SetMode2( work, ActionUnknown5_800C8734 );
        return 0;
    }

    if ( press & 0x80 )
    {
        SetMode2( work, ActionUnknown6_800C87FC );
        return 0;
    }

    if ( press & 0x400 )
    {
        SetMode2( work, ActionUnknown7_800C88D8 );
        return 0;
    }

    if ( press & 0x800 )
    {
        SetMode2( work, ActionUnknown8_800C8990 );
        return 0;
    }

    if ( press & 0x200 )
    {
        SetMode2( work, ActionUnknown9_800C8A6C );
        return 0;
    }

    if ( press & 0x800000 )
    {
        SetMode2( work, ActionUnknown10_800C8C98 );
        return 0;
    }
    
    if ( press & 0x1000000 )
    {
        SetMode2( work, ActionUnknown11_800C8DF8 );
        return 0;
    }

    if ( press & 0x100 )
    {
        SetMode( work, ActionUnknown12_800C615C );
        return 1;
    }

    if ( press & 0x20 )
    {
        SetMode( work, ActionUnknown13_800C6164 );
        return 1;
    }

    if ( press & 0x2000000 )
    {
        SetMode( work, ActionUnknown14_800C624C );
        return 1;
    }

    if ( press & 0x400000 )
    {
        SetMode( work, ActionUnknown15_800C6320 );
        
        return 1;
    }

    if ( press & 0x30000 )
    {
        SetMode( work, ActionUnknown16_800C65A8 );
        work->field_734 = 0;
        return 1;
    }
    
    return 0;
}

void sub_800C6320( WatcherWork *work, int time )
{
    work->target->field_0_flags |= 0x9F;
    work->field_B90 = dword_800E0D8C;
    work->field_8E6 = 0;
    
    if ( sub_800C5424( work ) )
    {
        UnsetCameraActCall_800D047C( );
        COM_GameStatus_800E0F3C &= ~COM_ST_DANBOWL ;
        printf(" ~COM_ST_DANBOWL 0 !! \n ") ;
        return;
    }
    
    if ( !(work->pad.press & SP_DANBOWLKERI) )
    {
        if ( !(CheckPad_800C5A60( work )) ) 
        {
    		SetMode( work, ActStandStill_800C5C84 ) ;
    	}
    	UnsetCameraActCall_800D047C( );
    	COM_GameStatus_800E0F3C &= ~COM_ST_DANBOWL ;
        printf(" ~COM_ST_DANBOWL 1 !! \n ") ;
    	return ;
	}

    if ( time == 0 ) {
		SetMode2( work, ActOverScoutD_800C85DC ) ;
		SetAction( work, STANDSTILL, ACTINTERP ) ;
		SetCameraActCall_800D043C( );
	}

	if ( time == 60 ) {
		UnsetMode2( work ) ;
		SetAction( work, DANBOWLKERI, ACTINTERP ) ;
	}

	if ( time == 78 ) {
		extern	void	*NewBoxKeri_800D2600( MATRIX	*, SVECTOR	* ) ;
		NewBoxKeri_800D2600( &(GM_PlayerBody_800ABA20->objs[ 0 ].world), &( work->control.field_44_movementVector ) ) ;
	}

    if ( time == 100 ) {
        //AN_HeadMarkMini( &(GM_PlayerBody_800ABA20->objs->objs[ 1 ].world), 2 ) ;
		SetAction( work, DANBOWLPOSE, ACTINTERP ) ;
	}

    if ( time == 130 ) {
		GM_CurrentItemId = ITEM_NONE ; //Actually should be named GM_Item and IT_None
	}

    if ( time > 150  ) {
		UnsetCameraActCall_800D047C( );
		work->actend = 1 ;
		SetMode( work, ActStandStill_800C5C84 ) ;
		COM_GameStatus_800E0F3C &= ~COM_ST_DANBOWL ;
        printf(" ~COM_ST_DANBOWL 2 !! \n ");
		return ;
	}
    work->control.field_4C_turn_vec.vy = work->sn_dir; //work->control.turn.vy = work->sn_dir
    work->vision_facedir = work->control.field_8_rotator.vy;  //work->vision.facedir = work->control.rot.vy
}