#include "spark.h"

#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/map.h"

extern int            GM_CurrentMap;
extern int            GV_Clock;
extern unsigned short gSparkRandomTable_800BDF10[];

/*---------------------------------------------------------------------------*/

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

#define EXEC_LEVEL GV_ACTOR_LEVEL5

/*---------------------------------------------------------------------------*/

STATIC int gSparkRandomTableIndex = -1;
STATIC int gSparkRandomTableIndex2 = 0;

void InitRandamTable(void)
{
    if (gSparkRandomTableIndex != -1)
    {
        short value = rand();

        gSparkRandomTableIndex++;
        gSparkRandomTableIndex &= 0x3F;

        gSparkRandomTable_800BDF10[gSparkRandomTableIndex] = value;
    }
    else
    {
        short *current = gSparkRandomTable_800BDF10;
        int remaining = 0x40;

        gSparkRandomTableIndex = 0;
        gSparkRandomTableIndex2 = 0;

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
    gSparkRandomTableIndex2++;
    gSparkRandomTableIndex2 &= 0x3F;
    return pTable[gSparkRandomTableIndex2];
}

STATIC void spark_loader3_80073E48(SVECTOR *a1, SVECTOR *a2, int count, int a4)
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

    sp58 = DG_ZeroVector;
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

STATIC void spark_act_helper_80074118(SVECTOR *arg0, SVECTOR *arg1, int count)
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

STATIC void spark_loader4_80074234(POLY_FT4 *pPoly, int count, DG_TEX *tex)
{
    POLY_FT4 *scratch;
    int x, y, w, h;

    scratch = (POLY_FT4 *)getScratchAddr(0);

    setPolyFT4(scratch);
    setSemiTrans(scratch, 1);

    x = tex->off_x;
    w = tex->w;
    y = tex->off_y;
    h = tex->h;

    setUVWH(scratch, x, y, w, h);

    scratch->tpage = tex->tpage;
    scratch->clut = tex->clut;

    while (--count >= 0)
    {
        LCOPY2(&scratch->tag, &pPoly->tag, &scratch->r0, &pPoly->r0);
        LCOPY(&scratch->u0, &pPoly->u0);
        LCOPY(&scratch->u1, &pPoly->u1);
        LCOPY(&scratch->u2, &pPoly->u2);
        LCOPY(&scratch->u3, &pPoly->u3);
        pPoly++;
    }
}

// Set
//     pPoly[i].r0 = color
//     pPoly[i].g0 = color
//     pPoly[i].b0 = color
// for
//     pPoly[0...count]
STATIC void spark_800742F0(POLY_FT4 *pPoly, int count, int color)
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

STATIC void spark_Act(SparkWork *work)
{
    int updated_f170;
    int lightRadius;

    GM_CurrentMap = work->map;

    updated_f170 = work->f170_counter - 1;
    work->f170_counter = updated_f170;

    if (updated_f170 < 1)
    {
        GV_DestroyActor(&work->actor);
    }
    else
    {
        spark_act_helper_80074118(work->f028, work->f068, 8);
        spark_800742F0(&work->prim->packs[GV_Clock]->poly_ft4, 8, updated_f170 * 0x10);

        lightRadius = (updated_f170 - 8) * 0x200;
        if (lightRadius > 0)
        {
            DG_SetTmpLight(&work->f168, lightRadius, 1000);
        }
    }
}

STATIC void spark_Die(SparkWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

STATIC int spark_GetResources(struct SparkWork *work, MATRIX *a2, int count)
{
    DG_TEX  *tex;
    DG_PRIM *prim;

    work->map = GM_CurrentMap;
    InitRandamTable();
    spark_loader3_80073E48(work->f028, work->f068, 8, count);

    prim = DG_GetPrim(DG_PRIM_POLY_FT4, 8, 0, work->f068, NULL);
    work->prim = prim;

    if (!prim)
    {
        return -1;
    }

    DG_SetPos(a2);
    DG_PutPrim(&prim->world);
    work->f168.vx = a2->t[0];
    work->f168.vy = a2->t[1];
    work->f168.vz = a2->t[2];
    tex = DG_GetTexture(GV_StrCode("spark_fl"));

    if (!tex)
    {
        return -1;
    }

    spark_loader4_80074234(&prim->packs[0]->poly_ft4, 8, tex);
    spark_loader4_80074234(&prim->packs[1]->poly_ft4, 8, tex);
    spark_800742F0(&prim->packs[0]->poly_ft4, 8, 0);
    spark_800742F0(&prim->packs[1]->poly_ft4, 8, 0);

    work->f170_counter = 12;
    return 0;
}

/*---------------------------------------------------------------------------*/

GV_ACT *NewSpark(MATRIX *pMatrix, int count)
{
    SparkWork *work = NULL;
    int i;

    for (i = 0; i <= count; i++)
    {
        work = (SparkWork *) GV_NewActor(EXEC_LEVEL, sizeof(SparkWork));
        if (work != NULL)
        {
            GV_SetNamedActor(&work->actor,
                             (GV_ACTFUNC)spark_Act,
                             (GV_ACTFUNC)spark_Die,
                             "spark.c");

            SetSpadStack(SPAD_STACK_ADDR);
            if (spark_GetResources(work, pMatrix, count) < 0)
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
