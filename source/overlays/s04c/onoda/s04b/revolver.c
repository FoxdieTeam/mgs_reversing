#include "chara/snake/shadow.h"
#include "game/game.h"
#include "libgcl/libgcl.h"
#include "menu/menuman.h"
#include "takabe/thing.h"

#define EXEC_LEVEL      5

#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE)
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
    char           pad1[0x90];
    MATRIX         light[2];
    TARGET        *field_83C;
    HOMING        *hom;
    MENU_BAR_CONF  lifebar;
    int            field_850;
    int            field_854;
    char           pad15[0x4];
    DG_TEX        *field_85C;
    DG_TEX        *field_860;
    DG_TEX        *field_864;
    SVECTOR        field_868;
    char           pad3[0x4];
    int            field_874;
    char           pad4[0x4];
    int            field_87C;
    int            field_880;
    char           pad5[0x4];
    int            field_888;
    int            field_88C;
    int            field_890;
    char           pad6[0xC];
    int            field_8A0;
    int            field_8A4;
    int            field_8A8;
    int            field_8AC;
    char           pad7[0x28];
    GV_ACT        *shadow;
    char           pad8[0x4];
    int            field_8E0;
    char           pad17[0x8];
    int            field_8EC;
    char           pad9[0xC];
    int            field_8FC[2];
    char           pad18[0x50];
    void          *field_954;
    void          *field_958;
    void          *field_95C;
    int            field_960;
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

extern void *s04c_dword_800DBE14;
extern int   s04c_dword_800DBE20;

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

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF518.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF584.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF5D0.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF650.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF69C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF71C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF748.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF7AC.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF7FC.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF868.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF8D8.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFAF0.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFBE0.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFC3C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFC6C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFD08.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFD84.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFE44.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFED4.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D00B4.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D02C8.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D03C0.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D03EC.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D0418.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D0444.s")

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
    GM_FreeTarget(work->field_83C);
    GV_DestroyActor(work->shadow);

    GM_GameStatus &= ~STATE_SHOW_LIFEBAR;
}

int s04c_revolver_800D1C60(RevolverWork *work)
{
    TARGET *target;

    target = GM_AllocTarget();
    work->field_83C = target;
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

    work->shadow = NewShadow_800602CC(control, body, indices);
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
    work->field_88C = 0;
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

    work->field_85C = DG_GetTexture(0xCB50); // tama_01
    work->field_860 = DG_GetTexture(0xCB51); // tama_02
    work->field_864 = DG_GetTexture(0xCB52); // tama_03

    work->field_964 = 4000;
    work->field_8EC = 0;
    work->field_968 = 3000;

    GM_GameStatus |= STATE_SHOW_LIFEBAR;

    work->field_960 = THING_Gcl_GetIntDefault('h', 1024);
    work->field_96C = 30;
    work->field_970 = 30;
    work->field_974 = 180;

    work->field_83C->field_26_hp = work->field_960;

    s04c_revolver_800D04B8(work->field_8FC, 6);

    s04c_dword_800DBE14 = work;
    s04c_dword_800DBE20 = 0;

    return 0;
}

void *NewRevolver(int name, int where)
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

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revbullt_800D20BC.s")

/*
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

    tex1 = work->field_85c[5];

    if (work->field_874)
    {
        start = work->field_874;
        tex2 = work->field_854[5];
    }
    else
    {
        start = work->field_878;
        tex2 = work->field_860;
    }

    prim = MENU_GetPrimInfo();

    if (prim->mPrimBuf.mFreeLocation + sizeof(*prims) <= prim->mPrimBuf.mOtEnd)
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

            addPrim(prim->mPrimBuf.mOt, sprt);
            sprt++;
        }

        addPrim(prim->mPrimBuf.mOt, &prims->tpage[0]);

        for (i = start; i < 6; i++)
        {
            setSprt(sprt);
            setRGB0(sprt, 128, 128, 128);
            setXY0(sprt, x, y);
            setWH(sprt, 6, 12);
            setUV0(sprt, tex1->off_x, tex1->off_y);
            sprt->clut = tex1->clut;

            x += 6;
            
            addPrim(prim->mPrimBuf.mOt, sprt);
            sprt++;
        }

        addPrim(prim->mPrimBuf.mOt, &prims->tpage[1]);
    }
}
*/