// vrtitle: VR revision copy of menu/datasave.c
// (writeGameData), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include <stdio.h>

#include "game/game.h"
#include "libgcl/libgcl.h"
#include "memcard/memcard.h"

extern char vrtitle_dword_800D9888[]; // "*"

// Called by data_info->make_game_data
void vrtitle_800D00A8( char *saveBuf )
{
    int   currentOffset;
    int   size;
    char *saveBufIter;

    currentOffset = 0x100;
    saveBufIter = saveBuf;
    // Note: the counter is incremented here, but the memory card
    // has not been written yet (see writeGameData in menu/datasave.c).
    GM_SaveCount++;
    for (;;)
    {
        size = GCL_MakeSaveFile(saveBufIter);
        currentOffset += size;

        if (currentOffset + size > MEMCARD_BLOCK_SIZE)
        {
            break;
        }

        saveBufIter += size;
        printf(vrtitle_dword_800D9888);
    }
}
