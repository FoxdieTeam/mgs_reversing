#include <sys/types.h>
#include <libcd.h>
#include <libgte.h>
#include <libgpu.h>
#include "common.h"
#include "psyq.h"

#include "mts/mts.h"
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

/*---------------------------------------------------------------------------*/

CHARA MainCharacterEntries[] = {
    { CHARA_SNAKE, sna_NewSnake_8005B650 }, // GV_StrCode("スネーク")
    { CHARA_ITEM, NewItem_800344F8 },       // GV_StrCode("アイテム")
    { CHARA_DOOR, NewDoor_8006FD00 },       // GV_StrCode("ドア")
    { 0, NULL }
};

#ifdef VR_EXE
const char *MGS_DiskName[] = {"SLPM_862.49", NULL};
#else
const char *MGS_DiskName[] = {"SLPM_862.47", "SLPM_862.48", NULL};
#endif
const char *MGS_MemoryCardName = "BISLPM-86247";

/*---------------------------------------------------------------------------*/

static char SdStack[2048];

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
    HZD_StartDaemon_80021900();

    printf("sound:");
    mts_start_task(MTSID_SOUND_MAIN, SdMain, STACK_BOTTOM(SdStack), sizeof(SdStack));

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

/*---------------------------------------------------------------------------*/

static inline void START_GAME( void (*proc)(void) )
{
    static char GameStack[2048];

    mts_boot_task( MTSID_GAME, proc, STACK_BOTTOM(GameStack), sizeof(GameStack) );
}

int main()
{
    START_GAME( Main );
}
