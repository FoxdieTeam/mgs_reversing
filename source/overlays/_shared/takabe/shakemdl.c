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
    GV_MSG *msg;
    int     count;
    short  *scrpad;
    int     temp_v0;
    short  *var_s0;
    short  *var_s1;
    int     i;

    //OPERATOR();

    /* メッセージチェック */

    count = GV_ReceiveMessage(work->name, &msg);

    for (; count > 0; count--, msg++)
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

    scrpad = (short *)SCRPAD_ADDR;

    if (work->active_flag)
    {
        work->scale = GV_NearSpeed(work->scale, work->trg_scale, work->change_speed);
        temp_v0 = work->scale;

        var_s0 = work->rots;
        var_s1 = work->speeds;

        for (i = ROT_GROUP; i > 0; i--)
        {
            *scrpad++ = (rsin(*var_s0) * temp_v0) >> 12;
            *var_s0++ += *var_s1++;
        }

        MoveVerts(work, (short *)SCRPAD_ADDR);

        if ((work->scale == 0) && (work->trg_scale == 0))
        {
            work->active_flag = FALSE;
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
    DG_MDL  *object;
    int      nvertices;
    int      nobjects;
    short   *vertices;
    SVECTOR *src;

    def = work->def;
    object = def->model;
    nvertices = 0;

    for (nobjects = def->n_models; nobjects > 0; object++, nobjects--)
    {
        nvertices += object->n_verts;
    }

    vertices = GV_Malloc(nvertices * 2);
    work->points = vertices;

    if (!vertices)
    {
        return -1;
    }

    object = def->model;

    for (nobjects = def->n_models; nobjects > 0; object++, nobjects--)
    {
        src = (SVECTOR *)((short *)object->vertices + work->move_axis);

        for (nvertices = object->n_verts; nvertices > 0; nvertices--)
        {
            *vertices++ = src->vx;
            src++;
        }
    }

    return 0;
}

static int MoveVerts( Work *work, short *scrpad )
{
    DG_MDL  *object;
    short   *src;
    int      index;
    int      nobjects;
    SVECTOR *vertex;
    int      nvertices;
    int      ret;

    object = work->def->model;
    src = work->points;
    index = 0;
    ret = 0;

    for (nobjects = work->def->n_models; nobjects > 0; nobjects--, object++)
    {
        vertex = (SVECTOR *)((short *)object->vertices + work->move_axis);

        for (nvertices = object->n_verts; nvertices > 0; nvertices--)
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
    DG_MDL  *object;
    short   *src;
    int      nobjects;
    SVECTOR *vertex;
    int      nvertices;

    object = work->def->model;
    src = work->points;

    for (nobjects = work->def->n_models; nobjects > 0; nobjects--, object++)
    {
        vertex = (SVECTOR *)((short *)object->vertices + work->move_axis);

        for (nvertices = object->n_verts; nvertices > 0; nvertices--)
        {
            vertex->vx = *src++;
            vertex++;
        }
    }

    return 0;
}
