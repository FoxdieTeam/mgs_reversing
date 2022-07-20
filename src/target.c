#include "linker.h"
#include "target.h"

GM_Target SECTION(".gTargets_800B64E0") gTargets_800B64E0[64];

extern int gTargets_down_count_800ABA68;
int SECTION(".sbss") gTargets_down_count_800ABA68;

void GM_Target_8002E374(int *ppDownCount, GM_Target **ppTargets)
{
    *ppDownCount = gTargets_down_count_800ABA68;
    *ppTargets = gTargets_800B64E0;
}
