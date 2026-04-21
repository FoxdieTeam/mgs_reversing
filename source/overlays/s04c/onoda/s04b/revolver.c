#include "common.h"
#include "linkvar.h"
#include "strcode.h"
#include "anime/animconv/anime.h"
#include "chara/snake/sna_init.h"
#include "chara/snake/shadow.h"
#include "game/game.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "menu/menuman.h"
#include "okajima/blood.h"
#include "takabe/revbullt.h"
#include "takabe/thing.h"

#define EXEC_LEVEL      5

#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )
#define BODY_MODEL      GV_StrCode("rev_gun")
#define MOTION_DATA     GV_StrCode("revolver")
#define TARGET_FLAG     ( TARGET_SEEK | TARGET_PUSH | TARGET_POWER )

#define REVJOINT_NUM    17

typedef struct
{
    int  state;
    int  time;
    int  field_8;
    int  field_C;
    char pad[0x8];
    int  field_18;
} STATE;

typedef struct
{
    SVECTOR field_940;
    int     field_948;
    int     field_94C;
    int     field_950;
} PARAM;

typedef struct _RevolverWork
{
    GV_ACT         actor;
    GV_PAD        *pad;
    CONTROL        control;
    OBJECT         body;
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT m_segs1[REVJOINT_NUM + 1];
    MOTION_SEGMENT m_segs2[REVJOINT_NUM + 1];
    SVECTOR        rots[REVJOINT_NUM];
    SVECTOR        adjust[REVJOINT_NUM];
    SVECTOR        field_7F4;
    MATRIX         light[2];
    TARGET        *target;
    HOMING        *hom;
    MENU_BAR_CONF  lifebar;
    int            life_rest;
    int            life_now;
    int            life_delay;
    DG_TEX        *field_85C; // maybe [3] array
    DG_TEX        *field_860;
    DG_TEX        *field_864;
    SVECTOR        field_868; // maybe pos
    int            field_870;
    int            field_874;
    int            field_878;
    int            field_87C;
    int            field_880;
    int            field_884;
    int            field_888;
    int            enable_shadow;
    int            field_890;
    int            field_894;
    int            field_898;
    int            field_89C;
    int            field_8A0;
    int            field_8A4;
    int            field_8A8;
    int            field_8AC;
    MATRIX         field_8B0;
    int            field_8D0;
    int            field_8D4;
    GV_ACT        *shadow;
    char           pad1[0x4];
    int            proc_id;
    char           pad2[0x8];
    int            field_8EC;
    int            field_8F0;
    char           pad3[0x4];
    int            field_8F8;
    STATE          state;
    char           pad4[0x4];
    SVECTOR        field_91C;
    int            field_924[4];
    SVECTOR        field_934;
    int            field_93C;
    PARAM          param;
    void          *field_954;
    void          *field_958;
    void          *field_95C;
    int            hp;
    int            field_964;
    int            field_968;
    int            field_96C;
    int            field_970;
    int            field_974;
} RevolverWork;

typedef struct _RevolverPrims
{
    DR_TPAGE tpage[2];
    SPRT     sprt[6];
} RevolverPrims;

extern CAMERA GM_CameraList[8];

SVECTOR revolver_target_size = {400, 900, 400};

extern char    s04c_dword_800C3468[]; // = "OCELOT"
extern short   s04c_dword_800C3470[][2];
extern SVECTOR s04c_dword_800C3490;
extern SVECTOR s04c_dword_800C3498[2];
extern MATRIX  s04c_dword_800C34A8;
extern SVECTOR s04c_dword_800C34C8;
extern SVECTOR s04c_dword_800C34D0;
extern short   s04c_dword_800C3518[];
extern short   s04c_dword_800C3528[];
extern short   s04c_dword_800C3538[];
extern short   s04c_dword_800C3548[];
extern short   s04c_dword_800C3558[];
extern short   s04c_dword_800C3568[];
extern short   s04c_dword_800C3578[];

typedef struct
{
    char action;
    char frame;
    char se_id;
    char pad;
} SOUNDTBL;

extern SOUNDTBL s04c_dword_800C3588[4];
extern SOUNDTBL s04c_dword_800C3598[4];

extern short  *s04c_dword_800DBE10;
extern void   *s04c_dword_800DBE14;
extern SVECTOR s04c_dword_800DBE18;
extern int     s04c_dword_800DBE20;

void NewAnime_8005E574(MATRIX *);
void *AN_Unknown_800CA1EC(MATRIX *mat, int mark);

void Voicesys_800CE2D0(void);
void Voicesys_800CE300(void);
void Voicesys_800CE310(void);
int  Voicesys_800CE694(void);
void Voicesys_800CE734(void);

static void DrawPrims(RevolverWork *work);

void s04c_revolver_800CF3DC(int id)
{
    if (GM_StreamStatus() != 2)
    {
        GM_SeSet2(0, 63, id);
    }
}

void s04c_revolver_800CF418(void)
{
    /* do nothing */
}

void s04c_revolver_800CF420(RevolverWork *work)
{
    if (work->body.action2 != 14)
    {
        work->field_888 = 1;

        // why?
        work->body.m_ctrl->info2.m_segs[1].base.vy += 2048;
        work->control.rot.vy += 2048;

        GM_ConfigObjectOverride(&work->body, 14, 0, 4, -1);
        work->body.m_ctrl->info2.action = 3;
        work->m_ctrl.info1.field_14 = 0;
    }
}

void s04c_revolver_800CF4A0(RevolverWork *work)
{
    int mask;

    if (work->field_890 != 0)
    {
        work->field_890 = 0;
        s04c_revolver_800CF420(work);
    }
    else if (work->field_888 == 0)
    {
        work->field_888 = 1;
        mask = work->field_880 ? 0x1F801 : -1;
        GM_ConfigObjectOverride(&work->body, 3, 0, 4, mask);
    }
}

void s04c_revolver_800CF518(RevolverWork *work)
{
    work->field_888 = 0;

    GM_ConfigObjectOverride(&work->body, 3, 0, 4, 0);
    work->m_ctrl.info2.field_14 = 0;

    if (work->field_880 == 0)
    {
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }
}

void s04c_revolver_800CF584(RevolverWork *work)
{
    if (work->body.action2 != 9)
    {
        GM_ConfigObjectOverride(&work->body, 9, 0, 4, -1);
    }

    work->m_ctrl.info1.field_14 = 0;
}

void s04c_revolver_800CF5D0(RevolverWork *work)
{
    if (work->field_888 != 0)
    {
        GM_ConfigObjectOverride(&work->body, 3, 0, 4, 0x1F801);
    }
    else
    {
        GM_ConfigObjectOverride(&work->body, 3, 0, 4, 0);
    }

    if (work->field_880 != 0)
    {
        work->m_ctrl.info1.field_14 = 1;
    }
    else
    {
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }
}

void s04c_revolver_800CF650(RevolverWork *work)
{
    if (work->body.action2 != 13)
    {
        GM_ConfigObjectOverride(&work->body, 13, 0, 4, -1);
    }

    work->m_ctrl.info1.field_14 = 0;
}

void s04c_revolver_800CF69C(RevolverWork *work)
{
    if (work->field_888 != 0)
    {
        GM_ConfigObjectOverride(&work->body, 3, 0, 4, 0x1F801);
    }
    else
    {
         GM_ConfigObjectOverride(&work->body, 3, 0, 4, 0);
    }

    if (work->field_880 != 0)
    {
        work->m_ctrl.info1.field_14 = 1;
    }
    else
    {
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }
}

void s04c_revolver_800CF71C(RevolverWork *work)
{
    GM_ConfigObjectAction(&work->body, 0, 0, 4);
}

void s04c_revolver_800CF748(RevolverWork *work)
{
    work->field_880 = 1;
    work->field_884 = 0;

    GM_ConfigObjectAction(&work->body, 8, 0, 4);

    if (work->field_888 != 0)
    {
        work->m_ctrl.info1.mask = 0x1F801;
        work->m_ctrl.info2.mask = ~0x1F801;
    }
}

void s04c_revolver_800CF7AC(RevolverWork *work)
{
    work->field_880 = 0;

    GM_ConfigObjectAction(&work->body, 0, 0, 4);

    if (work->field_888 != 0)
    {
        work->m_ctrl.info1.mask = -1;
        work->m_ctrl.info2.mask = 0;
    }
}

void s04c_revolver_800CF7FC(RevolverWork *work)
{
    int mov;

    sna_act_helper2_helper2_80033054(work->control.name, &work->field_7F4);
    work->adjust[1].vy = GV_NearExp4P(work->adjust[1].vy, work->field_8D0);

    mov = GV_NearExp4P(work->adjust[2].vx, work->field_8D4);
    work->adjust[2].vx = mov;
    work->adjust[7].vx = work->field_7F4.vx + mov;
    work->adjust[8].vx = mov;

    GM_ConfigMotionAdjust(&work->body, work->adjust);
}

void s04c_revolver_800CF868(RevolverWork* work, int unit, int count)
{
    MATRIX world;

    DG_SetPos(&work->body.objs->objs[unit].world);
    DG_MovePos(&s04c_dword_800C34C8);
    DG_RotatePos(&s04c_dword_800C34D0);
    ReadRotMatrix(&world);
    NewBlood(&world, count);
}

void s04c_revolver_800CF8D8(RevolverWork *work)
{
    TARGET *target;
    int     life;

    target = work->target;
    if (target->damaged & TARGET_POWER)
    {
        target->damaged &= ~TARGET_POWER;
        work->field_894 = 1;

        Voicesys_800CE300();

        switch (target->a_mode)
        {
        case 3:
            target->life--;
            GM_SeSet(&work->control.mov, 52);
            break;
        case 4:
            target->life -= 3;
            GM_SeSet(&work->control.mov, 53);
            break;
        case 2:
            if (target->weapon == WP_C4)
            {
                life = (work->life_now * work->hp) / 1024;
                life -= (life - target->life) * 2 / 3;
                target->life = life;
            }
            /* fallthrough */
        default:
            s04c_revolver_800CF868(work, 2, 0);
            break;
        }

        if ((GM_GameOverTimer != 0) && (work->target->life <= 0))
        {
            work->target->life = 1;
        }

        life = work->target->life;
        work->life_now = (life * 1024) / work->hp;
        if (life > 0)
        {
            s04c_revolver_800CF584(work);
            work->target->class &= ~(TARGET_POWER | TARGET_SEEK);
            GM_SeSet(NULL, 137);
        }
        else
        {
            work->state.state = 4;
            work->state.time = 0;
            s04c_revolver_800CF584(work);
            work->life_now = 0;
            GM_SeSet(NULL, 136);
        }

        work->field_868 = work->control.mov;
    }
}

int s04c_revolver_800CFAF0(RevolverWork *work, int turn)
{
    SVECTOR point[2];
    SVECTOR temp;
    MATRIX  world;
    int     len;
    int     len2;

    temp.vx = temp.vz = 0;
    temp.vy = turn;

    DG_SetPos2(&work->control.mov, &temp);
    ReadRotMatrix(&world);
    CompMatrix(&world, &s04c_dword_800C34A8, &world);

    DG_SetPos(&world);
    DG_PutVector(s04c_dword_800C3498, point, 2);

    HZD_LineCheck(work->control.map->hzd, &point[0], &point[1], 0xF, 0);
    HZD_LineNearVec(&point[1]);

    GV_SubVec3(&s04c_dword_800DBE18, &point[0], &temp);
    len = GV_VecLen3(&temp);

    GV_SubVec3(&point[1], &point[0], &point[0]);
    len2 = GV_VecLen3(&point[0]);

    return len <= len2;
}

int s04c_revolver_800CFBE0(int x, int z)
{
    int v0, v1;

    x += 2500;
    z -= 6000;

    v0 = abs(x) > abs(z);
    v1 = v0 ^ 1;

    if (x > 0)
    {
        if (z > 0)
        {
            return 1 - v1;
        }
        else
        {
            return 2 + v1;
        }
    }
    else
    {
        if (z > 0)
        {
            return 6 + v1;

        }
        else
        {
            return 5 - v1;
        }
    }
}

int s04c_revolver_800CFC3C(RevolverWork *work)
{
    return s04c_revolver_800CFBE0(GM_PlayerPosition.vx, GM_PlayerPosition.vz);
}

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFC6C.s")

void s04c_revolver_800CFD08(SVECTOR *arg0, int arg1)
{
    switch (arg1)
    {
    case 0:
        arg0->vx = -15000 - arg0->vx;
        break;
    case 1:
        arg0->vx = 5000 - arg0->vx;
        break;
    case 2:
        arg0->vz = 2000 - arg0->vz;
        break;
    case 3:
        arg0->vz = 22000 - arg0->vz;
        break;
    }
}

/* TODO: figure out what this struct is */
typedef struct _Unk
{
    SVECTOR vec;
    char    pad1[0x18];
    int     val;
} Unk;

int s04c_revolver_800CFD84(RevolverWork *work)
{
    Unk     *pos;
    SVECTOR *rot;
    int     *type;
    int      i;

    pos = (Unk *)&work->field_91C;
    rot = &work->field_934;
    type = work->field_924;

    work->field_91C = s04c_dword_800DBE18;

    for (i = pos->val; i > 0; i--)
    {
        s04c_revolver_800CFD08(&pos->vec, *type++);
    }

    GV_SubVec3(&pos->vec, &work->control.mov, rot);
    return ratan2(rot->vx, rot->vz) & 0xFFF;
}

int s04c_revolver_800CFE44(int arg0, int arg1)
{
    int side;
    int diff;

    side = (s04c_revolver_800CFBE0(GM_PlayerPosition.vx, GM_PlayerPosition.vz) - arg0) & 7;

    if ((side < 2) || (side > 5))
    {
        if (side < 4)
        {
            return (arg0 - 1) & 7;
        }
        else
        {
            return (arg0 + 1) & 7;
        }
    }
    else
    {
        diff = (arg1 - arg0) & 7;

        if (diff < 4)
        {
            return (arg0 + 1) & 7;
        }
        else
        {
            return (arg0 - 1) & 7;
        }
    }
}

int s04c_revolver_800CFED4(RevolverWork *work, int arg1)
{
    int      sector0;
    PARAM   *param;
    int      sector1;
    int      x, z;
    int      x2, z2;
    int      len, len2;
    CONTROL *control;
    int      ry;
    int      ty;
    int      diff;

    sector0 = work->field_8A0;
    if (sector0 == arg1)
    {
        return -1;
    }

    param = &work->param;
    param->field_950 = 0;
    param->field_94C = arg1;

    sector1 = s04c_revolver_800CFE44(sector0, arg1);
    if ((sector0 >> 1) != (sector1 >> 1))
    {
        param->field_948 = sector1;
    }
    else
    {
        x = s04c_dword_800C3470[sector0][0] - work->control.mov.vx;
        z = s04c_dword_800C3470[sector0][1] - work->control.mov.vz;
        work->control.turn.vy = ratan2(x, z) & 0xFFF;
        len = SquareRoot0(x * x + z * z);

        x2 = s04c_dword_800C3470[sector0][0] - work->control.mov.vx;
        z2 = s04c_dword_800C3470[sector0][1] - work->control.mov.vz;
        len2 = SquareRoot0(x2 * x2 + z2 * z2);

        if ((len < 1000) || (len2 < 1800))
        {
            param->field_948 = sector1;
        }
        else
        {
            param->field_948 = sector0;
        }
    }

    param->field_940.vx = s04c_dword_800C3470[param->field_948][0];
    param->field_940.vz = s04c_dword_800C3470[param->field_948][1];

    control = &work->control;

    control->turn.vy = ratan2(param->field_940.vx - control->mov.vx, param->field_940.vz - control->mov.vz) & 0xFFF;
    control->interp = 1;

    ry = control->rot.vy & 0xFFF;
    ty = control->turn.vy & 0xFFF;
    diff = ABS(ry - ty);
    diff -= 1536;

    if (diff > 0 && diff < 1024)
    {
        work->field_890 = 1;
    }

    return 0;
}

int s04c_revolver_800D00B4(RevolverWork *work)
{
    PARAM   *param;
    CONTROL *control;
    int      x, z;
    int      index;
    int      ry;
    int      ty;
    int      diff;

    if (work->enable_shadow != 0)
    {
        return -1;
    }

    param = &work->param;
    control = &work->control;

    x = param->field_940.vx - control->mov.vx;
    z = param->field_940.vz - control->mov.vz;

    if (SquareRoot0(x * x + z * z) < 300)
    {
        index = s04c_revolver_800CFBE0(GM_PlayerPosition.vx, GM_PlayerPosition.vz);
        param->field_94C = s04c_dword_800DBE10[index];

        index = param->field_948;
        if (param->field_94C == index)
        {
            work->field_868.vx = s04c_dword_800C3470[index][0];
            work->field_868.vz = s04c_dword_800C3470[index][1];
            return -1;
        }

        param->field_948 = index = s04c_revolver_800CFE44(index, param->field_94C);
        param->field_940.vx = s04c_dword_800C3470[index][0];
        param->field_940.vz = s04c_dword_800C3470[index][1];
        x = param->field_940.vx - control->mov.vx;
        z = param->field_940.vz - control->mov.vz;
    }

    control->turn.vy = ratan2(x, z) & 0xFFF;
    if (SquareRoot0(x * x + z * z) < 1000)
    {
        control->rot.vy = GV_NearExp2(control->rot.vy, control->turn.vy);
    }
    else
    {
        ry = control->rot.vy & 0xFFF;
        ty = control->turn.vy & 0xFFF;
        diff = ABS(ry - ty);
        diff -= 1536;

        if (diff > 0 && diff < 1024)
        {
            work->field_890 = 1;
            s04c_revolver_800CF4A0(work);
        }
    }


    if (work->field_880 == 0)
    {
        param->field_950++;
    }
    else
    {
        param->field_950 = 0;
    }

    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D02C8.s")
int s04c_revolver_800D02C8(RevolverWork *work, short *, short *);

int s04c_revolver_800D03C0(RevolverWork *work)
{
    return s04c_revolver_800D02C8(work, s04c_dword_800C3518, s04c_dword_800C3528);
}

int s04c_revolver_800D03EC(RevolverWork *work)
{
    return s04c_revolver_800D02C8(work, s04c_dword_800C3538, s04c_dword_800C3548);
}

int s04c_revolver_800D0418(RevolverWork *work)
{
    return s04c_revolver_800D02C8(work, s04c_dword_800C3558, s04c_dword_800C3568);
}

int s04c_revolver_800D0444(RevolverWork *work)
{
    int side;
    int shift;

    side = s04c_revolver_800CFBE0(work->control.mov.vx, work->control.mov.vz);
    shift = s04c_revolver_800CFBE0(GM_PlayerPosition.vx, GM_PlayerPosition.vz);

    if ((s04c_dword_800C3578[side] >> shift) & 1)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void s04c_revolver_800D04B8(STATE *state, int value)
{
    state->state = value;
    state->time = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D04C4.s")
void s04c_revolver_800D04C4(RevolverWork *work, STATE *state);

void s04c_revolver_800D07F4(RevolverWork *work, STATE *state)
{
    SVECTOR diff;
    int     len;
    int     dir;
    int     x, z;

    GV_SubVec3(&s04c_dword_800DBE18, &work->control.mov, &diff);
    len = GV_VecLen3(&diff);

    if (work->param.field_950 > 90)
    {
        work->field_898 = 1;
        work->field_868 = work->control.mov;
    }

    if (work->field_898 != 0)
    {
        dir = ratan2(diff.vx, diff.vz);
        if (s04c_revolver_800CFAF0(work, dir) && (work->field_874 > 0))
        {
            work->field_8A0 = work->param.field_94C;
            s04c_revolver_800CF518(work);
            work->enable_shadow = 0;
            work->field_93C = 0;
            work->field_934 = diff;
            s04c_revolver_800D04B8(state, 2);
            work->field_870 = 0;
            state->field_C = 0;
            work->control.turn.vy = dir;
            work->control.interp = 1;
            work->field_8D0 = 0;
            GM_ConfigObjectAction(&work->body, 6, 0, 4);
            state->field_18 = 1;

            x = work->field_934.vx;
            z = work->field_934.vz;
            work->field_8D4 = -ratan2(work->field_934.vy, SquareRoot0(x * x + z * z));
            return;
        }

        if (work->field_874 <= 0)
        {
            s04c_revolver_800D04B8(state, 3);
            s04c_revolver_800CF748(work);

            if (!s04c_revolver_800D0418(work))
            {
                s04c_revolver_800CF4A0(work);
            }

            if ((work->field_8EC == 0) && (work->field_8F0 < 3))
            {
                if (work->field_8F8 == 0)
                {
                    Voicesys_800CE2D0();
                    work->field_8F8 = 1;
                }
            }
            else
            {
                GV_RandU(32);
            }

            return;
        }

        if (!s04c_revolver_800D03C0(work))
        {
            s04c_revolver_800CF4A0(work);
        }
    }

    work->enable_shadow |= s04c_revolver_800D00B4(work);
    if (work->enable_shadow != 0)
    {
        if (len < 3000)
        {
            if (!s04c_revolver_800D03EC(work))
            {
                s04c_revolver_800CF4A0(work);
            }
        }
        else
        {
            s04c_revolver_800D04B8(state, 0);
            work->field_8A0 = work->param.field_94C;
            s04c_revolver_800CF518(work);
            work->enable_shadow = 0;
        }
    }
}

void s04c_revolver_800D0A94(RevolverWork* work, STATE *state)
{
    SVECTOR diff;
    MATRIX  world;
    int     len;
    int     dir;
    int     adjust;

    GV_SubVec3(&s04c_dword_800DBE18, &work->control.mov, &diff);

    len = SquareRoot0(diff.vx * diff.vx + diff.vz * diff.vz);
    dir = ratan2(diff.vx, diff.vz);

    if (work->field_898 != 0)
    {
        if ((len < 4000) || !s04c_revolver_800CFAF0(work, dir) || (work->field_874 <= 0))
        {
            if (!s04c_revolver_800D0418(work))
            {
                s04c_revolver_800CF4A0(work);
                s04c_revolver_800D04B8(state, 1);
            }
            else
            {
                s04c_revolver_800D04B8(state, 0);
                s04c_revolver_800CF71C(work);
                work->field_8D0 = 0;
                work->field_8D4 = 0;
            }

            return;
        }

        work->field_93C = 0;
        work->field_934 = diff;
        s04c_revolver_800D04B8(state, 2);
        work->field_870 = 0;
        state->field_C = 0;
        work->control.turn.vy = dir;
        work->control.interp = 1;
        work->field_8D0 = 0;
        GM_ConfigObjectAction(&work->body, 6, 0, 4);
        work->field_8D4 = -ratan2(work->field_934.vy, len);
    }

    work->field_870++;

    switch (state->time)
    {
    case 0:
        if (state->field_18 != 0)
        {
            work->control.turn.vy = ratan2(diff.vx, diff.vz);
        }

        if (work->field_870 == 10)
        {
            adjust = work->field_8D4;
            work->adjust[2].vx = adjust;
            work->adjust[7].vx = adjust;
            work->adjust[8].vx = adjust;
            work->adjust[1].vy = work->field_8D0;
            GM_ConfigObjectAction(&work->body, 6, 0, 1);
            state->time = 1;
        }
        break;
    case 1:
        work->field_874--;
        work->field_8B0 = work->body.objs->objs[5].world;
        DG_SetPos(&work->field_8B0);
        DG_MovePos(&s04c_dword_800C3490);
        ReadRotMatrix(&world);
        NewRevolverBullet(&world, work->field_93C);
        GM_SeSetPan(&work->control.mov, 178, 63);
        NewAnime_8005E574(&world);
        NewAnime_8005E6A4(&work->control.mov);
        work->field_87C = 1;
        state->time = 2;
        break;
    case 2:
        work->control.mov.vx = GV_NearExp8(work->control.mov.vx, work->field_868.vx);
        work->control.mov.vz = GV_NearExp8(work->control.mov.vz, work->field_868.vz);

        if (work->body.is_end)
        {
            if (state->field_18 == 0)
            {
                s04c_revolver_800D04B8(state, 0);
                s04c_revolver_800CF71C(work);
                work->field_8D0 = 0;
                work->field_8D4 = 0;
            }
            else
            {
                s04c_revolver_800D04B8(state, 1);

                if (!s04c_revolver_800D0418(work))
                {
                    s04c_revolver_800CF4A0(work);
                }

                state->field_18 = 0;
            }
        }
        break;
    }
}

void s04c_revolver_800D0DE0(RevolverWork *work, STATE *state)
{
    SVECTOR diff;
    int     frame;
    int     se_id;

    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &diff);

    if (work->field_898 != 0)
    {
        if (work->field_874 == 6)
        {
            s04c_revolver_800CF7AC(work);

            if (work->field_888 != 0)
            {
                work->enable_shadow |= s04c_revolver_800D00B4(work);
                if (work->enable_shadow == 0)
                {
                    s04c_revolver_800D04B8(state, 1);
                    return;
                }

                work->field_8A0 = work->param.field_94C;
                s04c_revolver_800CF518(work);
                work->enable_shadow = 0;
            }

            s04c_revolver_800D04B8(state, 0);
            return;
        }

        if (!s04c_revolver_800D0418(work))
        {
            s04c_revolver_800CF4A0(work);
        }
    }

    if (work->field_888 != 0)
    {
        work->enable_shadow |= s04c_revolver_800D00B4(work);
        if (work->enable_shadow != 0)
        {
            work->field_8A0 = work->param.field_94C;
            s04c_revolver_800CF518(work);
            work->enable_shadow = 0;
        }
    }
    else if ((GV_VecLen3(&diff) < work->field_968) && !s04c_revolver_800D0418(work))
    {
        AN_Unknown_800CA1EC(&work->body.objs->objs[6].world, 0);
        s04c_revolver_800CF4A0(work);
    }

    if (work->body.is_end)
    {
        s04c_revolver_800CF7AC(work);

        if (work->field_888 != 0)
        {
            work->enable_shadow |= s04c_revolver_800D00B4(work);
            if (work->enable_shadow == 0)
            {
                s04c_revolver_800D04B8(state, 1);
                return;
            }

            work->field_8A0 = work->param.field_94C;
            s04c_revolver_800CF518(work);
            work->enable_shadow = 0;
        }

        s04c_revolver_800D04B8(state, 0);
        return;
    }

    frame = work->m_ctrl.info1.frame;
    if (work->field_884 != frame)
    {
        if ((frame == 17) || (frame == 30) || (frame == 43) ||
            (frame == 56) || (frame == 69) || (frame == 82))
        {
            se_id = 181;
        }
        else if ((frame == 32) || (frame == 58) || (frame == 84))
        {
            se_id = 183;
        }

        else if ((frame == 120) || (frame == 134) || (frame == 148) ||
                 (frame == 162) || (frame == 176) || (frame == 190))
        {
            se_id = 179;
            work->field_878++;
        }
        else if ((frame == 123) || (frame == 165))
        {
            se_id = 133;
        }
        else if ((frame == 137) || (frame == 179))
        {
            se_id = 134;
        }
        else if ((frame == 151) || (frame == 193))
        {
            se_id = 135;
        }
        else if (frame == 208)
        {
            se_id = 177;
        }
        else if (frame == 230)
        {
            se_id = 180;
        }
        else
        {
            se_id = -1;
        }
    }
    else
    {
        se_id = -1;
    }

    work->field_884 = frame;

    if (se_id != -1)
    {
        GM_SeSet(&work->control.mov, se_id);
    }

    if (frame == 220)
    {
        if (work->field_8EC == 0)
        {
            if (work->field_8F8 == 1)
            {
                Voicesys_800CE2D0();
                work->field_8F8 = 0;
            }

            if (++work->field_8F0 == 3)
            {
                work->field_8EC = 1;
            }
        }

        work->field_874 = 6;
        work->field_878 = 0;
    }
}

void s04c_revolver_800D1120(RevolverWork *work, STATE *state)
{
    if (state->time == 0)
    {
        if (work->field_888 != 0)
        {
            s04c_revolver_800CF518(work);
        }

        s04c_revolver_800CF71C(work);

        if (work->proc_id != 0)
        {
            if (GM_GameOverTimer == 0)
            {
                GM_GameStatus &= ~STATE_SHOW_LIFEBAR;
                GCL_ExecProc(work->proc_id, NULL);
                work->proc_id = 0;
            }
        }

        state->time = 1;
    }
}

void s04c_revolver_800D11C8(RevolverWork *work, STATE *state)
{
    SVECTOR diff;

    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &diff);
    work->control.turn.vy = ratan2(diff.vx, diff.vz);

    if (work->field_898 != 0)
    {
        if (!s04c_revolver_800D0418(work))
        {
            s04c_revolver_800CF4A0(work);
            s04c_revolver_800D04B8(state, 1);
        }
        else
        {
            s04c_revolver_800D04B8(state, 0);
            s04c_revolver_800CF71C(work);
            work->field_8D0 = 0;
            work->field_8D4 = 0;
        }

        return;
    }

    if (work->field_888 == 0)
    {
        if (GV_VecLen3(&diff) < work->field_964)
        {
            if (s04c_revolver_800D03EC(work) == 0)
            {
                s04c_revolver_800CF4A0(work);
            }

            return;
        }
    }
    else
    {
        work->enable_shadow |= s04c_revolver_800D00B4(work);

        if (work->enable_shadow != 0)
        {
            work->field_8A0 = work->param.field_94C;
            s04c_revolver_800CF518(work);
            work->enable_shadow = 0;
        }
    }

    if (Voicesys_800CE694() == 0)
    {
        if (work->field_888 != 0)
        {
            s04c_revolver_800D04B8(state, 1);
        }
        else
        {
            s04c_revolver_800D04B8(state, 0);
        }
    }
}

void s04c_revolver_800D1318(RevolverWork *work, STATE *state)
{
    if (++state->time > 50)
    {
        Voicesys_800CE2D0();
        s04c_revolver_800D04B8(&work->state, 0);
    }
}

int s04c_revolver_800D1364(RevolverWork *work)
{
    s04c_revolver_800CF8D8(work);

    if (work->field_894 != 0)
    {
        if (work->body.time2 != 0)
        {
            work->field_8AC = 30;
            work->field_894 = 0;
            work->field_898 = 1;
            s04c_revolver_800CF5D0(work);
            work->target->class &= ~( TARGET_POWER | TARGET_SEEK );
        }

        if ((work->field_89C != 0) && (--work->field_89C == 0))
        {
            work->field_898 = 1;
        }
    }
    else if (work->field_89C != 0)
    {
        s04c_revolver_800CF650(work);

        if (--work->field_89C == 0)
        {
            s04c_revolver_800CF69C(work);
            work->field_898 = 1;
        }
    }

    if (GM_GameStatus & STATE_STUN)
    {
        work->field_89C = 60;
        s04c_revolver_800CF3DC(138);
        work->field_868 = work->control.mov;
    }

    if ((work->field_89C != 0) || (work->field_894 != 0))
    {
        return -1;
    }

    return 0;
}

int s04c_revolver_800D149C(RevolverWork *work)
{
    STATE *state;

    state = &work->state;

    if (s04c_revolver_800D1364(work))
    {
        return 0;
    }

    switch (state->state)
    {
    case 0:
        s04c_revolver_800D04C4(work, state);
        break;
    case 1:
        s04c_revolver_800D07F4(work, state);
        break;
    case 2:
        s04c_revolver_800D0A94(work, state);
        break;
    case 3:
        s04c_revolver_800D0DE0(work, state);
        break;
    case 4:
        s04c_revolver_800D1120(work, state);
        break;
    case 5:
        s04c_revolver_800D11C8(work, state);
        break;
    case 6:
        s04c_revolver_800D1318(work, state);
        break;
    }

    return 0;
}

void s04c_revolver_800D158C(RevolverWork *work)
{
    s04c_revolver_800D149C(work);

    work->field_898 = 0;

    if (GM_GameOverTimer < 0)
    {
        Voicesys_800CE310();
        Voicesys_800CE734();
    }
}

void s04c_revolver_800D15D4(RevolverWork *work)
{
    if (work->field_8AC > 1)
    {
        if ((--work->field_8AC & 3) != 0)
        {
            DG_VisibleObjs(work->body.objs);
        }
        else
        {
            DG_InvisibleObjs(work->body.objs);
        }
    }
    else if (work->field_8AC == 1)
    {
        work->field_8AC = 0;
        work->target->class |= TARGET_FLAG;
    }

    if (GM_GameOverTimer != 0)
    {
        work->target->class &= ~( TARGET_POWER | TARGET_SEEK );
    }
}

void s04c_revolver_800D168C(RevolverWork* work)
{
    MATRIX  mat;
    SVECTOR pos;

    if (work->field_87C != 0)
    {
        if (work->field_87C < 10)
        {
            work->field_8B0 = work->body.objs->objs[5].world;
            DG_SetPos(&work->field_8B0);
            DG_MovePos(&s04c_dword_800C3490);
            ReadRotMatrix(&mat);

            pos.vx = mat.t[0];
            pos.vy = mat.t[1];
            pos.vz = mat.t[2];

            NewAnime_8005E6A4(&pos);
            work->field_87C++;
        }
        else
        {
            work->field_87C = 0;
        }
    }
}

void s04c_revolver_800D1760(RevolverWork *work)
{
    int action;
    int frame;
    int i;

    action = -1;
    if (work->body.m_ctrl->info2.mask != -1)
    {
        action = work->body.action2;
    }

    frame = work->body.m_ctrl->info2.frame;

    if (work->control.nearvecs[0].pad == 2)
    {
        for (i = 0; i < 4; i++)
        {
            if ((action == s04c_dword_800C3588[i].action) && (frame == s04c_dword_800C3588[i].frame))
            {
                GM_SeSetMode(&work->control.mov, s04c_dword_800C3588[i].se_id, 1);
                break;
            }
        }
    }
    else
    {
        for (i = 0; i < 4; i++)
        {
            if ((action == s04c_dword_800C3598[i].action) && (frame == s04c_dword_800C3598[i].frame))
            {
                GM_SeSet(&work->control.mov, s04c_dword_800C3598[i].se_id);
                break;
            }
        }
    }
}

static void Act(RevolverWork *work)
{
    int diff;
    int sector;

    s04c_dword_800DBE18.vx = GM_PlayerPosition.vx;
    s04c_dword_800DBE18.vz = GM_PlayerPosition.vz;

    s04c_dword_800DBE18.vy = GM_PlayerControl->mov.vy;

    if (work->body.action2 == 14)
    {
        if (work->m_ctrl.info2.frame == 0)
        {
            work->rots[0].vy += 2048;
            work->m_ctrl.waist_rot.vy += 2048;
        }

        if (work->body.time2 != 0)
        {
            if (work->field_888 != 0)
            {
                work->body.action2 = 3;
                work->body.m_ctrl->interp = 4;

                if (work->field_880 != 0)
                {
                    work->m_ctrl.info1.mask = 0x1F801;
                    work->m_ctrl.info2.mask = ~0x1F801;
                    work->m_ctrl.info1.field_14 = 1;
                }
            }
            else
            {
                work->body.action2 = 0;
            }
        }
    }

    GM_ActMotion(&work->body);

    work->control.step.vy = -32;
    work->control.height = work->body.height;

    if ((work->body.action2 == 3) && (work->field_888 != 0))
    {
        diff = (GM_DifficultyFlag >= 0) ? GM_DifficultyFlag : 0;
        work->control.step.vx = (work->control.step.vx * (diff * 40 + 256)) / 256;
        work->control.step.vz = (work->control.step.vz * (diff * 40 + 256)) / 256;
    }

    GM_ActControl(&work->control);

    sector = s04c_revolver_800CFBE0(work->control.mov.vx, work->control.mov.vz);
    if ((sector == 0) || (sector == 7))
    {
        if (work->control.mov.vz < 8800)
        {
            work->control.mov.vz = 8800;
        }
    }

    if ((sector == 3) || (sector == 4))
    {
        if (work->control.mov.vz > 3200)
        {
            work->control.mov.vz = 3200;
        }
    }

    if ((sector == 1) || (sector == 2))
    {
        if (work->control.mov.vx < 300)
        {
            work->control.mov.vx = 300;
        }
    }

    if ((sector == 5) || (sector == 6))
    {
        if (work->control.mov.vx > -5300)
        {
            work->control.mov.vx = -5300;
        }
    }

    GM_ActObject(&work->body);

    DG_GetLightMatrix2(&work->control.mov, work->light);

    GM_MoveTarget(work->target, &work->control.mov);
    GM_PushTarget(work->target);

    s04c_revolver_800D158C(work);
    s04c_revolver_800CF7FC(work);
    s04c_revolver_800D15D4(work);

    MENU_DrawBar2(28, work->life_rest, work->life_now, 1024, &work->lifebar);

    if (work->life_now == work->life_rest)
    {
        work->life_delay = 10;
    }
    else if (--work->life_delay < 0)
    {
        work->life_rest = GV_NearSpeed(work->life_rest, work->life_now, 64);
    }

    DrawPrims(work);

    if ((GM_PlayerPosition.vx > -6000) && (GM_PlayerPosition.vx < 1000) && (GM_PlayerPosition.vz > 2500))
    {
        if (GM_PlayerPosition.vz < 9500)
        {
            if (work->control.mov.vx > -2500)
            {
                GM_CameraList[3].trg[0] = work->control.mov.vx - 1000;
            }
            else
            {
                GM_CameraList[3].trg[0] = work->control.mov.vx + 1000;
            }

            if (work->control.mov.vz > 6000)
            {
                GM_CameraList[3].trg[2] = work->control.mov.vz - 1000;
            }
            else
            {
                GM_CameraList[3].trg[2] = work->control.mov.vz + 1000;
            }
        }
    }

    s04c_revolver_800D168C(work);
    s04c_revolver_800D1760(work);
}

static void Die(RevolverWork *work)
{
    GM_GameStatus &= ~STATE_SHOW_LIFEBAR;

    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeTarget(work->target);
    GV_DestroyActor(work->shadow);

    GM_GameStatus &= ~STATE_SHOW_LIFEBAR;
}

static int InitTarget(RevolverWork *work)
{
    TARGET *target;

    target = GM_AllocTarget();
    work->target = target;
    if (target == NULL)
    {
        return -1;
    }

    GM_SetTarget(target, TARGET_FLAG, ENEMY_SIDE, &revolver_target_size);
    GM_Target_8002DCCC(target, 1, -1, 0, 0, &DG_ZeroVector);

    return 0;
}

static int GetResources(RevolverWork *work, int name, int where)
{
    SVECTOR        indices;
    CONTROL       *control;
    OBJECT        *body;
    HOMING        *hom;
    MENU_BAR_CONF *lifebar;

    control = &work->control;
    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));

    GM_ConfigControlHazard(control, work->control.mov.vy, -1, -1);
    GM_ConfigControlAttribute(control, 1);
    GM_ConfigControlInterp(control, 1);

    body = &work->body;
    GM_InitObject(body, BODY_MODEL, BODY_FLAG, MOTION_DATA);
    GM_ConfigObjectJoint(body);
    GM_ConfigMotionControl(body, &work->m_ctrl, MOTION_DATA, work->m_segs1, work->m_segs2, control, work->rots);
    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectAction(body, 1, 0, 0);

    work->field_954 = s04c_revolver_800CF418;
    work->field_958 = s04c_revolver_800CF418;
    work->field_95C = s04c_revolver_800CF418;

    hom = work->hom = GM_AllocHomingTarget(&work->body.objs->objs[0].world, control);
    hom->flag = 1;

    if (InitTarget(work) < 0)
    {
        return -1;
    }

    indices.vy = 7;
    indices.vx = 0;
    indices.vz = 13;
    indices.pad = 16;

    work->shadow = NewShadow(control, body, indices);
    if (!work->shadow)
    {
        return -1;
    }

    if (GCL_GetOption('e'))
    {
        work->proc_id = GCL_StrToInt(GCL_GetParamResult());
    }

    work->pad = GV_PadData;

    GM_ConfigObjectAction(body, 1, 0, 1);
    GM_ConfigObjectOverride(body, 8, 0, 0, 0);

    work->field_8A0 = 5;

    work->control.mov.vx = -5750;
    work->control.mov.vz = 3750;

    work->field_868 = work->control.mov;

    work->field_874 = 6;
    work->field_880 = 0;
    work->enable_shadow = 0;
    work->field_8A4 = 0;
    work->field_8A8 = 0;
    work->field_8AC = 0;
    work->field_87C = 0;

    lifebar = &work->lifebar;
    lifebar->name = s04c_dword_800C3468;
    lifebar->left[0] = 0x10;
    lifebar->left[1] = 0x6F;
    lifebar->left[2] = 0x9F;
    lifebar->right[0] = 0x1F;
    lifebar->right[1] = 0xDF;
    lifebar->right[2] = 0x7F;

    work->life_now = 1024;
    work->life_rest = 1024;

    work->field_85C = DG_GetTexture(PCX_TAMA_01);
    work->field_860 = DG_GetTexture(PCX_TAMA_02);
    work->field_864 = DG_GetTexture(PCX_TAMA_03);

    work->field_964 = 4000;
    work->field_8EC = 0;
    work->field_968 = 3000;

    GM_GameStatus |= STATE_SHOW_LIFEBAR;

    work->hp = THING_Gcl_GetIntDefault('h', 1024);
    work->field_96C = 30;
    work->field_970 = 30;
    work->field_974 = 180;

    work->target->life = work->hp;

    s04c_revolver_800D04B8(&work->state, 6);

    s04c_dword_800DBE14 = work;
    s04c_dword_800DBE20 = 0;

    return 0;
}

void *NewOcelotBoss(int name, int where)
{
    RevolverWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(RevolverWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "revolver.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}

static void DrawPrims(RevolverWork *work)
{
    int            x, y;
    DG_TEX        *tex1;
    int            start;
    DG_TEX        *tex2;
    MenuPrim      *prim;
    RevolverPrims *prims;
    SPRT          *sprt;
    int            i;

    x = 148;
    y = 28;

    tex1 = work->field_85C;

    if (work->field_874)
    {
        start = work->field_874;
        tex2 = work->field_864;
    }
    else
    {
        start = work->field_878;
        tex2 = work->field_860;
    }

    prim = MENU_GetPrimInfo();

    if (prim->next + sizeof(*prims) <= prim->end)
    {
        _NEW_PRIM(prims, prim);
    }
    else
    {
        prims = NULL;
    }

    if (prims)
    {
        sprt = prims->sprt;

        setDrawTPage(&prims->tpage[0], 0, 1, tex2->tpage);
        setDrawTPage(&prims->tpage[1], 0, 1, tex1->tpage);

        for (i = start; i > 0; i--)
        {
            setSprt(sprt);
            setRGB0(sprt, 128, 128, 128);
            setXY0(sprt, x, y);
            setWH(sprt, 6, 12);
            setUV0(sprt, tex2->off_x, tex2->off_y);
            sprt->clut = tex2->clut;

            x += 6;

            addPrim(prim->ot, sprt);
            sprt++;
        }

        addPrim(prim->ot, &prims->tpage[0]);

        for (i = start; i < 6; i++)
        {
            setSprt(sprt);
            setRGB0(sprt, 128, 128, 128);
            setXY0(sprt, x, y);
            setWH(sprt, 6, 12);
            setUV0(sprt, tex1->off_x, tex1->off_y);
            sprt->clut = tex1->clut;

            x += 6;

            addPrim(prim->ot, sprt);
            sprt++;
        }

        addPrim(prim->ot, &prims->tpage[1]);
    }
}
