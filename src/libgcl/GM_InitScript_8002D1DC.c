#include "gcl.h"

extern GCL_COMMANDDEF script_commands_8009D68C;

void GM_InitScript_8002D1DC(void)
{
    GCL_BindsInit_8002D1A8();
    GCL_AddCommMulti_8001FD2C(&script_commands_8009D68C);
}
