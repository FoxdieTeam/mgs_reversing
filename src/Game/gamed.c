#include "game.h"

#include "psyq.h"
#include <libpad.h>
#include "common.h"
#include "linker.h"

#include "libdg/libdg.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Menu/menuman.h"
#include "memcard/memcard.h"
#include "mts/mts.h"

#include "linkvarbuf.h"
#include "loader.h"
#include "target.h"
#include "homing_target.h"
#include "over.h"
#include "Game/map.h"
#include "camera.h"

extern unsigned short   gSystemCallbackProcs_800B58C0[];
extern int              GM_PlayerAddress_800AB9F0;
int                     GM_PlayerAddress_800AB9F0;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
PlayerStatusFlag        GM_PlayerStatus_800ABA50;
extern short            GM_Magazine_800AB9EC;
short                   GM_Magazine_800AB9EC;
extern short            GM_MagazineMax_800ABA2C;
short                   GM_MagazineMax_800ABA2C;
extern int              GM_AlertLevel_800ABA18;
int                     GM_AlertLevel_800ABA18;
extern int              GM_AlertMax_800AB9E0;
int                     GM_AlertMax_800AB9E0;
extern int              GM_ClaymoreMap_800AB9DC;
int                     GM_ClaymoreMap_800AB9DC;
extern int              GM_AlertMode_800ABA00;
int                     GM_AlertMode_800ABA00;
extern unsigned int     GM_DisableWeapon_800AB9E4;
unsigned int            GM_DisableWeapon_800AB9E4;
extern char            *GM_StageName_800AB918;
char                   *GM_StageName_800AB918;
extern SVECTOR          GM_PlayerPosition_800ABA10;
SVECTOR                 GM_PlayerPosition_800ABA10;
extern int              GM_DisableItem_800ABA28;
int                     GM_DisableItem_800ABA28;
extern short            GM_WeaponChanged_800AB9D8;
short                   GM_WeaponChanged_800AB9D8;
extern short            GM_O2_800ABA34;
short                   GM_O2_800ABA34;
extern int              GM_NoisePower_800ABA24;
int                     GM_NoisePower_800ABA24;
extern int              GM_NoiseLength_800ABA30;
int                     GM_NoiseLength_800ABA30;

int GM_GameStatus = 0;
int GM_LoadRequest = 0;
int GM_GameOverTimer = 0;

SVECTOR *GM_lpsvectWind = NULL;

TPlayerActFunction GM_lpfnPlayerActControl = NULL;
TPlayerActFunction GM_lpfnPlayerActObject2 = NULL;

short GM_uBombHoming = 0;
short GM_uTenageMotion = -1;

TBombFunction  GM_lpfnBombHoming = NULL;
TBombFunction2 GM_lpfnBombBound = NULL;
TBombFunction3 GM_lpfnBombExplosion = NULL;

int GM_PadResetDisable = 0;

extern int GM_PadVibration2_800ABA54;
int        SECTION(".sbss") GM_PadVibration2_800ABA54;

extern int GM_PadVibration_800ABA3C;
int        SECTION(".sbss") GM_PadVibration_800ABA3C;

extern int gTotalFrameTime_800AB9E8;
int        SECTION(".sbss") gTotalFrameTime_800AB9E8;

extern int GM_LoadComplete_800ABA38;
int        SECTION(".sbss") GM_LoadComplete_800ABA38;

extern GV_PAD *GM_CurrentPadData_800AB91C;
GV_PAD        *SECTION(".sbss") GM_CurrentPadData_800AB91C;

extern int dword_800AB9D0;
int        SECTION(".sbss") dword_800AB9D0;

extern CONTROL *GM_PlayerControl_800AB9F4;
CONTROL        *SECTION(".sbss") GM_PlayerControl_800AB9F4;

extern int          str_mute_fg_800BEFF0;
extern unsigned int str_status_800BF16C;
extern int          dword_800BF1A8;
extern int          dword_800BF270;
extern int          str_off_idx_800BF264;
extern char         exe_name_800B5860[32];
extern char        *MGS_DiskName[3]; /* in main.c */
extern int          gDiskNum_800ACBF0;
extern int          GV_PassageTime_800AB924;
extern int          DG_UnDrawFrameCount;
extern int          gSaveCache_800B5294;
extern int          GV_PauseLevel_800AB928;
extern GV_PAD       GV_PadData_800B05C0[4];

extern DG_TEX gMenuTextureRec_800B58B0;

extern GameWork GameWork_800B5880;

extern unsigned char *GV_ResidentMemoryBottom_800AB940;

extern unsigned char *gOverlayBase_800AB9C8;

extern int gOverlayBinSize_800B5290;

extern void MENU_AreaNameWrite_80049534(char *areaName);

void GM_InitGameSystem(void)
{
    int i;

    GM_PlayerAddress_800AB9F0 = -1;
    GM_GameStatus = 0;
    GM_GameOverTimer = 0;
    GM_PlayerStatus_800ABA50 = 0;
    GM_NoisePower_800ABA24 = 0;
    GM_NoiseLength_800ABA30 = 0;
    GM_ClaymoreMap_800AB9DC = 0;
    GM_AlertLevel_800ABA18 = 0;
    GM_AlertMax_800AB9E0 = 0;
    GM_AlertMode_800ABA00 = 0;
    GM_WeaponChanged_800AB9D8 = 0;
    GM_Magazine_800AB9EC = 0;
    GM_MagazineMax_800ABA2C = 0;
    GM_DisableItem_800ABA28 = 0;
    GM_DisableWeapon_800AB9E4 = 0;
    GM_O2_800ABA34 = 1024;
    GM_StageName_800AB918 = 0;
    GM_EnvironTemp = 0;
    GM_PlayerPosition_800ABA10.vx = GM_SnakePosX;
    GM_PlayerPosition_800ABA10.vy = GM_SnakePosY;
    GM_PlayerPosition_800ABA10.vz = GM_SnakePosZ;

    for (i = 5; i >= 0; i--)
    {
        gSystemCallbackProcs_800B58C0[i] = 0;
    }
}

void GM_InitNoise(void)
{
    int length;
    int max;

    // isn't this one of the inlines?
    length = GM_NoiseLength_800ABA30;
    if (GM_NoiseLength_800ABA30 > 0)
    {
        length = GM_NoiseLength_800ABA30 - 1;
    }
    if (!length)
    {
        GM_NoisePower_800ABA24 = 0;
    }

    max = GM_AlertMax_800AB9E0;
    GM_NoiseLength_800ABA30 = length;
    GM_AlertMax_800AB9E0 = 0;
    GM_AlertLevel_800ABA18 = max;
}

// Guessed function name
void GM_ResetSystem(void)
{
    menuman_Reset_800389A8();
    GV_ResetSystem();
    DG_ResetPipeline();
    GCL_ResetSystem();
}

void GM_ResetMemory(void)
{
    DG_TextureCacheInit();
    GV_ResetMemory();
    GM_ResetChara();
}

// GM_InitStage?
void GM_CreateLoader(void)
{
    char *stageName = "init";
    if (GM_CurrentStageFlag != 0)
    {
        stageName = GM_GetArea(GM_CurrentStageFlag);
    }
    Loader_Init_8002E460(stageName);
}

void GM_HidePauseScreen(void)
{
    GV_PauseLevel_800AB928 &= ~2;
    GM_Sound_80032C48(0x01ffff02, 0);
    MENU_JimakuClear_80049518();
    GM_GameStatus &= ~GAME_FLAG_BIT_08;
}

void GM_ShowPauseScreen(void)
{
    char *areaName;

    areaName = "";
    GV_PauseLevel_800AB928 |= 2;
    GM_Sound_80032C48(0x01ffff01, 0);
    if (GM_StageName_800AB918)
    {
        areaName = GM_StageName_800AB918;
    }
    MENU_AreaNameWrite_80049534(areaName);
}

void GM_TogglePauseScreen(void)
{
    int var1;
    int var2;
    int ret;

    var1 = GV_PauseLevel_800AB928;
    var2 = var1 & ~2;
    ret = var2; // Why this waste?
    // It should always be true because the only caller
    // does the same check before calling this function.
    if (var2 == 0)
    {
        if ((var1 & 2) == 0)
        {
            GM_ShowPauseScreen();
            return;
        }
        GM_HidePauseScreen();
    }
}

STATIC void GM_ActInit(GameWork *work)
{
    GM_Reset_helper3_80030760();
    GM_InitWhereSystem();
    GM_ResetTargets();
    GM_ResetHomingTargets();
    GM_InitBinds();
    GM_InitGameSystem();
    GM_AlertModeInit_8002EAA8();
}

void GM_InitReadError(void)
{
    DG_TEX *tex;

    tex = DG_GetTexture(PCC_READ);
    gMenuTextureRec_800B58B0 = *tex;
    gMenuTextureRec_800B58B0.id = 0;
}

STATIC void DrawReadError(void)
{
    int      u_off;
    DR_TPAGE tpage;
    SPRT     sprt;
    TILE     tile;

    u_off = 16 * gMenuTextureRec_800B58B0.id;
    gMenuTextureRec_800B58B0.id = (gMenuTextureRec_800B58B0.id + 1) % 6;

    DG_DisableClipping();

    setDrawTPage(&tpage, 1, 1, gMenuTextureRec_800B58B0.tpage);
    DrawPrim(&tpage);

    LSTORE(0, &tile.r0);
    setTile(&tile);
    tile.x0 = 287;
    tile.y0 = 15;
    tile.h = 18;
    tile.w = 18;
    DrawPrim(&tile);

    LSTORE(0x80808080, &sprt.r0);
    setSprt(&sprt);
    sprt.w = 16;
    sprt.h = 16;
    sprt.x0 = 288;
    sprt.y0 = 16;
    sprt.u0 = gMenuTextureRec_800B58B0.off_x + u_off;
    sprt.v0 = gMenuTextureRec_800B58B0.off_y;
    sprt.clut = gMenuTextureRec_800B58B0.clut;
    DrawPrim(&sprt);
}

STATIC void GM_Act(GameWork *work)
{
    int load_request;
    int status;

    unsigned short pad = mts_read_pad(1);

    if (mts_get_pad_vibration_type(1) == 1)
    {
        GM_GameStatusFlag &= ~0x400;
    }
    else
    {
        GM_GameStatusFlag |= 0x400;
    }

    if ((GM_GameStatusFlag & (0x2000 | 0x400)) == 0)
    {
        int vibration2;
        if (GM_PadVibration_800ABA3C != 0)
        {
            mts_set_pad_vibration(1, 10);
        }
        else
        {
            mts_set_pad_vibration(1, 0);
        }

        vibration2 = GM_PadVibration2_800ABA54;
        if (vibration2 > 255)
        {
            vibration2 = 255;
        }
        mts_set_pad_vibration2(1, vibration2);
    }

    GM_PadVibration2_800ABA54 = 0;
    GM_PadVibration_800ABA3C = 0;

    if ((GV_PauseLevel_800AB928 & 8) != 0)
    {
        if (!str_mute_fg_800BEFF0 && CDBIOS_TaskState() != 3)
        {
            GV_PauseLevel_800AB928 &= ~8;
        }
        else
        {
            DrawReadError();
        }
    }
    else if (str_mute_fg_800BEFF0 || CDBIOS_TaskState() == 3)
    {
        GV_PauseLevel_800AB928 |= 8;
    }

    if ((GV_PauseLevel_800AB928 & 2) == 0)
    {
        int minutes;
        gTotalFrameTime_800AB9E8 += GV_PassageTime_800AB924;
        minutes = gTotalFrameTime_800AB9E8 / 60;
        GM_TotalHours = minutes / 3600;
        GM_TotalSeconds = minutes % 3600;
    }

    status = work->status;
    if (status != WAIT_LOAD)
    {
        if (status != WORKING)
        {
            return;
        }
    }
    else
    {
        if (GM_LoadComplete_800ABA38 == 0)
        {
            return;
        }

        GM_LoadComplete_800ABA38 = 1;

        if ((GM_LoadRequest & 0x80) != 0)
        {
            DG_UnDrawFrameCount = 0;
        }

        if (gSaveCache_800B5294 != 0)
        {
            GV_ResidentFileCache();
            DG_SaveTexureCacheToResidentMem();
        }

        GM_ResetMapObjs_800310A0();
        camera_init_800306A0();
        DG_StorePalette();
        GM_Act_helper2_8002E8D4();

        if ((GM_LoadRequest & 0x10) != 0)
        {
            GCL_SaveVar();
        }

        printf("exec scenario\n");
        load_request = GM_LoadRequest;
        GM_LoadRequest = 0;

        if ((load_request & 0x20) != 0)
        {
            GCL_ExecProc((unsigned int)load_request >> 16, 0);
        }
        else
        {
            GCL_ExecScript();
        }

        printf("end scenario\n");
        MENU_ResetTexture_80038A00();
        GM_AlertModeReset_8002EAB8();
        GM_SoundStart_8002E640();
        work->status = WORKING;

        return;
    }

    if ((work->field_24 <= 0))
    {
        if (GM_GameOverTimer != 0)
        {
            if (GM_GameOverTimer > 0)
            {
                if ((GM_GameOverTimer == status))
                {
                    if (GM_StreamStatus_80037CD8() == -1)
                    {
                        if (over_init_800376F8(1))
                        {
                            GM_GameOverTimer = -1;
                        }
                        else
                        {
                            GV_DestroyActorSystem(4);
                        }
                    }
                    else if (GM_StreamStatus_80037CD8() == status)
                    {
                        GM_StreamPlayStop_80037D64();
                    }
                }
                else
                {
                    GM_GameOverTimer--;
                }
            }
        }
        else
        {
            if (GM_LoadRequest != 0 && (GV_PauseLevel_800AB928 & 2) == 0)
            {
                if ((GM_LoadRequest & 0x80) != 0)
                {
                    DG_UnDrawFrameCount = 0x7fff0000;
                }

                GV_DestroyActorSystem(4);
                GV_PauseLevel_800AB928 &= ~8;
                GM_FreeMapObjs_80031028();
                GM_StreamPlayStop_80037D64();
                work->field_24 = 3;
                GM_GameStatus |= STATE_PADRELEASE | STATE_ALL_OFF;

                return;
            }

            if (GV_PauseLevel_800AB928 == 0)
            {
                GM_AlertAct_8002E91C();
            }

            if ((GM_GameStatus & (STATE_VOX_STREAM | STATE_PAUSE_OFF | STATE_PADMASK | STATE_PADRELEASE |
                                           STATE_PADDEMO | STATE_DEMO)) == 0)
            {
                if (((GV_PauseLevel_800AB928 & ~2) == 0) && ((GM_CurrentPadData_800AB91C->press & PAD_START) != 0))
                {
                    GM_TogglePauseScreen();
                }
            }
            else if ((GV_PauseLevel_800AB928 & 2) != 0)
            {
                GM_HidePauseScreen();
            }

            Map_80030FA4();
        }

        // 0x90f: PAD_L1 | PAD_L2 | PAD_R1 | PAD_R2 | PAD_START | PAD_SELECT
        if (((pad & 0x90f) == 0x90f) && (GM_PadResetDisable == 0))
        {
            if (--dword_800AB9D0 < 0)
            {
                sprintf(exe_name_800B5860, "cdrom:\\MGS\\%s;1", MGS_DiskName[gDiskNum_800ACBF0]);
                EnterCriticalSection();
                SetDispMask(0);
                PadStopCom();
                SpuInit();
                CdInit();
                SpuSetIRQ(0);
                mts_shutdown();
                memcard_exit();
                ResetGraph(3);
                StopCallback();
                SetConf(0x10, 4, 0x801FFFF0); // note: hardcoded addresses
                ResetCallback();
                StopCallback();
                _96_remove();
                _96_init();

                do {
                    printf("load %s\n", exe_name_800B5860);
                    LoadExec(exe_name_800B5860, 0x801FFF00, 0);
                } while (1);
            }
        }
        else
        {
            dword_800AB9D0 = 0x5a;
        }

        if ((GM_GameStatus < 0) && ((GM_CurrentPadData_800AB91C[2].press & (PAD_START | PAD_CROSS)) != 0))
        {
            GM_StreamPlayStop_80037D64();
        }

        if ((mts_read_pad(2) & PAD_CIRCLE) != 0)
        {
            char         spu_status[24];
            char         spu_stat;
            int          i;
            unsigned int spu_key;

            SpuGetAllKeysStatus(spu_status);
            spu_key = 0;
            for (i = 0; i < 24; ++i)
            {
                spu_key *= 2;
                spu_stat = spu_status[i];
                spu_key |= spu_stat & 1;
            }

            printf("str_status %d irq %x %X %X\n", str_status_800BF16C, dword_800BF1A8, dword_800BF270,
                   str_off_idx_800BF264);
            printf("key %08X\n", spu_key);
        }

        if (GV_PauseLevel_800AB928 == 0)
        {
            GM_InitNoise();
        }
    }
    else
    {
        GV_PauseLevel_800AB928 &= ~8;

        if ((--work->field_24 <= 0))
        {
            if (GM_StreamStatus_80037CD8() == -1)
            {
                if ((GV_PauseLevel_800AB928 & 5) == 0)
                {
                    work->status = 0;
                    work->field_24 = 0;
                    GM_DieMap_80030FD0();
                    GM_ResetSystem();
                    GM_ActInit(work);

                    if ((GM_LoadRequest & 0x40) == 0)
                    {
                        GM_ResetMemory();
                        GM_CreateLoader();
                    }

                    return;
                }
                else if ((GM_LoadRequest & 0x80) != 0)
                {
                    DG_UnDrawFrameCount = 0;
                }
            }

            work->field_24 = status;
        }

        if (GV_PauseLevel_800AB928 == 0)
        {
            GM_InitNoise();
        }
    }
}

void GM_SetSystemCallbackProc(int index, int proc)
{
    gSystemCallbackProcs_800B58C0[index] = proc;
}

void GM_CallSystemCallbackProc(int id, int arg)
{
    int proc;

    if (id == 4 && GM_PlayerControl_800AB9F4 != NULL)
    {
        HZD_ReExecEvent_8002A1F4(GM_PlayerControl_800AB9F4->map->hzd,
                                 &GM_PlayerControl_800AB9F4->field_10_events, 0x301);
    }

    proc = gSystemCallbackProcs_800B58C0[id];
    if (proc != 0)
    {
        GCL_ARGS args;
        long     local_18[2];

        args.argc = 1;
        args.argv = local_18;
        local_18[0] = arg;
        GCL_ForceExecProc(proc, &args);
    }
}

void sub_8002B600(int param_1)
{
    if (param_1 == -1)
    {
        GM_LoadRequest = 0xc0;
        return;
    }
    GM_LoadRequest = param_1 << 16 | 0xe0;
    return;
}

void GM_ContinueStart(void)
{
    int total_continues; // $s2
    int current_stage;   // $s1

    GM_CallSystemCallbackProc(1, 0);
    total_continues = GM_TotalContinues;
    current_stage = GM_CurrentStageFlag;
    GCL_RestoreVar();
    if (GM_CurrentStageFlag != current_stage)
    {
        GM_LoadRequest = 1;
    }
    else
    {
        sub_8002B600(-1);
    }

    GM_TotalContinues = total_continues + 1;

    // Set the bomb to no less than 10 seconds to prevent instant death
    // note: casting needed to produce sltiu and lhu vs lh
    if ((unsigned int)(unsigned short)GM_TimerBombFlag - 1 < 9)
    {
        GM_TimerBombFlag = 10;
    }
}

void GM_GameOver(void)
{
    if (!GM_GameOverTimer)
    {
        GM_GameOverTimer = 4;
        GM_CallSystemCallbackProc(0, 0);
        GM_GameStatus |= (STATE_RADIO_OFF | STATE_PAUSE_OFF | STATE_MENU_OFF);
    }
}

/**
 *  @brief      Overlay binary initialization handler
 *
 *  Copies the overlay from its temporary buffer to the overlay base address.
 *  The overlay's filename will always be xxx.bin (where "xxx" is the name of
 *  the current stage).
 *
 *  @param[in]  buf     pointer to cached overlay buffer
 *  @param[in]  id      strcode of the overlay's basename
 *
 *  @retval     1       on success
 *  @retval     <= 0    on failure (but this can't happen)
 */
STATIC int GM_LoadInitBin(unsigned char *buf, int id)
{
#ifdef DEV_EXE
    return 1; // the overlay is embedded in the executable in dev variant
#endif

    if ((gOverlayBase_800AB9C8 + gOverlayBinSize_800B5290) > GV_ResidentMemoryBottom_800AB940)
    {
        printf("TOO LARGE STAGE BINARY!!\n");
    }

    memcpy(gOverlayBase_800AB9C8, buf, gOverlayBinSize_800B5290);
    return 1;
}

void GM_StartDaemon(void)
{
    gTotalFrameTime_800AB9E8 = 0;
    GM_GameOverTimer = 0;
    GM_LoadRequest = 0;
    GM_LoadComplete_800ABA38 = 0;
    MENU_StartDeamon_80038A20();
    GM_InitArea();
    GM_InitChara();
    GM_InitScript();
    GV_SetLoader('b', GM_LoadInitBin);
    GM_ClearWeaponAndItem();
    GV_InitActor(1, &GameWork_800B5880.actor, 0);
    GV_SetNamedActor(&GameWork_800B5880.actor, (TActorFunction)GM_Act, 0, "gamed.c");
    GM_ResetSystem();
    GM_ActInit(&GameWork_800B5880);
    GM_ResetMemory();
    GM_CurrentPadData_800AB91C = GV_PadData_800B05C0;
    GM_CurrentDiskFlag = gDiskNum_800ACBF0 + 1;
    GV_SaveResidentTop();
    GameWork_800B5880.status = 0;
    GameWork_800B5880.field_24 = 0;
    GM_CreateLoader();
}
