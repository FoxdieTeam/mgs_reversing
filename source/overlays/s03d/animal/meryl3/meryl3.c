#include "common.h"
#include "game/game.h"
#include "game/camera.h"
#include "libdg/libdg.h"

typedef struct _Work
{
    GV_ACT          actor;          /* 0x000 */
    CONTROL         control;        /* 0x020 */
    OBJECT          field_9C;       /* 0x09C */
    char            pad_180[0x798 - 0x180];
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
extern int s03d_dword_800DC2F8;
extern const char s03d_dword_800DB398[];
extern GM_CameraSystemWork GM_Camera;
void s03d_800CB4B4(DG_OBJS *objs, DG_DEF *def);
void Zako_800CC480(Work *work);
void Meryl3_800CB530(Work *work);
int s03d_800CB640(Work *work);

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CB4B4.s")
void Meryl3_800CB530(Work *work)
{
    if ((GM_GameStatus & 0x50) || GM_Camera.first_person)
    {
        if (work->field_8C0 != 1)
        {
            work->field_8C0 = 1;
            s03d_800CB4B4(work->field_9C.objs, work->field_8C8);
        }
    }
    else
    {
        if (work->field_8C0 != 0)
        {
            work->field_8C0 = 0;
            s03d_800CB4B4(work->field_9C.objs, work->field_8C4);
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
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CB640.s")
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
    if (s03d_800CB640(work) < 0)
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
