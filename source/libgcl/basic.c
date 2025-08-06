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

    return 0;
}

static int GCL_Command_eval(unsigned char *top)
{
    int code;
    int value;

    GCL_GetNextValue(top, &code, &value);
    return 0;
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
        if ((char)code == GCLCODE_PARAMETER)
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

    return 0;
}

static int GCL_Command_return(unsigned char *top)
{
    return 1;
}

STATIC GCL_COMMANDLIST commlist[] = {
    { CMD_if,      GCL_Command_if      },   // GV_StrCode("if")
    { CMD_eval,    GCL_Command_eval    },   // GV_StrCode("eval")
    { CMD_return,  GCL_Command_return  },   // GV_StrCode("return")
    { CMD_foreach, GCL_Command_foreach }    // GV_StrCode("foreach")
};

STATIC GCL_COMMANDDEF builtin_commands = { NULL, COUNTOF(commlist), commlist };

void GCL_InitBasicCommands(void)
{
    GCL_AddCommMulti(&builtin_commands);
}
