#include "common.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/camera.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/object.h"

typedef struct _BoxallWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT_NO_ROTS object;
    MATRIX         light[2];
    int            f100;
    int            f104;
    LINE_F4        line[2];
    DG_PRIM       *prim;
    SVECTOR        verts[4];
    int            proc;
} BoxallWork;

extern int       GV_Clock_800AB920;
extern CONTROL  *GM_PlayerControl_800AB9F4;
extern SVECTOR   GM_PlayerPosition_800ABA10;
extern GM_Camera GM_Camera_800B77E8;

#define EXEC_LEVEL 5

int Boxall_800C9780(SVECTOR *out, SVECTOR *in)
{
    int     z;
    MATRIX *m;

    m = &DG_Chanl(0)->field_10_eye_inv;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);
    gte_ldv0(in);
    gte_rtps();
    gte_stsxy(out);

    gte_stsz(&z);
    return z > 0;
}

void Boxall_800C9800(BoxallWork *work)
{
    SVECTOR  world;
    SVECTOR  pos;
    SVECTOR *mov;
    int      dx, dz;
    char    *ot;
    LINE_F4 *line;
    int      x, y;

    if (GM_Camera_800B77E8.field_22 == 0)
    {
        work->f104 = 0;
        return;
    }

    mov = &work->control.mov;

    dx = GM_PlayerControl_800AB9F4->mov.vx - mov->vx;
    if (dx < 0)
    {
        dx = -dx;
    }

    dz = GM_PlayerControl_800AB9F4->mov.vz - mov->vz;
    if (dz < 0)
    {
        dz = -dz;
    }

    if (dx >= 2000 || dz >= 2000)
    {
        return;
    }

    if ((work->f104++ % 60) < 21)
    {
        return;
    }

    ot = DG_ChanlOTag(1);
    line = &work->line[GV_Clock_800AB920];

    pos = work->control.mov;
    pos.vy += 250;

    if (!Boxall_800C9780(&world, &pos))
    {
        return;
    }

    x = world.vx + 160;
    y = world.vy + 104;

    if (y < -32 || y > 300)
    {
        return;
    }

    y = __max(y, 32);
    y = __min(y, 224);

    line->x2 = line->x1 = x + 16;
    line->y2 = line->y1 = y - 16;
    line->x0 = x;
    line->y0 = y;
    line->y3 = y - 23;

    addPrim(ot, line);

    MENU_Color_80038B4C(200, 200, 200);
    MENU_Locate_80038B34(line->x1 + 5, line->y1 - 8, 0x10);
    MENU_Printf_80038C38("SNAKE'S ITEMS");

    MENU_Color_80038B4C(1, 1, 1);
    MENU_Locate_80038B34(line->x1 + 6, line->y1 - 7, 0x10);
    line->x2 = line->x3 = MENU_Printf_80038C38("SNAKE'S ITEMS") + 3;
}

static inline void BoxallDrawMessage(short *x, short *y, char *message)
{
    MENU_Color_80038B4C(255, 255, 255);
    MENU_Locate_80038B34(*x + 160, *y + 104, 0x12);
    MENU_Printf_80038C38(message);

    MENU_Color_80038B4C(1, 1, 1);
    MENU_Locate_80038B34(*x + 161, *y + 105, 0x12);
    MENU_Printf_80038C38(message);

    menu_Text_Init_80038B98();
}

void Boxall_800C9A48(BoxallWork *work)
{
    SVECTOR pos;
    MATRIX *m;

    m = &DG_Chanl(0)->field_10_eye_inv;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);
    gte_ldv0(&work->control.mov);
    gte_rtps();
    gte_stsxy(&pos);

    if (work->f100 < 16)
    {
        pos.vy -= work->f100;
    }
    else
    {
        pos.vy -= 16;
    }

    if (work->f100 == 2)
    {
        GM_SeSet2_80032968(0, 63, 22);
    }

    BoxallDrawMessage(&pos.vx, &pos.vy, "SNAKE'S ITEMS");
}

int Boxall_800C9B94(BoxallWork *work)
{
    SVECTOR diff;
    SVECTOR pos;
    SVECTOR player;
    int     dist;
    int     py, y, dy;

    pos = work->control.mov;
    pos.vy = 0;

    player = GM_PlayerPosition_800ABA10;
    player.vy = 0;

    GV_SubVec3_80016D40(&pos, &player, &diff);
    dist = GV_VecLen3_80016D80(&diff);

    py = GM_PlayerPosition_800ABA10.vy;
    y = work->control.mov.vy;

    dy = py - y;
    if (dy < 0)
    {
        dy = y - py;
    }

    return dist < 500 && dy < 1000;
}

void BoxallAct_800C9C58(BoxallWork *work)
{
    if (work->f100 > 0)
    {
        if (++work->f100 < 20)
        {
            Boxall_800C9A48(work);
        }
        else
        {
            GV_DestroyActor_800151C8(&work->actor);
        }
    }
    else
    {
        GM_ActControl_80025A7C(&work->control);
        GM_ActObject2_80034B88((OBJECT *)&work->object);
        DG_GetLightMatrix_8001A3C4(&work->control.mov, work->light);

        work->control.turn.vy += 64;
        work->control.turn.vy &= 4095;

        Boxall_800C9800(work);

        if (Boxall_800C9B94(work))
        {
            work->f100++;
            DG_InvisibleObjs(work->object.objs);
            GCL_ExecProc_8001FF2C(work->proc, NULL);
        }
    }
}

void BoxallDie_800C9D34(BoxallWork *work)
{
    DG_PRIM *prim;

    GM_FreeControl_800260CC(&work->control);
    GM_FreeObject_80034BF8((OBJECT *)&work->object);

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

int Boxall_800C9D84(BoxallWork *work)
{
    int       k500;
    DG_PRIM  *prim;
    DG_TEX   *tex;
    int       i, j;
    POLY_FT4 *poly;
    int       x, y, w, h;
    SVECTOR  *verts;

    k500 = 250;

    prim = DG_GetPrim(0x12, 1, 0, work->verts, NULL);
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = k500;

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("shadow"));
    if (tex == NULL)
    {
        return -1;
    }

    for (i = 0; i < 2; i++)
    {
        poly = &prim->packs[i]->poly_ft4;

        setPolyFT4(poly);
        setSemiTrans(poly, 1);
        setRGB0(poly, 72, 72, 72);

        x = tex->field_8_offx;
        w = tex->field_A_width;
        y = tex->field_9_offy;
        h = tex->field_B_height;
        setUVWH(poly, x, y, w, h);

        poly->tpage = tex->field_4_tPage;
        poly->clut = tex->field_6_clut;
    }

    verts = work->verts;
    verts[0].vx = -500;
    verts[0].vy = 0;
    verts[0].vz = -500;
    verts[1].vx = 500;
    verts[1].vy = 0;
    verts[1].vz = -500;
    verts[2].vx = -500;
    verts[2].vy = 0;
    verts[2].vz = 500;
    verts[3].vx = 500;
    verts[3].vy = 0;
    verts[3].vz = 500;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            prim->world.m[i][j] = (i == j) ? 4096 : 0;
        }
    }

    prim->world.t[0] = work->control.mov.vx;
    prim->world.t[1] = work->control.mov.vy;
    prim->world.t[2] = work->control.mov.vz;
    prim->world.t[1] = 0;

    work->prim = prim;
    return 0;
}

int BoxallGetResources_800C9F58(BoxallWork *work, int name, int map)
{
    CONTROL        *control;
    char           *pos, *dir;
    unsigned short  model;
    OBJECT_NO_ROTS *object;
    int             i;

    control = &work->control;
    if (GM_InitLoader_8002599C(control, name, map) < 0)
    {
        return -1;
    }

    pos = GCL_GetOption_80020968('p');
    dir = GCL_GetOption_80020968('d');
    GM_ConfigControlString_800261C0(control, pos, dir);
    GM_ConfigControlHazard_8002622C(control, 500, -2, -2);

    model = GCL_StrToInt_800209E8(GCL_GetOption_80020968('m'));
    work->proc = GCL_StrToInt_800209E8(GCL_GetOption_80020968('e'));

    object = &work->object;
    GM_InitObjectNoRots_800349B0(object, model, WEAPON_FLAG, 0);
    GM_ConfigObjectLight_80034C44((OBJECT *)object, work->light);

    work->f100 = 0;
    work->f104 = 0;

    for (i = 0; i < 2; i++)
    {
        setLineF4(&work->line[i]);
        setRGB0(&work->line[i], 255, 255, 255);
    }

    if (Boxall_800C9D84(work) < 0)
    {
        return -1;
    }

    return 0;
}

GV_ACT * NewBoxall_800CA088(int name, int where)
{
    BoxallWork *work;

    work = (BoxallWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(BoxallWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)BoxallAct_800C9C58, (TActorFunction)BoxallDie_800C9D34, "boxall.c");

        if (BoxallGetResources_800C9F58(work, name, where) >= 0)
        {
            return &work->actor;
        }

        GV_DestroyActor_800151C8(&work->actor);
    }

    return NULL;
}
