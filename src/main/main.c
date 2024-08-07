#include <SYS/TYPES.H>
#include <LIBCD.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "linker.h"
#include "libgv/libgv.h"
#include "mts/mts_new.h"
#include "mts/taskid.h"
#include "libgcl/libgcl.h"
#include "psyq.h"
#include "unknown.h"
#include "libfs/libfs.h"
#include "memcard/memcard.h"
#include "libhzd/libhzd.h"
#include "Game/game.h"
#include "chara/snake/sna_init.h"
#include "libgcl/hash.h"
#include "Game/item.h"
#include "Thing/door.h"
#include "SD/sound.h"

unsigned int _ramsize = 0x200000; // ram size
unsigned int _stacksize = 0x8000; // stack size

GCL_ActorTableEntry MainCharacterEntries_8009D2DC[] = {
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

#define bottom(s) ((void *)(s) + sizeof(s))

//static long Stack_800ABBF0[512];
//static long SdStack_800AC3F0[512];
extern long SdStack_800AC3F0[512];

static void Main_800148B8(void)
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
    memcard_init_80024E48();

    printf("pad:");
    mts_init_controller_8008C098();

    printf("gv:");
    GV_StartDaemon_80014D18();

    printf("fs:");
    FS_StartDaemon_80014A7C();

    printf("dg:");
    DG_StartDaemon_8001F284();

    printf("gcl:");
    GCL_StartDaemon_8001FCDC();

    printf("hzd:");
    HZD_StartDaemon_80021900();

    printf("sound:");
    mts_set_stack_check_8008B648(MTSID_SOUND_MAIN, bottom(SdStack_800AC3F0), sizeof(SdStack_800AC3F0));
    mts_sta_tsk_8008B47C(MTSID_SOUND_MAIN, SdMain_80081A18, bottom(SdStack_800AC3F0));

    while (!sd_task_active_800886C4())
    {
        mts_wait_vbl_800895F4(1);
    }

    printf("gm:");
    GM_StartDaemon_8002B77C();

    printf("start\n");

    for (;;)
    {
        GV_ExecActorSystem_80014F88();
    }
}

static inline void START_GAME( void (*proc)(void) )
{
    extern long Stack_800ABBF0[512];

    mts_boot_task_8008AAC4( MTSID_GAME, proc, bottom(Stack_800ABBF0), sizeof(Stack_800ABBF0) );
}

int main()
{
    START_GAME( Main_800148B8 );
}
