#include "Game/linkvarbuf.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/object.h"
#include "Game/game.h"
#include "watcher.h"

#define COM_ST_DANBOWL 0x2000
#define SP_DANBOWLKERI 0x400000

#define ACTINTERP   4

#define STANDSTILL  0
#define GRENADE     7
#define DANBOWLKERI 17
#define DANBOWLPOSE 18

#define ENEMY_SIDE 2

#define WEAPON_TAKE 1

#define SE_PINNUKI 0x2C

//unsure
#define WEAPON_TRIG  2
#define WEAPON_TRIG2 4

extern unsigned int COM_GameStatus_800E0F3C;

extern void     UnsetCameraActCall_800D047C();
extern void     SetCameraActCall_800D043C();

extern int CheckDamage_800C5424( WatcherWork *work );

extern OBJECT   *GM_PlayerBody_800ABA20;


extern short    EYE_LENGTH_800E0D8C;
extern short    ActTable_800C3358[];

extern int      GM_PlayerStatus_800ABA50;
extern SVECTOR  GM_PlayerPosition_800ABA10;


extern void ActUnknown1_800C841C();
extern void ActUnknown2_800C84FC();
extern void ActOverScoutD_800C85DC();
extern void ActUnknown4_800C8688();
extern void ActUnknown5_800C8734();
extern void ActUnknown6_800C87FC();
extern void ActUnknown7_800C88D8();
extern void ActUnknown8_800C8990();
extern void ActUnknown9_800C8A6C();
extern void ActUnknown10_800C8C98();
extern void ActUnknown11_800C8DF8();
extern void ActUnknown12_800C615C(); 
extern void ActUnknown13_800C6164();
extern void ActUnknown14_800C624C();
extern void ActUnknown15_800C6320();
extern void ActUnknown16_800C65A8();

extern void ActStandStill_800C5C84();



static inline void SetMode( WatcherWork *work, void *func )
{
    work->field_8EC_func = func;
    work->field_8F4 = 0;
    work->control.field_4C_turn_vec.vz = 0;
    work->control.field_4C_turn_vec.vx = 0;
    GM_ConfigMotionAdjust_80035008( &( work->body ), 0 );
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
    GM_ConfigMotionAdjust_80035008( &( work->body ), 0 );
}

static inline void UnsetMode2( WatcherWork *work )
{
    work->field_8E2 = 0;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C3358[STANDSTILL], 0, ACTINTERP, 0 );
    
    work->field_8F0_func = 0;
    work->field_8F8 = 0;
    work->field_8E2 = 0;
    work->control.field_4C_turn_vec.vz = 0;
    work->control.field_4C_turn_vec.vx = 0;
    
    if ( work->field_B68 )
    {
        GV_DestroyOtherActor_800151D8( work->field_B68 );
        work->field_B68 = 0;
    }
    
}

static inline void SetAction( WatcherWork *work, int n_action, int interp )
{
    work->field_8E0 = n_action ;
    GM_ConfigObjectAction_80034CD4( &( work->body ), ActTable_800C3358[n_action], 0, interp );
}

static inline void UnsetAction( WatcherWork *work, int n_action )
{
    work->field_8E2 = n_action;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C3358[n_action], 0, ACTINTERP, 0x3FE );
}

static inline void UnsetAction2( WatcherWork *work )
{
    work->field_8E2 = 0;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C3358[STANDSTILL], 0, ACTINTERP, 0 );
    GV_DestroyOtherActor_800151D8( work->subweapon );
}

//should be in target.h
static inline void SetTargetClass( TARGET *target, unsigned int flag )
{
    target->field_0_flags |= ( flag | TARGET_AVAIL );
}

int CheckPad_800C5A60( WatcherWork *work )
{
    int press = work->pad.press;

    if ( press & 0x01 )
    {
        SetMode2( work, ActUnknown1_800C841C );
        return 0;
    }

    if ( press & 0x02 )
    {
        SetMode2( work, ActUnknown2_800C84FC );
        return 0;
    }

    if ( press & 0x04 )
    {
        SetMode2( work, ActOverScoutD_800C85DC );
        return 0;
    }

    if ( press & 0x2000 )
    {
        SetMode2( work, ActUnknown4_800C8688 );
        return 0;
    }

    if ( press & 0x40 )
    {
        SetMode2( work, ActUnknown5_800C8734 );
        return 0;
    }

    if ( press & 0x80 )
    {
        SetMode2( work, ActUnknown6_800C87FC );
        return 0;
    }

    if ( press & 0x400 )
    {
        SetMode2( work, ActUnknown7_800C88D8 );
        return 0;
    }

    if ( press & 0x800 )
    {
        SetMode2( work, ActUnknown8_800C8990 );
        return 0;
    }

    if ( press & 0x200 )
    {
        SetMode2( work, ActUnknown9_800C8A6C );
        return 0;
    }

    if ( press & 0x800000 )
    {
        SetMode2( work, ActUnknown10_800C8C98 );
        return 0;
    }
    
    if ( press & 0x1000000 )
    {
        SetMode2( work, ActUnknown11_800C8DF8 );
        return 0;
    }

    if ( press & 0x100 )
    {
        SetMode( work, ActUnknown12_800C615C );
        return 1;
    }

    if ( press & 0x20 )
    {
        SetMode( work, ActUnknown13_800C6164 );
        return 1;
    }

    if ( press & 0x2000000 )
    {
        SetMode( work, ActUnknown14_800C624C );
        return 1;
    }

    if ( press & 0x400000 )
    {
        SetMode( work, ActUnknown15_800C6320 );        
        return 1;
    }

    if ( press & 0x30000 )
    {
        SetMode( work, ActUnknown16_800C65A8 );
        work->field_734 = 0;
        return 1;
    }
    
    return 0;
}

void ActUnknown15_800C6320( WatcherWork *work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG ) ;
    work->vision_length = EYE_LENGTH_800E0D8C;
    work->field_8E6 = 0;
    
    if ( CheckDamage_800C5424( work ) )
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

void ActGrenade_800C67EC( WatcherWork *work, int time )
{
    int check = 0;
    SetTargetClass( work->target, TARGET_FLAG ) ;
    work->vision_length = EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        extern	void	*NewGrenadeEnemy( CONTROL *, OBJECT *, int, unsigned int *, SVECTOR *, int ) ;

        work->subweapon = NewGrenadeEnemy( &(work->control), &(work->body), 9,
                                            &(work->trigger), &GM_PlayerPosition_800ABA10, ENEMY_SIDE ) ;

        if ( GM_PlayerStatus_800ABA50 & 2 )
        {
            SetAction( work, GRENADE, ACTINTERP );
        }
        else
        {
            SetAction( work, STANDSTILL, ACTINTERP );
            UnsetAction( work, GRENADE );
        }
    }

    if ( time > ACTINTERP ) {
        work->trigger |= WEAPON_TAKE ;
    }

    if ( time == 17 ) {
        GM_SeSet_80032858( &( work->control.field_0_mov ), SE_PINNUKI ) ;
    }

    if ( time == 45 ) {
        if ( work->field_8E0 == 7 )
        {
            work->trigger |= WEAPON_TRIG2 ;
        }
        else
        {
            work->trigger |= WEAPON_TRIG ;
        }
    }

    if ( CheckDamage_800C5424( work ) ){
        UnsetAction2( work );
        return ;
    }

    if ( work->field_8E0 == 7 )
    {
        if ( work->body.field_1A )
        {
            check = 1;
        }
    }
    else
    {
        if (work->body.field_1C)
        {
            check = 1;
        }
    }

    if ( check )
    {
        work->actend = 1;
        UnsetAction2( work );
        SetMode( work, ActUnknown16_800C65A8 );
    }
    
}