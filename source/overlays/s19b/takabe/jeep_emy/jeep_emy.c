#include <rand.h>

#include "linkvar.h"
#include "strcode.h"
#include "game/game.h"
#include "libgcl/libgcl.h"
#include "takabe/thing.h"

typedef struct _JEEP_SYSTEM
{
    char     pad1[0x4];
    CONTROL *control;
    char     pad2[0x10];
    SVECTOR  pos;
    char     pad3[0x40];
    OBJECT  *body;
    char     pad4[0x18];
    int      field_7C;
    MATRIX   world;
} JEEP_SYSTEM;

extern JEEP_SYSTEM s19b_dword_800DE658; // Takabe_JeepSystem

typedef struct _Work
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         body;
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT m_segs1[16 + 1];
    MOTION_SEGMENT m_segs2[16 + 1];
    SVECTOR        rots[16];
    SVECTOR        adjust[16];
    MATRIX         light[2];
    OBJECT         weapon;
    int            lod;
    DG_DEF        *models[2];
    TARGET        *target1;
    TARGET        *target2;
    HOMING        *hom;
    char           pad1[0xC];
    int            field_8E0;
    SVECTOR        field_8E4;
    SVECTOR        field_8EC;
    SVECTOR        field_8F4;
    int            field_8FC;
    SVECTOR        field_900[4];
    void          *field_920;
    char           pad2[0x4];
    int            field_928;
    char           pad3[0x8];
    int            field_934;
    char           pad4[0x4];
    int            field_93C;
    char           pad5[0x4];
    int            field_944;
    int            field_948;
    int            field_94C;
    char           pad6[0x44];
} Work;

extern GM_CAMERA GM_Camera;

extern SVECTOR s19b_dword_800DE670;
extern SVECTOR s19b_dword_800DE690;

void s01a_800E2364(MATRIX *mtx, SVECTOR *in, VECTOR *out);
void *NewJeepBlood(MATRIX *world, int count, MATRIX *root);

void s19b_jbullet_800C5560(void);
void s19b_jbullet_800C5654(void);
void s19b_jbullet_800C5714(void);
void s19b_jbullet_800C58CC(void);
void s19b_jbullet_800C598C(void);
void s19b_jbullet_800C5F7C(void *);

#define EXEC_LEVEL 5

#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND )
#define WEAPON_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

static void Act(Work *work)
{
    VECTOR   scale = {2048, 2048, 2048};
    VECTOR   player_dist;
    CONTROL *control;
    SVECTOR *vec;
    int      i;
    int      update;
    int      dist;
    DG_DEF  *def;
    DG_MDL  *mdl;
    DG_OBJ  *obj;
    int      n_models;

    control = &work->control;
    GV_AddVec3(&control->mov, &s19b_dword_800DE670, &control->mov);
    GV_AddVec3(&work->field_8EC, &s19b_dword_800DE670, &work->field_8EC);
    GV_AddVec3(&work->field_8F4, &s19b_dword_800DE670, &work->field_8F4);

    vec = work->field_900;
    for (i = work->field_8FC; i > 0; i--, vec++)
    {
        GV_AddVec3(vec, &s19b_dword_800DE670, vec);
    }

    if (control->mov.vz > 16000)
    {
        GV_DestroyActor(work);
    }

    GM_ActMotion(&work->body);

    if (work->field_8E0 != 0)
    {
        control->step.vx = work->field_8E4.vx;
        control->step.vz = work->field_8E4.vz;
    }

    update = 0;

    control->height = work->body.height / 2;
    control->step.vx /= 2;
    control->step.vy /= 2;
    control->step.vz /= 2;

    GM_ActControl(control);
    GM_ActObject(&work->body);

    ScaleMatrix(&work->body.objs->world, &scale);
    DG_GetLightMatrix(&control->mov, work->light);

    GM_MoveTarget(work->target1, &work->control.mov);
    GM_MoveTarget(work->target2, &work->control.mov);

    s19b_jbullet_800C5F7C(work);
    s01a_800E2364(&DG_Chanl(0)->eye, &control->mov, &player_dist);

    if (player_dist.vz > 0)
    {
        dist = (GM_Camera.zoom * 1000) / player_dist.vz;
    }
    else
    {
        dist = 32000;
    }

    if (dist < 64)
    {
        if (work->lod == 0)
        {
            work->lod = 1;
            update = 1;
        }
    }
    else
    {
        if (work->lod == 1)
        {
            work->lod = 0;
            update = 1;
        }
    }

    if (update)
    {
        DG_FreeObjsPacket(work->body.objs, 0);
        DG_FreeObjsPacket(work->body.objs, 1);

        def = work->models[work->lod];
        work->body.objs->def = def;

        mdl = def->model;
        obj = work->body.objs->objs;
        for (n_models = def->n_models; n_models > 0; n_models--)
        {
            obj->n_packs = mdl->n_faces;
            obj->model = mdl;
            mdl++;
            obj++;
        }
    }
}

static void GetMidpoint(SVECTOR *vec)
{
    vec->vx /= 2;
    vec->vy /= 2;
    vec->vz /= 2;
    GV_AddVec3(vec, &s19b_dword_800DE690, vec);
}

static int GetResources(Work *work, int name, int where)
{
    CONTROL *control;
    char    *pos;
    char    *dir;
    SVECTOR *vec;
    int      i;
    OBJECT  *body;
    OBJECT  *weapon;

    control = &work->control;
    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    pos = GCL_GetOption('p');
    dir = GCL_GetOption('d');
    GM_ConfigControlString(control, pos, dir);
    GM_ConfigControlAttribute(control, RADAR_SIGHT | RADAR_VISIBLE);
    GM_ConfigControlInterp(control, 4);

    work->field_8FC = THING_Gcl_GetInt('n');
    if ((work->field_8FC > 0) && GCL_GetOption('a'))
    {
        vec = work->field_900;
        for (i = work->field_8FC; i > 0; i--, vec++)
        {
            GCL_StrToSV(GCL_GetParamResult(), vec);
            GetMidpoint(vec);
        }
    }

    GetMidpoint(&control->mov);

    body = &work->body;
    weapon = &work->weapon;

    GM_InitObject(body, KMD_IPPANHEI, BODY_FLAG, OAR_ENEMY);
    GM_ConfigObjectJoint(body);
    GM_ConfigMotionControl(body, &work->m_ctrl, OAR_ENEMY, work->m_segs1, work->m_segs2, control, work->rots);
    GM_ConfigObjectLight(body, work->light);

    work->models[0] = body->objs->def;
    work->models[1] = GV_GetCache(GV_CacheID(KMD_LOW_109P, 'k'));

    GM_InitObject(weapon, KMD_FAMAS, WEAPON_FLAG, 0);
    GM_ConfigObjectLight(weapon, work->light);
    GM_ConfigObjectRoot(weapon, body, 4);

    work->target1 = GM_AllocTarget();
    work->target2 = GM_AllocTarget();

    work->hom = GM_AllocHomingTarget(&body->objs->world, &work->control);
    if (work->hom)
    {
        work->hom->flag = 1;
    }

    control->step_size = -1;

    work->field_944 = 0;
    work->field_948 = 0;
    work->field_94C = 0;

    work->field_8EC = control->mov;
    work->field_8F4 = work->field_900[0];

    return 0;
}

static void Die(Work *work)
{
    GM_FreeTarget(work->target1);
    GM_FreeTarget(work->target2);
    GM_FreeHomingTarget(work->hom);
    GM_FreeObject(&work->weapon);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
}

void *NewJeepEnemy(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(work, Act, Die, "jeep_emy.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return 0;
        }
    }

    return work;
}

/* TODO: Fix */
int s19b_dword_800C32BC = 0x01433201;
int s19b_dword_800C32C0 = 0x000A0013;
int s19b_dword_800C32C4 = 0x00090016;
int s19b_dword_800C32C8 = 0x001B0008;
int s19b_dword_800C32CC = 0x00070003;
int s19b_dword_800C32D0 = 0x00180026;
int s19b_dword_800C32D4 = 0x00110017;
int s19b_dword_800C32D8 = 0x002B0012;
int s19b_dword_800C32DC = 0x00000016;

static SVECTOR s19b_dword_800C32E0 = {0, 0, 100};
static SVECTOR s19b_dword_800C32E8 = {-1024, 0, 0};

void s19b_jbullet_800C4F54(Work *work, int unit, int count)
{
    MATRIX  matrix;
    MATRIX *root;

    root = &work->body.objs->objs[unit].world;
    DG_SetPos(root);
    DG_MovePos(&s19b_dword_800C32E0);
    DG_RotatePos(&s19b_dword_800C32E8);
    ReadRotMatrix(&matrix);
    NewJeepBlood(&matrix, count, root);
}

int s19b_jbullet_800C4FD4(SVECTOR *vec)
{
    return abs(vec->vx) + abs(vec->vy) + abs(vec->vz);
}

int s19b_jbullet_800C5010(Work *work)
{
    SVECTOR sp10;
    TARGET *trg;
    int     len;

    trg = work->target1;
    if (trg->damaged & TARGET_POWER)
    {
        if (trg->a_mode == 1)
        {
            trg->scale = DG_ZeroVector;

            if (trg->life <= 0)
            {
                work->field_934 = 0;
                work->field_920 = s19b_jbullet_800C598C;
            }
            else
            {
                work->field_920 = s19b_jbullet_800C58CC;
            }

            work->field_928 = 0;

            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
        else
        {
            trg->scale = DG_ZeroVector;
            trg->life_lost = 0;
            trg->damaged = 0;
            goto check_next;
        }

        trg->life_lost = 0;
        trg->damaged = 0;

        work->field_8F4 = work->field_900[(rand() * work->field_8FC) >> 15];

        s19b_dword_800DE658.field_7C = 1;
        return 1;
    }

check_next:
    trg = work->target2;
    if (trg->damaged & TARGET_POWER)
    {
        if (trg->a_mode == 2)
        {
            sp10.vx = trg->scale.vx;
            sp10.vy = 0;
            sp10.vz = trg->scale.vz;

            len = s19b_jbullet_800C4FD4(&trg->scale);
            GV_LenVec3(&sp10, &work->field_8E4, GV_VecLen3(&sp10), len / 4);

            work->field_8E0 = 1;

            if (len < 100)
            {
                work->field_934 = 2;
            }
            else
            {
                work->field_934 = 1;
            }

            work->field_920 = s19b_jbullet_800C598C;
            work->field_928 = 0;

            work->control.turn.vz = 0;
            work->control.turn.vx = 0;

            work->target1->life = 0;
        }
        else
        {
            trg->life = 100;
            trg->scale = DG_ZeroVector;
            return 0;
        }

        trg->life_lost = 0;
        trg->damaged = 0;
        return 1;
    }

    return 0;
}

int s19b_jbullet_800C5258(Work *work)
{
    return s19b_jbullet_800C5010(work) != 0;
}

static SVECTOR s19b_dword_800C32F0 = {200, 500, 200};
static SVECTOR s19b_dword_800C32F8 = {0, 0, 0};

void s19b_jbullet_800C5278(Work *work)
{
    TARGET *trg;
    int     life;

    trg = work->target1;

    if (GM_DifficultyFlag > DIFFICULTY_EASY)
    {
        life = 255 + GM_DifficultyFlag * 64;
    }
    else
    {
        life = 255;
    }


    GM_SetTarget(trg, (TARGET_POWER | TARGET_SEEK), ENEMY_SIDE, &s19b_dword_800C32F0);
    GM_Target_8002DCCC(trg, 1, -1, life, 7, &s19b_dword_800C32F8);

    trg = work->target2;
    GM_SetTarget(trg, (TARGET_POWER | TARGET_SEEK), ENEMY_SIDE, &s19b_dword_800C32F0);
    GM_Target_8002DCCC(trg, 1, -1, 100, 0, &s19b_dword_800C32F8);
}

int s19b_jbullet_800C5348(Work *work)
{
    if (work->field_93C & 0x4)
    {
        work->field_920 = s19b_jbullet_800C5654;
        work->field_928 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }

    if (work->field_93C & 0x1)
    {
        work->field_920 = s19b_jbullet_800C5714;
        work->field_928 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }

    if (work->field_93C & 0x100)
    {
        work->field_920 = s19b_jbullet_800C5560;
        work->field_928 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }

    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C53C0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C543C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C54D0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5560.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5654.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5714.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C57E8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C58CC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C598C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5C50.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5D18.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5E40.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5E60.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5F2C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5F7C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5FB0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C63DC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C6404.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C6428.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C645C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C649C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C6524.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C65A8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C666C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C66BC.s")
