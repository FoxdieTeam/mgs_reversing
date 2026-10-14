#include "mgstype.h"
#include <libgte.h>
#include <rand.h>
#include "game/game.h"

typedef struct _Work Work;
typedef void (*MrlStateFunc)(Work *work, int time);

/* Meryl (or Otacon) sitting in the jeep Snake rides in, spawned by jeep.c */
struct _Work
{
    GV_ACT         actor;                              /* 0x000 */
    CONTROL       *root_ctrl;                          /* 0x020: the jeep's control */
    MATRIX        *root_mat;                           /* 0x024: the jeep body's world matrix */
    CONTROL        control;                            /* 0x028 */
    OBJECT         body;                               /* 0x0A4 */
    MOTION_CONTROL m_ctrl;                             /* 0x188 */
    MOTION_SEGMENT m_segs1[17];                        /* 0x1D8 */
    MOTION_SEGMENT m_segs2[17];                        /* 0x43C */
    SVECTOR        rots[16];                           /* 0x6A0 */
    SVECTOR        adjust[16];                         /* 0x720 */
    MATRIX         light[2];                           /* 0x7A0 */
    int            name_id;                            /* 0x7E0: GV_StrCode of the character's name */
    int            head_turn;                          /* 0x7E4: target head rotation */
    TARGET        *target;                             /* 0x7E8 */
    MrlStateFunc   state;                              /* 0x7EC */
    char           pad_7F0[0x4];
    int            time;                               /* 0x7F4: frames in the current state */
    char           pad_7F8[0x4];
    int            action;                             /* 0x7FC */
    int            flags;                              /* 0x800: mrl_flags of the jeep system */
    char           pad_804[0x818 - 0x804];
    short          se[4];                              /* 0x818 */
};

#include "../jeep_system.h"


extern SVECTOR s19b_dword_800C39E0;
extern void s19b_jeep_mrl_800D47B8(Work *work);
extern void sna_act_helper2_helper2_80033054(int id, SVECTOR *vec);

void s19b_jeep_mrl_800D3D30(Work *work)
{
    CONTROL *ctl = &work->control;
    OBJECT  *body;
    DG_OBJS *objs;
    SVECTOR *jpos = &Takabe_JeepSystem.meryl_head;

    s19b_jeep_mrl_800D47B8(work);
    body = &work->body;
    GM_ActMotion(body);
    sna_act_helper2_helper2_80033054(work->name_id, &work->adjust[6]);
    work->adjust[6].vy = GV_NearSpeed(work->adjust[6].vy, work->head_turn, 200);
    ctl->rot = ctl->turn = DG_ZeroVector;
    ctl->mov = s19b_dword_800C39E0;
    GM_ActControl(ctl);
    GM_ActObject(body);
    objs = body->objs;
    CompMatrix(work->root_mat, &objs->world, &objs->world);
    ctl->mov.vx = objs->world.t[0];
    ctl->mov.vy = objs->world.t[1];
    ctl->mov.vz = objs->world.t[2];
    DG_GetLightMatrix(&ctl->mov, &work->light[0]);
    jpos->vx = body->objs->objs[6].world.t[0];
    jpos->vy = body->objs->objs[6].world.t[1];
    jpos->vz = body->objs->objs[6].world.t[2];
    GM_MoveTarget(work->target, &ctl->mov);
}
int s19b_jeep_mrl_800D3E98(Work *work, int name, int otacon)
{
    CONTROL *ctl = &work->control;
    OBJECT  *body;

    if (GM_InitControl(ctl, name, GM_CurrentMap) < 0)
    {
        return -1;
    }
    ctl->mov = work->root_ctrl->mov;
    ctl->rot = work->root_ctrl->rot;
    GM_ConfigControlInterp(ctl, 4);

    body = &work->body;
    if (otacon == 0)
    {
        GM_InitObject(body, GV_StrCode("meryl"), 0x2D, GV_StrCode("mel_19b"));
        work->name_id = GV_StrCode("メリル");
        work->se[0] = 0x82;
        work->se[1] = 0x83;
        work->se[2] = 0x84;
        work->se[3] = 0x82;
    }
    else
    {
        GM_InitObject(body, GV_StrCode("otacom"), 0x2D, GV_StrCode("mel_19b"));
        work->name_id = GV_StrCode("オタコン");
        work->se[0] = 0x85;
        work->se[1] = 0x86;
        work->se[2] = 0x87;
        work->se[3] = 0x85;
    }
    GM_ConfigObjectJoint(body);
    GM_ConfigMotionControl(body, &work->m_ctrl, GV_StrCode("mel_19b"), work->m_segs1, work->m_segs2,
                           ctl, work->rots);
    GM_ConfigObjectLight(body, &work->light[0]);
    GM_ConfigObjectAction(body, 0, 0, 0);
    GM_ActMotion(&work->body);
    GM_ConfigMotionAdjust(body, work->adjust);
    work->target = GM_AllocTarget();
    Takabe_JeepSystem.meryl_body = body;
    ctl->r_sphere = -2;
    return 0;
}

void s19b_jeep_mrl_800D4098(Work *work)
{
    GM_FreeTarget(work->target);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
}
GV_ACT *s19b_jeep_mrl_800D40D4(CONTROL *root_ctrl, MATRIX *root_mat, int otacon)
{
    Work *work = GV_NewActor(GV_ACTOR_AFTER, 0x820);

    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jeep_mrl_800D3D30, s19b_jeep_mrl_800D4098,
                         "jeep_mrl.c");
        work->root_ctrl = root_ctrl;
        work->root_mat = root_mat;
        if (s19b_jeep_mrl_800D3E98(work, GV_StrCode("meryl"), otacon) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return &work->actor;
}

extern void s19b_jeep_mrl_800D424C(Work *work, int time);
extern void s19b_jeep_mrl_800D4290(Work *work, int time);
extern void s19b_jeep_mrl_800D43AC(Work *work, int time);
extern void s19b_jeep_mrl_800D4414(Work *work, int time);
extern void s19b_jeep_mrl_800D4574(Work *work, int time);
extern void s19b_jeep_mrl_800D46D4(Work *work, int time);

int s19b_jeep_mrl_800D4188(Work *work)
{
    int flags = work->flags;

    if (flags & 2)
    {
        work->state = s19b_jeep_mrl_800D46D4;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (flags & 1)
    {
        work->state = s19b_jeep_mrl_800D424C;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (flags & 0x20)
    {
        work->state = s19b_jeep_mrl_800D4414;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (flags & 0x200)
    {
        work->state = s19b_jeep_mrl_800D4574;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (flags & 0x1000)
    {
        work->state = s19b_jeep_mrl_800D43AC;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if ((flags & 0x10000) == 0)
    {
        work->state = s19b_jeep_mrl_800D4290;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    return 0;
}

void s19b_jeep_mrl_800D424C(Work *work, int time)
{
    if (time == 0)
    {
        work->action = 0;
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }
    s19b_jeep_mrl_800D4188(work);
}
void s19b_jeep_mrl_800D4290(Work *work, int time)
{
    SVECTOR sp10;
    int     diff;

    if (time == 0)
    {
        work->action = 0;
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }
    if ((Takabe_JeepSystem.flags & 1) && GV_RandU(0x100) < 0x14)
    {
        GM_SeSet(&work->control.mov, work->se[2]);
    }
    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &sp10);

    diff = (GM_PlayerControl->rot.vy - work->control.rot.vy) - work->root_ctrl->rot.vy;
    diff &= 0xFFF;
    if (diff & 0x800)
    {
        diff -= 0x1000;
    }
    if (diff < -0x400)
    {
        diff = -0x400;
    }
    if (diff > 0x400)
    {
        diff = 0x400;
    }
    work->head_turn = diff;

    if (work->flags & 0x10000)
    {
        work->head_turn = 0;
        if (s19b_jeep_mrl_800D4188(work) == 0)
        {
            work->state = s19b_jeep_mrl_800D424C;
            work->time = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
    }
}
void s19b_jeep_mrl_800D43AC(Work *work, int time)
{
    if (time == 0)
    {
        work->action = 7;
        GM_ConfigObjectAction(&work->body, 7, 0, 4);
    }
    if (work->flags & 0x10000)
    {
        work->state = s19b_jeep_mrl_800D424C;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
extern void s19b_jeep_mrl_800D4488(Work *work, int time);
extern void s19b_jeep_mrl_800D4500(Work *work, int time);
extern void s19b_jeep_mrl_800D45E8(Work *work, int time);
extern void s19b_jeep_mrl_800D4660(Work *work, int time);

void s19b_jeep_mrl_800D4414(Work *work, int time)
{
    if (time == 0)
    {
        work->action = 7;
        GM_ConfigObjectAction(&work->body, 7, 0, 4);
    }
    if (s19b_jeep_mrl_800D4188(work) != 0) return;
    if (work->body.is_end == 0) return;
    work->state = s19b_jeep_mrl_800D4488;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s19b_jeep_mrl_800D4488(Work *work, int time)
{
    if (time == 0)
    {
        work->action = 8;
        GM_ConfigObjectAction(&work->body, 8, 0, 0);
    }
    if (s19b_jeep_mrl_800D4188(work) != 0) return;
    if (work->flags & 0x20000) return;
    work->state = s19b_jeep_mrl_800D4500;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s19b_jeep_mrl_800D4500(Work *work, int time)
{
    if (time == 0)
    {
        work->action = 9;
        GM_ConfigObjectAction(&work->body, 9, 0, 4);
    }
    if (s19b_jeep_mrl_800D4188(work) != 0) return;
    if (work->body.is_end == 0) return;
    work->state = s19b_jeep_mrl_800D424C;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s19b_jeep_mrl_800D4574(Work *work, int time)
{
    if (time == 0)
    {
        work->action = 1;
        GM_ConfigObjectAction(&work->body, 1, 0, 4);
    }
    if (s19b_jeep_mrl_800D4188(work) != 0) return;
    if (work->body.is_end == 0) return;
    work->state = s19b_jeep_mrl_800D45E8;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s19b_jeep_mrl_800D45E8(Work *work, int time)
{
    if (time == 0)
    {
        work->action = 2;
        GM_ConfigObjectAction(&work->body, 2, 0, 0);
    }
    if (s19b_jeep_mrl_800D4188(work) != 0) return;
    if (work->flags & 0x20000) return;
    work->state = s19b_jeep_mrl_800D4660;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s19b_jeep_mrl_800D4660(Work *work, int time)
{
    if (time == 0)
    {
        work->action = 3;
        GM_ConfigObjectAction(&work->body, 3, 0, 4);
    }
    if (s19b_jeep_mrl_800D4188(work) != 0) return;
    if (work->body.is_end == 0) return;
    work->state = s19b_jeep_mrl_800D424C;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}
void s19b_jeep_mrl_800D46D4(Work *work, int time)
{
    if (time == 0)
    {
        work->action = 0xD;
        GM_ConfigObjectAction(&work->body, 0xD, 0, 4);
        GM_SeSet(&work->control.mov, work->se[0]);
    }
    if (work->body.is_end == 0) return;
    work->state = s19b_jeep_mrl_800D424C;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}
void s19b_jeep_mrl_800D4744(Work *work)
{
    MrlStateFunc fn;
    int          old = work->time;

    work->time = old + 1;
    fn = work->state;
    if (fn == 0)
    {
        fn = s19b_jeep_mrl_800D424C;
        work->state = fn;
        work->action = 0;
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }
    fn(work, old);
}

void s19b_jeep_mrl_800D47B8(Work *work)
{
    work->flags = Takabe_JeepSystem.mrl_flags;
    Takabe_JeepSystem.mrl_flags &= 0xFFFF0000;
    s19b_jeep_mrl_800D4744(work);
}
