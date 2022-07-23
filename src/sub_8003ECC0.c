#include "linker.h"

extern int           dword_800ABAE8;
int SECTION(".sbss") dword_800ABAE8;

void sub_8003ECC0(void)
{
  dword_800ABAE8 = 0;
}
