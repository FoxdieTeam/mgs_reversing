#include "linker.h"
#include "gcl.h"
#include "Script_tbl_map_8002BB44.h"

extern GameState_800B4D98 gGcl_gameStateVars_800B44C8;

GCL_Vars SECTION(".gGcl_memVars_800b4588") gGcl_memVars_800b4588;

unsigned char *GCL_VarSaveBuffer_800217F0(unsigned char *pScript)
{
    int   gcl_var, gcl_code, value;
    char *ptr;
    char  bitFlag;

    GCL_GetVar_80021634(pScript, &gcl_code, &value);
    gcl_var = GCL_GetLong(pScript);
    gcl_code = GCL_GetVarTypeCode(gcl_var);
    if (GCL_IsGameStateVar(gcl_var))
    {
        ptr = (char *)&gGcl_gameStateVars_800B44C8;
    }
    else
    {
        ptr = (char *)&gGcl_memVars_800b4588;
    }
    ptr += GCL_GetVarOffset(gcl_var);
    switch (gcl_code)
    {
    case GCLCODE_SHORT:         // $w:
    case GCLCODE_HASHED_STRING: // $s:
    case GCLCODE_PROC_CALL:
        *(short *)ptr = (short)value;
        break;

    case GCLCODE_BYTE: // $b:
    case GCLCODE_CHAR:
        *ptr = (char)value;
        break;

    case GCLCODE_BOOL: // $f:
        bitFlag = GCL_GetBoolVarBitFlag(gcl_var);
        if (value)
        {
            *ptr |= bitFlag;
        }
        else
        {
            *ptr &= ~bitFlag;
        }

    case 5:
    case GCLCODE_STRING:
    default:
        break;
    }
    return pScript + sizeof(gcl_var);
}
