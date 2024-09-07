#include <sys/types.h>
#include <libcd.h>
#include <libgte.h>
#include <libgpu.h>
#include "linker.h"
#include "psyq.h"

#include "mts/mts_new.h"
#include "mts/taskid.h"
#include "SD/sound.h"

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

unsigned int _ramsize = 0x200000; // ram size
unsigned int _stacksize = 0x8000; // stack size

CHARA MainCharacterEntries_8009D2DC[] = {
    {CHARA_SNAKE, sna_NewSnake_8005B650},
    {CHARA_ITEM, item_init_800344F8},
    {CHARA_DOOR, NewDoor_8006FD00},
    {0, 0}
};

#ifdef VR_EXE
const char *MGS_DiskName_8009D2FC[] = {"SLPM_862.49", NULL};
#else
const char *MGS_DiskName_8009D2FC[] = {"SLPM_862.47", "SLPM_862.48", NULL};
#endif
const char *MGS_MemoryCardName_800AB2EC = "BISLPM-86247";

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

    mts_init_vsync_800895AC();
    mts_set_vsync_task_800892B8();

    printf("mem:");
    memcard_init();

    printf("pad:");
    mts_init_controller_8008C098();

    printf("gv:");
    GV_StartDaemon();

    printf("fs:");
    FS_StartDaemon();

    printf("dg:");
    DG_StartDaemon();

    printf("gcl:");
    GCL_StartDaemon();

    printf("hzd:");
    HZD_StartDaemon_80021900();

    printf("sound:");
    mts_start_task(MTSID_SOUND_MAIN, SdMain, STACK_BOTTOM(SdStack_800AC3F0), SD_STACK_SIZE);

    while (!sd_task_active())
    {
        mts_wait_vbl_800895F4(1);
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
    mts_boot_task_8008AAC4( MTSID_GAME, proc, STACK_BOTTOM(GameStack_800ABBF0), GAME_STACK_SIZE );
}

int main()
{
    START_GAME( Main );
}
