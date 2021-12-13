#include "linker.h"
#include "mts_new.h"
#include "gcl.h"

// $gp
extern unsigned char*   pScript_800AB9A0;
unsigned char* SECTION(".sbss") pScript_800AB9A0;

extern int              GCL_Expr_8002058C(unsigned char *pScript, void *ptr);
extern unsigned char *  GCL_GetVar_80021634(unsigned char *pScript, int *retCode, int *retValue);
extern int              GCL_GetStackPointer_80020904(int param_1);

unsigned char*  GCL_GetNextValue_8002069C(unsigned char *pScript, int *retCode, int *retValue)
{
    unsigned char   *ptr;
    int             gcl_code;
    int             size;

    ptr = pScript;
    gcl_code = *ptr;
    ptr++;
    if (GCL_IsVariable(gcl_code))
    {
        return GCL_GetVar_80021634(pScript, retCode, retValue);
    }
    *retCode = gcl_code;
    switch (gcl_code)
    {
        case GCLCODE_NULL:
            ptr = 0;
            break;

        case GCLCODE_SHORT:
            *retValue = (short)GCL_GetShort(ptr);
            ptr += 2;
            break;

        case GCLCODE_SDCODE:
        case GCLCODE_TABLE_CODE:
            *retValue = (unsigned int)GCL_GetLong(ptr);
            ptr += 4;
            break;

        case GCLCODE_HASHED_STRING:
        case GCLCODE_PROC_CALL:
            *retValue = (unsigned short)GCL_GetShort(ptr);
            ptr += 2;
            break;

        case GCLCODE_BYTE:
        case GCLCODE_CHAR:
        case GCLCODE_BOOL:
            *retValue = (unsigned char)GCL_GetByte(ptr);
            ptr += 1;
            break;

        case GCLCODE_STRING:
            *retValue = (int)(ptr + 1);
            size = *ptr;
            goto ADD_SIZE_80020834;

        case GCLCODE_STACK_VAR:
            *retValue = GCL_GetStackPointer_80020904(*ptr);
            *retCode = 1;
            ptr += 1;
            break;

        case GCLCODE_SCRIPT_DATA:
            *retValue = (int)(ptr + 2);
            size = GCL_GetShort(ptr);
            ptr += size;
            break;

        case GCLCODE_EXPRESSION:
            *retValue = GCL_Expr_8002058C(ptr + 1, retValue);
            size = *ptr;
            ptr += size;
            break;

        case GCLCODE_PARAMETER:
            *retCode |= *ptr << 16;
            *retValue = (int)(ptr + 2);
            size = ptr[1];
ADD_SIZE_80020834:
            ptr += size + 1;
            break;

        default:
            mts_printf_8008BBA0("GCL:WRONG CODE %x\n", gcl_code);
            break;
    }
    pScript_800AB9A0 = ptr;
    return ptr;
}
