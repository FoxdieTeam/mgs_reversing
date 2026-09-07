#include <stdio.h>
#include <sys/types.h>
#include <libcd.h>
#include <libgte.h>
#include <libgpu.h>
#include "mgstype.h"

#include "mts/mts.h"
#include "mts/taskid.h"
#include "sound/sd_cli.h"

#include "libgv/libgv.h"
#include "libfs/libfs.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "memcard/memcard.h"
#include "game/game.h"

unsigned int _ramsize = 0x200000; //  2MB RAM size
unsigned int _stacksize = 0x8000; // 32KB stack size

/*--------------------------------------------------------------------------*/

#define DECLARE_NEWCHARA_PROTOS
#include "charalst.h"

CHARA MainCharacterEntries[] = {
    CHARA_SNAKE,        /* chara スネーク */
    CHARA_ITEM,         /* chara アイテム */
    CHARA_DOOR,         /* chara ドア */
    CHARA_END
};

#include "sonycode.h"

const char *MGS_DiskName[] = {
#ifdef DISC1_SONY_CODE
    DISC1_SONY_CODE,
#endif
#ifdef DISC2_SONY_CODE
    DISC2_SONY_CODE,
#endif
    NULL
};
const char *MGS_MemoryCardName = {
#ifdef PAL
    "BE" SONY_CODE  // SCEE
#else
#ifdef ENGLISH
    "BA" SONY_CODE  // SCEA
#else
    "BI" SONY_CODE  // SCEI
#endif
#endif // PAL
};

/*--------------------------------------------------------------------------*/

#define GAME_STACK_SIZE (2048)
#define SD_STACK_SIZE   (2048)

static char SECTION(".bss") GameStack[ GAME_STACK_SIZE ];
static char SECTION(".bss") SdStack[ SD_STACK_SIZE ];

static void Main( void )
{
    RECT rect;

    ResetGraph(0);
    SetGraphDebug(0);
    CdInit();
    SetDispMask(0);

    setRECT( &rect, 0, 0, 1024, 511 );
    ClearImage( &rect, 0, 0, 0 );

    DrawSync( 0 );
    SetDispMask( 1 );
    InitGeom();

    mts_init_vsync();
    mts_set_vsync_task();

    printf( "mem:" );
    memcard_init();

    printf( "pad:" );
    mts_init_controller();

    printf( "gv:" );
    GV_StartDaemon();

    printf( "fs:" );
    FS_StartDaemon();

    printf( "dg:" );
    DG_StartDaemon();

    printf( "gcl:" );
    GCL_StartDaemon();

    printf( "hzd:" );
    HZD_StartDaemon();

    printf( "sound:" );
    mts_start_task( MTSID_SOUND_MAIN, SdMain, STACK_BOTTOM( SdStack ), SD_STACK_SIZE );

    while ( !sd_task_active() )
    {
        mts_wait_vbl( 1 );
    }

    printf( "gm:" );
    GM_StartDaemon();

    printf( "start\n" );

    for ( ;; )
    {
        GV_ExecActorSystem();
    }
}

static inline void START_GAME( void (*proc)(void) )
{
    // the game task stack was originally declared static here
    // ...or at least it is in 5thMix's work.5th/main/bm.c

    mts_boot_task( MTSID_GAME, proc, STACK_BOTTOM( GameStack ), GAME_STACK_SIZE );
}

int main()
{
    START_GAME( Main );
}
