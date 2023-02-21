#include "libgcl/libgcl.h"

unsigned int GCL_Command_menu_helper_8002CA48(void)
{
    unsigned int ret = 0;
    int next;
    
    while (GCL_Get_Param_Result_80020AA4())
    {
        next = GCL_GetNextParamValue_80020AD4();

        if (next > 32)
        {
            return 0;
        }

        ret |= 1 << next;
    }

    return ret;
}
