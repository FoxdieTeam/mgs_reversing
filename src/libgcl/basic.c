#include "libgcl.h"
#include "common.h"
#include "hash.h"

int GCL_Command_if_80020274(unsigned char *pScript)
{
    int   type, res;
    int   block;
    char *p = pScript;
EXEC_ELSE:
    p = GCL_GetNextValue_8002069C(p, &type, &res);
EXEC_IF:
    p = GCL_GetNextValue_8002069C(p, &type, &block);

    if (res)
    {
        GCL_ExecBlock_80020118((unsigned char *)block, 0);
    }
    else
    {
        p = GCL_GetNextValue_8002069C(p, &type, &res);

        if (p)
        {
            p = (char *)res;

            switch (type >>= 16)
            {
            case 0x65:
                res = 1;
                goto EXEC_IF;
            case 0x69:
                goto EXEC_ELSE;
            }
        }
    }

    return 0;
}

int GCL_Command_eval_80020318(unsigned char *pScript)
{
    int code;
    int value;

    GCL_GetNextValue_8002069C(pScript, &code, &value);
    return 0;
}

int GCL_Command_foreach_8002033C(unsigned char *pScript)
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
        pScript = GCL_GetNextValue_8002069C(pScript, &code, &value);
        if ((char)code == GCLCODE_PARAMETER)
        {
            break;
        }
        *argbuf_p++ = value;
    }
    // Loop on args
    pScript = GCL_GetNextValue_8002069C((char *)value, &code, &value);
    exec_param = (char *)value; // "-do" parameter
    arg.argc = 1;
    arg.argv = argbuf;
    for (i = ((int)argbuf_p - (int)&argbuf) >> 2; i > 0; i--)
    {
        GCL_ExecBlock_80020118(exec_param, &arg);
        arg.argv++;
    }

    return 0;
}

int GCL_Cmd_Return_80020404(unsigned char *pScript)
{
    return 1;
}

GCL_COMMANDLIST commlist_8009D470[] = {{HASH_CMD_if, GCL_Command_if_80020274},
                                       {HASH_CMD_eval, GCL_Command_eval_80020318},
                                       {HASH_CMD_return, GCL_Cmd_Return_80020404},
                                       {HASH_CMD_foreach, GCL_Command_foreach_8002033C}};

GCL_COMMANDDEF builtin_commands_8009D490 = {0, COUNTOF(commlist_8009D470), commlist_8009D470};

void GCL_InitBasicCommands_8002040C()
{
    GCL_AddCommMulti_8001FD2C(&builtin_commands_8009D490);
}
