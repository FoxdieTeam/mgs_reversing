// vrsave: save file title strings of the VR save menu.
#include <stdio.h>

#include "mgstype.h"

extern int   vrsave_dword_800D1BF4;

extern char vrsave_dword_800D14FC[]; // = "%s%s%s%s%s";
extern char vrsave_dword_800D1508[]; // Shift-JIS string
extern char vrsave_dword_800D1514[]; // Shift-JIS string
extern char vrsave_dword_800D1518[]; // Shift-JIS string
extern char vrsave_dword_800D1520[]; // = "\f%c%s";

void vrsave_800C9C38(int mission, char *title, char *sjis);

void vrsave_800C9FA4(char *out)
{
    char title[32];
    char sjis[48];

    vrsave_800C9C38(vrsave_dword_800D1BF4, title, sjis);
    sprintf(out, vrsave_dword_800D14FC, vrsave_dword_800D1508, vrsave_dword_800D1514, vrsave_dword_800D1518,
            vrsave_dword_800D1514, sjis);
}

void vrsave_800CA018(char *out, u_char *mes)
{
    char title[32];
    char sjis[64];

    vrsave_800C9C38(((mes[7] << 4) & 0xF0) | (mes[1] & 0xF), title, sjis);
    sprintf(out, vrsave_dword_800D1520, '2', title);
}
