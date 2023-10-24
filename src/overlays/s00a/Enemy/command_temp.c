#include "enemy.h"

int s00a_command_800CEA2C( WatcherWork *work )
{
    int i;
    for ( i = 0 ; i <  8 ; i++ )
    {
        if ( EnemyCommand_800E0D98.field_0xC8[i].watcher == 0 )
        {
            EnemyCommand_800E0D98.field_0xC8[i].watcher = work; //update to be a struct with watcher ptr as 4th attribute
            EnemyCommand_800E0D98.field_0xC8[i].field_04 = 2;
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

int s00a_command_800CEBCC( int map_id, int val )
{
    int i;
    A4_STRUCT *unk = &EnemyCommand_800E0D98.field_0xA4;
    
    if ( unk->map_id == map_id )
    { 
        for ( i = 0 ; i < unk->n_entry ; i++ )
        {
            if ( unk->field_04[i].field_00 == val )
            {
                return unk->field_04[i].field_02;
            }
        }   
        goto end;
    }
    return 0;
end:
    return -1;
}

void s00a_command_800CEC40( SVECTOR *mov , int flag )
{
    s00a_dword_800E0D38.vx = mov->vx;
    s00a_dword_800E0D30 |= 1 | flag;
    s00a_dword_800E0D38.vy = mov->vy;
    s00a_dword_800E0D38.vz = mov->vz;

    if ( s00a_dword_800E0CA0 == 0 )
    {
        s00a_dword_800E0CA0 = 32;
    }
}

extern int COM_VibTime_800E0F68;

unsigned char s00a_dword_800C35DC[4];
unsigned char s00a_dword_800C35E0[4];

extern void NewPadVibration_8005D58C( unsigned char *ptr, int flags );

void s00a_command_800CEC90( void ) 
{
    if ( COM_VibTime_800E0F68 > 0 )
    {
        NewPadVibration_8005D58C( s00a_dword_800C35DC, 1 );
        NewPadVibration_8005D58C( s00a_dword_800C35E0, 2 );
        COM_VibTime_800E0F68--;
        return;
    }
    
    COM_VibTime_800E0F68 = 0;
}

void s00a_command_800CECF4(void)
{
    if ( s00a_dword_800E0CA0 == 32 )
    {
         GM_SeSet2_80032968( 0, 0x3F, 0x53 );
    }

    s00a_dword_800E0CA0--;

    if ( s00a_dword_800E0CA0 < 0 )
    {
        s00a_dword_800E0CA0 = 0;
    }
}

void s00a_command_800CED48( void )
{
    int i;
    for ( i = 0; i < EnemyCommand_800E0D98.field_0x08 ; i++ )
    {
        EnemyCommand_800E0D98.field_0x148[i] = 255;
    }
}

int s00a_command_800CED88( int ops, A4_STRUCT *unk )
{
    int i;
    i = 0;
    
    do {
        unk->field_04[i].field_00 = GCL_StrToInt_800209E8( GCL_Get_Param_Result_80020AA4() );
        unk->field_04[i].field_02 = GCL_StrToInt_800209E8( GCL_Get_Param_Result_80020AA4() );
        i++;
    } while ( GCL_Get_Param_Result_80020AA4() != NULL );

    
    return i;
}

int s00a_command_800CEDE8( int ops, short *addr, int map_id )
{
    int i;
    MAP *map;
    SVECTOR svec;
    unsigned char *res;
    map = Map_FromId_800314C0( map_id );

    for ( i = 0; ( res = GCL_Get_Param_Result_80020AA4() ) && i < 4 ; i++ )
    {
        GCL_StrToSV_80020A14( res, &svec );
        
        if ( svec.vy < 30000 )
        {
            addr[i] = HZD_GetAddress_8005C6C4( map->field_8_hzd, &svec, -1 ) & 0xFF;
        }
        else
        {
            addr[i] = 255;
        }
    }

    return i;
}

extern int GV_Time_800AB330;
extern const char aCresetposd_800E07FC[]; //" c_reset_pos = %d \n";
extern SVECTOR GM_PlayerPosition_800ABA10;

void s00a_command_800CEE98(void)
{
    int i;
    int s0;
    int dist2;
    int total;
    int delta;
    short dist1;
    int reset_pos;
    HZD_ZON *zone;
    SVECTOR svec;
    
    i = 0;
    delta = GV_Time_800AB330 % EnemyCommand_800E0D98.field_0x54;
    total = EnemyCommand_800E0D98.field_0x54;
    reset_pos = 0;
    
    for ( ; i < total ; i++  )
    {
        s0 = i + delta;
        if ( s0 >= total )
        {
            s0 -= total;
        }

        zone = &EnemyCommand_800E0D98.map->field_8_hzd->f00_header->navmeshes[ EnemyCommand_800E0D98.field_0x58[ s0 ] ];

        svec.vx = zone->x;
        svec.vy = GM_PlayerPosition_800ABA10.vy;
        svec.vz = zone->z;

        dist1 =  10000;
        dist2 = GV_DistanceVec3_80016E84( &svec, &GM_PlayerPosition_800ABA10 );
        if ( dist1 < dist2 )
        {
            reset_pos = s0;
            break;
        }

    }

    EnemyCommand_800E0D98.c_reset_pos = reset_pos;
    fprintf( 1, aCresetposd_800E07FC, reset_pos );
}


int s00a_command_800CEFE4( int val )
{
    return  EnemyCommand_800E0D98.field_0x0C % val;
}

void s00a_command_800CF024( int *val )
{
    if ( COM_GameStatus_800E0F3C & 1 )
    {
        *val = 0x82;
    }
    else
    {
        *val = 0x80;
    }
}

void s00a_command_800CF050( int *val )
{
    *val = 0x87;
}

void s00a_command_800CF05C( int *val )
{
    *val = 0x8B;
}

void s00a_command_800CF068( int *val )
{
    *val = 0x8A;
}

void s00a_command_800CF074( int *val )
{
    *val = 0x86;
}

void s00a_command_800CF080( int* val )
{
    switch( s00a_command_800CEFE4( 3 ) )
    {
    case 0:
        *val = 0x82;
        break;
    case 1:
    case 2:
        *val = 0x81;
        break;
    }
}

void s00a_command_800CF0CC( int *val )
{
    *val = 0x85;
}

extern const char aKottida_800E0810[]; //"kottida !!\n";

void s00a_command_800CF0D8( int* val )
{
    switch ( s00a_command_800CEFE4( 2 ) )
    {
    case 0:
        fprintf( 1, aKottida_800E0810 );
        *val = 0x81;
        return;
    case 1:
        *val = 0;
        return;
    }
}


int s00a_command_800CF13C( int val )
{
    switch( val )
    {
        case 240:
            s00a_command_800CF024( &val );
            break;
        case 241:
            s00a_command_800CF050( &val );
            break;
        case 242:
            s00a_command_800CF05C( &val );
            break;
        case 243:
            s00a_command_800CF068( &val );
            break;
        case 244:
            s00a_command_800CF074( &val );
            break;
        case 245:
            s00a_command_800CF0CC( &val );
            break;
        case 246:
            s00a_command_800CF080( &val );
            break;
        case 247:
            s00a_command_800CF0D8( &val );
            break;
    }

    return val;
}
