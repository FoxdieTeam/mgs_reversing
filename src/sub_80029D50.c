#include "libgcl/hash.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "Game/linkvarbuf.h"
#include "unknown.h"

extern int    dword_8009D548[];
extern int    dword_8009D570[];
extern int    GM_PlayerStatus_800ABA50;
extern GV_PAD GV_PadData_800B05C0[4];

extern int         gLastBindNum_800AB9B8;
int                gLastBindNum_800AB9B8;

extern BindStruct *gpBinds_800AB9BC;
BindStruct        *gpBinds_800AB9BC;

static inline int sub_helper_80029D50(unsigned short value, unsigned int hash)
{
    return (value == 0) || (value == hash);
}

static inline int sub_helper2_80029D50(BindStruct *pBind, Res_Control_unknown *arg1)
{
    int diff;
    int mask;

    if (!(pBind->field_B_param_e & 0xF))
    {
        return 1;
    }

    if (pBind->field_B_param_e & 0x1)
    {
        diff = (-pBind->field_C_param_d + arg1->field_14_vec.pad) & 0xFFF;

        if (diff > 2048)
        {
            diff = 4096 - diff;
        }

        if (pBind->field_E_param_d_or_512 < diff)
        {
            return 0;
        }
    }

    if (pBind->field_B_param_e & 0x2)
    {
        if (dword_8009D548[pBind->field_9_param_s])
        {
            if (!(GM_PlayerStatus_800ABA50 & dword_8009D548[pBind->field_9_param_s]))
            {
                return 0;
            }
        }
        else if (GM_PlayerStatus_800ABA50 != 0)
        {
            if ((GM_UnkFlagBE != 0) && !(GM_PlayerStatus_800ABA50 & 0x2))
            {
                mask = 0xFFF4C011;
            }
            else
            {
                mask = 0xFFF44010;
            }

            if (GM_PlayerStatus_800ABA50 & ~mask)
            {
                return 0;
            }
        }
    }

    if (pBind->field_B_param_e & 0x4)
    {
        if (GM_PlayerStatus_800ABA50 & 0x80)
        {
            return 0;
        }

        if (!(GV_PadData_800B05C0[0].press & dword_8009D570[pBind->field_A_param_b]))
        {
            return 0;
        }
    }

    return 1;
}

void sub_80029D50(HZD_MAP *pMap, Res_Control_unknown *arg1, int arg2)
{
    BindStruct   *pBind;
    unsigned int  hash, hash2;
    unsigned int  name;
    unsigned int  trigger;
    int           count;
    unsigned char flag;

    if (arg1->field_0_scriptData_orHashedName == 0x50AE)
    {
        sub_80029B9C(pMap, arg1, arg2);
        return;
    }

    pBind = gpBinds_800AB9BC;

    hash = arg1->field_0_scriptData_orHashedName;
    name = arg1->field_2_name_hash;
    trigger = arg1->field_4_trigger_Hash_Name_or_camera_w;

    count = gLastBindNum_800AB9B8;
    for (count--; count >= 0; pBind++, count--)
    {
        if (!sub_helper_80029D50(pBind->field_4, trigger) || !(pBind->field_6 & pMap->f08_areaIndex))
        {
            continue;
        }

        if (!sub_helper_80029D50(pBind->field_0, hash))
        {
            continue;
        }

        hash2 = name;

        if ((arg2 != 0) && sub_helper2_80029D50(pBind, arg1))
        {
            if (!(pBind->field_B_param_e & 0xF))
            {
                if ((arg2 != 1) && !(pBind->field_B_param_e & 0x40))
                {
                    continue;
                }
            }
            else if (pBind->field_8_param_i_c_flags & 0x80)
            {
                continue;
            }
            else if (!(pBind->field_B_param_e & 0x40))
            {
                pBind->field_8_param_i_c_flags |= 0x80;
            }
        }
        else
        {
            flag = pBind->field_B_param_e;
            if ((flag & 0xF) && !(flag & 0x40) && !(pBind->field_8_param_i_c_flags & 0x80))
            {
                continue;
            }

            hash2 = HASH_LEAVE;
            pBind->field_8_param_i_c_flags &= ~0x80;
        }

        if (sub_helper_80029D50(pBind->field_2_param_m, hash2))
        {
            sub_80029AEC(pBind, arg1, hash2, 0);
        }
    }
}
