#include "libgcl/libgcl.h"
#include "unknown.h"

extern BindStruct *gpBinds_800AB9BC;
BindStruct        *gpBinds_800AB9BC;

extern int gLastBindNum_800AB9B8;
int        gLastBindNum_800AB9B8;

static inline int sub_8002A090_helper(unsigned short value, int hash)
{
    return value == 0 || value == hash;
}

void sub_8002A090(HZD_MAP *pHzdMap, Res_Control_unknown *pCtrlSub, int flags, int hash)
{
    BindStruct     *pBinds;
    int             bindCount;
    int             msgType;
    unsigned short *pArray;
    int             count;

    pBinds = gpBinds_800AB9BC;
    bindCount = gLastBindNum_800AB9B8;

    msgType = pCtrlSub->field_0_scriptData_orHashedName;

    for (bindCount--; bindCount >= 0; pBinds++, bindCount--)
    {
        if (!(pBinds->field_6 & pHzdMap->f08_areaIndex))
        {
            continue;
        }

        if (flags != 0 && !(pBinds->field_8_param_i_c_flags & flags))
        {
            continue;
        }

        if (!sub_8002A090_helper(pBinds->field_0, msgType))
        {
            continue;
        }

        pArray = pCtrlSub->field_8_array;

        for (count = pCtrlSub->field_6_count; count > 0; count--, pArray++)
        {
            if (sub_8002A090_helper(pBinds->field_4, *pArray) && sub_8002A090_helper(pBinds->field_2_param_m, hash))
            {
                sub_80029AEC(pBinds, pCtrlSub, hash, 1);
            }
        }
    }
}
