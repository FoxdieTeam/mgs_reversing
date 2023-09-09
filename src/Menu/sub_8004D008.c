#include "Menu/menuman.h"
#include "psyq.h"
#include "Game/linkvarbuf.h"

extern int dword_800ABB90;
int        dword_800ABB90;

extern char  aAtEUC[];
extern char  aSSSSSS[];
extern char  dword_800122F4[];

extern const char aExSJIS[];
extern const char aHdSJIS[];
extern const char aNmSJIS[];
extern const char aEzSJIS[];
extern const char aVeSJIS[];

char dword_8009EC10[] = {0x82, 0x63, 0x82, 0x8F, 0x82, 0x83, 0x82, 0x8B, 0x00}; // Ｄｏｃｋ
const char *off_8009EC1C[] = {aVeSJIS, aEzSJIS, aNmSJIS, aHdSJIS, aExSJIS};

void sub_8004D008(char *outStr, mem_card *pMemcard, int arg2, int arg3)
{
    char  str1[11];
    char *str2;
    char *str3;

    str1[0] = 0x82;
    str1[1] = (arg2 / 10) + 0x4f;
    str1[2] = 0x82;
    str1[3] = (arg2 % 10) + 0x4f;
    str1[4] = 0x81;
    str1[5] = 0x46;
    str1[6] = 0x82;
    str1[7] = (arg3 / 10) + 0x4f;
    str1[8] = 0x82;
    str1[9] = (arg3 % 10) + 0x4f;
    str1[10] = '\0';
    if (dword_800ABB90 == 0)
    {
        sub_8004CF20(1, &str2, &str3);
        str3 = dword_8009EC10;
    }
    else
    {
        sub_8004CF20(dword_800ABB90, &str2, &str3);
    }
    sprintf(outStr, aSSSSSS, dword_800122F4, off_8009EC1C[GM_DifficultyFlag + 1], aAtEUC, str1, aAtEUC, str3);
}
