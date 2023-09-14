#include "linker.h"
#include "libgcl/libgcl.h"
#include "mts/mts_new.h"

int GCL_Command_varsave_8002C72C(unsigned char *pScript)
{
    unsigned char *param;

    param = GCL_Get_Param_Result_80020AA4();
    if (GCL_GetParam_80020968('a'))
    {
        GCL_SaveVar_80021314();
        return 0;
    }
    while (*param)
    {
        if (!GCL_IsVariable(*param))
        {
            printf("VARSAVE: NOT VAR !!\n");
        }
        param = GCL_VarSaveBuffer_800217F0(param);
    }
    return 0;
}
