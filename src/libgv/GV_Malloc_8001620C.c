#include "gvd.h"

/*
extern void* System_2_Alloc_80015EB8(int idx, int size);

void GV_Alloc_8001620C(int size)
{
    System_2_Alloc_80015EB8(2, size);
}*/
extern void *GV_AllocMemory_80015EB8(int idx, int size);

void            *GV_Malloc_8001620C( size )
int             size ;
{
        return GV_AllocMemory_80015EB8( GV_NORMAL_MEMORY, size ) ;
    //System_2_Alloc_80015EB8(2, size);
}
