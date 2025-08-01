#include "camera.h"

#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libhzd/libhzd.h"
#include "linkvar.h"
#include "strcode.h"

STATIC int     SECTION(".sbss") dword_800ABA84;
STATIC SVECTOR SECTION(".sbss") svec_800ABA88;
STATIC int     SECTION(".sbss") dword_800ABA90;
STATIC int     SECTION(".sbss") dword_800ABA94;

int SECTION(".sbss") GM_CameraShakeOffset;
int SECTION(".sbss") GM_event_camera_flag;

int      GM_CameraTrackSave = 10000;
SVECTOR  GM_CameraRotateSave = { 640, 2048, 0, 0 };
int      GM_CameraTrackOrg = 10000;

STATIC int      GM_CameraFirstPersonOrg = 0;
STATIC int      GM_CameraFlagsOrg = 0;
STATIC HZD_TRP *GM_800AB444 = NULL;
STATIC int      GM_800AB448 = 0;

extern GM_CAMERA        GM_Camera;
extern UnkCameraStruct  gUnkCameraStruct_800B77B8;
extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;
extern UnkCameraStruct2 gUnkCameraStruct2_800B76F0;
extern CAMERA           GM_CameraList[8];

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

void camera_get_euler_angles_8002FBC0(SVECTOR *eye, SVECTOR *center, SVECTOR *rotate, int *track);
void sub_8002FC58(SVECTOR *param_1, SVECTOR *param_2, SVECTOR *param_3, int *param_4);
void sub_8002FCA4(SVECTOR *param_1, SVECTOR *param_2, SVECTOR *param_3, int *param_4);
void sub_8002FCF0(void);
void sub_800303E0(SVECTOR *arg0);

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

STATIC void sub_8002EADC(int index)
{
    SVECTOR *pBase;
    SVECTOR *pVec;

    pBase = (SVECTOR *)&GM_Camera;
    pVec = pBase + index;

    GM_Camera.eye.vx = camera_clamp(GM_Camera.eye.vx, pVec[8].vz,  pVec[6].vz);
    GM_Camera.eye.vy = camera_clamp(GM_Camera.eye.vy, pVec[8].pad, pVec[6].pad);
    GM_Camera.eye.vz = camera_clamp(GM_Camera.eye.vz, pVec[9].vx,  pVec[7].vx);
}

STATIC void sub_8002EB80(SVECTOR *vec_1, SVECTOR *vec_2)
{
    int iVar1;

    iVar1 = GV_NearRange((int)vec_1->vx, (int)vec_2->vx, 500);
    vec_1->vx = (short)iVar1;
    iVar1 = GV_NearRange((int)vec_1->vz, (int)vec_2->vz, 500);
    vec_1->vz = (short)iVar1;
    iVar1 = GV_NearRange((int)vec_1->vy, (int)vec_2->vy, 0x96);

    vec_1->vy = (short)iVar1;
}

STATIC void sub_8002EBE8(SVECTOR *arg0, int index)
{
    SVECTOR *pBase;
    SVECTOR *pVec;

    pBase = (SVECTOR *)&GM_Camera;
    pVec = pBase + index;

    arg0->vx = camera_clamp(arg0->vx, pVec[12].vz, pVec[10].vz);
    arg0->vy = camera_clamp(arg0->vy, pVec[12].pad, pVec[10].pad);
    arg0->vz = camera_clamp(arg0->vz, pVec[13].vx, pVec[11].vx);

}

STATIC void sub_8002EC8C(SVECTOR *a1, SVECTOR *a2, SVECTOR *a3)
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

STATIC void sub_8002ECE4(SVECTOR *a, SVECTOR *b, SVECTOR *c)
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
    return GM_Camera.flags & mask;
}

STATIC int camera_act_helper3_helper_8002ED3C(void)
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

STATIC void sub_8002ED68(int arg0)
{
    switch (gUnkCameraStruct2_800B76F0.eye.pad & 3)
    {
    case 0:
        GV_OriginPadSystem(0);
        return;

    case 1:
        if (arg0 != 0)
        {
            camera_get_euler_angles_8002FBC0(&GM_Camera.eye, &GM_Camera.center, &gUnkCameraStruct2_800B76F0.rotate, &gUnkCameraStruct2_800B76F0.track);
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

STATIC void sub_8002EE04(void)
{
    GM_Camera.eye = gUnkCameraStruct2_800B76F0.eye;
    GM_Camera.center = gUnkCameraStruct2_800B76F0.center;
    GM_Camera.field_28 = 0;
    sub_8002ED68(0);
}

STATIC void sub_8002EE80(void)
{
    gUnkCameraStruct2_800B76F0.center.vz = gUnkCameraStruct_800B77B8.center.vz;
    GM_Camera.eye = gUnkCameraStruct2_800B76F0.eye;
    GM_Camera.center = gUnkCameraStruct2_800B76F0.center;
    GM_Camera.field_28 = 0;
    GV_OriginPadSystem(0);
}

STATIC void sub_8002EF08(void)
{
    GM_Camera.eye = gUnkCameraStruct2_800B76F0.eye;
    GM_Camera.center = gUnkCameraStruct_800B77B8.center;
    GM_Camera.field_28 = 0;
    sub_8002ED68(1);
}

STATIC void sub_8002EF88(void)
{
    int unused[2]; (void)unused;
    GM_Camera.center = gUnkCameraStruct_800B77B8.center;
    GM_Camera.track = gUnkCameraStruct_800B77B8.track;
    GM_Camera.rotate = gUnkCameraStruct_800B77B8.rotate;
    GM_Camera.field_28 = 2;
    GV_OriginPadSystem(0);
}

STATIC void camera_act_helper_helper_8002F008()
{
    GM_Camera.eye = gUnkCameraStruct_800B77B8.eye;
    GM_Camera.track = 1000;
    GM_Camera.rotate = gUnkCameraStruct_800B77B8.rotate2;
    GM_Camera.field_28 = 1;
    GV_OriginPadSystem(gUnkCameraStruct_800B77B8.rotate2.vy + 2048);
}

STATIC void camera_act_helper_helper2_8002F094(int param_1)
{
    int iVar1;
    SVECTOR vec;

    if (param_1 < 6)
    {
        GV_NearExp4V(&GM_Camera.center.vx, &gUnkCameraStruct_800B77B8.eye.vx, 3);
        GV_NearExp4PV(&GM_Camera.rotate.vx, &gUnkCameraStruct_800B77B8.rotate2.vx, 3);
        GM_Camera.track = GV_NearExp4(GM_Camera.track, 1000);
        GV_DirVec3(&GM_Camera.rotate, GM_Camera.track, &vec);
        sub_8002ECE4(&GM_Camera.center, &vec, &GM_Camera.eye);
        GM_Camera.field_28 = 0;
    }
    else
    {
        iVar1 = 12 - param_1;
        GV_NearTimeV(&GM_Camera.eye.vx, &gUnkCameraStruct_800B77B8.eye.vx, iVar1, 3);
        GV_NearTimePV(&GM_Camera.rotate.vx, &gUnkCameraStruct_800B77B8.rotate2.vx, iVar1, 3);
        GM_Camera.track = GV_NearTime(GM_Camera.track, 1000, iVar1);
        GV_DirVec3(&GM_Camera.rotate, GM_Camera.track, &vec);
        sub_8002EC8C(&GM_Camera.eye, &vec, &GM_Camera.center);
        GM_Camera.field_28 = 0;
    }

    GV_OriginPadSystem(0);
}

STATIC void camera_act_helper_8002F1C8(void)
{
    if (GM_Camera.flags & 0x100)
    {
        if (gUnkCameraStruct_800B77B8.interp >= 12)
        {
            GM_Camera.flags &= ~0x101;
        }

        camera_act_helper_helper2_8002F094(gUnkCameraStruct_800B77B8.interp);
    }
    else if (GM_Camera.flags & 0x200)
    {
        if (GM_Camera.callbacks[0])
        {
            GM_Camera.callbacks[0]();
        }
    }
    else
    {
        camera_act_helper_helper_8002F008();
    }

    gUnkCameraStruct_800B77B8.interp++;
}

STATIC int sub_8002F274(void)
{
    if (GM_Camera.pan.pad == 1)
    {
        GV_AddVec3(&gUnkCameraStruct_800B77B8.eye, &GM_Camera.pan, &gUnkCameraStruct_800B77B8.eye);
        GM_Camera.pan.pad = 0;
    }

    sub_800303E0(&gUnkCameraStruct_800B77B8.center);

    if (GM_Camera.flags & 0x20)
    {
        sub_8002EF88();
        return 2;
    }

    else if (GM_Camera.flags & 0x10)
    {
        sub_8002EE04();
    }
    else if (GM_Camera.flags & 8)
    {
        sub_8002EE80();
    }
    else if (GM_Camera.flags & 4)
    {
        sub_8002EF08();
    }
    else if (GM_Camera.flags & 2)
    {
        if (GM_Camera.callbacks[1])
        {
            GM_Camera.callbacks[1]();
        }

        if ((GM_Camera.flags & 0x80))
        {
            return 1;
        }
        else if (GM_Camera.flags & 0x40)
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

STATIC int camera_act_helper2_helper_8002F384(int arg0)
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
        GV_NearTimeV(&GM_Camera.center.vx, &gUnkCameraStruct_800B77B8.eye.vx, 2 - arg0, 3);
        GV_NearTimePV(&GM_Camera.rotate.vx, &gUnkCameraStruct_800B77B8.rotate2.vx, 2 - arg0, 3);
        GM_Camera.track = GV_NearTime(GM_Camera.track, 1000, 2 - arg0);
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

        vec = GM_Camera.center;
        vec2 = GM_Camera.rotate;

        temp_s3 = GM_Camera.track;
        var_s7 = sub_8002F274();

        switch (GM_Camera.field_28)
        {
        case 0:
            camera_get_euler_angles_8002FBC0(&GM_Camera.eye, &GM_Camera.center, &GM_Camera.rotate, &GM_Camera.track);
            break;

        case 1:
            sub_8002FC58(&GM_Camera.eye, &GM_Camera.center, &GM_Camera.rotate, &GM_Camera.track);
            break;
        }

        var_s5(&vec.vx, &GM_Camera.center.vx, 3);
        var_s6(&vec2.vx, &GM_Camera.rotate.vx, 3);

        temp_v0 = var_s4(temp_s3, GM_Camera.track);

        GM_Camera.center = vec;
        GM_Camera.rotate = vec2;
        GM_Camera.track = temp_v0;
    }

    GM_Camera.field_28 = 2;
    temp_s3 = var_s7;

    return temp_s3;
}

STATIC int camera_act_helper2_8002F5C4(void)
{
    int ret;

    if (GM_Camera.flags & 1)
    {
        if (gUnkCameraStruct_800B77B8.interp >= 12)
        {
            GM_Camera.flags &= ~0x101;
            GM_Camera.interp = -1;
            GM_Camera.field_2A = 0;
        }

        ret = camera_act_helper2_helper_8002F384(gUnkCameraStruct_800B77B8.interp);
        gUnkCameraStruct_800B77B8.interp++;

        return ret;
    }

    return sub_8002F274();
}

STATIC void camera_act_helper3_8002F64C(void)
{
    if (GM_Camera.first_person != GM_CameraFirstPersonOrg)
    {
        gUnkCameraStruct_800B77B8.interp = 0;
        GM_Camera.field_2A = 0;

        if (GM_Camera.first_person == 0)
        {
            GM_Camera.flags |= 1;
            sub_8002FAAC(&GM_Camera.eye, &GM_Camera.center, &GM_Camera.rotate, &GM_Camera.track);
        }
        else if (GM_Camera.first_person == 1)
        {
            GM_Camera.flags |= 0x100;
            sub_8002FAAC(&GM_Camera.eye, &GM_Camera.center, &GM_Camera.rotate, &GM_Camera.track);

            if (!(GM_Camera.flags & 1))
            {
                if (camera_act_helper3_helper_8002ED3C() & 0x3001E)
                {
                    gUnkCameraStruct_800B77B8.rotate = GM_Camera.rotate;
                    gUnkCameraStruct_800B77B8.track = GM_Camera.track;
                }
                else
                {
                    sub_8002FCF0();
                }
            }
        }
        else
        {
            GM_Camera.first_person = 1;
        }
    }

    if (GM_Camera.flags != GM_CameraFlagsOrg)
    {
        gUnkCameraStruct_800B77B8.interp = 0;
    }

    GM_CameraFirstPersonOrg = GM_Camera.first_person;
    GM_CameraFlagsOrg = GM_Camera.flags;
}

STATIC void camera_act_helper4_8002F78C(void)
{
    SVECTOR vec;

    gUnkCameraStruct2_800B7868.type = 0;
    gUnkCameraStruct2_800B7868.track = GM_Camera.track;
    gUnkCameraStruct2_800B7868.zoom = GM_Camera.zoom;

    if (GM_Camera.field_2A == 0)
    {
        gUnkCameraStruct2_800B7868.eye = GM_Camera.eye;
        gUnkCameraStruct2_800B7868.rotate = GM_Camera.rotate;
        gUnkCameraStruct2_800B7868.center = GM_Camera.center;
    }
    else
    {
        camera_get_euler_angles_8002FBC0(&GM_Camera.eye, &GM_Camera.center, &GM_Camera.rotate, &GM_Camera.track);

        GV_SubVec3(&GM_Camera.eye, &svec_800ABA88, &vec);
        GV_AddVec3(&vec, &gUnkCameraStruct2_800B7868.eye, &gUnkCameraStruct2_800B7868.eye);

        svec_800ABA88 = GM_Camera.eye;

        if (GM_Camera.field_2A == 3)
        {
            GV_NearTimeV(&gUnkCameraStruct2_800B7868.eye.vx, &GM_Camera.eye.vx, GM_Camera.interp, 3);
            GV_NearTimePV(&gUnkCameraStruct2_800B7868.rotate.vx, &GM_Camera.rotate.vx, GM_Camera.interp, 3);
        }
        else if (GM_Camera.field_2A == 1)
        {
            GV_NearExp2V(&gUnkCameraStruct2_800B7868.eye.vx, &GM_Camera.eye.vx, 3);
            GV_NearExp2PV(&gUnkCameraStruct2_800B7868.rotate.vx, &GM_Camera.rotate.vx, 3);
        }
        else if (GM_Camera.field_2A == 2)
        {
            GV_NearExp4V(&gUnkCameraStruct2_800B7868.eye.vx, &GM_Camera.eye.vx, 3);
            GV_NearExp4PV(&gUnkCameraStruct2_800B7868.rotate.vx, &GM_Camera.rotate.vx, 3);
        }

        if (gUnkCameraStruct2_800B7868.track > 10000)
        {
            gUnkCameraStruct2_800B7868.track = 10000;
        }

        sub_8002FC58(&gUnkCameraStruct2_800B7868.eye, &gUnkCameraStruct2_800B7868.center, &gUnkCameraStruct2_800B7868.rotate, &gUnkCameraStruct2_800B7868.track);

        if (--GM_Camera.interp < 0)
        {
            GM_Camera.field_2A = 0;
            GM_Camera.interp = -1;
        }
    }

    if (GM_NoisePower >= 255)
    {
        if (GM_Camera.first_person == 0)
        {
            gUnkCameraStruct2_800B7868.eye.vy += (GV_RandS(512) * GM_NoiseLength) / 32;
        }
        else
        {
            gUnkCameraStruct2_800B7868.eye.vy += (GV_RandS(512) * GM_NoiseLength) / 128;
        }
    }

    if (GM_Camera.first_person == 0)
    {
        gUnkCameraStruct2_800B7868.eye.vy += GM_CameraShakeOffset;
        GM_CameraShakeOffset = 0;
    }
    else
    {
        gUnkCameraStruct2_800B7868.eye.vy += GM_CameraShakeOffset / 4;
        GM_CameraShakeOffset = 0;
    }
}

STATIC void sub_8002FAAC(SVECTOR *eye, SVECTOR *center, SVECTOR *rotate, int *track)
{
    if ( gUnkCameraStruct2_800B7868.type == 0 )
    {
        *eye = gUnkCameraStruct2_800B7868.eye;
        *center = gUnkCameraStruct2_800B7868.center;
        camera_get_euler_angles_8002FBC0(eye, center, rotate, track);
        gUnkCameraStruct2_800B7868.rotate = *rotate;
    }
}

STATIC void camera_act_helper7_8002FB54()
{
    switch (GM_Camera.field_28)
    {
    case 0:
        break;
    case 1:
        sub_8002FC58(&GM_Camera.eye, &GM_Camera.center, &GM_Camera.rotate,
                     &GM_Camera.track);
        break;
    case 2:
        sub_8002FCA4(&GM_Camera.eye, &GM_Camera.center, &GM_Camera.rotate,
                     &GM_Camera.track);
        break;
    }
}

STATIC void camera_get_euler_angles_8002FBC0(SVECTOR *eye, SVECTOR *center, SVECTOR *rotate, int *track)
{
    SVECTOR forward;

    GV_SubVec3(center, eye, &forward);
    *track = GV_VecLen3(&forward);

    rotate->vz = 0;
    rotate->vy = GV_VecDir2(&forward);
    rotate->vx = ratan2(-forward.vy, SquareRoot0(forward.vx * forward.vx + forward.vz * forward.vz));
}

STATIC void sub_8002FC58(SVECTOR *param_1, SVECTOR *param_2, SVECTOR *param_3, int *param_4)
{
    SVECTOR vec;
    GV_DirVec3(param_3, *param_4, &vec);
    sub_8002EC8C(param_1, &vec, param_2);
}

STATIC void sub_8002FCA4(SVECTOR *param_1, SVECTOR *param_2, SVECTOR *param_3, int *param_4)
{
    SVECTOR vec;

    GV_DirVec3(param_3, *param_4, &vec);
    sub_8002ECE4(param_2, &vec, param_1);
}

STATIC void sub_8002FCF0(void)
{
    if (!(GM_Camera.flags & 0x20))
    {
        gUnkCameraStruct_800B77B8.track = GM_CameraTrackSave;
        gUnkCameraStruct_800B77B8.rotate = GM_CameraRotateSave;
    }
    else
    {
        gUnkCameraStruct_800B77B8.track = gUnkCameraStruct2_800B76F0.track;
        gUnkCameraStruct_800B77B8.rotate = gUnkCameraStruct2_800B76F0.rotate;
    }
}

void GM_SetCameraCallbackFunc_8002FD84(int index, TGMCameraFunc func)
{
    GM_Camera.callbacks[index] = func;
}

STATIC void ChangeCamera(int new, int old)
{
    CAMERA *camera;

    int cam_param1;

    GM_Camera.flags &= ~0x3C;

    if (new == -1)
    {
        if (!(GM_Camera.flags & 2))
        {
            sub_8002FCF0();
        }
    }
    else
    {
        camera = &GM_CameraList[new];
        cam_param1 = camera->field_10_param1;

        if (camera->field_10_param1 == 0)
        {
            GM_Camera.flags |= 0x20;

            gUnkCameraStruct_800B77B8.rotate.vx = camera->trg[0];
            gUnkCameraStruct_800B77B8.rotate.vy = camera->trg[1];
            gUnkCameraStruct_800B77B8.rotate.vz = 0;

            gUnkCameraStruct2_800B76F0.center = gUnkCameraStruct_800B77B8.center;
            gUnkCameraStruct2_800B76F0.rotate = gUnkCameraStruct_800B77B8.rotate;
            gUnkCameraStruct2_800B76F0.track = gUnkCameraStruct_800B77B8.track = camera->trg[2];

            sub_8002FCA4(&gUnkCameraStruct2_800B76F0.eye, &gUnkCameraStruct2_800B76F0.center, &gUnkCameraStruct2_800B76F0.rotate, &gUnkCameraStruct2_800B76F0.track);
        }
        else
        {
            switch (camera->field_12_param3)
            {
            case 0:
                gUnkCameraStruct2_800B76F0.eye = camera->pos;
                gUnkCameraStruct2_800B76F0.center = *(SVECTOR *)camera->trg;
                camera_get_euler_angles_8002FBC0(&gUnkCameraStruct2_800B76F0.eye, &gUnkCameraStruct2_800B76F0.center, &gUnkCameraStruct2_800B76F0.rotate, &gUnkCameraStruct2_800B76F0.track);
                break;

            case 1:
                gUnkCameraStruct2_800B76F0.eye = camera->pos;

                gUnkCameraStruct2_800B76F0.rotate.vx = camera->trg[0];
                gUnkCameraStruct2_800B76F0.rotate.vy = camera->trg[1];
                gUnkCameraStruct2_800B76F0.rotate.vz = 0;
                gUnkCameraStruct2_800B76F0.track = camera->trg[2];

                sub_8002FC58(&gUnkCameraStruct2_800B76F0.eye, &gUnkCameraStruct2_800B76F0.center, &gUnkCameraStruct2_800B76F0.rotate, &gUnkCameraStruct2_800B76F0.track);
                break;

            case 2:
                gUnkCameraStruct2_800B76F0.center = camera->pos;

                gUnkCameraStruct2_800B76F0.rotate.vx = camera->trg[0];
                gUnkCameraStruct2_800B76F0.rotate.vy = camera->trg[1];
                gUnkCameraStruct2_800B76F0.rotate.vz = 0;
                gUnkCameraStruct2_800B76F0.track = camera->trg[2];

                sub_8002FCA4(&gUnkCameraStruct2_800B76F0.eye, &gUnkCameraStruct2_800B76F0.center, &gUnkCameraStruct2_800B76F0.rotate, &gUnkCameraStruct2_800B76F0.track);
                break;
            }

            gUnkCameraStruct2_800B76F0.eye.pad = camera->field_13_param_p | ((unsigned short)camera->pos.pad * 4);
            gUnkCameraStruct2_800B76F0.type = 0;

            if (cam_param1 == 1)
            {
                GM_Camera.flags |= 0x10;
            }
            else if (cam_param1 == 2)
            {
                GM_Camera.flags |= 0x8;
            }
            else
            {
                GM_Camera.flags |= 0x4;
            }
        }
    }

    if ((GM_Camera.first_person == 1) || (DG_UnDrawFrameCount > 0))
    {
        GM_Camera.field_2A = 0;
        GM_Camera.interp = -1;
    }
    else if (old < 0)
    {
        GM_Camera.field_2A = 2;
        GM_Camera.interp = 30;
    }
    else
    {
        camera = &GM_CameraList[old];
        GM_Camera.field_2A = dword_80010C60[camera->field_11_param2];
        GM_Camera.interp = dword_80010C60[camera->field_11_param2] >> 16;
    }
}

STATIC void CheckMessages(GV_ACT *work)
{
    GV_MSG *msg;
    int     n_msg;
    int     bitmap;
    GV_MSG *iter;
    int     i;
    int     index;
    int     type;

    n_msg = GV_ReceiveMessage(0xC356, &msg);
    if (n_msg == 0)
    {
        return;
    }

    bitmap = 0;

    iter = msg;
    for (i = n_msg; i > 0; i--)
    {
        index = iter->message[0];
        type = iter->message[1];

        if (type == HASH_LEAVE)
        {
            bitmap |= (1 << index);
            GM_event_camera_flag &= ~(1 << index);
            printf("[%d]cam out %d\n", GV_Time, index);
        }

        iter++;
    }

    iter = msg;
    for (i = n_msg; i > 0; i--)
    {
        index = iter->message[0];
        type = iter->message[1];

        if (type == HASH_ENTER)
        {
            GM_event_camera_flag |= (1 << index);

            if (bitmap & (1 << index))
            {
                dword_800ABA90 &= ~(1 << index);
            }

            printf("[%d]cam in %d\n", GV_Time, index);
        }

        iter++;
    }
}

STATIC int CheckEvents(GV_ACT *work)
{
    int event;
    int changed;

    unsigned int mask;
    int i;
    int old_i;

    event = GM_event_camera_flag;

    if (GM_AlertMode == 3)
    {
        if (GM_Camera.alert_mask < 8)
        {
            event &= ~((1 << GM_Camera.alert_mask) - 1);
        }

        if (dword_800ABA94 != 0)
        {
            event &= ~dword_800ABA94;
        }
    }

    changed = event ^ dword_800ABA90;
    if (changed == 0)
    {
        return 0;
    }

    dword_800ABA90 = event;

    for (mask = 1, i = 0; i < 7; i++, mask <<= 1)
    {
        if (changed & mask)
        {
            break;
        }
    }

    changed = event;
    old_i = i;

    for (mask = 0x80, i = 7; i >= 0; i--, mask >>= 1)
    {
        if (changed & mask)
        {
            if (GM_CameraList[i].field_10_param1 != -1)
            {
                break;
            }

            GM_event_camera_flag &= ~mask;
        }
    }


    sub_8002FAAC(&GM_Camera.eye, &GM_Camera.center, &GM_Camera.rotate, &GM_Camera.track);
    ChangeCamera(i, old_i);
    printf("[%d]change camera %d\n", GV_Time, i);

    GM_GameStatus &= ~GAME_FLAG_BIT_07;

    if (GM_CameraList[i].field_0e_alertMask & 1)
    {
        GM_GameStatus |= GAME_FLAG_BIT_07;
    }

    return 1;
}

STATIC void sub_800303E0(SVECTOR *arg0)
{
    SVECTOR          vec;
    UnkCameraStruct *pUnkCamera;
    int              index;

    vec = *arg0;
    pUnkCamera = &gUnkCameraStruct_800B77B8;

    if (DG_UnDrawFrameCount > 0)
    {
        *arg0 = pUnkCamera->eye;
    }
    else
    {
        sub_8002EB80(&vec, &pUnkCamera->eye);
        GV_NearExp4V((short *)arg0, (short *)&vec, 3);
    }

#ifdef VR_EXE
    index = !!(GM_Camera.flags & 0x28);
#else
    index = !!(GM_Camera.flags & 0x20);
#endif

    sub_8002EBE8(arg0, index);
}

void sub_8003049C(SVECTOR *a1)
{
    GM_CAMERA *pCamera;

    pCamera = &GM_Camera;
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

STATIC void camera_act_8003059C(GV_ACT *work)
{
    int changed;

    int iVar2;

    if (GM_GameStatus >= 0)
    {
        if (GV_PauseLevel == 0)
        {
            CheckMessages(work);
            changed = CheckEvents(work);

            camera_act_helper3_8002F64C();

            if (GM_Camera.first_person == 1)
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

            if (changed)
            {
                svec_800ABA88 = GM_Camera.eye;
            }

            camera_act_helper4_8002F78C();
        }

        DG_LookAt(DG_Chanl(0),
            &gUnkCameraStruct2_800B7868.eye,
            &gUnkCameraStruct2_800B7868.center,
            gUnkCameraStruct2_800B7868.zoom);
    }
}

void *camera_init_800306A0(void)
{
    GV_ACT *work;

    work = GV_NewActor(GV_ACTOR_LEVEL2, sizeof(GV_ACT));
    if (work)
    {
        GV_SetNamedActor(work, camera_act_8003059C, NULL, "camera.c");
    }

    GM_Camera.zoom = 320;
    GM_Camera.first_person = 0;
    GM_Camera.flags = 0;
    GM_Camera.pan.pad = 0;
    gUnkCameraStruct2_800B7868.zoom = 320;
    dword_800ABA90 = 0;
    GM_event_camera_flag = 0;
    GM_CameraFirstPersonOrg = 0;
    GM_CameraFlagsOrg = 0;
    gUnkCameraStruct_800B77B8.track = 10000;
    GM_Camera.track = 10000;
    gUnkCameraStruct2_800B7868.track = 10000;
    sub_8002FCF0();
    gUnkCameraStruct_800B77B8.rotate2.vx = 0;
    gUnkCameraStruct_800B77B8.rotate2.vy = 2048;
    gUnkCameraStruct_800B77B8.rotate2.vz = 0;

    return (void *)work;
}

void GM_Reset_helper3_80030760()
{
    CAMERA    *cameraList, *cameraListIter;
    GM_CAMERA *gmCamera;
    int        i;
    int        field_10_param1;

    field_10_param1 = -1;
    i = 7;

    cameraList = GM_CameraList;
    cameraListIter = cameraList + 7;

    gmCamera = &GM_Camera;
    gmCamera->alert_mask = 100;

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

    GM_CameraRotateSave.vx = 0x280;
    GM_CameraRotateSave.vy = 0x800;
    GM_CameraRotateSave.vz = 0;

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

void GM_CameraSetAlertMask(unsigned int id, unsigned int mask)
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
    GM_Camera.bounds[1][param_e] = *min;
    GM_Camera.bounds[0][param_e] = *max;
}

void GM_CameraSetLimits_800308E0(SVECTOR *min, SVECTOR *max, int param_e)
{
    GM_Camera.limits[1][param_e] = *min;
    GM_Camera.limits[0][param_e] = *max;
}

void GM_CameraSetRotation_80030938(SVECTOR *rot)
{
    GM_CameraRotateSave = *rot;
    sub_8002FCF0();
}

void GM_CameraSetTrack_80030980(int track)
{
    GM_CameraTrackOrg = track;
    GM_CameraTrackSave = track;
    sub_8002FCF0();
}

void GM_CameraEventReset(void)
{
    dword_800ABA90 = 0;
    return;
}

void sub_800309B4(int param_1, int param_2)
{
    GM_Camera.field_2A = param_1;
    GM_Camera.interp = param_2;
    svec_800ABA88 = GM_Camera.eye;
}

void sub_800309F8(int param_1, int param_2)
{
    sub_800309B4(param_1, param_2);
    GM_Camera.flags |= 2;
}

void sub_80030A30()
{
    if (GM_Camera.first_person == 0)
    {
        gUnkCameraStruct_800B77B8.eye = gUnkCameraStruct_800B77B8.center = GM_Camera.center;
    }

    GM_Camera.flags &= ~2;
}

void GM_CameraBoundTrace(int param_1)
{
    sub_8002EADC(param_1);
}

void GM_CameraLimitTrace(int param_1)
{
    sub_8002EBE8(&GM_Camera.center, param_1);
}

void GM_ExitBehindCamera_80030AEC(void)
{
    if (GM_GameStatus & STATE_BEHIND_CAMERA)
    {
        GM_GameStatus &= ~STATE_BEHIND_CAMERA;
        GM_event_camera_flag &= ~8;
        dword_800ABA90 = dword_800ABA90 | 8;
    }

    GM_800AB448 = 0;
    GM_800AB444 = NULL;
}

void GM_CheckBehindCamera(HZD_HDL *pHzdMap, CONTROL *pControl)
{
    HZD_TRP *trp;
    CAMERA  *cam;
    short   *name;

    if ((GM_StatusEvent & 0x100 || GM_AlertMode != 3) &&
        (trp = HZD_CheckBehindTrap(pHzdMap, &pControl->mov)) != NULL)
    {
        if (GM_800AB444 != trp)
        {
            if (++GM_800AB448 >= 10)
            {
                GM_800AB444 = trp;

                cam = &GM_CameraList[3];
                cam->field_10_param1 = 1;
                cam->field_11_param2 = 2;
                cam->field_12_param3 = 0;
                cam->field_13_param_p = 2;
                cam->pos.pad = GV_GetPadOrigin();

                name = (short *)trp->name; // TODO: Is char[] name array in HZD_TRP correct? Is it really a name?
                cam->trg[0] = name[0];
                cam->trg[1] = name[1];
                cam->trg[2] = name[2];

                GM_event_camera_flag |= 8;
                dword_800ABA90 &= ~8;
                GM_GameStatus |= STATE_BEHIND_CAMERA;

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
