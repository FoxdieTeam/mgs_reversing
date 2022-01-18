#include <util/idaTypes.h>
#include "libgv.h"

extern LibGV_FileRecord* GV_FileCacheFind_80015240(DWORD);

void* GV_GetCache_8001538C(int fileNameHashed)
{
    LibGV_FileRecord* pRecord = GV_FileCacheFind_80015240(fileNameHashed);
    if (pRecord)
    {
        return pRecord->mFileBuffer;
    }

    return 0;
}
