#include "linker.h"
#include "libgcl/libgcl.h"
#include "mts/mts_new.h"
#include "Game/game.h"

extern char       aGcawi[5];

extern char *GM_StageName_800AB918;
char         SECTION(".sbss") * GM_StageName_800AB918;

int GCL_Command_system_8002C7C8(unsigned char *pScript)
{
    int i, proc;

    for (i = 0; i <= (int)sizeof(aGcawi); i++)
    {
        if (GCL_GetParam_80020968(aGcawi[i]))
        {
            proc = GCL_GetNextParamValue_80020AD4();
            if (!proc)
            {
                mts_printf_8008BBA0("SYSTEM:%c:change proc name\n", aGcawi[i]);
            }
            GM_SetSystemCallbackProc_8002B558(i, proc);
        }
    }

    i = GCL_GetParam_80020968('s');
    if (i)
    {
        GM_StageName_800AB918 = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());
    }
    return 0;
}
