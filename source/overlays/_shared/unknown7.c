#include "game/camera.h"

extern GM_CAMERA GM_Camera;

static int     s03b_dword_800D3318;
static SVECTOR s03b_dword_800D3320;
static SVECTOR s03b_dword_800D3328;
static SVECTOR s03b_dword_800D3330;
static SVECTOR s03b_dword_800D3338;
static GV_MSG *s03b_dword_800D3340;
static int     s03b_dword_800D3344;

int s03b_dword_800C33A0 = 0;

void s03b_800CA5DC(void)
{
    SVECTOR diff;
    SVECTOR offset;
    int     scale;
    int     len;

    if (s03b_dword_800C33A0 != 0)
    {
        scale = s03b_dword_800D3330.pad;
        if (scale < 0)
        {
            s03b_dword_800D3320 = s03b_dword_800D3330;
        }
        else
        {
            GV_SubVec3(&s03b_dword_800D3330, &s03b_dword_800D3320, &diff);
            len = GV_VecLen3(&diff);
            if (scale < len)
            {
                GV_LenVec3(&diff, &offset, len, scale);
                GV_AddVec3(&s03b_dword_800D3320, &offset, &s03b_dword_800D3320);
            }
        }

        scale = s03b_dword_800D3338.pad;
        if (scale < 0)
        {
            s03b_dword_800D3328 = s03b_dword_800D3338;
        }
        else
        {
            GV_SubVec3(&s03b_dword_800D3338, &s03b_dword_800D3328, &diff);
            len = GV_VecLen3(&diff);
            if (scale < len)
            {
                GV_LenVec3(&diff, &offset, len, scale);
                GV_AddVec3(&s03b_dword_800D3328, &offset, &s03b_dword_800D3328);
            }
        }

        GM_Camera.field_28 = 0;
        GM_Camera.eye = s03b_dword_800D3320;
        GM_Camera.center = s03b_dword_800D3328;
    }
}

void s03b_800CA794(void)
{
    if (s03b_dword_800C33A0 == 0)
    {
        GM_Camera.flags = 2;
        GM_Camera.interp = 0;
        GM_Camera.field_2A = 0;
        s03b_dword_800D3318 = GM_Camera.field_28;
        GM_SetCameraCallbackFunc_8002FD84(1, s03b_800CA5DC);
        s03b_dword_800C33A0 = 1;
    }
}

void s03b_800CA7FC(void)
{
    if (s03b_dword_800C33A0 != 0)
    {
        GM_Camera.field_2A = 2;
        GM_Camera.interp = 0;
        GM_Camera.field_28 = s03b_dword_800D3318;
        GM_Camera.flags &= ~0x2;
        GM_SetCameraCallbackFunc_8002FD84(1, NULL);
        s03b_dword_800C33A0 = 0;
    }
}

void s03b_800CA868(void)
{
    int     n_msgs;
    GV_MSG *msg;
    int     i;
    int     code;
    int     len;

    n_msgs = GV_ReceiveMessage(0xCED3, &s03b_dword_800D3340);
    s03b_dword_800D3344 = n_msgs;
    if (n_msgs == 0)
    {
        return;
    }

    msg = &s03b_dword_800D3340[n_msgs] - 1;
    for (i = n_msgs; i > 0; i--, msg--)
    {
        code = msg->message[0];
        len = msg->message_len;

        switch (code)
        {
        case 0xA3AC:
            if (len == 7)
            {
                s03b_dword_800D3330.vx = msg->message[4];
                s03b_dword_800D3330.vy = msg->message[5];
                s03b_dword_800D3330.vz = msg->message[6];

                s03b_dword_800D3338.vx = msg->message[1];
                s03b_dword_800D3338.vy = msg->message[2];
                s03b_dword_800D3338.vz = msg->message[3];
            }
            break;

        case 0xA86D:
            if (len >= 3)
            {
                s03b_dword_800D3330.pad = msg->message[1];
                s03b_dword_800D3338.pad = msg->message[2];
            }
            break;

        case HASH_START:
            s03b_800CA794();
            break;

        case 0xA225:
            s03b_800CA7FC();
            break;
        }
    }
}
