#include "../../s00a/Enemy/enemy.h"

extern TOPCOMMAND_STRUCT TOPCOMMAND_800E0F20;
extern SVECTOR ENEMY_ATTACK_FORCE_800C35BC;

extern void s07a_meryl_unk_800D8CB4( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D8BA4( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D8654( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D85E0( WatcherWork *work, int time );

extern int s07a_meryl_unk_800D6824( SVECTOR* svec );

int s07a_meryl_unk_800D66B0( SVECTOR* svec )
{
    if ( ( (unsigned short)svec->vx - 0x1B58 >= 0x5DDU ) || ( svec->vz < -0x5014 ) || (svec->vz >= -0x4A37 ) )
    {
        return 0;
    }

    return 1;
}

int s07a_meryl_unk_800D66F4( SVECTOR* svec )
{
    if ( ( (unsigned short)svec->vx - 0xFA0 >= 0x157Du ) || ( svec->vz < -0x5014 ) || (svec->vz >= -0x251B ) )
    {
        return 0;
    }

    return 1;
}

int s07a_meryl_unk_800D6738( SVECTOR* svec )
{
    if ( svec->vx > 5500 && svec->vx < 7000 && svec->vz > -9500 && svec->vz < -8500 )
    {
        return 1;
    }

    return 0;
}

extern void s07a_meryl_unk_800D7F70( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D8290( WatcherWork *work, int time );

int s07a_meryl_unk_800D677C( WatcherWork* work )
{
    TARGET *target;

    target= work->target;
    if (  target->damaged & 2 )
    {
        if ( target->a_mode == 0x24 )
        {
            SetMode( work, s07a_meryl_unk_800D7F70 ) ;
        }
        else
        {
            SetMode( work, s07a_meryl_unk_800D8290 ) ;
        }
        target->damaged = 0;
        return 1;
    }
    return 0;
}

// Identical to s00a_command_800C513C
int s07a_meryl_unk_800D6808( WatcherWork* work ) {
    int check;
    check = work->target->damaged & 0x20;
    return check > 0;
}

// Identical to s00a_command_800C5158
int s07a_meryl_unk_800D6824( SVECTOR* svec )
{
    return abs( svec->vx ) + abs( svec->vy ) + abs( svec->vz ) ;
}

int s07a_meryl_unk_800D6860( WatcherWork *work )
{
    short val;
    TARGET *target;

    target = work->target;
    if ( !( target->damaged & TARGET_POWER ) ) return 0;

    val = target->a_mode - 1;
    switch ( val )
    {
    case 2:
        target->field_2C_vec = DG_ZeroVector;
        if ( target->field_2A <= 0 )
        {
            work->field_8DC = 1;
            SetMode( work, s07a_meryl_unk_800D8CB4 ) ;
        }
        else
        {
            SetMode( work, s07a_meryl_unk_800D8BA4 ) ;
        }
        break;
    case 3:
        work->field_8DC = 0;
        SetMode( work, s07a_meryl_unk_800D8CB4 ) ;
        break;
    case 0:
        target->field_2C_vec = DG_ZeroVector;
        if ( target->field_26_hp <= 0 )
        {
            work->field_8DC = 1;
            SetMode( work, s07a_meryl_unk_800D8CB4 ) ;
        }
        else
        {
            SetMode( work, s07a_meryl_unk_800D8BA4 ) ;
        }
        break;
    case 1:
        if ( s07a_meryl_unk_800D6824( &target->field_2C_vec ) < 100 )
        {
            work->field_8DC = 3;
        }
        else
        {
            work->field_8DC = 2;
        }
        SetMode( work, s07a_meryl_unk_800D8CB4 ) ;
        break;
    case 4:
        work->field_8DC = 3;
        SetMode( work, s07a_meryl_unk_800D8CB4 ) ;
        break;
    case 7:
        SetMode( work, s07a_meryl_unk_800D85E0 ) ;
        break;
    case 8:
        SetMode( work, s07a_meryl_unk_800D8654 ) ;
        break;
    }

    target->field_28 = 0;
    target->damaged = 0;
    return 1;
}

int s07a_meryl_unk_800D6A50( WatcherWork * work )
{
    CONTROL *ctrl;

    ctrl = &work->control;

    if ( s07a_meryl_unk_800D66F4( &ctrl->mov ) || s07a_meryl_unk_800D6738( &ctrl->mov ) )
    {
        return 0;
    }

    if ( work->target->class & TARGET_POWER && GM_GameStatus & STATE_STUN )
    {
        SetMode( work, s07a_meryl_unk_800D8654 ) ;

        if ( TOPCOMMAND_800E0F20.mode == TOP_COMM_TRAVEL )
        {
            work->target->field_2A = 0;
        }
        else
        {
            work->target->field_2A -= 5;
        }

        return 1;
    }

    return 0;
}

int CheckDamage_800D6B30( WatcherWork* work )
{
    if ( s07a_meryl_unk_800D6860( work ) || s07a_meryl_unk_800D677C( work ) || s07a_meryl_unk_800D6A50( work ) )
    {
        work->target->class = TARGET_AVAIL ;
        return 1;
    }
    return 0;
}

// Identical to s00a_command_800C580C
int s07a_meryl_unk_800D6B90( int dir, int dist )
{
    int diff ;
    if ( dist < 0 || dir < 0 ) return 0 ;

    diff = GV_DiffDirS( dir, dist ) ;

    if ( diff + 0x380 > 0x700u ) return 0 ;
    if ( diff >= 0 ) return 1 ;

    return 2 ;
}

extern OBJECT *GM_PlayerBody_800ABA20;

void ReviseReadyGun_800D6BE4( WatcherWork* work )
{

    int trans;
    int near;

    trans = ( ( GM_PlayerBody_800ABA20->objs->objs[6].world.t[1] - work->body.objs->objs[6].world.t[1] ) );
    trans = ratan2( work->sn_dis, trans  )  & 0xFFF;

    near = GV_NearExp8( work->field_734, trans - 0x400 );
    work->field_734 = near;
    work->field_754 = near;

    if ( near < 0 )
    {
        work->field_75C = near * 3 ;
    }
    else
    {
        work->field_75C = ( near * 3 ) / 2 ;
    }
}

extern SVECTOR size_800E2F50;
extern SVECTOR force_800E2F48;
extern SVECTOR rp_shift_800E2F40;

int AttackForce_800D6C6C( WatcherWork *work )
{
    TARGET *target;
    SVECTOR svec;
    SVECTOR rp_shift  = rp_shift_800E2F40; /* 右パンチ */
    SVECTOR force     = force_800E2F48;
    SVECTOR size      = size_800E2F50;

    target = &work->punch;
    GM_SetTarget( target, 4, ENEMY_SIDE, &size );
    DG_SetPos2( &work->control.mov, &work->control.rot );
    DG_RotVector( &force, &svec, 1 );
    GM_Target_8002DCCC( target, 0, 2, 32, 1, &svec );
    DG_PutVector( &rp_shift, &work->punch.center, 1 );
    return GM_PowerTarget( target );
}

void s07a_meryl_unk_800D6D7C( WatcherWork *work)
{
    TARGET* target;

    target = &work->field_904;
    GM_Target_8002DCCC(target, 7, 5, 0, 3, &ENEMY_ATTACK_FORCE_800C35BC);
    GM_MoveTarget( target, &work->control.mov );
    GM_PowerTarget( target );
}

extern void s07a_meryl_unk_800D9E48( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D9F14( WatcherWork *work, int time );
extern void ActOverScoutD_800D9FE0( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA078( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA110( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA1C4( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA28C( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA330( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA3F8( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA610( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA75C( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D7474( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D7504( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D75F8( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D76CC( WatcherWork *work, int time );
extern void ActReadyGun_800D7924( WatcherWork *work, int time );

#define SP_DANBOWLKERI 0x400000

int CheckPad_800D6DE4( WatcherWork *work )
{
    int press = work->pad.press;

    if ( press & 0x01 )
    {
        SetMode2( work, s07a_meryl_unk_800D9E48 );
        return 0;
    }

    if ( press & 0x02 )
    {
        SetMode2( work, s07a_meryl_unk_800D9F14 );
        return 0;
    }

    if ( press & 0x04 )
    {
        SetMode2( work, ActOverScoutD_800D9FE0 ); // //ActOverScoutD_800C85DC
        return 0;
    }

    if ( press & 0x2000 )
    {
        SetMode2( work, s07a_meryl_unk_800DA078 );
        return 0;
    }

    if ( press & 0x40 )
    {
        SetMode2( work, s07a_meryl_unk_800DA110 );
        return 0;
    }

    if ( press & 0x80 )
    {
        SetMode2( work, s07a_meryl_unk_800DA1C4 );
        return 0;
    }

    if ( press & 0x400 )
    {
        SetMode2( work, s07a_meryl_unk_800DA28C );
        return 0;
    }

    if ( press & 0x800 )
    {
        SetMode2( work, s07a_meryl_unk_800DA330 );
        return 0;
    }

    if ( press & 0x200 )
    {
        SetMode2( work, s07a_meryl_unk_800DA3F8 );
        return 0;
    }

    if ( press & 0x800000 )
    {
        SetMode2( work, s07a_meryl_unk_800DA610 );
        return 0;
    }

    if ( press & 0x1000000 )
    {
        SetMode2( work, s07a_meryl_unk_800DA75C );
        return 0;
    }

    if ( press & 0x100 )
    {
        SetMode( work, s07a_meryl_unk_800D7474 );
        return 1;
    }

    if ( press & 0x20 )
    {
        SetMode( work, s07a_meryl_unk_800D7504 );
        return 1;
    }

    if ( press & 0x2000000 )
    {
        SetMode( work, s07a_meryl_unk_800D75F8 );
        return 1;
    }

    if ( press & SP_DANBOWLKERI )
    {
        SetMode( work, s07a_meryl_unk_800D76CC );
        return 1;
    }

    if ( press & 0x30000 )
    {
        SetMode( work, ActReadyGun_800D7924 );
        work->field_734 = 0;
        return 1;
    }

    return 0;
}
