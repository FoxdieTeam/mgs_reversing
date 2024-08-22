#include "common.h"
#include "demothrd.h"
#include "libdg/libdg.h"
#include "libgcl/hash.h"
#include "Anime/animeconv/anime.h"
#include "Bullet/blast.h"
#include "Game/linkvarbuf.h"

extern SVECTOR          DG_ZeroVector_800AB39C;
extern MATRIX           DG_ZeroMatrix_8009D430;
extern int              GV_Time_800AB330;
extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;
extern int              GM_PadVibration2_800ABA54;
extern int              GM_PadVibration_800ABA3C;
extern Blast_Data       blast_data_8009F4B8[8];
extern GM_Camera        GM_Camera_800B77E8;

void demothrd_Screen_Chanl_80080D48(DG_CHNL *pChnl, int idx);
void InitChain_8007F338(DemothrdWork_0x78_Chain *pSub);
void Chain_Remove_8007F394(DemothrdWork_0x78_Chain *pRoot, DemothrdWork_0x78_Chain *pRemove);
void demothrd_hind_8007D9C8(DemothrdWork *work, dmo_data_0x18 *pDmoData0x18, dmo_model_0x14 *p0x14, dmo_model_0x1A4 *p0x1A4);
void demothrd_m1e1_8007D404(DemothrdWork *work, dmo_data_0x18 *p0x18, dmo_model_0x14 *p0x14, dmo_model_0x1A4 *p0x1A4);
void AN_CaterpillerSmoke_8007DA28(SVECTOR *pos);
void M1E1GetCaterpillerVertex_800815FC(OBJECT *pE1, OBJECT *pE2, SVECTOR *pSmokeVecs, int a4);
void DG_8001CDB8(DG_OBJS *pObjs);
void sub_80032B40(SVECTOR *svec, unsigned int param_2, int param_3);

int CreateDemo_80079B50(DemothrdWork* pThis, demothrd_0x1C* pDmoData)
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

    pOldRendFunc = DG_SetChanlSystemUnits_80018598(DG_CHANL_SCREEN, demothrd_Screen_Chanl_80080D48);

    pThis->field_270_pOldRenderFn = pOldRendFunc;
    pThis->field_274_old_game_state_flags = GM_GameStatus_800AB3CC;
    pThis->field_278 = GM_Camera_800B77E8;

    pThis->field_2F4_old_equipped_item = GM_CurrentItemId;
    pThis->field_2F8_old_equipped_weapon = GM_CurrentWeaponId;

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
    memcpy(
        (char*)pThis->field_30_dmo_header->field_14_pMaps,
        (char*)pDmoData->field_14_pMaps,
        sizeof(Dmo_Map8) * pThis->field_30_dmo_header->field_C_num_maps);

    memcpy(
        pThis->field_30_dmo_header->field_18_pModels,
        (char*)pDmoData->field_18_pModels,
        sizeof(dmo_model_0x14) * pThis->field_30_dmo_header->field_10_num_models);

    pMapsIter = (Dmo_Map8*)pThis->field_30_dmo_header->field_14_pMaps;

    scene_no = 0;
    if (pThis->field_30_dmo_header->field_C_num_maps > 0) {
        while (1) {

            if (!GV_GetCache_8001538C(pMapsIter->field_0)) {
                printf("Noload model ( Stage )\n");
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
                printf("Noload model ( Scene = No.%d )\n", scene_no +1);
                asm(""); // TODO hack!
                return 0;
            }

            if (GM_InitLoader_8002599C(&pModels0x1A4Iter->field_0_ctrl, pModel0x14Iter->field_10, pThis->field_28_map) < 0) {
                printf("Error init control ( Scene = No.%d )\n", scene_no + 1);
                return 0;
            }

            pModels0x1A4Iter->field_0_ctrl.field_36 = 0;
            pModels0x1A4Iter->field_0_ctrl.field_54 = 0;

            if (((pModel0x14Iter)->field_4_flags & 1) != 0) {

                GM_InitObject_80034A18(&pModels0x1A4Iter->field_7C_obj, pModel0x14Iter->field_C_hashCode, 79, 0);
            }
            else {
                if ((pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o4a")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o5a")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o6a")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o7a")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o8a")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o9a")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o10a")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o4b")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o5b")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o6b")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o7b")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o8b")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o9b")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o10b")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o4c")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o5c")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o6c")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o7c")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o8c")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o9c")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("16d_o10c")) {
                    GM_InitObject_80034A18(&pModels0x1A4Iter->field_7C_obj, (pModel0x14Iter)->field_C_hashCode, 5, 0);
                }
                else if ((pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("02a_r8")) {

                    pModels0x1A4Iter->field_160_mtx[0].t[0] = 100;
                    pModels0x1A4Iter->field_160_mtx[0].t[1] = 110;
                    pModels0x1A4Iter->field_160_mtx[0].t[2] = 110;

                    GM_InitObject_80034A18(&pModels0x1A4Iter->field_7C_obj, (pModel0x14Iter)->field_C_hashCode, 0x10D, 0);
                }
                else if ((pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("mgrexw")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("mgrexll")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("mgrexrl")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("pit_t")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("pit_u")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("pit_liq")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("radar_f1")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("radar_f2")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("radar_f3")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("l_hatch1")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("l_hatch2")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("l_hatch3")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("l_hatch4")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("r_hatch1")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("r_hatch2")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("r_hatch3")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("r_hatch4")) {

                    pModels0x1A4Iter->field_160_mtx[0].t[0] = 64;
                    pModels0x1A4Iter->field_160_mtx[0].t[1] = 64;
                    pModels0x1A4Iter->field_160_mtx[0].t[2] = 64;
                    GM_InitObject_80034A18(&pModels0x1A4Iter->field_7C_obj, (pModel0x14Iter)->field_C_hashCode, 0x10D, 0);
                }
                else {
                    GM_InitObject_80034A18(&pModels0x1A4Iter->field_7C_obj, (pModel0x14Iter)->field_C_hashCode, 13, 0);
                }

                mtx = pModels0x1A4Iter->field_160_mtx;
                GM_ConfigObjectJoint_80034CB4(&pModels0x1A4Iter->field_7C_obj);
                GM_ConfigObjectLight_80034C44(&pModels0x1A4Iter->field_7C_obj, mtx);

                DG_InvisibleObjs(pModels0x1A4Iter->field_7C_obj.objs);

                if ((pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("m1e1")
                    || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("m1e1demo")) {
                    pM1Data = (dmo_m1e1_data*)GV_Malloc_8001620C(sizeof(dmo_m1e1_data));
                    pModels0x1A4Iter->field_1A0_pM1OrHind = pM1Data;
                    if (!pM1Data) {
                        return 0;
                    }
                    memset(pM1Data, 0, sizeof(dmo_m1e1_data));
                    GM_InitObject_80034A18(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[0][0], GV_StrCode_80016CCC("m1e1cl1"), 301, 0);
                    GM_InitObject_80034A18(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[0][1], GV_StrCode_80016CCC("m1e1cl2"), 301, 0);
                    GM_InitObject_80034A18(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[0][2], GV_StrCode_80016CCC("m1e1cl3"), 301, 0);

                    GM_InitObject_80034A18(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[1][0], GV_StrCode_80016CCC("m1e1cr1"), 301, 0);
                    GM_InitObject_80034A18(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[1][1], GV_StrCode_80016CCC("m1e1cr2"), 301, 0);
                    GM_InitObject_80034A18(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[1][2], GV_StrCode_80016CCC("m1e1cr3"), 301, 0);

                    GM_ConfigObjectJoint_80034CB4(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[0][0]);
                    GM_ConfigObjectJoint_80034CB4(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[0][1]);
                    GM_ConfigObjectJoint_80034CB4(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[0][2]);

                    GM_ConfigObjectJoint_80034CB4(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[1][0]);
                    GM_ConfigObjectJoint_80034CB4(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[1][1]);
                    GM_ConfigObjectJoint_80034CB4(&(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[1][2]);

                    GM_ConfigObjectLight_80034C44(
                        &(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[0][0],
                        mtx);
                    GM_ConfigObjectLight_80034C44(
                        &(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[0][1],
                        mtx);
                    GM_ConfigObjectLight_80034C44(
                        &(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[0][2],
                        mtx);

                    GM_ConfigObjectLight_80034C44(
                        &(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[1][0],
                        mtx);
                    GM_ConfigObjectLight_80034C44(
                        &(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[1][1],
                        mtx);
                    GM_ConfigObjectLight_80034C44(
                        &(pModels0x1A4Iter->field_1A0_pM1OrHind)->field_0[1][2],
                        mtx);

                    (pModels0x1A4Iter->field_1A0_pM1OrHind)->field_560 = 83;
                }
                else {
                    if ((pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("hind")
                        || (pModel0x14Iter)->field_C_hashCode == GV_StrCode_80016CCC("hinddemo")) {
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

        if (!GV_GetCache_8001538C(GV_CacheID2_800152FC("null", 'k'))) {
            printf("Noload model ( null.kmd )\n");
        }
        else {
            if (GM_InitLoader_8002599C(&pThis->field_C4_ctrl, 0, pThis->field_28_map) >= 0) {
                pThis->field_C4_ctrl.field_36 = 0;
                pThis->field_C4_ctrl.field_54 = 0;
                GM_InitObject_80034A18(&pThis->field_140_obj, GV_StrCode_80016CCC("null"), 13, 0);
                GM_ConfigObjectJoint_80034CB4(&pThis->field_140_obj);
                GM_ConfigObjectLight_80034C44(&pThis->field_140_obj, pThis->field_224_light_mtx);
                GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_32;
                DG_InvisibleObjs(pThis->field_140_obj.objs);
                return 1;
            }
            else {
                printf("Error init control ( null.kmd )\n");
            }
        }
    }
    return 0;
}

int DestroyDemo_8007A66C(DemothrdWork *work)
{
  DemothrdWork_0x78_Chain *i;
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

  if ((work->field_20_flag & 2) != 0)
  {
    GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_25;
  }
  for (i = work->field_38.field_4_pNext; i != (&work->field_38); i = work->field_38.field_4_pNext)
  {
    pPrevious = i->field_C_actor1;
    if (pPrevious)
    {
      GV_DestroyOtherActor_800151D8(pPrevious);
    }
    pNext = i->field_10_actor2;
    if (pNext)
    {
      GV_DestroyOtherActor_800151D8(pNext);
    }
    Chain_Remove_8007F394(&work->field_38, i);
    GV_Free_80016230(i);
  }

  field_34_pModels = work->field_34_pModels;
  if (field_34_pModels)
  {
    pModelIter = work->field_34_pModels;

    pModelIter_1 = work->field_30_dmo_header->field_18_pModels;
    mdlNum = 0;
    if (work->field_30_dmo_header->field_10_num_models > mdlNum)
    {
      do
      {
        GM_FreeObject_80034BF8(&pModelIter->field_7C_obj);
        if (pModelIter->field_1A0_pM1OrHind)
        {
          if (((pModelIter_1->field_C_hashCode) == GV_StrCode_80016CCC("m1e1")) || ((pModelIter_1->field_C_hashCode) == GV_StrCode_80016CCC("m1e1demo")))
          {
            GM_FreeObject_80034BF8(&pModelIter->field_1A0_pM1OrHind->field_0[0][0]);
            GM_FreeObject_80034BF8(&pModelIter->field_1A0_pM1OrHind->field_0[0][1]);
            GM_FreeObject_80034BF8(&pModelIter->field_1A0_pM1OrHind->field_0[0][2]);
            GM_FreeObject_80034BF8(&pModelIter->field_1A0_pM1OrHind->field_0[1][0]);
            GM_FreeObject_80034BF8(&pModelIter->field_1A0_pM1OrHind->field_0[1][1]);
            GM_FreeObject_80034BF8(&pModelIter->field_1A0_pM1OrHind->field_0[1][2]);
          }
          GV_Free_80016230(pModelIter->field_1A0_pM1OrHind);
        }
        mdlNum++;
        pModelIter_1++;
        pModelIter++;
      }
      while (mdlNum < work->field_30_dmo_header->field_10_num_models);
    }
    GM_FreeControl_800260CC(&pModelIter->field_0_ctrl);
    GV_Free_80016230(work->field_34_pModels);
  }
  GM_FreeObject_80034BF8(&work->field_140_obj);
  GM_FreeControl_800260CC(&work->field_C4_ctrl);
  pHeader = work->field_30_dmo_header;
  if (pHeader)
  {
    pMaps = (void *) pHeader->field_14_pMaps;
    if (pMaps)
    {
      GV_Free_80016230(pMaps);
    }
    pMods = work->field_30_dmo_header->field_18_pModels;
    if (pMods)
    {
      GV_Free_80016230(pMods);
    }
    GV_Free_80016230(work->field_30_dmo_header);
  }
  field_270_pOldRenderFn = work->field_270_pOldRenderFn;
  GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_32;
  DG_SetChanlSystemUnits_80018598(DG_CHANL_SCREEN, field_270_pOldRenderFn);
  GM_GameStatus_800AB3CC = work->field_274_old_game_state_flags;
  GM_Camera_800B77E8 = work->field_278;
  GM_CurrentItemId = work->field_2F4_old_equipped_item;
  GM_CurrentWeaponId = work->field_2F8_old_equipped_weapon;
  return 1;
}

void Chain_Add_8007F350(DemothrdWork_0x78_Chain *pRoot, DemothrdWork_0x78_Chain *pAdd);
int  demothrd_make_chara_8007AE10(DemothrdWork *work, dmo_data_0x36 *pData, DemothrdWork_0x78_Chain *pChain);
int  demothrd_8007CDF8(DemothrdWork *work, dmo_data_0x28 *pDmoData, DemothrdWork_0x78_Chain *pChain);
int  demothrd_1_FrameRunDemo_helper4_8007CF14(DemothrdWork *work, dmo_data_0x28 *pDmo);
int  demothrd_8007CFE8(DemothrdWork *work, dmo_data_0x18 *pDmoData0x18);

int demothrd_1_FrameRunDemo_8007A948(DemothrdWork *pThis, dmo_data_0x28 *pDmoData)
{
    SVECTOR                    tmpVec1;
    SVECTOR                    tmpVec2;
    VECTOR                     tmpVec3;
    int                        root;
    int                        i;
    dmo_data_0x34             *pDmoData_0x34;
    DemothrdWork_0x78_Chain *pChain;
    DemothrdWork_0x78_Chain *pNext;
    dmo_data_0x18             *field_24_pDmoEnd;

    pDmoData->field_1C_dmo_data_offset = (dmo_data_0x34 *)((unsigned int)pDmoData + (unsigned int)pDmoData->field_1C_dmo_data_offset);
    pDmoData->field_24_pDmoEnd = (dmo_data_0x18 *)((unsigned int)pDmoData + (unsigned int)pDmoData->field_24_pDmoEnd);

    pThis->field_C4_ctrl.mov.vx = pDmoData->field_8_xpos;
    pThis->field_C4_ctrl.mov.vy = pDmoData->field_A_ypos;
    pThis->field_C4_ctrl.mov.vz = pDmoData->field_C_zpos;

    tmpVec1.vx = (pDmoData->field_E_x - pDmoData->field_8_xpos) >> 2;
    tmpVec1.vx = (pDmoData->field_10_y - pDmoData->field_A_ypos) >> 2;
    tmpVec1.vx = (pDmoData->field_12_z - pDmoData->field_C_zpos) >> 2;

    root = SquareRoot0(tmpVec1.vx  * tmpVec1.vx  + tmpVec1.vz * tmpVec1.vz);

    pThis->field_C4_ctrl.rot.vx = ratan2(tmpVec1.vy, root);
    pThis->field_C4_ctrl.rot.vy = ratan2(tmpVec1.vx, tmpVec1.vz);
    pThis->field_C4_ctrl.rot.vz = pDmoData->field_14_z;

    GM_ActControl_80025A7C(&pThis->field_C4_ctrl);
    GM_ActObject2_80034B88(&pThis->field_140_obj);
    DG_GetLightMatrix_8001A3C4(&pThis->field_C4_ctrl.mov, pThis->field_224_light_mtx);

    pThis->field_268 = 0;
    pThis->field_26C = 0;

    for ( pChain = pThis->field_38.field_4_pNext; pChain != &pThis->field_38; pChain = pChain->field_4_pNext )
    {
        *(int *)pChain->field_8_fileNameBuffer = 0;
    }

    pDmoData_0x34 = pDmoData->field_1C_dmo_data_offset;

    for ( i = 0; i < pDmoData->field_18_count; i++, pDmoData_0x34++ )
    {
        pChain = pThis->field_38.field_4_pNext;

        if ( pChain != &pThis->field_38 )
        {
            do
            {
                if ( pChain->field_14[0].field_0_type == pDmoData_0x34->field_0)
                {
                    *(int *)pChain->field_8_fileNameBuffer = 1;
                    break;
                }

                pChain = pChain->field_4_pNext;
            }
            while ( pChain != &pThis->field_38 );

            if ( pChain->field_14[0].field_0_type == pDmoData_0x34->field_0 )
            {
                continue;
            }
        }

        pChain = GV_Malloc_8001620C(sizeof(DemothrdWork_0x78_Chain));

        if ( !pChain )
        {
            return 1;
        }

        memset(pChain, 0, 0x78);
        Chain_Add_8007F350(&pThis->field_38, pChain);

        *(int *)pChain->field_8_fileNameBuffer = 1;

        memcpy(pChain->field_14, pDmoData_0x34, sizeof(dmo_data_0x34));

        // This function uses offset 0x34 of pDmoData_0x34 despite it seemingly only being 0x34 bytes in size
        if ( !demothrd_make_chara_8007AE10(pThis, (dmo_data_0x36 *)pDmoData_0x34, pChain) )
        {
            return 0;
        }
    }

    for ( pNext = pThis->field_38.field_4_pNext; pNext != &pThis->field_38; )
    {
        pChain = pNext;
        pNext = pChain->field_4_pNext;

        if ( *(int *)pChain->field_8_fileNameBuffer != 1 && !pChain->field_C_actor1 )
        {
            Chain_Remove_8007F394(&pThis->field_38, pChain);
            GV_Free_80016230(pChain);
        }
    }

    for ( pChain = pThis->field_38.field_4_pNext; pChain != &pThis->field_38; pChain = pChain->field_4_pNext )
    {
        if ( !demothrd_8007CDF8(pThis, pDmoData, pChain) )
        {
            return 0;
        }
    }

    demothrd_1_FrameRunDemo_helper4_8007CF14(pThis, pDmoData);

    for ( i = 0, field_24_pDmoEnd = pDmoData->field_24_pDmoEnd; i < pDmoData->field_20_count; i++, field_24_pDmoEnd++ )
    {
        if ( !demothrd_8007CFE8(pThis, field_24_pDmoEnd) )
        {
            return 0;
        }
    }

    gUnkCameraStruct2_800B7868.eye.vx = pDmoData->field_8_xpos;
    gUnkCameraStruct2_800B7868.eye.vy = pDmoData->field_A_ypos;
    gUnkCameraStruct2_800B7868.eye.vz = pDmoData->field_C_zpos;

    gUnkCameraStruct2_800B7868.center.vx = pDmoData->field_E_x;
    gUnkCameraStruct2_800B7868.center.vy = pDmoData->field_10_y;
    gUnkCameraStruct2_800B7868.center.vz = pDmoData->field_12_z;

    DG_Chanl(0)->field_50_clip_distance = pDmoData->field_16;

    tmpVec1.vx = pDmoData->field_E_x - pDmoData->field_8_xpos;
    tmpVec1.vy = pDmoData->field_10_y - pDmoData->field_A_ypos;
    tmpVec1.vz = pDmoData->field_12_z - pDmoData->field_C_zpos;
    root = SquareRoot0(tmpVec1.vx * tmpVec1.vx + tmpVec1.vz * tmpVec1.vz);

    tmpVec2.vx = -ratan2(tmpVec1.vy, root);
    tmpVec2.vy = ratan2(tmpVec1.vx, tmpVec1.vz);
    tmpVec2.vz = 2048;

    tmpVec1.vx = pDmoData->field_8_xpos;
    tmpVec1.vy = pDmoData->field_A_ypos;
    tmpVec1.vz = pDmoData->field_C_zpos;

    DG_SetPos2_8001BC8C(&tmpVec1, &tmpVec2);
    memset(&tmpVec2, 0, 8);

    tmpVec2.vz = pDmoData->field_14_z;

    DG_RotatePos_8001BD64(&tmpVec2);
    ReadRotMatrix(&DG_Chanl(0)->field_30_eye);

    DG_TransposeMatrix_8001EAD8(&DG_Chanl(0)->field_30_eye, &DG_Chanl(0)->field_10_eye_inv);

    tmpVec3.vx = -DG_Chanl(0)->field_30_eye.t[0];
    tmpVec3.vy = -DG_Chanl(0)->field_30_eye.t[1];
    tmpVec3.vz = -DG_Chanl(0)->field_30_eye.t[2];

    ApplyMatrixLV(&DG_Chanl(0)->field_10_eye_inv, &tmpVec3, (VECTOR *)DG_Chanl(0)->field_10_eye_inv.t);

    return 1;
}

int demothrd_make_chara_8007AE10(DemothrdWork *work, dmo_data_0x36 *pData, DemothrdWork_0x78_Chain *pChain)
{
    // TODO: Some funcptr calls are first cast to VoidMakeChara. This is a hack
    // to prevent those cases from being merged (GCC "cross jump" optimization).
    typedef void (*VoidMakeChara)();

    HZD_VEC                    hzdout;
    GV_MSG                     msg;
    SVECTOR                    svec1, svec2, svec3, svec4;
    MATRIX                     mat1, mat2;
    DemothrdWork_0x78_Chain *pIter;

    GV_ACT *(*funcptr)();

    dmo_model_0x14  *pDmoModel;
    dmo_model_0x1A4 *pModel;
    int              hzdret;
    int              i;

    svec1.vx = pData->field_E_vec2.vx;
    svec1.vy = pData->field_E_vec2.vy;
    svec1.vz = pData->field_E_vec2.vz;
    svec2.vx = pData->field_8_vec1.vx;
    svec2.vy = pData->field_8_vec1.vy;
    svec2.vz = pData->field_8_vec1.vz;

    DG_SetPos2_8001BC8C(&svec1, &DG_ZeroVector_800AB39C);
    ReadRotMatrix(&mat1);
    DG_SetPos2_8001BC8C(&svec1, &svec2);
    ReadRotMatrix(&mat2);

    switch (pData->field_4_type)
    {
    case 0x1:
        funcptr = GM_GetCharaID_8002A8EC(0x1);
        if (funcptr != NULL)
        {
            funcptr(&mat1, &blast_data_8009F4B8[3]);
        }
        break;

    case 0x2:
        funcptr = GM_GetCharaID_8002A8EC(0x2);
        if (funcptr != NULL)
        {
            funcptr(&svec1);
        }
        break;

    case 0x3:
    case 0x4:
        demothrd_remove_via_id_8007CD60(work, 4);

        switch (pData->field_4_type)
        {
        case 0x3:
            funcptr = GM_GetCharaID_8002A8EC(3);
            if (funcptr != NULL)
            {
                if (pData->data.variant_0x3.field_18 == 0)
                {
                    funcptr(1, pData->data.variant_0x3.field_14);
                }
                else
                {
                    funcptr(3, pData->data.variant_0x3.field_14);
                }
            }
            break;

        case 0x4:
            funcptr = GM_GetCharaID_8002A8EC(4);
            if (funcptr != NULL)
            {
                if (pData->data.variant_0x4.field_18 == 0)
                {
                    pChain->field_C_actor1 = funcptr(0, pData->data.variant_0x4.field_14);
                }
                else
                {
                    pChain->field_C_actor1 = funcptr(2, pData->data.variant_0x4.field_14);
                }
            }
            break;
        }
        break;

    case 0x5:
        funcptr = GM_GetCharaID_8002A8EC(5);
        if (funcptr != NULL)
        {
            funcptr(pData->data.variant_0x5.field_18, pData->data.variant_0x5.field_1A, 0, pData->data.variant_0x5.field_14,
                    pData->data.variant_0x5.field_1C);
        }
        break;

    case 0x6:
        funcptr = GM_GetCharaID_8002A8EC(6);
        if (funcptr != NULL)
        {
            if (pData->data.variant_0x6.field_14 == 0)
            {
                funcptr(&mat1, 2);
            }
            else
            {
                funcptr(&mat1, 0);
            }
        }
        break;

    case 0x7:
        funcptr = GM_GetCharaID_8002A8EC(7);
        if (funcptr != NULL)
        {
            if (pData->data.variant_0x7.field_14 == 0)
            {
                funcptr(&mat1, 3);
            }
            else
            {
                funcptr(&mat1, 1);
            }
        }
        break;

    case 0x8:
        funcptr = GM_GetCharaID_8002A8EC(0x8);
        if (funcptr != NULL)
        {
            funcptr(&svec1);
        }
        break;

    case 0x9:
        if (pData->data.variant_0x9.field_14 != 4)
        {
            funcptr = GM_GetCharaID_8002A8EC(9);
            if (funcptr != NULL)
            {
                funcptr(&mat2, pData->data.variant_0x9.field_14);
            }
        }
        else
        {
            funcptr = GM_GetCharaID_8002A8EC(0xA);
            if (funcptr != NULL)
            {
                funcptr(&mat2, 0xFF);
            }
        }
        break;
    case 0xA:
        funcptr = GM_GetCharaID_8002A8EC(0xB);
        if (funcptr != NULL)
        {
            funcptr(pData->data.variant_0xA.field_14, &mat2, pData->data.variant_0xA.field_18,
                    pData->data.variant_0xA.field_1A, pData->data.variant_0xA.field_1C, pData->data.variant_0xA.field_1E,
                    pData->data.variant_0xA.field_20, pData->data.variant_0xA.field_22, pData->data.variant_0xA.field_24);
        }
        break;
    case 0xB:
        funcptr = GM_GetCharaID_8002A8EC(0xC);
        if (funcptr != NULL)
        {
            funcptr(&mat2);
        }
        break;

    case 0xC:
        funcptr = GM_GetCharaID_8002A8EC(0xD);
        if (funcptr != NULL)
        {
            if (pData->data.variant_0xC.field_14 >= 4 && pData->data.variant_0xC.field_14 <= 7)
            {
                funcptr(&svec1, pData->data.variant_0xC.field_14, pData->data.variant_0xC.field_18,
                        pData->data.variant_0xC.field_1C);
            }
            else
            {
                pChain->field_C_actor1 = funcptr(&svec1, pData->data.variant_0xC.field_14, pData->data.variant_0xC.field_18,
                                                 pData->data.variant_0xC.field_1C);
            }
        }
        break;

    case 0xD:
        funcptr = GM_GetCharaID_8002A8EC(0xe);
        if (funcptr != NULL)
        {
            funcptr(&mat2);
        }
        break;

    case 0xE:
        pModel = work->field_34_pModels;
        pDmoModel = work->field_30_dmo_header->field_18_pModels;

        for (i = 0; i < work->field_30_dmo_header->field_10_num_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->field_0_type == pData->data.variant_0xE.field_14)
            {
                break;
            }
        }

        if (i >= work->field_30_dmo_header->field_10_num_models)
        {
            break;
        }

        for (pIter = work->field_38.field_4_pNext; pIter != &work->field_38; pIter = pIter->field_4_pNext)
        {
            if (pIter->field_14[0].field_4_type == 0xE && pIter->field_14[1].field_4_type == pData->data.variant_0xE.field_14)
            {
                if (pIter->field_C_actor1)
                {
                    GV_DestroyOtherActor_800151D8(pIter->field_C_actor1);
                    pIter->field_C_actor1 = NULL;
                }
            }
        }

        if (pData->data.variant_0xE.field_20 != 1)
        {
            funcptr = GM_GetCharaID_8002A8EC(0xF);
            if (funcptr != NULL)
            {
                pChain->field_C_actor1 =
                    funcptr(&pModel->field_7C_obj, pData->data.variant_0xE.field_18, &pChain->field_48, &pChain->field_4C,
                            pData->data.variant_0xE.field_22 & 0xFF, pData->data.variant_0xE.field_24 & 0xFF,
                            pData->data.variant_0xE.field_26 & 0xFF);
            }
        }
        break;

    case 0xF:
        svec1.vy += 0x64;
        hzdret = sub_800296C4(work->field_C4_ctrl.map->hzd, &svec1, 1);

        do
        {
        } while (0);
        sub_800298DC(&hzdout);

        if (hzdret & 1)
        {
            svec1.vy = hzdout.long_access[0];
        }

        else if (hzdret & 2)
        {
            svec1.vy = hzdout.long_access[1];
        }
        else
        {
            svec1.vy = pData->field_E_vec2.vy;
        }

        funcptr = GM_GetCharaID_8002A8EC(0x10);
        if (funcptr != NULL)
        {
            pChain->field_C_actor1 = funcptr(&mat2, pData->data.variant_0xF.field_14, svec1.vy);
        }
        break;

    case 0x10:
        memset(&msg, 0, sizeof(msg));
        msg.address = pData->data.variant_0x10.field_14;
        msg.message[0] = pData->data.variant_0x10.field_18;
        msg.message[1] = pData->data.variant_0x10.field_1C;
        msg.message[2] = pData->data.variant_0x10.field_20;
        msg.message[3] = pData->data.variant_0x10.field_24;
        msg.message[4] = pData->data.variant_0x10.field_28;
        msg.message[5] = pData->data.variant_0x10.field_2C;
        msg.message[6] = pData->data.variant_0x10.field_30;
        msg.message_len = 7;
        GV_SendMessage_80016504(&msg);
        break;

    case 0x11:
        funcptr = GM_GetCharaID_8002A8EC(0x11);
        if (funcptr != NULL)
        {
            ((VoidMakeChara)funcptr)(&mat2);
        }
        break;

    case 0x12:
        if (pData->data.variant_0x12.field_14 == 0)
        {
            funcptr = GM_GetCharaID_8002A8EC(0x12);
            if (funcptr != NULL)
            {
                funcptr(&svec1, pData->data.variant_0x12.field_20, pData->data.variant_0x12.field_24, &work->field_26C,
                        pData->data.variant_0x12.field_26, pData->data.variant_0x12.field_28,
                        pData->data.variant_0x12.field_2A);
            }
        }
        else if (pData->data.variant_0x12.field_14 == 1)
        {
            svec3.vx = pData->data.variant_0x12.field_16;
            svec3.vy = pData->data.variant_0x12.field_18;
            svec3.vz = pData->data.variant_0x12.field_1A;

            funcptr = GM_GetCharaID_8002A8EC(0x13);
            if (funcptr != NULL)
            {
                funcptr(&svec1, &svec3, pData->data.variant_0x12.field_1C, &work->field_26C,
                        pData->data.variant_0x12.field_26, pData->data.variant_0x12.field_28,
                        pData->data.variant_0x12.field_2A);
            }
        }
        else
        {
            work->field_26C = 1;
        }
        break;

    case 0x13:
    case 0x14:
    case 0x15:
    case 0x1E:
        pIter = work->field_38.field_4_pNext;
        while (pIter != &work->field_38)
        {
            if (pIter->field_14[0].field_4_type == 0x13 || pIter->field_14[0].field_4_type == 0x14 || pIter->field_14[0].field_4_type == 0x15 || pIter->field_14[0].field_4_type == 0x1E)
            {
                if (pIter->field_C_actor1 != NULL)
                {
                    GV_DestroyOtherActor_800151D8(pIter->field_C_actor1);
                    if (pIter->field_10_actor2 != NULL)
                    {
                        GV_DestroyOtherActor_800151D8(pIter->field_10_actor2);
                    }
                    pIter->field_C_actor1 = NULL;
                    pIter->field_10_actor2 = NULL;
                }
            }
            pIter = pIter->field_4_pNext;
        }

        switch (pData->field_4_type)
        {
        case 0x13:
            if (pData->data.variant_0x13.field_14 != 1)
            {
                funcptr = GM_GetCharaID_8002A8EC(0x14);
                if (funcptr != NULL)
                {
                    pChain->field_C_actor1 = funcptr(&work->field_C4_ctrl, &work->field_140_obj, 0);
                }
            }
            break;

        case 0x14:
            if (pData->data.variant_0x14.field_14 != 1)
            {
                funcptr = GM_GetCharaID_8002A8EC(0x15);
                if (funcptr != NULL)
                {
                    pChain->field_C_actor1 = funcptr(&work->field_C4_ctrl, &work->field_140_obj, 0);
                    if (pData->data.variant_0x14.field_16 != 0)
                    {
                        funcptr = GM_GetCharaID_8002A8EC(0x16);
                        if (funcptr != NULL)
                        {
                            pChain->field_10_actor2 = funcptr(5);
                        }
                    }
                }
            }
            break;

        case 0x15:
            if (pData->data.variant_0x15.field_14 != 1)
            {
                funcptr = GM_GetCharaID_8002A8EC(0x17);
                if (funcptr != NULL)
                {
                    pChain->field_C_actor1 = funcptr(&work->field_C4_ctrl, &work->field_140_obj, 0);
                    if (pData->data.variant_0x15.field_16 != 0)
                    {
                        funcptr = GM_GetCharaID_8002A8EC(0x18);
                        if (funcptr != NULL)
                        {
                            pChain->field_10_actor2 = funcptr(6);
                        }
                    }
                }
            }
            break;

        case 0x1E:
            if (pData->data.variant_0x1E.field_14 != 1)
            {
                funcptr = GM_GetCharaID_8002A8EC(0x22);
                if (funcptr != NULL)
                {
                    pChain->field_C_actor1 = funcptr();
                }
            }
            break;
        }
        break;

    case 0x16:
        funcptr = GM_GetCharaID_8002A8EC(0x19);
        if (funcptr != NULL)
        {
            funcptr(&svec1);
        }
        break;

    case 0x17:
        pModel = work->field_34_pModels;
        pDmoModel = work->field_30_dmo_header->field_18_pModels;

        for (i = 0; i < work->field_30_dmo_header->field_10_num_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->field_0_type == pData->data.variant_0x17.field_18)
            {
                break;
            }
        }

        if (i >= work->field_30_dmo_header->field_10_num_models)
        {
            break;
        }

        pIter = work->field_38.field_4_pNext;
        while (pIter != &work->field_38)
        {
            if ((pIter->field_14[0].field_4_type == 0x17) && (pIter->field_14[1].field_8_xy == pData->data.variant_0x17.field_18))
            {
                if (pIter->field_C_actor1 != NULL)
                {
                    GV_DestroyOtherActor_800151D8(pIter->field_C_actor1);
                    pIter->field_C_actor1 = NULL;
                }
            }
            pIter = pIter->field_4_pNext;
        }

        if (pData->data.variant_0x17.field_14 != 1 && pData->field_4_type == 0x17)
        {
            if (pData->data.variant_0x17.field_1C == 0)
            {
                funcptr = GM_GetCharaID_8002A8EC(0x1A);
                if (funcptr != NULL)
                {
                    pChain->field_C_actor1 = funcptr(&work->field_C4_ctrl, &pModel->field_7C_obj, 0);
                }
            }
            else
            {
                funcptr = GM_GetCharaID_8002A8EC(0x1B);
                if (funcptr != NULL)
                {
                    pChain->field_C_actor1 = funcptr(&work->field_C4_ctrl, &pModel->field_7C_obj, 0);
                }
            }
        }
        break;
    case 0x18:
        pModel = work->field_34_pModels;
        pDmoModel = work->field_30_dmo_header->field_18_pModels;

        for (i = 0; i < work->field_30_dmo_header->field_10_num_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->field_0_type == pData->data.variant_0x18.field_18)
            {
                break;
            }
        }

        if (i >= work->field_30_dmo_header->field_10_num_models)
        {
            break;
        }

        pIter = work->field_38.field_4_pNext;
        while (pIter != &work->field_38)
        {
            if ((pIter->field_14[0].field_4_type == 0x18) && (pIter->field_14[1].field_8_xy == pData->data.variant_0x18.field_18))
            {
                if (pIter->field_C_actor1 != NULL)
                {
                    GV_DestroyOtherActor_800151D8(pIter->field_C_actor1);
                    pIter->field_C_actor1 = NULL;
                }
            }
            pIter = pIter->field_4_pNext;
        }
        if (pData->data.variant_0x18.field_14 == 0)
        {
            funcptr = GM_GetCharaID_8002A8EC(0x1C);
            if (funcptr != NULL)
            {
                pChain->field_C_actor1 = funcptr(&pModel->field_7C_obj, pData->data.variant_0x18.field_1C);
            }
        }
        break;
    case 0x19:
        pModel = work->field_34_pModels;
        pDmoModel = work->field_30_dmo_header->field_18_pModels;

        for (i = 0; i < work->field_30_dmo_header->field_10_num_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->field_0_type == pData->data.variant_0x19.field_14)
            {
                break;
            }
        }

        if (i >= work->field_30_dmo_header->field_10_num_models)
        {
            break;
        }

        funcptr = GM_GetCharaID_8002A8EC(0x1D);
        if (funcptr != NULL)
        {
            funcptr(&pModel->field_7C_obj, pData->data.variant_0x19.field_18, pData->data.variant_0x19.field_1A,
                    pData->data.variant_0x19.field_1C, pData->data.variant_0x19.field_20);
        }
        break;
    case 0x1A:
        funcptr = GM_GetCharaID_8002A8EC(0x1E);
        if (funcptr != NULL)
        {
            funcptr(&mat2, pData->data.variant_0x1A.field_14);
        }
        break;
    case 0x1B:
        demothrd_remove_via_id_8007CD60(work, 0x1B);
        if (pData->data.variant_0x1B.field_14 == 0)
        {
            funcptr = GM_GetCharaID_8002A8EC(0x1F);
            if (funcptr != NULL)
            {
                pChain->field_C_actor1 = funcptr(pData->data.variant_0x1B.field_16, pData->data.variant_0x1B.field_18,
                                                 pData->data.variant_0x1B.field_1A);
            }
        }
        break;
    case 0x1C:
        pIter = work->field_38.field_4_pNext;
        while (pIter != &work->field_38 && (pIter->field_14[0].field_4_type != 0x1C || pIter->field_C_actor1 == NULL))
        {
            pIter = pIter->field_4_pNext;
        }
        svec1.vx = pData->data.variant_0x1C.field_14;
        svec1.vy = pData->data.variant_0x1C.field_16;
        svec1.vz = pData->data.variant_0x1C.field_18;
        svec2.vx = pData->data.variant_0x1C.field_1A;
        svec2.vy = pData->data.variant_0x1C.field_1C;
        svec2.vz = pData->data.variant_0x1C.field_1E;
        if (pIter == &work->field_38)
        {
            funcptr = GM_GetCharaID_8002A8EC(0x20);
            if (funcptr != NULL)
            {
                pChain->field_C_actor1 = funcptr(&pChain->field_58);
                pIter = pChain;
            }
            else
            {
                break;
            }
        }
        DG_SetPos2_8001BC8C(&svec1, &svec2);
        ReadRotMatrix(&pIter->field_58);

        break;
    case 0x1D:
        demothrd_remove_via_id_8007CD60(work, 0x1D);
        if (pData->data.variant_0x1D.field_14 == 0)
        {
            funcptr = GM_GetCharaID_8002A8EC(0x21);
            if (funcptr != NULL)
            {
                pChain->field_C_actor1 = funcptr(pData->data.variant_0x1D.field_18, pData->data.variant_0x1D.field_1C);
            }
        }
        break;
    case 0x1F:
        pIter = work->field_38.field_4_pNext;
        work->field_268 = 1;
        work->field_26C = 1;
        while (pIter != &work->field_38)
        {
            if (pIter->field_C_actor1 != NULL)
            {
                GV_DestroyOtherActor_800151D8(pIter->field_C_actor1);
                if (pIter->field_10_actor2 != NULL)
                {
                    GV_DestroyOtherActor_800151D8(pIter->field_10_actor2);
                }
                pIter->field_C_actor1 = NULL;
                pIter->field_10_actor2 = NULL;
            }
            pIter = pIter->field_4_pNext;
        }
        break;
    case 0x20:
        if (pData->data.variant_0x20.field_20 == 1)
        {
            pIter = work->field_38.field_4_pNext;
            while (pIter != &work->field_38)
            {
                if (pIter->field_14[0].field_4_type == 0x20)
                {
                    if (pIter->field_C_actor1 != NULL)
                    {
                        GV_DestroyOtherActor_800151D8(pIter->field_C_actor1);
                        pIter->field_C_actor1 = NULL;
                    }
                }
                pIter = pIter->field_4_pNext;
            }
        }
        else
        {
            funcptr = GM_GetCharaID_8002A8EC(0x23);
            if (funcptr != NULL)
            {
                if (pData->data.variant_0x20.field_14 >= 2 && pData->data.variant_0x20.field_14 <= 5)
                {
                    funcptr(&svec1, pData->data.variant_0x20.field_14 + 2, pData->data.variant_0x20.field_18,
                            pData->data.variant_0x20.field_1C);
                }
                else
                {
                    pChain->field_C_actor1 = funcptr(&svec1, pData->data.variant_0x20.field_14 + 2,
                                                     pData->data.variant_0x20.field_18, pData->data.variant_0x20.field_1C);
                }
            }
        }
        break;
    case 0x21:
        svec3.vx = pData->data.variant_0x21.field_14;
        svec3.vy = pData->data.variant_0x21.field_16;
        svec3.vz = pData->data.variant_0x21.field_18;
        funcptr = GM_GetCharaID_8002A8EC(0x24);
        if (funcptr != NULL)
        {
            funcptr(&svec1, &svec3, pData->data.variant_0x21.field_1C);
        }
        break;
    case 0x22:
        demothrd_remove_via_id_8007CD60(work, 0x22);
        if (pData->data.variant_0x22.field_14 == 0)
        {
            funcptr = GM_GetCharaID_8002A8EC(0x25);
            if (funcptr != NULL)
            {
                pChain->field_C_actor1 = funcptr(pData->data.variant_0x22.field_16, pData->data.variant_0x22.field_18,
                                                 pData->data.variant_0x22.field_1A);
            }
        }
        break;
    case 0x23:
        svec3.vx = pData->data.variant_0x23.field_14;
        svec3.vy = pData->data.variant_0x23.field_16;
        svec3.vz = pData->data.variant_0x23.field_18;
        if (pData->data.variant_0x23.field_1A != 4)
        {
            funcptr = GM_GetCharaID_8002A8EC(0x26);
            if (funcptr != NULL)
            {
                ((VoidMakeChara)funcptr)(&svec1, &svec3, pData->data.variant_0x23.field_1A);
            }
        }
        else
        {
            funcptr = GM_GetCharaID_8002A8EC(0x27);
            if (funcptr != NULL)
            {
                ((VoidMakeChara)funcptr)(&svec1, &svec3, pData->data.variant_0x23.field_1C & 0xFF,
                                         pData->data.variant_0x23.field_1E & 0xFF,
                                         pData->data.variant_0x23.field_20 & 0xFF);
            }
        }
        break;
    case 0x24:
        demothrd_remove_via_id_8007CD60(work, 0x24);

        if (pData->data.variant_0x24.field_14 == 0)
        {
            funcptr = GM_GetCharaID_8002A8EC(0x28);
            if (funcptr != NULL)
            {
                pChain->field_C_actor1 = funcptr();
            }
        }
        break;

    case 0x25:
        demothrd_remove_via_id_8007CD60(work, 0x25);

        if (pData->data.variant_0x25.field_14 == 0)
        {
            funcptr = GM_GetCharaID_8002A8EC(0x29);
            if (funcptr != NULL)
            {
                pChain->field_C_actor1 = funcptr();
            }
        }
        break;

    case 0x26:
        pModel = work->field_34_pModels;
        pDmoModel = work->field_30_dmo_header->field_18_pModels;

        for (i = 0; i < work->field_30_dmo_header->field_10_num_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->field_C_hashCode == GV_StrCode_80016CCC("hind"))
            {
                break;
            }
            if (pDmoModel->field_C_hashCode == GV_StrCode_80016CCC("hinddemo"))
            {
                break;
            }
        }

        if (i >= work->field_30_dmo_header->field_10_num_models)
        {
            break;
        }

        pModel->field_1A0_pM1OrHind->field_0[0][0].objs = pData->data.variant_0x26.field_14;
        pModel->field_1A0_pM1OrHind->field_0[0][0].flag = pData->data.variant_0x26.field_18;

        break;
    case 0x27:
        funcptr = GM_GetCharaID_8002A8EC(0x2a);
        if (funcptr != NULL)
        {
            funcptr(&svec1);
        }
        break;

    case 0x28:
        funcptr = GM_GetCharaID_8002A8EC(0x2B);
        if (funcptr != NULL)
        {
            if (pData->data.variant_0x28.field_14 >= 0 && pData->data.variant_0x28.field_14 <= 3)
            {
                funcptr(&svec1, pData->data.variant_0x28.field_14 + 4, pData->data.variant_0x28.field_18,
                        pData->data.variant_0x28.field_1C);
            }
            else
            {
                pChain->field_C_actor1 = funcptr(&svec1, pData->data.variant_0x28.field_14 + 4,
                                                 pData->data.variant_0x28.field_18, pData->data.variant_0x28.field_1C);
            }
        }
        break;

    case 0x29:
        pIter = work->field_38.field_4_pNext;

        if (pIter != &work->field_38)
        {
            while ((pIter->field_14[0].field_4_type != 0x29) || !pIter->field_C_actor1)
            {
                pIter = pIter->field_4_pNext;

                if (pIter == &work->field_38)
                {
                    break;
                }
            }
        }

        if (pIter == &work->field_38)
        {
            if (pData->data.variant_0x29.field_14 != 1)
            {
                funcptr = GM_GetCharaID_8002A8EC(0x2C);
                if (funcptr != NULL)
                {
                    pChain->field_C_actor1 = funcptr(pData->data.variant_0x29.field_1C, &pData->data.variant_0x29.field_16);
                }
            }
        }
        else if (pData->data.variant_0x29.field_14 != 0)
        {
            if (pIter->field_14[1].field_C_zpad != pData->data.variant_0x29.field_1C)
            {
                GV_DestroyOtherActor_800151D8(pIter->field_C_actor1);
                pIter->field_C_actor1 = NULL;
                funcptr = GM_GetCharaID_8002A8EC(0x2C);
                if (funcptr != NULL)
                {
                    pChain->field_C_actor1 = funcptr(pData->data.variant_0x29.field_1C, &pData->data.variant_0x29.field_16);
                }
            }
            else
            {
                // TODO: I can't make sense of it (field_28 is used as an int in other places...)
                struct copier
                {
                    short a, b;
                };
                *(struct copier *)((char *)&pIter->field_14[1].field_4_type + 2) = *(struct copier *)&pData->data.variant_0x29.field_16;
            }
        }
        else
        {
            GV_DestroyOtherActor_800151D8(pIter->field_C_actor1);
            pIter->field_C_actor1 = NULL;
        }
        break;

    case 0x2A:
        pModel = work->field_34_pModels;
        pDmoModel = work->field_30_dmo_header->field_18_pModels;

        for (i = 0; i < work->field_30_dmo_header->field_10_num_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->field_0_type == pData->data.variant_0x2A.field_14)
            {
                break;
            }
        }

        if (i >= work->field_30_dmo_header->field_10_num_models)
        {
            break;
        }

        pIter = work->field_38.field_4_pNext;
        while (pIter != &work->field_38)
        {
            if ((pIter->field_14[0].field_4_type == 0x2A) && (pIter->field_14[1].field_4_type == pData->data.variant_0x2A.field_14))
            {
                if (pIter->field_C_actor1 != NULL)
                {
                    GV_DestroyOtherActor_800151D8(pIter->field_C_actor1);
                    pIter->field_C_actor1 = NULL;
                }
            }
            pIter = pIter->field_4_pNext;
        }
        if (pData->data.variant_0x2A.field_18 != 1)
        {
            funcptr = GM_GetCharaID_8002A8EC(0x2D);
            if (funcptr != NULL)
            {
                pChain->field_C_actor1 = funcptr(&pModel->field_7C_obj.objs->objs[4]);
            }
        }
        break;

    case 0x2B:
        pIter = work->field_38.field_4_pNext;

        while (pIter != &work->field_38)
        {
            if (pIter->field_14[0].field_4_type == 0x2B)
            {
                if (pIter->field_C_actor1 != NULL)
                {
                    GV_DestroyOtherActor_800151D8(pIter->field_C_actor1);
                    pIter->field_C_actor1 = NULL;
                }
            }
            pIter = pIter->field_4_pNext;
        }

        if (pData->data.variant_0x2B.field_14 == 0)
        {
            funcptr = GM_GetCharaID_8002A8EC(0x2E);
            if (funcptr != NULL)
            {
                pChain->field_C_actor1 = funcptr();
            }
        }
        break;

    case 0x2C:
        svec3.vx = pData->data.variant_0x2C.field_14;
        svec3.vy = pData->data.variant_0x2C.field_16;
        svec3.vz = pData->data.variant_0x2C.field_18;
        funcptr = GM_GetCharaID_8002A8EC(0x2F);
        if (funcptr != NULL)
        {
            funcptr(&svec1, &svec3, pData->data.variant_0x2C.field_1A, pData->data.variant_0x2C.field_1C);
        }
        break;
    case 0x2D:
        svec3.vx = pData->data.variant_0x2D.field_14;
        svec3.vy = pData->data.variant_0x2D.field_16;
        svec3.vz = pData->data.variant_0x2D.field_18;
        funcptr = GM_GetCharaID_8002A8EC(0x30);
        if (funcptr != NULL)
        {
            funcptr(pData->data.variant_0x2D.field_22, pData->data.variant_0x2D.field_1C, pData->data.variant_0x2D.field_20,
                    &svec1, &svec3);
        }
        break;

    case 0x2E:
        svec3.vx = pData->data.variant_0x2E.field_14;
        svec3.vy = pData->data.variant_0x2E.field_16;
        svec3.vz = pData->data.variant_0x2E.field_18;
        svec4.vx = pData->data.variant_0x2E.field_1A;
        svec4.vy = pData->data.variant_0x2E.field_1C;
        svec4.vz = pData->data.variant_0x2E.field_1E;
        funcptr = GM_GetCharaID_8002A8EC(0x31);
        if (funcptr != NULL)
        {
            funcptr(pData->data.variant_0x2E.field_26, pData->data.variant_0x2E.field_20, pData->data.variant_0x2E.field_24,
                    &svec1, &svec3, &svec4, pData->data.variant_0x2E.field_28 & 0xFF,
                    pData->data.variant_0x2E.field_2A & 0xFF, pData->data.variant_0x2E.field_2C & 0xFF);
        }
        break;

    case 0x2F:
        funcptr = GM_GetCharaID_8002A8EC(0x32);
        if (funcptr != NULL)
        {
            funcptr(pData->data.variant_0x2F.field_14, &svec1, &svec2);
        }
        break;

    case 0x30:
        funcptr = GM_GetCharaID_8002A8EC(0x33);
        if (funcptr != NULL)
        {
            funcptr(&svec2, &svec1);
        }
        break;

    case 0x31:
        funcptr = GM_GetCharaID_8002A8EC(0x34);
        if (funcptr != NULL)
        {
            funcptr(&svec1);
        }
        break;

    case 0x32:
        funcptr = GM_GetCharaID_8002A8EC(0x35);
        if (funcptr != NULL)
        {
            funcptr(&mat2);
        }
        break;

    case 0x33:
        funcptr = GM_GetCharaID_8002A8EC(0x36);
        if (funcptr != NULL)
        {
            funcptr(&svec1);
        }
        break;

    case 0x34:
        svec3.vx = pData->data.variant_0x34.field_24;
        svec3.vy = pData->data.variant_0x34.field_26;
        svec3.vz = pData->data.variant_0x34.field_28;
        svec4.vx = pData->data.variant_0x34.field_2A;
        svec4.vy = pData->data.variant_0x34.field_2C;
        svec4.vz = pData->data.variant_0x34.field_2E;
        if (pData->data.variant_0x34.field_30 == 0)
        {
            funcptr = GM_GetCharaID_8002A8EC(0x37);
            if (funcptr != NULL)
            {
                funcptr(pData->data.variant_0x34.field_14, pData->data.variant_0x34.field_18, &svec3, &svec4,
                        pData->data.variant_0x34.field_1C, pData->data.variant_0x34.field_20);
            }
        }
        else
        {
            memset(&msg, 0, sizeof(msg));
            msg.address = pData->data.variant_0x34.field_14;
            msg.message[0] = HASH_KILL;
            msg.message_len = 1;

            GV_SendMessage_80016504(&msg);
        }
        break;

    case 0x35:
        funcptr = GM_GetCharaID_8002A8EC(0x39);
        if (funcptr != NULL)
        {
            funcptr(&svec1, &svec2, pData->data.variant_0x35.field_18, pData->data.variant_0x35.field_1C,
                    pData->data.variant_0x35.field_1E, pData->data.variant_0x35.field_20,
                    pData->data.variant_0x35.field_22 & 0xFF, pData->data.variant_0x35.field_24 & 0xFF,
                    pData->data.variant_0x35.field_26 & 0xFF);
        }
        break;

    case 0x37:
        funcptr = GM_GetCharaID_8002A8EC(0x3A);
        if (funcptr != NULL)
        {
            funcptr(pData->data.variant_0x37.field_14, pData->data.variant_0x37.field_18, pData->data.variant_0x37.field_1C,
                    pData->data.variant_0x37.field_1E, pData->data.variant_0x37.field_20, pData->data.variant_0x37.field_22,
                    &pData->data.variant_0x37.field_24, &pData->data.variant_0x37.field_28, pData->data.variant_0x37.field_2C,
                    pData->data.variant_0x37.field_2E, pData->data.variant_0x37.field_30, pData->data.variant_0x37.field_32);
        }
        break;

    case 0x38:
        funcptr = GM_GetCharaID_8002A8EC(0x3B);
        if (funcptr != NULL)
        {
            ((VoidMakeChara)funcptr)(&svec1);
        }
        break;
    case 0x39:
        switch (pData->data.variant_0x39.field_14)
        {
        case 0:
            funcptr = GM_GetCharaID_8002A8EC(0x3C);
            if (funcptr != NULL)
            {
                ((VoidMakeChara)funcptr)(&mat2);
            }
            break;

        case 1:
            funcptr = GM_GetCharaID_8002A8EC(0x3D);
            if (funcptr != 0)
            {
                funcptr(&mat2, 0);
            }
            break;

        case 2:
            funcptr = GM_GetCharaID_8002A8EC(0x3D);
            if (funcptr != 0)
            {
                funcptr(&mat2, 1);
            }
            break;
        }
        break;
    case 0x3A:
        svec3.vx = pData->data.variant_0x3A.field_14;
        svec3.vy = pData->data.variant_0x3A.field_16;
        svec3.vz = pData->data.variant_0x3A.field_18;
        funcptr = GM_GetCharaID_8002A8EC(0x3E);
        if (funcptr != NULL)
        {
            funcptr(&svec1, &svec3);
        }
        break;
    case 0x3B:
        funcptr = GM_GetCharaID_8002A8EC(0x3F);
        if (funcptr != NULL)
        {
            funcptr(&svec1, pData->data.variant_0x3B.field_14, pData->data.variant_0x3B.field_18,
                    pData->data.variant_0x3B.field_1C, pData->data.variant_0x3B.field_20, pData->data.variant_0x3B.field_22,
                    pData->data.variant_0x3B.field_24, pData->data.variant_0x3B.field_26, pData->data.variant_0x3B.field_28);
        }
        break;
    case 0x3C:
        funcptr = GM_GetCharaID_8002A8EC(0x40);
        if (funcptr != NULL)
        {
            funcptr(pData->data.variant_0x3C.field_14, pData->data.variant_0x3C.field_18, pData->data.variant_0x3C.field_1C,
                    pData->data.variant_0x3C.field_1E, pData->data.variant_0x3C.field_20, pData->data.variant_0x3C.field_22,
                    pData->data.variant_0x3C.field_24, &pData->data.variant_0x3C.field_26, &pData->data.variant_0x3C.field_2A,
                    pData->data.variant_0x3C.field_2E, pData->data.variant_0x3C.field_30, pData->data.variant_0x3C.field_32,
                    pData->data.variant_0x3C.field_34);
        }
        break;
    case 0x3D:
        pModel = work->field_34_pModels;
        pDmoModel = work->field_30_dmo_header->field_18_pModels;

        for (i = 0; i < work->field_30_dmo_header->field_10_num_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->field_0_type == pData->data.variant_0x3D.field_18)
            {
                break;
            }
        }

        if (i >= work->field_30_dmo_header->field_10_num_models)
        {
            break;
        }

        funcptr = GM_GetCharaID_8002A8EC(0x41);
        if (funcptr != NULL)
        {
            funcptr(&pModel->field_7C_obj.objs[6].world.m[1][1], pData->data.variant_0x3D.field_14,
                    pData->data.variant_0x3D.field_16);
        }
        break;
    case 0x3E:
        pIter = work->field_38.field_4_pNext;

        if (pIter != &work->field_38)
        {
            while ((pIter->field_14[0].field_4_type != 0x3e) || !pIter->field_C_actor1)
            {
                pIter = pIter->field_4_pNext;

                if (pIter == &work->field_38)
                {
                    break;
                }
            }
        }

        if (pData->data.variant_0x3E.field_14 == 0)
        {
            if (pIter != &work->field_38)
            {
                GV_DestroyOtherActor_800151D8(pIter->field_C_actor1);
                pIter->field_C_actor1 = NULL;
            }

            funcptr = GM_GetCharaID_8002A8EC(0x42);
            if (funcptr != NULL)
            {
                svec3.vx = pData->data.variant_0x3E.field_16;
                svec3.vy = pData->data.variant_0x3E.field_18;
                svec3.vz = pData->data.variant_0x3E.field_1A;
                pChain->field_C_actor1 =
                    funcptr(&svec3, pData->data.variant_0x3E.field_1E, pData->data.variant_0x3E.field_1C + 1);
            }
        }
        else if (pData->data.variant_0x3E.field_14 == 1)
        {
            if (pIter != &work->field_38)
            {
                GV_DestroyOtherActor_800151D8(pIter->field_C_actor1);
                pIter->field_C_actor1 = NULL;
            }
        }
        else if (pData->data.variant_0x3E.field_14 == 2)
        {
            if (pIter != &work->field_38)
            {
                memset(&msg, 0, sizeof(msg));
                msg.address = 0x3B8E;
                if (pData->data.variant_0x3E.field_20 == 0)
                {
                    msg.message[0] = 0xD182;
                }
                else
                {
                    msg.message[0] = 0x6B;
                }
                msg.message[1] = pData->data.variant_0x3E.field_22;
                msg.message_len = 2;

                GV_SendMessage_80016504(&msg);
            }
        }
        break;

    case 0x3F:
        pModel = work->field_34_pModels;
        pDmoModel = work->field_30_dmo_header->field_18_pModels;

        for (i = 0; i < work->field_30_dmo_header->field_10_num_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->field_0_type == pData->data.variant_0x3F.field_18)
            {
                break;
            }
        }

        if (i >= work->field_30_dmo_header->field_10_num_models)
        {
            break;
        }

        pIter = work->field_38.field_4_pNext;
        while (pIter != &work->field_38)
        {
            if ((pIter->field_14[0].field_4_type == 0x3F) && (pIter->field_14[1].field_8_xy == pData->data.variant_0x3F.field_18))
            {
                if (pIter->field_C_actor1 != NULL)
                {
                    GV_DestroyOtherActor_800151D8(pIter->field_C_actor1);
                    pIter->field_C_actor1 = NULL;
                }
            }
            pIter = pIter->field_4_pNext;
        }

        if (pData->data.variant_0x3F.field_14 != 1)
        {
            funcptr = GM_GetCharaID_8002A8EC(0x43);
            if (funcptr != NULL)
            {
                pChain->field_C_actor1 = funcptr(&pModel->field_7C_obj, &pModel->field_0_ctrl.rot);
            }
        }

        break;
    case 0x36:
    case 0x40:
        if (pData->data.variant_0x36.field_14 != 0)
        {
            GM_PadVibration_800ABA3C = 1;
        }
        if (pData->data.variant_0x36.field_16 != 0)
        {
            GM_PadVibration2_800ABA54 = pData->data.variant_0x36.field_18;
        }
        break;
    case 0x41:
        demothrd_remove_via_id_8007CD60(work, 0x41);
        if (pData->data.variant_0x41.field_14 == 0)
        {
            funcptr = GM_GetCharaID_8002A8EC(0x44);
            if (funcptr != NULL)
            {
                pChain->field_C_actor1 = funcptr();
            }
        }
        break;

    case 0x42:
        DG_SetTmpLight_8001A114(&svec1, pData->data.variant_0x42.field_14, pData->data.variant_0x42.field_16);
        break;

    case 0x43:
        pModel = work->field_34_pModels;
        pDmoModel = work->field_30_dmo_header->field_18_pModels;

        for (i = 0; i < work->field_30_dmo_header->field_10_num_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->field_0_type == pData->data.variant_0x43.field_14)
            {
                break;
            }
        }

        if (i >= work->field_30_dmo_header->field_10_num_models)
        {
            break;
        }

        pIter = work->field_38.field_4_pNext;

        while (pIter != &work->field_38)
        {
            if ((pIter->field_14[0].field_4_type == 0x43) && (pIter->field_14[1].field_4_type == pData->data.variant_0x43.field_14))
            {
                if (pIter->field_C_actor1 != NULL)
                {
                    GV_DestroyOtherActor_800151D8(pIter->field_C_actor1);
                    pIter->field_C_actor1 = NULL;
                }
            }
            pIter = pIter->field_4_pNext;
        }

        if (pData->data.variant_0x43.field_18 != 1)
        {
            funcptr = GM_GetCharaID_8002A8EC(0x45);
            if (funcptr != NULL)
            {
                pChain->field_C_actor1 = funcptr(pModel->field_7C_obj.objs + 1);
            }
        }
        break;
    case 0x44:
        pModel = work->field_34_pModels;
        pDmoModel = work->field_30_dmo_header->field_18_pModels;

        for (i = 0; i < work->field_30_dmo_header->field_10_num_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->field_0_type == pData->data.variant_0x44.field_18)
            {
                break;
            }
        }

        if (i >= work->field_30_dmo_header->field_10_num_models)
        {
            break;
        }

        pIter = work->field_38.field_4_pNext;

        if (pIter != &work->field_38)
        {
            while ((pIter->field_14[0].field_4_type != 0x44) || !pIter->field_C_actor1)
            {
                pIter = pIter->field_4_pNext;

                if (pIter == &work->field_38)
                {
                    break;
                }
            }
        }

        if (pIter == &work->field_38)
        {
            if (pData->data.variant_0x44.field_14 != 1)
            {
                funcptr = GM_GetCharaID_8002A8EC(0x46);

                if (funcptr != NULL)
                {
                    pChain->field_50 = pData->data.variant_0x44.field_1E;
                    pChain->field_52 = pData->data.variant_0x44.field_20;
                    pChain->field_54 = pData->data.variant_0x44.field_22;

                    if (pData->data.variant_0x44.field_1C == 0)
                    {
                        pChain->field_56 = 0;
                    }
                    else
                    {
                        pChain->field_56 = -1;
                    }

                    pChain->field_C_actor1 =
                        funcptr(pModel, &pModel->field_7C_obj, &pChain->field_50, pDmoModel->field_8);
                }
            }
        }
        else if (pData->data.variant_0x44.field_14 == 1)
        {
            GV_DestroyOtherActor_800151D8(pIter->field_C_actor1);
            pIter->field_C_actor1 = NULL;
        }
        else
        {
            pIter->field_50 = pData->data.variant_0x44.field_1E;
            pIter->field_52 = pData->data.variant_0x44.field_20;
            pIter->field_54 = pData->data.variant_0x44.field_22;
        }
        break;

    case 0x45:
        funcptr = GM_GetCharaID_8002A8EC(0x47);
        if (funcptr != NULL)
        {
            pChain->field_C_actor1 = funcptr(&mat2, pData->data.variant_0x45.field_14, pData->data.variant_0x45.field_16,
                                             pData->data.variant_0x45.field_18, pData->data.variant_0x45.field_1A);
        }
        break;
    case 0x46:
        funcptr = GM_GetCharaID_8002A8EC(0x48);
        if (funcptr != NULL)
        {
            funcptr(&svec1, pData->data.variant_0x46.field_14, pData->data.variant_0x46.field_16);
        }
        break;
    case 0x47:
        funcptr = GM_GetCharaID_8002A8EC(0x49);
        if (funcptr != NULL)
        {
            funcptr(&mat2, 400, 400, 400, 10);
        }
        break;

    case 0x48:
        funcptr = GM_GetCharaID_8002A8EC(0x4A);
        if (funcptr != NULL)
        {
            ((VoidMakeChara)funcptr)(&svec1);
        }
        break;

    case 0x49:
        pIter = work->field_38.field_4_pNext;
        while (pIter != &work->field_38)
        {
            if (pIter->field_14[0].field_4_type == 0x49)
            {
                if (pIter->field_C_actor1 != NULL)
                {
                    GV_DestroyOtherActor_800151D8(pIter->field_C_actor1);
                    pIter->field_C_actor1 = NULL;
                }
            }
            pIter = pIter->field_4_pNext;
        }

        if (pData->data.variant_0x49.field_14 == 0)
        {
            funcptr = GM_GetCharaID_8002A8EC(0x4B);
            if (funcptr != NULL)
            {
                pChain->field_C_actor1 = funcptr();
            }
        }
        break;

    case 0x4A:
        funcptr = GM_GetCharaID_8002A8EC(0x4C);

        if (funcptr != NULL)
        {
            funcptr(pData->data.variant_0x4A.field_18, pData->data.variant_0x4A.field_1A, 0,
                    pData->data.variant_0x4A.field_14, pData->data.variant_0x4A.field_1C, pData->data.variant_0x4A.field_20);
        }
        break;
    }

    return 1;
}

void demothrd_remove_via_id_8007CD60(DemothrdWork *pThis, int id_to_remove)
{
    DemothrdWork_0x78_Chain *pSubIter; // $s0
    DemothrdWork_0x78_Chain *pCur; // $a0
    DemothrdWork_0x78_Chain *pCur_; // $s1
    GV_ACT *pPrevious; // $a0
    GV_ACT *pNext; // $a0

    pSubIter = pThis->field_38.field_4_pNext;
    pCur = &pThis->field_38;
    if ( pSubIter != pCur )
    {
        pCur_ = pCur;
        do
        {
            if ( pSubIter->field_14[0].field_4_type == id_to_remove )
            {
                pPrevious = pSubIter->field_C_actor1;
                if ( pPrevious )
                {
                    GV_DestroyOtherActor_800151D8(pPrevious);
                    pNext = pSubIter->field_10_actor2;
                    if ( pNext )
                    {
                        GV_DestroyOtherActor_800151D8(pNext);
                    }
                    pSubIter->field_C_actor1 = 0;
                    pSubIter->field_10_actor2 = 0;
                }
            }
            pSubIter = pSubIter->field_4_pNext;
        }
        while ( pSubIter != pCur_ );
    }
}

int demothrd_8007CDF8(DemothrdWork *work, dmo_data_0x28 *pDmoData, DemothrdWork_0x78_Chain *pChain)
{
  dmo_data_0x18 *field_24_pDmoEnd;
  int idx;
  HZD_VEC vec2;
  SVECTOR vecPos;
  if (pChain->field_14[0].field_4_type == 14)
  {
    field_24_pDmoEnd = pDmoData->field_24_pDmoEnd;
    {
      for (idx = 0; idx < pDmoData->field_20_count; idx++)
      {
        if (field_24_pDmoEnd->field_0_type == pChain->field_14[1].field_4_type)
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
        idx = sub_800296C4(work->field_C4_ctrl.map->hzd, &vecPos, 1);
        sub_800298DC(&vec2);
        pChain->field_48 = field_24_pDmoEnd->rot_y;
        if ((idx & 1) != 0)
        {
          pChain->field_4C = vec2.x + 50;
        }
        else  if ((idx & 2) != 0)
        {
          pChain->field_4C = vec2.y + 50;
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

int demothrd_1_FrameRunDemo_helper4_8007CF14(DemothrdWork *work, dmo_data_0x28 *pDmo)
{
  dmo_data_0x34 *pIter;
  int i;
  DemothrdWork_0x78_Chain *pNext;
  DemothrdWork_0x78_Chain *new_var;
  DemothrdWork_0x78_Chain *new_var2;
  DemothrdWork_0x78_Chain *pRoot;
  pIter = pDmo->field_1C_dmo_data_offset;
  for (i = 0; i < pDmo->field_18_count; ++pIter)
  {
    ++i;
    if (pIter->field_4_type == 28)
    {
      return 1;
    }
  }

  pNext = work->field_38.field_4_pNext;
  new_var = &work->field_38;
  if (pNext != new_var)
  {
    if (pNext->field_14[0].field_4_type != 28)
    {
      new_var2 = new_var;
      pRoot = &work->field_38;
      while (1)
      {
        pNext = pNext->field_4_pNext;
        if (pNext == new_var2)
        {
          break;
        }
        if (pNext->field_14[0].field_4_type == 28)
        {
          pRoot = &work->field_38;
          break;
        }
      }

    }
  }
  if (pNext != (&work->field_38))
  {
    GV_DestroyOtherActor_800151D8(pNext->field_C_actor1);
    pRoot = &work->field_38;
    pNext->field_C_actor1 = 0;
    Chain_Remove_8007F394(pRoot, pNext);
    GV_Free_80016230(pNext);
  }
  return 1;
}

int demothrd_8007CFE8(DemothrdWork *work, dmo_data_0x18 *pDmoData0x18)
{
  dmo_model_0x1A4 *pModelIter_0x1A4;
  dmo_model_0x14 *pModelIter_0x14;
  int counter;
  dmo_6 *pEndIter;

  OFFSET_TO_PTR(pDmoData0x18, &pDmoData0x18->field_14_pEndData);


  pModelIter_0x1A4 = work->field_34_pModels;
  pModelIter_0x14 = work->field_30_dmo_header->field_18_pModels;

  for (counter = 0; counter < work->field_30_dmo_header->field_10_num_models;)
  {
    if (pModelIter_0x14->field_0_type == pDmoData0x18->field_0_type)
    {
      break;
    }
     counter++;
    ++pModelIter_0x14;
    ++pModelIter_0x1A4;

  }

  if (counter >= work->field_30_dmo_header->field_10_num_models)
  {
    return 0;
  }

  if (!pDmoData0x18->field_4)
  {
    DG_InvisibleObjs(pModelIter_0x1A4->field_7C_obj.objs);
    if ((pModelIter_0x14->field_C_hashCode == GV_StrCode_80016CCC("m1e1")) || ((pModelIter_0x14->field_C_hashCode == GV_StrCode_80016CCC("m1e1demo"))))
    {
      DG_InvisibleObjs(pModelIter_0x1A4->field_1A0_pM1OrHind->field_0[0][0].objs);
      DG_InvisibleObjs(pModelIter_0x1A4->field_1A0_pM1OrHind->field_0[0][1].objs);
      DG_InvisibleObjs(pModelIter_0x1A4->field_1A0_pM1OrHind->field_0[0][2].objs);
      DG_InvisibleObjs(pModelIter_0x1A4->field_1A0_pM1OrHind->field_0[1][0].objs);
      DG_InvisibleObjs(pModelIter_0x1A4->field_1A0_pM1OrHind->field_0[1][1].objs);
      DG_InvisibleObjs(pModelIter_0x1A4->field_1A0_pM1OrHind->field_0[1][2].objs);
    }
  }
  else
  {
    DG_VisibleObjs(pModelIter_0x1A4->field_7C_obj.objs);
    if ((pModelIter_0x14->field_C_hashCode == GV_StrCode_80016CCC("m1e1")) || (pModelIter_0x14->field_C_hashCode == GV_StrCode_80016CCC("m1e1demo")))
    {
      DG_VisibleObjs(pModelIter_0x1A4->field_1A0_pM1OrHind->field_0[0][pModelIter_0x1A4->field_1A0_pM1OrHind->field_558_idx[0]].objs);
      DG_VisibleObjs(pModelIter_0x1A4->field_1A0_pM1OrHind->field_0[1][pModelIter_0x1A4->field_1A0_pM1OrHind->field_558_idx[1]].objs);
    }

    pModelIter_0x1A4->field_0_ctrl.mov.vx = pDmoData0x18->field_C_pos_x;
    pModelIter_0x1A4->field_0_ctrl.mov.vy = pDmoData0x18->field_E_pos_y;
    pModelIter_0x1A4->field_0_ctrl.mov.vz = pDmoData0x18->field_10_pos_z;
    pModelIter_0x1A4->field_0_ctrl.rot.vx = pDmoData0x18->field_6_rot_x;
    pModelIter_0x1A4->field_0_ctrl.rot.vy = pDmoData0x18->rot_y;
    pModelIter_0x1A4->field_0_ctrl.rot.vz = pDmoData0x18->field_A_rot_z;
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
            pModelIter_0x1A4->field_7C_obj.rots[counter].vx = pEndIter->field_0;
            pModelIter_0x1A4->field_7C_obj.rots[counter].vy = pEndIter->field_2; // field_0
            pModelIter_0x1A4->field_7C_obj.rots[counter].vz = pEndIter->field_4;
            counter++;
            pEndIter++;
          }
          while (counter < pDmoData0x18->field_12_total);
        }

        if ((pModelIter_0x14->field_C_hashCode == GV_StrCode_80016CCC("m1e1")) || (pModelIter_0x14->field_C_hashCode == GV_StrCode_80016CCC("m1e1demo")))
        {
          demothrd_m1e1_8007D404(work, pDmoData0x18, pModelIter_0x14, pModelIter_0x1A4);
        }
        else if ((pModelIter_0x14->field_C_hashCode == GV_StrCode_80016CCC("hind")) || (pModelIter_0x14->field_C_hashCode == GV_StrCode_80016CCC("hinddemo")))
        {
           demothrd_hind_8007D9C8(work, pDmoData0x18, pModelIter_0x14, pModelIter_0x1A4);
        }

        GM_ActMotion_80034A7C(&pModelIter_0x1A4->field_7C_obj);
        GM_ActControl_80025A7C(&pModelIter_0x1A4->field_0_ctrl);
        GM_ActObject_80034AF4(&pModelIter_0x1A4->field_7C_obj);
        DG_GetLightMatrix_8001A3C4(&pModelIter_0x1A4->field_0_ctrl.mov, pModelIter_0x1A4->field_160_mtx);
    }
  }
  return 1;
}


static inline int magic_calc(SVECTOR* vecTmp, dmo_model_0x1A4 *p0x1A4)
{
    int distance1 = SquareRoot0(((vecTmp->vx * vecTmp->vx) + (vecTmp->vy * vecTmp->vy)) + (vecTmp->vz * vecTmp->vz));

    int rTan1 = ratan2(vecTmp->vx, vecTmp->vz);
    int tmp4 = rTan1;
    tmp4 -= p0x1A4->field_0_ctrl.rot.vy + p0x1A4->field_7C_obj.rots[0].vy;
    tmp4 = abs(tmp4);
    return (distance1 * (1024 - tmp4)) / 1024;
}

void demothrd_m1e1_8007D404(DemothrdWork *work, dmo_data_0x18 *p0x18, dmo_model_0x14 *p0x14, dmo_model_0x1A4 *p0x1A4)
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
    GM_ActMotion_80034A7C(&pData->field_0[0][i]);
    GM_ActMotion_80034A7C(&pData->field_0[1][i]);
  }

  DG_SetPos2_8001BC8C(&p0x1A4->field_0_ctrl.mov, &p0x1A4->field_0_ctrl.rot);
  DG_RotatePos_8001BD64(p0x1A4->field_7C_obj.rots);

  M1E1GetCaterpillerVertex_800815FC(&p0x1A4->field_1A0_pM1OrHind->field_0[0][0], &p0x1A4->field_1A0_pM1OrHind->field_0[1][0], smokeVecs, 1);
  for (i = 0; i < 10; i++)
  {
    smokeVecs[i].vy = smokeVecs[i].vy + 300;
  }

  DG_PutVector_8001BE48(smokeVecs, smokeVecs, 10);

  memset(&vec, 0, sizeof(SVECTOR));
  vec.vx = pData->field_0[1][0].objs->objs[0].model->min.vx + ((pData->field_0[1][0].objs->objs[0].model->max.vx - pData->field_0[1][0].objs->objs[0].model->min.vx) / 2);
  DG_PutVector_8001BE48(&vec, &vec, 1);

  vecTmp.vx = vec.vx - pData->field_564[0].vx;
  vecTmp.vy = vec.vy - pData->field_564[0].vy;
  vecTmp.vz = vec.vz - pData->field_564[0].vz;

  tmp1 = magic_calc(&vecTmp, p0x1A4);

  if (abs(tmp1) >= pData->field_560)
  {
    AN_CaterpillerSmoke_8007DA28(&smokeVecs[rand() % 5]);
    DG_InvisibleObjs(pData->field_0[0][pData->field_558_idx[0]].objs);
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
    DG_VisibleObjs(pData->field_0[0][pData->field_558_idx[0]].objs);
    pData->field_564[0] = vec;
  }


  memset(&vec, 0, sizeof(SVECTOR));
  vec.vx = pData->field_0[1][0].objs->objs[0].model->min.vx + ((pData->field_0[1][0].objs->objs[0].model->max.vx - pData->field_0[1][0].objs->objs[0].model->min.vx) / 2);
  DG_SetPos2_8001BC8C(&p0x1A4->field_0_ctrl.mov, &p0x1A4->field_0_ctrl.rot);

  DG_PutVector_8001BE48(&vec, &vec, 1);
  vecTmp.vx = vec.vx - pData->field_564[1].vx;
  vecTmp.vy = vec.vy - pData->field_564[1].vy;
  vecTmp.vz = vec.vz - pData->field_564[1].vz;

  tmp1 = magic_calc(&vecTmp, p0x1A4);

  if (abs(tmp1) >= pData->field_560)
  {
    AN_CaterpillerSmoke_8007DA28(&smokeVecs[(rand() % 5) + 5]);
    DG_InvisibleObjs(pData->field_0[1][pData->field_558_idx[1]].objs);
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
    DG_VisibleObjs(pData->field_0[1][pData->field_558_idx[1]].objs);
    pData->field_564[1] = vec;
  }
  DG_SetPos2_8001BC8C(&p0x1A4->field_0_ctrl.mov, &p0x1A4->field_0_ctrl.rot);
  DG_RotatePos_8001BD64(p0x1A4->field_7C_obj.rots);
  for (i = 0; i < 3; i++)
  {
    GM_ActObject_80034AF4(&pData->field_0[0][i]);
    GM_ActObject_80034AF4(&pData->field_0[1][i]);
  }
}

void demothrd_hind_8007D9C8(DemothrdWork *work, dmo_data_0x18 *pDmoData0x18, dmo_model_0x14 *p0x14, dmo_model_0x1A4 *p0x1A4)
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

    p0x1A4->field_7C_obj.rots[1].vy = pTmp->field_8;
    p0x1A4->field_7C_obj.rots[2].vx = pTmp->field_C;
}

const char animation_data_8001345C[] = {
    0x00, 0x27, 0x01, 0x00, 0x05, 0x01, 0xfe, 0x0c, 0x00, 0x05, 0x01, 0xff, 0x0a, 0x00, 0x64, 0x00,
    0x64, 0x08, 0xf1, 0xf1, 0xf1, 0x02, 0x00, 0x01, 0x0d, 0x0c, 0x00, 0x05, 0x01, 0xff, 0x0a, 0x01,
    0x2c, 0x01, 0x2c, 0x08, 0xe2, 0xe2, 0xe2, 0x02, 0x00, 0x01, 0x0d, 0x0f
};

ANIMATION stru_8009F73C = {PCX_SMOKE, 8, 4, 30, 1, 1000, 3, 500, 500, 255, NULL, (char *)animation_data_8001345C};

const char animation_data_80013488[] = {
    0x00, 0x4a, 0x02, 0x00, 0x07, 0x00, 0x20, 0x01, 0xfe, 0x0c, 0x00, 0x05, 0x01, 0xff, 0x02, 0x00,
    0x01, 0x0d, 0x0c, 0x00, 0x0a, 0x01, 0xff, 0x08, 0xfa, 0xfa, 0xfa, 0x02, 0x00, 0x01, 0x0d, 0x0f,
    0x01, 0xfe, 0x0c, 0x00, 0x04, 0x0a, 0x01, 0x2c, 0x01, 0x2c, 0x01, 0xff, 0x02, 0x00, 0x01, 0x0d,
    0x0c, 0x00, 0x0a, 0x0a, 0x00, 0x46, 0x00, 0x46, 0x01, 0xff, 0x02, 0x00, 0x01, 0x0d, 0x0c, 0x00,
    0x0a, 0x01, 0xff, 0x0a, 0x00, 0x50, 0x00, 0x50, 0x08, 0xf0, 0xf0, 0xf0, 0x02, 0x00, 0x01, 0x0d,
    0x0f, 0x00, 0x00, 0x00
};

ANIMATION stru_8009F758 = {PCX_SMOKE, 8, 4, 30, 3, 0, 1, 1000, 1000, 64, NULL, (char *)animation_data_80013488};

const char animation_data_800134DC[] = {
    0x00, 0x2c, 0x01, 0x00, 0x05, 0x01, 0xfe, 0x0c, 0x00, 0x05, 0x01, 0xff, 0x02, 0x00, 0x01, 0x0d,
    0x0c, 0x00, 0x05, 0x01, 0xff, 0x0a, 0x00, 0x05, 0x00, 0x05, 0x02, 0x00, 0x01, 0x0d, 0x0c, 0x00,
    0x0f, 0x01, 0xff, 0x08, 0xf0, 0xf0, 0xf0, 0x0a, 0x00, 0x05, 0x00, 0x05, 0x02, 0x00, 0x01, 0x0d,
    0x0f, 0x00, 0x00, 0x00
};

ANIMATION stru_8009F774 = {PCX_SMOKE, 8, 4, 30, 8, 0, 3, 2200, 2200, 255, NULL, (char *)animation_data_800134DC};

const char animation_data_80013510[] = {
    0x00, 0x49, 0x03, 0x00, 0x09, 0x00, 0x1e, 0x00, 0x38, 0x01, 0xfe, 0x0c, 0x00, 0x04, 0x02, 0x00,
    0x01, 0x0d, 0x0c, 0x00, 0x04, 0x08, 0xec, 0xec, 0xec, 0x02, 0x00, 0x01, 0x0d, 0x0f, 0x01, 0xfe,
    0x0a, 0xfc, 0x18, 0xfc, 0x18, 0x0c, 0x00, 0x04, 0x02, 0x00, 0x01, 0x0d, 0x0c, 0x00, 0x04, 0x08,
    0xec, 0xec, 0xec, 0x02, 0x00, 0x01, 0x0d, 0x0f, 0x01, 0xfe, 0x0a, 0xfb, 0x50, 0xfb, 0x50, 0x0c,
    0x00, 0x04, 0x02, 0x00, 0x01, 0x0d, 0x0c, 0x00, 0x04, 0x08, 0xec, 0xec, 0xec, 0x02, 0x00, 0x01,
    0x0d, 0x0f, 0x00, 0x00
};

ANIMATION stru_8009F790 = {PCX_CANON_SEQ, 2, 2, 4, 1, 300, 1, 5000, 5000, 128, NULL, (char *)animation_data_80013510};

void AN_CaterpillerSmoke_8007DA28(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT  pre = {{ 0 }};

    pre.pos = *pos;

    anm = &stru_8009F73C;
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8( NULL, 0, anm );
}

void demothrd_2_8007DA94(SVECTOR *pPosition, SVECTOR *pRotation)
{
    SVECTOR    rotation;
    SVECTOR    speed;
    PRESCRIPT  pres[3];
    int        i;
    ANIMATION *anm;

    rotation.vx = 0;
    rotation.vy = pRotation->vy - 512;
    rotation.vz = 0;

    for (i = 0; i < 2; i++)
    {
        pres[i].pos = *pPosition;
        pres[i].pos.vy += 400;

        speed.vx = 0;
        speed.vy = 30;
        speed.vz = 200;

        rotation.vy += 341;

        DG_SetPos2_8001BC8C(&DG_ZeroVector_800AB39C, &rotation);
        DG_PutVector_8001BE48(&speed, &speed, 1);

        pres[i].speed = speed;
        pres[i].scr_num = 0;
        pres[i].s_anim = 0;
    }

    anm = &stru_8009F758;
    anm->field_14_pre_script = pres;

    pres[2].pos = *pPosition;
    pres[2].pos.vy += 400;
    pres[2].speed = DG_ZeroVector_800AB39C;
    pres[2].scr_num = 1;
    pres[2].s_anim = 0;

    NewAnime_8005FBC8( NULL, 0, anm );
}

void sub_8007DC24(SVECTOR *pPosition)
{
    SVECTOR    rotation;
    SVECTOR    speed_in;
    SVECTOR    speed_out;
    PRESCRIPT  pres[8];
    int        i;
    ANIMATION *anm;

    rotation = DG_ZeroVector_800AB39C;
    rotation.vy += GV_RandU_80017090(512);

    speed_in = DG_ZeroVector_800AB39C;

    for (i = 0; i < 8; i++)
    {
        pres[i].pos = *pPosition;
        pres[i].pos.vy += 500;

        speed_in.vz = 100;
        rotation.vy += 512;

        DG_SetPos2_8001BC8C(&DG_ZeroVector_800AB39C, &rotation);
        DG_PutVector_8001BE48(&speed_in, &speed_out, 1);

        pres[i].speed = speed_out;
        pres[i].scr_num = 0;
    }

    anm = &stru_8009F774;
    anm->field_14_pre_script = pres;

    NewAnime_8005FBC8( NULL, 0, anm );
}

void sub_8007DD80(short param_1, SVECTOR *pPos)
{
    int i;
    SVECTOR vec1;
    SVECTOR vec2;
    SVECTOR speed_tmp;
    SVECTOR speed;
    PRESCRIPT prescript[8];

    vec1 = DG_ZeroVector_800AB39C;
    vec2 = DG_ZeroVector_800AB39C;
    vec1.vy = param_1 - 512;
    speed_tmp = DG_ZeroVector_800AB39C;
    for (i = 0; i < 8; i++)
    {
        prescript[i].pos = *pPos;
        prescript[i].pos.vy -= 1000;
        speed_tmp.vz = GV_RandU_80017090(64) + 100;
        vec1.vy += 0x80;
        vec2.vy = vec1.vy + GV_RandS_800170BC(0x40);
        DG_SetPos2_8001BC8C(&DG_ZeroVector_800AB39C, &vec2);
        DG_PutVector_8001BE48(&speed_tmp, &speed, 1);
        prescript[i].speed = speed;
        prescript[i].scr_num = 0;
    }

    stru_8009F774.field_14_pre_script = prescript;
    NewAnime_8005FBC8(0, 0, &stru_8009F774);
}

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

#define __detx(a, b, c) (((b).y - (a).y) * ((c).z - (b).z) - ((b).z - (a).z) * ((c).y - (b).y))
#define __dety(a, b, c) (((b).z - (a).z) * ((c).x - (b).x) - ((b).x - (a).x) * ((c).z - (b).z))
#define __detz(a, b, c) (((b).x - (a).x) * ((c).y - (b).y) - ((b).y - (a).y) * ((c).x - (b).x))

void sub_8007E1C0(HZD_VEC *pOut, HZD_VEC *pOut2, MATRIX *pTransform, SVECTOR *pMin, SVECTOR *pMax)
{
    VECTOR   cross;
    SVECTOR *va;
    SVECTOR *vb;
    int      idx;
    int      i;
    int      len;
    int      min, max;

    va = (SVECTOR *)getScratchAddr(0);
    vb = (SVECTOR *)getScratchAddr(16);

    va[0].vx = pMin->vx;
    va[0].vy = pMin->vy;
    va[0].vz = pMin->vz;

    va[1].vx = pMin->vx;
    va[1].vy = pMin->vy;
    va[1].vz = pMax->vz;

    va[2].vx = pMax->vx;
    va[2].vy = pMin->vy;
    va[2].vz = pMax->vz;

    va[3].vx = pMax->vx;
    va[3].vy = pMin->vy;
    va[3].vz = pMin->vz;

    va[4].vx = pMin->vx;
    va[4].vy = pMax->vy;
    va[4].vz = pMin->vz;

    va[5].vx = pMin->vx;
    va[5].vy = pMax->vy;
    va[5].vz = pMax->vz;

    va[6].vx = pMax->vx;
    va[6].vy = pMax->vy;
    va[6].vz = pMax->vz;

    va[7].vx = pMax->vx;
    va[7].vy = pMax->vy;
    va[7].vz = pMin->vz;

    DG_SetPos_8001BC44(pTransform);
    DG_PutVector_8001BE48(va, va, 8);

    vb[0] = va[0];

    idx = 0;
    for (i = 0; i < 8; i++)
    {
        if ((va[i].vx < vb[0].vx) || ((va[i].vx == vb[0].vx) && (va[i].vz < vb[0].vz)))
        {
            idx = i;
            vb[0] = va[i];
        }
    }

    if (idx >= 4)
    {
        idx -= 4;
    }

    vb[4] = vb[0];

    vb[0].vy = MIN(va[idx].vy, va[idx + 4].vy);
    vb[4].vy = MAX(va[idx].vy, va[idx + 4].vy);

    if (++idx >= 4)
    {
        idx = 0;
    }

    vb[1] = (va[idx].vz >= va[idx + 4].vz) ? va[idx] : va[idx + 4];
    vb[5] = vb[1];
    vb[1].vy = MIN(va[idx].vy, va[idx + 4].vy);
    vb[5].vy = MAX(va[idx].vy, va[idx + 4].vy);

    if (++idx >= 4)
    {
        idx = 0;
    }

    vb[2] = (va[idx].vx >= va[idx + 4].vx) ? va[idx] : va[idx + 4];
    vb[6] = vb[2];
    vb[2].vy = MIN(va[idx].vy, va[idx + 4].vy);
    vb[6].vy = MAX(va[idx].vy, va[idx + 4].vy);

    if (++idx >= 4)
    {
        idx = 0;
    }

    vb[3] = (va[idx].vz <= va[idx + 4].vz) ? va[idx] : va[idx + 4];
    vb[7] = vb[3];
    vb[3].vy = MIN(va[idx].vy, va[idx + 4].vy);
    vb[7].vy = MAX(va[idx].vy, va[idx + 4].vy);

    pOut[0].x = vb[0].vx;
    pOut[0].z = vb[0].vz;
    pOut[0].y = vb[0].vy;
    pOut[0].h = vb[4].vy - vb[0].vy;

    pOut[1].x = vb[1].vx;
    pOut[1].z = vb[1].vz;
    pOut[1].y = vb[1].vy;
    pOut[1].h = vb[5].vy - vb[1].vy;

    pOut[2].x = vb[1].vx;
    pOut[2].z = vb[1].vz;
    pOut[2].y = vb[1].vy;
    pOut[2].h = vb[5].vy - vb[1].vy;

    pOut[3].x = vb[2].vx;
    pOut[3].z = vb[2].vz;
    pOut[3].y = vb[2].vy;
    pOut[3].h = vb[6].vy - vb[2].vy;

    pOut[4].x = vb[3].vx;
    pOut[4].z = vb[3].vz;
    pOut[4].y = vb[3].vy;
    pOut[4].h = vb[7].vy - vb[3].vy;

    pOut[5].x = vb[2].vx;
    pOut[5].z = vb[2].vz;
    pOut[5].y = vb[2].vy;
    pOut[5].h = vb[6].vy - vb[2].vy;

    pOut[6].x = vb[0].vx;
    pOut[6].z = vb[0].vz;
    pOut[6].y = vb[0].vy;
    pOut[6].h = vb[4].vy - vb[0].vy;

    pOut[7].x = vb[3].vx;
    pOut[7].z = vb[3].vz;
    pOut[7].y = vb[3].vy;
    pOut[7].h = vb[7].vy - vb[3].vy;

    pOut2[2].x = vb[0].vx;
    pOut2[2].z = vb[0].vz;
    pOut2[2].y = vb[0].vy;

    pOut2[3].x = vb[3].vx;
    pOut2[3].z = vb[3].vz;
    pOut2[3].y = vb[3].vy;

    pOut2[4].x = vb[2].vx;
    pOut2[4].z = vb[2].vz;
    pOut2[4].y = vb[2].vy;

    pOut2[5].x = vb[1].vx;
    pOut2[5].z = vb[1].vz;
    pOut2[5].y = vb[1].vy;
    pOut2[5].h = 0;

    pOut2[0] = pOut2[2];
    pOut2[0].h = 0;

    pOut2[0].x = MIN(pOut2[0].x, pOut2[3].x);
    pOut2[0].x = MIN(pOut2[0].x, pOut2[4].x);
    pOut2[0].x = MIN(pOut2[0].x, pOut2[5].x);

    pOut2[0].z = MIN(pOut2[0].z, pOut2[3].z);
    pOut2[0].z = MIN(pOut2[0].z, pOut2[4].z);
    pOut2[0].z = MIN(pOut2[0].z, pOut2[5].z);

    pOut2[0].y = MIN(pOut2[0].y, pOut2[3].y);
    pOut2[0].y = MIN(pOut2[0].y, pOut2[4].y);
    pOut2[0].y = MIN(pOut2[0].y, pOut2[5].y);

    pOut2[1] = pOut2[2];
    pOut2[1].h = 0;

    pOut2[1].x = MAX(pOut2[1].x, pOut2[3].x);
    pOut2[1].x = MAX(pOut2[1].x, pOut2[4].x);
    pOut2[1].x = MAX(pOut2[1].x, pOut2[5].x);

    pOut2[1].z = MAX(pOut2[1].z, pOut2[3].z);
    pOut2[1].z = MAX(pOut2[1].z, pOut2[4].z);
    pOut2[1].z = MAX(pOut2[1].z, pOut2[5].z);

    pOut2[1].y = MAX(pOut2[1].y, pOut2[3].y);
    pOut2[1].y = MAX(pOut2[1].y, pOut2[4].y);
    pOut2[1].y = MAX(pOut2[1].y, pOut2[5].y);

    cross.vx = __detx(pOut2[2], pOut2[3], pOut2[4]) >> 16;
    cross.vy = __dety(pOut2[2], pOut2[3], pOut2[4]) >> 16;
    cross.vz = __detz(pOut2[2], pOut2[3], pOut2[4]) >> 16;

    len = cross.vx * cross.vx + cross.vy * cross.vy + cross.vz * cross.vz;
    len = SquareRoot0(len);
    if (len == 0)
    {
        len = 1;
    }

    pOut2[2].h = (cross.vx * 255) / len;
    pOut2[3].h = (cross.vz * 255) / len;
    pOut2[4].h = (cross.vy * 255) / len;
    if (pOut2[4].h == 0)
    {
        pOut2[4].h = 1;
    }

    pOut2[8].x = vb[4].vx;
    pOut2[8].z = vb[4].vz;
    pOut2[8].y = vb[4].vy;

    pOut2[9].x = vb[7].vx;
    pOut2[9].z = vb[7].vz;
    pOut2[9].y = vb[7].vy;

    pOut2[10].x = vb[6].vx;
    pOut2[10].z = vb[6].vz;
    pOut2[10].y = vb[6].vy;

    pOut2[11].x = vb[5].vx;
    pOut2[11].z = vb[5].vz;
    pOut2[11].y = vb[5].vy;
    pOut2[11].h = 0;

    pOut2[6].x = pOut2[0].x;
    pOut2[6].z = pOut2[0].z;
    pOut2[6].h = 0;

    min = MIN(pOut2[8].y, pOut2[9].y);
    min = MIN(min, pOut2[10].y);
    min = MIN(min, pOut2[11].y);
    pOut2[6].y = min;

    pOut2[7].x = pOut2[1].x;
    pOut2[7].z = pOut2[1].z;
    pOut2[7].h = 0;

    max = MAX(pOut2[8].y, pOut2[9].y);
    max = MAX(max, pOut2[10].y);
    max = MAX(max, pOut2[11].y);
    pOut2[7].y = max;

    pOut2[8].h = pOut2[2].h;
    pOut2[9].h = pOut2[3].h;
    pOut2[10].h = pOut2[4].h;
}

void sub_8007EF34(SVECTOR *pOutVec1, SVECTOR *pOutVec2, MATRIX *pInMtx)
{
  int tmp;
  int distance;
  MATRIX rotMtx;
  SVECTOR vec1;
  SVECTOR vec2;
  ReadRotMatrix(&rotMtx);
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
  distance = SquareRoot0(tmp + (vec2.vz * vec2.vz));
  pOutVec2->vx = -((short) ratan2(vec2.vy, distance));
  pOutVec2->vy = ratan2(vec2.vx, vec2.vz);
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

void sub_8007F0D0(VECTOR *out, VECTOR *a, VECTOR *b, VECTOR *c)
{
    out->vx = (b->vy - a->vy) * (c->vz - b->vz) - (b->vz - a->vz) * (c->vy - b->vy);
    out->vy = (b->vz - a->vz) * (c->vx - b->vx) - (b->vx - a->vx) * (c->vz - b->vz);
    out->vz = (b->vx - a->vx) * (c->vy - b->vy) - (b->vy - a->vy) * (c->vx - b->vx);
    out->pad = out->vx * -a->vx + out->vy * -a->vy + out->vz * -a->vz;
}

VECTOR * sub_8007F1DC(VECTOR *out, DG_VECTOR *arg1, VECTOR *arg2)
{
    VECTOR vec;
    int    area;
    int    weight;

    area = arg2->vx * arg1[1].vx + arg2->vy * arg1[1].vy + arg2->vz * arg1[1].vz;
    if (area == 0)
    {
        vec.vx = 0x7FFFFFFF;
        vec.vy = 0x7FFFFFFF;
        vec.vz = 0x7FFFFFFF;
    }
    else
    {
        weight = ((-arg2->vx * arg1[0].vx - arg2->vy * arg1[0].vy - arg2->vz * arg1[0].vz - arg2->pad) << 12) / area;
        vec.vx = arg1->vx + ((arg1[1].vx * weight) >> 12);
        vec.vy = arg1->vy + ((arg1[1].vy * weight) >> 12);
        vec.vz = arg1->vz + ((arg1[1].vz * weight) >> 12);
    }

    *out = vec;
    return out;
}

void InitChain_8007F338(DemothrdWork_0x78_Chain *pSub)
{
    if (pSub)
    {
        pSub->field_0_pPrev = pSub;
        pSub->field_4_pNext = pSub;
    }
}

void Chain_Add_8007F350(DemothrdWork_0x78_Chain *pRoot, DemothrdWork_0x78_Chain *pAdd)
{
    DemothrdWork_0x78_Chain *prev; // $v0

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

void Chain_Remove_8007F394(DemothrdWork_0x78_Chain *pRoot, DemothrdWork_0x78_Chain *pRemove)
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

typedef struct
{
    char    pad[16];
    SVECTOR pre[8];
    SVECTOR post[8];
    HZD_SEG segment;
    SVECTOR unknown;
} SCRPAD_DATA_8007F3F8;

SVECTOR svector_8009F7AC = {0, 255, 0, 0};

void sub_8007F3F8(HZD_SEG *pIn, HZD_FLR *pOut, MATRIX *pTransform, SVECTOR *pMin, SVECTOR *pMax)
{
    SCRPAD_DATA_8007F3F8 *scrpad;
    SVECTOR              *pIter;
    int                   count;
    int                   a, b, c, d;
    int                   hzd_h;
    int                   min, v1, v2;

    scrpad = (SCRPAD_DATA_8007F3F8 *)getScratchAddr(0);

    DG_SetPos_8001BC44(pTransform);
    DG_RotVector_8001BE98(&svector_8009F7AC, &scrpad->unknown, 1);

    scrpad->pre[0].vx = pMin->vx;
    scrpad->pre[0].vy = pMin->vy;
    scrpad->pre[0].vz = pMin->vz;

    scrpad->pre[1].vx = pMin->vx;
    scrpad->pre[1].vy = pMin->vy;
    scrpad->pre[1].vz = pMax->vz;

    scrpad->pre[2].vx = pMax->vx;
    scrpad->pre[2].vy = pMin->vy;
    scrpad->pre[2].vz = pMax->vz;

    scrpad->pre[3].vx = pMax->vx;
    scrpad->pre[3].vy = pMin->vy;
    scrpad->pre[3].vz = pMin->vz;

    scrpad->pre[4].vx = pMin->vx;
    scrpad->pre[4].vy = pMax->vy;
    scrpad->pre[4].vz = pMin->vz;

    scrpad->pre[5].vx = pMin->vx;
    scrpad->pre[5].vy = pMax->vy;
    scrpad->pre[5].vz = pMax->vz;

    scrpad->pre[6].vx = pMax->vx;
    scrpad->pre[6].vy = pMax->vy;
    scrpad->pre[6].vz = pMax->vz;

    scrpad->pre[7].vx = pMax->vx;
    scrpad->pre[7].vy = pMax->vy;
    scrpad->pre[7].vz = pMin->vz;

    DG_PutVector_8001BE48(scrpad->pre, scrpad->post, 8);

    pIter = scrpad->post;
    for (count = 4; count > 0; count--, pIter++)
    {
        a = pIter[0].vx;
        b = pIter[4].vx;
        c = pIter[0].vz;
        d = pIter[4].vz;

        pIter[0].vx = pIter[4].vx = (a + b) / 2;
        pIter[0].vz = pIter[4].vz = (c + d) / 2;
    }

    hzd_h = scrpad->post[4].vy - scrpad->post[0].vy;

    scrpad->segment.p1.x = scrpad->post[0].vx;
    scrpad->segment.p1.z = scrpad->post[0].vz;
    scrpad->segment.p1.y = scrpad->post[0].vy;
    scrpad->segment.p1.h = hzd_h;

    scrpad->segment.p2.x = scrpad->post[1].vx;
    scrpad->segment.p2.z = scrpad->post[1].vz;
    scrpad->segment.p2.y = scrpad->post[1].vy;
    scrpad->segment.p2.h = hzd_h;

    HZD_SetDynamicSegment_8006FEE4(&scrpad->segment, pIn);

    scrpad->segment.p1.x = scrpad->post[1].vx;
    scrpad->segment.p1.z = scrpad->post[1].vz;
    scrpad->segment.p1.y = scrpad->post[1].vy;
    scrpad->segment.p1.h = hzd_h;

    scrpad->segment.p2.x = scrpad->post[2].vx;
    scrpad->segment.p2.z = scrpad->post[2].vz;
    scrpad->segment.p2.y = scrpad->post[2].vy;
    scrpad->segment.p2.h = hzd_h;

    HZD_SetDynamicSegment_8006FEE4(&scrpad->segment, pIn + 1);

    scrpad->segment.p1.x = scrpad->post[3].vx;
    scrpad->segment.p1.z = scrpad->post[3].vz;
    scrpad->segment.p1.y = scrpad->post[3].vy;
    scrpad->segment.p1.h = hzd_h;

    scrpad->segment.p2.x = scrpad->post[2].vx;
    scrpad->segment.p2.z = scrpad->post[2].vz;
    scrpad->segment.p2.y = scrpad->post[2].vy;
    scrpad->segment.p2.h = hzd_h;

    HZD_SetDynamicSegment_8006FEE4(&scrpad->segment, pIn + 2);

    scrpad->segment.p1.x = scrpad->post[0].vx;
    scrpad->segment.p1.z = scrpad->post[0].vz;
    scrpad->segment.p1.y = scrpad->post[0].vy;
    scrpad->segment.p1.h = hzd_h;

    scrpad->segment.p2.x = scrpad->post[3].vx;
    scrpad->segment.p2.z = scrpad->post[3].vz;
    scrpad->segment.p2.y = scrpad->post[3].vy;
    scrpad->segment.p2.h = hzd_h;

    HZD_SetDynamicSegment_8006FEE4(&scrpad->segment, pIn + 3);

    pOut[0].p1.x = scrpad->post[0].vx;
    pOut[0].p1.z = scrpad->post[0].vz;
    pOut[0].p1.y = scrpad->post[0].vy;

    pOut[0].p2.x = scrpad->post[3].vx;
    pOut[0].p2.z = scrpad->post[3].vz;
    pOut[0].p2.y = scrpad->post[3].vy;

    pOut[0].p3.x = scrpad->post[2].vx;
    pOut[0].p3.z = scrpad->post[2].vz;
    pOut[0].p3.y = scrpad->post[2].vy;

    pOut[0].p4.x = scrpad->post[1].vx;
    pOut[0].p4.z = scrpad->post[1].vz;
    pOut[0].p4.y = scrpad->post[1].vy;
    pOut[0].p4.h = 0;

    pOut[1].p1.x = scrpad->post[4].vx;
    pOut[1].p1.z = scrpad->post[4].vz;
    pOut[1].p1.y = scrpad->post[4].vy;

    pOut[1].p2.x = scrpad->post[7].vx;
    pOut[1].p2.z = scrpad->post[7].vz;
    pOut[1].p2.y = scrpad->post[7].vy;

    pOut[1].p3.x = scrpad->post[6].vx;
    pOut[1].p3.z = scrpad->post[6].vz;
    pOut[1].p3.y = scrpad->post[6].vy;

    pOut[1].p4.x = scrpad->post[5].vx;
    pOut[1].p4.z = scrpad->post[5].vz;
    pOut[1].p4.y = scrpad->post[5].vy;
    pOut[1].p4.h = 0;

    pOut[0].b1.h = 0;
    pOut[0].b2.h = 0;
    pOut[1].b1.h = 0;
    pOut[1].b2.h = 0;

    //start
    v1 = scrpad->post[0].vx;

    min = scrpad->post[1].vx;
    if (min > v1)
    {
        min = v1;
    }

    v2 = scrpad->post[1].vx;
    if (v2 < v1)
    {
        v2 = v1;
    }
    v1 = v2;

    v2 = scrpad->post[2].vx;
    if (v2 > min)
    {
        v2 = min;
    }
    min = v2;

    v2 = scrpad->post[2].vx;
    if (v1 > v2)
    {
        v2 = v1;
    }
    v1 = v2;

    v2 = scrpad->post[3].vx;
    if (v2 > min)
    {
        v2 = min;
    }
    min = v2;

    v2 = scrpad->post[3].vx;
    if (v1 > v2)
    {
        v2 = v1;
    }
    v1 = v2;

    pOut[0].b1.x = min;
    pOut[1].b1.x = min;
    pOut[0].b2.x = v1;
    pOut[1].b2.x = v1;


    //next
    v1 = scrpad->post[0].vy;

    min = scrpad->post[1].vy;
    if (min > v1)
    {
        min = v1;
    }

    v2 = scrpad->post[1].vy;
    if (v2 < v1)
    {
        v2 = v1;
    }
    v1 = v2;

    v2 = scrpad->post[2].vy;
    if (v2 > min)
    {
        v2 = min;
    }
    min = v2;

    v2 = scrpad->post[2].vy;
    if (v1 > v2)
    {
        v2 = v1;
    }
    v1 = v2;

    v2 = scrpad->post[3].vy;
    if (v2 > min)
    {
        v2 = min;
    }
    min = v2;

    v2 = scrpad->post[3].vy;
    if (v1 > v2)
    {
        v2 = v1;
    }
    v1 = v2;

    pOut[0].b1.y = min;
    pOut[0].b2.y = v1;

    //next
    v1 = scrpad->post[0].vz;

    min = scrpad->post[1].vz;
    if (min > v1)
    {
        min = v1;
    }

    v2 = scrpad->post[1].vz;
    if (v2 < v1)
    {
        v2 = v1;
    }
    v1 = v2;

    v2 = scrpad->post[2].vz;
    if (v2 > min)
    {
        v2 = min;
    }
    min = v2;

    v2 = scrpad->post[2].vz;
    if (v1 > v2)
    {
        v2 = v1;
    }
    v1 = v2;

    v2 = scrpad->post[3].vz;
    if (v2 > min)
    {
        v2 = min;
    }
    min = v2;

    v2 = scrpad->post[3].vz;
    if (v1 > v2)
    {
        v2 = v1;
    }
    v1 = v2;

    pOut[0].b1.z = min;
    pOut[1].b1.z = min;
    pOut[0].b2.z = v1;
    pOut[1].b2.z = v1;

    //next
    v1 = scrpad->post[4].vy;
    min = scrpad->post[5].vy;
    if (min > v1)
    {
        min = v1;
    }

    v2 = scrpad->post[5].vy;
    if (v2 < v1)
    {
        v2 = v1;
    }
    v1 = v2;

    v2 = scrpad->post[6].vy;
    if (v2 > min)
    {
       v2 = min;
    }
    min = v2;

    v2 = scrpad->post[6].vy;
    if (v1 > v2)
    {
        v2 = v1;
    }
    v1 = v2;

    v2 = scrpad->post[7].vy;
    if (v2 > min)
    {
        v2 = min;
    }
    min = v2;

    v2 = scrpad->post[7].vy;
    if (v1 > v2)
    {
        v2 = v1;
    }
    v1 = v2;

    pOut[1].b1.y = min;
    pOut[1].b2.y = v1;

    if (scrpad->unknown.vy == 0)
    {
        scrpad->unknown.vy = 1;
    }

    pOut[0].p1.h = scrpad->unknown.vx;
    pOut[0].p2.h = scrpad->unknown.vz;
    pOut[0].p3.h = scrpad->unknown.vy;

    pOut[1].p1.h = scrpad->unknown.vx;
    pOut[1].p2.h = scrpad->unknown.vz;
    pOut[1].p3.h = scrpad->unknown.vy;
}

void demothrd_4_helper_helper_8007FB90(DG_OBJS* pObjs, int n_models)
{
    MATRIX *pMatrix;
    VECTOR *pVector;
    DG_OBJ *pObj;
    int     count;

    pMatrix = (MATRIX *)0x1F800020;
    pVector = (VECTOR *)0x1F800000;

    pMatrix->t[0] -= pVector[56].vx;
    pMatrix->t[1] -= pVector[56].vy;
    pMatrix->t[2] -= pVector[56].vz;

    gte_SetRotMatrix((MATRIX *)0x1F800000);
    gte_SetTransMatrix((MATRIX *)0x1F800000);

    ApplyRotMatrixLV((VECTOR *)0x1F800034, (VECTOR *)0x1F800054);

    gte_ldclmv(0x1F800020);
    gte_rtir();
    gte_stclmv(0x1F800040);

    gte_ldclmv(0x1F800022);
    gte_rtir();
    gte_stclmv(0x1F800042);

    gte_ldclmv(0x1F800024);
    gte_rtir();
    gte_stclmv(0x1F800044);

    pObj = pObjs->objs;
    for (count = n_models; count > 0; count--)
    {
        pObj->world = *(MATRIX *)0x1F800020;
        pObj->screen = *(MATRIX *)0x1F800040;
        pObj++;
    }
}

void demothrd_4_helper_helper2_8007FDD8(DG_OBJS* pObjs, int n_models)
{
    MATRIX *pMatrix;
    VECTOR *pVector;
    int     x, y, z;
    DG_OBJ *pObj;
    int     count;

    gte_SetRotMatrix((MATRIX *)0x1F800000);
    gte_SetTransMatrix((MATRIX *)0x1F800000);

    pMatrix = (MATRIX *)0x1F800040;
    pVector = (VECTOR *)0x1F800000;

    x = pVector[56].vx;
    y = pVector[56].vy;
    z = pVector[56].vz;

    pObj = pObjs->objs;
    for (count = n_models; count > 0; count--)
    {
        pMatrix->t[0] -= x;
        pMatrix->t[1] -= y;
        pMatrix->t[2] -= z;

        ApplyRotMatrixLV((VECTOR *)pMatrix->t, (VECTOR *)pObj->screen.t);

        gte_ldclmv(&pMatrix->m[0][0]);
        gte_rtir();
        gte_stclmv(&pObj->screen.m[0][0]);

        gte_ldclmv(&pMatrix->m[0][1]);
        gte_rtir();
        gte_stclmv(&pObj->screen.m[0][1]);

        gte_ldclmv(&pMatrix->m[0][2]);
        gte_rtir();
        gte_stclmv(&pObj->screen.m[0][2]);

        pObj++;
        pMatrix++;
    }
}

void demothrd_4_helper_helper3_8007FF9C(DG_OBJS* pObjs, int n_models)
{
    SVECTOR *pMovs;
    MATRIX  *pMatrix;
    DG_OBJ  *pObj;
    int      count;

    pMovs = pObjs->movs;
    gte_SetRotMatrix(0x1F800020);

    pMatrix = (MATRIX *)0x1F800040;

    pObj = pObjs->objs;
    for (count = n_models; count > 0; count--)
    {
        gte_SetTransMatrix((MATRIX *)0x1F800040 + pObj->model->parent);
        gte_ldv0(pMovs);
        gte_rt();
        gte_ReadRotMatrix(pMatrix);
        gte_stlvnl((VECTOR *)pMatrix->t);

        pObj->world = *pMatrix;

        pMovs++;
        pObj++;
        pMatrix++;
    }
}

void demothrd_4_helper_helper4_800800D8(DG_OBJS *pObjs, int n_models)
{
    MATRIX  *pWorld;
    DG_OBJ  *pObj;
    MATRIX  *pSavedTransform;
    SVECTOR *pRots;
    SVECTOR *pWaistRot;
    SVECTOR *pAdjust;
    DG_MDL  *pMdl;
    MATRIX  *pWorkMatrix;
    int      count;
    MATRIX  *pParent;

    pWorld = (MATRIX *)0x1F800040;
    pObj = pObjs->objs;
    pSavedTransform = (MATRIX *)0x1F800360;
    pRots = pObjs->rots;
    pWaistRot = pObjs->waist_rot;
    pAdjust = pObjs->adjust;
    pMdl = pObj->model;
    pWorkMatrix = (MATRIX *)0x1F800340;

    if (pWaistRot)
    {
        RotMatrixZYX_gte(pWaistRot, pWorkMatrix);
    }
    else
    {
        RotMatrixZYX_gte(pObjs->rots, pWorkMatrix);
    }

    pWorkMatrix->t[0] = pMdl->pos.vx;
    pWorkMatrix->t[1] = pMdl->pos.vy;
    pWorkMatrix->t[2] = pMdl->pos.vz;

    if (pAdjust == NULL)
    {
        gte_CompMatrix(0x1F800020, pWorkMatrix, pWorkMatrix);

        for (count = n_models; count > 0; count--)
        {
            pMdl = pObj->model;
            pParent = (MATRIX *)0x1F800040 + pMdl->parent;

            RotMatrixZYX_gte(pRots, pWorld);

            pWorld->t[0] = pMdl->pos.vx;
            pWorld->t[1] = pMdl->pos.vy;
            pWorld->t[2] = pMdl->pos.vz;

            if (count == (n_models - 1))
            {
                gte_CompMatrix(pWorkMatrix, pWorld, pWorld);
            }
            else
            {
                gte_CompMatrix(pParent, pWorld, pWorld);
            }

            pObj->world = *pWorld;
            pObj++;
            pWorld++;
            pRots++;
        }
    }
    else
    {
        *pSavedTransform = *(MATRIX *)0x1F800020;
        *(MATRIX *)0x1F800020 = DG_ZeroMatrix_8009D430;

        for (count = n_models; count > 0; count--)
        {
            pMdl = pObj->model;
            pParent = (MATRIX *)0x1F800040 + pMdl->parent;

            RotMatrixZYX_gte(pRots, pWorld);

            pWorld->t[0] = pMdl->pos.vx;
            pWorld->t[1] = pMdl->pos.vy;
            pWorld->t[2] = pMdl->pos.vz;

            if (count == (n_models - 1))
            {
                gte_CompMatrix(pWorkMatrix, pWorld, pWorld);
            }
            else
            {
                gte_CompMatrix(pParent, pWorld, pWorld);
            }

            if (pAdjust->vz != 0)
            {
                RotMatrixZ(pAdjust->vz, pWorld);
            }

            if (pAdjust->vx != 0)
            {
                RotMatrixX(pAdjust->vx, pWorld);
            }

            if (pAdjust->vy != 0)
            {
                RotMatrixY(pAdjust->vy, pWorld);
            }

            pObj++;
            pWorld++;
            pRots++;
            pAdjust++;
        }

        *(MATRIX *)0x1F800020 = *pSavedTransform;
        pWorld = (MATRIX *)0x1F800040;

        pObj = pObjs->objs;
        for (count = n_models; count > 0; count--)
        {
            gte_CompMatrix(0x1F800020, pWorld, pWorld);
            pObj->world = *pWorld;
            pObj++;
            pWorld++;
        }
    }
}

void demothrd_4_helper_80080C20(DG_OBJS *pObjs)
{
    int n_models;

    n_models = pObjs->n_models;

    if (pObjs->root)
    {
        pObjs->world = *pObjs->root;
    }

    *(MATRIX *)getScratchAddr(8) = pObjs->world;

    if (pObjs->flag & 0x40)
    {
        demothrd_4_helper_helper_8007FB90(pObjs, n_models);
        return;
    }

    if (pObjs->rots)
    {
        demothrd_4_helper_helper4_800800D8(pObjs, n_models);
    }
    else if (pObjs->movs)
    {
        demothrd_4_helper_helper3_8007FF9C(pObjs, n_models);
    }

    demothrd_4_helper_helper2_8007FDD8(pObjs, n_models);
}

typedef struct
{
    MATRIX matrix;
    char   pad[0x360];
    int    translation[3];
} SCRPAD_DATA_80080D48;

void demothrd_Screen_Chanl_80080D48(DG_CHNL *pChnl, int idx)
{
    DG_OBJS             **ppObjs;
    SCRPAD_DATA_80080D48 *scrpad;
    int                   count;

    ppObjs = pChnl->mQueue;

    scrpad = (SCRPAD_DATA_80080D48 *)getScratchAddr(0);
    scrpad->matrix = pChnl->field_10_eye_inv;
    scrpad->matrix.t[0] = scrpad->matrix.t[1] = scrpad->matrix.t[2] = 0;

    scrpad->translation[0] = pChnl->field_30_eye.t[0];
    scrpad->translation[1] = pChnl->field_30_eye.t[1];
    scrpad->translation[2] = pChnl->field_30_eye.t[2];

    DG_800174DC(&scrpad->matrix);

    for (count = pChnl->mTotalObjectCount; count > 0; count--)
    {
        demothrd_4_helper_80080C20(*ppObjs++);
    }
}

void sub_80080E14(Actor_m1e1 *work)
{
    SVECTOR sp10;
    SVECTOR sp18;
    SVECTOR rotation;
    int     diff;
    int     f70;
    int     length;
    DG_MDL *pMdl;
    DG_MDL *pMdl2;

    diff = work->field_D60 - work->field_D8C;
    f70 = 2;

    if (diff > 0)
    {
        f70 += ((diff - (work->field_D68 - work->field_D8C)) * 5) / diff;
    }

    if ((GV_Time_800AB330 & 1) == 0)
    {
        DG_SetPos2_8001BC8C(&work->control.mov, &work->control.turn);
        rotation = work->control.turn;

        while (rotation.vy < -2048)
        {
            rotation.vy += 4096;
        }

        while (rotation.vy > 2048)
        {
            rotation.vy -= 4096;
        }

        memset(&sp10, 0, 8);

        pMdl = work->field_1C0[0].objs->objs[0].model;
        sp10.vx = pMdl->min.vx + (pMdl->max.vx - pMdl->min.vx) / 2;

        DG_PutVector_8001BE48(&sp10, &sp10, 1);

        if (work->field_740 == 1)
        {
            work->field_E8C = sp10;
        }

        sp18.vx = sp10.vx - work->field_E8C.vx;
        sp18.vy = sp10.vy - work->field_E8C.vy;
        sp18.vz = sp10.vz - work->field_E8C.vz;

        length = SquareRoot0(sp18.vx * sp18.vx + sp18.vy * sp18.vy + sp18.vz * sp18.vz);
        length = (length * (1024 - abs(ratan2(sp18.vx, sp18.vz) - rotation.vy))) >> 10;

        if (abs(length) < work->field_E84)
        {
            return;
        }

        rotation = work->control.rot;
        rotation.vy += 2048;

        if (length > 0)
        {
            if (work->field_E7C != 1 && work->field_F60 == 0)
            {
                work->field_F60 = 6;
                demothrd_2_8007DA94(&work->field_718_targets[4]->center, &rotation);
            }

            work->field_E7C = 1;
        }
        else
        {
            if (work->field_E7C != -1 && work->field_F60 == 0)
            {
                work->field_F60 = 6;
                demothrd_2_8007DA94(&work->field_718_targets[0]->center, &work->control.rot);
            }

            work->field_E7C = -1;
        }

        AN_CaterpillerSmoke_8007DA28(&work->field_718_targets[rand() % 5]->center);
        DG_InvisibleObjs(work->field_1C0[work->field_E74].objs);

        work->field_E74 += work->field_E7C;

        if (work->field_E74 < 0)
        {
            work->field_E74 = 2;
        }

        if (work->field_E74 > 2)
        {
            work->field_E74 = 0;
        }

        DG_VisibleObjs(work->field_1C0[work->field_E74].objs);

        work->field_E8C = sp10;

        if ((f70 >= 3) && (work->field_F70 <= 0))
        {
            if (work->field_F74 == 0)
            {
                sub_80032B40(&work->control.mov, 182, work->field_E60);
            }
            else
            {
                sub_80032B40(&work->control.mov, 190, work->field_E60);
            }

            work->field_F70 = f70;
            work->field_F74 = 30;
        }
    }
    else
    {
        memset(&sp10, 0, 8);

        pMdl2 = work->field_46C[0].objs->objs[0].model;
        sp10.vx = pMdl2->min.vx + (pMdl2->max.vx - pMdl2->min.vx) / 2;

        DG_SetPos2_8001BC8C(&work->control.mov, &work->control.turn);
        DG_PutVector_8001BE48(&sp10, &sp10, 1);

        if (work->field_740 == 1)
        {
            work->field_E94 = sp10;
        }

        sp18.vx = sp10.vx - work->field_E94.vx;
        sp18.vy = sp10.vy - work->field_E94.vy;
        sp18.vz = sp10.vz - work->field_E94.vz;

        length = SquareRoot0(sp18.vx * sp18.vx + sp18.vy * sp18.vy + sp18.vz * sp18.vz);
        length = (length * (1024 - abs(ratan2(sp18.vx, sp18.vz) - rotation.vy))) >> 10;

        if (abs(length) < work->field_E84)
        {
            return;
        }

        rotation = work->control.rot;
        rotation.vy += 2048;

        if (length > 0)
        {
            if (work->field_E80 != 1 && work->field_F64 == 0)
            {
                work->field_F64 = 6;
                demothrd_2_8007DA94(&work->field_718_targets[9]->center, &rotation);
            }

            work->field_E80 = 1;
        }
        else
        {
            if (work->field_E80 != -1 && work->field_F64 == 0)
            {
                work->field_F64 = 6;
                demothrd_2_8007DA94(&work->field_718_targets[5]->center, &work->control.rot);
            }

            work->field_E80 = -1;
        }

        AN_CaterpillerSmoke_8007DA28(&work->field_718_targets[(rand() % 5) + 5]->center);
        DG_InvisibleObjs(work->field_46C[work->field_E78].objs);

        work->field_E78 += work->field_E7C;

        if (work->field_E78 < 0)
        {
            work->field_E78 = 2;
        }

        if (work->field_E78 > 2)
        {
            work->field_E78 = 0;
        }

        DG_VisibleObjs(work->field_46C[work->field_E78].objs);

        work->field_E94 = sp10;

        if ((f70 >= 3) && (work->field_F70 <= 0))
        {
            if (work->field_F74 == 0)
            {
                sub_80032B40(&work->control.mov, 182, work->field_E60);
            }
            else
            {
                sub_80032B40(&work->control.mov, 190, work->field_E60);
            }

            work->field_F70 = f70;
            work->field_F74 = 30;
        }
    }
}

void M1E1GetCaterpillerVertex_800815FC(OBJECT *pE1, OBJECT *pE2, SVECTOR *pSmokeVecs, int a4)
{
    DG_MDL *model; // $v0
    int vx; // $v1
    DG_MDL *v8; // $v0
    int v9; // $v1

    model = pE1->objs->objs[0].model;
    vx = model->min.vx;
    if ( a4 == 1 )
    {
        vx += (model->max.vx - vx) >> 1;
    }

    pSmokeVecs[0].vx = vx;
    pSmokeVecs[0].vy = pE1->objs->objs[0].model->min.vy;
    pSmokeVecs[0].vz = 2 * pE1->objs->objs[0].model->max.vz / 3;

    pSmokeVecs[1].vx = vx;
    pSmokeVecs[1].vy = pE1->objs->objs[0].model->min.vy;
    pSmokeVecs[1].vz = pE1->objs->objs[0].model->max.vz / 3;

    pSmokeVecs[2].vx = vx;
    pSmokeVecs[2].vy = pE1->objs->objs[0].model->min.vy;
    pSmokeVecs[2].vz = 0;

    pSmokeVecs[3].vx = vx;
    pSmokeVecs[3].vy = pE1->objs->objs[0].model->min.vy;
    pSmokeVecs[3].vz = pE1->objs->objs[0].model->min.vz / 3;

    pSmokeVecs[4].vx = vx;
    pSmokeVecs[4].vy = pE1->objs->objs[0].model->min.vy;
    pSmokeVecs[4].vz = (2 * pE1->objs->objs[0].model->min.vz) / 3;

    v8 = pE2->objs->objs[0].model;
    v9 = v8->max.vx;
    if ( a4 == 1 )
    {
        v9 += (v8->min.vx - v9) >> 1;
    }

    pSmokeVecs[5].vx = v9;
    pSmokeVecs[5].vy = pE2->objs->objs[0].model->min.vy;
    pSmokeVecs[5].vz = 2 * pE2->objs->objs[0].model->max.vz / 3;

    pSmokeVecs[6].vx = v9;
    pSmokeVecs[6].vy = pE2->objs->objs[0].model->min.vy;
    pSmokeVecs[6].vz = pE2->objs->objs[0].model->max.vz / 3;

    pSmokeVecs[7].vx = v9;
    pSmokeVecs[7].vy = pE2->objs->objs[0].model->min.vy;
    pSmokeVecs[7].vz = 0;

    pSmokeVecs[8].vx = v9;
    pSmokeVecs[8].vy = pE2->objs->objs[0].model->min.vy;
    pSmokeVecs[8].vz = pE2->objs->objs[0].model->min.vz / 3;

    pSmokeVecs[9].vx = v9;
    pSmokeVecs[9].vy = pE2->objs->objs[0].model->min.vy;
    pSmokeVecs[9].vz = 2 * pE2->objs->objs[0].model->min.vz / 3;
}
