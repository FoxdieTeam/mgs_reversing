#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Game/game.h"

typedef struct _Envmap3Work
{
    GV_ACT  actor;
    OBJECT *object;
    u_long  flag;
    DG_TEX *tex;
} Envmap3Work;

typedef struct _Envmap3Scratch
{
    char  uv[472];
    int   x;
    int   y;
    short tpage;
    short clut;
} Envmap3Scratch;

MATRIX envmap3_scale = {{{63, 0, 0}, {0, 63, 0}, {0, 0, 63}}, {0, 0, 0}};

extern int GV_Clock_800AB920;

#define EXEC_LEVEL 0

// clang-format off
#define gte_read_normal(x, y, z) __asm__ volatile (             \
        "mfc2   %0, $9;"                                        \
        "mfc2   %1, $10;"                                       \
        "mfc2   %2, $11"                                        \
        : "=r"(x), "=r"(y), "=r"(z))
// clang-format on

void Envmap3_800C9F14(DG_MDL *mdl)
{
    Envmap3Scratch *scratch;
    int             offx, offy;
    char           *uv;
    SVECTOR        *normals;
    int             n_normals;
    int             nx, ny, nz;

    scratch = (Envmap3Scratch *)getScratchAddr(0);
    offx = scratch->x;
    offy = scratch->y;
    uv = scratch->uv;

    normals = mdl->normals;
    n_normals = mdl->n_normals;

    gte_ldv3c(normals);
    gte_rtv0_b();
    normals += 3;

    for (; n_normals > 0; n_normals -= 3)
    {
        gte_read_normal(nx, ny, nz);
        nx = nx + offx;
        ny = offy - ny;

        gte_rtv1_b();

        uv[0] = nx;
        uv[1] = ny;

        gte_read_normal(nx, ny, nz);
        nx = nx + offx;
        ny = offy - ny;

        gte_rtv2_b();

        uv[2] = nx;
        uv[3] = ny;

        gte_read_normal(nx, ny, nz);

        gte_ldv3c(normals);

        nx = nx + offx;
        ny = offy - ny;

        gte_rtv0_b();
        normals += 3;

        uv[4] = nx;
        uv[5] = ny;

        uv += 6;
    }
}

POLY_GT4 * Envmap3_800C9FF4(unsigned int *normal, POLY_GT4 *packs, int n_packs)
{
    Envmap3Scratch *scratch;
    unsigned int    n0, n1, n2, n3;

    scratch = (Envmap3Scratch *)getScratchAddr(0);

    while (--n_packs >= 0)
    {
        if (packs->tag & 0xFF000000)
        {
            n0 = *normal;
            n1 = *normal;
            n2 = *normal;
            n3 = *normal;

            n0 <<= 1;
            n1 >>= 7;
            n2 >>= 23;
            n3 >>= 15;

            n0 &= 0xFE;
            n1 &= 0xFE;
            n2 &= 0xFE;
            n3 &= 0xFE;

            n0 += (unsigned int)scratch->uv;
            n1 += (unsigned int)scratch->uv;
            n2 += (unsigned int)scratch->uv;
            n3 += (unsigned int)scratch->uv;

            SCOPYL((void *)n0, &packs->u0);
            SCOPYL((void *)n1, &packs->u1);
            SCOPYL((void *)n2, &packs->u2);
            SCOPYL((void *)n3, &packs->u3);
        }

        packs++;
        normal++;
    }

    return packs;
}

POLY_GT4 * Envmap3_800CA0A8(POLY_GT4 *packs, int n_packs)
{
    Envmap3Scratch *scratch;
    short           tpage;
    short           clut;

    scratch = (Envmap3Scratch *)getScratchAddr(0);
    tpage = scratch->tpage;
    clut = scratch->clut;

    while (--n_packs >= 0)
    {
        packs->tpage = tpage;
        packs->clut = clut;
        packs++;
    }

    return packs;
}

void Envmap3_800CA0E4(DG_OBJ *obj)
{
    MATRIX          rot;
    int             dirty;
    POLY_GT4       *packs;
    Envmap3Scratch *scratch;
    DG_MDL         *mdl;

    dirty = 0;

    packs = obj->packs[1 - GV_Clock_800AB920];
    if (packs == NULL)
    {
        return;
    }

    scratch = (Envmap3Scratch *)getScratchAddr(0);
    if ((packs->tpage != scratch->tpage) || (packs->clut != scratch->clut))
    {
        dirty = 1;
    }

    MulMatrix0(&DG_Chanl(0)->field_10_eye_inv, &obj->world, &rot);
    MulMatrix(&rot, &envmap3_scale);
    SetRotMatrix(&rot);

    for (; obj != NULL; obj = obj->extend)
    {
        mdl = obj->model;

        Envmap3_800C9F14(obj->model);

        if (dirty != 0)
        {
            Envmap3_800CA0A8(packs, obj->n_packs);
        }

        packs = Envmap3_800C9FF4((unsigned int *)mdl->normal_indices, packs, obj->n_packs);
    }
}

void Envmap3_800CA1F4(Envmap3Work *work)
{
    DG_OBJS *objs;
    DG_OBJ  *obj;
    int      n_models;

    objs = work->object->objs;

    obj = objs->objs;
    for (n_models = objs->n_models; n_models > 0; n_models--, obj++)
    {
        Envmap3_800CA0E4(obj);
    }
}

void Envmap3_800CA24C(Envmap3Work *work)
{
    DG_OBJS *objs;
    DG_OBJ  *obj;
    int      n_models;

    objs = work->object->objs;
    objs->flag = work->flag;

    obj = objs->objs;
    for (n_models = objs->n_models; n_models > 0; n_models--, obj++)
    {
        DG_WriteObjPacketUV_8001A774(obj, 0);
        DG_WriteObjPacketUV_8001A774(obj, 1);
    }
}

void Envmap3Act_800CA2B4(Envmap3Work *work)
{
    Envmap3Scratch *scratch;

    scratch = (Envmap3Scratch *)getScratchAddr(0);
    scratch->x = work->tex->off_x + work->tex->w / 2;
    scratch->y = work->tex->off_y + work->tex->h / 2;
    scratch->tpage = work->tex->tpage;
    scratch->clut = work->tex->clut;

    envmap3_scale.m[0][0] = work->tex->w / 2 - 1;
    envmap3_scale.m[1][1] = work->tex->w / 2 - 1;
    envmap3_scale.m[2][2] = work->tex->w / 2 - 1;

    Envmap3_800CA1F4(work);
}

void Envmap3Die_800CA384(Envmap3Work *work)
{
    Envmap3_800CA24C(work);
}

GV_ACT * NewEnvmap3_800CA3A4(OBJECT *object, unsigned int name)
{
    Envmap3Work *work;
    DG_OBJS     *objs;
    int          i;
    DG_OBJ      *obj;
    int          n_models;
    POLY_GT4    *packs;
    unsigned int color;
    DG_OBJ      *iter;
    int          n_packs;

    work = (Envmap3Work *)GV_NewActor(EXEC_LEVEL, sizeof(Envmap3Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)Envmap3Act_800CA2B4, (TActorFunction)Envmap3Die_800CA384, "envmap3.c");

        work->object = object;
        work->tex = DG_GetTexture_8001D830(name);

        objs = object->objs;

        work->flag = objs->flag;
        objs->flag = (objs->flag & ~DG_FLAG_BOUND) | DG_FLAG_GBOUND;

        if (work->flag & DG_FLAG_SHADE)
        {
            objs->flag &= ~DG_FLAG_SHADE;

            for (i = 0; i < 2; i++)
            {
                obj = objs->objs;
                for (n_models = objs->n_models; n_models > 0; n_models--, obj++)
                {
                    packs = obj->packs[i];
                    if (packs == NULL)
                    {
                        continue;
                    }

                    if (!(obj->model->flags & DG_MODEL_TRANS))
                    {
                        color = 0x3C808080;
                    }
                    else
                    {
                        color = 0x3E808080;
                    }

                    for (iter = obj; iter != NULL; iter = iter->extend)
                    {
                        for (n_packs = iter->n_packs; n_packs > 0; n_packs--)
                        {
                            LSTORE(color, &packs->r0);
                            LSTORE(color, &packs->r1);
                            LSTORE(color, &packs->r2);
                            LSTORE(color, &packs->r3);
                            packs++;
                        }
                    }
                }
            }
        }
    }

    return &work->actor;
}
