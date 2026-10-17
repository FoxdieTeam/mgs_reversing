#include <stdlib.h>
#include "strcode.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "bullet/blast.h"
#include "takabe/prim.h"
#include "takabe/windcrcl.h"

/* Metal Gear REX homing missile */

typedef struct _Work
{
    GV_ACT         actor;
    int            map;             // 0x20
    OBJECT_NO_ROTS body;            // 0x24
    MATRIX         light[2];        // 0x48
    MATRIX         world;           // 0x88
    int            speed;           // 0xA8
    SVECTOR        aim;             // 0xAC
    SVECTOR        rot;             // 0xB4
    SVECTOR        pos;             // 0xBC
    SVECTOR        velocity;        // 0xC4
    int            turn;            // 0xCC
    int            phase;           // 0xD0
    int            frame;           // 0xD4
    int            state;           // 0xD8
    int            se_timer;        // 0xDC
    int            side;            // 0xE0
    TARGET         target;          // 0xE4
    DG_PRIM       *prim;            // 0x12C
    DG_TEX        *tex;             // 0x130
    int            index;           // 0x134
    SVECTOR        vertices[32];    // 0x138
    SVECTOR        speeds[32];      // 0x238
    DVECTOR        params[32];      // 0x338: vx = life, vy = anim frame
} Work;

#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )

extern BLAST_DATA blast_data_8009F4B8[8];
extern int        s17a_dword_800E5E30;

void s01a_800E2364(MATRIX *mtx, SVECTOR *in, VECTOR *out);

/* no hazard checks inside this box */
SVECTOR hmissile_box[2] = {{15000, 32000, 24000}, {-15000, 4000, -24000}};
SVECTOR hmissile_dir = {0, 0, 0};
SVECTOR hmissile_target_size = {1000, 1500, 1000};

typedef struct _Scratch
{
    VECTOR vec;     // 0x00
    VECTOR sqr;     // 0x10
    MATRIX mtx;     // 0x20
} Scratch;

static void InitPrim(Work *work);
static void UpdateSmoke(Work *work, int spawn);

static void Act(Work *work)
{
    SVECTOR from;
    SVECTOR to;
    MATRIX  world;
    MAP    *map;
    int     hit;
    int     dist;
    int     yaw, pitch;
    Scratch *scratch;
    int      frame;
    int      dx, dz;

    hit = 0;

    GM_CurrentMap = work->map;
    map = GM_GetMap(work->map);

    if (work->state == -1)
    {
        UpdateSmoke(work, 1);

        from = work->pos;
        GV_AddVec3(&from, &work->velocity, &to);

        if (work->pos.vx < hmissile_box[0].vx && work->pos.vy < hmissile_box[0].vy && work->pos.vz < hmissile_box[0].vz &&
            hmissile_box[1].vx < work->pos.vx && hmissile_box[1].vy < work->pos.vy && hmissile_box[1].vz < work->pos.vz)
        {
            work->pos = to;
        }
        else if (HZD_OnlineHazardCheck(map->hzd, &from, &to, 15, 8))
        {
            HZD_GetOnlinePoint(&work->pos);
            hit = 1;
        }
        else if (GM_OnlineTargetCheck(&from, &to, map->index, &work->pos, work->side))
        {
            hit = 2;
        }
        else
        {
            work->pos = to;
        }

        work->world.t[0] = work->pos.vx;
        work->world.t[1] = work->pos.vy;
        work->world.t[2] = work->pos.vz;

        DG_SetPos(&work->world);
        GM_ActObject2((OBJECT *)&work->body);

        if (hit)
        {
            NewBlast(&work->world, &blast_data_8009F4B8[3]);

            work->target.center = work->pos;
            GM_PushTarget(&work->target);

            DG_InvisibleObjs(work->body.objs);
            work->state = 32;

            if (hit == 1)
            {
                world = DG_ZeroMatrix;
                world.t[0] = work->world.t[0];
                world.t[1] = work->world.t[1];
                world.t[2] = work->world.t[2];
                NewWindcrcl_800CF6BC(&world, 4000);
            }
        }
        else
        {
            DG_GetLightMatrix2(&work->pos, work->light);

            hmissile_dir.vz = work->speed + rsin(work->phase) * 50 / 4096;
            DG_RotVector(&hmissile_dir, &work->velocity, 1);
            work->velocity.vy -= 20;

            work->speed = GV_NearSpeed(work->speed, 500, 10);

            if (!(GM_GameStatus & STATE_CHAFF))
            {
                work->aim.vx = GM_PlayerPosition.vx >> 2;
                work->aim.vy = GM_PlayerPosition.vy >> 2;
                work->aim.vz = GM_PlayerPosition.vz >> 2;
            }

            scratch = (Scratch *)getScratchAddr(0);
            scratch->mtx = work->world;
            scratch->mtx.t[0] >>= 2;
            scratch->mtx.t[1] >>= 2;
            scratch->mtx.t[2] >>= 2;

            s01a_800E2364(&scratch->mtx, &work->aim, &scratch->vec);
            Square0(&scratch->vec, &scratch->sqr);

            dist = SquareRoot0(scratch->sqr.vx + scratch->sqr.vz);

            yaw = ratan2(scratch->vec.vx, scratch->vec.vz) & 0xFFF;
            if (yaw >= 0x800)
            {
                yaw -= 0x1000;
            }

            pitch = ratan2(-scratch->vec.vy, dist) & 0xFFF;
            if (pitch >= 0x800)
            {
                pitch -= 0x1000;
            }

            work->rot.vy = GV_NearSpeed(work->rot.vy, yaw, work->turn);
            work->rot.vx = GV_NearSpeed(work->rot.vx, pitch, work->turn);

            RotMatrixYXZ_gte(&work->rot, &scratch->mtx);
            MulMatrix(&work->world, &scratch->mtx);

            work->rot.vx = 0;
            work->rot.vy = 0;

            frame = work->frame++;
            if (frame >= 10)
            {
                if (frame < 40)
                {
                    work->turn = GV_NearSpeed(work->turn, 25, 4);
                }
                else
                {
                    work->turn = GV_NearSpeed(work->turn, 0, 1);
                }
            }

            if (++work->se_timer > 0)
            {
                work->se_timer = -90000;
            }

            if (work->se_timer == 0)
            {
                GM_SeSetMode(&work->pos, 187, GM_SEMODE_BOMB);
            }

            work->phase += 50;

            dx = GM_PlayerPosition.vx - work->pos.vx;
            dz = GM_PlayerPosition.vz - work->pos.vz;
            if (abs(dx) < 12000 && abs(dz) < 12000)
            {
                s17a_dword_800E5E30 = 45;
            }
        }
    }
    else
    {
        UpdateSmoke(work, 0);

        if (work->state == 0)
        {
            GV_DestroyActor(work);
            return;
        }

        work->state--;
    }
}

static void Die(Work *work)
{
    GM_FreeObject((OBJECT *)&work->body);
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, MATRIX *world, SVECTOR *aim, int side)
{
    OBJECT_NO_ROTS *body;
    SVECTOR         rot;
    MATRIX          mtx;

    body = &work->body;
    GM_InitObjectNoRots(body, GV_StrCode("rex_mis"), BODY_FLAG, 0);
    GM_ConfigObjectLight((OBJECT *)body, work->light);
    work->body.objs->objs[0].raise = -500;

    rot.vx = GV_RandS(64);
    rot.vy = GV_RandS(64);
    rot.vz = GV_RandS(64);
    RotMatrix_gte(&rot, &mtx);
    MulMatrix0(world, &mtx, &work->world);

    work->pos.vx = work->world.t[0] = world->t[0];
    work->pos.vy = work->world.t[1] = world->t[1];
    work->pos.vz = work->world.t[2] = world->t[2];

    work->aim.vx = aim->vx >> 2;
    work->aim.vy = aim->vy >> 2;
    work->aim.vz = aim->vz >> 2;

    GM_SetTarget(&work->target, TARGET_PUSH, PLAYER_SIDE, &hmissile_target_size);

    work->map = GM_CurrentMap;
    work->speed = GV_RandU(64) + 40;
    work->rot.vz = 180;
    work->turn = 10;
    work->phase = GV_RandU(1024);
    work->se_timer = -15;
    work->side = side;

    GM_SeSetMode(&work->pos, 186, GM_SEMODE_BOMB);
    InitPrim(work);

    work->state = -1;
    return 0;
}

void *NewHomingMissile(MATRIX *world, SVECTOR *aim, int side)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "hmissile.c");

        if (GetResources(work, world, aim, side) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return (void *)work;
}

static void InitPacks(POLY_FT4 *packs, DG_TEX *tex, int n_packs)
{
    int x, y, w, h;

    while (--n_packs != -1)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);

        x = tex->off_x;
        w = tex->w;
        packs->u0 = packs->u2 = x;
        packs->u1 = packs->u3 = x + (w + 1) / 4 - 1;

        y = tex->off_y;
        h = tex->h;
        packs->v0 = packs->v1 = y;
        packs->v2 = packs->v3 = y + (h + 1) / 4 - 1;

        packs->tpage = tex->tpage;
        packs->clut = tex->clut;

        packs->tpage |= (3 << 5);

        setRGB0(packs, 0, 0, 0);
        packs++;
    }
}

static void InitPrim(Work *work)
{
    DG_TEX  *tex;
    DG_PRIM *prim;

    work->tex = tex = DG_GetTexture(PCX_SMOKE);
    work->prim = prim = Takabe_MakeIndividualRect3DPrim(32, work->vertices);

    InitPacks(prim->packs[0], tex, 32);
    InitPacks(prim->packs[1], tex, 32);

    prim->world = DG_ZeroMatrix;
}

static void UpdateSmoke(Work *work, int spawn)
{
    DVECTOR  *param;
    SVECTOR  *vert;
    SVECTOR  *speed;
    POLY_FT4 *packs;
    int       i;
    int       xs, ys;
    int       x, y, w, h;
    int       shade;

    param = work->params;
    vert = work->vertices;
    speed = work->speeds;
    packs = work->prim->packs[GV_Clock];

    for (i = 32; i > 0; i--)
    {
        if (param->vx != 0)
        {
            vert->pad += 25;

            vert->vx += speed->vx;
            vert->vy += speed->vy;
            vert->vz += speed->vz;

            xs = param->vy & 7;
            ys = param->vy / 8;

            x = work->tex->off_x;
            w = work->tex->w + 1;
            packs->u0 = packs->u2 = x + (w * xs) / 8;
            packs->u1 = packs->u3 = x + (w * (xs + 1)) / 8 - 1;

            y = work->tex->off_y;
            h = work->tex->h + 1;
            packs->v0 = packs->v1 = y + (h * ys) / 4;
            packs->v2 = packs->v3 = y + (h * (ys + 1)) / 4 - 1;

            if (++param->vy >= 30)
            {
                param->vy = 0;
            }

            shade = param->vx * 8;
            setRGB0(packs, shade, shade, shade);
            param->vx--;
        }
        else
        {
            vert->pad = 0;
            setRGB0(packs, 0, 0, 0);
        }

        vert++;
        speed++;
        param++;
        packs++;
    }

    if (spawn != 0)
    {
        work->params[work->index].vx = 31;
        work->params[work->index].vy = GV_RandU(16);

        work->vertices[work->index] = work->pos;
        work->vertices[work->index].pad = 200;

        work->speeds[work->index].vx = GV_RandS(16);
        work->speeds[work->index].vy = GV_RandS(16);
        work->speeds[work->index].vz = GV_RandS(16);

        work->index = (work->index + 1) & 31;
    }
}
