#include "enemy.h"

int s00a_command_800CEA2C( WatcherWork *work )
{
    int i;
    for ( i = 0 ; i <  8 ; i++ )
    {
        if ( EnemyCommand_800E0D98.field_0xC8[i].pad == 0 )
        {
            EnemyCommand_800E0D98.field_0xC8[i].pad = (int)work; //update to be a struct with watcher ptr as 4th attribute
            EnemyCommand_800E0D98.field_0xC8[i].vy = 2;
            COM_PlayerAddressOne_800E0F40[i] = -1;
            return i;
        }
    }

    return -1;
}

void s00a_command_800CEA84( int idx, int val )
{
    EnemyCommand_800E0D98.field_0x148[ idx ] = val;
}

int s00a_command_800CEA9C( int val )
{
    int i;
    for ( i = 0 ; i < EnemyCommand_800E0D98.field_0x08 ; i++ )
    {
        if ( EnemyCommand_800E0D98.field_0x148[i] == val )
        {
            return 1;
        }
    }
    return 0;
}

void ENE_SetTopCommAL_800CEAE8( int alert )
{
    TOPCOMMAND_800E0F20.alert = alert;
}

void ENE_SetTopCommMD_800CEAF4( int mode )
{
    TOPCOMMAND_800E0F20.mode = mode;
}

void ENE_SetGopointLast_800CEB00(void)
{
    EnemyCommand_800E0D98.com_addr = COM_PlayerAddress_800E0D90;
    EnemyCommand_800E0D98.com_pos  = COM_PlayerPosition_800E0F30;
    EnemyCommand_800E0D98.com_map  = COM_PlayerMap_800E0F1C;
    EnemyCommand_800E0D98.field_0x40 = 1;
}

extern CONTROL *GM_WhereList_800B56D0[94];
extern SVECTOR GM_NoisePosition_800AB9F8;
extern int dword_800ABA0C; //GM_PlayerMap?

void s00a_command_800CEB54(void) 
{
    EnemyCommand_800E0D98.com_addr = HZD_GetAddress_8005C6C4( GM_WhereList_800B56D0[0]->field_2C_map->field_8_hzd, &GM_NoisePosition_800AB9F8, -1 );
    EnemyCommand_800E0D98.com_pos = GM_NoisePosition_800AB9F8;
    EnemyCommand_800E0D98.com_map = dword_800ABA0C;
}

int s00a_command_800CEBCC( int a0, int a1 )
{
    int i;

    if ( s00a_dword_800E0E3C[0][0] == a0 )
    { 
        for ( i = 0 ; i < s00a_dword_800E0E3C[0][1] ; i++ )
        {
            if ( s00a_dword_800E0E3C[i][2] == a1 )
            {
                return s00a_dword_800E0E3C[i][3];
            }
        }   
        goto end;
    }
    return 0;
end:
    return -1;
}