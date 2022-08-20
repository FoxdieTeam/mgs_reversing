#include "libfs.h"

extern int fs_stream_tick_start_8009D510;
extern int fs_dword_8009D514;
extern int fs_stream_is_force_stop_8009D518;
extern int fs_stream_end_flag_8009D51C;
extern int fs_dword_8009D520;
extern int gmem_card_system_inited_8009D524;

extern int   fs_dword_800B52A0;
extern void *fs_stream_heap_800B52A4;

extern void *fs_ptr_800B52B4;
extern void *fs_ptr_800B52B8;
extern void *fs_ptr_800B52BC;

extern int   fs_stream_task_state_800B52C0;

void FS_StreamTaskStart_80023D94(int param_1)
{    
    fs_stream_end_flag_8009D51C = 0;
    fs_stream_is_force_stop_8009D518 = 0;

    fs_dword_800B52A0 = param_1;

    fs_stream_tick_start_8009D510 = -1;
    
    fs_dword_8009D514 = 0;
    fs_dword_8009D520 = 0;

    fs_stream_task_state_800B52C0 = -1;

    fs_ptr_800B52B4 = fs_stream_heap_800B52A4;
    fs_ptr_800B52BC = fs_stream_heap_800B52A4;
    fs_ptr_800B52B8 = fs_stream_heap_800B52A4;

    sub_80023C40();
}
