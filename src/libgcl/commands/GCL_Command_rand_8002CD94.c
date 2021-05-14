#include "linker.h"
#include "gcl.h"
#include "idaTypes.h"
#include "Script_tbl_map_8002BB44.h"

unsigned int rand_8008E6B8(void);

extern GameState_800B4D98 gGameState_800B4D98;

int GCL_Command_rand_8002CD94(void)
{
    int param;
    int rand;

    param = GCL_GetNextParamValue_80020AD4();
    rand = rand_8008E6B8();
    gGameState_800B4D98.field_0A_random_value = (short)(rand % param);
    return 0;
}
