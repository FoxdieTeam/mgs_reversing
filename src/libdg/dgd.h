#ifndef _DGD_H
#define _DGD_H

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct
{
    unsigned char *mOrderingTables[2]; // 257 pointers? // One for each active buffer
    short word_6BC374_8;
    short word_6BC376_16;
    short word_6BC378_1;
    short word_6BC37A_0_1EC_size;
    MATRIX field_10_matrix;
    MATRIX dword_6BC39C;
    short word_6BC3BC; // Camera number?
    short mTotalQueueSize;
    short mFreePrimCount;
    short mTotalObjectCount;
    void **mQueue;
    RECT dword_6BC3C8_pStructure_rect;
    RECT dword_6BC3D0_rect;
    int dword_6BC3D8_dst[16]; // One for each active buffer
    int dword_6BC418_dst[16];
    int dword_6BC458[16];
    int dword_6BC498[16];
    DR_ENV dword_6BC4D8_src_dr_env1;
    DR_ENV dword_6BC518_src_offsetted_dr_evn;
} struct_dg;

void DG_StartDaemon_8001F284(void);

typedef int (*TFileExtHandler)(unsigned char *pFileData, int fileNameHashed);

void GV_SetFileHandler_80015418(int fileExtChar, TFileExtHandler pFn);

#endif // _DGD_H
