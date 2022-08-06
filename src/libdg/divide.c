#include "libdg.h"

#define SCRPAD_ADDR 0x1F800000

static inline DG_DivideMem* get_mem()
{
    return (DG_DivideMem*)(SCRPAD_ADDR);
}

void DG_DivideChanl_helper_80019044( int memIdx )
{
    void* ret;
    GV_Heap* heap;

    DG_DivideMem* unknown = get_mem();
    
    heap = GV_SplitMemory_80018FA4( memIdx, &unknown->addr, 0x34 );

    unknown->pHeap = heap;
    unknown->pAlloc = 0;
    ret = sub_800190A0( heap, &unknown->pAlloc, &unknown->size );
    
    unknown->pDataStart = ret;
}

void DG_DivideStart_80019098(void)
{

}

void* sub_800190A0( GV_Heap* heap, GV_MemoryAllocation** alloc_list, int* size )
{
    int i;
    int alloc_idx;
    GV_MemoryAllocation* allocs;

    allocs = *alloc_list;

    if (!allocs) 
    {
        allocs = heap->mAllocs;
    }
    else
    {
        allocs++;
    }
    
    //gets the number of allocs between the current one and the total
    alloc_idx  = (int)(allocs - 2);
    alloc_idx -= (int)heap;
    alloc_idx >>= 3;
    
    i = heap->mUnitsCount - alloc_idx;

    for ( ; i > 0 ; --i )
    {
        if ( allocs->mAllocType == GV_MemoryAllocation_States_Free_0 )
        {
            alloc_list[0] = allocs;
            *size = allocs[1].mPDataStart - allocs[0].mPDataStart;
            return allocs->mPDataStart;
        }
        allocs++;
    }

    *size = 0;
    return  0;
}

void* sub_8001911C() {
    void*           org_addr;
    DG_DivideMem*   divide_mem;

    divide_mem = get_mem();
  
    divide_mem->size = divide_mem->size - 0x34;

    if (divide_mem->size < 0)
    {
        divide_mem->pDataStart =  sub_800190A0( divide_mem->pHeap, &divide_mem->pAlloc, &divide_mem->size );
    }
    else
    {
        divide_mem->addr -= 1;
        org_addr = divide_mem->pDataStart;
        divide_mem->pDataStart  += 0x34;
        return org_addr;
    }
    
    if ( divide_mem->pDataStart ) 
    {
        return sub_8001911C();
    }
    else
    {
        divide_mem->addr = 0;
        return 0;
    }
}

char sub_80019194( DG_DivideFile* a0 )
{
    int v0, v1;

    if ( !a0->field_0B ) return 0;

    v1 = a0[3].field_0B;

    v0 = a0->field_0B & a0[1].field_0B;
    v0 &= v1;
    v0 &= a0[4].field_0B;

    return v0;
}

//set some flag?
void sub_800191CC( DG_DivideFile* a0 )
{
    char result = 0;

    if ( a0->field_0C < -160 )
    {
        result = 1;
    }
    else if ( 160 < a0->field_0C )
    {
        result = 2;
    }

    if ( a0->field_0E < -112 )
    {
        result |= 4;
    }
    else if ( 112 < a0->field_0E )
    {
        result |= 8;
    }

    if ( !a0->field_10 )
    {
        result |= 16;
    }

    a0->field_0B = result;
}

void sub_8001923C( DG_DivideFile* a0, DG_DivideFile* a1, DG_DivideFile* a2 )
{
    a2->field_00 = (a0->field_00 + a1->field_00) / 2;
    a2->field_02 = (a0->field_02 + a1->field_02) / 2;
    a2->field_04 = (a0->field_04 + a1->field_04) / 2;
    a2->field_06 = (a0->field_06 + a1->field_06) / 2;
    a2->field_07 = (a0->field_07 + a1->field_07) / 2;
    a2->field_08 = (a0->field_08 + a1->field_08) / 2;
    a2->field_09 = (a0->field_09 + a1->field_09) / 2;
    a2->field_0A = (a0->field_0A + a1->field_0A) / 2;
}

//this is probably just some really simple divide
void sub_80019318( DG_DivideFile* file_1, DG_DivideFile* file_2, DG_DivideFile* a3 )
{
    int a2, a0, v1;

    a2 = file_2->field_0E - file_1->field_0E;
    a0 = file_1->field_0C - file_2->field_0C;
    v1 = get_mem()->field_0C;

    if ( a2 >= 0 )
    {
        if (a0 >= 0)
        {
            if ( a0 / 2 < a2 )
            {
                a3->field_0C += v1;
            }
            //loc_80019370:
            if (a2 / 2 < a0)
            {
                a3->field_0E += v1;
            }
        }
        else
        {
            //loc_80019398
            a0 = -a0;
            if ( a0 / 2 < a2 )
            {
                a3->field_0C += v1;
            }
            //loc_8001941C:
            if (a2 / 2 < a0)
            {
                a3->field_0E -= v1;
            }
        }
    }
    else
    {
        a2 = -a2;
        if (a0 >= 0)
        {
            if ( a0 / 2 < a2 )
            {
                a3->field_0C -= v1;
            }
            //loc_80019370:
            if (a2 / 2 < a0)
            {
                a3->field_0E += v1;
            }
        }
        else
        {
            //loc_800193EC
            a0 = -a0;
            if ( a0 / 2 < a2 )
            {
                a3->field_0C -= v1;
            }
            //loc_8001941C:
            if (a2 / 2 < a0)
            {
                a3->field_0E -= v1;
            }
        }
    }
}