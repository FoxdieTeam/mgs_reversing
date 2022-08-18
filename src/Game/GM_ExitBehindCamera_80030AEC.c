#include "linker.h"

extern int GM_event_camera_flag_800ABA9C;
int SECTION(".sbss") GM_event_camera_flag_800ABA9C;

extern int GM_CameraTrackOrg_800AB444;
int SECTION(".sdata") GM_CameraTrackOrg_800AB444;

extern int GM_CameraTrackOrg_800AB448;
int SECTION(".sdata") GM_CameraTrackOrg_800AB448;

extern int dword_800ABA90;
int SECTION(".sbss") dword_800ABA90;

extern int GM_GameStatus_800AB3CC;

void GM_ExitBehindCamera_80030AEC(void)
{
    if ((GM_GameStatus_800AB3CC & 0x10) != 0)
    {
        GM_GameStatus_800AB3CC &= ~0x10;
        GM_event_camera_flag_800ABA9C &= ~8;
        dword_800ABA90 = dword_800ABA90 | 8;
    }

    GM_CameraTrackOrg_800AB448 = 0;
    GM_CameraTrackOrg_800AB444 = 0;
}
