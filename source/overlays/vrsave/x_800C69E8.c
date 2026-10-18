// vrsave: VR revision copy of overlays/camera/unknown/camera.c
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

extern RadioFileModeStru_800ABB7C *vrsave_dword_800D1C24;
extern char                       *MGS_MemoryCardName; /* in main.c */

extern const char vrsave_dword_800D135C[]; // = "NO MEMORY FOR OBJ\n";

void vrsave_800C69E8()
{
    int i;

    vrsave_dword_800D1C24 =
        (RadioFileModeStru_800ABB7C *)GV_AllocMemory(GV_NORMAL_MEMORY, sizeof(RadioFileModeStru_800ABB7C));
    if (vrsave_dword_800D1C24 == NULL)
    {
        printf((char *)vrsave_dword_800D135C);
    }

    for (i = 0; i < 12; i++)
    {
        vrsave_dword_800D1C24->field_0_array[i].field_0 = 0;
    }
}

void vrsave_800C6A44(void)
{
    GV_FreeMemory(GV_NORMAL_MEMORY, vrsave_dword_800D1C24);
}
