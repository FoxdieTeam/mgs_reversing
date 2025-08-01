#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "game/camera.h"
#include "chara/snake/sna_init.h"

typedef struct WakeWork
{
    GV_ACT  actor;
    SVECTOR field_20;
    SVECTOR player_pos;
    SVECTOR field_30;
    SVECTOR field_38;
    GV_PAD *pad;
    int     unused1;
    int     unused2;
    int     where;
} WakeWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

extern GM_Camera        GM_Camera_800B77E8;
extern UnkCameraStruct  gUnkCameraStruct_800B77B8;

void WakePollMessages_800C5D78(WakeWork *work)
{
    GV_MSG *message;
    int     count;

    count = GV_ReceiveMessage(work->where, &message);
    if (count > 0)
    {
        for (count--; count >= 0; count--, message++)
        {
            if (message->message[0] == 0x7E11 && message->message_len >= 4)
            {
                work->field_38.vx = message->message[1];
                work->field_38.vy = message->message[2];
                work->field_38.vz = message->message[3];
            }
        }
    }
}

// Modified s03b_torture_800C3F7C
int Wake_800C5E24(GV_PAD *pad)
{
    char *analog;
    int   i;
    char  adjust;

    if (pad->analog == 0)
    {
        return 0;
    }

    if (!(pad->status & (PAD_LEFT | PAD_DOWN | PAD_RIGHT | PAD_UP)))
    {
        return 0;
    }

    analog = &pad->left_dx;
    for (i = 0; i < 2; i++)
    {
        adjust = *analog - 64;
        if (adjust > 128)
        {
            return 1;
        }

        analog++;
    }

    return 0;
}

void WakeCheckPad_800C5E8C(WakeWork *work)
{
    short         status;
    unsigned char left_dy;
    GV_PAD       *pad, *pad2;
    int           coord;

    pad = work->pad;
    status = pad->status;

    pad2 = work->pad;
    left_dy = pad2->left_dy;

    GM_CheckShukanReverse(&status);
    GM_CheckShukanReverseAnalog(&left_dy);

    if (Wake_800C5E24(pad))
    {
        coord = work->field_38.vx;
        if (status & PAD_UP)
        {
            coord -= work->field_20.vx * ((64 - left_dy) & 0xFF) / 64;
        }
        else if (status & PAD_DOWN)
        {
            coord += work->field_20.vy * ((left_dy + 64) & 0xFF) / 64;
        }
        work->field_30.vx = coord;

        coord = work->field_38.vy;
        if (status & PAD_LEFT)
        {
            coord += work->field_20.vz * ((64 - pad->left_dx) & 0xFF) / 64;
        }
        else if (status & PAD_RIGHT)
        {
            coord -= work->field_20.pad * ((pad->left_dx + 64) & 0xFF) / 64;
        }
        work->field_30.vy = coord;
    }
    else
    {
        coord = work->field_38.vx;
        if (status & PAD_UP)
        {
            coord -= work->field_20.vx;
        }
        else if (status & PAD_DOWN)
        {
            coord += work->field_20.vy;
        }
        work->field_30.vx = coord;

        coord = work->field_38.vy;
        if (status & PAD_LEFT)
        {
            coord += work->field_20.vz;
        }
        else if (status & PAD_RIGHT)
        {
            coord -= work->field_20.pad;
        }
        work->field_30.vy = coord;
    }

    if (work->field_30.vx < -1000)
    {
        work->field_30.vx = -1000;
    }

    GV_NearExp4PV(&gUnkCameraStruct_800B77B8.rotate2.vx, &work->field_30.vx, 3);
    gUnkCameraStruct_800B77B8.eye = work->player_pos;
}

void WakeAct_800C60BC(WakeWork *work)
{
    if (GM_PlayerStatus & PLAYER_SECOND_CONTROLLER)
    {
        work->pad = &GV_PadData[1];
    }
    else
    {
        work->pad = &GV_PadData[0];
    }
    WakePollMessages_800C5D78(work);
    WakeCheckPad_800C5E8C(work);
    GM_PlayerPosition = work->player_pos;
}

void WakeDie_800C6140(WakeWork *work)
{
    GM_PlayerStatus &= ~PLAYER_MENU_DISABLE;
}

int WakeGetResources_800C615C(WakeWork *work, int where)
{
    if (!GCL_GetOption('b'))
    {
        return -1;
    }
    work->field_20.vx = GCL_StrToInt(GCL_GetParamResult());
    work->field_20.vy = GCL_StrToInt(GCL_GetParamResult());
    work->field_20.vz = GCL_StrToInt(GCL_GetParamResult());
    work->field_20.pad = GCL_StrToInt(GCL_GetParamResult());

    if (!GCL_GetOption('p'))
    {
        return -1;
    }
    GCL_StrToSV(GCL_GetParamResult(), &work->player_pos);

    if (!GCL_GetOption('d'))
    {
        return -1;
    }

    GCL_StrToSV(GCL_GetParamResult(), &work->field_30);
    work->field_38 = work->field_30;

    work->unused1 = 0;
    work->unused2 = 0;
    work->where = where;

    GM_Camera_800B77E8.first_person = 2;
    gUnkCameraStruct_800B77B8.rotate2 = work->field_30;

    GM_PlayerStatus |= PLAYER_MENU_DISABLE;

    return 0;
}

void *NewWake_800C6298(int where)
{
    WakeWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(WakeWork));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, WakeAct_800C60BC, WakeDie_800C6140, "wake.c");

    if (WakeGetResources_800C615C(work, where) < 0)
    {
        GV_DestroyActor(&work->actor);
        return NULL;
    }

    return (void *)work;
}
