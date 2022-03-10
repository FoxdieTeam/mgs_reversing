#include "linker.h"

unsigned int GetRCnt_800996E8(unsigned int rcnt);

short SECTION(".sbss") N_ChanlPerfMax_800AB980;
short SECTION(".sbss") word_800AB982;

unsigned short SECTION(".sbss") gCurrentRootCnt_800AB984;

void DG_DrawSyncCallback_80017984(void)
{
    word_800AB982 = GetRCnt_800996E8(0xf2000001);
}