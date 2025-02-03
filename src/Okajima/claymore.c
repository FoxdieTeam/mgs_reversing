#include "claymore.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/game.h"
#include "Game/map.h"
#include "Game/target.h"
#include "Anime/animeconv/anime.h"
#include "SD/g_sound.h"
#include "spark.h"

extern MAP *claymore_MAP_800bdf08;
extern int GM_CurrentMap;
extern int GM_ClaymoreMap_800AB9DC;

/*---------------------------------------------------------------------------*/

typedef struct ClaymoreWork
{
    GV_ACT      actor;
    int       field_20_map;
    SVECTOR   field_24;
    SVECTOR   field_2C;
    SVECTOR   field_34;
    TARGET field_3C_target;
    DG_PRIM  *field_84_pPrim;
    SVECTOR   field_88;
    int       field_90;
    int       field_94;
    int       field_98;
    int       field_9C;
    int       field_A0;
    int       field_A4;
    int       field_A8;
    int       field_AC;
    int       field_B0;
    int       field_B4;
    int       field_B8;
    int       field_BC;
    int       field_C0;
    int       field_C4;
    SVECTOR   field_C8; // Maybe a SVECTOR array from here? ([8], [4][2] or [2][4])
    SVECTOR   field_D0;
    SVECTOR   field_D8;
    SVECTOR   field_E0;
    SVECTOR   field_E8;
    SVECTOR   field_F0;
    SVECTOR   field_F8;
    SVECTOR   field_100;
    int       field_108;
    int       field_10C;
    SVECTOR   field_110;
    SVECTOR   field_118;
    int       field_120;
    int       field_124; // Counter increasing from 0 to 3?
    int       field_128;
} ClaymoreWork;

#define EXEC_LEVEL GV_ACTOR_AFTER

/*---------------------------------------------------------------------------*/

STATIC SVECTOR stru_8009F630[4] = {
    {  20,   0, 0, 0 },
    { -20,   0, 0, 0 },
    {   0,  20, 0, 0 },
    {   0, -20, 0, 0 }
};
STATIC SVECTOR stru_8009F650[2] = {
    { 0, 0,   200, 0 },
    { 0, 0, 10000, 0 }
};
STATIC SVECTOR stru_8009F660 = { 100, 100, 100, 0 };

STATIC void claymore_800731CC(SVECTOR *param_1)
{
    DG_PutVector(stru_8009F630, param_1, 4); // 4 = sizeof?
}

STATIC void claymore_loader_helper2_800731F8(ClaymoreWork *work)
{
    // Perform copies:
    //   work->field_E8  = work->field_C8;
    //   work->field_F0  = work->field_D0;
    //   work->field_F8  = work->field_D8;
    //   work->field_100 = work->field_E0;
    //
    // This function is the same as claymore_act_helper_800732B0,
    // but this one calls claymore_800731CC earlier.

    int      i;
    SVECTOR *vec = &work->field_C8;

    claymore_800731CC(vec);
    for (i = 1; i > 0; i--, vec += 4)
    {
        memcpy(&vec[4], &vec[0], 4 * sizeof(SVECTOR));
    }
}

STATIC void claymore_act_helper_800732B0(ClaymoreWork *work)
{
    // Perform copies:
    //   work->field_E8  = work->field_C8;
    //   work->field_F0  = work->field_D0;
    //   work->field_F8  = work->field_D8;
    //   work->field_100 = work->field_E0;
    //
    // This function is the same as claymore_loader_helper2_800731F8,
    // but this one calls claymore_800731CC later.

    int      i;
    SVECTOR *vec = &work->field_E8;

    for (i = 1; i > 0; i--, vec -= 4)
    {
        memcpy(&vec[0], &vec[-4], 4 * sizeof(SVECTOR));
    }
    claymore_800731CC(vec);
}

STATIC void claymore_act_helper_80073364(ClaymoreWork *work)
{
    SVECTOR *pSrc;
    SVECTOR *pDst;
    int i;

    pSrc = &work->field_C8;
    pDst = &work->field_88;

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

STATIC void claymore_loader_helper_80073490(POLY_FT4 *pPoly, DG_TEX *pTex)
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

            shade = GV_RandS(64) + 191;
            setRGB0(pPoly, shade, shade, shade);

            x = pTex->off_x;
            w = pTex->w;
            pPoly->u0 = pPoly->u2 = x;
            pPoly->u1 = pPoly->u3 = w + x;

            y = pTex->off_y;
            h = pTex->h + 1;
            pPoly->v0 = pPoly->v1 = y + (h * i);
            pPoly->v2 = pPoly->v3 = y + (h * (i + 1)) - 1;

            pPoly->tpage = pTex->tpage;
            pPoly->clut =  pTex->clut;
            pPoly->tpage |= 0x60;
            pPoly++;
        }
    }
}

STATIC int claymore_loader_helper_800735A0(ClaymoreWork *work, SVECTOR *arg1, SVECTOR *arg2)
{
    SVECTOR  vec;
    SVECTOR  vec2;
    HZD_FLR *floor;
    int      var_s2;
    int      len;

    DG_SetPos2(arg1, arg2);
    DG_PutVector(stru_8009F650, &vec, 2);

    var_s2 = 0;

    if (HZD_80028454(claymore_MAP_800bdf08->hzd, &vec, &vec2, 15, 4))
    {
        HZD_GetSpadVector(&vec2);
        floor = HZD_80028820();

        if ((int)floor < 0)
        {
            HZD_800272E0(floor, &work->field_118);
        }
        else
        {
            work->field_118.vx = floor->p1.h;
            work->field_118.vz = floor->p2.h;
            work->field_118.vy = floor->p3.h;
        }

        var_s2 = 1;
    }

    work->field_110 = vec2;

    GV_SubVec3(&vec2, &vec, &vec);
    len = GV_VecLen3(&vec);
    work->field_128 = var_s2;

    return len;
}

STATIC void claymore_Act(ClaymoreWork *work)
{
    SVECTOR vec;
    MATRIX  matrix;

    if (work->field_120 == 0)
    {
        int field_10C = work->field_10C;

        GM_CurrentMap = work->field_20_map;
        work->field_10C += 1500;
        if (work->field_10C < work->field_108)
        {
            GV_AddVec3(&work->field_24, &work->field_34, &vec);
        }
        else
        {
            vec = work->field_110;
        }

        GM_Target_8002E1B8(&work->field_24, &vec, work->field_20_map, &vec, 0xff);
        GM_MoveTarget(&work->field_3C_target, &vec);

        if (GM_GameOverTimer == 0)
        {
            if (GM_PowerTarget(&work->field_3C_target) != 0)
            {
                work->field_108 = 0;
                work->field_128 = 2;
            }
        }
        else
        {
            work->field_108 = 0;
        }

        work->field_24 = vec;
        DG_SetPos2(&work->field_24, &work->field_2C);

        claymore_act_helper_800732B0(work);
        claymore_act_helper_80073364(work);
        if (work->field_108 <= work->field_10C)
        {
            if (work->field_128 == 1 && (field_10C = GV_RandU(0x20), 0x14 < field_10C))
            {
                ReadRotMatrix(&matrix);
                matrix.t[0] = work->field_110.vx;
                matrix.t[1] = work->field_110.vy;
                matrix.t[2] = work->field_110.vz;
                DG_ReflectMatrix(&work->field_118, &matrix, &matrix);
                NewSpark(&matrix, 0);
                GM_SeSet(&work->field_24, SE_REBDRM01);
            }

            work->field_120 = 1;
            work->field_124 = 0;
            work->field_34 = DG_ZeroVector;
        }
    }
    else
    {
        int field_124 = work->field_124;
        if (field_124 == 0)
        {
            DG_InvisiblePrim(work->field_84_pPrim);
        }
        if (field_124 >= 3)
        {
            GV_DestroyActor(&work->actor);
        }
        else
        {
            work->field_124 = field_124 + 1;
        }
    }
}

STATIC void claymore_Die(ClaymoreWork *work)
{
    DG_PRIM *prim;

    prim = work->field_84_pPrim;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

STATIC void claymore_loader_80073930(ClaymoreWork *work)
{
    SVECTOR vec;

    TARGET *pTarget = &work->field_3C_target;
    GM_SetTarget(&work->field_3C_target, 4, NO_SIDE, &stru_8009F660);
    vec.vx = work->field_34.vx / 32;
    vec.vy = work->field_34.vy / 32;
    vec.vz = work->field_34.vz / 32;
    GM_Target_8002DCCC(pTarget, 0, 2, 256, 0, &vec);
    pTarget->field_44 = 5;
}

STATIC const SVECTOR svector_80012EDC = {0, 0, 1500, 0};

STATIC int claymore_GetResources(ClaymoreWork *work, SVECTOR *new_field_24, SVECTOR *new_field_2C)
{
    DG_PRIM *prim;
    DG_TEX  *tex;
    SVECTOR  new_field_34 = svector_80012EDC;
    int      retval;

    work->field_10C = 0;
    work->field_20_map = GM_CurrentMap;
    work->field_24 = *new_field_24;
    work->field_2C = *new_field_2C;
    work->field_2C.vy += GV_RandS(0x200);
    work->field_2C.vx += GV_RandS(0x200);
    work->field_108 = claymore_loader_helper_800735A0(work, &work->field_24, &work->field_2C);

    DG_SetPos2(&work->field_24, &work->field_2C);
    DG_RotVector(&new_field_34, &work->field_34, 1);

    prim = DG_GetPrim(DG_PRIM_POLY_FT4, 2, 0, &work->field_88, NULL);
    work->field_84_pPrim = prim;

    retval = -1;

    if (prim)
    {
        prim->field_2E_k500 = 1000;

        tex = DG_GetTexture(GV_StrCode("bullet"));
        if (tex)
        {
            claymore_loader_helper_80073490(&prim->packs[0]->poly_ft4, tex);
            claymore_loader_helper_80073490(&prim->packs[1]->poly_ft4, tex);
            claymore_loader_helper2_800731F8(work);
            retval = 0;
        }
        else
        {
            return -1;
        }
    }
    return retval;
}

/*---------------------------------------------------------------------------*/

STATIC const SVECTOR stru_80012EEC = {200, 200, 200, 0};

void *NewClaymore(SVECTOR *noise_position, SVECTOR *new_field_2C, int pCnt, int param_4)
{
    int             i;
    ClaymoreWork   *work;
    ClaymoreWork   *dummy;
    SVECTOR         new_field_24;
    SVECTOR         vec2;
    int             current_map;

    work = NULL;
    dummy = NULL;

    new_field_24 = stru_80012EEC;

    vec2 = *noise_position;
    vec2.vx += GV_RandS(0x100);
    vec2.vy += GV_RandS(0x80);

    DG_SetPos2(&vec2, new_field_2C);
    DG_PutVector(&new_field_24, &new_field_24, 1);

    if (param_4 == 8)
    {
        GM_SeSet(noise_position, SE_EXPLOSION);
        GM_SetNoise(0xff, 0x20, noise_position);

        NewAnime_8005DF50(&new_field_24, new_field_2C);
    }

    // from MAP* to int, back to MAP*: (to get a match)
    current_map = (int)GM_GetMap(GM_CurrentMap);
    claymore_MAP_800bdf08 = (MAP *)current_map;

    for (i = 0; i < pCnt; i++)
    {
        work = GV_NewActor(EXEC_LEVEL, sizeof(ClaymoreWork));
        if (work != NULL)
        {
            GV_SetNamedActor(&work->actor, claymore_Act, claymore_Die, "claymore.c");
            current_map = GM_CurrentMap;
            GM_ClaymoreMap_800AB9DC = current_map;
            if (claymore_GetResources(work, &new_field_24, new_field_2C) < 0)
            {
                GV_DestroyActor(&work->actor);
                return NULL;
            }
            claymore_loader_80073930(work);
            work->field_120 = 0;
        }
        else
        {
            return (void *)dummy;
        }
    }

    return (void *)work;
}
