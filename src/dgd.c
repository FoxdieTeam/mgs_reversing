#include "linker.h"
#include "dgd.h"
#include "mts_new.h"
#include "actor.h"

int DG_DrawSyncResetGraph_8001F014(void);
void DG_InitDispEnv_800170F0(int, int, int, int, int);
void DG_3OTsInit_80017B98(int);
void DG_8001F1DC(void);
void DG_ClearResidentTexture_8001DB10(void);

int pcx_file_handler_8001F920(unsigned char *pFileData, int fileNameHashed);
int kmd_file_handler_8001F4EC(unsigned char *pFileData, int fileNameHashed);
int lit_file_handler_8001F6B4(unsigned char *pFileData, int fileNameHashed);
int n_file_handler_8001F5F8(unsigned char *pFileData, int fileNameHashed);
int oar_file_handler_8001F610(unsigned char *pFileData, int fileNameHashed);
int zmd_file_handler_8001FAD0(unsigned char *pFileData, int fileNameHashed);
int img_file_handler_8001F644(unsigned char *pFileData, int fileNameHashed);
int sgt_file_handler_8001F670(unsigned char *pFileData, int fileNameHashed);

void DG_Update2_8001F078(Actor*);
void DG_Update1_8001F1BC(Actor*);


extern const char aDgdC[];

Actor SECTION(".gDgdActor2_800B3750") gDgdActor2_800B3750;
Actor SECTION(".gDgdActor2_800B3750") gDgdActor1_800B3770; // same section as its directly after

void DG_StartDaemon_8001F284(void)
{
    mts_set_vsync_task_800892B8();
    mts_800893B4(DG_DrawSyncResetGraph_8001F014); // SetVblankControlFunc_7(PrimitiveQueueEmpty_4011F8);
    DG_InitDispEnv_800170F0(0, 0, 320, 240, 320);
    DG_3OTsInit_80017B98(320);
    DG_ClearResidentTexture_8001DB10();
    DG_8001F1DC();
    GD_SetFileHandler_80015418('p', pcx_file_handler_8001F920);
    GD_SetFileHandler_80015418('k', kmd_file_handler_8001F4EC);
    GD_SetFileHandler_80015418('l', lit_file_handler_8001F6B4);
    GD_SetFileHandler_80015418('n', n_file_handler_8001F5F8);
    GD_SetFileHandler_80015418('o', oar_file_handler_8001F610);
    GD_SetFileHandler_80015418('z', zmd_file_handler_8001FAD0);
    GD_SetFileHandler_80015418('i', img_file_handler_8001F644);
    GD_SetFileHandler_80015418('s', sgt_file_handler_8001F670);

    // 2D handler?
    GV_ActorPushBack_800150a8(0, &gDgdActor2_800B3750, 0);
    GV_ActorInit_8001514c(&gDgdActor2_800B3750, DG_Update2_8001F078, 0, aDgdC);
 
    // 3D handler?
    GV_ActorPushBack_800150a8(8, &gDgdActor1_800B3770, 0);
    GV_ActorInit_8001514c(&gDgdActor1_800B3770, DG_Update1_8001F1BC, 0, aDgdC);
}
