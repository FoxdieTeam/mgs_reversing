#include "linker.h"
#include "mts_new.h"
#include "menuMan.h"
#include "gcl.h"

extern const char aSetCharaCodeD[];
extern const char aAnimeCharaDCod[];

void sub_800470B4(int param_1, void *param_2, int param_3, int param_4, int param_5, int param_6);
void SwEnterCriticalSection_8009954C(void);
void SwExitCriticalSection_8009956C(void);

void sub_80037EE0(int, int);
int sub_80037CD8(void);

void mts_8008C408(int, int);
void mts_8008C454(int, int);
void sub_80032C48(int, int code);

extern const char aVoxcodeX[];

#define MakeVoxCode(x) ((unsigned int)x[0] << 0x18) |     \
                           ((unsigned int)x[1] << 0x10) | \
                           ((unsigned int)x[2] << 8) |    \
                           ((unsigned int)x[3])

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

    unknown->field_0_state = 1;

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

void sub_80047330(menu_chara_struct *unknown, unsigned char *pScript)
{
    unsigned int voxCode = MakeVoxCode(pScript);
    pScript += sizeof(unsigned int);

    mts_printf_8008BBA0(aVoxcodeX, voxCode);

    if ((unknown->field_18 & 0x100) == 0)
    {
        SwEnterCriticalSection_8009954C();
        sub_80037EE0(voxCode, 0);
        SwExitCriticalSection_8009956C();
        unknown->field_14_bInExecBlock = 1;
        menu_gcl_exec_block_800478B4(unknown, pScript);
        unknown->field_14_bInExecBlock = 0;
        while (sub_80037CD8() != -1) // wait vox finish ?
        {
            mts_wait_vbl_800895F4(2);
        }
    }
    else
    {
        menu_gcl_exec_block_800478B4(unknown, pScript);
    }
}

void sub_80047414(menu_chara_struct *unknown, unsigned char *pScript)
{
    unsigned char *pScriptIter;
    int scriptVal;
    int i;

    switch (*pScript)
    {
    case 0x00:
        pScriptIter = pScript;
        pScriptIter++;
        sub_80032C48(MakeVoxCode(pScriptIter), 0);
        break;

    case 0x01:
        scriptVal = pScript[1];
        i = (signed short int)(pScript[3] | (pScript[2] << 8));
        while (i > 0)
        {
            if (scriptVal > 0)
            {
                mts_8008C408(1, 2);
                mts_8008C454(1, scriptVal);
            }
            mts_wait_vbl_800895F4(1);
            i--;
        }
        break;
    }
}

void sub_800474EC(int* pRet, unsigned char* pScript)
{
    int any;
    GCL_Execute_8002069C(pScript, &any, pRet);
}
