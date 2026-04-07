#include "demokage.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct _Work
{
    GV_ACT   actor;
    OBJECT  *parent;
    DG_PRIM *prim;
    SVECTOR  f28[4];
    SVECTOR  f48;
    int     *f50;
    int     *f54;
} Work;

/*---------------------------------------------------------------------------*/

static int Max3(int a, int b, int c)
{
    int max;

    max = MAX(a, b);
    max = MAX(max, c);

    return max;
}

static int Min3(int a, int b, int c)
{
    int min;

    min = MIN(a, b);
    min = MIN(min, c);

    return min;
}

static int d11c_800C42AC(SVECTOR *vec1, SVECTOR *vec2)
{
    SVECTOR diff;

    GV_SubVec3(vec1, vec2, &diff);
    return GV_VecDir2(&diff);
}

static void d11c_800C42D4(Work *work)
{
    SVECTOR  sp10[4];
    SVECTOR *vec;
    short   *index;
    int      i;
    DG_OBJ  *obj;
    int      dist;
    int      yaw;
    int      tmp;
    int      x, z;
    SVECTOR *vec2;

    vec = sp10;
    index = (short *)&work->f48;
    for (i = 0; i < 4; i++, vec++, index++)
    {
        obj = &work->parent->objs->objs[*index];
        vec->vx = obj->world.t[0];

        obj = &work->parent->objs->objs[*index];
        vec->vy = obj->world.t[1];

        obj = &work->parent->objs->objs[*index];
        vec->vz = obj->world.t[2];

        vec->vy = 0;
    }

    for (i = 1; i < 4; i++)
    {
        dist = GV_DiffVec3(&sp10[0], &sp10[i]);
        yaw = d11c_800C42AC(&sp10[0], &sp10[i]);
        GV_DirVec2(yaw - *work->f50, dist, &sp10[i]);
    }

    tmp = Max3(sp10[1].vz, sp10[2].vz, sp10[3].vz);
    z = (tmp - Min3(sp10[1].vz, sp10[2].vz, sp10[3].vz)) / 2;

    tmp = Max3(sp10[1].vx, sp10[2].vx, sp10[3].vx);
    x = (tmp - Min3(sp10[1].vx, sp10[2].vx, sp10[3].vx)) / 2;

    vec2 = work->f28;

    if (z > 500)
    {
        x += 100;

        work->f28[2].vx = -x;
        work->f28[0].vx = -x;
        work->f28[3].vx = x;
        vec2[1].vx = x;

        work->f28[1].vz = 10 - z;
        vec2[0].vz = 10 - z;
        work->f28[3].vz = z + 50;
        vec2[2].vz = z + 50;
    }
    else
    {
        x += 200;
        z += 200;

        work->f28[2].vx = -x;
        work->f28[0].vx = -x;
        work->f28[3].vx = x;
        vec2[1].vx = x;

        work->f28[1].vz = -z;
        vec2[0].vz = -z;
        work->f28[3].vz = z;
        vec2[2].vz = z;
    }
}

static void d11c_800C44F8(Work *work)
{
    SVECTOR vec;

    vec = DG_ZeroVector;
    vec.vy = *work->f50;

    RotMatrixYXZ(&vec, &work->prim->world);

    work->prim->world.t[0] = work->parent->objs->world.t[0];
    work->prim->world.t[2] = work->parent->objs->world.t[2];
    work->prim->world.t[1] = *work->f54;
}

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    if (work->parent->objs->flag & DG_FLAG_INVISIBLE)
    {
        DG_InvisiblePrim(work->prim);
    }
    else
    {
        DG_VisiblePrim(work->prim);

        d11c_800C42D4(work);
        d11c_800C44F8(work);
    }
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, OBJECT *parent, SVECTOR arg2, int *arg3, int *arg4, char r, char g, char b, int unused)
{
    DG_PRIM  *prim;
    DG_TEX   *tex;
    int       i;
    POLY_FT4 *poly;
    SVECTOR  *vec;

    work->prim = GM_MakePrim(DG_PRIM_POLY_FT4, 1, work->f28, NULL);
    prim = work->prim;
    if (!prim)
    {
        return -1;
    }

    prim->group_id = 0;

    tex = DG_GetTexture(GV_StrCode("shadow"));
    if (!tex)
    {
        return -1;
    }

    for (i = 0; i < 2; i++)
    {
        poly = prim->packs[i];

        setPolyFT4(poly);
        setSemiTrans(poly, 1);
        setRGB0(poly, r, g, b);
        DG_SetPacketTexture4(poly, tex);
    }

    vec = work->f28;
    for (i = 0; i < 4; vec++, i++)
    {
        *vec = DG_ZeroVector;
        vec->vx = (i & 1) ? 400 : -400;
        vec->vz = (i & 2) ? 400 : -400;
    }

    work->prim->world.t[0] = 0;
    work->prim->world.t[1] = -31000;
    work->prim->world.t[2] = 0;

    work->parent = parent;
    work->f48 = arg2;
    work->f50 = arg3;
    work->f54 = arg4;

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewDemoKage(OBJECT *parent, SVECTOR arg1, int *arg2, int *arg3, char r, char g, char b, int unused)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, Act, Die, "demokage.c");

    if (GetResources(work, parent, arg1, arg2, arg3, r, g, b, unused) < 0)
    {
        GV_DestroyActor(&work->actor);
        return NULL;
    }

    return (void *)work;
}
