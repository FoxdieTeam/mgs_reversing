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

    char           pad2[0x910 - 0x7E8 - sizeof(OBJECT)];

    TARGET        *target;            /* 0x910 */

    char           pad_918[0x918 - 0x910 - sizeof(TARGET *)];
    void          *field_918;         /* 0x918 */
    char           pad_920[0x920 - 0x918 - sizeof(void *)];
    int            field_920;         /* 0x920 */
    char           pad3a[0x928 - 0x920 - sizeof(int)];
    int            field_928;         /* 0x928 */
    char           pad3b[0x93C - 0x928 - sizeof(int)];

    int            hp;                /* 0x93C */

    char           pad4[0x18];

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

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_sne_800D4188.s")
extern int s19b_jeep_sne_800D4188(Work *work);

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

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp2_800D5054.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp2_800D50F4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp2_800D519C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp2_800D5260.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp2_800D5328.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp2_800D5484.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp2_800D55E8.s")
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
    if (GM_GameStatus & 0x40000000)
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
