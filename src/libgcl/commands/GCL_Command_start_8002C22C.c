#include "linker.h"
#include "libgcl/gcl.h"
#include "mts/mts_new.h"
#include "Font/font.h"
#include "Game/game.h"

extern int gBinds_800ABA60;
int        SECTION(".sbss") gBinds_800ABA60;

extern const char aMenuInitEnd[];

extern int gTotalFrameTime_800AB9E8;

int GCL_Command_start_8002C22C(int argc, char **argv)
{
    if (GCL_GetParam_80020968('s'))
    {
        GM_InitReadError_8002AC44();
    }

    if (GCL_GetParam_80020968('m')) // menu
    {
        menuman_init_80038954();
        mts_printf_8008BBA0(aMenuInitEnd);
    }

    if (GCL_GetParam_80020968('f')) // font
    {
        font_load_80044A9C();
    }

    if (GCL_GetParam_80020968('v'))
    {
        GCL_InitVar_80021264();
        menu_InitRadioMemory_8004E0EC();
        gTotalFrameTime_800AB9E8 = 0;
    }

    if (GCL_GetParam_80020968('d')) // demo (1 to use demo.gcx instead of scenerio.gcx)
    {
        GCL_ChangeSenerioCode_8001FCB0(GCL_GetNextParamValue_80020AD4());
    }

    if (GCL_GetParam_80020968('c'))
    {
        GCL_InitClearVar_800212CC();
        menu_InitRadioMemory_8004E0EC();
        gTotalFrameTime_800AB9E8 = 0;
    }
    return 0;
}
