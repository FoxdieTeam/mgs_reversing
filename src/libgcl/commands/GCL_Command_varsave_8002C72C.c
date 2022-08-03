#include "linker.h"
#include "gcl.h"

extern const char aVarsaveNotVar[];

void     mts_printf_8008BBA0(const char*, ...);
unsigned char*  GCL_VarSaveBuffer_800217F0(unsigned char *);
void            GCL_SaveVar_80021314(void);

int GCL_Command_varsave_8002C72C(int argc, char **argv)
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
            mts_printf_8008BBA0(aVarsaveNotVar);
        }
        param = GCL_VarSaveBuffer_800217F0(param);
    }
    return 0;
}
