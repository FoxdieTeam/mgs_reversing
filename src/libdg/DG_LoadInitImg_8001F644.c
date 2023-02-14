#include "libdg.h"

int DG_LoadInitImg_8001F644(unsigned char *pFileData, int fileNameHashed)
{
    DG_IMG *img = (DG_IMG *)pFileData;
    img->unknown2 = (unsigned char *)img + (unsigned int)img->unknown2;
    img->unknown3 = (unsigned char *)img + (unsigned int)img->unknown3;
    img->unknown4 = (unsigned char *)img + (unsigned int)img->unknown4;
    return 1;
}
