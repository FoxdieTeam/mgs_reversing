#include "demothrd.h"
#include "libfs/libfs.h"
#include "Anime/animeconv/anime.h"

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
