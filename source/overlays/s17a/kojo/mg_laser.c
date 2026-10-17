#include <stdlib.h>
#include "strcode.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "anime/animconv/anime.h"
#include "takabe/thing.h"

/* Metal Gear REX laser (in game) */

#define N_SEGMENTS  8   // around the beam
#define N_RINGS     9   // along the beam
#define N_TRAILS    8
#define N_SPARKS    8

typedef struct _Work
{
    GV_ACT         actor;
    int            map;                                 // 0x20
    char           pad_24[0x24];
    TARGET         target;                              // 0x48
    char           pad_90[0x40];
    MATRIX        *root;                                // 0xD0
    SVECTOR        start;                               // 0xD4
    SVECTOR        end;                                 // 0xDC
    int            time;                                // 0xE4
    TARGET         push;                                // 0xE8
    int            se_timer;                            // 0x130
    DG_PRIM       *prim;                                // 0x134
    DG_PRIM       *sparks;                              // 0x138
    int            brightness;                          // 0x13C
    int            spark_index;                         // 0x140
    int            spark_life[N_SPARKS];                // 0x144
    SVECTOR        spark_pos[N_SPARKS];                 // 0x164
    OBJECT_NO_ROTS body;                                // 0x1A4
    MATRIX         light[2];                            // 0x1C8
    int            index;                               // 0x208
    SVECTOR        verts[2 * N_TRAILS * N_RINGS];       // 0x20C
    u_char         vindices[(N_RINGS - 2) * 8 * 4];     // 0x68C
    SVECTOR        norms[N_SEGMENTS];                   // 0x76C
    u_char         nindices[(N_RINGS - 2) * 8 * 4];     // 0x7AC
    u_char         uvs[(N_RINGS - 2) * 8 * 8];          // 0x88C
    short          texids[(N_RINGS - 2) * 8];           // 0xA4C
    int            unused;                              // 0xABC
} Work;

#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_BOUND | DG_FLAG_ONEPIECE | DG_FLAG_AMBIENT )

extern int s17a_dword_800E5E30;

int s01a_800E1FCC(SVECTOR *in0, VECTOR *in1, SVECTOR *out, int len);

unsigned short mg_laser_msgs[2] = {HASH_STOP, HASH_KILL};

DG_DEF mg_laser_def = {
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

SVECTOR mg_laser_step = {0, -20000, 0};
SVECTOR mg_laser_target_size = {100, 500, 100};
SVECTOR mg_laser_push_size = {300, 1500, 300};
RECT    mg_laser_rect = {300, 300, 600, 600};
RECT    mg_laser_spark_rect = {500, 500, 1000, 1000};
SVECTOR mg_laser_rot = {-854, 0, 0};
SVECTOR mg_laser_offset = {0, -500, 1800};

void MgLaser_GetMatrix(MATRIX *root, MATRIX *out);
static void InitModel(Work *work, SVECTOR *pos);

static inline void SetPackUV(POLY_FT4 *pack, int x, int w, int y, int h)
{
    setUVWH(pack, x, y, w, h);
}

static void InitBeamPacks(DG_PRIM *prim, DG_TEX *tex)
{
    POLY_FT4 *pack0;
    POLY_FT4 *pack1;

    pack0 = prim->packs[0];
    pack1 = prim->packs[1];

    setPolyFT4(pack0);
    setSemiTrans(pack0, 1);
    setPolyFT4(pack1);
    setSemiTrans(pack1, 1);

    setRGB0(pack0, 0, 0, 0);
    setRGB0(pack1, 0, 0, 0);

    SetPackUV(pack0, tex->off_x, tex->w, tex->off_y, tex->h);
    pack0->tpage = tex->tpage;
    pack0->clut = tex->clut;

    SetPackUV(pack1, tex->off_x, tex->w, tex->off_y, tex->h);
    pack1->tpage = tex->tpage;
    pack1->clut = tex->clut;

    prim->raise = 1000;
}

static void SetBeamColor(DG_PRIM *prim, int shade)
{
    POLY_FT4 *pack0;
    POLY_FT4 *pack1;

    pack0 = prim->packs[0];
    pack1 = prim->packs[1];

    setRGB0(pack0, shade, shade, shade);
    setRGB0(pack1, shade, shade, shade);
}

static void InitSparkPacks(POLY_FT4 *packs, DG_TEX *tex, int n_packs)
{
    int x, y, w, h;

    while (--n_packs != -1)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;
        setUVWH(packs, x, y, w, h);

        packs->tpage = tex->tpage;
        packs->clut = tex->clut;

        packs->tpage |= (3 << 5);

        setRGB0(packs, 0, 0, 0);
        packs++;
    }
}

static void InitSparkPrim(DG_PRIM *prim, DG_TEX *tex)
{
    InitSparkPacks(prim->packs[0], tex, N_SPARKS);
    InitSparkPacks(prim->packs[1], tex, N_SPARKS);

    prim->world = DG_ZeroMatrix;
    prim->raise = 1000;
}

static void UpdateSparks(Work *work, int spawn)
{
    int      *life;
    POLY_FT4 *packs;
    int       i;
    int       shade;

    packs = work->sparks->packs[GV_Clock];
    life = work->spark_life;

    if (spawn)
    {
        work->spark_pos[work->spark_index] = work->end;
        work->spark_life[work->spark_index] = 8;

        if (++work->spark_index >= 8)
        {
            work->spark_index = 0;
        }
    }

    for (i = N_SPARKS; i > 0; i--)
    {
        if (*life)
        {
            shade = (*life * 255) / 8;
            setRGB0(packs, shade, shade, shade);
            (*life)--;
        }
        else
        {
            setRGB0(packs, 0, 0, 0);
        }

        life++;
        packs++;
    }
}

static void Act(Work *work)
{
    SVECTOR  from;
    SVECTOR  to;
    SVECTOR  dir;
    SVECTOR  next;
    SVECTOR  hit_pos;
    MATRIX   mtx;
    VECTOR   vec;
    MAP     *map;
    SVECTOR *verts;
    SVECTOR *scratch;
    int      len;
    int      n;
    int      dist;
    int      hit;
    int      dx, dy, dz;
    int      px, pz;
    int      i;

    switch (THING_Msg_CheckMessage(0x3B49, 2, mg_laser_msgs))
    {
    case 0:
        work->time = -1;
        break;

    case 1:
        GV_DestroyActor(work);
        return;
    }

    GM_CurrentMap = work->map;
    map = GM_GetMap(work->map);

    if (work->time >= 0)
    {
        MgLaser_GetMatrix(work->root, &mtx);

        work->start.vx = mtx.t[0];
        work->start.vy = mtx.t[1];
        work->start.vz = mtx.t[2];

        DG_SetPos(&mtx);

        from = work->start;

        dir.vx = 0;
        dir.vy = -15000;
        dir.vz = 0;
        ApplyRotMatrix(&dir, &vec);

        vec.vx = vec.vx * 2 + from.vx;
        vec.vy = vec.vy * 2 + from.vy;
        vec.vz = vec.vz * 2 + from.vz;

        len = s01a_800E1FCC(&from, &vec, &to, 30000);

        dist = 0;
        hit = 0;
        n = len / 20000 + 1;

        DG_RotVector(&mg_laser_step, &dir, 1);

        for (; n > 0; n--)
        {
            dist += 20000;

            if (len < dist)
            {
                next = to;
            }
            else
            {
                GV_AddVec3(&from, &dir, &next);
            }

            if (HZD_OnlineHazardCheck(map->hzd, &from, &next, 15, 14))
            {
                HZD_GetOnlinePoint(&next);
                n = 1;
            }

            if (!hit)
            {
                if (GM_OnlineTargetCheck(&from, &next, map->index, &hit_pos, work->target.side))
                {
                    hit = 1;
                }
                else
                {
                    hit_pos = next;
                }
            }

            from = next;
        }

        work->end = next;

        DG_SetPos(&mtx);

        GM_MoveTarget(&work->target, &hit_pos);
        GM_PowerTarget(&work->target);

        AN_RecoilSmoke(&work->end);

        if (--work->se_timer <= 0)
        {
            GM_SeSetMode(&work->start, 183, GM_SEMODE_BOMB);
            work->se_timer = 7;
        }
    }

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

    if (work->time > 0)
    {
        work->brightness = GV_NearSpeed(work->brightness, 128, 20);
        UpdateSparks(work, 1);
    }
    else
    {
        work->brightness = GV_NearExp2(work->brightness, 0);
        UpdateSparks(work, 0);
    }

    SetBeamColor(work->prim, work->brightness);

    px = GM_PlayerPosition.vx - work->end.vx;
    pz = GM_PlayerPosition.vz - work->end.vz;
    if (abs(px) < 5000 && abs(pz) < 5000)
    {
        s17a_dword_800E5E30 = 45;
    }

    work->push.center = work->end;
    GM_PushTarget(&work->push);

    if (--work->time < -8)
    {
        GV_DestroyActor(work);
    }
}

static void Die(Work *work)
{
    GM_FreeObject((OBJECT *)&work->body);
    GM_FreePrim(work->prim);
    GM_FreePrim(work->sparks);
}

static int InitTarget(Work *work, int power, int side)
{
    TARGET *target;

    target = &work->target;
    GM_SetTarget(target, TARGET_POWER, side, &mg_laser_target_size);
    GM_SetPowerTarget(target, 0, -1, power, 0, &DG_ZeroVector);

    GM_SetTarget(&work->push, TARGET_PUSH, PLAYER_SIDE, &mg_laser_push_size);
    return 0;
}

static int GetResources(Work *work, MATRIX *root, int side, int power)
{
    SVECTOR         pos;
    MATRIX          mtx;
    OBJECT_NO_ROTS *body;
    DG_PRIM        *prim;

    MgLaser_GetMatrix(root, &mtx);

    pos.vx = mtx.t[0];
    pos.vy = mtx.t[1];
    pos.vz = mtx.t[2];
    InitModel(work, &pos);

    body = &work->body;
    body->flag = BODY_FLAG;
    body->light = work->light;
    body->map_name = GM_CurrentMap;

    work->body.objs = DG_MakeObjs(&mg_laser_def, body->flag, 0);
    DG_QueueObjs(work->body.objs);
    DG_GroupObjs(work->body.objs, body->map_name);

    work->body.objs->world = DG_ZeroMatrix;
    work->body.objs->light = work->light;
    work->body.objs->objs[0].raise = 1000;

    prim = GM_MakePrim(DG_PRIM_RECTANGLE | DG_PRIM_POLY_FT4, 1, &work->start, &mg_laser_rect);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    InitBeamPacks(prim, DG_GetTexture(0xBFE9));

    prim = GM_MakePrim(DG_PRIM_RECTANGLE | DG_PRIM_POLY_FT4, N_SPARKS, work->spark_pos, &mg_laser_spark_rect);
    work->sparks = prim;
    if (prim == NULL)
    {
        return -1;
    }

    InitSparkPrim(prim, DG_GetTexture(0xBFE9));
    InitTarget(work, power, side);

    work->root = root;
    work->map = GM_CurrentMap;

    GM_SeSetMode(&work->start, 182, GM_SEMODE_BOMB);
    work->se_timer = 10;
    return 0;
}

void *NewMgLaser(MATRIX *root, int side, int power, int time)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "mg_laser.c");

        if (GetResources(work, root, side, power) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }

        work->time = time;
    }

    return (void *)work;
}

static void InitModel(Work *work, SVECTOR *pos)
{
    u_char  *idx;
    u_char  *nidx;
    u_char  *uv;
    short   *texid;
    SVECTOR *vert;
    SVECTOR *norm;
    DG_MDL  *mdl;
    u_long   xy, zp;
    short    hash;
    int      j, i;
    int      v;
    int      u0, u1;
    int      w0, w1;
    int      ang, step;

    mdl = &mg_laser_def.models[0];
    mdl->verts = work->verts;
    mdl->vindices = work->vindices;
    mdl->norms = work->norms;
    mdl->nindices = work->nindices;
    mdl->uvs = work->uvs;
    mdl->texids = (u_short *)work->texids;

    idx = work->vindices;
    for (j = 0; j < N_RINGS - 2; j++)
    {
        v = j * N_RINGS;
        for (i = 8; i > 0; i--)
        {
            *idx++ = v;
            *idx++ = v + 9;
            *idx++ = v + 10;
            *idx++ = v + 1;
            v++;
        }
    }

    vert = work->verts;
    xy = LLOAD(&pos->vx);
    zp = LLOAD(&pos->vz);
    for (i = 2 * N_TRAILS * N_RINGS; i > 0; i--)
    {
        LSTORE(xy, &vert->vx);
        LSTORE(zp, &vert->vz);
        vert++;
    }

    hash = 0xBFE8;
    DG_GetTexture(hash);

    texid = work->texids;
    for (i = (N_RINGS - 2) * 8; i > 0; i--)
    {
        *texid++ = hash;
    }

    uv = work->uvs;
    u1 = 0;
    for (j = 0; j < N_RINGS - 2; j++)
    {
        w1 = 0;
        u0 = u1;
        u1 = ((j + 1) * 255) / 7;

        for (i = 0; i < 8; i++)
        {
            w0 = w1;
            w1 = ((i + 1) * 255) / 8;

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
    for (j = 0; j < N_RINGS - 2; j++)
    {
        for (i = 8; i > 0; i--)
        {
            *nidx++ = j;
            *nidx++ = j + 1;
            *nidx++ = j + 1;
            *nidx++ = j;
        }
    }

    norm = work->norms;
    step = 4096 / (N_SEGMENTS * 4);
    ang = 0;
    for (i = N_SEGMENTS; i > 0; i--)
    {
        norm->vx = rcos(ang);
        norm->vy = rsin(ang);
        ang += step;
        norm++;
    }

    work->light[0].m[0][0] = 4096;
    work->light[0].m[0][1] = 0;
    work->light[0].m[0][2] = 0;

    work->light[1].m[0][0] = 2048;
    work->light[1].m[1][0] = 2048;
    work->light[1].m[2][0] = 2048;
}

void MgLaser_GetMatrix(MATRIX *root, MATRIX *out)
{
    MATRIX rot;

    DG_SetPos(root);
    DG_MovePos(&mg_laser_offset);
    RotMatrix_gte(&mg_laser_rot, &rot);
    MulRotMatrix0(&rot, out);
    SetRotMatrix(out);
    ReadRotMatrix(out);
}
