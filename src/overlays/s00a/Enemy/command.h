#include "Game/game.h"
#include "libgv/libgv.h"

typedef struct _CommanderWork
{
    GV_ACT         actor;
    unsigned short unk; //0x20
    unsigned short unk2; //0x22
    int            name; //0x24
} CommanderWork;

typedef struct _TOPCOMMAND_STRUCT {
    int mode;
    int alert;
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

#define TOP_COMM_TRAVEL 0
#define TOP_COMM_ALERT  1

extern SVECTOR       ENEMY_TARGET_SIZE_800C35A4;
extern SVECTOR       ENEMY_TARGET_FORCE_800C35AC;
extern SVECTOR       ENEMY_ATTACK_SIZE_800C35B4;
extern SVECTOR       ENEMY_ATTACK_FORCE_800C35BC;
extern SVECTOR       ENEMY_TOUCH_SIZE_800C35C4;
extern SVECTOR       ENEMY_TOUCH_FORCE_800C35CC;
extern SVECTOR       COM_NO_POINT_800C35D4;

extern int           dword_800E01F4;

extern const char           aCom_noisemode_disD_800E0940[]; // COM_NOISEMODE_DIS =%d \n
extern const char           aEeeDDDTD_800E095C[];           //eee %d %d %d t %d \n

extern int           s00a_dword_800E0CA0;

extern int           s00a_dword_800E0D2C;
extern int           s00a_dword_800E0D30;

extern int           COM_SHOOTRANGE_800E0D88; 
extern int           COM_EYE_LENGTH_800E0D8C;

extern int           COM_PlayerAddress_800E0D90;
extern unsigned int  ENE_SPECIAL_FLAG_800E0D94;


extern ENEMY_COMMAND EnemyCommand_800E0D98;

//extern int         EC_MODE_800E0DB0; // EC_MODE
extern SVECTOR       s00a_dword_800E0E3C;

extern int                     COM_PlayerMap_800E0F1C;
extern TOPCOMMAND_STRUCT       TOPCOMMAND_800E0F20;
extern TOPCOMMAND_STRUCT       s00a_dword_800E0F28;
extern SVECTOR                 COM_PlayerPosition_800E0F30;
extern int                     COM_NOISEMODE_DIS_800E0F38;
extern unsigned int            COM_GameStatus_800E0F3C;
extern short                   COM_PlayerAddressOne_800E0F40[];

extern int          COM_ALERT_DECREMENT_800E0F60;
extern int          GM_GameFlag_800E0F64;
extern int          COM_VibTime_800E0F68;

extern void  s00a_command_800CEC90( void ) ;
extern void  s00a_command_800CECF4( void ) ;
extern short s00a_command_800CEDE8( int ops, void *val, int where );
extern short s00a_command_800CED88( int ops, SVECTOR* svec );
extern void  s00a_command_800CFA94( CommanderWork* work ) ;
extern void  s00a_command_800CFEA8( void ) ;
extern int   s00a_command_800D0128( int ops );
extern void  s00a_command_800D018C( CommanderWork* work ) ;
extern void  s00a_command_800D0218( void ) ;
extern void  s00a_command_800D0344( void ) ;
