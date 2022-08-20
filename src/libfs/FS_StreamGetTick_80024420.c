#include "SD/sd.h"
#include "mts/mts_new.h"

extern int fs_stream_tick_start_8009D510;
extern int fs_dword_8009D514;

int FS_StreamGetTick_80024420(void)
{
    int current = mts_get_tick_count_8008BBB0();
    int iVar2;
  
    if (fs_dword_8009D514 != 0)
    {
        iVar2 = get_str_counter_80088CA0();
    
        if (iVar2 < 0)
        {
            if (fs_stream_tick_start_8009D510 < 0)
            {
                return -1;
            }

            return current - fs_stream_tick_start_8009D510 + fs_dword_8009D514;
        }

        fs_stream_tick_start_8009D510 = current;
        fs_dword_8009D514 = (iVar2 * 64) / 105 + 1;
        return (iVar2 * 64) / 105 + 1;
    }

    return current - fs_stream_tick_start_8009D510; 
}
