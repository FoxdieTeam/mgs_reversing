#include "claymore.h"
#include "spark.h"
#include "psyq.h"
#include "Game/game.h"

extern SVECTOR stru_8009F630[4];

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

#pragma INCLUDE_ASM("asm/Okajima/claymore_act_helper_80073364.s")     // 300 bytes
void claymore_act_helper_80073364(Actor_Claymore *claymore);

#pragma INCLUDE_ASM("asm/Okajima/claymore_loader_helper_80073490.s")  // 272 bytes
void claymore_loader_helper_80073490(union Prim_Union *prim, DG_TEX *tex);

#pragma INCLUDE_ASM("asm/Okajima/claymore_loader_helper_800735A0.s")  // 272 bytes
int  claymore_loader_helper_800735A0(Actor_Claymore *claymore, SVECTOR *v1, SVECTOR *v2);

extern int     GM_CurrentMap_800AB9B0;
extern int     GM_GameOverTimer_800AB3D4;
extern SVECTOR DG_ZeroVector_800AB39C;

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
                ReadRotMatrix_80092DD8(&matrix);
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
    DG_OBJS *objs;

    objs = (DG_OBJS *)claymore->field_84_pPrim;
    if (objs)
    {
        DG_DequeuePrim_800182E0(objs);
        DG_FreePrim_8001BC04(objs);
    }
}

extern SVECTOR stru_8009F660;

void claymore_loader_80073930(Actor_Claymore *pActor)
{
    SVECTOR vec;

    GM_Target *pTarget = &pActor->field_3C_target;
    GM_SetTarget_8002DC74(&pActor->field_3C_target, 4, 0, &stru_8009F660);
    vec.vx = pActor->field_34.vx / 32;
    vec.vy = pActor->field_34.vy / 32;
    vec.vz = pActor->field_34.vz / 32;
    GM_Target_8002DCCC(pTarget, 0, 2, 256, 0, &vec);
    pTarget->field_44 = 5;
}

extern SVECTOR    svector_80012EDC;
extern const char aBullet_0[]; // "bullet"

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
            claymore_loader_helper_80073490(prim->field_40_pBuffers[0], tex);
            claymore_loader_helper_80073490(prim->field_40_pBuffers[1], tex);
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

#pragma INCLUDE_ASM("asm/Okajima/NewClaymore_80073B8C.s")     // 548 bytes
