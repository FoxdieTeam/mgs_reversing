#include "common.h"
#include "menu/menuman.h"
#include "game.h"

#define MAX_HISTORY 8

static short area_history[ MAX_HISTORY ];

STATIC char GM_CurrentStageName[8] = {};

short SECTION(".sbss") area_name;
short SECTION(".sbss") pad3_;
short SECTION(".sbss") pad3;

//------------------------------------------------------------------------------

void GM_InitArea(void)
{
    memset(&area_history, 0, sizeof(area_history));
}

void GM_GetAreaHistory(short *buf)
{
    memcpy(buf, area_history, sizeof(area_history));
}

void GM_SetAreaHistory(short *buf)
{
    memcpy(area_history, buf, sizeof(area_history));
}

int GM_SetArea(int stage_id, char *stage_name)
{
    int i;

    area_name = stage_id;
    strcpy(GM_CurrentStageName, stage_name);

    for (i = MAX_HISTORY - 1; i > 0; i--)
    {
        area_history[i] = area_history[i - 1];
    }

    area_history[0] = stage_id;
    return stage_id;
}

int GM_AreaHistory(int stage_id)
{
    int i;

    for (i = 1; i < MAX_HISTORY; i++)
    {
        if (area_history[i] == stage_id)
        {
            break;
        }
    }

    return i;
}

char *GM_GetArea(int flag)
{
    return GM_CurrentStageName;
}
