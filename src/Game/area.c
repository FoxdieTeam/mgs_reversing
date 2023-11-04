#include "linker.h"
#include "Menu/menuman.h"
#include "game.h"
#include "psyq.h"

extern AreaHistory      gAreaHistory_800B5850;
extern char             exe_name_800B5860[32];
extern Actor_GM_Daemon  GM_Daemon_800B5880;

char GM_CurrentStageName_800AB3C4[8] = {};

short SECTION(".sbss")  sCurrentAreaName_800AB9C0;
short SECTION(".sbss")  pad3_;
short SECTION(".sbss")  pad3;

//------------------------------------------------------------------------------

void GM_InitArea_8002A704(void)
{
    gAreaHistory_800B5850 = ( AreaHistory ){{ 0 }};
}

void GM_GetAreaHistory_8002A730(AreaHistory *pHistoryCopy)
{
    *pHistoryCopy = gAreaHistory_800B5850;
}

void GM_SetAreaHistory_8002A784(AreaHistory *pNewHistory)
{
    gAreaHistory_800B5850 = *pNewHistory;
}

int GM_SetArea_8002A7D8(int stage_id, char *pStageName)
{
    int i;

    sCurrentAreaName_800AB9C0 = stage_id;
    strcpy(GM_CurrentStageName_800AB3C4, pStageName);
    for (i = MAX_HISTORY - 1; i > 0; i--)
    {
        gAreaHistory_800B5850.history[i] = gAreaHistory_800B5850.history[i - 1];
    }
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

char *GM_GetArea_8002A880(int unused)
{
    return GM_CurrentStageName_800AB3C4;
}
