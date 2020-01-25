#include <util/idaTypes.h>

typedef struct
{
    DWORD mId;
    void* mFileBuffer;
} LibGV_FileRecord;

extern LibGV_FileRecord* sub_80015240(DWORD);

void* GV_FindCachedFile_8001538C(DWORD fileNameHashed)
{
    LibGV_FileRecord* pRecord = sub_80015240(fileNameHashed);
    if (pRecord)
    {
        return pRecord->mFileBuffer;
    }

    return 0;
}
