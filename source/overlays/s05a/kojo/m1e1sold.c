#include "game/game.h"
#include "chara/snake/sna_init.h"
#include "libhzd/libhzd.h"
#include "linkvar.h"
#include "strcode.h"
#include "bullet/blast.h"
#include <rand.h>

typedef struct
{
    HZD_SEG seg[4];
    HZD_FLR flr[2];
} HzdBlock; /* 0xA0 */

typedef struct _CamEb0
{
    char    pad_000[0x1C0];
    TARGET *field_1C0;      /* 0x1C0 */
} CamEb0;

typedef struct _CamActor
{
    char      pad_000[0x20];
    CONTROL   control;         /* 0x020 */
    char      pad_09C[0xB0 - 0x9C];
    int       field_B0;        /* 0x0B0 */
    int       field_B4;        /* 0x0B4 */
    int       field_B8;        /* 0x0B8 */
    char      pad_BC[0xDC - 0xBC];
    OBJECT    body;            /* 0x0DC */
    char      pad_1C0[0x718 - 0x1C0];
    TARGET   *field_718[10];   /* 0x718 */
    char      pad_740[0x744 - 0x740];
    int       field_744;       /* 0x744 */
    int       field_748;       /* 0x748 */
    CONTROL   snap_control;    /* 0x74C */
    OBJECT    snap_body;       /* 0x7C8 */
    char      pad_8AC[0xD54 - 0x8AC];
    int       field_D54;       /* 0xD54 */
    int       field_D58;       /* 0xD58 */
    int       field_D5C;       /* 0xD5C */
    int       field_D60;       /* 0xD60 */
    int       field_D64;       /* 0xD64 */
    int       field_D68;       /* 0xD68 */
    char      pad_D6C[0xD74 - 0xD6C];
    int       field_D74;       /* 0xD74 */
    char      pad_D78[0xD88 - 0xD78];
    int       field_D88;       /* 0xD88 */
    int       field_D8C;       /* 0xD8C */
    char      pad_D90[0xDA0 - 0xD90];
    int       field_DA0;       /* 0xDA0 */
    char      pad_DA4[0xDEC - 0xDA4];
    int       field_DEC;       /* 0xDEC */
    int       field_DF0;       /* 0xDF0 */
    int       field_DF4;       /* 0xDF4 */
    int       field_DF8;       /* 0xDF8 */
    int       field_DFC;       /* 0xDFC */
    int       field_E00;       /* 0xE00 */
    int       field_E04;       /* 0xE04 */
    int       field_E08;       /* 0xE08 */
    int       field_E0C;       /* 0xE0C */
    int       field_E10;       /* 0xE10 */
    int       field_E14;       /* 0xE14 */
    int       field_E18;       /* 0xE18 */
    char      pad_E1C[0xE60 - 0xE1C];
    int       field_E60;       /* 0xE60 */
    char      pad_E64[0xEB0 - 0xE64];
    CamEb0   *field_EB0;       /* 0xEB0 */
    SVECTOR   field_EB4;       /* 0xEB4 */
    char      pad_EBC[0xED0 - 0xEBC];
    int       field_ED0;       /* 0xED0 */
    int       field_ED4;       /* 0xED4 */
    char      pad_ED8[0xF4C - 0xED8];
    int       field_F4C;       /* 0xF4C */
    int       field_F50;       /* 0xF50 */
    char      pad_F54[0xF5C - 0xF54];
    int       field_F5C;       /* 0xF5C */
    char      pad_F60[0xF78 - 0xF60];
    int       field_F78;       /* 0xF78 */
    char      pad_F7C[0xFEC - 0xF7C];
    HzdBlock  hzd[5];          /* 0xFEC */
    HZD_FLR   copy0;           /* 0x130C */
    HZD_FLR   copy1;           /* 0x133C */
    HZD_FLR   copy2;           /* 0x136C */
} CamActor;

typedef struct _Sol
{
    GV_ACT         actor;         /* 0x000 */
    CONTROL        control;       /* 0x020 */
    MATRIX         light[2];      /* 0x09C */
    OBJECT         body;          /* 0x0DC */
    TARGET        *target;        /* 0x1C0 */
    HOMING        *homing;        /* 0x1C4 */
    MATRIX         field_1C8;     /* 0x1C8 */
    int            field_1E8;     /* 0x1E8 */
    CamActor      *field_1EC;     /* 0x1EC */
    int            field_1F0;     /* 0x1F0 */
    int            field_1F4;     /* 0x1F4 */
    int            last_weapon;   /* 0x1F8 */
    int            last_item;     /* 0x1FC */
    int            field_200;     /* 0x200 */
    int            field_204;     /* 0x204 */
    int            field_208;     /* 0x208 */
    int            field_20C;     /* 0x20C */
    char           pad_210[0x218 - 0x210];
    int            field_218;     /* 0x218 */
    int            field_21C;     /* 0x21C */
    char           pad_220[0x228 - 0x220];
    void          *field_228;     /* 0x228 */
    int            field_22C;     /* 0x22C */
    int            field_230;     /* 0x230 */
    MOTION_CONTROL m_ctrl;        /* 0x234 */
    MOTION_SEGMENT m_segs1[17];   /* 0x284 */
    MOTION_SEGMENT m_segs2[17];   /* 0x4E8 */
    CONTROL        subcontrol;    /* 0x74C */
    SVECTOR        rots[16];      /* 0x7C8 */
} Sol;

extern CamActor *s05a_dword_800C362C;
extern CONTROL   s05a_dword_800E3800;

void s05a_800DDF18(Sol *work);
int  s05a_800DEC18(Sol *work, SVECTOR *s2, int a2);
extern void *NewDemoKage(OBJECT *parent, SVECTOR vec, int *arg2, int *arg3, char r, char g, char b);
void s05a_800DEB94(Sol *work);
const char s05a_dword_800E356C[] = "m1e1sold.c";
const char s05a_dword_800E3578[] = "out_c_m1";
const char s05a_dword_800E3584[] = "tankman";
const char s05a_dword_800E358C[] = "out_cold";
extern MATRIX DG_ZeroMatrix;

void *s05a_800DDCBC(CamActor *director)
{
    Sol      *work;
    int       one;
    int       name;
    int       i;
    OBJECT   *bodyp;
    const char *tankstr;
    DG_OBJS  *objs;
    SVECTOR   size;

    work = GV_NewActor(6, 0x848);
    if (work == NULL)
    {
        return 0;
    }
    one = 1;
    work->field_1E8 = one;
    work->field_1EC = director;
    GV_SetNamedActor(work, s05a_800DDF18, s05a_800DEB94, s05a_dword_800E356C);

    if (GM_InitControl(&work->control, work->field_1EC->field_744,
                       work->field_1EC->field_748) < 0)
    {
        GV_DestroyActor(work);
        return 0;
    }

    *(short *)((char *)&work->control + 0x36) = -2; /* sh -2, 0x56(s3) */
    *(char *)((char *)&work->control + 0x54) = 0;   /* sb 0, 0x74(s3) */
    GM_ConfigControlAttribute(&work->control, 5);

    *(int *)&work->light[0].t[0] = *(int *)&work->field_1EC->field_B0;
    *(int *)&work->light[0].t[1] = *(int *)&work->field_1EC->field_B4;
    *(int *)&work->light[0].t[2] = *(int *)&work->field_1EC->field_B8;
    name = GV_StrCode(s05a_dword_800E3578);  /* "out_" */

    tankstr = s05a_dword_800E3584;
    bodyp = &work->body;
    GM_InitObject(bodyp, name, 0x32d, GV_StrCode(tankstr));
    GM_ConfigObjectJoint(bodyp);
    GM_ConfigMotionControl(bodyp, &work->m_ctrl,
                           GV_StrCode(tankstr),
                           work->m_segs1,
                           work->m_segs2,
                           &work->subcontrol,
                           work->rots);
    GM_ConfigObjectLight(bodyp, &work->light[0]);

    objs = bodyp->objs;
    *(int *)&objs->flag |= 0x80;
    work->homing = GM_AllocHomingTarget(&work->field_1C8, &work->control);
    work->homing->flag = one;
    work->target = GM_AllocTarget();
    size.vx = 0x12c;
    size.vy = 0x12c;
    size.vz = 0x12c;
    GM_SetTarget(work->target, 0x94, 2, &size);
    GM_SetPowerTarget(work->target, 1, -1, 0x2710, 0, &DG_ZeroVector);

    for (i = 0; i < 0x10; i++)
    {
        work->body.objs->objs[i].world = DG_ZeroMatrix;
    }
    return work;
}
void s05a_800DDF18(Sol *work)
{
    int     lvl[2];
    SVECTOR vec1;
    SVECTOR vec2;

    memset(&work->subcontrol.step, 0, 8);
    GM_ActMotion(&work->body);
    GM_ActControl(&work->control);
    vec1 = work->subcontrol.step;
    GM_ActObject(&work->body);
    work->subcontrol.step = vec1;
    DG_GetLightMatrix2(&work->control.mov, &work->light[0]);

    if (work->field_1E8 == 0)
    {
        work->body.objs->flag &= ~0x80;
    }
    if (--work->field_20C < 0) work->field_20C = 0;
    if (--work->field_218 < 0) work->field_218 = 0;
    if (--work->field_21C < 0) work->field_21C = 0;

    if (work->field_21C == 0 && work->field_1EC->field_ED0 == 3)
    {
        if (work->field_1EC->field_D58 == 0)
        {
            work->field_1EC->field_D54 = 2;
        }
        else
        {
            work->field_1EC->field_D54 = 7;
        }
        work->field_1EC->field_ED0 = 1;
        GM_Weapon = work->last_weapon;
        GM_Item = work->last_item;
    }

    work->field_1F0 = 0;
    if (work->m_ctrl.info1.frame == 1)
    {
        work->field_200 = work->body.height;
    }
    work->control.step.vx = 0;
    work->control.step.vz = 0;
    work->subcontrol.step.vy = work->body.height - work->field_200;

    switch (work->body.action)
    {
    case 0:
    case 1:
    case 2:
    case 5:
    case 6:
        if (work->body.action == 2 && work->field_1EC->field_E10 == 1)
        {
            work->field_1EC->field_E10 = 0;
            if (GM_Vitality != 0 && GM_GameOverTimer == 0)
            {
                work->field_218 = 0x96;
                work->field_21C = 0x3C;
                GM_SeSetPan(&GM_PlayerPosition, 0x82, 0x3F);
                work->field_1EC->field_D54 = 3;
                work->field_1EC->field_ED0 = 3;
                work->last_weapon = GM_Weapon;
                work->last_item = GM_Item;
                GM_Weapon = WP_None;
                if (GM_Item != IT_NVG && GM_Item != IT_ThermG)
                {
                    GM_Item = IT_None;
                }
            }
        }
        else if (work->body.action == 1)
        {
            if (work->field_1EC->field_E10 == 0 && work->field_218 <= 0 && work->field_1EC->field_ED4 >= 0x1E)
            {
                if (rand() % 3 != 0)
                {
                    work->field_218 = 0x96;
                    GM_SeSetPan(&work->control.mov, 0x80, work->field_1EC->field_E60);
                }
            }
        }

        DG_SetPos(&work->field_1EC->body.objs->objs[12].world);
        vec1.vx = 0;
        vec1.vy = 0;
        vec1.vz = 0;
        vec2.vx = 0;
        vec2.vy = 0;
        vec2.vz = 0x64;
        DG_PutVector(&vec1, &vec1, 1);
        DG_PutVector(&vec2, &vec2, 1);
        vec2.vx -= vec1.vx;
        vec2.vy -= vec1.vy;
        vec2.vz -= vec1.vz;
        work->control.turn.vx = -ratan2(vec2.vy, SquareRoot0(vec2.vx * vec2.vx + vec2.vz * vec2.vz));
        work->control.turn.vy = ratan2(vec2.vx, vec2.vz);
        work->control.turn.vz = 0;
        vec1.vx = work->field_1EC->body.objs->objs[12].world.t[0];
        vec1.vy = work->field_1EC->body.objs->objs[12].world.t[1];
        vec1.vz = work->field_1EC->body.objs->objs[12].world.t[2];
        work->control.mov.vy = work->body.height + work->field_1EC->control.mov.vy - 0xC8;
        work->control.step.vx = vec1.vx - work->control.mov.vx;
        work->control.step.vz = vec1.vz - work->control.mov.vz;
        memset(&vec1, 0, 8);
        vec1.vy = 0x12C;
        DG_PutVector(&vec1, &vec1, 1);
        GM_MoveTarget(work->target, &vec1);
        vec1.vy += 0x96;
        DG_SetPos2(&vec1, &DG_ZeroVector);
        ReadRotMatrix(&work->field_1C8);
        break;

    case 3:
        DG_SetPos2(&DG_ZeroVector, &work->control.rot);
        vec1.vx = 0;
        vec1.vy = work->subcontrol.step.vy;
        vec1.vz = SquareRoot0(work->subcontrol.step.vx * work->subcontrol.step.vx +
                              work->subcontrol.step.vz * work->subcontrol.step.vz);
        DG_PutVector(&vec1, &vec1, 1);
        work->control.mov.vy = s05a_800DEC18(work, &work->control.mov, work->control.mov.vy + vec1.vy);
        work->control.step.vx = vec1.vx;
        work->control.step.vz = vec1.vz;
        vec1 = work->control.mov;
        if (HZD_LevelHazardCheck(work->control.map->hzd, &vec1, HZD_CHK_FLOOR) != 1)
        {
            vec1.vy = 0;
        }
        else
        {
            HZD_GetLevelHeight(lvl);
            vec1.vy = lvl[0];
        }
        if (work->field_1F4 == 0 && work->control.mov.vy - vec1.vy < 0x12C)
        {
            work->field_1F4 = 1;
            GM_SeSetPan(&work->control.mov, 0x33, work->field_1EC->field_E60);
        }
        work->field_22C = work->control.rot.vy;
        work->field_230 = vec1.vy + 0x64;
        break;

    case 4:
        if (!((GV_Time >> 2) & 1))
        {
            work->body.objs->flag |= 0x80;
        }
        if (work->field_20C <= 0)
        {
            GV_DestroyActor(work);
            return;
        }
        break;
    }

    if (work->body.is_end != 0)
    {
        switch (work->body.action)
        {
        case 2:
            GM_ConfigObjectAction(&work->body, 0, 0, 5);
            break;
        case 5:
            GV_DestroyActor(work);
            return;
        case 3:
            work->field_20C = 0x3C;
            GM_ConfigObjectAction(&work->body, 4, 0, 5);
            if (work->field_1F4 == 0)
            {
                work->field_1F4 = 1;
                GM_SeSetPan(&work->control.mov, 0x33, work->field_1EC->field_E60);
            }
            break;
        case 0:
        case 1:
        case 4:
        case 6:
            break;
        }
    }

    if (work->target != NULL)
    {
        if (work->field_1EC->field_F5C > 0)
        {
            if (work->field_1EC->field_ED0 == 0 && !((GV_Time >> 2) & 1))
            {
                work->body.objs->flag |= 0x80;
            }
            work->target->vital = 0x2710;
            work->target->damage = 0;
            work->target->damaged = 0;
        }
        if (work->target != NULL)
        {
            if (work->target->damaged < work->field_1EC->field_D74 / work->field_1EC->field_DEC)
            {
                if (work->field_1EC->field_D74 / work->field_1EC->field_DF0 >= work->field_1EC->field_E0C)
                {
                    work->target->vital = 0x2710;
                    work->target->damage = 0;
                    work->target->damaged = 0;
                }
            }
            if (work->target != NULL && work->target->damaged != 0)
            {
                if (work->target->damaged >= work->field_1EC->field_D74 / work->field_1EC->field_DEC)
                {
                    work->field_1EC->field_F5C = work->field_1EC->field_E14;
                }
                else
                {
                    work->target->damaged = work->field_1EC->field_D74 / work->field_1EC->field_DF0;
                    work->field_1EC->field_F5C = work->field_1EC->field_E18;
                }
                if ((work->field_1EC->field_E0C -= work->target->damaged) < 0)
                {
                    work->field_1EC->field_E0C = 0;
                }
                work->target->vital = 0x2710;
                work->target->damage = 0;
                work->target->damaged = 0;
                if (work->field_1EC->field_E0C > 0)
                {
                    GM_SeSetPan(&work->control.mov, 0x88, work->field_1EC->field_E60);
                }
            }
        }
    }

    if (GM_Vitality != 0 && GM_GameOverTimer == 0 && work->target != NULL && work->field_1EC->field_E0C <= 0)
    {
        GM_EnemyKillCount++;
        work->field_1EC->field_E0C = work->field_1EC->field_D74;
        work->field_1F0 = 1;
        GM_FreeTarget(work->target);
        work->target = NULL;
        AN_Blast_high(&work->control.mov);
        GM_SeSetPan(&work->control.mov, 0xB1, work->field_1EC->field_E60);
        GM_FreeObject(&work->body);
        GM_InitObject(&work->body, GV_StrCode(s05a_dword_800E358C), 0x32D, GV_StrCode(s05a_dword_800E3584));
        GM_ConfigObjectJoint(&work->body);
        GM_ConfigMotionControl(&work->body, &work->m_ctrl, GV_StrCode(s05a_dword_800E3584), work->m_segs1,
                               work->m_segs2, &work->subcontrol, work->rots);
        GM_ConfigObjectLight(&work->body, &work->light[0]);
        GM_ActMotion(&work->body);
        GM_ActControl(&work->control);
        GM_ActObject(&work->body);
        if (work->field_1EC->field_E08 >= 2)
        {
            GM_SeSetPan(&work->control.mov, 0x81, work->field_1EC->field_E60);
        }
        else
        {
            GM_SeSetPan(&work->control.mov, 0x84, work->field_1EC->field_E60);
        }
        GM_ConfigObjectAction(&work->body, 3, 0, 5);
        vec1.vx = 0;
        vec1.vy = 6;
        vec1.vz = 0xC;
        vec1.pad = 0xF;
        work->field_228 = NewDemoKage(&work->body, vec1, &work->field_22C, &work->field_230, 0x80, 0x80, 0x80);
        memset(&vec1, 0, 8);
        vec1.vx = -work->control.mov.vx;
        vec1.vy = -work->control.mov.vy;
        vec1.vz = -work->control.mov.vz;
        work->control.turn.vx = 0;
        work->control.turn.vy = ratan2(vec1.vx, vec1.vz);
        work->control.turn.vz = 0;
        work->field_204 = 0;
    }

    work->field_200 = work->body.height;
    work->field_1EC->field_EB4 = work->control.mov;
    work->field_1E8 = 0;
}

void s05a_800DEB94(Sol *work)
{
    work->field_1EC->field_EB0 = 0;
    if (work->field_228)
    {
        GV_DestroyActor(work->field_228);
    }
    GM_FreeObject(&work->body);
    GM_FreeControl(&work->control);
    if (work->target)
    {
        GM_FreeTarget(work->target);
    }
    if (work->homing)
    {
        GM_FreeHomingTarget(work->homing);
    }
}
int s05a_800DEC18(Sol *work, SVECTOR *s2, int a2)
{
    int     v;
    int     heights[2];
    SVECTOR local;

    v = 1;
    if (work->field_204 == 0)
    {
        work->field_208 = 0;
    }

    if (a2 - s2->vy <= 0)
    {
        work->field_204 += s2->vy - a2;
    }
    if (work->field_204 < 0x190)
    {
        return a2;
    }

    if (work->field_208 == 0)
    {
        v = work->m_ctrl.info1.frames_left;
        if (v <= 0)
        {
            v = 1;
        }
    }

    local = *s2;
    local.vy += 0x2710;
    if (HZD_LevelHazardCheck(work->control.map->hzd, &local, HZD_CHK_FLOOR) != 1)
    {
        local.vy = 0;
    }
    else
    {
        HZD_GetLevelHeight(heights);
        local.vy = heights[0];
    }
    local.vy += 0x64;

    if (work->field_208 == 0)
    {
        work->field_208 = (s2->vy - local.vy) / v;
    }

    v = s2->vy - work->field_208;
    if (v < local.vy)
    {
        v = local.vy;
    }
    {
        int t = work->field_208 * 15;
        work->field_208 = t / 14;
    }
    if (work->field_208 >= 0x3E9)
    {
        work->field_208 = 0x3E8;
    }
    return v;
}
void s05a_800DEDE8(CONTROL *control, int fuse_time, u_short *arg3)
{
    int     lvl[2];
    SVECTOR pos;
    SVECTOR tgt;
    SVECTOR mov_d;
    SVECTOR rot_d;
    int     hit;
    int     frames;
    int     d1;
    int     d2;
    int     v;
    int     spd;
    int     q;
    short   h;

    mov_d.vx = s05a_dword_800C362C->control.mov.vx - s05a_dword_800C362C->snap_control.mov.vx;
    mov_d.vy = s05a_dword_800C362C->control.mov.vy - s05a_dword_800C362C->snap_control.mov.vy;
    mov_d.vz = s05a_dword_800C362C->control.mov.vz - s05a_dword_800C362C->snap_control.mov.vz;
    rot_d.vx = s05a_dword_800C362C->control.rot.vx - s05a_dword_800C362C->snap_control.rot.vx;
    rot_d.vy = s05a_dword_800C362C->control.rot.vy - s05a_dword_800C362C->snap_control.rot.vy;
    rot_d.vz = s05a_dword_800C362C->control.rot.vz - s05a_dword_800C362C->snap_control.rot.vz;

    pos = control->mov;
    pos.vy += 0x4B;
    if (HZD_GetFloorHit(&s05a_dword_800C362C->copy2, &pos) == 1)
    {
        HZD_GetLevelHeight(lvl);
        hit = control->mov.vy - lvl[0];
        if (hit < 0x96)
        {
            DG_SetPos2(&mov_d, &rot_d);
            memset(&pos, 0, 8);
            pos.vy = s05a_dword_800C362C->body.rots[3].vy - s05a_dword_800C362C->snap_body.rots[3].vy;
            DG_RotatePos(&pos);
            pos = control->mov;
            pos.vx -= s05a_dword_800C362C->snap_control.mov.vx;
            pos.vy -= s05a_dword_800C362C->snap_control.mov.vy;
            pos.vz -= s05a_dword_800C362C->snap_control.mov.vz;
            DG_PutVector(&pos, &pos, 1);
            pos.vx += s05a_dword_800C362C->snap_control.mov.vx;
            pos.vy += s05a_dword_800C362C->snap_control.mov.vy;
            pos.vz += s05a_dword_800C362C->snap_control.mov.vz;
            hit = HZD_GetFloorHit(&s05a_dword_800C362C->hzd[4].flr[1], &pos);
            HZD_GetLevelHeight(lvl);
            if (hit & 1)
            {
                control->mov.vy = lvl[0];
            }
            else if (hit & 2)
            {
                control->mov.vy = lvl[1];
            }
            if (hit & 3)
            {
                control->step.vx = pos.vx - control->mov.vx;
                control->step.vz = pos.vz - control->mov.vz;
                return;
            }
        }
    }

    pos = control->mov;
    pos.vy += 0x4B;
    if (HZD_GetFloorHit(&s05a_dword_800C362C->copy0, &pos) == 1)
    {
        HZD_GetLevelHeight(lvl);
        hit = control->mov.vy - lvl[0];
        if (hit < 0x96)
        {
            DG_SetPos2(&mov_d, &rot_d);
            pos = control->mov;
            pos.vx -= s05a_dword_800C362C->snap_control.mov.vx;
            pos.vy -= s05a_dword_800C362C->snap_control.mov.vy;
            pos.vz -= s05a_dword_800C362C->snap_control.mov.vz;
            DG_PutVector(&pos, &pos, 1);
            pos.vx += s05a_dword_800C362C->snap_control.mov.vx;
            pos.vy += s05a_dword_800C362C->snap_control.mov.vy;
            pos.vz += s05a_dword_800C362C->snap_control.mov.vz;
            hit = HZD_GetFloorHit(&s05a_dword_800C362C->hzd[0].flr[1], &pos);
            HZD_GetLevelHeight(lvl);
            if (hit & 1)
            {
                control->mov.vy = lvl[0];
            }
            else if (hit & 2)
            {
                control->mov.vy = lvl[1];
            }
            if (hit & 3)
            {
                control->step.vx = pos.vx - control->mov.vx;
                control->step.vz = pos.vz - control->mov.vz;
                return;
            }
        }
    }

    pos = control->mov;
    pos.vy += 0x4B;
    if (HZD_GetFloorHit(&s05a_dword_800C362C->copy1, &pos) == 1)
    {
        HZD_GetLevelHeight(lvl);
        hit = control->mov.vy - lvl[0];
        if (hit < 0x96)
        {
            DG_SetPos2(&mov_d, &rot_d);
            pos = control->mov;
            pos.vx -= s05a_dword_800C362C->snap_control.mov.vx;
            pos.vy -= s05a_dword_800C362C->snap_control.mov.vy;
            pos.vz -= s05a_dword_800C362C->snap_control.mov.vz;
            DG_PutVector(&pos, &pos, 1);
            pos.vx += s05a_dword_800C362C->snap_control.mov.vx;
            pos.vy += s05a_dword_800C362C->snap_control.mov.vy;
            pos.vz += s05a_dword_800C362C->snap_control.mov.vz;
            hit = HZD_GetFloorHit(&s05a_dword_800C362C->hzd[1].flr[1], &pos);
            HZD_GetLevelHeight(lvl);
            if (hit & 1)
            {
                control->mov.vy = lvl[0];
            }
            else if (hit & 2)
            {
                control->mov.vy = lvl[1];
            }
            if (hit & 3)
            {
                control->step.vx = pos.vx - control->mov.vx;
                control->step.vz = pos.vz - control->mov.vz;
                return;
            }
        }
    }

    if (*arg3 & 4)
    {
        return;
    }

    tgt.vx = s05a_dword_800C362C->body.objs->objs[12].world.t[0];
    tgt.vy = s05a_dword_800C362C->body.objs->objs[12].world.t[1];
    tgt.vz = s05a_dword_800C362C->body.objs->objs[12].world.t[2];
    pos.vx = (tgt.vx - GM_PlayerControl->mov.vx) >> 2;
    pos.vy = (tgt.vy - GM_PlayerControl->mov.vy) >> 2;
    pos.vz = (tgt.vz - GM_PlayerControl->mov.vz) >> 2;
    memset(&rot_d, 0, 8);
    rot_d.vy = ratan2(pos.vx, pos.vz);
    while (rot_d.vy < -0x800) rot_d.vy += 0x1000;
    while (rot_d.vy >= 0x801) rot_d.vy -= 0x1000;
    hit = SquareRoot0(pos.vx * pos.vx + pos.vz * pos.vz) * 4;

    if (!(*arg3 & 1))
    {
        *arg3 |= 1;
        if (GM_PlayerStatus & 0x340)
        {
            return;
        }
        if (s05a_dword_800C362C->field_DF8 < hit)
        {
            return;
        }
        pos.vy = rot_d.vy - GM_PlayerControl->rot.vy;
        while (pos.vy < -0x800) pos.vy += 0x1000;
        while (pos.vy >= 0x801) pos.vy -= 0x1000;
        if (pos.vy < -s05a_dword_800C362C->field_DF4 || pos.vy > s05a_dword_800C362C->field_DF4)
        {
            return;
        }
        memset(&control->step, 0, 8);
        if (hit <= s05a_dword_800C362C->field_DF8 * 2 / 3)
        {
            control->step.vz = 0x78;
        }
        else
        {
            control->step.vz = 0xAA;
        }
        frames = hit / control->step.vz * 3 / 4;
        h = control->mov.vy;
        if (h < tgt.vy) h = tgt.vy;
        pos.vy = h + 0x3E8;
        d1 = pos.vy - control->mov.vy;
        d2 = pos.vy - tgt.vy;
        v = d1 + d2;
        if (v == 0)
        {
            d1 = 0;
        }
        else
        {
            d1 = frames * d1 / v;
        }
        v = 0;
        if (d1 != 0)
        {
            v = (pos.vy - control->mov.vy) * 2 / d1 / d1;
        }
        control->step.vy = v * d1;
        *arg3 |= v << 8;
        *arg3 |= 2;
    }
    else
    {
        if (!(*arg3 & 2))
        {
            return;
        }
        if (GM_PlayerStatus & 0x300)
        {
            return;
        }
        if (control->mov.vy < s05a_dword_800C362C->body.objs->objs[12].world.t[1])
        {
            return;
        }
    }

    memset(&mov_d, 0, 8);
    spd = SquareRoot0(control->step.vx * control->step.vx + control->step.vz * control->step.vz);
    q = hit / fuse_time;
    mov_d.vz = spd;
    if (mov_d.vz < q) mov_d.vz = q;
    DG_SetPos2(&DG_ZeroVector, &rot_d);
    DG_PutVector(&mov_d, &mov_d, 1);
    control->step.vx = mov_d.vx;
    control->step.vz = mov_d.vz;
    control->step.vy += 0x10;
    control->step.vy -= (short)*arg3 >> 8;
}
int s05a_800DF834(int arg0, SVECTOR *vec, u_short *arg3)
{
    SVECTOR d;
    SVECTOR e;
    int     dist;

    if (arg0 != 0)
    {
        return 0;
    }
    if (s05a_dword_800C362C->field_EB0 == NULL)
    {
        return 0;
    }

    d.vx = s05a_dword_800C362C->body.objs->objs[12].world.t[0];
    d.vy = s05a_dword_800C362C->body.objs->objs[12].world.t[1];
    d.vz = s05a_dword_800C362C->body.objs->objs[12].world.t[2];
    d.vx -= vec->vx;
    d.vy -= vec->vy;
    d.vz -= vec->vz;

    e.vx = s05a_dword_800C362C->body.objs->objs[10].model->ux -
           s05a_dword_800C362C->body.objs->objs[10].model->lx;
    e.vz = s05a_dword_800C362C->body.objs->objs[10].model->uz -
           s05a_dword_800C362C->body.objs->objs[10].model->lz;
    e.vx = (e.vx + e.vz) >> 2;

    dist = SquareRoot0(d.vx * d.vx + d.vy * d.vy + d.vz * d.vz);
    if (dist < e.vx * s05a_dword_800C362C->field_DFC)
    {
        GM_SeSetPan(&s05a_dword_800C362C->field_EB0->field_1C0->center, 0xB2,
                    s05a_dword_800C362C->field_E60);
        *arg3 |= 4;
        return 1;
    }
    return 0;
}
int s05a_800DF9C8(TARGET *t, int flags)
{
    SVECTOR delta;
    SVECTOR e;
    int     i;
    short   dx, dy, dz;
    int     dist;

    if (s05a_dword_800C362C->field_ED0 != 0)
    {
        if (s05a_dword_800C362C->field_EB0 != 0)
        {
            s05a_dword_800C362C->field_EB0->field_1C0->vital = 0x2710;
            s05a_dword_800C362C->field_EB0->field_1C0->damage = 0;
            s05a_dword_800C362C->field_EB0->field_1C0->damaged = 0;
        }
        for (i = 0; i < 10; i++)
        {
            s05a_dword_800C362C->field_718[i]->vital = 0x2710;
            s05a_dword_800C362C->field_718[i]->damage = 0;
            s05a_dword_800C362C->field_718[i]->damaged = 0;
        }
        return 1;
    }

    if (s05a_dword_800C362C->field_EB0 != 0)
    {
        delta = s05a_dword_800C362C->field_EB0->field_1C0->center;
        dx = delta.vx - t->center.vx;
        delta.vx = dx;
        dy = delta.vy - t->center.vy;
        delta.vy = dy;
        dz = delta.vz - t->center.vz;
        delta.vz = dz;

        e.vx = s05a_dword_800C362C->body.objs->objs[10].model->ux -
               s05a_dword_800C362C->body.objs->objs[10].model->lx;
        e.vz = s05a_dword_800C362C->body.objs->objs[10].model->uz -
               s05a_dword_800C362C->body.objs->objs[10].model->lz;
        e.vx = (e.vx + e.vz) >> 2;

        if (flags & 4)
        {
            for (i = 0; i < 10; i++)
            {
                s05a_dword_800C362C->field_718[i]->vital = 0x2710;
                s05a_dword_800C362C->field_718[i]->damage = 0;
                s05a_dword_800C362C->field_718[i]->damaged = 0;
            }
            if (s05a_dword_800C362C->field_F5C > 0)
            {
                return 0;
            }
            s05a_dword_800C362C->field_EB0->field_1C0->damaged =
                (u_short)s05a_dword_800C362C->field_D74;
            return 1;
        }

        if (s05a_dword_800C362C->field_EB0->field_1C0->damaged != 0)
        {
            dist = SquareRoot0(dx * dx + dy * dy + dz * dz);
            if (dist < e.vx * s05a_dword_800C362C->field_DFC * 3 &&
                t->center.vy >=
                    s05a_dword_800C362C->field_EB0->field_1C0->center.vy - 0x3E8)
            {
                for (i = 0; i < 10; i++)
                {
                    s05a_dword_800C362C->field_718[i]->vital = 0x2710;
                    s05a_dword_800C362C->field_718[i]->damage = 0;
                    s05a_dword_800C362C->field_718[i]->damaged = 0;
                }
                if (s05a_dword_800C362C->field_F5C > 0)
                {
                    return 0;
                }
                s05a_dword_800C362C->field_EB0->field_1C0->damaged =
                    s05a_dword_800C362C->field_D74 / s05a_dword_800C362C->field_DEC;
                return (s05a_dword_800C362C->field_E0C -
                        s05a_dword_800C362C->field_EB0->field_1C0->damaged) < 1;
            }
        }

        s05a_dword_800C362C->field_EB0->field_1C0->vital = 0x2710;
        s05a_dword_800C362C->field_EB0->field_1C0->damage = 0;
        s05a_dword_800C362C->field_EB0->field_1C0->damaged = 0;
    }

    if (s05a_dword_800C362C->field_F4C > 0 ||
        s05a_dword_800C362C->field_F50 > 0 ||
        HZD_GetFloorHit((HZD_FLR *)((char *)s05a_dword_800C362C + 0x12AC), &t->center) == 1 ||
        HZD_GetFloorHit((HZD_FLR *)((char *)s05a_dword_800C362C + 0x102C), &t->center) == 1 ||
        HZD_GetFloorHit((HZD_FLR *)((char *)s05a_dword_800C362C + 0x10CC), &t->center) == 1)
    {
        for (i = 0; i < 10; i++)
        {
            s05a_dword_800C362C->field_718[i]->vital = 0x2710;
            s05a_dword_800C362C->field_718[i]->damage = 0;
            s05a_dword_800C362C->field_718[i]->damaged = 0;
        }
        return 0;
    }

    for (i = 0; i < 10; i++)
    {
        dx = s05a_dword_800C362C->field_718[i]->center.vx -
             t->center.vx;
        delta.vx = dx;
        dy = s05a_dword_800C362C->field_718[i]->center.vy -
             t->center.vy;
        delta.vy = dy;
        dz = s05a_dword_800C362C->field_718[i]->center.vz -
             t->center.vz;
        delta.vz = dz;
        if (s05a_dword_800C362C->field_718[i]->damaged != 0)
        {
            dist = SquareRoot0(dx * dx + dy * dy + dz * dz);
            if (dist >= 0x9C5)
            {
                s05a_dword_800C362C->field_718[i]->vital = 0x2710;
                s05a_dword_800C362C->field_718[i]->damage = 0;
                s05a_dword_800C362C->field_718[i]->damaged = 0;
            }
        }
    }

    if (s05a_dword_800C362C->field_D64 > s05a_dword_800C362C->field_D88 ||
        s05a_dword_800C362C->field_D68 > s05a_dword_800C362C->field_D8C)
    {
        for (i = 0; i < 10; i++)
        {
            if (s05a_dword_800C362C->field_718[i]->damaged != 0)
            {
                return 1;
            }
        }
    }

    return 0;
}

void s05a_800DFFC0(SnaInitWork *work, void *pFn)
{
    short vec_x = 0;
    work->field_9B8_fn_anim = pFn;
    work->field_9BC_anim_frame = 0;
    work->field_A3A = 0;
    work->field_A38_local_data = 0;

    if ((GM_PlayerStatus & PLAYER_GROUND) != 0)
    {
        vec_x = work->field_A2A;
    }

    work->control.turn.vx = vec_x;
    work->control.turn.vz = 0;
}
void s05a_800DFFF8(SnaInitWork *work, int action_flag, int interp)
{
    if (work->body.action != action_flag)
    {
        GM_ConfigObjectAction(&work->body, action_flag, 0, interp);
    }
}
void s05a_800E002C(SnaInitWork *work, int a2, int interp, int a4)
{
    if (work->body.action2 != a2)
    {
        GM_ConfigObjectOverride(&work->body, a2, 0, interp, a4);
    }
}
int s05a_800E0068(PlayerStatusFlag flag)
{
    return (GM_PlayerStatus & flag) != 0;
}

int s05a_800E0080(PlayerStatusFlag flag)
{
    int temp_v0;

    temp_v0 = GM_PlayerStatus | flag;
    GM_PlayerStatus = temp_v0;
    return temp_v0;
}

void s05a_800E0098(PlayerStatusFlag flag)
{
    GM_PlayerStatus &= ~flag;
}

void s05a_800E00B0(SnaInitWork *snake, SnaFlag1 flags)
{
    snake->field_894_flags1 |= flags;
}

void s05a_800E00C4(SnaInitWork *snake, SnaFlag1 flags)
{
    snake->field_894_flags1 &= ~flags;
}

int s05a_800E00D8(SnaInitWork *snake, SnaFlag1 flags)
{
    return (snake->field_894_flags1 & flags) != 0;
}
void s05a_800E0D38(CONTROL *control, HZD_HDL *hzd);
void s05a_800E0E28(CONTROL *work, HZD_HDL *hzd);
void s05a_800E0F64(CONTROL *work, HZD_HDL *hzd);
void s05a_800E1014(CONTROL *work, HZD_HDL *hzd);

int s05a_800E00EC(GV_ACT *actor)
{
    int      vy = 0;
    SnaInitWork *work = (SnaInitWork *)actor;
    HZD_HDL *hzd;
    SVECTOR  pos;
    SVECTOR  rot;
    int      time;
    int      dist;

    GM_uTenageMotion = -1;
    if (HZD_GetFloorHit(&s05a_dword_800C362C->hzd[0].flr[0], &work->control.mov) == 0 && !(GM_PlayerStatus & 0x1340))
    {
        if (s05a_dword_800C362C->field_EB0 != NULL)
        {
            pos = s05a_dword_800C362C->field_EB0->field_1C0->center;
        }
        else
        {
            pos = s05a_dword_800C362C->control.mov;
        }
        pos.vx = (pos.vx - work->control.mov.vx) >> 2;
        pos.vy = (pos.vy - work->control.mov.vy) >> 2;
        pos.vz = (pos.vz - work->control.mov.vz) >> 2;
        memset(&rot, 0, 8);
        rot.vy = ratan2(pos.vx, pos.vz);
        while (rot.vy < -0x800) rot.vy += 0x1000;
        while (rot.vy >= 0x801) rot.vy -= 0x1000;
        dist = SquareRoot0(pos.vx * pos.vx + pos.vz * pos.vz) * 4;
        if (s05a_dword_800C362C->field_DF8 >= dist)
        {
            pos.vy = rot.vy - GM_PlayerControl->rot.vy;
            while (pos.vy < -0x800) pos.vy += 0x1000;
            while (pos.vy >= 0x801) pos.vy -= 0x1000;

            if (pos.vy >= -s05a_dword_800C362C->field_DF4 && pos.vy <= -s05a_dword_800C362C->field_DF4 / 2)
            {
                if (dist <= s05a_dword_800C362C->field_DF8 * 2 / 3)
                {
                    GM_uTenageMotion = 2;
                }
                else
                {
                    GM_uTenageMotion = 5;
                }
            }
            else if (pos.vy > -s05a_dword_800C362C->field_DF4 / 2 && pos.vy < s05a_dword_800C362C->field_DF4 / 2)
            {
                if (dist <= s05a_dword_800C362C->field_DF8 * 2 / 3)
                {
                    GM_uTenageMotion = 0;
                }
                else
                {
                    GM_uTenageMotion = 3;
                }
            }
            else if (pos.vy >= s05a_dword_800C362C->field_DF4 / 2 && pos.vy <= s05a_dword_800C362C->field_DF4)
            {
                if (dist <= s05a_dword_800C362C->field_DF8 * 2 / 3)
                {
                    GM_uTenageMotion = 1;
                }
                else
                {
                    GM_uTenageMotion = 4;
                }
            }
        }
        return 0;
    }

    hzd = work->control.map->hzd;
    s05a_800E0D38(&work->control, hzd);
    GM_CurrentMap = work->control.map->index;

    if (work->control.r_sphere > 0)
    {
        work->control.n_touches = 0;
        if (work->control.hzd_height != -0x7fff)
        {
            vy = work->control.mov.vy;
            work->control.mov.vy = work->control.hzd_height;
        }
        s05a_800E0E28(&work->control, hzd);
        work->control.mov.vx += work->control.step.vx;
        work->control.mov.vz += work->control.step.vz;
        s05a_800E0F64(&work->control, hzd);
        if (work->control.hzd_height != -0x7fff)
        {
            work->control.mov.vy = vy;
        }
        time = work->control.interp;
        if (work->control.interp == 0)
        {
            GV_NearExp4PV(&work->control.rot.vx, &work->control.turn.vx, 3);
        }
        else
        {
            GV_NearTimePV(&work->control.rot.vx, &work->control.turn.vx, work->control.interp, 3);
            work->control.interp = time - 1;
        }
        s05a_800E1014(&work->control, hzd);
    }
    else if (work->control.r_sphere < 0)
    {
        work->control.n_touches = 0;
        time = work->control.interp;
        work->control.mov.vx += work->control.step.vx;
        work->control.mov.vz += work->control.step.vz;
        if (time == 0)
        {
            GV_NearExp4PV(&work->control.rot.vx, &work->control.turn.vx, 3);
        }
        else
        {
            GV_NearTimePV(&work->control.rot.vx, &work->control.turn.vx, time, 3);
            work->control.interp = time - 1;
        }
        if (work->control.r_sphere >= -1)
        {
            s05a_800E1014(&work->control, hzd);
        }
    }

    if (!(work->control.skip_flag & CTRL_SKIP_TRAP))
    {
        work->control.evt.mov = work->control.mov;
        work->control.evt.mov.pad = work->control.rot.vy;
        HZD_EnterTrap(hzd, &work->control.evt);
    }
    DG_SetPos2(&work->control.mov, &work->control.rot);
    return 1;
}
int s05a_800E066C(SnaInitWork *work_)
{
    SnaInitWork *work = work_;
    int     heights[2];
    SVECTOR size;
    TARGET  target;
    int     hit;
    int     dx, dz, dist;
    int     status;

    if (s05a_dword_800C362C->field_ED0 == 1)
    {
        s05a_dword_800E3800.step.vx = 0;
        s05a_dword_800E3800.step.vy = 0;
        s05a_dword_800E3800.step.vz = 0;
        GM_PlayerControl->mov  = s05a_dword_800E3800.mov;
        GM_PlayerControl->step = s05a_dword_800E3800.step;
        GM_PlayerControl->rot  = s05a_dword_800E3800.rot;
        GM_PlayerControl->turn = s05a_dword_800E3800.turn;
        GM_GameStatus   &= ~STATE_PADRELEASE;
        GM_PlayerStatus &= ~PLAYER_PAD_OFF;
        return 0;
    }
    if (s05a_dword_800C362C->field_ED0 != 0)
    {
        GM_PlayerControl->mov.vx = 0x7530;
        GM_PlayerControl->mov.vy = 0;
        GM_PlayerControl->mov.vz = 0x7530;
        GM_PlayerStatus |= PLAYER_PAD_OFF;
        return 0;
    }

    if (s05a_dword_800C362C->field_D54 == 1 || s05a_dword_800C362C->field_D54 == 6)
    {
        s05a_dword_800E3800 = *GM_PlayerControl;
        return 0;
    }

    if (HZD_GetFloorHit((HZD_FLR *)&s05a_dword_800C362C->hzd[0].flr[0], &GM_PlayerPosition) != 0)
    {
        if (s05a_dword_800C362C->field_F78 > 0)
        {
            s05a_dword_800C362C->field_F78 = 0x5a;
        }
        hit = HZD_LevelHazardCheck(s05a_dword_800C362C->control.map->hzd, &s05a_dword_800E3800.mov, HZD_CHK_F_FLOOR);
        HZD_GetLevelHeight(heights);
        if (hit & 1)
        {
            s05a_dword_800E3800.mov.vy = heights[0];
        }
        else if (hit & 2)
        {
            s05a_dword_800E3800.mov.vy = heights[1];
        }
        else
        {
            s05a_dword_800E3800.mov.vy = 0;
        }
        s05a_dword_800E3800.step.vx = 0;
        s05a_dword_800E3800.step.vy = 0;
        s05a_dword_800E3800.step.vz = 0;
        s05a_dword_800E3800.mov.vy += 0x64;
        GM_PlayerControl->mov  = s05a_dword_800E3800.mov;
        GM_PlayerControl->step = s05a_dword_800E3800.step;
        GM_PlayerControl->rot  = s05a_dword_800E3800.rot;
        GM_PlayerControl->turn = s05a_dword_800E3800.turn;
        GM_PlayerStatus |= PLAYER_PAD_OFF;
        DG_SetPos2(&GM_PlayerControl->mov, &GM_PlayerControl->rot);

        if ((u_int)(GM_PlayerAction - 0x43) < 2)
        {
            GM_ActObject(&work->body);
            return 1;
        }
        status = GM_PlayerStatus;
        if (status & PLAYER_DOWNED)
        {
            GM_ActObject(&work->body);
            return 1;
        }
        if (GM_Vitality == 0)
        {
            GM_ActObject(&work->body);
            return 1;
        }
        if (GM_GameOverTimer != 0)
        {
            GM_ActObject(&work->body);
            return 1;
        }

        work->field_894_flags1 &= ~1;
        work->field_89C_pTarget->class |= 0x9e;
        GM_PlayerStatus = status & ~(PLAYER_INVINCIBLE | PLAYER_DAMAGED);
        *(int *)&work->body.objs->flag &= ~0x80;
        size.vx = 0x7d0;
        size.vy = 0x7d0;
        size.vz = 0x7d0;
        memset(&target, 0, sizeof(target));
        GM_SetTarget(&target, 4, ENEMY_SIDE, &size);
        GM_SetPowerTarget(&target, POWER_CONST, ATK_BLAST, s05a_dword_800C362C->field_DA0, 0, &DG_ZeroVector);
        GM_MoveTarget(&target, &GM_PlayerPosition);
        GM_PowerTarget(&target);
        GM_PushTarget(&target);
        if (work->field_89C_pTarget->damaged != 0)
        {
            GM_PlayerStatus |= PLAYER_DOWNED;
            s05a_dword_800C362C->field_F78 = 0x5a;
            GM_SeSetPan(&GM_PlayerPosition, 0xbd, 0x3f);
        }
        return 0;
    }

    size.vy = 0;
    dx = (s05a_dword_800E3800.mov.vx - GM_PlayerControl->mov.vx) >> 2;
    size.vx = dx;
    dz = (s05a_dword_800E3800.mov.vz - GM_PlayerControl->mov.vz) >> 2;
    size.vz = dz;
    dist = SquareRoot0(dx * dx + dz * dz);
    if ((dist << 2) < 0x1f4)
    {
        GM_GameStatus   &= ~STATE_PADRELEASE;
        GM_PlayerStatus &= ~PLAYER_PAD_OFF;
        s05a_dword_800E3800 = *GM_PlayerControl;
        return 0;
    }

    hit = HZD_LevelHazardCheck(s05a_dword_800C362C->control.map->hzd, &s05a_dword_800E3800.mov, HZD_CHK_F_FLOOR);
    HZD_GetLevelHeight(heights);
    if (hit & 1)
    {
        s05a_dword_800E3800.mov.vy = heights[0];
    }
    else if (hit & 2)
    {
        s05a_dword_800E3800.mov.vy = heights[1];
    }
    else
    {
        s05a_dword_800E3800.mov.vy = 0;
    }
    s05a_dword_800E3800.step.vx = 0;
    s05a_dword_800E3800.step.vy = 0;
    s05a_dword_800E3800.step.vz = 0;
    s05a_dword_800E3800.mov.vy += 0x64;
    GM_PlayerControl->mov  = s05a_dword_800E3800.mov;
    GM_PlayerControl->step = s05a_dword_800E3800.step;
    GM_PlayerControl->rot  = s05a_dword_800E3800.rot;
    GM_PlayerControl->turn = s05a_dword_800E3800.turn;
    GM_PlayerStatus |= PLAYER_PAD_OFF;
    DG_SetPos2(&GM_PlayerControl->mov, &GM_PlayerControl->rot);
    GM_ActObject(&work->body);
    return 1;
}
void s05a_800E0D38(CONTROL *control, HZD_HDL *hzd)
{
    GV_MSG *msg;
    int     name;
    int     n_msg;
    int     map_msg, move_msg;
    MAP    *map;

    name = control->name;

    if ((name != 0) && !(control->skip_flag & CTRL_SKIP_MESSAGE))
    {
        n_msg = GV_ReceiveMessage(name, &control->msg);
        control->n_msg = n_msg;

        msg = control->msg;

        map_msg = HASH_MAP;
        move_msg = HASH_MOVE2;

        for (n_msg--; n_msg >= 0; n_msg--, msg++)
        {
            if (msg->message[0] == map_msg)
            {
                map = GM_FindMap(msg->message[1]);

                if (map)
                {
                    control->map = map;
                }
            }
            else if (msg->message[0] == move_msg)
            {
                control->mov.vx = msg->message[1];
                control->mov.vy = msg->message[2];
                control->mov.vz = msg->message[3];
            }
        }
    }
}

void s05a_800E0E28(CONTROL *work, HZD_HDL *hzd)
{
    SVECTOR local;
    int     half;
    int     dist;
    int     len;
    int     diff;

    half = work->r_sphere / 2;
    dist = work->step.vx;
    if (dist < 0)
    {
        dist = -dist;
    }
    if (work->step.vz > 0)
    {
        dist += work->step.vz;
    }
    else
    {
        dist -= work->step.vz;
    }

    if (half < dist)
    {
        GV_AddVec3(&work->mov, &work->step, &local);
        if (HZD_OnlineHazardCheck(hzd, &work->mov, &local, 5, work->seg_flag) != 0)
        {
            work->n_touches = 1;
            work->segs[0] = HZD_GetOnlineHazard();
            work->is_edge[0] = HZD_GetOnlineHazardAtr();
            HZD_GetOnlineVector(&work->vecs[0]);
            len = GV_VecLen3(&work->vecs[0]);
            diff = len - half;
            if (diff < 0)
            {
                GV_LenVec3(&work->vecs[0], &local, len, -diff);
                GV_SubVec3(&DG_ZeroVector, &local, &local);
            }
            else
            {
                GV_LenVec3(&work->vecs[0], &local, len, diff);
            }
            work->step = local;
        }
    }
}
void s05a_800E0F64(CONTROL *work, HZD_HDL *hzd)
{
    SVECTOR react;
    int     hazard;

    hazard = HZD_NearHazardCheck(hzd, &work->mov, 0x1F4, 4, work->seg_flag);
    if (hazard > 0)
    {
        work->n_touches = hazard;
        HZD_GetNearHazard(&work->segs[0]);
        HZD_GetIsEdge(&work->is_edge[0]);
        HZD_GetNearVector(&work->vecs[0]);
        HZD_HazardReaction(&work->vecs[0], hazard, work->r_sphere, &react);
        work->mov.vx += react.vx;
        work->mov.vz += react.vz;
    }
}

void s05a_800E1014(CONTROL *work, HZD_HDL *hzd)
{
    int height[2];
    int flags;
    int y;
    int base;
    int lo;

    y = work->mov.vy + work->step.vy;
    base = work->height;
    work->grounded = 0;
    flags = HZD_LevelHazardCheck(hzd, &work->mov, HZD_CHK_F_FLOOR);
    HZD_GetLevelHeight(height);

    if (flags & HZD_CHK_D_FLOOR)
    {
        if ((unsigned int)(height[1] - work->levels[0] + 0xC7) < 0x18F)
        {
            height[0] = height[1];
            flags &= ~HZD_CHK_D_FLOOR;
        }
    }
    if (!(flags & HZD_CHK_F_FLOOR))
    {
        height[0] = 0;
    }
    if (!(flags & HZD_CHK_D_FLOOR))
    {
        height[1] = 0x7D00;
    }

    lo = base;
    if (flags & HZD_CHK_F_FLOOR)
    {
        lo += height[0];
    }

    if (y < lo)
    {
        y = lo;
        work->grounded = 1;
    }
    else if ((flags & HZD_CHK_D_FLOOR) && height[1] - base < y)
    {
        y = height[1] - base;
        work->grounded = 2;
    }

    work->levels[0] = height[0];
    lo = (work->levels[1] = height[1]);
    work->mov.vy = y;
}
