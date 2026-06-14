#include "common.h"
#include "game/game.h"
#include "game/camera.h"
#include "game/motion.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "chara/snake/shadow.h"
#include "enemy/glight.h"

typedef struct _Work
{
    GV_ACT          actor;          /* 0x000 */
    CONTROL         control;        /* 0x020 */
    OBJECT          field_9C;       /* 0x09C */
    MOTION_CONTROL  field_180;      /* 0x180 */
    MOTION_SEGMENT  field_1D0[17];  /* 0x1D0 */
    MOTION_SEGMENT  field_434[17];  /* 0x434 */
    SVECTOR         field_698[32];  /* 0x698 */
    MATRIX          field_798;      /* 0x798 */
    char            pad_7B8[0x7DC - 0x7B8];
    OBJECT          field_7DC;      /* 0x7DC */
    int             field_8C0;      /* 0x8C0 */
    DG_DEF         *field_8C4;      /* 0x8C4 */
    DG_DEF         *field_8C8;      /* 0x8C8 */
    TARGET         *target;         /* 0x8CC */
    char            pad_8D0[0x954 - 0x8D0];
    int             field_954;      /* 0x954 */
    char            pad_958[0x990 - 0x958];
    int             field_990;      /* 0x990 */
    char            pad_994[0x9B0 - 0x994];
    void           *field_9B0;      /* 0x9B0 */
    void           *field_9B4;      /* 0x9B4 */
} Work;

extern int s03d_dword_800C3960;
extern int s03d_dword_800C3968;
extern const char s03d_dword_800DB374[];
extern const char s03d_dword_800DB37C[];
extern const char s03d_dword_800DB388[];
extern const char s03d_dword_800DB390[];
extern int s03d_dword_800DC2F8;
extern const char s03d_dword_800DB398[];
extern GM_CameraSystemWork GM_Camera;
void Zako_800CC480(Work *work);
void Meryl3_800CB530(Work *work);

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
        obj->n_packs = *(short *)&def->model[i].n_faces;
        obj++;
    }
}
void Meryl3_800CB530(Work *work)
{
    if ((GM_GameStatus & 0x50) || GM_Camera.first_person)
    {
        if (work->field_8C0 != 1)
        {
            work->field_8C0 = 1;
            Meryl3_800CB4B4(work->field_9C.objs, work->field_8C8);
        }
    }
    else
    {
        if (work->field_8C0 != 0)
        {
            work->field_8C0 = 0;
            Meryl3_800CB4B4(work->field_9C.objs, work->field_8C4);
        }
    }
}
void Meryl3_800CB5B4(Work *work)
{
    GM_ActControl(&work->control);
    GM_ActObject2(&work->field_9C);
    DG_GetLightMatrix2(&work->control.mov, &work->field_798);
    Zako_800CC480(work);
    GM_MoveTarget(work->target, &work->control.mov);
    if (s03d_dword_800DC2F8 >= 7)
    {
        work->field_990++;
    }
    Meryl3_800CB530(work);
}
int Meryl3_800CB640(Work *work, int scriptData, int scriptBinds)
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

    head = &work->field_9C;
    body = &work->field_7DC;
    ctl->seg_flag = 1;
    strcode = GV_StrCode(s03d_dword_800DB374);
    GM_InitObject(head, strcode, 0x32D, GV_StrCode(s03d_dword_800DB37C));
    GM_ConfigObjectJoint(head);
    GM_ConfigMotionControl(head, &work->field_180, GV_StrCode(s03d_dword_800DB37C),
                           &work->field_1D0[0], &work->field_434[0], ctl, work->field_698);
    GM_ConfigObjectLight(head, &work->field_798);

    work->field_8C8 = head->objs->def;
    work->field_8C4 = GV_GetCache(GV_CacheID(GV_StrCode(s03d_dword_800DB388), 0x6B));
    work->field_8C0 = 1;
    GM_InitObject(body, GV_StrCode(s03d_dword_800DB390), 0x6D, 0);
    GM_ConfigObjectLight(body, &work->field_798);
    GM_ConfigObjectRoot(body, head, 4);
    work->field_9B4 = NewGunLight(&head->objs->objs[4].world, 0);

    indices.vx = 0;
    indices.vy = 6;
    indices.vz = 0xC;
    indices.pad = 0xF;
    work->field_9B0 = NewShadow(ctl, head, indices);
    if (work->field_9B0 == 0)
    {
        return -1;
    }
    return 0;
}
void Meryl3_800CB834(Work *work)
{
    TARGET *t = work->target;

    GM_SetTarget(t, 0x14, 1, (SVECTOR *)&s03d_dword_800C3960);
    GM_SetPowerTarget(t, 1, -1, 0xEA60, 0xEA60, (SVECTOR *)&s03d_dword_800C3968);
}

void Meryl3_800CB894(Work *work)
{
    GV_DestroyActor(work->field_9B0);
    GV_DestroyActor(work->field_9B4);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->field_9C);
    GM_FreeObject(&work->field_7DC);
    GM_FreeTarget(work->target);
}

int Meryl3_800CB8F0(Work *work, int arg1, int arg2)
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
    Work *work = GV_NewActor(4, 0x9B8);

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
