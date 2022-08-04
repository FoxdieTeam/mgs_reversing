#include "linker.h"
#include "Menu/menuMan.h"
#include "game.h"
#include <SYS/TYPES.H>

void *memset_8008E688(void *pSrc, int value, int len);

AreaHistory SECTION(".gAreaHistory_800B5850") gAreaHistory_800B5850;
char SECTION(".gAreaHistory_800B5850") exe_name_800B5860[32];
Actor_GM_Daemon SECTION(".gAreaHistory_800B5850") GM_Daemon_800B5880;

void GM_InitArea_8002A704(void)
{
    memset_8008E688(&gAreaHistory_800B5850, 0, sizeof(gAreaHistory_800B5850));
}

void GM_GetAreaHistory_8002A730(AreaHistory *pHistoryCopy)
{
    *pHistoryCopy = gAreaHistory_800B5850;
}

void GM_SetAreaHistory_8002A784(AreaHistory *pNewHistory)
{
    gAreaHistory_800B5850 = *pNewHistory;
}

extern char gCurrentStageName_800AB3C4[8];

char *strcpy_8008E768(char *, char *);

short SECTION(".sbss") sCurrentAreaName_800AB9C0;
short SECTION(".sbss") pad3_;
short SECTION(".sbss") pad3;

int GM_SetArea_8002A7D8(int stage_id, char *pStageName)
{
    int i;

    sCurrentAreaName_800AB9C0 = stage_id;
    strcpy_8008E768(gCurrentStageName_800AB3C4, pStageName);
    i = MAX_HISTORY - 1;
    do
    {
        gAreaHistory_800B5850.history[i] = gAreaHistory_800B5850.history[i - 1];
        i--;
    } while (0 < i);
    gAreaHistory_800B5850.history[0] = stage_id;
    return stage_id;
}

int GM_AreaHistory_8002A848(int stage_id)
{
    int i;
    for (i = 1; i < MAX_HISTORY; i++)
    {
        if (gAreaHistory_800B5850.history[i] == stage_id)
        {
            break;
        }
    }
    return i;
}

char *GM_GetArea_8002A880(void)
{
    return gCurrentStageName_800AB3C4;
}
