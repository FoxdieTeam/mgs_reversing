#include <stdio.h>
#include <sys/types.h>
#include <libcd.h>
#include <libgte.h>
#include <libgpu.h>
#include "common.h"

#include "mts/mts.h"
#include "mts/taskid.h"
#include "sd/sd_cli.h"

#include "libgv/libgv.h"
#include "libfs/libfs.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "memcard/memcard.h"
#include "game/game.h"

#include "strcode.h"
#include "charalst.h"

unsigned int _ramsize = 0x200000; //  2MB ram size
unsigned int _stacksize = 0x8000; // 32KB stack size

CHARA MainCharacterEntries[] = {
    CHARA_SNAKE,        /* chara スネーク */
    CHARA_ITEM,         /* chara アイテム */
    CHARA_DOOR,         /* chara ドア */
    CHARA_END
};

const char *MGS_DiskName[] = {
#ifdef INTEGRAL
#ifdef VR_EXE
    "SLPM_862.49",      // 0: VR-DISC
#else
    "SLPM_862.47",      // 0: DISC 1
    "SLPM_862.48",      // 1: DISC 2
#endif
#endif
    NULL                // end-of-list
};
const char *MGS_MemoryCardName = {
#ifdef INTEGRAL
    "BISLPM-86247"
#endif
};

//static long GameStack[512];
//static long SdStack[512];

#define GAME_STACK_SIZE (2048)
#define SD_STACK_SIZE   (2048)

extern char GameStack[GAME_STACK_SIZE];
extern char SdStack[SD_STACK_SIZE];

static void Main(void)
{
    RECT rect;

    ResetGraph(0);
    SetGraphDebug(0);
    CdInit();
    SetDispMask(0);

    setRECT(&rect, 0, 0, 1024, 511);
    ClearImage(&rect, 0, 0, 0);

    DrawSync(0);
    SetDispMask(1);
    InitGeom();

    mts_init_vsync();
    mts_set_vsync_task();

    printf("mem:");
    memcard_init();

    printf("pad:");
    mts_init_controller();

    printf("gv:");
    GV_StartDaemon();

    printf("fs:");
    FS_StartDaemon();

    printf("dg:");
    DG_StartDaemon();

    printf("gcl:");
    GCL_StartDaemon();

    printf("hzd:");
    HZD_StartDaemon();

    printf("sound:");
    mts_start_task(MTSID_SOUND_MAIN, SdMain, STACK_BOTTOM(SdStack), SD_STACK_SIZE);

    while (!sd_task_active())
    {
        mts_wait_vbl(1);
    }

    printf("gm:");
    GM_StartDaemon();

    printf("start\n");

    for (;;)
    {
        GV_ExecActorSystem();
    }
}

static inline void START_GAME( void (*proc)(void) )
{
    // the game task stack was originally declared static here
    // ...or at least it is in 5thMix's work.5th/main/bm.c

    mts_boot_task( MTSID_GAME, proc, STACK_BOTTOM(GameStack), GAME_STACK_SIZE );
}

int main()
{
    START_GAME( Main );
}
