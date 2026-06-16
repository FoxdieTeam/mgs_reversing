#include "game/game.h"
#include "okajima/spark.h"

typedef struct _Work
{
    GV_ACT   actor;
    CONTROL  control;
    TARGET   target;
    int      dist;
    int      hurt;
    int      map;
    SVECTOR  pos;
    DG_PRIM *prim;
    SVECTOR  vertices[16];
} Work;

static SVECTOR target_size = {280, 280, 280};
static int SECTION(".bss") bul_damage;

static int CheckTarget(Work *work)
{
    SVECTOR mov;
    SVECTOR out;
    SVECTOR diff;
    int     hit;

    if (work->hurt == 0)
    {
        return 0;
    }

    mov = work->control.mov;
    GV_SubVec3(&work->pos, &mov, &diff);
    GV_LenVec3(&diff, &out, GV_VecLen3(&diff), 2000);
    GV_AddVec3(&mov, &out, &out);

    hit = GM_Target_8002E1B8(&mov, &out, work->map, &out, ENEMY_SIDE);
    if (hit)
    {
        GM_MoveTarget(&work->target, &out);
        GM_PowerTarget(&work->target);
    }

    return hit;
}

static void Move(Work *work)
{
    SVECTOR rot;
    SVECTOR step;

    rot = DG_ZeroVector;
    rot.vy = GV_VecDir2(&work->control.step);

    step.vx = work->control.step.vy;
    step.vz = work->control.step.vz;
    rot.vx = GV_VecDir2(&step);

    RotMatrixYXZ(&rot, &work->prim->world);

    work->prim->world.t[0] = work->control.mov.vx;
    work->prim->world.t[1] = work->control.mov.vy;
    work->prim->world.t[2] = work->control.mov.vz;
}

static void Act(Work *work)
{
    MATRIX  mat;
    SVECTOR rot;
    VECTOR  scale;

    GM_ActControl(&work->control);

    work->dist -= 2000;
    work->control.mov.vy += work->control.step.vy;

    Move(work);

    if (CheckTarget(work))
    {
        GV_DestroyActor(work);
        return;
    }

    if (work->dist <= 0)
    {
        rot.vx = -1024;
        rot.vz = 0;
        rot.vy = 0;
        RotMatrixYXZ(&rot, &mat);

        mat.t[0] = work->pos.vx;
        mat.t[1] = work->pos.vy;
        mat.t[2] = work->pos.vz;

        GM_SeSet(&work->pos, 181);

        scale.vx = scale.vy = scale.vz = 8192;
        ScaleMatrix(&mat, &scale);
        NewSpark(&mat, 1);

        GV_DestroyActor(work);
    }
}

static void Die(Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreePrim(work->prim);
}

static int CalcEndpoint(Work *work, SVECTOR *trg)
{
    SVECTOR from;
    SVECTOR to;
    SVECTOR diff;
    int     hit;

    hit = 0;

    from = work->control.mov;
    to = *trg;

    if (HZD_OnlineHazardCheck(work->control.map->hzd, &from, &to, HZD_CHK_F_SEGMENT, HZD_SEG_NO_PLAYER))
    {
        HZD_GetOnlinePoint(&to);
        hit = 1;
        work->pos = to;
    }

    if (!hit)
    {
        work->pos = *trg;
        GV_SubVec3(trg, &work->control.mov, &diff);
        return GV_VecLen3(&diff);
    }

    GV_SubVec3(&to, &from, &from);
    return GV_VecLen3(&from);
}

static int InitPrim(Work *work)
{
    SVECTOR  *vert;
    DG_PRIM  *prim;
    DG_TEX   *tex;
    int       i, j;
    POLY_FT4 *pack;

    vert = work->vertices;

    work->prim = prim = GM_MakePrim(DG_PRIM_POLY_FT4, 4, vert, NULL);
    if (prim == NULL)
    {
        return -1;
    }

    tex = DG_GetTexture(GV_StrCode("bullet"));
    if (tex == NULL)
    {
        return -1;
    }

    for (i = 0; i < 2; i++)
    {
        pack = prim->packs[i];
        for (j = 0; j < 4; j++)
        {
            setPolyFT4(pack);
            setRGB0(pack, 36, 36, 12);
            setSemiTrans(pack, 1);
            DG_SetPacketTexture4(pack, tex);
            pack->tpage |= (1 << 5);
            pack++;
        }
    }

    prim->world = DG_ZeroMatrix;

    for (i = 0; i < 16; i++, vert++)
    {
        if (i < 4)
        {
            if (i & 2)
            {
                vert->vz = 1250;
            }
            else
            {
                vert->vz = 0;
            }

            if (i & 1)
            {
                vert->vx = 16;
            }
            else
            {
                vert->vx = -16;
            }

            vert->vy = 0;
        }
        else if (i < 8)
        {
            if (i & 2)
            {
                vert->vz = 1250;
            }
            else
            {
                vert->vz = 0;
            }

            if (i & 1)
            {
                vert->vx = -16;
            }
            else
            {
                vert->vx = 16;
            }

            vert->vy = 0;
        }
        else if (i < 12)
        {
            if (i & 2)
            {
                vert->vz = 1250;
            }
            else
            {
                vert->vz = 0;
            }

            if (i & 1)
            {
                vert->vy = -16;
            }
            else
            {
                vert->vy = 16;
            }

            vert->vx = 0;
        }
        else
        {
            if (i & 2)
            {
                vert->vz = 1250;
            }
            else
            {
                vert->vz = 0;
            }

            if (i & 1)
            {
                vert->vy = 16;
            }
            else
            {
                vert->vy = -16;
            }

            vert->vx = 0;
        }
    }

    return 0;
}

static int GetResources(Work *work, SVECTOR *pos, SVECTOR *trg)
{
    SVECTOR  diff;
    CONTROL *control;
    SVECTOR *step;
    int      len;

    control = &work->control;
    if (GM_InitControl(control, 0, 0) < 0)
    {
        return -1;
    }
        
    control->mov = *pos;
    control->rot = control->turn = DG_ZeroVector;

    GM_ConfigControlHazard(control, 0, -2, -2);

    GM_SetTarget(&work->target, TARGET_POWER, ENEMY_SIDE, &target_size);
    GM_SetPowerTarget(&work->target, POWER_ONCE, 1, bul_damage, 0, &DG_ZeroVector);

    step = &work->control.step;
    GV_SubVec3(trg, &control->mov, &diff);
    len = GV_VecLen3(&diff);

    work->dist = CalcEndpoint(work, trg);
    GV_LenVec3(&diff, step, len, 2000);

    work->map = GM_CurrentMap;

    if (InitPrim(work) < 0)
    {
        return -1;
    }

    return 0;
}

void *NewHindBullet(SVECTOR *pos, SVECTOR *trg, int hurt, int damage)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(work, Act, Die, "hind_bul.c");
    if (GetResources(work, pos, trg) < 0)
    {
        GV_DestroyActor(work);
        return NULL;
    }

    bul_damage = damage;
    work->hurt = hurt;

    return (void *)work;
}
