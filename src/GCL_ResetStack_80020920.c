#include "linker.h"
#include "gcl.h"


unsigned char** SECTION(".sbss") gGCL_stack_800AB99C;

int SECTION(".sbss") dword_800AB9A0[2];
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
