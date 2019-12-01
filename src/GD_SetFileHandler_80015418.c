#include "linker.h"

typedef int (*TFileExtHandler)(unsigned char *pFileData, int fileNameHashed);

#define MAX_FILE_HANDLERS 26

TFileExtHandler SECTION(".gFileExtHandlers_800ACE80") gFileExtHandlers_800ACE80[MAX_FILE_HANDLERS];

void GD_SetFileHandler_80015418(int fileExtChar, TFileExtHandler pFn)
{
  const int idx = fileExtChar - 'a';
  gFileExtHandlers_800ACE80[idx] = pFn;
}

void GD_ClearFileHandlers_80015434(void)
{
  TFileExtHandler *pExtIter;
  int i;

  pExtIter = &gFileExtHandlers_800ACE80[0];
  for (i = MAX_FILE_HANDLERS; i > 0; i--)
  {
    *pExtIter = 0;
    pExtIter++;
  }
}
