#include "game.h"
#include "linkvarbuf.h"

extern int dword_800ABA90;
int        dword_800ABA90;

extern int GM_event_camera_flag_800ABA9C;
int        GM_event_camera_flag_800ABA9C;

extern int GM_CameraTrackOrg_800AB448;
int        GM_CameraTrackOrg_800AB448;

extern HZD_TRP *GM_CameraTrackOrg_800AB444;
HZD_TRP        *GM_CameraTrackOrg_800AB444;

extern int    GM_AlertMode_800ABA00;
extern CAMERA GM_CameraList_800B7718[8];

void GM_CheckBehindCamera_80030B3C(HZD_MAP *pHzdMap, CONTROL *pControl)
{
    HZD_TRP *trp;
    CAMERA  *cam;
    short   *name;

    if ((GM_SnakeState & 0x100 || GM_AlertMode_800ABA00 != 3) &&
        (trp = HZD_CheckBehindTrap_8002A5E0(pHzdMap, pControl)) != NULL)
    {
        if (GM_CameraTrackOrg_800AB444 != trp)
        {
            if (++GM_CameraTrackOrg_800AB448 >= 10)
            {
                GM_CameraTrackOrg_800AB444 = trp;

                cam = &GM_CameraList_800B7718[3];
                cam->field_10_param1 = 1;
                cam->field_11_param2 = 2;
                cam->field_12_param3 = 0;
                cam->field_13_param_p = 2;
                cam->field_00_pos.pad = GV_GetPadOrigin_80016C84();

                name = (short *)trp->name; // TODO: Is char[] name array in HZD_TRP correct? Is it really a name?
                cam->field_08_trg[0] = name[0];
                cam->field_08_trg[1] = name[1];
                cam->field_08_trg[2] = name[2];

                GM_event_camera_flag_800ABA9C |= 8;
                dword_800ABA90 &= ~8;
                GM_GameStatus_800AB3CC |= 0x10;

                cam->field_00_pos.vx = name[3];
                cam->field_00_pos.vy = name[4];
                cam->field_00_pos.vz = name[5];
            }
        }
    }
    else
    {
        GM_ExitBehindCamera_80030AEC();
    }
}
