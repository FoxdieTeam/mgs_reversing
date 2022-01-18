#ifndef GAME_H
#define GAME_H

#include "linker.h"
#include "libdg.h"

//Placeholder: this struct is incorrect
//might be named MOTION
typedef struct _ACTION
{
    unsigned long   field_00;       //0x00
    unsigned long   field_04;       //0x04
    unsigned long   field_08;       //0x08
    unsigned long   field_0C;       //0x0C
    unsigned long   field_10;       //0x10
    unsigned long   field_14;       //0x14
    short           field_18;       //0x18
    unsigned short  field_1A;       //0x1A
    unsigned long   field_1C;       //0x1C
    unsigned long   field_20;       //0x20
    unsigned long   field_24;       //0x24
    unsigned long   field_28;       //0x28
    unsigned long   field_2C;       //0x2C
    unsigned short  field_30;       //0x30
    unsigned short  field_32;       //0x32
    unsigned long   field_34;       //0x34
    SVECTOR        *step;           //0x38
    unsigned long   field_3C;       //0x3C
    unsigned long   field_40;       //0x40
} ACTION;

typedef struct _OBJECT
{
    DG_OBJS           *objs;        //0x00
    unsigned long      flag;        //0x04
    MATRIX            *light;       //0x08
    unsigned short     map_name;    //0x0C
    short              action_flag; //0x0E
    unsigned short     field_10;    //0x10
    unsigned short     field_12;    //0x12
    ACTION            *action;      //0x14
    unsigned short     field_18;    //0x18
    unsigned short     field_1A;    //0x1A
    unsigned short     field_1C;    //0x1C
    unsigned short     field_1E;    //0x1C
    unsigned long      field_20;    //0x20
    SVECTOR            rots[ 0 ];   //0x24
} OBJECT;

typedef struct _OBJECT_NO_ROTS
{
    DG_OBJS           *objs;        //0x00
    unsigned long      flag;        //0x04
    MATRIX            *light;       //0x08
    unsigned short     map_name;    //0x0C
    unsigned short     action_flag; //0x0E
    unsigned short     field_10;    //0x10
    unsigned short     field_12;    //0x12
    ACTION            *action;      //0x14
    unsigned short     field_18;    //0x18
    unsigned short     field_1A;    //0x1A
    unsigned short     field_1C;    //0x1C
    unsigned short     field_1E;    //0x1C
    unsigned long      field_20;    //0x20
} OBJECT_NO_ROTS;

#endif //GAME_H