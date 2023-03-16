#include "demothrd.h"
#include "libfs/libfs.h"
#include "Anime/animeconv/anime.h"
#include "libdg/libdg.h"

extern const char aDemothrdC[];
extern SVECTOR DG_ZeroVector_800AB39C;
extern ANIMATION stru_8009F774;
extern int DG_UnDrawFrameCount_800AB380;
extern int demodebug_finish_proc_800AB414;
extern int dword_800BDFB8;
extern int dword_800BDFBC;
extern int dword_800BDFC0;
extern int dword_800BDFC4;
extern const char aM1e1[];
extern const char aM1e1demo[];
extern GM_Camera        GM_Camera_800B77E8;
extern short           gGameState_800B4D98[0x60];
extern SVECTOR DG_ZeroVector_800AB39C;
extern ANIMATION stru_8009F774;
extern ANIMATION stru_8009F73C;
extern ANIMATION stru_8009F790;
extern const char aDemothrdC[];
extern SVECTOR DG_ZeroVector_800AB39C;
extern ANIMATION stru_8009F774;

extern const char aDemothrdC[];
extern const char aCacheBufferCle[]; // = "Cache Buffer Cleared\n";
extern const char aCacheReadEnabl[]; // = "Cache Read Enable\n";
extern const char aDemothrdC[];
extern const char aDemoFileS[];
extern const char aSNotFound[];
extern const char aM1e1[];
extern const char aM1e1demo[];
extern const char aHinddemo[];
extern const char aHind[];
extern const char aNoloadModelSce[];
extern const char aErrorInitContr[];
extern const char aDemothrdC[];
extern const char aDemoFileS[];
extern const char aSNotFound[];
extern const char aM1e1[];
extern const char aM1e1demo[];
extern const char aHinddemo[];
extern const char aHind[];
extern const char a16dO4a[];
extern const char a16dO5a[];
extern const char a16dO6a[];
extern const char a16dO7a[];
extern const char a16dO8a[];
extern const char a16dO9a[];
extern const char a16dO10a[];
extern const char a16dO4b[];
extern const char a16dO5b[];
extern const char a16dO6b[];
extern const char a16dO7b[];
extern const char a16dO8b[];
extern const char a16dO9b[];
extern const char a16dO10b[];
extern const char a16dO4c[];
extern const char a16dO5c[];
extern const char a16dO6c[];
extern const char a16dO7c[];
extern const char a16dO8c[];
extern const char a16dO9c[];
extern const char a16dO10c[];
extern const char a02aR8[];
extern const char aMgrexw[];
extern const char aMgrexll[];
extern const char aMgrexrl[];
extern const char aPitT[];
extern const char aPitU[];
extern const char aPitLiq[];
extern const char aRadarF1[];
extern const char aRadarF2[];
extern const char aRadarF3[];
extern const char aLHatch1[];
extern const char aLHatch2[];
extern const char aLHatch3[];
extern const char aLHatch4[];
extern const char aRHatch1[];
extern const char aRHatch2[];
extern const char aRHatch3[];
extern const char aRHatch4[];
extern const char aM1e1cl1[];
extern const char aM1e1cl2[];
extern const char aM1e1cl3[];
extern const char aM1e1cr1[];
extern const char aM1e1cr2[];
extern const char aM1e1cr3[];
extern const char aNoloadModelSta[];
extern const char aNull_0[];
extern const char aNoloadModelNul[];
extern const char aErrorInitContr_0[];
extern const char aNull[];

void demothrd_Screen_Chanl_80080D48(DG_CHNL *pOt, int idx);

void InitChain_8007F338(Actor_demothrd_0x78_Chain *pSub);
void Chain_Remove_8007F394(Actor_demothrd_0x78_Chain *pRoot, Actor_demothrd_0x78_Chain *pRemove);
TChanl_Fn DG_SetChanlSystemUnits_80018598(int idx, TChanl_Fn newFunc);
void demothrd_hind_8007D9C8(Actor_demothrd *pActor, dmo_data_0x18 *pDmoData0x18, dmo_model_0x14 *p0x14, dmo_model_0x1A4 *p0x1A4);
void demothrd_m1e1_8007D404(Actor_demothrd *pActor, dmo_data_0x18 *p0x18, dmo_model_0x14 *p0x14, dmo_model_0x1A4 *p0x1A4);
void demothrd_file_stream_act_800797FC(Actor_demothrd* pActor);
void demothrd_file_stream_kill_80079960(Actor_demothrd* pActor);

void AN_CaterpillerSmoke_8007DA28(SVECTOR *pos);
void M1E1GetCaterpillerVertex_800815FC(dmo_m1e1_entry *pE1, dmo_m1e1_entry *pE2, SVECTOR *pSmokeVecs, int a4);

void DG_8001CDB8(DG_OBJS *pObjs);

int DM_ThreadStream_80079460(int flag, int unused)
{
    Actor_demothrd *pDemoThrd = (Actor_demothrd *)GV_NewActor_800150E4(1, sizeof(Actor_demothrd));
    if (!pDemoThrd)
    {
        return 0;
    }

    pDemoThrd->field_20_flag = flag;
    pDemoThrd->field_2C_timer_ticks = -1;
    GV_SetNamedActor_8001514C(&pDemoThrd->field_0_actor, (TActorFunction)demothrd_cd_act_80079664,
                              (TActorFunction)demothrd_cd_stream_die_800797CC, aDemothrdC);
    pDemoThrd->field_28_map = GM_CurrentMap_800AB9B0;
    FS_StreamOpen_80024060();
    return 1;
}

// https://decomp.me/scratch/TwT1k
#pragma INCLUDE_ASM("asm/Kojo/DM_ThreadFile_800794E4.s")                           // 384 bytes


#pragma INCLUDE_ASM("asm/Kojo/demothrd_cd_act_80079664.s")                              // 360 bytes

void demothrd_cd_stream_die_800797CC(Actor_demothrd *pActor)
{
    DestroyDemo_8007A66C(pActor);
    FS_StreamClose_80024098();
    DG_UnDrawFrameCount_800AB380 = 0x7fff0000;
}

#pragma INCLUDE_ASM("asm/Kojo/demothrd_file_stream_act_800797FC.s")                         // 356 bytes

void demothrd_file_stream_kill_80079960(Actor_demothrd *pActor)
{
    DestroyDemo_8007A66C(pActor);
    FS_EnableMemfile_800799A8(1, 1);

    if (demodebug_finish_proc_800AB414 != -1)
    {
        GCL_ExecProc_8001FF2C(demodebug_finish_proc_800AB414, NULL);
    }
}

void FS_EnableMemfile_800799A8(int cache_read_enable, int clear_cache_buffer)
{
    dword_800BDFB8 = cache_read_enable;
    dword_800BDFBC = clear_cache_buffer;

    if (clear_cache_buffer != 0) {
        mts_printf_8008BBA0(aCacheBufferCle);
        dword_800BDFC4 = 0x80700c00;
        // Debug build address
        *(int *)0x80700000 = 0;
        dword_800BDFC0 = 0x80700000;
    }

    if (cache_read_enable) {
        mts_printf_8008BBA0(aCacheReadEnabl);
    }
}

void sub_80079A1C(void)
{
    // Debug build address
    *(int *)0x80700000 = 0;
}

#pragma INCLUDE_ASM("asm/sub_80079A2C.s")                                          // 184 bytes
#pragma INCLUDE_ASM("asm/sub_80079AE4.s")                                          // 108 bytes


int CreateDemo_80079B50(Actor_demothrd* pThis, demothrd_0x1C* pDmoData)
{
    void* pOldRendFunc; // $v0
    demothrd_0x1C* pHdr; // $v0
    Dmo_Map8* pMaps; // $v0
    dmo_model_0x14* pNew_14; // $v0
    Dmo_Map8* pMapsIter; // $s0
    int scene_no; // $s4
    dmo_model_0x14* pModel0x14Iter; // $s0
    dmo_model_0x1A4* pModels0x1A4Iter; // $s3
    dmo_m1e1_data* pM1Data; // $v0
    dmo_hind* pHindData; // $v0
    MATRIX* mtx;

    pOldRendFunc = DG_SetChanlSystemUnits_80018598(0, demothrd_Screen_Chanl_80080D48);

    pThis->field_270_pOldRenderFn = pOldRendFunc;
    pThis->field_274_old_game_state_flags = GM_GameStatus_800AB3CC;
    pThis->field_278 = GM_Camera_800B77E8;

    pThis->field_2F4_old_equipped_item = gGameState_800B4D98[15];
    pThis->field_2F8_old_equipped_weapon = gGameState_800B4D98[14];

    pDmoData->field_14_pMaps = (Dmo_Map8*)(((char*)pDmoData) + (int)pDmoData->field_14_pMaps);
    pDmoData->field_18_pModels = (dmo_model_0x14*)((int)pDmoData->field_18_pModels + (char*)pDmoData);
    InitChain_8007F338(&pThis->field_38);
    pHdr = (demothrd_0x1C*)GV_Malloc_8001620C(sizeof(demothrd_0x1C));
    pThis->field_30_dmo_header = pHdr;
    if (!pHdr) {
        return 0;
    }
    *pHdr = *((demothrd_0x1C*)pDmoData);

    pThis->field_30_dmo_header->field_14_pMaps = 0;
    pThis->field_30_dmo_header->field_18_pModels = 0;
    pMaps = GV_Malloc_8001620C((sizeof(Dmo_Map8) * pDmoData->field_C_num_maps) | 1);
    pThis->field_30_dmo_header->field_14_pMaps = pMaps;
    if (!pMaps) {
        return 0;
    }
    pNew_14 = (dmo_model_0x14*)GV_Malloc_8001620C((sizeof(dmo_model_0x14) * pDmoData->field_10_num_models) | 1);
    pThis->field_30_dmo_header->field_18_pModels = pNew_14;
    if (!pNew_14) {
        return 0;
    }
    memcpy_8008E648(
        (char*)pThis->field_30_dmo_header->field_14_pMaps,
        (char*)pDmoData->field_14_pMaps,
        sizeof(Dmo_Map8) * pThis->field_30_dmo_header->field_C_num_maps);

    memcpy_8008E648(
        pThis->field_30_dmo_header->field_18_pModels,
        (char*)pDmoData->field_18_pModels,
        sizeof(dmo_model_0x14) * pThis->field_30_dmo_header->field_10_num_models);

    pMapsIter = (Dmo_Map8*)pThis->field_30_dmo_header->field_14_pMaps;

    scene_no = 0;
    if (pThis->field_30_dmo_header->field_C_num_maps > 0) {
        while (1) {

            if (!GV_GetCache_8001538C(pMapsIter->field_0)) {
                mts_printf_8008BBA0(aNoloadModelSta);
                return 0;
            }
            ++scene_no;
            pMapsIter++;

            if (scene_no >= pThis->field_30_dmo_header->field_C_num_maps) {
                break;
            }
        }
    }

    pThis->field_34_pModels = (dmo_model_0x1A4*)GV_Malloc_8001620C((sizeof(dmo_model_0x1A4) * pThis->field_30_dmo_header->field_10_num_models) | 1);
    if (pThis->field_34_pModels) {


        memset(pThis->field_34_pModels, 0, sizeof(dmo_model_0x1A4) * pThis->field_30_dmo_header->field_10_num_models);

        pModels0x1A4Iter = pThis->field_34_pModels;
        pModel0x14Iter = pThis->field_30_dmo_header->field_18_pModels;

        scene_no = 0;
        while (scene_no < pThis->field_30_dmo_header->field_10_num_models) {

            if (!GV_GetCache_8001538C((pModel0x14Iter)->field_8)) {
                mts_printf_8008BBA0(aNoloadModelSce, scene_no +1);
                asm(""); // TODO hack!
                return 0;
            }

            if (Res_Control_init_loader_8002599C(&pModels0x1A4Iter->field_0_ctrl, pModel0x14Iter->field_10, pThis->field_28_map) < 0) {
                mts_printf_8008BBA0(aErrorInitContr, scene_no + 1);
                return 0;
            }

            pModels0x1A4Iter->field_0_ctrl.field_36 = 0;
            pModels0x1A4Iter->field_0_ctrl.field_54 = 0;

            if (((pModel0x14Iter)->field_4_flags & 1) != 0) {

                GM_InitObject_80034A18(&pModels0x1A4Iter->field_7C_obj, pModel0x14Iter->field_C_hashCode, 79, 0);
            }
            else {
                if ((pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO4a)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO5a)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO6a)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO7a)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO8a)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO9a)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO10a)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO4b)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO5b)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO6b)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO7b)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO8b)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO9b)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO10b)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO4c)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO5c)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO6c)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO7c)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO8c)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO9c)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a16dO10c)) {
                    GM_InitObject_80034A18(&pModels0x1A4Iter->field_7C_obj, (pModel0x14Iter)->field_C_hashCode, 5, 0);
                }
                else if ((pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(a02aR8)) {

                    pModels0x1A4Iter->field_160_mtx.t[0] = 100;
                    pModels0x1A4Iter->field_160_mtx.t[1] = 110;
                    pModels0x1A4Iter->field_160_mtx.t[2] = 110;

                    GM_InitObject_80034A18(&pModels0x1A4Iter->field_7C_obj, (pModel0x14Iter)->field_C_hashCode, 0x10D, 0);
                }
                else if ((pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aMgrexw)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aMgrexll)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aMgrexrl)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aPitT)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aPitU)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aPitLiq)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aRadarF1)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aRadarF2)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aRadarF3)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aLHatch1)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aLHatch2)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aLHatch3)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aLHatch4)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aRHatch1)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aRHatch2)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aRHatch3)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aRHatch4)) {

                    pModels0x1A4Iter->field_160_mtx.t[0] = 64;
                    pModels0x1A4Iter->field_160_mtx.t[1] = 64;
                    pModels0x1A4Iter->field_160_mtx.t[2] = 64;
                    GM_InitObject_80034A18(&pModels0x1A4Iter->field_7C_obj, (pModel0x14Iter)->field_C_hashCode, 0x10D, 0);
                }
                else {
                    GM_InitObject_80034A18(&pModels0x1A4Iter->field_7C_obj, (pModel0x14Iter)->field_C_hashCode, 13, 0);
                }

                mtx = &pModels0x1A4Iter->field_160_mtx;
                GM_ConfigObjectJoint_80034CB4(&pModels0x1A4Iter->field_7C_obj);
                GM_ConfigObjectLight_80034C44(&pModels0x1A4Iter->field_7C_obj, mtx);

                DG_InvisibleObjs(pModels0x1A4Iter->field_7C_obj.objs);

                if ((pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aM1e1)
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aM1e1demo)) {
                    pM1Data = (dmo_m1e1_data*)GV_Malloc_8001620C(sizeof(dmo_m1e1_data));
                    pModels0x1A4Iter->field_1A0_pM1OrHind = pM1Data;
                    if (!pM1Data) {
                        return 0;
                    }
                    memset(pM1Data, 0, sizeof(dmo_m1e1_data));
                    GM_InitObject_80034A18(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[0][0].field_0, GV_StrCode_80016CCC(aM1e1cl1), 301, 0);
                    GM_InitObject_80034A18(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[0][1].field_0, GV_StrCode_80016CCC(aM1e1cl2), 301, 0);
                    GM_InitObject_80034A18(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[0][2].field_0, GV_StrCode_80016CCC(aM1e1cl3), 301, 0);

                    GM_InitObject_80034A18(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[1][0].field_0, GV_StrCode_80016CCC(aM1e1cr1), 301, 0);
                    GM_InitObject_80034A18(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[1][1].field_0, GV_StrCode_80016CCC(aM1e1cr2), 301, 0);
                    GM_InitObject_80034A18(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[1][2].field_0, GV_StrCode_80016CCC(aM1e1cr3), 301, 0);

                    GM_ConfigObjectJoint_80034CB4(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[0][0].field_0);
                    GM_ConfigObjectJoint_80034CB4(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[0][1].field_0);
                    GM_ConfigObjectJoint_80034CB4(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[0][2].field_0);

                    GM_ConfigObjectJoint_80034CB4(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[1][0].field_0);
                    GM_ConfigObjectJoint_80034CB4(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[1][1].field_0);
                    GM_ConfigObjectJoint_80034CB4(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[1][2].field_0);

                    GM_ConfigObjectLight_80034C44(
                        &(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[0][0].field_0,
                        mtx);
                    GM_ConfigObjectLight_80034C44(
                        &(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[0][1].field_0,
                        mtx);
                    GM_ConfigObjectLight_80034C44(
                        &(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[0][2].field_0,
                        mtx);

                    GM_ConfigObjectLight_80034C44(
                        &(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[1][0].field_0,
                        mtx);
                    GM_ConfigObjectLight_80034C44(
                        &(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[1][1].field_0,
                        mtx);
                    GM_ConfigObjectLight_80034C44(
                        &(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[1][2].field_0,
                        mtx);

                    (pModels0x1A4Iter->field_1A0_pM1OrHind)->field_560 = 83;
                }
                else {
                    if ((pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aHind)
                        || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC(aHinddemo)) {
                        pHindData = (dmo_hind*)GV_Malloc_8001620C(sizeof(dmo_hind));
                        pModels0x1A4Iter->field_1A0_pM1OrHind = (dmo_m1e1_data*)pHindData;
                        if (!pHindData) {
                            return 0;
                        }
                        memset(pHindData, 0, sizeof(dmo_hind));
                    }
                }
            }
            ++scene_no;
            pModel0x14Iter++;
            ++pModels0x1A4Iter;
        }

        if (!GV_GetCache_8001538C(GV_CacheID2_800152FC(aNull, 'k'))) {
            mts_printf_8008BBA0(aNoloadModelNul);
        }
        else {
            if (Res_Control_init_loader_8002599C(&pThis->field_C4_ctrl, 0, pThis->field_28_map) >= 0) {
                pThis->field_C4_ctrl.field_36 = 0;
                pThis->field_C4_ctrl.field_54 = 0;
                GM_InitObject_80034A18(&pThis->field_140_obj, GV_StrCode_80016CCC(aNull), 13, 0);
                GM_ConfigObjectJoint_80034CB4(&pThis->field_140_obj);
                GM_ConfigObjectLight_80034C44(&pThis->field_140_obj, &pThis->field_224_light_mtx);
                GM_GameStatus_800AB3CC |= 0x80000000;
                DG_InvisibleObjs(pThis->field_140_obj.objs);
                return 1;
            }
            else {
                mts_printf_8008BBA0(aErrorInitContr_0);
            }
        }
    }
    return 0;
}

int DestroyDemo_8007A66C(Actor_demothrd *pActor)
{
  Actor_demothrd_0x78_Chain *i;
  GV_ACT *pPrevious;
  GV_ACT *pNext;
  dmo_model_0x1A4 *field_34_pModels;
  dmo_model_0x1A4 *pModelIter;
  dmo_model_0x14 *pModelIter_1;
  int mdlNum;
  demothrd_0x1C *pHeader;
  void *pMaps;
  dmo_model_0x14 *pMods;
  TChanl_Fn field_270_pOldRenderFn;

  if ((pActor->field_20_flag & 2) != 0)
  {
    GM_GameStatus_800AB3CC |= 0x1000000u;
  }
  for (i = pActor->field_38.field_4_pNext; i != (&pActor->field_38); i = pActor->field_38.field_4_pNext)
  {
    pPrevious = i->field_C_actor.pPrevious;
    if (pPrevious)
    {
      GV_DestroyOtherActor_800151D8(pPrevious);
    }
    pNext = i->field_C_actor.pNext;
    if (pNext)
    {
      GV_DestroyOtherActor_800151D8(pNext);
    }
    Chain_Remove_8007F394(&pActor->field_38, i);
    GV_Free_80016230(i);
  }

  field_34_pModels = pActor->field_34_pModels;
  if (field_34_pModels)
  {
    pModelIter = pActor->field_34_pModels;

    pModelIter_1 = pActor->field_30_dmo_header->field_18_pModels;
    mdlNum = 0;
    if (pActor->field_30_dmo_header->field_10_num_models > mdlNum)
    {
      do
      {
        GM_FreeObject_80034BF8(&pModelIter->field_7C_obj);
        if (pModelIter->field_1A0_pM1OrHind)
        {
          if (((pModelIter_1->field_C_hashCode) == GV_StrCode_80016CCC(aM1e1)) || ((pModelIter_1->field_C_hashCode) == GV_StrCode_80016CCC(aM1e1demo)))
          {
            GM_FreeObject_80034BF8(&pModelIter->field_1A0_pM1OrHind->field_0[0][0].field_0);
            GM_FreeObject_80034BF8(&pModelIter->field_1A0_pM1OrHind->field_0[0][1].field_0);
            GM_FreeObject_80034BF8(&pModelIter->field_1A0_pM1OrHind->field_0[0][2].field_0);
            GM_FreeObject_80034BF8(&pModelIter->field_1A0_pM1OrHind->field_0[1][0].field_0);
            GM_FreeObject_80034BF8(&pModelIter->field_1A0_pM1OrHind->field_0[1][1].field_0);
            GM_FreeObject_80034BF8(&pModelIter->field_1A0_pM1OrHind->field_0[1][2].field_0);
          }
          GV_Free_80016230(pModelIter->field_1A0_pM1OrHind);
        }
        mdlNum++;
        pModelIter_1++;
        pModelIter++;
      }
      while (mdlNum < pActor->field_30_dmo_header->field_10_num_models);
    }
    GM_FreeControl_800260CC(&pModelIter->field_0_ctrl);
    GV_Free_80016230(pActor->field_34_pModels);
  }
  GM_FreeObject_80034BF8(&pActor->field_140_obj);
  GM_FreeControl_800260CC(&pActor->field_C4_ctrl);
  pHeader = pActor->field_30_dmo_header;
  if (pHeader)
  {
    pMaps = (void *) pHeader->field_14_pMaps;
    if (pMaps)
    {
      GV_Free_80016230(pMaps);
    }
    pMods = pActor->field_30_dmo_header->field_18_pModels;
    if (pMods)
    {
      GV_Free_80016230(pMods);
    }
    GV_Free_80016230(pActor->field_30_dmo_header);
  }
  field_270_pOldRenderFn = pActor->field_270_pOldRenderFn;
  GM_GameStatus_800AB3CC &= ~0x80000000;
  DG_SetChanlSystemUnits_80018598(0, field_270_pOldRenderFn);
  GM_GameStatus_800AB3CC = pActor->field_274_old_game_state_flags;
  GM_Camera_800B77E8 = pActor->field_278;
  gGameState_800B4D98[15] = pActor->field_2F4_old_equipped_item;
  gGameState_800B4D98[14] = pActor->field_2F8_old_equipped_weapon;
  return 1;
}


#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_8007A948.s")                 // 1224 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_make_chara_8007AE10.s")         // 8016 bytes

void demothrd_remove_via_id_8007CD60(Actor_demothrd *pThis, int id_to_remove)
{
    Actor_demothrd_0x78_Chain *pSubIter; // $s0
    Actor_demothrd_0x78_Chain *pCur; // $a0
    Actor_demothrd_0x78_Chain *pCur_; // $s1
    GV_ACT *pPrevious; // $a0
    GV_ACT *pNext; // $a0

    pSubIter = pThis->field_38.field_4_pNext;
    pCur = &pThis->field_38;
    if ( pSubIter != pCur )
    {
        pCur_ = pCur;
        do
        {
            if ( pSubIter->field_C_actor.mFnShutdown == (TActorFunction)id_to_remove )
            {
                pPrevious = pSubIter->field_C_actor.pPrevious;
                if ( pPrevious )
                {
                    GV_DestroyOtherActor_800151D8(pPrevious);
                    pNext = pSubIter->field_C_actor.pNext;
                    if ( pNext )
                    {
                        GV_DestroyOtherActor_800151D8(pNext);
                    }
                    pSubIter->field_C_actor.pPrevious = 0;
                    pSubIter->field_C_actor.pNext = 0;
                }
            }
            pSubIter = pSubIter->field_4_pNext;
        }
        while ( pSubIter != pCur_ );
    }
}

int demothrd_8007CDF8(Actor_demothrd *pActor, dmo_data_0x28 *pDmoData, Actor_demothrd_0x78_Chain *pChain)
{
  dmo_data_0x18 *field_24_pDmoEnd;
  int idx;
  SVECTOR vec2;
  SVECTOR vecPos;
  if (pChain->field_C_actor.mFnShutdown == ((TActorFunction) 14))
  {
    field_24_pDmoEnd = pDmoData->field_24_pDmoEnd;
    {
      for (idx = 0; idx < pDmoData->field_20_count; idx++)
      {
        if (field_24_pDmoEnd->field_0_type == pChain->field_C_actor.field_1C)
        {
          break;
        }
        ++field_24_pDmoEnd;
      }

      if (idx < pDmoData->field_20_count)
      {
        vecPos.vx = field_24_pDmoEnd->field_C_pos_x;
        vecPos.vy = field_24_pDmoEnd->field_E_pos_y;
        vecPos.vz = field_24_pDmoEnd->field_10_pos_z;
        idx = sub_800296C4(pActor->field_C4_ctrl.field_2C_map->field_8_hzd, &vecPos, 1);
        sub_800298DC((int *) (&vec2));
        pChain->field_48 = field_24_pDmoEnd->field_8_rot_y;
        if ((idx & 1) != 0)
        {
          pChain->field_4C = vec2.vx + 50;
        }
        else  if ((idx & 2) != 0)
        {
          pChain->field_4C = vec2.vz + 50;
        }
        else
        {
          pChain->field_4C = field_24_pDmoEnd->field_E_pos_y + 50;
        }

      }
    }
  }
  return 1;
}

int demothrd_1_FrameRunDemo_helper4_8007CF14(Actor_demothrd *pActor, dmo_data_0x28 *pDmo)
{
  dmo_data_0x34 *pIter;
  int i;
  Actor_demothrd_0x78_Chain *pNext;
  Actor_demothrd_0x78_Chain *new_var;
  Actor_demothrd_0x78_Chain *new_var2;
  Actor_demothrd_0x78_Chain *pRoot;
  pIter = pDmo->field_1C_dmo_data_offset;
  for (i = 0; i < pDmo->field_18_count; ++pIter)
  {
    ++i;
    if (pIter->field_4_type == 28)
    {
      return 1;
    }
  }

  pNext = pActor->field_38.field_4_pNext;
  new_var = &pActor->field_38;
  if (pNext != new_var)
  {
    if (pNext->field_C_actor.mFnShutdown != ((TActorFunction) 28))
    {
      new_var2 = new_var;
      pRoot = &pActor->field_38;
      while (1)
      {
        pNext = pNext->field_4_pNext;
        if (pNext == new_var2)
        {
          break;
        }
        if (pNext->field_C_actor.mFnShutdown == ((TActorFunction) 28))
        {
          pRoot = &pActor->field_38;
          break;
        }
      }

    }
  }
  if (pNext != (&pActor->field_38))
  {
    GV_DestroyOtherActor_800151D8(pNext->field_C_actor.pPrevious);
    pRoot = &pActor->field_38;
    pNext->field_C_actor.pPrevious = 0;
    Chain_Remove_8007F394(pRoot, pNext);
    GV_Free_80016230(pNext);
  }
  return 1;
}

int demothrd_8007CFE8(Actor_demothrd *pActor, dmo_data_0x18 *pDmoData0x18)
{
  dmo_model_0x1A4 *pModelIter_0x1A4;
  dmo_model_0x14 *pModelIter_0x14;
  int counter;
  dmo_6 *pEndIter;

  OFFSET_TO_PTR(pDmoData0x18, &pDmoData0x18->field_14_pEndData);


  pModelIter_0x1A4 = pActor->field_34_pModels;
  pModelIter_0x14 = pActor->field_30_dmo_header->field_18_pModels;

  for (counter = 0; counter < pActor->field_30_dmo_header->field_10_num_models;)
  {
    if (pModelIter_0x14->field_0_type == pDmoData0x18->field_0_type)
    {
      break;
    }
     counter++;
    ++pModelIter_0x14;
    ++pModelIter_0x1A4;

  }

  if (counter >= pActor->field_30_dmo_header->field_10_num_models)
  {
    return 0;
  }

  if (!pDmoData0x18->field_4)
  {
    DG_InvisibleObjs(pModelIter_0x1A4->field_7C_obj.objs);
    if ((pModelIter_0x14->field_C_hashCode == GV_StrCode_80016CCC(aM1e1)) || ((pModelIter_0x14->field_C_hashCode == GV_StrCode_80016CCC(aM1e1demo))))
    {
      DG_InvisibleObjs(pModelIter_0x1A4->field_1A0_pM1OrHind->field_0[0][0].field_0.objs);
      DG_InvisibleObjs(pModelIter_0x1A4->field_1A0_pM1OrHind->field_0[0][1].field_0.objs);
      DG_InvisibleObjs(pModelIter_0x1A4->field_1A0_pM1OrHind->field_0[0][2].field_0.objs);
      DG_InvisibleObjs(pModelIter_0x1A4->field_1A0_pM1OrHind->field_0[1][0].field_0.objs);
      DG_InvisibleObjs(pModelIter_0x1A4->field_1A0_pM1OrHind->field_0[1][1].field_0.objs);
      DG_InvisibleObjs(pModelIter_0x1A4->field_1A0_pM1OrHind->field_0[1][2].field_0.objs);
    }
  }
  else
  {
    DG_VisibleObjs(pModelIter_0x1A4->field_7C_obj.objs);
    if ((pModelIter_0x14->field_C_hashCode == GV_StrCode_80016CCC(aM1e1)) || (pModelIter_0x14->field_C_hashCode == GV_StrCode_80016CCC(aM1e1demo)))
    {
      DG_VisibleObjs(pModelIter_0x1A4->field_1A0_pM1OrHind->field_0[0][pModelIter_0x1A4->field_1A0_pM1OrHind->field_558_idx[0]].field_0.objs);
      DG_VisibleObjs(pModelIter_0x1A4->field_1A0_pM1OrHind->field_0[1][pModelIter_0x1A4->field_1A0_pM1OrHind->field_558_idx[1]].field_0.objs);
    }

    pModelIter_0x1A4->field_0_ctrl.field_0_mov.vx = pDmoData0x18->field_C_pos_x;
    pModelIter_0x1A4->field_0_ctrl.field_0_mov.vy = pDmoData0x18->field_E_pos_y;
    pModelIter_0x1A4->field_0_ctrl.field_0_mov.vz = pDmoData0x18->field_10_pos_z;
    pModelIter_0x1A4->field_0_ctrl.field_8_rotator.vx = pDmoData0x18->field_6_rot_x;
    pModelIter_0x1A4->field_0_ctrl.field_8_rotator.vy = pDmoData0x18->field_8_rot_y;
    pModelIter_0x1A4->field_0_ctrl.field_8_rotator.vz = pDmoData0x18->field_A_rot_z;
    if ((pModelIter_0x14->field_4_flags & 1) != 0)
    {
      GM_ActControl_80025A7C(&pModelIter_0x1A4->field_0_ctrl);
      GM_ActObject2_80034B88(&pModelIter_0x1A4->field_7C_obj);
     // return 1;
    }
    else
    {
        pEndIter = pDmoData0x18->field_14_pEndData;
        counter = 0;
        if (pDmoData0x18->field_12_total > 0)
        {
          do
          {
            pModelIter_0x1A4->field_A0[counter].vx = pEndIter->field_0;
            pModelIter_0x1A4->field_A0[counter].vy = pEndIter->field_2; // field_0
            pModelIter_0x1A4->field_A0[counter].vz = pEndIter->field_4;
            counter++;
            pEndIter++;
          }
          while (counter < pDmoData0x18->field_12_total);
        }

        if ((pModelIter_0x14->field_C_hashCode == GV_StrCode_80016CCC(aM1e1)) || (pModelIter_0x14->field_C_hashCode == GV_StrCode_80016CCC(aM1e1demo)))
        {
          demothrd_m1e1_8007D404(pActor, pDmoData0x18, pModelIter_0x14, pModelIter_0x1A4);
        }
        else if ((pModelIter_0x14->field_C_hashCode == GV_StrCode_80016CCC(aHind)) || (pModelIter_0x14->field_C_hashCode == GV_StrCode_80016CCC(aHinddemo)))
        {
           demothrd_hind_8007D9C8(pActor, pDmoData0x18, pModelIter_0x14, pModelIter_0x1A4);
        }

        GM_ActMotion_80034A7C(&pModelIter_0x1A4->field_7C_obj);
        GM_ActControl_80025A7C(&pModelIter_0x1A4->field_0_ctrl);
        GM_ActObject_80034AF4(&pModelIter_0x1A4->field_7C_obj);
        DG_GetLightMatrix_8001A3C4(&pModelIter_0x1A4->field_0_ctrl.field_0_mov, &pModelIter_0x1A4->field_160_mtx);
    }
  }
  return 1;
}


static inline int magic_calc(SVECTOR* vecTmp, dmo_model_0x1A4 *p0x1A4)
{
    int distance1 = SquareRoot0_80092708(((vecTmp->vx * vecTmp->vx) + (vecTmp->vy * vecTmp->vy)) + (vecTmp->vz * vecTmp->vz));

    int rTan1 = ratan2_80094308(vecTmp->vx, vecTmp->vz);
    int tmp4 = rTan1;
    tmp4 -= p0x1A4->field_0_ctrl.field_8_rotator.vy + p0x1A4->field_A0[0].vy;
    tmp4 = abs(tmp4);
    return (distance1 * (1024 - tmp4)) / 1024;
}

void demothrd_m1e1_8007D404(Actor_demothrd *pActor, dmo_data_0x18 *p0x18, dmo_model_0x14 *p0x14, dmo_model_0x1A4 *p0x1A4)
{
  dmo_m1e1_data *pData;
  int tmp1;
  int i;
  SVECTOR vec;
  SVECTOR vecTmp;
  SVECTOR smokeVecs[10];

  pData = p0x1A4->field_1A0_pM1OrHind;
  for (i = 0; i < 3; i++)
  {
    GM_ActMotion_80034A7C(&pData->field_0[0][i].field_0);
    GM_ActMotion_80034A7C(&pData->field_0[1][i].field_0);
  }

  DG_SetPos2_8001BC8C(&p0x1A4->field_0_ctrl.field_0_mov, &p0x1A4->field_0_ctrl.field_8_rotator);
  DG_RotatePos_8001BD64(&p0x1A4->field_A0[0]);

  M1E1GetCaterpillerVertex_800815FC(&p0x1A4->field_1A0_pM1OrHind->field_0[0][0], &p0x1A4->field_1A0_pM1OrHind->field_0[1][0], smokeVecs, 1);
  for (i = 0; i < 10; i++)
  {
    smokeVecs[i].vy = smokeVecs[i].vy + 300;
  }

  DG_PutVector_8001BE48(smokeVecs, smokeVecs, 10);

  memset(&vec, 0, sizeof(SVECTOR));
  vec.vx = pData->field_0[1][0].field_0.objs->objs[0].model->max_8.field_0_x + ((pData->field_0[1][0].field_0.objs->objs[0].model->min_14.field_0_x - pData->field_0[1][0].field_0.objs->objs[0].model->max_8.field_0_x) / 2);
  DG_PutVector_8001BE48(&vec, &vec, 1);

  vecTmp.vx = vec.vx - pData->field_564[0].vx;
  vecTmp.vy = vec.vy - pData->field_564[0].vy;
  vecTmp.vz = vec.vz - pData->field_564[0].vz;

  tmp1 = magic_calc(&vecTmp, p0x1A4);

  if (abs(tmp1) >= pData->field_560)
  {
    AN_CaterpillerSmoke_8007DA28(&smokeVecs[rand_8008E6B8() % 5]);
    DG_InvisibleObjs(pData->field_0[0][pData->field_558_idx[0]].field_0.objs);
    if (tmp1 > 0)
    {
      pData->field_558_idx[0]++;
    }
    else
    {
      pData->field_558_idx[0]--;
    }
    if (pData->field_558_idx[0] < 0)
    {
      pData->field_558_idx[0] = 2;
    }
    if (pData->field_558_idx[0] >= 3)
    {
      pData->field_558_idx[0] = 0;
    }
    DG_VisibleObjs(pData->field_0[0][pData->field_558_idx[0]].field_0.objs);
    pData->field_564[0] = vec;
  }


  memset(&vec, 0, sizeof(SVECTOR));
  vec.vx = pData->field_0[1][0].field_0.objs->objs[0].model->max_8.field_0_x + ((pData->field_0[1][0].field_0.objs->objs[0].model->min_14.field_0_x - pData->field_0[1][0].field_0.objs->objs[0].model->max_8.field_0_x) / 2);
  DG_SetPos2_8001BC8C(&p0x1A4->field_0_ctrl.field_0_mov, &p0x1A4->field_0_ctrl.field_8_rotator);

  DG_PutVector_8001BE48(&vec, &vec, 1);
  vecTmp.vx = vec.vx - pData->field_564[1].vx;
  vecTmp.vy = vec.vy - pData->field_564[1].vy;
  vecTmp.vz = vec.vz - pData->field_564[1].vz;

  tmp1 = magic_calc(&vecTmp, p0x1A4);

  if (abs(tmp1) >= pData->field_560)
  {
    AN_CaterpillerSmoke_8007DA28(&smokeVecs[(rand_8008E6B8() % 5) + 5]);
    DG_InvisibleObjs(pData->field_0[1][pData->field_558_idx[1]].field_0.objs);
    if (tmp1 > 0)
    {
      pData->field_558_idx[1]++;
    }
    else
    {
      pData->field_558_idx[1]--;
    }
    if (pData->field_558_idx[1] < 0)
    {
      pData->field_558_idx[1] = 2;
    }
    if (pData->field_558_idx[1] >= 3)
    {
      pData->field_558_idx[1] = 0;
    }
    DG_VisibleObjs(pData->field_0[1][pData->field_558_idx[1]].field_0.objs);
    pData->field_564[1] = vec;
  }
  DG_SetPos2_8001BC8C(&p0x1A4->field_0_ctrl.field_0_mov, &p0x1A4->field_0_ctrl.field_8_rotator);
  DG_RotatePos_8001BD64(p0x1A4->field_A0);
  for (i = 0; i < 3; i++)
  {
    GM_ActObject_80034AF4(&pData->field_0[0][i].field_0);
    GM_ActObject_80034AF4(&pData->field_0[1][i].field_0);
  }
}

void demothrd_hind_8007D9C8(Actor_demothrd *pActor, dmo_data_0x18 *pDmoData0x18, dmo_model_0x14 *p0x14, dmo_model_0x1A4 *p0x1A4)
{
    dmo_hind *pTmp = (dmo_hind *)p0x1A4->field_1A0_pM1OrHind; // TODO: Would be cleaner as a union

    pTmp->field_8 = pTmp->field_8 - pTmp->field_0;
    if ( pTmp->field_8 < 0 )
    {
        pTmp->field_8 = pTmp->field_8 + 4096;
    }

    pTmp->field_C = pTmp->field_C - pTmp->field_4;
    if ( pTmp->field_C < 0 )
    {
        pTmp->field_C = pTmp->field_C + 4096;
    }

    p0x1A4->field_AA = pTmp->field_8;
    p0x1A4->field_B0 = pTmp->field_C;
}


void AN_CaterpillerSmoke_8007DA28(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT  pre = {{ 0 }};

    pre.pos = *pos;

    anm = &stru_8009F73C;
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8( NULL, 0, anm );
}

#pragma INCLUDE_ASM("asm/Kojo/demothrd_2_8007DA94.s")                              // 400 bytes
#pragma INCLUDE_ASM("asm/Kojo/sub_8007DC24.s")                                     // 348 bytes
#pragma INCLUDE_ASM("asm/sub_8007DD80.s")                                          // 400 bytes

void sub_8007DF10(SVECTOR *pRotation, SVECTOR *pTranslation)
{
    ANIMATION *anm;
    SVECTOR    vin[3];
    SVECTOR    vout[3];
    PRESCRIPT  pre;

    pre.speed = DG_ZeroVector_800AB39C;

    vin[0] = DG_ZeroVector_800AB39C;
    vin[0].vz = 500;

    vin[1] = DG_ZeroVector_800AB39C;
    vin[1].vz = 2000;

    vin[2] = DG_ZeroVector_800AB39C;
    vin[2].vz = 3000;

    DG_SetPos2_8001BC8C(pTranslation, pRotation);
    DG_PutVector_8001BE48(vin, vout, 3);

    anm = &stru_8009F790;
    anm->field_14_pre_script = &pre;

    pre.pos = vout[0];
    pre.scr_num = 0;
    NewAnime_8005FBC8( NULL, 0, anm );

    pre.pos = vout[1];
    pre.scr_num = 1;
    NewAnime_8005FBC8( NULL, 0, anm );

    pre.pos = vout[2];
    pre.scr_num = 2;
    NewAnime_8005FBC8( NULL, 0, anm );
}

void sub_8007E0AC(int y, SVECTOR *pPosition)
{
    ANIMATION *anm;
    SVECTOR    rotation;
    SVECTOR    vin;
    PRESCRIPT  pre[8];
    int        i;

    rotation.vx = 0;
    rotation.vy = y;
    rotation.vz = 0;

    vin = DG_ZeroVector_800AB39C;

    for ( i = 0; i < 8; i++ )
    {
        pre[i].pos = *pPosition;

        vin.vx = GV_RandU_80017090(64);
        vin.vz = GV_RandU_80017090(64);

        rotation.vz += 512;

        DG_SetPos2_8001BC8C(&DG_ZeroVector_800AB39C, &rotation);
        DG_PutVector_8001BE48(&vin, &pre[i].speed, 1);
        pre[i].scr_num = 0;
    }

    anm = &stru_8009F774;
    anm->field_14_pre_script = pre;

    NewAnime_8005FBC8( NULL, 0, anm );
}

#pragma INCLUDE_ASM("asm/sub_8007E1C0.s")                                          // 3444 bytes

void sub_8007EF34(SVECTOR *pOutVec1, SVECTOR *pOutVec2, MATRIX *pInMtx)
{
  int tmp;
  int distance;
  MATRIX rotMtx;
  SVECTOR vec1;
  SVECTOR vec2;
  ReadRotMatrix_80092DD8(&rotMtx);
  pOutVec1->vx = pInMtx->t[0];
  pOutVec1->vy = pInMtx->t[1];
  pOutVec1->vz = pInMtx->t[2];
  DG_SetPos_8001BC44(pInMtx);
  vec1.vx = 0;
  vec1.vy = 0;
  vec1.vz = 0;
  vec2.vx = 0;
  vec2.vy = 0;
  vec2.vz = 100;
  DG_PutVector_8001BE48(&vec1, &vec1, 1);
  DG_PutVector_8001BE48(&vec2, &vec2, 1);
  tmp = (short) (vec2.vx - vec1.vx) * (short) (vec2.vx - vec1.vx);
  vec2.vx -= vec1.vx;
  vec2.vy -= vec1.vy;
  vec2.vz -= vec1.vz;
  distance = SquareRoot0_80092708(tmp + (vec2.vz * vec2.vz));
  pOutVec2->vx = -((short) ratan2_80094308(vec2.vy, distance));
  pOutVec2->vy = ratan2_80094308(vec2.vx, vec2.vz);
  pOutVec2->vz = 0;
  DG_SetPos_8001BC44(&rotMtx);
}

void sub_8007F06C(int *param_1, int *param_2, int *param_3)
{
    param_1[0] = param_2[0];
    param_1[1] = param_2[1];
    param_1[2] = param_2[2];
    param_1[3] = param_3[0] - param_2[0];
    param_1[4] = param_3[1] - param_2[1];
    param_1[5] = param_3[2] - param_2[2];
}

#pragma INCLUDE_ASM("asm/sub_8007F0D0.s")                                          // 268 bytes
#pragma INCLUDE_ASM("asm/sub_8007F1DC.s")                                          // 348 bytes

void InitChain_8007F338(Actor_demothrd_0x78_Chain *pSub)
{
    if (pSub)
    {
        pSub->field_0_pPrev = pSub;
        pSub->field_4_pNext = pSub;
    }
}

void Chain_Add_8007F350(Actor_demothrd_0x78_Chain *pRoot, Actor_demothrd_0x78_Chain *pAdd)
{
    Actor_demothrd_0x78_Chain *prev; // $v0

    if (pRoot)
    {
        if (pAdd)
        {
            prev = pRoot->field_0_pPrev;
            pAdd->field_4_pNext = pRoot;
            pAdd->field_0_pPrev = prev;
            if (pRoot->field_0_pPrev == pRoot)
            {
                pRoot->field_4_pNext = pAdd;
            }
            else
            {
                pRoot->field_0_pPrev->field_4_pNext = pAdd;
            }
            pRoot->field_0_pPrev = pAdd;
        }
    }
}

void Chain_Remove_8007F394(Actor_demothrd_0x78_Chain *pRoot, Actor_demothrd_0x78_Chain *pRemove)
{
    int pPrev;

    if (pRoot && pRemove)
    {
        pPrev = pRemove->field_0_pPrev == pRoot;
        if (pPrev)
        {
            pRoot->field_4_pNext = pRemove->field_4_pNext;
        }
        else
        {
            pRemove->field_0_pPrev->field_4_pNext = pRemove->field_4_pNext;
        }
        pRemove->field_4_pNext->field_0_pPrev = pRemove->field_0_pPrev;
        InitChain_8007F338(pRemove);
    }
}

#pragma INCLUDE_ASM("asm/Kojo/sub_8007F3F8.s")                       // 1944 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_4_helper_helper_8007FB90.s")  // 584 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_4_helper_helper2_8007FDD8.s") // 452 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_4_helper_helper3_8007FF9C.s") // 316 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_4_helper_helper4_800800D8.s") // 2888 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_4_helper_80080C20.s")         // 296 bytes

#pragma INCLUDE_ASM("asm/Kojo/demothrd_Screen_Chanl_80080D48.s")                // 204 bytes
/*
void demothrd_Screen_Chanl_80080D48(DG_CHNL *pOt, int idx)
{
    DG_OBJS **mQueue;
    int       i;

    mQueue = pOt->mQueue;

    *((MATRIX *)0x1F800000) = pOt->field_10_transformation_matrix;
    DG_800174DC((MATRIX *)0x1F800000);

    *((int *)0x1F80001C) = 0;
    *((int *)0x1F800018) = 0;
    *((int *)0x1F800014) = 0;

    *((SVECTOR *)0x1F800380) = *(SVECTOR*)&pOt->field_30_matrix.t[0];

    for (i = pOt->mTotalObjectCount; i > 0; --i)
    {
        demothrd_4_helper_80080C20(*mQueue++);
    }
}
*/

#pragma INCLUDE_ASM("asm/Kojo/sub_80080E14.s")                       // 2024 bytes

void M1E1GetCaterpillerVertex_800815FC(dmo_m1e1_entry *pE1, dmo_m1e1_entry *pE2, SVECTOR *pSmokeVecs, int a4)
{
    DG_MDL *model; // $v0
    int field_0_x; // $v1
    DG_MDL *v8; // $v0
    int v9; // $v1

    model = pE1->field_0.objs->objs[0].model;
    field_0_x = model->max_8.field_0_x;
    if ( a4 == 1 )
    {
        field_0_x += (model->min_14.field_0_x - field_0_x) >> 1;
    }

    pSmokeVecs[0].vx = field_0_x;
    pSmokeVecs[0].vy = pE1->field_0.objs->objs[0].model->max_8.field_4_y;
    pSmokeVecs[0].vz = 2 * pE1->field_0.objs->objs[0].model->min_14.field_8_z / 3;

    pSmokeVecs[1].vx = field_0_x;
    pSmokeVecs[1].vy = pE1->field_0.objs->objs[0].model->max_8.field_4_y;
    pSmokeVecs[1].vz = pE1->field_0.objs->objs[0].model->min_14.field_8_z / 3;

    pSmokeVecs[2].vx = field_0_x;
    pSmokeVecs[2].vy = pE1->field_0.objs->objs[0].model->max_8.field_4_y;
    pSmokeVecs[2].vz = 0;

    pSmokeVecs[3].vx = field_0_x;
    pSmokeVecs[3].vy = pE1->field_0.objs->objs[0].model->max_8.field_4_y;
    pSmokeVecs[3].vz = pE1->field_0.objs->objs[0].model->max_8.field_8_z / 3;

    pSmokeVecs[4].vx = field_0_x;
    pSmokeVecs[4].vy = pE1->field_0.objs->objs[0].model->max_8.field_4_y;
    pSmokeVecs[4].vz = (2 * pE1->field_0.objs->objs[0].model->max_8.field_8_z) / 3;

    v8 = pE2->field_0.objs->objs[0].model;
    v9 = v8->min_14.field_0_x;
    if ( a4 == 1 )
    {
        v9 += (v8->max_8.field_0_x - v9) >> 1;
    }

    pSmokeVecs[5].vx = v9;
    pSmokeVecs[5].vy = pE2->field_0.objs->objs[0].model->max_8.field_4_y;
    pSmokeVecs[5].vz = 2 * pE2->field_0.objs->objs[0].model->min_14.field_8_z / 3;

    pSmokeVecs[6].vx = v9;
    pSmokeVecs[6].vy = pE2->field_0.objs->objs[0].model->max_8.field_4_y;
    pSmokeVecs[6].vz = pE2->field_0.objs->objs[0].model->min_14.field_8_z / 3;

    pSmokeVecs[7].vx = v9;
    pSmokeVecs[7].vy = pE2->field_0.objs->objs[0].model->max_8.field_4_y;
    pSmokeVecs[7].vz = 0;

    pSmokeVecs[8].vx = v9;
    pSmokeVecs[8].vy = pE2->field_0.objs->objs[0].model->max_8.field_4_y;
    pSmokeVecs[8].vz = pE2->field_0.objs->objs[0].model->max_8.field_8_z / 3;

    pSmokeVecs[9].vx = v9;
    pSmokeVecs[9].vy = pE2->field_0.objs->objs[0].model->max_8.field_4_y;
    pSmokeVecs[9].vz = 2 * pE2->field_0.objs->objs[0].model->max_8.field_8_z / 3;
}
