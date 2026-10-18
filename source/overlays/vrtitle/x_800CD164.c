// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C5308), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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

extern void* vrtitle_dword_800D9D34;

extern char vrtitle_dword_800D9684[];

void vrtitle_800CCBAC(void);

void        vrtitle_800CD164(int);

void vrtitle_800CD164(int arg0) {

    void* temp_v0;

    temp_v0 = GV_AllocMemory(GV_NORMAL_MEMORY, 2048);
    vrtitle_dword_800D9D34 = temp_v0;

    if (temp_v0 == NULL) {

        printf(vrtitle_dword_800D9684);
    }

    vrtitle_dword_800D9D2C = arg0;
    mts_start_task(MTSID_MEMORY_CARD, vrtitle_800CCBAC, vrtitle_dword_800D9D34 + 2048, 2048);
}
