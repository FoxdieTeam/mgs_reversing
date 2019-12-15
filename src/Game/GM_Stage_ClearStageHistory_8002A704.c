#include "linker.h"
#include <sys/types.h>

void *memset_8008E688(void *pSrc, int value, int len);

typedef struct AreaHistory
{
    short history[8];
} AreaHistory;

AreaHistory SECTION(".gAreaHistory_800B5850") gAreaHistory_800B5850;

void GM_Stage_ClearStageHistory_8002A704(void)
{
    memset_8008E688(&gAreaHistory_800B5850, 0, sizeof(gAreaHistory_800B5850));
}

void GM_SaveAreaHistory_8002A730(AreaHistory *pHistoryCopy)
{
    *pHistoryCopy = gAreaHistory_800B5850;
}

void GM_RestoreAreaHistory_8002A784(AreaHistory *pNewHistory)
{
    gAreaHistory_800B5850 = *pNewHistory;
}
