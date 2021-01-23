#include "linker.h"
#include "gcl.h"
#include "idaTypes.h"
#include "Script_tbl_map_8002BB44.h"

unsigned int rand_8008E6B8(void);

extern GameState gGameState_800B4D98;

int Script_tbl_rand_8002CD94(void)
{
    int param;
    int rand;

    param = GCL_Get_Param_80020AD4();
    rand = rand_8008E6B8();
    gGameState_800B4D98.unk.LastRand = (short)(rand % param);
    return 0;
}
