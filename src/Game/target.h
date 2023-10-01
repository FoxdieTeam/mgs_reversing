#ifndef _TARGET_H_
#define _TARGET_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

typedef struct TARGET
{
    unsigned short class;
    unsigned short field_2_side;
    unsigned short field_4_map;
    unsigned short field_6_flags;
    SVECTOR        field_8_vec;
    SVECTOR        field_10_size;
    int           *field_18;
    SVECTOR       *field_1C;
    MATRIX        *field_20;
    short          field_24;
    short          field_26_hp;
    short          field_28;
    short          field_2A;
    SVECTOR        field_2C_vec;
    SVECTOR        field_34_vec;
    short          field_3C;
    short          field_3E;
    short          field_40;
    short          field_42;
    int            field_44;
} TARGET;

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

#define	TARGET_FLAG	( TARGET_POWER | TARGET_CAPTURE | TARGET_PUSH | TARGET_TOUCH | TARGET_SEEK ) // 0x9e

enum
{
    NO_SIDE = 0,
    PLAYER_SIDE = 1,
    ENEMY_SIDE = 2,
    BOTH_SIDE = 3
};

static inline void SetTargetClass( TARGET *target, unsigned int flag )
{
    target->class |= ( flag | TARGET_AVAIL );
}

int        GM_Target_8002E1B8(SVECTOR *pVec, SVECTOR *pVec1, int map_bit, SVECTOR *pVec2, int side);
void       GM_Targets_Reset_8002D3F0(void);
void       GM_FreeTarget_8002D4B0(TARGET *pTarget);
void       GM_SetTarget_8002DC74(TARGET *pTarget, int targetFlags, int whichSide, SVECTOR *pSize);
void       GM_Target_8002DCCC(TARGET *pTarget, int a2, int a3, int hp, int a5, SVECTOR *a6);
void       GM_Target_SetVector_8002D500(TARGET *pTarget, SVECTOR *pVec);
void       GM_Target_8002E374(int *ppDownCount, TARGET **ppTargets);
TARGET *GM_AllocTarget_8002D400(void);
// int GM_Target_8002D7DC(TARGET *pTarget);
int        GM_TouchTarget_8002D6D8(TARGET *pTarget);
int        sub_8002D7DC(TARGET *pTarget);
int        sub_8002D208(TARGET *pTarget, TARGET *a2);
int        sub_8002DA14(TARGET *pTarget);
void       sub_8002DD1C(SVECTOR *a1, SVECTOR *a2, TARGET *a3);
int        sub_8002DDE0(SVECTOR *a1, SVECTOR *a2, TARGET *a3, SVECTOR *a4);
void       GM_Target_8002DCB4(TARGET *pTarget, int a2, int a3, int *a4, SVECTOR *a5);
TARGET *GM_C4Target_8002D620(TARGET *pTarget);
TARGET *GM_CaptureTarget_8002D530(TARGET *pTarget);

#endif // _TARGET_H_
