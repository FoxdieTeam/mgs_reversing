#include <stdio.h>
#include <sys/types.h>
#include <libcd.h>
#include <libgte.h>
#include <libgpu.h>
#include "common.h"

#include "mts/mts.h"
#include "mts/taskid.h"
#include "SD/sd_cli.h"

#include "libgv/libgv.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "memcard/memcard.h"

#include "strcode.h"
#include "Game/game.h"
#include "Game/item.h"
#include "chara/snake/sna_init.h"
#include "Thing/door.h"

unsigned int _ramsize = 0x200000; //  2MB ram size
unsigned int _stacksize = 0x8000; // 32KB stack size

CHARA MainCharacterEntries[] = {
    { CHARA_SNAKE, NewSnake },  // GV_StrCode("スネーク")
    { CHARA_ITEM, NewItem },    // GV_StrCode("アイテム")
    { CHARA_DOOR, NewDoor },    // GV_StrCode("ドア")
    { 0, NULL }
};

#ifdef VR_EXE
const char *MGS_DiskName[] = {"SLPM_862.49", NULL};
#else
const char *MGS_DiskName[] = {"SLPM_862.47", "SLPM_862.48", NULL};
#endif
const char *MGS_MemoryCardName = "BISLPM-86247";

//static long GameStack_800ABBF0[512];
//static long SdStack_800AC3F0[512];

#define GAME_STACK_SIZE (2048)
#define SD_STACK_SIZE   (2048)

extern char GameStack_800ABBF0[GAME_STACK_SIZE];
extern char SdStack_800AC3F0[SD_STACK_SIZE];

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
    mts_start_task(MTSID_SOUND_MAIN, SdMain, STACK_BOTTOM(SdStack_800AC3F0), SD_STACK_SIZE);

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

    mts_boot_task( MTSID_GAME, proc, STACK_BOTTOM(GameStack_800ABBF0), GAME_STACK_SIZE );
}

int main()
{
    START_GAME( Main );
}
