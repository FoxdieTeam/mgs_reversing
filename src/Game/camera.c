#include "camera.h"
#include "linkvarbuf.h"
#include "libgcl/hash.h"

extern int GM_event_camera_flag_800ABA9C;
int SECTION(".sbss") GM_event_camera_flag_800ABA9C;

extern int dword_800ABA90;
int SECTION(".sbss") dword_800ABA90;

extern int dword_800ABA94;
int SECTION(".sbss") dword_800ABA94;

extern int GM_CameraShakeOffset_800ABA98;
int SECTION(".sbss") GM_CameraShakeOffset_800ABA98;

int      GM_CameraTrackSave_800AB42C = 10000;
SVECTOR  GM_CameraRotateSave_800AB430 = { 640, 2048, 0, 0 };
int      GM_CameraTrackOrg_800AB438 = 10000;
int      GM_800AB43C = 0;
int      GM_CameraFlagsOrg_800AB440 = 0;    /* static */
HZD_TRP *GM_800AB444 = NULL;
int      GM_800AB448 = 0;


extern SVECTOR          svec_800ABA88;
SVECTOR                 svec_800ABA88; // gp

extern int              GV_PauseLevel_800AB928;
extern GM_Camera        GM_Camera_800B77E8;
extern UnkCameraStruct  gUnkCameraStruct_800B77B8;
extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;
extern UnkCameraStruct2 gUnkCameraStruct2_800B76F0;
extern int              DG_UnDrawFrameCount_800AB380;
extern int              GV_Time_800AB330;
extern int              GM_AlertMode_800ABA00;
extern int              GM_GameStatus_800AB3CC;
extern CAMERA           GM_CameraList_800B7718[8];
extern int              GM_NoisePower_800ABA24;
extern int              GM_NoiseLength_800ABA30;

static const unsigned int dword_80010C60[] =
{
    0,
    0x1E0001,
    0x1E0002,
    0x1E0003,
    0x140003,
    0xA0003,
    0x50003,
    0x30003
};


/*
Camera Attributes:
 FLY: SVECTOR;
 TRG: SVECTOR;
 ROT: SVECTOR;
 TRK: INT;
 POS: INT;
 ANG: SHORT?
 TYPE: UNSIGNED INT (FLAG);
*/

static inline int camera_clamp(int val, int min, int max)
{
    if (val < min)
    {
        val = min;
    }

    if (val > max)
    {
        val = max;
    }

    return val;
}

void sub_8002EADC(int index)
{
    SVECTOR *pBase;
    SVECTOR *pVec;

    pBase = (SVECTOR *)&GM_Camera_800B77E8;
    pVec = pBase + index;

    GM_Camera_800B77E8.eye.vx = camera_clamp(GM_Camera_800B77E8.eye.vx, pVec[8].vz,  pVec[6].vz);
    GM_Camera_800B77E8.eye.vy = camera_clamp(GM_Camera_800B77E8.eye.vy, pVec[8].pad, pVec[6].pad);
    GM_Camera_800B77E8.eye.vz = camera_clamp(GM_Camera_800B77E8.eye.vz, pVec[9].vx,  pVec[7].vx);
}

void sub_8002EB80(SVECTOR *vec_1, SVECTOR *vec_2)
{
    int iVar1;

    iVar1 = sub_80026440((int)vec_1->vx, (int)vec_2->vx, 500);
    vec_1->vx = (short)iVar1;
    iVar1 = sub_80026440((int)vec_1->vz, (int)vec_2->vz, 500);
    vec_1->vz = (short)iVar1;
    iVar1 = sub_80026440((int)vec_1->vy, (int)vec_2->vy, 0x96);

    vec_1->vy = (short)iVar1;
}

void sub_8002EBE8(SVECTOR *arg0, int index)
{
    SVECTOR *pBase;
    SVECTOR *pVec;

    pBase = (SVECTOR *)&GM_Camera_800B77E8;
    pVec = pBase + index;

    arg0->vx = camera_clamp(arg0->vx, pVec[12].vz, pVec[10].vz);
    arg0->vy = camera_clamp(arg0->vy, pVec[12].pad, pVec[10].pad);
    arg0->vz = camera_clamp(arg0->vz, pVec[13].vx, pVec[11].vx);

}

void sub_8002EC8C(SVECTOR *a1, SVECTOR *a2, SVECTOR *a3)
{
    short *a;
    short *b;
    short *out;
    int i;
    int sum;
    int clamped;

    a = (short *)a1;
    b = (short *)a2;
    out = (short *)a3;

    for (i = 0; i < 3; i++, a++, b++, out++)
    {
        sum = *a + *b;

        if (sum != (short)sum)
        {
            if (sum < 0)
            {
                clamped = 0x8000;
            }
            else
            {
                clamped = 0x7FFF;
            }

            sum = clamped;
        }

        *out = sum;
    }
}

void sub_8002ECE4(SVECTOR *a, SVECTOR *b, SVECTOR *c)
{
    short *av;
    short *bv;
    short *cv;

    int i;
    int diff;
    int clamp;

    av = (short *)a;
    bv = (short *)b;
    cv = (short *)c;

    for (i = 0; i < 3; i++, av++, bv++, cv++)
    {
        diff = *av - *bv;

        if (diff != (short)diff)
        {
            if (diff < 0)
            {
                clamp = 0x8000;
            }
            else
            {
                clamp = 0x7FFF;
            }

            diff = clamp;
        }

        *cv = diff;
    }
}

// move to camera.h when it exists?
static inline int CheckFlag(int mask)
{
    return GM_Camera_800B77E8.flags & mask;
}

int camera_act_helper3_helper_8002ED3C(void)
{
    int uVar1;
    int uVar2;

    uVar2 = 0x20;
    uVar1 = CheckFlag(uVar2);
    while (uVar1)
    {
        uVar2 >>= 1;
        uVar1 = CheckFlag(uVar2);
    }
    return uVar1;
}

void sub_8002ED68(int arg0)
{
    switch (gUnkCameraStruct2_800B76F0.eye.pad & 3)
    {
    case 0:
        GV_OriginPadSystem(0);
        return;

    case 1:
        if (arg0 != 0)
        {
            camera_get_euler_angles_8002FBC0(&GM_Camera_800B77E8.eye, &GM_Camera_800B77E8.center, &gUnkCameraStruct2_800B76F0.rotate, &gUnkCameraStruct2_800B76F0.track);
        }

        GV_OriginPadSystem(gUnkCameraStruct2_800B76F0.rotate.vy + 2048);
        break;

    case 2:
        GV_OriginPadSystem(gUnkCameraStruct2_800B76F0.eye.pad >> 2);
        break;

    default:
        break;
    }
}

void sub_8002EE04()
{
    GM_Camera_800B77E8.eye = gUnkCameraStruct2_800B76F0.eye;
    GM_Camera_800B77E8.center = gUnkCameraStruct2_800B76F0.center;
    GM_Camera_800B77E8.field_28 = 0;
    sub_8002ED68(0);
}

void sub_8002EE80(void)
{
    gUnkCameraStruct2_800B76F0.center.vz = gUnkCameraStruct_800B77B8.center.vz;
    GM_Camera_800B77E8.eye = gUnkCameraStruct2_800B76F0.eye;
    GM_Camera_800B77E8.center = gUnkCameraStruct2_800B76F0.center;
    GM_Camera_800B77E8.field_28 = 0;
    GV_OriginPadSystem(0);
}

void sub_8002EF08()
{
    GM_Camera_800B77E8.eye = gUnkCameraStruct2_800B76F0.eye;
    GM_Camera_800B77E8.center = gUnkCameraStruct_800B77B8.center;
    GM_Camera_800B77E8.field_28 = 0;
    sub_8002ED68(1);
}

void sub_8002EF88()
{
    int unused[2]; (void)unused;
    GM_Camera_800B77E8.center = gUnkCameraStruct_800B77B8.center;
    GM_Camera_800B77E8.track = gUnkCameraStruct_800B77B8.track;
    GM_Camera_800B77E8.rotate = gUnkCameraStruct_800B77B8.rotate;
    GM_Camera_800B77E8.field_28 = 2;
    GV_OriginPadSystem(0);
}

void camera_act_helper_helper_8002F008()
{
    GM_Camera_800B77E8.eye = gUnkCameraStruct_800B77B8.eye;
    GM_Camera_800B77E8.track = 1000;
    GM_Camera_800B77E8.rotate = gUnkCameraStruct_800B77B8.rotate2;
    GM_Camera_800B77E8.field_28 = 1;
    GV_OriginPadSystem(gUnkCameraStruct_800B77B8.rotate2.vy + 2048);
}

void camera_act_helper_helper2_8002F094(int param_1)
{
    int iVar1;
    SVECTOR vec;

    if (param_1 < 6)
    {
        GV_NearExp4V(&GM_Camera_800B77E8.center.vx, &gUnkCameraStruct_800B77B8.eye.vx, 3);
        GV_NearExp4PV(&GM_Camera_800B77E8.rotate.vx, &gUnkCameraStruct_800B77B8.rotate2.vx, 3);
        GM_Camera_800B77E8.track = GV_NearExp4_800263B0(GM_Camera_800B77E8.track, 1000);
        GV_DirVec3(&GM_Camera_800B77E8.rotate, GM_Camera_800B77E8.track, &vec);
        sub_8002ECE4(&GM_Camera_800B77E8.center, &vec, &GM_Camera_800B77E8.eye);
        GM_Camera_800B77E8.field_28 = 0;
    }
    else
    {
        iVar1 = 12 - param_1;
        GV_NearTimeSV(&GM_Camera_800B77E8.eye.vx, &gUnkCameraStruct_800B77B8.eye.vx, iVar1, 3);
        GV_NearTimePV(&GM_Camera_800B77E8.rotate.vx, &gUnkCameraStruct_800B77B8.rotate2.vx, iVar1, 3);
        GM_Camera_800B77E8.track = GV_NearTime_800264B0(GM_Camera_800B77E8.track, 1000, iVar1);
        GV_DirVec3(&GM_Camera_800B77E8.rotate, GM_Camera_800B77E8.track, &vec);
        sub_8002EC8C(&GM_Camera_800B77E8.eye, &vec, &GM_Camera_800B77E8.center);
        GM_Camera_800B77E8.field_28 = 0;
    }

    GV_OriginPadSystem(0);
}

void camera_act_helper_8002F1C8(void)
{
    if (GM_Camera_800B77E8.flags & 0x100)
    {
        if (gUnkCameraStruct_800B77B8.interp >= 12)
        {
            GM_Camera_800B77E8.flags &= ~0x101;
        }

        camera_act_helper_helper2_8002F094(gUnkCameraStruct_800B77B8.interp);
    }
    else if (GM_Camera_800B77E8.flags & 0x200)
    {
        if (GM_Camera_800B77E8.callbacks[0])
        {
            GM_Camera_800B77E8.callbacks[0]();
        }
    }
    else
    {
        camera_act_helper_helper_8002F008();
    }

    gUnkCameraStruct_800B77B8.interp++;
}

int sub_8002F274(void)
{
    if (GM_Camera_800B77E8.pan.pad == 1)
    {
        GV_AddVec3(&gUnkCameraStruct_800B77B8.eye, &GM_Camera_800B77E8.pan, &gUnkCameraStruct_800B77B8.eye);
        GM_Camera_800B77E8.pan.pad = 0;
    }

    sub_800303E0(&gUnkCameraStruct_800B77B8.center);

    if (GM_Camera_800B77E8.flags & 0x20)
    {
        sub_8002EF88();
        return 2;
    }

    else if (GM_Camera_800B77E8.flags & 0x10)
    {
        sub_8002EE04();
    }
    else if (GM_Camera_800B77E8.flags & 8)
    {
        sub_8002EE80();
    }
    else if (GM_Camera_800B77E8.flags & 4)
    {
        sub_8002EF08();
    }
    else if (GM_Camera_800B77E8.flags & 2)
    {
        if (GM_Camera_800B77E8.callbacks[1])
        {
            GM_Camera_800B77E8.callbacks[1]();
        }

        if ((GM_Camera_800B77E8.flags & 0x80))
        {
            return 1;
        }
        else if (GM_Camera_800B77E8.flags & 0x40)
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        sub_8002EF88();
        return 1;
    }

    return 0;

}

int camera_act_helper2_helper_8002F384(int arg0)
{
    SVECTOR vec;
    SVECTOR vec2;

    int temp_s3;
    int temp_v0;
    int var_s7;

    int (*var_s4)(int, int);
    void (*var_s5)(short *, short *, int);
    void (*var_s6)(short *, short *, int);

    var_s7 = 0;

    if (arg0 < 2)
    {
        GV_NearTimeSV(&GM_Camera_800B77E8.center.vx, &gUnkCameraStruct_800B77B8.eye.vx, 2 - arg0, 3);
        GV_NearTimePV(&GM_Camera_800B77E8.rotate.vx, &gUnkCameraStruct_800B77B8.rotate2.vx, 2 - arg0, 3);
        GM_Camera_800B77E8.track = GV_NearTime(GM_Camera_800B77E8.track, 1000, 2 - arg0);
        GV_OriginPadSystem(0);
    }
    else
    {
        if (arg0 < 4)
        {
            var_s5 = &GV_NearExp4V;
            var_s6 = &GV_NearExp4PV;
            var_s4 = &GV_NearExp4;
        }
        else
        {
            var_s5 = &GV_NearExp2V;
            var_s6 = &GV_NearExp2PV;
            var_s4 = &GV_NearExp2;
        }

        vec = GM_Camera_800B77E8.center;
        vec2 = GM_Camera_800B77E8.rotate;

        temp_s3 = GM_Camera_800B77E8.track;
        var_s7 = sub_8002F274();

        switch (GM_Camera_800B77E8.field_28)
        {
        case 0:
            camera_get_euler_angles_8002FBC0(&GM_Camera_800B77E8.eye, &GM_Camera_800B77E8.center, &GM_Camera_800B77E8.rotate, &GM_Camera_800B77E8.track);
            break;

        case 1:
            sub_8002FC58(&GM_Camera_800B77E8.eye, &GM_Camera_800B77E8.center, &GM_Camera_800B77E8.rotate, &GM_Camera_800B77E8.track);
            break;
        }

        var_s5(&vec.vx, &GM_Camera_800B77E8.center.vx, 3);
        var_s6(&vec2.vx, &GM_Camera_800B77E8.rotate.vx, 3);

        temp_v0 = var_s4(temp_s3, GM_Camera_800B77E8.track);

        GM_Camera_800B77E8.center = vec;
        GM_Camera_800B77E8.rotate = vec2;
        GM_Camera_800B77E8.track = temp_v0;
    }

    GM_Camera_800B77E8.field_28 = 2;
    temp_s3 = var_s7;

    return temp_s3;
}

int camera_act_helper2_8002F5C4(void)
{
    int ret;

    if (GM_Camera_800B77E8.flags & 1)
    {
        if (gUnkCameraStruct_800B77B8.interp >= 12)
        {
            GM_Camera_800B77E8.flags &= ~0x101;
            GM_Camera_800B77E8.interp = -1;
            GM_Camera_800B77E8.field_2A = 0;
        }

        ret = camera_act_helper2_helper_8002F384(gUnkCameraStruct_800B77B8.interp);
        gUnkCameraStruct_800B77B8.interp++;

        return ret;
    }

    return sub_8002F274();
}

void camera_act_helper3_8002F64C(void)
{
    if (GM_Camera_800B77E8.first_person != GM_800AB43C)
    {
        gUnkCameraStruct_800B77B8.interp = 0;
        GM_Camera_800B77E8.field_2A = 0;

        if (GM_Camera_800B77E8.first_person == 0)
        {
            GM_Camera_800B77E8.flags |= 1;
            sub_8002FAAC(&GM_Camera_800B77E8.eye, &GM_Camera_800B77E8.center, &GM_Camera_800B77E8.rotate, &GM_Camera_800B77E8.track);
        }
        else if (GM_Camera_800B77E8.first_person == 1)
        {
            GM_Camera_800B77E8.flags |= 0x100;
            sub_8002FAAC(&GM_Camera_800B77E8.eye, &GM_Camera_800B77E8.center, &GM_Camera_800B77E8.rotate, &GM_Camera_800B77E8.track);

            if (!(GM_Camera_800B77E8.flags & 1))
            {
                if (camera_act_helper3_helper_8002ED3C() & 0x3001E)
                {
                    gUnkCameraStruct_800B77B8.rotate = GM_Camera_800B77E8.rotate;
                    gUnkCameraStruct_800B77B8.track = GM_Camera_800B77E8.track;
                }
                else
                {
                    sub_8002FCF0();
                }
            }
        }
        else
        {
            GM_Camera_800B77E8.first_person = 1;
        }
    }

    if (GM_Camera_800B77E8.flags != GM_CameraFlagsOrg_800AB440)
    {
        gUnkCameraStruct_800B77B8.interp = 0;
    }

    GM_800AB43C = GM_Camera_800B77E8.first_person;
    GM_CameraFlagsOrg_800AB440 = GM_Camera_800B77E8.flags;
}

void camera_act_helper4_8002F78C(void)
{
    SVECTOR vec;

    gUnkCameraStruct2_800B7868.type = 0;
    gUnkCameraStruct2_800B7868.track = GM_Camera_800B77E8.track;
    gUnkCameraStruct2_800B7868.zoom = GM_Camera_800B77E8.zoom;

    if (GM_Camera_800B77E8.field_2A == 0)
    {
        gUnkCameraStruct2_800B7868.eye = GM_Camera_800B77E8.eye;
        gUnkCameraStruct2_800B7868.rotate = GM_Camera_800B77E8.rotate;
        gUnkCameraStruct2_800B7868.center = GM_Camera_800B77E8.center;
    }
    else
    {
        camera_get_euler_angles_8002FBC0(&GM_Camera_800B77E8.eye, &GM_Camera_800B77E8.center, &GM_Camera_800B77E8.rotate, &GM_Camera_800B77E8.track);

        GV_SubVec3(&GM_Camera_800B77E8.eye, &svec_800ABA88, &vec);
        GV_AddVec3(&vec, &gUnkCameraStruct2_800B7868.eye, &gUnkCameraStruct2_800B7868.eye);

        svec_800ABA88 = GM_Camera_800B77E8.eye;

        if (GM_Camera_800B77E8.field_2A == 3)
        {
            GV_NearTimeSV(&gUnkCameraStruct2_800B7868.eye.vx, &GM_Camera_800B77E8.eye.vx, GM_Camera_800B77E8.interp, 3);
            GV_NearTimePV(&gUnkCameraStruct2_800B7868.rotate.vx, &GM_Camera_800B77E8.rotate.vx, GM_Camera_800B77E8.interp, 3);
        }
        else if (GM_Camera_800B77E8.field_2A == 1)
        {
            GV_NearExp2V(&gUnkCameraStruct2_800B7868.eye.vx, &GM_Camera_800B77E8.eye.vx, 3);
            GV_NearExp2PV(&gUnkCameraStruct2_800B7868.rotate.vx, &GM_Camera_800B77E8.rotate.vx, 3);
        }
        else if (GM_Camera_800B77E8.field_2A == 2)
        {
            GV_NearExp4V(&gUnkCameraStruct2_800B7868.eye.vx, &GM_Camera_800B77E8.eye.vx, 3);
            GV_NearExp4PV(&gUnkCameraStruct2_800B7868.rotate.vx, &GM_Camera_800B77E8.rotate.vx, 3);
        }

        if (gUnkCameraStruct2_800B7868.track > 10000)
        {
            gUnkCameraStruct2_800B7868.track = 10000;
        }

        sub_8002FC58(&gUnkCameraStruct2_800B7868.eye, &gUnkCameraStruct2_800B7868.center, &gUnkCameraStruct2_800B7868.rotate, &gUnkCameraStruct2_800B7868.track);

        if (--GM_Camera_800B77E8.interp < 0)
        {
            GM_Camera_800B77E8.field_2A = 0;
            GM_Camera_800B77E8.interp = -1;
        }
    }

    if (GM_NoisePower_800ABA24 >= 255)
    {
        if (GM_Camera_800B77E8.first_person == 0)
        {
            gUnkCameraStruct2_800B7868.eye.vy += (GV_RandS(512) * GM_NoiseLength_800ABA30) / 32;
        }
        else
        {
            gUnkCameraStruct2_800B7868.eye.vy += (GV_RandS(512) * GM_NoiseLength_800ABA30) / 128;
        }
    }

    if (GM_Camera_800B77E8.first_person == 0)
    {
        gUnkCameraStruct2_800B7868.eye.vy += GM_CameraShakeOffset_800ABA98;
        GM_CameraShakeOffset_800ABA98 = 0;
    }
    else
    {
        gUnkCameraStruct2_800B7868.eye.vy += GM_CameraShakeOffset_800ABA98 / 4;
        GM_CameraShakeOffset_800ABA98 = 0;
    }
}

void sub_8002FAAC(SVECTOR *eye, SVECTOR *center, SVECTOR *rotate, int *track)
{
    if ( gUnkCameraStruct2_800B7868.type == 0 )
    {
        *eye = gUnkCameraStruct2_800B7868.eye;
        *center = gUnkCameraStruct2_800B7868.center;
        camera_get_euler_angles_8002FBC0(eye, center, rotate, track);
        gUnkCameraStruct2_800B7868.rotate = *rotate;
    }
}

void camera_act_helper7_8002FB54()
{
    switch (GM_Camera_800B77E8.field_28)
    {
    case 0:
        break;
    case 1:
        sub_8002FC58(&GM_Camera_800B77E8.eye, &GM_Camera_800B77E8.center, &GM_Camera_800B77E8.rotate,
                     &GM_Camera_800B77E8.track);
        break;
    case 2:

        sub_8002FCA4(&GM_Camera_800B77E8.eye, &GM_Camera_800B77E8.center, &GM_Camera_800B77E8.rotate,
                     &GM_Camera_800B77E8.track);
        break;
    }
}

void camera_get_euler_angles_8002FBC0(SVECTOR *eye, SVECTOR *center, SVECTOR *rotate, int *track)
{
    SVECTOR forward;

    GV_SubVec3(center, eye, &forward);
    *track = GV_VecLen3(&forward);

    rotate->vz = 0;
    rotate->vy = GV_VecDir2(&forward);
    rotate->vx = ratan2(-forward.vy, SquareRoot0(forward.vx * forward.vx + forward.vz * forward.vz));
}

void sub_8002FC58(SVECTOR *param_1, SVECTOR *param_2, SVECTOR *param_3, int *param_4)
{
    SVECTOR vec;
    GV_DirVec3(param_3, *param_4, &vec);
    sub_8002EC8C(param_1, &vec, param_2);
}

void sub_8002FCA4(SVECTOR *param_1, SVECTOR *param_2, SVECTOR *param_3, int *param_4)
{
    SVECTOR vec;

    GV_DirVec3(param_3, *param_4, &vec);
    sub_8002ECE4(param_2, &vec, param_1);
}

void sub_8002FCF0(void)
{
    if (!(GM_Camera_800B77E8.flags & 0x20))
    {
        gUnkCameraStruct_800B77B8.track = GM_CameraTrackSave_800AB42C;
        gUnkCameraStruct_800B77B8.rotate = GM_CameraRotateSave_800AB430;
    }
    else
    {
        gUnkCameraStruct_800B77B8.track = gUnkCameraStruct2_800B76F0.track;
        gUnkCameraStruct_800B77B8.rotate = gUnkCameraStruct2_800B76F0.rotate;
    }
}

void GM_SetCameraCallbackFunc_8002FD84(int index, TGMCameraFunc func)
{
    GM_Camera_800B77E8.callbacks[index] = func;
}

void camera_act_helper6_helper_8002FD9C(int cam1, int cam2)
{
    CAMERA *pCamera;
    int cam_param1;

    GM_Camera_800B77E8.flags &= ~0x3C;

    if (cam1 == -1)
    {
        if (!(GM_Camera_800B77E8.flags & 2))
        {
            sub_8002FCF0();
        }
    }
    else
    {
        pCamera = &GM_CameraList_800B7718[cam1];
        cam_param1 = pCamera->field_10_param1;

        if (pCamera->field_10_param1 == 0)
        {
            GM_Camera_800B77E8.flags |= 0x20;

            gUnkCameraStruct_800B77B8.rotate.vx = pCamera->trg[0];
            gUnkCameraStruct_800B77B8.rotate.vy = pCamera->trg[1];
            gUnkCameraStruct_800B77B8.rotate.vz = 0;

            gUnkCameraStruct2_800B76F0.center = gUnkCameraStruct_800B77B8.center;
            gUnkCameraStruct2_800B76F0.rotate = gUnkCameraStruct_800B77B8.rotate;
            gUnkCameraStruct2_800B76F0.track = gUnkCameraStruct_800B77B8.track = pCamera->trg[2];

            sub_8002FCA4(&gUnkCameraStruct2_800B76F0.eye, &gUnkCameraStruct2_800B76F0.center, &gUnkCameraStruct2_800B76F0.rotate, &gUnkCameraStruct2_800B76F0.track);
        }
        else
        {
            switch (pCamera->field_12_param3)
            {
            case 0:
                gUnkCameraStruct2_800B76F0.eye = pCamera->pos;
                gUnkCameraStruct2_800B76F0.center = *(SVECTOR *)pCamera->trg;
                camera_get_euler_angles_8002FBC0(&gUnkCameraStruct2_800B76F0.eye, &gUnkCameraStruct2_800B76F0.center, &gUnkCameraStruct2_800B76F0.rotate, &gUnkCameraStruct2_800B76F0.track);
                break;

            case 1:
                gUnkCameraStruct2_800B76F0.eye = pCamera->pos;

                gUnkCameraStruct2_800B76F0.rotate.vx = pCamera->trg[0];
                gUnkCameraStruct2_800B76F0.rotate.vy = pCamera->trg[1];
                gUnkCameraStruct2_800B76F0.rotate.vz = 0;
                gUnkCameraStruct2_800B76F0.track = pCamera->trg[2];

                sub_8002FC58(&gUnkCameraStruct2_800B76F0.eye, &gUnkCameraStruct2_800B76F0.center, &gUnkCameraStruct2_800B76F0.rotate, &gUnkCameraStruct2_800B76F0.track);
                break;

            case 2:
                gUnkCameraStruct2_800B76F0.center = pCamera->pos;

                gUnkCameraStruct2_800B76F0.rotate.vx = pCamera->trg[0];
                gUnkCameraStruct2_800B76F0.rotate.vy = pCamera->trg[1];
                gUnkCameraStruct2_800B76F0.rotate.vz = 0;
                gUnkCameraStruct2_800B76F0.track = pCamera->trg[2];

                sub_8002FCA4(&gUnkCameraStruct2_800B76F0.eye, &gUnkCameraStruct2_800B76F0.center, &gUnkCameraStruct2_800B76F0.rotate, &gUnkCameraStruct2_800B76F0.track);
                break;
            }

            gUnkCameraStruct2_800B76F0.eye.pad = pCamera->field_13_param_p | ((unsigned short)pCamera->pos.pad * 4);
            gUnkCameraStruct2_800B76F0.type = 0;

            if (cam_param1 == 1)
            {
                GM_Camera_800B77E8.flags |= 0x10;
            }
            else if (cam_param1 == 2)
            {
                GM_Camera_800B77E8.flags |= 0x8;
            }
            else
            {
                GM_Camera_800B77E8.flags |= 0x4;
            }
        }
    }

    if ((GM_Camera_800B77E8.first_person == 1) || (DG_UnDrawFrameCount_800AB380 > 0))
    {
        GM_Camera_800B77E8.field_2A = 0;
        GM_Camera_800B77E8.interp = -1;
    }
    else if (cam2 < 0)
    {
        GM_Camera_800B77E8.field_2A = 2;
        GM_Camera_800B77E8.interp = 30;
    }
    else
    {
        pCamera = &GM_CameraList_800B7718[cam2];
        GM_Camera_800B77E8.field_2A = dword_80010C60[pCamera->field_11_param2];
        GM_Camera_800B77E8.interp = dword_80010C60[pCamera->field_11_param2] >> 16;
    }
}

void camera_act_helper5_80030118(GV_ACT *pActor)
{
    GV_MSG *pMsg;
    int msgLen;
    int bitmap;
    GV_MSG *pMsgIter;
    int i;
    int index;
    int type;

    msgLen = GV_ReceiveMessage(0xC356, &pMsg);

    if (!msgLen)
    {
        return;
    }

    bitmap = 0;

    pMsgIter = pMsg;
    for (i = msgLen; i > 0; i--)
    {
        index = pMsgIter->message[0];
        type = pMsgIter->message[1];

        if (type == HASH_LEAVE)
        {
            bitmap |= (1 << index);
            GM_event_camera_flag_800ABA9C &= ~(1 << index);
            printf("[%d]cam out %d\n", GV_Time_800AB330, index);
        }

        pMsgIter++;
    }

    pMsgIter = pMsg;
    for (i = msgLen; i > 0; i--)
    {
        index = pMsgIter->message[0];
        type = pMsgIter->message[1];

        if (type == HASH_ENTER)
        {
            GM_event_camera_flag_800ABA9C |= (1 << index);

            if (bitmap & (1 << index))
            {
                dword_800ABA90 &= ~(1 << index);
            }

            printf("[%d]cam in %d\n", GV_Time_800AB330, index);
        }

        pMsgIter++;
    }
}

int camera_act_helper6_80030250(GV_ACT *pActor)
{
    int var_a1;
    int temp_a2;
    unsigned int mask;
    int i;
    int old_i;

    var_a1 = GM_event_camera_flag_800ABA9C;

    if (GM_AlertMode_800ABA00 == 3)
    {
        if (GM_Camera_800B77E8.field_24_gcl_param_a < 8)
        {
            var_a1 &= -(1 << GM_Camera_800B77E8.field_24_gcl_param_a);
        }

        if (dword_800ABA94 != 0)
        {
            var_a1 &= ~dword_800ABA94;
        }
    }

    temp_a2 = var_a1 ^ dword_800ABA90;

    if (temp_a2 == 0)
    {
        return 0;
    }

    dword_800ABA90 = var_a1;

    for (mask = 1, i = 0; i < 7; i++, mask <<= 1)
    {
        if (temp_a2 & mask)
        {
            break;
        }
    }

    temp_a2 = var_a1;
    old_i = i;

    for (mask = 0x80, i = 7; i >= 0; i--, mask >>= 1)
    {
        if (temp_a2 & mask)
        {
            if (GM_CameraList_800B7718[i].field_10_param1 != -1)
            {
                break;
            }

            GM_event_camera_flag_800ABA9C &= ~mask;
        }
    }


    sub_8002FAAC(&GM_Camera_800B77E8.eye, &GM_Camera_800B77E8.center, &GM_Camera_800B77E8.rotate, &GM_Camera_800B77E8.track);
    camera_act_helper6_helper_8002FD9C(i, old_i);
    printf("[%d]change camera %d\n", GV_Time_800AB330, i);

    GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_07;

    if (GM_CameraList_800B7718[i].field_0e_alertMask & 1)
    {
        GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_07;
    }

    return 1;
}

void sub_800303E0(SVECTOR *arg0)
{
    SVECTOR          vec;
    UnkCameraStruct *pUnkCamera;
    int              index;

    vec = *arg0;
    pUnkCamera = &gUnkCameraStruct_800B77B8;

    if (DG_UnDrawFrameCount_800AB380 > 0)
    {
        *arg0 = pUnkCamera->eye;
    }
    else
    {
        sub_8002EB80(&vec, &pUnkCamera->eye);
        GV_NearExp4V((short *)arg0, (short *)&vec, 3);
    }

#ifdef VR_EXE
    index = !!(GM_Camera_800B77E8.flags & 0x28);
#else
    index = !!(GM_Camera_800B77E8.flags & 0x20);
#endif

    sub_8002EBE8(arg0, index);
}

void sub_8003049C(SVECTOR *a1)
{
    GM_Camera *pCamera;

    pCamera = &GM_Camera_800B77E8;
    pCamera->pan = *a1;
    pCamera->pan.pad = 1;

    GV_AddVec3(&gUnkCameraStruct2_800B7868.eye, a1, &gUnkCameraStruct2_800B7868.eye);
    GV_AddVec3(&gUnkCameraStruct2_800B7868.center, a1, &gUnkCameraStruct2_800B7868.center);

    GV_AddVec3(&pCamera->eye, a1, &pCamera->eye);
    GV_AddVec3(&pCamera->center, a1, &pCamera->center);

    GV_AddVec3(&gUnkCameraStruct_800B77B8.field_1C, a1, &gUnkCameraStruct_800B77B8.field_1C);
    GV_AddVec3(&gUnkCameraStruct_800B77B8.eye, a1, &gUnkCameraStruct_800B77B8.eye);
    GV_AddVec3(&gUnkCameraStruct_800B77B8.center, a1, &gUnkCameraStruct_800B77B8.center);

    GV_AddVec3(&svec_800ABA88, a1, &svec_800ABA88);
}

void camera_act_8003059C(GV_ACT *pActor)
{
    int iVar1;
    int iVar2;

    if (GM_GameStatus_800AB3CC >= 0)
    {
        if (GV_PauseLevel_800AB928 == 0)
        {
            camera_act_helper5_80030118(pActor);
            iVar1 = camera_act_helper6_80030250(pActor);
            camera_act_helper3_8002F64C();

            if (GM_Camera_800B77E8.first_person == 1)
            {
                camera_act_helper_8002F1C8();
                camera_act_helper7_8002FB54();
            }
            else
            {
                iVar2 = camera_act_helper2_8002F5C4();
                camera_act_helper7_8002FB54();

                if (iVar2 > 0)
                {
                    sub_8002EADC(iVar2 - 1);
                }
            }

            if (iVar1)
            {
                svec_800ABA88 = GM_Camera_800B77E8.eye;
            }

            camera_act_helper4_8002F78C();
        }

        DG_LookAt_800172D0(DG_Chanl(0),
            &gUnkCameraStruct2_800B7868.eye,
            &gUnkCameraStruct2_800B7868.center,
            gUnkCameraStruct2_800B7868.zoom);
    }
}

GV_ACT *camera_init_800306A0()
{
    GV_ACT *pActor;

    pActor = GV_NewActor(2, sizeof(GV_ACT));
    if (pActor)
    {
        GV_SetNamedActor(pActor, camera_act_8003059C, NULL, "camera.c");
    }

    GM_Camera_800B77E8.zoom = 320;
    GM_Camera_800B77E8.first_person = 0;
    GM_Camera_800B77E8.flags = 0;
    GM_Camera_800B77E8.pan.pad = 0;
    gUnkCameraStruct2_800B7868.zoom = 320;
    dword_800ABA90 = 0;
    GM_event_camera_flag_800ABA9C = 0;
    GM_800AB43C = 0;
    GM_CameraFlagsOrg_800AB440 = 0;
    gUnkCameraStruct_800B77B8.track = 10000;
    GM_Camera_800B77E8.track = 10000;
    gUnkCameraStruct2_800B7868.track = 10000;
    sub_8002FCF0();
    gUnkCameraStruct_800B77B8.rotate2.vx = 0;
    gUnkCameraStruct_800B77B8.rotate2.vy = 2048;
    gUnkCameraStruct_800B77B8.rotate2.vz = 0;

    return pActor;
}

void GM_Reset_helper3_80030760()
{
    CAMERA    *cameraList, *cameraListIter;
    GM_Camera *gmCamera;
    int        i;
    int        field_10_param1;

    field_10_param1 = -1;
    i = 7;

    cameraList = GM_CameraList_800B7718;
    cameraListIter = cameraList + 7;

    gmCamera = &GM_Camera_800B77E8;
    gmCamera->field_24_gcl_param_a = 100;

    gmCamera->bounds[0][0].vx = 0x7fff;
    gmCamera->bounds[0][0].vy = 0x7fff;
    gmCamera->bounds[0][0].vz = 0x7fff;
    gmCamera->bounds[1][0].vx = -0x7fff;
    gmCamera->bounds[1][0].vy = -0x7fff;
    gmCamera->bounds[1][0].vz = -0x7fff;

    gmCamera->limits[0][0].vx = 0x7fff;
    gmCamera->limits[0][0].vy = 0x7fff;
    gmCamera->limits[0][0].vz = 0x7fff;
    gmCamera->limits[1][0].vx = -0x7fff;
    gmCamera->limits[1][0].vy = -0x7fff;
    gmCamera->limits[1][0].vz = -0x7fff;

    gmCamera->bounds[0][1].vx = 0x7fff;
    gmCamera->bounds[0][1].vy = 0x7fff;
    gmCamera->bounds[0][1].vz = 0x7fff;
    gmCamera->bounds[1][1].vx = -0x7fff;
    gmCamera->bounds[1][1].vy = -0x7fff;
    gmCamera->bounds[1][1].vz = -0x7fff;

    gmCamera->limits[0][1].vx = 0x7fff;
    gmCamera->limits[0][1].vy = 0x7fff;
    gmCamera->limits[0][1].vz = 0x7fff;
    gmCamera->limits[1][1].vx = -0x7fff;
    gmCamera->limits[1][1].vy = -0x7fff;
    gmCamera->limits[1][1].vz = -0x7fff;

    GM_CameraRotateSave_800AB430.vx = 0x280;
    GM_CameraRotateSave_800AB430.vy = 0x800;
    GM_CameraRotateSave_800AB430.vz = 0;

    while (i >= 0)
    {
        cameraListIter->field_10_param1 = field_10_param1;
        i--;
        cameraListIter--;
    }
    dword_800ABA94 = 0;
}

void sub_8003081C()
{
    gUnkCameraStruct_800B77B8.center = gUnkCameraStruct_800B77B8.eye;
}

void GM_CameraSetAlertMask_80030850(unsigned int id, unsigned int mask)
{
    if ( mask & 0x2 )
    {
        mask = 1 << id;
    }
    else
    {
        mask = 0;
    }

    dword_800ABA94 &= ~(1 << id);
    dword_800ABA94 |= mask;
}

void GM_CameraSetBounds_80030888(SVECTOR *min, SVECTOR *max, int param_e)
{
    GM_Camera_800B77E8.bounds[1][param_e] = *min;
    GM_Camera_800B77E8.bounds[0][param_e] = *max;
}

void GM_CameraSetLimits_800308E0(SVECTOR *min, SVECTOR *max, int param_e)
{
    GM_Camera_800B77E8.limits[1][param_e] = *min;
    GM_Camera_800B77E8.limits[0][param_e] = *max;
}

void GM_CameraSetRotation_80030938(SVECTOR *rot)
{
    GM_CameraRotateSave_800AB430 = *rot;
    sub_8002FCF0();
}

void GM_CameraSetTrack_80030980(int track)
{
    GM_CameraTrackOrg_800AB438 = track;
    GM_CameraTrackSave_800AB42C = track;
    sub_8002FCF0();
}

void GM_CameraEventReset_800309A8(void)
{
    dword_800ABA90 = 0;
    return;
}

void sub_800309B4(int param_1, int param_2)
{
    GM_Camera_800B77E8.field_2A = param_1;
    GM_Camera_800B77E8.interp = param_2;
    svec_800ABA88 = GM_Camera_800B77E8.eye;
}

void sub_800309F8(int param_1, int param_2)
{
    sub_800309B4(param_1, param_2);
    GM_Camera_800B77E8.flags |= 2;
}

void sub_80030A30()
{
    if (GM_Camera_800B77E8.first_person == 0)
    {
        gUnkCameraStruct_800B77B8.eye = gUnkCameraStruct_800B77B8.center = GM_Camera_800B77E8.center;
    }

    GM_Camera_800B77E8.flags &= ~2;
}

void GM_CameraBoundTrace_80030AA4(int param_1)
{
    sub_8002EADC(param_1);
}

void GM_CameraLimitTrace_80030AC4(int param_1)
{
    sub_8002EBE8(&GM_Camera_800B77E8.center, param_1);
}

void GM_ExitBehindCamera_80030AEC(void)
{
    if (GM_GameStatus_800AB3CC & GAME_FLAG_BIT_05)
    {
        GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_05;
        GM_event_camera_flag_800ABA9C &= ~8;
        dword_800ABA90 = dword_800ABA90 | 8;
    }

    GM_800AB448 = 0;
    GM_800AB444 = NULL;
}

void GM_CheckBehindCamera_80030B3C(HZD_HDL *pHzdMap, CONTROL *pControl)
{
    HZD_TRP *trp;
    CAMERA  *cam;
    short   *name;

    if ((GM_StatusEvent & 0x100 || GM_AlertMode_800ABA00 != 3) &&
        (trp = HZD_CheckBehindTrap_8002A5E0(pHzdMap, pControl)) != NULL)
    {
        if (GM_800AB444 != trp)
        {
            if (++GM_800AB448 >= 10)
            {
                GM_800AB444 = trp;

                cam = &GM_CameraList_800B7718[3];
                cam->field_10_param1 = 1;
                cam->field_11_param2 = 2;
                cam->field_12_param3 = 0;
                cam->field_13_param_p = 2;
                cam->pos.pad = GV_GetPadOrigin();

                name = (short *)trp->name; // TODO: Is char[] name array in HZD_TRP correct? Is it really a name?
                cam->trg[0] = name[0];
                cam->trg[1] = name[1];
                cam->trg[2] = name[2];

                GM_event_camera_flag_800ABA9C |= 8;
                dword_800ABA90 &= ~8;
                GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_05;

                cam->pos.vx = name[3];
                cam->pos.vy = name[4];
                cam->pos.vz = name[5];
            }
        }
    }
    else
    {
        GM_ExitBehindCamera_80030AEC();
    }
}
