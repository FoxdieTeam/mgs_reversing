#include "libfs/libfs.h"

int menu_radio_codec_helper_helper9_80047FF4()
{
    int iVar1;

    iVar1 = FS_LoadFileSync_80021F48();
    if (iVar1 >= 1)
    {
        return iVar1;
    }

    return 0;
}
