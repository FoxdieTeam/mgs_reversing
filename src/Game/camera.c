
#include "camera.h"
#include "linkvarbuf.h"

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
int      GM_CameraTrackOrg_800AB440 = 0;
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

    GM_Camera_800B77E8.field_0.vx = camera_clamp(GM_Camera_800B77E8.field_0.vx, pVec[8].vz,  pVec[6].vz);
    GM_Camera_800B77E8.field_0.vy = camera_clamp(GM_Camera_800B77E8.field_0.vy, pVec[8].pad, pVec[6].pad);
    GM_Camera_800B77E8.field_0.vz = camera_clamp(GM_Camera_800B77E8.field_0.vz, pVec[9].vx,  pVec[7].vx);
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
    return GM_Camera_800B77E8.field_18_flags & mask;
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
        GV_OriginPadSystem_80016C78(0);
        return;

    case 1:
        if (arg0 != 0)
        {
            camera_get_euler_angles_8002FBC0(&GM_Camera_800B77E8.field_0, &GM_Camera_800B77E8.field_8, &gUnkCameraStruct2_800B76F0.field_10, &gUnkCameraStruct2_800B76F0.field_18);
        }

        GV_OriginPadSystem_80016C78(gUnkCameraStruct2_800B76F0.field_10.vy + 2048);
        break;

    case 2:
        GV_OriginPadSystem_80016C78(gUnkCameraStruct2_800B76F0.eye.pad >> 2);
        break;

    default:
        break;
    }
}

void sub_8002EE04()
{
    GM_Camera_800B77E8.field_0 = gUnkCameraStruct2_800B76F0.eye;
    GM_Camera_800B77E8.field_8 = gUnkCameraStruct2_800B76F0.center;
    GM_Camera_800B77E8.field_28 = 0;
    sub_8002ED68(0);
}

void sub_8002EE80(void)
{
    gUnkCameraStruct2_800B76F0.center.vz = gUnkCameraStruct_800B77B8.field_8.vz;
    GM_Camera_800B77E8.field_0 = gUnkCameraStruct2_800B76F0.eye;
    GM_Camera_800B77E8.field_8 = gUnkCameraStruct2_800B76F0.center;
    GM_Camera_800B77E8.field_28 = 0;
    GV_OriginPadSystem_80016C78(0);
}

void sub_8002EF08()
{
    GM_Camera_800B77E8.field_0 = gUnkCameraStruct2_800B76F0.eye;
    GM_Camera_800B77E8.field_8 = gUnkCameraStruct_800B77B8.field_8;
    GM_Camera_800B77E8.field_28 = 0;
    sub_8002ED68(1);
}

void sub_8002EF88()
{
    int unused[2]; (void)unused;
    GM_Camera_800B77E8.field_8 = gUnkCameraStruct_800B77B8.field_8;
    GM_Camera_800B77E8.field_1C = gUnkCameraStruct_800B77B8.field_18;
    GM_Camera_800B77E8.field_10 = gUnkCameraStruct_800B77B8.field_10;
    GM_Camera_800B77E8.field_28 = 2;
    GV_OriginPadSystem_80016C78(0);
}

void camera_act_helper_helper_8002F008()
{
    GM_Camera_800B77E8.field_0 = gUnkCameraStruct_800B77B8.field_0;
    GM_Camera_800B77E8.field_1C = 1000;
    GM_Camera_800B77E8.field_10 = gUnkCameraStruct_800B77B8.field_28;
    GM_Camera_800B77E8.field_28 = 1;
    GV_OriginPadSystem_80016C78(gUnkCameraStruct_800B77B8.field_28.vy + 2048);
}

void camera_act_helper_helper2_8002F094(int param_1)
{
    int iVar1;
    SVECTOR vec;

    if (param_1 < 6)
    {
        GV_NearExp4V_800266D4(&GM_Camera_800B77E8.field_8.vx, &gUnkCameraStruct_800B77B8.field_0.vx, 3);
        GV_NearExp4PV_800269A0(&GM_Camera_800B77E8.field_10.vx, &gUnkCameraStruct_800B77B8.field_28.vx, 3);
        GM_Camera_800B77E8.field_1C = GV_NearExp4_800263B0(GM_Camera_800B77E8.field_1C, 1000);
        GV_DirVec3_80016FA0(&GM_Camera_800B77E8.field_10, GM_Camera_800B77E8.field_1C, &vec);
        sub_8002ECE4(&GM_Camera_800B77E8.field_8, &vec, &GM_Camera_800B77E8.field_0);
        GM_Camera_800B77E8.field_28 = 0;
    }
    else
    {
        iVar1 = 12 - param_1;
        GV_NearTimeSV_800268AC(&GM_Camera_800B77E8.field_0.vx, &gUnkCameraStruct_800B77B8.field_0.vx, iVar1, 3);
        GV_NearTimePV_80026BC4(&GM_Camera_800B77E8.field_10.vx, &gUnkCameraStruct_800B77B8.field_28.vx, iVar1, 3);
        GM_Camera_800B77E8.field_1C = GV_NearTime_800264B0(GM_Camera_800B77E8.field_1C, 1000, iVar1);
        GV_DirVec3_80016FA0(&GM_Camera_800B77E8.field_10, GM_Camera_800B77E8.field_1C, &vec);
        sub_8002EC8C(&GM_Camera_800B77E8.field_0, &vec, &GM_Camera_800B77E8.field_8);
        GM_Camera_800B77E8.field_28 = 0;
    }

    GV_OriginPadSystem_80016C78(0);
}

void camera_act_helper_8002F1C8(void)
{
    if (GM_Camera_800B77E8.field_18_flags & 0x100)
    {
        if (gUnkCameraStruct_800B77B8.field_24 >= 12)
        {
            GM_Camera_800B77E8.field_18_flags &= ~0x101;
        }

        camera_act_helper_helper2_8002F094(gUnkCameraStruct_800B77B8.field_24);
    }
    else if (GM_Camera_800B77E8.field_18_flags & 0x200)
    {
        if (GM_Camera_800B77E8.field_74_funcs[0])
        {
            GM_Camera_800B77E8.field_74_funcs[0]();
        }
    }
    else
    {
        camera_act_helper_helper_8002F008();
    }

    gUnkCameraStruct_800B77B8.field_24++;
}

int sub_8002F274(void)
{
    if (GM_Camera_800B77E8.field_2C.pad == 1)
    {
        GV_AddVec3_80016D00(&gUnkCameraStruct_800B77B8.field_0, &GM_Camera_800B77E8.field_2C, &gUnkCameraStruct_800B77B8.field_0);
        GM_Camera_800B77E8.field_2C.pad = 0;
    }

    sub_800303E0(&gUnkCameraStruct_800B77B8.field_8);

    if (GM_Camera_800B77E8.field_18_flags & 0x20)
    {
        sub_8002EF88();
        return 2;
    }

    else if (GM_Camera_800B77E8.field_18_flags & 0x10)
    {
        sub_8002EE04();
    }
    else if (GM_Camera_800B77E8.field_18_flags & 8)
    {
        sub_8002EE80();
    }
    else if (GM_Camera_800B77E8.field_18_flags & 4)
    {
        sub_8002EF08();
    }
    else if (GM_Camera_800B77E8.field_18_flags & 2)
    {
        if (GM_Camera_800B77E8.field_74_funcs[1])
        {
            GM_Camera_800B77E8.field_74_funcs[1]();
        }

        if ((GM_Camera_800B77E8.field_18_flags & 0x80))
        {
            return 1;
        }
        else if (GM_Camera_800B77E8.field_18_flags & 0x40)
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
        GV_NearTimeSV_800268AC(&GM_Camera_800B77E8.field_8.vx, &gUnkCameraStruct_800B77B8.field_0.vx, 2 - arg0, 3);
        GV_NearTimePV_80026BC4(&GM_Camera_800B77E8.field_10.vx, &gUnkCameraStruct_800B77B8.field_28.vx, 2 - arg0, 3);
        GM_Camera_800B77E8.field_1C = GV_NearTime_800264B0(GM_Camera_800B77E8.field_1C, 1000, 2 - arg0);
        GV_OriginPadSystem_80016C78(0);
    }
    else
    {
        if (arg0 < 4)
        {
            var_s5 = &GV_NearExp4V_800266D4;
            var_s6 = &GV_NearExp4PV_800269A0;
            var_s4 = &GV_NearExp4_800263B0;
        }
        else
        {
            var_s5 = &GV_NearExp2V_8002667C;
            var_s6 = &GV_NearExp2PV_80026924;
            var_s4 = &GV_NearExp2_80026384;
        }

        vec = GM_Camera_800B77E8.field_8;
        vec2 = GM_Camera_800B77E8.field_10;

        temp_s3 = GM_Camera_800B77E8.field_1C;
        var_s7 = sub_8002F274();

        switch (GM_Camera_800B77E8.field_28)
        {
        case 0:
            camera_get_euler_angles_8002FBC0(&GM_Camera_800B77E8.field_0, &GM_Camera_800B77E8.field_8, &GM_Camera_800B77E8.field_10, &GM_Camera_800B77E8.field_1C);
            break;

        case 1:
            sub_8002FC58(&GM_Camera_800B77E8.field_0, &GM_Camera_800B77E8.field_8, &GM_Camera_800B77E8.field_10, &GM_Camera_800B77E8.field_1C);
            break;
        }

        var_s5(&vec.vx, &GM_Camera_800B77E8.field_8.vx, 3);
        var_s6(&vec2.vx, &GM_Camera_800B77E8.field_10.vx, 3);

        temp_v0 = var_s4(temp_s3, GM_Camera_800B77E8.field_1C);

        GM_Camera_800B77E8.field_8 = vec;
        GM_Camera_800B77E8.field_10 = vec2;
        GM_Camera_800B77E8.field_1C = temp_v0;
    }

    GM_Camera_800B77E8.field_28 = 2;
    temp_s3 = var_s7;

    return temp_s3;
}

int camera_act_helper2_8002F5C4(void)
{
    int ret;

    if (GM_Camera_800B77E8.field_18_flags & 1)
    {
        if (gUnkCameraStruct_800B77B8.field_24 >= 12)
        {
            GM_Camera_800B77E8.field_18_flags &= ~0x101;
            GM_Camera_800B77E8.field_26 = -1;
            GM_Camera_800B77E8.field_2A = 0;
        }

        ret = camera_act_helper2_helper_8002F384(gUnkCameraStruct_800B77B8.field_24);
        gUnkCameraStruct_800B77B8.field_24++;

        return ret;
    }

    return sub_8002F274();
}

void camera_act_helper3_8002F64C(void)
{
    if (GM_Camera_800B77E8.field_22 != GM_800AB43C)
    {
        gUnkCameraStruct_800B77B8.field_24 = 0;
        GM_Camera_800B77E8.field_2A = 0;

        if (GM_Camera_800B77E8.field_22 == 0)
        {
            GM_Camera_800B77E8.field_18_flags |= 1;
            sub_8002FAAC(&GM_Camera_800B77E8.field_0, &GM_Camera_800B77E8.field_8, &GM_Camera_800B77E8.field_10, &GM_Camera_800B77E8.field_1C);
        }
        else if (GM_Camera_800B77E8.field_22 == 1)
        {
            GM_Camera_800B77E8.field_18_flags |= 0x100;
            sub_8002FAAC(&GM_Camera_800B77E8.field_0, &GM_Camera_800B77E8.field_8, &GM_Camera_800B77E8.field_10, &GM_Camera_800B77E8.field_1C);

            if (!(GM_Camera_800B77E8.field_18_flags & 1))
            {
                if (camera_act_helper3_helper_8002ED3C() & 0x3001E)
                {
                    gUnkCameraStruct_800B77B8.field_10 = GM_Camera_800B77E8.field_10;
                    gUnkCameraStruct_800B77B8.field_18 = GM_Camera_800B77E8.field_1C;
                }
                else
                {
                    sub_8002FCF0();
                }
            }
        }
        else
        {
            GM_Camera_800B77E8.field_22 = 1;
        }
    }

    if (GM_Camera_800B77E8.field_18_flags != GM_CameraTrackOrg_800AB440)
    {
        gUnkCameraStruct_800B77B8.field_24 = 0;
    }

    GM_800AB43C = GM_Camera_800B77E8.field_22;
    GM_CameraTrackOrg_800AB440 = GM_Camera_800B77E8.field_18_flags;
}

void camera_act_helper4_8002F78C(void)
{
    SVECTOR vec;

    gUnkCameraStruct2_800B7868.field_20 = 0;
    gUnkCameraStruct2_800B7868.field_18 = GM_Camera_800B77E8.field_1C;
    gUnkCameraStruct2_800B7868.clip_distance = GM_Camera_800B77E8.field_20;

    if (GM_Camera_800B77E8.field_2A == 0)
    {
        gUnkCameraStruct2_800B7868.eye = GM_Camera_800B77E8.field_0;
        gUnkCameraStruct2_800B7868.field_10 = GM_Camera_800B77E8.field_10;
        gUnkCameraStruct2_800B7868.center = GM_Camera_800B77E8.field_8;
    }
    else
    {
        camera_get_euler_angles_8002FBC0(&GM_Camera_800B77E8.field_0, &GM_Camera_800B77E8.field_8, &GM_Camera_800B77E8.field_10, &GM_Camera_800B77E8.field_1C);

        GV_SubVec3_80016D40(&GM_Camera_800B77E8.field_0, &svec_800ABA88, &vec);
        GV_AddVec3_80016D00(&vec, &gUnkCameraStruct2_800B7868.eye, &gUnkCameraStruct2_800B7868.eye);

        svec_800ABA88 = GM_Camera_800B77E8.field_0;

        if (GM_Camera_800B77E8.field_2A == 3)
        {
            GV_NearTimeSV_800268AC(&gUnkCameraStruct2_800B7868.eye.vx, &GM_Camera_800B77E8.field_0.vx, GM_Camera_800B77E8.field_26, 3);
            GV_NearTimePV_80026BC4(&gUnkCameraStruct2_800B7868.field_10.vx, &GM_Camera_800B77E8.field_10.vx, GM_Camera_800B77E8.field_26, 3);
        }
        else if (GM_Camera_800B77E8.field_2A == 1)
        {
            GV_NearExp2V_8002667C(&gUnkCameraStruct2_800B7868.eye.vx, &GM_Camera_800B77E8.field_0.vx, 3);
            GV_NearExp2PV_80026924(&gUnkCameraStruct2_800B7868.field_10.vx, &GM_Camera_800B77E8.field_10.vx, 3);
        }
        else if (GM_Camera_800B77E8.field_2A == 2)
        {
            GV_NearExp4V_800266D4(&gUnkCameraStruct2_800B7868.eye.vx, &GM_Camera_800B77E8.field_0.vx, 3);
            GV_NearExp4PV_800269A0(&gUnkCameraStruct2_800B7868.field_10.vx, &GM_Camera_800B77E8.field_10.vx, 3);
        }

        if (gUnkCameraStruct2_800B7868.field_18 > 10000)
        {
            gUnkCameraStruct2_800B7868.field_18 = 10000;
        }

        sub_8002FC58(&gUnkCameraStruct2_800B7868.eye, &gUnkCameraStruct2_800B7868.center, &gUnkCameraStruct2_800B7868.field_10, &gUnkCameraStruct2_800B7868.field_18);

        if (--GM_Camera_800B77E8.field_26 < 0)
        {
            GM_Camera_800B77E8.field_2A = 0;
            GM_Camera_800B77E8.field_26 = -1;
        }
    }

    if (GM_NoisePower_800ABA24 >= 255)
    {
        if (GM_Camera_800B77E8.field_22 == 0)
        {
            gUnkCameraStruct2_800B7868.eye.vy += (GV_RandS_800170BC(512) * GM_NoiseLength_800ABA30) / 32;
        }
        else
        {
            gUnkCameraStruct2_800B7868.eye.vy += (GV_RandS_800170BC(512) * GM_NoiseLength_800ABA30) / 128;
        }
    }

    if (GM_Camera_800B77E8.field_22 == 0)
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

void sub_8002FAAC(SVECTOR *a1, SVECTOR *a2, SVECTOR *a3, int *a4)
{
    if ( !gUnkCameraStruct2_800B7868.field_20 )
    {
        *a1 = gUnkCameraStruct2_800B7868.eye;
        *a2 = gUnkCameraStruct2_800B7868.center;
        camera_get_euler_angles_8002FBC0(a1, a2, a3, a4);
        gUnkCameraStruct2_800B7868.field_10 = *a3;
    }
}

void camera_act_helper7_8002FB54()
{
    switch (GM_Camera_800B77E8.field_28)
    {
    case 0:
        break;
    case 1:
        sub_8002FC58(&GM_Camera_800B77E8.field_0, &GM_Camera_800B77E8.field_8, &GM_Camera_800B77E8.field_10,
                     &GM_Camera_800B77E8.field_1C);
        break;
    case 2:

        sub_8002FCA4(&GM_Camera_800B77E8.field_0, &GM_Camera_800B77E8.field_8, &GM_Camera_800B77E8.field_10,
                     &GM_Camera_800B77E8.field_1C);
        break;
    }
}

void camera_get_euler_angles_8002FBC0(SVECTOR *eye, SVECTOR *center, SVECTOR *euler, int *length)
{
    SVECTOR forward;

    GV_SubVec3_80016D40(center, eye, &forward);
    *length = GV_VecLen3_80016D80(&forward);

    euler->vz = 0;
    euler->vy = GV_VecDir2_80016EF8(&forward);
    euler->vx = ratan2(-forward.vy, SquareRoot0(forward.vx * forward.vx + forward.vz * forward.vz));
}

void sub_8002FC58(SVECTOR *param_1, SVECTOR *param_2, SVECTOR *param_3, int *param_4)
{
    SVECTOR vec;
    GV_DirVec3_80016FA0(param_3, *param_4, &vec);
    sub_8002EC8C(param_1, &vec, param_2);
}

void sub_8002FCA4(SVECTOR *param_1, SVECTOR *param_2, SVECTOR *param_3, int *param_4)
{
    SVECTOR vec;

    GV_DirVec3_80016FA0(param_3, *param_4, &vec);
    sub_8002ECE4(param_2, &vec, param_1);
}

void sub_8002FCF0(void)
{
    if (!(GM_Camera_800B77E8.field_18_flags & 0x20))
    {
        gUnkCameraStruct_800B77B8.field_18 = GM_CameraTrackSave_800AB42C;
        gUnkCameraStruct_800B77B8.field_10 = GM_CameraRotateSave_800AB430;
    }
    else
    {
        gUnkCameraStruct_800B77B8.field_18 = gUnkCameraStruct2_800B76F0.field_18;
        gUnkCameraStruct_800B77B8.field_10 = gUnkCameraStruct2_800B76F0.field_10;
    }
}

void GM_SetCameraCallbackFunc_8002FD84(int index, TGMCameraFunc func)
{
    GM_Camera_800B77E8.field_74_funcs[index] = func;
}

void camera_act_helper6_helper_8002FD9C(int cam1, int cam2)
{
    CAMERA *pCamera;
    int cam_param1;

    GM_Camera_800B77E8.field_18_flags &= ~0x3C;

    if (cam1 == -1)
    {
        if (!(GM_Camera_800B77E8.field_18_flags & 2))
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
            GM_Camera_800B77E8.field_18_flags |= 0x20;

            gUnkCameraStruct_800B77B8.field_10.vx = pCamera->field_08_trg[0];
            gUnkCameraStruct_800B77B8.field_10.vy = pCamera->field_08_trg[1];
            gUnkCameraStruct_800B77B8.field_10.vz = 0;

            gUnkCameraStruct2_800B76F0.center = gUnkCameraStruct_800B77B8.field_8;
            gUnkCameraStruct2_800B76F0.field_10 = gUnkCameraStruct_800B77B8.field_10;
            gUnkCameraStruct2_800B76F0.field_18 = gUnkCameraStruct_800B77B8.field_18 = pCamera->field_08_trg[2];

            sub_8002FCA4(&gUnkCameraStruct2_800B76F0.eye, &gUnkCameraStruct2_800B76F0.center, &gUnkCameraStruct2_800B76F0.field_10, &gUnkCameraStruct2_800B76F0.field_18);
        }
        else
        {
            switch (pCamera->field_12_param3)
            {
            case 0:
                gUnkCameraStruct2_800B76F0.eye = pCamera->field_00_pos;
                gUnkCameraStruct2_800B76F0.center = *(SVECTOR *)pCamera->field_08_trg;
                camera_get_euler_angles_8002FBC0(&gUnkCameraStruct2_800B76F0.eye, &gUnkCameraStruct2_800B76F0.center, &gUnkCameraStruct2_800B76F0.field_10, &gUnkCameraStruct2_800B76F0.field_18);
                break;

            case 1:
                gUnkCameraStruct2_800B76F0.eye = pCamera->field_00_pos;

                gUnkCameraStruct2_800B76F0.field_10.vx = pCamera->field_08_trg[0];
                gUnkCameraStruct2_800B76F0.field_10.vy = pCamera->field_08_trg[1];
                gUnkCameraStruct2_800B76F0.field_10.vz = 0;
                gUnkCameraStruct2_800B76F0.field_18 = pCamera->field_08_trg[2];

                sub_8002FC58(&gUnkCameraStruct2_800B76F0.eye, &gUnkCameraStruct2_800B76F0.center, &gUnkCameraStruct2_800B76F0.field_10, &gUnkCameraStruct2_800B76F0.field_18);
                break;

            case 2:
                gUnkCameraStruct2_800B76F0.center = pCamera->field_00_pos;

                gUnkCameraStruct2_800B76F0.field_10.vx = pCamera->field_08_trg[0];
                gUnkCameraStruct2_800B76F0.field_10.vy = pCamera->field_08_trg[1];
                gUnkCameraStruct2_800B76F0.field_10.vz = 0;
                gUnkCameraStruct2_800B76F0.field_18 = pCamera->field_08_trg[2];

                sub_8002FCA4(&gUnkCameraStruct2_800B76F0.eye, &gUnkCameraStruct2_800B76F0.center, &gUnkCameraStruct2_800B76F0.field_10, &gUnkCameraStruct2_800B76F0.field_18);
                break;
            }

            gUnkCameraStruct2_800B76F0.eye.pad = pCamera->field_13_param_p | ((unsigned short)pCamera->field_00_pos.pad * 4);
            gUnkCameraStruct2_800B76F0.field_20 = 0;

            if (cam_param1 == 1)
            {
                GM_Camera_800B77E8.field_18_flags |= 0x10;
            }
            else if (cam_param1 == 2)
            {
                GM_Camera_800B77E8.field_18_flags |= 0x8;
            }
            else
            {
                GM_Camera_800B77E8.field_18_flags |= 0x4;
            }
        }
    }

    if ((GM_Camera_800B77E8.field_22 == 1) || (DG_UnDrawFrameCount_800AB380 > 0))
    {
        GM_Camera_800B77E8.field_2A = 0;
        GM_Camera_800B77E8.field_26 = -1;
    }
    else if (cam2 < 0)
    {
        GM_Camera_800B77E8.field_2A = 2;
        GM_Camera_800B77E8.field_26 = 30;
    }
    else
    {
        pCamera = &GM_CameraList_800B7718[cam2];
        GM_Camera_800B77E8.field_2A = dword_80010C60[pCamera->field_11_param2];
        GM_Camera_800B77E8.field_26 = dword_80010C60[pCamera->field_11_param2] >> 16;
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

    msgLen = GV_ReceiveMessage_80016620(0xC356, &pMsg);

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

        if (type == 0xD5CC)
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

        if (type == 0xDD2)
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


    sub_8002FAAC(&GM_Camera_800B77E8.field_0, &GM_Camera_800B77E8.field_8, &GM_Camera_800B77E8.field_10, &GM_Camera_800B77E8.field_1C);
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
        *arg0 = pUnkCamera->field_0;
    }
    else
    {
        sub_8002EB80(&vec, &pUnkCamera->field_0);
        GV_NearExp4V_800266D4((short *)arg0, (short *)&vec, 3);
    }

#ifdef VR_EXE
    index = !!(GM_Camera_800B77E8.field_18_flags & 0x28);
#else
    index = !!(GM_Camera_800B77E8.field_18_flags & 0x20);
#endif

    sub_8002EBE8(arg0, index);
}

void sub_8003049C(SVECTOR *a1)
{
    GM_Camera *pCamera;

    pCamera = &GM_Camera_800B77E8;
    pCamera->field_2C = *a1;
    pCamera->field_2C.pad = 1;

    GV_AddVec3_80016D00(&gUnkCameraStruct2_800B7868.eye, a1, &gUnkCameraStruct2_800B7868.eye);
    GV_AddVec3_80016D00(&gUnkCameraStruct2_800B7868.center, a1, &gUnkCameraStruct2_800B7868.center);

    GV_AddVec3_80016D00(&pCamera->field_0, a1, &pCamera->field_0);
    GV_AddVec3_80016D00(&pCamera->field_8, a1, &pCamera->field_8);

    GV_AddVec3_80016D00(&gUnkCameraStruct_800B77B8.field_1C, a1, &gUnkCameraStruct_800B77B8.field_1C);
    GV_AddVec3_80016D00(&gUnkCameraStruct_800B77B8.field_0, a1, &gUnkCameraStruct_800B77B8.field_0);
    GV_AddVec3_80016D00(&gUnkCameraStruct_800B77B8.field_8, a1, &gUnkCameraStruct_800B77B8.field_8);

    GV_AddVec3_80016D00(&svec_800ABA88, a1, &svec_800ABA88);
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

            if (GM_Camera_800B77E8.field_22 == 1)
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
                svec_800ABA88 = GM_Camera_800B77E8.field_0;
            }

            camera_act_helper4_8002F78C();
        }

        DG_LookAt_800172D0(DG_Chanl(0),
            &gUnkCameraStruct2_800B7868.eye,
            &gUnkCameraStruct2_800B7868.center,
            gUnkCameraStruct2_800B7868.clip_distance);
    }
}

GV_ACT *camera_init_800306A0()
{
    GV_ACT *pActor;

    pActor = GV_NewActor_800150E4(2, sizeof(GV_ACT));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(pActor, camera_act_8003059C, NULL, "camera.c");
    }

    GM_Camera_800B77E8.field_20 = 320;
    GM_Camera_800B77E8.field_22 = 0;
    GM_Camera_800B77E8.field_18_flags = 0;
    GM_Camera_800B77E8.field_2C.pad = 0;
    gUnkCameraStruct2_800B7868.clip_distance = 320;
    dword_800ABA90 = 0;
    GM_event_camera_flag_800ABA9C = 0;
    GM_800AB43C = 0;
    GM_CameraTrackOrg_800AB440 = 0;
    gUnkCameraStruct_800B77B8.field_18 = 10000;
    GM_Camera_800B77E8.field_1C = 10000;
    gUnkCameraStruct2_800B7868.field_18 = 10000;
    sub_8002FCF0();
    gUnkCameraStruct_800B77B8.field_28.vx = 0;
    gUnkCameraStruct_800B77B8.field_28.vy = 2048;
    gUnkCameraStruct_800B77B8.field_28.vz = 0;

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
    gmCamera->field_34[0][0].vx = 0x7fff;
    gmCamera->field_34[0][0].vy = 0x7fff;
    gmCamera->field_34[0][0].vz = 0x7fff;
    gmCamera->field_34[1][0].vx = -0x7fff;
    gmCamera->field_34[1][0].vy = -0x7fff;
    gmCamera->field_34[1][0].vz = -0x7fff;
    gmCamera->field_34[2][0].vx = 0x7fff;
    gmCamera->field_34[2][0].vy = 0x7fff;
    gmCamera->field_34[2][0].vz = 0x7fff;
    gmCamera->field_34[3][0].vx = -0x7fff;
    gmCamera->field_34[3][0].vy = -0x7fff;
    gmCamera->field_34[3][0].vz = -0x7fff;
    gmCamera->field_34[0][1].vx = 0x7fff;
    gmCamera->field_34[0][1].vy = 0x7fff;
    gmCamera->field_34[0][1].vz = 0x7fff;
    gmCamera->field_34[1][1].vx = -0x7fff;
    gmCamera->field_34[1][1].vy = -0x7fff;
    gmCamera->field_34[1][1].vz = -0x7fff;
    gmCamera->field_34[2][1].vx = 0x7fff;
    gmCamera->field_34[2][1].vy = 0x7fff;
    gmCamera->field_34[2][1].vz = 0x7fff;
    gmCamera->field_34[3][1].vx = -0x7fff;
    gmCamera->field_34[3][1].vy = -0x7fff;
    gmCamera->field_34[3][1].vz = -0x7fff;

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
    gUnkCameraStruct_800B77B8.field_8 = gUnkCameraStruct_800B77B8.field_0;
}

void GM_CameraSetAlertMask_80030850(unsigned int a1, unsigned int a2)
{
    int v2;
    int result;

    if ((a2 & 2) != 0)
    {
        v2 = 1 << a1;
    }

    else
    {
        v2 = 0;
    }

    result = ~(1 << a1);
    dword_800ABA94 = (dword_800ABA94 & result) | v2;
}

void GCL_Command_camera_helper_80030888(SVECTOR *vec1, SVECTOR *vec2, int param_3_bool)
{
    GM_Camera_800B77E8.field_34[1][param_3_bool] = *vec1;
    GM_Camera_800B77E8.field_34[0][param_3_bool] = *vec2;
}

void GCL_Command_camera_helper2_800308E0(SVECTOR *vec1, SVECTOR *vec2, int param_3_bool)
{
    GM_Camera_800B77E8.field_34[3][param_3_bool] = *vec1;
    GM_Camera_800B77E8.field_34[2][param_3_bool] = *vec2;
}

void GCL_Command_camera_helper3_80030938(SVECTOR *pVec)
{
    GM_CameraRotateSave_800AB430 = *pVec;
    sub_8002FCF0();
}

void GCL_Command_camera_helper4_80030980(int param_1)
{
    GM_CameraTrackOrg_800AB438 = param_1;
    GM_CameraTrackSave_800AB42C = param_1;

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
    GM_Camera_800B77E8.field_26 = param_2;
    svec_800ABA88 = GM_Camera_800B77E8.field_0;
}

void sub_800309F8(int param_1, int param_2)
{
    sub_800309B4(param_1, param_2);
    GM_Camera_800B77E8.field_18_flags |= 2;
}

void sub_80030A30()
{
    if (GM_Camera_800B77E8.field_22 == 0)
    {
        gUnkCameraStruct_800B77B8.field_0 = gUnkCameraStruct_800B77B8.field_8 = GM_Camera_800B77E8.field_8;
    }

    GM_Camera_800B77E8.field_18_flags &= ~2;
}

void GM_CameraBoundTrace_80030AA4(int param_1)
{
    sub_8002EADC(param_1);
}

void GM_CameraLimitTrace_80030AC4(int param_1)
{
    sub_8002EBE8(&GM_Camera_800B77E8.field_8, param_1);
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
                cam->field_00_pos.pad = GV_GetPadOrigin_80016C84();

                name = (short *)trp->name; // TODO: Is char[] name array in HZD_TRP correct? Is it really a name?
                cam->field_08_trg[0] = name[0];
                cam->field_08_trg[1] = name[1];
                cam->field_08_trg[2] = name[2];

                GM_event_camera_flag_800ABA9C |= 8;
                dword_800ABA90 &= ~8;
                GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_05;

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
