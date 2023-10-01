#include "Game/linkvarbuf.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/object.h"
#include "Game/game.h"
#include "command.h"
#include "action.h"

#define ENEMY_SIDE 2

#define WEAPON_TAKE 1

#define SE_PINNUKI 0x2C

#define WEAPON_TRIG  2
#define WEAPON_TRIG2 4

extern void     UnsetCameraActCall_800D047C();
extern void     SetCameraActCall_800D043C();
extern int      CheckDamage_800C5424( WatcherWork *work );
extern int      sub_800C580C( int dir, int val );

extern OBJECT   *GM_PlayerBody_800ABA20;
extern int       GM_PlayerStatus_800ABA50;
extern SVECTOR   GM_PlayerPosition_800ABA10;

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

extern int GV_VecDir2_80016EF8(SVECTOR *vec);
extern int GV_NearExp4P_80026554(int from, int to);

extern SVECTOR DG_ZeroVector_800AB39C;

void ActStandStill_800C5C84(WatcherWork* work, int time ) 
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->act_status |= 1;
    
    if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
    {
        work->target->class |= TARGET_C4 ;
    }
    
    work->vision_length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        SetAction( work, STANDSTILL, ACTINTERP );
    }

    if ( CheckDamage_800C5424( work ) || CheckPad_800C5A60( work ) )
    {
		UnsetMode2( work ) ;
		return ;        
    }
    

    if ( work->pad.dir >= 0 )
    {
        if ( GV_DiffDirAbs_8001706C( work->control.field_8_rotator.vy, work->pad.dir ) < 0x100 )
        {
            if ( work->pad.field_08 & 0x1 )
            {
                SetAction( work, ACTION2, ACTINTERP );
            }
            else
            {
                SetAction( work, ACTION1, ACTINTERP );
            }
            SetMode( work, ActUnknown_800C5E48 );
            
        }
        else
        {
            work->control.field_4C_turn_vec.vy = work->pad.dir;
        }
    }
    work->vision_facedir = GV_NearExp4P_80026554( work->vision_facedir, work->control.field_8_rotator.vy );
}

void ActUnknown_800C5E48( WatcherWork* work, int time )
{
    int x, z;
    int s0;
    int interval;
    int tmp;
    int dist;
    CONTROL * ctrl;
    int dir;
    int field_8E0;
    SVECTOR* svec;

    SetTargetClass( work->target, TARGET_FLAG );

    if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
    {
        work->target->class |= TARGET_C4 ;
    }

    work->vision_length = COM_EYE_LENGTH_800E0D8C ;
    work->act_status |= 0x100;
    work->control.field_44_movementVector = DG_ZeroVector_800AB39C;

    if ( CheckDamage_800C5424( work ) || CheckPad_800C5A60( work ) )
    {
		UnsetMode2( work ) ;
		return ;        
    }

    dist = -1;
    ctrl = &(work->control );
    dir = work->pad.dir;
    field_8E0 = work->field_8E0;
    svec = work->control.field_60_vecs_ary;

    if ( (work->pad.field_08 & 0x1) && ( work->field_8E0 != ACTION2 ) )
    {
        SetAction( work, ACTION2, ACTINTERP );
    }

    if ( dir >= 0 )
    {
        s0 = ctrl->field_58;
        if ( s0 > 0 )
        {
            dist = GV_VecDir2_80016EF8( svec );
    
            if ( s0 >= 2 )
            {
                tmp = GV_VecDir2_80016EF8( &ctrl->field_60_vecs_ary[1] );
                if ( GV_DiffDirAbs_8001706C( dir, tmp ) < GV_DiffDirAbs_8001706C( dir, dist ) )
                {
                    dist = tmp;
                }
            }
        }
    }
    
    if ( dir < 0 )
    {
        SetMode( work, ActStandStill_800C5C84);
        UnsetMode2( work ) ;
        return;
    }

    if ( time != 1 )
    {
        switch ( sub_800C580C( dir, dist ) )
        {
        case 1:
            dir = (dist - 1024) & 0xFFF;
            break;
        case 2:
            dir = (dist + 1024) & 0xFFF;
            break;
        }
    }

    if ( !work->body.objs->bound_mode )
    {     
        ctrl->field_8_rotator.vy   = dir;
        ctrl->field_4C_turn_vec.vy = dir;
        work->vision_facedir = GV_NearExp4P_80026554( work->vision_facedir, work->control.field_8_rotator.vy );
    }
    else
    {  
        ctrl->field_4C_turn_vec.vy = dir;
        work->vision_facedir = work->control.field_8_rotator.vy;
    }

    interval = 0;

    if ( field_8E0 == 1 )
    {
        interval = 50;
    }
    else if ( field_8E0 == 2 )
    {
        interval = 100;
    }

    x = interval * rsin( dir );
    
    if ( x < 0 )
    {
        x += 0xFFF;
    }

    ctrl->field_44_movementVector.vx = x >> 12;

    z = interval * rcos( dir );
    
    if ( z < 0 )
    {
        z += 0xFFF;
    }

    ctrl->field_44_movementVector.vz = z >> 12;   

    if ( !time )
    {
        work->field_8E6 = 0;
    }
}

void ActUnknown12_800C615C( WatcherWork *work, int time )
{
}

void ActUnknown13_800C6164( WatcherWork *work, int time )
{
    CONTROL *ctrl;

    ctrl = &( work->control );
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision_length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        SetAction( work, ACTION16, ACTINTERP );
    }

    if ( CheckDamage_800C5424( work ) )
    {
		return ;
    }

    if ( work->body.is_end || !( work->pad.press & 0x20 ) )
    {
        SetMode( work, ActStandStill_800C5C84 );
        return;
    }

    ctrl->field_4C_turn_vec.vy = work->sn_dir;
    ctrl->field_44_movementVector.vx = 0;
    ctrl->field_44_movementVector.vz = 0;
    work->vision_facedir = work->control.field_8_rotator.vy;
}

void ActUnknown14_800C624C( WatcherWork *work, int time )
{
    CONTROL *ctrl;

    ctrl = &( work->control );
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision_length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        SetAction( work, ACTION13, ACTINTERP );
    }

    if ( CheckDamage_800C5424( work ) )
    {
		return ;
    }

    if ( !( work->pad.press & 0x2000000 ) )
    {
        SetMode( work, ActStandStill_800C5C84 );
        return;
    }

    ctrl->field_4C_turn_vec.vy = work->pad.dir;
    ctrl->field_44_movementVector.vx = 0;
    ctrl->field_44_movementVector.vz = 0;
    work->vision_facedir = work->control.field_8_rotator.vy;
}

void ActUnknown15_800C6320( WatcherWork *work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG ) ;
    work->vision_length = COM_EYE_LENGTH_800E0D8C;
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

extern void sub_800C6724();
extern void sub_800C67E4();
extern void sub_800C6A40();
extern void sub_800C5860( WatcherWork *work );

void ActUnknown16_800C65A8( WatcherWork* work, int time )
{
    int press;
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision_length = COM_EYE_LENGTH_800E0D8C ;
    press = work->pad.press;
    
    if ( time == 0 )
    {
        if ( press & 0x10000 )
        {
            SetAction( work, ACTION3, ACTINTERP ) ;
        }
        else
        {
            SetAction( work, ACTION5, ACTINTERP );
        }        
        GM_ConfigMotionAdjust_80035008( &( work->body ), &work->field_724 ) ;
    }

    sub_800C5860( work );
    if ( CheckDamage_800C5424( work ) )
    {
		return ;        
    }

    if ( !(press & 0x30000) )
    {
        SetMode( work, ActStandStill_800C5C84 ) ;
        return ;
    }

    if ( press & 0x40000 )
    {
        SetModeFields( work, sub_800C6724) ;
        return;
    }

    if ( press & 0x80000 )
    {
        SetModeFields( work, sub_800C67E4) ;
        return;
    }    
    
    if ( press & 0x100000 )
    {
        SetMode( work, ActGrenade_800C67EC ) ;
        return;
    }    

    if ( press & 0x200000 )
    {
        SetModeFields( work, sub_800C6A40 ) ;
        return;
    } 

    work->control.field_4C_turn_vec.vy = work->sn_dir;
    work->control.field_44_movementVector.vx = 0;
    work->control.field_44_movementVector.vz = 0;
    work->vision_facedir = work->control.field_8_rotator.vy;
}

extern int ENE_SetPutChar_800C979C( WatcherWork *work, int put ) ;

void sub_800C6724( WatcherWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision_length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        SetAction( work, ACTION4, 0 ) ;
        ENE_SetPutChar_800C979C( work, 3 ) ;
        GM_ConfigMotionAdjust_80035008( &( work->body ), &work->field_724 ) ;
    }

    sub_800C5860( work );
    work->control.field_4C_turn_vec.vy = work->sn_dir;

    if ( CheckDamage_800C5424( work ) )
    {
		return ;        
    }
    
    SetModeFields( work, ActUnknown16_800C65A8 );
    work->control.field_44_movementVector.vx = 0;
    work->control.field_44_movementVector.vz = 0;
}

void sub_800C67E4( WatcherWork *work, int time )
{

}

void ActGrenade_800C67EC( WatcherWork *work, int time )
{
    int check = 0;
    SetTargetClass( work->target, TARGET_FLAG ) ;
    work->vision_length = COM_EYE_LENGTH_800E0D8C ;

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

    if ( time > ACTINTERP )
    {
        work->trigger |= WEAPON_TAKE ;
    }

    if ( time == 17 )
    {
        GM_SeSet_80032858( &( work->control.field_0_mov ), SE_PINNUKI ) ;
    }

    if ( time == 45 )
    {
        if ( work->field_8E0 == 7 )
        {
            work->trigger |= WEAPON_TRIG2 ;
        }
        else
        {
            work->trigger |= WEAPON_TRIG ;
        }
    }

    if ( CheckDamage_800C5424( work ) )
    {
        UnsetAction2( work );
        return ;
    }

    if ( work->field_8E0 == 7 )
    {
        if ( work->body.is_end )
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

extern int sub_800C58E8( WatcherWork *work );

void sub_800C6A40( WatcherWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision_length = COM_EYE_LENGTH_800E0D8C ;
    work->field_8E6 = 0;

    if ( time == 0 )
    {
        SetAction( work, ACTION8, 0 );
    }

    if ( time == 3 )
    {
        if ( sub_800C58E8( work ) )
        {
            GM_SeSet_80032858( &( work->control.field_0_mov ), 0x25 );
        }
    }

    work->control.field_4C_turn_vec.vy = work->sn_dir;

    if ( CheckDamage_800C5424( work ) )
    {
		return ;        
    }

    if ( work->body.is_end )
    {
        SetMode( work, ActUnknown16_800C65A8 );
    }
    work->control.field_44_movementVector.vx = 0;
    work->control.field_44_movementVector.vz = 0;
}

void sub_800C6B24( WatcherWork* work, int time )
{
    work->vision_length = 0;

    if ( time == 0 )
    {
        SetAction( work, ACTION21, ACTINTERP ) ;
    }

    if ( CheckDamage_800C5424( work ) )
    {
		return ;        
    }

    SetTargetClass( work->target, TARGET_FLAG );

    if ( work->body.is_end )
    {
        work->actend = 1;
        SetMode( work, ActStandStill_800C5C84 );
    }
}