#include "linkvar.h"
#include "game/game.h"

typedef struct _JEEP_SYSTEM
{
    char     pad1[0x4];
    CONTROL *control;
    char     pad2a[0x4C - 0x8];
    int      field_4C;
    int      field_50;
    char     pad2b[0x60 - 0x50 - sizeof(int)];
    OBJECT  *snake_body;
    char     pad3[0x78 - 0x60 - sizeof(OBJECT *)];
    int      field_78;
} JEEP_SYSTEM;

typedef struct _Work
{
    GV_ACT         actor;
    CONTROL       *root_ctrl;
    MATRIX        *root_mat;
    CONTROL        control;
    OBJECT         body;
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT m_segs1[16 + 1];
    MOTION_SEGMENT m_segs2[16 + 1];
    SVECTOR        rots[16];          /* 0x6A0 */
    SVECTOR        adjust[16];        /* 0x720 */
    MATRIX         light[2];          /* 0x7A0 */

    SVECTOR        field_7E0;         /* 0x7E0 */

    /* NewJeepSnake builds the weapon OBJECT here, while the per-frame state
       handlers reuse the same bytes as their state block. */
    union
    {
        OBJECT weapon;                /* 0x7E8 */
        struct
        {
            char  pad_7EC[0x7EC - 0x7E8];
            void *field_7EC;          /* 0x7EC: current state handler */
            char  pad_7F4[0x7F4 - 0x7EC - sizeof(void *)];
            int   field_7F4;          /* 0x7F4: frame counter */
            char  pad_7FC[0x7FC - 0x7F4 - sizeof(int)];
            int   field_7FC;          /* 0x7FC: action id */
            int   field_800;          /* 0x800: flags */
            char  pad_818[0x818 - 0x800 - sizeof(int)];
            short field_818;          /* 0x818 */
            char  pad_81C[0x81C - 0x818 - sizeof(short)];
            short field_81C;          /* 0x81C */
        } st;
    } u;

    char           pad2a[0x8E4 - 0x7E8 - sizeof(OBJECT)];
    MATRIX         field_8E4;         /* 0x8E4 */
    char           pad2b[0x908 - 0x8E4 - sizeof(MATRIX)];
    int            field_908;         /* 0x908 */
    char           pad_910[0x910 - 0x908 - sizeof(int)];

    TARGET        *target;            /* 0x910 */

    char           pad_918[0x918 - 0x910 - sizeof(TARGET *)];
    void          *field_918;         /* 0x918 */
    char           pad_920[0x920 - 0x918 - sizeof(void *)];
    int            field_920;         /* 0x920 */
    char           pad3a[0x928 - 0x920 - sizeof(int)];
    int            field_928;         /* 0x928 */
    int            field_92C;         /* 0x92C */
    char           pad3b[0x93C - 0x92C - sizeof(int)];

    int            hp;                /* 0x93C */

    int            field_940;         /* 0x940 */
    int            field_944;         /* 0x944 */
    char           pad_950[0x950 - 0x944 - sizeof(int)];
    int            field_950;         /* 0x950 */
    char           pad4[0x958 - 0x950 - sizeof(int)];

    SVECTOR        pos;               /* 0x958 */
} Work;

extern JEEP_SYSTEM Takabe_JeepSystem;

extern SVECTOR s19b_dword_800C39F8;

#define EXEC_LEVEL  GV_ACTOR_AFTER

#define MOTION_DATA GV_StrCode("sne_19b")
#define BODY_DATA   GV_StrCode("snake")
#define WEAPON_DATA GV_StrCode("jeep_gun")

#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND )
#define WEAPON_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

extern void s19b_jeep_sne_800D424C(Work *work, int arg1);
extern void s19b_jeep_sne_800D4290(Work *work, int arg1);
extern void s19b_jeep_sne_800D43AC(Work *work, int arg1);
extern void s19b_jeep_sne_800D4414(Work *work, int arg1);
extern void s19b_jeep_sne_800D4574(Work *work, int arg1);
extern void s19b_jeep_sne_800D46D4(Work *work, int arg1);

int s19b_jeep_sne_800D4188(Work *work)
{
    int flags = work->u.st.field_800;

    if (flags & 2)
    {
        work->u.st.field_7EC = (void *)s19b_jeep_sne_800D46D4;
        work->u.st.field_7F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (flags & 1)
    {
        work->u.st.field_7EC = (void *)s19b_jeep_sne_800D424C;
        work->u.st.field_7F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (flags & 0x20)
    {
        work->u.st.field_7EC = (void *)s19b_jeep_sne_800D4414;
        work->u.st.field_7F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (flags & 0x200)
    {
        work->u.st.field_7EC = (void *)s19b_jeep_sne_800D4574;
        work->u.st.field_7F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (flags & 0x1000)
    {
        work->u.st.field_7EC = (void *)s19b_jeep_sne_800D43AC;
        work->u.st.field_7F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if ((flags & 0x10000) == 0)
    {
        work->u.st.field_7EC = (void *)s19b_jeep_sne_800D4290;
        work->u.st.field_7F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    return 0;
}

void s19b_jeep_sne_800D424C(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->u.st.field_7FC = 0;
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }
    s19b_jeep_sne_800D4188(work);
}
void s19b_jeep_sne_800D4290(Work *work, int arg1)
{
    SVECTOR sp10;
    int     diff;

    if (arg1 == 0)
    {
        work->u.st.field_7FC = 0;
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }
    if ((Takabe_JeepSystem.field_4C & 1) && GV_RandU(0x100) < 0x14)
    {
        GM_SeSet(&work->control.mov, work->u.st.field_81C);
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
    /* 0x7E4 overlaps the field_7E0 SVECTOR (used by the jlamp2 actor) */
    *(int *)((char *)work + 0x7E4) = diff;

    if (work->u.st.field_800 & 0x10000)
    {
        *(int *)((char *)work + 0x7E4) = 0;
        if (s19b_jeep_sne_800D4188(work) == 0)
        {
            work->u.st.field_7EC = (void *)s19b_jeep_sne_800D424C;
            work->u.st.field_7F4 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
    }
}
void s19b_jeep_sne_800D43AC(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->u.st.field_7FC = 7;
        GM_ConfigObjectAction(&work->body, 7, 0, 4);
    }
    if (work->u.st.field_800 & 0x10000)
    {
        work->u.st.field_7EC = (void *)s19b_jeep_sne_800D424C;
        work->u.st.field_7F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
extern void s19b_jeep_sne_800D4488(Work *work, int arg1);
extern void s19b_jeep_sne_800D4500(Work *work, int arg1);
extern void s19b_jeep_sne_800D45E8(Work *work, int arg1);
extern void s19b_jeep_sne_800D4660(Work *work, int arg1);

void s19b_jeep_sne_800D4414(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->u.st.field_7FC = 7;
        GM_ConfigObjectAction(&work->body, 7, 0, 4);
    }
    if (s19b_jeep_sne_800D4188(work) != 0) return;
    if (work->body.is_end == 0) return;
    work->u.st.field_7EC = (void *)s19b_jeep_sne_800D4488;
    work->u.st.field_7F4 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s19b_jeep_sne_800D4488(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->u.st.field_7FC = 8;
        GM_ConfigObjectAction(&work->body, 8, 0, 0);
    }
    if (s19b_jeep_sne_800D4188(work) != 0) return;
    if (work->u.st.field_800 & 0x20000) return;
    work->u.st.field_7EC = (void *)s19b_jeep_sne_800D4500;
    work->u.st.field_7F4 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s19b_jeep_sne_800D4500(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->u.st.field_7FC = 9;
        GM_ConfigObjectAction(&work->body, 9, 0, 4);
    }
    if (s19b_jeep_sne_800D4188(work) != 0) return;
    if (work->body.is_end == 0) return;
    work->u.st.field_7EC = (void *)s19b_jeep_sne_800D424C;
    work->u.st.field_7F4 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s19b_jeep_sne_800D4574(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->u.st.field_7FC = 1;
        GM_ConfigObjectAction(&work->body, 1, 0, 4);
    }
    if (s19b_jeep_sne_800D4188(work) != 0) return;
    if (work->body.is_end == 0) return;
    work->u.st.field_7EC = (void *)s19b_jeep_sne_800D45E8;
    work->u.st.field_7F4 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s19b_jeep_sne_800D45E8(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->u.st.field_7FC = 2;
        GM_ConfigObjectAction(&work->body, 2, 0, 0);
    }
    if (s19b_jeep_sne_800D4188(work) != 0) return;
    if (work->u.st.field_800 & 0x20000) return;
    work->u.st.field_7EC = (void *)s19b_jeep_sne_800D4660;
    work->u.st.field_7F4 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s19b_jeep_sne_800D4660(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->u.st.field_7FC = 3;
        GM_ConfigObjectAction(&work->body, 3, 0, 4);
    }
    if (s19b_jeep_sne_800D4188(work) != 0) return;
    if (work->body.is_end == 0) return;
    work->u.st.field_7EC = (void *)s19b_jeep_sne_800D424C;
    work->u.st.field_7F4 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}
void s19b_jeep_sne_800D46D4(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->u.st.field_7FC = 0xD;
        GM_ConfigObjectAction(&work->body, 0xD, 0, 4);
        GM_SeSet(&work->control.mov, work->u.st.field_818);
    }
    if (work->body.is_end == 0) return;
    work->u.st.field_7EC = (void *)s19b_jeep_sne_800D424C;
    work->u.st.field_7F4 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}
void s19b_jeep_sne_800D4744(Work *work)
{
    void (*fn)(Work *, int);
    int   old = work->u.st.field_7F4;

    work->u.st.field_7F4 = old + 1;
    fn = (void (*)(Work *, int))work->u.st.field_7EC;
    if (fn == 0)
    {
        fn = s19b_jeep_sne_800D424C;
        work->u.st.field_7EC = (void *)fn;
        work->u.st.field_7FC = 0;
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }
    fn(work, old);
}

void s19b_jeep_sne_800D47B8(Work *work)
{
    work->u.st.field_800 = Takabe_JeepSystem.field_50;
    Takabe_JeepSystem.field_50 &= 0xFFFF0000;
    s19b_jeep_sne_800D4744(work);
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_sne_800D47F8.s")
void s19b_jeep_sne_800D47F8(Work *);

void s19b_jeep_sne_800D4CA0(Work *work)
{
    TARGET *target;
    int     hp;

    target = work->target;
    hp = GM_SnakeCurrentHealth;

    GM_SetTarget(target, ( TARGET_POWER | TARGET_SEEK ), PLAYER_SIDE, &s19b_dword_800C39F8);
    GM_SetPowerTarget(target, POWER_DECREASE, -1, hp, 0, &DG_ZeroVector);
    target->map = work->root_ctrl->map->index;
}

int s19b_jeep_sne_800D4D34(Work *work, int name)
{
    CONTROL *control;
    OBJECT  *body;
    OBJECT  *weapon;

    control = &work->control;
    if (GM_InitControl(control, name, work->root_ctrl->map->index) < 0)
    {
        return -1;
    }

    work->control.mov = work->root_ctrl->mov;
    work->control.rot = work->root_ctrl->rot;

    GM_ConfigControlInterp(control, 4);
    GM_ConfigControlHazard(control, 750, 450, 450);
    GM_ConfigControlAttribute(control, RADAR_VISIBLE);

    GM_PlayerStatus = 0;

    body = &work->body;
    weapon = &work->u.weapon;

    GM_InitObject(body, BODY_DATA, BODY_FLAG, MOTION_DATA);
    GM_ConfigMotionControl(body, &work->m_ctrl, MOTION_DATA, work->m_segs1, work->m_segs2, control, work->rots);

    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectAction(body, 0, 0, 0);
    GM_ConfigMotionAdjust(body, work->adjust);

    GM_InitObject(weapon, WEAPON_DATA, WEAPON_FLAG, 0);
    GM_ConfigObjectLight(weapon, work->light);

    work->target = GM_AllocTarget();

    s19b_jeep_sne_800D4CA0(work);

    control->r_sphere = -2;

    GM_PlayerBody = body;
    GM_PlayerControl = control;

    work->hp = GM_SnakeCurrentHealth;

    Takabe_JeepSystem.snake_body = body;
    work->pos = Takabe_JeepSystem.control->mov;
    return 0;
}

void s19b_jeep_sne_800D4F5C(Work *work)
{
    GM_FreeTarget(work->target);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->u.weapon);
    GM_FreeObject(&work->body);
    GM_PlayerControl = NULL;
    GM_PlayerBody = NULL;
}

void *NewJeepSnake(CONTROL *root_ctrl, MATRIX *root_mat)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jeep_sne_800D47F8, s19b_jeep_sne_800D4F5C, "jeep_sne.c");

        work->root_ctrl = root_ctrl;
        work->root_mat = root_mat;

        if (s19b_jeep_sne_800D4D34(work, GV_StrCode("スネーク")) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}

// new file

extern void DG_SetPos(MATRIX *);
extern void NewBlood(MATRIX *, int);
extern void *NewJeepBlood(MATRIX *, int, DG_OBJ *);
extern SVECTOR s19b_dword_800C3A28;
extern SVECTOR s19b_dword_800C3A30;

void s19b_jlamp2_800D5054(Work *work, int model, int arg2)
{
    MATRIX  mtx;
    DG_OBJ *obj = &work->body.objs->objs[model];

    DG_SetPos(&obj->world);
    DG_MovePos(&s19b_dword_800C3A28);
    DG_RotatePos(&s19b_dword_800C3A30);
    ReadRotMatrix(&mtx);
    if (Takabe_JeepSystem.field_78 == 0)
    {
        NewBlood(&mtx, arg2);
    }
    else
    {
        NewJeepBlood(&mtx, arg2, obj);
    }
}
void s19b_jlamp2_800D5484(Work *work, int arg1);
extern void *NewPadVibration(unsigned char *, int);
extern int s19b_dword_800C3A14;
extern int s19b_dword_800C3A18;

int s19b_jlamp2_800D50F4(Work *work)
{
    TARGET *target = work->target;

    if (target->damaged & TARGET_POWER)
    {
        target->force = DG_ZeroVector;
        work->field_918 = (void *)s19b_jlamp2_800D5484;
        work->field_920 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        target->damage = 0;
        target->damaged = 0;
        NewPadVibration((unsigned char *)&s19b_dword_800C3A14, 1);
        NewPadVibration((unsigned char *)&s19b_dword_800C3A18, 2);
        return 1;
    }
    return 0;
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp2_800D519C.s")
extern void *NewJeepBullet(MATRIX *world, int side, int mode, int mode2);
extern void NewAnime_8005D604(MATRIX *world);
extern void s19b_jblood_800C8070(MATRIX *world);
extern SVECTOR s19b_dword_800C3A40;
extern SVECTOR s19b_dword_800C3A38;

void s19b_jlamp2_800D5260(Work *work)
{
    MATRIX  mtx;
    SVECTOR svec;
    long    flag;

    RotMatrix(&s19b_dword_800C3A40, &mtx);
    MulMatrix0(&work->field_8E4, &mtx, &mtx);
    DG_SetPos(&work->field_8E4);
    RotTrans(&s19b_dword_800C3A38, (VECTOR *)mtx.t, &flag);
    NewJeepBullet(&mtx, 1, 1, 0);
    svec.vx = *(short *)&mtx.t[0];
    svec.vy = *(short *)&mtx.t[1];
    svec.vz = *(short *)&mtx.t[2];
    if (Takabe_JeepSystem.field_78 == 0)
    {
        GM_SeSet(&svec, 0x2E);
        NewAnime_8005D604(&mtx);
    }
    else
    {
        GM_SeSet(&svec, 0x2E);
        s19b_jblood_800C8070(&mtx);
    }
}
extern int  s19b_jlamp2_800D519C(Work *work);
extern int  s19b_dword_800C3A00;

void s19b_jlamp2_800D5328(Work *work, int arg1)
{
    int flags = work->field_92C;

    if (s19b_jlamp2_800D519C(work) != 0)
    {
        return;
    }
    if (flags & 1)
    {
        s19b_jlamp2_800D5260(work);
    }
    if (arg1 == 0)
    {
        if (work->field_928 != 0)
        {
            *(int *)((char *)&work->field_928) = 0;
            GM_ConfigObjectAction(&work->body, *(short *)&s19b_dword_800C3A00, 0, 4);
            work->field_7E0 = DG_ZeroVector;
        }
    }
    if (flags & 2)
    {
        if (work->field_928 != 2)
        {
            *(int *)((char *)&work->field_928) = 2;
            GM_ConfigObjectAction(&work->body, *(short *)((char *)&s19b_dword_800C3A00 + 4), 0, 4);
            work->field_7E0 = DG_ZeroVector;
        }
    }
    else if (flags & 4)
    {
        if (work->field_928 != 3)
        {
            *(int *)((char *)&work->field_928) = 3;
            GM_ConfigObjectAction(&work->body, *(short *)((char *)&s19b_dword_800C3A00 + 6), 0, 4);
            work->field_7E0 = DG_ZeroVector;
        }
    }
    else
    {
        if (work->field_928 != 0)
        {
            *(int *)((char *)&work->field_928) = 0;
            GM_ConfigObjectAction(&work->body, *(short *)&s19b_dword_800C3A00, 0, 4);
            work->field_7E0 = DG_ZeroVector;
        }
    }
}
extern void s19b_jlamp2_800D5054(Work *work, int arg1, int arg2);
extern void s19b_jlamp2_800D5328(Work *work, int arg1);
extern void s19b_jlamp2_800D571C(Work *work, int arg1);
extern int  s19b_dword_800C3A00;

void s19b_jlamp2_800D5484(Work *work, int arg1)
{
    work->field_944 = 4;
    if (arg1 == 0)
    {
        work->field_940 = 1;
        if (work->field_928 != 1)
        {
            *(int *)((char *)&work->field_928) = 1;
            GM_ConfigObjectAction(&work->body, *(short *)((char *)&s19b_dword_800C3A00 + 2), 0, 4);
            work->field_7E0 = DG_ZeroVector;
        }
        s19b_jlamp2_800D5054(work, 5, 0);
        Takabe_JeepSystem.field_4C |= 1;
        if (linkvarbuf[0xB] > 0)
        {
            GM_SeSet(&work->control.mov, 0x88);
        }
    }
    if (work->body.is_end != 0)
    {
        if (work->field_950 == 0)
        {
            work->field_918 = (void *)s19b_jlamp2_800D5328;
            work->field_920 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            if (work->field_928 != 0)
            {
                *(int *)((char *)&work->field_928) = 0;
                GM_ConfigObjectAction(&work->body, *(short *)&s19b_dword_800C3A00, 0, 4);
                work->field_7E0 = DG_ZeroVector;
            }
            work->field_940 = 0;
            work->field_944 = 0x2D;
        }
        else
        {
            work->field_918 = (void *)s19b_jlamp2_800D571C;
            work->field_920 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
    }
}
extern int  s19b_jlamp2_800D50F4(Work *work);
extern int  GV_RandS(int);
extern int  s19b_dword_800C3A10;

void s19b_jlamp2_800D55E8(Work *work, int arg1)
{
    if (s19b_jlamp2_800D50F4(work) != 0)
    {
        work->target->class = 1;
        work->field_944 = 4;
        work->field_908 += GV_RandS(0x200);
        return;
    }
    if (arg1 == 0)
    {
        if (work->field_928 != 8)
        {
            *(int *)((char *)&work->field_928) = 8;
            GM_ConfigObjectAction(&work->body, *(short *)&s19b_dword_800C3A10, 0, 4);
            work->field_7E0 = DG_ZeroVector;
        }
        GM_SeSet(&work->control.mov, 0x88);
    }
    if (arg1 >= 0x15)
    {
        work->field_918 = (void *)s19b_jlamp2_800D5328;
        work->field_920 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        if (work->field_928 != 0)
        {
            *(int *)((char *)&work->field_928) = 0;
            GM_ConfigObjectAction(&work->body, *(short *)&s19b_dword_800C3A00, 0, 4);
            work->field_7E0 = DG_ZeroVector;
        }
    }
}
extern void s19b_jlamp2_800D5820(Work *work, int arg1);
extern void Voicesys_800CE310(void);
extern void Voicesys_800CE5F8(int, int);
extern void Voicesys_800CE734(void);
extern void *NewPadVibration(unsigned char *, int);
extern int  GM_GameOverTimer;
extern int  s19b_dword_800C3A08;
extern int  s19b_dword_800C3A20;
extern int  s19b_dword_800C3A24;

void s19b_jlamp2_800D571C(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        if (work->field_928 != 4)
        {
            *(int *)((char *)&work->field_928) = 4;
            GM_ConfigObjectAction(&work->body, *(short *)&s19b_dword_800C3A08, 0, 4);
            work->field_7E0 = DG_ZeroVector;
        }
        Voicesys_800CE310();
        Voicesys_800CE5F8(0xF, 1);
        Voicesys_800CE734();
    }
    if (arg1 == 0x3D)
    {
        NewPadVibration((unsigned char *)&s19b_dword_800C3A20, 1);
        NewPadVibration((unsigned char *)&s19b_dword_800C3A24, 2);
        GM_SeSetMode(&work->control.mov, 0x33, 1);
    }
    if (work->body.is_end != 0)
    {
        GM_GameOverTimer = 1;
        work->field_918 = (void *)s19b_jlamp2_800D5820;
        work->field_920 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
extern int s19b_dword_800C3A00;
extern int s19b_dword_800C3A08;

void s19b_jlamp2_800D5820(Work *work, int arg1)
{
    if (arg1 == 0 && work->field_928 != 5)
    {
        /* the char* launder keeps the store ahead of the call; a plain
           work->field_928 = 5 sinks it into the delay slot and diverges */
        *(int *)((char *)&work->field_928) = 5;
        GM_ConfigObjectAction(&work->body,
                              *(short *)((char *)&s19b_dword_800C3A08 + 2), 0, 4);
        work->field_7E0 = DG_ZeroVector;
    }
}
extern void s19b_jlamp2_800D5328(Work *work, int arg1);

void s19b_jlamp2_800D5894(Work *work)
{
    void (*fn)(Work *, int);
    int   old;

    work->target->class = 1;
    old = work->field_920;
    fn  = (void (*)(Work *, int))work->field_918;
    work->field_920 = old + 1;
    if (fn == 0)
    {
        fn = s19b_jlamp2_800D5328;
        work->field_918 = (void *)fn;
        if (work->field_928 != 0)
        {
            /* char* launder keeps the store ahead of the call (see 800D5820) */
            *(int *)((char *)&work->field_928) = 0;
            GM_ConfigObjectAction(&work->body, *(short *)&s19b_dword_800C3A00, 0, 4);
            work->field_7E0 = DG_ZeroVector;
        }
    }
    fn(work, old);
    if (GM_GameStatus & STATE_PADDEMO)
    {
        work->target->class = 1;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp2_800D596C.s")
extern void s19b_jlamp2_800D596C(void *work);

void s19b_jlamp2_800D613C(void *work)
{
    s19b_jlamp2_800D596C(work);
    Takabe_JeepSystem.field_4C &= 0xFFFF0000;
    s19b_jlamp2_800D5894(work);
}
