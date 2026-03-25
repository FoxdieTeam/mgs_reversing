#include "dummy_fl.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "linkvar.h"
#include "game/vibrate.h"
#include "takabe/thing.h"

typedef struct _FLOOR_OBJ
{
    SVECTOR  pos;
    SVECTOR  rot;
    MATRIX   model;
    DG_OBJS *objs;
    SVECTOR  f34;
    char     pad[0x4];
    SVECTOR  bounds[5];
} FLOOR_OBJ;

typedef struct _Work
{
    GV_ACT    actor;
    int       name;
    int       map;
    char      pad[0x4];
    FLOOR_OBJ flr_obj[2];
    MATRIX    world;
    MATRIX    light[2];
    SVECTOR   f15C;
    MATRIX    f164;
    int       f184;
    int       f188;
    int       raise;
    int       f190;
    int       f194;
    int       f198;
    int       f19C;
    int       f1A0;
    int       f1A4;
    int       add_speed; /* 落下加速度 */
    int       rot_z; /* 蝶番角度 */
    int       close_wait; /* 落し穴が閉じるまでの最低時間 */
	//int       wepon_fall_flag ; /* C4&クレイモア落下フラグ */

    int       proc_id;

	/* shading関連 */
    int       shade_flag;

	/* 扉当たり判定用可動壁データ */
    int       hzd_flag;
    HZD_HDL  *hzd;
    HZD_FLR   floors[2];
} Work;

typedef struct
{
    MATRIX  mat;
    SVECTOR vec;
} SCRPAD_DATA;

char dummy_floor_800C3610[] = {0x7F, 0x01, 0x00, 0x00};
char dummy_floor_800C3614[] = {0x50, 0x04, 0x00, 0x00};

SVECTOR normal = {0, 4096, 0};

extern CONTROL *tenage_ctrls_800BDD30[16];
extern int      tenage_ctrls_count_800BDD70;

void Takabe_FreeObjs(DG_OBJS *objs);
void Takabe_ReshadeModel(DG_OBJS *, LIT *);
void Takabe_RefreshObjectPacks(DG_OBJS *);

DG_OBJS *Takabe_MakePreshade(int model, LIT *lit);

void s01a_800E2364(MATRIX *mtx, SVECTOR *in, VECTOR *out);
void s16b_800C4874(int arg0, HZD_SEG *arg1, int arg2, HZD_FLR *arg3);

/* モデル初期化 */
static void InitPreshadeObject(Work *work, FLOOR_OBJ *flr_obj, int model_name, int map);
static void MakeFloor(SVECTOR *in, HZD_FLR *floor);

#define EXEC_LEVEL GV_ACTOR_LEVEL5

static void Act(Work *work)
{
    VECTOR       sp10;
    SCRPAD_DATA *scratch;
    CONTROL    **iter;
    int          count;
    int          i;
    FLOOR_OBJ   *flap;

    GM_CurrentMap = work->map;

    s01a_800E2364(&work->f164, &GM_PlayerControl->mov, &sp10);

    sp10.vx = ABS(sp10.vx);
    sp10.vy = ABS(sp10.vy);
    sp10.vz = ABS(sp10.vz);

    if ((sp10.vx < (work->flr_obj[0].f34.vx - 100)) &&
        (sp10.vz < (work->flr_obj[0].f34.vz / 2)))
    {
        if (work->hzd_flag != 0)
        {
            work->f188 = 0;
            work->add_speed = 0;
            work->hzd_flag = 0;
            work->f194 = 1;
            work->f184 = work->f190;

            GM_SeSet(&work->f15C, 187);

            NewPadVibration(dummy_floor_800C3610, 1);
            NewPadVibration(dummy_floor_800C3614, 2);
        }

        work->f198 = 1;
    }
    else
    {
        if (work->close_wait != 0)
        {
            work->close_wait--;
        }
        else if ((work->hzd_flag == 0) && (work->f194 == 0))
        {
            work->f188 = 1;
            work->f184 = 0;
            work->f1A4 = 2;
            work->hzd_flag = 1;
        }

        work->f198 = 0;
    }

    if (work->f194 != 0)
    {
        work->f184--;
    }

    switch (work->f188)
    {
    case 0:
        if ((work->f184 < 0) && (GM_GameOverTimer == 0))
        {
            GM_SeSet(&work->f15C, 186);

            if (GM_GameOverTimer == 0)
            {
                if (work->f198 == 1)
                {
                    GM_UnkFlagA0++;
                    dword_800ABA1C = 1;

                    if (work->proc_id != 0)
                    {
                        GCL_ExecProc(work->proc_id, NULL);
                    }

                    GM_GameOver();
                }

                work->f188 = 2;
                work->f1A4 = 1;
                work->close_wait = 40;
            }

            s16b_800C4874(0, NULL, 2, work->floors);

            scratch = (SCRPAD_DATA *)SCRPAD_ADDR;

            scratch->mat = work->f164;
            DG_TransposeMatrix(&scratch->mat, &scratch->mat);
            DG_SetPos(&scratch->mat);

            if (tenage_ctrls_count_800BDD70 != 0)
            {
                iter = tenage_ctrls_800BDD30;
                for (count = 16; count > 0; count--)
                {
                    *iter = NULL;

                    scratch->vec = *(SVECTOR *)0x00000000;
                    scratch->vec.vx -= scratch->mat.t[0];
                    scratch->vec.vy -= scratch->mat.t[1];
                    scratch->vec.vz -= scratch->mat.t[2];

                    DG_RotVector(&scratch->vec, &scratch->vec, 1);

                    scratch->vec.vx = ABS(scratch->vec.vx);
                    scratch->vec.vy = ABS(scratch->vec.vy);
                    scratch->vec.vz = ABS(scratch->vec.vz);

                    if ((scratch->vec.vx < work->flr_obj[0].f34.vx) &&
                        (scratch->vec.vz < work->flr_obj[0].f34.vz / 2) &&
                        (scratch->vec.vy < 150))
                    {
                        (*iter)->mov.pad = 1;
                    }

                    iter++;
                }
            }

            work->f194 = 0;
        }

        work->f1A0 = work->f19C - 100;
        break;

    case 1:
        work->f1A0 = GV_NearSpeed(work->f1A0, work->f19C, 32);
        break;

    case 2:
        if ((GM_GameOverTimer == 0) && (work->f198 == 1))
        {
            work->f1A4 = 1;
            GM_UnkFlagA0++;
            dword_800ABA1C = 1;

            if (work->proc_id != 0)
            {
                GCL_ExecProc(work->proc_id, NULL);
            }

            if (work->name == 0x5862)
            {
                work->proc_id = 0;
            }
            else
            {
                GM_GameOver();
            }
        }
        break;
    }

    switch (work->f1A4)
    {
    case 0:
        break;

    case 1:
        work->add_speed += (rcos(work->rot_z) * 40) / 4096;
        work->rot_z += work->add_speed;

        if (work->rot_z > 1024)
        {
            work->rot_z = 2048 - work->rot_z;
            work->add_speed = -work->add_speed / 4;
        }

        work->flr_obj[0].rot.vz = -work->rot_z;
        work->flr_obj[1].rot.vz = work->rot_z;
        break;

    case 2:
        work->rot_z = GV_NearExp8(work->rot_z, 0);
        if (work->rot_z < 8)
        {
            work->rot_z = 0;
            work->f1A4 = 0;
            GM_SeSet(&work->f15C, 188);
        }

        work->flr_obj[0].rot.vz = -work->rot_z;
        work->flr_obj[1].rot.vz = work->rot_z;
        break;
    }

    work->world.t[1] = work->f1A0;

    for (i = 0; i < 2; i++)
    {
        flap = &work->flr_obj[i];
        DG_SetPos2(&flap->pos, &flap->rot);
        ReadRotMatrix(&flap->model);
        CompMatrix(&work->world, &flap->model, &flap->objs->world);
    }

    if (GM_GameStatus & STATE_THERMG)
    {
        if (work->shade_flag == 0)
        {
            work->flr_obj[0].objs->flag = ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_BOUND | DG_FLAG_ONEPIECE | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE );
            work->flr_obj[1].objs->flag = ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_BOUND | DG_FLAG_ONEPIECE | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE );
            work->flr_obj[0].objs->light = work->light;
            work->flr_obj[1].objs->light = work->light;
            DG_GetLightMatrix2(&DG_ZeroVector, work->light);
            work->shade_flag = 1;
        }
    }
    else if (work->shade_flag != 0)
    {
        work->flr_obj[0].objs->flag = ( DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS | DG_FLAG_BOUND | DG_FLAG_ONEPIECE | DG_FLAG_IRTEXTURE );
        work->flr_obj[1].objs->flag = ( DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS | DG_FLAG_BOUND | DG_FLAG_ONEPIECE | DG_FLAG_IRTEXTURE );
        Takabe_RefreshObjectPacks(work->flr_obj[0].objs);
        Takabe_RefreshObjectPacks(work->flr_obj[1].objs);
        work->shade_flag = 0;
    }
}

static void Die(Work *work)
{
    if (work->hzd_flag != 0)
    {
        HZD_DequeueDynamicFloor(work->hzd, &work->floors[0]);
        HZD_DequeueDynamicFloor(work->hzd, &work->floors[1]);
    }

    work->flr_obj[0].objs->flag = ( DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS | DG_FLAG_BOUND | DG_FLAG_ONEPIECE | DG_FLAG_IRTEXTURE );
    Takabe_FreeObjs(work->flr_obj[0].objs);

    work->flr_obj[1].objs->flag = ( DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS | DG_FLAG_BOUND | DG_FLAG_ONEPIECE | DG_FLAG_IRTEXTURE );
    Takabe_FreeObjs(work->flr_obj[1].objs);
}

static int GetResources(Work *work, int name, int map)
{
    SVECTOR    pos;
    SVECTOR    dir;
    SVECTOR    bounds[5];
    FLOOR_OBJ *flr_obj;
    int        model;
    FLOOR_OBJ *flap;
    int        i, j;
    DG_MDL    *mdl;
    SVECTOR   *bound;
    int        xmax, xmin;
    int        zmax, zmin;

    GM_CurrentMap = map;

    THING_Gcl_GetSVector('p', &pos);
    THING_Gcl_GetSVector('d', &dir);

    work->raise = THING_Gcl_GetInt('r');
    work->f190 = THING_Gcl_GetIntDefault('t', 30);
    work->proc_id = THING_Gcl_GetInt('e');

    DG_SetPos2(&pos, &dir);
    ReadRotMatrix(&work->world);

    flr_obj = &work->flr_obj[0];

    work->f1A0 = work->f19C = pos.vy;

    GCL_GetOption('m');

    model = GCL_StrToInt(GCL_GetParamResult());
    InitPreshadeObject(work, &work->flr_obj[0], model, work->map);
    flr_obj[0].objs->light = work->light;

    model = GCL_StrToInt(GCL_GetParamResult());
    InitPreshadeObject(work, &work->flr_obj[1], model, work->map);
    flr_obj[1].objs->light = work->light;

    ReadRotMatrix(&flr_obj[0].model);
    ReadRotMatrix(&flr_obj[0].objs->world);

    Takabe_ReshadeModel(flr_obj[0].objs, GM_GetMap(map)->lit);

    flr_obj[1].pos.vx = flr_obj[0].f34.vx + flr_obj[1].f34.vx;

    DG_MovePos(&flr_obj[1].pos);

    ReadRotMatrix(&flr_obj[1].model);
    ReadRotMatrix(&flr_obj[1].objs->world);

    Takabe_ReshadeModel(flr_obj[1].objs, GM_GetMap(map)->lit);

    work->f15C.vx = flr_obj[0].f34.vx;
    work->f15C.vz = flr_obj[0].f34.vz / 2;
    work->f15C.vy = 0;

    DG_SetPos(&flr_obj[0].model);
    DG_PutVector(&work->f15C, &work->f15C, 1);
    DG_SetPos2(&work->f15C, &dir);
    ReadRotMatrix(&work->f164);

    for (i = 0; i < 2; i++)
    {
        flap = &work->flr_obj[i];
        mdl = flap->objs->def->model;
        bound = flap->bounds;

        xmax = mdl->min.vx;
        xmin = mdl->max.vx;

        zmax = mdl->min.vz;
        zmin = mdl->max.vz;

        for (j = 4; j > 0; j--)
        {
            if (j & 2)
            {
                bound->vx = xmax;
            }
            else
            {
                bound->vx = xmin;
            }

            bound->vy = 0;

            if ((j + 1) & 2)
            {
                bound->vz = zmax;
            }
            else
            {
                bound->vz = zmin;
            }

            bound++;
        }

        bound->vx = 0;
        bound->vy = 4096;
        bound->vz = 0;

        DG_SetPos(&flap->model);
        DG_PutVector(flap->bounds, bounds, 4);
        DG_RotVector(&normal, &bounds[4], 1);

        work->hzd = GM_GetMap(map)->hzd;
        MakeFloor(bounds, &work->floors[i]);
        HZD_QueueDynamicFloor(work->hzd, &work->floors[i]);

        flap++;
    }

    work->hzd_flag = 1;
    work->f184 = 0;
    work->f188 = -1;
    work->shade_flag = 0;
    work->add_speed = 0;
    return 0;
}

void *NewDummyFloor(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        work->name = name;
        work->map = where;

        GV_SetNamedActor(&work->actor, Act, Die, "dummy_fl.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}

static void InitPreshadeObject(Work *work, FLOOR_OBJ *flr_obj, int model_name, int map)
{
    DG_MDL *mdl;

    flr_obj->objs = Takabe_MakePreshade(model_name, NULL);
    flr_obj->objs->flag = ( DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS | DG_FLAG_BOUND | DG_FLAG_ONEPIECE | DG_FLAG_IRTEXTURE );

    mdl = flr_obj->objs->def->model;
    flr_obj->f34.vx = mdl->max.vx - mdl->min.vx;
    flr_obj->f34.vy = mdl->max.vy - mdl->min.vy;
    flr_obj->f34.vz = mdl->max.vz - mdl->min.vz;

    flr_obj->objs->objs[0].raise = work->raise;
}

static void MakeFloor(SVECTOR *in, HZD_FLR *floor)
{
    int      xmax, ymax, zmax;
    int      xmin, ymin, zmin;
    int      x, y, z;
    SVECTOR *vec;
    HZD_VEC *bounds;
    int      i;

    zmax = -32000;
    ymax = -32000;
    xmax = -32000;

    zmin = 32000;
    ymin = 32000;
    xmin = 32000;

    vec = in;
    bounds = &floor->p1;

    for (i = 4; i > 0; i--)
    {
        x = vec->vx;

        if (x > xmax)
        {
            xmax = x;
        }

        if (x < xmin)
        {
            xmin = x;
        }

        bounds->x = x;

        y = vec->vy;

        if (y > ymax)
        {
            ymax = y;
        }

        if (y < ymin)
        {
            ymin = y;
        }

        bounds->y = y;

        z = vec->vz;

        if (z > zmax)
        {
            zmax = z;
        }

        if (z < zmin)
        {
            zmin = z;
        }

        bounds->z = z;

        vec++;
        bounds++;
    }

    floor->p1.h = in[4].vx >> 4;
    floor->p2.h = in[4].vz >> 4;
    floor->p3.h = in[4].vy >> 4;

    if (in[4].vy == 0)
    {
        floor->p3.h++;
    }

    floor->b1.z = zmin;
    floor->b2.z = zmax;
    floor->b1.x = xmin;
    floor->b2.x = xmax;
    floor->b1.y = ymin;
    floor->b2.y = ymax;
    floor->b1.h = 0;
}
