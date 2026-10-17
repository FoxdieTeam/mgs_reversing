#include "loadrep.h"

#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"

/*---------------------------------------------------------------------------*/
// Copies the replay picture (the frame buffer area below the screen) into the
// "replay" image of the resident cache. The actor dies on its first frame.

#define REPLAY_IMAGE_X      0
#define REPLAY_IMAGE_Y      224
#define REPLAY_IMAGE_W      160
#define REPLAY_IMAGE_H      32

// Only the first 0xe00 pixels are copied to the cached image
#define REPLAY_COPY_SIZE    0xe00

/*---------------------------------------------------------------------------*/

static void Act(GV_ACT *actor)
{
    GV_DestroyActor(actor);
}

static void Die(GV_ACT *actor)
{
}

/*---------------------------------------------------------------------------*/

void *NewLoadReplay(void)
{
    RECT     rect = {REPLAY_IMAGE_X, REPLAY_IMAGE_Y, REPLAY_IMAGE_W, REPLAY_IMAGE_H};
    GV_ACT  *actor;
    u_short *buffer;
    u_short *image;
    int      i;

    actor = GV_NewActor(GV_ACTOR_AFTER2, sizeof(GV_ACT));
    if (actor != NULL)
    {
        GV_SetNamedActor(actor, Act, Die, "loadrep.c");

        buffer = GV_Malloc(REPLAY_IMAGE_W * REPLAY_IMAGE_H * sizeof(u_short));
        if (buffer == NULL)
        {
            printf("NO MEMORY FOR FILE BODY\n");
        }

        StoreImage(&rect, (u_long *)buffer);
        DrawSync(0);

        image = GV_GetCache(GV_CacheID(GV_StrCode("replay"), 'c'));
        printf("store image\n");
        printf("end DrawSync\n");

        // NON_MATCHING: the original increments i before the load in this loop
        // (3 instructions in a different order), everything else matches
        for (i = 0; i < REPLAY_COPY_SIZE; i++)
        {
            image[i] = buffer[i];
        }

        GV_Free(buffer);
    }

    return (void *)actor;
}
