#ifndef __MGS_GAME_TARGET_H__
#define __MGS_GAME_TARGET_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct TARGET
{
    unsigned short class;
    unsigned short side;
    unsigned short map;
    unsigned short damaged;
    SVECTOR        center;
    SVECTOR        size;
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
    short          a_mode;
    short          field_40;
    short          field_42;
    int            field_44;
} TARGET;

enum
{
    TARGET_STALE     =   0x0,
    TARGET_AVAIL     =   0x1,
    TARGET_CAPTURE   =   0x2,
    TARGET_POWER     =   0x4,
    TARGET_PUSH      =   0x8,
    TARGET_SEEK      =  0x10,
    TARGET_DOWN      =  0x20,
    TARGET_C4        =  0x40,
    TARGET_TOUCH     =  0x80,
    TARGET_PUSH_OVER = 0x100,
    TARGET_NO_LOCKON = 0x200,
    TARGET_C4_CLEAR  = 0x400,
    TARGET_DIE       = 0x800,
};

enum
{
    ATK_BLAST = 0x2,
};

enum
{
    NO_SIDE = 0,
    PLAYER_SIDE = 1,
    ENEMY_SIDE = 2,
    BOTH_SIDE = 3
};

static inline void SetTargetClass( TARGET *target, unsigned int flag )
{
    target->class |= ( flag );
}

static inline void UnsetTargetClass( TARGET *target, unsigned int flag )
{
    target->class &= ~( flag );
}

#define TARGET_ARRAY_LENGTH 64

/* target.c */
int GM_TargetIntersects(TARGET *a, TARGET *b);
int GM_TargetIntersectsNoSide(TARGET *a, TARGET *b);

void    GM_ResetTargets(void);
TARGET *GM_AllocTarget(void);
void    GM_FreeTarget(TARGET *target);
void    GM_MoveTarget(TARGET *target, SVECTOR *pVec);
TARGET *GM_CaptureTarget(TARGET *target);
TARGET *GM_C4Target(TARGET *target);
int     GM_TouchTarget(TARGET *target);
int     GM_PowerTarget(TARGET *target);
int     GM_PushTarget(TARGET *target);
void    GM_SetTarget(TARGET *target, int class, int side, SVECTOR *size);
void    GM_Target_8002DCB4(TARGET *target, int a2, int a3, int *a4, SVECTOR *a5);
void    GM_Target_8002DCCC(TARGET *target, int a2, int a3, int hp, int a5, SVECTOR *a6);
void    sub_8002DD14(TARGET *target, MATRIX *pMatrix) ;
void    sub_8002DD1C(SVECTOR *a1, SVECTOR *a2, TARGET *a3);
int     sub_8002DDE0(SVECTOR *a1, SVECTOR *a2, TARGET *a3, SVECTOR *a4);
int     GM_Target_8002E1B8(SVECTOR *pVec, SVECTOR *pVec1, int map_bit, SVECTOR *pVec2, int side);
int     sub_8002E2A8(SVECTOR *arg0, SVECTOR *arg1, int map, SVECTOR *arg3);
void    GM_Target_8002E374(int *ppDownCount, TARGET **ppTargets);

#endif // __MGS_GAME_TARGET_H__
