#include "linker.h"
#include "Script_tbl_map_8002BB44.h"
#include "gcl.h"
#include "delay.h"
#include "strcode.h"
#include "mts_new.h"
#include "menuMan.h"
#include <sys/types.h>
#include <libgte.h>

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
        if (!(game_state_flags_800AB3CC & GAME_FLAG_BIT_32))
        {
            counter_800AB380 = 4;
        }
    }

    if (GCL_GetParam_80020968('c'))
    {
        Map_ScriptReloadMaps_80031450(0);

        if (!(game_state_flags_800AB3CC & GAME_FLAG_BIT_32))
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

void GM_SetBinds_80029A5C(int, BindStruct *, int);

BindStruct SECTION(".gBindsArray_800b58e0") gBindsArray_800b58e0[128];

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
        mts_printf_8008BBA0(aBindsOver);
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
    GM_SetBinds_80029A5C(0, gBindsArray_800b58e0, gBindsCount_800ABA64);

    return 0;
}

extern const char aNtrapCanTSetEv[];
extern const char aNtrapCanTSetPr[];
extern const char aBind08x[];

int Script_tbl_ntrap_8002BE20(unsigned char *pScript)
{
    // int bindIdx;

    BindStruct *pBind;

    int bVar7;
    int sVar3;
    int tmp;

    if (gBindsCount_800ABA64 > 127) // 780 gp
    {
        mts_printf_8008BBA0(aBindsOver);
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

    if (GCL_GetParam_80020968('m'))
    {
        sVar3 = GCL_Get_Param_80020AD4();
        if (sVar3 == 0x14c9)
        {
            sVar3 = 0;
        }
        pBind->field_2_param_m = sVar3;
    }
    else
    {
        pBind->field_2_param_m = 0;
    }

    if (GCL_GetParam_80020968('d'))
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

    if (GCL_GetParam_80020968('b'))
    {
        bVar7 |= 4;
        pBind->field_A_param_b = GCL_Get_Param_80020AD4();
    }

    if (GCL_GetParam_80020968('s'))
    {
        bVar7 |= 2;
        pBind->field_9_param_s = GCL_Get_Param_80020AD4();
    }

    if (GCL_GetParam_80020968('r'))
    {
        bVar7 |= 0x40;
    }

    if (GCL_GetParam_80020968('i'))
    {
        pBind->field_8_param_i_c_flags |= 1;
    }

    if (GCL_GetParam_80020968('c'))
    {
        pBind->field_8_param_i_c_flags |= 2;
    }

    if (GCL_GetParam_80020968('t'))
    {
        if ((bVar7 & 0x40) != 0)
        {
            mts_printf_8008BBA0(aNtrapCanTSetEv);
        }
        pBind->field_10_every = GCL_Get_Param_80020AD4();
    }

    if (GCL_GetParam_80020968('p'))
    {
        bVar7 |= 0x80;
        pBind->field_14_proc_and_block = GCL_Get_Param_80020AD4();
    }

    if (GCL_GetParam_80020968('e'))
    {
        int auStack24;
        int local_14;
        if ((bVar7 & 0x80) != 0)
        {
            mts_printf_8008BBA0(aNtrapCanTSetPr);
        }
        GCL_Execute_8002069C(GCL_Get_Param_Result_80020AA4(), &auStack24, &local_14);
        pBind->field_14_proc_and_block = local_14;
    }

    pBind->field_B_param_e = bVar7;
    gBindsCount_800ABA64++;
    tmp = gBinds_800ABA60;
    pBind->field_6 = (short)tmp;
    mts_printf_8008BBA0(aBind08x, tmp);
    GM_SetBinds_80029A5C(0, gBindsArray_800b58e0, gBindsCount_800ABA64);
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

TGCL_ActorCreateFn GM_GCL_LookupActorFunc_8002A8C4(unsigned char *pScript);

int Script_tbl_chara_8002C1B0(unsigned char *pScript, int unknown)
{
    int ret;
    TGCL_ActorCreateFn pCreateActorFn;

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

extern const char aMenuInitEnd[];

void MENU_InitRadioMemory_8004E0EC(void);
void sub_800212CC(void);
void menu_textureload_8002AC44(void);
void font_load_80044A9C(void);
void sub_80021264(void);

extern int dword_800AB9E8;

int Script_tbl_start_8002C22C(unsigned char *pScript)
{
    if (GCL_GetParam_80020968('s'))
    {
        menu_textureload_8002AC44();
    }

    if (GCL_GetParam_80020968('m'))
    {
        menuman_init_80038954();
        mts_printf_8008BBA0(aMenuInitEnd);
    }

    if (GCL_GetParam_80020968('f'))
    {
        font_load_80044A9C();
    }

    if (GCL_GetParam_80020968('v'))
    {
        sub_80021264();
        MENU_InitRadioMemory_8004E0EC();
        dword_800AB9E8 = 0;
    }

    if (GCL_GetParam_80020968('d'))
    {
        GCL_SetMainOrDemo_8001FCB0(GCL_Get_Param_80020AD4());
    }

    if (GCL_GetParam_80020968('c'))
    {
        sub_800212CC();
        MENU_InitRadioMemory_8004E0EC();
        dword_800AB9E8 = 0;
    }
    return 0;
}

extern int gFlags_800AB3D0;
extern char dword_800ABA58[8];

char *GCL_Read_String_80020A70(char *pScript);
char *GM_StageName_8002A880(char *);
int GM_PushAreaHistory_8002A7D8(int, char *);

char *strcpy_8008E768(char *, char *);

void GV_ResidentHeapReset_800163B0(void);
void GV_ClearFileCache_80015458(void);
void DG_ClearResidentTexture_8001DB10(void);

GameState SECTION(".gGameState_800B4D98") gGameState_800B4D98;

int Script_tbl_load_8002C308(char *pScript)
{
    char *scriptStageName;
    short vec[3];

    scriptStageName = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());
    if (*scriptStageName == '\0')
    {
        gFlags_800AB3D0 = 1;
        return 0;
    }

    if (GCL_GetParam_80020968('r'))
    {
        if (!GCL_Get_Param_80020AD4())
        {
            // Hard restart?
            strcpy_8008E768(dword_800ABA58, GM_StageName_8002A880(scriptStageName));
            GV_ResidentHeapReset_800163B0();
            GV_ClearFileCache_80015458();
            DG_ClearResidentTexture_8001DB10();
            GM_PushAreaHistory_8002A7D8(GV_StrCode_80016CCC(scriptStageName), scriptStageName);
        }
        else
        {
            // Soft restart?
            scriptStageName = dword_800ABA58;
            GM_PushAreaHistory_8002A7D8(gGameState_800B4D98.field_0_stageNameHashed, scriptStageName);
        }

        gFlags_800AB3D0 = 1;
        return 0;
    }

    gGameState_800B4D98.field_88_prevStageNameHashed = gGameState_800B4D98.field_0_stageNameHashed;
    gGameState_800B4D98.field_0_stageNameHashed = GV_StrCode_80016CCC(scriptStageName);

    GM_PushAreaHistory_8002A7D8(gGameState_800B4D98.field_0_stageNameHashed, scriptStageName);

    if (GCL_GetParam_80020968('m'))
    {
        gGameState_800B4D98.field_2_loader_param_m = GCL_Get_Param_80020AD4();
    }

    if (GCL_GetParam_80020968('p'))
    {
        // Snakes starting position in the map?
        GCL_ReadVector_80020A14(GCL_Get_Param_Result_80020AA4(), &vec[0]);
        gGameState_800B4D98.field_4_param_p_vec[0] = vec[0];
        gGameState_800B4D98.field_4_param_p_vec[1] = vec[1];
        gGameState_800B4D98.field_4_param_p_vec[2] = vec[2];
    }

    if (GCL_GetParam_80020968('s'))
    {
        gFlags_800AB3D0 = GCL_Get_Param_80020AD4();
        if (gFlags_800AB3D0)
        {
            gFlags_800AB3D0 |= 0x80;
        }
    }
    else
    {
        gFlags_800AB3D0 = 1;
    }

    if (!GCL_GetParam_80020968('n'))
    {
        gFlags_800AB3D0 |= 0x10;
    }

    return 0;
}
