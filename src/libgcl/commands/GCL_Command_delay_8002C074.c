#include "linker.h"
#include "Script_tbl_map_8002BB44.h"
#include "gcl.h"
#include "delay.h"

int GCL_Command_delay_8002C074(void)
{
    int time = 0;
    int proc = 0;

    if (GCL_GetParam_80020968('t')) // time
    {
        time = GCL_GetNextParamValue_80020AD4();
    }
    if (GCL_GetParam_80020968('p')) // proc
    {
        proc = GCL_GetNextParamValue_80020AD4();
    }
    if (GCL_GetParam_80020968('e')) // exec
    {
        int code;
        int value;
        GCL_Execute_8002069C(GCL_Get_Param_Result_80020AA4(), &code, &value);
        proc = value;
    }
    if (GCL_GetParam_80020968('g'))
    {
        time = -time;
    }
    if (time && proc)
    {
        delay_init_80033230(proc, 0, time);
        return 0;
    }
    return -1;
}
