#include "linker.h"
#include "libgcl/gcl.h"
#include "mts/mts_new.h"

extern char         aGcawi[5];
extern const char   aSystemCChangeP[];

extern char          *GM_StageName_800AB918;
char SECTION(".sbss") *GM_StageName_800AB918;

char*        GCL_Read_String_80020A70(unsigned char *pScript);
void         GM_SetSystemCallbackProc_8002B558(int index, int proc);

int GCL_Command_system_8002C7C8(void)
{
    int i, proc;

    for (i = 0; i <= (int)sizeof(aGcawi); i++)
    {
        if (GCL_GetParam_80020968(aGcawi[i]))
        {
            proc = GCL_GetNextParamValue_80020AD4();
            if (!proc)
            {
                mts_printf_8008BBA0(aSystemCChangeP, aGcawi[i]);
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
