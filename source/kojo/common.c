/******************************************************************************
 * included
 */

#include "common.h"

/******************************************************************************
 * publics
 */

void InitChain(
    void* lpAddress)
{
    if (lpAddress == NULL)
        return;

    *(void**)lpAddress = lpAddress;
    *(void**)((char*)lpAddress + sizeof(void*)) = lpAddress;
}

void NextChain(
    void* lpManeger,
    void* lpChain)
{
    if ((lpManeger == NULL) || (lpChain == NULL))
        return;

    *(void**)lpChain = *(void**)lpManeger;
    *(void**)((char*)lpChain + sizeof(void*)) = lpManeger;

    if (*(void**)lpManeger == lpManeger)
        *(void**)((char*)lpManeger + sizeof(void*)) = lpChain;
    else
        *(void**)((char*)(*(void**)lpManeger) + sizeof(void*)) = lpChain;

    *(void**)lpManeger = lpChain;
}

void DeleteChain(
    void* lpManeger,
    void* lpDelete)
{
    if ((lpManeger == NULL) || (lpDelete == NULL))
        return;

    if (*(void**)lpDelete == lpManeger)
        *(void**)((char*)lpManeger + sizeof(void*))
            = *(void**)((char*)lpDelete + sizeof(void*));
    else
        *(void**)((char*)(*(void**)lpDelete) + sizeof(void*))
            = *(void**)((char*)lpDelete + sizeof(void*));

    if (*(void**)((char*)lpDelete + sizeof(void*)) == lpManeger)
        *(void**)lpManeger = *(void**)lpDelete;
    else
        *(void**)*(void**)
            ((char*)lpDelete + sizeof(void*)) = *(void**)lpDelete;

    InitChain(lpDelete);
}
