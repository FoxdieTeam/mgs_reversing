#ifndef _DGD_H
#define _DGD_H

void DG_StartDaemon_8001F284(void);

typedef int (*TFileExtHandler)(unsigned char *pFileData, int fileNameHashed);

void GV_SetFileHandler_80015418(int fileExtChar, TFileExtHandler pFn);

#endif // _DGD_H
