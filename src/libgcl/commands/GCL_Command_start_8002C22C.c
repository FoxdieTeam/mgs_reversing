#include "linker.h"
#include "Script_tbl_map_8002BB44.h"
#include "gcl.h"
#include "mts_new.h"
//#include "menuMan.h"

extern int gBinds_800ABA60;
int SECTION(".sbss") gBinds_800ABA60;

extern const char aMenuInitEnd[];

void MENU_InitRadioMemory_8004E0EC(void);
void GCL_InitVars_800212CC(void);
void menu_textureload_8002AC44(void);
void font_load_80044A9C(void);
void GCL_InitVarsClear_80021264(void);

extern int dword_800AB9E8;

int GCL_Command_start_8002C22C(int argc, char **argv)
{
    if (GCL_GetParam_80020968('s'))
    {
        menu_textureload_8002AC44();
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
        GCL_InitVarsClear_80021264();
        MENU_InitRadioMemory_8004E0EC();
        dword_800AB9E8 = 0;
    }

    if (GCL_GetParam_80020968('d')) // demo (1 to use demo.gcx instead of scenerio.gcx)
    {
        GCL_SetScriptNameHash_8001FCB0(GCL_GetNextParamValue_80020AD4());
    }

    if (GCL_GetParam_80020968('c'))
    {
        GCL_InitVars_800212CC();
        MENU_InitRadioMemory_8004E0EC();
        dword_800AB9E8 = 0;
    }
    return 0;
}
