#include "linker.h"
#include "libdg/libdg.h"
#include "map/map.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include <LIBGPU.H>
#include "spark.h"
#include "common.h"
#include "psyq.h"

extern int GM_CurrentMap_800AB9B0;
extern int GV_Clock_800AB920;

static inline int GM_GetCurrentMap()
{
    return GM_CurrentMap_800AB9B0;
};

extern const char aSparkFl[];
extern const char aSparkC[];

extern int gSparkRandomTableIndex_8009F668;
extern int dword_8009F66C;
extern short gSparkRandomTable_800BDF10[];

void spark_init_random_table_80073DB0()
{
    if (gSparkRandomTableIndex_8009F668 != -1)
    {
        short value = rand_8008E6B8();

        gSparkRandomTableIndex_8009F668++;
        gSparkRandomTableIndex_8009F668 &= 0x3F;

        gSparkRandomTable_800BDF10[gSparkRandomTableIndex_8009F668] = value;
    }
    else
    {
        short *current = gSparkRandomTable_800BDF10;
        int remaining = 0x40;

        gSparkRandomTableIndex_8009F668 = 0;
        dword_8009F66C = 0;

        do
        {
            *current = rand_8008E6B8();

            remaining--;
            current++;
        } while (remaining > 0);
    }
}

#pragma INCLUDE_ASM("asm/Okajima/spark_loader3_80073E48.s")    // 720 bytes
#pragma INCLUDE_ASM("asm/Okajima/spark_act_helper_80074118.s") // 284 bytes
#pragma INCLUDE_ASM("asm/Okajima/spark_loader4_80074234.s")    // 188 bytes

// Set
//     pPoly[i].r0 = color
//     pPoly[i].g0 = color
//     pPoly[i].b0 = color
// for
//     pPoly[0...count]
void spark_800742F0(POLY_FT4 *pPoly, int count, int color)
{
    int mask_r0_g0_b0 = color | (color << 8) | (color << 16);

    POLY_FT4 *currentPoly = pPoly;
    for (count--; count >= 0; count--, currentPoly++)
    {
        int *ptr_r0_g0_b0_code = (int *) &currentPoly->r0;

        *ptr_r0_g0_b0_code &= 0xFF000000;
        *ptr_r0_g0_b0_code |= mask_r0_g0_b0;
    }
}

void spark_act_helper_80074118(void *param_1, void *param_2, int param_3);

void spark_act_80074334(Actor_Spark *pActor)
{
    int updated_f170;
    int lightRadius;

    GM_CurrentMap_800AB9B0 = pActor->f020_map;

    updated_f170 = pActor->f170_counter - 1;
    pActor->f170_counter = updated_f170;

    if (updated_f170 < 1)
    {
        GV_DestroyActor_800151C8(&pActor->f000_actor);
    }
    else
    {
        spark_act_helper_80074118(&pActor->f028, &pActor->f068, 8);
        spark_800742F0(&pActor->f024_pPrim->field_40_pBuffers[GV_Clock_800AB920]->poly_ft4, 8, updated_f170 * 0x10);

        lightRadius = (updated_f170 - 8) * 0x200;
        if (lightRadius > 0)
        {
            DG_SetTmpLight_8001A114(&pActor->f168, lightRadius, 1000);
        }
    }
}

void spark_kill_800743DC(Actor_Spark *pActor)
{
    DG_PRIM *prim;

    prim = pActor->f024_pPrim;
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

int spark_loader_80074418(struct Actor_Spark *pActor, MATRIX *a2, int a3)
{
    DG_TEX  *pTexture;
    DG_PRIM *pNewPrim;

    pActor->f020_map = GM_CurrentMap_800AB9B0;
    spark_init_random_table_80073DB0();
    spark_loader3_80073E48(&pActor->f028, &pActor->f068, 8, a3);

    pNewPrim = DG_GetPrim(18, 8, 0, &pActor->f068, NULL);
    pActor->f024_pPrim = pNewPrim;

    if (!pNewPrim)
    {
        return -1;
    }

    DG_SetPos_8001BC44(a2);
    DG_PutPrim_8001BE00((MATRIX *)pNewPrim);
    pActor->f168.vx = a2->t[0];
    pActor->f168.vy = a2->t[1];
    pActor->f168.vz = a2->t[2];
    pTexture = DG_GetTexture_8001D830(GV_StrCode_80016CCC(aSparkFl));

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

Actor_Spark *NewSpark_80074564(MATRIX *pMatrix, int pCnt)
{
    Actor_Spark *pActor = NULL;
    int i;

    for (i = 0; i <= pCnt; i++)
    {
        pActor = (Actor_Spark *) GV_NewActor_800150E4(5, sizeof(Actor_Spark));
        if (pActor != NULL)
        {
            GV_SetNamedActor_8001514C(&pActor->f000_actor, (TActorFunction) spark_act_80074334, (TActorFunction) spark_kill_800743DC, aSparkC);

            SetSpadStack(DCache);
            if (spark_loader_80074418(pActor, pMatrix, pCnt) < 0)
            {
                ResetSpadStack();

                GV_DestroyActor_800151C8(&pActor->f000_actor);
                return NULL;
            }
            else
            {
                ResetSpadStack();
            }
        }
    }

    return pActor;
}
