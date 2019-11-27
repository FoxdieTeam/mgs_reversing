#include "linker.h"
#include "gcl.h"


unsigned char** SECTION(".sbss") gGCL_stack_800AB99C;

unsigned char* SECTION(".sbss") dword_800AB9A0;
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

unsigned char* sub_8002069C(unsigned char*, int*, unsigned char**);

unsigned char* sub_80020968(int uParm1)
{
    unsigned char* pScript;
    int scriptBytes;
    unsigned char* pRet;
  
    pScript = *(gGCL_stack_800AB99C-1);
    do 
    {
        pScript = sub_8002069C(pScript, &scriptBytes, &pRet);
        if (scriptBytes == 0)
        {
            return 0;
        }
    }
    while (((scriptBytes & 0xff) != 0x50) || (scriptBytes >> 0x10 != (uParm1 & 0xff)));

    dword_800AB9A0 = pRet;
    return pRet;
}

unsigned char* sub_800209E8(unsigned char* uParm1)
{
    int scriptBytes;
    unsigned char* pRet;   
    dword_800AB9A0 = sub_8002069C(uParm1, &scriptBytes, &pRet);
    return pRet;
}

int sub_80020A14(unsigned char* pInScript, unsigned short* pOut3Words)
{
    int counter = 0;
    unsigned short* pOutIter = pOut3Words;
    unsigned char* pScript = pInScript;
    do
    {
        unsigned short* pRet;
        int scriptBytes;
        pScript = sub_8002069C(pScript, &scriptBytes, &pRet);
        counter++;
        *pOutIter = pRet;
        pOutIter++;
    } while (counter < 3);

    dword_800AB9A0 = pScript;
    return 0;
}
