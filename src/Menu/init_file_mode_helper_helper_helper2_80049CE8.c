#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Game/linkvarbuf.h"
#include "memcard/memcard.h"
#include "Game/game.h"

extern int  GM_PadResetDisable_800AB3F4;

extern char aNoMemoryForFil[];

int init_file_mode_helper_helper_helper2_80049CE8(unsigned char *arg0, int idx)
{
    int   retval;
    int   statusFlag;
    short statusFlagTmp;
    int   offset;
    int   i;
    void *buf;
    char *pFilename;

    GM_PadResetDisable_800AB3F4 = 1;
    buf = GV_AllocMemory_80015EB8(0, 0x2000);
    if (buf == NULL)
    {
        mts_printf_8008BBA0(aNoMemoryForFil);
    }

    retval = 0;
    for (i = 4, offset = (idx * 0x1C) + 4; i > 0; i--)
    {
        pFilename = arg0 + offset;
        memcard_read_8002569C(*arg0, pFilename, 0, buf, 0x2000);

        while (memcard_get_status_800257B0() > 0)
        {
            mts_wait_vbl_800895F4(2);
        }

        if (memcard_get_status_800257B0() == 0)
        {
            statusFlagTmp = GM_GameStatusFlag & 0xF7FF;
            statusFlag = statusFlagTmp;
            if (GCL_SetLoadFile_80020EAC(buf + 0x100) != 0)
            {
                retval = 1;
                if (statusFlag & 0x10)
                {
                    GM_GameStatusFlag = (GM_GameStatusFlag & 0x1EFF) | (statusFlag & ~0x1EFF);
                }
                if (statusFlag & 8)
                {
                    GM_GameStatusFlag = (GM_GameStatusFlag & 0xEFF8) | (statusFlag & 0x1007);
                }
                GM_GameStatusFlag &= 0xFFE7;
                GCL_SaveLinkVar_80020B90(&GM_GameStatusFlag);
                if (GM_GameStatusFlag & 0x8000)
                {
                    GM_Sound_80032C48(-0xFFFFFB, 0);
                }
                else
                {
                    GM_Sound_80032C48(-0xFFFFFA, 0);
                }
            }
            break;
        }
    }

    GV_FreeMemory_80015FD0(0, buf);
    GM_PadResetDisable_800AB3F4 = 0;
    return retval;
}
