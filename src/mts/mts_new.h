#ifndef _MTS_NEW_H
#define _MTS_NEW_H

#include "mts.h"
#include <kernel.h>

#define SEMAPHORE_NOT_WAITING -1
#define SEMAPHORE_LAST_IN_QUEUE -1

enum {
    MTS_SYS_START = 0,
    MTS_SYS_EXIT = 1,
};

typedef struct MTS_SYS_MSG
{
    int       code;             // MTS_SYS_*
    int       tasknr;
    void    (*procedure)(void);
    void     *stack_pointer;
} MTS_SYS_MSG;

typedef struct MTS_ITASK
{
    struct MTS_ITASK *next;     // linked-list of all interrupt tasks
    int               tasknr;   // system task to wake up upon execution
    unsigned int      last;     // last execution time
    unsigned int      target;   // next execution time
    int (*callback)(void);      // execution callback
} MTS_ITASK;

typedef struct MTS_TASK
{
    signed char state;           // See TaskState enum
    signed char task_queue;      // Queue of pending tasks
    signed char next_task;       // Next pending task to receive
    signed char src;             // Task to wait on
    MTS_ITASK  *intr;            // Interrupt/vblank task
    union {
        int (*callback)(void);   // used when starting a new task
        unsigned char *message;  // used when sending or receiving
    } u;
    signed char wake_count;      // Pending wake up count to keep task active
    signed char next_sem;        // Next task in the semaphore wait queue
    char        overrun;         // Count of interrupts sent to a task not receiving interrupts
    signed char pending;         // Source/destination of a queued message
    void       *stack_top;
    int         stack_size;
    int         tid;             // Thread ID
    struct TCB *tcb;             // Thread Control Block pointer
} MTS_TASK;

#define MTS_STACK_COOKIE 0x12435687

/*---------------------------------------------------------------------------*/

/* mts_new.c */
void mts_lock_sio( void );
void mts_unlock_sio( void );
//void mts_SioTaskEntrypoint( void );
void mts_task_start(void);

/* mask.c */
extern void SetExMask();
extern void *mts_get_bss_tail(void);

/*---------------------------------------------------------------------------*/

// "mts_new.c" should really be __FILE__ but we get the full path using the
// decomp's build system. mts.lib was originally built using a local Makefile.

#if __STDC_VERSION__ >= 199901L // C99
#define mts_assert( cond, line, ... )                               \
        if ( !( cond ) )                                            \
        {                                                           \
            printf( "assertion faled : %s line %d : Task %d\n",     \
                    "mts_new.c", line, mts_active_task_800C0DB0 );  \
            printf( __VA_ARGS__ );                                  \
            printf( "\n" );                                         \
            mts_print_process_status();                             \
        }
#else
#define mts_assert( cond, line, args... )                           \
        if ( !( cond ) )                                            \
        {                                                           \
            printf( "assertion faled : %s line %d : Task %d\n",     \
                    "mts_new.c", line, mts_active_task_800C0DB0 );  \
            printf( ##args );                                       \
            printf( "\n" );                                         \
            mts_print_process_status();                             \
        }
#endif

//-----------------------------------------------------------------------------
//  Build Date      Build Time      Product Code    Version
//-----------------------------------------------------------------------------
//  "Mar 17 1998"   "20:53:30"      SLPM-80254      METAL GEAR SOLID PILOT DISC
//   〃  〃  〃      〃 〃 〃       SLPM-80256      METAL GEAR SOLID PILOT DISC
//  "Jun 13 1998"   "15:05:16"      SLPM-86098      METAL GEAR SOLID 体験版
//   〃  〃  〃      〃 〃 〃       PAPX-90044      METAL GEAR SOLID PILOT DISC
//  "Jun 13 1998"   "15:04:42"      SLUS-90035      METAL GEAR SOLID DEMO (ver.1)
//   〃  〃  〃      〃 〃 〃       SLED-01400      METAL GEAR SOLID DEMO (ver.1)
//  "Jul 11 1998"   "22:16:33"      SLPM-86111      METAL GEAR SOLID (NTSC-J)
//   〃  〃  〃      〃 〃 〃       SLUS-00594      METAL GEAR SOLID (NTSC-U)
//   〃  〃  〃      〃 〃 〃       SLES-01370      METAL GEAR SOLID (PAL, English)
//   〃  〃  〃      〃 〃 〃       SLES-01507      METAL GEAR SOLID (PAL, German)
//   〃  〃  〃      〃 〃 〃       SLES-01506      METAL GEAR SOLID (PAL, French)
//   〃  〃  〃      〃 〃 〃       SLPM-86247      METAL GEAR SOLID INTEGRAL
//   〃  〃  〃      〃 〃 〃       SLPM-86249      METAL GEAR SOLID INTEGRAL VR-DISC
//  "Aug 28 1998"   "16:35:40"      SCUS-XXXXX      METAL GEAR SOLID DEMO (ver.2)
//  "Nov 12 1998"   "18:51:44"      SLED-01775      METAL GEAR SOLID DEMO (ver.2)
//  "Nov 12 1998"   "20:00:47"      SLES-01508      METAL GEAR SOLID (PAL, Italian)
//   〃  〃  〃      〃 〃 〃       SLES-01734      METAL GEAR SOLID (PAL, Spanish)
//   〃  〃  〃      〃 〃 〃       SLUS-00957      METAL GEAR SOLID VR MISSIONS
//   〃  〃  〃      〃 〃 〃       SLES-02136      METAL GEAR SOLID SPECIAL MISSIONS
//  "Jun 11 1999"   "10:13:47"      SLUS-90062      METAL GEAR SOLID VR MISSIONS DEMO
//  "Jun 24 1999"   "13:17:49"      SCED-XXXXX      METAL GEAR SOLID SPECIAL MISSIONS DEMO
//  "Aug 21 2007"   "21:28:42"      (none)          MGS1 (for METAL GEAR SOLID 4)
//
// Note that the Jun 13 1998 timestamps are less than one minute apart.
// Were these different configs built in the same batch?
// Same for the Nov 12 1998 builds, though the hour gap raises more questions...
//

#ifdef DEV_EXE
#define MTS_BUILD_DATE  __DATE__
#define MTS_BUILD_TIME  __TIME__
#else
#define MTS_BUILD_DATE  "Jul 11 1998"
#define MTS_BUILD_TIME  "22:16:33"
#endif

#endif // _MTS_NEW_H
