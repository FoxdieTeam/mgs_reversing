#include "demothrd.h"
#include "libfs/libfs.h"
#include "Anime/animeconv/anime.h"
#include "libdg/libdg.h"

void DG_8001CDB8(DG_OBJS *pObjs);

extern const char aDemothrdC[];
extern SVECTOR DG_ZeroVector_800AB39C;
extern ANIMATION stru_8009F774;
extern int DG_UnDrawFrameCount_800AB380;
extern int demodebug_finish_proc_800AB414;

void Chain_Remove_8007F394(Actor_demothrd_0x78_Chain *pRoot, Actor_demothrd_0x78_Chain *pRemove);
TChanl_Fn DG_SetChanlSystemUnits_80018598(int idx, TChanl_Fn newFunc);

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

extern int dword_800BDFB8;
extern int dword_800BDFBC;
extern int dword_800BDFC0;
extern int dword_800BDFC4;

extern const char aCacheBufferCle[]; // = "Cache Buffer Cleared\n";
extern const char aCacheReadEnabl[]; // = "Cache Read Enable\n";

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

int CreateDemo_80079B50(Actor_demothrd *pActor, demothrd_0x1C *pDmoData);
#pragma INCLUDE_ASM("asm/Kojo/CreateDemo_80079B50.s")                              // 2844 bytes

//#pragma INCLUDE_ASM("asm/Kojo/DestroyDemo_8007A66C.s")                             // 732 bytes
extern const char aM1e1[];
extern const char aM1e1demo[];

void demothrd_file_stream_act_800797FC(Actor_demothrd* pActor);
void demothrd_file_stream_kill_80079960(Actor_demothrd* pActor);

extern GM_Camera        GM_Camera_800B77E8;
extern short           gGameState_800B4D98[0x60]; 

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
            GM_FreeObject_80034BF8(&pModelIter->field_1A0_pM1OrHind->field_0[0].field_0);
            GM_FreeObject_80034BF8(&pModelIter->field_1A0_pM1OrHind->field_0[1].field_0);
            GM_FreeObject_80034BF8(&pModelIter->field_1A0_pM1OrHind->field_0[2].field_0);
            GM_FreeObject_80034BF8(&pModelIter->field_1A0_pM1OrHind->field_0[3].field_0);
            GM_FreeObject_80034BF8(&pModelIter->field_1A0_pM1OrHind->field_0[4].field_0);
            GM_FreeObject_80034BF8(&pModelIter->field_1A0_pM1OrHind->field_0[5].field_0);
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

#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_helper3_8007CDF8.s")         // 284 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_helper4_8007CF14.s")         // 212 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_helper5_8007CFE8.s")         // 1052 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_m1e1_8007D404.s")  // 1476 bytes

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

extern ANIMATION stru_8009F73C;

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

extern ANIMATION stru_8009F790;

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

extern const char aDemothrdC[];
extern SVECTOR DG_ZeroVector_800AB39C;
extern ANIMATION stru_8009F774;

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

extern const char aDemothrdC[];
extern SVECTOR DG_ZeroVector_800AB39C;
extern ANIMATION stru_8009F774;

#pragma INCLUDE_ASM("asm/sub_8007E1C0.s")                                          // 3444 bytes
#pragma INCLUDE_ASM("asm/sub_8007EF34.s")                                          // 312 bytes

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
