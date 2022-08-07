#include "linker.h"
#include "libgcl/gcl.h"
#include "psyq.h"

extern GameState_800B4D98 gGameState_800B4D98;

int GCL_Command_rand_8002CD94(int argc, char **argv)
{
    int param;
    int rand;

    param = GCL_GetNextParamValue_80020AD4();
    rand = rand_8008E6B8();
    gGameState_800B4D98.field_0A_last_result = (short)(rand % param);
    return 0;
}
