#include "gcl.h"
#include "Game/linkvarbuf.h"

extern GCL_Vars gGcl_vars_800B3CC8;

unsigned char *GCL_SetVar_8002171C(unsigned char *pScript, unsigned int value)
{
    int   gcl_var, gcl_code;
    char *ptr;
    char  bitFlag;

    gcl_var = GCL_GetLong(pScript);
    gcl_code = GCL_GetVarTypeCode(gcl_var);
    if (GCL_IsGameStateVar(gcl_var))
    {
        ptr = (char *)linkvarbuf;
    }
    else
    {
        ptr = (char *)&gGcl_vars_800B3CC8;
    }
    ptr += GCL_GetVarOffset(gcl_var);
    switch (gcl_code)
    {
    case GCLCODE_SHORT:
    case GCLCODE_HASHED_STRING:
    case GCLCODE_PROC_CALL:
        *(unsigned short *)ptr = value;
        break;

    case GCLCODE_BYTE:
    case GCLCODE_CHAR:
        *ptr = value;
        break;

    case GCLCODE_BOOL:
        bitFlag = GCL_GetBoolVarBitFlag(gcl_var);
        if (value)
        {
            *ptr |= bitFlag;
        }
        else
        {
            *ptr &= ~(char)bitFlag;
        }
        break;

    default:
        break;
    }
    return pScript + sizeof(gcl_var);
}
