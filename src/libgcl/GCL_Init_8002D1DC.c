#include "gcl.h"

extern GCL_COMMANDDEF gGCL_default_commands_8009D68C;

extern int       GCL_BindsInit_8002D1A8(void);

void GCL_Init_8002D1DC(void)
{
    GCL_BindsInit_8002D1A8();
    GCL_AddCommMulti_8001FD2C(&gGCL_default_commands_8009D68C);
}
