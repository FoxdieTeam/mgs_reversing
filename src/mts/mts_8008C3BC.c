

#include "idaTypes.h"

extern int              dword_800A3DC8;
extern unsigned char    gMtsPadSendBuffers_800C14D0[2];

extern void*            memset_8008E688(void *pSrc, int value, int len);

int mts_8008C3BC(int arg0)
{
    int ret;

    ret = dword_800A3DC8;
    if (arg0 >= 0)
    {
        dword_800A3DC8 = arg0;
    }
    memset_8008E688(gMtsPadSendBuffers_800C14D0, 0, 0x10);
    return ret;
}
