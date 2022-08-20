extern int fs_stream_is_force_stop_8009D518;

extern void *fs_stream_heap_800B52A4;

extern int fs_stream_heapSize_800B52AC;

extern void *fs_ptr_800B52B4;
extern void *fs_ptr_800B52B8;
extern void *fs_ptr_800B52BC;

void * FS_StreamGetData_800240E0(int param_1)
{
    int cVar2;
    char *ptr;
    int uVar1;
    char *stream_end;
    
    if (fs_stream_is_force_stop_8009D518 != 0)
    {
        return 0;
    }
    
    for (ptr = fs_ptr_800B52B4; ptr != fs_ptr_800B52BC;)
    {
        cVar2 = *(int*)ptr & 0xFF;
        uVar1 = *(int*)ptr;

        uVar1 >>= 8;
        
        if (cVar2 == 0xff)
        {            
            ptr = fs_stream_heap_800B52A4;
        }
        else
        {
            if (cVar2 == param_1)
            {
                *ptr = cVar2 | 0x80;
                return ptr + 4;
            }

            ptr = ptr + uVar1;

            stream_end = (char *)fs_stream_heap_800B52A4 + fs_stream_heapSize_800B52AC;
            if (ptr >= stream_end)
            {
                ptr = fs_stream_heap_800B52A4;
            }
        }
    }
    
    return 0;
}