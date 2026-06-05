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
    SVECTOR        rots[16];
    SVECTOR        adjust[16];
    MATRIX         light[2];

    char           pad1[0x8];

    OBJECT         weapon;

    char           pad2[0x44];

    TARGET        *target;

    char           pad3[0x28];

    int            hp;

    char           pad4[0x18];

    SVECTOR        pos;
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
        *(int *)((char *)work + 0x7FC) = 0;
        GM_ConfigObjectAction((OBJECT *)((char *)work + 0xA4), 0, 0, 4);
    }
    s19b_jeep_sne_800D4188(work);
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_sne_800D4290.s")
void s19b_jeep_sne_800D43AC(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        *(int *)((char *)work + 0x7FC) = 7;
        GM_ConfigObjectAction((OBJECT *)((char *)work + 0xA4), 7, 0, 4);
    }
    if (*(int *)((char *)work + 0x800) & 0x10000)
    {
        *(void **)((char *)work + 0x7EC) = (void *)s19b_jeep_sne_800D424C;
        *(int *)((char *)work + 0x7F4) = 0;
        *(short *)((char *)work + 0x78) = 0;
        *(short *)((char *)work + 0x74) = 0;
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
        *(int *)((char *)work + 0x7FC) = 7;
        GM_ConfigObjectAction((OBJECT *)((char *)work + 0xA4), 7, 0, 4);
    }
    if (s19b_jeep_sne_800D4188(work) != 0) return;
    if (*(short *)((char *)work + 0xBE) == 0) return;
    *(void **)((char *)work + 0x7EC) = (void *)s19b_jeep_sne_800D4488;
    *(int *)((char *)work + 0x7F4) = 0;
    *(short *)((char *)work + 0x78) = 0;
    *(short *)((char *)work + 0x74) = 0;
}

void s19b_jeep_sne_800D4488(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        *(int *)((char *)work + 0x7FC) = 8;
        GM_ConfigObjectAction((OBJECT *)((char *)work + 0xA4), 8, 0, 0);
    }
    if (s19b_jeep_sne_800D4188(work) != 0) return;
    if (*(int *)((char *)work + 0x800) & 0x20000) return;
    *(void **)((char *)work + 0x7EC) = (void *)s19b_jeep_sne_800D4500;
    *(int *)((char *)work + 0x7F4) = 0;
    *(short *)((char *)work + 0x78) = 0;
    *(short *)((char *)work + 0x74) = 0;
}

void s19b_jeep_sne_800D4500(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        *(int *)((char *)work + 0x7FC) = 9;
        GM_ConfigObjectAction((OBJECT *)((char *)work + 0xA4), 9, 0, 4);
    }
    if (s19b_jeep_sne_800D4188(work) != 0) return;
    if (*(short *)((char *)work + 0xBE) == 0) return;
    *(void **)((char *)work + 0x7EC) = (void *)s19b_jeep_sne_800D424C;
    *(int *)((char *)work + 0x7F4) = 0;
    *(short *)((char *)work + 0x78) = 0;
    *(short *)((char *)work + 0x74) = 0;
}

void s19b_jeep_sne_800D4574(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        *(int *)((char *)work + 0x7FC) = 1;
        GM_ConfigObjectAction((OBJECT *)((char *)work + 0xA4), 1, 0, 4);
    }
    if (s19b_jeep_sne_800D4188(work) != 0) return;
    if (*(short *)((char *)work + 0xBE) == 0) return;
    *(void **)((char *)work + 0x7EC) = (void *)s19b_jeep_sne_800D45E8;
    *(int *)((char *)work + 0x7F4) = 0;
    *(short *)((char *)work + 0x78) = 0;
    *(short *)((char *)work + 0x74) = 0;
}

void s19b_jeep_sne_800D45E8(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        *(int *)((char *)work + 0x7FC) = 2;
        GM_ConfigObjectAction((OBJECT *)((char *)work + 0xA4), 2, 0, 0);
    }
    if (s19b_jeep_sne_800D4188(work) != 0) return;
    if (*(int *)((char *)work + 0x800) & 0x20000) return;
    *(void **)((char *)work + 0x7EC) = (void *)s19b_jeep_sne_800D4660;
    *(int *)((char *)work + 0x7F4) = 0;
    *(short *)((char *)work + 0x78) = 0;
    *(short *)((char *)work + 0x74) = 0;
}

void s19b_jeep_sne_800D4660(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        *(int *)((char *)work + 0x7FC) = 3;
        GM_ConfigObjectAction((OBJECT *)((char *)work + 0xA4), 3, 0, 4);
    }
    if (s19b_jeep_sne_800D4188(work) != 0) return;
    if (*(short *)((char *)work + 0xBE) == 0) return;
    *(void **)((char *)work + 0x7EC) = (void *)s19b_jeep_sne_800D424C;
    *(int *)((char *)work + 0x7F4) = 0;
    *(short *)((char *)work + 0x78) = 0;
    *(short *)((char *)work + 0x74) = 0;
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_sne_800D46D4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_sne_800D4744.s")
extern void s19b_jeep_sne_800D4744(Work *work);

void s19b_jeep_sne_800D47B8(Work *work)
{
    *(int *)((char *)work + 0x800) = Takabe_JeepSystem.field_50;
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
    weapon = &work->weapon;

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
    GM_FreeObject(&work->weapon);
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
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp2_800D571C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp2_800D5820.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp2_800D5894.s")
extern void s19b_jlamp2_800D5894(void *work);
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp2_800D596C.s")
extern void s19b_jlamp2_800D596C(void *work);

void s19b_jlamp2_800D613C(void *work)
{
    s19b_jlamp2_800D596C(work);
    Takabe_JeepSystem.field_4C &= 0xFFFF0000;
    s19b_jlamp2_800D5894(work);
}
