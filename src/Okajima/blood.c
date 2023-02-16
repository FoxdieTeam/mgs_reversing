#include "blood.h"
#include "psyq.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Anime/animeconv/anime.h"

extern ANIMATION stru_8009F614;

extern const char aBloodC[]; // = "blood.c"

#pragma INCLUDE_ASM("asm/Okajima/blood_loader2_helper2_80072080.s") // 788 bytes
#pragma INCLUDE_ASM("asm/Okajima/blood_act_helper_80072394.s")      // 228 bytes
#pragma INCLUDE_ASM("asm/Okajima/blood_loader2_helper_80072478.s")  // 148 bytes
#pragma INCLUDE_ASM("asm/Okajima/blood_act_helper_8007250C.s")      // 44 bytes
#pragma INCLUDE_ASM("asm/Okajima/blood_act_80072538.s")             // 148 bytes

void blood_kill_800725CC(Actor_Blood *pActor)
{
    DG_OBJS *prim;

    prim = pActor->field_24_prim;
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

#pragma INCLUDE_ASM("asm/Okajima/blood_loader2_80072608.s") // 288 bytes

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
