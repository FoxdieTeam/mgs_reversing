#include "libdg.h"

int DG_LoadInitNar_8001F5F8(unsigned char *pFileData, int fileNameHashed)
{
  NFile *n = (NFile *)pFileData;
  n->unknown1 = (unsigned char *)n + (unsigned int)n->unknown1;
  return 1;
}
