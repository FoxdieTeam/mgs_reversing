#include "Game/linkvarbuf.h"
#include "libgcl/libgcl.h"

extern char aStar[]; // = "*";

void sub_8004D1D0(char *saveBuf)
{
    int   currentOffset;
    int   size;
    char *saveBufIter;

    currentOffset = 0x100;
    saveBufIter = saveBuf;
    GM_TotalSaves++;
    for (;;)
    {
        size = GCL_MakeSaveFile_80020C0C(saveBufIter);
        currentOffset += size;

        if (currentOffset + size > 0x2000)
        {
            break;
        }

        saveBufIter += size;
        printf(aStar);
    }
}
