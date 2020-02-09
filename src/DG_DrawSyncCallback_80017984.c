#include "linker.h"

unsigned int GetRCnt_800996E8(unsigned int rcnt);

short SECTION(".sbss") word_800AB980;
short SECTION(".sbss") word_800AB982;

short SECTION(".sbss") word_800AB984[2];

int SECTION(".sbss") dword_800AB988;
int SECTION(".sbss") dword_800AB98C;

void DG_DrawSyncCallback_80017984(void)
{
    word_800AB982 = GetRCnt_800996E8(0xf2000001);
}