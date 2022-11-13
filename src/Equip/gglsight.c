#include "gglsight.h"
#include "Game/GM_Control.h"
#include "Game/game.h"
#include "Menu/menuman.h"
#include "Thing/sight.h"
#include "chara/snake/sna_init.h"
#include "psyq.h"

// night vision goggles / thermal goggles first person

extern int         GV_Clock_800AB920;
extern DG_CHNL     DG_Chanls_800B1800[3];
extern GM_Control *gSnaControl_800AB9F4;

extern const char a02d[]; // = "%02d"

void gglsight_act_helper_80077A24(Actor_gglsight *pActor)
{
    int r, g, b;
    TILE_1 *pTile;
    DG_CHNL *pChnl;
    unsigned char *pOt;

    short a1;
    short a2;
    short a3;
    short a4;

    short var_s0;
    short var_s1;
    short x;

    if (pActor->field_3C < 6)
    {
        return;
    }

    pTile = pActor->field_40_tile1[GV_Clock_800AB920];

    pChnl = &DG_Chanls_800B1800[1];
    pOt = pChnl[1].mOrderingTables[GV_Clock_800AB920];

    menu_Text_XY_Flags_80038B34(0, 0, 0x122);

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

    a1 = gSnaControl_800AB9F4->field_8_rotator.vy & 0xfff;
    a2 = a1 / 64;
    a3 = a1 % 64;
    a4 = ((a3 * 24) / 64) + 160;
    x = a4 - ((a4 / 24) * 24);
    var_s1 = a2 + (a4 / 24);

    while (x < 300)
    {
        if (x >= 20)
        {
            var_s0 = var_s1 - 64;

            if (var_s1 < 65)
            {
                if (var_s1 < 0)
                {
                    var_s0 = -var_s1;
                }
                else
                {
                    var_s0 = var_s1;

                    if (var_s1 > 32)
                    {
                        var_s0 = 64 - var_s1;
                    }
                }
            }

            menu_Text_XY_Flags_80038B34(x, 148, 0x122);
            menu_Text_80038C38(a02d, var_s0);

            pTile->x0 = x;
            addPrim(pOt, pTile);
            pTile++;
        }

        x += 24;
        var_s1--;
    }
}

extern const char aLd[];        // = "%ld\n"
extern const char aGglsightC[]; // = "gglsight.c"

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
        vy = gSnaControl_800AB9F4->field_8_rotator.vy;
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

extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern GV_PAD           GV_PadData_800B05C0[4];
extern int              dword_8009F604;
extern short            word_8009F714[];

void gglsight_act_80078228(Actor_gglsight *pActor)
{
    short *ptr = word_8009F714;
    int type = pActor->field_20_type;
    int f24 = pActor->field_24;
    unsigned short status;
    int f3c;

    if (GM_PlayerStatus_800ABA50 & PLAYER_STATUS_USING_CONTROLLER_PORT_2)
    {
        status = GV_PadData_800B05C0[1].status;
    }
    else
    {
        status = GV_PadData_800B05C0[0].status;
    }

    GM_CheckShukanReverse_8004FBF8(&status);

    ptr[0] = 1;

    if (type == 5 && dword_8009F604 != f24)
    {
        NewSight_80071CDC(0x8504, f24, ptr, 1, 0);
        NewSight_80071CDC(0x8505, f24, ptr, 1, &pActor->field_2C_8Array[2]);
        NewSight_80071CDC(0x8506, f24, ptr, 1, &pActor->field_2C_8Array[4]);
    }
    else if (dword_8009F604 != f24)
    {
        NewSight_80071CDC(0x84db, f24, ptr, 1, 0);
        NewSight_80071CDC(0x84dc, f24, ptr, 1, &pActor->field_2C_8Array[2]);
        NewSight_80071CDC(0x84dd, f24, ptr, 1, &pActor->field_2C_8Array[4]);
    }

    f3c = pActor->field_3C++;

    if (!(GM_PlayerStatus_800ABA50 & 8))
    {
        status &= 0xafff;
    }

    gglsight_act_helper_80078054(f3c, status, &pActor->field_2C_8Array[2], 3, 2, 20);
    gglsight_act_helper_80078054(f3c, status, &pActor->field_2C_8Array[4], 5, 1, 12);
    gglsight_act_helper_80077A24(pActor);
    gglsight_act_helper_80077F70(pActor);
    gglsight_act_helper_80077C6C(pActor);
    gglsight_act_helper_80077D24(pActor);
}


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

void gglsight_loader2_80078444(Actor_gglsight *actor)
{
    int pos, count;

    DR_TPAGE *tpage;
    LINE_F2  *line;
    POLY_F4  *poly;

    tpage = actor->field_370_dr_tpage;
    line = &actor->field_280_lineF2[0];
    poly = &actor->field_2E0_polyF4[0];
    pos = 40;

    for (count = 0; count < 6; count++) {
        if (count == 3) pos = 40;

        *(int *)&line->r0 = actor->field_28_rgb;

        setLineF2(line);
        setSemiTrans(line, 1);
        line->x0 = pos + 3;
        line->x1 = pos + 6;

        *(int *)&poly->r0 = actor->field_28_rgb;

        setPolyF4(poly);
        setSemiTrans(poly, 1);
        poly->x2 = pos;
        poly->x0 = pos;
        poly->x3 = pos + 3;
        poly->x1 = pos + 3;
        poly->y3 = 0x8c;
        poly->y2 = 0x8c;

        line++;
        poly++;

        pos += 12;
    }

    SetDrawTPage_800924A8(&tpage[0], 0, 1, 32);
    SetDrawTPage_800924A8(&tpage[1], 0, 1, 32);
}

Actor_gglsight *gglsight_init_80078520(int type)
{
    Actor_gglsight *actor;
    int             status, count;
    short          *arr;
    short          *arr2;

    actor = (Actor_gglsight *)GV_NewActor_800150E4(7, sizeof(Actor_gglsight));

    if (actor)
    {
        GV_SetNamedActor_8001514C(&actor->field_0_actor, (TActorFunction)gglsight_act_80078228,
                                  (TActorFunction)gglsight_kill_800783F8, aGglsightC);

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
