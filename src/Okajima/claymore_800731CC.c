#include "linker.h"
#include "libdg.h"

extern SVECTOR stru_8009F630[4];

void claymore_800731CC(SVECTOR *param_1)
{
    DG_PutVector_8001BE48(stru_8009F630, param_1, 4); // 4 = sizeof?
}
