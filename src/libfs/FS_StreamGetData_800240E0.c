extern int fs_stream_is_force_stop_8009D518;

extern void *fs_stream_heap_800B52A4;

extern int fs_stream_heapSize_800B52AC;

extern void *fs_ptr_800B52B4;
extern void *fs_ptr_800B52B8;
extern void *fs_ptr_800B52BC;

void * FS_StreamGetData_800240E0(int param_1)
{
    char *ptr;
    int cVar1;
    int uVar2;
    
    if (fs_stream_is_force_stop_8009D518 != 0)
    {
        return 0;
    }
    
    for (ptr = fs_ptr_800B52B4; ptr != fs_ptr_800B52BC;)
    {
        cVar1 = *(int*)ptr & 0xFF;
        uVar2 = *(int*)ptr >> 8;
        
        if (cVar1 == 0xff)
        {            
            ptr = fs_stream_heap_800B52A4;
        }
        else
        {
            if (cVar1 == param_1)
            {
                *ptr = cVar1 | 0x80;
                return ptr + 4;
            }

            ptr += uVar2;

            if (ptr >= (char *)fs_stream_heap_800B52A4 + fs_stream_heapSize_800B52AC)
            {
                ptr = fs_stream_heap_800B52A4;
            }
        }
    }
    
    return 0;
}