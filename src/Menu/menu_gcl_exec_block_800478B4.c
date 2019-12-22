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
    int lenB1;
    int scriptWord;
    unsigned char *pAfterLen;

    int byteAfter;

    lenB1 = ((pScript[1] << 8) | (pScript[2]));

    pAfterLen = pScript + 3; // 	$s1, $s3, 3

    byteAfter = *pAfterLen;

    while (*pAfterLen)
    {
        if (*pAfterLen == 0xff)
        {

            int opCode = pAfterLen[1];

            // +2 isn't happening in delay slot

            unsigned char *pData = pAfterLen + 2;
            pAfterLen = menu_gcl_read_word_80047098(&scriptWord, pData);

            switch (opCode)
            {
            case 1:
                MENU_set_chara_code_800471AC(unknown, pAfterLen);
                break;

            case 2:
                sub_80047330(unknown, pAfterLen);
                break;

            case 3:
                menu_gcl_anime_chara_code_80047280(unknown, pAfterLen);
                break;

            case 4:
                menu_gcl_set_radio_var_80047768(unknown, pAfterLen);
                break;

            case 5:
                sub_800477B0(unknown, pAfterLen);
                break;

            case 6:
                sub_80047414(unknown, pAfterLen);
                break;

            case 7:
                sub_8004780C(unknown, pAfterLen);
                break;

            case 8:
                sub_80047838(unknown, pAfterLen);
                break;

            case 0x10:
                sub_80047514(unknown, pAfterLen);
                break;

            case 0x20:
                sub_800475B8(unknown, pAfterLen);
                break;

            case 0x30:
                sub_80047660(unknown, pAfterLen);
                break;

            case 0x40:
                sub_80047748(unknown, pAfterLen);
                break;

            default:
                mts_printf_8008BBA0(aBlockExecError);
                break;
            }
            pAfterLen = (pAfterLen - 2 + scriptWord);
        }
        else
        {
            mts_printf_8008BBA0(aIllegalCodeX, *pAfterLen);
        }
        byteAfter = *pAfterLen;
    }
    return lenB1 + 1 + pScript;
}
