#include "linker.h"
#include "gcl.h"

GCL_CommandChain*  SECTION(".sdata") dword_800AB3B8 = 0;

void sub_80020B68(void);
void sub_80021264(void);
void sub_8002040C(void);
void sub_8001FC88(unsigned char*); // TODO: Prob wrong
void sub_8001FCB0(int);

void GD_SetFileHandler_80015418(char, void*);

void GCL_StartDaemon_8001FCDC(void)
{
    sub_80020B68();
    sub_80021264();
    sub_8002040C();
    GD_SetFileHandler_80015418('g', sub_8001FC88);
    sub_8001FCB0(0);
}

void GLC_Null_8001FD24(void)
{

}

int GCL_InitCommandTable_8001FD2C(GCL_CommandChain* pChain)
{
    // Set the new chains next to the existing chain
    pChain->pNext = dword_800AB3B8;

    // Update the existing chain to be the new chain
    dword_800AB3B8 = pChain;
    
    return 0;
}

extern void mg_printf_8008BBA0(const char*, ...);

extern const char aCommandNotFoun[];

GCL_CommandTableEntry* GCL_FindCommand_8001FD40(int hashedName)
{
    GCL_CommandTableEntry* pTableIter;
    int commandCount;
    GCL_CommandChain* pChainIter;
  
    pChainIter = dword_800AB3B8;
    if (pChainIter)
    {
        do
        {
            commandCount = pChainIter->commandTableSize;
            pTableIter = pChainIter->pTable;
            while (0 < commandCount)
            {
                commandCount--;
                if (pTableIter->hashCode == hashedName)
                {
                    return pTableIter;
                }
                pTableIter++;
            }
            pChainIter = pChainIter->pNext;
        } while (pChainIter);
    }
    mg_printf_8008BBA0(aCommandNotFoun);
    return 0;
}
