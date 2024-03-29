#include "linker.h"
#include "libgcl/libgcl.h"
#include "libgcl/hash.h"
#include "mts/mts_new.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/camera.h"
#include "libdg/libdg.h"
#include "Game/linkvarbuf.h"
#include "Game/item.h"
#include "Game/delay.h"
#include "Menu/menuman.h"
#include "Kojo/demothrd.h"

STATIC_ASSERT_SIZE(BindStruct, 0x18);

extern  CAMERA          GM_CameraList_800B7718[8];
extern  GM_Camera       GM_Camera_800B77E8;
extern  int             GM_GameStatus_800AB3CC;
extern  int             DG_UnDrawFrameCount_800AB380;
extern  int             GM_LoadRequest_800AB3D0;
extern  char            dword_800ABA58[8];
char                    dword_800ABA58[8]; // gp
extern  BindStruct      gBindsArray_800b58e0[128];
extern  int             GV_PadMask_800AB374;
extern  unsigned int    GM_DisableWeapon_800AB9E4;
extern  int             GM_DisableItem_800ABA28;
extern  int             GM_GameStatus_800AB3CC;
extern  CONTROL        *GM_PlayerControl_800AB9F4;
extern  int             GM_Photocode_800ABA04;
extern  int             dword_8009F46C;
extern  SVECTOR         svector_8009F478;
extern  SVECTOR         GM_PhotoViewPos_800ABA48;

int SECTION(".sbss") gBinds_800ABA60;
int SECTION(".sbss") gBindsCount_800ABA64;

extern char *GM_StageName_800AB918;
char         SECTION(".sbss") * GM_StageName_800AB918;

GCL_COMMANDLIST Commands_8009D5CC[] = {
    {HASH_CMD_mesg, GCL_Command_mesg_8002C138},
    {HASH_CMD_trap, GCL_Command_trap_8002BD34},
    {HASH_CMD_chara, (TGCL_CommandFn)GCL_Command_chara_8002C1B0}, // TODO: Why does this one have a different signature?
    {HASH_CMD_map, GCL_Command_map_8002BB44},
    {HASH_CMD_mapdef, GCL_Command_mapdef_8002BD04},
    {HASH_CMD_camera, GCL_Command_camera_8002B8F0},
    {HASH_CMD_light, GCL_Command_light_8002B854},
    {HASH_CMD_start, GCL_Command_start_8002C22C},
    {HASH_CMD_load, GCL_Command_load_8002C308},
    {HASH_CMD_radio, GCL_Command_radio_8002C4A8},
    {HASH_CMD_str_status, GCL_Command_strstatus_8002C6A4},
    {HASH_CMD_demo, GCL_Command_demo_8002C890},
    {HASH_CMD_ntrap, GCL_Command_ntrap_8002BE20},
    {HASH_CMD_delay, GCL_Command_delay_8002C074},
    {HASH_CMD_pad, GCL_Command_pad_8002C988},
    {HASH_CMD_varsave, GCL_Command_varsave_8002C72C},
    {HASH_CMD_system, GCL_Command_system_8002C7C8},
    {HASH_CMD_sound, GCL_Command_sound_8002CA28},
    {HASH_CMD_menu, GCL_Command_menu_8002CAAC},
    {HASH_CMD_rand, GCL_Command_rand_8002CD94},
    {HASH_CMD_func, GCL_Command_func_8002CDF4}, // probably not func ??
    {HASH_CMD_demodebug, GCL_Command_demodebug_8002CFBC},
    {HASH_CMD_print, GCL_Command_print_8002D0E4},
    {HASH_CMD_jimaku, GCL_Command_jimaku_8002D188}};

GCL_COMMANDDEF script_commands_8009D68C = {0, COUNTOF(Commands_8009D5CC), Commands_8009D5CC};

int GCL_Command_light_8002B854(unsigned char *pScript)
{
    char *light_dir;
    char *light_col;
    char *light_ambient;
    SVECTOR vec;

    if ((light_dir = GCL_GetOption_80020968('d')))
    {
        GCL_StrToSV_80020A14(light_dir, &vec);
        DG_SetMainLightDir_80019FF8(vec.vx, vec.vy, vec.vz);
    }
    if ((light_col = GCL_GetOption_80020968('c')))
    {
        GCL_StrToSV_80020A14(light_col, &vec);
        DG_SetMainLightCol_8001A048(vec.vx, vec.vy, vec.vz);
    }
    if ((light_ambient = GCL_GetOption_80020968('a')))
    {
        GCL_StrToSV_80020A14(light_ambient, &vec);
        DG_SetAmbient_80019F80(vec.vx, vec.vy, vec.vz);
    }
    return 0;
}

/*
proc AGL_FIRST_VF {
#pos -3362 1759 4936
#trg -2475 770 6672
#rot 306 308 0
    camera  set 4  d:CAM_FIX d:CAM_INTERP_LINER d:CAM_CAM_TO_TRG \
            -3362,1759,4936 -2475,770,6672 1
*/

int GCL_Command_camera_8002B8F0(unsigned char *pScript)
{
    int     isEnabled, param_p, camera_id;
    SVECTOR   vec1, vec2;
    CAMERA *cam;

    isEnabled = GCL_GetOption_80020968('e') != 0; // enabled

    if (GCL_GetOption_80020968('b')) // bound
    {
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &vec1);
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &vec2);
        GCL_Command_camera_helper_80030888(&vec1, &vec2, isEnabled);
    }

    if (GCL_GetOption_80020968('t')) // track
    {
        GCL_Command_camera_helper4_80030980(GCL_GetNextParamValue_80020AD4());
    }

    if (GCL_GetOption_80020968('l')) // limit
    {
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &vec1);
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &vec2);
        GCL_Command_camera_helper2_800308E0(&vec1, &vec2, isEnabled);
    }

    if (GCL_GetOption_80020968('r')) // rotate
    {
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &vec1);
        GCL_Command_camera_helper3_80030938(&vec1);
    }

    param_p = GCL_GetOption_80020968('p') != 0;

    if (GCL_GetOption_80020968('s')) // set
    {
        camera_id = GCL_GetNextParamValue_80020AD4();
        if (camera_id < 8)
        {
            printf("set camera %d\n", camera_id); // "set camera %d\n"
            cam = &GM_CameraList_800B7718[camera_id];
            cam->field_10_param1 = GCL_GetNextParamValue_80020AD4();
            cam->field_11_param2 = GCL_GetNextParamValue_80020AD4();
            cam->field_12_param3 = GCL_GetNextParamValue_80020AD4();
            cam->field_13_param_p = param_p;
            GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &cam->field_00_pos);
            GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), (SVECTOR *)&cam->field_08_trg);
            if (GCL_Get_Param_Result_80020AA4())
            {
                cam->field_0e_alertMask = GCL_GetNextParamValue_80020AD4();
            }
            else
            {
                cam->field_0e_alertMask = 0;
            }
            GM_CameraSetAlertMask_80030850(camera_id, cam->field_0e_alertMask);
        }
    }

    if (GCL_GetOption_80020968('a'))
    {
        GM_Camera_800B77E8.field_24_gcl_param_a = GCL_GetNextParamValue_80020AD4();
    }

    if (GCL_GetOption_80020968('c'))
    {
        if (GCL_GetNextParamValue_80020AD4() == 0)
        {
            GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_07;
        }
        else
        {
            GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_07;
        }
    }

    return 0;
}

int GCL_Command_map_8002BB44(unsigned char *pScript)
{
    MAP *pMapRecord;
    SVECTOR       colourVec;

    if (GCL_GetOption_80020968('d'))
    {
        Map_ScriptLoadMapBlocks_800312D0();
    }

    if (GCL_GetOption_80020968('s'))
    {
        Map_ScriptReloadMaps_80031450(1);
        if (!(GM_GameStatus_800AB3CC & GAME_FLAG_BIT_32))
        {
            DG_UnDrawFrameCount_800AB380 = 4;
        }
    }

    if (GCL_GetOption_80020968('c'))
    {
        Map_ScriptReloadMaps_80031450(0);

        if (!(GM_GameStatus_800AB3CC & GAME_FLAG_BIT_32))
        {
            if (GCL_GetOption_80020968('u'))
            {
                DG_UnDrawFrameCount_800AB380 = 4;
            }
            else
            {
                DG_UnDrawFrameCount_800AB380 = 0;
            }
        }
    }

    if (GCL_GetOption_80020968('a'))
    {
        gBinds_800ABA60 = 0;
        while (GCL_Get_Param_Result_80020AA4())
        {
            pMapRecord = Map_FindByNum_80031504(GCL_GetNextParamValue_80020AD4());
            if (pMapRecord == 0)
            {
                return -1;
            }
            gBinds_800ABA60 = gBinds_800ABA60 | pMapRecord->field_0_map_index_bit;
        }
    }

    if (GCL_GetOption_80020968('p'))
    {
        while (GCL_Get_Param_Result_80020AA4())
        {
            GM_AddMap_80031324(GCL_GetNextParamValue_80020AD4());
        }
    }

    if (GCL_GetOption_80020968('m'))
    {
        while (GCL_Get_Param_Result_80020AA4())
        {
            GM_DelMap_800313C0(GCL_GetNextParamValue_80020AD4());
        }
    }

    if (GCL_GetOption_80020968('b'))
    {
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &colourVec);
        DG_Set_RGB_800184F4(colourVec.vx, colourVec.vy, colourVec.vz);
    }

    return 0;
}

int GCL_Command_mapdef_8002BD04(unsigned char *pScript)
{
    if (!GCL_Command_mapdef_impl_800310D0())
    {
        return -1;
    }
    return 0;
}

int GCL_Command_trap_8002BD34(unsigned char *pScript)
{
    BindStruct *pBind;
    int         i, arg, code, value;
    int         tmp;

    if (0x7f < gBindsCount_800ABA64)
    {
        printf("binds over\n");
    }

    i = gBindsCount_800ABA64;
    pBind = gBindsArray_800b58e0 + i;

    // Trap id
    arg = GCL_GetNextParamValue_80020AD4();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    gBindsArray_800b58e0[i].field_4 = arg;

    // Entity id
    arg = GCL_GetNextParamValue_80020AD4();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    pBind->field_0 = arg;

    // Event condition
    arg = GCL_GetNextParamValue_80020AD4();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    gBindsArray_800b58e0[i].field_2_param_m = arg; // mask

    gBindsArray_800b58e0[i].field_B_param_e = 0; // exec
    gBindsArray_800b58e0[i].field_8_param_i_c_flags = 0;

    GCL_GetNextValue_8002069C(GCL_Get_Param_Result_80020AA4(), &code, &value);
    gBindsArray_800b58e0[i].field_14_proc_and_block = value;
    gBindsCount_800ABA64++;

    tmp = gBinds_800ABA60;
    gBindsArray_800b58e0[i].field_6 = (short)tmp;
    HZD_SetBind_80029A5C(0, gBindsArray_800b58e0, gBindsCount_800ABA64);

    return 0;
}

int GCL_Command_ntrap_8002BE20(unsigned char *pScript)
{
    // int bindIdx;
    BindStruct *pBind;
    int         flags;
    int         arg;
    int         tmp;

    if (gBindsCount_800ABA64 > 127) // 780 gp
    {
        printf("binds over\n");
    }
    // bindIdx = gBindsCount_800ABA64; // 780 gp
    pBind = gBindsArray_800b58e0 + gBindsCount_800ABA64;
    arg = GCL_GetNextParamValue_80020AD4();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    pBind->field_4 = arg;
    arg = GCL_GetNextParamValue_80020AD4();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    pBind->field_0 = arg;
    pBind->field_8_param_i_c_flags = 0; // v0
    flags = 0;                          // still s1
    if (GCL_GetOption_80020968('m'))     // mask
    {
        arg = GCL_GetNextParamValue_80020AD4();
        if (arg == HASH_TRAP_ALL)
        {
            arg = 0;
        }
        pBind->field_2_param_m = arg;
    }
    else
    {
        pBind->field_2_param_m = 0;
    }
    if (GCL_GetOption_80020968('d')) // dir
    {
        flags |= 1;
        pBind->field_C_param_d = GCL_GetNextParamValue_80020AD4();

        if (GCL_Get_Param_Result_80020AA4())
        {
            pBind->field_E_param_d_or_512 = GCL_GetNextParamValue_80020AD4();
        }
        else
        {
            pBind->field_E_param_d_or_512 = 0x200;
        }
    }
    if (GCL_GetOption_80020968('b')) // button
    {
        flags |= 4;
        pBind->field_A_param_b = GCL_GetNextParamValue_80020AD4();
    }
    if (GCL_GetOption_80020968('s')) // stance
    {
        flags |= 2;
        pBind->field_9_param_s = GCL_GetNextParamValue_80020AD4();
    }
    if (GCL_GetOption_80020968('r')) // repeat
    {
        flags |= 0x40;
    }
    if (GCL_GetOption_80020968('i'))
    {
        pBind->field_8_param_i_c_flags |= 1;
    }
    if (GCL_GetOption_80020968('c'))
    {
        pBind->field_8_param_i_c_flags |= 2;
    }
    if (GCL_GetOption_80020968('t')) // time
    {
        if ((flags & 0x40) != 0)
        {
            printf("ntrap:can't set every\n");
        }
        pBind->field_10_every = GCL_GetNextParamValue_80020AD4();
    }
    if (GCL_GetOption_80020968('p')) // proc
    {
        flags |= 0x80;
        pBind->field_14_proc_and_block = GCL_GetNextParamValue_80020AD4();
    }
    if (GCL_GetOption_80020968('e')) // exec
    {
        int code;
        int value;
        if ((flags & 0x80) != 0)
        {
            printf("ntrap:can't set proc and block\n");
        }
        GCL_GetNextValue_8002069C(GCL_Get_Param_Result_80020AA4(), &code, &value);
        pBind->field_14_proc_and_block = value;
    }
    pBind->field_B_param_e = flags;
    gBindsCount_800ABA64++;
    tmp = gBinds_800ABA60;
    pBind->field_6 = (short)tmp;
    printf("BIND %08X\n", tmp);
    HZD_SetBind_80029A5C(0, gBindsArray_800b58e0, gBindsCount_800ABA64);
    return 0;
}

int GCL_Command_delay_8002C074(unsigned char *pScript)
{
    int time = 0;
    int proc = 0;

    if (GCL_GetOption_80020968('t')) // time
    {
        time = GCL_GetNextParamValue_80020AD4();
    }
    if (GCL_GetOption_80020968('p')) // proc
    {
        proc = GCL_GetNextParamValue_80020AD4();
    }
    if (GCL_GetOption_80020968('e')) // exec
    {
        int code;
        int value;
        GCL_GetNextValue_8002069C(GCL_Get_Param_Result_80020AA4(), &code, &value);
        proc = value;
    }
    if (GCL_GetOption_80020968('g'))
    {
        time = -time;
    }
    if (time && proc)
    {
        GM_DelayedExecCommand_80033230(proc, 0, time);
        return 0;
    }
    return -1;
}


int GCL_Command_mesg_8002C138(unsigned char *pScript)
{
    unsigned char *uParm1;
    int            iVar1;
    int            ret;
    short         *pMsgDst;
    GV_MSG         mesg;
    int            count;

    mesg.address = GCL_GetNextParamValue_80020AD4();
    pMsgDst = &mesg.message[0];
    count = 0;
    while (uParm1 = GCL_Get_Param_Result_80020AA4(), uParm1 != 0x0)
    {
        int iVar2 = GCL_StrToInt_800209E8(uParm1);
        *pMsgDst = (short)iVar2;
        pMsgDst++;
        count++;
    }
    mesg.message_len = count;
    iVar1 = GV_SendMessage_80016504(&mesg);
    ret = 0;
    if (iVar1 < 0)
    {
        ret = -1;
    }
    return ret;
}

int GCL_Command_chara_8002C1B0(int argc, char **argv)
{
    int                ret;
    int                charaHash;
    TGCL_ActorCreateFn pCreateActorFn;

    pCreateActorFn = GM_GetChara_8002A8C4(GCL_Get_Param_Result_80020AA4());
    if (pCreateActorFn)
    {
        charaHash = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        (*pCreateActorFn)(charaHash, gBinds_800ABA60, argc, argv);
        ret = 0;
    }
    else
    {
        ret = -1;
    }
    return ret;
}

extern int gTotalFrameTime_800AB9E8;

int GCL_Command_start_8002C22C(unsigned char *pScript)
{
    if (GCL_GetOption_80020968('s'))
    {
        GM_InitReadError_8002AC44();
    }

    if (GCL_GetOption_80020968('m')) // menu
    {
        menuman_init_80038954();
        printf("MENU INIT END\n");
    }

    if (GCL_GetOption_80020968('f')) // font
    {
        font_load_80044A9C();
    }

    if (GCL_GetOption_80020968('v'))
    {
        GCL_InitVar_80021264();
        menu_InitRadioMemory_8004E0EC();
        gTotalFrameTime_800AB9E8 = 0;
    }

    if (GCL_GetOption_80020968('d')) // demo (1 to use demo.gcx instead of scenerio.gcx)
    {
        GCL_ChangeSenerioCode_8001FCB0(GCL_GetNextParamValue_80020AD4());
    }

    if (GCL_GetOption_80020968('c'))
    {
        GCL_InitClearVar_800212CC();
        menu_InitRadioMemory_8004E0EC();
        gTotalFrameTime_800AB9E8 = 0;
    }
    return 0;
}

int GCL_Command_load_8002C308(unsigned char *pScript)
{
    char *scriptStageName;
    SVECTOR vec;

    scriptStageName = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());
    if (*scriptStageName == '\0')
    {
        GM_LoadRequest_800AB3D0 = 1;
        return 0;
    }

    if (GCL_GetOption_80020968('r'))
    {
        if (!GCL_GetNextParamValue_80020AD4())
        {
            // Hard restart?
            strcpy(dword_800ABA58, GM_GetArea_8002A880((int)scriptStageName));
            GV_ResidentHeapReset_800163B0();
            GV_InitCacheSystem_80015458();
            DG_ClearResidentTexture_8001DB10();
            GM_SetArea_8002A7D8(GV_StrCode_80016CCC(scriptStageName), scriptStageName);
        }
        else
        {
            // Soft restart?
            scriptStageName = dword_800ABA58;
            GM_SetArea_8002A7D8(GM_CurrentStageFlag, scriptStageName);
        }

        GM_LoadRequest_800AB3D0 = 1;
        return 0;
    }

    GM_PreviousStageFlag = GM_CurrentStageFlag;
    GM_CurrentStageFlag = GV_StrCode_80016CCC(scriptStageName);

    GM_SetArea_8002A7D8(GM_CurrentStageFlag, scriptStageName);

    if (GCL_GetOption_80020968('m')) // map
    {
        GM_CurrentMapFlag = GCL_GetNextParamValue_80020AD4();
    }

    if (GCL_GetOption_80020968('p')) // pos
    {
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &vec);
        GM_SnakePosX = vec.vx;
        GM_SnakePosY = vec.vy;
        GM_SnakePosZ = vec.vz;
    }

    if (GCL_GetOption_80020968('s'))
    {
        GM_LoadRequest_800AB3D0 = GCL_GetNextParamValue_80020AD4();
        if (GM_LoadRequest_800AB3D0)
        {
            GM_LoadRequest_800AB3D0 |= 0x80;
        }
    }
    else
    {
        GM_LoadRequest_800AB3D0 = 1;
    }

    if (!GCL_GetOption_80020968('n'))
    {
        GM_LoadRequest_800AB3D0 |= 0x10;
    }

    return 0;
}

int GCL_Command_radio_8002C4A8(unsigned char *pScript)
{
    int contactFrequency;
    int radioTableCode;

    if (GCL_GetOption_80020968('b'))
    {
        while (GCL_Get_Param_Result_80020AA4())
        {
            contactFrequency = GCL_GetNextParamValue_80020AD4();
            radioTableCode = GCL_GetNextParamValue_80020AD4();
            menu_SetRadioBaseCall_80049764(contactFrequency, radioTableCode);
        }
    }
    if (GCL_GetOption_80020968('o'))
    {
        int hash = GCL_GetNextParamValue_80020AD4();
        if (hash == HASH_ENTER)
        {
            hash = 0;
        }
        else if (hash == HASH_LEAVE)
        {
            hash = 1;
        }
        else
        {
            printf("Wrong Code for radio over\n");
        }
        while (GCL_Get_Param_Result_80020AA4())
        {
            contactFrequency = GCL_GetNextParamValue_80020AD4();
            radioTableCode = GCL_GetNextParamValue_80020AD4();
            if (hash)
            {
                radioTableCode = -1;
            }
            menu_SetRadioOverCall_80049794(contactFrequency, radioTableCode);
        }
    }
    if (GCL_GetOption_80020968('c')) // call
    {
        menu_RadioCall_80042730(GCL_GetNextParamValue_80020AD4(),  // contactFrequency
                                GCL_GetNextParamValue_80020AD4(),  // radioTableCode
                                GCL_GetNextParamValue_80020AD4()); // ring duration ?
    }
    if (GCL_GetOption_80020968('p')) // proc
    {
        menu_SetRadioCallbackProc_8004283C(GCL_GetNextParamValue_80020AD4());
    }
    if (GCL_GetOption_80020968('r')) // reset
    {
        menu_ResetCall_80042814();
    }
    if (GCL_GetOption_80020968('m')) // mesg string (example: "clear")
    {
        menu_SetRadioMemory_8004E110(GCL_GetNextParamValue_80020AD4(),                           // contactFrequency
                                     GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4())); // string
    }
    if (GCL_GetOption_80020968('d')) // disable?
    {
        GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_14;
    }
    if (GCL_GetOption_80020968('e')) // enable?
    {
        GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_14;
    }
    if (GCL_GetOption_80020968('a'))
    {
        menu_ClearRadioTable_8004967C();
    }
    return 0;
}

int GCL_Command_strstatus_8002C6A4(unsigned char *pScript)
{
    int val;

    if (GCL_GetOption_80020968('p'))
    {
        val = GCL_GetNextParamValue_80020AD4();
    }
    else
    {
        val = -1;
    }
    sub_8002B600(val);
    if (GCL_GetOption_80020968('s'))
    {
        GM_LoadRequest_800AB3D0 |= GAME_FLAG_BIT_05;
    }
    if (GCL_GetOption_80020968('a')) // area
    {
        GM_SetArea_8002A7D8(GM_CurrentStageFlag, GM_GetArea_8002A880(0));
    }
    return 0;
}

int GCL_Command_varsave_8002C72C(unsigned char *pScript)
{
    unsigned char *param;

    param = GCL_Get_Param_Result_80020AA4();
    if (GCL_GetOption_80020968('a'))
    {
        GCL_SaveVar_80021314();
        return 0;
    }
    while (*param)
    {
        if (!GCL_IsVariable(*param))
        {
            printf("VARSAVE: NOT VAR !!\n");
        }
        param = GCL_VarSaveBuffer_800217F0(param);
    }
    return 0;
}

int GCL_Command_system_8002C7C8(unsigned char *pScript)
{
    static char options[5] = "gcawi";

    int i, proc;

    for (i = 0; i <= (int)sizeof(options); i++)
    {
        if (GCL_GetOption_80020968(options[i]))
        {
            proc = GCL_GetNextParamValue_80020AD4();
            if (!proc)
            {
                printf("SYSTEM:%c:change proc name\n", options[i]);
            }
            GM_SetSystemCallbackProc_8002B558(i, proc);
        }
    }

    if (GCL_GetOption_80020968('s'))
    {
        GM_StageName_800AB918 = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());
    }
    return 0;
}

int GCL_Command_demo_8002C890(unsigned char *pScript)
{
    int   code, cb_proc;
    char  *msg;

    if ( !GCL_GetOption_80020968( 's' ) ) // scene ?
    {
        printf( "DEMO:NO CODE\n" );
    }
    code = GCL_GetNextParamValue_80020AD4();

    if ( GCL_GetOption_80020968( 'p' ) ) // proc
    {
        cb_proc = GCL_GetNextParamValue_80020AD4() | GAME_FLAG_BIT_32;
    }
    else
    {
        cb_proc = 0;
    }

    GM_CurrentMap_800AB9B0 = gBinds_800ABA60;

    if ( code >= 0 )
    {
        DG_UnDrawFrameCount_800AB380 = 0x7FFF0000;
        GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_32;
        GCL_Command_demo_helper_80037DD8( code, cb_proc );
    }
    else
    {
        if ( cb_proc < 0 )
        {
            cb_proc &= 0xFFFF;
        }
        else
        {
            cb_proc = -1;
        }

        if ( GCL_GetOption_80020968( 'f' ) ) // file
        {
            msg = GCL_Read_String_80020A70( GCL_Get_Param_Result_80020AA4() );
        }
        else
        {
            msg = "DEMO ( no data on CD )";
        }
        NewJimakuStr_8004955C( msg, cb_proc );
    }
    return 0;
}

int GCL_Command_pad_8002C988(unsigned char *pScript)
{
    if (GCL_GetOption_80020968('m'))
    {
        GV_PadMask_800AB374 = GCL_GetNextParamValue_80020AD4();
        GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_28;
    }
    if (GCL_GetOption_80020968('r')) // resume
    {
        GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_29;
    }
    else if (GCL_GetOption_80020968('s')) // stop
    {
        GM_GameStatus_800AB3CC &= ~(GAME_FLAG_BIT_29 | GAME_FLAG_BIT_28 | GAME_FLAG_BIT_08);
    }
    GV_UpdatePadSystem_8001682C();
    return 0;
}

int GCL_Command_sound_8002CA28(unsigned char *pScript)
{
    GCL_Command_sound_impl_8002E688();
    return 0;
}

unsigned int GCL_Command_menu_helper_8002CA48(void)
{
    unsigned int ret = 0;
    int next;

    while (GCL_Get_Param_Result_80020AA4())
    {
        next = GCL_GetNextParamValue_80020AD4();

        if (next > 32)
        {
            return 0;
        }

        ret |= 1 << next;
    }

    return ret;
}


int GCL_Command_menu_8002CAAC(unsigned char *pScript)
{
    if (GCL_GetOption_80020968('j'))
    {
        if (GCL_GetNextParamValue_80020AD4() & 1)
        {
            GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_24;
        }
        else
        {
            GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_24;
        }
    }

    if (GCL_GetOption_80020968('n'))
    {
        if (GCL_GetNextParamValue_80020AD4() & 1)
        {
            item_all_items_and_weapons_unknown2_80033500();
        }
        else
        {
            item_all_items_and_weapons_unknown_80033560();
        }
    }

    if (GCL_GetOption_80020968('m'))
    {
        if (!(GCL_GetNextParamValue_80020AD4() & 1))
        {
            GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_20;
        }
        else
        {
            GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_20;
        }
    }

    if (GCL_GetOption_80020968('l'))
    {
        switch (GCL_GetNextParamValue_80020AD4())
        {
        case 0:
            GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_18;
            break;
        case 1:
        case 3:
            GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_18;
            break;
        case 2:
            GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_17;
            break;
        }
    }

    if (GCL_GetOption_80020968('r'))
    {
        switch (GCL_GetNextParamValue_80020AD4())
        {
        case 0:
            GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_23;
            break;
        case 1:
            GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_23;
            break;
        case 2:
            GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_22;
            break;
        case 3:
            GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_21;
            break;
        }
    }

    if (GCL_GetOption_80020968('p'))
    {
        if (GCL_GetNextParamValue_80020AD4() & 1)
        {
            GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_15;
        }
        else
        {
            GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_15;
        }
    }

    if (GCL_GetOption_80020968('s'))
    {
        menu_SetRadarScale_80038E28(GCL_GetNextParamValue_80020AD4());
    }

    if (GCL_GetOption_80020968('w')) // weapon
    {
        GM_DisableWeapon_800AB9E4 = GCL_Command_menu_helper_8002CA48();
    }

    if (GCL_GetOption_80020968('i')) // item
    {
        GM_DisableItem_800ABA28 = GCL_Command_menu_helper_8002CA48();
    }
    return 0;
}

int GCL_Command_rand_8002CD94(unsigned char *pScript)
{
    int param;
    int randValue;

    param = GCL_GetNextParamValue_80020AD4();
    randValue = rand();
    GM_LastResultFlag = randValue % param;
    return 0;
}

int GCL_Command_func_8002CDF4(unsigned char *pScript)
{
    SVECTOR     vec;
    CONTROL *unkStruct;
    int         param;
    MAP *map;

    if (GCL_GetOption_80020968('v')) // vector
    {
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &vec);
        GM_LastResultFlag = DG_PointCheckOne_8001C18C((DVECTOR *)&vec);
    }
    if (GCL_GetOption_80020968('s'))
    {
        unkStruct = GM_PlayerControl_800AB9F4;
        GM_SnakePosX = unkStruct->field_0_mov.vx;
        GM_SnakePosY = unkStruct->field_0_mov.vy;
        GM_SnakePosZ = unkStruct->field_0_mov.vz;
        GM_LastResultFlag = unkStruct->field_8_rot.vy;
    }
    if (GCL_GetOption_80020968('a')) // area
    {
        GM_LastResultFlag = GM_AreaHistory_8002A848(GCL_GetNextParamValue_80020AD4());
    }
    if (GCL_GetOption_80020968('p')) // photo (used for ghosts easter egg)
    {
        param = GCL_GetNextParamValue_80020AD4();
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &GM_PhotoViewPos_800ABA48);
        if (GCL_GetNextParamValue_80020AD4() == HASH_LEAVE)
        {
            param = 0;
        }
        GM_Photocode_800ABA04 = param;
    }
    if (GCL_GetOption_80020968('m')) // map
    {
        map = Map_FindByNum_80031504(GCL_GetNextParamValue_80020AD4());
        if (map && map->field_6_bUsed)
        {
            GM_LastResultFlag = 1;
        }
        else
        {
            GM_LastResultFlag = 0;
        }
    }
    if (GCL_GetOption_80020968('c'))
    {
        GM_LastResultFlag = GM_StreamStatus_80037CD8();
    }
    if (GCL_GetOption_80020968('n'))
    {
        GM_LastResultFlag = dword_8009F46C;
        GM_SnakePosX = svector_8009F478.vx;
        GM_SnakePosY = svector_8009F478.vy;
        GM_SnakePosZ = svector_8009F478.vz;
    }
    return 0;
}

int demodebug_finish_proc_800AB414 = -1;

int GCL_Command_demodebug_8002CFBC(unsigned char *pScript)
{
    int   tmp, demo, flags, ivar;
    char *str;

    ivar = 0;
    str = (char *)0;
    flags = GCL_GetOption_80020968('e') != 0;
    if (GCL_GetOption_80020968('a'))
    {
        flags |= 4;
    }
    if (GCL_GetOption_80020968('v'))
    {
        flags |= 2;
    }
    if (GCL_GetOption_80020968('s'))
    {
        ivar = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    if (GCL_GetOption_80020968('f'))
    {
        str = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());
    }
    if (GCL_GetOption_80020968('p'))
    {
        demodebug_finish_proc_800AB414 = GCL_GetNextParamValue_80020AD4();
    }
    else
    {
        demodebug_finish_proc_800AB414 = -1;
    }
    tmp = GM_CurrentMap_800AB9B0;
    GM_CurrentMap_800AB9B0 = gBinds_800ABA60;
    if (str)
    {
        demo = DM_ThreadFile_800794E4(flags, (int)str);
    }
    else
    {
        demo = DM_ThreadStream_80079460(flags, ivar);
    }
    GM_CurrentMap_800AB9B0 = tmp;
    if (!demo)
    {
        printf("Error demo thread\n");
    }
    return 0;
}

int GCL_Command_print_8002D0E4(unsigned char *pScript)
{
    int code;
    int value;

    printf("print: ");

    while (pScript)
    {
        pScript = GCL_GetNextValue_8002069C(pScript, &code, &value);
        if (code == GCLCODE_NULL)
            break;
        if (code == GCLCODE_STRING)
            printf("%s ", (char *)value);
        else
            printf("%d ", value);
    }

    printf("\n");
    return 0;
}

int GCL_Command_jimaku_8002D188(unsigned char *pScript)
{
    NewJimaku_800495A8();
    return 0;
}

int GM_InitBinds_8002D1A8(void)
{
    gBinds_800ABA60 = 0;
    gBindsCount_800ABA64 = 0;
    HZD_SetBind_80029A5C(0, gBindsArray_800b58e0, 0);
    return 0;
}

void GM_InitScript_8002D1DC(void)
{
    GM_InitBinds_8002D1A8();
    GCL_AddCommMulti_8001FD2C(&script_commands_8009D68C);
}
