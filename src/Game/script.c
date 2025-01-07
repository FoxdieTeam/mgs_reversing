#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "charadef.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/camera.h"
#include "Game/linkvarbuf.h"
#include "Game/item.h"
#include "Game/delay.h"
#include "Menu/menuman.h"
#include "Kojo/demothrd.h"
#include "strcode.h"

extern  CAMERA          GM_CameraList_800B7718[8];
extern  GM_Camera       GM_Camera_800B77E8;



extern  BindStruct      gBindsArray_800b58e0[128];
extern  unsigned int    GM_DisableWeapon_800AB9E4;
extern  int             GM_DisableItem_800ABA28;
extern  CONTROL        *GM_PlayerControl_800AB9F4;
extern  int             GM_Photocode_800ABA04;
extern  int             dword_8009F46C;
extern  SVECTOR         svector_8009F478;
extern  SVECTOR         GM_PhotoViewPos_800ABA48;

char SECTION(".sbss") dword_800ABA58[8];
int  SECTION(".sbss") gBinds_800ABA60;
int  SECTION(".sbss") gBindsCount_800ABA64;

extern char *GM_StageName_800AB918;
char         SECTION(".sbss") * GM_StageName_800AB918;

STATIC int GM_Command_light(unsigned char *);
STATIC int GM_Command_camera(unsigned char *);
STATIC int GM_Command_map(unsigned char *);
STATIC int GM_Command_mapdef(unsigned char *);
STATIC int GM_Command_trap(unsigned char *);
STATIC int GM_Command_ntrap(unsigned char *);
STATIC int GM_Command_delay(unsigned char *);
STATIC int GM_Command_mesg(unsigned char *);
STATIC int GM_Command_chara(int argc, char **argv);
STATIC int GM_Command_start(unsigned char *);
STATIC int GM_Command_load(unsigned char *);
STATIC int GM_Command_radio(unsigned char *);
STATIC int GM_Command_strstatus(unsigned char *);
STATIC int GM_Command_varsave(unsigned char *);
STATIC int GM_Command_system(unsigned char *);
STATIC int GM_Command_demo(unsigned char *);
STATIC int GM_Command_pad(unsigned char *);
STATIC int GM_Command_sound(unsigned char *);
STATIC int GM_Command_menu(unsigned char *);
STATIC int GM_Command_rand(unsigned char *);
STATIC int GM_Command_func(unsigned char *);
STATIC int GM_Command_demodebug(unsigned char *);
STATIC int GM_Command_print(unsigned char *);
STATIC int GM_Command_jimaku(unsigned char *);

STATIC GCL_COMMANDLIST Commands[] = {
    { HASH_CMD_mesg,        GM_Command_mesg         },  // GV_StrCode("mesg")
    { HASH_CMD_trap,        GM_Command_trap         },  // GV_StrCode("trap")
    // TODO: Why does this one have a different signature?
    // Putting a breakpoint GM_Command_chara shows it receives
    // trash argc and argv.
    { HASH_CMD_chara, (GCL_COMMANDFUNC)GM_Command_chara },  // GV_StrCode("chara")
    { HASH_CMD_map,         GM_Command_map          },  // GV_StrCode("map")
    { HASH_CMD_mapdef,      GM_Command_mapdef       },  // GV_StrCode("mapdef")
    { HASH_CMD_camera,      GM_Command_camera       },  // GV_StrCode("camera")
    { HASH_CMD_light,       GM_Command_light        },  // GV_StrCode("light")
    { HASH_CMD_start,       GM_Command_start        },  // GV_StrCode("start")
    { HASH_CMD_load,        GM_Command_load         },  // GV_StrCode("load")
    { HASH_CMD_radio,       GM_Command_radio        },  // GV_StrCode("radio")
    { HASH_CMD_str_status,  GM_Command_strstatus    },  // GV_StrCode("str_status")
    { HASH_CMD_demo,        GM_Command_demo         },  // GV_StrCode("demo")
    { HASH_CMD_ntrap,       GM_Command_ntrap        },  // GV_StrCode("ntrap")
    { HASH_CMD_delay,       GM_Command_delay        },  // GV_StrCode("delay")
    { HASH_CMD_pad,         GM_Command_pad          },  // GV_StrCode("pad")
    { HASH_CMD_varsave,     GM_Command_varsave      },  // GV_StrCode("varsave")
    { HASH_CMD_system,      GM_Command_system       },  // GV_StrCode("system")
    { HASH_CMD_sound,       GM_Command_sound        },  // GV_StrCode("sound")
    { HASH_CMD_menu,        GM_Command_menu         },  // GV_StrCode("menu")
    { HASH_CMD_rand,        GM_Command_rand         },  // GV_StrCode("rand")
    { HASH_CMD_func,        GM_Command_func         },  // GV_StrCode("func")
    { HASH_CMD_demodebug,   GM_Command_demodebug    },  // GV_StrCode("demodebug")
    { HASH_CMD_print,       GM_Command_print        },  // GV_StrCode("print")
    { HASH_CMD_jimaku,      GM_Command_jimaku       }   // GV_StrCode("jimaku")
};

STATIC GCL_COMMANDDEF script_commands = { 0, COUNTOF(Commands), Commands };

STATIC int GM_Command_light(unsigned char *top)
{
    char *light_dir;
    char *light_col;
    char *light_ambient;
    SVECTOR vec;

    if ((light_dir = GCL_GetOption('d')))
    {
        GCL_StrToSV(light_dir, &vec);
        DG_SetMainLightDir(vec.vx, vec.vy, vec.vz);
    }
    if ((light_col = GCL_GetOption('c')))
    {
        GCL_StrToSV(light_col, &vec);
        DG_SetMainLightCol(vec.vx, vec.vy, vec.vz);
    }
    if ((light_ambient = GCL_GetOption('a')))
    {
        GCL_StrToSV(light_ambient, &vec);
        DG_SetAmbient(vec.vx, vec.vy, vec.vz);
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

STATIC int GM_Command_camera(unsigned char *top)
{
    int     isEnabled, param_p, camera_id;
    SVECTOR vec1, vec2;
    CAMERA *cam;

    isEnabled = GCL_GetOption('e') != 0; // enabled

    if (GCL_GetOption('b')) // bound
    {
        GCL_StrToSV(GCL_GetParamResult(), &vec1);
        GCL_StrToSV(GCL_GetParamResult(), &vec2);
        GM_CameraSetBounds_80030888(&vec1, &vec2, isEnabled);
    }

    if (GCL_GetOption('t')) // track
    {
        GM_CameraSetTrack_80030980(GCL_GetNextParamValue());
    }

    if (GCL_GetOption('l')) // limit
    {
        GCL_StrToSV(GCL_GetParamResult(), &vec1);
        GCL_StrToSV(GCL_GetParamResult(), &vec2);
        GM_CameraSetLimits_800308E0(&vec1, &vec2, isEnabled);
    }

    if (GCL_GetOption('r')) // rotate
    {
        GCL_StrToSV(GCL_GetParamResult(), &vec1);
        GM_CameraSetRotation_80030938(&vec1);
    }

    param_p = GCL_GetOption('p') != 0;

    if (GCL_GetOption('s')) // set
    {
        camera_id = GCL_GetNextParamValue();
        if (camera_id < 8)
        {
            printf("set camera %d\n", camera_id);
            cam = &GM_CameraList_800B7718[camera_id];

            cam->field_10_param1 = GCL_GetNextParamValue();
            cam->field_11_param2 = GCL_GetNextParamValue();
            cam->field_12_param3 = GCL_GetNextParamValue();
            cam->field_13_param_p = param_p;

            GCL_StrToSV(GCL_GetParamResult(), &cam->pos);
            GCL_StrToSV(GCL_GetParamResult(), (SVECTOR *)&cam->trg);

            if (GCL_GetParamResult())
            {
                cam->field_0e_alertMask = GCL_GetNextParamValue();
            }
            else
            {
                cam->field_0e_alertMask = 0;
            }

            GM_CameraSetAlertMask_80030850(camera_id, cam->field_0e_alertMask);
        }
    }

    if (GCL_GetOption('a'))
    {
        GM_Camera_800B77E8.field_24_gcl_param_a = GCL_GetNextParamValue();
    }

    if (GCL_GetOption('c'))
    {
        if (GCL_GetNextParamValue() == 0)
        {
            GM_GameStatus &= ~GAME_FLAG_BIT_07;
        }
        else
        {
            GM_GameStatus |= GAME_FLAG_BIT_07;
        }
    }

    return 0;
}

STATIC int GM_Command_map(unsigned char *top)
{
    MAP *pMapRecord;
    SVECTOR       colourVec;

    if (GCL_GetOption('d'))
    {
        Map_ScriptLoadMapBlocks_800312D0();
    }

    if (GCL_GetOption('s'))
    {
        Map_ScriptReloadMaps_80031450(1);
        if (!(GM_GameStatus & STATE_DEMO))
        {
            DG_UnDrawFrameCount = 4;
        }
    }

    if (GCL_GetOption('c'))
    {
        Map_ScriptReloadMaps_80031450(0);

        if (!(GM_GameStatus & STATE_DEMO))
        {
            if (GCL_GetOption('u'))
            {
                DG_UnDrawFrameCount = 4;
            }
            else
            {
                DG_UnDrawFrameCount = 0;
            }
        }
    }

    if (GCL_GetOption('a'))
    {
        gBinds_800ABA60 = 0;
        while (GCL_GetParamResult())
        {
            pMapRecord = Map_FindByNum_80031504(GCL_GetNextParamValue());
            if (pMapRecord == 0)
            {
                return -1;
            }
            gBinds_800ABA60 = gBinds_800ABA60 | pMapRecord->index;
        }
    }

    if (GCL_GetOption('p'))
    {
        while (GCL_GetParamResult())
        {
            GM_AddMap_80031324(GCL_GetNextParamValue());
        }
    }

    if (GCL_GetOption('m'))
    {
        while (GCL_GetParamResult())
        {
            GM_DelMap_800313C0(GCL_GetNextParamValue());
        }
    }

    if (GCL_GetOption('b'))
    {
        GCL_StrToSV(GCL_GetParamResult(), &colourVec);
        DG_SetRGB(colourVec.vx, colourVec.vy, colourVec.vz);
    }

    return 0;
}

STATIC int GM_Command_mapdef(unsigned char *top)
{
    if (!GM_Command_mapdef_impl_800310D0())
    {
        return -1;
    }
    return 0;
}

STATIC int GM_Command_trap(unsigned char *top)
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
    arg = GCL_GetNextParamValue();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    gBindsArray_800b58e0[i].field_4 = arg;

    // Entity id
    arg = GCL_GetNextParamValue();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    pBind->field_0 = arg;

    // Event condition
    arg = GCL_GetNextParamValue();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    gBindsArray_800b58e0[i].field_2_param_m = arg; // mask

    gBindsArray_800b58e0[i].field_B_param_e = 0; // exec
    gBindsArray_800b58e0[i].field_8_param_i_c_flags = 0;

    GCL_GetNextValue(GCL_GetParamResult(), &code, &value);
    gBindsArray_800b58e0[i].field_14_proc_and_block = value;
    gBindsCount_800ABA64++;

    tmp = gBinds_800ABA60;
    gBindsArray_800b58e0[i].field_6 = (short)tmp;
    HZD_SetBind(0, gBindsArray_800b58e0, gBindsCount_800ABA64);

    return 0;
}

STATIC int GM_Command_ntrap(unsigned char *top)
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
    arg = GCL_GetNextParamValue();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    pBind->field_4 = arg;
    arg = GCL_GetNextParamValue();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    pBind->field_0 = arg;
    pBind->field_8_param_i_c_flags = 0; // v0
    flags = 0;                          // still s1
    if (GCL_GetOption('m'))             // mask
    {
        arg = GCL_GetNextParamValue();
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
    if (GCL_GetOption('d')) // dir
    {
        flags |= 1;
        pBind->field_C_param_d = GCL_GetNextParamValue();

        if (GCL_GetParamResult())
        {
            pBind->field_E_param_d_or_512 = GCL_GetNextParamValue();
        }
        else
        {
            pBind->field_E_param_d_or_512 = 0x200;
        }
    }
    if (GCL_GetOption('b')) // button
    {
        flags |= 4;
        pBind->field_A_param_b = GCL_GetNextParamValue();
    }
    if (GCL_GetOption('s')) // stance
    {
        flags |= 2;
        pBind->field_9_param_s = GCL_GetNextParamValue();
    }
    if (GCL_GetOption('r')) // repeat
    {
        flags |= 0x40;
    }
    if (GCL_GetOption('i'))
    {
        pBind->field_8_param_i_c_flags |= 1;
    }
    if (GCL_GetOption('c'))
    {
        pBind->field_8_param_i_c_flags |= 2;
    }
    if (GCL_GetOption('t')) // time
    {
        if ((flags & 0x40) != 0)
        {
            printf("ntrap:can't set every\n");
        }
        pBind->field_10_every = GCL_GetNextParamValue();
    }
    if (GCL_GetOption('p')) // proc
    {
        flags |= 0x80;
        pBind->field_14_proc_and_block = GCL_GetNextParamValue();
    }
    if (GCL_GetOption('e')) // exec
    {
        int code;
        int value;
        if ((flags & 0x80) != 0)
        {
            printf("ntrap:can't set proc and block\n");
        }
        GCL_GetNextValue(GCL_GetParamResult(), &code, &value);
        pBind->field_14_proc_and_block = value;
    }
    pBind->field_B_param_e = flags;
    gBindsCount_800ABA64++;
    tmp = gBinds_800ABA60;
    pBind->field_6 = (short)tmp;
    printf("BIND %08X\n", tmp);
    HZD_SetBind(0, gBindsArray_800b58e0, gBindsCount_800ABA64);
    return 0;
}

STATIC int GM_Command_delay(unsigned char *top)
{
    int time = 0;
    int proc = 0;

    if (GCL_GetOption('t')) // time
    {
        time = GCL_GetNextParamValue();
    }
    if (GCL_GetOption('p')) // proc
    {
        proc = GCL_GetNextParamValue();
    }
    if (GCL_GetOption('e')) // exec
    {
        int code;
        int value;
        GCL_GetNextValue(GCL_GetParamResult(), &code, &value);
        proc = value;
    }
    if (GCL_GetOption('g'))
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

STATIC int GM_Command_mesg(unsigned char *top)
{
    unsigned char *uParm1;
    int            iVar1;
    int            ret;
    short         *pMsgDst;
    GV_MSG         mesg;
    int            count;

    mesg.address = GCL_GetNextParamValue();
    pMsgDst = &mesg.message[0];
    count = 0;
    while (uParm1 = GCL_GetParamResult(), uParm1 != 0x0)
    {
        int iVar2 = GCL_StrToInt(uParm1);
        *pMsgDst = (short)iVar2;
        pMsgDst++;
        count++;
    }
    mesg.message_len = count;
    iVar1 = GV_SendMessage(&mesg);
    ret = 0;
    if (iVar1 < 0)
    {
        ret = -1;
    }
    return ret;
}

STATIC int GM_Command_chara(int argc, char **argv)
{
    int         ret;
    int         charaHash;
    NEWCHARA    pCreateActorFn;

    pCreateActorFn = GM_GetChara(GCL_GetParamResult());
    if (pCreateActorFn)
    {
        charaHash = GCL_StrToInt(GCL_GetParamResult());
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

STATIC int GM_Command_start(unsigned char *top)
{
    if (GCL_GetOption('s'))
    {
        GM_InitReadError();
    }

    if (GCL_GetOption('m')) // menu
    {
        menuman_init_80038954();
        printf("MENU INIT END\n");
    }

    if (GCL_GetOption('f')) // font
    {
        font_load();
    }

    if (GCL_GetOption('v'))
    {
        GCL_InitVar();
        MENU_InitRadioMemory();
        gTotalFrameTime_800AB9E8 = 0;
    }

    if (GCL_GetOption('d')) // demo (1 to use demo.gcx instead of scenerio.gcx)
    {
        GCL_ChangeSenerioCode(GCL_GetNextParamValue());
    }

    if (GCL_GetOption('c'))
    {
        GCL_InitClearVar();
        MENU_InitRadioMemory();
        gTotalFrameTime_800AB9E8 = 0;
    }
    return 0;
}

STATIC int GM_Command_load(unsigned char *top)
{
    char *scriptStageName;
    SVECTOR vec;

    scriptStageName = GCL_ReadString(GCL_GetParamResult());
    if (*scriptStageName == '\0')
    {
        GM_LoadRequest = 1;
        return 0;
    }

    if (GCL_GetOption('r'))
    {
        if (!GCL_GetNextParamValue())
        {
            // Hard restart?
            strcpy(dword_800ABA58, GM_GetArea((int)scriptStageName));
            GV_ResidentHeapReset();
            GV_InitCacheSystem();
            DG_ClearResidentTexture();
            GM_SetArea(GV_StrCode(scriptStageName), scriptStageName);
        }
        else
        {
            // Soft restart?
            scriptStageName = dword_800ABA58;
            GM_SetArea(GM_CurrentStageFlag, scriptStageName);
        }

        GM_LoadRequest = 1;
        return 0;
    }

    GM_PreviousStageFlag = GM_CurrentStageFlag;
    GM_CurrentStageFlag = GV_StrCode(scriptStageName);

    GM_SetArea(GM_CurrentStageFlag, scriptStageName);

    if (GCL_GetOption('m')) // map
    {
        GM_CurrentMapFlag = GCL_GetNextParamValue();
    }

    if (GCL_GetOption('p')) // pos
    {
        GCL_StrToSV(GCL_GetParamResult(), &vec);
        GM_SnakePosX = vec.vx;
        GM_SnakePosY = vec.vy;
        GM_SnakePosZ = vec.vz;
    }

    if (GCL_GetOption('s'))
    {
        GM_LoadRequest = GCL_GetNextParamValue();
        if (GM_LoadRequest)
        {
            GM_LoadRequest |= 0x80;
        }
    }
    else
    {
        GM_LoadRequest = 1;
    }

    if (!GCL_GetOption('n'))
    {
        GM_LoadRequest |= 0x10;
    }

    return 0;
}

STATIC int GM_Command_radio(unsigned char *top)
{
    int contactFrequency;
    int radioTableCode;

    if (GCL_GetOption('b'))
    {
        while (GCL_GetParamResult())
        {
            contactFrequency = GCL_GetNextParamValue();
            radioTableCode = GCL_GetNextParamValue();
            MENU_SetRadioBaseCall(contactFrequency, radioTableCode);
        }
    }
    if (GCL_GetOption('o'))
    {
        int hash = GCL_GetNextParamValue();
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
        while (GCL_GetParamResult())
        {
            contactFrequency = GCL_GetNextParamValue();
            radioTableCode = GCL_GetNextParamValue();
            if (hash)
            {
                radioTableCode = -1;
            }
            MENU_SetRadioOverCall(contactFrequency, radioTableCode);
        }
    }
    if (GCL_GetOption('c')) // call
    {
        MENU_RadioCall(GCL_GetNextParamValue(),  // contactFrequency
                       GCL_GetNextParamValue(),  // radioTableCode
                       GCL_GetNextParamValue()); // ring duration ?
    }
    if (GCL_GetOption('p')) // proc
    {
        MENU_SetRadioCallbackProc(GCL_GetNextParamValue());
    }
    if (GCL_GetOption('r')) // reset
    {
        MENU_ResetCall();
    }
    if (GCL_GetOption('m')) // mesg string (example: "clear")
    {
        MENU_SetRadioMemory(GCL_GetNextParamValue(), // contactFrequency
                            GCL_ReadString(GCL_GetParamResult())); // string
    }
    if (GCL_GetOption('d')) // disable?
    {
        GM_GameStatus |= STATE_RADIO_OFF;
    }
    if (GCL_GetOption('e')) // enable?
    {
        GM_GameStatus &= ~STATE_RADIO_OFF;
    }
    if (GCL_GetOption('a'))
    {
        MENU_ClearRadioTable();
    }
    return 0;
}

STATIC int GM_Command_strstatus(unsigned char *top)
{
    int val;

    if (GCL_GetOption('p'))
    {
        val = GCL_GetNextParamValue();
    }
    else
    {
        val = -1;
    }
    GM_8002B600(val);
    if (GCL_GetOption('s'))
    {
        GM_LoadRequest |= STATE_BEHIND_CAMERA;
    }
    if (GCL_GetOption('a')) // area
    {
        GM_SetArea(GM_CurrentStageFlag, GM_GetArea(0));
    }
    return 0;
}

STATIC int GM_Command_varsave(unsigned char *top)
{
    unsigned char *param;

    param = GCL_GetParamResult();
    if (GCL_GetOption('a'))
    {
        GCL_SaveVar();
        return 0;
    }
    while (*param)
    {
        if (!GCL_IsVariable(*param))
        {
            printf("VARSAVE: NOT VAR !!\n");
        }
        param = GCL_VarSaveBuffer(param);
    }
    return 0;
}

STATIC int GM_Command_system(unsigned char *top)
{
    static char options[5] = "gcawi";

    int i, proc;

    for (i = 0; i <= (int)sizeof(options); i++)
    {
        if (GCL_GetOption(options[i]))
        {
            proc = GCL_GetNextParamValue();
            if (!proc)
            {
                printf("SYSTEM:%c:change proc name\n", options[i]);
            }
            GM_SetSystemCallbackProc(i, proc);
        }
    }

    if (GCL_GetOption('s'))
    {
        GM_StageName_800AB918 = GCL_ReadString(GCL_GetParamResult());
    }
    return 0;
}

STATIC int GM_Command_demo(unsigned char *top)
{
    int   code, cb_proc;
    char  *msg;

    if ( !GCL_GetOption( 's' ) ) // scene ?
    {
        printf( "DEMO:NO CODE\n" );
    }
    code = GCL_GetNextParamValue();

    if ( GCL_GetOption( 'p' ) ) // proc
    {
        cb_proc = GCL_GetNextParamValue() | STATE_DEMO;
    }
    else
    {
        cb_proc = 0;
    }

    GM_CurrentMap_800AB9B0 = gBinds_800ABA60;

    if ( code >= 0 )
    {
        DG_UnDrawFrameCount = 0x7FFF0000;
        GM_GameStatus |= STATE_DEMO;
        GM_Command_demo_helper_80037DD8( code, cb_proc );
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

        if ( GCL_GetOption( 'f' ) ) // file
        {
            msg = GCL_ReadString( GCL_GetParamResult() );
        }
        else
        {
            msg = "DEMO ( no data on CD )";
        }
        NewJimakuStr( msg, cb_proc );
    }
    return 0;
}

STATIC int GM_Command_pad(unsigned char *top)
{
    if (GCL_GetOption('m'))
    {
        GV_PadMask = GCL_GetNextParamValue();
        GM_GameStatus |= STATE_PADMASK;
    }
    if (GCL_GetOption('r')) // resume
    {
        GM_GameStatus |= STATE_PADRELEASE;
    }
    else if (GCL_GetOption('s')) // stop
    {
        GM_GameStatus &= ~(STATE_PADRELEASE | STATE_PADMASK | GAME_FLAG_BIT_08);
    }
    GV_UpdatePadSystem();
    return 0;
}

STATIC int GM_Command_sound(unsigned char *top)
{
    GM_Command_sound_impl();
    return 0;
}

STATIC unsigned int GM_Command_menu_helper(void)
{
    unsigned int ret = 0;
    int next;

    while (GCL_GetParamResult())
    {
        next = GCL_GetNextParamValue();

        if (next > 32)
        {
            return 0;
        }

        ret |= 1 << next;
    }

    return ret;
}

STATIC int GM_Command_menu(unsigned char *top)
{
    if (GCL_GetOption('j'))
    {
        if (GCL_GetNextParamValue() & 1)
        {
            GM_GameStatus |= STATE_JAMMING;
        }
        else
        {
            GM_GameStatus &= ~STATE_JAMMING;
        }
    }

    if (GCL_GetOption('n'))
    {
        if (GCL_GetNextParamValue() & 1)
        {
            item_all_items_and_weapons_unknown2_80033500();
        }
        else
        {
            item_all_items_and_weapons_unknown_80033560();
        }
    }

    if (GCL_GetOption('m'))
    {
        if (!(GCL_GetNextParamValue() & 1))
        {
            GM_GameStatus |= STATE_MENU_OFF;
        }
        else
        {
            GM_GameStatus &= ~STATE_MENU_OFF;
        }
    }

    if (GCL_GetOption('l')) // lifebar
    {
        switch (GCL_GetNextParamValue())
        {
        case 0:
            GM_GameStatus |= STATE_LIFEBAR_OFF;
            break;
        case 1:
        case 3:
            GM_GameStatus &= ~STATE_LIFEBAR_OFF;
            break;
        case 2:
            GM_GameStatus |= STATE_HIDE_LIFEBAR;
            break;
        }
    }

    if (GCL_GetOption('r'))
    {
        switch (GCL_GetNextParamValue())
        {
        case 0:
            GM_GameStatus |= STATE_RADAR_OFF;
            break;
        case 1:
            GM_GameStatus &= ~STATE_RADAR_OFF;
            break;
        case 2:
            GM_GameStatus |= STATE_HIDE_RADAR;
            break;
        case 3:
            GM_GameStatus |= STATE_SHOW_RADAR;
            break;
        }
    }

    if (GCL_GetOption('p'))
    {
        if (GCL_GetNextParamValue() & 1)
        {
            GM_GameStatus |= STATE_PAUSE_OFF;
        }
        else
        {
            GM_GameStatus &= ~STATE_PAUSE_OFF;
        }
    }

    if (GCL_GetOption('s'))
    {
        MENU_SetRadarScale(GCL_GetNextParamValue());
    }

    if (GCL_GetOption('w')) // weapon
    {
        GM_DisableWeapon_800AB9E4 = GM_Command_menu_helper();
    }

    if (GCL_GetOption('i')) // item
    {
        GM_DisableItem_800ABA28 = GM_Command_menu_helper();
    }
    return 0;
}

STATIC int GM_Command_rand(unsigned char *top)
{
    int param;
    int randValue;

    param = GCL_GetNextParamValue();
    randValue = rand();
    GM_LastResultFlag = randValue % param;
    return 0;
}

STATIC int GM_Command_func(unsigned char *top)
{
    SVECTOR     vec;
    CONTROL *unkStruct;
    int         param;
    MAP *map;

    if (GCL_GetOption('v')) // vector
    {
        GCL_StrToSV(GCL_GetParamResult(), &vec);
        GM_LastResultFlag = DG_PointCheckOne((DVECTOR *)&vec);
    }
    if (GCL_GetOption('s'))
    {
        unkStruct = GM_PlayerControl_800AB9F4;
        GM_SnakePosX = unkStruct->mov.vx;
        GM_SnakePosY = unkStruct->mov.vy;
        GM_SnakePosZ = unkStruct->mov.vz;
        GM_LastResultFlag = unkStruct->rot.vy;
    }
    if (GCL_GetOption('a')) // area
    {
        GM_LastResultFlag = GM_AreaHistory(GCL_GetNextParamValue());
    }
    if (GCL_GetOption('p')) // photo (used for ghosts easter egg)
    {
        param = GCL_GetNextParamValue();
        GCL_StrToSV(GCL_GetParamResult(), &GM_PhotoViewPos_800ABA48);
        if (GCL_GetNextParamValue() == HASH_LEAVE)
        {
            param = 0;
        }
        GM_Photocode_800ABA04 = param;
    }
    if (GCL_GetOption('m')) // map
    {
        map = Map_FindByNum_80031504(GCL_GetNextParamValue());
        if (map && map->used)
        {
            GM_LastResultFlag = 1;
        }
        else
        {
            GM_LastResultFlag = 0;
        }
    }
    if (GCL_GetOption('c'))
    {
        GM_LastResultFlag = GM_StreamStatus_80037CD8();
    }
    if (GCL_GetOption('n'))
    {
        GM_LastResultFlag = dword_8009F46C;
        GM_SnakePosX = svector_8009F478.vx;
        GM_SnakePosY = svector_8009F478.vy;
        GM_SnakePosZ = svector_8009F478.vz;
    }
    return 0;
}

int demodebug_finish_proc = -1;

STATIC int GM_Command_demodebug(unsigned char *top)
{
    int   tmp, demo, flags, ivar;
    char *str;

    ivar = 0;
    str = (char *)0;
    flags = GCL_GetOption('e') != 0;
    if (GCL_GetOption('a'))
    {
        flags |= 4;
    }
    if (GCL_GetOption('v'))
    {
        flags |= 2;
    }
    if (GCL_GetOption('s'))
    {
        ivar = GCL_StrToInt(GCL_GetParamResult());
    }
    if (GCL_GetOption('f'))
    {
        str = GCL_ReadString(GCL_GetParamResult());
    }
    if (GCL_GetOption('p'))
    {
        demodebug_finish_proc = GCL_GetNextParamValue();
    }
    else
    {
        demodebug_finish_proc = -1;
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

STATIC int GM_Command_print(unsigned char *top)
{
    int code;
    int value;

    printf("print: ");

    while (top)
    {
        top = GCL_GetNextValue(top, &code, &value);
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

STATIC int GM_Command_jimaku(unsigned char *top)
{
    NewJimaku();
    return 0;
}

int GM_InitBinds(void)
{
    gBinds_800ABA60 = 0;
    gBindsCount_800ABA64 = 0;
    HZD_SetBind(0, gBindsArray_800b58e0, 0);
    return 0;
}

void GM_InitScript(void)
{
    GM_InitBinds();
    GCL_AddCommMulti(&script_commands);
}
