#include "libgcl/gcl.h"

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
