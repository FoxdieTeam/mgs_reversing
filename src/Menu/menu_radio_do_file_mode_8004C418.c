#include "Menu/radio.h"
#include "Game/linkvarbuf.h"
#include "Game/game.h"

extern void *dword_800ABB50;
void        *dword_800ABB50;

extern int dword_800ABB5C;
int        dword_800ABB5C;

extern int dword_800AB700;
int        dword_800AB700;

extern int dword_800ABB54;
int        dword_800ABB54;

extern int dword_800ABB58;
int        dword_800ABB58;

extern int dword_800AB6FC;
int        dword_800AB6FC;

extern int dword_800AB6F4;
int        dword_800AB6F4;

extern Stru_800ABB74 *dword_800ABB70;
Stru_800ABB74        *dword_800ABB70;

extern Stru_800ABB74 *dword_800ABB74;
Stru_800ABB74        *dword_800ABB74;

extern Stru_800ABB74 *dword_800ABB78;
Stru_800ABB74        *dword_800ABB78;

extern Stru_800ABB74 *dword_800ABB88;
Stru_800ABB74        *dword_800ABB88;

extern int dword_800ABB84;
int        dword_800ABB84;

extern int dword_800ABB80;
int        dword_800ABB80;

extern menu_save_mode_data *dword_800ABB4C;
menu_save_mode_data        *dword_800ABB4C;

extern int dword_800ABB48;
int        dword_800ABB48;


extern char       aEndSaveMode[];
extern char       aEndStateD[];
extern char       aLoadData[];
extern char       aLoading[];
extern char       aNoFile_0[];
extern char       aNoSpace[];
extern char       aPressToExit[];
extern char       aPressToSelectM[];
extern char       aResD[];
extern char       aSaving[];
extern char       aSelectMemoryCa[];
extern char       aNull[];
extern mem_card  *mcd_last_file_800ABB68[];
extern const int  dword_800120B4[];
extern const int  dword_800120CC[];
extern const int  dword_800120E4[];

char aBislpm99999[] = "BISLPM-99999        ";

int dword_8009EB4C[] = {
    0x800AB6F8, 0x8001203C, 0x80012020, 0x80012008, 0x80011FEC, 0x80011FC4,
    0x80011FB0, 0x80011F90, 0x80011F6C, 0x80011F5C, 0x80011F34, 0x80011F18
};

char *dword_8009EB7C[] = {
    (char *)0x800AB6F8, (char *)dword_800120B4, (char *)0x80012098, (char *)0x80012008, (char *)0x80012078, (char *)0x80011FC4,
    (char *)0x80012064, (char *)0x80011F90,     (char *)0x80011F6C, (char *)0x80012054, (char *)0x80011F34, (char *)0x80011F18
};

extern const char aOverwriteOk[];
extern const char aFormatOk[];

char *dword_8009EBAC[] = {(char *)dword_800120E4, (char *)dword_800120CC};
const char *dword_8009EBB4[] = {aOverwriteOk, aFormatOk};

extern const char aError[];
extern const char aComplete[];

const char *dword_8009EBBC[] = {
    NULL,
    NULL,
    aComplete,
    NULL,
    aError
};

extern const char aEz[];
extern const char aNm[];
extern const char aHd[];
extern const char aEx[];

Menu_Triangle triangle_8009EBD0 = {155, 79, 160, 74, 165, 79, 0x80808080};
Menu_Triangle triangle_8009EBE0 = {156, 184, 160, 188, 164, 184, 0x80808080};

const char *difficulty_str_8009EBF0[] = {aEz, aNm, aHd, aEx};

extern const char aMemoryCard1[];
extern const char aMemoryCard2[];

const char *gMemoryCardNames_8009EC00[] = {aMemoryCard1, aMemoryCard2};

extern const char aYes[];
extern const char aNo[];

const char *off_8009EC08[] = {aYes, aNo};

int menu_radio_do_file_mode_8004C418(Actor_MenuMan *pActor, GV_PAD *pPad)
{
    TextConfig     textConfig1, textConfig2;
    int            res1, res2, res3;
    char         **strArr;
    Stru_800ABB74 *pStru;
    int            xpos;
    int            divisor;
    int            var_v0_2; // ypos?
    unsigned int   flags;
    DR_TPAGE      *tpage;
    unsigned char *mOt;
    int            flagsExtracted;

    mOt = pActor->field_20_otBuf->mPrimBuf.mOt;
    if (dword_800ABB48 == 0)
    {
        strArr = (char **)dword_8009EB4C;
        dword_8009EBBC[0] = dword_800ABB4C->field_4_name;
        dword_8009EBBC[1] = aSaving;
        dword_8009EBBC[3] = aNoSpace;
    }
    else
    {
        strArr = (char **)dword_8009EB7C;
        dword_8009EBBC[0] = aLoadData;
        dword_8009EBBC[1] = aLoading;
        dword_8009EBBC[3] = aNoFile_0;
    }
    switch (dword_800ABB80)
    {
    case 0:
        sub_80048124();
        dword_800ABB84 = 0;
        font_set_color_80044DC4(pActor->field_214_font, 1, 0x19F2, 0);
        font_clut_update_80046980(pActor->field_214_font);
        dword_800ABB80 = 1;
        dword_800ABB88 = NULL;
        dword_800ABB78 = NULL;
        dword_800ABB74 = NULL;
        dword_800ABB70 = NULL;
        menu_radio_do_file_mode_helper2_8004A87C(0, 160, 100, 0, 0);
        sub_8004ABF0(160, 0x67, 0x60, 0xC, 0);
        GM_SeSet2_80032968(0, 0x3F, 0x20);
        dword_800AB6F4 = 0;
        dword_800AB6FC = -1;
        break;
    case 1:
        menu_radio_do_file_mode_helper2_8004A87C(3, 160, 0x80, 0, -1);
        flags = dword_800ABB58;
        if (flags == 0)
        {
            break;
        }
        if (flags == 0xC1000001)
        {
            if (dword_800ABB48 == 0)
            {
                strcpy(dword_800ABB70->field_24[dword_800ABB70->field_4].field_0_name, aBislpm99999 + 0xc);
                dword_800ABB70->field_24[dword_800ABB70->field_4].field_20 = 0;
                sub_8004AEA8(dword_800ABB70);
            }
            menu_radio_do_file_mode_helper2_8004A87C(2, 160, 0x80, 0, 2);
        }
        if (flags == 0x1000009)
        {
            menu_radio_do_file_mode_helper2_8004A87C(2, 160, 0x80, 0, 1);
            menu_radio_do_file_mode_helper4_8004AA68(8, 160, 0x6E, 160, 0x7A, 0);
            sub_8004ABF0(160, 0x83, 0x60, 0xC, 4);
        }
        if (flags & 0x04000000)
        {
            menu_radio_do_file_mode_helper2_8004A87C(2, 160, 0x80, 0, 4);
            sub_8004ABF0(160, 0x83, 0x60, 0xC, 4);
        }
        if (flags & 0x01000000)
        {
            menu_radio_do_file_mode_helper7_8004AE3C(pActor, strArr[(unsigned char)dword_800ABB58]);
            dword_800ABB84 = 0xF;
        }
        if (flags & 0x40000000)
        {
            dword_800ABB80 = 2;
            dword_800ABB84 = 1;
        }
        else if (flags & 0x20000000)
        {
            dword_800ABB84 = 0;
            switch ((unsigned char)dword_800ABB58)
            {
            case 0:
                dword_800ABB80 = 4;
                menu_radio_do_file_mode_helper11_8004B958(&dword_800ABB70, 0x11);
                dword_800ABB88 = dword_800ABB70;
                if (menu_radio_do_file_mode_helper12_8004BA80(pActor, mcd_last_file_800ABB68[dword_800AB6FC], aNull, dword_800ABB70) == 0)
                {
                    menu_radio_do_file_mode_helper7_8004AE3C(pActor, strArr[4]);
                    dword_800ABB84 = 1;
                    menu_radio_do_file_mode_helper2_8004A87C(3, 160, 0x80, 0, 3);
                    sub_8004ABF0(160, 0x83, 0x60, 0xC, 4);
                    dword_800ABB54 = 3;
                }
                if (dword_800ABB74 == NULL)
                {
                    menu_radio_do_file_mode_helper11_8004B958(&dword_800ABB74, 3);
                    menu_radio_do_file_mode_helper14_8004BE98(pActor, aSelectMemoryCa, dword_800ABB74);
                    divisor = -4;
                    dword_800ABB74->field_14 = 0;
                }
                else
                {
                    divisor = 4;
                }
                menu_radio_do_file_mode_helper2_8004A87C(0, 0x40, 0x18, 4, 0);
                menu_radio_do_file_mode_helper3_8004A994(4, 160, 0x28, divisor, dword_800ABB74);
                menu_radio_do_file_mode_helper4_8004AA68(5, 0x6C, 0x1A, 160, 0x1A, divisor);
                menu_radio_do_file_mode_helper4_8004AA68(6, 160, 0x1A, 160, 0x24, divisor);
                pStru = dword_800ABB74;
                if (dword_800ABB74->field_8 == 1)
                {
                    xpos = pStru->field_0_xpos;
                }
                else
                {
                    xpos = pStru->field_0_xpos - pStru->field_10 / 2;
                    if (pStru->field_4 == 1)
                    {
                        xpos += pStru->field_10;
                    }
                }

                if (dword_800ABB88->field_8 == 0)
                {
                    xpos = pStru->field_0_xpos;
                    var_v0_2 = 0x7A;
                }
                else
                {
                    var_v0_2 = 0x40;
                }
                menu_radio_do_file_mode_helper4_8004AA68(7, xpos, 0x3C, xpos, var_v0_2, -4);
                menu_radio_do_file_mode_helper5_8004ABDC(8);
                break;
            case 1:
                if (dword_800ABB74 != NULL)
                {
                    divisor = 4;
                }
                else
                {
                    divisor = -4;
                }
                if (dword_800ABB70 != NULL)
                {
                    menu_radio_do_file_mode_helper10_8004B91C(dword_800ABB70);
                    dword_800ABB70 = NULL;
                }
                menu_radio_do_file_mode_helper11_8004B958(&dword_800ABB74, 3);
                dword_800ABB88 = dword_800ABB74;
                menu_radio_do_file_mode_helper14_8004BE98(pActor, aSelectMemoryCa, dword_800ABB74);
                dword_800ABB80 = 3;
                menu_radio_do_file_mode_helper2_8004A87C(0, 160, 0x18, 4, 0);
                menu_radio_do_file_mode_helper3_8004A994(4, 160, 100, divisor, dword_800ABB74);
                menu_radio_do_file_mode_helper4_8004AA68(5, 160, 0x1A, 160, 0x1A, divisor);
                menu_radio_do_file_mode_helper4_8004AA68(6, 160, 0x20, 160, 0x60, divisor);
                menu_radio_do_file_mode_helper5_8004ABDC(7);
                menu_radio_do_file_mode_helper5_8004ABDC(8);
                break;
            }
        }
        else if (flags & 0x10000000)
        {
            flagsExtracted = ((flags >> 0x14) ^ 1);
            flagsExtracted &= 1;
            dword_800ABB80 = 5;
            menu_radio_do_file_mode_helper11_8004B958(&dword_800ABB78, 2);
            dword_800ABB88 = dword_800ABB78;
            menu_radio_do_file_mode_helper15_8004C04C(pActor, off_8009EC08, 2, flagsExtracted,
                                                      dword_8009EBB4[(unsigned char)dword_800ABB58], dword_800ABB78);
            menu_radio_do_file_mode_helper7_8004AE3C(pActor, dword_8009EBAC[(unsigned char)dword_800ABB58]);
            dword_800ABB84 = 1;
        }
        else if ((int)flags < 0)
        {
            dword_800ABB80 = 6;
            dword_800ABB58 = 0;
            mts_wup_tsk_8008A540(7);
        }
        else
        {
            dword_800ABB80 = 1;
            dword_800ABB58 = 0;
            mts_wup_tsk_8008A540(7);
        }
        break;
    case 2:
        if (pPad->press & 0xF0)
        {
            dword_800ABB84 = 0;
            if (dword_800ABB58 < 0)
            {
                dword_800ABB80 = 6;
                dword_800ABB58 = 0;
            }
            else
            {
                dword_800ABB80 = 1;
                dword_800ABB58 = 0;
            }
            mts_wup_tsk_8008A540(7);
            menu_radio_do_file_mode_helper2_8004A87C(3, 160, 0x80, 0, -1);
            menu_radio_do_file_mode_helper2_8004A87C(2, 160, 0x80, 0, -1);
        }
        else
        {
            draw_radio_wait_mark_8004143C(pActor, mOt);
        }
        break;
    case 3:
        if (dword_800AB700 & 0x80)
        {
            menu_radio_do_file_mode_helper14_8004BE98(pActor, aSelectMemoryCa, dword_800ABB74);
            dword_800AB700 &= ~0x80;
        }
        textConfig1.xpos = 160;
        textConfig1.ypos = 0xC8;
        textConfig1.flags = 0x12;
        textConfig1.colour = 0x66748956;
        menu_number_draw_string2_80043220(pActor->field_20_otBuf, &textConfig1, aPressToExit);
        if (menu_radio_do_file_mode_helper17_8004C2E4(pPad, &res1, dword_800ABB74) != 0)
        {
            printf(aResD, res1);
            dword_800ABB58 = 0;
            dword_800ABB80 = 1;
            dword_800ABB84 = 0;
            dword_800ABB74->field_14 = 0;
            dword_800ABB5C = res1;
        }
        break;
    case 5:
        if (menu_radio_do_file_mode_helper17_8004C2E4(pPad, &res2, dword_800ABB78) != 0)
        {
            printf(aResD, res2);
            dword_800ABB78->field_14 = 0;
            if (res2 == -1)
            {
                menu_radio_do_file_mode_helper5_8004ABDC(8);
            }
            dword_800ABB58 = 0;
            dword_800ABB5C = res2;
            mts_wup_tsk_8008A540(7);
            dword_800ABB80 = 1;
            dword_800ABB84 = 0;
        }
        else
        {
            menu_radio_do_file_mode_helper16_8004C164(pActor->field_20_otBuf, dword_800ABB88);
            if (dword_800ABB70 != NULL)
            {
                menu_radio_do_file_mode_helper4_8004AA68(8, 160, 0x6E, 160, 0x7A, 0);
            }
        }
        break;
    case 4:
        if (dword_800ABB70->field_8 != 0)
        {
            textConfig2.xpos = 160;
            textConfig2.ypos = 0xC8;
            textConfig2.flags = 0x12;
            textConfig2.colour = 0x66748956;
            menu_number_draw_string2_80043220(pActor->field_20_otBuf, &textConfig2, aPressToSelectM);
        }
        if (menu_radio_do_file_mode_helper13_8004BCF8(pPad, &res3, dword_800ABB70) != 0)
        {
            printf(aResD, res3);
            dword_800ABB70->field_14 = 0;
            if (res3 == -1)
            {
                menu_radio_do_file_mode_helper10_8004B91C(dword_800ABB70);
                dword_800ABB70 = NULL;
            }
            else
            {
                dword_800ABB70->field_18 = 4;
            }
            dword_800ABB5C = res3;
            if (dword_800ABB80 == 4)
            {
                dword_800ABB58 = 0;
                mts_wup_tsk_8008A540(7);
            }
            dword_800ABB80 = 1;
            dword_800ABB84 = 0;
        }
        break;
    case 6:
        if (mts_get_task_status_8008B618(7) == 0)
        {
            printf(aEndSaveMode);
            menu_radio_do_file_mode_helper10_8004B91C(dword_800ABB70);
            menu_radio_do_file_mode_helper10_8004B91C(dword_800ABB74);
            menu_radio_do_file_mode_helper10_8004B91C(dword_800ABB78);
            menu_radio_do_file_mode_helper_8004A858();
            GV_FreeMemory_80015FD0(0, dword_800ABB50);
            GM_LastResultFlag = dword_800ABB54;
            printf(aEndStateD, GM_LastResultFlag);
            if (dword_800ABB48 != 2)
            {
                font_set_color_80044DC4(pActor->field_214_font, 1, 0x3BEF, 0);
                return 1;
            }

            return 2;
        }
        break;
    }

    if (dword_800ABB84 >= 2)
    {
        dword_800ABB84--;
    }
    else if (dword_800ABB84 > 0)
    {
        menu_radio_do_file_mode_helper8_8004AFE4(pActor, mOt, dword_800ABB88);
    }
    NEW_PRIM(tpage, pActor);
    setDrawTPage(tpage, 0, 1, getTPage(0, 1, 960, 256));
    addPrim(mOt, tpage);
    if (dword_800ABB70 != NULL)
    {
        menu_radio_do_file_mode_save_memcard_8004B0A0(pActor, mOt, dword_800ABB70);
    }
    menu_radio_do_file_mode_helper6_8004AD40(pActor->field_20_otBuf);
    return 0;
}
