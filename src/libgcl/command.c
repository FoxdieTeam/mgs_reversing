#include "libgcl.h"
#include "Game/game.h"

// #define STATIC static
#define STATIC

STATIC GCL_COMMANDDEF *commdef = 0;

int GCL_AddCommMulti(GCL_COMMANDDEF *def)
{
    // Set the new chains next to the existing chain
    def->next = commdef;

    // Update the existing chain to be the new chain
    commdef = def;

    return 0;
}

STATIC GCL_COMMANDLIST *GCL_FindCommand(int id)
{
    GCL_COMMANDLIST *list;
    int              commandCount;
    GCL_COMMANDDEF  *def;

    for (def = commdef; def != NULL; def = def->next)
    {
        list = def->commlist;
        for (commandCount = def->n_commlist; 0 < commandCount; commandCount--)
        {
            if (list->id == id)
            {
                return list;
            }
            list++;
        }
    }
    printf("command not found\n");
    return 0;
}

int GCL_Command(unsigned char *ptr)
{
    int commandRet;

    GCL_COMMANDLIST *pFoundCommand = GCL_FindCommand((unsigned short)GCL_GetShort(ptr));
    GCL_AdvanceShort(ptr);

    GCL_SetCommandLine(ptr + GCL_GetByte(ptr));
    GCL_AdvanceByte(ptr);

    GCL_SetArgTop(ptr); // save command return address?

    commandRet = pFoundCommand->function(ptr);

    GCL_UnsetCommandLine();

    return commandRet;
}

STATIC GCL_PROC_TABLE *set_proc_table(GCL_PROC_TABLE *proc_table)
{
    GCL_PROC_TABLE *pt = proc_table;
    while (*(int *)pt)
    {
        pt->proc_id = (unsigned short)GCL_GetShort((char *)&pt->proc_id);
        pt->offset = (unsigned short)GCL_GetShort((char *)&pt->offset);
        pt++;
    }
    return pt + 1;
}

extern GCL_SCRIPT gGCL_SCRIPT_800B3C18;

STATIC unsigned char *get_proc_block(int proc_id)
{
    GCL_PROC_TABLE *pt;
    for (pt = gGCL_SCRIPT_800B3C18.proc_table; *(int *)pt; pt++)
    {
        if (pt->proc_id == proc_id)
        {
            return gGCL_SCRIPT_800B3C18.proc_body + pt->offset;
        }
    }
    printf("PROC %X NOT FOUND\n", proc_id);
    return 0;
}

void GCL_ForceExecProc(int proc_id, GCL_ARGS *args)
{
    GCL_ExecBlock(get_proc_block(proc_id) + 3, args);
}

extern int              GM_LoadRequest_800AB3D0;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;

int GCL_ExecProc(int proc_id, GCL_ARGS *args)
{
    if (GM_LoadRequest_800AB3D0 || (GM_PlayerStatus_800ABA50 & PLAYER_GAMEOVER))
    {
        printf("proc %d cancel\n", proc_id);
        return 0;
    }
    return GCL_ExecBlock(get_proc_block(proc_id) + 3, args);
}

#define GCL_MakeShort(b1, b2) ((b1) | (b2 << 8))

STATIC int GCL_Proc(unsigned char *ptr)
{
    long     argbuf[8];
    GCL_ARGS args;
    int      code;
    int      value;
    int      arg_idx;

    int b1 = ptr[0];
    int b2 = ptr[1];

    int proc_id = GCL_MakeShort(b2, b1);
    GCL_AdvanceShort(ptr);

    arg_idx = 0;

    // TODO: Can't match without comma operator ??
    while (ptr = GCL_GetNextValue(ptr, &code, &value), code != 0)
    {
        if (arg_idx >= 8)
        {
            printf("TOO MANY ARGS PROC\n");
        }
        argbuf[arg_idx++] = value;
    }

    args.argc = arg_idx;
    args.argv = argbuf;

    GCL_ExecProc(proc_id, &args);
    return 0;
}

int GCL_LoadScript(unsigned char *datatop)
{
    GCL_PROC_TABLE     *proc_table;
    unsigned char      *tmp;
    unsigned int        len;

    proc_table = (GCL_PROC_TABLE *)(datatop + sizeof(int));

    len = GCL_GetLong(datatop);
    gGCL_SCRIPT_800B3C18.proc_table = proc_table;
    gGCL_SCRIPT_800B3C18.proc_body = (char *)set_proc_table(proc_table);
    tmp = ((char *)gGCL_SCRIPT_800B3C18.proc_table) + len;
    gGCL_SCRIPT_800B3C18.script_body = tmp + sizeof(int);

    // Points to script data end
    font_set_font_addr_80044BC0(2, gGCL_SCRIPT_800B3C18.script_body + GCL_GetLong(tmp) + sizeof(int));

    return 0;
}

int GCL_ExecBlock(unsigned char *top, GCL_ARGS *args)
{
    int *pOldStack = GCL_SetArgStack(args);
    while (top)
    {
        switch (*top)
        {
        case GCLCODE_EXPRESSION: {
            int auStack24[2]; // TODO: probably an arg pair ??
            GCL_Expr(top + 2, auStack24);
            top++;
            top += *top;
        }
        break;

        case GCLCODE_COMMAND:
            if (GCL_Command(top + 3) == 1)
            {
                return 1;
            }
            top++;
            top += (short)GCL_MakeShort(top[1], top[0]);
            break;

        case GCLCODE_PROC:
            GCL_Proc(top + 2);
            top++;
            top += *top;
            break;

        case GCLCODE_NULL:
            GCL_UnsetArgStack(pOldStack);
            return 0;

        default:
            printf("SCRIPT COMMAND ERROR %x\n", (unsigned int)*top);
        }
    }
    printf("ERROR in script\n");
    return 1;
}

GCL_ARGS gcl_null_args = {};

void GCL_ExecScript(void)
{
    unsigned char *datatop = gGCL_SCRIPT_800B3C18.script_body;
    if (*datatop != 0x40)
    {
        printf("NOT SCRIPT DATA !!\n");
    }
    GCL_ExecBlock(datatop + 3, &gcl_null_args);
}
