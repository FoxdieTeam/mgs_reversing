// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C82B0), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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

void vrtitle_800CD550(void);

extern char                       *MGS_MemoryCardName; /* in main.c */
extern DATA_INFO                  *vrtitle_dword_800D9D30;
extern int                         vrtitle_dword_800D9D6C;

void        vrtitle_800CD164(int);

void vrtitle_800D0124(DATA_INFO *arg0, int arg1)
{
    vrtitle_dword_800D9D6C = 0;
    vrtitle_dword_800D9D30 = arg0;
    vrtitle_800CD550();
    vrtitle_800CD164(arg1);
}
