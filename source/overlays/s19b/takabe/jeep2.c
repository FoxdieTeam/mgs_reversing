#include "common.h"
#include "game/game.h"

typedef struct _Jeep2Work
{
    /* +0x000 */ GV_ACT         actor;
    /* +0x020 */ void          *field_20;
    /* +0x024 */ CONTROL        control;
    /* +0x0A0 */ TARGET        *target;
    /* +0x0A4 */ OBJECT         jeep_b;
    /* +0x188 */ OBJECT         jeep_t;
    /* +0x26C */ OBJECT_NO_ROTS gun;
    /* +0x290 */ MATRIX         light[2];
    /* +0x2D0 */ OBJECT_NO_ROTS fhl;
    /* +0x2F4 */ OBJECT_NO_ROTS hl;
    /* +0x318 */ MATRIX         light2;
                 char           pad_338[0x358 - 0x318 - sizeof(MATRIX)];
    /* +0x358 */ VECTOR         field_358;
    /* +0x368 */ VECTOR         field_368;
    /* +0x378 */ SVECTOR        field_378;
    /* +0x380 */ SVECTOR        field_380;
    /* +0x388 */ SVECTOR        field_388;
    /* +0x390 */ SVECTOR        field_390;
                 char           pad_398[0x3A0 - 0x390 - sizeof(SVECTOR)];
    /* +0x3A0 */ int            field_3A0;
    /* +0x3A4 */ int            field_3A4;
    /* +0x3A8 */ int            field_3A8;
                 char           pad_3AC[0x3B0 - 0x3A8 - sizeof(int)];
    /* +0x3B0 */ int            field_3B0;
    /* +0x3B4 */ int            field_3B4;
    /* +0x3B8 */ int            field_3B8;
                 char           pad_3BC[0x3C4 - 0x3B8 - sizeof(int)];
    /* +0x3C4 */ int            field_3C4;
    /* +0x3C8 */ int            field_3C8;
    /* +0x3CC */ int            field_3CC;
    /* +0x3D0 */ void          *field_3D0;
    /* +0x3D4 */ int            field_3D4;
    /* +0x3D8 */ int            field_3D8;
    /* +0x3DC */ void          *field_3DC;
    /* +0x3E0 */ int            field_3E0;
    /* +0x3E4 */ int            field_3E4;
    /* +0x3E8 */ void          *field_3E8;
    /* +0x3EC */ int            field_3EC;
    /* +0x3F0 */ int            field_3F0;
    /* +0x3F4 */ int            field_3F4;
    /* +0x3F8 */ void          *field_3F8;
} Jeep2Work;

typedef struct _JEEP_SYSTEM
{
    char     pad_0[0xC];
    int      field_C;    /* 0x0C */
    CONTROL *field_10;   /* 0x10 */
    SVECTOR *field_14;   /* 0x14 */
    char     pad_18[0x28 - 0x14 - sizeof(SVECTOR *)];
    VECTOR   field_28;   /* 0x28 */
    char     pad_38[0x54 - 0x28 - sizeof(VECTOR)];
    int      field_54;   /* 0x54 */
    char     pad_58[0x70 - 0x54 - sizeof(int)];
    OBJECT  *field_70;   /* 0x70 */
} JEEP_SYSTEM;

extern JEEP_SYSTEM Takabe_JeepSystem;

extern void  s19b_jeep_gls_800CEC24(int arg0, SVECTOR *out);
extern void  s19b_jeep_liq_800D76B0(void *work);
extern void  s19b_jeep_liq_800D7ACC(void *work);
extern void  s19b_jeep_liq_800D7BB0(void *work);
extern void  s19b_jeep_liq_800D81A8(void *work);
extern void *s19b_spark2_m_800D8670(CONTROL *arg0, DG_PRIM *arg1, int *arg2);
extern void *NewJeepLamp2(MATRIX *root);
extern void  s19b_jeep2_800D6AD8(Jeep2Work *work);

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep2_800D667C.s")

void s19b_jeep2_800D6A70(Jeep2Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->jeep_b);
    GM_FreeObject(&work->jeep_t);
    GM_FreeObject((OBJECT *)&work->gun);
    GM_FreeObject((OBJECT *)&work->fhl);
    GM_FreeObject((OBJECT *)&work->hl);
    GM_FreeTarget(work->target);
    GV_DestroyActor(work->field_20);
}
extern int s19b_dword_800C3A94;

void s19b_jeep2_800D6AD8(Jeep2Work *work)
{
    TARGET *target = GM_AllocTarget();

    work->target = target;
    GM_SetTarget(target, TARGET_PUSH, NO_SIDE, (SVECTOR *)&s19b_dword_800C3A94);
}
int s19b_jeep2_800D6B18(Jeep2Work *work, int name, int where)
{
    CONTROL        *control = &work->control;
    SVECTOR        *rot;
    OBJECT         *obj;
    OBJECT_NO_ROTS *nr;
    SVECTOR         vec;
    short           z;

    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(control, -1, -2, -1);
    GM_ConfigControlInterp(control, 0);

    rot = &control->rot;
    obj = &work->jeep_t;

    work->control.mov = work->control.rot = work->control.turn = DG_ZeroVector;
    work->control.step = DG_ZeroVector;
    control->rot.vy  = 0x800;
    control->turn.vy = 0x800;

    GM_InitObject(&work->jeep_b, 0x26C7, 0x2D, 0);
    GM_InitObject(obj, 0x26D9, 0x2D, 0);
    GM_ConfigObjectJoint(&work->jeep_b);
    GM_ConfigObjectJoint(obj);
    GM_ConfigObjectLight(&work->jeep_b, &work->light[0]);
    GM_ConfigObjectLight(obj, &work->light[0]);

    nr = &work->gun;
    GM_InitObjectNoRots(nr, 0x3FA9, 0x6D, 0);
    GM_ConfigObjectLight((OBJECT *)nr, &work->light[0]);

    nr = &work->fhl;
    GM_InitObjectNoRots(nr, 0x3A07, 0x16D, 0);
    nr->objs->root = &work->jeep_b.objs->world;
    GM_ConfigObjectLight((OBJECT *)nr, &work->light2);

    nr = &work->hl;
    GM_InitObjectNoRots(nr, 0xDA10, 0x16D, 0);
    nr->objs->root = &work->jeep_b.objs->world;
    GM_ConfigObjectLight((OBJECT *)nr, &work->light2);

    work->light2.t[0] = 0x80;
    work->light2.t[1] = 0x80;
    work->light2.t[2] = 0x80;

    s19b_jeep2_800D6AD8(work);

    work->field_390 = work->control.rot;

    work->field_358 = Takabe_JeepSystem.field_28;
    work->field_358.vz += 20000;
    work->field_368 = work->field_358;
    work->field_368.vz += 400;

    work->field_388 = work->field_378 = work->field_380 = DG_ZeroVector;
    work->field_378.vz = -400;
    work->field_388.vz = -0x800;

    work->field_3B0 = 0x1A9;
    work->field_3A8 = 0x1A9;
    work->field_3A0 = 0;
    work->field_3A4 = 0;
    work->field_3B4 = 0;
    work->field_3B8 = 0;

    z = work->field_358.vz - Takabe_JeepSystem.field_28.vz;
    control->mov.vz = z;
    s19b_jeep_gls_800CEC24(z, &vec);
    control->mov.vx = vec.vx;
    work->field_358.vx = vec.vx + Takabe_JeepSystem.field_28.vx;
    control->mov.vy = vec.vy;

    work->field_3D0 = (void *)s19b_jeep_liq_800D76B0;
    work->field_3DC = (void *)s19b_jeep_liq_800D7ACC;
    work->field_3E8 = (void *)s19b_jeep_liq_800D7BB0;
    work->field_3C8 = 0;
    work->field_3CC = 0;
    work->field_3D4 = 0;
    work->field_3D8 = 0;
    work->field_3E0 = 0;
    work->field_3E4 = 0;
    work->field_3EC = 0;
    work->field_3F0 = 0;
    work->field_3F4 = 0;
    work->field_3F8 = (void *)s19b_jeep_liq_800D81A8;

    work->field_20 = s19b_spark2_m_800D8670(control, (DG_PRIM *)work->jeep_b.objs, &work->field_3C4);
    NewJeepLamp2(&work->jeep_b.objs->world);

    Takabe_JeepSystem.field_C  = 1;
    Takabe_JeepSystem.field_10 = control;
    Takabe_JeepSystem.field_14 = rot;
    Takabe_JeepSystem.field_54 = 0x10000;
    Takabe_JeepSystem.field_70 = &work->jeep_b;
    return 0;
}

extern void s19b_jeep2_800D667C(Jeep2Work *work);
extern int  s19b_jeep2_800D6B18(Jeep2Work *work, int arg0, int arg1);
const char s19b_aJeepc_800DDE44[] = "jeep2.c";

void *s19b_jeep2_800D6F24(int arg0, int arg1)
{
    Jeep2Work *work = GV_NewActor(GV_ACTOR_USER, 0x3FC);

    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jeep2_800D667C, s19b_jeep2_800D6A70,
                         s19b_aJeepc_800DDE44);
        if (s19b_jeep2_800D6B18(work, arg0, arg1) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return work;
}
