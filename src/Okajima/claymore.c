#include "claymore.h"
#include "spark.h"
#include "psyq.h"
#include "unknown.h"
#include "Game/game.h"
#include "map/map.h"
#include "Anime/animeconv/anime.h"

extern map_record   *claymore_map_record_800bdf08;
extern int           GM_CurrentMap_800AB9B0;
extern int           GM_GameOverTimer_800AB3D4;
extern SVECTOR       DG_ZeroVector_800AB39C;
extern SVECTOR       svector_80012EDC;
extern int           claymore_map_800AB9DC;
extern const SVECTOR stru_80012EEC;

extern const char aBullet_0[];  // "bullet"
extern const char aClaymoreC[]; // = "claymore.c"

SVECTOR stru_8009F630[4] = {{20, 0, 0, 0}, {-20, 0, 0, 0}, {0, 20, 0, 0}, {0, -20, 0, 0}};
SVECTOR stru_8009F650[2] = {{0, 0, 200, 0}, {0, 0, 10000, 0}};
SVECTOR stru_8009F660 = {100, 100, 100, 0};

void claymore_800731CC(SVECTOR *param_1)
{
    DG_PutVector_8001BE48(stru_8009F630, param_1, 4); // 4 = sizeof?
}

void claymore_loader_helper2_800731F8(Actor_Claymore *claymore)
{
    // Perform copies:
    //   claymore->field_E8  = claymore->field_C8;
    //   claymore->field_F0  = claymore->field_D0;
    //   claymore->field_F8  = claymore->field_D8;
    //   claymore->field_100 = claymore->field_E0;
    //
    // This function is the same as claymore_act_helper_800732B0,
    // but this one calls claymore_800731CC earlier.

    int      i;
    SVECTOR *vec = &claymore->field_C8;

    claymore_800731CC(vec);
    for (i = 1; i > 0; i--, vec += 4)
    {
        memcpy(&vec[4], &vec[0], 4 * sizeof(SVECTOR));
    }
}

void claymore_act_helper_800732B0(Actor_Claymore *claymore)
{
    // Perform copies:
    //   claymore->field_E8  = claymore->field_C8;
    //   claymore->field_F0  = claymore->field_D0;
    //   claymore->field_F8  = claymore->field_D8;
    //   claymore->field_100 = claymore->field_E0;
    //
    // This function is the same as claymore_loader_helper2_800731F8,
    // but this one calls claymore_800731CC later.

    int      i;
    SVECTOR *vec = &claymore->field_E8;

    for (i = 1; i > 0; i--, vec -= 4)
    {
        memcpy(&vec[0], &vec[-4], 4 * sizeof(SVECTOR));
    }
    claymore_800731CC(vec);
}

void claymore_act_helper_80073364(Actor_Claymore *pActor)
{
    SVECTOR *pSrc;
    SVECTOR *pDst;
    int i;

    pSrc = &pActor->field_C8;
    pDst = &pActor->field_88;

    for (i = 1; i > 0; pDst += 8, pSrc += 4, i--)
    {
        pDst[0] = pSrc[0];
        pDst[1] = pSrc[1];
        pDst[2] = pSrc[4];
        pDst[3] = pSrc[5];
        pDst[4] = pSrc[2];
        pDst[5] = pSrc[3];
        pDst[6] = pSrc[6];
        pDst[7] = pSrc[7];
    }
}

void claymore_loader_helper_80073490(POLY_FT4 *pPoly, DG_TEX *pTex)
{
    int i, j;
    int shade;
    int x, y, w, h;

    for (i = 0; i < 1; i++)
    {
        for (j = 2; j > 0; j--)
        {
            setPolyFT4(pPoly);
            setSemiTrans(pPoly, 1);

            shade = GV_RandS_800170BC(64) + 191;
            setRGB0(pPoly, shade, shade, shade);

            x = pTex->field_8_offx;
            w = pTex->field_A_width;
            pPoly->u0 = pPoly->u2 = x;
            pPoly->u1 = pPoly->u3 = w + x;

            y = pTex->field_9_offy;
            h = pTex->field_B_height + 1;
            pPoly->v0 = pPoly->v1 = y + (h * i);
            pPoly->v2 = pPoly->v3 = y + (h * (i + 1)) - 1;

            pPoly->tpage = pTex->field_4_tPage;
            pPoly->clut =  pTex->field_6_clut;
            pPoly->tpage |= 0x60;
            pPoly++;
        }
    }
}

int claymore_loader_helper_800735A0(Actor_Claymore *pActor, SVECTOR *arg1, SVECTOR *arg2)
{
    SVECTOR vec;
    SVECTOR vec2;
    SVECTOR *temp_v0;
    int var_s2;
    int len;

    DG_SetPos2_8001BC8C(arg1, arg2);
    DG_PutVector_8001BE48(stru_8009F650, &vec, 2);

    var_s2 = 0;

    if (sub_80028454(claymore_map_record_800bdf08->field_8_hzd, &vec, &vec2, 15, 4))
    {
        sub_80028890(&vec2);
        temp_v0 = sub_80028820();

        if ((int)temp_v0 < 0)
        {
            sub_800272E0(temp_v0, &pActor->field_118);
        }
        else
        {
            pActor->field_118.vx = temp_v0[2].pad;
            pActor->field_118.vz = temp_v0[3].pad;
            pActor->field_118.vy = temp_v0[4].pad;
        }

        var_s2 = 1;
    }

    pActor->field_110 = vec2;

    GV_SubVec3_80016D40(&vec2, &vec, &vec);
    len = GV_VecLen3_80016D80(&vec);
    pActor->field_128 = var_s2;

    return len;
}

void claymore_act_800736B0(Actor_Claymore *claymore)
{
    SVECTOR vec;
    MATRIX  matrix;

    if (claymore->field_120 == 0)
    {
        int field_10C = claymore->field_10C;

        GM_CurrentMap_800AB9B0 = claymore->field_20_map;
        claymore->field_10C += 1500;
        if (claymore->field_10C < claymore->field_108)
        {
            GV_AddVec3_80016D00(&claymore->field_24, &claymore->field_34, &vec);
        }
        else
        {
            vec = claymore->field_110;
        }

        GM_Target_8002E1B8(&claymore->field_24, &vec, claymore->field_20_map, &vec, 0xff);
        GM_Target_SetVector_8002D500(&claymore->field_3C_target, &vec);

        if (GM_GameOverTimer_800AB3D4 == 0)
        {
            if (sub_8002D7DC(&claymore->field_3C_target) != 0)
            {
                claymore->field_108 = 0;
                claymore->field_128 = 2;
            }
        }
        else
        {
            claymore->field_108 = 0;
        }

        claymore->field_24 = vec;
        DG_SetPos2_8001BC8C(&claymore->field_24, &claymore->field_2C);

        claymore_act_helper_800732B0(claymore);
        claymore_act_helper_80073364(claymore);
        if (claymore->field_108 <= claymore->field_10C)
        {
            if (claymore->field_128 == 1 && (field_10C = GV_RandU_80017090(0x20), 0x14 < field_10C))
            {
                ReadRotMatrix(&matrix);
                matrix.t[0] = claymore->field_110.vx;
                matrix.t[1] = claymore->field_110.vy;
                matrix.t[2] = claymore->field_110.vz;
                DG_ReflectMatrix_8001EDCC(&claymore->field_118, &matrix, &matrix);
                NewSpark_80074564(&matrix, 0);
                GM_SeSet_80032858(&claymore->field_24, 0x28);
            }

            claymore->field_120 = 1;
            claymore->field_124 = 0;
            claymore->field_34 = DG_ZeroVector_800AB39C;
        }
    }
    else
    {
        int field_124 = claymore->field_124;
        if (field_124 == 0)
        {
            DG_InvisiblePrim(claymore->field_84_pPrim);
        }
        if (field_124 >= 3)
        {
            GV_DestroyActor_800151C8(&claymore->field_0);
        }
        else
        {
            claymore->field_124 = field_124 + 1;
        }
    }
}

void claymore_kill_800738F4(Actor_Claymore *claymore)
{
    DG_PRIM *prim;

    prim = claymore->field_84_pPrim;
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

void claymore_loader_80073930(Actor_Claymore *pActor)
{
    SVECTOR vec;

    TARGET *pTarget = &pActor->field_3C_target;
    GM_SetTarget_8002DC74(&pActor->field_3C_target, 4, 0, &stru_8009F660);
    vec.vx = pActor->field_34.vx / 32;
    vec.vy = pActor->field_34.vy / 32;
    vec.vz = pActor->field_34.vz / 32;
    GM_Target_8002DCCC(pTarget, 0, 2, 256, 0, &vec);
    pTarget->field_44 = 5;
}

int claymore_loader_800739EC(Actor_Claymore *claymore, SVECTOR *new_field_24, SVECTOR *new_field_2C)
{
    DG_PRIM *prim;
    DG_TEX  *tex;
    SVECTOR  new_field_34 = svector_80012EDC;
    int      retval;

    claymore->field_10C = 0;
    claymore->field_20_map = GM_CurrentMap_800AB9B0;
    claymore->field_24 = *new_field_24;
    claymore->field_2C = *new_field_2C;
    claymore->field_2C.vy += GV_RandS_800170BC(0x200);
    claymore->field_2C.vx += GV_RandS_800170BC(0x200);
    claymore->field_108 = claymore_loader_helper_800735A0(claymore, &claymore->field_24, &claymore->field_2C);

    DG_SetPos2_8001BC8C(&claymore->field_24, &claymore->field_2C);
    DG_RotVector_8001BE98(&new_field_34, &claymore->field_34, 1);

    prim = DG_GetPrim(18, 2, 0, &claymore->field_88, NULL);
    claymore->field_84_pPrim = prim;

    retval = -1;

    if (prim)
    {
        prim->field_2E_k500 = 1000;

        tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC(aBullet_0));
        if (tex)
        {
            claymore_loader_helper_80073490(&prim->field_40_pBuffers[0]->poly_ft4, tex);
            claymore_loader_helper_80073490(&prim->field_40_pBuffers[1]->poly_ft4, tex);
            claymore_loader_helper2_800731F8(claymore);
            retval = 0;
        }
        else
        {
            return -1;
        }
    }
    return retval;
}

Actor_Claymore * NewClaymore_80073B8C(SVECTOR *noise_position, SVECTOR *new_field_2C, int pCnt, int param_4)
{
    int             i;
    Actor_Claymore *claymore;
    Actor_Claymore *null_claymore;
    SVECTOR         new_field_24;
    SVECTOR         vec2;
    int             current_map;

    claymore = NULL;
    null_claymore = NULL;

    new_field_24 = stru_80012EEC;

    vec2 = *noise_position;
    vec2.vx += GV_RandS_800170BC(0x100);
    vec2.vy += GV_RandS_800170BC(0x80);

    DG_SetPos2_8001BC8C(&vec2, new_field_2C);
    DG_PutVector_8001BE48(&new_field_24, &new_field_24, 1);

    if (param_4 == 8)
    {
        GM_SeSet_80032858(noise_position, 0x29);
        GM_SetNoise(0xff, 0x20, noise_position);

        anime_create_8005DF50(&new_field_24, new_field_2C);
    }

    // from map_record* to int, back to map_record*: (to get a match)
    current_map = (int)Map_FromId_800314C0(GM_CurrentMap_800AB9B0);
    claymore_map_record_800bdf08 = (map_record *)current_map;

    for (i = 0; i < pCnt; i++)
    {
        claymore = (Actor_Claymore *)GV_NewActor_800150E4(6, sizeof(Actor_Claymore));
        if (claymore != NULL)
        {
            GV_SetNamedActor_8001514C(&claymore->field_0, (TActorFunction)claymore_act_800736B0,
                                      (TActorFunction)claymore_kill_800738F4, aClaymoreC);
            current_map = GM_CurrentMap_800AB9B0;
            claymore_map_800AB9DC = current_map;
            if (claymore_loader_800739EC(claymore, &new_field_24, new_field_2C) < 0)
            {
                GV_DestroyActor_800151C8(&claymore->field_0);
                return NULL;
            }
            claymore_loader_80073930(claymore);
            claymore->field_120 = 0;
        }
        else
        {
            return null_claymore;
        }
    }

    return claymore;
}
