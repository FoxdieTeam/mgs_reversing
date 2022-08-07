#include "linker.h"
#include "Script_tbl_map_8002BB44.h"
#include "gcl.h"

GCL_Vars SECTION(".gGcl_vars_800B3CC8") gGcl_vars_800B3CC8;

extern GameState_800B4D98 gGameState_800B4D98;

// This function takes a gcl variable and return the C variable associated
//
// gcl_variable example: 0x11800002 (difficulty_level)
//     1 = type variable
//     1 = type short
//    80 = gameState struct
//  0002 = offset in gameState struct

unsigned char *GCL_GetVar_80021634(unsigned char *pScript, int *retCode, int *retValue)
{
    int   gcl_var;
    int   gcl_code;
    char *ptr;

    gcl_var = GCL_GetLong(pScript);
    gcl_code = GCL_GetVarTypeCode(gcl_var);
    *retCode = gcl_code;
    if (GCL_IsGameStateVar(gcl_var))
    {
        ptr = (char *)&gGameState_800B4D98;
    }
    else
    {
        ptr = (char *)&gGcl_vars_800B3CC8;
    }
    ptr += GCL_GetVarOffset(gcl_var);
    switch (gcl_code)
    {
    case GCLCODE_SHORT:         // $w:
    case GCLCODE_HASHED_STRING: // $s:
    case GCLCODE_PROC_CALL:
        if (gcl_code == GCLCODE_SHORT)
        {
            *retValue = *((short *)ptr);
        }
        else
        {
            *retValue = *((unsigned short *)ptr);
        }
        break;

    case GCLCODE_BYTE: // $b:
    case GCLCODE_CHAR:
        *retValue = (unsigned char)*ptr;
        break;

    case GCLCODE_BOOL: // $f:
        *retValue = (*ptr & GCL_GetBoolVarBitFlag(gcl_var)) != 0;
        break;

    default:
        break;
    }
    return pScript + sizeof(gcl_var);
}
