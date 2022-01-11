#include <util/idaTypes.h>
#include "libgv.h"

extern LibGV_FileRecord* GV_FileCacheFind_80015240(DWORD);

void* GV_FindCachedFile_8001538C(DWORD fileNameHashed)
{
    LibGV_FileRecord* pRecord = GV_FileCacheFind_80015240(fileNameHashed);
    if (pRecord)
    {
        return pRecord->mFileBuffer;
    }

    return 0;
}
