#include "libfs.h"
#include "mts/mts_new.h"

int FS_CdMakePositionTable_helper2_800228D4(void *pBuffer, int startSector, int sectorSize)
{
    CDBIOS_ReadRequest_8002280C(pBuffer, startSector + 150, sectorSize, 0);

    while (1)
    {
        if (CDBIOS_ReadSync_80022854() <= 0)
        {
            break;
        }
        mts_wait_vbl_800895F4(1);
    }

    return 1;
}
