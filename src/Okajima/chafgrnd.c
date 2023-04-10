#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "Bullet/blast.h"
#include "Game/camera.h"
#include "Game/game.h"
#include "chafgrnd.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "unknown.h"

extern int              dword_800ABA0C;

extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;

extern int              dword_800BDF98;
extern int              dword_800BDF9C;
extern int              dword_800BDFA0;

extern int              GM_GameStatus_800AB3CC;
extern int              GM_CurrentMap_800AB9B0;

extern int              GV_Clock_800AB920;
extern int              GV_Time_800AB330;

extern MATRIX           DG_ZeroMatrix_8009D430;
extern SVECTOR          DG_ZeroVector_800AB39C;

void chafgrnd_init_particle_size_800769EC(TILE *a0)
{
    TILE        *pIter = a0;
    int          i;
    unsigned int rand_width, rand_height;

    for (i = 64; i > 0; i--)
    {
        setTile(pIter);
        rand_width = GV_RandU_80017090(2) + 1;
        rand_height = GV_RandU_80017090(2) + 1;
        setWH(pIter, rand_width, rand_height);
        pIter++;
    }
}

void chafgrnd_init_particle_color_80076A6C(TILE * a0)
{
    int i;

    for (i = 0x40; i > 0; i--)
    {
        a0->r0 = -1;
        a0->g0 = -1;
        a0->b0 = 0;
        a0++;
    }
}

void chafgrnd_calc_particle_position_80076A98(SVECTOR *va, SVECTOR *vb, SVECTOR *vout)
{
    SVECTOR vec;
    int temp_s0;
    short temp_v0;
    int temp_v1;

    GV_SubVec3_80016D40(vb, va, &vec);
    vout->vy = ratan2_80094308(vec.vx, vec.vz) & 0xfff;

    temp_s0 = vec.vy;
    vec.vy = 0;

    temp_v1 = ratan2_80094308(GV_VecLen3_80016D80(&vec), temp_s0) & 0xfff;

    temp_v0 = temp_v1 - 0x400;
    vout->vx = temp_v0;

    if (temp_v0 < 0)
    {
        vout->vx = temp_v1 + 0xc00;
    }

    vout->vz = 0;
}

void chafgrnd_act_80076B28(Actor_Chafgrnd* pActor)
{
    SVECTOR unused;
    SVECTOR sp18;

    int sp20;
    int i;
    int ang;
    int temp_v0_2;

    SVECTOR *var_s4;
    SVECTOR *var_s5;
    SVECTOR *var_s7;

    SVECTOR *pVec;
    SVECTOR *pVec2;

    if (GM_CheckMessage_8002631C(&pActor->field_0_actor, GV_StrCode_80016CCC("effect"), 0x3223))
    {
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
        return;
    }

    if (GM_GameStatus_800AB3CC < 0)
    {
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
    }

    GM_GameStatus_800AB3CC |= 1;
    GM_SetCurrentMap(dword_800ABA0C);

    pActor->field_a34->group_id = dword_800ABA0C;

    if (dword_800BDF98 == 1)
    {
        dword_800BDF98 = 0;

        pActor->field_a38 = 64;

        for (i = 0; i < 64; i++)
        {
            pActor->field_a40[i] = 0;
        }
    }

    if (--dword_800BDFA0 < 0)
    {
        GM_GameStatus_800AB3CC &= ~0x1;
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
        return;
    }

    if ((mts_get_tick_count_8008BBB0() - dword_800BDF9C) > 48)
    {
        dword_800BDF9C = mts_get_tick_count_8008BBB0();
        GM_SeSet2_80032968(0, 63, 58);
    }

    var_s7 = pActor->field_834;

    if (pActor->field_a3c == 1)
    {
        return;
    }

    unused.vz = 0;

    temp_v0_2 = dword_800BDFA0 % 2;
    var_s5 = pActor->field_34[temp_v0_2];
    var_s4 = pActor->field_434[temp_v0_2];

    DG_PointCheck_8001BF34(var_s4, 64);

    sp20 = 0;

    if ((dword_800BDFA0 < pActor->field_28) || (pActor->field_24 == 1))
    {
        pActor->field_24 = 1;

        chafgrnd_calc_particle_position_80076A98(&gUnkCameraStruct2_800B7868.field_0, &gUnkCameraStruct2_800B7868.field_8, &sp18);

        pVec = (SVECTOR *)getScratchAddr(0);
        pVec->vx = 0;
        pVec->vy = 0;
        pVec->vz = 2000;

        DG_SetPos2_8001BC8C(&gUnkCameraStruct2_800B7868.field_0, &sp18);
        DG_PutVector_8001BE48(pVec, pVec, 1);

        sp20 = 1;
        pActor->field_a34->root = &pActor->field_a80;
    }

    if (dword_800BDFA0 == pActor->field_a38)
    {
        pActor->field_a38 = dword_800BDFA0 - 1;
        pActor->field_a40[dword_800BDFA0 - 1] = 1;
    }

    for (i = 0; i < 64; i++, var_s5++, var_s4++, var_s7++)
    {
        if (pActor->field_a40[i])
        {
            *var_s7 = gUnkCameraStruct2_800B7868.field_0;
            continue;
        }

        if (sp20)
        {
            if ((var_s4->pad != 1) || (GV_RandU_80017090(64) == 0))
            {
                pVec2 = (SVECTOR *)getScratchAddr(0);
                var_s4->vx = pVec2->vx + GV_RandS_800170BC(4096);
                var_s4->vy = pVec2->vy + GV_RandS_800170BC(4096);
                var_s4->vz = pVec2->vz + GV_RandS_800170BC(4096);
            }

            ang = GV_Time_800AB330 + (i * 16);

            if (i > 32)
            {
                var_s4->vx -= rsin_80092508(ang * 64) / 128;
                var_s4->vy -= 15;
                var_s4->vz -= rcos_800925D8(ang * 64) / 128;
            }
            else
            {
                var_s4->vx += rsin_80092508(ang * 64) / 128;
                var_s4->vy -= 15;
                var_s4->vz -= rcos_800925D8(ang * 64) / 128;
            }
        }
        else
        {
            var_s5->vx = (var_s5->vx * 7) >> 3;
            var_s5->vy -= 5;
            var_s5->vz = (var_s5->vz * 7) >> 3;

            var_s4->vx += var_s5->vx;
            var_s4->vy += var_s5->vy;
            var_s4->vz += var_s5->vz;
        }

        *var_s7 = *var_s4;
    }

    chafgrnd_init_particle_color_80076A6C(&pActor->field_a34->field_40_pBuffers[GV_Clock_800AB920]->tiles);
}

int chafgrnd_loader_80077014(Actor_Chafgrnd *pActor, MATRIX *pWorld)
{
    SVECTOR vec1;
    SVECTOR vec2;
    DG_PRIM *pPrim;
    int i;
    int j;

    dword_800BDFA0 = 300;
    dword_800BDF9C = mts_get_tick_count_8008BBB0();

    pActor->field_a38 = 64;
    pActor->field_24 = 0;
    pActor->field_28 = dword_800BDFA0 - 60;

    pActor->field_20_map = GM_CurrentMap_800AB9B0;

    pActor->field_2c.vx = pWorld->t[0];
    pActor->field_2c.vy = pWorld->t[1];
    pActor->field_2c.vz = pWorld->t[2];

    pActor->field_20_map = GM_CurrentMap_800AB9B0;

    vec1.vx = 0;
    vec1.vy = 0;
    vec2.vz = 0;

    pPrim = DG_GetPrim(1033, 64, 0, pActor->field_834, NULL);
    pActor->field_a34 = pPrim;

    if (!pPrim)
    {
        return -1;
    }

    chafgrnd_init_particle_size_800769EC(&pPrim->field_40_pBuffers[0]->tiles);
    chafgrnd_init_particle_size_800769EC(&pPrim->field_40_pBuffers[1]->tiles);

    pActor->field_a80 = DG_ZeroMatrix_8009D430;

    for (i = 0; i < 64; i++)
    {
        for (j = 0; j < 2; j++)
        {
            vec1.vz = GV_RandU_80017090(1024) + 100;
            vec2.vx = -GV_RandU_80017090(512) - 256;
            vec2.vy = GV_RandU_80017090(4096);

            DG_SetPos2_8001BC8C(&DG_ZeroVector_800AB39C, &vec2);
            DG_PutVector_8001BE48(&vec1, &pActor->field_34[j][i], 1);

            pActor->field_434[j][i] = pActor->field_2c;
        }

        pActor->field_a40[i] = 0;
    }

    return 0;
}

void chafgrnd_kill_8007721C(Actor_Chafgrnd *pActor)
{
    DG_PRIM *pPrim = pActor->field_a34;

    GM_GameStatus_800AB3CC &= ~1;

    if (pPrim)
    {
        DG_DequeuePrim_800182E0(pPrim);
        DG_FreePrim_8001BC04(pPrim);
    }
}

Actor_Chafgrnd * NewChafgrnd_80077264(MATRIX *pWorld)
{
    SVECTOR vec;
    Actor_Chafgrnd *pActor;

    vec.vx = pWorld->t[0];
    vec.vy = pWorld->t[1];
    vec.vz = pWorld->t[2];

    GM_SetCurrentMap(GM_CurrentMap_800AB9B0);
    AN_Blast_Minimini_8006E32C(&vec);

    if (GM_GameStatus_800AB3CC & 1)
    {
        dword_800BDFA0 = 300;
        dword_800BDF98 = 1;
        GM_Sound_800329C4(&vec, 66, 1);
        GM_SetNoise(100, 32, &vec);
        return NULL;
    }

    pActor = (Actor_Chafgrnd *)GV_NewActor_800150E4(5, sizeof(Actor_Chafgrnd));

    if (pActor)
    {
        dword_800BDF98 = 0;
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)&chafgrnd_act_80076B28,
                                  (TActorFunction)&chafgrnd_kill_8007721C, "chafgrnd.c");

        pActor->field_a3c = 0;
        if (chafgrnd_loader_80077014(pActor, pWorld) < 0)
        {
            pActor->field_a3c = 1;
        }

        GM_Sound_800329C4(&pActor->field_2c, 66, 1);
        GM_SetNoise(100, 32, &pActor->field_2c);
    }

    return pActor;
}
