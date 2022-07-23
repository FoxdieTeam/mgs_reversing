#ifndef _TARGET_H_
#define _TARGET_H_

#include <sys/types.h>
#include <LIBGTE.h>
#include <LIBGPU.h>

typedef struct GM_Target
{
    short field_0_flags;
    short field_2_side;
    unsigned short field_4_map;
    short field_6_flags;
    SVECTOR field_8_vec;
    SVECTOR field_10_size;
    int field_18;
    int field_1C;
    MATRIX *field_20;
    short field_24;
    short field_26_hp;
    short field_28;
    short field_2A;
    short field_2C_vec;
    short field_2E;
    int field_30;
    short field_34_vec;
    short field_36;
    short field_38;
    short field_3A;
    short field_3C;
    short field_3E;
    short field_40;
    short field_42;
    int field_44;
} GM_Target;

enum
{
    TARGET_STALE = 0,         
    TARGET_AVAIL = 1,         
    TARGET_CAPTURE = 2,         
    TARGET_POWER = 4,         
    TARGET_PUSH = 8, 
    TARGET_SEEK = 16,         
    TARGET_DOWN = 32,         
    TARGET_C4 = 64,             
    TARGET_TOUCH = 128,         
    TARGET_PUSH_OVER = 256,     
    TARGET_NO_LOCKON = 512,
    TARGET_C4_CLEAR = 1024,     
    TARGET_DIE = 2048,    
};

enum 
{
    NO_SIDE = 0,             
    PLAYER_SIDE = 1,         
    ENEMY_SIDE = 2,             
    BOTH_SIDE = 3             
};

int GM_Target_8002E1B8(SVECTOR *pVec, SVECTOR *pVec1, int map_bit, SVECTOR *pVec2, int side);
void GM_Targets_Reset_8002D3F0(void);

#endif // _TARGET_H_
