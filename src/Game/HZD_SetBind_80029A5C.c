#include "linker.h"
#include "libgcl/gcl.h"

extern int         gLastBindNum_800AB9B8;
extern BindStruct *gpBinds_800AB9BC;

int         SECTION(".sbss") gLastBindNum_800AB9B8;
BindStruct *SECTION(".sbss") gpBinds_800AB9BC;

void HZD_SetBind_80029A5C(int param_1, BindStruct *param_2, int param_3)
{
    gLastBindNum_800AB9B8 = param_3;
    gpBinds_800AB9BC = param_2;
    return;
}
