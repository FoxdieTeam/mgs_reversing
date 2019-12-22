#include "linker.h"
#include "menuMan.h"
#include "mts_new.h"

extern const char aIllegalCodeX[];
extern const char aBlockExecError[];

void MENU_set_chara_code_800471AC(void *, unsigned char *);
void sub_80047330(void *, unsigned char *);
void menu_gcl_anime_chara_code_80047280(void *, unsigned char *);
void sub_800477B0(void *, unsigned char *);
void sub_80047414(void *, unsigned char *);
void sub_8004780C(void *, unsigned char *);
void sub_80047838(void *, unsigned char *);
void sub_80047514(void *, unsigned char *);
void sub_800475B8(void *, unsigned char *);
void sub_80047660(void *, unsigned char *);
void sub_80047748(void *, unsigned char *);

unsigned char *menu_gcl_exec_block_800478B4(unsigned char *unknown, unsigned char *pScript)
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
