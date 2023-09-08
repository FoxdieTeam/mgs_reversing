#include "blood.h"
#include "psyq.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Anime/animeconv/anime.h"
#include "Game/game.h"

extern int       GM_CurrentMap_800AB9B0;

extern const char aBloodC[]; // = "blood.c"
extern const char aBlood_1[]; // = "blood_1"

RECT rect_8009F60C = {50, 50, 100, 100};

ANIMATION stru_8009F614 = {31572, 1, 1, 1, 1, 500, 3, 300, 300, 200, NULL, (void *)0x80012E84};

void blood_loader2_helper2_80072080(MATRIX *pMtx, SVECTOR *arg1, SVECTOR *arg2, int count, int arg4)
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

    DG_SetPos_8001BC44(pMtx);

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
        temp_v0 = GV_RandU_80017090(4096);

        var_s3 = rcos_800925D8(temp_v0) >> 2;
        var_s4 = rsin_80092508(temp_v0) >> 2;

        var_s2 = GV_RandU_80017090(128) + 32;

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

        temp_s1 = GV_RandS_800170BC(64);
        temp_s0 = GV_RandS_800170BC(64);
        temp_v0_2 = GV_RandS_800170BC(64);

        vecs[1].vx = var_s3 + temp_s1;
        vecs[1].vy = var_s2 + temp_s0;
        vecs[1].vz = var_s4 + temp_v0_2;

        vecs[2].vx = var_s3 - temp_s1;
        vecs[2].vy = var_s2 - temp_s0;
        vecs[2].vz = var_s4 - temp_v0_2;

        DG_RotVector_8001BE98(vecs, arg1, 1);
        DG_PutVector_8001BE48(vecs, arg2, 4);

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

void blood_act_helper_80072394(SVECTOR *pVecsA, SVECTOR *pVecsB, int count)
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

void blood_loader2_helper_80072478(POLY_FT4 *pPolys, int primCount, DG_TEX *pTex, int count)
{
    int x, y, w, h;

    while (--primCount >= 0)
    {
        setPolyFT4(pPolys);
        setSemiTrans(pPolys, 1);
        x = pTex->field_8_offx;
        w = pTex->field_A_width;
        y = pTex->field_9_offy;
        h = pTex->field_B_height;

        setUVWH(pPolys, x, y, w, h);

        pPolys->tpage = pTex->field_4_tPage;
        pPolys->clut = pTex->field_6_clut;

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

void blood_act_helper_8007250C(POLY_FT4 *pPolys, int count, int shade)
{
    while (--count >= 0)
    {
        setRGB0(pPolys, shade, shade, shade);
        pPolys++;
    }
}

void blood_act_80072538(Actor_Blood *pActor)
{
    int temp_s0;
    DG_PRIM *pPrims;

    GM_SetCurrentMap(pActor->field_20_map);

    temp_s0 = --pActor->field_2A8;
    if (temp_s0 <= 0)
    {
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
        return;
    }

    blood_act_helper_80072394(pActor->field_28, pActor->field_A8, pActor->field_2AC_prim_count);

    pPrims = pActor->field_24_prims;
    blood_act_helper_8007250C(&pPrims->field_40_pBuffers[0]->poly_ft4, pActor->field_2AC_prim_count, temp_s0 * 8);
    blood_act_helper_8007250C(&pPrims->field_40_pBuffers[1]->poly_ft4, pActor->field_2AC_prim_count, temp_s0 * 8);
}

void blood_kill_800725CC(Actor_Blood *pActor)
{
    DG_PRIM *pPrims;

    pPrims = pActor->field_24_prims;
    if (pPrims)
    {
        DG_DequeuePrim_800182E0(pPrims);
        DG_FreePrim_8001BC04(pPrims);
    }
}

int blood_loader2_80072608(Actor_Blood *pActor, MATRIX *arg1, int count)
{
    DG_PRIM *pPrims;
    DG_TEX  *pTex;

    pActor->field_20_map = GM_CurrentMap_800AB9B0;

    if (count < 11)
    {
        pActor->field_2AC_prim_count = 16;
    }
    else
    {
        pActor->field_2AC_prim_count = count - 10;
    }

    blood_loader2_helper2_80072080(arg1, pActor->field_28, pActor->field_A8, pActor->field_2AC_prim_count, count);

    pPrims = DG_GetPrim(18, pActor->field_2AC_prim_count, 0, pActor->field_A8, &rect_8009F60C);
    pActor->field_24_prims = pPrims;

    if (!pPrims)
    {
        return -1;
    }

    pTex = DG_GetTexture_8001D830(GV_StrCode_80016CCC(aBlood_1));

    if (!pTex)
    {
        return -1;
    }

    blood_loader2_helper_80072478(&pPrims->field_40_pBuffers[0]->poly_ft4, pActor->field_2AC_prim_count, pTex, count);
    blood_loader2_helper_80072478(&pPrims->field_40_pBuffers[1]->poly_ft4, pActor->field_2AC_prim_count, pTex, count);

    pActor->field_2A8 = 16;
    return 0;
}

Actor_Blood * NewBlood_80072728(MATRIX *arg0, int count)
{
    SVECTOR input;
    SVECTOR speed;
    SVECTOR pos;
    int angle;
    short divisor;
    int i;
    Actor_Blood *pActor;

    pActor = NULL;

    if (count < 11)
    {
        DG_SetPos_8001BC44(arg0);

        angle = GV_RandU_80017090(4096);
        input.vx = rcos_800925D8(angle) / 4;
        input.vz = rsin_80092508(angle) / 4;

        divisor = GV_RandU_80017090(128) + 32;
        input.vx /= divisor;
        input.vy = divisor;
        input.vz /= divisor;

        DG_RotVector_8001BE98(&input, &speed, 1);
        DG_PutVector_8001BE48(&input, &pos, 1);

        speed.vx /= 4;
        speed.vy /= 4;
        speed.vz /= 4;

        AN_Blood_Mist_80072934(&pos, &speed);
    }

    for (i = 0; i < count; i++)
    {
        pActor = (Actor_Blood *)GV_NewActor_800150E4(5, sizeof(Actor_Blood));

        if (!pActor)
        {
            continue;
        }

        GV_SetNamedActor_8001514C(&pActor->field_0_actor,
                                  (TActorFunction)&blood_act_80072538,
                                  (TActorFunction)&blood_kill_800725CC,
                                  aBloodC);

        if (blood_loader2_80072608(pActor, arg0, count) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return NULL;
        }
    }

    return pActor;
}

void AN_Blood_Mist_80072934(SVECTOR *pos, SVECTOR *speed)
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

    anm = &stru_8009F614;
    anm->field_14_pre_script = &pre;

    pre.scr_num = 0;
    NewAnime_8005FBC8( NULL, 0, anm );
}
