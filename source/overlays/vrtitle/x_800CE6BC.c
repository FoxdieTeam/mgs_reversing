// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C68DC, camera_800C6918), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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

extern const char vrtitle_dword_800D9708[];
extern const char vrtitle_dword_800D9714[];
extern const char vrtitle_dword_800D9728[];

void vrtitle_800CE6BC(void *ptr)
{
    printf((char *)vrtitle_dword_800D9708);
    if (ptr)
    {
        GV_FreeMemory(GV_NORMAL_MEMORY, ptr);
    }
}

void vrtitle_800CE6F8(void **arg0, int arg1)
{
    void *temp_v0;

    if (*arg0 == NULL)
    {
        temp_v0 = GV_AllocMemory(GV_NORMAL_MEMORY, (arg1 * 0x24) + 0x24);
        *arg0 = temp_v0;
        if (temp_v0 == NULL)
        {
            printf((char *)vrtitle_dword_800D9714);
        }
        printf((char *)vrtitle_dword_800D9728, *arg0);
    }
}
