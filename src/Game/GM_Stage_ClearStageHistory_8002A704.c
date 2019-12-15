#include "linker.h"
#include <sys/types.h>

void *memset_8008E688(void *pSrc, int value, int len);

#define MAX_HISTORY 8

typedef struct AreaHistory
{
    short history[MAX_HISTORY];
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

extern char gCurrentStageName_800AB3C4[8];

char *strcpy_8008E768(char *, char *);

short SECTION(".sbss") sCurrentAreaName_800AB9C0;
short SECTION(".sbss") pad3_;
short SECTION(".sbss") pad3;

int GM_PushAreaHistory_8002A7D8(int areaName, char *pStageName)
{
    int i;

    sCurrentAreaName_800AB9C0 = areaName;
    strcpy_8008E768(gCurrentStageName_800AB3C4, pStageName);
    i = MAX_HISTORY - 1;
    do
    {
        gAreaHistory_800B5850.history[i] = gAreaHistory_800B5850.history[i - 1];
        i--;
    } while (0 < i);
    gAreaHistory_800B5850.history[0] = areaName;
    return areaName;
}

int GM_AreaHistory_8002A848(int areaName)
{
    int i;
    for (i=1; i<MAX_HISTORY; i++)
    {
        if (gAreaHistory_800B5850.history[i] == areaName)
        {
            break;
        }
    }
    return i;
}
