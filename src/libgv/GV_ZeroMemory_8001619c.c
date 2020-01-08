#include <util/idaTypes.h>

void GV_ZeroMemory_8001619c(BYTE *pMemToClear, DWORD lengthToClear)
{
    int iterator = ((DWORD)pMemToClear) & 3;
    DWORD* pMemToClearWorkingCopy;
    lengthToClear -= iterator;

    for (; iterator > 0; iterator--)
    {
        *pMemToClear = 0;
        pMemToClear++;
    }

    pMemToClearWorkingCopy = (DWORD*)pMemToClear;
    for (iterator = lengthToClear / (sizeof(DWORD)*4); iterator > 0; iterator--)
    {
        *(pMemToClearWorkingCopy) = 0;
        *(pMemToClearWorkingCopy + 1) = 0;
        *(pMemToClearWorkingCopy + 2) = 0;
        *(pMemToClearWorkingCopy + 3) = 0;
        pMemToClearWorkingCopy += 4;
    }
    pMemToClear = (BYTE*)pMemToClearWorkingCopy;

    for (iterator = lengthToClear & ((sizeof(DWORD)*4)-1); iterator > 0; iterator--)
    {
        *pMemToClear = 0;
        pMemToClear++;
    }
}