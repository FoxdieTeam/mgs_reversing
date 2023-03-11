#include "libfs.h"

extern int   fs_stream_is_force_stop_8009D518;
extern void *fs_stream_heap_800B52A4;
extern int   fs_stream_heapSize_800B52AC;
extern void *fs_ptr_800B52B4;
extern void *fs_ptr_800B52BC;

extern const char aClearX[]; // = "clear %X\n"

void sub_800241C8(char *arg0, int arg1)
{
    char *ptr;
    char *ptr2;
    int size;
    int type;

    if (fs_stream_is_force_stop_8009D518 != 0)
    {
        return;
    }

    ptr = fs_ptr_800B52B4;
    ptr2 = arg0 - 4;

    while ((ptr != ptr2) && (ptr != fs_ptr_800B52BC))
    {
        size = *(int *)ptr >> 8;
        type = *(int *)ptr & 0xF;

        if (type == arg1)
        {
            ptr[0] = 0;
            mts_printf_8008BBA0(aClearX, size);
        }

        ptr += size;

        if (ptr == (fs_stream_heap_800B52A4 + fs_stream_heapSize_800B52AC))
        {
            ptr = fs_stream_heap_800B52A4;
        }
    }
}