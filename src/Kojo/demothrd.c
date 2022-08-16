#include "demothrd.h"
#include "libfs/libfs.h"
#include "Anime/animeconv/anime.h"

extern const char aDemothrdC[];
extern SVECTOR DG_ZeroVector_800AB39C;
extern Anim_Data stru_8009F774;

int DM_ThreadStream_80079460(int flag, int unused)
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

extern Anim_Data stru_8009F73C;

void AN_CaterpillerSmoke_8007DA28(SVECTOR *pVec)
{
    anime_data_0x14 data;

    memset_8008E688(&data, 0, sizeof(anime_data_0x14));
    data.field_0_vec = *pVec;
    stru_8009F73C.field_14 = &data;
    anime_init_8005FBC8(0, 0, &stru_8009F73C);
}

#pragma INCLUDE_ASM("asm/Kojo/demothrd_2_8007DA94.s")                              // 400 bytes
#pragma INCLUDE_ASM("asm/Kojo/sub_8007DC24.s")                                     // 348 bytes
#pragma INCLUDE_ASM("asm/sub_8007DD80.s")                                          // 400 bytes

extern Anim_Data stru_8009F790;

void sub_8007DF10(SVECTOR *pVec1, SVECTOR *pVec2)
{
    SVECTOR vecs1[3]; // [sp+10h] [-48h] BYREF
    SVECTOR vecs2[3]; // [sp+28h] [-30h] BYREF
    anime_data_0x14 data; // [sp+40h] [-18h] BYREF
    
    data.field_8_vec = DG_ZeroVector_800AB39C;

    vecs1[0] = DG_ZeroVector_800AB39C;
    vecs1[0].vz = 500;

    vecs1[1] = DG_ZeroVector_800AB39C;
    vecs1[1].vz = 2000;

    vecs1[2] = DG_ZeroVector_800AB39C;
    vecs1[2].vz = 3000;

    DG_SetPos2_8001BC8C(pVec2, pVec1);
    DG_PutVector_8001BE48(vecs1, vecs2, 3);

    stru_8009F790.field_14 = &data;

    data.field_0_vec = vecs2[0];
    data.field_10_anim_idx = 0;
    anime_init_8005FBC8(0, 0, &stru_8009F790);

    data.field_0_vec = vecs2[1];
    data.field_10_anim_idx = 1;
    anime_init_8005FBC8(0, 0, &stru_8009F790);

    data.field_0_vec = vecs2[2];
    data.field_10_anim_idx = 2;
    anime_init_8005FBC8(0, 0, &stru_8009F790);
}

extern const char aDemothrdC[];
extern SVECTOR DG_ZeroVector_800AB39C;
extern Anim_Data stru_8009F774;

void sub_8007E0AC(int y, SVECTOR *pVec)
{
    int i; // $s2
    SVECTOR vec[2]; // [sp+10h] [-B0h] BYREF
    anime_data_0x14 data[8]; // [sp+20h] [-A0h] BYREF

    vec[0].vx = 0;
    vec[0].vy = y;
    vec[0].vz = 0;
    vec[1] = DG_ZeroVector_800AB39C;
    
    for (i = 0; i < 8; i++)
    {
        data[i].field_0_vec = *pVec;

        vec[1].vx = GV_RandU_80017090(64);
        vec[1].vz = GV_RandU_80017090(64);
        vec[0].vz += 512;

        DG_SetPos2_8001BC8C(&DG_ZeroVector_800AB39C, &vec[0]);
        DG_PutVector_8001BE48(&vec[1], &data[i].field_8_vec, 1);
        data[i].field_10_anim_idx = 0;
    }
    
    stru_8009F774.field_14 = data;
    anime_init_8005FBC8(0, 0, &stru_8009F774);
}

extern const char aDemothrdC[];
extern SVECTOR DG_ZeroVector_800AB39C;
extern Anim_Data stru_8009F774;

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
