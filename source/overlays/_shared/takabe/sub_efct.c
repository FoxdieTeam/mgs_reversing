#include "sub_efct.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

typedef struct _SubEfctWork
{
    GV_ACT   actor;
    OBJECT  *parent;
    SVECTOR *rotation;
    MATRIX   light[2];
    u_long   flag;
    MATRIX  *lightp;
    char     pad[0x4];
} SubEfctWork;

#define EXEC_LEVEL GV_ACTOR_DAEMON

#define gte_pop_color(r0) __asm__ volatile ("mfc2   %0, $9;" : "=r"(r0))

void SubEfct_800CC798(DG_MDL *model)
{
    int      base;
    u_char  *out;
    SVECTOR *vertices;
    int      n_vertices;
    int      color;

    base = 128;
    out = (u_char *)SCRPAD_ADDR;

    vertices = model->vertices;
    n_vertices = model->n_verts;

    gte_ldv3c(vertices);
    gte_nop();
    gte_rtv0_b();

    vertices += 3;

    for (; n_vertices > 0; n_vertices -= 3)
    {
        gte_pop_color(color);
        color >>= 3;
        gte_nop();
        gte_rtv1_b();
        out[0] = base + color;

        gte_pop_color(color);
        color >>= 3;
        gte_nop();
        gte_rtv2_b();
        out[2] = base + color;

        gte_pop_color(color);
        gte_ldv3c(vertices);
        color >>= 3;
        gte_nop();
        gte_rtv0_b();
        out[4] = base + color;

        vertices += 3;
        out += 6;
    }
}

POLY_GT4 * SubEfct_800CC860(unsigned int *indices, POLY_GT4 *packs, int n_packs)
{
    unsigned int scratch;
    unsigned int n0, n1, n2, n3;

    scratch = SCRPAD_ADDR;

    while (--n_packs >= 0)
    {
        if (packs->tag & 0xFF000000)
        {
            n0 = *indices;
            n1 = *indices;
            n2 = *indices;
            n3 = *indices;

            n0 <<= 1;
            n1 >>= 7;
            n2 >>= 23;
            n3 >>= 15;

            n0 &= 0xFE;
            n1 &= 0xFE;
            n2 &= 0xFE;
            n3 &= 0xFE;

            n0 += scratch;
            n1 += scratch;
            n2 += scratch;
            n3 += scratch;

            packs->u0 = *(u_char *)n0;
            packs->u1 = *(u_char *)n1;
            packs->u2 = *(u_char *)n2;
            packs->u3 = *(u_char *)n3;
        }

        packs++;
        indices++;
    }

    return packs;
}

void SubEfct_800CC914(DG_OBJ *obj)
{
    POLY_GT4 *packs;
    DG_MDL   *model;

    packs = obj->packs[1 - GV_Clock];
    if (packs == NULL)
    {
        return;
    }

    while (obj != NULL)
    {
        model = obj->model;
        SubEfct_800CC798(model);
        packs = SubEfct_800CC860((unsigned int *)model->vindices, packs, obj->n_packs);
        obj = obj->extend;
    }
}

void SubEfct_800CC9A0(SubEfctWork *work)
{
    MATRIX   world;
    DG_OBJS *objs;
    DG_OBJ  *obj;
    int      i;

    objs = work->parent->objs;

    world = DG_ZeroMatrix;
    RotMatrixZ(work->rotation->vz, &world);
    DG_SetPos(&world);

    obj = objs->objs;
    for (i = objs->n_models; i > 0; i--)
    {
        SubEfct_800CC914(obj);
        obj++;
    }
}

void SubEfct_800CCA58(SubEfctWork *work)
{
    DG_OBJS *objs;
    DG_OBJ  *obj;
    int      i;

    objs = work->parent->objs;
    objs->flag = work->flag;

    obj = objs->objs;
    for (i = objs->n_models; i > 0; i--)
    {
        DG_WriteObjPacketUV(obj, 0);
        DG_WriteObjPacketUV(obj, 1);
        obj++;
    }
}

void SubEfctAct_800CCAC0(SubEfctWork *work)
{
    SubEfct_800CC9A0(work);
    work->parent->light = work->light;
}

void SubEfctDie_800CCAF0(SubEfctWork *work)
{
    SubEfct_800CCA58(work);
}

void *NewSubEfct_800CCB10(OBJECT *parent, SVECTOR *rotation)
{
    SubEfctWork *work;
    DG_OBJS     *objs;

    work = GV_NewActor(EXEC_LEVEL, sizeof(SubEfctWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, SubEfctAct_800CCAC0, SubEfctDie_800CCAF0, "sub_efct.c");

        work->parent = parent;
        work->rotation = rotation;

        objs = parent->objs;
        work->flag = objs->flag;

        objs->flag = (objs->flag & ~DG_FLAG_BOUND) | DG_FLAG_AMBIENT | DG_FLAG_GBOUND;

        work->lightp = objs->light;
        objs->light = work->light;

        work->light[0].m[0][0] = 0;
        work->light[0].m[0][1] = -4096;
        work->light[0].m[0][2] = 0;

        work->light[1].m[0][0] = 2048;
        work->light[1].m[1][0] = 2048;
        work->light[1].m[2][0] = 2048;
    }

    return (void *)work;
}
