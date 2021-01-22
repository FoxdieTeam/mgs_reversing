#include "linker.h"
#include "gcl.h"
#include "idaTypes.h"

unsigned int rand_8008E6B8(void);

extern unknown_800B4D98 gUnknown_struct_800B4D98;

int Script_tbl_rand_8002CD94(unsigned char *pScript)
{
    int param;
    int rand;

    param = GCL_Get_Param_80020AD4();
    rand = rand_8008E6B8();
    gUnknown_struct_800B4D98.unknown_6 = (short)(rand % param);
    return 0;
}
