#include "linker.h"
#include "gcl.h"

GCL_CommandChain*  SECTION(".sdata") dword_800AB3B8 = 0;

void sub_80020B68(void);
void sub_80021264(void);
void GCL_AddBasicBuiltInCommands_8002040C(void);
void GCL_FileHandler_8001FC88(unsigned char*); // TODO: Prob wrong

void GD_SetFileHandler_80015418(char, void*);


int SECTION(".sbss") gGcl_main_or_demo_800AB990;

int SECTION(".sbss") dword_800AB9948;

int SECTION(".sbss") dword_800AB998;



void GCL_SetMainOrDemo_8001FCB0(int bMain)
{
    gGcl_main_or_demo_800AB990 = (bMain == 1) ? 0x6A242 : 0x6EA54;
}

void GCL_StartDaemon_8001FCDC(void)
{
    sub_80020B68();
    sub_80021264();
    GCL_AddBasicBuiltInCommands_8002040C();
    GD_SetFileHandler_80015418('g', GCL_FileHandler_8001FC88);
    GCL_SetMainOrDemo_8001FCB0(0);
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
  
    for (pChainIter = dword_800AB3B8 ; pChainIter ; pChainIter = pChainIter->pNext)
    {
        pTableIter = pChainIter->pTable;
        for (commandCount = pChainIter->commandTableSize; 0 < commandCount; commandCount--)
        {
            if (pTableIter->hashCode == hashedName)
            {
                return pTableIter;
            }
            pTableIter++;
        }
    }
    mg_printf_8008BBA0(aCommandNotFoun);
    return 0;
}

void GCL_Push_80020934(unsigned char*);
void sub_80020690(unsigned char*);
void GCL_Pop_80020950(void);

#define GCL_ReadShort(p) ( p[1] ) | ( p[0] << 8 )
#define GCL_AdvanceShort(p) p += sizeof(short)

#define GCL_ReadByte(p) p[0]
#define GCL_AdvanceByte(p) p += sizeof(unsigned char)

int GCL_8001FDB0(unsigned char* pScript)
{
    int commandRet;

    GCL_CommandTableEntry* pFoundCommand = GCL_FindCommand_8001FD40(GCL_ReadShort(pScript));
    GCL_AdvanceShort(pScript);
    
    GCL_Push_80020934(pScript + GCL_ReadByte(pScript));
    GCL_AdvanceByte(pScript);

    sub_80020690(pScript); // save command return address?

    commandRet = pFoundCommand->function(pScript);

    GCL_Pop_80020950();

    return commandRet;
}
