#include "libfs.h"

extern void *fs_stream_heap_800B52A4;
extern int   fs_stream_heapSize_800B52AC;
extern void *fs_ptr_800B52B4;
extern void *fs_ptr_800B52B8;
extern void *fs_ptr_800B52BC;

extern const char aNowDataTopXLoa[]; // = "now_data_top %X loaded_header %X\n"
extern const char aTickD[];          // = "Tick %d\n"
extern const char a08xTypeXSizeDT[]; // = "%08X TYPE %X size %d time %d\n"
extern const char a08xTypeXSizeD[];  // = "%08X TYPE %X size %d\n"

void sub_800242A4(void)
{
    char *ptr;
    int type;
    int size;

    ptr = fs_ptr_800B52B4;

    mts_printf_8008BBA0(aNowDataTopXLoa, ptr, fs_ptr_800B52BC);
    mts_printf_8008BBA0(aTickD, FS_StreamGetTick_80024420());

    while (ptr != fs_ptr_800B52BC)
    {
        type = *(int *)ptr & 0xFF;
        size = *(int *)ptr >> 8;

        if (type == 0xFF)
        {
            ptr = fs_stream_heap_800B52A4;
        }
        else
        {
            if (type == 5)
            {
                mts_printf_8008BBA0(a08xTypeXSizeDT, ptr, 5, size, *(int *)(ptr + 4));
            }
            else
            {
                mts_printf_8008BBA0(a08xTypeXSizeD, ptr, type, size);
            }

            ptr += size;

            if (ptr == (fs_stream_heap_800B52A4 + fs_stream_heapSize_800B52AC))
            {
                ptr = fs_stream_heap_800B52A4;
            }
        }
    }
}
