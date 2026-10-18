// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (CameraDie_800CE470), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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

void vrtitle_800D5EC0(Work *work)
{
    GM_FreePrim(work->prim1);
    GM_FreePrim(work->prim2);
    GM_FreePrim(work->prim3);
}
