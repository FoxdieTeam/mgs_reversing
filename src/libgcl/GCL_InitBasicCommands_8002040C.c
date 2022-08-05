#include "gcl.h"

/********* sdata ******************/
extern GCL_COMMANDLIST commlist_8009D470[];
extern GCL_COMMANDDEF  builtin_commands_8009D490;
/*********************************/

void GCL_InitBasicCommands_8002040C()
{
    GCL_AddCommMulti_8001FD2C(&builtin_commands_8009D490);
}
