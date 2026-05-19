#include "libgcl.h"
#include "common.h"
#include "strcode.h"

static int GCL_Command_if(unsigned char *top)
{
    int   type, res;
    int   block;
    char *p = top;
exec_else:
    p = GCL_GetNextValue(p, &type, &res);
exec_if:
    p = GCL_GetNextValue(p, &type, &block);

    if (res)
    {
        GCL_ExecBlock((unsigned char *)block, 0);
    }
    else
    {
        p = GCL_GetNextValue(p, &type, &res);

        if (p)
        {
            p = (char *)res;

            switch (type >>= 16)
            {
            case 'e':
                res = 1;
                goto exec_if;
            case 'i':
                goto exec_else;
            }
        }
    }

    return GCL_OK;
}

static int GCL_Command_eval(unsigned char *top)
{
    int code;
    int value;

    GCL_GetNextValue(top, &code, &value);
    return GCL_OK;
}

static int GCL_Command_foreach(unsigned char *top)
{
    long     argbuf[16];
    long    *argbuf_p;
    GCL_ARGS arg;
    int      i, code, value;
    char    *exec_param;

    // Parse args
    argbuf_p = argbuf;
    for (;;)
    {
        top = GCL_GetNextValue(top, &code, &value);
        if ((char)code == GCL_OPTION)
        {
            break;
        }
        *argbuf_p++ = value;
    }
    // Loop on args
    top = GCL_GetNextValue((char *)value, &code, &value);
    exec_param = (char *)value; // "-do" parameter
    arg.argc = 1;
    arg.argv = argbuf;
    for (i = ((int)argbuf_p - (int)&argbuf) >> 2; i > 0; i--)
    {
        GCL_ExecBlock(exec_param, &arg);
        arg.argv++;
    }

    return GCL_OK;
}

static int GCL_Command_return(unsigned char *top)
{
    return GCL_RETURN;
}

STATIC GCL_COMMANDLIST commlist[] = {
    { 0x0d86, GCL_Command_if },         // GV_StrCode("if")
    { 0x64c0, GCL_Command_eval },       // GV_StrCode("eval")
    { 0xcd3a, GCL_Command_return },     // GV_StrCode("return")
    { 0x7636, GCL_Command_foreach },    // GV_StrCode("foreach")
};

STATIC GCL_COMMANDDEF builtin_commands = GCL_COMMANDS(commlist);

void GCL_InitBasicCommands(void)
{
    GCL_AddCommMulti(&builtin_commands);
}
