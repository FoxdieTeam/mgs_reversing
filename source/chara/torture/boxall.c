#include "boxall.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "sound/g_sound.h"

typedef struct _BoxallWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT_NO_ROTS body;
    MATRIX         light[2];
    int            timer;
    int            f104;
    LINE_F4        text_line[2];
    DG_PRIM       *prim;
    SVECTOR        vertices[4];
    int            proc_id;
} Work;

extern GM_CAMERA GM_Camera;

#define EXEC_LEVEL GV_ACTOR_LEVEL5
#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE | DG_FLAG_ONEPIECE )

static int GetWorldPosition(SVECTOR *out, SVECTOR *in)
{
    int     z;
    MATRIX *m;

    m = &DG_Chanl(0)->eye_inv;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);
    gte_ldv0(in);
    gte_rtps();
    gte_stsxy(out);

    gte_stsz(&z);
    return z > 0;
}

static void DrawItemText(Work *work)
{
    SVECTOR  world;
    SVECTOR  pos;
    SVECTOR *mov;
    int      dx, dz;
    u_long  *ot;
    LINE_F4 *text_line;
    int      x, y;

    if (GM_Camera.first_person == 0)
    {
        work->f104 = 0;
        return;
    }

    mov = &work->control.mov;

    dx = GM_PlayerControl->mov.vx - mov->vx;
    if (dx < 0)
    {
        dx = -dx;
    }

    dz = GM_PlayerControl->mov.vz - mov->vz;
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
    text_line = &work->text_line[GV_Clock];

    pos = work->control.mov;
    pos.vy += 250;

    if (!GetWorldPosition(&world, &pos))
    {
        return;
    }

    x = world.vx + 160;
    y = world.vy + 104;

    if (y < -32 || y > 300)
    {
        return;
    }

    y = MAX(y, 32);
    y = MIN(y, FRAME_HEIGHT);

    text_line->x2 = text_line->x1 = x + 16;
    text_line->y2 = text_line->y1 = y - 16;
    text_line->x0 = x;
    text_line->y0 = y;
    text_line->y3 = y - 23;

    addPrim(ot, text_line);

    MENU_Color(200, 200, 200);
    MENU_Locate(text_line->x1 + 5, text_line->y1 - 8, 0x10);
    MENU_Printf("SNAKE'S ITEMS");

    MENU_Color(1, 1, 1);
    MENU_Locate(text_line->x1 + 6, text_line->y1 - 7, 0x10);
    text_line->x2 = text_line->x3 = MENU_Printf("SNAKE'S ITEMS") + 3;
}

static inline void DrawMessage(short *x, short *y, char *message)
{
    MENU_Color(255, 255, 255);
    MENU_Locate(*x + 160, *y + 104, 0x12);
    MENU_Printf(message);

    MENU_Color(1, 1, 1);
    MENU_Locate(*x + 161, *y + 105, 0x12);
    MENU_Printf(message);

    MENU_ResetText();
}

static void DrawItemTextCollected(Work *work)
{
    SVECTOR pos;
    MATRIX *m;

    m = &DG_Chanl(0)->eye_inv;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);
    gte_ldv0(&work->control.mov);
    gte_rtps();
    gte_stsxy(&pos);

    if (work->timer < 16)
    {
        pos.vy -= work->timer;
    }
    else
    {
        pos.vy -= 16;
    }

    if (work->timer == 2)
    {
        GM_SeSet2(0, 63, SE_ITEM_GET);
    }

    DrawMessage(&pos.vx, &pos.vy, "SNAKE'S ITEMS");
}

static int HasCollectedItem(Work *work)
{
    SVECTOR diff;
    SVECTOR pos;
    SVECTOR player;
    int     dist;
    int     py, y, dy;

    pos = work->control.mov;
    pos.vy = 0;

    player = GM_PlayerPosition;
    player.vy = 0;

    GV_SubVec3(&pos, &player, &diff);
    dist = GV_VecLen3(&diff);

    py = GM_PlayerPosition.vy;
    y = work->control.mov.vy;

    dy = py - y;
    if (dy < 0)
    {
        dy = y - py;
    }

    return dist < 500 && dy < 1000;
}

static void Act(Work *work)
{
    if (work->timer > 0)
    {
        if (++work->timer < 20)
        {
            DrawItemTextCollected(work);
        }
        else
        {
            GV_DestroyActor(&work->actor);
        }
    }
    else
    {
        GM_ActControl(&work->control);
        GM_ActObject2((OBJECT *)&work->body);
        DG_GetLightMatrix(&work->control.mov, work->light);

        work->control.turn.vy += 64;
        work->control.turn.vy &= 4095;

        DrawItemText(work);

        if (HasCollectedItem(work))
        {
            work->timer++;
            DG_InvisibleObjs(work->body.objs);
            GCL_ExecProc(work->proc_id, NULL);
        }
    }
}

static void Die(Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject((OBJECT *)&work->body);
    GM_FreePrim(work->prim);
}

static int InitPrim(Work *work)
{
    int       raise;
    DG_PRIM  *prim;
    DG_TEX   *tex;
    int       i, j;
    POLY_FT4 *poly;
    int       x, y, w, h;
    SVECTOR  *vertices;

    raise = 250;

    prim = GM_MakePrim(DG_PRIM_POLY_FT4, 1, work->vertices, NULL);
    if (prim == NULL)
    {
        return -1;
    }

    prim->raise = raise;

    tex = DG_GetTexture(GV_StrCode("shadow"));
    if (tex == NULL)
    {
        return -1;
    }

    for (i = 0; i < 2; i++)
    {
        poly = prim->packs[i];

        setPolyFT4(poly);
        setSemiTrans(poly, 1);
        setRGB0(poly, 72, 72, 72);

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;
        setUVWH(poly, x, y, w, h);

        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
    }

    vertices = work->vertices;
    vertices[0].vx = -500;
    vertices[0].vy = 0;
    vertices[0].vz = -500;
    vertices[1].vx = 500;
    vertices[1].vy = 0;
    vertices[1].vz = -500;
    vertices[2].vx = -500;
    vertices[2].vy = 0;
    vertices[2].vz = 500;
    vertices[3].vx = 500;
    vertices[3].vy = 0;
    vertices[3].vz = 500;

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

static int GetResources(Work *work, int name, int map)
{
    CONTROL        *control;
    char           *pos, *dir;
    unsigned short  model;
    OBJECT_NO_ROTS *body;
    int             i;

    control = &work->control;
    if (GM_InitControl(control, name, map) < 0)
    {
        return -1;
    }

    pos = GCL_GetOption('p');
    dir = GCL_GetOption('d');
    GM_ConfigControlString(control, pos, dir);
    GM_ConfigControlHazard(control, 500, -2, -2);

    model = GCL_StrToInt(GCL_GetOption('m'));
    work->proc_id = GCL_StrToInt(GCL_GetOption('e'));

    body = &work->body;
    GM_InitObjectNoRots(body, model, BODY_FLAG, 0);
    GM_ConfigObjectLight((OBJECT *)body, work->light);

    work->timer = 0;
    work->f104 = 0;

    for (i = 0; i < 2; i++)
    {
        setLineF4(&work->text_line[i]);
        setRGB0(&work->text_line[i], 255, 255, 255);
    }

    if (InitPrim(work) < 0)
    {
        return -1;
    }

    return 0;
}

void *NewAllItemBox(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "boxall.c");

        if (GetResources(work, name, where) >= 0)
        {
            return (void *)work;
        }

        GV_DestroyActor(&work->actor);
    }

    return NULL;
}
