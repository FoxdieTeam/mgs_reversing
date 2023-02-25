#include "camera.h"

extern int dword_800ABA90;
int SECTION(".sbss") dword_800ABA90;

extern int GM_event_camera_flag_800ABA9C;
int SECTION(".sbss") GM_event_camera_flag_800ABA9C;

extern int GM_CameraTrackOrg_800AB43C;
int SECTION(".sdata") GM_CameraTrackOrg_800AB43C;

extern int GM_CameraTrackOrg_800AB440;
int SECTION(".sdata") GM_CameraTrackOrg_800AB440;

extern const char aCameraC[];
extern SVECTOR svec_800ABA88;
extern int GV_PauseLevel_800AB928;
extern GM_Camera GM_Camera_800B77E8;
extern UnkCameraStruct gUnkCameraStruct_800B77B8;
extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;

#pragma INCLUDE_ASM("asm/sub_8002EADC.s") // 164 bytes

void sub_8002FC58(SVECTOR *param_1, SVECTOR *param_2, SVECTOR *param_3, int *param_4);
void sub_8002FCA4(SVECTOR *param_1, SVECTOR *param_2, SVECTOR *param_3, int *param_4);
void sub_8002FBC0(SVECTOR *pVec1, SVECTOR *pVec2, SVECTOR *pVec3, int *pLen);
void sub_8002FAAC(SVECTOR *a1, SVECTOR *a2, SVECTOR *a3, int *a4);

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

#pragma INCLUDE_ASM("asm/sub_8002EBE8.s") // 164 bytes

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

extern GM_Camera GM_Camera_800B77E8;

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
#pragma INCLUDE_ASM("asm/sub_8002ED68.s") // 156 bytes

extern UnkCameraStruct2 gUnkCameraStruct2_800B76F0;

void sub_8002EE04()
{
    GM_Camera_800B77E8.field_0 = gUnkCameraStruct2_800B76F0.field_0;
    GM_Camera_800B77E8.field_8 = gUnkCameraStruct2_800B76F0.field_8;
    GM_Camera_800B77E8.field_28 = 0;
    sub_8002ED68(0);
}

#pragma INCLUDE_ASM("asm/sub_8002EE80.s") // 136 bytes

void sub_8002EF08()
{
    GM_Camera_800B77E8.field_0 = gUnkCameraStruct2_800B76F0.field_0;
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
        sub_800268AC(&GM_Camera_800B77E8.field_0.vx, &gUnkCameraStruct_800B77B8.field_0.vx, iVar1, 3);
        sub_80026BC4(&GM_Camera_800B77E8.field_10.vx, &gUnkCameraStruct_800B77B8.field_28.vx, iVar1, 3);
        GM_Camera_800B77E8.field_1C = sub_800264B0(GM_Camera_800B77E8.field_1C, 1000, iVar1);
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

#pragma INCLUDE_ASM("asm/sub_8002F274.s") // 272 bytes
#pragma INCLUDE_ASM("asm/Game/camera_act_helper2_helper_8002F384.s") // 576 bytes
#pragma INCLUDE_ASM("asm/Game/camera_act_helper2_8002F5C4.s") // 136 bytes

#pragma INCLUDE_ASM("asm/Game/camera_act_helper3_8002F64C.s") // 320 bytes

#pragma INCLUDE_ASM("asm/Game/camera_act_helper4_8002F78C.s") // 800 bytes


void sub_8002FAAC(SVECTOR *a1, SVECTOR *a2, SVECTOR *a3, int *a4)
{
    if ( !gUnkCameraStruct2_800B7868.field_20 )
    {
        *a1 = gUnkCameraStruct2_800B7868.field_0;
        *a2 = gUnkCameraStruct2_800B7868.field_8;
        sub_8002FBC0(a1, a2, a3, a4);
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

void sub_8002FBC0(SVECTOR *pVec1, SVECTOR *pVec2, SVECTOR *pVec3, int *pLen)
{
    SVECTOR vec;
    GV_SubVec3_80016D40(pVec2, pVec1, &vec);
    *pLen = GV_VecLen3_80016D80(&vec);
    pVec3->vz = 0;
    pVec3->vy = GV_VecDir2_80016EF8(&vec);
    pVec3->vx = ratan2_80094308(-vec.vy, SquareRoot0_80092708(vec.vx * vec.vx + vec.vz * vec.vz));
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

extern int     GM_CameraTrackSave_800AB42C;
int            SECTION(".sdata") GM_CameraTrackSave_800AB42C;

extern SVECTOR GM_CameraRotateSave_800AB430;
SVECTOR        SECTION(".sdata") GM_CameraRotateSave_800AB430;

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

void sub_8002FD84(int index, TGMCameraFunc func)
{
    GM_Camera_800B77E8.field_74_funcs[index] = func;
}

#pragma INCLUDE_ASM("asm/Game/camera_act_helper6_helper_8002FD9C.s") // 892 bytes
#pragma INCLUDE_ASM("asm/Game/camera_act_helper5_80030118.s") // 312 bytes
#pragma INCLUDE_ASM("asm/Game/camera_act_helper6_80030250.s") // 400 bytes
#pragma INCLUDE_ASM("asm/sub_800303E0.s") // 188 bytes
#pragma INCLUDE_ASM("asm/sub_8003049C.s") // 256 bytes

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

        DG_800172D0(DG_Chanl(0),
            &gUnkCameraStruct2_800B7868.field_0,
            &gUnkCameraStruct2_800B7868.field_8,
            gUnkCameraStruct2_800B7868.field_1C);
    }
}

GV_ACT *camera_init_800306A0()
{
    GV_ACT *pActor;

    pActor = GV_NewActor_800150E4(2, 0x20);
    if (pActor)
    {
        GV_SetNamedActor_8001514C(pActor, camera_act_8003059C, NULL, aCameraC); // "camera.c"
    }

    GM_Camera_800B77E8.field_20 = 320;
    GM_Camera_800B77E8.field_22 = 0;
    GM_Camera_800B77E8.field_18_flags = 0;
    GM_Camera_800B77E8.field_32 = 0;
    gUnkCameraStruct2_800B7868.field_1C = 320;
    dword_800ABA90 = 0;
    GM_event_camera_flag_800ABA9C = 0;
    GM_CameraTrackOrg_800AB43C = 0;
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
