// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C4BAC, camera_800C4D20), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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

extern int vrtitle_dword_800D9D3C;
extern int vrtitle_dword_800D9D40;

extern char vrtitle_dword_800D9660[];
extern char vrtitle_dword_800D9654[];
extern char vrtitle_dword_800D9410[];
extern char vrtitle_dword_800D942C[];
extern int vrtitle_dword_800D9D08;
extern int vrtitle_dword_800D9D0C;
extern int vrtitle_dword_800D9D10;
extern int vrtitle_dword_800D9D14;

int vrtitle_800CC9E8(MEMCARD *card, int index) {

    char         *buffer;
    int           result;
    int           retries;
    int           i;

    GM_PadResetDisable = 1;
    buffer = GV_AllocMemory(2, 0x2000);

    if (!buffer) {
        printf(vrtitle_dword_800D9410);
    }

    result = 0;
    retries = 4;

    vrtitle_dword_800D9D08 = (int)buffer;
    vrtitle_dword_800D9D0C = (int)buffer;

    for (; retries > 0; retries--) {
        memcard_read(card->port, card->files[index].name, 0, buffer, 0x2000);

        while (memcard_status() > 0) {
            mts_wait_vbl(2);
        }

        if (memcard_status() == 0) {
            *(char *)&vrtitle_dword_800D9D10 = card->port;
            for (i = 0; i < 24; i++) {
                /* per-iteration scope for p710 is required for the match */
                char *p710 = (char *)&vrtitle_dword_800D9D14;
                p710[i] = card->files[index].name[i];
            }
            printf(vrtitle_dword_800D942C, *(unsigned char *)&vrtitle_dword_800D9D10, (char *)&vrtitle_dword_800D9D14);
            result = 1;
            break;
        }
    }

    GM_PadResetDisable = 0;
    return result;
}

int vrtitle_800CCB5C(int arg0) {

    vrtitle_dword_800D9D3C = arg0;
    printf(vrtitle_dword_800D9654, arg0);

    mts_slp_tsk();
    printf(vrtitle_dword_800D9660, vrtitle_dword_800D9D40);

    return vrtitle_dword_800D9D40;
}
