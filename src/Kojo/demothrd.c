#include "demothrd.h"

extern const char aDemothrdC[];

void demothrd_1_80079664(Actor_demothrd *pActor);
void demothrd_1_FrameRunDemo_helper_800797CC(Actor_demothrd *pActor);

void FS_StreamOpen_80024060();

int DM_ThreadStream_80079460(int flag)
{
    Actor_demothrd *pDemoThrd = (Actor_demothrd *)GV_NewActor_800150E4(1, sizeof(Actor_demothrd));
    if (!pDemoThrd)
    {
        return 0;
    }

    pDemoThrd->field_20_flag = flag;
    pDemoThrd->field_2C_timer_ticks = -1;
    GV_SetNamedActor_8001514C(&pDemoThrd->field_0_actor, (TActorFunction)demothrd_1_80079664,
                              (TActorFunction)demothrd_1_FrameRunDemo_helper_800797CC, aDemothrdC);
    pDemoThrd->field_28_map = GM_CurrentMap_800AB9B0;
    FS_StreamOpen_80024060();
    return 1;
}

#pragma INCLUDE_ASM("asm/Kojo/DM_ThreadFile_800794E4.s")                           // 384 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_80079664.s")                              // 360 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_helper_800797CC.s")          // 48 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_update_800797FC.s")                         // 356 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_kill_80079960.s")                           // 72 bytes
#pragma INCLUDE_ASM("asm/Kojo/FS_EnableMemfile_800799A8.s")                        // 116 bytes
#pragma INCLUDE_ASM("asm/sub_80079A1C.s")                                          // 16 bytes
#pragma INCLUDE_ASM("asm/sub_80079A2C.s")                                          // 184 bytes
#pragma INCLUDE_ASM("asm/sub_80079AE4.s")                                          // 108 bytes
#pragma INCLUDE_ASM("asm/Kojo/CreateDemo_80079B50.s")                              // 2844 bytes
#pragma INCLUDE_ASM("asm/Kojo/DestroyDemo_8007A66C.s")                             // 732 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_8007A948.s")                 // 1224 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_helper2_8007AE10.s")         // 8016 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_helper2_helper_8007CD60.s")  // 152 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_helper3_8007CDF8.s")         // 284 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_helper4_8007CF14.s")         // 212 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_helper5_8007CFE8.s")         // 1052 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_helper5_helper_8007D404.s")  // 1476 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_1_FrameRunDemo_helper5_helper2_8007D9C8.s") // 96 bytes
#pragma INCLUDE_ASM("asm/Kojo/AN_CaterpillerSmoke_8007DA28.s")                     // 108 bytes
#pragma INCLUDE_ASM("asm/Kojo/demothrd_2_8007DA94.s")                              // 400 bytes
#pragma INCLUDE_ASM("asm/Kojo/sub_8007DC24.s")                                     // 348 bytes
#pragma INCLUDE_ASM("asm/sub_8007DD80.s")                                          // 400 bytes
#pragma INCLUDE_ASM("asm/sub_8007DF10.s")                                          // 412 bytes
#pragma INCLUDE_ASM("asm/sub_8007E0AC.s")                                          // 276 bytes
#pragma INCLUDE_ASM("asm/sub_8007E1C0.s")                                          // 3444 bytes
#pragma INCLUDE_ASM("asm/sub_8007EF34.s")                                          // 312 bytes
#pragma INCLUDE_ASM("asm/sub_8007F06C.s")                                          // 100 bytes
#pragma INCLUDE_ASM("asm/sub_8007F0D0.s")                                          // 268 bytes
#pragma INCLUDE_ASM("asm/sub_8007F1DC.s")                                          // 348 bytes

void InitChain_8007F338(Actor_demothrd_sub *pSub)
{
    if (pSub)
    {
        pSub->field_0_pPrev = pSub;
        pSub->field_4_pNext = pSub;
    }
}

void Chain_Add_8007F350(Actor_demothrd_sub *pRoot, Actor_demothrd_sub *pAdd)
{
    Actor_demothrd_sub *prev; // $v0

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

void Chain_Remove_8007F394(Actor_demothrd_sub *pRoot, Actor_demothrd_sub *pRemove)
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
#pragma INCLUDE_ASM("asm/Kojo/demothrd_4_80080D48.s")                // 204 bytes
#pragma INCLUDE_ASM("asm/Kojo/sub_80080E14.s")                       // 2024 bytes
#pragma INCLUDE_ASM("asm/M1E1GetCaterpillerVertex_800815FC.s")       // 788 bytes
