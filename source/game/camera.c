#include "camera.h"

#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"

#include "game.h"
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

extern GM_CameraSystemWork        GM_Camera;
extern GM_SnakeCameraWork  GM_SnakeCamera;
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

static void MakeRotate( SVECTOR *cam, SVECTOR *trg, SVECTOR *rot, int *track );
static void MakeTarget( SVECTOR *cam, SVECTOR *trg, SVECTOR *rot, int *track );
static void MakeCamera( SVECTOR *cam, SVECTOR *trg, SVECTOR *rot, int *track );

STATIC void sub_8002FAAC(SVECTOR *eye, SVECTOR *center, SVECTOR *rotate, int *track);
STATIC void sub_8002FCF0(void);
STATIC void sub_800303E0(SVECTOR *arg0);

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

    GM_Camera.position.vx = camera_clamp(GM_Camera.position.vx, pVec[8].vz,  pVec[6].vz);
    GM_Camera.position.vy = camera_clamp(GM_Camera.position.vy, pVec[8].pad, pVec[6].pad);
    GM_Camera.position.vz = camera_clamp(GM_Camera.position.vz, pVec[9].vx,  pVec[7].vx);
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

static void SaturatedAdd( SVECTOR *vec1, SVECTOR *vec2, SVECTOR *vec3 )
{
    short *v1, *v2, *v3;
    int    i, val;

    v1 = (short *)vec1;
    v2 = (short *)vec2;
    v3 = (short *)vec3;
    for ( i = 0; i < 3; i++, v1++, v2++, v3++ )
    {
        val = *v1 + *v2;
        if ( val != (short)val ) val = ( val < 0 ) ? 0x8000 : 0x7FFF;
        *v3 = val;
    }
}

static void SaturatedSub( SVECTOR *vec1, SVECTOR *vec2, SVECTOR *vec3 )
{
    short *v1, *v2, *v3;
    int    i, val;

    v1 = (short *)vec1;
    v2 = (short *)vec2;
    v3 = (short *)vec3;
    for ( i = 0; i < 3; i++, v1++, v2++, v3++ )
    {
        val = *v1 - *v2;
        if ( val != (short)val ) val = ( val < 0 ) ? 0x8000 : 0x7FFF;
        *v3 = val;
    }
}

// move to camera.h when it exists?
static inline int CheckFlag(int mask)
{
    return GM_Camera.flag & mask;
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
    switch (gUnkCameraStruct2_800B76F0.position.pad & 3)
    {
    case 0:
        GV_OriginPadSystem(0);
        return;

    case 1:
        if (arg0 != 0)
        {
            MakeRotate(&GM_Camera.position, &GM_Camera.target, &gUnkCameraStruct2_800B76F0.rotate, &gUnkCameraStruct2_800B76F0.track);
        }

        GV_OriginPadSystem(gUnkCameraStruct2_800B76F0.rotate.vy + 2048);
        break;

    case 2:
        GV_OriginPadSystem(gUnkCameraStruct2_800B76F0.position.pad >> 2);
        break;

    default:
        break;
    }
}

STATIC void sub_8002EE04(void)
{
    GM_Camera.position = gUnkCameraStruct2_800B76F0.position;
    GM_Camera.target = gUnkCameraStruct2_800B76F0.target;
    GM_Camera.type = 0;
    sub_8002ED68(0);
}

STATIC void sub_8002EE80(void)
{
    gUnkCameraStruct2_800B76F0.target.vz = GM_SnakeCamera.target.vz;
    GM_Camera.position = gUnkCameraStruct2_800B76F0.position;
    GM_Camera.target = gUnkCameraStruct2_800B76F0.target;
    GM_Camera.type = 0;
    GV_OriginPadSystem(0);
}

STATIC void sub_8002EF08(void)
{
    GM_Camera.position = gUnkCameraStruct2_800B76F0.position;
    GM_Camera.target = GM_SnakeCamera.target;
    GM_Camera.type = 0;
    sub_8002ED68(1);
}

STATIC void sub_8002EF88(void)
{
    int unused[2]; (void)unused;
    GM_Camera.target = GM_SnakeCamera.target;
    GM_Camera.track = GM_SnakeCamera.track;
    GM_Camera.rotate = GM_SnakeCamera.rotate;
    GM_Camera.type = 2;
    GV_OriginPadSystem(0);
}

STATIC void camera_act_helper_helper_8002F008()
{
    GM_Camera.position = GM_SnakeCamera.position;
    GM_Camera.track = 1000;
    GM_Camera.rotate = GM_SnakeCamera.rotate2;
    GM_Camera.type = 1;
    GV_OriginPadSystem(GM_SnakeCamera.rotate2.vy + 2048);
}

static void InterpIntoSubject( int interp )
{
    SVECTOR tmp;

    if ( interp < 6 )
    {
        GV_NearExp4V( &GM_Camera.target, &GM_SnakeCamera.position, 3 );
        GV_NearExp4PV( &GM_Camera.rotate, &GM_SnakeCamera.rotate2, 3 );
        GM_Camera.track = GV_NearExp4( GM_Camera.track, 1000 );
        GV_DirVec3( &GM_Camera.rotate, GM_Camera.track, &tmp );
        SaturatedSub( &GM_Camera.target, &tmp, &GM_Camera.position );
        GM_Camera.type = 0;
    }
    else
    {
        GV_NearTimeV( &GM_Camera.position, &GM_SnakeCamera.position, 12 - interp, 3 );
        GV_NearTimePV( &GM_Camera.rotate, &GM_SnakeCamera.rotate2, 12 - interp, 3 );
        GM_Camera.track = GV_NearTime( GM_Camera.track, 1000, 12 - interp );
        GV_DirVec3( &GM_Camera.rotate, GM_Camera.track, &tmp );
        SaturatedAdd( &GM_Camera.position, &tmp, &GM_Camera.target );
        GM_Camera.type = 0;
    }

    GV_OriginPadSystem( 0 );
}

STATIC void camera_act_helper_8002F1C8(void)
{
    if (GM_Camera.flag & 0x100)
    {
        if (GM_SnakeCamera.interp >= 12)
        {
            GM_Camera.flag &= ~0x101;
        }

        InterpIntoSubject(GM_SnakeCamera.interp);
    }
    else if (GM_Camera.flag & 0x200)
    {
        if (GM_Camera.callback[0])
        {
            GM_Camera.callback[0]();
        }
    }
    else
    {
        camera_act_helper_helper_8002F008();
    }

    GM_SnakeCamera.interp++;
}

STATIC int sub_8002F274(void)
{
    if (GM_Camera.pan.pad == 1)
    {
        GV_AddVec3(&GM_SnakeCamera.position, &GM_Camera.pan, &GM_SnakeCamera.position);
        GM_Camera.pan.pad = 0;
    }

    sub_800303E0(&GM_SnakeCamera.target);

    if (GM_Camera.flag & 0x20)
    {
        sub_8002EF88();
        return 2;
    }

    else if (GM_Camera.flag & 0x10)
    {
        sub_8002EE04();
    }
    else if (GM_Camera.flag & 8)
    {
        sub_8002EE80();
    }
    else if (GM_Camera.flag & 4)
    {
        sub_8002EF08();
    }
    else if (GM_Camera.flag & 2)
    {
        if (GM_Camera.callback[1])
        {
            GM_Camera.callback[1]();
        }

        if ((GM_Camera.flag & 0x80))
        {
            return 1;
        }
        else if (GM_Camera.flag & 0x40)
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

static int InterpOutSubject( int interp )
{
    SVECTOR trg, rot;
    int     ret, track;

    ret = 0;

    if ( interp < 2 )
    {
        GV_NearTimeV( &GM_Camera.target, &GM_SnakeCamera.position, 2 - interp, 3 );
        GV_NearTimePV( &GM_Camera.rotate, &GM_SnakeCamera.rotate2, 2 - interp, 3 );
        GM_Camera.track = GV_NearTime( GM_Camera.track, 1000, 2 - interp );
        GV_OriginPadSystem( 0 );
    }
    else
    {
        int ( *nearfunc )( int, int );
        void ( *nearfuncV )( void *, void *, int );
        void ( *nearfuncPV )( void *, void *, int );

        if ( interp < 4 )
        {
            nearfuncV = &GV_NearExp4V;
            nearfuncPV = &GV_NearExp4PV;
            nearfunc = &GV_NearExp4;
        }
        else
        {
            nearfuncV = &GV_NearExp2V;
            nearfuncPV = &GV_NearExp2PV;
            nearfunc = &GV_NearExp2;
        }

        trg = GM_Camera.target;
        rot = GM_Camera.rotate;

        track = GM_Camera.track;
        ret = sub_8002F274();

        switch ( GM_Camera.type )
        {
        case 0:
            MakeRotate( &GM_Camera.position, &GM_Camera.target, &GM_Camera.rotate, &GM_Camera.track );
            break;
        case 1:
            MakeTarget( &GM_Camera.position, &GM_Camera.target, &GM_Camera.rotate, &GM_Camera.track );
            break;
        }

        nearfuncV( &trg, &GM_Camera.target, 3 );
        nearfuncPV( &rot, &GM_Camera.rotate, 3 );
        track = nearfunc( track, GM_Camera.track );

        GM_Camera.target = trg;
        GM_Camera.rotate = rot;
        GM_Camera.track = track;
    }

    GM_Camera.type = 2;
    return ret;
}

STATIC int camera_act_helper2_8002F5C4(void)
{
    int ret;

    if (GM_Camera.flag & 1)
    {
        if (GM_SnakeCamera.interp >= 12)
        {
            GM_Camera.flag &= ~0x101;
            GM_Camera.interp = -1;
            GM_Camera.interp_mode = 0;
        }

        ret = InterpOutSubject(GM_SnakeCamera.interp);
        GM_SnakeCamera.interp++;

        return ret;
    }

    return sub_8002F274();
}

STATIC void camera_act_helper3_8002F64C(void)
{
    if (GM_Camera.first_person != GM_CameraFirstPersonOrg)
    {
        GM_SnakeCamera.interp = 0;
        GM_Camera.interp_mode = 0;

        if (GM_Camera.first_person == 0)
        {
            GM_Camera.flag |= 1;
            sub_8002FAAC(&GM_Camera.position, &GM_Camera.target, &GM_Camera.rotate, &GM_Camera.track);
        }
        else if (GM_Camera.first_person == 1)
        {
            GM_Camera.flag |= 0x100;
            sub_8002FAAC(&GM_Camera.position, &GM_Camera.target, &GM_Camera.rotate, &GM_Camera.track);

            if (!(GM_Camera.flag & 1))
            {
                if (camera_act_helper3_helper_8002ED3C() & 0x3001E)
                {
                    GM_SnakeCamera.rotate = GM_Camera.rotate;
                    GM_SnakeCamera.track = GM_Camera.track;
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

    if (GM_Camera.flag != GM_CameraFlagsOrg)
    {
        GM_SnakeCamera.interp = 0;
    }

    GM_CameraFirstPersonOrg = GM_Camera.first_person;
    GM_CameraFlagsOrg = GM_Camera.flag;
}

STATIC void camera_act_helper4_8002F78C(void)
{
    SVECTOR vec;

    gUnkCameraStruct2_800B7868.type = 0;
    gUnkCameraStruct2_800B7868.track = GM_Camera.track;
    gUnkCameraStruct2_800B7868.zoom = GM_Camera.zoom;

    if (GM_Camera.interp_mode == 0)
    {
        gUnkCameraStruct2_800B7868.position = GM_Camera.position;
        gUnkCameraStruct2_800B7868.rotate = GM_Camera.rotate;
        gUnkCameraStruct2_800B7868.target = GM_Camera.target;
    }
    else
    {
        MakeRotate(&GM_Camera.position, &GM_Camera.target, &GM_Camera.rotate, &GM_Camera.track);

        GV_SubVec3(&GM_Camera.position, &svec_800ABA88, &vec);
        GV_AddVec3(&vec, &gUnkCameraStruct2_800B7868.position, &gUnkCameraStruct2_800B7868.position);

        svec_800ABA88 = GM_Camera.position;

        if (GM_Camera.interp_mode == 3)
        {
            GV_NearTimeV(&gUnkCameraStruct2_800B7868.position.vx, &GM_Camera.position.vx, GM_Camera.interp, 3);
            GV_NearTimePV(&gUnkCameraStruct2_800B7868.rotate.vx, &GM_Camera.rotate.vx, GM_Camera.interp, 3);
        }
        else if (GM_Camera.interp_mode == 1)
        {
            GV_NearExp2V(&gUnkCameraStruct2_800B7868.position.vx, &GM_Camera.position.vx, 3);
            GV_NearExp2PV(&gUnkCameraStruct2_800B7868.rotate.vx, &GM_Camera.rotate.vx, 3);
        }
        else if (GM_Camera.interp_mode == 2)
        {
            GV_NearExp4V(&gUnkCameraStruct2_800B7868.position.vx, &GM_Camera.position.vx, 3);
            GV_NearExp4PV(&gUnkCameraStruct2_800B7868.rotate.vx, &GM_Camera.rotate.vx, 3);
        }

        if (gUnkCameraStruct2_800B7868.track > 10000)
        {
            gUnkCameraStruct2_800B7868.track = 10000;
        }

        MakeTarget(&gUnkCameraStruct2_800B7868.position, &gUnkCameraStruct2_800B7868.target, &gUnkCameraStruct2_800B7868.rotate, &gUnkCameraStruct2_800B7868.track);

        if (--GM_Camera.interp < 0)
        {
            GM_Camera.interp_mode = 0;
            GM_Camera.interp = -1;
        }
    }

    if (GM_NoisePower >= 255)
    {
        if (GM_Camera.first_person == 0)
        {
            gUnkCameraStruct2_800B7868.position.vy += (GV_RandS(512) * GM_NoiseLength) / 32;
        }
        else
        {
            gUnkCameraStruct2_800B7868.position.vy += (GV_RandS(512) * GM_NoiseLength) / 128;
        }
    }

    if (GM_Camera.first_person == 0)
    {
        gUnkCameraStruct2_800B7868.position.vy += GM_CameraShakeOffset;
        GM_CameraShakeOffset = 0;
    }
    else
    {
        gUnkCameraStruct2_800B7868.position.vy += GM_CameraShakeOffset / 4;
        GM_CameraShakeOffset = 0;
    }
}

STATIC void sub_8002FAAC( SVECTOR *cam, SVECTOR *trg, SVECTOR *rot, int *track )
{
    if ( gUnkCameraStruct2_800B7868.type == 0 )
    {
        *cam = gUnkCameraStruct2_800B7868.position;
        *trg = gUnkCameraStruct2_800B7868.target;
        MakeRotate( cam, trg, rot, track );
        gUnkCameraStruct2_800B7868.rotate = *rot;
    }
}

STATIC void camera_act_helper7_8002FB54()
{
    switch (GM_Camera.type)
    {
    case 0:
        break;
    case 1:
        MakeTarget(&GM_Camera.position, &GM_Camera.target, &GM_Camera.rotate,
                     &GM_Camera.track);
        break;
    case 2:
        MakeCamera(&GM_Camera.position, &GM_Camera.target, &GM_Camera.rotate,
                     &GM_Camera.track);
        break;
    }
}

static void MakeRotate( SVECTOR *cam, SVECTOR *trg, SVECTOR *rot, int *track )
{
    SVECTOR tmp;

    GV_SubVec3( trg, cam, &tmp );
    *track = GV_VecLen3( &tmp );

    rot->vz = 0;
    rot->vy = GV_VecDir2( &tmp );
    rot->vx = ratan2( -tmp.vy, SquareRoot0( tmp.vx * tmp.vx + tmp.vz * tmp.vz ) );
}

static void MakeTarget( SVECTOR *cam, SVECTOR *trg, SVECTOR *rot, int *track )
{
    SVECTOR tmp;

    GV_DirVec3( rot, *track, &tmp );
    SaturatedAdd( cam, &tmp, trg );
}

static void MakeCamera( SVECTOR *cam, SVECTOR *trg, SVECTOR *rot, int *track )
{
    SVECTOR tmp;

    GV_DirVec3( rot, *track, &tmp );
    SaturatedSub( trg, &tmp, cam );
}

STATIC void sub_8002FCF0(void)
{
    if (!(GM_Camera.flag & 0x20))
    {
        GM_SnakeCamera.track = GM_CameraTrackSave;
        GM_SnakeCamera.rotate = GM_CameraRotateSave;
    }
    else
    {
        GM_SnakeCamera.track = gUnkCameraStruct2_800B76F0.track;
        GM_SnakeCamera.rotate = gUnkCameraStruct2_800B76F0.rotate;
    }
}

void GM_SetCameraCallbackFunc(int index, TGMCameraFunc func)
{
    GM_Camera.callback[index] = func;
}

STATIC void ChangeCamera(int new, int old)
{
    CAMERA *camera;

    int cam_param1;

    GM_Camera.flag &= ~0x3C;

    if (new == -1)
    {
        if (!(GM_Camera.flag & 2))
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
            GM_Camera.flag |= 0x20;

            GM_SnakeCamera.rotate.vx = camera->trg.vx;
            GM_SnakeCamera.rotate.vy = camera->trg.vy;
            GM_SnakeCamera.rotate.vz = 0;

            gUnkCameraStruct2_800B76F0.target = GM_SnakeCamera.target;
            gUnkCameraStruct2_800B76F0.rotate = GM_SnakeCamera.rotate;
            gUnkCameraStruct2_800B76F0.track = GM_SnakeCamera.track = camera->trg.vz;

            MakeCamera(&gUnkCameraStruct2_800B76F0.position, &gUnkCameraStruct2_800B76F0.target, &gUnkCameraStruct2_800B76F0.rotate, &gUnkCameraStruct2_800B76F0.track);
        }
        else
        {
            switch (camera->type)
            {
            case 0:
                gUnkCameraStruct2_800B76F0.position = camera->pos;
                gUnkCameraStruct2_800B76F0.target = camera->trg;
                MakeRotate(&gUnkCameraStruct2_800B76F0.position, &gUnkCameraStruct2_800B76F0.target, &gUnkCameraStruct2_800B76F0.rotate, &gUnkCameraStruct2_800B76F0.track);
                break;

            case 1:
                gUnkCameraStruct2_800B76F0.position = camera->pos;

                gUnkCameraStruct2_800B76F0.rotate.vx = camera->trg.vx;
                gUnkCameraStruct2_800B76F0.rotate.vy = camera->trg.vy;
                gUnkCameraStruct2_800B76F0.rotate.vz = 0;
                gUnkCameraStruct2_800B76F0.track = camera->trg.vz;

                MakeTarget(&gUnkCameraStruct2_800B76F0.position, &gUnkCameraStruct2_800B76F0.target, &gUnkCameraStruct2_800B76F0.rotate, &gUnkCameraStruct2_800B76F0.track);
                break;

            case 2:
                gUnkCameraStruct2_800B76F0.target = camera->pos;

                gUnkCameraStruct2_800B76F0.rotate.vx = camera->trg.vx;
                gUnkCameraStruct2_800B76F0.rotate.vy = camera->trg.vy;
                gUnkCameraStruct2_800B76F0.rotate.vz = 0;
                gUnkCameraStruct2_800B76F0.track = camera->trg.vz;

                MakeCamera(&gUnkCameraStruct2_800B76F0.position, &gUnkCameraStruct2_800B76F0.target, &gUnkCameraStruct2_800B76F0.rotate, &gUnkCameraStruct2_800B76F0.track);
                break;
            }

            gUnkCameraStruct2_800B76F0.position.pad = camera->pad_type | ((unsigned short)camera->pos.pad * 4);
            gUnkCameraStruct2_800B76F0.type = 0;

            if (cam_param1 == 1)
            {
                GM_Camera.flag |= 0x10;
            }
            else if (cam_param1 == 2)
            {
                GM_Camera.flag |= 0x8;
            }
            else
            {
                GM_Camera.flag |= 0x4;
            }
        }
    }

    if ((GM_Camera.first_person == 1) || (DG_UnDrawFrameCount > 0))
    {
        GM_Camera.interp_mode = 0;
        GM_Camera.interp = -1;
    }
    else if (old < 0)
    {
        GM_Camera.interp_mode = 2;
        GM_Camera.interp = 30;
    }
    else
    {
        camera = &GM_CameraList[old];
        GM_Camera.interp_mode = dword_80010C60[camera->interp];
        GM_Camera.interp = dword_80010C60[camera->interp] >> 16;
    }
}

STATIC void CheckMessage(GV_ACT *work)
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

    if (GM_AlertMode == ALERT_ACTIVE)
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


    sub_8002FAAC(&GM_Camera.position, &GM_Camera.target, &GM_Camera.rotate, &GM_Camera.track);
    ChangeCamera(i, old_i);
    printf("[%d]change camera %d\n", GV_Time, i);

    GM_GameStatus &= ~GAME_FLAG_BIT_07;

    if (GM_CameraList[i].trg.pad & 1)
    {
        GM_GameStatus |= GAME_FLAG_BIT_07;
    }

    return 1;
}

STATIC void sub_800303E0(SVECTOR *arg0)
{
    SVECTOR          vec;
    GM_SnakeCameraWork *pUnkCamera;
    int              index;

    vec = *arg0;
    pUnkCamera = &GM_SnakeCamera;

    if (DG_UnDrawFrameCount > 0)
    {
        *arg0 = pUnkCamera->position;
    }
    else
    {
        sub_8002EB80(&vec, &pUnkCamera->position);
        GV_NearExp4V((short *)arg0, (short *)&vec, 3);
    }

#ifdef VR_EXE
    index = !!(GM_Camera.flag & 0x28);
#else
    index = !!(GM_Camera.flag & 0x20);
#endif

    sub_8002EBE8(arg0, index);
}

void GM_PanCamera(SVECTOR *pan)
{
    GM_CameraSystemWork *pCamera;

    pCamera = &GM_Camera;
    pCamera->pan = *pan;
    pCamera->pan.pad = 1;

    GV_AddVec3(&gUnkCameraStruct2_800B7868.position, pan, &gUnkCameraStruct2_800B7868.position);
    GV_AddVec3(&gUnkCameraStruct2_800B7868.target, pan, &gUnkCameraStruct2_800B7868.target);

    GV_AddVec3(&pCamera->position, pan, &pCamera->position);
    GV_AddVec3(&pCamera->target, pan, &pCamera->target);

    GV_AddVec3(&GM_SnakeCamera.pan, pan, &GM_SnakeCamera.pan);
    GV_AddVec3(&GM_SnakeCamera.position, pan, &GM_SnakeCamera.position);
    GV_AddVec3(&GM_SnakeCamera.target, pan, &GM_SnakeCamera.target);

    GV_AddVec3(&svec_800ABA88, pan, &svec_800ABA88);
}

static void Act(GV_ACT *work)
{
    int changed;

    int iVar2;

    if (GM_GameStatus >= 0)
    {
        if (GV_PauseLevel == 0)
        {
            CheckMessage(work);
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
                svec_800ABA88 = GM_Camera.position;
            }

            camera_act_helper4_8002F78C();
        }

        DG_LookAt(DG_Chanl(0),
            &gUnkCameraStruct2_800B7868.position,
            &gUnkCameraStruct2_800B7868.target,
            gUnkCameraStruct2_800B7868.zoom);
    }
}

void *NewCameraSystem(void)
{
    GV_ACT *work;

    work = GV_NewActor(GV_ACTOR_ASSIST, sizeof(GV_ACT));
    if (work)
    {
        GV_SetNamedActor(work, Act, NULL, "camera.c");
    }

    GM_Camera.zoom = 320;
    GM_Camera.first_person = 0;
    GM_Camera.flag = 0;
    GM_Camera.pan.pad = 0;
    gUnkCameraStruct2_800B7868.zoom = 320;
    dword_800ABA90 = 0;
    GM_event_camera_flag = 0;
    GM_CameraFirstPersonOrg = 0;
    GM_CameraFlagsOrg = 0;
    GM_SnakeCamera.track = 10000;
    GM_Camera.track = 10000;
    gUnkCameraStruct2_800B7868.track = 10000;
    sub_8002FCF0();
    GM_SnakeCamera.rotate2.vx = 0;
    GM_SnakeCamera.rotate2.vy = 2048;
    GM_SnakeCamera.rotate2.vz = 0;

    return (void *)work;
}

void GM_Reset_helper3_80030760()
{
    CAMERA    *cameraList, *cameraListIter;
    GM_CameraSystemWork *gmCamera;
    int        i;
    int        field_10_param1;

    field_10_param1 = -1;
    i = 7;

    cameraList = GM_CameraList;
    cameraListIter = cameraList + 7;

    gmCamera = &GM_Camera;
    gmCamera->alert_mask = 100;

    gmCamera->bound[0][0].vx = 0x7fff;
    gmCamera->bound[0][0].vy = 0x7fff;
    gmCamera->bound[0][0].vz = 0x7fff;
    gmCamera->bound[1][0].vx = -0x7fff;
    gmCamera->bound[1][0].vy = -0x7fff;
    gmCamera->bound[1][0].vz = -0x7fff;

    gmCamera->limit[0][0].vx = 0x7fff;
    gmCamera->limit[0][0].vy = 0x7fff;
    gmCamera->limit[0][0].vz = 0x7fff;
    gmCamera->limit[1][0].vx = -0x7fff;
    gmCamera->limit[1][0].vy = -0x7fff;
    gmCamera->limit[1][0].vz = -0x7fff;

    gmCamera->bound[0][1].vx = 0x7fff;
    gmCamera->bound[0][1].vy = 0x7fff;
    gmCamera->bound[0][1].vz = 0x7fff;
    gmCamera->bound[1][1].vx = -0x7fff;
    gmCamera->bound[1][1].vy = -0x7fff;
    gmCamera->bound[1][1].vz = -0x7fff;

    gmCamera->limit[0][1].vx = 0x7fff;
    gmCamera->limit[0][1].vy = 0x7fff;
    gmCamera->limit[0][1].vz = 0x7fff;
    gmCamera->limit[1][1].vx = -0x7fff;
    gmCamera->limit[1][1].vy = -0x7fff;
    gmCamera->limit[1][1].vz = -0x7fff;

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
    GM_SnakeCamera.target = GM_SnakeCamera.position;
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

void GM_CameraSetBound(SVECTOR *min, SVECTOR *max, int which)
{
    GM_Camera.bound[1][which] = *min;
    GM_Camera.bound[0][which] = *max;
}

void GM_CameraSetLimit(SVECTOR *min, SVECTOR *max, int which)
{
    GM_Camera.limit[1][which] = *min;
    GM_Camera.limit[0][which] = *max;
}

void GM_CameraSetRotation(SVECTOR *rot)
{
    GM_CameraRotateSave = *rot;
    sub_8002FCF0();
}

void GM_CameraSetTrack(int track)
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
    GM_Camera.interp_mode = param_1;
    GM_Camera.interp = param_2;
    svec_800ABA88 = GM_Camera.position;
}

void sub_800309F8(int param_1, int param_2)
{
    sub_800309B4(param_1, param_2);
    GM_Camera.flag |= 2;
}

void sub_80030A30()
{
    if (GM_Camera.first_person == 0)
    {
        GM_SnakeCamera.position = GM_SnakeCamera.target = GM_Camera.target;
    }

    GM_Camera.flag &= ~2;
}

void GM_CameraBoundTrace(int param_1)
{
    sub_8002EADC(param_1);
}

void GM_CameraLimitTrace(int param_1)
{
    sub_8002EBE8(&GM_Camera.target, param_1);
}

void GM_ExitBehindCamera(void)
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

    if ((GM_StatusEvent & 0x100 || GM_AlertMode != ALERT_ACTIVE) &&
        (trp = HZD_CheckBehindTrap(pHzdMap, &pControl->mov)) != NULL)
    {
        if (GM_800AB444 != trp)
        {
            if (++GM_800AB448 >= 10)
            {
                GM_800AB444 = trp;

                cam = &GM_CameraList[3];
                cam->field_10_param1 = 1;
                cam->interp = 2;
                cam->type = 0;
                cam->pad_type = 2;
                cam->pos.pad = GV_GetPadOrigin();

                name = (short *)trp->name; // TODO: Is char[] name array in HZD_TRP correct? Is it really a name?
                cam->trg.vx = name[0];
                cam->trg.vy = name[1];
                cam->trg.vz = name[2];

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
        GM_ExitBehindCamera();
    }
}
