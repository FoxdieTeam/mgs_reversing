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