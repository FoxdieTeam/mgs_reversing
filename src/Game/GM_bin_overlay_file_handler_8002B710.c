#include "linker.h"
#include "mts_new.h"

extern unsigned char* GV_ResidentMemoryBottom_800AB940;

void *memcpy_8008E648(void *destination, const void *source, int num);

extern unsigned char* gOverlayBase_800AB9C8;

extern const char aTooLargeStageB[];

extern int gOverlayBinSize_800B5290;

int GM_bin_overlay_file_handler_8002B710(unsigned char *pFileData, int fileNameHashed)
{
    if ((gOverlayBase_800AB9C8 + gOverlayBinSize_800B5290) > GV_ResidentMemoryBottom_800AB940)
    {
        mts_printf_8008BBA0(aTooLargeStageB);
    }
    memcpy_8008E648(gOverlayBase_800AB9C8, pFileData, gOverlayBinSize_800B5290);
    return 1;
}
