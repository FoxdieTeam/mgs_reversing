#define __GAMED_SBSS__
#include "game.h"

#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libapi.h>
#include <libcd.h>
#include <libpad.h>
#include <libspu.h>

#include "common.h"
#include "mts/mts.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"
#include "memcard/memcard.h"

#include "linkvar.h"
#include "game/loader.h"
#include "game/target.h"
#include "game/homing.h"
#include "game/over.h"
#include "game/map.h"
#include "game/camera.h"
#include "menu/menuman.h"

/*---------------------------------------------------------------------------*/

//both below are defined in gvd.c
extern char            *GM_StageName;
char                   *GM_StageName;

extern GV_PAD                  *GM_CurrentPadData;
GV_PAD        *SECTION(".sbss") GM_CurrentPadData;

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

int GM_PadResetDisable = FALSE;

int          SECTION(".sbss") dword_800AB9CC;
int          SECTION(".sbss") dword_800AB9D0;
int          SECTION(".sbss") dword_800AB9D4;
short        SECTION(".sbss") GM_WeaponChanged;
short        SECTION(".sbss") word_800AB9DA;
int          SECTION(".sbss") GM_ClaymoreMap;
int          SECTION(".sbss") GM_AlertMax;
unsigned int SECTION(".sbss") GM_DisableWeapon;
int          SECTION(".sbss") gTotalFrameTime;
short        SECTION(".sbss") GM_Magazine;
int          SECTION(".sbss") GM_PlayerAddress;
CONTROL     *SECTION(".sbss") GM_PlayerControl;
SVECTOR      SECTION(".sbss") GM_NoisePosition;
int          SECTION(".sbss") GM_AlertMode;
int          SECTION(".sbss") GM_Photocode;
int          SECTION(".sbss") dword_800ABA08;
int          SECTION(".sbss") GM_PlayerMap;
SVECTOR      SECTION(".sbss") GM_PlayerPosition;
int          SECTION(".sbss") GM_AlertLevel;
int          SECTION(".sbss") dword_800ABA1C;
OBJECT      *SECTION(".sbss") GM_PlayerBody;
int          SECTION(".sbss") GM_NoisePower;
int          SECTION(".sbss") GM_DisableItem;
short        SECTION(".sbss") GM_MagazineMax;
int          SECTION(".sbss") GM_NoiseLength;
short        SECTION(".sbss") GM_O2;
short        SECTION(".sbss") GM_PDA_ClearRank;
int          SECTION(".sbss") GM_LoadComplete;
int          SECTION(".sbss") GM_PadVibration;
int          SECTION(".sbss") GM_PlayerAction;
STATIC int   SECTION(".sbss") dword_800ABA44;
SVECTOR      SECTION(".sbss") GM_PhotoViewPos;

/**
 * Some known settings via GM_SetPlayerStatusFlag():
 * |= 0x20008000 if Snake dies from sna_check_dead_8004E384() and sna_anim_dying_80055524().
 * |= 0x20 if Snake crouches from sna_anim_crouch_800527DC().
 * |= 0x40 if Snake goes prone from  sna_anim_prone_begin_80053BE8() and sna_anim_prone_idle_800528BC().
 * |= 0x10 if Snake runs from sna_anim_run_begin_80053B88(), sna_anim_run_8005292C(),
 * sna_anim_rungun_begin_80056BDC() and sna_anim_rungun_80056C3C().
 * |= 0x10 if Snake moves while prone from sna_anim_prone_move_800529C0().
 * |= 0x10 if Snake moves while in a box from sna_anim_box_run_8005544C().
 * |= 0x10000 if Snake pushes up against a wall from sna_anim_wall_idle_and_c4_80052A5C().
 * |= 0x10010 if Snake moves while up against a wall from sna_anim_wall_move_80052BA8().
 * |= 0x10020 if Snake crouches while up against a wall from sna_anim_wall_crouch_80052CCC().
 * |= 0x10 from sna_anim_choke_drag_80059054().
 */
PlayerStatusFlag SECTION(".sbss") GM_PlayerStatus;
int              SECTION(".sbss") GM_PadVibration2;

extern unsigned short   gSystemCallbackProcs_800B58C0[];
extern int          str_mute_fg;
extern unsigned int str_status;
extern int          dword_800BF1A8;
extern int          dword_800BF270;
extern int          str_off_idx;
extern char         exe_name_800B5860[32];
extern char        *MGS_DiskName[3]; /* in main.c */
extern int          FS_DiskNum_800ACBF0;
extern int          FS_ResidentCacheDirty;
extern GV_PAD       GV_PadData_800B05C0[4];

extern DG_TEX gMenuTextureRec_800B58B0;

extern GameWork GameWork_800B5880;

extern unsigned char *GV_ResidentMemoryBottom;

extern void *StageCharacterEntries;
extern int gOverlayBinSize_800B5290;

/*---------------------------------------------------------------------------*/

static void GM_ClearWeaponAndItem(void)
{
    GM_CurrentWeaponId = WP_None;
    GM_CurrentItemId = IT_None;
}

static void GM_InitGameSystem(void)
{
    int i;

    GM_PlayerAddress = -1;
    GM_GameStatus = 0;
    GM_GameOverTimer = 0;
    GM_PlayerStatus = 0;
    GM_NoisePower = 0;
    GM_NoiseLength = 0;
    GM_ClaymoreMap = 0;
    GM_AlertLevel = 0;
    GM_AlertMax = 0;
    GM_AlertMode = 0;
    GM_WeaponChanged = 0;
    GM_Magazine = 0;
    GM_MagazineMax = 0;
    GM_DisableItem = 0;
    GM_DisableWeapon = 0;
    GM_O2 = 1024;
    GM_StageName = NULL;
    GM_EnvironTemp = 0;
    GM_PlayerPosition.vx = GM_SnakePosX;
    GM_PlayerPosition.vy = GM_SnakePosY;
    GM_PlayerPosition.vz = GM_SnakePosZ;

    for (i = 5; i >= 0; i--)
    {
        gSystemCallbackProcs_800B58C0[i] = 0;
    }
}

static void GM_InitNoise(void)
{
    int length;
    int max;

    // isn't this one of the inlines?
    length = GM_NoiseLength;
    if (GM_NoiseLength > 0)
    {
        length = GM_NoiseLength - 1;
    }
    if (!length)
    {
        GM_NoisePower = 0;
    }

    max = GM_AlertMax;
    GM_NoiseLength = length;
    GM_AlertMax = 0;
    GM_AlertLevel = max;
}

static void GM_ResetSystem(void)
{
    menuman_Reset();
    GV_ResetSystem();
    DG_ResetPipeline();
    GCL_ResetSystem();
}

static void GM_ResetMemory(void)
{
    DG_ResetTextureCache();
    GV_ResetMemory();
    GM_ResetChara();
}

// GM_InitStage?
static void GM_CreateLoader(void)
{
    char *stage = "init";
    if (GM_CurrentStageFlag != 0)
    {
        stage = GM_GetArea(GM_CurrentStageFlag);
    }
    NewLoader(stage);
}

static void GM_HidePauseScreen(void)
{
    GV_PauseLevel &= ~2;
    GM_SetSound(0x01ffff02, SD_ASYNC);
    MENU_JimakuClear();
    GM_GameStatus &= ~GAME_FLAG_BIT_08;
}

static void GM_ShowPauseScreen(void)
{
    char *areaName;

    areaName = "";
    GV_PauseLevel |= 2;
    GM_SetSound(0x01ffff01, SD_ASYNC);
    if (GM_StageName)
    {
        areaName = GM_StageName;
    }
    MENU_AreaNameWrite(areaName);
}

static void GM_TogglePauseScreen(void)
{
    int var1;
    int var2;
    int ret;

    var1 = GV_PauseLevel;
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

static void GM_ActInit(GameWork *work)
{
    GM_Reset_helper3_80030760();
    GM_InitWhereSystem();
    GM_ResetTargets();
    GM_ResetHomingTargets();
    GM_InitBinds();
    GM_InitGameSystem();
    GM_AlertModeInit();
}

/*---------------------------------------------------------------------------*/

#define PCC_READ    0xa0be  // GV_StrCode("read")

void GM_InitReadError(void)
{
    DG_TEX *tex;

    tex = DG_GetTexture(PCC_READ);
    gMenuTextureRec_800B58B0 = *tex;
    gMenuTextureRec_800B58B0.id = 0;
}

void DrawReadError(void)
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

/*---------------------------------------------------------------------------*/

static void Act(GameWork *work)
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
        if (GM_PadVibration != 0)
        {
            mts_set_pad_vibration(1, 10);
        }
        else
        {
            mts_set_pad_vibration(1, 0);
        }

        vibration2 = GM_PadVibration2;
        if (vibration2 > 255)
        {
            vibration2 = 255;
        }
        mts_set_pad_vibration2(1, vibration2);
    }

    GM_PadVibration2 = 0;
    GM_PadVibration = 0;

    if ((GV_PauseLevel & 8) != 0)
    {
        if (!str_mute_fg && CDBIOS_TaskState() != 3)
        {
            GV_PauseLevel &= ~8;
        }
        else
        {
            DrawReadError();
        }
    }
    else if (str_mute_fg || CDBIOS_TaskState() == 3)
    {
        GV_PauseLevel |= 8;
    }

    if ((GV_PauseLevel & 2) == 0)
    {
        int minutes;
        gTotalFrameTime += GV_PassageTime;
        minutes = gTotalFrameTime / 60;
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
        if (GM_LoadComplete == 0)
        {
            return;
        }

        GM_LoadComplete = 1;

        if ((GM_LoadRequest & 0x80) != 0)
        {
            DG_UnDrawFrameCount = 0;
        }

        if (FS_ResidentCacheDirty)
        {
            GV_SaveResidentFileCache();
            DG_SaveResidentTextureCache();
        }

        GM_ResetMap();
        camera_init_800306A0();
        DG_StorePalette();
        GM_Act_helper2();

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
        MENU_ResetTexture();
        GM_AlertModeReset();
        GM_SoundStart();
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
                    if (GM_StreamStatus() == -1)
                    {
                        if (NewGameOver(TRUE))
                        {
                            GM_GameOverTimer = -1;
                        }
                        else
                        {
                            GV_DestroyActorSystem(GV_ACTOR_LEVEL4);
                        }
                    }
                    else if (GM_StreamStatus() == status)
                    {
                        GM_StreamPlayStop();
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
            if (GM_LoadRequest != 0 && (GV_PauseLevel & 2) == 0)
            {
                if ((GM_LoadRequest & 0x80) != 0)
                {
                    DG_UnDrawFrameCount = 0x7fff0000;
                }

                GV_DestroyActorSystem(GV_ACTOR_LEVEL4);
                GV_PauseLevel &= ~8;
                GM_ResetMapModel();
                GM_StreamPlayStop();
                work->field_24 = 3;
                GM_GameStatus |= STATE_PADRELEASE | STATE_ALL_OFF;

                return;
            }

            if (GV_PauseLevel == 0)
            {
                GM_AlertAct();
            }

            if ((GM_GameStatus & (STATE_VOX_STREAM | STATE_PAUSE_OFF | STATE_PADMASK | STATE_PADRELEASE |
                                           STATE_PADDEMO | STATE_DEMO)) == 0)
            {
                if (((GV_PauseLevel & ~2) == 0) && ((GM_CurrentPadData->press & PAD_START) != 0))
                {
                    GM_TogglePauseScreen();
                }
            }
            else if ((GV_PauseLevel & 2) != 0)
            {
                GM_HidePauseScreen();
            }

            GM_UpdateMap();
        }

        // 0x90f: PAD_L1 | PAD_L2 | PAD_R1 | PAD_R2 | PAD_START | PAD_SELECT
        if (((pad & 0x90f) == 0x90f) && (GM_PadResetDisable == 0))
        {
            if (--dword_800AB9D0 < 0)
            {
                sprintf(exe_name_800B5860, "cdrom:\\MGS\\%s;1", MGS_DiskName[FS_DiskNum_800ACBF0]);
                EnterCriticalSection();
                SetDispMask(0);
                PadStopCom();
                SpuInit();
                CdInit();
                SpuSetIRQ(SPU_OFF);
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

        if ((GM_GameStatus < 0) && ((GM_CurrentPadData[2].press & (PAD_START | PAD_CROSS)) != 0))
        {
            GM_StreamPlayStop();
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

            printf("str_status %d irq %x %X %X\n", str_status, dword_800BF1A8, dword_800BF270,
                   str_off_idx);
            printf("key %08X\n", spu_key);
        }

        if (GV_PauseLevel == 0)
        {
            GM_InitNoise();
        }
    }
    else
    {
        GV_PauseLevel &= ~8;

        if ((--work->field_24 <= 0))
        {
            if (GM_StreamStatus() == -1)
            {
                if ((GV_PauseLevel & 5) == 0)
                {
                    work->status = 0;
                    work->field_24 = 0;
                    GM_ResetMapHazard();
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

        if (GV_PauseLevel == 0)
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

    if (id == 4 && GM_PlayerControl != NULL)
    {
        HZD_ReExecEvent(GM_PlayerControl->map->hzd,
                        &GM_PlayerControl->event, 0x301);
    }

    proc = gSystemCallbackProcs_800B58C0[id];
    if (proc != 0)
    {
        GCL_ARGS args;
        long     argbuf[2];

        args.argc = 1;
        args.argv = argbuf;
        argbuf[0] = arg;
        GCL_ForceExecProc(proc, &args);
    }
}

void GM_SetLoadCallbackProc(int proc_id)
{
    if (proc_id == -1)
    {
        GM_LoadRequest = 0xc0;
    }
    else
    {
        GM_LoadRequest = proc_id << 16 | 0xe0;
    }
}

void GM_ContinueStart(void)
{
    int total_continues;
    int current_stage;

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
        GM_SetLoadCallbackProc(-1);
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
static int GM_LoadInitBin(unsigned char *buf, int id)
{
#ifdef DEV_EXE
    return 1; // the overlay is embedded in the executable in dev variant
#endif

    if (((u_char *)StageCharacterEntries + gOverlayBinSize_800B5290) > GV_ResidentMemoryBottom)
    {
        printf("TOO LARGE STAGE BINARY!!\n");
    }

    memcpy(StageCharacterEntries, buf, gOverlayBinSize_800B5290);
    return 1;
}

void GM_StartDaemon(void)
{
    gTotalFrameTime = 0;
    GM_GameOverTimer = 0;
    GM_LoadRequest = 0;
    GM_LoadComplete = 0;
    MENU_StartDeamon();
    GM_InitArea();
    GM_InitChara();
    GM_InitScript();
    GV_SetLoader('b', GM_LoadInitBin);
    GM_ClearWeaponAndItem();
    GV_InitActor(GV_ACTOR_MANAGER, &GameWork_800B5880.actor, NULL);
    GV_SetNamedActor(&GameWork_800B5880.actor, Act, NULL, "gamed.c");
    GM_ResetSystem();
    GM_ActInit(&GameWork_800B5880);
    GM_ResetMemory();
    GM_CurrentPadData = GV_PadData_800B05C0;
    GM_CurrentDiskFlag = FS_DiskNum_800ACBF0 + 1;
    GV_SaveResidentTop();
    GameWork_800B5880.status = 0;
    GameWork_800B5880.field_24 = 0;
    GM_CreateLoader();
}
