// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C5D54), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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

extern RECT                        vrtitle_dword_800C1B74;
extern char                       *vrtitle_dword_800D9D68;
extern char                       *MGS_MemoryCardName; /* in main.c */

void vrtitle_800CDBB0(MenuWork *work)
{
    KCB  local_kcb;
    KCB *allocated_kcb;

    if (work->field_214_font == NULL)
    {
        KCB *ptr_local_kcb = &local_kcb;

        GV_ZeroMemory(ptr_local_kcb, sizeof(KCB));
        ClearImage(&vrtitle_dword_800C1B74, 0, 0, 0);

        font_init_kcb(ptr_local_kcb, &vrtitle_dword_800C1B74, 960, 510);
        font_set_kcb(ptr_local_kcb, -1, -1, 0, 6, 2, 0);

        allocated_kcb = (KCB *)GV_AllocMemory(GV_NORMAL_MEMORY, font_get_buffer_size(ptr_local_kcb) + sizeof(KCB));
        font_set_buffer(ptr_local_kcb, allocated_kcb + 1);
        font_set_color(ptr_local_kcb, 0, 0x6739, 0);
        font_set_color(ptr_local_kcb, 1, 0x3bef, 0);
        font_set_color(ptr_local_kcb, 2, 0x3a4b, 0);
        // font_set_color(ptr_local_kcb, 3, 0x1094, 0);
        font_clut_update(ptr_local_kcb);

        work->field_214_font = allocated_kcb;
        memcpy(allocated_kcb, ptr_local_kcb, sizeof(KCB));

        vrtitle_dword_800D9D68 = NULL;
    }
}
