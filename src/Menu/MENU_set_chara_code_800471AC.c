#include "linker.h"
#include "mts_new.h"
#include "menuMan.h"
#include "gcl.h"

extern const char aSetCharaCodeD[];
extern const char aAnimeCharaDCod[];
extern const char aVoxcodeX[];
extern const char aIllegalCodeX[];
extern const char aSetDS[];
extern const char aBlockExecError[];

void sub_800470B4(int param_1, void *param_2, int param_3, int param_4, int param_5, int param_6);
void SwEnterCriticalSection_8009954C(void);
void SwExitCriticalSection_8009956C(void);
void sub_80037EE0(int, int);
int sub_80037CD8(void);
void mts_8008C408(int, int);
void mts_8008C454(int, int);
void GM_Sound_80032C48(int, int code);
int rand_8008E6B8(void);
unsigned char *sub_80047880(menu_chara_struct *unknown, unsigned char *pScript);
unsigned char *GCL_VarSaveBuffer_800217F0(unsigned char *);

#define MakeVoxCode(x) ((unsigned int)x[0] << 0x18) |     \
                           ((unsigned int)x[1] << 0x10) | \
                           ((unsigned int)x[2] << 8) |    \
                           ((unsigned int)x[3])

#define CHARA_SNAKE 0x21ca // スネーク

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

    bVar1 = charaCode == CHARA_SNAKE;

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

    sub_800470B4(anime_chara == CHARA_SNAKE, unknown, anime_chara, code, w3, w3_cond);

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
        GM_Sound_80032C48(MakeVoxCode(pScriptIter), 0);
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

unsigned char *sub_800474EC(int *pRet, unsigned char *pScript)
{
    int code;
    return GCL_Execute_8002069C(pScript, &code, pRet);
}

void sub_80047514(menu_chara_struct *unknown, unsigned char *pScript)
{
    for (;;)
    {
        int execRet;
        pScript = sub_800474EC(&execRet, pScript);
        for (;;)
        {
            if (execRet)
            {
                menu_gcl_exec_block_800478B4(unknown, pScript);
                return;
            }

            pScript = sub_80047880(unknown, pScript);
            if (*pScript == 0xff)
            {
                int scriptByte = pScript[1];
                pScript += 2;

                if (scriptByte == 0x12)
                {
                    break;
                }
                else if (scriptByte != 0x11)
                {
                    return;
                }
                execRet = 1;
            }
            else
            {
                if (*pScript != 0)
                {
                    mts_printf_8008BBA0(aIllegalCodeX, *pScript);
                }
                return;
            }
        }
    }
}

void sub_800475B8(menu_chara_struct *unknown, unsigned char *pScript)
{
    int execRet;
    int script_word;

    pScript = sub_800474EC(&execRet, pScript);
    for (;;)
    {
        const int script_b1 = *pScript;
        pScript++;

        if (script_b1 == 0x21)
        {
            pScript = menu_gcl_read_word_80047098(&script_word, pScript);
            if (execRet == script_word)
            {
                menu_gcl_exec_block_800478B4(unknown, pScript);
                return;
            }
            else
            {
                pScript = sub_80047880(unknown, pScript);
            }
        }
        else if (script_b1 == 0x22)
        {
            menu_gcl_exec_block_800478B4(unknown, pScript);
            return;
        }
        else if (script_b1 == 0)
        {
            return;
        }
        else
        {
            mts_printf_8008BBA0(aIllegalCodeX, script_b1);
        }
    }
}

void sub_80047660(menu_chara_struct *unknown, unsigned char *pScript)
{
    int script_word;
    pScript = menu_gcl_read_word_80047098(&script_word, pScript);
    script_word = rand_8008E6B8() % script_word;

    for (;;)
    {
        const int script_byte = *pScript;
        pScript++;
        if (script_byte == 0x31)
        {
            int script_word2;
            pScript = menu_gcl_read_word_80047098(&script_word2, pScript);
            script_word -= script_word2;
            if (script_word < 1)
            {
                menu_gcl_exec_block_800478B4(unknown, pScript);
                return;
            }
            pScript = sub_80047880(unknown, pScript);
        }
        else
        {
            if (script_byte == 0)
            {
                return;
            }
            mts_printf_8008BBA0(aIllegalCodeX, script_byte);
        }
    }
}

void sub_80047748(menu_chara_struct *unknown, unsigned char *pScript)
{
    int ret;
    sub_800474EC(&ret, pScript);
}

void menu_gcl_set_radio_var_80047768(menu_chara_struct *unknown, unsigned char *pScript)
{
    int varId;
    pScript = menu_gcl_read_word_80047098(&varId, pScript);
    mts_printf_8008BBA0(aSetDS, varId, pScript);
    menu_radio_clear_or_set_var_8004E110(varId, pScript);
}

void sub_800477B0(menu_chara_struct *unknown, unsigned char *pScript)
{
    int iVar1 = GCL_GetNextValue_800209E8(pScript);
    unknown->field_0_state = 3;
    unknown->field_C_pScript = GCL_Get_Param_Result_80020AA4();
    unknown->field_1A = iVar1;
    mts_8008A400();
    unknown->field_18 &= ~0x100;
}

void sub_8004780C(menu_chara_struct *unknown, unsigned char *pScript)
{
    unknown->field_0_state = 4;
    unknown->field_C_pScript = pScript;
    unknown->field_1A = 0;
    mts_8008A400();
}

void sub_80047838(menu_chara_struct *unknown, unsigned char *pScript)
{
    while (*pScript)
    {
        pScript = GCL_VarSaveBuffer_800217F0(pScript);
    }
}

unsigned char *sub_80047880(menu_chara_struct* unknown, unsigned char *pScript)
{
    int len;
    pScript++;
    menu_gcl_read_word_80047098(&len, pScript);
    return pScript + len;
}

unsigned char *menu_gcl_exec_block_800478B4(menu_chara_struct *unknown, unsigned char *pScript)
{
    const int scriptBlockLen = ((pScript[1] << 8) | (pScript[2]));
    unsigned char *pScriptIter = pScript + 3;
    while (*pScriptIter)
    {
        if (*pScriptIter == 0xff)
        {
            int scriptWord;
            const int opCode = pScriptIter[1];
            pScriptIter = menu_gcl_read_word_80047098(&scriptWord, pScriptIter + 2);

            switch (opCode)
            {
            case 0x01:
                MENU_set_chara_code_800471AC(unknown, pScriptIter);
                break;

            case 0x02:
                sub_80047330(unknown, pScriptIter);
                break;

            case 0x03:
                menu_gcl_anime_chara_code_80047280(unknown, pScriptIter);
                break;

            case 0x04:
                menu_gcl_set_radio_var_80047768(unknown, pScriptIter);
                break;

            case 0x05:
                sub_800477B0(unknown, pScriptIter);
                break;

            case 0x06:
                sub_80047414(unknown, pScriptIter);
                break;

            case 0x07:
                sub_8004780C(unknown, pScriptIter);
                break;

            case 0x08:
                sub_80047838(unknown, pScriptIter);
                break;

            case 0x10:
                sub_80047514(unknown, pScriptIter);
                break;

            case 0x20:
                sub_800475B8(unknown, pScriptIter);
                break;

            case 0x30:
                sub_80047660(unknown, pScriptIter);
                break;

            case 0x40:
                sub_80047748(unknown, pScriptIter);
                break;

            default:
                mts_printf_8008BBA0(aBlockExecError);
                break;
            }
            pScriptIter = (pScriptIter - sizeof(short) + scriptWord);
        }
        else
        {
            mts_printf_8008BBA0(aIllegalCodeX, *pScriptIter);
        }
    }
    return scriptBlockLen + 1 + pScript;
}
