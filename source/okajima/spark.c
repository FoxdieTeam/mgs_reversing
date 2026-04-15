#include "spark.h"

#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

extern unsigned short gSparkRandomTable[];

/*---------------------------------------------------------------------------*/

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    SVECTOR  f028[8];
    SVECTOR  f068[32];
    SVECTOR  f168;
    int      f170_counter;
} Work;

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

        gSparkRandomTable[gSparkRandomTableIndex] = value;
    }
    else
    {
        short *current = gSparkRandomTable;
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
    unsigned short *table = gSparkRandomTable;

    gSparkRandomTableIndex2++;
    gSparkRandomTableIndex2 &= 0x3F;
    return table[gSparkRandomTableIndex2];
}

/*---------------------------------------------------------------------------*/

static void spark_loader3_80073E48(SVECTOR *a1, SVECTOR *a2, int count, int a4)
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

static void spark_act_helper_80074118(SVECTOR *arg0, SVECTOR *arg1, int count)
{
    int x, y, z;

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

static void spark_loader4_80074234(POLY_FT4 *poly, int count, DG_TEX *tex)
{
    POLY_FT4 *scratch;

    scratch = (POLY_FT4 *)getScratchAddr(0);

    setPolyFT4(scratch);
    setSemiTrans(scratch, 1);
    DG_SetPacketTexture4(scratch, tex);

    while (--count >= 0)
    {
        LCOPY2(&scratch->tag, &poly->tag, &scratch->r0, &poly->r0);
        LCOPY(&scratch->u0, &poly->u0);
        LCOPY(&scratch->u1, &poly->u1);
        LCOPY(&scratch->u2, &poly->u2);
        LCOPY(&scratch->u3, &poly->u3);
        poly++;
    }
}

// Set
//     poly[i].r0 = shade
//     poly[i].g0 = shade
//     poly[i].b0 = shade
// for
//     poly[0...count]
static void SetSparkShade(POLY_FT4 *poly, int count, int shade)
{
    int color = MAKE_RGB(shade, shade, shade);
    POLY_FT4 *currentPoly = poly;

    for (count--; count >= 0; count--, currentPoly++)
    {
        int *color_code = (int *)&currentPoly->r0;

        *color_code &= RGBA_A_MASK;
        *color_code |= color;
    }
}

static void Act(Work *work)
{
    int updated_f170;
    int lightRadius;

    GM_SetCurrentMap(work->map);

    updated_f170 = work->f170_counter - 1;
    work->f170_counter = updated_f170;

    if (updated_f170 < 1)
    {
        GV_DestroyActor(&work->actor);
    }
    else
    {
        spark_act_helper_80074118(work->f028, work->f068, 8);
        SetSparkShade(work->prim->packs[GV_Clock], 8, updated_f170 * 0x10);

        lightRadius = (updated_f170 - 8) * 0x200;
        if (lightRadius > 0)
        {
            DG_SetTmpLight(&work->f168, lightRadius, 1000);
        }
    }
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, MATRIX *a2, int count)
{
    DG_TEX  *tex;
    DG_PRIM *prim;

    work->map = GM_CurrentMap;
    InitRandamTable();
    spark_loader3_80073E48(work->f028, work->f068, 8, count);

    prim = GM_MakePrim(DG_PRIM_POLY_FT4, 8, work->f068, NULL);
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

    spark_loader4_80074234(prim->packs[0], 8, tex);
    spark_loader4_80074234(prim->packs[1], 8, tex);
    SetSparkShade(prim->packs[0], 8, 0);
    SetSparkShade(prim->packs[1], 8, 0);

    work->f170_counter = 12;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewSpark(MATRIX *pMatrix, int count)
{
    Work *work = NULL;
    int i;

    for (i = 0; i <= count; i++)
    {
        work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
        if (work != NULL)
        {
            GV_SetNamedActor(&work->actor, Act, Die, "spark.c");

            SetSpadStack(SPAD_STACK_ADDR);
            if (GetResources(work, pMatrix, count) < 0)
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

    return (void *)work;
}
