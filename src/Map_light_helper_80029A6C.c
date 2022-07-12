#include "linker.h"
#include "Script_tbl_map_8002BB44.h"

extern int gLastBindNum_800AB9B8;
int SECTION(".sbss") gLastBindNum_800AB9B8;

extern BindStruct *gpBinds_800AB9BC;
BindStruct *SECTION(".sbss") gpBinds_800AB9BC;

void Map_light_helper_80029A6C(int mask)
{
    int counter;        // $a1
    BindStruct *pIter; // $v1

    pIter = gpBinds_800AB9BC;

    for (counter = gLastBindNum_800AB9B8; counter > 0; counter--)
    {
        if ((pIter->field_6 & mask) == 0)
        {
            pIter->field_8_param_i_c_flags &= ~0x80u;
        }
        pIter++;
    }
}

