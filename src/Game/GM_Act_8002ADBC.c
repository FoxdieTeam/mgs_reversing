#include "linker.h"
#include "Game/linkvarbuf.h"
#include "Game/object.h"
#include "map/map.h"
#include "psyq.h"
#include "memcard/memcard.h"
#include "mts/mts_new.h"
#include "libgv/libgv.h"
#include "unknown.h"
#include "libfs/libfs.h"
#include "over.h"

extern int GM_PadVibration2_800ABA54;
int        SECTION(".sbss") GM_PadVibration2_800ABA54;

extern int GM_PadVibration_800ABA3C;
int        SECTION(".sbss") GM_PadVibration_800ABA3C;

extern int gTotalFrameTime_800AB9E8;
int        SECTION(".sbss") gTotalFrameTime_800AB9E8;

extern int GM_LoadComplete_800ABA38;
int        SECTION(".sbss") GM_LoadComplete_800ABA38;

extern int GM_LoadRequest_800AB3D0;
int        SECTION(".sdata") GM_LoadRequest_800AB3D0;

extern int GM_GameStatus_800AB3CC;
int        SECTION(".sbss") GM_GameStatus_800AB3CC;

extern int GM_GameOverTimer_800AB3D4;
int        SECTION(".sdata") GM_GameOverTimer_800AB3D4;

extern short *GM_CurrentPadData_800AB91C;
short        *SECTION(".sbss") GM_CurrentPadData_800AB91C;

extern int GM_PadResetDisable_800AB3F4;
int        SECTION(".sdata") GM_PadResetDisable_800AB3F4;

extern int dword_800AB9D0;
int        SECTION(".sbss") dword_800AB9D0;

extern int          dword_800BEFF0;
extern unsigned int gStr_FadeOut1_800BF16C;
extern int          dword_800BF268;
extern int          dword_800BF1A8;
extern int          dword_800BF270;
extern int          dword_800BF264;
extern char         exe_name_800B5860[32];
extern char        *MGS_DiskName_8009D2FC[3];
extern int          gDiskNum_800ACBF0;
extern int          GV_PassageTime_800AB924;
extern int          DG_UnDrawFrameCount_800AB380;
extern int          gSaveCache_800B5294;
extern int          GV_PauseLevel_800AB928;

void GM_Act_8002ADBC(Actor_GM_Daemon *pActor)
{
    int load_request;
    int unk_f20;

    unsigned short pad = mts_read_pad_8008C25C(1);

    if (mts_get_pad_vibration_type_8008C4BC(1) == 1)
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
            mts_set_pad_vibration_8008C408(1, 10);
        }
        else
        {
            mts_set_pad_vibration_8008C408(1, 0);
        }

        vibration2 = GM_PadVibration2_800ABA54;
        if (vibration2 > 255)
        {
            vibration2 = 255;
        }
        mts_set_pad_vibration2_8008C454(1, vibration2);
    }

    GM_PadVibration2_800ABA54 = 0;
    GM_PadVibration_800ABA3C = 0;

    if ((GV_PauseLevel_800AB928 & 8) != 0)
    {
        if (!dword_800BEFF0 && CDBIOS_TaskState_80022888() != 3)
        {
            GV_PauseLevel_800AB928 &= ~0x08;
        }
        else
        {
            DrawReadError_8002AC9C();
        }
    }
    else if (dword_800BEFF0 || CDBIOS_TaskState_80022888() == 3)
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

    unk_f20 = pActor->field_20;
    if (unk_f20 != 0)
    {
        if (unk_f20 != 1)
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

        if ((GM_LoadRequest_800AB3D0 & 0x80) != 0)
        {
            DG_UnDrawFrameCount_800AB380 = 0;
        }

        if (gSaveCache_800B5294 != 0)
        {
            GV_ResidentFileCache_80015484();
            DG_SaveTexureCacheToResidentMem_8001DB20();
        }

        Map_ResetMapCountAndKmdsCount_800310A0();
        camera_init_800306A0();
        DG_StorePalette_8001FC28();
        GM_Act_helper2_8002E8D4();

        if ((GM_LoadRequest_800AB3D0 & 0x10) != 0)
        {
            GCL_SaveVar_80021314();
        }

        mts_printf_8008BBA0("exec scenario\n");
        load_request = GM_LoadRequest_800AB3D0;
        GM_LoadRequest_800AB3D0 = 0;

        if ((load_request & 0x20) != 0)
        {
            GCL_ExecProc_8001FF2C((unsigned int)load_request >> 0x10, 0);
        }
        else
        {
            GCL_ExecScript_80020228();
        }

        mts_printf_8008BBA0("end scenario\n");
        menu_ResetTexture_80038A00();
        GM_AlertModeReset_8002EAB8();
        GM_SoundStart_8002E640();
        pActor->field_20 = 1;

        return;
    }

    if ((pActor->field_24 <= 0))
    {
        if (GM_GameOverTimer_800AB3D4 != 0)
        {
            if (GM_GameOverTimer_800AB3D4 > 0)
            {
                if ((GM_GameOverTimer_800AB3D4 == unk_f20))
                {
                    if (GM_StreamStatus_80037CD8() == -1)
                    {
                        if (over_init_800376F8(1))
                        {
                            GM_GameOverTimer_800AB3D4 = -1;
                        }
                        else
                        {
                            GV_DestroyActorSystem_80015010(4);
                        }
                    }
                    else if (GM_StreamStatus_80037CD8() == unk_f20)
                    {
                        GM_StreamPlayStop_80037D64();
                    }
                }
                else
                {
                    GM_GameOverTimer_800AB3D4--;
                }
            }
        }
        else
        {
            if (GM_LoadRequest_800AB3D0 != 0 && (GV_PauseLevel_800AB928 & 2) == 0)
            {
                if ((GM_LoadRequest_800AB3D0 & 0x80) != 0)
                {
                    DG_UnDrawFrameCount_800AB380 = 0x7fff0000;
                }

                GV_DestroyActorSystem_80015010(4);
                GV_PauseLevel_800AB928 &= ~0x8;
                GM_FreeMapObjs_80031028();
                GM_StreamPlayStop_80037D64();
                pActor->field_24 = 3;
                GM_GameStatus_800AB3CC = GM_GameStatus_800AB3CC | 0x104a6000; // TODO: split these flags

                return;
            }

            if (GV_PauseLevel_800AB928 == 0)
            {
                GM_AlertAct_8002E91C();
            }

            if ((GM_GameStatus_800AB3CC & 0xd8004020) == 0)
            {
                if (((GV_PauseLevel_800AB928 & ~0x2) == 0) && ((GM_CurrentPadData_800AB91C[1] & 0x800) != 0))
                {
                    GM_Act_helper3_8002ABA4();
                }
            }
            else if ((GV_PauseLevel_800AB928 & 2) != 0)
            {
                sub_8002AAEC();
            }

            Map_80030FA4();
        }

        if (((pad & 0x90f) == 0x90f) && (GM_PadResetDisable_800AB3F4 == 0))
        {
            if (--dword_800AB9D0 < 0)
            {
                sprintf_8008E878(exe_name_800B5860, "cdrom:\\MGS\\%s;1", MGS_DiskName_8009D2FC[gDiskNum_800ACBF0]);
                EnterCriticalSection_8009952C();
                SetDispMask_8008F7CC(0);
                PadStopCom_8009A24C();
                SpuInit_80094568();
                CdInit();
                SpuSetIRQ_80096A28(0);
                mts_shutdown_8008B044();
                memcard_exit_800250C4();
                ResetGraph(3);
                StopCallback_8009840C();
                SetConf_800997BC(0x10, 4, 0x801FFFF0); // note: hardcoded addresses
                ResetCallback_80098318();
                StopCallback_8009840C();
                _96_remove_80099434();
                _96_init_8009941C();

                do
                {
                    mts_printf_8008BBA0("load %s\n", exe_name_800B5860);
                    LoadExec_8009940C(exe_name_800B5860, 0x801FFF00, 0);
                } while (1);
            }
        }
        else
        {
            dword_800AB9D0 = 0x5a;
        }

        if ((GM_GameStatus_800AB3CC < 0) && ((GM_CurrentPadData_800AB91C[17] & 0x840) != 0))
        {
            GM_StreamPlayStop_80037D64();
        }

        if ((mts_read_pad_8008C25C(2) & 0x20) != 0)
        {
            char         spu_status[24];
            char         status;
            int          i;
            unsigned int unk;

            SpuGetAllKeysStatus_8009748C(spu_status);
            unk = 0;
            for (i = 0; i < 24; ++i)
            {
                unk *= 2;
                status = spu_status[i];
                unk |= status & 1;
            }

            // "str_status %d irq %x %X %X\n"
            mts_printf_8008BBA0("str_status %d irq %x %X %X\n", gStr_FadeOut1_800BF16C, dword_800BF1A8, dword_800BF270, dword_800BF264);
            mts_printf_8008BBA0("key %08X\n", unk);
        }

        if (GV_PauseLevel_800AB928 == 0)
        {
            GM_Act_helper_8002AA10();
        }
    }
    else
    {
        GV_PauseLevel_800AB928 &= ~0x8;

        if ((--pActor->field_24 <= 0))
        {
            if (GM_StreamStatus_80037CD8() == -1)
            {
                if ((GV_PauseLevel_800AB928 & 5) == 0)
                {
                    pActor->field_20 = 0;
                    pActor->field_24 = 0;
                    GM_DieMap_80030FD0();
                    sub_8002AA48();
                    GM_Reset_8002ABF4(pActor);

                    if ((GM_LoadRequest_800AB3D0 & 0x40) == 0)
                    {
                        GM_ResetMemory_8002AA80();
                        GM_CreateLoader_8002AAB0();
                    }

                    return;
                }
                else if ((GM_LoadRequest_800AB3D0 & 0x80) != 0)
                {
                    DG_UnDrawFrameCount_800AB380 = 0;
                }
            }

            pActor->field_24 = unk_f20;
        }

        if (GV_PauseLevel_800AB928 == 0)
        {
            GM_Act_helper_8002AA10();
        }
    }
}
