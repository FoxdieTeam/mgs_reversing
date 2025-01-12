/**
 * This file defines the core structures, enumerations, and function prototypes
 * used in the LibGV library, It provides essential services for managing game
 * actors, memory allocation, message handling, input processing, and
 * mathematical operations.
 *
 * Key Components:
 * - Actor Management: Defines structures and functions for creating, updating,
 * and managing game actors
 * - Memory Management: Provides dynamic memory allocation and heap management
 * to handle the game's resource
 * - Message Handling: Implements a messaging system for communication between
 * different game components
 * - Input Processing: Manages gamepad inputs.
 * - Cache System: Handles file caching and loading for game resources by
 * hashing file names
 * - Heap Management: Manages memory allocation and deallocation using a
 * heap-based system
 * - Mathematical Operations: Offers functions for vector calculations and other
 * mathematical tasks needed for game physics and transformations.
 */

#ifndef _LIBGV_H_
#define _LIBGV_H_

#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libetc.h>

/* gvd.c */
extern int GV_Time;

void GV_StartDaemon(void);
void GV_ResetSystem(void);

void GV_SetPacketTempMemory(void);
void GV_ResetPacketMemory(void);

/* strcode.c */
int GV_StrCode( const char *string );

/* debug.c */
void GV_Assert( char *, int );
void GV_Warning( char *, int );
void GV_Error( char *, int );

/*------ Actor Management ---------------------------------------------------*/

struct GV_ACT;

typedef void (*GV_ACTFUNC)(struct GV_ACT *);
typedef void (*GV_FREEFUNC)(void *);

/**
 * @brief Linked list of game actors.
 * A game actor is an entity with a name and an update function.
 */
typedef struct GV_ACT
{
    struct GV_ACT  *prev;
    struct GV_ACT  *next;
    GV_ACTFUNC      act;        // update callback
    GV_ACTFUNC      die;        // shutdown callback
    GV_FREEFUNC     free;       // free callback
    const char     *filename;   // source filename
    int             field_18;
    int             field_1C;
} GV_ACT;

struct ActorList    // private to libgv/actor.c
{
    GV_ACT first;
    GV_ACT last;
    short  pause;
    short  kill;
};

struct PauseKill    // private to libgv/actor.c
{
    short pause;
    short kill;
};

enum {
    GV_ACTOR_DAEMON,    // 0
    GV_ACTOR_MANAGER,   // 1
    GV_ACTOR_LEVEL2,    // 2 todo: rename
    GV_ACTOR_LEVEL3,    // 3 todo: rename
    GV_ACTOR_LEVEL4,    // 4 todo: rename
    GV_ACTOR_LEVEL5,    // 5 todo: rename
//--- memleak ---
    GV_ACTOR_AFTER,     // 6
    GV_ACTOR_AFTER2,    // 7

    GV_ACTOR_DAEMON2,   // 8
    GV_ACTOR_LEVEL      // 9
};

/* actor.c */
void    GV_InitActorSystem(void);
void    GV_ConfigActorSystem(int index, short pause, short kill);
void    GV_DumpActorSystem(void);
void    GV_ExecActorSystem(void);
void    GV_DestroyActorSystem(int level);
void    GV_InitActor(int level, GV_ACT *actor, GV_FREEFUNC free_func);
GV_ACT *GV_NewActor(int level, int memSize);

#define GV_SetActor(_actor, _act, _die) \
    GV_SetNamedActor(_actor, _act, _die, __FILE__)

void    GV_SetNamedActor(GV_ACT *actor,
                         GV_ACTFUNC act_func,
                         GV_ACTFUNC die_func,
                         const char *filename);

void    GV_DestroyActor(GV_ACT *actor);
void    GV_DestroyActorQuick(GV_ACT *actor);
void    GV_DestroyOtherActor(GV_ACT *actor);

/*------ Cache System -------------------------------------------------------*/

enum GV_CACHE_REGION
{
    GV_REGION_NOCACHE,
    GV_REGION_CACHE,
    GV_REGION_RESIDENT,
};

typedef struct GV_CACHE_TAG
{
    int   id;
    void *ptr;
} GV_CACHE_TAG;

#define MAX_CACHE_TAGS 128

typedef struct GV_CACHE_PAGE
{
    GV_CACHE_TAG tags[MAX_CACHE_TAGS];
} GV_CACHE_PAGE;

#define MAX_FILE_HANDLERS 26    // from 'a' to 'z'

typedef int (*GV_LOADFUNC)(unsigned char *data, int id);

/* cache.c */
int   GV_CacheID(int strcode, int extID);
int   GV_CacheID2(const char *fileName, int extID);
int   GV_CacheID3(char *string);
void *GV_GetCache(int id);
int   GV_SetCache(int id, void *buf);
void  GV_SetLoader(int fileExtChar, GV_LOADFUNC func);
void  GV_InitLoader(void);
void  GV_InitCacheSystem(void);
void  GV_ResidentFileCache(void);
void  GV_FreeCacheSystem(void);
int   GV_LoadInit(void *buf, int id, int region);

/*------ Memory Management --------------------------------------------------*/

#define GV_PACKET_MEMORY0       0
#define GV_PACKET_MEMORY1       1
#define GV_NORMAL_MEMORY        2   // known memleak constant
#define GV_MEMORY_MAX           3

#define GV_NORMAL_MEMORY_TOP    ((void *)0x80117000)
#define GV_NORMAL_MEMORY_SIZE   0x6b000 /* 428KiB */

#define GV_PACKET_MEMORY0_TOP   ((void *)0x80182000)
#define GV_PACKET_MEMORY1_TOP   ((void *)0x801b1000)
#define GV_PACKET_MEMORY_SIZE   0x2f000 /* 188KiB */

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

void  GV_ResidentHeapReset(void);
void  GV_SaveResidentTop(void);

void  GV_InitResidentMemory(void);
void *GV_AllocResidentMemory(long size);

/*------ Message Handling ---------------------------------------------------*/

typedef struct          // from memleak
{
    unsigned short address;
    unsigned short _len;
    unsigned short message[7];
    unsigned short message_len;
} GV_MSG;

typedef struct          // private to libgv/message.c
{
    int     num;
    GV_MSG  msg[16];
} MESSAGE_LIST;

/* message.c */
void GV_InitMessageSystem(void);
void GV_ClearMessageSystem(void);
int  GV_SendMessage(GV_MSG *send);
int  GV_ReceiveMessage(int address, GV_MSG **msg_ptr);

/*------ Input Processing ---------------------------------------------------*/

// TODO: typedef enum and use type in GV_PAD?
enum
{
    PAD_UP = PADLup,        //  0x1000
    PAD_DOWN = PADLdown,    //  0x4000
    PAD_LEFT = PADLleft,    //  0x8000
    PAD_RIGHT = PADLright,  //  0x2000
    PAD_TRIANGLE = PADRup,  //  0x0010
    PAD_CROSS = PADRdown,   //  0x0040
    PAD_SQUARE = PADRleft,  //  0x0080
    PAD_CIRCLE = PADRright, //  0x0020
    PAD_L1 = PADL1,         //  0x0004
    PAD_L2 = PADL2,         //  0x0001
    PAD_R1 = PADR1,         //  0x0008
    PAD_R2 = PADR2,         //  0x0002
    PAD_START = PADstart,   //  0x0800
    PAD_SELECT = PADselect, //  0x0100
};

#define PAD_DIR (PAD_LEFT | PAD_DOWN | PAD_RIGHT | PAD_UP) // 0xF000

typedef struct
{
    unsigned short status;
    unsigned short press;
    unsigned short release;
    unsigned short quick;
    short          dir;

    short         analog;
    unsigned char right_dx;
    unsigned char right_dy;
    unsigned char left_dx;
    unsigned char left_dy;
} GV_PAD;

enum
{
    GV_PAD_DIGITAL = 0,
    GV_PAD_ANAJOY = 1,
    GV_PAD_ANALOG = 2
};

/* pad.c */
extern int GV_PadMask;

void GV_InitPadSystem(void);
void GV_UpdatePadSystem(void);
void GV_OriginPadSystem(int);
int  GV_GetPadOrigin(void);
int  GV_GetPadDirNoPadOrg(unsigned int);

/*------ Math Operations ----------------------------------------------------*/

/* math.c */
void    GV_AddVec3(SVECTOR *vec1, SVECTOR *vec2, SVECTOR *dst);
void    GV_SubVec3(SVECTOR *vec1, SVECTOR *vec2, SVECTOR *dst);
int     GV_VecLen3(SVECTOR *vec);
void    GV_LenVec3(SVECTOR *in, SVECTOR *out, int denom, int num);
int     GV_DiffVec3(SVECTOR *vec1, SVECTOR *vec2);
int     GV_VecDir2(SVECTOR *vec);
void    GV_DirVec2(int angle, int radius, SVECTOR *out);
void    GV_DirVec3(SVECTOR *angle, int length, SVECTOR *pDstVec);
unsigned int GV_DiffDirU(int from, int to);
int     GV_DiffDirS(int from, int to);
int     GV_DiffDirAbs(int from, int to);
int     GV_RandU(unsigned int input);
int     GV_RandS(int input);

/* math_near.c */
int     GV_NearExp2(int from, int to);
int     GV_NearExp4(int from, int to);
int     GV_NearExp8(int from, int to);
int     GV_NearPhase(int from, int to);
int     GV_NearRange(int from, int to, int range);
int     GV_NearSpeed(int from, int to, int range);
int     GV_NearTime(int from, int to, int interp);
int     GV_NearExp2P(int from, int to);
int     GV_NearExp4P(int from, int to);
int     GV_NearExp8P(int from, int to);
int     GV_NearTimeP(int from, int to, int interp);
void    GV_NearExp2V(short *from, short *to, int count);
void    GV_NearExp4V(short *from, short *to, int count);
void    GV_NearExp8V(short *from, short *to, int count);
void    GV_NearPhaseV(short *from, short *to, int count);
void    GV_NearRangeV(short *from, short *to, int range, int count);
void    GV_NearSpeedV(short *from, short *to, int range, int count);
void    GV_NearTimeV(short *from, short *to, int interp, int count);
void    GV_NearExp2PV(short *from, short *to, int count);
void    GV_NearExp4PV(short *from, short *to, int count);
void    GV_NearExp8PV(short *from, short *to, int count);
void    GV_NearRangeExp2V(short *from, short *to, int range, int count);
void    GV_NearRangeExp4V(short *from, short *to, int range, int count);
void    GV_NearRangeExp8V(short *from, short *to, int range, int count);
void    GV_NearTimePV(short *from, short *to, int interp, int count);

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

#endif // _LIBGV_H_
