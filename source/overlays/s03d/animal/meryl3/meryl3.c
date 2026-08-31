#include "meryl3.h"
#include "game/camera.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "chara/snake/shadow.h"
#include "enemy/glight.h"

/*---------------------------------------------------------------------------*/

#define BODY_DATA   GV_StrCode("mel_hei")
#define WEAPON_DATA GV_StrCode("famas")
#define LOWP_DATA   GV_StrCode("low_lit")

#define MOTION_DATA GV_StrCode("melhei03")

#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                      | DG_FLAG_GBOUND | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )
#define WEAPON_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                      | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

#define TARGET_FLAG ( TARGET_SEEK | TARGET_POWER )

/*---------------------------------------------------------------------------*/

static SVECTOR target_size = {300, 1500, 300};
static SVECTOR target_force = {0, 0, 0};

/*---------------------------------------------------------------------------*/

extern GM_CameraSystemWork GM_Camera;

extern int s03d_dword_800DC2F8;

/*---------------------------------------------------------------------------*/

static void FreeModel(DG_OBJS *objs, DG_DEF *def)
{
    DG_OBJ *obj;
    int     i;

    DG_FreeObjsPacket(objs, 0);
    DG_FreeObjsPacket(objs, 1);

    objs->def = def;
    obj = objs->objs;
    for (i = 0; i < 16; i++)
    {
        obj->model = &def->models[i];
        obj->n_packs = def->models[i].n_faces;
        obj++;
    }
}

static void SwapModel(Work *work)
{
    if ((GM_GameStatus & (STATE_BEHIND_CAMERA | STATE_CUT_IN)) || GM_Camera.first_person)
    {
        if (work->lod != 1)
        {
            work->lod = 1;
            FreeModel(work->body.objs, work->models[1]);
        }
    }
    else
    {
        if (work->lod != 0)
        {
            work->lod = 0;
            FreeModel(work->body.objs, work->models[0]);
        }
    }
}

static void Act(Work *work)
{
    GM_ActControl(&work->control);
    GM_ActObject2(&work->body);
    DG_GetLightMatrix2(&work->control.mov, work->light);

    Meryl3Act(work);
    GM_MoveTarget(work->target, &work->control.mov);

    if (s03d_dword_800DC2F8 > 6)
    {
        work->field_990++;
    }

    SwapModel(work);
}

static int CreateObjects(Work *work, int name, int where)
{
    SVECTOR  indices;
    CONTROL *control;
    OBJECT  *body, *weapon;

    control = &work->control;
    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));
    GM_ConfigControlAttribute(control, RADAR_SIGHT | RADAR_VISIBLE);
    GM_ConfigControlInterp(control, 4);
    control->seg_flag = HZD_SEG_NO_COLLIDE;

    body = &work->body;
    weapon = &work->weapon;

    GM_InitObject(body, BODY_DATA, BODY_FLAG, MOTION_DATA);
    GM_ConfigObjectJoint(body);
    GM_ConfigMotionControl(body, &work->m_ctrl, MOTION_DATA, work->m_segs1, work->m_segs2, control, work->rots);
    GM_ConfigObjectLight(body, work->light);

    work->models[1] = body->objs->def;
    work->models[0] = GV_GetCache(GV_CacheID(LOWP_DATA, 'k'));
    work->lod = 1;

    GM_InitObject(weapon, WEAPON_DATA, WEAPON_FLAG, 0);
    GM_ConfigObjectLight(weapon, work->light);
    GM_ConfigObjectRoot(weapon, body, 4);

    work->glight = NewGunLight(&body->objs->objs[4].world, 0);

    indices.vx = 0;
    indices.vy = 6;
    indices.vz = 12;
    indices.pad = 15;

    work->shadow = NewShadow(control, body, indices);
    if (work->shadow == NULL)
    {
        return -1;
    }

    return 0;
}

static void CreateTarget(Work *work)
{
    TARGET *trg;

    trg = work->target;
    GM_SetTarget(trg, TARGET_FLAG, PLAYER_SIDE, &target_size);
    GM_SetPowerTarget(trg, POWER_DECREASE, -1, 60000, 60000, &target_force);
}

static void Die(Work *work)
{
    GV_DestroyActor(work->shadow);
    GV_DestroyActor(work->glight);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeObject(&work->weapon);
    GM_FreeTarget(work->target);
}

static int GetResources(Work *work, int name, int where)
{
    if (CreateObjects(work, name, where) < 0)
    {
        return -1;
    }

    work->target = GM_AllocTarget();
    if (work->target != NULL)
    {
        CreateTarget(work);
    }

    work->action = NULL;

    work->control.mov.vx = 8000;
    work->control.mov.vy = 0;
    work->control.mov.vz = -1000;

    work->field_990 = 0;
    return 0;
}

void *NewMeryl3(int name, int where)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_PREV, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "meryl3.c");
        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}
