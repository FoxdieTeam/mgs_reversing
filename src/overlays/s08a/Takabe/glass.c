#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/game.h"
#include "Takabe/thing.h"
#include "SD/g_sound.h"

typedef struct _GlassWork
{
    GV_ACT   actor;
    MATRIX   world;
    DG_PRIM *prim;
    DG_TEX  *tex;
    SVECTOR  verts[8];
    TARGET  *target;
    SVECTOR  pos;
    SVECTOR  dir;
    SVECTOR  size;
    short    fA4; // front?
    short    fA6; // back?
    int      n_prims;
    int      map;
    int      fB0;
    short    has_bounds;
    HZD_HDL *hzd;
    HZD_SEG  bounds[2];
    int      proc;
} GlassWork;

extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GM_CurrentMap_800AB9B0;

void s16b_800C4874(int n_segs, HZD_SEG *segs, int n_flrs, HZD_FLR *flrs);
void s16b_800C49AC(HZD_SEG *seg);

GV_ACT *NewGsplash_800D4000(MATRIX *pos, SVECTOR *arg1, short arg2, short n_prims);

#define EXEC_LEVEL 5

static inline void GlassInitPack(POLY_FT4 *poly, DG_TEX *tex, int size, int which)
{
    int x, y, w, h;

    setPolyFT4(poly);
    setSemiTrans(poly, 1);
    setRGB0(poly, 128, 128, 128);

    x = tex->off_x;
    w = tex->w + 1;
    poly->u0 = poly->u2 = x + (w * size) / 3;
    poly->u1 = poly->u3 = x + (w * (size + 1)) / 3 - 1;

    y = tex->off_y;
    h = tex->h + 1;

    if (which == 0)
    {
        poly->v0 = poly->v1 = y;
        poly->v2 = poly->v3 = y + h / 2 - 1;
    }
    else if (which == 1)
    {
        poly->v0 = poly->v1 = y + h / 2;
        poly->v2 = poly->v3 = y + h - 1;
    }

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}

void GlassInitPacks_800D2E88(POLY_FT4 *poly, DG_TEX *tex, int size)
{
    GlassInitPack(&poly[0], tex, size, 0);
    GlassInitPack(&poly[1], tex, size, 1);
}

void GlassAct_800D302C(GlassWork *work)
{
    MATRIX  world;
    SVECTOR sp30;
    TARGET *target;
    int     check;
    int     size;

    GM_CurrentMap_800AB9B0 = work->map;

    target = work->target;
    if (target->damaged & TARGET_POWER)
    {
        target->damaged &= ~TARGET_POWER;

        check = 0;
        switch (target->a_mode)
        {
        case 1:
            work->fB0--;
            check = 1;
            break;

        case 2:
            work->fB0 = 0;
            check = 1;
            break;
        }

        if (check != 0)
        {
            if (work->fB0 <= 0)
            {
                GM_SeSet_80032858(&work->pos, SE_GLASS_SHATTER);

                DG_TransposeMatrix_8001EAD8(&work->world, &world);
                gte_ApplyMatrixSV(&world, &target->field_2C_vec, &sp30);

                if (sp30.vz > 0)
                {
                    NewGsplash_800D4000(&work->world, &work->size, work->fA4, work->n_prims);
                }
                else
                {
                    world = work->world;
                    RotMatrixY(2048, &world);
                    NewGsplash_800D4000(&world, &work->size, work->fA6, work->n_prims);
                }

                if (work->proc != 0)
                {
                    GCL_ExecProc(work->proc, NULL);
                }

                s16b_800C4874(2, work->bounds, 0, NULL);

                GV_DestroyActor(&work->actor);
                return;
            }

            GM_SeSet_80032858(&work->pos, SE_BROKEN_GLASS);

            size = 3 - work->fB0;
            GlassInitPacks_800D2E88(&work->prim->packs[0]->poly_ft4, work->tex, size);
            GlassInitPacks_800D2E88(&work->prim->packs[1]->poly_ft4, work->tex, size);
        }
    }

    GM_MoveTarget_8002D500(target, &work->pos);
    GM_PushTarget_8002DA14(target);
    target->damaged &= ~TARGET_PUSH;
}

void GlassDie_800D3270(GlassWork *work)
{
    DG_PRIM* prim;

    if (work->has_bounds != 0)
    {
        HZD_DequeueDynamicSegment_8006FE44(work->hzd, &work->bounds[0]);
        HZD_DequeueDynamicSegment_8006FE44(work->hzd, &work->bounds[1]);
    }

    GM_FreeTarget_8002D4B0(work->target);

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

void GlassCreateTarget_800D32E4(GlassWork *work, SVECTOR *size)
{
    TARGET *target;

    target = GM_AllocTarget_8002D400();
    work->target = target;

    GM_SetTarget_8002DC74(target, ( TARGET_SEEK | TARGET_POWER ), NO_SIDE, size);
    GM_Target_8002DCCC(target, 1, -1, 0, 0, &DG_ZeroVector_800AB39C);
}

static inline void GlassClampSize(SVECTOR *size)
{
    size->vx = abs(size->vx);
    size->vy = abs(size->vy);
    size->vz = abs(size->vz);

    if (size->vx < 150)
    {
        size->vx = 150;
    }

    if (size->vy < 150)
    {
        size->vy = 150;
    }

    if (size->vz < 150)
    {
        size->vz = 150;
    }
}

int GlassGetResources_800D335C(GlassWork *work, int name, int map)
{
    SVECTOR  size;
    SVECTOR  max;
    SVECTOR  min;
    int      w;
    int      hzd_flags;
    SVECTOR *verts;
    DG_PRIM *prim;
    DG_TEX  *tex;
    int      x, y;
    HZD_SEG *maxb;
    HZD_SEG *minb;

    GM_CurrentMap_800AB9B0 = map;

    THING_Gcl_GetSVector('p', &work->pos);
    THING_Gcl_GetSVector('d', &work->dir);
    THING_Gcl_GetSVector('s', &size);

    work->size = size;

    work->fA4 = -THING_Gcl_GetIntDefault('f', work->pos.vy);
    work->fA6 = -THING_Gcl_GetIntDefault('b', -work->fA4);
    work->n_prims = THING_Gcl_GetIntDefault('n', 64);
    work->proc = THING_Gcl_GetInt('e');

    w = THING_Gcl_GetIntDefault('w', 125);
    hzd_flags = THING_Gcl_GetIntDefault('z', 180);
    hzd_flags &= ~0x4;

    verts = work->verts;

    prim = DG_GetPrim(0x12, 2, 0, verts, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    tex = DG_GetTexture_8001D830(GV_StrCode("glass"));
    work->tex = tex;
    if (tex == NULL)
    {
        return -1;
    }

    RotMatrix(&work->dir, &work->world);
    work->world.t[0] = work->pos.vx;
    work->world.t[1] = work->pos.vy;
    work->world.t[2] = work->pos.vz;

    DG_SetPos_8001BC44(&work->world);
    DG_PutPrim_8001BE00(&prim->world);

    GlassInitPacks_800D2E88(&work->prim->packs[0]->poly_ft4, tex, 0);
    GlassInitPacks_800D2E88(&work->prim->packs[1]->poly_ft4, tex, 0);

    x = work->size.vx;
    y = work->size.vy;

    verts[0].vx = -x;
    verts[0].vy = y;
    verts[0].vz = 0;

    verts[1].vx = x;
    verts[1].vy = y;
    verts[1].vz = 0;

    verts[2].vx = -x;
    verts[2].vy = 0;
    verts[2].vz = 0;

    verts[3].vx = x;
    verts[3].vy = 0;
    verts[3].vz = 0;

    verts[4].vx = -x;
    verts[4].vy = 0;
    verts[4].vz = 0;

    verts[5].vx = x;
    verts[5].vy = 0;
    verts[5].vz = 0;

    verts[6].vx = -x;
    verts[6].vy = -y;
    verts[6].vz = 0;

    verts[7].vx = x;
    verts[7].vy = -y;
    verts[7].vz = 0;

    DG_RotVector_8001BE98(&work->size, &size, 1);
    GlassClampSize(&size);
    GlassCreateTarget_800D32E4(work, &size);

    maxb = &work->bounds[0];
    max = work->verts[1];
    min = work->verts[6];
    max.vz += w;
    min.vz += w;

    s16b_800C45C4(maxb, &work->world, &max, &min);
    s16b_800C49AC(maxb);

    minb = &work->bounds[1];
    max = work->verts[1];
    min = work->verts[6];
    max.vz -= w;
    min.vz -= w;

    s16b_800C45C4(minb, &work->world, &max, &min);
    s16b_800C49AC(minb);

    work->hzd = Map_FromId_800314C0(map)->hzd;
    HZD_QueueDynamicSegment2_8006FDDC(work->hzd, maxb, hzd_flags);
    HZD_QueueDynamicSegment2_8006FDDC(work->hzd, minb, hzd_flags);
    work->has_bounds = 1;

    return 0;
}

GV_ACT * NewGlass_800D37A4(int name, int where)
{
    GlassWork *work;

    work = (GlassWork *)GV_NewActor(EXEC_LEVEL, sizeof(GlassWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)GlassAct_800D302C,
                         (TActorFunction)GlassDie_800D3270, "glass.c");

        if (GlassGetResources_800D335C(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->fB0 = 3;
        work->map = where;
    }

    return &work->actor;
}
