#include "libgv/libgv.h"

typedef struct CameraWork
{
    GV_ACT actor;
    char   padding[0x49C8];
} CameraWork;

extern const char camera_aCamerac_800D06A4[]; // = "camera.c";

extern int GM_GameStatus_800AB3CC;

void CameraAct_800CE404();
void CameraDie_800CE470();
int  camera_800CE6EC(CameraWork *work, int where);

GV_ACT *NewCamera_800CF388(int name, int where, int argc, char **argv)
{
    CameraWork *work;

    GM_GameStatus_800AB3CC |= 0x4A6000;
    work = (CameraWork *)GV_NewActor_800150E4(1, sizeof(CameraWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, CameraAct_800CE404, CameraDie_800CE470, camera_aCamerac_800D06A4);
        if (camera_800CE6EC(work, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
