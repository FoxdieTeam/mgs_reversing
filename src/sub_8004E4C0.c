#include "linker.h"

extern int dword_800ABBA8;
int SECTION(".sbss") dword_800ABBA8;

extern int dword_800ABBB4;
int SECTION(".sbss") dword_800ABBB4;

int sub_8004E4C0(int unused, int param_2)
{
  int iVar1;
  
  if (-1 < dword_800ABBA8) {
    if ((*(char *)dword_800ABBB4 & 0x40) != 0) {
      return param_2;
    }
    iVar1 = (param_2 - dword_800ABBA8) & 0xfff;
    if (iVar1 < 0x400) {
      param_2 = dword_800ABBA8 + 0x400;
    }
    if (iVar1 > 0xc00) {
      param_2 = dword_800ABBA8 - 0x400;
    }
  }
  return param_2;
}

