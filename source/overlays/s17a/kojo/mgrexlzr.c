#include <stdlib.h>
#include <memory.h>
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

/* Metal Gear REX laser (demo) */

#define N_SEGMENTS  8   // around the beam
#define N_RINGS     9   // along the beam
#define N_TRAILS    8

typedef struct _Work
{
    GV_ACT         actor;
    int            map;                                 // 0x20
    MATRIX        *root;                                // 0x24
    SVECTOR        start;                               // 0x28
    SVECTOR        end;                                 // 0x30
    OBJECT_NO_ROTS body;                                // 0x38
    MATRIX         light[2];                            // 0x5C
    int            index;                               // 0x9C
    SVECTOR        verts[2 * N_TRAILS * N_RINGS];       // 0xA0
    u_char         vindices[(N_RINGS - 2) * 8 * 4];     // 0x520
    SVECTOR        norms[N_SEGMENTS];                   // 0x600
    u_char         nindices[(N_RINGS - 2) * 8 * 4];     // 0x640
    u_char         uvs[(N_RINGS - 2) * 8 * 8];          // 0x720
    short          texids[(N_RINGS - 2) * 8];           // 0x8E0
    int            timer;                               // 0x950
} Work;

#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_BOUND | DG_FLAG_ONEPIECE | DG_FLAG_AMBIENT )

DG_DEF mgrexlzr_def = {
    1,                      // n_models
    1,                      // n_x_models
    -32000, -32000, -32000, // lx, ly, lz
     32000,  32000,  32000, // ux, uy, uz
    {                       // model[]
        {
            1027,                   // flags
            56,                     // n_faces
            -32000, -32000, -32000, // lx, ly, lz
             32000,  32000,  32000, // ux, uy, uz
            0, 0, 0,                // tx, ty, tz
            -1,                     // parent
            -1,                     // extend
            72,                     // n_verts
            NULL,                   // verts
            NULL,                   // vindices
            8,                      // n_norms
            NULL,                   // norms
            NULL,                   // nindices
            NULL,                   // uvs
            NULL,                   // texids
            0                       // pad0
        }
    }
};

static void Act(Work *work);
static void Die(Work *work);

void *NewMetalGearLaser(MATRIX *root)
{
    Work    *work;
    DG_OBJS *objs;
    u_char  *idx;
    u_char  *nidx;
    u_char  *uv;
    short   *texid;
    SVECTOR *norm;
    SVECTOR  pos;
    int      i, j;
    int      v;
    int      u0, u1;
    int      w0, w1;
    int      ang, step;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, Act, Die, "mgrexlzr.c");

    work->timer = 8;
    work->root = root;
    work->map = GM_CurrentMap;

    mgrexlzr_def.models[0].verts = work->verts;
    mgrexlzr_def.models[0].vindices = work->vindices;
    mgrexlzr_def.models[0].norms = work->norms;
    mgrexlzr_def.models[0].nindices = work->nindices;
    mgrexlzr_def.models[0].uvs = work->uvs;
    mgrexlzr_def.models[0].texids = (u_short *)work->texids;

    idx = work->vindices;
    for (i = 0; i < N_RINGS - 2; i++)
    {
        v = i * N_RINGS;
        for (j = 8; j > 0; j--)
        {
            *idx++ = v;
            *idx++ = v + 9;
            *idx++ = v + 10;
            *idx++ = v + 1;
            v++;
        }
    }

    DG_SetPos(root);
    memset(&pos, 0, sizeof(SVECTOR));
    DG_PutVector(&pos, &pos, 1);

    for (i = 2 * N_TRAILS * N_RINGS; i > 0; i--)
    {
        work->verts[i] = pos;
    }

    texid = work->texids;
    for (i = (N_RINGS - 2) * 8; i > 0; i--)
    {
        *texid++ = -0x4018; /* GV_StrCode("laser")? */
    }

    uv = work->uvs;
    u1 = 0;
    for (i = 0; i < N_RINGS - 2; i++)
    {
        w1 = 0;
        u0 = u1;
        u1 = ((i + 1) * 255) / 7;

        for (j = 0; j < 8; j++)
        {
            w0 = w1;
            w1 = ((j + 1) * 255) / 8;

            uv[0] = u0;
            uv[1] = w0;
            uv[2] = u1;
            uv[3] = w0;
            uv[4] = u1;
            uv[5] = w1;
            uv[6] = u0;
            uv[7] = w1;
            uv += 8;
        }
    }

    nidx = work->nindices;
    for (i = 0; i < N_RINGS - 2; i++)
    {
        for (j = 8; j > 0; j--)
        {
            *nidx++ = i;
            *nidx++ = i + 1;
            *nidx++ = i + 1;
            *nidx++ = i;
        }
    }

    norm = work->norms;
    ang = 0;
    step = 4096 / (N_SEGMENTS * 4);
    for (i = N_SEGMENTS; i > 0; i--)
    {
        norm->vx = rcos(ang);
        norm->vy = rsin(ang);
        ang += step;
        norm++;
    }

    work->body.flag = BODY_FLAG;

    work->light[0].m[0][0] = 4096;
    work->light[0].m[0][1] = 0;
    work->light[0].m[0][2] = 0;

    work->light[1].m[0][0] = 2048;
    work->light[1].m[1][0] = 2048;
    work->light[1].m[2][0] = 2048;

    work->body.light = work->light;
    work->body.map_name = GM_CurrentMap;

    objs = DG_MakeObjs(&mgrexlzr_def, work->body.flag, 0);
    work->body.objs = objs;
    DG_QueueObjs(objs);

    DG_GroupObjs(work->body.objs, work->body.map_name);
    work->body.objs->world = DG_ZeroMatrix;
    work->body.objs->light = work->light;
    work->body.objs->objs[0].raise = 1000;
    DG_InvisibleObjs(work->body.objs);

    return (void *)work;
}

static void Act(Work *work)
{
    MATRIX   mtx;
    SVECTOR  pos;
    SVECTOR *verts;
    SVECTOR *scratch;
    int      dx, dy, dz;
    int      i;

    if (--work->timer < 0)
    {
        DG_VisibleObjs(work->body.objs);
    }

    DG_SetPos(work->root);
    memset(&work->start, 0, sizeof(SVECTOR));
    DG_PutVector(&work->start, &work->start, 1);

    DG_SetPos(work->root);
    memset(&pos, 0, sizeof(SVECTOR));
    pos.vz = 30000;
    DG_MovePos(&pos);
    ReadRotMatrix(&mtx);

    memset(&work->end, 0, sizeof(SVECTOR));
    DG_PutVector(&work->end, &work->end, 1);

    DG_SetPos(work->root);

    work->index = (work->index + 7) & 7;
    verts = &work->verts[work->index * N_RINGS];
    work->body.objs->def->models[0].verts = verts;

    scratch = (SVECTOR *)getScratchAddr(0);

    dx = (work->start.vx - work->end.vx) / 8;
    dy = (work->start.vy - work->end.vy) / 8;
    dz = (work->start.vz - work->end.vz) / 8;

    *scratch = work->end;

    for (i = N_RINGS; i > 0; i--)
    {
        verts[0] = *scratch;
        verts[N_TRAILS * N_RINGS] = *scratch;
        verts++;

        scratch->vx += dx;
        scratch->vy += dy;
        scratch->vz += dz;
    }
}

static void Die(Work *work)
{
    GM_FreeObject((OBJECT *)&work->body);
}
