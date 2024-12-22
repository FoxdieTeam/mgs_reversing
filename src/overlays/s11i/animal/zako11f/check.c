#include "../../../s00a/Enemy/enemy.h"

extern SVECTOR DG_ZeroVector;

extern OBJECT *GM_PlayerBody_800ABA20;

extern SVECTOR ZAKO11F_ATTACK_FORCE_800C3674;

void s11i_asiato_800CA4F4( Zako11FWork *work, int time );
void s11i_asiato_800CA584( Zako11FWork *work, int time );
void ActBoxKick_800CA66C( Zako11FWork *work, int time );
void ActReadyGun_800CA674( Zako11FWork *work, int time );
void s11i_asiato_800CADDC( Zako11FWork *work, int time );
void s11i_asiato_800CB140( Zako11FWork *work, int time );
void s11i_asiato_800CB4B4( Zako11FWork *work, int time );
void s11i_asiato_800CB528( Zako11FWork *work, int time );
void s11i_asiato_800CB9BC( Zako11FWork *work, int time );
void s11i_asiato_800CBACC( Zako11FWork *work, int time );
void s11i_asiato_800CC528( Zako11FWork *work, int time );
void s11i_asiato_800CC5F4( Zako11FWork *work, int time );
void ActOverScoutD_800CC6C0( Zako11FWork *work, int time );
void s11i_asiato_800CC758( Zako11FWork *work, int time );
void s11i_asiato_800CC7F0( Zako11FWork *work, int time );
void s11i_asiato_800CC8A4( Zako11FWork *work, int time );
void s11i_asiato_800CC96C( Zako11FWork *work, int time );
void s11i_asiato_800CCA10( Zako11FWork *work, int time );
void s11i_asiato_800CCAD8( Zako11FWork *work, int time );
void s11i_asiato_800CCCF0( Zako11FWork *work, int time );
void s11i_asiato_800CCE38( Zako11FWork *work, int time );

void s11i_zk11fcom_800D0DD8( void );

/***Inlines***********************************************************************************************/
static inline void SetZako11FMode( Zako11FWork *work, ZAKO11FACTION action ) // rename
{
    work->action = action;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_ConfigMotionAdjust_80035008( &( work->body ), NULL );
}

static inline void SetZako11FMode2( Zako11FWork *work, ZAKO11FACTION action ) // rename
{
    if ( !work->action2 )
    {
        work->action2 = action;
        work->time2 = 0;
    }

    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_ConfigMotionAdjust_80035008( &( work->body ), 0 );
}
/**********************************************************************************************************/

int s11i_asiato_800C9840(Zako11FWork *work)
{
    TARGET *target;

    target = work->target;
    if (target->damaged & TARGET_CAPTURE)
    {
        if (target->a_mode == 36)
        {
            SetZako11FMode(work, s11i_asiato_800CADDC);
        }
        else
        {
            SetZako11FMode(work, s11i_asiato_800CB140);
        }

        target->damaged = 0;
        return 1;
    }

    return 0;
}

int s11i_asiato_800C98CC(Zako11FWork *work)
{
    if (work->target->damaged & TARGET_DOWN)
    {
        return 1;
    }

    return 0;
}

int s11i_asiato_800C98E8(SVECTOR *vec)
{
    return ABS(vec->vx) + ABS(vec->vy) + ABS(vec->vz);
}

int s11i_asiato_800C9924( Zako11FWork *work )
{
    short   a_mode;
    TARGET *target;

    target = work->target;
    if ( !( target->damaged & TARGET_POWER ) ) return 0;

    a_mode = target->a_mode - 1;
    switch ( a_mode )
    {
    case 2:
        target->field_2C_vec = DG_ZeroVector;
        if ( target->field_2A <= 0 )
        {
            work->unknown.field_14 = 1;
            SetZako11FMode( work, s11i_asiato_800CBACC ) ;
        }
        else
        {
            SetZako11FMode( work, s11i_asiato_800CB9BC ) ;
        }
        break;
    case 3:
        work->unknown.field_14 = 0;
        SetZako11FMode( work, s11i_asiato_800CBACC ) ;
        break;
    case 0:
        target->field_2C_vec = DG_ZeroVector;
        if ( target->field_26_hp <= 0 )
        {
            work->unknown.field_14 = 1;
            SetZako11FMode( work, s11i_asiato_800CBACC ) ;
        }
        else
        {
            SetZako11FMode( work, s11i_asiato_800CB9BC ) ;
        }
        break;
    case 1:
        if ( s11i_asiato_800C98E8( &target->field_2C_vec ) < 100 )
        {
            work->unknown.field_14 = 3;
        }
        else
        {
            work->unknown.field_14 = 2;
        }
        SetZako11FMode( work, s11i_asiato_800CBACC ) ;
        break;
    case 4:
        work->unknown.field_14 = 3;
        SetZako11FMode( work, s11i_asiato_800CBACC ) ;
        break;
    case 7:
        SetZako11FMode( work, s11i_asiato_800CB4B4 ) ;
        break;
    case 8:
        SetZako11FMode( work, s11i_asiato_800CB528 ) ;
        break;
    }

    target->field_28 = 0;
    target->damaged = 0;
    return 1;
}

int s11i_asiato_800C9B14( Zako11FWork *work )
{
    if ( GM_GameStatus & STATE_STUN )
    {
        SetZako11FMode( work, s11i_asiato_800CB528 );
        return 1;
    }

    return 0;
}

int CheckDamage_800C9B6C( Zako11FWork *work )
{
    if ( s11i_asiato_800C9840( work ) | s11i_asiato_800C9924( work ) | s11i_asiato_800C9B14( work ) )
    {
        work->target->class = TARGET_AVAIL;
        s11i_zk11fcom_800D0DD8();
        return 1;
    }

    return 0;
}

int s11i_asiato_800C9BE0( int from, int to )
{
    int diff;

    if ( to < 0 || from < 0 ) return 0 ;

    diff = GV_DiffDirS( from, to ) ;

    if ( diff < -896 || diff > 896 ) return 0 ;
    if ( diff >= 0 ) return 1 ;

    return 2 ;
}

void ReviseReadyGun_800C9C34( Zako11FWork *work )
{
    int trans;
    int near;

    trans = ( ( GM_PlayerBody_800ABA20->objs->objs[6].world.t[1] - work->body.objs->objs[6].world.t[1] ) );
    trans = ratan2( work->sn_dis, trans ) & 0xFFF;

    near = GV_NearExp8( work->adjust[2].vx, trans - 1024 );
    work->adjust[2].vx = near;
    work->adjust[6].vx = near;

    if ( near < 0 )
    {
        work->adjust[7].vx = near * 3 ;
    }
    else
    {
        work->adjust[7].vx = ( near * 3 ) / 2 ;
    }
}

void ReviseReadyGun2_800C9CBC( Zako11FWork *work )
{
    int trans;
    int near;

    trans = ( ( GM_PlayerBody_800ABA20->objs->objs[6].world.t[1] - work->body.objs->objs[6].world.t[1] ) );
    trans = ratan2( work->sn_dis, trans ) & 0xFFF;

    near = trans - 1024;
    work->adjust[2].vx = near;
    work->adjust[6].vx = near;

    if ( near < 0 )
    {
        work->adjust[7].vx = near * 3 ;
    }
    else
    {
        work->adjust[7].vx = ( near * 3 ) / 2 ;
    }
}

int AttackForce_800C9D38( Zako11FWork *work )
{
    TARGET *target;
    SVECTOR svec;
    SVECTOR rp_shift  = {-200, 1000, 600}; /* 右パンチ */
    SVECTOR force     = {5, 0, 100};
    SVECTOR size      = {400, 1000, 400};

    target = &work->punch;
    GM_SetTarget( target, TARGET_POWER, ENEMY_SIDE, &size );
    DG_SetPos2( &work->control.mov, &work->control.rot );
    DG_RotVector( &force, &svec, 1 );
    GM_Target_8002DCCC( target, 0, 2, 32, 1, &svec );
    DG_PutVector( &rp_shift, &work->punch.center, 1 );
    return GM_PowerTarget( target );
}

// TODO: remove
const int s11i_dword_800D5204 = 0;

void s11i_asiato_800C9E48( Zako11FWork *work )
{
    TARGET *target;

    target = &work->field_904;
    GM_Target_8002DCCC( target, 7, 5, 0, 3, &ZAKO11F_ATTACK_FORCE_800C3674 );
    GM_MoveTarget( target, &work->control.mov );
    GM_PowerTarget( target );
}

int CheckPad_800C9EB0( Zako11FWork *work )
{
    int press;

    press = work->pad.press;

    if ( press & 0x1 )
    {
        SetZako11FMode2( work, s11i_asiato_800CC528 );
        return 0;
    }

    if ( press & 0x2 )
    {
        SetZako11FMode2( work, s11i_asiato_800CC5F4 );
        return 0;
    }

    if ( press & 0x4 )
    {
        SetZako11FMode2( work, ActOverScoutD_800CC6C0 );
        return 0;
    }

    if ( press & 0x2000 )
    {
        SetZako11FMode2( work, s11i_asiato_800CC758 );
        return 0;
    }

    if ( press & 0x40 )
    {
        SetZako11FMode2( work, s11i_asiato_800CC7F0 );
        return 0;
    }

    if ( press & 0x80 )
    {
        SetZako11FMode2( work, s11i_asiato_800CC8A4 );
        return 0;
    }

    if ( press & 0x400 )
    {
        SetZako11FMode2( work, s11i_asiato_800CC96C );
        return 0;
    }

    if ( press & 0x800 )
    {
        SetZako11FMode2( work, s11i_asiato_800CCA10 );
        return 0;
    }

    if ( press & 0x200 )
    {
        SetZako11FMode2( work, s11i_asiato_800CCAD8 );
        return 0;
    }

    if ( press & 0x800000 )
    {
        SetZako11FMode2( work, s11i_asiato_800CCCF0 );
        return 0;
    }

    if ( press & 0x1000000 )
    {
        SetZako11FMode2( work, s11i_asiato_800CCE38 );
        return 0;
    }

    if ( press & 0x100 )
    {
        SetZako11FMode( work, s11i_asiato_800CA4F4 );
        return 1;
    }

    if ( press & 0x20 )
    {
        SetZako11FMode( work, s11i_asiato_800CA584 );
        return 1;
    }

    if ( press & SP_DANBOWLKERI )
    {
        SetZako11FMode( work, ActBoxKick_800CA66C );
        return 1;
    }

    if ( press & (SP_WEAPON | SP_WEAPON2) )
    {
        SetZako11FMode( work, ActReadyGun_800CA674 );
        work->adjust[2].vx = 0;
        return 1;
    }

    return 0;
}
