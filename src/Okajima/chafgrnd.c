#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "Bullet/blast.h"
#include "Game/game.h"
#include "chafgrnd.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "unknown.h"

extern int     dword_800BDF98;
extern int     dword_800BDF9C;
extern int     dword_800BDFA0;

extern int     GM_GameStatus_800AB3CC;
extern int     GM_CurrentMap_800AB9B0;

extern MATRIX  DG_ZeroMatrix_8009D430;
extern SVECTOR DG_ZeroVector_800AB39C;

extern const char aChafgrndC[]; // = "chafgrnd.c";

void chafgrnd_init_tiles_800769EC(TILE *a1)
{
    TILE        *pIter = a1;
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

void chafgrnd_act_helper_80076A6C(TILE * a0)
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

void chafgrnd_act_helper_80076A98(SVECTOR *va, SVECTOR *vb, SVECTOR *vout)
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

#pragma INCLUDE_ASM("asm/Okajima/chafgrnd_act_80076B28.s")        // 1260 bytes

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

    chafgrnd_init_tiles_800769EC(&pPrim->field_40_pBuffers[0]->tiles);
    chafgrnd_init_tiles_800769EC(&pPrim->field_40_pBuffers[1]->tiles);

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
        DG_DequeuePrim_800182E0((DG_OBJS *)pPrim);
        DG_FreePrim_8001BC04((DG_OBJS *)pPrim);
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
                                  (TActorFunction)&chafgrnd_kill_8007721C, aChafgrndC);

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
