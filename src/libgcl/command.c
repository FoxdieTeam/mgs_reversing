#include "libgcl.h"
#include "Game/game.h"

GCL_COMMANDDEF *commdef_800AB3B8 = 0;

int GCL_AddCommMulti_8001FD2C(GCL_COMMANDDEF *def)
{
    // Set the new chains next to the existing chain
    def->next = commdef_800AB3B8;

    // Update the existing chain to be the new chain
    commdef_800AB3B8 = def;

    return 0;
}

GCL_COMMANDLIST *GCL_FindCommand_8001FD40(int hashedName)
{
    GCL_COMMANDLIST *pTableIter;
    int              commandCount;
    GCL_COMMANDDEF  *pChainIter;

    for (pChainIter = commdef_800AB3B8; pChainIter; pChainIter = pChainIter->next)
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
    printf("command not found\n");
    return 0;
}

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

GCL_ProcTableEntry *GCL_ByteSwap_ProcTable_8001FE28(GCL_ProcTableEntry *pTable)
{
    GCL_ProcTableEntry *pIter = pTable;
    while (*(int *)pIter)
    {
        pIter->procNameHashed = (unsigned short)GCL_GetShort((char *)&pIter->procNameHashed);
        pIter->offset = (unsigned short)GCL_GetShort((char *)&pIter->offset);
        pIter++;
    }
    return pIter + 1;
}

extern GCL_FileData gGCL_fileData_800B3C18;

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
    printf("PROC %X NOT FOUND\n", procNameHashed);
    return 0;
}

void GCL_ForceExecProc_8001FEFC(int procNameHashed, GCL_ARGS *pArgs)
{
    GCL_ExecBlock_80020118(GCL_FindProc_8001FE80(procNameHashed) + 3, pArgs);
}

extern int              GM_LoadRequest_800AB3D0;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;

int GCL_ExecProc_8001FF2C(int procNameHashed, GCL_ARGS *pArgs)
{
    if (GM_LoadRequest_800AB3D0 || (GM_PlayerStatus_800ABA50 & PLAYER_GAMEOVER))
    {
        printf("proc %d cancel\n", procNameHashed);
        return 0;
    }
    return GCL_ExecBlock_80020118(GCL_FindProc_8001FE80(procNameHashed) + 3, pArgs);
}

#define GCL_MakeShort(b1, b2) ((b1) | (b2 << 8))

int GCL_Proc_8001FFA0(unsigned char *pScript)
{
    long     args[8];
    GCL_ARGS argsPtr;
    int      code;
    int      value;
    int      arg_idx;

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
            printf("TOO MANY ARGS PROC\n");
        }
        args[arg_idx++] = value;
    }

    argsPtr.argc = arg_idx;
    argsPtr.argv = args;

    GCL_ExecProc_8001FF2C(procId, &argsPtr);
    return 0;
}

int GCL_LoadScript_80020064(unsigned char *pScript)
{
    GCL_ProcTableEntry *pTableStart;
    unsigned char      *tmp;
    unsigned int        len;

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

int GCL_ExecBlock_80020118(unsigned char *pScript, GCL_ARGS *pArgs)
{
    int *pOldStack = GCL_SetArgStack_8002087C(pArgs);
    while (pScript)
    {
        switch (*pScript)
        {
        case GCLCODE_EXPRESSION: {
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
            printf("SCRIPT COMMAND ERROR %x\n", (unsigned int)*pScript);
        }
    }
    printf("ERROR in script\n");
    return 1;
}

GCL_ARGS gcl_null_args_800AB3BC = {};

void GCL_ExecScript_80020228()
{
    unsigned char *pMainProc = gGCL_fileData_800B3C18.field_8_pMainProc;
    if (*pMainProc != 0x40)
    {
        printf("NOT SCRIPT DATA !!\n");
    }
    GCL_ExecBlock_80020118(pMainProc + 3, &gcl_null_args_800AB3BC);
}
