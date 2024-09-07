#include "linker.h"
#include "libdg/libdg.h"
#include "Game/map.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include <libgpu.h>
#include "spark.h"
#include "common.h"
#include "psyq.h"

typedef struct SparkWork
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    SVECTOR  f028[8];
    SVECTOR  f068[32];
    SVECTOR  f168;
    int      f170_counter;
} SparkWork;

#define EXEC_LEVEL 5

extern int            GM_CurrentMap_800AB9B0;
extern int            GV_Clock_800AB920;
extern unsigned short gSparkRandomTable_800BDF10[];
extern SVECTOR        DG_ZeroVector_800AB39C;

int gSparkRandomTableIndex_8009F668 = -1;
int gSparkRandomTableIndex2_8009F66C = 0;

void InitRandamTable_80073DB0(void)
{
    if (gSparkRandomTableIndex_8009F668 != -1)
    {
        short value = rand();

        gSparkRandomTableIndex_8009F668++;
        gSparkRandomTableIndex_8009F668 &= 0x3F;

        gSparkRandomTable_800BDF10[gSparkRandomTableIndex_8009F668] = value;
    }
    else
    {
        short *current = gSparkRandomTable_800BDF10;
        int remaining = 0x40;

        gSparkRandomTableIndex_8009F668 = 0;
        gSparkRandomTableIndex2_8009F66C = 0;

        do
        {
            *current = rand();

            remaining--;
            current++;
        } while (remaining > 0);
    }
}

static inline int spark_next_random(void)
{
    unsigned short *pTable = gSparkRandomTable_800BDF10;
    gSparkRandomTableIndex2_8009F66C++;
    gSparkRandomTableIndex2_8009F66C &= 0x3F;
    return pTable[gSparkRandomTableIndex2_8009F66C];
}

void spark_loader3_80073E48(SVECTOR *a1, SVECTOR *a2, int count, int a4)
{
    MATRIX sp10;
    MATRIX sp30;
    SVECTOR sp50;
    SVECTOR sp58;
    SVECTOR sp60;
    int var_s7;
    int var_s2;
    int x, y, z;
    int rx, ry, rz;

    gte_ReadRotMatrix(&sp30);

    sp58 = DG_ZeroVector_800AB39C;
    sp50.vz = 0;

    var_s7 = (a4 == 0) ? -8192 : -16384;

    while (--count >= 0)
    {
        sp50.vy = spark_next_random() & 0xFFF;
        var_s2 = sp50.vx = spark_next_random() & 0x1FF;

        RotMatrixYXZ_gte(&sp50, &sp10);
        sp58.vy = var_s7 / (var_s2 + 64);
        ApplyMatrixSV(&sp10, &sp58, &sp60);

        *a1 = sp60;

        x = sp60.vx;
        y = sp60.vy;
        z = sp60.vz;

        a2[0].vx = x;
        a2[0].vy = y;
        a2[0].vz = z;


        a2[3].vx = x * 4;
        a2[3].vy = y * 4;
        a2[3].vz = z * 4;

        rx = (spark_next_random() & 0x7F) - 64;
        ry = (spark_next_random() & 0x7F) - 64;
        rz = (spark_next_random() & 0x7F) - 64;

        x = x * 4 - x;
        y = y * 4 - y;
        z = z * 4 - z;

        a2[1].vx = x + rx;
        a2[1].vy = y + ry;
        a2[1].vz = z + rz;

        a2[2].vx = x - rx;
        a2[2].vy = y - ry;
        a2[2].vz = z - rz;

        a1 += 1;
        a2 += 4;
    }

    gte_SetRotMatrix(&sp30);
    gte_SetTransMatrix(&sp30);
}

void spark_act_helper_80074118(SVECTOR *arg0, SVECTOR *arg1, int count)
{
    int x;
    int y;
    int z;

    while (--count >= 0)
    {
        x = arg0->vx;
        y = arg0->vy;
        z = arg0->vz;

        arg1[0].vx += x;
        arg1[0].vy += y;
        arg1[0].vz += z;

        arg1[3].vx += x;
        arg1[3].vy += y;
        arg1[3].vz += z;

        arg1[1].vx += x;
        arg1[1].vy += y;
        arg1[1].vz += z;

        arg1[2].vx += x;
        arg1[2].vy += y;
        arg1[2].vz += z;

        arg0->vx = x - (x / 8);
        arg0->vy = y - (y / 8);
        arg0->vz = z - (z / 8);

        arg1 += 4;
        arg0++;
    }
}

void spark_loader4_80074234(POLY_FT4 *pPoly, int count, DG_TEX *pTex)
{
    POLY_FT4 *pScratch;
    int x, y, w, h;

    pScratch = (POLY_FT4 *)getScratchAddr(0);

    setPolyFT4(pScratch);
    setSemiTrans(pScratch, 1);

    x = pTex->off_x;
    w = pTex->w;
    y = pTex->off_y;
    h = pTex->h;

    setUVWH(pScratch, x, y, w, h);

    pScratch->tpage = pTex->tpage;
    pScratch->clut = pTex->clut;

    while (--count >= 0)
    {
        LCOPY2(&pScratch->tag, &pPoly->tag, &pScratch->r0, &pPoly->r0);
        LCOPY(&pScratch->u0, &pPoly->u0);
        LCOPY(&pScratch->u1, &pPoly->u1);
        LCOPY(&pScratch->u2, &pPoly->u2);
        LCOPY(&pScratch->u3, &pPoly->u3);
        pPoly++;
    }
}

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

void spark_act_80074334(SparkWork *work)
{
    int updated_f170;
    int lightRadius;

    GM_CurrentMap_800AB9B0 = work->map;

    updated_f170 = work->f170_counter - 1;
    work->f170_counter = updated_f170;

    if (updated_f170 < 1)
    {
        GV_DestroyActor(&work->actor);
    }
    else
    {
        spark_act_helper_80074118(work->f028, work->f068, 8);
        spark_800742F0(&work->prim->packs[GV_Clock_800AB920]->poly_ft4, 8, updated_f170 * 0x10);

        lightRadius = (updated_f170 - 8) * 0x200;
        if (lightRadius > 0)
        {
            DG_SetTmpLight(&work->f168, lightRadius, 1000);
        }
    }
}

void spark_kill_800743DC(SparkWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

int SparkGetResources_80074418(struct SparkWork *work, MATRIX *a2, int a3)
{
    DG_TEX  *pTexture;
    DG_PRIM *pNewPrim;

    work->map = GM_CurrentMap_800AB9B0;
    InitRandamTable_80073DB0();
    spark_loader3_80073E48(work->f028, work->f068, 8, a3);

    pNewPrim = DG_GetPrim(DG_PRIM_POLY_FT4, 8, 0, work->f068, NULL);
    work->prim = pNewPrim;

    if (!pNewPrim)
    {
        return -1;
    }

    DG_SetPos(a2);
    DG_PutPrim(&pNewPrim->world);
    work->f168.vx = a2->t[0];
    work->f168.vy = a2->t[1];
    work->f168.vz = a2->t[2];
    pTexture = DG_GetTexture(GV_StrCode("spark_fl"));

    if (!pTexture)
    {
        return -1;
    }

    spark_loader4_80074234(&pNewPrim->packs[0]->poly_ft4, 8, pTexture);
    spark_loader4_80074234(&pNewPrim->packs[1]->poly_ft4, 8, pTexture);
    spark_800742F0(&pNewPrim->packs[0]->poly_ft4, 8, 0);
    spark_800742F0(&pNewPrim->packs[1]->poly_ft4, 8, 0);

    work->f170_counter = 12;
    return 0;
}

GV_ACT *NewSpark_80074564(MATRIX *pMatrix, int pCnt)
{
    SparkWork *work = NULL;
    int i;

    for (i = 0; i <= pCnt; i++)
    {
        work = (SparkWork *) GV_NewActor(EXEC_LEVEL, sizeof(SparkWork));
        if (work != NULL)
        {
            GV_SetNamedActor(&work->actor, (TActorFunction)spark_act_80074334, (TActorFunction)spark_kill_800743DC, "spark.c");

            SetSpadStack(SPAD_STACK_ADDR);
            if (SparkGetResources_80074418(work, pMatrix, pCnt) < 0)
            {
                ResetSpadStack();

                GV_DestroyActor(&work->actor);
                return NULL;
            }
            else
            {
                ResetSpadStack();
            }
        }
    }

    return &work->actor;
}
