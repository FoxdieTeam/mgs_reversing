#include "blood.h"

#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Anime/animeconv/anime.h"
#include "Game/game.h"
#include "strcode.h"

extern int GM_CurrentMap;

/*---------------------------------------------------------------------------*/

typedef struct _BloodWork
{
    GV_ACT   actor;
    int      field_20_map;
    DG_PRIM *field_24_prims;
    SVECTOR  field_28[16];
    SVECTOR  field_A8[64];
    int      field_2A8;
    int      field_2AC_prim_count;
} BloodWork;

// STATIC_ASSERT(sizeof(BloodWork) == 0x2B0, "sizeof(BloodWork) is wrong!");

#define EXEC_LEVEL GV_ACTOR_LEVEL5

/*---------------------------------------------------------------------------*/

STATIC RECT rect_8009F60C = {50, 50, 100, 100};

STATIC void blood_loader2_helper2_80072080(MATRIX *pMtx, SVECTOR *arg1, SVECTOR *arg2, int count, int arg4)
{
    SVECTOR vecs[4];
    int sp30;
    int sp34;
    int temp_s0;
    int temp_s1;
    int temp_v0;
    int temp_v0_2;
    int var_s2;
    int var_s3;
    int var_s4;
    int var_s5;

    sp34 = count;

    DG_SetPos(pMtx);

    switch (arg4)
    {
    case 0:
        sp30 = 4;
        var_s5 = 4;
        break;
    case 1:
        sp30 = 4;
        var_s5 = 4;
        break;

    case 2:
        sp30 = count >> 1;
        var_s5 = 1;
        break;

    default:
        sp30 = 0;
        var_s5 = 1;
        break;
    }

    while (--count >= 0)
    {
        temp_v0 = GV_RandU(4096);

        var_s3 = rcos(temp_v0) >> 2;
        var_s4 = rsin(temp_v0) >> 2;

        var_s2 = GV_RandU(128) + 32;

        var_s3 /= var_s2;
        var_s4 /= var_s2;

        if (sp30 >= count)
        {
            var_s2 = -var_s2 / var_s5;
            var_s3 = var_s3 / var_s5;
            var_s4 = var_s4 / var_s5;
        }

        vecs[3].vx = var_s3 * 8;
        vecs[3].vy = var_s2 * 8;

        vecs[0].vx = var_s3;
        vecs[0].vy = var_s2;
        vecs[0].vz = var_s4;
        vecs[3].vz = var_s4 * 8;

        temp_s1 = GV_RandS(64);
        temp_s0 = GV_RandS(64);
        temp_v0_2 = GV_RandS(64);

        vecs[1].vx = var_s3 + temp_s1;
        vecs[1].vy = var_s2 + temp_s0;
        vecs[1].vz = var_s4 + temp_v0_2;

        vecs[2].vx = var_s3 - temp_s1;
        vecs[2].vy = var_s2 - temp_s0;
        vecs[2].vz = var_s4 - temp_v0_2;

        DG_RotVector(vecs, arg1, 1);
        DG_PutVector(vecs, arg2, 4);

        if (count >= (sp34 - 1))
        {
            arg1->vx /= 4;
            arg1->vy /= 4;
            arg1->vz /= 4;
        }

        arg1 += 1;
        arg2 += 4;
    }
}

STATIC void blood_act_helper_80072394(SVECTOR *pVecsA, SVECTOR *pVecsB, int count)
{
    int x, y, z;

    while (--count >= 0)
    {
        x = pVecsA->vx;
        y = pVecsA->vy;
        z = pVecsA->vz;

        applyVector(&pVecsB[0], x, y, z, +=);
        applyVector(&pVecsB[3], x, y, z, +=);
        applyVector(&pVecsB[1], x, y, z, +=);
        applyVector(&pVecsB[2], x, y, z, +=);

        pVecsB += 4;

        pVecsA->vx = x;
        pVecsA->vy = y - 11;
        pVecsA->vz = z;
        pVecsA++;
    }
}

STATIC void blood_loader2_helper_80072478(POLY_FT4 *pPolys, int primCount, DG_TEX *pTex, int count)
{
    int x, y, w, h;

    while (--primCount >= 0)
    {
        setPolyFT4(pPolys);
        setSemiTrans(pPolys, 1);
        x = pTex->off_x;
        w = pTex->w;
        y = pTex->off_y;
        h = pTex->h;

        setUVWH(pPolys, x, y, w, h);

        pPolys->tpage = pTex->tpage;
        pPolys->clut = pTex->clut;

        // Some silly code to force the compiler
        // to emit "li t2, 2" and not clobber
        // a3 register (storing "count" variable).
        if (count == 2)
        {
            pPolys->tpage |= 0x20;
        }
        else
        {
            pPolys->tpage |= 0x20;
        }

        pPolys++;
    }
}

STATIC void blood_act_helper_8007250C(POLY_FT4 *pPolys, int count, int shade)
{
    while (--count >= 0)
    {
        setRGB0(pPolys, shade, shade, shade);
        pPolys++;
    }
}

STATIC void blood_Act(BloodWork *work)
{
    int temp_s0;
    DG_PRIM *prim;

    GM_SetCurrentMap(work->field_20_map);

    temp_s0 = --work->field_2A8;
    if (temp_s0 <= 0)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    blood_act_helper_80072394(work->field_28, work->field_A8, work->field_2AC_prim_count);

    prim = work->field_24_prims;
    blood_act_helper_8007250C(&prim->packs[0]->poly_ft4, work->field_2AC_prim_count, temp_s0 * 8);
    blood_act_helper_8007250C(&prim->packs[1]->poly_ft4, work->field_2AC_prim_count, temp_s0 * 8);
}

STATIC void blood_Die(BloodWork *work)
{
    DG_PRIM *prim;

    prim = work->field_24_prims;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

STATIC int blood_GetResources(BloodWork *work, MATRIX *arg1, int count)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->field_20_map = GM_CurrentMap;

    if (count < 11)
    {
        work->field_2AC_prim_count = 16;
    }
    else
    {
        work->field_2AC_prim_count = count - 10;
    }

    blood_loader2_helper2_80072080(arg1, work->field_28, work->field_A8, work->field_2AC_prim_count, count);

    prim = DG_GetPrim(DG_PRIM_POLY_FT4, work->field_2AC_prim_count, 0, work->field_A8, &rect_8009F60C);
    work->field_24_prims = prim;

    if (!prim)
    {
        return -1;
    }

    tex = DG_GetTexture(GV_StrCode("blood_1"));

    if (!tex)
    {
        return -1;
    }

    blood_loader2_helper_80072478(&prim->packs[0]->poly_ft4, work->field_2AC_prim_count, tex, count);
    blood_loader2_helper_80072478(&prim->packs[1]->poly_ft4, work->field_2AC_prim_count, tex, count);

    work->field_2A8 = 16;
    return 0;
}

/*---------------------------------------------------------------------------*/

GV_ACT *NewBlood(MATRIX *arg0, int count)
{
    SVECTOR input;
    SVECTOR speed;
    SVECTOR pos;
    int angle;
    short divisor;
    int i;
    BloodWork *work;

    work = NULL;

    if (count < 11)
    {
        DG_SetPos(arg0);

        angle = GV_RandU(4096);
        input.vx = rcos(angle) / 4;
        input.vz = rsin(angle) / 4;

        divisor = GV_RandU(128) + 32;
        input.vx /= divisor;
        input.vy = divisor;
        input.vz /= divisor;

        DG_RotVector(&input, &speed, 1);
        DG_PutVector(&input, &pos, 1);

        speed.vx /= 4;
        speed.vy /= 4;
        speed.vz /= 4;

        AN_Blood_Mist(&pos, &speed);
    }

    for (i = 0; i < count; i++)
    {
        work = GV_NewActor(EXEC_LEVEL, sizeof(BloodWork));

        if (!work)
        {
            continue;
        }

        GV_SetNamedActor(&work->actor, &blood_Act, &blood_Die, "blood.c");

        if (blood_GetResources(work, arg0, count) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

/*---------------------------------------------------------------------------*/

STATIC const int blood_anim_data[] = {
    0x00012A00, 0x02FE0105, 0x00080100, 0x000CB0B0,
    0x0AFF0105, 0x64006400, 0x0D010002, 0x0105000C,
    0x1E000AFF, 0xE8081E00, 0x0002F8F8, 0x000F0D01
};

STATIC ANIMATION blood_anim = { PCX_BLOOD_2, 1, 1, 1, 1, 500, 3, 300, 300, 200, NULL, (void *)blood_anim_data };

void AN_Blood_Mist(SVECTOR *pos, SVECTOR *speed)
{
    ANIMATION *anm;
    PRESCRIPT  pre;
    SVECTOR   *pSpeed = &pre.speed;

    pre.pos.vx = pos->vx;
    pre.pos.vy = pos->vy;
    pre.pos.vz = pos->vz;

    pSpeed->vx = speed->vx;
    pSpeed->vy = speed->vy;
    pSpeed->vz = speed->vz;

    pre.scr_num = 0;
    pre.s_anim = 0;

    anm = &blood_anim;
    anm->pre_script = &pre;

    pre.scr_num = 0;
    NewAnime( NULL, 0, anm );
}
