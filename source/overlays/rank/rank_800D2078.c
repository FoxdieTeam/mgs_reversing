#include "libgcl/libgcl.h"

int rank_800D2078(int proc, long *argv, int argc)
{
    GCL_ARGS  args;
    GCL_ARGS *pArgs;

    pArgs = NULL;
    if (argc)
    {
        args.argc = argc;
        args.argv = argv;
        pArgs = &args;
    }
    return GCL_ExecProc(proc, pArgs);
}
