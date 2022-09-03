#include "linker.h"
#include "libdg/libdg.h"
#include "map/map.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include <LIBGPU.H>
#include "spark.h"

extern int GM_CurrentMap_800AB9B0;

static inline int GM_GetCurrentMap()
{
    return GM_CurrentMap_800AB9B0;
};

extern const char aSparkFl[];

#pragma INCLUDE_ASM("asm/Okajima/InitRandamTable_80073DB0.s")  // 152 bytes
#pragma INCLUDE_ASM("asm/Okajima/spark_loader3_80073E48.s")    // 720 bytes
#pragma INCLUDE_ASM("asm/Okajima/spark_act_helper_80074118.s") // 284 bytes
#pragma INCLUDE_ASM("asm/Okajima/spark_loader4_80074234.s")    // 188 bytes
#pragma INCLUDE_ASM("asm/Okajima/spark_800742F0.s")            // 68 bytes
#pragma INCLUDE_ASM("asm/Okajima/spark_act_80074334.s")        // 168 bytes

void spark_kill_800743DC(int param_1)
{
    DG_OBJS *prim;

    prim = *(DG_OBJS **)(param_1 + 0x24);
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
    return;
}

int spark_loader_80074418(struct Actor_Spark *pActor, MATRIX *a2, int a3)
{
    DG_TEX  *pTexture;
    DG_PRIM *pNewPrim;

    pActor->f020 = GM_CurrentMap_800AB9B0;
    InitRandamTable_80073DB0();
    spark_loader3_80073E48(&pActor->f028, &pActor->f068, 8, a3);
    pNewPrim = DG_MakePrim_8001BABC(18, 8, 0, &pActor->f068, 0);
    if (pNewPrim)
    {
        DG_QueuePrim_80018274((DG_OBJS *)pNewPrim);
        DG_GroupPrim(pNewPrim, GM_CurrentMap_800AB9B0);
    }

    pActor->f024_pPrim = pNewPrim;
    if (!pNewPrim)
    {
        return -1;
    }

    DG_SetPos_8001BC44(a2);
    DG_PutPrim_8001BE00((MATRIX *)pNewPrim);
    pActor->f168 = a2->t[0];
    pActor->f16A = a2->t[1];
    pActor->f16C = a2->t[2];
    pTexture = DG_FindTexture_8001D830(GV_StrCode_80016CCC(aSparkFl));

    if (!pTexture)
    {
        return -1;
    }

    spark_loader4_80074234(&pNewPrim->field_40_pBuffers[0]->poly_ft4, 8, pTexture);
    spark_loader4_80074234(&pNewPrim->field_40_pBuffers[1]->poly_ft4, 8, pTexture);
    spark_800742F0(&pNewPrim->field_40_pBuffers[0]->poly_ft4, 8, 0);
    spark_800742F0(&pNewPrim->field_40_pBuffers[1]->poly_ft4, 8, 0);

    pActor->f170_counter = 12;
    return 0;
}

#pragma INCLUDE_ASM("asm/Okajima/NewSpark_80074564.s") // 224 bytes
