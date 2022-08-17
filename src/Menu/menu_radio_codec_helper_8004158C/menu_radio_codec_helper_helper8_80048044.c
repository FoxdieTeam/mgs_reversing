#include "mts/mts_new.h"

int *dword_800ABB38;

void menu_radio_codec_helper_helper8_80048044(void)
{
    if (mts_get_task_status_8008B618(6))
    {
        mts_wup_tsk_8008A540(6);
        *dword_800ABB38 = 0;
    }
}
