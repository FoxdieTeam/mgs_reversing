#include "gglsight.h"
#include "Game/GM_Control.h"

extern short word_8009F714[];

#pragma INCLUDE_ASM("asm/Equip/gglsight_act_helper_80077A24.s") // 584 bytes

void menu_Text_XY_Flags_80038B34(int x, int y, int flags);
void menu_Color_80038B4C(int r, int g, int b);
void menu_Text_80038C38(const char *pStr, ...);

extern const char aLd[];

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

void gglsight_kill_800783F8(void)
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
#pragma INCLUDE_ASM("asm/Equip/gglsight_init_80078520.s")    // 256 bytes
