#include "../../s00a/Enemy/enemy.h"

extern TOPCOMMAND_STRUCT TOPCOMMAND_800E0F20;
extern SVECTOR DG_ZeroVector_800AB39C;

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
    if (  target->field_6_flags & 2 )
    {
        if ( target->field_3E == 0x24 )
        {
            SetMode( work, s07a_meryl_unk_800D7F70 ) ;
        }
        else
        {
            SetMode( work, s07a_meryl_unk_800D8290 ) ;
        }
        target->field_6_flags = 0;
        return 1;
    }
    return 0;
}

// Identical to s00a_command_800C513C
int s07a_meryl_unk_800D6808( WatcherWork* work ) {
    int check;
    check = work->target->field_6_flags & 0x20;
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
    if ( !( target->field_6_flags & 4 ) ) return 0;

    val = target->field_3E - 1;
    switch ( val )
    {
    case 2:
        target->field_2C_vec = DG_ZeroVector_800AB39C;
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
        target->field_2C_vec = DG_ZeroVector_800AB39C;
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
    target->field_6_flags = 0;
    return 1;
}

int s07a_meryl_unk_800D6A50( WatcherWork * work )
{
    CONTROL *ctrl;

    ctrl = &work->control;

    if ( s07a_meryl_unk_800D66F4( &ctrl->field_0_mov ) || s07a_meryl_unk_800D6738( &ctrl->field_0_mov ) )
    {
        return 0;
    }

    if ( work->target->class & TARGET_POWER && GM_GameStatus_800AB3CC & 2 )
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

    diff = GV_DiffDirS_8001704C( dir, dist ) ;

    if ( diff + 0x380 > 0x700u ) return 0 ;
    if ( diff >= 0 ) return 1 ;

    return 2 ;
}
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D6BE4.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D6C6C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D6D7C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D6DE4.s")
