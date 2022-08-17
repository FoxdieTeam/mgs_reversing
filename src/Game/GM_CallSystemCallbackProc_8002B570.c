#include "libgcl/gcl.h"
#include "game.h"
#include "map/map.h"

extern GM_Control* gSnaControl_800AB9F4;
GM_Control* SECTION(".sbss") gSnaControl_800AB9F4;

extern unsigned short gSystemCallbackProcs_800B58C0[5];

void GM_CallSystemCallbackProc_8002B570(int id, int arg)
{
    int proc;

    if (id == 4 && gSnaControl_800AB9F4 != NULL)
    {
        HZD_ReExecEvent_8002A1F4(gSnaControl_800AB9F4->field_2C_map->field_8_hzd,
                                 &gSnaControl_800AB9F4->field_10_pStruct_hzd_unknown, 0x301);
    }

    proc = gSystemCallbackProcs_800B58C0[id];
    if (proc != 0)
    {
        GCL_ARGS args;
        long     local_18[2];
        
        args.argc = 1;
        args.argv = local_18;
        local_18[0] = arg;
        GCL_ForceExecProc_8001FEFC(proc, &args);
    }
}
