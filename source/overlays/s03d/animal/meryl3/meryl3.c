#include "meryl3.h"
#include "game/camera.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "chara/snake/shadow.h"
#include "enemy/glight.h"

extern int s03d_dword_800C3960;
extern int s03d_dword_800C3968;
extern const char s03d_dword_800DB374[];
extern const char s03d_dword_800DB37C[];
extern const char s03d_dword_800DB388[];
extern const char s03d_dword_800DB390[];
extern int s03d_dword_800DC2F8;
extern const char s03d_dword_800DB398[];
extern GM_CameraSystemWork GM_Camera;
void Zako_800CC480(Meryl3Work *work);
void Meryl3_800CB530(Meryl3Work *work);

void Meryl3_800CB4B4(DG_OBJS *objs, DG_DEF *def)
{
    int i;
    DG_OBJ *obj;

    DG_FreeObjsPacket(objs, 0);
    DG_FreeObjsPacket(objs, 1);
    objs->def = def;
    obj = objs->objs;
    for (i = 0; i < 16; i++)
    {
        obj->model = &def->model[i];
        obj->n_packs = def->model[i].n_faces;
        obj++;
    }
}
void Meryl3_800CB530(Meryl3Work *work)
{
    if ((GM_GameStatus & 0x50) || GM_Camera.first_person)
    {
        if (work->lod != 1)
        {
            work->lod = 1;
            Meryl3_800CB4B4(work->body.objs, work->models[1]);
        }
    }
    else
    {
        if (work->lod != 0)
        {
            work->lod = 0;
            Meryl3_800CB4B4(work->body.objs, work->models[0]);
        }
    }
}
void Meryl3_800CB5B4(Meryl3Work *work)
{
    GM_ActControl(&work->control);
    GM_ActObject2(&work->body);
    DG_GetLightMatrix2(&work->control.mov, work->light);
    Zako_800CC480(work);
    GM_MoveTarget(work->target, &work->control.mov);
    if (s03d_dword_800DC2F8 >= 7)
    {
        work->field_990++;
    }
    Meryl3_800CB530(work);
}
int Meryl3_800CB640(Meryl3Work *work, int scriptData, int scriptBinds)
{
    CONTROL *ctl = &work->control;
    OBJECT  *head;
    OBJECT  *body;
    char    *opt_p;
    int      strcode;
    SVECTOR  indices;

    if (GM_InitControl(ctl, scriptData, scriptBinds) < 0)
    {
        return -1;
    }
    opt_p = GCL_GetOption('p');
    GM_ConfigControlString(ctl, opt_p, GCL_GetOption('d'));
    GM_ConfigControlAttribute(ctl, 5);
    GM_ConfigControlInterp(ctl, 4);

    head = &work->body;
    body = &work->weapon;
    ctl->seg_flag = 1;
    strcode = GV_StrCode(s03d_dword_800DB374);
    GM_InitObject(head, strcode, 0x32D, GV_StrCode(s03d_dword_800DB37C));
    GM_ConfigObjectJoint(head);
    GM_ConfigMotionControl(head, &work->m_ctrl, GV_StrCode(s03d_dword_800DB37C),
                           &work->m_segs1[0], &work->m_segs2[0], ctl, work->rots);
    GM_ConfigObjectLight(head, work->light);

    work->models[1] = head->objs->def;
    work->models[0] = GV_GetCache(GV_CacheID(GV_StrCode(s03d_dword_800DB388), 0x6B));
    work->lod = 1;
    GM_InitObject(body, GV_StrCode(s03d_dword_800DB390), 0x6D, 0);
    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectRoot(body, head, 4);
    work->glight = NewGunLight(&head->objs->objs[4].world, 0);

    indices.vx = 0;
    indices.vy = 6;
    indices.vz = 0xC;
    indices.pad = 0xF;
    work->shadow = NewShadow(ctl, head, indices);
    if (work->shadow == 0)
    {
        return -1;
    }
    return 0;
}
void Meryl3_800CB834(Meryl3Work *work)
{
    TARGET *t = work->target;

    GM_SetTarget(t, 0x14, 1, (SVECTOR *)&s03d_dword_800C3960);
    GM_SetPowerTarget(t, 1, -1, 0xEA60, 0xEA60, (SVECTOR *)&s03d_dword_800C3968);
}

void Meryl3_800CB894(Meryl3Work *work)
{
    GV_DestroyActor(work->shadow);
    GV_DestroyActor(work->glight);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeObject(&work->weapon);
    GM_FreeTarget(work->target);
}

int Meryl3_800CB8F0(Meryl3Work *work, int arg1, int arg2)
{
    if (Meryl3_800CB640(work, arg1, arg2) < 0)
    {
        return -1;
    }
    work->target = GM_AllocTarget();
    if (work->target != NULL)
    {
        Meryl3_800CB834(work);
    }
    work->control.mov.vx = 0x1F40;
    work->field_954 = 0;
    work->control.mov.vy = 0;
    work->control.mov.vz = -0x3E8;
    work->field_990 = 0;
    return 0;
}
void *Meryl3_800CB954(int arg0, int arg1)
{
    Meryl3Work *work = GV_NewActor(GV_ACTOR_PREV, sizeof(Meryl3Work));

    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Meryl3_800CB5B4, Meryl3_800CB894, s03d_dword_800DB398);
        if (Meryl3_800CB8F0(work, arg0, arg1) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
