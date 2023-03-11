#include "libfs.h"

extern int          fs_stream_end_flag_8009D51C;
extern int          fs_dword_800B529C;
extern int          fs_stream_is_force_stop_8009D518;
extern unsigned int fs_stream_task_state_800B52C0;
extern void        *fs_dword_800B52B0;
extern void        *fs_stream_heap_800B52A4;
extern void        *fs_ptr_800B52B4;
extern void        *fs_ptr_800B52B8;
extern void        *fs_ptr_800B52BC;
extern int          fs_stream_heapSize_800B52AC;

int FS_StreamSync_80023E24(void)
{
    int temp_t2;
    int temp_t3;
    int temp_v0;
    int temp_v1_2;
    int var_a0_2;
    char *var_a0;

    temp_t2 = fs_dword_800B529C;
    temp_t3 = fs_stream_end_flag_8009D51C;

    if ((temp_t3 != 0) || (fs_stream_is_force_stop_8009D518 != 0))
    {
        fs_stream_task_state_800B52C0 = 0;
        return 0;
    }

    if (fs_stream_task_state_800B52C0 == -1)
    {
        if (temp_t2 == 1)
        {
            return 1;
        }

        fs_stream_task_state_800B52C0 = 1;
        fs_dword_800B52B0 = fs_stream_heap_800B52A4;
    }

    var_a0 = fs_ptr_800B52B4;

    while (var_a0 != fs_ptr_800B52BC)
    {
        temp_v0 = *(int *)var_a0;
        temp_v1_2 = temp_v0 & 0xFF;
        temp_v0 >>= 8;

        if (temp_v1_2 == 0xFF)
        {
            var_a0 = fs_stream_heap_800B52A4;
        }
        else if (temp_v1_2 == 0)
        {
            var_a0 += temp_v0;

            if (var_a0 == (fs_stream_heap_800B52A4 + fs_stream_heapSize_800B52AC))
            {
                var_a0 = fs_stream_heap_800B52A4;
            }
        }
        else
        {
            break;
        }
    }

    fs_ptr_800B52B4 = var_a0;

    if (temp_t2 == 0)
    {
        if (temp_t3 == 0)
        {
            var_a0_2 = (char *)fs_ptr_800B52B8 - var_a0;

            if (var_a0_2 < 0)
            {
                var_a0_2 += fs_stream_heapSize_800B52AC;
            }

            if (var_a0_2 < ((fs_stream_heapSize_800B52AC * 2) / 3))
            {
                sub_80023C40();
            }
        }
    }

    return 1;
}
