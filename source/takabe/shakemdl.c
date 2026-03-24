#include "shakemdl.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "takabe/thing.h"
#include "strcode.h"

/*----------------------------------------------------------------*/

#define EXEC_LEVEL  GV_ACTOR_LEVEL5

#define ROT_GROUP   16

// clang-format off
/*----------------------------------------------------------------*/

typedef struct {
    /* 公開部（プログラム呼び出し用） */
    GV_ACT      actor;
    int         name;
    int         active_flag;    /* 動作フラグ */
    int         scale;          /* 揺れ幅 */
    int         move_axis;      /* アニメーション頂点軸 */
    int         trg_scale;      /* 揺れ幅移行値 */
    int         change_speed;   /* 揺れ幅の変化スピード */

    /* 非公開部 */

    DG_DEF      *def;
    short       rots[ROT_GROUP];    /* 揺らぎ回転角 */
    short       speeds[ROT_GROUP];  /* 揺らぎ回転速度 */
    short       *points;    /* 頂点座標のオリジナル */

} Work;

typedef struct {
    short       offset[ROT_GROUP];  /* 計算された頂点オフセット */
} SCRPAD_DATA;

/*----------------------------------------------------------------*/
/* 頂点数だけバッファを確保 */
static int AllocVertsMemory( Work *work );
/* 頂点を動かす */
static int MoveVerts( Work *work, short *scrpad );
/* モデルを元に戻す */
static int RestoreVerts( Work *work );

/*----------------------------------------------------------------*/
// clang-format on

static void Act( Work *work )
{
    short *scrpad;
    //OPERATOR();

    {/* メッセージチェック */
        GV_MSG *msg;
        int     len;

        len = GV_ReceiveMessage(work->name, &msg);

        for (; len > 0; len--, msg++)
        {
            switch (msg->message[0])
            {
            case HASH_KILL:
                GV_DestroyActor(&work->actor);
                return;

            case 0xD368:
                work->trg_scale = msg->message[1];
                work->change_speed = msg->message[2];
                work->active_flag = TRUE;
                break;

            case 0x9873:
                work->active_flag = FALSE;
                break;
            }
        }
    }

    scrpad = (short *)SCRPAD_ADDR;

    {
        int     scale;
        short  *rots;
        short  *speeds;
        int     i;

        if (work->active_flag)
        {
            work->scale = GV_NearSpeed(work->scale, work->trg_scale, work->change_speed);

            scale = work->scale;
            rots = work->rots;
            speeds = work->speeds;

            for (i = ROT_GROUP; i > 0; i--)
            {
                *scrpad++ = (rsin(*rots) * scale) >> 12;
                *rots++ += *speeds++;
            }

            MoveVerts(work, (short *)SCRPAD_ADDR);

            if ((work->scale == 0) && (work->trg_scale == 0))
            {
                work->active_flag = FALSE;
            }
        }
    }
}

static void Die( Work *work )
{
    RestoreVerts(work);

    if (work->points)
    {
        GV_Free(work->points);
    }
}

static int GetResources( Work *work, int model )
{
    short *rots;
    short *speeds;
    int    i;

    work->def = GV_GetCache(GV_CacheID(model, 'k'));

    if (AllocVertsMemory(work))
    {
        return -1;
    }

    rots = work->rots;
    speeds = work->speeds;

    for (i = ROT_GROUP; i > 0; i--)
    {
        *rots++ = GV_RandU(0x1000U);
        *speeds++ = GV_RandU(0x40U) + 0x10;
    }

    return 0;
}

/*----------------------------------------------------------------*/

void *NewShakeModelGCL( int name, int where, int argc, char **argv )
{
    Work   *work;
    int     model;
    int     scale;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "shakemdl.c");

        model = THING_Gcl_GetInt('m');
        work->move_axis = THING_Gcl_GetInt('a');

        if (GetResources(work, model) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->name = name;
        work->active_flag = THING_Gcl_GetIntDefault('f', 1);
        scale = THING_Gcl_GetIntDefault('s', 50);
        work->scale = scale;
        work->trg_scale = scale;
    }

    return (void *)work;
}

void *NewShakeModel( int model, int axis, int scale )
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "shakemdl.c");

        work->move_axis = axis;

        if (GetResources(work, model) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->name = 0x7743;
        work->active_flag = TRUE;
        work->scale = scale;
        work->trg_scale = scale;
    }

    return (void *)work;
}

/*----------------------------------------------------------------*/

static int AllocVertsMemory( Work *work )
{
    DG_DEF  *def;
    DG_MDL  *mdl;
    int      n_verts;
    int      n_models;
    short   *vertices;
    SVECTOR *src;

    def = work->def;
    mdl = def->model;
    n_verts = 0;

    for (n_models = def->n_models; n_models > 0; mdl++, n_models--)
    {
        n_verts += mdl->n_verts;
    }

    vertices = GV_Malloc(n_verts * 2);
    work->points = vertices;

    if (!vertices)
    {
        return -1;
    }

    mdl = def->model;

    for (n_models = def->n_models; n_models > 0; mdl++, n_models--)
    {
        src = (SVECTOR *)((short *)mdl->vertices + work->move_axis);

        for (n_verts = mdl->n_verts; n_verts > 0; n_verts--)
        {
            *vertices++ = src->vx;
            src++;
        }
    }

    return 0;
}

static int MoveVerts( Work *work, short *scrpad )
{
    DG_MDL  *mdl;
    short   *src;
    int      index;
    int      n_models;
    SVECTOR *vertex;
    int      n_verts;
    int      ret;

    mdl = work->def->model;
    src = work->points;
    index = 0;
    ret = 0;

    for (n_models = work->def->n_models; n_models > 0; n_models--, mdl++)
    {
        vertex = (SVECTOR *)((short *)mdl->vertices + work->move_axis);

        for (n_verts = mdl->n_verts; n_verts > 0; n_verts--)
        {
            vertex->vx = *src++ + scrpad[index];
            index = (index + 1) & 0xF;
            vertex++;
        }
    }

    return ret;
}

static int RestoreVerts( Work *work )
{
    DG_MDL  *mdl;
    short   *src;
    int      n_models;
    SVECTOR *vertex;
    int      n_verts;

    mdl = work->def->model;
    src = work->points;

    for (n_models = work->def->n_models; n_models > 0; n_models--, mdl++)
    {
        vertex = (SVECTOR *)((short *)mdl->vertices + work->move_axis);

        for (n_verts = mdl->n_verts; n_verts > 0; n_verts--)
        {
            vertex->vx = *src++;
            vertex++;
        }
    }

    return 0;
}
