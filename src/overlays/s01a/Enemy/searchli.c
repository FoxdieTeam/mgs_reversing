#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"

typedef struct _SearchlightWork
{
    GV_ACT   actor;
    CONTROL  control;
    char     pad[0x60];   // 9C
    SVECTOR  fFC;
    SVECTOR  f104;
    SVECTOR  f10C;
    SVECTOR  f114;
    SVECTOR  f11C;
    char     pad2[0x120]; // 124
    SVECTOR  f244;
    char     pad3[0x8];   // 24C
    DG_PRIM *prim;        // 254
    DG_TEX  *tex;
    char     pad4[0x4];
    SVECTOR  f260;
    short    f268;
    short    f26A;
    short    height;
    short    f26E;
    short    angle;
    short    f272;
    short    f274;
    short    f276;
    short    f278;
    short    f27A;
    short    f27C;
    short    f27E;
    int      debug;
    char     pad5[0x10];
    int      f294;
    char     pad6[0x4];
    int      f29C;
    int      f2A0;
    int      f2A4;
    int      f2A8;
    int      f2AC;
    int      f2B0;
    int      f2B4;
    char     pad8[0x8];
    GV_ACT  *lit_mdl;
    MATRIX   lit_mtx;
} SearchlightWork;

extern MATRIX  DG_ZeroMatrix_8009D430;
extern SVECTOR DG_ZeroVector_800AB39C;
extern SVECTOR GM_PlayerPosition_800ABA10;
extern GV_PAD  GV_PadData_800B05C0[4];

extern SVECTOR SearchliCenter_800E46D8;
extern int     s01a_dword_800E4C78;
extern int     s01a_dword_800E4DC0;
extern int     s01a_dword_800E4E08;

extern const char aSearchliUDRotXLRRotY[];  // = "UD:ROT.X  LR:ROT.Y\n"
extern const char aSearchliUDPosXLRPosZ[];  // = "UD:POS.X  LR:POS.Z\n"
extern const char aSearchliUDPosYLRAngle[]; // = "UD:POS.Y  LR:ANGLE\n"
extern const char aSearchliRot7D7D7D[];     // = "ROT:%7d %7d %7d\n"
extern const char aSearchliPos7D7D7D[];     // = "POS:%7d %7d %7d\n"
extern const char aSearchliAngle4D[];       // = "ANGLE:%4d \n"
extern const char aSearchli0[];             // = "0"
extern const char aSearchliShadow[];        // = "shadow"
extern const char aSearchliC[];             // = "searchli.c"

GV_ACT *s01a_lit_mdl_800E2C88(MATRIX *arg0, int arg1, int arg2, int arg3);

#define EXEC_LEVEL 4

void s01a_camshake_800E2D3C(GV_ACT *, int angle);
void s01a_env_snd_800E2364(MATRIX *, SVECTOR *, VECTOR *);
void s01a_object_800D9424(CONTROL *, int);
void s01a_command_800D1648(int);
void s01a_command_800D1660(void);
void s01a_command_800D17A0(SVECTOR *, int);

int  s01a_searchli_800D73D8(SearchlightWork *work);
void s01a_searchli_800D7500(SVECTOR *, SVECTOR *, SearchlightWork *work);
void s01a_searchli_800D75C0(SearchlightWork *work);
int  s01a_searchli_800D763C(SearchlightWork *work);
int  s01a_searchli_800D770C(SearchlightWork *work);
int  s01a_searchli_800D77A4(SearchlightWork *work);
void s01a_searchli_800D783C(SearchlightWork *work);

int Searchli_800D7908(SearchlightWork *work)
{
    SVECTOR *from;
    SVECTOR *to;
    int      diff;

    from = &work->f260;
    to = &work->control.field_4C_turn_vec;

    diff = GV_DiffDirS_8001704C(from->vy, to->vy);
    if (diff < -10)
    {
        to->vy += 8;
    }
    else if (diff < 10)
    {
        to->vy = from->vy;
    }
    else
    {
        to->vy -= 8;
    }
    to->vy &= 0xFFF;

    diff = GV_DiffDirS_8001704C(from->vx, to->vx);
    if (diff < -10)
    {
        to->vx += 8;
    }
    else if (diff < 10)
    {
        to->vx = from->vx;
    }
    else
    {
        to->vx -= 8;
    }
    to->vx &= 0xFFF;

    if (to->vx == from->vx && to->vy == from->vy && (work->f2A0 < 0 || work->f2A0 > 96))
    {
        return 1;
    }

    work->f2A0++;
    return 0;
}

void Searchli_800D7A4C(SearchlightWork *work)
{
    switch (work->f29C)
    {
    case 2:
        if (s01a_searchli_800D770C(work))
        {
            work->f29C = 3;
            work->f2A0 = 0;
        }

        s01a_searchli_800D7500(&work->control.field_4C_turn_vec, &work->control.field_4C_turn_vec, work);

        if (s01a_searchli_800D73D8(work))
        {
            work->f29C = 1;
            work->f2A0 = 0;
        }
        break;

    case 3:
        if (s01a_searchli_800D77A4(work))
        {
            work->f29C = 2;
            work->f2A0 = 0;
        }

        s01a_searchli_800D7500(&work->control.field_4C_turn_vec, &work->control.field_4C_turn_vec, work);

        if (s01a_searchli_800D73D8(work))
        {
            work->f29C = 1;
            work->f2A0 = 0;
        }
        break;

    case 4:
        s01a_searchli_800D75C0(work);
        break;

    case 1:
        if (s01a_searchli_800D763C(work))
        {
            s01a_command_800D1648(255);
            s01a_command_800D1660();
            work->f294 = 1;
            work->f29C = 4;
            work->f2A0 = 0;
        }
        break;
    }

    if (s01a_dword_800E4DC0 == 1)
    {
        work->f294 = s01a_dword_800E4DC0;

        do {} while (0);

        if (work->f294 == s01a_dword_800E4C78)
        {
            work->f29C = 4;
        }
        else
        {
            work->f29C = 0;
        }

        work->f2A0 = 0;
    }
}

void Searchli_800D7BB8(SearchlightWork *work)
{
    switch (work->f29C)
    {
    case 4:
        s01a_searchli_800D75C0(work);

        if (s01a_searchli_800D73D8(work))
        {
            s01a_command_800D1648(255);
            s01a_command_800D1660();
        }
        break;

    case 0:
        if (s01a_searchli_800D73D8(work))
        {
            work->f29C = 4;
        }
        break;
    }

    if (s01a_dword_800E4DC0 != 1)
    {
        work->f294 = 2;
        work->f29C = 5;
        work->f2A0 = 0;
    }
}

void Searchli_800D7C58(SearchlightWork *work)
{
    switch (work->f29C)
    {
    case 5:
        s01a_searchli_800D783C(work);

        if (s01a_dword_800E4DC0 == 0)
        {
            work->f29C = 6;
            work->f2A0 = 0;
        }
        break;

    case 6:
        if (Searchli_800D7908(work))
        {
            work->f294 = 0;
            work->f29C = 2;
            work->f2A0 = 0;
        }
        break;
    }

    if (s01a_searchli_800D73D8(work))
    {
        s01a_command_800D1648(255);
        s01a_command_800D1660();
        s01a_command_800D17A0(&work->control.field_0_mov, 64);
        s01a_dword_800E4E08 = 10;
        work->f294 = 1;
        work->f29C = 4;
        work->f2A0 = 0;
    }
    else if (s01a_dword_800E4DC0 == 1)
    {
        work->f294 = 1;
        work->f29C = 4;
        work->f2A0 = 0;
    }
}

void Searchli_800D7D40(SearchlightWork *work)
{
    switch (work->f294)
    {
    case 0:
        Searchli_800D7A4C(work);
        break;

    case 1:
        Searchli_800D7BB8(work);
        break;

    case 2:
        Searchli_800D7C58(work);
        break;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s01a/Searchli_800D7DBC.s")

void Searchli_800D80AC(SVECTOR *vec, short x, short y, short z)
{
    vec->vx = x;
    vec->vy = y;
    vec->vz = z;
}

#pragma INCLUDE_ASM("asm/overlays/s01a/Searchli_800D80BC.s")
void Searchli_800D80BC(SearchlightWork *);

void SearchlightAct_800D86F0(SearchlightWork *work)
{
    SVECTOR  pos;
    VECTOR   sp18;
    VECTOR   sp28;
    SVECTOR  center;
    int      f2A8;
    int      status;

    GM_ActControl_80025A7C(&work->control);

    DG_SetPos2_8001BC8C(&work->control.field_0_mov, &work->control.field_8_rotator);
    ReadRotMatrix(&work->lit_mtx);

    if (GM_CurrentItemId == ITEM_STEALTH)
    {
        work->f2A4 = 0;
        work->f2B4 = 0;
    }
    else
    {
        // Snake detected by searchlight logic
        pos.vx = GM_PlayerPosition_800ABA10.vx;
        pos.vz = GM_PlayerPosition_800ABA10.vz;
        pos.vy = work->height;

        s01a_env_snd_800E2364(&work->lit_mtx, &pos, &sp18);

        sp18.vx >>= 2;
        sp18.vy >>= 2;
        sp18.vz >>= 2;

        Square0(&sp18, &sp28);

        f2A8 = ratan2(SquareRoot0(sp28.vx + sp28.vy), sp18.vz) & 0xFFF;
        work->f2A8 = f2A8;
        work->f2AC = SquareRoot0(sp28.vx + sp28.vy + sp28.vz);

        if ((work->angle / 2) < f2A8)
        {
            work->f2A4 = 0;
        }
        else
        {
            work->f2A4 = 1;
        }

        if (f2A8 < (work->f272 / 2))
        {
            work->f2B4 = 1;
        }
        else
        {
            work->f2B4 = 0;
        }
    }

    if ((work->debug != 0) && (GV_PadData_800B05C0[1].status & PAD_SQUARE))
    {
        status = GV_PadData_800B05C0[1].status;

        if ((GV_PadData_800B05C0[1].press & PAD_TRIANGLE) && (++work->debug >= 4))
        {
            work->debug = 1;
        }

        menu_Text_XY_Flags_80038B34(8, 180, 0);

        switch (work->debug - 1)
        {
        case 0:
            menu_Text_80038C38(aSearchliUDRotXLRRotY);

            if (status & PAD_UP)
            {
                work->control.field_4C_turn_vec.vx -= 5;
            }

            if (status & PAD_DOWN)
            {
                work->control.field_4C_turn_vec.vx += 5;
            }

            if (status & PAD_LEFT)
            {
                work->control.field_4C_turn_vec.vy += 5;
            }

            if (status & PAD_RIGHT)
            {
                work->control.field_4C_turn_vec.vy -= 5;
            }
            break;

        case 1:
            menu_Text_80038C38(aSearchliUDPosXLRPosZ);

            if (status & PAD_UP)
            {
                work->control.field_0_mov.vz -= 20;
            }

            if (status & PAD_DOWN)
            {
                work->control.field_0_mov.vz += 20;
            }

            if (status & PAD_LEFT)
            {
                work->control.field_0_mov.vx -= 20;
            }

            if (status & PAD_RIGHT)
            {
                work->control.field_0_mov.vx += 20;
            }
            break;

        case 2:
            menu_Text_80038C38(aSearchliUDPosYLRAngle);

            if (status & PAD_UP)
            {
                work->control.field_0_mov.vy += 20;
            }

            if (status & PAD_DOWN)
            {
                work->control.field_0_mov.vy -= 20;
            }

            if (status & PAD_LEFT)
            {
                work->angle = sub_8002646C(work->angle, 0, 5);
            }

            if (status & PAD_RIGHT)
            {
                work->angle = sub_8002646C(work->angle, 512, 5);
            }
            break;
        }

        menu_Text_80038C38(aSearchliRot7D7D7D, work->control.field_4C_turn_vec.vx, work->control.field_4C_turn_vec.vy, work->control.field_4C_turn_vec.vz);
        menu_Text_80038C38(aSearchliPos7D7D7D, work->control.field_0_mov.vx, work->control.field_0_mov.vy, work->control.field_0_mov.vz);
        menu_Text_80038C38(aSearchliAngle4D, work->angle);

        s01a_camshake_800E2D3C(work->lit_mdl, work->angle);

        if (status & PAD_L2)
        {
            center = SearchliCenter_800E46D8;
            DG_SetPos2_8001BC8C(&work->control.field_0_mov, &work->control.field_4C_turn_vec);
            DG_PutVector_8001BE48(&center, &center, 1);
            DG_LookAt_800172D0(DG_Chanl(0), &work->control.field_0_mov, &center, 320);
        }
        else
        {
            s01a_object_800D9424(&work->control, 2);
        }

        Searchli_800D80BC(work);
    }
    else
    {
        Searchli_800D80BC(work);

        if (work->debug == 0)
        {
            Searchli_800D7D40(work);
        }
    }
}

int Searchlight_800D8B84(SearchlightWork *work, int name, int map)
{
    int opt;

    opt = GCL_GetOption_80020968('i');
    work->f26E = GCL_StrToInt_800209E8(opt ? (char *)opt : (char *)aSearchli0);

    opt = GCL_GetOption_80020968('w');
    work->f268 = GCL_StrToInt_800209E8(opt ? (char *)opt : (char *)aSearchli0);
    if (work->f268 > 4000)
    {
        work->f268 = 4000;
    }

    opt = GCL_GetOption_80020968('x');
    work->f26A = GCL_StrToInt_800209E8(opt ? (char *)opt : (char *)aSearchli0);
    if (work->f26A > 1024)
    {
        work->f26A = 1024;
    }

    opt = GCL_GetOption_80020968('h');
    work->height = GCL_StrToInt_800209E8(opt ? (char *)opt : (char *)aSearchli0);
    if (work->height > 30000)
    {
        work->height = 30000;
    }

    work->f260 = work->control.field_8_rotator;
    if (work->f260.vx > 1000)
    {
        work->f260.vx = 1000;
    }

    work->angle = 300;
    if (GCL_GetOption_80020968('a'))
    {
        work->angle = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    if (GCL_GetOption_80020968('l'))
    {
        work->f272 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    work->f272 += work->angle;

    if (GCL_GetOption_80020968('t'))
    {
        work->f274 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->f276 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->f26A = work->f278 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->f27A = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        work->f274 = 280;
        work->f276 = 330;
        work->f278 = 512;
        work->f27A = 4;
    }

    work->f27C = 48;

    if (GCL_GetOption_80020968('z'))
    {
        work->debug = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    work->f294 = 0;
    work->f29C = 2;
    work->f2A0 = 0;
    work->f2B0 = 100000;

    return 0;
}

void Searchli_800D8DDC(POLY_FT4 *packs, DG_TEX *tex, int abr, int r, int g, int b, int size)
{
    int xs, ys;
    int x, y;
    int u0, u1, v0, v1;
    int u, v, w, h;

    xs = size;
    ys = size;

    for (y = 0; y < ys; y++)
    {
        for (x = 0; x < xs; x++)
        {
            setPolyFT4(packs);
            setRGB0(packs, r, g, b);

            if (abr < 4)
            {
                setSemiTrans(packs, 1);

                u0 = tex->field_8_offx + ((tex->field_A_width + 1) * x) / xs;
                u1 = tex->field_8_offx + ((tex->field_A_width + 1) * (x + 1)) / xs - 1;
                packs->u0 = packs->u2 = u0;
                packs->u1 = packs->u3 = u1;

                v0 = tex->field_9_offy + ((tex->field_B_height + 1) * y) / ys;
                v1 = tex->field_9_offy + ((tex->field_B_height + 1) * (y + 1)) / ys - 1;
                packs->v0 = packs->v1 = v0;
                packs->v2 = packs->v3 = v1;

                packs->tpage = tex->field_4_tPage;
                packs->clut = tex->field_6_clut;

                packs->tpage = (packs->tpage & ~0x60) | (abr << 5);
            }
            else
            {
                u = tex->field_8_offx;
                w = tex->field_A_width;
                v = tex->field_9_offy;
                h = tex->field_B_height;
                setUVWH(packs, u, v, w, h);
                packs->tpage = tex->field_4_tPage;
                packs->clut = tex->field_6_clut;
            }

            packs++;
        }
    }
}

int Searchli_800D9040(SearchlightWork *work)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    Searchli_800D80AC(&work->f244, 0, 0, 0);
    Searchli_800D80AC(&work->fFC, 0, 0, 0);
    Searchli_800D80AC(&work->f104, -200, 0, -200);
    Searchli_800D80AC(&work->f10C, 200, 0, -200);
    Searchli_800D80AC(&work->f114, -200, 0, 200);
    Searchli_800D80AC(&work->f11C, 200, 0, 200);

    prim = DG_GetPrim(0x12, 9, 0, (SVECTOR *)work->pad2, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 600;

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC(aSearchliShadow));
    work->tex = tex;
    if (tex == NULL)
    {
        return -1;
    }

    Searchli_800D8DDC(&prim->field_40_pBuffers[0]->poly_ft4, tex, 2, 78, 78, 78, 3);
    Searchli_800D8DDC(&prim->field_40_pBuffers[1]->poly_ft4, tex, 2, 78, 78, 78, 3);
    return 0;
}

int SearchlightGetResources_800D91B0(SearchlightWork *work, int name, int map)
{
    CONTROL *control;
    int      pos, dir;

    control = &work->control;

    if (GM_InitLoader_8002599C(control, name, map) < 0)
    {
        return -1;
    }

    pos = GCL_GetOption_80020968('p');
    dir = GCL_GetOption_80020968('d');

    GM_ConfigControlString_800261C0(control, (char *)pos, (char *)dir);
    GM_ConfigControlAttribute_8002623C(control, 0);
    GM_ConfigControlHazard_8002622C(control, -1, -2, -1);
    work->control.field_44_movementVector = DG_ZeroVector_800AB39C;

    Searchli_800D9040(work);
    return 0;
}

void SearchlightDie_800D9274(SearchlightWork *work)
{
    DG_PRIM *prim;

    GM_FreeControl_800260CC(&work->control);

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

GV_ACT * NewSearchlight_800D92BC(int name, int where)
{
    SearchlightWork *work;

    work = (SearchlightWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(SearchlightWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)SearchlightAct_800D86F0, (TActorFunction)SearchlightDie_800D9274, aSearchliC);

        if (SearchlightGetResources_800D91B0(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        Searchlight_800D8B84(work, name, where);

        work->lit_mtx = DG_ZeroMatrix_8009D430;
        work->lit_mdl = s01a_lit_mdl_800E2C88(&work->lit_mtx, work->height, work->f272, 500);
    }

    return &work->actor;
}
