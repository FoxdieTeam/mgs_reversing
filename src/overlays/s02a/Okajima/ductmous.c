#include "ductmous.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"
#include "Game/object.h"
#include "SD/g_sound.h"

typedef struct _DuctmouseWork
{
    GV_ACT   actor;
    OBJECT   body;
    MATRIX   light[2];
    DG_PRIM *prim;
    SVECTOR  pos;
    SVECTOR  rot;
    int      map;
    int      f15C;
    int      f160[8];
    int      f180;
    int      f184;
    int      f188;
    char     pad[0x4];
    int      n_points;
    SVECTOR  points[32];
    int      f294;
    SVECTOR  vec[4];
    MATRIX   world;
} DuctmouseWork;

SVECTOR mouse_offsets[2] = {{48, 0, 96, 0}, {-48, 0, 96, 0}};

extern MATRIX  DG_ZeroMatrix;
extern SVECTOR DG_ZeroVector;
extern int     GM_CurrentMap_800AB9B0;
extern SVECTOR GM_PlayerPosition_800ABA10;

void AN_Unknown_800CA458(MATRIX *, int);

#define EXEC_LEVEL 5

int Ductmouse_800DA2EC(SVECTOR *a, SVECTOR *b)
{
    int dx, dy, dz;

    dx = (a->vx - b->vx) >> 4;
    dy = (a->vy - b->vy) >> 4;
    dz = (a->vz - b->vz) >> 4;
    return SquareRoot0(dx * dx + dy * dy + dz * dz) * 16;
}

void Ductmouse_800DA35C(SVECTOR *from, SVECTOR *to, SVECTOR *out)
{
    SVECTOR diff;
    int     y;

    GV_SubVec3(to, from, &diff);
    out->vy = ratan2(diff.vx, diff.vz) & 0xFFF;

    y = diff.vy;
    diff.vy = 0;

    out->vx = (ratan2(GV_VecLen3(&diff), y) & 0xFFF) - 1024;
    out->vz = 0;
}

void Ductmouse_800DA3DC(DuctmouseWork *work)
{
    SVECTOR  pos;
    SVECTOR  off[2];
    MATRIX   rot;
    SVECTOR *vec;

    pos = work->pos;
    rot = DG_ZeroMatrix;

    vec = work->vec;

    RotMatrixYXZ_gte(&work->rot, &rot);
    DG_SetPos(&rot);
    DG_PutVector(mouse_offsets, off, 2);

    vec[0].vx = pos.vx + off[0].vx;
    vec[3].vx = pos.vx - off[0].vx;
    vec[0].vz = pos.vz + off[0].vz;
    vec[3].vz = pos.vz - off[0].vz;
    vec[1].vx = pos.vx + off[1].vx;
    vec[2].vx = pos.vx - off[1].vx;
    vec[1].vz = pos.vz + off[1].vz;
    vec[2].vz = pos.vz - off[1].vz;
    vec[0].vy = work->vec[1].vy = work->vec[2].vy = work->vec[3].vy = pos.vy;
}

void Ductmouse_800DA55C(POLY_FT4 *poly, DG_TEX *tex)
{
    int x, y, w, h;

    setPolyFT4(poly);
    setSemiTrans(poly, 1);

    x = tex->off_x;
    w = tex->w;
    y = tex->off_y;
    h = tex->h;
    setUVWH(poly, x, y, w, h);

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}

void Ductmouse_800DA5BC(DuctmouseWork *work)
{
    SVECTOR sp10;
    SVECTOR sp18;
    SVECTOR sp20;
    SVECTOR sp28;
    int     len;
    int     z;

    sp10 = work->pos;
    sp18 = work->points[work->f294];

    work->f15C++;

    len = Ductmouse_800DA2EC(&work->pos, &GM_PlayerPosition_800ABA10);

    Ductmouse_800DA3DC(work);

    DG_SetPos2(&work->pos, &work->rot);
    ReadRotMatrix(&work->world);

    sp28.vx = 0;
    sp28.vy = 0;
    sp28.vz = 100;

    DG_PutVector(&sp28, &sp28, 1);

    work->world.t[0] = sp28.vx;
    work->world.t[1] = sp28.vy;
    work->world.t[2] = sp28.vz;

    z = 0;

    if (work->pos.vy < -50)
    {
        z = 200;
    }
    else if (work->f188 >= 0)
    {
        if (work->f188 == 2)
        {
            GM_SeSet_80032858(&work->pos, SE_MOUSE_STEP);
        }

        work->f188--;

        Ductmouse_800DA35C(&sp10, &GM_PlayerPosition_800ABA10, &work->rot);
        work->rot.vy -= 512;
        return;
    }
    else if (work->f184 <= 0)
    {
        if (len < 2000)
        {
            GM_SeSet2_80032968(0, 127, 183);
            AN_Unknown_800CA458(&work->world, 0);
            work->f188 = 0x28;
            work->f184 = GV_RandU(32) + 25;
        }
        else if (len > 4000)
        {
            if (GV_RandU(512) == 0)
            {
                GM_SeSet_80032858(&work->pos, SE_MOUSE_STEP);
                work->rot.vy += work->f160[work->f15C % 8] * 32;
            }

            return;
        }
        else if (--work->f180 < 0)
        {
            GM_SeSet_80032858(&work->pos, SE_MOUSE_STEP);
            work->f180 = GV_RandU(512) + 256;
            z = GV_RandU(8) + 8;
            work->f184 = GV_RandU(4) + 2;
        }
        else
        {
            return;
        }
    }
    else
    {
        z = 80;
        work->f184--;
    }

    if (Ductmouse_800DA2EC(&sp10, &sp18) < z)
    {
        work->pos = sp18;

        if (++work->f294 >= work->n_points)
        {
            GV_DestroyActor(&work->actor);
        }
    }
    else
    {
        Ductmouse_800DA35C(&sp10, &sp18, &work->rot);

        sp20 = DG_ZeroVector;
        sp20.vz = z;

        DG_SetPos2(&sp10, &work->rot);
        DG_PutVector(&sp20, &sp20, 1);

        work->pos = sp20;
    }

    work->rot.vy += work->f160[work->f15C % 8] * 64;
}

void DuctmouseAct_800DA978(DuctmouseWork *work)
{
    GM_CurrentMap_800AB9B0 = work->map;

    Ductmouse_800DA5BC(work);

    DG_SetPos2(&work->pos, &work->rot);
    GM_ActObject2(&work->body);
    DG_GetLightMatrix2(&work->pos, work->light);
}

void DuctmouseDie_800DA9D4(DuctmouseWork *work)
{
    DG_PRIM *prim;

    GM_FreeObject(&work->body);

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

int DuctmouseGetResources_800DAA1C(DuctmouseWork *work, int name, int where)
{
    MAP        *map;
    char       *opt;
    int         route_index;
    HZD_HEADER *hzd;
    HZD_PAT    *route;
    HZD_PTP    *point;
    int         i;
    OBJECT     *body;
    DG_PRIM    *prim;
    DG_TEX     *tex;

    work->map = where;

    map = Map_FromId_800314C0(where);

    opt = GCL_GetOption('r');
    if (opt != 0)
    {
        route_index = GCL_StrToInt(opt);
    }
    else
    {
        route_index = 0;
    }

    hzd = map->hzd->f00_header;

    if ((route_index + 1) > hzd->n_routes)
    {
        route_index = 0;
    }

    route = &hzd->routes[route_index];

    work->n_points = route->n_points;
    if (work->n_points <= 0)
    {
        return -1;
    }

    if (work->n_points >= 32)
    {
        return -1;
    }

    point = route->points;
    for (i = 0; i < work->n_points; i++)
    {
        work->points[i].vx = point->x;
        work->points[i].vy = point->y;
        work->points[i].vz = point->z;
        point++;
    }

    work->pos = work->points[0];

    body = &work->body;
    GM_InitObject(body, GV_StrCode("mouse"), BODY_FLAG | DG_FLAG_ONEPIECE, 0);
    GM_ConfigObjectJoint(body);
    GM_ConfigObjectLight(body, work->light);
    body->objs->objs[0].raise = 200;

    prim = DG_GetPrim(DG_PRIM_POLY_FT4, 1, 0, work->vec, NULL);
    work->prim = prim;
    if (prim != NULL)
    {
        prim->field_2E_k500 = 500;
    }

    tex = DG_GetTexture(GV_StrCode("shadow"));
    if (tex == NULL)
    {
        return 0;
    }

    Ductmouse_800DA55C(&work->prim->packs[0]->poly_ft4, tex);
    Ductmouse_800DA55C(&work->prim->packs[1]->poly_ft4, tex);

    work->prim->packs[0]->poly_ft4.r0 = 80;
    work->prim->packs[0]->poly_ft4.g0 = 80;
    work->prim->packs[0]->poly_ft4.b0 = 80;

    work->prim->packs[1]->poly_ft4.r0 = 80;
    work->prim->packs[1]->poly_ft4.g0 = 80;
    work->prim->packs[1]->poly_ft4.b0 = 80;

    work->f180 = 0;
    work->f294 = 1;

    work->f160[0] = 0;
    work->f160[1] = 1;
    work->f160[2] = 2;
    work->f160[3] = 1;
    work->f160[4] = 0;
    work->f160[5] = -1;
    work->f160[6] = -2;
    work->f160[7] = -1;

    work->f180 = GV_RandU(256) + 128;

    return 0;
}

GV_ACT *NewDuctmouse_800DACC8(int name, int where, int argc, char **argv)
{
    DuctmouseWork *work;

    work = (DuctmouseWork *)GV_NewActor(EXEC_LEVEL, sizeof(DuctmouseWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)DuctmouseAct_800DA978, (TActorFunction)DuctmouseDie_800DA9D4, "ductmous.c");

        if (DuctmouseGetResources_800DAA1C(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
