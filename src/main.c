#include <SYS/TYPES.H>
#include <LIBCD.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "linker.h"
#include "libgv/libgv.h"
#include "mts/mts_new.h"
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

void __main_80098F14(void);

int __ramsize_800AB2E4 = 0x200000; // ram size, sdata
int __stacksize_800AB2E8 = 0x8000; // stack size, sdata

GCL_ActorTableEntry MainCharacterEntries_8009D2DC[] = {
    {CHARA_SNAKE, sna_NewSnake_8005B650},
    {CHARA_ITEM, item_init_800344F8},
    {CHARA_DOOR, NewDoor_8006FD00},
    {0, 0}};

const char *MGS_DiskName_8009D2FC[] = {"SLPM_862.47", "SLPM_862.48", NULL};
const char *MGS_MemoryCardName_800AB2EC = "BISLPM-86247"; // sdata

extern unsigned int sdStack_800AC3F0[512];

static void task_main_800148B8(void)
{
    RECT rect;

    ResetGraph(0);
    SetGraphDebug(0);
    CdInit();
    SetDispMask_8008F7CC(0);

    setRECT(&rect, 0, 0, 1024, 511);
    ClearImage(&rect, 0, 0, 0);

    DrawSync(0);
    SetDispMask_8008F7CC(1);
    InitGeom_80092680();

    mts_init_vsync_800895AC();
    mts_set_vsync_task_800892B8();

    mts_printf_8008BBA0("mem:"); // sdata
    memcard_init_80024E48();

    mts_printf_8008BBA0("pad:"); // sdata
    mts_init_controller_8008C098();

    mts_printf_8008BBA0("gv:"); // sdata
    GV_StartDaemon_80014D18();

    mts_printf_8008BBA0("fs:"); // sdata
    FS_StartDaemon_80014A7C();

    mts_printf_8008BBA0("dg:"); // sdata
    DG_StartDaemon_8001F284();

    mts_printf_8008BBA0("gcl:"); // sdata
    GCL_StartDaemon_8001FCDC();

    mts_printf_8008BBA0("hzd:"); // sdata
    HZD_StartDaemon_80021900();

    mts_printf_8008BBA0("sound:"); // sdata

    mts_set_stack_check_8008B648(5, mts_stack_end(sdStack_800AC3F0), sizeof(sdStack_800AC3F0));
    mts_sta_tsk_8008B47C(5, SdMain_80081A18, mts_stack_end(sdStack_800AC3F0));

    while (!sd_task_active_800886C4())
    {
        mts_wait_vbl_800895F4(1);
    }

    mts_printf_8008BBA0("gm:"); // sdata
    GM_StartDaemon_8002B77C();

    mts_printf_8008BBA0("start\n"); // sdata

    for (;;)
    {
        GV_ExecActorSystem_80014F88();
    }
}

extern unsigned char main_task_stack_800ABBF0[2048];
void                 _main_80014A40()
{
    __main_80098F14();
    mts_boot_task_8008AAC4(3, task_main_800148B8, mts_stack_end(main_task_stack_800ABBF0),
                           sizeof(main_task_stack_800ABBF0));
}
