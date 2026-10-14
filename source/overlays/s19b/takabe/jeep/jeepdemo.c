#include "game/game.h"
#include "game/camera.h"
#include "takabe/cinema.h"

#include "../jeep_system.h"
#include "../democame.h"

#include "jeepdemo.h"

extern JlampState s19b_dword_800DE5C8;
void s19b_jlamp_800D0C44(void);
extern SVECTOR s19b_dword_800C3760;
extern SVECTOR s19b_dword_800C3768;
extern SVECTOR s19b_dword_800C3770;
extern GV_ACT *s19b_dword_800DE5B8; /* blur effect */
void *NewBlurSet();
void s19b_jlamp_800D0FE4(int arg0);

void s19b_jlamp_800D0648(SVECTOR *from, SVECTOR *to, SVECTOR *ang, int *len)
{
    SVECTOR diff;

    GV_SubVec3(to, from, &diff);
    *len = GV_VecLen3(&diff);

    ang->vz = 0;
    ang->vy = GV_VecDir2(&diff);
    ang->vx = ratan2(-diff.vy, SquareRoot0(diff.vx * diff.vx + diff.vz * diff.vz));
}

void s19b_jlamp_800D06E0(DemoCamera *work)
{
    NewCinemaScreen(300, 0);
    work->center_src = &Takabe_JeepSystem.camera_pos;
    Takabe_JeepSystem.liq_flags |= 0x10000000;
}

extern void Voicesys_800CE2D0(void);

void s19b_jlamp_800D072C(DemoCamera *work)
{
    Takabe_JeepSystem.flags |= 0x10000;
    work->eye_src = &Takabe_JeepSystem.attach_pos[0];
    Takabe_JeepSystem.attach[0].mtx = &Takabe_JeepSystem.body->objs->world;
    Takabe_JeepSystem.attach[0].ofs = s19b_dword_800C3760;
    work->center_src = &Takabe_JeepSystem.attach_pos[1];
    Takabe_JeepSystem.attach[1].mtx = &Takabe_JeepSystem.body2->objs->world;
    Takabe_JeepSystem.attach[1].ofs = s19b_dword_800C3768;
    GM_SeSet(NULL, 0xC4);
}
void s19b_jlamp_800D07EC(DemoCamera *work)
{
    Voicesys_800CE2D0();
    work->center_src = &Takabe_JeepSystem.liq_pos;
    work->eye_src = &Takabe_JeepSystem.attach_pos[0];
    Takabe_JeepSystem.attach[0].mtx = &Takabe_JeepSystem.body2->objs->world;
    Takabe_JeepSystem.attach[0].ofs = s19b_dword_800C3770;
    s19b_dword_800DE5B8 = NewBlurSet(0, 0, 0);
    s19b_jlamp_800D0FE4(1);
}

void s19b_jlamp_800D087C(void)
{
    GV_DestroyActorQuick(s19b_dword_800DE5B8);
    Takabe_JeepSystem.flags = (Takabe_JeepSystem.flags & ~0x10000) | 0x20000;
}
void s19b_jlamp_800D08C8(DemoCamera *work)
{
    work->center_src = &Takabe_JeepSystem.camera_pos;
    Voicesys_800CE2D0();
}
void s19b_jlamp_800D08F0(void)
{
    GM_GameStatus &= ~0x40000000;
    Takabe_JeepSystem.liq_flags &= ~0x10000000;
}
void s19b_jlamp_800D0928(DemoCamera *work)
{
    work->center_src = &Takabe_JeepSystem.meryl_head;
    Takabe_JeepSystem.flags |= 0x40000;
}
void s19b_jlamp_800D094C(void)
{
    NewCinemaScreen(270, 0);
}

void s19b_jlamp_800D0970(void)
{
    Voicesys_800CE2D0();
}
void s19b_jlamp_800D0990(DemoCamera *work)
{
    work->center_src = &Takabe_JeepSystem.liq_pos;
    Voicesys_800CE2D0();
}
void s19b_jlamp_800D09B8(DemoCamera *work)
{
    work->center_src = NULL;
    Takabe_JeepSystem.flags &= ~0x40000;
}
void s19b_jlamp_800D09DC(void)
{
    GM_SeSet(NULL, 0xB5);
    GM_SetSound(0x01FFFF0B, 0);
    GM_SetSound(0xFF0000FE, 0);
}
extern GM_CameraSystemWork GM_Camera;
extern GM_SnakeCameraWork  GM_SnakeCamera;


extern DEMOCAM_KEY s19b_dword_800C3778[];
extern DEMOCAM_CMD s19b_dword_800C3898[];
extern DEMOCAM_KEY s19b_dword_800C38D0[];
extern DEMOCAM_CMD s19b_dword_800C3950[];

void s19b_jlamp_800D0A20(int arg0)
{
    JEEP_SYSTEM *js;

    if (GM_GameOverTimer != 0)
    {
        return;
    }
    js = &Takabe_JeepSystem;
    if (js->demo_camera != NULL)
    {
        return;
    }
    if (arg0 == 0)
    {
        js->demo_camera = NewDemoCamera(s19b_dword_800C3778);
        js->demo_camera->cmd = s19b_dword_800C3898;
    }
    else if (arg0 == 1)
    {
        js->demo_camera = NewDemoCamera(s19b_dword_800C38D0);
        js->demo_camera->cmd = s19b_dword_800C3950;
    }
    else
    {
        return;
    }
    GV_DemoPadStatus[0] = 0;
    GM_GameStatus |= 0x40000000;
}

void s19b_jlamp_800D0ABC(void)
{
    DemoCamera *cam;

    cam = Takabe_JeepSystem.demo_camera;
    if (cam == 0)
    {
        return;
    }

    {
        DEMOCAM_CMD *cmd = cam->cmd;
        if (cmd != 0)
        {
            if (cmd->frame != -1 && cam->frame >= cmd->frame)
            {
                cmd->fn(cam);
                cam->cmd = cmd + 1;
            }
        }
    }

    {
        JEEP_SYSTEM *js = &Takabe_JeepSystem;
        if (js->attach[0].mtx != 0)
        {
            DG_SetPos(js->attach[0].mtx);
            DG_PutVector(&js->attach[0].ofs, &js->attach_pos[0], 1);
        }
        if (js->attach[1].mtx != 0)
        {
            DG_SetPos(js->attach[1].mtx);
            DG_PutVector(&js->attach[1].ofs, &js->attach_pos[1], 1);
        }
        GM_Camera.position = cam->eye;
        GM_Camera.target = cam->center;
        GM_Camera.rotate = cam->rotate;
        GM_Camera.track = cam->track;
        GM_Camera.type = cam->type;
        if (cam->done != 0)
        {
            GV_DestroyActor(&cam->actor);
            js->demo_camera = 0;
            js->flags &= ~0x20000;
        }
    }
}

void s19b_jlamp_800D0C44(void)
{
    GM_CameraSystemWork *cam = &GM_Camera;
    JlampState       *p = &s19b_dword_800DE5C8;

    GV_NearExp4V(cam, p, 3);
    if (p->use_target == 0)
    {
        cam->target = GM_SnakeCamera.target;
        GV_NearExp4V(&cam->target, &GM_SnakeCamera, 3);
    }
    else
    {
        GV_NearExp4V(&cam->target, &p->target, 3);
    }
    GM_Camera.type = 0;
    s19b_jlamp_800D0ABC();
}
void s19b_jlamp_800D0CE0(void)
{
    JlampState *state;

    state = &s19b_dword_800DE5C8;
    state->eye.vx = 0;
    state->eye.vy = 1500;
    state->eye.vz = 2000;
    state->dist = 2000;
    state->mode = 0;
    state->height = 1500;
    state->field_14 = 0;
    state->use_target = 0;
    GM_SetCameraCallbackFunc(1, s19b_jlamp_800D0C44);
}

extern const SVECTOR s19b_dword_800DDD4C; /* mode 3: eye, target */
extern const SVECTOR s19b_dword_800DDD54;
extern const SVECTOR s19b_dword_800DDD5C; /* mode 4: eye, target */
extern const SVECTOR s19b_dword_800DDD64;
void s19b_jeep_gls_800CEC24(int, SVECTOR *);
int  s19b_jeep_800D39B4(SVECTOR *dst);

void s19b_jlamp_800D0D40(void)
{
    JlampState *p = &s19b_dword_800DE5C8;
    SVECTOR        sp10;
    SVECTOR        sp18;
    SVECTOR        sp20;
    SVECTOR        sp28;

    switch (p->mode)
    {
    case 1:
        p->dist = GV_NearExp4(p->dist, -2000);
        break;
    case 0:
    case 2:
        p->dist = GV_NearExp4(p->dist, 2000);
        break;
    }

    switch (s19b_dword_800DE5C8.mode)
    {
    case 3:
        sp20 = s19b_dword_800DDD4C;
        sp28 = s19b_dword_800DDD54;
        s19b_dword_800DE5C8.eye = sp20;
        s19b_dword_800DE5C8.target = sp28;
        s19b_dword_800DE5C8.use_target = 1;
        s19b_jlamp_800D0648(&s19b_dword_800DE5C8.eye, &s19b_dword_800DE5C8.target,
                            &GM_SnakeCamera.rotate, &GM_SnakeCamera.track);
        break;
    case 4:
        sp20 = s19b_dword_800DDD5C;
        sp28 = s19b_dword_800DDD64;
        s19b_dword_800DE5C8.eye = sp20;
        s19b_dword_800DE5C8.target = sp28;
        s19b_dword_800DE5C8.use_target = 1;
        s19b_jlamp_800D0648(&s19b_dword_800DE5C8.eye, &s19b_dword_800DE5C8.target,
                            &GM_SnakeCamera.rotate, &GM_SnakeCamera.track);
        break;
    default:
    {
        int r;
        s19b_jeep_gls_800CEC24(Takabe_JeepSystem.control->mov.vz + s19b_dword_800DE5C8.dist, &sp10);
        s19b_dword_800DE5C8.height = GV_NearSpeed(s19b_dword_800DE5C8.height, 1500, 100);
        sp10.vy += s19b_dword_800DE5C8.height;
        r = s19b_jeep_800D39B4(&sp18);
        s19b_dword_800DE5C8.use_target = 0;
        sp10.vx += r;
        s19b_dword_800DE5C8.eye = sp10;
        s19b_jlamp_800D0648(&s19b_dword_800DE5C8.eye, &GM_SnakeCamera.position,
                            &GM_SnakeCamera.rotate, &GM_SnakeCamera.track);
        break;
    }
    }
}

void s19b_jlamp_800D0FE4(int arg0)
{
    s19b_dword_800DE5C8.mode = arg0;
}
