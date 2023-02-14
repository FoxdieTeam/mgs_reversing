#include "libdg.h"

int DG_LoadInitOar_8001F610(unsigned char *pFileData, int fileNameHashed)
{
    DG_OAR *oar = (DG_OAR *)pFileData;
    oar->deep = oar->oarData + 2 * ((oar->recordSize + 2) * oar->count);
    oar->start = oar->oarData;
    return 1;
}
