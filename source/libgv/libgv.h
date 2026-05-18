/**
 * Main include header for the GV library.
 *
 * LibGV is the core of the MGS "system" library group and provides various
 * services, including memory management, resource loading, input processing,
 * actor creation/execution control, message-passing, and linear algebra.
 */

#ifndef __MGS_LIBGV_H__
#define __MGS_LIBGV_H__

#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libetc.h>

/* gvd.c */
extern int GV_Time;
#ifndef __LIBGV_GVD_C__
extern int GV_Clock;
extern int GV_PassageTime;
#endif

void GV_StartDaemon(void);
void GV_ResetSystem(void);

void GV_SetPacketTempMemory(void);
void GV_ResetPacketMemory(void);

/* strcode.c */
int GV_StrCode( const char *string );

/*---------------------------------------------------------------------------*/

/* debug.c */
extern const char *GV_DebugMes;

void GV_Assert( char *, int );
void GV_Warning( char *, int );
void GV_Error( char *, int );

#ifdef DEV_EXE // #ifdef DEBUG
#define ASSERT(c)       if (!(c)) { GV_Assert(__FILE__, __LINE__); }
#define WARNING(f,v)    GV_Warning(f,v)
#define ERROR(f,v)      GV_Error(f,v)
#define OPERATOR()
#define MARK(n)         (GV_DebugMes = (char *)n)
#define HANGUP()        (*(int *)1 = 0)
#else
// NOTE: Assertions were disabled for INTEGRAL, but the US release
// (and possibly others) were compiled with assertions still enabled.
#define ASSERT(c)
#define WARNING(f,v)
#define ERROR(f,v)
#define OPERATOR()
#define MARK(n)
#define HANGUP()
#endif

/*------ Actor Management ---------------------------------------------------*/

struct _GV_ACT;

typedef void (*GV_ACTFUNC)(struct _GV_ACT *);
typedef void (*GV_FREEFUNC)(void *);

/**
 * @brief Linked list of game actors.
 * A game actor is an entity with a name and an update function.
 */
typedef struct _GV_ACT
{
    struct _GV_ACT *prev;
    struct _GV_ACT *next;
    GV_ACTFUNC      act;        // update callback
    GV_ACTFUNC      die;        // shutdown callback
    GV_FREEFUNC     free;       // free callback
    const char     *filename;   // source filename
    int             runtime;
    int             count;
} GV_ACT;

typedef struct      // private to libgv/actor.c
{
    GV_ACT start;
    GV_ACT end;
    short  pause_level;
    short  kill_level;
} AList;

enum {
    GV_ACTOR_DAEMON,    // 0
    GV_ACTOR_MANAGER,   // 1
    GV_ACTOR_ASSIST,    // 2

    GV_ACTOR_PREV2,     // 3
    GV_ACTOR_PREV,      // 4

    GV_ACTOR_USER,      // 5

    GV_ACTOR_AFTER,     // 6
    GV_ACTOR_AFTER2,    // 7

    GV_ACTOR_DAEMON2,   // 8
    GV_ACTOR_LEVEL      // 9
};

#define GV_KILL_LEVEL_NORMAL    (0x04)
#define GV_KILL_LEVEL_MANAGER   (0x07)

#define GV_PAUSE_NOSTOP     0x00
#define GV_PAUSE_STOP       0x01
#define GV_PAUSE_PAUSE      0x02
#define GV_PAUSE_MENU       0x04
#define GV_PAUSE_READERROR  0x08

#define GV_LEVEL_NORMAL     (GV_PAUSE_STOP|GV_PAUSE_PAUSE|GV_PAUSE_MENU|GV_PAUSE_READERROR)
#define GV_LEVEL_STOP       (GV_PAUSE_STOP|GV_PAUSE_READERROR)

/* actor.c */
#ifndef __LIBGV_ACTOR_C__
extern int GV_PauseLevel;
#endif

void GV_InitActorSystem( void );
void GV_ConfigActorSystem( int level, short pause, short kill );
void GV_DumpActorSystem( void );
void GV_ExecActorSystem( void );
void GV_DestroyActorSystem( int kill );
void GV_InitActor( int level, void *this, GV_FREEFUNC free );
void *GV_NewActor( int level, int size );
void GV_SetNamedActor( void *this, void *act, void *die, const char *name );
void GV_DestroyActor( void *this );
void GV_DestroyActorQuick( void *this );
void GV_DestroyOtherActor( void *target );

#define GV_SetActor( _this, _act, _die ) GV_SetNamedActor( _this, _act, _die, __FILE__ )

/*------ Cache System -------------------------------------------------------*/

enum GV_CACHE_REGION
{
    GV_INIT_NOCACHE,
    GV_INIT_CACHE,
    GV_INIT_RESIDENT,
};

typedef struct CACHE
{
    int   id;
    void *buf;
} CACHE;

#define MAX_CACHES 128

#define MAX_LOADERS  26  // 'a'～'z'

typedef int ( *GV_LOADFUNC )( void *data, int id );

/* cache.c */
int   GV_CacheID( int root_id, int spec );
int   GV_CacheID2( const char *root_name, int spec );
int   GV_CacheID3( char *name );
void *GV_GetCache( int id );
int   GV_SetCache( int id, void *buf );
void  GV_SetLoader( int spec, GV_LOADFUNC init );
void  GV_ResetLoader( void );
void  GV_InitCacheSystem( void );
void  GV_SaveResidentFileCache( void );
void  GV_FreeCacheSystem( void );
int   GV_LoadInit( void *data, int name, int cache_mode );

/*------ Memory Management --------------------------------------------------*/

#define PACK_SIZE       (188 * 1024) /* 188KiB */
#define MEM_SIZE        (428 * 1024) /* 428KiB */

#define MEM_BOTTOM      ((void *)0x801E0000)

#define PACK_ADDR0      (MEM_BOTTOM - PACK_SIZE * 2)
#define PACK_ADDR1      (MEM_BOTTOM - PACK_SIZE)

#define MEM_ADDR        (PACK_ADDR0 - MEM_SIZE)
#define RESIDENT_BOTTOM (MEM_ADDR)

#define GV_MEMORY_STATIC        0
#define GV_MEMORY_DYNAMIC       1

#define GV_PACKET_MEMORY0       0
#define GV_PACKET_MEMORY1       1
#define GV_NORMAL_MEMORY        2   // known memleak constant
#define MAX_MEMSYS              3

enum GV_ALLOC_STATE
{
    GV_ALLOC_STATE_FREE = 0,
    GV_ALLOC_STATE_VOID = 1,
    GV_ALLOC_STATE_USED = 2,
};

typedef struct GV_ALLOC
{
    void        *start;
    unsigned int state; // pointer to start of memory for dynamic allocations
} GV_ALLOC;

enum GV_HEAP_FLAG
{
    GV_HEAP_FLAG_DYNAMIC = 0x1,
    GV_HEAP_FLAG_VOIDED  = 0x2,
    GV_HEAP_FLAG_FAILED  = 0x4,
};

#define MAX_ALLOC_UNITS 512

typedef struct GV_HEAP
{
    int      flags;
    void    *start;
    void    *end;
    int      used;
    GV_ALLOC units[MAX_ALLOC_UNITS];
} GV_HEAP;

/* memory.c */
void  GV_InitMemorySystemAll(void);
void  GV_InitMemorySystem(int, int, void *, int);
void  GV_ResetMemory(void);
void *GV_AllocMemory(int, int);
void *GV_AllocMemory2(int, int, void **);
void  GV_FreeMemory(int, void *);
void  GV_FreeMemory2(int, void **);
void  GV_ClearMemorySystem(int);
void  GV_CheckMemorySystem(int);
void  GV_DumpMemorySystem(int);
void  GV_CopyMemory(void *, void *, int);
void  GV_ZeroMemory(void *, int);
void *GV_Malloc(int);
void  GV_Free(void *);
void  GV_DelayedFree(void *);

void *GV_GetMaxFreeMemory(int which);
void *GV_SplitMemory(int which, void *addr, int size);

/* resident.c */
void  GV_InitResidentMemory( void );
void  GV_SaveResidentTop( void );
void *GV_AllocResidentMemory( long size );

/*------ Message Handling ---------------------------------------------------*/

typedef struct          // from memleak
{
    u_short address;
    u_short _len;
    u_short message[7];
    u_short message_len;
} GV_MSG;

#define MAX_MESSAGES 16

typedef struct          // private to libgv/message.c
{
    int     num;
    GV_MSG  messages[ MAX_MESSAGES ];
} MESSAGE_LIST;

/* message.c */
void GV_InitMessageSystem( void );
void GV_ClearMessageSystem( void );
int  GV_SendMessage( GV_MSG *send );
int  GV_ReceiveMessage( int address, GV_MSG **msg_ptr );

/*------ Input Processing ---------------------------------------------------*/

/* SNES-style button layout */
#define PAD_U           PADLup          // 0x1000 ↑
#define PAD_D           PADLdown        // 0x4000 ↓
#define PAD_L           PADLleft        // 0x8000 ←
#define PAD_R           PADLright       // 0x2000 →
#define PAD_A           PADRright       // 0x0020 ○
#define PAD_B           PADRdown        // 0x0040 ×
#define PAD_X           PADRup          // 0x0010 △
#define PAD_Y           PADRleft        // 0x0080 □
#define PAD_L1          PADL1           // 0x0004 L1
#define PAD_L2          PADL2           // 0x0001 L2
#define PAD_R1          PADR1           // 0x0008 R1
#define PAD_R2          PADR2           // 0x0002 R2
#define PAD_STA         PADstart        // 0x0800 START
#define PAD_SEL         PADselect       // 0x0100 SELECT
#define PAD_AL          PADi            // 0x0200 L3
#define PAD_AR          PADj            // 0x0400 R3

/* button masks */
#define PAD_UDLR        (PAD_U  | PAD_D  | PAD_L  | PAD_R)
#define PAD_ABXY        (PAD_A  | PAD_B  | PAD_X  | PAD_Y)
#define PAD_LR          (PAD_L1 | PAD_L2 | PAD_R1 | PAD_R2)

/* button aliases */
#define PAD_UP          PAD_U
#define PAD_DOWN        PAD_D
#define PAD_LEFT        PAD_L
#define PAD_RIGHT       PAD_R
#define PAD_CIRCLE      PAD_A
#define PAD_CROSS       PAD_B
#define PAD_TRIANGLE    PAD_X
#define PAD_SQUARE      PAD_Y
#define PAD_START       PAD_STA
#define PAD_SELECT      PAD_SEL
#define PAD_L3          PAD_AL
#define PAD_R3          PAD_AR

typedef struct
{
    u_short         status;
    u_short         press;
    u_short         release;
    u_short         quick;
    short           dir;

    short           analog;
    unsigned char   right_dx;
    unsigned char   right_dy;
    unsigned char   left_dx;
    unsigned char   left_dy;
} GV_PAD;

enum
{
    GV_PAD_DIGITAL = 0,
    GV_PAD_ANAJOY = 1,
    GV_PAD_ANALOG = 2
};

/* pad.c */
#ifndef __LIBGV_PAD_C__
extern u_short  GV_DemoPadStatus[2];
extern u_long   GV_DemoPadAnalog;
#endif
#ifndef __BSSDEFINE__
extern GV_PAD GV_PadData[4];
#endif
extern int GV_PadMask;

void GV_InitPadSystem(void);
void GV_UpdatePadSystem(void);
void GV_OriginPadSystem(int);
int  GV_GetPadOrigin(void);
int  GV_GetPadDirNoPadOrg(unsigned int);

/*------ Math Operations ----------------------------------------------------*/

/* util.c */
extern  void    GV_AddVec3( SVECTOR *vec1, SVECTOR *vec2, SVECTOR *vec3 );
extern  void    GV_SubVec3( SVECTOR *vec1, SVECTOR *vec2, SVECTOR *vec3 );
extern  int     GV_VecLen3( SVECTOR *vec );
extern  void    GV_LenVec3( SVECTOR *vec1, SVECTOR *vec2, int len1, int len2 );
extern  int     GV_DiffVec3( SVECTOR *vec1, SVECTOR *vec2 );
extern  int     GV_VecDir2( SVECTOR *vec );
extern  void    GV_DirVec2( int dir, int len, SVECTOR *vec );
extern  void    GV_DirVec3( SVECTOR *dir, int len, SVECTOR *vec );
extern  int     GV_DiffDirU( int from, int to );
extern  int     GV_DiffDirS( int from, int to );
extern  int     GV_DiffDirAbs( int from, int to );
extern  int     GV_RandU( int input );
extern  int     GV_RandS( int input );

/* near.c */
extern  int     GV_NearExp2( int from, int to );
extern  int     GV_NearExp4( int from, int to );
extern  int     GV_NearExp8( int from, int to );
extern  int     GV_NearPhase( int from, int to );
extern  int     GV_NearRange( int from, int to, int range );
extern  int     GV_NearSpeed( int from, int to, int speed );
extern  int     GV_NearTime( int from, int to, int interp );

extern  int     GV_NearExp2P( int from, int to );
extern  int     GV_NearExp4P( int from, int to );
extern  int     GV_NearExp8P( int from, int to );
extern  int     GV_NearTimeP( int from, int to, int interp );

extern  void    GV_NearExp2V( void *vfrom, void *vto, int n );
extern  void    GV_NearExp4V( void *vfrom, void *vto, int n );
extern  void    GV_NearExp8V( void *vfrom, void *vto, int n );
extern  void    GV_NearPhaseV( void *vfrom, void *vto, int n );
extern  void    GV_NearRangeV( void *vfrom, void *vto, int range, int n );
extern  void    GV_NearSpeedV( void *vfrom, void *vto, int speed, int n );
extern  void    GV_NearTimeV( void *vfrom, void *vto, int interp, int n );

extern  void    GV_NearExp2PV( void *vfrom, void *vto, int n );
extern  void    GV_NearExp4PV( void *vfrom, void *vto, int n );
extern  void    GV_NearExp8PV( void *vfrom, void *vto, int n );
extern  void    GV_NearExp2SV( void *vfrom, void *vto, int speed, int n );
extern  void    GV_NearExp4SV( void *vfrom, void *vto, int speed, int n );
extern  void    GV_NearExp8SV( void *vfrom, void *vto, int speed, int n );
extern  void    GV_NearTimePV( void *vfrom, void *vto, int interp, int n );

/* quat.c */
typedef struct {                /* short word type quaternion */
    short   x, y;
    short   z, w;
} SQUAT;

extern  void    GV_QuatToMat( SQUAT *quat, MATRIX *mat );
extern  void    GV_EulerToQuat( SVECTOR *rot, SQUAT *quat );
extern  void    GV_MatToQuat( MATRIX *mat, SQUAT *quat );
extern  void    GV_QuatSlerp( SQUAT *from, SQUAT *to, int t, SQUAT *res );
extern  void    GV_QuatNormalize( SQUAT *quat );
extern  void    GV_QuatMul( SQUAT *q1, SQUAT *q2, SQUAT *res );

/*---------------------------------------------------------------------------*/

static inline short FP_Extend(short value)
{
    value &= 0x0fff;

    if (value > 2048)
    {
        value -= 4096;
    }
    return value;
}

static inline int FP_Extend2(int value)
{
    value &= 0x0fff;

    if (value >= 2048)
    {
        value -= 4096;
    }
    return value;
}

static inline int FP_ExtendN(int value)
{
    value |= 0xf000;

    if (value < -2048)
    {
        value += 4096;
    }
    return value;
}

static inline int FP_Subtract(int fp, int toSub)
{
    short value = fp - toSub;

    value &= 0x0fff;

    if (value > 2048)
    {
        value -= 4096;
    }
    return value;
}

static inline int FP_Subtract_2(int a, int b)
{
    int value = a - b;

    if (value >= 0)
    {
        value &= 0x0fff;

        if (value >= 2048)
        {
            value -= 4096;
        }
    }
    else
    {
        value |= 0xf000;

        if (value < -2048)
        {
            value += 4096;
        }
    }
    return value;
}

#endif // __MGS_LIBGV_H__
