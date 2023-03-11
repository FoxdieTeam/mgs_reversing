#include "libfs.h"
#include "psyq.h"

extern int  *fs_dword_8009D520;
extern int   fs_dword_800B529C;

extern int   fs_dword_800B52A0;
extern void *fs_stream_heap_800B52A4;
extern void *fs_stream_heap_end_800B52A8;
extern int   fs_stream_heapSize_800B52AC;

extern void *fs_ptr_800B52B4;
extern int  *fs_ptr_800B52B8;
extern void *fs_ptr_800B52BC;

void sub_80023C40(void)
{
    int temp_a0;
    int var_v1;
    int* temp_v0;
    int* var_a1;
    int* var_v1_2;
    int new_var;

    if (fs_dword_8009D520 != 0)
    {
        temp_v0 = fs_dword_8009D520;

        var_v1 = (int)(fs_stream_heap_800B52A4 + (temp_v0[0] >> 8)) - (int)temp_v0;

        if (var_v1 < 0)
        {
            var_v1 += fs_stream_heapSize_800B52AC;
        }

        temp_a0 = (int)fs_ptr_800B52B4 - (int)temp_v0;

        if (temp_a0 < 0)
        {
            temp_a0 += fs_stream_heapSize_800B52AC;
        }

        if (temp_a0 < var_v1)
        {
            return;
        }

        SwEnterCriticalSection_8009954C();

        var_a1 = fs_stream_heap_800B52A4;
        var_v1_2 = temp_v0;

        while (var_v1_2 < fs_ptr_800B52B8)
        {
            *var_a1++ = *var_v1_2++;
        }

        fs_ptr_800B52B8 = var_a1;
        *temp_v0 = -1;
        fs_dword_8009D520 = 0;
        new_var = (fs_stream_heapSize_800B52AC - ((int)var_a1 - (int)fs_stream_heap_800B52A4)) & ~0x7FF;
        fs_stream_heap_end_800B52A8 = (char *)var_a1 + new_var;
        fs_ptr_800B52BC = fs_stream_heap_800B52A4;

        SwExitCriticalSection_8009956C();
    }

    fs_dword_800B529C = 1;
    CDBIOS_ReadRequest_8002280C(fs_ptr_800B52B8, fs_dword_800B52A0, 0, &sub_800239E8);
}
