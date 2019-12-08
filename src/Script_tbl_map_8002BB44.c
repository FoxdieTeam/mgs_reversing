#include "linker.h"
#include "gcl.h"
#include "delay.h"

typedef struct LitHeader
{
    int field_0_num_lights;
} LitHeader;

typedef struct map_record
{
    int field_0_map_index_bit;
    short field_4_map_num;
    short field_6_bUsed;
    struct HzdMap *field_8_hzd;
    LitHeader *field_C_l_file;
    int field_10_script_z_param_bit_index_zone_id;
} map_record;

void Map_ScriptLoadMapBlocks_800312D0(void);
void Map_ScriptReloadMaps_80031450(int);
map_record *Map_FindByNum_80031504(int);
void Map_MarkUsed_80031324(int);
void Map_MarkNotUsed_800313C0(int);

void DG_Set_RGB_800184F4(int, int, int);

extern int game_state_flags_800AB3CC;
extern int counter_800AB380;

int SECTION(".sbss") gBinds_800ABA60;
int SECTION(".sbss") gBindsCount_800ABA64;

int Script_tbl_map_8002BB44(unsigned char *pScript)
{
    map_record *pMapRecord;
    short colourVec[3];

    if (GCL_GetParam_80020968('d'))
    {
        Map_ScriptLoadMapBlocks_800312D0();
    }

    if (GCL_GetParam_80020968('s'))
    {
        Map_ScriptReloadMaps_80031450(1);
        if (!(game_state_flags_800AB3CC & 0x80000000))
        {
            counter_800AB380 = 4;
        }
    }

    if (GCL_GetParam_80020968('c'))
    {
        Map_ScriptReloadMaps_80031450(0);

        if (!(game_state_flags_800AB3CC & 0x80000000))
        {
            if (GCL_GetParam_80020968('u'))
            {
                counter_800AB380 = 4;
            }
            else
            {
                counter_800AB380 = 0;
            }
        }
    }

    if (GCL_GetParam_80020968('a'))
    {
        gBinds_800ABA60 = 0;
        while (GCL_Get_Param_Result_80020AA4())
        {
            pMapRecord = Map_FindByNum_80031504(GCL_Get_Param_80020AD4());
            if (pMapRecord == 0)
            {
                return -1;
            }
            gBinds_800ABA60 = gBinds_800ABA60 | pMapRecord->field_0_map_index_bit;
        }
    }

    if (GCL_GetParam_80020968('p'))
    {
        while (GCL_Get_Param_Result_80020AA4())
        {
            Map_MarkUsed_80031324(GCL_Get_Param_80020AD4());
        }
    }

    if (GCL_GetParam_80020968('m'))
    {
        while (GCL_Get_Param_Result_80020AA4())
        {
            Map_MarkNotUsed_800313C0(GCL_Get_Param_80020AD4());
        }
    }

    if (GCL_GetParam_80020968('b'))
    {
        GCL_ReadVector_80020A14(GCL_Get_Param_Result_80020AA4(), &colourVec[0]);
        DG_Set_RGB_800184F4(colourVec[0], colourVec[1], colourVec[2]);
    }

    return 0;
}

int Map_Script_tbl_hzd_impl_800310D0(void);

int Script_tbl_hzd_8002BD04(unsigned char *pScript)
{
    if (!Map_Script_tbl_hzd_impl_800310D0())
    {
        return -1;
    }
    return 0;
}

#define CTC(X) ({ extern int __attribute__((error("assertion failure: '" #X "' not true"))) compile_time_check(); ((X)?0:compile_time_check()),0; })

#define CTASTR2(pre, post) pre##post
#define CTASTR(pre, post) CTASTR2(pre, post)
#define STATIC_ASSERT(cond, msg, line)                        \
    typedef struct                                            \
    {                                                         \
        int CTASTR(static_assertion_failed_, msg) : !!(cond); \
    } CTASTR(static_assertion_failed_, line)

#define STATIC_ASSERT_SIZE(struct, size) STATIC_ASSERT(sizeof(struct) == size, wrong_size, __LINE__)

typedef struct BindStruct
{
    short field_0;
    short field_2_param_m;

    short field_4;
    short field_6;

    unsigned char field_8_param_i_c_flags;
    char field_9_param_s;
    char field_A_param_b;
    unsigned char field_B_param_e;

    short field_C_param_d;
    short field_E_param_d_or_512;

    int field_10_every;
    int field_14_proc_and_block;
} BindStruct;

STATIC_ASSERT_SIZE(BindStruct, 0x18);

void sub_80029A5C(int, BindStruct *, int);

BindStruct SECTION(".gBindsArray_800b58e0") gBindsArray_800b58e0[128];

extern void mg_printf_8008BBA0(const char *, ...);

extern const char aBindsOver[];

int sub_8002BD34(unsigned char *pScript)
{
    int iVar1;
    int sVar2;
    BindStruct *pBVar4;
    int auStack24;
    int local_14;
    int tmp;

    if (0x7f < gBindsCount_800ABA64)
    {
        mg_printf_8008BBA0(aBindsOver);
    }

    iVar1 = gBindsCount_800ABA64;
    pBVar4 = gBindsArray_800b58e0 + gBindsCount_800ABA64;

    sVar2 = GCL_Get_Param_80020AD4();
    if (sVar2 == 0x14c9)
    {
        sVar2 = 0;
    }
    gBindsArray_800b58e0[iVar1].field_4 = sVar2;

    sVar2 = GCL_Get_Param_80020AD4();
    if (sVar2 == 0x14c9)
    {
        sVar2 = 0;
    }
    pBVar4->field_0 = sVar2;

    sVar2 = GCL_Get_Param_80020AD4();
    if (sVar2 == 0x14c9)
    {
        sVar2 = 0;
    }
    gBindsArray_800b58e0[iVar1].field_2_param_m = sVar2;

    gBindsArray_800b58e0[iVar1].field_B_param_e = 0;
    gBindsArray_800b58e0[iVar1].field_8_param_i_c_flags = 0;

    GCL_Execute_8002069C(GCL_Get_Param_Result_80020AA4(), &auStack24, &local_14);
    gBindsArray_800b58e0[iVar1].field_14_proc_and_block = local_14;
    gBindsCount_800ABA64++; // 780 gp

    tmp = gBinds_800ABA60;
    gBindsArray_800b58e0[iVar1].field_6 = (short)tmp; // 0x77c gp
    sub_80029A5C(0, gBindsArray_800b58e0, gBindsCount_800ABA64);

    return 0;
}

extern const char aNtrapCanTSetEv[];
extern const char aNtrapCanTSetPr[];
extern const char aBind08x[];

int Script_tbl_ntrap_8002BE20(unsigned char *pScript)
{
    // int bindIdx;

    BindStruct *pBind;
    short bVar7;
    
    int sVar3;
    int tmp ;

    if (gBindsCount_800ABA64 > 127) // 780 gp
    {
        mg_printf_8008BBA0(aBindsOver);
    }
    // bindIdx = gBindsCount_800ABA64; // 780 gp
    pBind = gBindsArray_800b58e0 + gBindsCount_800ABA64;

    sVar3 = GCL_Get_Param_80020AD4();
    if (sVar3 == 0x14c9)
    {
        sVar3 = 0;
    }

    pBind->field_4 = sVar3;

    sVar3 = GCL_Get_Param_80020AD4();
     if (sVar3 == 0x14c9)
    {
        sVar3 = 0;
    }
    pBind->field_0 = sVar3;

    pBind->field_8_param_i_c_flags = 0; // v0

    bVar7 = 0; // still s1

  
    sVar3 = GCL_GetParam_80020968(0x6d);
    if (sVar3 != 0)
    {
        sVar3 = GCL_Get_Param_80020AD4();
        if (sVar3 == 0x14c9)
        {
            // TODO: Hack to force a match :(
            asm("move $2, $17"); // sVar3 = bVar7, the compiler always wants to use $zero instead of $s1, e.g $v0, $s1 VS $v0, $zero
            //sVar3 = 0; // wrong
        }
        
        pBind->field_2_param_m = sVar3;
    }
    else
    {
        pBind->field_2_param_m = 0;
    }

    sVar3 = GCL_GetParam_80020968(0x64);
    if (sVar3)
    {
        bVar7 |= 1;
        pBind->field_C_param_d = GCL_Get_Param_80020AD4();

        if (GCL_Get_Param_Result_80020AA4())
        {
            pBind->field_E_param_d_or_512 = GCL_Get_Param_80020AD4();
        }
        else
        {
            pBind->field_E_param_d_or_512 = 0x200;
        }
    }

    if (GCL_GetParam_80020968(0x62))
    {
        bVar7 |= 4;
        pBind->field_A_param_b = GCL_Get_Param_80020AD4();
    }

    if (GCL_GetParam_80020968(0x73))
    {
        bVar7 |= 2;
        pBind->field_9_param_s = GCL_Get_Param_80020AD4();
    }

    if (GCL_GetParam_80020968(0x72))
    {
        bVar7 |= 0x40;
    }

    if (GCL_GetParam_80020968(0x69))
    {
        pBind->field_8_param_i_c_flags |= 1;
    }

    if (GCL_GetParam_80020968(99))
    {
        pBind->field_8_param_i_c_flags |= 2;
    }

    if (GCL_GetParam_80020968(0x74))
    {
        if ((bVar7 & 0x40) != 0)
        {
            mg_printf_8008BBA0(aNtrapCanTSetEv);
        }
        pBind->field_10_every = GCL_Get_Param_80020AD4();
    }

    if (GCL_GetParam_80020968(0x70))
    {
        bVar7 |= 0x80;
        pBind->field_14_proc_and_block = GCL_Get_Param_80020AD4();
    }

    if (GCL_GetParam_80020968(0x65))
    {
        int auStack24;
        int local_14;
        if ((bVar7 & 0x80) != 0)
        {
            mg_printf_8008BBA0(aNtrapCanTSetPr);
        }
        GCL_Execute_8002069C(GCL_Get_Param_Result_80020AA4(), &auStack24, &local_14);
        pBind->field_14_proc_and_block = local_14;
    }

    pBind->field_B_param_e = bVar7;
    gBindsCount_800ABA64++;
    tmp = gBinds_800ABA60;
    pBind->field_6 = (short)tmp;
    mg_printf_8008BBA0(aBind08x, tmp);
    sub_80029A5C(0, gBindsArray_800b58e0, gBindsCount_800ABA64);
    return 0;
}

int Script_tbl_delay_8002C074(void)
{
    int script_pVar;
    int script_tVar;
    int auStack24;
    int local_14;

    script_tVar = 0;
    script_pVar = 0;

    if (GCL_GetParam_80020968('t'))
    {
        script_tVar = GCL_Get_Param_80020AD4();
    }

    if (GCL_GetParam_80020968('p'))
    {
        script_pVar = GCL_Get_Param_80020AD4();
    }

    if (GCL_GetParam_80020968('e'))
    {
        GCL_Execute_8002069C(GCL_Get_Param_Result_80020AA4(), &auStack24, &local_14);
        script_pVar = local_14;
    }

    if (GCL_GetParam_80020968('g'))
    {
        script_tVar = -script_tVar;
    }

    if (script_tVar && script_pVar)
    {
        delay_init_80033230(script_pVar, 0, script_tVar);
        return 0;
    }
    return -1;
}

typedef struct LibGV_Msg
{
    short field_0_res_hash;
    short field_2_num_same_messages;
    short field_4_action_hash_or_ptr;
    short field_6_hash;
    short field_8_min1;
    short field_A_min1;
    short field_C_min1;
    short field_E;
    short field_10;
    short field_12_num_valid_fields;
} LibGV_Msg;

int GV_SendMessage_80016504(LibGV_Msg *);

int Script_tbl_mesg_8002C138(unsigned char *pScript)
{
    unsigned char *uParm1;
    int iVar1;
    int ret;
    short *pMsgDst;
    LibGV_Msg mesg;
    int count;

    mesg.field_0_res_hash = GCL_Get_Param_80020AD4();
    pMsgDst = &mesg.field_4_action_hash_or_ptr;
    count = 0;
    while (uParm1 = GCL_Get_Param_Result_80020AA4(), uParm1 != 0x0)
    {
        int iVar2 = GCL_800209E8(uParm1);
        *pMsgDst = (short)iVar2;
        pMsgDst++;
        count++;
    }
    mesg.field_12_num_valid_fields = count;
    iVar1 = GV_SendMessage_80016504(&mesg);
    ret = 0;
    if (iVar1 < 0)
    {
        ret = -1;
    }
    return ret;
}

TGCL_CommandFn GM_GCL_LookupActorFunc_8002A8C4(unsigned char *pScript);

int Script_tbl_chara_8002C1B0(unsigned char *pScript, int unknown)
{
    int ret;
    TGCL_CommandFn pCreateActorFn;

    pCreateActorFn = GM_GCL_LookupActorFunc_8002A8C4(GCL_Get_Param_Result_80020AA4());
    if (pCreateActorFn)
    {
        (*pCreateActorFn)(GCL_800209E8(GCL_Get_Param_Result_80020AA4()), gBinds_800ABA60, pScript, unknown);
        ret = 0;
    }
    else
    {
        ret = -1;
    }
    return ret;
}
