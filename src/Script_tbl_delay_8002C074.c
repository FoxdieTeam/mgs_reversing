#include "linker.h"
#include "delay.h"
#include "gcl.h"

int Script_tbl_delay_8002C074(void)
{
    int script_pVar;
    int script_tVar;
    int auStack24;
    int local_14;

    script_tVar = 0;
    script_pVar = 0;

    if (GCL_GetParam_80020968('t'))
    {
        script_tVar = GCL_Get_Param_80020AD4();
    }

    if (GCL_GetParam_80020968('p'))
    {
        script_pVar = GCL_Get_Param_80020AD4();
    }

    if (GCL_GetParam_80020968('e'))
    {
        GCL_Execute_8002069C(GCL_Get_Param_Result_80020AA4(), &auStack24, &local_14);
        script_pVar = local_14;
    }

    if (GCL_GetParam_80020968('g'))
    {
        script_tVar = -script_tVar;
    }

    if (script_tVar && script_pVar)
    {
        delay_init_80033230(script_pVar, 0, script_tVar);
        return 0;
    }
    return -1;
}
