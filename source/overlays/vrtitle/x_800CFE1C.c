// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C7FF4, camera_800C80E4), transplanted from the main-tree twin; offsets/constants adapted to the VR.
// Note that there are two "camera.c" actors,
// this is probably not the enemy/camera.c actor.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libpress.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libfs/libfs.h"
#include "menu/menuman.h"
#include "menu/radio.h"
#include "memcard/memcard.h"
#include "game/game.h"
#include "mts/mts.h"
#include "mts/taskid.h"
#include "overlays/camera/unknown/camera.h"

extern char                       *MGS_MemoryCardName; /* in main.c */
extern int                         vrtitle_dword_800D9D2C;

extern int        vrtitle_dword_800D9D78;
extern int        vrtitle_dword_800D9D7C;
extern char vrtitle_dword_800D9850[];
extern char vrtitle_dword_800D985C[];

extern char vrtitle_dword_800D9860[];
extern char vrtitle_dword_800D986C[];
extern char       vrtitle_dword_800C1BAC[]; // Shift-JIS default area name

void vrtitle_800CFE1C(int code, char **pAreaNameForMenu, char **pAreaNameForSaveData)
{
    int i;

    if (code == 0)
    {
        *pAreaNameForMenu = vrtitle_dword_800D9850;
        *pAreaNameForSaveData = vrtitle_dword_800D985C;
    }

    GCL_SetArgTop((unsigned char *)vrtitle_dword_800D9D78);

    for (i = 0; i < code; i++)
    {
        if (GCL_NextStr() == 0)
        {
            return;
        }
        *pAreaNameForMenu = GCL_GetString(GCL_NextStr());
        if (vrtitle_dword_800D9D7C > 0 && vrtitle_dword_800D9D2C == 0)
        {
            *pAreaNameForSaveData = GCL_GetString(GCL_NextStr());
        }
    }
}

void vrtitle_800CFF0C(char *out, MEMCARD *unused, int hours, int minutes)
{
    char  playTime[11];
    char *discard;
    char *areaName;

    playTime[0] = 0x82;
    playTime[1] = (hours / 10) + 0x4F;
    playTime[2] = 0x82;
    playTime[3] = (hours % 10) + 0x4F;
    playTime[4] = 0x81;
    playTime[5] = 0x46;
    playTime[6] = 0x82;
    playTime[7] = (minutes / 10) + 0x4F;
    playTime[8] = 0x82;
    playTime[9] = (minutes % 10) + 0x4F;
    playTime[10] = '\0';

    if (vrtitle_dword_800D9D7C == 0)
    {
        vrtitle_800CFE1C(1, &discard, &areaName);
        areaName = vrtitle_dword_800C1BAC;
    }
    else
    {
        vrtitle_800CFE1C(vrtitle_dword_800D9D7C, &discard, &areaName);
    }

    sprintf(out, vrtitle_dword_800D9860,
            vrtitle_dword_800D986C, vrtitle_dword_800D985C, playTime, vrtitle_dword_800D985C, areaName);
}
