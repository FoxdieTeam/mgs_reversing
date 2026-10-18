// vrsave: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C4D20), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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

extern int vrsave_dword_800D1C00;
extern int vrsave_dword_800D1C04;

extern char vrsave_dword_800D1300[];
extern char vrsave_dword_800D12F4[];

int vrsave_800C5EE8(int arg0) {

    vrsave_dword_800D1C00 = arg0;
    printf(vrsave_dword_800D12F4, arg0);

    mts_slp_tsk();
    printf(vrsave_dword_800D1300, vrsave_dword_800D1C04);

    return vrsave_dword_800D1C04;
}
