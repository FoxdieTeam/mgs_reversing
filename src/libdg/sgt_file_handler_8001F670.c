#include "libdg.h"

int sgt_file_handler_8001F670(unsigned char *pFileData, int fileNameHashed)
{
  SgtFile *sgt = (SgtFile *)pFileData;
  sgt->unknown1 = (unsigned char *)sgt + (unsigned int)sgt->unknown1;
  sgt->unknown2 = (unsigned char *)sgt + (unsigned int)sgt->unknown2;
  sgt->unknown3 = (unsigned char *)sgt + (unsigned int)sgt->unknown3;
  sgt->unknown4 = (unsigned char *)sgt + (unsigned int)sgt->unknown4;
  sgt->unknown5 = (unsigned char *)sgt + (unsigned int)sgt->unknown5;
  return 1;
}
