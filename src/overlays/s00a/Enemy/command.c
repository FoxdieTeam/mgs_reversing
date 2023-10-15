#include "libgcl/libgcl.h"
#include "Game/camera.h"
#include "Game/map.h"
#include "enemy.h"


//extern CommandAct_800D0258();
//extern CommandDie_800D02EC();
//extern CommandGetResources_800D04F4( int work, int name, int where );

//extern void s00a_command_800D0258( CommanderWork *work ) ; //CommandAct_800D0258
//extern void s00a_command_800D02EC( void ) ; //CommandDie_800D02EC
//extern void s00a_command_800D04F4( CommanderWork *work, int name, int where ) ; //CommandGetResources_800D04F4

extern SVECTOR DG_ZeroVector_800AB39C;
extern GM_Camera GM_Camera_800B77E8;

void CommandAct_800D0258( CommanderWork* work )
{
    if (GM_CheckMessage_8002631C( &work->actor , work->name, 0x3223) != NULL)
    {
        GV_DestroyActor_800151C8( &work->actor );
        return;
    }

    s00a_command_800D018C( work );
    s00a_command_800D0344();
    s00a_command_800CFEA8();
    s00a_command_800D0218();
    s00a_command_800CFA94( work );
    s00a_command_800CEC90();
    s00a_command_800CECF4();
    EnemyCommand_800E0D98.field_0x0C++;
}

void CommandDie_800D02EC( void )
{
    return;
}

#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_command_800D02F4.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_command_800D0344.s")

void SetCameraActCall_800D043C()
{
    if ( COM_GameStatus_800E0F3C & 0x1000 ) return;

    COM_GameStatus_800E0F3C |= 0x1000 ;
    GM_GameStatus_800AB3CC  |= 0x10000000 ;
    s00a_dword_800E0D2C = 0 ;

}

void UnsetCameraActCall_800D047C()
{
    if ( !( COM_GameStatus_800E0F3C & 0x1000 ) ) return;

    COM_GameStatus_800E0F3C &= ~( 0x1000 ) ;
    GM_GameStatus_800AB3CC  &= ~( 0x10000000 ) ;

    sub_8002FD84( 1, NULL ) ;
    s00a_dword_800E0D2C = 0 ;
    GM_Camera_800B77E8.field_18_flags &= ~( 2 ) ;
}

void CommandGetResources_800D04F4( CommanderWork *work, int name, int where )
{
    int i;
    int ops;

    work->name = name;

    GM_GameFlag_800E0F64  = 0;
    EnemyCommand_800E0D98.field_0x17A = 1;

    COM_PlayerAddress_800E0D90  = 0;
    EnemyCommand_800E0D98.field_0x14  = 0;
    EnemyCommand_800E0D98.field_0x170 = 0;


    EnemyCommand_800E0D98.field_0x180 = 0;
    EnemyCommand_800E0D98.field_0x182 = 0;
    EnemyCommand_800E0D98.field_0x40  = 0;

    COM_PlayerPosition_800E0F30 = DG_ZeroVector_800AB39C;
    COM_PlayerMap_800E0F1C = where;
    COM_VibTime_800E0F68 = 0;
    s00a_dword_800E0CA0 = 0;
    s00a_dword_800E0D30 = 0;
    s00a_dword_800E0D2C = 0;

    for ( i = 0 ; i < 8 ; i++ )
    {
        EnemyCommand_800E0D98.field_0xC8[i].vx  = 0;
        EnemyCommand_800E0D98.field_0xC8[i].vy  = 0;
        EnemyCommand_800E0D98.field_0xC8[i].vz  = 0;
        EnemyCommand_800E0D98.field_0xC8[i].pad = 0;
    }

    for ( i = 0 ; i < 8 ; i++ )
    {
        EnemyCommand_800E0D98.field_0x68[i]  = i;
        EnemyCommand_800E0D98.field_0x20[i]  = 0;
        EnemyCommand_800E0D98.field_0x148[i] = 0xFF;
    }
    //v_option( where );
    EnemyCommand_800E0D98.field_0x0C = 0;
    EnemyCommand_800E0D98.mode       = 0;

    TOPCOMMAND_800E0F20.mode = 0;
    TOPCOMMAND_800E0F20.alert= 0;
    EnemyCommand_800E0D98.map = Map_FromId_800314C0( where );

    ops = GCL_GetOption_80020968( 'v' );
    if ( ops )
    {
        EnemyCommand_800E0D98.field_0x54 = s00a_command_800CEDE8( ops, &EnemyCommand_800E0D98.field_0x58 , where );
    }
    else
    {
        EnemyCommand_800E0D98.field_0x54 = 1;
        EnemyCommand_800E0D98.field_0x58[0] = 0;
    }

    EnemyCommand_800E0D98.reset_enemy_max = 5;

    ops = GCL_GetOption_80020968( 'b');
    if ( ops )
    {
        EnemyCommand_800E0D98.reset_enemy_max = GCL_StrToInt_800209E8( (unsigned char*)ops );
    }

    EnemyCommand_800E0D98.field_0x88.vx = 0xFA0;
    EnemyCommand_800E0D98.field_0x88.vy = 0xFA0;
    EnemyCommand_800E0D98.field_0x88.vz = 0xFA0;

    ops = GCL_GetOption_80020968( 'l' );
    if ( ops )
    {
        GCL_StrToSV_80020A14( (unsigned char*)ops, &EnemyCommand_800E0D98.field_0x88 );
    }

    //loc_800D06A0:
    COM_NOISEMODE_DIS_800E0F38 = 0x1F40;

    ops = GCL_GetOption_80020968( 'y' );
    if ( ops )
    {
        COM_NOISEMODE_DIS_800E0F38 = GCL_StrToInt_800209E8( (unsigned char*)ops );
    }

    printf( ( void* )&aCom_noisemode_disD_800E0940 , COM_NOISEMODE_DIS_800E0F38 );
    EnemyCommand_800E0D98.field_0x88.pad = 0;

    ops = GCL_GetOption_80020968( 't' );
    if ( ops ) {
        EnemyCommand_800E0D98.field_0x88.pad = GCL_StrToInt_800209E8( (unsigned char*)ops );
    }

    switch ( EnemyCommand_800E0D98.field_0x88.pad )
    {
        case 0:
            COM_ALERT_DECREMENT_800E0F60 = 4;
            break;
        case 1:
            COM_ALERT_DECREMENT_800E0F60 = 3;
            break;
        case 2:
            COM_ALERT_DECREMENT_800E0F60 = EnemyCommand_800E0D98.field_0x88.pad;
            break;
        default:
            COM_ALERT_DECREMENT_800E0F60 = 4;
    }

    printf( ( void* )&aEeeDDDTD_800E095C, EnemyCommand_800E0D98.field_0x88.vx, EnemyCommand_800E0D98.field_0x88.vy, EnemyCommand_800E0D98.field_0x88.vz, COM_ALERT_DECREMENT_800E0F60  );

    EnemyCommand_800E0D98.field_0x1C  = 0x1E;
    EnemyCommand_800E0D98.field_0x56  = 0;
    EnemyCommand_800E0D98.field_0x16C = 0;
    EnemyCommand_800E0D98.field_0x174 = 0;

    s00a_dword_800E0F28.mode = 0;
    EnemyCommand_800E0D98.field_0x178 = 0;
    COM_EYE_LENGTH_800E0D8C = EnemyCommand_800E0D98.field_0x88.vx;
    COM_SHOOTRANGE_800E0D88 = EnemyCommand_800E0D98.field_0x88.vx + 0x1F4;

    ops = GCL_GetOption_80020968( 'w' );
    if ( ops )
    {
        EnemyCommand_800E0D98.field_0x178 = GCL_StrToInt_800209E8( (unsigned char*)ops );
    }

    ops = GCL_GetOption_80020968( 'z' );
    if ( ops )
    {
        *(int*)(&EnemyCommand_800E0D98.field_0x17C) = GCL_StrToInt_800209E8( GCL_Get_Param_Result_80020AA4() );
    }
    else
    {
        *(int*)(&EnemyCommand_800E0D98.field_0x17C) = -1;
    }

    COM_GameStatus_800E0F3C = 0;

    ops = GCL_GetOption_80020968( 'a' );
    if ( ops )
    {
        COM_GameStatus_800E0F3C |= GCL_StrToInt_800209E8( (unsigned char*)ops );
    }

    ops = GCL_GetOption_80020968( 'j' );
    if ( ops )
    {
        s00a_dword_800E0E3C.vy = s00a_command_800CED88( ops, &s00a_dword_800E0E3C );
    }
    else
    {
        EnemyCommand_800E0D98.field_0xA6 = 1;
        EnemyCommand_800E0D98.field_0xA8 = 0;
        EnemyCommand_800E0D98.field_0xAA = 0;
    }

    EnemyCommand_800E0D98.where  = where;
    EnemyCommand_800E0D98.field_0x08 = 0;

    ops = GCL_GetOption_80020968( 'n' );
    if ( ops )
    {
        EnemyCommand_800E0D98.field_0x08 = s00a_command_800D0128( ops );
    }

    ops = GCL_GetOption_80020968( 'm' );
    if ( ops )
    {
        EnemyCommand_800E0D98.field_0x08 += s00a_command_800D0128( ops );
    }

    EnemyCommand_800E0D98.field_0x00 = 0;

    ops = GCL_GetOption_80020968( 'c' );
    if ( ops )
    {
        EnemyCommand_800E0D98.field_0x00 = s00a_command_800D0128( ops );
    }

    EnemyCommand_800E0D98.field_0x04 = 0;

    ops = GCL_GetOption_80020968( 's' );
    if ( ops )
    {
        EnemyCommand_800E0D98.field_0x04 = s00a_command_800D0128( ops );
    }
}


extern const char aCommandC_800E0970[]; //command.c

void *NewCommand_800D0908( int name, int where, int argc, char **argv )
{
    CommanderWork *work ;

    work = (CommanderWork *)GV_NewActor_800150E4( 4, sizeof( CommanderWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor_8001514C( &( work->actor ), ( TActorFunction )CommandAct_800D0258, ( TActorFunction )CommandDie_800D02EC, aCommandC_800E0970 );
        CommandGetResources_800D04F4( work, name, where );
    }
    return (void *)work ;
}
