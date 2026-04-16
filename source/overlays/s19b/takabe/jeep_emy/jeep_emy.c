#include "game/game.h"
#include "libgcl/libgcl.h"
#include "takabe/thing.h"
#include "strcode.h"

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
    int            field_8E4;
    int            field_8E8;
    SVECTOR        field_8EC;
    SVECTOR        field_8F4;
    int            field_8FC;
    SVECTOR        field_900[8];
    char           pad2[0x4];
    int            field_944;
    int            field_948;
    int            field_94C;
    char           pad3[0x44];
} Work;

extern GM_CAMERA GM_Camera;

extern SVECTOR s19b_dword_800DE670;
extern SVECTOR s19b_dword_800DE690;

void s01a_800E2364(MATRIX *mtx, SVECTOR *in, VECTOR *out);
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
        control->step.vx = work->field_8E4;
        control->step.vz = work->field_8E8;
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
