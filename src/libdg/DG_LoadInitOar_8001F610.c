#include "libdg.h"

int DG_LoadInitOar_8001F610(unsigned char *pFileData, int fileNameHashed)
{
    OarFile *oar = (OarFile *)pFileData;
    oar->deep = oar->oarData + 2 * ((oar->recordSize + 2) * oar->count);
    oar->start = oar->oarData;
    return 1;
}
