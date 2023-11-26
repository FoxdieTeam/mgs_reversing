
#include "../../s00a/Enemy/enemy.h"
#include "Game/item.h"
#include "Game/linkvarbuf.h"

extern int COM_EYE_LENGTH_800E0D8C;
extern ENEMY_COMMAND EnemyCommand_800E0D98;
extern unsigned int  COM_GameStatus_800E0F3C;

extern OBJECT *GM_PlayerBody_800ABA20;
extern SVECTOR DG_ZeroVector_800AB39C;

extern int CheckPad_800D6DE4( WatcherWork *work );
extern int CheckDamage_800D6B30( WatcherWork* work );

extern int s07a_meryl_unk_800D6B90( int dir, int dist );
extern void s07a_meryl_unk_800D6BE4( WatcherWork* work );

extern void s07a_meryl_unk_800D71B0( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D7A90( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D7B48( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D7C98( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D7DF0( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D9FE0( WatcherWork* work, int time );

extern int s07a_meryl_unk_800D9D6C( WatcherWork *work, int idx ); //int ENE_SetPutChar_800C979C( WatcherWork *work, int idx )


/****Inlines**********************************************************************************************/
static inline void UnsetMode( WatcherWork *work )
{
    extern short    ActTable_800C3628[];
    work->field_8E2 = 0;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C3628[ STANDSTILL ], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->field_8E2 = 0;
    work->control.field_4C_turn.vz = 0;
    work->control.field_4C_turn.vx = 0;
}

static inline void UnsetMode2( WatcherWork *work )
{
    extern short    ActTable_800C3628[];
    work->field_8E2 = 0;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C3628[ STANDSTILL ], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->field_8E2 = 0;
    work->control.field_4C_turn.vz = 0;
    work->control.field_4C_turn.vx = 0;

    if ( work->field_B68 )
    {
        GV_DestroyOtherActor_800151D8( work->field_B68 );
        work->field_B68 = 0;
    }

}

static inline void SetAction( WatcherWork *work, int n_action, int interp )
{
    extern short    ActTable_800C3628[];
    work->field_8E0 = n_action ;
    GM_ConfigObjectAction_80034CD4( &( work->body ), ActTable_800C3628[ n_action ], 0, interp );
}

static inline void UnsetAction( WatcherWork *work, int n_action )
{
    extern short    ActTable_800C3628[];

    work->field_8E2 = n_action;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C3628[ n_action ], 0, ACTINTERP, 0x3FE );
}

static inline void UnsetActionManual( WatcherWork *work, int n_action, int a4 )
{
    extern short    ActTable_800C3628[];

    work->field_8E2 = n_action;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C3628[ n_action ], 0, ACTINTERP, a4 );
}

static inline void UnsetAction2( WatcherWork *work )
{
    extern short    ActTable_800C3628[];

    work->field_8E2 = 0;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C3628[ STANDSTILL ], 0, ACTINTERP, 0 );
    GV_DestroyOtherActor_800151D8( work->subweapon );
}
/*********************************************************************************************************/

void ActStandStill_800D7008( WatcherWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->act_status |= 1;

    if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
    {
        work->target->class |= TARGET_C4 ;
    }

    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        SetAction( work, STANDSTILL, ACTINTERP );
    }

    if ( CheckDamage_800D6B30( work ) || CheckPad_800D6DE4( work ) )
    {
        UnsetMode( work ) ;
        return ;
    }


    if ( work->pad.dir >= 0 )
    {
        if ( GV_DiffDirAbs_8001706C( work->control.field_8_rot.vy, work->pad.dir ) < 0x100 )
        {
            if ( work->pad.field_08 & 0x1 )
            {
                SetAction( work, ACTION2, ACTINTERP );
            }
            else
            {
                SetAction( work, ACTION1, ACTINTERP );
            }
            SetMode( work, s07a_meryl_unk_800D71B0 );

        }
        else
        {
            work->control.field_4C_turn.vy = work->pad.dir;
        }
    }
    work->vision.facedir = work->control.field_8_rot.vy;
}

void s07a_meryl_unk_800D71B0( WatcherWork* work, int time )
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

    work->act_status |= 0x1;
    if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
    {
        work->target->class |= TARGET_C4 ;
    }

    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

    if ( CheckDamage_800D6B30( work ) || CheckPad_800D6DE4( work ) )
    {
        UnsetMode( work ) ;
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
        SetMode( work, ActStandStill_800D7008);
        UnsetMode( work ) ;
        return;
    }


    switch ( s07a_meryl_unk_800D6B90( dir, dist ) )
    {
    case 1:
        dir = (dist - 1024) & 0xFFF;
        break;
    case 2:
        dir = (dist + 1024) & 0xFFF;
        break;
    }
    

    if ( !work->body.objs->bound_mode )
    {
        ctrl->field_8_rot.vy   = dir;
        ctrl->field_4C_turn.vy = dir;
        work->vision.facedir = GV_NearExp4P_80026554( work->vision.facedir, work->control.field_8_rot.vy );
    }
    else
    {
        ctrl->field_4C_turn.vy = dir;
        work->vision.facedir = work->control.field_8_rot.vy;
    }

    interval = 0;

    if ( field_8E0 == 1 )
    {
        interval = 50;
    }
    else if ( field_8E0 == 2 )
    {
        interval = 120;
    }

    x = interval * rsin( dir );

    if ( x < 0 )
    {
        x += 0xFFF;
    }

    ctrl->field_44_step.vx = x >> 12;

    z = interval * rcos( dir );

    if ( z < 0 )
    {
        z += 0xFFF;
    }

    ctrl->field_44_step.vz = z >> 12;

}

extern void s07a_meryl_unk_800D8798( WatcherWork* work, int time ) ;

void s07a_meryl_unk_800D7474( WatcherWork* work, int time ) 
{
    if ( time == 0 )
    {
        work->field_8DC = 3;
        SetAction( work, ACTION35, 4 );
    }

    if ( !( CheckDamage_800D6B30( work ) ) && ( work->body.is_end ) )
    {
        work->pad.tmp = 0;
        SetMode( work, s07a_meryl_unk_800D8798 );
    }
}

void s07a_meryl_unk_800D7504( WatcherWork* work, int time )
{
    CONTROL *ctrl;

    ctrl = &( work->control );
    work->act_status |= 0x01;
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        SetAction( work, ACTION16, ACTINTERP );
    }

    if ( CheckDamage_800D6B30( work ) )
    {
        return ;
    }

    if ( work->body.is_end || !( work->pad.press & 0x20 ) )
    {
        SetMode( work, ActStandStill_800D7008 );
        return;
    }

    ctrl->field_4C_turn.vy = work->sn_dir;
    ctrl->field_44_step.vx = 0;
    ctrl->field_44_step.vz = 0;
    work->vision.facedir = work->control.field_8_rot.vy;
}

void s07a_meryl_unk_800D75F8( WatcherWork* work, int time )
{
    CONTROL *ctrl;

    ctrl = &( work->control );
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        SetAction( work, ACTION13, ACTINTERP );
    }

    if ( CheckDamage_800D6B30( work ) )
    {
        return ;
    }

    if ( !( work->pad.press & 0x2000000 ) )
    {
        SetMode( work, ActStandStill_800D7008 );
        return;
    }

    ctrl->field_4C_turn.vy = work->pad.dir;
    ctrl->field_44_step.vx = 0;
    ctrl->field_44_step.vz = 0;
    work->vision.facedir = work->control.field_8_rot.vy;
}

void s07a_meryl_unk_800D76CC( WatcherWork *work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG ) ;
    work->vision.length = COM_EYE_LENGTH_800E0D8C;

    if ( CheckDamage_800D6B30( work ) )
    {
        UnsetCameraActCall_800D047C( );
        COM_GameStatus_800E0F3C &= ~COM_ST_DANBOWL ;
        return;
    }

    if ( !(work->pad.press & SP_DANBOWLKERI) )
    {
        if ( !(CheckPad_800D6DE4( work )) )
        {
            SetMode( work, ActStandStill_800D7008 ) ;
        }
        UnsetCameraActCall_800D047C( );
        COM_GameStatus_800E0F3C &= ~COM_ST_DANBOWL ;
        return ;
    }

    if ( time == 0 ) {
        SetMode2( work, s07a_meryl_unk_800D9FE0 ) ;
        SetAction( work, STANDSTILL, ACTINTERP ) ;
        SetCameraActCall_800D043C( );
    }

    if ( time == 60 ) {
        UnsetMode( work ) ;
        SetAction( work, DANBOWLKERI, ACTINTERP ) ;
    }

    if ( time == 78 ) {
        extern  void    *NewBoxKeri_800D2600( MATRIX    *, SVECTOR  * ) ;
        NewBoxKeri_800D2600( &( GM_PlayerBody_800ABA20->objs[ 0 ].world ), &( work->control.field_0_mov ) ) ;
    }

    if ( time == 100 ) {
        SetAction( work, DANBOWLPOSE, ACTINTERP ) ;
    }

    if ( time == 130 ) {
        GM_CurrentItemId = ITEM_NONE ;
    }

    if ( time > 150  ) {
        UnsetCameraActCall_800D047C( );
        work->actend = 1 ;
        SetMode( work, ActStandStill_800D7008 ) ;
        COM_GameStatus_800E0F3C &= ~COM_ST_DANBOWL ;
        return ;
    }
    work->control.field_4C_turn.vy = work->sn_dir;
    work->vision.facedir = work->control.field_8_rot.vy;
}

void s07a_meryl_unk_800D7924( WatcherWork* work, int time )
{
    int press;
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;
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

    s07a_meryl_unk_800D6BE4( work );
    if ( CheckDamage_800D6B30( work ) )
    {
        return ;
    }

    if ( !(press & 0x30000) )
    {
        SetMode( work, ActStandStill_800D7008 ) ;
        return ;
    }

    if ( press & 0x40000 )
    {
        SetModeFields( work, s07a_meryl_unk_800D7A90 ) ;
        return;
    }

    if ( press & 0x80000 )
    {
        SetModeFields( work, s07a_meryl_unk_800D7B48 ) ;
        return;
    }

    if ( press & 0x100000 )
    {
        SetModeFields( work, s07a_meryl_unk_800D7C98 ) ;
        return;
    }

    if ( press & 0x200000 )
    {
        SetModeFields( work, s07a_meryl_unk_800D7DF0 ) ;
        return;
    }

    work->control.field_4C_turn.vy = work->sn_dir;
    work->vision.facedir = work->control.field_8_rot.vy;
}

void s07a_meryl_unk_800D7A90( WatcherWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        SetAction( work, ACTION4, 0 ) ;
        s07a_meryl_unk_800D9D6C( work, 3 ) ;
        GM_ConfigMotionAdjust_80035008( &( work->body ), &work->field_724 ) ;
    }

    s07a_meryl_unk_800D6BE4( work );
    work->control.field_4C_turn.vy = work->sn_dir;

    if ( CheckDamage_800D6B30( work ) )
    {
        return ;
    }

    SetModeFields( work, s07a_meryl_unk_800D7924 );
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D7B48.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D7C98.s") //ActGrenade_800D7C98
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D7DF0.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D7EC8.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D7F70.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D8210.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D8290.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D85E0.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D8654.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D8798.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D89D8.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D8AA0.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D8BA4.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D8CB4.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9230.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9410.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9508.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D952C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D973C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D97AC.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9810.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D998C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9A28.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9A6C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9B14.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9C5C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9C98.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9D6C.s")

// Identical to ENE_ClearPutChar_800C97E4
int s07a_meryl_unk_800D9DB4( WatcherWork *work, void *func )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[ i ] == func )
        {
            work->field_B00[ i ] = 0;
            return 1;
        }
    }
    return 0;
}

// Identical to ENE_ExecPutChar_800C9818
void s07a_meryl_unk_800D9DE8( WatcherWork* work )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[i] )
        {
            PUTFUNC func = work->field_B00[i];
            func( work );
        }
    }
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9E48.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9F14.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9FE0.s") //ActOverScoutD_800D9FE0
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA078.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA110.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA1C4.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA28C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA330.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA3F8.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA5D0.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA610.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA75C.s")
