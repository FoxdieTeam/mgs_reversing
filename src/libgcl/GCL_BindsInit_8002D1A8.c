#include "Script_tbl_map_8002BB44.h"
#include "linker.h"
#include "map/hzd.h"

extern int        gBinds_800ABA60;
extern int        gBindsCount_800ABA64;
extern BindStruct gBindsArray_800b58e0;

// $gp
int SECTION(".sbss") gBinds_800ABA60;
int SECTION(".sbss") gBindsCount_800ABA64;

int GCL_BindsInit_8002D1A8(void)
{
    gBinds_800ABA60 = 0;
    gBindsCount_800ABA64 = 0;
    HZD_SetBind_80029A5C(0, &gBindsArray_800b58e0, 0);
    return 0;
}
