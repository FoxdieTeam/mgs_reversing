/*
 * ref."beatmania APPEND 5thMIX"
 *  work.5th/include/mts.h (Oct.04,1999)
 */
/* clang-format off */
#ifndef MTS_H_INCLUDED
#define MTS_H_INCLUDED

#define MTS_NR_TASK             (12)

#define MTS_NR_INT_TASK         (8)             /* use V-Sync interrupt */

#define MTS_MAX_SEMAPHORE       (32)            /* semaphore num */

#define MTS_TASK_IDLE           (MTS_NR_TASK-1) /* pre-defined idle task */
#define MTS_TASK_SYSTEM         (0)             /* pre-defined system task */
#define MTS_TASK_INTR           (-1)
#define MTS_TASK_ANY            (-2)
#define MTS_TASK_INTR_RESETED   (-3)
#define MTS_TASK_INTR2          (-4)

#define MTS_SZ_MESSAGE          (16)

#define MTS_STANDARD_STACK_SIZE (8*1024/sizeof(double))
#define MTS_STANDARD_STACK_TOP  (MTS_STANDARD_STACK_SIZE)

#define STACK_BOTTOM(name)      ((char *)name + sizeof(name))

extern void mts_boot( int tasknr, void (*procedure)(void), void *stack_pointer );
extern void mts_send( int dst, unsigned char *message );
extern int mts_isend( int dst );
extern int mts_receive( int src, unsigned char *message );

#define mts_lock()      SwEnterCriticalSection()
#define mts_unlock()    SwExitCriticalSection()

/* append by K.Uehara */

extern void mts_slp_tsk( void );
extern void mts_wup_tsk( int dst );

extern void mts_lock_sem( int no );
extern void mts_unlock_sem( int no );

extern int mts_get_current_task_id( void );
extern int mts_get_task_status( long id );

extern void mts_reset_interrupt_wait( int id );
extern void mts_reset_interrupt_overrun( void );

// #ifdef DEBUG
extern void mts_set_stack_check( long tasknr, void *stack_top, long stack_size );
extern void mts_print_process_status( void );
extern void mts_set_exception_func( void (*func)(void) );
// extern void mts_print_memmap( void );
// extern void mts_check_memmap( void );
extern void mts_get_use_stack_size( int *max, int *now, int *limit );
// #else
// #define mts_print_process_status()
// #define mts_set_stack_check(a, b, c)
// #define mts_set_exception_func(a)
// #define mts_print_memmap()
// #define mts_check_memmap()
// #define mts_get_use_stack_size()
// #endif

enum TaskState {
    MTS_TASK_DEAD       = 0,
    MTS_TASK_SENDING    = 1,
    MTS_TASK_RECEIVING  = 2,
    MTS_TASK_READY      = 3,
    MTS_TASK_SLEEPING   = 4,
    MTS_TASK_WAIT_VBL   = 5,
    MTS_PENDING         = 6,
};

/* append end */

typedef struct {
    unsigned char count;
} MTS_MESSAGE_INTR_T;

extern int mts_sta_tsk( int tasknr, void (*procedure)(void), void *stack_pointer );
extern void mts_ext_tsk( void );
extern void mts_send_msg( int dst, int data0, int data1 );
extern int mts_recv_msg( int src, int *data0, int *data1 );

//#ifdef DEBUG

#define mts_start_task( _tasknr, _procedure, _stack_pointer, _stack_size )\
{\
    mts_set_stack_check( _tasknr, _stack_pointer, _stack_size );\
    mts_sta_tsk( _tasknr, _procedure, _stack_pointer );\
}

extern void mts_boot_task( int tasknr, void (*procedure)(void), void *stack_pointer, long stack_size );

//#else
//
//#define mts_start_task( _tasknr, _procedure, _stack_pointer, _stack_size )\
//            mts_sta_tsk( _tasknr, _procedure, _stack_pointer )
//
//#define mts_boot_task( _tasknr, _procedure, _stack_pointer, _stack_size )\
//            mts_boot( _tasknr, _procedure, _stack_pointer )
//
//#endif

extern void mts_shutdown( void );

/* for PSX V-Sync Interrupt */

extern void mts_init_vsync( void );
extern void mts_set_vsync_callback_func( int (*func)(void) );
extern void mts_set_vsync_task( void );
extern int mts_wait_vbl( long count );

extern /*unsigned*/ int mts_get_tick_count( void );

/* malloc */

/*
extern void *mts_malloc( long size );
extern void mts_free( void *ptr );
extern void mts_free_all( long owner );
extern void mts_set_malloc_limit( void *limit );
extern void mts_change_memory_owner( void *ptr, long owner );

#define MTS_MALLOC_SEM_NO       0

#ifdef DEBUG
extern void mts_set_memory_fence( void *blocktop );
extern void mts_set_memory_fence_array( void *arraytop, long arraysize );
extern void mts_memory_check( char *file, long line, void *ptr );
#define MTS_SET_MEMORY_FENCE( _blocktop )\
        mts_set_memory_fence( _blocktop )
#define MTS_SET_MEMORY_FENCE_ARRAY( _blocktop, _blocksize )\
        mts_set_memory_fence_array( _blocktop, _blocksize )
#define MTS_MEMORY_CHECK( _ptr )\
        mts_memory_check( __FILE__, __LINE__, _ptr )
#else
#define MTS_SET_MEMORY_FENCE( _blocktop )
#define MTS_SET_MEMORY_FENCE_ARRAY( _blocktop, _blocksize )
#define MTS_MEMORY_CHECK( _ptr )
#endif
*/

/* Controller Service */

void mts_set_vsync_control_func( void (*func)(void) );

/*
typedef struct {
    signed char channel;
    char        button;
    signed char dx;
    signed char dy;
    long        pos_x;
    long        pos_y;
} MTS_MOUSE;
*/

typedef struct {
    signed char    channel;
    char           flag;        // See MTS_PAD_* flags
    unsigned short button;
    unsigned char  rx;
    unsigned char  ry;
    unsigned char  lx;
    unsigned char  ly;
} MTS_PAD;

#define MTS_PAD_DIGITAL 1
#define MTS_PAD_ANAJOY  2
#define MTS_PAD_ANALOG  3

void mts_init_controller( void );
//void mts_reset_mouse( MTS_MOUSE *mouse );
//long mts_get_mouse( MTS_MOUSE *mouse );
int mts_get_pad( int channel, MTS_PAD *pad );
void *mts_get_controller_data( int channel );
int mts_read_pad( int channel ); /* FIXME: should return unsigned short */
void mts_set_pad_vibration( int channel, int time );
void mts_set_pad_vibration2( int channel, int value );
int mts_get_pad_vibration_type( int channel );

void mts_reset_graph( void );

/* Stream Service */

int set_stdout_stream( int stream );
void reset_stdout_stream( void );
void set_output_stream( int stream );

#ifndef __IN_MTS_NEW__
int fprintf( int stream, const char *format, ... );
int cprintf( const char *format, ... );
#endif

#endif
/* clang-format on */
