#include "game/game.h"
#include "takabe/cinema.h"

typedef struct _JEEP_SYSTEM
{
    char     pad1[0x4];
    CONTROL *control;
    char     pad2[0x10];
    SVECTOR  pos;
    char     pad3a[0x4C - 0x20];
    int      field_4C;
    char     pad3b[0x54 - 0x4C - sizeof(int)];
    int      field_54;
    char     pad4[0x8];
    OBJECT  *body;
    char     pad5a[0x6C - 0x64];
    MATRIX **field_6C;
    MATRIX **field_70;
    char     pad5b[0x7C - 0x70 - sizeof(MATRIX **)];
    int      field_7C;
    MATRIX   world;
    char     pad6[0x88];
    int      field_128;
    char     pad7[0x130 - 0x128 - sizeof(int)];
    int      field_130;
    char     pad8[0x138 - 0x130 - sizeof(int)];
    int      field_138;
    char     pad9[0x140 - 0x138 - sizeof(int)];
    SVECTOR  field_140;
    SVECTOR  field_148;
    MATRIX  *field_150;
    SVECTOR  field_154;
    MATRIX  *field_15C;
    SVECTOR  field_160;
    void    *field_168;
} JEEP_SYSTEM;

extern JEEP_SYSTEM Takabe_JeepSystem;

typedef struct _Work
{
    GV_ACT actor;
    char   pad1[0x40 - 0x20];
    void  *field_40;
    void  *field_44;
    char   pad2[0x4C - 0x44 - sizeof(void *)];
    int    field_4C;
} Work;

typedef struct _JeepCamParams
{
    SVECTOR svec0;
    int     field_8;
    int     field_C;
    int     field_10;
    int     field_14;
    int     field_18;
    SVECTOR field_1C;
} JeepCamParams; /* 0x24, at 0x800DE5C8 */

extern JeepCamParams s19b_JeepCamParams_800DE5C8;
extern void s19b_jlamp_800D0C44(void);

void s19b_jlamp_800D0648(SVECTOR *from, SVECTOR *to, SVECTOR *ang, int *len)
{
    SVECTOR diff;

    GV_SubVec3(to, from, &diff);
    *len = GV_VecLen3(&diff);

    ang->vz = 0;
    ang->vy = GV_VecDir2(&diff);
    ang->vx = ratan2(-diff.vy, SquareRoot0(diff.vx * diff.vx + diff.vz * diff.vz));
}

void s19b_jlamp_800D06E0(Work *work)
{
    NewCinemaScreen(300, 0);
    work->field_44 = &Takabe_JeepSystem.field_128;
    Takabe_JeepSystem.field_54 |= 0x10000000;
}

extern void Voicesys_800CE2D0(void);

extern int s19b_dword_800C3760;
extern int s19b_dword_800C3768;

void s19b_jlamp_800D072C(Work *work)
{
    Takabe_JeepSystem.field_4C |= 0x10000;
    work->field_40 = &Takabe_JeepSystem.field_140;
    Takabe_JeepSystem.field_150 = *Takabe_JeepSystem.field_6C;
    Takabe_JeepSystem.field_154 = *(SVECTOR *)&s19b_dword_800C3760;
    work->field_44 = &Takabe_JeepSystem.field_148;
    Takabe_JeepSystem.field_15C = *Takabe_JeepSystem.field_70;
    Takabe_JeepSystem.field_160 = *(SVECTOR *)&s19b_dword_800C3768;
    GM_SeSet(NULL, 0xC4);
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D07EC.s")
extern int s19b_dword_800DE5B8;

void s19b_jlamp_800D087C(void)
{
    GV_DestroyActorQuick((GV_ACT *)s19b_dword_800DE5B8);
    Takabe_JeepSystem.field_4C = (Takabe_JeepSystem.field_4C & ~0x10000) | 0x20000;
}
void s19b_jlamp_800D08C8(Work *work)
{
    work->field_44 = &Takabe_JeepSystem.field_128;
    Voicesys_800CE2D0();
}
void s19b_jlamp_800D08F0(void)
{
    GM_GameStatus &= ~0x40000000;
    Takabe_JeepSystem.field_54 &= ~0x10000000;
}
void s19b_jlamp_800D0928(Work *work)
{
    work->field_44 = &Takabe_JeepSystem.field_130;
    Takabe_JeepSystem.field_4C |= 0x40000;
}
void s19b_jlamp_800D094C(void)
{
    NewCinemaScreen(270, 0);
}

void s19b_jlamp_800D0970(void)
{
    Voicesys_800CE2D0();
}
void s19b_jlamp_800D0990(Work *work)
{
    work->field_44 = &Takabe_JeepSystem.field_138;
    Voicesys_800CE2D0();
}
void s19b_jlamp_800D09B8(Work *work)
{
    work->field_44 = NULL;
    Takabe_JeepSystem.field_4C &= ~0x40000;
}
void s19b_jlamp_800D09DC(void)
{
    GM_SeSet(NULL, 0xB5);
    GM_SetSound(0x01FFFF0B, 0);
    GM_SetSound(0xFF0000FE, 0);
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp_800D0A20.s")

extern GM_CameraSystemWork GM_Camera;
extern GM_SnakeCameraWork  GM_SnakeCamera;

struct _DemoCam;

typedef struct _DemoCamCmd
{
    int frame;
    void (*fn)(struct _DemoCam *);
} DemoCamCmd;

typedef struct _DemoCam
{
    GV_ACT      actor;
    SVECTOR     field_20;
    SVECTOR     field_28;
    SVECTOR     field_30;
    int         field_38;
    u_short     field_3C;
    char        pad1[0x88 - 0x3E];
    int         field_88;
    int         field_8C;
    int         field_90;
    DemoCamCmd *field_94;
} DemoCam;

void s19b_jlamp_800D0ABC(void)
{
    DemoCam *cam;

    cam = (DemoCam *)Takabe_JeepSystem.field_168;
    if (cam == 0)
    {
        return;
    }

    {
        DemoCamCmd *cmd = cam->field_94;
        if (cmd != 0)
        {
            if (cmd->frame != -1 && cam->field_90 >= cmd->frame)
            {
                cmd->fn(cam);
                cam->field_94 = cmd + 1;
            }
        }
    }

    {
        JEEP_SYSTEM *js = &Takabe_JeepSystem;
        if (js->field_150 != 0)
        {
            DG_SetPos(js->field_150);
            DG_PutVector(&js->field_154, &js->field_140, 1);
        }
        if (js->field_15C != 0)
        {
            DG_SetPos(js->field_15C);
            DG_PutVector(&js->field_160, &js->field_148, 1);
        }
        GM_Camera.position = cam->field_20;
        GM_Camera.target = cam->field_28;
        GM_Camera.rotate = cam->field_30;
        GM_Camera.track = cam->field_38;
        GM_Camera.type = cam->field_3C;
        if (cam->field_88 != 0)
        {
            GV_DestroyActor(&cam->actor);
            js->field_168 = 0;
            js->field_4C &= ~0x20000;
        }
    }
}

void s19b_jlamp_800D0C44(void)
{
    GM_CameraSystemWork *cam = &GM_Camera;
    JeepCamParams       *p = &s19b_JeepCamParams_800DE5C8;

    GV_NearExp4V(cam, p, 3);
    if (p->field_18 == 0)
    {
        cam->target = GM_SnakeCamera.target;
        GV_NearExp4V(&cam->target, &GM_SnakeCamera, 3);
    }
    else
    {
        GV_NearExp4V(&cam->target, &p->field_1C, 3);
    }
    GM_Camera.type = 0;
    s19b_jlamp_800D0ABC();
}
void s19b_jlamp_800D0CE0(void)
{
    s19b_JeepCamParams_800DE5C8.svec0.vx = 0;
    s19b_JeepCamParams_800DE5C8.svec0.vy = 0x5DC;
    s19b_JeepCamParams_800DE5C8.svec0.vz = 0x7D0;
    s19b_JeepCamParams_800DE5C8.field_C = 0x7D0;
    s19b_JeepCamParams_800DE5C8.field_8 = 0;
    s19b_JeepCamParams_800DE5C8.field_10 = 0x5DC;
    s19b_JeepCamParams_800DE5C8.field_14 = 0;
    s19b_JeepCamParams_800DE5C8.field_18 = 0;
    GM_SetCameraCallbackFunc(1, s19b_jlamp_800D0C44);
}

extern const char s19b_dword_800DDD4C[];
extern const char s19b_dword_800DDD54[];
extern const char s19b_dword_800DDD5C[];
extern const char s19b_dword_800DDD64[];
void s19b_jeep_gls_800CEC24(int, SVECTOR *);
int  s19b_jeep_mrl_800D39B4(SVECTOR *dst);

void s19b_jlamp_800D0D40(void)
{
    JeepCamParams *p = &s19b_JeepCamParams_800DE5C8;
    SVECTOR        sp10;
    SVECTOR        sp18;
    SVECTOR        sp20;
    SVECTOR        sp28;

    switch (p->field_8)
    {
    case 1:
        p->field_C = GV_NearExp4(p->field_C, -2000);
        break;
    case 0:
    case 2:
        p->field_C = GV_NearExp4(p->field_C, 2000);
        break;
    }

    switch (s19b_JeepCamParams_800DE5C8.field_8)
    {
    case 3:
        sp20 = *(SVECTOR *)s19b_dword_800DDD4C;
        sp28 = *(SVECTOR *)s19b_dword_800DDD54;
        s19b_JeepCamParams_800DE5C8.svec0 = sp20;
        s19b_JeepCamParams_800DE5C8.field_1C = sp28;
        s19b_JeepCamParams_800DE5C8.field_18 = 1;
        s19b_jlamp_800D0648(&s19b_JeepCamParams_800DE5C8.svec0, &s19b_JeepCamParams_800DE5C8.field_1C,
                            &GM_SnakeCamera.rotate, &GM_SnakeCamera.track);
        break;
    case 4:
        sp20 = *(SVECTOR *)s19b_dword_800DDD5C;
        sp28 = *(SVECTOR *)s19b_dword_800DDD64;
        s19b_JeepCamParams_800DE5C8.svec0 = sp20;
        s19b_JeepCamParams_800DE5C8.field_1C = sp28;
        s19b_JeepCamParams_800DE5C8.field_18 = 1;
        s19b_jlamp_800D0648(&s19b_JeepCamParams_800DE5C8.svec0, &s19b_JeepCamParams_800DE5C8.field_1C,
                            &GM_SnakeCamera.rotate, &GM_SnakeCamera.track);
        break;
    default:
    {
        int r;
        s19b_jeep_gls_800CEC24(Takabe_JeepSystem.control->mov.vz + s19b_JeepCamParams_800DE5C8.field_C, &sp10);
        s19b_JeepCamParams_800DE5C8.field_10 = GV_NearSpeed(s19b_JeepCamParams_800DE5C8.field_10, 1500, 100);
        sp10.vy += *(short *)&s19b_JeepCamParams_800DE5C8.field_10;
        r = s19b_jeep_mrl_800D39B4(&sp18);
        s19b_JeepCamParams_800DE5C8.field_18 = 0;
        sp10.vx += r;
        s19b_JeepCamParams_800DE5C8.svec0 = sp10;
        s19b_jlamp_800D0648(&s19b_JeepCamParams_800DE5C8.svec0, &GM_SnakeCamera.position,
                            &GM_SnakeCamera.rotate, &GM_SnakeCamera.track);
        break;
    }
    }
}

void s19b_jlamp_800D0FE4(int arg0)
{
    s19b_JeepCamParams_800DE5C8.field_8 = arg0;
}
