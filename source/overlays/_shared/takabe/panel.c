#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "takabe/thing.h"
#include "sd/g_sound.h"

typedef struct _PanelWork
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    DG_TEX  *tex;
    SVECTOR  verts[4];
    TARGET  *target;
    SVECTOR  pos;
    SVECTOR  normal;
    MATRIX   world;
    int      f80;
    short    f84;
    short    f86;
    short    f88;
    short    f8A;
} PanelWork;

int panel_base_color = 0x3C808080;

void AN_Unknown_800DCE84(SVECTOR *pos);
void *NewSpark2_800CA714(MATRIX *world);

#define EXEC_LEVEL GV_ACTOR_LEVEL5

void PanelTexPack_800D1BD0(POLY_GT4 *pack, DG_TEX *tex, int size, PanelWork *work)
{
    int x, y, w, h;
    int x2, y2, w2, h2;
    int x3, y3, w3, h3;

    setPolyGT4(pack);

    if (work->f8A != 0)
    {
        if (work->f88 == 0)
        {
            x = tex->off_x;
            w = tex->w + 1;
            pack->u0 = pack->u2 = x + (w * size) / 2;
            pack->u1 = pack->u3 = x + (w * (size + 1)) / 2 - 1;

            y = tex->off_y;
            h = tex->h;
            pack->v0 = pack->v1 = y;
            pack->v2 = pack->v3 = h + y;
        }
        else
        {
            x2 = tex->off_x;
            w2 = tex->w;
            pack->u0 = pack->u2 = x2;
            pack->u1 = pack->u3 = w2 + x2;

            y2 = tex->off_y;
            h2 = tex->h + 1;
            pack->v0 = pack->v1 = y2 + (h2 * size) / 2;
            pack->v2 = pack->v3 = y2 + (h2 * (size + 1)) / 2 - 1;
        }
    }
    else
    {
        x3 = tex->off_x;
        w3 = tex->w;
        y3 = tex->off_y;
        h3 = tex->h;
        setUVWH(pack, x3, y3, w3, h3);
    }

    pack->tpage = tex->tpage;
    pack->clut = tex->clut;
}

void PanelLightPacks_800D1D54(POLY_GT4 *pack0, POLY_GT4 *pack1, SVECTOR *pos, SVECTOR *normal)
{
    MATRIX light[2];
    int    color[4];
    int    i;

    gte_ldrgb(&panel_base_color);
    gte_ldv0(normal);

    for (i = 0; i < 4; i++)
    {
        DG_GetLightMatrix(pos, light);
        SetLightMatrix(&light[0]);
        SetColorMatrix(&light[1]);
        gte_nccs();
        pos++;
        gte_strgb(&color[i]);
    }

    LSTORE(color[0], &pack0->r0);
    LSTORE(color[0], &pack1->r0);
    LSTORE(color[1], &pack0->r1);
    LSTORE(color[1], &pack1->r1);
    LSTORE(color[2], &pack0->r2);
    LSTORE(color[2], &pack1->r2);
    LSTORE(color[3], &pack0->r3);
    LSTORE(color[3], &pack1->r3);
}

void PanelAct_800D1E58(PanelWork *work)
{
    TARGET  *target;
    DG_PRIM *prim;

    if (work->f8A == 0)
    {
        return;
    }

    GM_CurrentMap = work->map;

    target = work->target;
    if ((target->damaged & TARGET_POWER) && (work->f86 == 0))
    {
        target->damaged &= ~TARGET_POWER;
        target->field_2C_vec = DG_ZeroVector;

        PanelTexPack_800D1BD0(&work->prim->packs[0]->poly_gt4, work->tex, 1, work);
        PanelTexPack_800D1BD0(&work->prim->packs[1]->poly_gt4, work->tex, 1, work);

        AN_Unknown_800DCE84(&work->pos);
        NewSpark2_800CA714(&work->world);
        GM_SeSet(&work->pos, SE_ELECTRIC_PANEL);

        work->f86 = 1;
    }

    target->damaged &= ~TARGET_PUSH;
    GM_MoveTarget(target, &work->pos);

    if (work->f80 == 0)
    {
        prim = work->prim;
        PanelLightPacks_800D1D54(&prim->packs[0]->poly_gt4, &prim->packs[1]->poly_gt4, work->verts, &work->normal);
        work->f80++;
    }
}

void PanelDie_800D1F98(PanelWork *work)
{
    TARGET  *target;

    target = work->target;
    if (target != NULL)
    {
        GM_FreeTarget(target);
    }

    GM_FreePrim(work->prim);
}

void PanelCreateTarget_800D1FF0(PanelWork *work)
{
    SVECTOR size;
    int     i;
    int     x, y, z;
    TARGET *target;

    size.vx = 150;
    size.vy = 150;
    size.vz = 150;

    for (i = 0; i < 4; i++)
    {
        x = work->verts[i].vx - work->pos.vx;
        if (x > size.vx)
        {
            size.vx = x;
        }

        y = work->verts[i].vy - work->pos.vy;
        if (y > size.vy)
        {
            size.vy = y;
        }

        z = work->verts[i].vz - work->pos.vz;
        if (z > size.vz)
        {
            size.vz = z;
        }
    }

    target = GM_AllocTarget();
    work->target = target;

    target->field_2C_vec = DG_ZeroVector;

    GM_SetTarget(target, (TARGET_SEEK | TARGET_POWER), NO_SIDE, &size);
    GM_Target_8002DCCC(target, 1, -1, 2, 0, &DG_ZeroVector);
}

int PanelGetResources_800D210C(PanelWork *work, int name, int map)
{
    VECTOR   e12;
    VECTOR   e01;
    VECTOR   normal;
    SVECTOR  rot;
    SVECTOR  in;
    SVECTOR  out;
    SVECTOR  tmp;
    char    *opt;
    SVECTOR *iter;
    int      i;
    SVECTOR *verts;
    DG_PRIM *prim;
    int      texid;
    DG_TEX  *tex;
    int      rotate;

    GM_CurrentMap = map;

    e12.vx = 0;
    e12.vy = 0;
    e12.vz = 0;

    opt = GCL_GetOption('p');
    if (opt)
    {
        iter = work->verts;
        for (i = 0; i < 4; i++)
        {
            GCL_StrToSV(opt, iter);

            e12.vx += iter->vx;
            e12.vy += iter->vy;
            e12.vz += iter->vz;

            opt = GCL_GetParamResult();
            iter++;
        }
    }

    work->pos.vx = e12.vx / 4;
    work->pos.vy = e12.vy / 4;
    work->pos.vz = e12.vz / 4;

    verts = work->verts;
    prim = DG_GetPrim(DG_PRIM_POLY_GT4, 1, 0, verts, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    texid = THING_Gcl_GetShortDefault('t', GV_StrCode("moni_d"));
    tex = DG_GetTexture(texid);
    work->tex = tex;
    if (tex == NULL)
    {
        return -1;
    }

    work->f8A = THING_Gcl_GetIntDefault('h', 1);
    work->f88 = THING_Gcl_GetIntDefault('m', 0);
    work->f86 = THING_Gcl_GetIntDefault('b', 0);

    PanelTexPack_800D1BD0(&work->prim->packs[0]->poly_gt4, tex, work->f86, work);
    PanelTexPack_800D1BD0(&work->prim->packs[1]->poly_gt4, tex, work->f86, work);

    e01.vx = verts[1].vx - verts[0].vx;
    e01.vy = verts[1].vy - verts[0].vy;
    e01.vz = verts[1].vz - verts[0].vz;
    e12.vx = verts[2].vx - verts[1].vx;
    e12.vy = verts[2].vy - verts[1].vy;
    e12.vz = verts[2].vz - verts[1].vz;
    OuterProduct0(&e12, &e01, &normal);

    rot = DG_ZeroVector;
    rot.vy = ratan2(normal.vx, normal.vz);
    rot.vx = 200;

    normal.vx /= 64;
    normal.vy /= 64;
    normal.vz /= 64;

    VectorNormalS(&normal, &work->normal);
    work->normal.vx = -work->normal.vx;
    work->normal.vy = -work->normal.vy;
    work->normal.vz = -work->normal.vz;

    PanelLightPacks_800D1D54(&work->prim->packs[0]->poly_gt4, &work->prim->packs[1]->poly_gt4, verts, &work->normal);

    RotMatrix(&rot, &work->world);
    work->world.t[0] = work->pos.vx;
    work->world.t[1] = work->pos.vy;
    work->world.t[2] = work->pos.vz;

    in.vx = 0;
    in.vy = 0;
    in.vz = -300;

    DG_SetPos(&work->world);
    DG_PutVector(&in, &out, 1);
    work->world.t[0] = out.vx;
    work->world.t[1] = out.vy;
    work->world.t[2] = out.vz;

    rotate = THING_Gcl_GetInt('r');
    if (rotate & 1)
    {
        tmp = work->verts[0];
        work->verts[0] = work->verts[1];
        work->verts[1] = tmp;

        tmp = work->verts[2];
        work->verts[2] = work->verts[3];
        work->verts[3] = tmp;
    }

    if (rotate & 2)
    {
        tmp = work->verts[0];
        work->verts[0] = work->verts[2];
        work->verts[2] = tmp;

        tmp = work->verts[1];
        work->verts[1] = work->verts[3];
        work->verts[3] = tmp;
    }

    if (work->f8A != 0)
    {
        PanelCreateTarget_800D1FF0(work);
    }
    else
    {
        work->target = NULL;
    }

    return 0;
}

void *NewPanel_800D2680(int name, int where)
{
    PanelWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(PanelWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, PanelAct_800D1E58, PanelDie_800D1F98, "panel.c");

        if (PanelGetResources_800D210C(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->f86 = 0;
        work->f84 = 3;
        work->map = where;
        work->f80 = 0;
    }

    return (void *)work;
}
