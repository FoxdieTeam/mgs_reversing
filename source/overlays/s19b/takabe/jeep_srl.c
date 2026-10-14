#include <stdio.h>
#include "strcode.h"
#include "game/game.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "game/vibrate.h"
#include "takabe/fadeio.h"
#include "takabe/thing.h"

typedef struct _JEEP_SYSTEM
{
    char     pad1[0x4];
    CONTROL *control;       // 0x04
    char     pad2[0x10];
    SVECTOR  pos;           // 0x18
    SVECTOR  next_pos;      // 0x20
    int      field_28;      // 0x28
    int      field_2C;      // 0x2C
    int      field_30;      // 0x30
    char     pad3[0x4];
    SVECTOR  field_38;      // 0x38
    int      field_40;      // 0x40
    int      field_44;      // 0x44
    int      field_48;      // 0x48
    char     pad4[0x14];
    OBJECT  *body;          // 0x60
    char     pad5[0x14];
    int      field_78;      // 0x78
    int      field_7C;      // 0x7C
    MATRIX   world;         // 0x80
    char     pad6[0xCC];
} JEEP_SYSTEM;

extern JEEP_SYSTEM Takabe_JeepSystem;

// One step of the scripted scroll speed table
typedef struct _JEEP_KEY
{
    short model;            // 0x00
    short time;             // 0x02
    short target_a;         // 0x04
    short target_b;         // 0x06
    short speed_a;          // 0x08
    short speed_b;          // 0x0A
    short count;            // 0x0C
    short attr;             // 0x0E
} JEEP_KEY;

// Result of stepping the scroll table, describes the next road piece
typedef struct _JEEP_STEP
{
    int model;
    int a;
    int b;
    int attr;
} JEEP_STEP;

// Loaded models of the road pieces
typedef struct _JEEP_MODEL
{
    DG_DEF   *def;          // 0x00
    DG_LITS  *lit;          // 0x04
    HZD_DEF  *hzd;          // 0x08
    HZD_GRP  *grp;          // 0x0C
    DG_OBJS  *objs;         // 0x10
    int       pad[2];       // 0x14
} JEEP_MODEL;

// A piece of the scrolling road
typedef struct _JEEP_ROAD
{
    SVECTOR   pos;          // 0x00
    SVECTOR   step;         // 0x08
    short     shear_x;      // 0x10
    short     shear_y;      // 0x12
    short     field_14;     // 0x14
    short     pad_16;       // 0x16
    DG_OBJS  *objs;         // 0x18
    DG_LITS  *lit;          // 0x1C
    HZD_GRP  *grp;          // 0x20
    int       flags;        // 0x24
    int       attr;         // 0x28
} JEEP_ROAD;

#define JEEP_MODEL_COUNT 13
#define JEEP_ROAD_COUNT  16
#define JEEP_FLR_COUNT   24
#define JEEP_SEG_COUNT   48

typedef struct _Work
{
    GV_ACT      actor;                      // 0x00
    int         map;                        // 0x20
    int         name;                       // 0x24
    MATRIX      world;                      // 0x28
    JEEP_MODEL  models[JEEP_MODEL_COUNT];   // 0x48
    JEEP_ROAD   road[JEEP_ROAD_COUNT];      // 0x1B4
    DG_OBJS    *extra[JEEP_ROAD_COUNT];     // 0x474
    HZD_HDL    *hzd;                        // 0x4B4
    HZD_FLR    *flr_cur;                    // 0x4B8
    HZD_FLR     flrs[JEEP_FLR_COUNT];       // 0x4BC
    HZD_SEG    *seg_cur;                    // 0x93C
    HZD_SEG     segs[JEEP_SEG_COUNT];       // 0x940
    u_int       lit_count;                  // 0xC40
    DG_LITS    *lit;                        // 0xC44
    int         speed_a;                    // 0xC48
    int         speed_b;                    // 0xC4C
    int         key_time;                   // 0xC50
    int         key_count;                  // 0xC54
    JEEP_KEY   *key;                        // 0xC58
    int         field_C5C;                  // 0xC5C
    int         field_C60;                  // 0xC60
    int         field_C64;                  // 0xC64
    int         reshaded;                   // 0xC68
    int         head;                       // 0xC6C
    int         proc_c70;                   // 0xC70
    int         proc_c74;                   // 0xC74
    int         proc_c78;                   // 0xC78
    int         field_C7C;                  // 0xC7C
    int         field_C80;                  // 0xC80
} Work;

void s19b_jeep_gls_800CEE7C(Work *work, int attr, SVECTOR *pos);
void s19b_jeep_gls_800CEFE4(Work *work, int model, SVECTOR *road_pos);
int  s19b_jeep_gls_800CEDFC(int z, int offset);
void s19b_jeep_gls_800CF088(void);
void s19b_jlamp_800D0CE0(void);
void s19b_jlamp_800D0D40(void);
void  Takabe_ReshadeModel(DG_OBJS *objs, DG_LITS *lit);
void *NewJeep(int name, int where);
void  s19b_jeep_800D2170(SVECTOR *arg0, SVECTOR *arg1, SVECTOR *arg2, short *arg3);
void  s19b_jeep_800D21DC(int ang, MATRIX *mat, SVECTOR *out);

extern unsigned short s19b_dword_800C3530[JEEP_MODEL_COUNT];
extern JEEP_KEY       s19b_dword_800C354C[];
extern MATRIX         s19b_dword_800C36DC;
extern unsigned char  s19b_dword_800C36FC[];
extern unsigned char  s19b_dword_800C3710[];
extern Work          *s19b_dword_800DE5B0;

void *NewJeepGate(int name, SVECTOR *pos, int side);
void *NewJeepGlass(int name, SVECTOR *pos, int side);
void *NewJeepLamp(SVECTOR *root_pos, int tex_id, int unused);
void *s19b_jeep2_800D6F24(int name, int map); // NewJeep2

static void LoadModels(Work *work);
static DG_OBJS *CopyModelObjs(int index, Work *work);
static void FreeCopiedObjs(DG_OBJS *objs);
void s19b_jeep_gls_800CE8DC(Work *work, JEEP_ROAD *road, int do_segs); // QueueRoadHazard

// Advances the scripted scroll speeds and describes the next road piece
static void StepKey(Work *work, JEEP_STEP *step)
{
    JEEP_KEY *key;

    key = work->key;
    work->speed_a = GV_NearSpeed(work->speed_a, key->target_a, key->speed_a);
    work->speed_b = GV_NearSpeed(work->speed_b, key->target_b, key->speed_b);

    step->model = key->model;
    step->a = work->speed_a;
    step->b = work->speed_b;
    step->attr = key->attr;

    if (work->key_time > 0)
    {
        if (--work->key_count == 0)
        {
            Takabe_JeepSystem.field_40 = key->attr;
        }
        else
        {
            Takabe_JeepSystem.field_40 = 0;
        }

        if (--work->key_time == 0)
        {
            work->key++;
            key = work->key;
            if (key->model == -1)
            {
                key = s19b_dword_800C354C;
                work->key = key;
            }

            work->key_time = key->time;
            work->key_count = key->count;
        }
    }
    else
    {
        Takabe_JeepSystem.field_40 = 0;
        if (Takabe_JeepSystem.field_44 != 0)
        {
            Takabe_JeepSystem.field_44--;
            work->key_time = -work->key_time;
        }
    }
}

static void InitKey(Work *work)
{
    JEEP_KEY *key = s19b_dword_800C354C;
    work->key = key;
    work->key_time = key->time;
    work->key_count = key->count;
}

// Places the road pieces, collects their lights and dynamic hazards
static void UpdateRoadObjs(Work *work, JEEP_ROAD *last, DG_LIT *lights)
{
    JEEP_ROAD *road;
    DG_LIT    *src;
    SVECTOR    pos;
    long       flag;
    int        i, j;
    int        idx;

    for (i = 0; i < JEEP_ROAD_COUNT; i++)
    {
        idx = (i - work->head) & 0xF;
        road = &work->road[i];

        if (idx >= 4 && idx <= 11)
        {
            DG_SetPos2(&road->pos, &DG_ZeroVector);
            DG_PutObjs(road->objs);

            s19b_dword_800C36DC.m[0][2] = road->shear_x;
            s19b_dword_800C36DC.m[1][2] = road->shear_y;
            MulMatrix0(&road->objs->world, &s19b_dword_800C36DC, &road->objs->world);
            SetRotMatrix(&road->objs->world);

            DG_GroupObjs(road->objs, GM_CurrentMap);
            work->extra[i]->root = &road->objs->world;

            if (road->objs->def == work->models[0].def && ABS(road->pos.vz) >= 6001)
            {
                DG_VisibleObjs(work->extra[i]);
                DG_InvisibleObjs(road->objs);
            }
            else
            {
                DG_VisibleObjs(road->objs);
                DG_InvisibleObjs(work->extra[i]);
            }

            src = road->lit->lights;
            for (j = road->lit->n_lights; j > 0; j--)
            {
                RotTransSV(&src->point, &pos, &flag);
                lights->point = pos;
                lights->r_range = src->r_range >> 1;
                lights->e_range = src->e_range >> 1;
                lights->color = src->color;
                src++;
                lights++;
                work->lit->n_lights++;
            }

            if (idx >= 5 && idx <= 9)
            {
                s19b_jeep_gls_800CE8DC(work, road, 1);
            }
            else
            {
                s19b_jeep_gls_800CE8DC(work, road, 0);
            }

            road->flags &= ~2;
        }
        else
        {
            DG_InvisibleObjs(road->objs);
            DG_InvisibleObjs(work->extra[i]);
        }

        road->flags &= ~1;
    }
}

static void Act(Work *work)
{
    JEEP_ROAD *road;
    JEEP_ROAD *next_road;
    JEEP_STEP  step;
    DG_LITS   *lit;
    DG_LIT    *lights;
    int        z;
    int        i;
    int        j;
    int        next;
    int        a;

    GM_CurrentMap = work->map;

    if (work->reshaded == 0)
    {
        for (j = 0; j < JEEP_MODEL_COUNT; j++)
        {
            Takabe_ReshadeModel(work->models[j].objs, work->models[j].lit);
        }

        work->reshaded = 1;
    }

    Takabe_JeepSystem.pos = Takabe_JeepSystem.next_pos;

    lit = work->lit;
    lit->n_lights = 0;
    work->flr_cur = work->flrs;
    work->seg_cur = work->segs;
    work->hzd->n_d_segs = 0;
    work->hzd->n_d_flrs = 0;
    lights = lit->lights;

    for (i = 0; i < JEEP_ROAD_COUNT; i++)
    {
        road = &work->road[i];
        z = road->pos.vz + Takabe_JeepSystem.pos.vz;

        if (z >= 32000)
        {
            StepKey(work, &step);

            a = step.a;
            road->step.vx = a / 2;
            road->shear_x = (-a * 2048) / 4000;
            a = step.b;
            road->flags = 3;
            road->step.vy = a / 2;
            road->shear_y = (-a * 2048) / 4000;
            road->attr = step.attr;

            next = (i + 1) & 0xF;
            z -= 64000;
            next_road = &work->road[next];

            road->pos.vx = next_road->pos.vx + next_road->step.vx;
            road->pos.vy = next_road->pos.vy + next_road->step.vy;
            road->pos.vx += road->step.vx;
            road->pos.vy += road->step.vy;

            if (next < i)
            {
                road->pos.vx -= Takabe_JeepSystem.pos.vx;
                road->pos.vy -= Takabe_JeepSystem.pos.vy;
            }

            work->head = i;

            FreeCopiedObjs(road->objs);
            road->objs = CopyModelObjs(step.model, work);
            road->lit = work->models[step.model].lit;
            road->grp = work->models[step.model].grp;
            road->pos.vz = z;
            road->pos.vx += Takabe_JeepSystem.pos.vx;
            road->pos.vy += Takabe_JeepSystem.pos.vy;

            s19b_jeep_gls_800CEE7C(work, step.attr, &road->pos);
            s19b_jeep_gls_800CEFE4(work, step.model, &road->pos);
        }
        else
        {
            road->pos.vz = z;
            road->pos.vx += Takabe_JeepSystem.pos.vx;
            road->pos.vy += Takabe_JeepSystem.pos.vy;
        }
    }

    SetSpadStack(SPAD_STACK_ADDR);
    UpdateRoadObjs(work, road, lights);
    ResetSpadStack();

    if (work->lit->n_lights > work->lit_count)
    {
        printf("<<<<< light over !!!!!!!(jeep.srl.c) >>>>>\n");
    }

    s19b_jlamp_800D0D40();

    GM_Camera.zoom = 240;
    GM_Camera.flag |= 2;

    if (work->field_C80 != 0)
    {
        work->field_C80++;
        if (work->field_C80 >= 71)
        {
            if (work->proc_c78 != 0 && GM_GameOverTimer == 0)
            {
                GCL_ExecProc(work->proc_c78, NULL);
            }
        }
        else if (work->field_C80 >= 31)
        {
            if (work->field_C80 == 31)
            {
                NewPadVibration(s19b_dword_800C36FC, 1);
                NewPadVibration(s19b_dword_800C3710, 2);
            }
        }
    }
    else
    {
        if (s19b_jeep_gls_800CEDFC(Takabe_JeepSystem.control->mov.vz, 9600) == 14)
        {
            NewFadeInOut(2, 20);
            work->field_C80 = 1;
        }
    }

    Takabe_JeepSystem.world.t[0] += Takabe_JeepSystem.pos.vx;
    Takabe_JeepSystem.world.t[1] += Takabe_JeepSystem.pos.vy;
    Takabe_JeepSystem.world.t[2] += Takabe_JeepSystem.pos.vz;
}

static void Die(Work *work)
{
    DG_OBJS *objs;
    int     *count;
    int      i;

    for (i = 0; i < JEEP_ROAD_COUNT; i++)
    {
        FreeCopiedObjs(work->extra[i]);
    }

    for (i = 0; i < JEEP_ROAD_COUNT; i++)
    {
        FreeCopiedObjs(work->road[i].objs);
    }

    for (i = 0; i < JEEP_MODEL_COUNT; i++)
    {
        objs = work->models[i].objs;
        DG_FreePreshade(objs);
        DG_FreeObjs(objs);
    }

    Takabe_JeepSystem.field_78 = 0;
    GM_StreamPlayStop();

    // restore the light count (stored through a plain int pointer in the original)
    count = &work->lit->n_lights;
    *count = work->lit_count;
    GM_GameStatus &= ~STATE_NOSLOW;
}

static int GetResources(Work *work, int name, int where)
{
    JEEP_ROAD *road;
    DG_OBJS  **extra;
    DG_OBJS   *objs;
    int        i;
    int        j;

    s19b_jeep_gls_800CF088();

    GM_CurrentMap = where;
    work->map = where;
    work->name = name;
    work->field_C64 = 0;
    work->world = DG_ZeroMatrix;

    LoadModels(work);

    work->lit = GM_GetMap(GM_CurrentMap)->lit;
    work->lit_count = work->lit->n_lights;
    printf("max light:%d\n", work->lit_count);

    Takabe_JeepSystem.field_48 = THING_Gcl_GetInt('c');
    road = work->road;
    work->field_C60 = 0;
    work->reshaded = 0;
    work->head = 0;

    Takabe_JeepSystem.next_pos = DG_ZeroVector;
    Takabe_JeepSystem.pos = Takabe_JeepSystem.next_pos;
    Takabe_JeepSystem.field_30 = 0;
    Takabe_JeepSystem.field_2C = 0;
    Takabe_JeepSystem.field_28 = 0;

    for (i = 0; i < JEEP_ROAD_COUNT; i++)
    {
        road->objs = CopyModelObjs(0, work);
        road->lit = work->models[0].lit;
        road->grp = work->models[0].grp;
        road->step.vz = -2000;
        road->shear_x = 0;
        road->field_14 = 0;
        road->step.vx = 0;
        road->step.vy = 0;
        road->pos.vx = 0;
        road->pos.vy = 0;
        road->pos.vz = i * 4000 - 31500;
        road->flags = 1;
        road->attr = 0;

        Takabe_JeepSystem.field_38 = road->pos;
        if (Takabe_JeepSystem.field_38.vz < 16000)
        {
            s19b_jeep_gls_800CEFE4(work, 0, &road->pos);
        }

        road++;
    }

    extra = work->extra;
    j = JEEP_ROAD_COUNT;
    do
    {
        objs = CopyModelObjs(12, work);
        *extra++ = objs;
        DG_InvisibleObjs(objs);
    } while (--j > 0);

    work->hzd = GM_GetMap(work->map)->hzd;
    s19b_dword_800DE5B0 = work;

    if (GCL_GetOption('e'))
    {
        work->proc_c70 = GCL_StrToInt(GCL_NextStr());
        work->proc_c74 = GCL_StrToInt(GCL_NextStr());
        work->proc_c78 = GCL_StrToInt(GCL_NextStr());
    }

    Takabe_JeepSystem.field_78 = 0x800;
    Takabe_JeepSystem.world = DG_ZeroMatrix;

    NewJeep(GV_StrCode("j_snake"), where);
    s19b_jlamp_800D0CE0();
    InitKey(work);

    work->key = s19b_dword_800C354C;
    GM_GameStatus |= STATE_NOSLOW;
    return 0;
}

void *NewJeepScroll(int name, int where)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_PREV, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "jeep_srl.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}

static void LoadModels(Work *work)
{
    JEEP_MODEL     *model;
    unsigned short *ids;
    DG_DEF         *def;
    DG_LITS        *lit;
    int             i;

    model = work->models;

    for (i = 0, ids = s19b_dword_800C3530; i < JEEP_MODEL_COUNT; i++)
    {
        model->def = def = GV_GetCache(GV_CacheID(*ids, 'k'));
        model->lit = lit = GV_GetCache(GV_CacheID(*ids, 'l'));
        if (lit == NULL)
        {
            model->lit = lit = work->models[0].lit;
        }

        model->hzd = GV_GetCache(GV_CacheID(*ids, 'h'));
        model->grp = model->hzd->groups;

        model->objs = DG_MakeObjs(def, DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS | DG_FLAG_BOUND | DG_FLAG_ONEPIECE, 0);
        if (lit != NULL)
        {
            DG_MakePreshade(model->objs, lit->lights, lit->n_lights);
        }
        else
        {
            DG_MakePreshade(model->objs, NULL, 0);
        }

        DG_InvisibleObjs(model->objs);

        model++;
        ids++;
    }
}

static DG_OBJS *CopyModelObjs(int index, Work *work)
{
    JEEP_MODEL *models;
    DG_OBJS    *new_objs;
    DG_OBJ     *dst, *src;
    DG_OBJ     *dst_iter, *src_iter;
    int         i;

    models = work->models;
    new_objs = DG_MakeObjs(models[index].def, 0x57, 0);
    dst_iter = new_objs->objs;
    src_iter = models[index].objs->objs;
    for (i = new_objs->n_models; i > 0; i--)
    {
        src = src_iter++;
        dst = dst_iter++;
        while (dst != NULL)
        {
            dst->rgbs = src->rgbs;
            dst = dst->extend;
            src = src->extend;
        }
    }

    DG_SetPos(&DG_ZeroMatrix);
    DG_PutObjs(new_objs);
    DG_QueueObjs(new_objs);
    DG_GroupObjs(new_objs, GM_CurrentMap);
    return new_objs;
}

static void FreeCopiedObjs(DG_OBJS *objs)
{
    DG_DequeueObjs(objs);
    objs->objs[0].rgbs = NULL;
    DG_FreeObjs(objs);
}

// Builds the dynamic floor of a road piece from 4 transformed vertices
void s19b_jeep_gls_800CE628(JEEP_ROAD *road, SVECTOR *verts, HZD_FLR *flr, int calc_normal)
{
    VECTOR  vec_b;
    VECTOR  vec_a;
    VECTOR  normal;
    SVECTOR norm;
    SVECTOR *vec;

    vec = &verts[0];
    flr->p1.x = vec->vx;
    flr->p1.y = vec->vy;
    flr->p1.z = vec->vz;
    vec = &verts[1];
    flr->p2.x = vec->vx;
    flr->p2.y = vec->vy;
    flr->p2.z = vec->vz;
    vec = &verts[2];
    flr->p3.x = vec->vx;
    flr->p3.y = vec->vy;
    flr->p3.z = vec->vz;
    vec = &verts[3];
    flr->p4.x = vec->vx;
    flr->p4.y = vec->vy;
    flr->p4.z = vec->vz;

    if (flr->p4.z < flr->p1.z)
    {
        flr->p1.z = flr->p2.z = flr->p3.z = flr->p4.z = road->pos.vz;
    }

    if (calc_normal)
    {
        vec_a.vx = verts[1].vx - verts[0].vx;
        vec_a.vy = verts[1].vy - verts[0].vy;
        vec_a.vz = verts[1].vz - verts[0].vz;
        vec_b.vx = verts[2].vx - verts[1].vx;
        vec_b.vy = verts[2].vy - verts[1].vy;
        vec_b.vz = verts[2].vz - verts[1].vz;
        OuterProduct12(&vec_b, &vec_a, &normal);
        VectorNormalS(&normal, &norm);
        flr->p1.h = norm.vx >> 4;
        flr->p2.h = norm.vz >> 4;
        flr->p3.h = norm.vy >> 4;
    }

    flr->b1.z = road->pos.vz - 2000;
    flr->b2.z = road->pos.vz + 2000;
    flr->b1.x = road->pos.vx - 8000;
    flr->b2.x = road->pos.vx + 8000;
    flr->b1.y = road->pos.vy - 8000;
    flr->b2.y = road->pos.vy + 8000;
    flr->b1.h = 0;
}

void s19b_jeep_gls_800CE83C(SVECTOR *src, HZD_SEG *dst)
{
    dst->p1.x = src->vx;
    dst->p1.y = src->vy;
    dst->p1.z = src->vz;
    dst->p1.h = src->pad;
    src++;
    dst->p2.x = src->vx;
    dst->p2.y = src->vy;
    dst->p2.z = src->vz;
    dst->p2.h = src->pad;
    HZD_SetDynamicSegment(dst, dst);
}

// Converts a hazard point to a normal vector (the hazard format has y and z swapped)
void s19b_jeep_gls_800CE8B8(HZD_VEC *src, SVECTOR *dst)
{
    dst->vx = src->x;
    dst->vy = src->y;
    dst->vz = src->z;
}

/* verts[] pointers are kept in callee saved registers in the original, the rest is identical */
#if 0 /* NON_MATCHING */
static void QueueRoadHazard(Work *work, JEEP_ROAD *road, int do_segs)
{
    SVECTOR  verts[4];
    SVECTOR *vec;
    HZD_GRP *grp;
    HZD_HDL *hzd;
    HZD_FLR *flr;
    HZD_SEG *seg;
    char    *flags1;
    char    *flags2;
    int      i;

    SetRotMatrix(&road->objs->world);

    grp = road->grp;
    hzd = work->hzd;
    flr = grp->floors;

    for (i = grp->n_floors; i > 0; i--)
    {
        if (hzd->n_d_segs < JEEP_FLR_COUNT)
        {
            vec = verts;
            s19b_jeep_gls_800CE8B8(&flr->p1, vec);
            vec = &verts[1];
            s19b_jeep_gls_800CE8B8(&flr->p2, vec);
            vec = &verts[2];
            s19b_jeep_gls_800CE8B8(&flr->p3, vec);
            vec = &verts[3];
            s19b_jeep_gls_800CE8B8(&flr->p4, vec);
            DG_PutVector(verts, verts, 4);

            if (Takabe_JeepSystem.pos.vz != 0)
            {
                s19b_jeep_gls_800CE628(road, verts, work->flr_cur, road->flags & 2);
            }

            flr++;
            HZD_QueueDynamicFloor(work->hzd, work->flr_cur++);
        }
    }

    if (do_segs)
    {
        grp = road->grp;
        flags1 = grp->wallsFlags;
        seg = grp->walls;
        flags2 = flags1 + grp->n_walls;
        hzd = work->hzd;

        for (i = grp->n_walls; i > 0; i--)
        {
            if (hzd->n_d_segs < JEEP_SEG_COUNT)
            {
                s19b_jeep_gls_800CE8B8(&seg->p1, &verts[0]);
                s19b_jeep_gls_800CE8B8(&seg->p2, &verts[1]);
                DG_PutVector(verts, verts, 2);

                verts[0].pad = seg->p1.h / 2;
                verts[1].pad = seg->p2.h / 2;

                if (Takabe_JeepSystem.pos.vz != 0)
                {
                    s19b_jeep_gls_800CE83C(verts, work->seg_cur);
                }

                seg++;
                HZD_QueueDynamicSegment2(work->hzd, work->seg_cur++, *flags1++ | (*flags2++ << 8));
            }
        }
    }
}
#endif
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_gls_800CE8DC.s")

/* register allocation differs (head/constant swapped) */
#if 0 /* NON_MATCHING */
void s19b_jeep_gls_800CEB2C(int z, SVECTOR *rot)
{
    Work    *work;
    SVECTOR  vec;
    int      base;
    int      i;

    work = s19b_dword_800DE5B0;
    base = work->road[work->head].pos.vz - 2000;
    i = ((z - base) / 4000 + work->head) & 0xF;
    vec = work->road[i].step;

    rot->vy = GV_VecDir2(&vec);
    rot->vx = ratan2(-vec.vy, SquareRoot0(vec.vx * vec.vx + vec.vz * vec.vz));
    rot->vz = 0;
}
#endif
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_gls_800CEB2C.s")

/* register allocation differs */
#if 0 /* NON_MATCHING */
void s19b_jeep_gls_800CEC24(int z, SVECTOR *out)
{
    Work      *work;
    JEEP_ROAD *cur;
    JEEP_ROAD *near;
    JEEP_ROAD *far;
    SVECTOR    zero;
    SVECTOR    step;
    SVECTOR    tmp;
    MATRIX     mat;
    int        base;
    int        i;

    work = s19b_dword_800DE5B0;
    base = work->road[work->head].pos.vz - 2000;
    i = ((z - base) / 4000 + work->head) & 0xF;
    cur = &work->road[i];

    if (z < cur->pos.vz)
    {
        far = cur;
        near = &work->road[(i + 15) & 0xF];
    }
    else
    {
        near = cur;
        far = &work->road[(i + 1) & 0xF];
    }

    zero = DG_ZeroVector;
    step = far->step;
    tmp.vx = step.vx + near->step.vx;
    tmp.vy = step.vy + near->step.vy;
    tmp.vz = -4000;
    s19b_jeep_800D2170(&zero, &step, &tmp, mat.m[0]);
    s19b_jeep_800D21DC(((far->pos.vz - z) << 12) / 4000, &mat, out);
    GV_AddVec3(out, &far->pos, out);
}
#endif
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_gls_800CEC24.s")

/* register allocation differs */
#if 0 /* NON_MATCHING */
int s19b_jeep_gls_800CEDFC(int z, int offset)
{
    Work *work;
    int   base;
    int   i;

    work = s19b_dword_800DE5B0;
    base = work->road[work->head].pos.vz - 2000;
    i = ((z - base - offset) / 4000 + work->head) & 0xF;
    return work->road[i].attr;
}
#endif
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_gls_800CEDFC.s")

void s19b_jeep_gls_800CEE7C(Work *work, int attr, SVECTOR *pos)
{
    GCL_ARGS args;
    SVECTOR  diff;
    int      state;
    int      proc_id;
    
    Takabe_JeepSystem.field_38 = *pos;
    state = Takabe_JeepSystem.field_40;

    GV_SubVec3(pos, &Takabe_JeepSystem.pos, &diff);

    if (state == 2)
    {
        Takabe_JeepSystem.field_7C = 0;

        NewJeepGate(1, &diff, 0);
        NewJeepGate(1, &diff, 1);
        NewJeepGlass(2, &diff, 0);
        NewJeepGlass(2, &diff, 1);

        proc_id = work->proc_c70;
        if (proc_id)
        {
            args.argc = 0;
            args.argv = NULL;
            GCL_ExecProc(proc_id, &args);
        }
    }
    else if (state == 4)
    {
        Takabe_JeepSystem.field_7C = 0;

        NewJeepGate(1, &diff, 0);
        NewJeepGate(1, &diff, 1);
        NewJeepGlass(2, &diff, 0);
        NewJeepGlass(2, &diff, 1);

        proc_id = work->proc_c74;
        if (proc_id)
        {
            args.argc = 0;
            args.argv = NULL;
            GCL_ExecProc(proc_id, &args);
        }
    }
    else if (state == 5)
    {
        s19b_jeep2_800D6F24(GV_StrCode("j_liquid"), GM_CurrentMap);
    }
}

void s19b_jeep_gls_800CEFE4(Work *work, int model, SVECTOR *road_pos)
{
    SVECTOR diff;
    SVECTOR pos;

    GV_SubVec3(&Takabe_JeepSystem.field_38, &Takabe_JeepSystem.pos, &diff);

    if (model == 0)
    {
        pos.vx = diff.vx + 1562;
        pos.vy = diff.vy + 1815;
        pos.vz = diff.vz - 500;
        NewJeepLamp(&pos, PCX_JEEP_BONBORI_ADD, 0);

        pos.vx = diff.vx - 1562;
        pos.vy = diff.vy + 1815;
        pos.vz = diff.vz - 500;
        NewJeepLamp(&pos, PCX_JEEP_BONBORI_ADD, 0);
    }
}

void s19b_jeep_gls_800CF088(void)
{
    GV_ZeroMemory(&Takabe_JeepSystem, sizeof(Takabe_JeepSystem));
}
