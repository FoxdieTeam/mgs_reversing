#include "linker.h"
#include "mts/mts_new.h"
#include "game.h"
#include "libgv/libgv.h"
#include "libdg/dgd.h"
#include "Menu/menuman.h"
#include "unknown.h"
#include "psyq.h"

extern GameState gGameState_800B4D98;

extern unsigned char *GV_ResidentMemoryBottom_800AB940;

extern unsigned char *gOverlayBase_800AB9C8;

extern const char aTooLargeStageB[];
extern const char aGamedC[];

extern int gOverlayBinSize_800B5290;

// forcec gp
extern int GM_GameOverTimer_800AB3D4;
int        SECTION(".sdata") GM_GameOverTimer_800AB3D4;

// force GP
extern int GM_LoadRequest_800AB3D0;
int        SECTION(".sdata") GM_LoadRequest_800AB3D0;

// force gp
extern int gTotalFrameTime_800AB9E8;
int        SECTION(".sbss") gTotalFrameTime_800AB9E8;

extern int GM_LoadComplete_800ABA38;
int        SECTION(".sbss") GM_LoadComplete_800ABA38;

extern GV_PAD *GM_CurrentPadData_800AB91C;
GV_PAD        *SECTION(".sbss") GM_CurrentPadData_800AB91C; // sbss

extern Actor_GM_Daemon GM_Daemon_800B5880;

extern int gDiskNum_800ACBF0;

extern GV_PAD GV_PadData_800B05C0[4];

int GM_bin_overlay_file_handler_8002B710(unsigned char *pFileData, int fileNameHashed)
{
    if ((gOverlayBase_800AB9C8 + gOverlayBinSize_800B5290) > GV_ResidentMemoryBottom_800AB940)
    {
        mts_printf_8008BBA0(aTooLargeStageB);
    }

    memcpy_8008E648(gOverlayBase_800AB9C8, pFileData, gOverlayBinSize_800B5290);

    return 1;
}

void GM_StartDaemon_8002B77C()
{
    gTotalFrameTime_800AB9E8 = 0;
    GM_GameOverTimer_800AB3D4 = 0;
    GM_LoadRequest_800AB3D0 = 0;
    GM_LoadComplete_800ABA38 = 0;
    menu_StartDeamon_80038A20();
    GM_InitArea_8002A704();
    GM_InitChara_8002A890();
    GM_InitScript_8002D1DC();
    GV_SetLoader_80015418('b', GM_bin_overlay_file_handler_8002B710);
    GM_ClearWeaponAndItem_8002A960();
    GV_InitActor_800150A8(1, &GM_Daemon_800B5880.field_0, 0);
    GV_SetNamedActor_8001514C(&GM_Daemon_800B5880.field_0, (TActorFunction)GM_Act_8002ADBC, 0, aGamedC);
    sub_8002AA48();
    GM_Reset_8002ABF4(&GM_Daemon_800B5880);
    GM_ResetMemory_8002AA80();
    GM_CurrentPadData_800AB91C = &GV_PadData_800B05C0[0];
    gGameState_800B4D98.field_08_cd_number = gDiskNum_800ACBF0 + 1;
    GV_SaveResidentTop_800163C4();
    GM_Daemon_800B5880.field_20 = 0;
    GM_Daemon_800B5880.field_24 = 0;
    GM_CreateLoader_8002AAB0();
}
