#include "common.h"
#include "Game/object.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"

typedef struct _DemokageWork
{
    GV_ACT   actor;  // 0
    OBJECT  *parent; // 20
    DG_PRIM *prim;   // 24
    SVECTOR  f28[4]; // 28
    SVECTOR  f48;    // 48
    int     *f50;    // 50
    int     *f54;    // 54
} DemokageWork;

// Enemy/demokage.c
const char aShadow[] = "shadow";
const char aDemokageC[] = "demokage.c";

extern SVECTOR DG_ZeroVector_800AB39C;

#define EXEC_LEVEL 5

int d11c_800C425C(int a, int b, int c)
{
    int max;

    max = __max(a, b);
    max = __max(max, c);

    return max;
}

int d11c_800C4284(int a, int b, int c)
{
    int min;

    min = __min(a, b);
    min = __min(min, c);

    return min;
}

int d11c_800C42AC(SVECTOR *vec1, SVECTOR *vec2)
{
    SVECTOR diff;

    GV_SubVec3_80016D40(vec1, vec2, &diff);
    return GV_VecDir2_80016EF8(&diff);
}

void d11c_800C42D4(DemokageWork *work)
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
        dist = GV_DiffVec3_80016E84(&sp10[0], &sp10[i]);
        yaw = d11c_800C42AC(&sp10[0], &sp10[i]);
        GV_DirVec2_80016F24(yaw - *work->f50, dist, &sp10[i]);
    }

    tmp = d11c_800C425C(sp10[1].vz, sp10[2].vz, sp10[3].vz);
    z = (tmp - d11c_800C4284(sp10[1].vz, sp10[2].vz, sp10[3].vz)) / 2;

    tmp = d11c_800C425C(sp10[1].vx, sp10[2].vx, sp10[3].vx);
    x = (tmp - d11c_800C4284(sp10[1].vx, sp10[2].vx, sp10[3].vx)) / 2;

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

void d11c_800C44F8(DemokageWork *work)
{
    SVECTOR vec;

    vec = DG_ZeroVector_800AB39C;
    vec.vy = *work->f50;

    RotMatrixYXZ(&vec, &work->prim->world);

    work->prim->world.t[0] = work->parent->objs->world.t[0];
    work->prim->world.t[2] = work->parent->objs->world.t[2];
    work->prim->world.t[1] = *work->f54;
}

void d11c_800C45AC(DemokageWork *work)
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

void d11c_800C4630(DemokageWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

int d11c_800C466C(DemokageWork *work, OBJECT *parent, SVECTOR arg2, int *arg3, int *arg4, char r, char g, char b, int unused)
{
    DG_PRIM  *prim;
    DG_TEX   *tex;
    int       i;
    POLY_FT4 *poly;
    int       x, y, w, h;
    SVECTOR  *vec;

    work->prim = DG_GetPrim(0x12, 1, 0, work->f28, NULL);
    prim = work->prim;
    if (!prim)
    {
        return -1;
    }

    prim->group_id = 0;

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC(aShadow));
    if (!tex)
    {
        return -1;
    }

    for (i = 0; i < 2; i++)
    {
        poly = &prim->field_40_pBuffers[i]->poly_ft4;

        setPolyFT4(poly);
        setSemiTrans(poly, 1);

        setRGB0(poly, r, g, b);

        x = tex->field_8_offx;
        w = tex->field_A_width;
        y = tex->field_9_offy;
        h = tex->field_B_height;
        setUVWH(poly, x, y, w, h);

        poly->tpage = tex->field_4_tPage;
        poly->clut = tex->field_6_clut;
    }

    vec = work->f28;
    for (i = 0; i < 4; vec++, i++)
    {
        *vec = DG_ZeroVector_800AB39C;
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

GV_ACT *d11c_800C48A4(OBJECT *parent, SVECTOR arg1, int *arg2, int *arg3, char r, char g, char b, int unused)
{
    DemokageWork *work;

    work = (DemokageWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(DemokageWork));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)d11c_800C45AC, (TActorFunction)d11c_800C4630, aDemokageC);

    if (d11c_800C466C(work, parent, arg1, arg2, arg3, r, g, b, unused) < 0)
    {
        GV_DestroyActor_800151C8(&work->actor);
        return NULL;
    }

    return &work->actor;
}
