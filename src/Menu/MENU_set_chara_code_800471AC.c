#include "linker.h"
#include "mts_new.h"
#include "menuMan.h"

extern const char aSetCharaCodeD[];
extern const char aAnimeCharaDCod[];

void sub_800470B4(int param_1, void *param_2, int param_3, int param_4, int param_5, int param_6);

void MENU_set_chara_code_800471AC(menu_chara_struct *unknown, unsigned char *pScript)
{
    int charaCode;
    int w2;
    int w3;
    unsigned char *pScriptIter;
    int bVar1;

    pScriptIter = menu_gcl_read_word_80047098(&charaCode, pScript);
    pScriptIter = menu_gcl_read_word_80047098(&w2, pScriptIter);
    pScriptIter = menu_gcl_read_word_80047098(&w3, pScriptIter);

    bVar1 = charaCode == 0x21ca; // probably a hashed name ?

    unknown->field_C_pScript = pScriptIter;

    mts_printf_8008BBA0(aSetCharaCodeD, charaCode);

    if (w3 >= 1)
    {
        sub_800470B4(bVar1, unknown, charaCode, w2, w3, 1);
        mts_8008A400();
    }
    else
    {
        sub_800470B4(bVar1, unknown, charaCode, w2, w3, 0);
    }

    unknown->field_0_bUsed = 1;

    mts_8008A400();
}

void menu_gcl_anime_chara_code_80047280(menu_chara_struct *unknown, unsigned char *pScript)
{
    int anime_chara;
    int code;
    int w3;
    int w3_cond;

    pScript = menu_gcl_read_word_80047098(&anime_chara, pScript);
    pScript = menu_gcl_read_word_80047098(&code, pScript);
    pScript = menu_gcl_read_word_80047098(&w3, pScript);
    if (w3 < 0x101)
    {
        w3_cond = 1;
    }
    else
    {
        w3_cond = 0;
        w3 -= 0x100;
    }

    sub_800470B4(anime_chara == 0x21ca, unknown, anime_chara, code, w3, w3_cond);

    if (w3_cond)
    {
        mts_8008A400();
    }
    mts_printf_8008BBA0(aAnimeCharaDCod, anime_chara, code);
}
