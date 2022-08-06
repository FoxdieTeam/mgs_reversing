#include "gglsight.h"
#include "Game/GM_Control.h"
#include "Menu/menuman.h"

// night vision goggles / thermal goggles first person

extern short word_8009F714[];

#pragma INCLUDE_ASM("asm/Equip/gglsight_act_helper_80077A24.s") // 584 bytes

extern const char aLd[];        // = "%ld\n"
extern char       aGglsightC[]; // = "gglsight.c"

extern GM_Control *gSnaControl_800AB9F4;

void gglsight_act_helper_80077C6C(Actor_gglsight *pActor)
{
    int r;  // $a0
    int g;  // $a1
    int b;  // $a2
    int vy; // $s0

    if (pActor->field_3C >= 6)
    {
        menu_Text_XY_Flags_80038B34(40, 56, 0x120);

        if (pActor->field_20_type == 5)
        {
            r = 255;
            g = 0;
            b = 0;
        }
        else
        {
            r = 65;
            g = 160;
            b = 74;
        }
        menu_Color_80038B4C(r, g, b);
        vy = gSnaControl_800AB9F4->field_8_vec.vy;
        menu_Text_80038C38(aLd, 8 * (vy & 2047));
        menu_Text_80038C38(aLd, 4 * (vy & 4095));
        menu_Text_80038C38(aLd, 16 * (vy & 1023));
    }
}

#pragma INCLUDE_ASM("asm/Equip/gglsight_act_helper_80077D24.s") // 588 bytes

extern const char aScan[];
extern const char aModeB[];
extern const char aModeA[];

void gglsight_act_helper_80077F70(Actor_gglsight *pActor)
{
    int old_380; // $s1
    int r;       // $a0
    int g;       // $a1
    int b;       // $a2

    if (pActor->field_3C >= 6)
    {
        old_380 = pActor->field_380;
        menu_Text_XY_Flags_80038B34(41, 42, 304);
        if (pActor->field_20_type == 5)
        {
            r = 255;
            g = 0;
            b = 0;
        }
        else
        {
            r = 65;
            g = 160;
            b = 74;
        }
        menu_Color_80038B4C(r, g, b);

        pActor->field_380++;
        if (pActor->field_380 >= 17)
        {
            pActor->field_380 = -16;
        }

        if (old_380 > 0)
        {
            menu_Text_80038C38(aScan); // scan
        }

        menu_Text_XY_Flags_80038B34(137, 42, 304);

        if (pActor->field_20_type == 5)
        {
            menu_Text_80038C38(aModeB); // MODE - B
        }
        else
        {
            menu_Text_80038C38(aModeA); // MODE - A
        }
    }
}

#pragma INCLUDE_ASM("asm/Equip/gglsight_act_helper_80078054.s") // 468 bytes
#pragma INCLUDE_ASM("asm/Equip/gglsight_act_80078228.s")        // 464 bytes

void gglsight_kill_800783F8(Actor *pActor)
{
    word_8009F714[0] = 0;
}

void gglsight_loader1_80078404(Actor_gglsight *pActor)
{
    int     i;
    TILE_1 *pIter = &pActor->field_40_tile1[0][0];
    for (i = 0; i < 48; i++)
    {
        *(int *)&pIter->r0 = pActor->field_28_rgb;
        setTile1(pIter);
        pIter->y0 = 144;
        pIter++;
    }
}

#pragma INCLUDE_ASM("asm/Equip/gglsight_loader2_80078444.s") // 220 bytes

Actor_gglsight *gglsight_init_80078520(int type)
{
    Actor_gglsight *actor;
    int             status, count;
    short          *arr;
    short          *arr2;

    actor = (Actor_gglsight *)GV_NewActor_800150E4(7, sizeof(Actor_gglsight));

    if (actor)
    {
        GV_SetNamedActor_8001514C(&actor->field_0_actor, gglsight_act_80078228, gglsight_kill_800783F8, aGglsightC);

        actor->field_20_type = type;

        if (type == 5)
        {
            actor->field_24 = 0x9c26;
            actor->field_28_rgb = 0xff;
        }
        else if (type == 6)
        {
            actor->field_24 = 0x5425;
            actor->field_28_rgb = 0x4aa041;
        }
        else
        {
            status = -1;
            goto cleanup;
        }

        gglsight_loader1_80078404(actor);
        gglsight_loader2_80078444(actor);

        count = 0;
        arr = (short *)actor;

        // The compiler is optimising this and causing a mismatch if we try to do this cleanly
        for (; count < 4; count++)
        {
            arr2 = &arr[22];
            arr2[0] = 0;
            arr2[1] = 0;
            arr += 2;
            arr2 = arr;
        }

        actor->field_380 = -0x10;
        actor->field_3C = 0;

        word_8009F714[0] = 0;

        status = 0;

    cleanup:
        if (status < 0)
        {
            GV_DestroyActor_800151C8(&actor->field_0_actor);
            return NULL;
        }
    }

    return actor;
}
