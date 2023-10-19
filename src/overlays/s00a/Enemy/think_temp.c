#include "enemy.h"

void EnemyResetThink_800CB224( WatcherWork* work ) 
{
    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->count3 = 0;
    work->field_B4C = 0;
    work->pad.field_08 = 0;
}

void s00a_command_800CB240( WatcherWork* work ) 
{
    work->think2 = 7;
    work->think3 = 14;
    work->count3 = 0;
}

void s00a_command_800CB258( WatcherWork *work )
{
    if ( work->field_B7C == 0xFF )
    {
        work->think1 = 1;
        work->think2 = 8;
        work->think3 = 19;
    }
    else
    {
        work->think1 = 1;
        work->think2 = 10;
        work->think3 = 28; 
        s00a_command_800CB0E0( work );
    }
    work->count3 = 0;
    work->pad.field_08 = 1;
}

void s00a_command_800CB2C8( WatcherWork *work )
{

    work->think1 = 1;
    work->think2 = 9;
    work->think3 = 27;
    work->count3 = 32;
    work->pad.field_08 = 1;
}

void s00a_command_800CB2F4( WatcherWork *work )
{
    if ( work->field_B7C == 0xFF )
    {
        s00a_command_800CAFD4( work );
        work->think1 = 1;

        if ( EnemyCommand_800E0D98.field_0x40 == 1 )
        {
            work->think2 = 8;
            work->think3 = 18;
        }
        else
        {
            work->think2 = 10;
            work->think3 = 29;
        }
    }
    else
    {
        s00a_command_800CB0E0( work );
        work->think1 = 1;
        work->think2 = 10;
        work->think3 = 28;
    }
    work->count3 = 0;
    work->pad.field_08 = 1;
}

void s00a_command_800CB394( WatcherWork *work )
{
    work->think1 = 1;
    work->think2 = 10;
    
    if ( work->field_B7C == 0xFF )
    {
        work->think3 = 29;
    }
    else
    {
        s00a_command_800CB0E0( work );
        work->think3 = 28;
    }
    
    work->count3 = 0;
    work->pad.field_08 = 1;
}

void s00a_command_800CB3F0( WatcherWork *work )
{

    work->think2 = 4;

    if ( (work->act_status & 0x10) && (work->field_BA1 & 8) )
    {
        work->think3 = 0xE;
    }
    else
    {
        work->think3 = 4;
    }
    
    work->count3 = 0;
    work->modetime[2] = 0;
}

void SetThink_Move_800CB42C( WatcherWork* work )
{
    EnemyCommand_800E0D98.field_0x40 = 0;
    if ( work->act_status & 4 )
    {
        work->think1 = 2;
        s00a_command_800CB3F0( work );
        work->pad.field_08 = 0;
        return;
    }

    if ( work->field_B7C != 0xFF )
    {
        if ( !( sub_8005D134( work->control.field_2C_map->field_8_hzd, &work->control.field_0_mov, work->field_B7C ) ) )
        {
            s00a_command_800CB0E0( work );
            work->think1 = 2;
            work->think2 = 0xB;
            work->pad.field_08 = 1;
            work->count3 = 0;
            return;
        }
        else
        {
            work->think1 = 2;
            work->think2 = 0xD;
            work->think3 = 0x22;
            work->think4 = 3;
            work->pad.field_08 = 0;
            work->count3 = 0;
            return;
        }
    }

    if ( work->field_BFC >= 5800 )
    {
        work->think1 = 2;
        work->think2 = 0xD;
        work->think3 = 0x22;
        work->think4 = 3;
        work->pad.field_08 = 0;
    }
    else
    {
        work->think1 = 2;
        work->think2 = 0xB;
        work->pad.field_08 = 1;  
    }
    work->count3 = 0;
}