#include "common.h"
#include "linkvar.h"
#include "strcode.h"
#include "chara/snake/sna_init.h"
#include "chara/snake/shadow.h"
#include "game/game.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "menu/menuman.h"
#include "okajima/blood.h"
#include "takabe/thing.h"

#define EXEC_LEVEL      5

#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )
#define TARGET_FLAG     ( TARGET_SEEK | TARGET_PUSH | TARGET_POWER )

#define REVJOINT_NUM    17

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
    int            field_850;
    int            field_854;
    char           pad1[0x4];
    DG_TEX        *field_85C;
    DG_TEX        *field_860;
    DG_TEX        *field_864;
    SVECTOR        field_868;
    char           pad2[0x4];
    int            field_874;
    int            field_878;
    int            field_87C;
    int            field_880;
    int            field_884;
    int            field_888;
    int            enable_shadow;
    int            field_890;
    char           pad3[0xC];
    int            field_8A0;
    int            field_8A4;
    int            field_8A8;
    int            field_8AC;
    char           pad4[0x20];
    int            field_8D0;
    int            field_8D4;
    GV_ACT        *shadow;
    char           pad5[0x4];
    int            field_8E0;
    char           pad6[0x8];
    int            field_8EC;
    char           pad9[0xC];
    int            field_8FC[2];
    char           pad10[0x18];
    SVECTOR        field_91C;
    int            field_924[4];
    SVECTOR        field_934;
    int            field_93C;
    char           pad12[0x14];
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

SVECTOR revolver_target_size = {400, 900, 400};

extern char s04c_dword_800C3468[]; // = "OCELOT"

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

extern void   *s04c_dword_800DBE14;
extern SVECTOR s04c_dword_800DBE18;
extern int     s04c_dword_800DBE20;

MenuPrim *MENU_GetPrimInfo(void);

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

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF8D8.s")

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

void s04c_revolver_800CFC3C(void)
{
    s04c_revolver_800CFBE0(GM_PlayerPosition.vx, GM_PlayerPosition.vz);
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

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFED4.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D00B4.s")

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

void s04c_revolver_800D04B8(int *arg0, int arg1)
{
    arg0[0] = arg1;
    arg0[1] = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D04C4.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D07F4.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D0A94.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D0DE0.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D1120.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D11C8.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D1318.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D1364.s")

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D149C.s")
const int s04c_dword_800DBAA8 = 0x800D14F0;
const int s04c_dword_800DBAAC = 0x800D1504;
const int s04c_dword_800DBAB0 = 0x800D1518;
const int s04c_dword_800DBAB4 = 0x800D152C;
const int s04c_dword_800DBAB8 = 0x800D1540;
const int s04c_dword_800DBABC = 0x800D1554;
const int s04c_dword_800DBAC0 = 0x800D1568;

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D158C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D15D4.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D168C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D1760.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D184C.s") // Act
void s04c_revolver_800D184C(RevolverWork *work);

void Die(RevolverWork *work)
{
    GM_GameStatus &= ~STATE_SHOW_LIFEBAR;

    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeTarget(work->target);
    GV_DestroyActor(work->shadow);

    GM_GameStatus &= ~STATE_SHOW_LIFEBAR;
}

int s04c_revolver_800D1C60(RevolverWork *work)
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

int GetResources(RevolverWork *work, int name, int where)
{
    SVECTOR        indices;
    CONTROL       *control;
    char          *pos;
    char          *dir;
    OBJECT        *body;
    int            model;
    int            motion;
    HOMING        *hom;
    MENU_BAR_CONF *lifebar;

    control = &work->control;

    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    pos = GCL_GetOption('p');
    dir = GCL_GetOption('d');
    GM_ConfigControlString(control, pos, dir);

    GM_ConfigControlHazard(control, work->control.mov.vy, -1, -1);
    GM_ConfigControlAttribute(control, 1);
    GM_ConfigControlInterp(control, 1);

    body = &work->body;
    model = GV_StrCode("rev_gun");
    motion = GV_StrCode("revolver");
    GM_InitObject(body, model, BODY_FLAG, motion);

    GM_ConfigObjectJoint(body);
    GM_ConfigMotionControl(body, &work->m_ctrl, GV_StrCode("revolver"), work->m_segs1, work->m_segs2, control, work->rots);
    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectAction(body, 1, 0, 0);

    work->field_954 = s04c_revolver_800CF418;
    work->field_958 = s04c_revolver_800CF418;
    work->field_95C = s04c_revolver_800CF418;

    hom = GM_AllocHomingTarget(&work->body.objs->objs[0].world, control);
    work->hom = hom;

    hom->flag = 1;

    if (s04c_revolver_800D1C60(work) < 0)
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
        work->field_8E0 = GCL_StrToInt(GCL_GetParamResult());
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

    work->field_854 = 1024;
    work->field_850 = 1024;

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

    s04c_revolver_800D04B8(work->field_8FC, 6);

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
        GV_SetNamedActor(&work->actor, s04c_revolver_800D184C, Die, "revolver.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}


void s04c_revbullt_800D20BC(RevolverWork *work)
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
