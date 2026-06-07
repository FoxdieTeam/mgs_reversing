#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "charadef.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "linkvar.h"
#include "game/item.h"
#include "game/delay.h"
#include "menu/menuman.h"
#include "kojo/demo.h"
#include "strcode.h"

extern  CAMERA          GM_CameraList[8];
extern  GM_CameraSystemWork       GM_Camera;
extern  HZD_BND        gBindsArray_800b58e0[128];
extern  int             dword_8009F46C;
extern  SVECTOR         svector_8009F478;

/*---------------------------------------------------------------------------*/

STATIC char SECTION(".sbss") dword_800ABA58[8];
STATIC int  SECTION(".sbss") gBinds_800ABA60;
STATIC int  SECTION(".sbss") gBindsCount_800ABA64;

extern char *GM_StageName;
char         SECTION(".sbss") * GM_StageName;

/*---------------------------------------------------------------------------*/

static int GM_Command_light(char *top)
{
    char *light_dir;
    char *light_col;
    char *light_ambient;
    SVECTOR vec;

    if ((light_dir = GCL_GetOption('d')))
    {
        GCL_StrToSV(light_dir, (short *)&vec);
        DG_SetMainLightDir(vec.vx, vec.vy, vec.vz);
    }
    if ((light_col = GCL_GetOption('c')))
    {
        GCL_StrToSV(light_col, (short *)&vec);
        DG_SetMainLightCol(vec.vx, vec.vy, vec.vz);
    }
    if ((light_ambient = GCL_GetOption('a')))
    {
        GCL_StrToSV(light_ambient, (short *)&vec);
        DG_SetAmbient(vec.vx, vec.vy, vec.vz);
    }
    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

/*
proc AGL_FIRST_VF {
#pos -3362 1759 4936
#trg -2475 770 6672
#rot 306 308 0
    camera  set 4  d:CAM_FIX d:CAM_INTERP_LINER d:CAM_CAM_TO_TRG \
            -3362,1759,4936 -2475,770,6672 1
*/

static int GM_Command_camera(char *top)
{
    int     isEnabled, param_p, camera_id;
    SVECTOR vec1, vec2;
    CAMERA *cam;

    isEnabled = GCL_GetOption('e') != 0; // enabled

    if (GCL_GetOption('b')) // bound
    {
        GCL_StrToSV(GCL_NextStr(), (short *)&vec1);
        GCL_StrToSV(GCL_NextStr(), (short *)&vec2);
        GM_CameraSetBound(&vec1, &vec2, isEnabled);
    }

    if (GCL_GetOption('t')) // track
    {
        GM_CameraSetTrack(GCL_GetNextInt());
    }

    if (GCL_GetOption('l')) // limit
    {
        GCL_StrToSV(GCL_NextStr(), (short *)&vec1);
        GCL_StrToSV(GCL_NextStr(), (short *)&vec2);
        GM_CameraSetLimit(&vec1, &vec2, isEnabled);
    }

    if (GCL_GetOption('r')) // rotate
    {
        GCL_StrToSV(GCL_NextStr(), (short *)&vec1);
        GM_CameraSetRotation(&vec1);
    }

    param_p = GCL_GetOption('p') != 0;

    if (GCL_GetOption('s')) // set
    {
        camera_id = GCL_GetNextInt();
        if (camera_id < 8)
        {
            printf("set camera %d\n", camera_id);
            cam = &GM_CameraList[camera_id];

            cam->field_10_param1 = GCL_GetNextInt();
            cam->interp = GCL_GetNextInt();
            cam->type = GCL_GetNextInt();
            cam->pad_type = param_p;

            GCL_StrToSV(GCL_NextStr(), (short *)&cam->pos);
            GCL_StrToSV(GCL_NextStr(), (short *)&cam->trg);

            if (GCL_NextStr())
            {
                cam->trg.pad = GCL_GetNextInt();
            }
            else
            {
                cam->trg.pad = 0;
            }

            GM_CameraSetAlertMask(camera_id, cam->trg.pad);
        }
    }

    if (GCL_GetOption('a'))
    {
        GM_Camera.alert_mask = GCL_GetNextInt();
    }

    if (GCL_GetOption('c'))
    {
        if (GCL_GetNextInt() == 0)
        {
            GM_GameStatus &= ~GAME_FLAG_BIT_07;
        }
        else
        {
            GM_GameStatus |= GAME_FLAG_BIT_07;
        }
    }

    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_map(char *top)
{
    MAP *pMapRecord;
    SVECTOR       colorVec;

    if (GCL_GetOption('d'))
    {
        GM_DefineMap();
    }

    if (GCL_GetOption('s'))
    {
        GM_ReloadMap(1);
        if (!(GM_GameStatus & STATE_DEMO))
        {
            DG_UnDrawFrameCount = 4;
        }
    }

    if (GCL_GetOption('c'))
    {
        GM_ReloadMap(0);

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
        while (GCL_NextStr())
        {
            pMapRecord = GM_FindMap(GCL_GetNextInt());
            if (pMapRecord == 0)
            {
                return GCL_ERROR;
            }
            gBinds_800ABA60 = gBinds_800ABA60 | pMapRecord->index;
        }
    }

    if (GCL_GetOption('p'))
    {
        while (GCL_NextStr())
        {
            GM_AddMap(GCL_GetNextInt());
        }
    }

    if (GCL_GetOption('m'))
    {
        while (GCL_NextStr())
        {
            GM_DelMap(GCL_GetNextInt());
        }
    }

    if (GCL_GetOption('b'))
    {
        GCL_StrToSV(GCL_NextStr(), (short *)&colorVec);
        DG_SetRGB(colorVec.vx, colorVec.vy, colorVec.vz);
    }

    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_mapdef(char *top)
{
    if (!GM_CreateMap())
    {
        return GCL_ERROR;
    }
    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_trap(char *top)
{
    HZD_BND *pBind;
    int         i, arg, code, value;
    int         tmp;

    if (0x7f < gBindsCount_800ABA64)
    {
        printf("binds over\n");
    }

    i = gBindsCount_800ABA64;
    pBind = gBindsArray_800b58e0 + i;

    // Trap id
    arg = GCL_GetNextInt();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    gBindsArray_800b58e0[i].field_4 = arg;

    // Entity id
    arg = GCL_GetNextInt();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    pBind->field_0 = arg;

    // Event condition
    arg = GCL_GetNextInt();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    gBindsArray_800b58e0[i].field_2_param_m = arg; // mask

    gBindsArray_800b58e0[i].field_B_param_e = 0; // exec
    gBindsArray_800b58e0[i].field_8_param_i_c_flags = 0;

    GCL_GetNextValue(GCL_NextStr(), &code, &value);
    gBindsArray_800b58e0[i].command = value;
    gBindsCount_800ABA64++;

    tmp = gBinds_800ABA60;
    gBindsArray_800b58e0[i].map = (short)tmp;
    HZD_SetBind(0, gBindsArray_800b58e0, gBindsCount_800ABA64);

    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_ntrap(char *top)
{
    // int bindIdx;
    HZD_BND *pBind;
    int         flags;
    int         arg;
    int         tmp;

    if (gBindsCount_800ABA64 > 127) // 780 gp
    {
        printf("binds over\n");
    }
    // bindIdx = gBindsCount_800ABA64; // 780 gp
    pBind = gBindsArray_800b58e0 + gBindsCount_800ABA64;
    arg = GCL_GetNextInt();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    pBind->field_4 = arg;
    arg = GCL_GetNextInt();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    pBind->field_0 = arg;
    pBind->field_8_param_i_c_flags = 0; // v0
    flags = 0;                          // still s1
    if (GCL_GetOption('m'))             // mask
    {
        arg = GCL_GetNextInt();
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
        pBind->field_C_param_d = GCL_GetNextInt();

        if (GCL_NextStr())
        {
            pBind->field_E_param_d_or_512 = GCL_GetNextInt();
        }
        else
        {
            pBind->field_E_param_d_or_512 = 0x200;
        }
    }
    if (GCL_GetOption('b')) // button
    {
        flags |= 4;
        pBind->field_A_param_b = GCL_GetNextInt();
    }
    if (GCL_GetOption('s')) // stance
    {
        flags |= 2;
        pBind->field_9_param_s = GCL_GetNextInt();
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
        pBind->time = GCL_GetNextInt();
    }
    if (GCL_GetOption('p')) // proc
    {
        flags |= 0x80;
        pBind->command = GCL_GetNextInt();
    }
    if (GCL_GetOption('e')) // exec
    {
        int code;
        int value;
        if ((flags & 0x80) != 0)
        {
            printf("ntrap:can't set proc and block\n");
        }
        GCL_GetNextValue(GCL_NextStr(), &code, &value);
        pBind->command = value;
    }
    pBind->field_B_param_e = flags;
    gBindsCount_800ABA64++;
    tmp = gBinds_800ABA60;
    pBind->map = (short)tmp;
    printf("BIND %08X\n", tmp);
    HZD_SetBind(0, gBindsArray_800b58e0, gBindsCount_800ABA64);
    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_delay(char *top)
{
    int time = 0;
    int proc = 0;

    if (GCL_GetOption('t')) // time
    {
        time = GCL_GetNextInt();
    }
    if (GCL_GetOption('p')) // proc
    {
        proc = GCL_GetNextInt();
    }
    if (GCL_GetOption('e')) // exec
    {
        int code;
        int value;
        GCL_GetNextValue(GCL_NextStr(), &code, &value);
        proc = value;
    }
    if (GCL_GetOption('g'))
    {
        time = -time;
    }
    if (time && proc)
    {
        GM_DelayedExecCommand(proc, NULL, time);
        return GCL_OK;
    }
    return GCL_ERROR;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_mesg(char *top)
{
    unsigned char *uParm1;
    int            iVar1;
    int            ret;
    short         *pMsgDst;
    GV_MSG         mesg;
    int            count;

    mesg.address = GCL_GetNextInt();
    pMsgDst = &mesg.message[0];
    count = 0;
    while (uParm1 = GCL_NextStr(), uParm1 != 0x0)
    {
        int iVar2 = GCL_StrToInt(uParm1);
        *pMsgDst = (short)iVar2;
        pMsgDst++;
        count++;
    }
    mesg.message_len = count;
    iVar1 = GV_SendMessage(&mesg);
    ret = GCL_OK;
    if (iVar1 < 0)
    {
        ret = GCL_ERROR;
    }
    return ret;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_chara(int argc, char **argv)
{
    int         ret;
    int         name;
    NEWCHARA   *func;

    func = GM_GetChara(GCL_NextStr());
    if (func != NULL)
    {
        name = GCL_StrToInt(GCL_NextStr());
        (*func)(name, gBinds_800ABA60, argc, argv);
        ret = GCL_OK;
    }
    else
    {
        ret = GCL_ERROR;
    }
    return ret;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_start(char *top)
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
        gTotalFrameTime = 0;
    }

    if (GCL_GetOption('d')) // demo (1 to use demo.gcx instead of scenerio.gcx)
    {
        GCL_ChangeSenerioCode(GCL_GetNextInt());
    }

    if (GCL_GetOption('c'))
    {
        GCL_InitClearVar();
        MENU_InitRadioMemory();
        gTotalFrameTime = 0;
    }
    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_load(char *top)
{
    char *scriptStageName;
    SVECTOR vec;

    scriptStageName = GCL_GetString(GCL_NextStr());
    if (*scriptStageName == '\0')
    {
        GM_LoadRequest = 1;
        return GCL_OK;
    }

    if (GCL_GetOption('r'))
    {
        if (!GCL_GetNextInt())
        {
            // Hard restart?
            strcpy(dword_800ABA58, GM_GetArea((int)scriptStageName));
            GV_InitResidentMemory();
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
        return GCL_OK;
    }

    GM_PreviousStageFlag = GM_CurrentStageFlag;
    GM_CurrentStageFlag = GV_StrCode(scriptStageName);

    GM_SetArea(GM_CurrentStageFlag, scriptStageName);

    if (GCL_GetOption('m')) // map
    {
        GM_CurrentMapFlag = GCL_GetNextInt();
    }

    if (GCL_GetOption('p')) // pos
    {
        GCL_StrToSV(GCL_NextStr(), (short *)&vec);
        GM_SnakePosX = vec.vx;
        GM_SnakePosY = vec.vy;
        GM_SnakePosZ = vec.vz;
    }

    if (GCL_GetOption('s'))
    {
        GM_LoadRequest = GCL_GetNextInt();
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

    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_radio(char *top)
{
    int contactFrequency;
    int radioTableCode;

    if (GCL_GetOption('b'))
    {
        while (GCL_NextStr())
        {
            contactFrequency = GCL_GetNextInt();
            radioTableCode = GCL_GetNextInt();
            MENU_SetRadioBaseCall(contactFrequency, radioTableCode);
        }
    }
    if (GCL_GetOption('o'))
    {
        int hash = GCL_GetNextInt();
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
        while (GCL_NextStr())
        {
            contactFrequency = GCL_GetNextInt();
            radioTableCode = GCL_GetNextInt();
            if (hash)
            {
                radioTableCode = -1;
            }
            MENU_SetRadioOverCall(contactFrequency, radioTableCode);
        }
    }
    if (GCL_GetOption('c')) // call
    {
        MENU_RadioCall(GCL_GetNextInt(),  // contactFrequency
                       GCL_GetNextInt(),  // radioTableCode
                       GCL_GetNextInt()); // ring duration ?
    }
    if (GCL_GetOption('p')) // proc
    {
        MENU_SetRadioCallbackProc(GCL_GetNextInt());
    }
    if (GCL_GetOption('r')) // reset
    {
        MENU_ResetCall();
    }
    if (GCL_GetOption('m')) // mesg string (example: "clear")
    {
        MENU_SetRadioMemory(GCL_GetNextInt(), // contactFrequency
                            GCL_GetString(GCL_NextStr())); // string
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
    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_restart(char *top)
{
    int proc_id;

    if (GCL_GetOption('p')) // proc
    {
        proc_id = GCL_GetNextInt();
    }
    else
    {
        proc_id = -1;
    }

    GM_SetLoadCallbackProc(proc_id);

    if (GCL_GetOption('s')) // save
    {
        GM_LoadRequest |= 0x10;
    }

    if (GCL_GetOption('a')) // area
    {
        GM_SetArea(GM_CurrentStageFlag, GM_GetArea(0));
    }

    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_varsave(char *top)
{
    unsigned char *param;

    param = GCL_NextStr();
    if (GCL_GetOption('a'))
    {
        GCL_SaveVar();
        return GCL_OK;
    }
    while (*param)
    {
        if ( GCL_TAG( *param ) != GCL_VAR )
        {
            printf("VARSAVE: NOT VAR !!\n");
        }
        param = GCL_VarSaveBuffer(param);
    }
    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_system(char *top)
{
    static char options[5] = "gcawi";

    int i, proc;

    for (i = 0; i <= (int)sizeof(options); i++)
    {
        if (GCL_GetOption(options[i]))
        {
            proc = GCL_GetNextInt();
            if (!proc)
            {
                printf("SYSTEM:%c:change proc name\n", options[i]);
            }
            GM_SetSystemCallbackProc(i, proc);
        }
    }

    if (GCL_GetOption('s'))
    {
        GM_StageName = GCL_GetString(GCL_NextStr());
    }
    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_demo(char *top)
{
    int   code, cb_proc;
    char  *msg;

    if ( !GCL_GetOption( 's' ) ) // scene ?
    {
        printf( "DEMO:NO CODE\n" );
    }
    code = GCL_GetNextInt();

    if ( GCL_GetOption( 'p' ) ) // proc
    {
        cb_proc = GCL_GetNextInt() | STATE_DEMO;
    }
    else
    {
        cb_proc = 0;
    }

    GM_CurrentMap = gBinds_800ABA60;

    if ( code >= 0 )
    {
        DG_UnDrawFrameCount = 0x7FFF0000;
        GM_GameStatus |= STATE_DEMO;
        GM_DemoStream( code, cb_proc );
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
            msg = GCL_GetString( GCL_NextStr() );
        }
        else
        {
            msg = "DEMO ( no data on CD )";
        }
        NewJimakuStr( msg, cb_proc );
    }
    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_pad(char *top)
{
    if (GCL_GetOption('m'))
    {
        GV_PadMask = GCL_GetNextInt();
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
    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_sound(char *top)
{
    GM_AlertSound();
    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

static unsigned int GM_Command_menu_helper(void)
{
    unsigned int ret = 0;
    int next;

    while (GCL_NextStr())
    {
        next = GCL_GetNextInt();

        if (next > 32)
        {
            return 0;
        }

        ret |= 1 << next;
    }

    return ret;
}

static int GM_Command_menu(char *top)
{
    if (GCL_GetOption('j'))
    {
        if (GCL_GetNextInt() & 1)
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
        if (GCL_GetNextInt() & 1)
        {
            disable_equipment();
        }
        else
        {
            enable_equipment();
        }
    }

    if (GCL_GetOption('m'))
    {
        if (!(GCL_GetNextInt() & 1))
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
        switch (GCL_GetNextInt())
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
        switch (GCL_GetNextInt())
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
        if (GCL_GetNextInt() & 1)
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
        MENU_SetRadarScale(GCL_GetNextInt());
    }

    if (GCL_GetOption('w')) // weapon
    {
        GM_DisableWeapon = GM_Command_menu_helper();
    }

    if (GCL_GetOption('i')) // item
    {
        GM_DisableItem = GM_Command_menu_helper();
    }
    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_rand(char *top)
{
    int param;
    int randValue;

    param = GCL_GetNextInt();
    randValue = rand();
    GM_LastResultFlag = randValue % param;
    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_func(char *top)
{
    SVECTOR     vec;
    CONTROL    *control;
    int         param;
    MAP        *map;

    if (GCL_GetOption('v')) // vector
    {
        GCL_StrToSV(GCL_NextStr(), (short *)&vec);
        GM_LastResultFlag = DG_PointCheckOne((DVECTOR *)&vec);
    }
    if (GCL_GetOption('s'))
    {
        control = GM_PlayerControl;
        GM_SnakePosX = control->mov.vx;
        GM_SnakePosY = control->mov.vy;
        GM_SnakePosZ = control->mov.vz;
        GM_LastResultFlag = control->rot.vy;
    }
    if (GCL_GetOption('a')) // area
    {
        GM_LastResultFlag = GM_AreaHistory(GCL_GetNextInt());
    }
    if (GCL_GetOption('p')) // photo (used for ghosts easter egg)
    {
        param = GCL_GetNextInt();
        GCL_StrToSV(GCL_NextStr(), (short *)&GM_PhotoViewPos);
        if (GCL_GetNextInt() == HASH_LEAVE)
        {
            param = 0;
        }
        GM_Photocode = param;
    }
    if (GCL_GetOption('m')) // map
    {
        map = GM_FindMap(GCL_GetNextInt());
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
        GM_LastResultFlag = GM_StreamStatus();
    }
    if (GCL_GetOption('n'))
    {
        GM_LastResultFlag = dword_8009F46C;
        GM_SnakePosX = svector_8009F478.vx;
        GM_SnakePosY = svector_8009F478.vy;
        GM_SnakePosZ = svector_8009F478.vz;
    }
    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

int demodebug_finish_proc = -1;

static int GM_Command_demodebug(char *top)
{
    int   tmp, demo, flags, ivar;
    char *filename;

    ivar = 0;
    filename = NULL;

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
        ivar = GCL_StrToInt(GCL_NextStr());
    }
    if (GCL_GetOption('f'))
    {
        filename = GCL_GetString(GCL_NextStr());
    }
    if (GCL_GetOption('p'))
    {
        demodebug_finish_proc = GCL_GetNextInt();
    }
    else
    {
        demodebug_finish_proc = -1;
    }
    tmp = GM_CurrentMap;
    GM_CurrentMap = gBinds_800ABA60;
    if (filename)
    {
        demo = DM_ThreadFile(flags, filename);
    }
    else
    {
        demo = DM_ThreadStream(flags, ivar);
    }
    GM_CurrentMap = tmp;
    if (!demo)
    {
        printf("Error demo thread\n");
    }
    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_print(char *top)
{
    int code;
    int value;

    printf("print: ");

    while (top)
    {
        top = GCL_GetNextValue(top, &code, &value);
        if (code == GCL_END)
            break;
        if (code == GCL_STRING)
            printf("%s ", (char *)value);
        else
            printf("%d ", value);
    }

    printf("\n");
    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

static int GM_Command_jimaku(char *top)
{
    NewJimaku();
    return GCL_OK;
}

/*---------------------------------------------------------------------------*/

STATIC GCL_COMMANDLIST Commands[] = {
    { 0x22ff, GM_Command_mesg },        // GV_StrCode("mesg")
    { 0xd4cb, GM_Command_trap },        // GV_StrCode("trap")
    // TODO: Why does this one have a different signature?
    // Putting a breakpoint GM_Command_chara shows it receives
    // trash argc and argv.
    { 0x9906, (GCL_COMMANDFUNC)GM_Command_chara }, // GV_StrCode("chara")
    { 0xc091, GM_Command_map },         // GV_StrCode("map")
    { 0x7d50, GM_Command_mapdef },      // GV_StrCode("mapdef")
    { 0xeee9, GM_Command_camera },      // GV_StrCode("camera")
    { 0x306a, GM_Command_light },       // GV_StrCode("light")
    { 0x9a1f, GM_Command_start },       // GV_StrCode("start")
    { 0xc8bb, GM_Command_load },        // GV_StrCode("load")
    { 0x24e1, GM_Command_radio },       // GV_StrCode("radio")
    { 0xe43c, GM_Command_restart },     // GV_StrCode("restart")
    { 0xa242, GM_Command_demo },        // GV_StrCode("demo")
    { 0xdbab, GM_Command_ntrap },       // GV_StrCode("ntrap")
    { 0x430d, GM_Command_delay },       // GV_StrCode("delay")
    { 0xcc85, GM_Command_pad },         // GV_StrCode("pad")
    { 0x5c9e, GM_Command_varsave },     // GV_StrCode("varsave")
    { 0x4ad9, GM_Command_system },      // GV_StrCode("system")
    { 0x698d, GM_Command_sound },       // GV_StrCode("sound")
    { 0x226d, GM_Command_menu },        // GV_StrCode("menu")
    { 0x925e, GM_Command_rand },        // GV_StrCode("rand")
    { 0xe257, GM_Command_func },        // GV_StrCode("func")
    { 0xa2bf, GM_Command_demodebug },   // GV_StrCode("demodebug")
    { 0xb96e, GM_Command_print },       // GV_StrCode("print")
    { 0xec9d, GM_Command_jimaku },      // GV_StrCode("jimaku")
};

STATIC GCL_COMMANDDEF script_commands = GCL_COMMANDS(Commands);

int GM_ResetScript(void)
{
    gBinds_800ABA60 = 0;
    gBindsCount_800ABA64 = 0;
    HZD_SetBind(0, gBindsArray_800b58e0, 0);
    return 0;
}

void GM_InitScript(void)
{
    GM_ResetScript();
    GCL_AddCommMulti(&script_commands);
}
