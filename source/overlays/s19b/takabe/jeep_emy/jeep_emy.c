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

extern JEEP_SYSTEM s19b_dword_800DE658; /* Takabe_JeepSystem */

struct _Work;
typedef void (*JBULLET_FN)(struct _Work *, int);

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
    int            field_8D4;
    char           pad1[0x8];
    int            field_8E0;
    SVECTOR        field_8E4;
    SVECTOR        field_8EC;
    SVECTOR        field_8F4;
    int            field_8FC;
    SVECTOR        field_900[4];
    JBULLET_FN     field_920;
    char           pad2[0x4];
    int            field_928;
    char           pad3[0x4];
    int            field_930;
    int            field_934;
    int            field_938;
    int            field_93C;
    int            field_940;
    int            field_944;
    int            field_948;
    int            field_94C;
    int            field_950;
    int            field_954;
    char           pad4[0xC];
    int            field_964;
    int            field_968;
    char           pad5[0x28];
} Work;

/* unused */
u_short s19b_dword_800C32BC[] = {0x3201, 0x0143};

static short s19b_dword_800C32C0[] =
{
    19, 10, 22, 9, 8, 27, 3, 7, 38, 24, 23, 17, 18, 43, 22
};

static SVECTOR s19b_dword_800C32E0 = {0, 0, 100};
static SVECTOR s19b_dword_800C32E8 = {-1024, 0, 0};
static SVECTOR s19b_dword_800C32F0 = {200, 500, 200};
static SVECTOR s19b_dword_800C32F8 = {0, 0, 0};
static SVECTOR s19b_dword_800C3300 = {5, -500, 80};

extern GM_CAMERA GM_Camera;

extern SVECTOR s19b_dword_800DE670;
extern SVECTOR s19b_dword_800DE690;

void s01a_800E2364(MATRIX *mtx, SVECTOR *in, VECTOR *out);
void *NewJeepBlood(MATRIX *world, int count, MATRIX *root);
void *NewJeepBullet2(MATRIX *world, int side, int mode, int mode2);
void Voicesys_800CE2D0(void);
void AN_Unknown_800CA1EC(MATRIX *, int);

/* BUG: bad declaration, should have int arg1 */
void s19b_jblood_800C8128(MATRIX *world);
void s19b_jblood_800C7FB8(MATRIX *world);

void s19b_jbullet_800C5560(Work *work, int);
void s19b_jbullet_800C5654(Work *work, int);
void s19b_jbullet_800C5714(Work *work, int);
void s19b_jbullet_800C57E8(Work *work, int arg1);
void s19b_jbullet_800C58CC(Work *work, int);
void s19b_jbullet_800C598C(Work *work, int);
void s19b_jbullet_800C5C50(Work *work, int);
void s19b_jbullet_800C5D18(Work *work, int);
void s19b_jbullet_800C5E40(Work *work, int);
void s19b_jbullet_800C5F7C(Work *work);
void s19b_jbullet_800C66BC(Work *work);

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

void s19b_jbullet_800C53C0(Work *work)
{
    int height;
    int ang;

    height = GM_PlayerBody->objs->objs[6].world.t[1] - work->body.objs->objs[6].world.t[1];
    ang = (ratan2(work->field_968, height) & 0xFFF) - 1024;

    work->adjust[2].vx = ang;
    work->adjust[6].vx = ang;

    if (ang < 0)
    {
        work->adjust[7].vx = ang * 3;
    }
    else
    {
        work->adjust[7].vx = (ang * 3) / 2;
    }
}

void s19b_jbullet_800C543C(Work *work)
{
    MATRIX  world;
    MATRIX *head;

    head = &work->body.objs->objs[4].world;

    DG_SetPos(head);
    DG_MovePos(&s19b_dword_800C3300);
    ReadRotMatrix(&world);
    RotMatrixY(GV_RandU(16), &world);

    NewJeepBullet2(&world, ENEMY_SIDE, 1, 0);
    GM_SeSet(&work->control.mov, SE_GUNCAM_SHOT);

    s19b_jblood_800C8128(head);
    s19b_jblood_800C7FB8(&world);
}

void s19b_jbullet_800C54D0(Work *work, int arg1)
{
    CONTROL *control;

    control = &work->control;

    if (arg1 == 0)
    {
        work->field_930 = 0;
        GM_ConfigObjectAction(&work->body, s19b_dword_800C32C0[0], 0, 4);
    }

    if (!s19b_jbullet_800C5258(work) && !s19b_jbullet_800C5348(work))
    {
        control->turn.vy = work->field_940;
        work->target1->class |= ( TARGET_POWER | TARGET_SEEK );
    }
}

void s19b_jbullet_800C5560(Work *work, int arg1)
{
    CONTROL *control;

    control = &work->control;

    if (arg1 == 0)
    {
        work->field_930 = 4;
        GM_ConfigObjectAction(&work->body, s19b_dword_800C32C0[4], 0, 4);
        AN_Unknown_800CA1EC(&work->body.objs->objs[6].world, 0);

        GM_SeSet2(0, 63, SE_ALERT_SIREN);

        if (s19b_dword_800DE658.field_7C == 0)
        {
            Voicesys_800CE2D0();
        }

        s19b_dword_800DE658.field_7C = 1;
    }

    work->target1->class |= ( TARGET_POWER | TARGET_SEEK );

    if (!s19b_jbullet_800C5258(work))
    {
        control->turn.vy = work->field_940;

        if (work->body.is_end)
        {
            work->field_920 = s19b_jbullet_800C54D0;
            work->field_928 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
    }
}

void s19b_jbullet_800C5654(Work *work, int arg1)
{
    CONTROL *control;
    int      turn;

    control = &work->control;
    turn = work->field_940;

    if (arg1 == 0)
    {
        work->field_930 = 1;
        GM_ConfigObjectAction(&work->body, s19b_dword_800C32C0[1], 0, 4);
    }

    work->target1->class |= ( TARGET_POWER | TARGET_SEEK );

    if (!s19b_jbullet_800C5258(work))
    {
        if (!(work->field_93C & 4))
        {
            if (!s19b_jbullet_800C5348(work))
            {
                work->field_920 = s19b_jbullet_800C54D0;
                work->field_928 = 0;
                work->control.turn.vz = 0;
                work->control.turn.vx = 0;
            }
        }
        else
        {
            control->turn.vy = turn;
        }
    }
}

void s19b_jbullet_800C5714(Work *work, int arg1)
{
    int temp_s2;

    temp_s2 = work->field_93C;

    if (arg1 == 0)
    {
        work->field_930 = 2;
        GM_ConfigObjectAction(&work->body, s19b_dword_800C32C0[2], 0, 4);
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }

    s19b_jbullet_800C53C0(work);
    work->target1->class |= ( TARGET_POWER | TARGET_SEEK );

    if (!s19b_jbullet_800C5258(work))
    {
        if (!(temp_s2 & 1))
        {
            work->field_920 = s19b_jbullet_800C54D0;
            work->field_928 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
        else if (temp_s2 & 2)
        {
            work->field_920 = s19b_jbullet_800C57E8;
            work->field_928 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
        else
        {
            work->control.turn.vy = work->field_964;
        }
    }
}

void s19b_jbullet_800C57E8(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_930 = 2;
        GM_ConfigObjectAction(&work->body, s19b_dword_800C32C0[2], 0, 4);
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }

    if ((arg1 == 5) || (arg1 == 8) || (arg1 == 11))
    {
        s19b_jbullet_800C543C(work);
    }

    work->target1->class |= ( TARGET_POWER | TARGET_SEEK );

    if (!s19b_jbullet_800C5258(work))
    {
        s19b_jbullet_800C53C0(work);
        work->control.turn.vy = work->field_964;

        if (arg1 > 18)
        {
            work->field_920 = s19b_jbullet_800C5714;
            work->field_928 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
    }
}

void s19b_jbullet_800C58CC(Work *work, int arg1)
{
    if (arg1 > 8)
    {
        work->target1->class |= ( TARGET_POWER | TARGET_SEEK );
    }

    if (!s19b_jbullet_800C5258(work))
    {
        if (arg1 == 0)
        {
            work->field_930 = 5;
            GM_ConfigObjectAction(&work->body, s19b_dword_800C32C0[5], 0, 4);
            GM_SeSet(&work->control.mov, SE_ENEMY_DAMAGE);
            s19b_jbullet_800C4F54(work, 5, 1);
        }

        if (work->body.is_end)
        {
            work->field_920 = s19b_jbullet_800C54D0;
            work->field_928 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
    }
}

void s19b_jbullet_800C598C(Work *work, int arg1)
{
    work->control.step_size = 500;
    work->control.step = work->target1->scale;

    if (arg1 == 0)
    {
        switch (work->field_934)
        {
        case 0:
            work->field_930 = 6;
            GM_ConfigObjectAction(&work->body, s19b_dword_800C32C0[6], 0, 4);

            if (work->target1->life <= 0)
            {
                s19b_jbullet_800C4F54(work, 6, 1);
            }
            else
            {
                s19b_jbullet_800C4F54(work, 5, 0);
            }

            work->field_938 = 46;
            break;
        case 2:
            work->field_930 = 7;
            GM_ConfigObjectAction(&work->body, s19b_dword_800C32C0[7], 0, 4);
            s19b_jbullet_800C4F54(work, 5, 0);
            work->field_938 = 14;
            break;
        case 1:
            work->field_930 = 8;
            GM_ConfigObjectAction(&work->body, s19b_dword_800C32C0[8], 0, 4);
            s19b_jbullet_800C4F54(work, 5, 0);
            work->field_938 = 22;
            break;
        }

        GM_SeSet(&work->control.mov, SE_ENEMY_DAMAGE);
        GM_TotalEnemiesKilled++;
    }

    switch (work->field_934)
    {
    case 0:
        if (arg1 == 24)
        {
            GM_SeSet(&work->control.mov, SE_ENEMY_COLLAPSE);
        }
        break;
    case 2:
        if (arg1 == 17)
        {
            work->field_8E0 = 0;
        }
        break;
    case 1:
        if (arg1 == 37)
        {
            work->field_8E0 = 0;
        }
        break;
    }

    if ((arg1 > 16) && (work->control.level_flag != 0))
    {
        work->control.step = DG_ZeroVector;
    }

    if (arg1 == work->field_938)
    {
        GM_SeSet(&work->control.mov, SE_HIT_FLOOR);
    }

    if (work->body.is_end)
    {
        work->control.step_size = -1;
        work->target1->scale = DG_ZeroVector;

        if (work->target1->life <= 0)
        {
            work->field_920 = s19b_jbullet_800C5D18;
        }
        else
        {
            work->field_920 = s19b_jbullet_800C5C50;
        }

        work->field_928 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void s19b_jbullet_800C5C50(Work *work, int arg1)
{
    work->target1->class |= ( TARGET_POWER | TARGET_SEEK );

    if (s19b_jbullet_800C5258(work) == 0)
    {
        if (arg1 == 0)
        {
            switch (work->field_934)
            {
            case 2:
                work->field_930 = 9;
                GM_ConfigObjectAction(&work->body, s19b_dword_800C32C0[9], 0, 4);
                break;
            case 1:
                work->field_930 = 10;
                GM_ConfigObjectAction(&work->body, s19b_dword_800C32C0[10], 0, 4);
                break;
            }
        }

        if (work->body.is_end)
        {
            work->field_920 = s19b_jbullet_800C54D0;
            work->field_928 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
    }
}

void s19b_jbullet_800C5D18(Work *work, int arg1)
{
    work->hom->flag = 0;

    if (arg1 == 0)
    {
        if (work->field_934 < 2)
        {
            if (work->field_934 == 0)
            {
                work->field_930 = 13;
                GM_ConfigObjectAction(&work->body, s19b_dword_800C32C0[13], 0, 4);

            }
            else
            {
                work->field_930 = 11;
                GM_ConfigObjectAction(&work->body, s19b_dword_800C32C0[11], 0, 4);
            }
        }
        else
        {
            work->field_930 = 12;
            GM_ConfigObjectAction(&work->body, s19b_dword_800C32C0[12], 0, 4);
        }

        DG_InvisibleObjs(work->weapon.objs);
        GM_ConfigControlAttribute(&work->control, 0);
        work->target1->class = TARGET_AVAIL;
    }

    if (arg1 & 0x2)
    {
        DG_InvisibleObjs(work->body.objs);
    }
    else
    {
        DG_VisibleObjs(work->body.objs);
    }

    if (arg1 > 32)
    {
        work->field_920 = s19b_jbullet_800C5E40;
        work->field_928 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void s19b_jbullet_800C5E40(Work *work, int arg1)
{
    GV_DestroyActor(work);
}

void s19b_jbullet_800C5E60(Work *work)
{
    CONTROL   *control;
    OBJECT    *body;
    JBULLET_FN callback;
    int        count;

    control = &work->control;
    body = &work->body;

    work->target1->class = TARGET_AVAIL;

    callback = work->field_920;
    count = work->field_928++;

    if (callback == NULL)
    {
        s19b_jbullet_800C5278(work);
        callback = s19b_jbullet_800C54D0;
        work->field_920 = callback;
    }

    callback(work, count);
    control->height = body->height;

    if ((work->field_8D4 < 0) && (control->level_flag != 0))
    {
        work->field_8D4 = 0;
    }

    work->field_8D4 -= 16;
    control->step.vy = work->field_8D4;
}

void s19b_jbullet_800C5F2C(Work *work)
{
    SVECTOR diff;

    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &diff);
    diff.vy = 0;

    work->field_964 = GV_VecDir2(&diff);
    work->field_968 = GV_VecLen3(&diff);
}

void s19b_jbullet_800C5F7C(Work *work)
{
    s19b_jbullet_800C5F2C(work);
    s19b_jbullet_800C66BC(work);
    s19b_jbullet_800C5E60(work);
}
