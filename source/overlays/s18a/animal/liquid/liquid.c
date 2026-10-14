#include "liquid.h"

#include <stdio.h>
#include "mgstype.h"
#include "libgcl/libgcl.h"
#include "chara/snake/shadow.h"
#include "animal/liquid/bombled.h"
#include "menu/menuman.h"
#include "linkvar.h"
#include "mts/mts.h" // for fprintf

#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )
#define WEAPON_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

extern int  GetCountdownTime(void);

extern void s18a_800CC660(LiquidWork *work, int arg1);
extern void s18a_800CC7BC(LiquidWork *work);
extern void *NewLensFlare(MATRIX *world, int time);

extern int     GM_AlertMax;
extern SVECTOR GM_PlayerPosition;

/*---------------------------------------------------------------------------*/

MENU_BAR_CONF liquid_bar_conf = {"LIQUID", {0x10, 0x6F, 0x9F}, {0x1F, 0xDF, 0x7F}, 0};
int           liquid_life_disp = 255;
SVECTOR       liquid_target_size = {200, 1500, 200, 0};
SVECTOR       liquid_target_power = {0, 0, -1000, 0};

CONTROL    *SECTION(".bss") liquid_control;
int        *SECTION(".bss") liquid_cam_mode;
LiquidWork *SECTION(".bss") liquid_work;
int         SECTION(".bss") liquid_cam_time;
int         SECTION(".bss") liquid_cam_dist;

/*---------------------------------------------------------------------------*/

void s18a_liquid_800C5108(short *a, short *b)
{
    a[0] = GV_NearRange(a[0], b[0], 250);
    a[1] = GV_NearRange(a[1], b[1], 100);
    a[2] = GV_NearRange(a[2], b[2], 250);
}

void s18a_liquid_800C5170(short *out, short *from, short *to, int total, int time)
{
    int i;

    for (i = 0; i < 3; i++)
    {
        *out++ = *from + ((*to++ - *from) / total) * time;
        from++;
    }
}

void s18a_liquid_800C51F0(SVECTOR *vec, short x, short y, short z)
{
    vec->vx = x;
    vec->vy = y;
    vec->vz = z;
}

void s18a_liquid_800C5200(int mode)
{
    *liquid_cam_mode = mode;
    liquid_cam_time = 0;
}

void s18a_liquid_800C521C(void)
{
    GM_Camera.type = 0;
    GM_Camera.position.vx = 2379;
    GM_Camera.position.vy = 12461;
    GM_Camera.position.vz = -156;
    GM_Camera.target.vx = 2283;
    GM_Camera.target.vy = 12479;
    GM_Camera.target.vz = -147;
    liquid_cam_time++;
}

void s18a_liquid_800C526C(void)
{
    SVECTOR pos_start;
    SVECTOR trg_start;
    SVECTOR pos_end;
    SVECTOR trg_end;

    GM_Camera.type = 0;

    s18a_liquid_800C51F0(&pos_start, 2446, 13168, -2366);
    s18a_liquid_800C51F0(&pos_end, 2542, 12664, -3446);
    s18a_liquid_800C5170((short *)&GM_Camera.position, (short *)&pos_start, (short *)&pos_end, 200, liquid_cam_time);

    s18a_liquid_800C51F0(&trg_start, 2453, 13126, -2455);
    s18a_liquid_800C51F0(&trg_end, 2549, 12622, -3535);
    s18a_liquid_800C5170((short *)&GM_Camera.target, (short *)&trg_start, (short *)&trg_end, 200, liquid_cam_time);

    liquid_cam_time++;
}

void s18a_liquid_800C5350(void)
{
    SVECTOR pos_start;
    SVECTOR trg_start;
    SVECTOR pos_end;
    SVECTOR trg_end;

    GM_Camera.type = 0;

    if (liquid_cam_time < 30)
    {
        s18a_liquid_800C51F0(&GM_Camera.position, -409, 13003, 952);
        s18a_liquid_800C51F0(&GM_Camera.target, 3168, 12092, -582);
    }
    else if (liquid_cam_time < 90)
    {
        s18a_liquid_800C51F0(&GM_Camera.position, -409, 13003, 952);
        s18a_liquid_800C51F0(&trg_start, 3168, 12092, -582);
        s18a_liquid_800C51F0(&trg_end, 1548, 10058, 2815);
        s18a_liquid_800C5170((short *)&GM_Camera.target, (short *)&trg_start, (short *)&trg_end, 60, liquid_cam_time - 30);
    }
    else if (liquid_cam_time < 135)
    {
    }
    else if (liquid_cam_time < 240)
    {
        s18a_liquid_800C51F0(&pos_start, -2183, 2648, 15174);
        s18a_liquid_800C51F0(&pos_end, 2212, 28178, 12064);
        s18a_liquid_800C5170((short *)&GM_Camera.position, (short *)&pos_start, (short *)&pos_end, 150, liquid_cam_time - 135);

        s18a_liquid_800C51F0(&trg_start, -1405, 4631, 9573);
        s18a_liquid_800C51F0(&trg_end, 2212, 23404, 8444);
        s18a_liquid_800C5170((short *)&GM_Camera.target, (short *)&trg_start, (short *)&trg_end, 150, liquid_cam_time - 135);
    }

    liquid_cam_time++;
}

void s18a_liquid_800C54F4(void)
{
    GM_Camera.type = 2;

    if (liquid_cam_time <= 0)
    {
        GM_Camera.target.vx = (GM_PlayerPosition.vx + liquid_work->control.mov.vx) / 2;
        GM_Camera.target.vz = (GM_PlayerPosition.vz + liquid_work->control.mov.vz) / 2;
        GM_Camera.target.vy = GM_PlayerPosition.vy / 2 + liquid_work->control.mov.vy / 2;
        GM_Camera.track = 3000;
        GM_Camera.rotate.vx = -200;
        GM_Camera.rotate.vy = 2960;
    }
    else if (liquid_cam_time < 60)
    {
        GM_Camera.rotate.vy--;
    }
    else if (liquid_cam_time < 90)
    {
        GM_Camera.rotate.vy--;
    }
    else if (liquid_cam_time < 91)
    {
        GM_Camera.target.vx = (GM_PlayerPosition.vx + liquid_work->control.mov.vx) / 2;
        GM_Camera.target.vz = (GM_PlayerPosition.vz + liquid_work->control.mov.vz) / 2;
        GM_Camera.target.vy = GM_PlayerPosition.vy / 2 + liquid_work->control.mov.vy / 2;
        GM_Camera.track = 3000;
        GM_Camera.rotate.vx = 50;
        GM_Camera.rotate.vy = 1206;
    }
    else if (liquid_cam_time < 150)
    {
        GM_Camera.rotate.vy++;
    }
    else if (liquid_cam_time < 500)
    {
        GM_Camera.rotate.vy++;
    }
    else
    {
        *liquid_cam_mode = 4;
        liquid_cam_time = 0;
    }

    liquid_cam_time++;
}

void s18a_liquid_800C5698(void)
{
    GM_Camera.rotate.vx = 440;
    GM_Camera.rotate.vy = 2048;
    GM_Camera.track = 6600;
    GM_Camera.rotate.vz = 0;
    GM_Camera.type = 2;
    GM_Camera.target.vx = GM_PlayerPosition.vx;
    GM_Camera.target.vz = GM_PlayerPosition.vz;
    GM_Camera.target.vy = GM_PlayerPosition.vy;
    *liquid_cam_mode = 6;
    liquid_cam_time = 0;
}

void s18a_liquid_800C5700(void)
{
    GM_Camera.type = 2;

    if (liquid_cam_time < 128)
    {
        GM_Camera.target.vx = (GM_PlayerPosition.vx + liquid_work->control.mov.vx) / 2;
        GM_Camera.target.vz = (GM_PlayerPosition.vz + liquid_work->control.mov.vz) / 2;
        GM_Camera.target.vy = GM_PlayerPosition.vy;
        GM_Camera.track = 6000;
        GM_Camera.rotate.vx = 700;
        GM_Camera.rotate.vy = liquid_cam_time * 24 + 2048;
    }
    else if (liquid_cam_time < 280)
    {
        GV_NearExp8V(&GM_Camera.target, &GM_PlayerPosition, 3);

        GM_Camera.track += 15;
        if (GM_Camera.track > 6600)
        {
            GM_Camera.track = 6600;
        }

        GM_Camera.rotate.vx -= 10;
        if (GM_Camera.rotate.vx < 440)
        {
            GM_Camera.rotate.vx = 440;
        }

        GM_Camera.rotate.vy = liquid_cam_time * 24 + 2048;
        if (GM_Camera.rotate.vy > 6144)
        {
            GM_Camera.rotate.vy = 6144;
        }
    }
    else
    {
        *liquid_cam_mode = 6;
        liquid_cam_time = 0;
    }

    liquid_cam_time++;
}

void s18a_liquid_800C5880(void)
{
    SVECTOR target;
    int     track;

    target = GM_Camera.target;
    s18a_liquid_800C5108((short *)&target, (short *)&GM_PlayerPosition);
    GV_NearExp4V(&GM_Camera.target, &target, 3);

    track = liquid_work->f9B0 + 4000;
    if (track > 8000)
    {
        track = 8000;
    }

    if (GM_Camera.track < track)
    {
        GM_Camera.track = track;
    }
    else if (track - 1000 < GM_Camera.track)
    {
        GM_Camera.track = GV_NearExp8(GM_Camera.track, track);
    }

    liquid_cam_dist = (GM_Camera.track + 5120) / 256;

    GM_Camera.rotate.vx = 440;
    GM_Camera.rotate.vy = 2048;

    if (GM_PlayerStatus & PLAYER_ACT_ONLY)
    {
        *liquid_cam_mode = 8;
        liquid_cam_time = 0;
    }
}

void s18a_liquid_800C59B0(void)
{
    if (liquid_cam_time == 0)
    {
        GM_Camera.rotate.vy = liquid_work->f9AC;
    }

    GM_GameStatus |= STATE_PADRELEASE;
    GM_Camera.target = liquid_work->control.mov;
    GM_Camera.rotate.vx = 640;
    liquid_cam_time++;
}

void s18a_liquid_800C5A34(void)
{
    GV_NearExp8V(&GM_Camera.target, &GM_PlayerPosition, 3);

    GM_Camera.rotate.vx = GV_NearExp8(GM_Camera.rotate.vx, 440);
    GM_Camera.rotate.vy = GV_NearExp8(GM_Camera.rotate.vy, 2048);
    GM_Camera.track = GV_NearExp8(GM_Camera.track, 6000);

    if (!(GM_PlayerStatus & PLAYER_ACT_ONLY))
    {
        GM_Camera.rotate.vx = 440;
        GM_Camera.rotate.vy = 2048;
        GM_Camera.track = 6000;
        *liquid_cam_mode = 6;
    }

    liquid_cam_time++;
}

void s18a_liquid_800C5AEC(void)
{
    if (liquid_cam_time == 0)
    {
        GM_Camera.target = liquid_work->control.mov;
        GM_Camera.track = 5000;
        GM_Camera.rotate.vx = 1000;
        GM_Camera.rotate.vy = liquid_work->control.rot.vy + 512;
        GM_Camera.track = 3000;
    }

    if (liquid_cam_time == 16)
    {
        GM_Camera.rotate.vy = liquid_work->control.rot.vy - 512;
        GM_Camera.track = 2000;
    }

    if (liquid_cam_time == 48)
    {
        GM_Camera.rotate.vy = liquid_work->control.rot.vy + 2048;
        GM_Camera.track = 500;
    }

    liquid_cam_time++;
}

int s18a_liquid_800C5BCC(SVECTOR *pos)
{
    int vz = pos->vz;
    int vx = pos->vx;

    if (vz >= 4751)
    {
        return 0;
    }

    if (vz < -1250)
    {
        return 4;
    }

    if (vx < -750)
    {
        return 3;
    }

    if (vx < 1250)
    {
        return 2;
    }

    if (vx < 2500)
    {
        return 1;
    }

    if (vx < 3250)
    {
        return 7;
    }

    if (vx < 5500)
    {
        return 6;
    }

    return 5;
}

void s18a_liquid_800C5C4C(void)
{
    if (GM_Camera.flag & 1)
    {
        liquid_cam_time = 0;
    }

    if (liquid_cam_time == 0)
    {
        int area;

        area = s18a_liquid_800C5BCC(&GM_PlayerPosition);

        GM_Camera.target = GM_PlayerPosition;
        GM_Camera.rotate.vy = (liquid_work->f9AC - 2048) & 0xFFF;
        GM_Camera.rotate.vx = 240;
        GM_Camera.track = 5000;

        switch (area)
        {
        case 0:
            GM_Camera.rotate.vx = -240;
            GM_Camera.track = 5000;
            break;

        case 1:
            GM_Camera.rotate.vx = 0;
            GM_Camera.track = 4000;
            break;

        case 2:
            GM_Camera.rotate.vx = -100;
            GM_Camera.track = 5000;
            break;

        case 3:
            GM_Camera.rotate.vx = 450;
            GM_Camera.track = 5000;
            break;

        case 4:
            GM_Camera.rotate.vy = 2048;
            GM_Camera.rotate.vx = 600;
            GM_Camera.track = 5000;
            break;

        case 5:
            GM_Camera.rotate.vx = 1000;
            GM_Camera.track = 5000;
            break;

        case 6:
            if (GM_Camera.rotate.vy < 1900)
            {
                GM_Camera.rotate.vy = 1900;
            }
            GM_Camera.rotate.vx = -180;
            GM_Camera.track = 2500;
            break;
        }
    }

    if (GM_PlayerBody->action == 2)
    {
        *liquid_cam_mode = 9;
        liquid_cam_time = 0;
    }

    liquid_cam_time++;
}

void s18a_liquid_800C5E20(void)
{
    switch (*liquid_cam_mode)
    {
    case 0:
        s18a_liquid_800C521C();
        break;

    case 1:
        s18a_liquid_800C526C();
        break;

    case 2:
        s18a_liquid_800C5350();
        break;

    case 3:
        s18a_liquid_800C54F4();
        break;

    case 4:
        s18a_liquid_800C5698();
        break;

    case 5:
        s18a_liquid_800C5700();
        break;

    case 6:
        s18a_liquid_800C5880();
        break;

    case 7:
        s18a_liquid_800C59B0();
        break;

    case 8:
        s18a_liquid_800C5C4C();
        break;

    case 9:
        s18a_liquid_800C5A34();
        break;

    case 10:
        s18a_liquid_800C5AEC();
        break;
    }
}

void s18a_liquid_800C5F18(LiquidWork *work)
{
    MATRIX   mat;
    CONTROL *control;
    int      alert;
    int      time;

    control = &work->control;

    GM_ActControl(control);
    GM_ActObject2(&work->body);
    DG_GetLightMatrix(&control->mov, work->light);

    s18a_800CC7BC(work);

    GM_MoveTarget(work->target, &control->mov);
    GM_MoveTarget(work->target2, &control->mov);

    if (--work->f978 < 0)
    {
        work->f978 = 0;
    }

    alert = (work->f978 + 29) / 30;
    if (alert > 256)
    {
        alert = 256;
    }

    if (GM_AlertMax < alert)
    {
        GM_AlertMax = alert;
    }

    if (work->life < liquid_life_disp)
    {
        liquid_life_disp--;
    }

    if (work->f95C)
    {
        MENU_DrawBar2(28, liquid_life_disp * 3, work->life * 3, 768, &liquid_bar_conf);

        if (work->f95C && work->dead_timer == 0 && GetCountdownTime() == 0)
        {
            work->dead_timer = 1;

            mat = DG_ZeroMatrix;
            mat.t[0] = 3483;
            mat.t[1] = 11810;
            mat.t[2] = -4300;

            GM_GameStatus |= STATE_PADRELEASE;
            NewLensFlare(&mat, 20);

            if (GM_GameOverTimer == 0 && GM_Vitality > 0)
            {
                if (work->proc_b >= 0)
                {
                    GCL_ExecProc(work->proc_b, NULL);
                }

                GM_GameOver();
                GM_GameOverTimer = -2;
            }
        }
    }

    if (work->dead_timer > 0)
    {
        if (work->dead_timer > 30 && GM_GameOverTimer == -2)
        {
            GM_GameOverTimer = 1;
        }

        if (work->dead_timer == 600)
        {
            GM_GameOverTimer = 0;
            GM_GameOver();
        }

        work->dead_timer++;
    }

    time = GetCountdownTime();
    if (time != 0 && time < 5400 && (time % 30) == 0)
    {
        if (time < 900)
        {
            GM_SeSet2(0, 63, 185);
        }
        else
        {
            GM_SeSet2(0, 63, 183);
        }
    }
}

void s18a_liquid_800C6204(LiquidWork *work)
{
    liquid_control = &work->control;
    liquid_cam_mode = &work->cam_mode;
    liquid_work = work;
    liquid_cam_time = 0;

    GM_SetCameraCallbackFunc(1, s18a_liquid_800C5E20);

    GM_Camera.interp_mode = 2;
    GM_Camera.interp = 4;
    GM_Camera.rotate.vx = 440;
    GM_Camera.rotate.vz = 0;
    GM_Camera.rotate.vy = 2048;
    GM_Camera.flag |= 2;
    GM_Camera.track = 4000;
    GM_Camera.type = 2;

    work->cam_mode = 0;
}

void s18a_liquid_800C62A4(LiquidWork *work)
{
    TARGET *target;

    target = work->target;
    GM_SetTarget(target, 0x17, ENEMY_SIDE, &liquid_target_size);
    GM_SetPowerTarget(target, 1, -1, 0xFF, 0xFF, &liquid_target_power);
    GM_SetCaptureTarget(target, -1, 0xFF, NULL, NULL);

    GM_SetTarget(work->target2, 8, NO_SIDE, &liquid_target_size);
}

int s18a_liquid_800C6348(char *unused, int *out)
{
    int   count;
    char *str;

    count = 0;
    while ((str = GCL_NextStr()) != NULL)
    {
        *out++ = GCL_StrToInt(str);
        count++;
    }

    return count;
}

int s18a_liquid_800C63A0(LiquidWork *work)
{
    char *opt;
    int   count;

    opt = GCL_GetOption('v');
    if (opt)
    {
        count = s18a_liquid_800C6348(opt, work->voices);
        printf("@@@@ num=%d \n", count);

        if (count >= 20)
        {
            fprintf(0, "Err Err Err Sound Buff Over !!\n");
            return -1;
        }

        return 0;
    }

    return 0;
}

int s18a_liquid_800C6414(char *unused, u_char *out)
{
    int   count;
    char *str;

    count = 0;
    while ((str = GCL_NextStr()) != NULL)
    {
        *out++ = GCL_StrToInt(str);
        count++;
    }

    return count;
}

int s18a_liquid_800C646C(LiquidWork *work)
{
    char *opt;
    int   count;
    int   count2;

    work->damage1[0] = 5;
    work->damage1[1] = 8;
    work->damage1[2] = 4;

    opt = GCL_GetOption('y');
    if (opt)
    {
        count = s18a_liquid_800C6414(opt, work->damage1);
        printf("@@@@ num=%d \n", count);

        if (count != 3)
        {
            goto error;
        }
    }

    printf(" punch damage=%d \n", work->damage1[0]);
    printf(" kick damage=%d \n", work->damage1[1]);
    printf(" through damage=%d \n", work->damage1[2]);

    work->damage2[0] = 28;
    work->damage2[1] = 56;
    work->damage2[2] = 64;
    work->damage2[3] = 32;
    work->damage2[4] = 64;

    opt = GCL_GetOption('z');
    if (opt)
    {
        count2 = s18a_liquid_800C6414(opt, work->damage2);
        printf("@@@@ num=%d \n", count2);

        if (count2 != 5)
        {
error:
            fprintf(0, "Err Err Err Sound Buff Over !!\n");
            return -1;
        }
    }

    printf(" punch damage=%d \n", work->damage2[0]);
    printf(" kick damage=%d \n", work->damage2[1]);
    printf(" okiagari damage=%d \n", work->damage2[2]);
    printf(" fumituke damage=%d \n", work->damage2[3]);
    printf(" tackle damage=%d \n", work->damage2[4]);
    return 0;
}

int s18a_liquid_800C65DC(LiquidWork *work, int name, int where)
{
    CONTROL *control;
    OBJECT  *body;
    OBJECT  *weapon;
    char    *pos;
    char    *dir;
    SVECTOR  indices;

    control = &work->control;
    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    pos = GCL_GetOption('p');
    dir = GCL_GetOption('d');
    GM_ConfigControlString(control, pos, dir);
    GM_ConfigControlAttribute(control, 5);
    control->seg_flag = 4;
    GM_ConfigControlInterp(control, 4);

    body = &work->body;
    GM_InitObject(body, GV_StrCode("liquid"), BODY_FLAG, GV_StrCode("lqd_18a"));
    GM_ConfigObjectJoint(body);
    GM_ConfigMotionControl(body, &work->m_ctrl, GV_StrCode("lqd_18a"), work->m_segs1, work->m_segs2, control, work->rots);
    GM_ConfigObjectLight(body, work->light);

    weapon = &work->weapon;
    GM_InitObject(weapon, GV_StrCode("b_switch"), WEAPON_FLAG, 0);
    GM_ConfigObjectLight(weapon, work->light);
    GM_ConfigObjectRoot(weapon, body, 4);

    indices.vx = 0;
    indices.vy = 6;
    indices.vz = 12;
    indices.pad = 15;

    work->shadow = NewShadow(control, body, indices);
    if (work->shadow == NULL)
    {
        return -1;
    }

    if (s18a_liquid_800C63A0(work) < 0)
    {
        return -1;
    }

    if (s18a_liquid_800C646C(work) < 0)
    {
        return -1;
    }

    return 0;
}

void s18a_liquid_800C67A0(LiquidWork *work)
{
    GM_ResetHomingTarget(work->hom);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeTarget(work->target);
    GM_FreeTarget(work->target2);
    GM_FreeObject(&work->weapon);
    GV_DestroyActor(work->shadow);
}

int s18a_liquid_800C6808(LiquidWork *work, int name, int where)
{
    CONTROL *control;
    SVECTOR  pos;
    char    *opt;

    if (s18a_liquid_800C65DC(work, name, where) < 0)
    {
fail:
        return -1;
    }

    control = &work->control;

    work->target = GM_AllocTarget();
    if (work->target == NULL)
    {
        goto fail;
    }

    work->target2 = GM_AllocTarget();
    if (work->target2 == NULL)
    {
        goto fail;
    }

    s18a_liquid_800C62A4(work);
    s18a_800CC660(work, 2);

    work->hom = GM_SetHomingTarget(&work->body.objs->objs[6].world, control);
    work->hom->flag = 0;

    pos.vx = 3483;
    pos.vy = 11810;
    pos.vz = -4300;
    NewBombLed(&pos);

    s18a_liquid_800C6204(work);

    work->f9BE = 0;
    opt = GCL_GetOption('m');
    if (opt)
    {
        /* both arms are the same: the redundant test only leaves a join label
           that keeps CSE from rewriting control->mov.vx below as 0x20(work) */
        if (work)
        {
            work->f9BE = GCL_StrToInt(opt);
        }
        else
        {
            work->f9BE = GCL_StrToInt(opt);
        }
    }

    control->mov.vx = 1000;
    control->mov.vy = 12000;
    control->mov.vz = 0;

    work->life = 255;
    work->time = 0;
    work->time2 = 0;
    work->act = 0;
    work->act2 = 0;
    work->f95C = 0;
    work->f960 = 0;
    work->f964 = 0;
    work->f968 = 0;
    work->f948 = 0;
    work->dead_timer = 0;
    work->f978 = 0;
    work->f990 = 0;
    work->f994 = 0;
    work->f980 = 1;
    work->f984 = 0;
    work->f958 = 0;
    work->f99C = 0;
    work->f9A0 = 0;
    work->f9A4 = 0;
    return 0;
}

void *NewLiquid(int name, int where)
{
    LiquidWork *work;

    work = GV_NewActor(GV_ACTOR_PREV, sizeof(LiquidWork));
    if (work != NULL)
    {
        GV_SetNamedActor(work, s18a_liquid_800C5F18, s18a_liquid_800C67A0, "liquid.c");

        if (GCL_GetOption('e'))
        {
            work->proc_e = GCL_StrToInt(GCL_NextStr());
        }
        else
        {
            work->proc_e = -1;
        }

        if (GCL_GetOption('b'))
        {
            work->proc_b = GCL_StrToInt(GCL_NextStr());
        }
        else
        {
            work->proc_b = -1;
        }

        if (GCL_GetOption('s'))
        {
            work->proc_s = GCL_StrToInt(GCL_NextStr());
        }
        else
        {
            work->proc_s = -1;
        }

        if (s18a_liquid_800C6808(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return (void *)work;
}
