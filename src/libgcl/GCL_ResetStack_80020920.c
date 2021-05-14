#include "linker.h"
#include "gcl.h"


unsigned char** SECTION(".sbss") gGCL_stack_800AB99C;

unsigned char* SECTION(".sbss") pScript_800AB9A0;
int SECTION(".sbss") dword_800AB9A4;

int SECTION(".sbss") dword_800AB9A8[2];

unsigned char* SECTION(".bss_800B3CA8") dword_800B3CA8;

void GCL_ResetStack_80020920(void)
{
    gGCL_stack_800AB99C = &dword_800B3CA8;
}

void GCL_Push_80020934(unsigned char* pValue)
{
    unsigned char** pStackTmp = gGCL_stack_800AB99C;
    (*pStackTmp) = pValue;
    pStackTmp++;
    gGCL_stack_800AB99C = pStackTmp;
}

void GCL_Pop_80020950()
{
    gGCL_stack_800AB99C--;
}

int GCL_GetParam_80020968(char paramName)
{
    unsigned char* pScript;
    int code;
    int value;
  
    pScript = *(gGCL_stack_800AB99C - 1);
    do 
    {
        pScript = GCL_Execute_8002069C(pScript, &code, &value);
        if (code == GCLCODE_NULL)
        {
            return 0;
        }
    }
    while (!GCL_IsParam(code) || (code >> 0x10 != (paramName & 0xff)));

    pScript_800AB9A0 = (unsigned char*)value; // TODO: Union/any type return ??
    return value;
}

int GCL_GetNextValue_800209E8(unsigned char* pScript)
{
    int code;
    int value;  
    pScript_800AB9A0 = GCL_Execute_8002069C(pScript, &code, &value);
    return value;
}

int GCL_ReadVector_80020A14(unsigned char* pInScript, short* pOut3Words)
{
    int counter = 0;
    unsigned short* pOutIter = pOut3Words;
    unsigned char* pScript = pInScript;
    do
    {
        int code;
        int value;
        pScript = GCL_Execute_8002069C(pScript, &code, &value);
        counter++;
        *pOutIter = value;
        pOutIter++;
    } while (counter < 3);

    pScript_800AB9A0 = pScript;
    return 0;
}
