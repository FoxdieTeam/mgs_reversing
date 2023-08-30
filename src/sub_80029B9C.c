#include "libgcl/hash.h"
#include "libhzd/libhzd.h"
#include "unknown.h"

extern int         gLastBindNum_800AB9B8;
int                gLastBindNum_800AB9B8;

extern BindStruct *gpBinds_800AB9BC;
BindStruct        *gpBinds_800AB9BC;

static inline int sub_helper_80029B9C(unsigned short value, unsigned int hash)
{
    return (value == 0) || (value == hash);
}

void sub_80029B9C(HZD_MAP *pMap, Res_Control_unknown *arg1, int arg2)
{
    BindStruct  *pBind;
    unsigned int hash;
    unsigned int name;
    unsigned int trigger;
    int          count;
    unsigned int one;
    unsigned int name2;

    pBind = gpBinds_800AB9BC;
    hash = arg1->field_0_scriptData_orHashedName;
    name = arg1->field_2_name_hash;
    trigger = arg1->field_4_trigger_Hash_Name_or_camera_w;

    count = gLastBindNum_800AB9B8;
    for (count--; count >= 0; pBind++, count--)
    {
        one = 1;

        if (!sub_helper_80029B9C(pBind->field_4, trigger))
        {
            continue;
        }

        if (!(pBind->field_6 & pMap->f08_areaIndex))
        {
            continue;
        }

        if (!sub_helper_80029B9C(pBind->field_0, hash))
        {
            if (!(pBind->field_8_param_i_c_flags & 0x2))
            {
                continue;
            }

            if (!sub_helper_80029B9C(pBind->field_0, CHARA_SNAKE))
            {
                continue;
            }
        }

        name2 = name;

        if (pBind->field_B_param_e & 0xF)
        {
            continue;
        }

        if ((arg2 != 0) && (one != 0))
        {
            if ((arg2 != one) && !(pBind->field_B_param_e & 0x40))
            {
                continue;
            }
        }
        else
        {
            name2 = HASH_LEAVE;
            pBind->field_8_param_i_c_flags &= ~0x80;
        }

        if (sub_helper_80029B9C(pBind->field_2_param_m, name2))
        {
            sub_80029AEC(pBind, arg1, name2, 2);
        }
    }
}
