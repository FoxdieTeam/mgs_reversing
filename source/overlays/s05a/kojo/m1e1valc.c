#include <rand.h>
#include "game/game.h"
#include "linkvar.h"

typedef struct _Work Work;

typedef struct _M1e1
{
    char    pad_000[0x20];
    SVECTOR field_20;    /* 0x020 */
    char    pad_28[0xB0 - 0x28];
    int     field_B0;    /* 0x0B0 */
    int     field_B4;    /* 0x0B4 */
    int     field_B8;    /* 0x0B8 */
    char    pad_BC[0xDC - 0xBC];
    OBJECT  body;        /* 0x0DC */
    char    pad_1C0[0x744 - 0x1C0];
    int     field_744;   /* 0x744 */
    int     field_748;   /* 0x748 */
    char    pad_74C[0xD54 - 0x74C];
    int     field_D54;   /* 0xD54 */
    int     field_D58;   /* 0xD58 */
    char    pad_D5C[0xDB8 - 0xD5C];
    int     field_DB8;   /* 0xDB8 */
    char    pad_DBC[0xE60 - 0xDBC];
    int     field_E60;   /* 0xE60 */
    char    pad_E64[0xEBC - 0xE64];
    Work   *field_EBC;   /* 0xEBC */
    int     field_EC0;   /* 0xEC0 */
    int     field_EC4;   /* 0xEC4 */
    int     field_EC8;   /* 0xEC8 */
    int     field_ECC;   /* 0xECC */
    int     field_ED0;   /* 0xED0 */
    char    pad_ED4[0xF48 - 0xED4];
    int     field_F48;   /* 0xF48 */
} M1e1;

struct _Work
{
    GV_ACT  actor;       /* 0x000 */
    CONTROL control;     /* 0x020 */
    MATRIX  light[2];    /* 0x09C */
    OBJECT  body;        /* 0x0DC */
    char    pad_1C0[0x1E8 - 0x1C0];
    int     field_1E8;   /* 0x1E8 */
    M1e1   *field_1EC;   /* 0x1EC */
    char    pad_1F0[0x1F8 - 0x1F0];
    int     last_weapon; /* 0x1F8 */
    int     last_item;   /* 0x1FC */
    char    pad_200[0x214 - 0x200];
    int     field_214;   /* 0x214 */
    char    pad_218[0x220 - 0x218];
    int     field_220;   /* 0x220 */
    int     field_224;   /* 0x224 */
    char    pad_228[0x234 - 0x228];
    MOTION_CONTROL m_ctrl;        /* 0x234 */
    MOTION_SEGMENT m_segs1[17];   /* 0x284 */
    MOTION_SEGMENT m_segs2[17];   /* 0x4E8 */
    CONTROL        subcontrol;    /* 0x74C */
    SVECTOR        rots[16];      /* 0x7C8 */
};

extern int s05a_dword_800C3644;
extern int s05a_dword_800C3648;

const char s05a_dword_800E351C[] = "m1e1valc.c";
const char s05a_dword_800E3528[] = "valcan";
const char s05a_dword_800E3530[] = "tankman";

void  s05a_800DD6B8(Work *work);
void  s05a_800DDC14(Work *work);
Work *NewM1E1Vulcan(M1e1 *m1e1);

void s05a_800DD1C8(M1e1 *m1e1)
{
    SVECTOR pos;
    int     s1;

    if (m1e1->field_ED0 == 2)
    {
        pos = GM_PlayerPosition;
        s1 = 0x3F;
    }
    else
    {
        pos = m1e1->field_20;
        s1 = m1e1->field_E60;
    }

    if (s05a_dword_800C3648 <= 0 && m1e1->field_EBC == NULL)
    {
        if (m1e1->field_EC0 == 1)
        {
            if (m1e1->field_EC4 < 2)
            {
                s05a_dword_800C3644 = 0x32;
            }
            else
            {
                s05a_dword_800C3644 = 1;
            }
        }
        if (s05a_dword_800C3644 == 1)
        {
            if (m1e1->field_EC4 < 2 || !(rand() & 1))
            {
                m1e1->field_EBC = NewM1E1Vulcan(m1e1);
                GM_ConfigObjectAction(&m1e1->field_EBC->body, 2, 0, 5);
            }
            else
            {
                s05a_dword_800C3648 = m1e1->field_DB8 * 2 / 3;
                GM_SeSetPan(&pos, 0x85, s1);
            }
        }
    }

    if (--s05a_dword_800C3644 < 0)
    {
        s05a_dword_800C3644 = 0;
    }
    if (--s05a_dword_800C3648 < 0)
    {
        s05a_dword_800C3648 = 0;
    }

    if (s05a_dword_800C3648 <= 0)
    {
        if (m1e1->field_EBC != NULL && m1e1->field_EBC->body.action != 5 &&
            m1e1->field_EBC->field_214 == 0)
        {
            m1e1->body.rots[8].vx = GV_NearSpeed(m1e1->body.rots[8].vx, -0x638, 0x2D);
            if (m1e1->body.rots[8].vx >= -0x5B1 && m1e1->body.rots[8].vx < -0x584)
            {
                GM_SeSetPan(&pos, 0xBC, s1);
            }
        }
        if (m1e1->field_EBC == NULL || m1e1->field_EBC->body.action == 5)
        {
            m1e1->body.rots[8].vx = GV_NearSpeed(m1e1->body.rots[8].vx, 0, 0x2D);
            if (m1e1->body.rots[8].vx >= -0xB4 && m1e1->body.rots[8].vx < -0x87)
            {
                GM_SeSetPan(&pos, 0xBB, s1);
            }
        }
    }
}
Work *NewM1E1Vulcan(M1e1 *m1e1)
{
    Work *work;
    int   i;

    work = GV_NewActor(GV_ACTOR_AFTER, sizeof(Work));
    if (work == NULL)
    {
        return NULL;
    }
    work->field_1E8 = 1;
    work->field_1EC = m1e1;
    GV_SetNamedActor(work, s05a_800DD6B8, s05a_800DDC14, s05a_dword_800E351C);
    if (GM_InitControl(&work->control, work->field_1EC->field_744, work->field_1EC->field_748) < 0)
    {
        GV_DestroyActor(work);
        return NULL;
    }
    work->control.r_sphere = -2;
    work->control.interp = 0;
    GM_ConfigControlAttribute(&work->control, 5);
    work->light[0].t[0] = work->field_1EC->field_B0;
    work->light[0].t[1] = work->field_1EC->field_B4;
    work->light[0].t[2] = work->field_1EC->field_B8;
    GM_InitObject(&work->body, GV_StrCode(s05a_dword_800E3528), 0x32D, GV_StrCode(s05a_dword_800E3530));
    GM_ConfigObjectJoint(&work->body);
    GM_ConfigMotionControl(&work->body, &work->m_ctrl, GV_StrCode(s05a_dword_800E3530),
                           work->m_segs1, work->m_segs2, &work->subcontrol, work->rots);
    GM_ConfigObjectLight(&work->body, &work->light[0]);
    DG_InvisibleObjs(work->body.objs);
    for (i = 0; i < 16; i++)
    {
        work->body.objs->objs[i].world = DG_ZeroMatrix;
    }
    if (GM_Vitality != 0 && GM_GameOverTimer == 0 && work->field_1EC->field_EC4 < 2)
    {
        work->field_1EC->field_D54 = 3;
        work->field_1EC->field_ED0 = 2;
        work->last_weapon = GM_Weapon;
        work->last_item = GM_Item;
        GM_Weapon = WP_None;
        if (GM_Item != IT_NVG && GM_Item != IT_ThermG)
        {
            GM_Item = IT_None;
        }
    }
    work->field_214 = 0x1E;
    return work;
}
void s05a_800DD6B8(Work *work)
{
    SVECTOR pos;
    SVECTOR vec;
    SVECTOR vec2;
    int     vol;

    if (work->body.action == 5 && work->field_214 == 1)
    {
        GV_DestroyActor(work);
        return;
    }
    if (--work->field_214 < 0) work->field_214 = 0;
    if (work->field_214 > 0) return;

    memset(&work->subcontrol.step, 0, 8);
    GM_ActMotion(&work->body);
    GM_ActControl(&work->control);
    vec = work->subcontrol.step;
    GM_ActObject(&work->body);
    work->subcontrol.step = vec;
    DG_GetLightMatrix2(&work->control.mov, &work->light[0]);
    if (work->field_1E8 == 0)
    {
        work->body.objs->flag &= ~0x80;
    }
    work->control.step.vx = 0;
    work->control.step.vz = 0;

    if (work->field_1EC->field_ED0 == 2)
    {
        pos = GM_PlayerPosition;
        vol = 0x3F;
    }
    else
    {
        pos = work->control.mov;
        vol = work->field_1EC->field_E60;
    }

    switch (work->body.action)
    {
    case 2:
    case 5:
        break;
    case 11:
    case 12:
        if (work->field_224 == 0) GM_SeSetPan(&pos, 0x83, vol);
        if (work->body.action == 12)
        {
            if (work->field_224 == 0x11 || work->field_224 == 0x18 || work->field_224 == 0x1F ||
                work->field_224 == 0x26 || work->field_224 == 0x2D || work->field_224 == 0x34 ||
                work->field_224 == 0x3B || work->field_224 == 0x42)
            {
                GM_SeSetPan(&pos, 0x34, vol / 2);
            }
        }
        if (work->body.action == 12)
        {
            if (work->field_224 == 0x4E || work->field_224 == 0x55 || work->field_224 == 0x5C ||
                work->field_224 == 0x63 || work->field_224 == 0x69 || work->field_224 == 0x70)
            {
                GM_SeSetPan(&pos, 0xBA, vol);
            }
        }
        work->field_224++;
        break;
    case 13:
        if (work->field_224 == 0x17) GM_SeSetPan(&pos, 0x87, vol);
        if (work->field_224 == 0x50) GM_SeSetPan(&pos, 0x87, vol);
        work->field_224++;
        break;
    }

    DG_SetPos(&work->field_1EC->body.objs->objs[6].world);
    vec.vx = 0;
    vec.vy = 0;
    vec.vz = 0;
    vec2.vx = 0;
    vec2.vy = 0;
    vec2.vz = 0x64;
    DG_PutVector(&vec, &vec, 1);
    DG_PutVector(&vec2, &vec2, 1);
    vec2.vx -= vec.vx;
    vec2.vy -= vec.vy;
    vec2.vz -= vec.vz;
    work->control.turn.vx = -ratan2(vec2.vy, SquareRoot0(vec2.vx * vec2.vx + vec2.vz * vec2.vz));
    work->control.turn.vy = ratan2(vec2.vx, vec2.vz);
    work->control.turn.vz = 0;
    vec.vx = work->field_1EC->body.objs->objs[6].world.t[0];
    vec.vy = work->field_1EC->body.objs->objs[6].world.t[1];
    vec.vz = work->field_1EC->body.objs->objs[6].world.t[2];
    work->control.mov.vy = work->body.height + work->field_1EC->field_20.vy;
    work->control.step.vx = vec.vx - work->control.mov.vx;
    work->control.step.vz = vec.vz - work->control.mov.vz;

    if (work->body.is_end == 0)
    {
        work->field_1E8 = 0;
    }
    else
    {
        switch (work->body.action)
        {
        case 2:
            work->field_220 = 0;
            work->field_224 = 0;
            if (work->field_1EC->field_ED0 == 2)
            {
                if (work->field_1EC->field_ECC == 7)
                {
                    GM_ConfigObjectAction(&work->body, 0xD, 0, 5);
                }
                else if (work->field_1EC->field_ECC < 4)
                {
                    GM_ConfigObjectAction(&work->body, 0xB, 0, 5);
                }
                else
                {
                    GM_ConfigObjectAction(&work->body, 0xC, 0, 5);
                }
            }
            else
            {
                if ((rand() & 1) == 0)
                {
                    GM_ConfigObjectAction(&work->body, 0xB, 0, 5);
                }
                else
                {
                    GM_ConfigObjectAction(&work->body, 0xC, 0, 5);
                }
            }
            work->field_1E8 = 0;
            break;
        case 11:
        case 12:
        case 13:
            GM_ConfigObjectAction(&work->body, 5, 0, 5);
            work->field_1E8 = 0;
            break;
        case 5:
            work->field_214 = 0x1E;
            work->body.objs->flag |= 0x80;
            break;
        default:
            work->field_1E8 = 0;
            break;
        }
    }
}

void s05a_800DDC14(Work *work)
{
    if (work->field_1EC->field_ED0 == 2)
    {
        if (work->field_1EC->field_D58 == 0)
        {
            work->field_1EC->field_D54 = work->field_1EC->field_ED0;
        }
        else
        {
            work->field_1EC->field_D54 = 7;
        }
        work->field_1EC->field_ED0 = 1;
        work->field_1EC->field_F48 = work->field_1EC->field_DB8;
        GM_Weapon = work->last_weapon;
        GM_Item = work->last_item;
    }

    work->field_1EC->field_EBC = 0;
    GM_FreeObject(&work->body);
    GM_FreeControl(&work->control);
}
