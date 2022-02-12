#include <util/idaTypes.h>
#include "gcl.h"

DWORD GCL_Command_eval_80020318(BYTE* cmd)
{
    DWORD code;
    DWORD value;

    GCL_GetNextValue_8002069C(cmd, &code, &value);
    return 0;
}
