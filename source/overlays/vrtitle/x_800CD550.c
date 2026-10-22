// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C56F4, camera_800C5750), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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

extern RadioFileModeStru_800ABB7C *vrtitle_dword_800D9D64;
extern char                       *MGS_MemoryCardName; /* in main.c */

extern char vrtitle_dword_800D96B0[]; // = "NO MEMORY FOR OBJ\n";

void vrtitle_800CD550()
{
    int i;

    vrtitle_dword_800D9D64 =
        (RadioFileModeStru_800ABB7C *)GV_AllocMemory(GV_NORMAL_MEMORY, sizeof(RadioFileModeStru_800ABB7C));
    if (vrtitle_dword_800D9D64 == NULL)
    {
        printf(vrtitle_dword_800D96B0);
    }

    for (i = 0; i < 12; i++)
    {
        vrtitle_dword_800D9D64->field_0_array[i].field_0 = 0;
    }
}

void vrtitle_800CD5AC(void)
{
    GV_FreeMemory(GV_NORMAL_MEMORY, vrtitle_dword_800D9D64);
}
