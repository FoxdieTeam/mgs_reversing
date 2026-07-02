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
    char    pad_BC[0x140 - 0xBC];
    short   field_140;   /* 0x140 */
    char    pad_142[0x744 - 0x142];
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
    char    pad_EC8[0xED0 - 0xEC8];
    int     field_ED0;   /* 0xED0 */
    char    pad_ED4[0xF48 - 0xED4];
    int     field_F48;   /* 0xF48 */
} M1e1;

struct _Work
{
    GV_ACT  actor;       /* 0x000 */
    CONTROL control;     /* 0x020 */
    MATRIX  light;       /* 0x09C */
    char    pad_BC[0xDC - 0xBC];
    OBJECT  body;        /* 0x0DC */
    char    pad_1C0[0x1E8 - 0x1C0];
    int     field_1E8;   /* 0x1E8 */
    M1e1   *field_1EC;   /* 0x1EC */
    char    pad_1F0[0x1F8 - 0x1F0];
    int     field_1F8;   /* 0x1F8 */
    int     field_1FC;   /* 0x1FC */
    char    pad_200[0x214 - 0x200];
    int     field_214;   /* 0x214 */
    char    pad_218[0x234 - 0x218];
    MOTION_CONTROL m_ctrl;        /* 0x234 */
    MOTION_SEGMENT m_segs1[17];   /* 0x284 */
    MOTION_SEGMENT m_segs2[17];   /* 0x4E8 */
    CONTROL        subcontrol;    /* 0x74C */
    SVECTOR        rots[16];      /* 0x7C8 */
};

extern int s05a_dword_800C3644;
extern int s05a_dword_800C3648;

extern const char s05a_dword_800E351C[];
extern const char s05a_dword_800E3528[];
extern const char s05a_dword_800E3530[];

void  s05a_800DD6B8(Work *work);
void  s05a_800DDC14(Work *work);
Work *s05a_800DD440(M1e1 *m1e1);

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
                m1e1->field_EBC = s05a_800DD440(m1e1);
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
            m1e1->field_140 = GV_NearSpeed(m1e1->field_140, -0x638, 0x2D);
            if ((u_short)(m1e1->field_140 + 0x5B1) < 0x2D)
            {
                GM_SeSetPan(&pos, 0xBC, s1);
            }
        }
        if (m1e1->field_EBC == NULL || m1e1->field_EBC->body.action == 5)
        {
            m1e1->field_140 = GV_NearSpeed(m1e1->field_140, 0, 0x2D);
            if ((u_short)(m1e1->field_140 + 0xB4) < 0x2D)
            {
                GM_SeSetPan(&pos, 0xBB, s1);
            }
        }
    }
}
Work *s05a_800DD440(M1e1 *m1e1)
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
    work->light.t[0] = work->field_1EC->field_B0;
    work->light.t[1] = work->field_1EC->field_B4;
    work->light.t[2] = work->field_1EC->field_B8;
    GM_InitObject(&work->body, GV_StrCode(s05a_dword_800E3528), 0x32D, GV_StrCode(s05a_dword_800E3530));
    GM_ConfigObjectJoint(&work->body);
    GM_ConfigMotionControl(&work->body, &work->m_ctrl, GV_StrCode(s05a_dword_800E3530),
                           work->m_segs1, work->m_segs2, &work->subcontrol, work->rots);
    GM_ConfigObjectLight(&work->body, &work->light);
    work->body.objs->flag |= 0x80;
    for (i = 0; i < 16; i++)
    {
        work->body.objs->objs[i].world = DG_ZeroMatrix;
    }
    if (GM_SnakeCurrentHealth != 0 && GM_GameOverTimer == 0 && work->field_1EC->field_EC4 < 2)
    {
        work->field_1EC->field_D54 = 3;
        work->field_1EC->field_ED0 = 2;
        work->field_1F8 = GM_CurrentWeaponId;
        work->field_1FC = GM_CurrentItemId;
        GM_CurrentWeaponId = -1;
        if ((u_short)(GM_CurrentItemId - 5) >= 2)
        {
            GM_CurrentItemId = -1;
        }
    }
    work->field_214 = 0x1E;
    return work;
}
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DD6B8.s")

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
        GM_CurrentWeaponId = work->field_1F8;
        GM_CurrentItemId = work->field_1FC;
    }

    work->field_1EC->field_EBC = 0;
    GM_FreeObject(&work->body);
    GM_FreeControl(&work->control);
}
