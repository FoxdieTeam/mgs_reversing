#ifndef __MGS_GAME_TARGET_H__
#define __MGS_GAME_TARGET_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct TARGET
{
    u_short  class;
    u_short  side;
    u_short  map;
    u_short  damaged;
    SVECTOR  center;
    SVECTOR  size;
    int     *field_18; /* unused */
    SVECTOR *field_1C; /* unused */
    MATRIX  *body;
    short    p_mode;
    short    vital;
    short    damage;
    short    faint;
    SVECTOR  force;
    SVECTOR  offset;
    short    flag;
    short    a_mode;
    short    push_side;
    short    captured;
    int      weapon;
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
    POWER_ONCE      = 0,
    POWER_DECREASE  = 1,
    POWER_THRESHOLD = 2,
    POWER_CONST     = 3,
    POWER_EXPLODE   = 4,
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

#define TARGET_MAX 64

/* target.c */
void    GM_InitTargetSystem(void);
TARGET *GM_AllocTarget(void);
void    GM_FreeTarget(TARGET *target);
void    GM_MoveTarget(TARGET *target, SVECTOR *pVec);
TARGET *GM_CaptureTarget(TARGET *target);
TARGET *GM_C4Target(TARGET *target);
int     GM_TouchTarget(TARGET *target);
int     GM_PowerTarget(TARGET *target);
int     GM_PushTarget(TARGET *target);
void    GM_SetTarget(TARGET *target, int class, int side, SVECTOR *size);
void    GM_SetCaptureTarget(TARGET *target, int a_mode, int faint, int *a4, SVECTOR *a5);
void    GM_SetPowerTarget(TARGET *target, int p_mode, int a_mode, int vital, int faint, SVECTOR *force);
void    GM_TargetBody(TARGET *target, MATRIX *body) ;
int     GM_OnlineTargetCheck(SVECTOR *from, SVECTOR *to, int map, SVECTOR *hit, int side);
int     GM_OnlineTargetCheckAny(SVECTOR *from, SVECTOR *to, int map, SVECTOR *hit);
void    GM_GetTargets(int *count, TARGET **targets);

#endif // __MGS_GAME_TARGET_H__
