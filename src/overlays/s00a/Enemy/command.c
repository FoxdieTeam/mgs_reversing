#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/map.h"



typedef struct _Work
{
    GV_ACT         actor;
    unsigned short unk; //0x20
    unsigned short unk2; //0x22
    int            name; //0x24
} Work;

typedef struct _TOPCOMMAND_STRUCT {
    int a;
    int b;
} TOPCOMMAND_STRUCT;

typedef struct _ENEMY_COMMAND
{
    int     field_0x00;
    int     field_0x04;
    int     field_0x08;
    int     field_0x0C;
    int     field_0x10;
    int     field_0x14;
    int     mode;        ///0x18
    int     field_0x1C;
    int     field_0x20[8];
    int     field_0x40;
    int     field_0x44;
    int     field_0x48;
    int     field_0x4C;
    int     field_0x50;
    short   field_0x54;
    short   field_0x56;
    short   field_0x58;
    short   field_0x5A;
    int     field_0x5C;
    int     field_0x60;
    int     field_0x64;
    int     field_0x68[8];
    SVECTOR field_0x88;
    int     field_0x90;
    int     field_0x94;
    int     field_0x98;
    int     field_0x9C;
    MAP     *map;
    short   where;        //0xA4
    short   field_0xA6;
    short   field_0xA8;
    short   field_0xAA;
    int     field_0xAC;
    int     field_0xB0;
    int     field_0xB4;
    int     field_0xB8;
    int     field_0xBC;
    int     field_0xC0;
    int     field_0xC4;
    VECTOR  field_0xC8[8];
    int     field_0x148[8];
    int     field_0x168;
    int     field_0x16C;
    int     field_0x170;
    int     field_0x174;
    short   field_0x178;
    short   field_0x17A;
    int     field_0x17C;
    short   field_0x180;
    short   field_0x182;
} ENEMY_COMMAND;

extern SVECTOR DG_ZeroVector_800AB39C;

extern int dword_800E01F4;

extern int dword_800E0940;
extern int dword_800E095C;

extern int dword_800E0D90; //maybe COM_PlayerAddress

extern int dword_800E0CA0;
extern int dword_800E0D2C;
extern int dword_800E0D30;
extern int dword_800E0D88;
extern int dword_800E0D8C;

extern ENEMY_COMMAND EnemyCommand_800E0D98; //maybe EnemyCommand

extern SVECTOR dword_800E0E3C;

extern int COM_PlayerMap_800E0F1C;
extern TOPCOMMAND_STRUCT TOPCOMMAND_800E0F20;
extern VECTOR dword_800E0F28;

extern SVECTOR COM_PlayerPosition_800E0F30;

extern int COM_NOISEMODE_DIS_800E0F38;
extern int COM_GameStatus_800E0F3C;

extern int COM_PlayerAddressOne_800E0F40;

extern int dword_800E0F60;
extern int dword_800E0F64;
extern int dword_800E0F68;


extern short sub_800CEDE8( int ops, void *val, int where );
extern short sub_800CED88( int ops, SVECTOR* svec );
extern int   sub_800D0128( int ops );
extern void  sub_800D018C( Work* work ) ;
extern void  sub_800D0344( void ) ;
extern void  sub_800CFEA8( void ) ;
extern void  sub_800D0218( void ) ;
extern void  sub_800CFA94( Work* work ) ;
extern void  sub_800CEC90( void ) ;
extern void  sub_800CECF4( void ) ;



void CommandAct_800D0258( Work* work )
{
    if (GM_CheckMessage_8002631C( &work->actor , work->name, 0x3223) != NULL)
    {
        GV_DestroyActor_800151C8( &work->actor );
        return;
    }
    
    sub_800D018C( work );
    sub_800D0344();
    sub_800CFEA8();
    sub_800D0218();
    sub_800CFA94( work );
    sub_800CEC90();
    sub_800CECF4();
    EnemyCommand_800E0D98.field_0x0C++;
}

void CommandDie_800D02EC(void)
{
    return;
}

void CommandGetResources_800D04F4( Work *work, int name, int where )
{
    int i;
    int ops;
    
    work->name = name;

    dword_800E0F64  = 0;
    EnemyCommand_800E0D98.field_0x17A = 1;
    
    dword_800E0D90  = 0;
    EnemyCommand_800E0D98.field_0x14  = 0;
    EnemyCommand_800E0D98.field_0x170 = 0;
    

    EnemyCommand_800E0D98.field_0x180 = 0;
    EnemyCommand_800E0D98.field_0x182 = 0;
    EnemyCommand_800E0D98.field_0x40  = 0;
    
    COM_PlayerPosition_800E0F30 = DG_ZeroVector_800AB39C;
    COM_PlayerMap_800E0F1C = where;
    dword_800E0F68 = 0;
    dword_800E0CA0 = 0;
    dword_800E0D30 = 0;
    dword_800E0D2C = 0;

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

    TOPCOMMAND_800E0F20.a = 0;
    TOPCOMMAND_800E0F20.b = 0;
    EnemyCommand_800E0D98.map = Map_FromId_800314C0( where );

    ops = GCL_GetParam_80020968( 'v' );
    if ( ops ) 
    {
        EnemyCommand_800E0D98.field_0x54 = sub_800CEDE8( ops, &EnemyCommand_800E0D98.field_0x5A , where );
    } 
    else 
    {
        EnemyCommand_800E0D98.field_0x54 = 1;
        EnemyCommand_800E0D98.field_0x58 = 0;
    }

    EnemyCommand_800E0D98.field_0x94 = 5;
    
    ops = GCL_GetParam_80020968( 'b');
    if ( ops )
    {
        EnemyCommand_800E0D98.field_0x94 = GCL_GetNextInt_800209E8( (unsigned char*)ops );
    }
    
    EnemyCommand_800E0D98.field_0x88.vx = 0xFA0;
    EnemyCommand_800E0D98.field_0x88.vy = 0xFA0;
    EnemyCommand_800E0D98.field_0x88.vz = 0xFA0;

    ops = GCL_GetParam_80020968( 'l' );
    if ( ops ) 
    {
        GCL_GetSV_80020A14( (unsigned char*)ops, &EnemyCommand_800E0D98.field_0x88 );
    }

    //loc_800D06A0:
    COM_NOISEMODE_DIS_800E0F38 = 0x1F40;

    ops = GCL_GetParam_80020968( 'y' );
    if ( ops )
    {
        COM_NOISEMODE_DIS_800E0F38 = GCL_GetNextInt_800209E8( (unsigned char*)ops );
    }

    printf( ( void* )&dword_800E0940 , COM_NOISEMODE_DIS_800E0F38 );    
    EnemyCommand_800E0D98.field_0x88.pad = 0;

    ops = GCL_GetParam_80020968( 't' );
    if ( ops ) {
        EnemyCommand_800E0D98.field_0x88.pad = GCL_GetNextInt_800209E8( (unsigned char*)ops );
    }

    switch ( EnemyCommand_800E0D98.field_0x88.pad )
    {
        case 0:
            dword_800E0F60 = 4;
            break;
        case 1:
            dword_800E0F60 = 3;
            break;
        case 2:
            dword_800E0F60 = EnemyCommand_800E0D98.field_0x88.pad;
            break;
        default:
            dword_800E0F60 = 4;
    }

    printf( ( void* )&dword_800E095C, EnemyCommand_800E0D98.field_0x88.vx, EnemyCommand_800E0D98.field_0x88.vy, EnemyCommand_800E0D98.field_0x88.vz, dword_800E0F60  ); 
    
    EnemyCommand_800E0D98.field_0x1C  = 0x1E;
    EnemyCommand_800E0D98.field_0x56  = 0;
    EnemyCommand_800E0D98.field_0x16C = 0;
    EnemyCommand_800E0D98.field_0x174 = 0;
    
    dword_800E0F28.vx = 0;
    EnemyCommand_800E0D98.field_0x178 = 0;
    dword_800E0D8C = EnemyCommand_800E0D98.field_0x88.vx;
    dword_800E0D88 = EnemyCommand_800E0D98.field_0x88.vx + 0x1F4;
    
    ops = GCL_GetParam_80020968( 'w' );
    if ( ops )
    {
        EnemyCommand_800E0D98.field_0x178 = GCL_GetNextInt_800209E8( (unsigned char*)ops );
    }

    ops = GCL_GetParam_80020968( 'z' );
    if ( ops )
    {
        *(int*)(&EnemyCommand_800E0D98.field_0x178) = GCL_GetNextInt_800209E8( GCL_Get_Param_Result_80020AA4() );
    } 
    else 
    {
        *(int*)(&EnemyCommand_800E0D98.field_0x178) = -1;
    }
 
    COM_GameStatus_800E0F3C = 0;

    ops = GCL_GetParam_80020968( 'a' );
    if ( ops )
    {
        COM_GameStatus_800E0F3C |= GCL_GetNextInt_800209E8( (unsigned char*)ops );
    } 
    
    ops = GCL_GetParam_80020968( 'j' );
    if ( ops )
    {
        dword_800E0E3C.vy = sub_800CED88( ops, &dword_800E0E3C );
    } 
    else
    {
        EnemyCommand_800E0D98.field_0xA6 = 1;
        EnemyCommand_800E0D98.field_0xA8 = 0;
        EnemyCommand_800E0D98.field_0xAA = 0;
    }

    EnemyCommand_800E0D98.where  = where;
    EnemyCommand_800E0D98.field_0x08 = 0;
    
    ops = GCL_GetParam_80020968( 'n' );
    if ( ops )
    {
        EnemyCommand_800E0D98.field_0x08 = sub_800D0128( ops );
    }

    ops = GCL_GetParam_80020968( 'm' );
    if ( ops )
    {
        EnemyCommand_800E0D98.field_0x08 += sub_800D0128( ops );
    }

    EnemyCommand_800E0D98.field_0x00 = 0;
    
    ops = GCL_GetParam_80020968( 'c' );
    if ( ops )
    {
        EnemyCommand_800E0D98.field_0x00 = sub_800D0128( ops );
    }
    
    EnemyCommand_800E0D98.field_0x04 = 0;
    
    ops = GCL_GetParam_80020968( 's' );
    if ( ops )
    {
        EnemyCommand_800E0D98.field_0x04 = sub_800D0128( ops );
    }
}

void *NewCommander_800D0908( int name, int where, int argc, char **argv )
{
    Work *work ;

    work = (Work *)GV_NewActor_800150E4( 4, sizeof( Work ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor_8001514C( &( work->actor ), ( TActorFunction )CommandAct_800D0258, ( TActorFunction )CommandDie_800D02EC, "command.c");
        CommandGetResources_800D04F4( work, name, where );
    }
    return (void *)work ;
}