#include "linker.h"

extern char byte_8009F734[];

int SECTION(".dword_800B3818") dword_800B3818;

int StoreImage_8008FB70(char *, int *);

void sub_80078F04(void)
{
	StoreImage_8008FB70(byte_8009F734, &dword_800B3818);
}
