#include "libgcl/hash.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/camera.h"
#include "intr_cam.h"

typedef struct IntrCamWork
{
    GV_ACT  actor;
    int     field_20;
    int     field_24;
    int     field_28;
    SVECTOR field_2C;
    SVECTOR field_34;
} IntrCamWork;

const char s03e_dword_800CBFD0[] = "intr_cam.c";

extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern UnkCameraStruct  gUnkCameraStruct_800B77B8;

void IntrCam_800C5548(IntrCamWork *work)
{
    GV_MSG *msgs;
    int     count;

    count = GV_ReceiveMessage(work->field_20, &msgs);
    if (count <= 0)
    {
        return;
    }

    while (--count >= 0)
    {
        switch (msgs->message[0])
        {
        case HASH_KILL:
            work->field_24 = 3;
            break;

        case HASH_ON:
            work->field_24 = 1;
            work->field_34 = gUnkCameraStruct_800B77B8.field_0;
            break;

        case HASH_OFF:
            work->field_24 = 2;
            break;
        }
        msgs++;
    }
}

void IntrCam_Act_800C5638(IntrCamWork *work)
{
    int field_28;

    IntrCam_800C5548(work);
    if (!(GM_PlayerStatus_800ABA50 & PLAYER_INTRUDE))
    {
        work->field_28 = 8;
        return;
    }

    if (work->field_24 >= 2)
    {
        if (work->field_24 == 3)
        {
            GV_DestroyActor(&work->actor);
        }
        work->field_28 = 8;
        return;
    }

    field_28 = work->field_28;
    if (work->field_28 > 0)
    {
        work->field_28--;
    }
    GV_NearTimeSV(&work->field_34.vx, &work->field_2C.vx, field_28, 3);
    gUnkCameraStruct_800B77B8.field_0 = work->field_34;
}

void IntrCam_Die_800C56F0(IntrCamWork *work)
{
}

int IntrCam_GetResources_800C56F8(IntrCamWork *work)
{
    GCL_GetOption('p');
    GCL_StrToSV(GCL_GetParamResult(), &work->field_2C);
    work->field_24 = 2;
    work->field_28 = 8;
    return 0;
}

GV_ACT *NewIntrCam_800C5748(int name, int where, int argc, char **argv)
{
    IntrCamWork *work;

    work = (IntrCamWork *)GV_NewActor(7, sizeof(IntrCamWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)IntrCam_Act_800C5638,
                         (TActorFunction)IntrCam_Die_800C56F0, s03e_dword_800CBFD0);
        if (IntrCam_GetResources_800C56F8(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        work->field_20 = name;
    }
    return &work->actor;
}
