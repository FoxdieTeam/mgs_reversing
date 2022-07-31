#ifndef GAME_H
#define GAME_H

#include "linker.h"
#include "libdg.h"
#include "actor.h"

typedef struct Actor_GM_Daemon
{
  Actor field_0;
  int field_20;
  int field_24;
} Actor_GM_Daemon;


typedef struct _MOTION_CONTROL
{
    void*   field_00_oar_ptr;       //0x00
    unsigned short  field_04;       //0x04
    unsigned short  field_06;       
    unsigned short  field_08;       //0x08
    unsigned short  field_0A;     
    unsigned long   field_0C;       //0x0C
    unsigned long   field_10;       //0x10
    unsigned short  field_14;       //0x14
    unsigned short  field_16;   
    short           field_18;       //0x18
    unsigned short  field_1A;       //0x1A
    unsigned short  field_1C;       //0x1C
    unsigned short  field_1E;      
    unsigned short  field_20;       //0x20
    unsigned short  field_22;      
    unsigned long   field_24;       //0x24
    unsigned long   field_28;       //0x28
    unsigned short  field_2C;       //0x2C
    unsigned short  field_2E;     
    unsigned short  field_30;       //0x30
    unsigned short  field_32;       //0x32
    SVECTOR*        field_34;       //0x34
    SVECTOR        *step;           //0x38
    unsigned short* field_3C;       //0x3C
    unsigned long   interp;         //0x40
    SVECTOR field_44;
    SVECTOR *field_4C;
    // todo: padding field here?
} MOTION_CONTROL;

typedef struct _OBJECT
{
    DG_OBJS           *objs;        //0x00
    unsigned long      flag;        //0x04
    MATRIX            *light;       //0x08
    unsigned short     map_name;    //0x0C
    short              action_flag; //0x0E
    short     field_10;    //0x10 no match with unsigned in sna_init_8004E260
    unsigned short     field_12;    //0x12
    MOTION_CONTROL    *m_ctrl;      //0x14
    unsigned short     field_18;    //0x18
    short     field_1A;    //0x1A must be signed for sna_init_anim_box_stop_800554B4 to match
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
    MOTION_CONTROL    *m_ctrl;      //0x14
    unsigned short     field_18;    //0x18
    unsigned short     field_1A;    //0x1A
    unsigned short     field_1C;    //0x1C
    unsigned short     field_1E;    //0x1C
    unsigned long      field_20;    //0x20
} OBJECT_NO_ROTS;

extern int GM_CurrentMap_800AB9B0;
extern int GM_NoisePower_800ABA24;
extern int GM_NoiseLength_800ABA30;
extern SVECTOR GM_NoisePosition_800AB9F8;

typedef enum
{
    PLAYER_STATUS_FIRST_PERSON                =  0x1,
    PLAYER_STATUS_FIRST_PERSON_DUCT           =  0x2,
    PLAYER_STATUS_UNK4                        =  0x4,
    PLAYER_STATUS_UNK8                        =  0x8,
    PLAYER_STATUS_MOVING                      =  0x10,
    PLAYER_STATUS_CROUCHING                   =  0x20,
    PLAYER_STATUS_PRONE                       =  0x40,
    PLAYER_STATUS_UNK80                       =  0x80,
    PLAYER_STATUS_UNK100                      =  0x100,
    PLAYER_STATUS_UNK200                      =  0x200,
    PLAYER_STATUS_UNK400                      =  0x400,
    PLAYER_STATUS_PREVENT_FIRST_PERSON        =  0x800,
    PLAYER_STATUS_UNK1000                     =  0x1000,
    // triggers game over when set. could this be the 'dead' flag?
    PLAYER_STATUS_GAMEOVER                    =  0x2000,
    PLAYER_STATUS_UNK4000                     =  0x4000,
    PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH  =  0x8000,
    PLAYER_STATUS_ON_WALL                     =  0x10000,
    PLAYER_STATUS_KNOCKING                    =  0x20000,
    PLAYER_STATUS_UNK40000                    =  0x40000,
    PLAYER_STATUS_UNK80000                    =  0x80000,
    PLAYER_STATUS_UNK100000                   =  0x100000,
    PLAYER_STATUS_PREVENT_ITEM_SWITCH         =  0x200000,
    PLAYER_STATUS_PREVENT_WEAPON_SWITCH       =  0x400000,
    PLAYER_STATUS_INVULNERABLE                =  0x800000,
    PLAYER_STATUS_UNK1000000                  =  0x1000000,
    PLAYER_STATUS_UNK2000000                  =  0x2000000,
    PLAYER_STATUS_UNK4000000                  =  0x4000000,
    PLAYER_STATUS_UNK8000000                  =  0x8000000,
    PLAYER_STATUS_UNK10000000                 =  0x10000000,
    PLAYER_STATUS_UNK20000000                 =  0x20000000,
    // Set from sna_init_check_dead_8004E384() and sna_init_anim_dying_80055524().
    PLAYER_STATUS_DEADORDYING                 =  0x40000000,
    PLAYER_STATUS_UNK80000000                 =  0x80000000,
} PlayerStatusFlag;

static inline void GM_SetNoise(int power, int length, SVECTOR* pos)
{
    int old = GM_NoisePower_800ABA24;
    if ( power < old) return;
    if ( power == old && length < GM_NoiseLength_800ABA30) return;
    
    GM_NoisePower_800ABA24 = power;
    GM_NoiseLength_800ABA30 = length;
    GM_NoisePosition_800AB9F8 = *pos;          
}

#endif //GAME_H
