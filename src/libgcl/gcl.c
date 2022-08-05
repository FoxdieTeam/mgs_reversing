#include "linker.h"
#include "gcl.h"
#include "mts/mts_new.h"
#include "Game/game.h"

GCL_COMMANDDEF *dword_800AB3B8 = 0; //sdata

void GCL_ParseInit_80020B68(void);
void GCL_InitVar_80021264(void);
void GCL_InitBasicCommands_8002040C(void);
int GCL_LoadScript_80020064(unsigned char *);

int SECTION(".sbss") gGcl_scriptNameHash_800AB990;

int SECTION(".sbss") dword_800AB994;

int GCL_InitFunc_8001FC88(unsigned char *pFileData, int hashedName)
{
    if (hashedName == gGcl_scriptNameHash_800AB990)
    {
        GCL_LoadScript_80020064(pFileData);
    }
    return 1;
}

void GCL_ChangeSenerioCode_8001FCB0(int isDemoScript)
{
    // 0x6 means hashed string
    // 0xA242 = "demo"
    // 0xEA54 = "scenerio"
    gGcl_scriptNameHash_800AB990 = (isDemoScript == 1) ? 0x6A242 : 0x6EA54;
}

void GCL_StartDaemon_8001FCDC(void)
{
    GCL_ParseInit_80020B68();
    GCL_InitVar_80021264();
    GCL_InitBasicCommands_8002040C();
    GV_SetLoader_80015418('g', GCL_InitFunc_8001FC88);
    GCL_ChangeSenerioCode_8001FCB0(0);
}

void GCL_ResetSystem_8001FD24(void)
{
}

int GCL_AddCommMulti_8001FD2C(GCL_COMMANDDEF *pChain)
{
    // Set the new chains next to the existing chain
    pChain->next = dword_800AB3B8;

    // Update the existing chain to be the new chain
    dword_800AB3B8 = pChain;

    return 0;
}

//extern const char aCommandNotFoun[];

GCL_COMMANDLIST *GCL_FindCommand_8001FD40(int hashedName)
{
    GCL_COMMANDLIST *pTableIter;
    int commandCount;
    GCL_COMMANDDEF *pChainIter;

    for (pChainIter = dword_800AB3B8; pChainIter; pChainIter = pChainIter->next)
    {
        pTableIter = pChainIter->commlist;
        for (commandCount = pChainIter->n_commlist; 0 < commandCount; commandCount--)
        {
            if (pTableIter->hashCode == hashedName)
            {
                return pTableIter;
            }
            pTableIter++;
        }
    }
    mts_printf_8008BBA0("command not found\n");
    return 0;
}

void GCL_SetCommandLine_80020934(unsigned char *);
void GCL_SetArgTop_80020690(unsigned char *);
void GCL_UnsetCommandLine_80020950(void);


int GCL_Command_8001FDB0(unsigned char *pScript)
{
    int commandRet;

    GCL_COMMANDLIST *pFoundCommand = GCL_FindCommand_8001FD40((unsigned short)GCL_GetShort(pScript));
    GCL_AdvanceShort(pScript);

    GCL_SetCommandLine_80020934(pScript + GCL_GetByte(pScript));
    GCL_AdvanceByte(pScript);

    GCL_SetArgTop_80020690(pScript); // save command return address?

    commandRet = pFoundCommand->function(pScript);

    GCL_UnsetCommandLine_80020950();

    return commandRet;
}

typedef struct
{
    unsigned short procNameHashed;
    unsigned short offset;
} GCL_ProcTableEntry;

GCL_ProcTableEntry *GCL_ByteSwap_ProcTable_8001FE28(GCL_ProcTableEntry *pTable)
{
    GCL_ProcTableEntry *pIter = pTable;
    while (*(int *)pIter)
    {
        pIter->procNameHashed = (unsigned short)GCL_GetShort((char*)&pIter->procNameHashed);
        pIter->offset = (unsigned short)GCL_GetShort((char*)&pIter->offset);
        pIter++;
    }
    return pIter + 1;
}

typedef struct
{
    GCL_ProcTableEntry *field_0_procTable;
    unsigned char *field_4_pByteCode;
    unsigned char *field_8_pMainProc;
} GCL_FileData;

GCL_FileData SECTION(".gGCL_fileData_800B3C18") gGCL_fileData_800B3C18;
//extern const char aProcXNotFound[];

unsigned char *GCL_FindProc_8001FE80(int procNameHashed)
{
    GCL_ProcTableEntry *pProcIter;
    for (pProcIter = gGCL_fileData_800B3C18.field_0_procTable; *(int *)pProcIter; pProcIter++)
    {
        if (pProcIter->procNameHashed == procNameHashed)
        {
            return gGCL_fileData_800B3C18.field_4_pByteCode + pProcIter->offset;
        }
    }
    mts_printf_8008BBA0("PROC %X NOT FOUND\n", procNameHashed);
    return 0;
}

void GCL_ForceExecProc_8001FEFC(int procNameHashed, GCL_ARGS *pArgs)
{
    GCL_ExecBlock_80020118(GCL_FindProc_8001FE80(procNameHashed) + 3, pArgs);
}

//extern const char aProcDCancel[];

extern int GM_LoadRequest_800AB3D0;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;

int GCL_ExecProc_8001FF2C(int procNameHashed, GCL_ARGS *pArgs)
{
    if (GM_LoadRequest_800AB3D0 || (GM_PlayerStatus_800ABA50 & PLAYER_STATUS_GAMEOVER))
    {
        mts_printf_8008BBA0("proc %d cancel\n", procNameHashed);
        return 0;
    }
    return GCL_ExecBlock_80020118(GCL_FindProc_8001FE80(procNameHashed) + 3, pArgs);
}

//extern const char aTooManyArgsPro[];

#define GCL_MakeShort(b1, b2) ((b1) | (b2 << 8))

int GCL_Proc_8001FFA0(unsigned char *pScript)
{
    long args[8];
    GCL_ARGS argsPtr;
    int code;
    int value;
    int arg_idx;

    int b1 = pScript[0];
    int b2 = pScript[1];

    int procId = GCL_MakeShort(b2, b1);
    GCL_AdvanceShort(pScript);

    arg_idx = 0;

    // TODO: Can't match without comma operator ??
    while (pScript = GCL_GetNextValue_8002069C(pScript, &code, &value), code != 0)
    {
        if (arg_idx >= 8)
        {
            mts_printf_8008BBA0("TOO MANY ARGS PROC\n");
        }
        args[arg_idx++] = value;
    }

    argsPtr.argc = arg_idx;
    argsPtr.argv = args;

    GCL_ExecProc_8001FF2C(procId, &argsPtr);
    return 0;
}

void font_set_font_addr_80044BC0(int arg1, void *data);

int GCL_LoadScript_80020064(unsigned char *pScript)
{
    GCL_ProcTableEntry *pTableStart;
    unsigned char *tmp;
    unsigned int len;

    pTableStart = (GCL_ProcTableEntry *)(pScript + sizeof(int));

    len = GCL_GetLong(pScript);
    gGCL_fileData_800B3C18.field_0_procTable = pTableStart;
    gGCL_fileData_800B3C18.field_4_pByteCode = (char *)GCL_ByteSwap_ProcTable_8001FE28(pTableStart);
    tmp = ((char *)gGCL_fileData_800B3C18.field_0_procTable) + len;
    gGCL_fileData_800B3C18.field_8_pMainProc = tmp + sizeof(int);

    // Points to script data end
    font_set_font_addr_80044BC0(2, gGCL_fileData_800B3C18.field_8_pMainProc + GCL_GetLong(tmp) + sizeof(int));

    return 0;
}

int *GCL_SetArgStack_8002087C(GCL_ARGS *pArgs);
void GCL_UnsetArgStack_800208F0(int *pStack);
void GCL_Expr_8002058C(unsigned char *pScript, void *ptr);

//extern const char aScriptCommandE[];
//extern const char aErrorInScript[];

int GCL_ExecBlock_80020118(unsigned char *pScript, GCL_ARGS *pArgs)
{
    int *pOldStack = GCL_SetArgStack_8002087C(pArgs);
    while (pScript)
    {
        switch (*pScript)
        {
            case GCLCODE_EXPRESSION:
            {
                int auStack24[2]; // TODO: probably an arg pair ??
                GCL_Expr_8002058C(pScript + 2, auStack24);
                pScript++;
                pScript += *pScript;
            }
            break;

            case GCLCODE_COMMAND:
                if (GCL_Command_8001FDB0(pScript + 3) == 1)
                {
                    return 1;
                }
                pScript++;
                pScript += (short)GCL_MakeShort(pScript[1], pScript[0]);
                break;

            case GCLCODE_PROC:
                GCL_Proc_8001FFA0(pScript + 2);
                pScript++;
                pScript += *pScript;
                break;

            case GCLCODE_NULL:
                GCL_UnsetArgStack_800208F0(pOldStack);
                return 0;

            default:
                mts_printf_8008BBA0("SCRIPT COMMAND ERROR %x\n", (unsigned int)*pScript);
        }
    }
    mts_printf_8008BBA0("ERROR in script\n");
    return 1;
}

//extern const char aNotScriptData[];
extern GCL_ARGS gcl_null_args_800AB3BC;

void GCL_ExecScript_80020228()
{
    unsigned char *pMainProc = gGCL_fileData_800B3C18.field_8_pMainProc;
    if (*pMainProc != 0x40)
    {
        mts_printf_8008BBA0("NOT SCRIPT DATA !!\n");
    }
    GCL_ExecBlock_80020118(pMainProc + 3, &gcl_null_args_800AB3BC);
}
