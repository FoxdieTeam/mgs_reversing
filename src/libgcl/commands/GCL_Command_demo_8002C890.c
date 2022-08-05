#include "linker.h"
#include "libgcl/gcl.h"
#include "mts/mts_new.h"

extern const char   aDemoNoCode[];
extern const char   aDemoNoDataOnCd[];

extern int          GM_CurrentMap_800AB9B0;
extern int          gBinds_800ABA60;
extern int          GM_GameStatus_800AB3CC;
extern int          DG_UnDrawFrameCount_800AB380;

int SECTION(".sbss") gBinds_800ABA60;

char*           GCL_Read_String_80020A70(char *pScript);
int             NewJimakuStr_8004955C(char*, int);
int             GCL_Command_demo_helper_80037DD8(int, unsigned int);

int GCL_Command_demo_8002C890(int argc, char **argv) {
    int     param;
    int     load_data;
    char    *msg;

    if (GCL_GetParam_80020968('s') == 0)
    {
        mts_printf_8008BBA0(aDemoNoCode);
    }

    param = GCL_GetNextParamValue_80020AD4();

    if (GCL_GetParam_80020968('p') == 0)
    {
        load_data = 0;
    }
    else
    {
        load_data = GCL_GetNextParamValue_80020AD4() | GAME_FLAG_BIT_32;
    }

    GM_CurrentMap_800AB9B0 = gBinds_800ABA60;

    if (param >= 0)
    {
        DG_UnDrawFrameCount_800AB380 = 0x7FFF0000;
        GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_32;
        GCL_Command_demo_helper_80037DD8(param, load_data);
    }
    else
    {
        if (load_data < 0)
        {
            load_data &= 0xFFFF;
        }
        else
        {
            load_data = -1;
        }

        if (GCL_GetParam_80020968('f'))
        {
            msg = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());
        }
        else
        {
            msg = (char*)aDemoNoDataOnCd;
        }
        NewJimakuStr_8004955C(msg, load_data);
    }
    return 0;
}
