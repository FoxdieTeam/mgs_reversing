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


typedef struct _PadWork
{
    int field_00;
    int press;
    int field_08;
    int tmp;
    int time;
} PadWork;

//probably similar to snainit but for enemy
typedef struct _Work
{
    GV_ACT       field_0_actor;
    CONTROL      field_20_control;
    OBJECT       field_9C_object;
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
    SVECTOR     *field_900;
    char         field_904_padding[0x220];
    int          field_B24;                  //0xB24
    unsigned int count3;                     //0xB28
    int          field_B2C;
    int          field_B30;
    PadWork      pad;                        //0xB34
    char         field_B48_padding[0x20];
    GV_ACT      *field_B68_other_actor;
    char         field_B64_padding[0x1F];
    short        field_B8C_facedir; //vision.facedir
    short        field_B8E;
    short        field_B90;
    char         field_B92_padding[0x96];
    int          sn_dir;                     //0xC28
} Work;

extern unsigned int COM_GameStatus_800E0F3C;

extern int      CheckPad_800C5A60( Work *work );
extern void     UnsetCameraActCall_800D047C();
extern void     SetCameraActCall_800D043C();

extern int      sub_800C5424( Work * work );
extern void     ActStandStill_800C5C84();
extern void     ActOverScoutD_800C85DC();

extern OBJECT   *GM_PlayerBody_800ABA20;

extern short    dword_800E0D8C;
extern short    ActTable_800C3358[];

static inline void SetMode( Work *work, void *func )
{
    work->field_8EC_func = func;
    work->field_8F4 = 0;
    work->field_20_control.field_4C_turn_vec.vz = 0;
    work->field_20_control.field_4C_turn_vec.vx = 0;
    GM_ConfigMotionAdjust_80035008( &( work->field_9C_object ), 0 );
}

static inline void SetMode2( Work *work, void *func )
{
    if ( work->field_8F0_func == NULL )
    {
        work->field_8F0_func = func;
        work->field_8F8 = 0;
    }

    work->field_20_control.field_4C_turn_vec.vz = 0;
    work->field_20_control.field_4C_turn_vec.vx = 0;
    GM_ConfigMotionAdjust_80035008( &( work->field_9C_object ), 0 );
}

static inline void UnsetMode2( Work *work )
{
    work->field_8E2 = 0;
    GM_ConfigObjectOverride_80034D30( &( work->field_9C_object ), ActTable_800C3358[STANDSTILL], 0, ACTINTERP, 0 );
    
    work->field_8F0_func = 0;
    work->field_8F8 = 0;
    work->field_8E2 = 0;
    work->field_20_control.field_4C_turn_vec.vz = 0;
    work->field_20_control.field_4C_turn_vec.vx = 0;
    
    if ( work->field_B68_other_actor )
    {
        GV_DestroyOtherActor_800151D8( work->field_B68_other_actor );
        work->field_B68_other_actor = 0;
    }
    
}

static inline void SetAction( Work *work, int n_action, int interp )
{
    work->field_8E0 = n_action ;
    GM_ConfigObjectAction_80034CD4( &( work->field_9C_object ), ActTable_800C3358[n_action], 0, interp );
}

void sub_800C6320( Work *work, int time )
{
    work->field_900->vx |= 0x9F;
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
		NewBoxKeri_800D2600( &(GM_PlayerBody_800ABA20->objs[ 0 ].world), &( work->field_20_control.field_44_movementVector ) ) ;
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
    work->field_20_control.field_4C_turn_vec.vy = work->sn_dir; //work->control.turn.vy = work->sn_dir
    work->field_B8C_facedir = work->field_20_control.field_8_rotator.vy;  //work->vision.facedir = work->control.rot.vy
}