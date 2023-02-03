#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "Bullet/blast.h"
#include "Game/game.h"
#include "chafgrnd.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "unknown.h"

extern int   GM_GameStatus_800AB3CC;

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

#pragma INCLUDE_ASM("asm/Okajima/chafgrnd_act_helper_80076A6C.s") // 44 bytes
#pragma INCLUDE_ASM("asm/Okajima/chafgrnd_act_helper_80076A98.s") // 144 bytes
#pragma INCLUDE_ASM("asm/Okajima/chafgrnd_act_80076B28.s")        // 1260 bytes

#pragma INCLUDE_ASM("asm/Okajima/chafgrnd_loader_80077014.s")     // 520 bytes

void chafgrnd_kill_8007721C(Actor_Chafgrnd *pActor)
{
    DG_OBJS *pObjs = pActor->field_a34;

    GM_GameStatus_800AB3CC &= ~1;

    if (pObjs)
    {
        DG_DequeuePrim_800182E0(pObjs);
        DG_FreePrim_8001BC04(pObjs);
    }
}

extern int GM_GameStatus_800AB3CC;
extern int GM_CurrentMap_800AB9B0;

extern int dword_800BDF98;
extern int dword_800BDFA0;

extern const char aChafgrndC[]; // = "chafgrnd.c";

Actor_Chafgrnd * NewChaffGrd_80077264(MATRIX *pWorld)
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
