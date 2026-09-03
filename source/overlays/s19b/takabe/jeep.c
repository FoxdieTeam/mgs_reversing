#include "common.h"
#include <libgte.h>
#include <rand.h>
#include "game/game.h"

#define EXEC_LEVEL GV_ACTOR_AFTER

typedef struct _Work
{
    GV_ACT         actor;      /* 0x000 */
    void          *field_20;   /* 0x020 */
    int            map;        /* 0x024 */
    CONTROL        control;    /* 0x028 */
    TARGET        *target;     /* 0x0A4 */
    OBJECT         field_A8;   /* 0x0A8 */
    OBJECT         field_18C;  /* 0x18C */
    MATRIX         light1;     /* 0x270: body lights */
    char           pad_290[0x2B0 - 0x270 - sizeof(MATRIX)];
    TARGET         target2;    /* 0x2B0 */
    OBJECT_NO_ROTS field_2F8;  /* 0x2F8 */
    OBJECT_NO_ROTS field_31C;  /* 0x31C */
    MATRIX         light2;     /* 0x340: lights for the two no-rot objects */
    char           pad_360[0x380 - 0x340 - sizeof(MATRIX)];
    VECTOR         field_380;  /* 0x380 */
    VECTOR         field_390;  /* 0x390 */
    SVECTOR        field_3A0;  /* 0x3A0 */
    SVECTOR        field_3A8;  /* 0x3A8 */
    SVECTOR        field_3B0;  /* 0x3B0 */
    SVECTOR        field_3B8;  /* 0x3B8 */
    char           pad_3C0[0x3C8 - 0x3B8 - sizeof(SVECTOR)];
    short          field_3C8;  /* 0x3C8 */
    short          field_3CA;  /* 0x3CA */
    int            field_3CC;  /* 0x3CC */
    int            field_3D0;  /* 0x3D0 */
    int            field_3D4;  /* 0x3D4 */
    char           pad_3D8[0x3DC - 0x3D4 - sizeof(int)];
    int            field_3DC;  /* 0x3DC */
    int            field_3E0;  /* 0x3E0 */
    char           pad_3E4[0x3E8 - 0x3E0 - sizeof(int)];
    int            field_3E8;  /* 0x3E8 */
    int            field_3EC;  /* 0x3EC */
    char           pad_3F0[0x3F8 - 0x3EC - sizeof(int)];
    void          *field_3F8;  /* 0x3F8: state handler */
} Work;

typedef struct _JEEP_SYSTEM
{
    char     pad_0[0x4];
    CONTROL *control;    /* 0x04 */
    SVECTOR *field_8;    /* 0x08 */
    char     pad_C[0x18 - 0x8 - sizeof(SVECTOR *)];
    SVECTOR  pos;        /* 0x18 */
    SVECTOR  field_20;   /* 0x20 */
    VECTOR   field_28;   /* 0x28 */
    char     pad_38[0x48 - 0x28 - sizeof(VECTOR)];
    int      field_48;   /* 0x48 */
    char     pad_4C[0x50 - 0x48 - sizeof(int)];
    int      field_50;   /* 0x50 */
    char     pad_54[0x6C - 0x50 - sizeof(int)];
    OBJECT  *field_6C;   /* 0x6C */
} JEEP_SYSTEM;

extern JEEP_SYSTEM Takabe_JeepSystem;
extern Work *s19b_dword_800DE64C;
extern void  s19b_jeep_mrl_800D2E78(Work *work);
extern void *s19b_jeep_mrl_800D40D4(int arg0, int arg1, int arg2);
extern void *NewJeepSnake(CONTROL *root_ctrl, MATRIX *root_mat);
extern void *NewJeepLamp2(MATRIX *root);


extern SVECTOR s19b_dword_800C39BC;
extern SVECTOR s19b_dword_800C39C4;

void s19b_jeep_800D2170(SVECTOR *arg0, SVECTOR *arg1, SVECTOR *arg2, short *arg3)
{
    arg3[0] = arg0->vx;
    arg3[1] = arg1->vx;
    arg3[2] = arg2->vx;
    arg3[3] = arg0->vy;
    arg3[4] = arg1->vy;
    arg3[5] = arg2->vy;
    arg3[6] = arg0->vz;
    arg3[7] = arg1->vz;
    arg3[8] = arg2->vz;
}

void s19b_jeep_800D21DC(int ang, MATRIX *mat, SVECTOR *out)
{
    SVECTOR vec;
    VECTOR  sqr;
    int     y;

    sqr.vx = 4096 - ang;
    sqr.vz = ang;

    gte_ldlvl(&sqr);
    gte_sqr12();
    y = ang * (4096 - ang);
    y >>= 11;
    gte_stlvnl(&sqr);

    vec.vy = y;
    vec.vx = sqr.vx;
    vec.vz = sqr.vz;
    ApplyMatrixSV(mat, &vec, out);
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_800D2258.s")
void s19b_jeep_800D2258(Work *work);

void s19b_jeep_800D2790(Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->field_A8);
    GM_FreeObject(&work->field_18C);
    GM_FreeObject((OBJECT *)&work->field_2F8);
    GM_FreeObject((OBJECT *)&work->field_31C);
    GM_FreeTarget(work->target);
    GV_DestroyActor(work->field_20);
    GM_SetSound(0xFF0000FE, 0);
}

void s19b_jeep_800D2800(Work *work)
{
    TARGET *trg;

    trg = work->target = GM_AllocTarget();
    GM_SetTarget(trg, TARGET_PUSH, PLAYER_SIDE, &s19b_dword_800C39BC);

    trg = &work->target2;
    GM_SetTarget(trg, TARGET_POWER, PLAYER_SIDE, &s19b_dword_800C39C4);
    GM_SetPowerTarget(trg, POWER_DECREASE | POWER_EXPLODE, 2, 8, 0, &DG_ZeroVector);
}

int s19b_jeep_800D2880(Work *work, int name, int where)
{
    CONTROL *control = &work->control;
    OBJECT  *obj2;
    SVECTOR *rot;
    OBJECT_NO_ROTS *nr;

    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(control, -1, -2, -1);
    GM_ConfigControlInterp(control, 0);

    rot  = &control->rot;
    obj2 = &work->field_18C;

    work->control.mov = work->control.rot = work->control.turn = DG_ZeroVector;
    work->control.step = DG_ZeroVector;
    control->rot.vy  = 0x800;
    control->turn.vy = 0x800;

    GM_InitObject(&work->field_A8, 0x26C7, 0x2D, 0);
    GM_ConfigObjectJoint(&work->field_A8);
    GM_InitObject(obj2, 0x26D9, 0x2D, 0);
    GM_ConfigObjectJoint(obj2);
    GM_ConfigObjectLight(&work->field_A8, &work->light1);
    GM_ConfigObjectLight(obj2, &work->light1);

    nr = &work->field_2F8;
    GM_InitObjectNoRots(nr, 0x3A07, 0x16D, 0);
    nr->objs->root = &work->field_A8.objs->world;
    GM_ConfigObjectLight((OBJECT *)nr, &work->light2);

    nr = &work->field_31C;
    GM_InitObjectNoRots(nr, 0xDA10, 0x16D, 0);
    nr->objs->root = &work->field_A8.objs->world;
    GM_ConfigObjectLight((OBJECT *)nr, &work->light2);

    work->light2.t[0] = 0x80;
    work->light2.t[1] = 0x80;
    work->light2.t[2] = 0x80;

    s19b_jeep_800D2800(work);

    work->map = where;
    work->field_3B8 = work->control.rot;

    work->field_380.vx = 0;
    work->field_380.vy = 0;
    work->field_380.vz = 0;
    work->field_390 = work->field_380;
    Takabe_JeepSystem.field_28 = work->field_390;

    work->field_3B0 = work->field_3A0 = work->field_3A8 = DG_ZeroVector;
    work->field_3A0.vz = -400;
    work->field_3B0.vz = -0x800;
    work->field_3C8 = 0;
    work->field_3CA = 0;

    Takabe_JeepSystem.field_20.vx = -work->field_3A0.vx;
    Takabe_JeepSystem.field_20.vy = -work->field_3A0.vy;
    Takabe_JeepSystem.field_20.vz = -work->field_3A0.vz;
    Takabe_JeepSystem.pos = Takabe_JeepSystem.field_20;

    work->field_3D4 = 400;
    work->field_3D0 = 400;
    work->field_3E8 = 400;
    work->field_3CC = 0;
    work->field_3EC = 0;
    work->field_3F8 = (void *)s19b_jeep_mrl_800D2E78;
    work->field_3DC = 0;
    work->field_3E0 = 0;

    work->field_20 = s19b_jeep_mrl_800D40D4((int)control, (int)work->field_A8.objs,
                                            Takabe_JeepSystem.field_48);
    s19b_dword_800DE64C = work;
    NewJeepSnake(control, &work->field_A8.objs->world);

    Takabe_JeepSystem.control  = control;
    Takabe_JeepSystem.field_8  = rot;
    Takabe_JeepSystem.field_6C = &work->field_A8;
    Takabe_JeepSystem.field_50 |= 0x10000;

    NewJeepLamp2(&work->field_A8.objs->world);
    GM_SeSet(0, 0xC0);
    return 0;
}
int s19b_jeep_800D2880(Work *work, int, int);

extern const char s19b_aJeepc_800DDD8C[]; // = "jeep.c"

void *NewJeep(int arg0, int arg1)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jeep_800D2258, s19b_jeep_800D2790, s19b_aJeepc_800DDD8C);

        if (s19b_jeep_800D2880(work, arg0, arg1) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}

extern const char s19b_dword_800DDDC4[];
extern void RotTransSV(SVECTOR *v0, SVECTOR *v1, long *sz);

void s19b_jeep_mrl_800D2CE8(Work *work)
{
    if (work->field_3E0 == 0)
    {
        work->field_3D0 = GV_NearSpeed(work->field_3D0, work->field_3D4, 5);
    }
    else
    {
        work->field_3D0 = GV_NearSpeed(work->field_3D0, work->field_3D4, 10);
    }
}
extern void s19b_jeep_gls_800CEC24(int arg0, SVECTOR *out);

void s19b_jeep_mrl_800D2D3C(Work *work)
{
    CONTROL *ctl = &work->control;
    SVECTOR  rot;
    SVECTOR  vec;

    memset(&vec, 0, 8);
    vec.vz = work->field_3D0;
    rot = vec;
    DG_SetPos2(&DG_ZeroVector, &work->field_3B8);
    DG_RotVector(&rot, &rot, 1);
    work->field_3A0.vx = rot.vx;
    work->field_3A0.vz = rot.vz;
    s19b_jeep_gls_800CEC24(ctl->mov.vz - 0x640, &vec);
    GV_SubVec3(&vec, &ctl->mov, &vec);
    vec.vx += work->field_3C8;
    vec.vx += rsin(work->field_3CC << 5) * 50 >> 12;
    work->field_3B8.vy = GV_VecDir2(&vec);
    work->field_3CC++;
    work->field_3D4 = GV_NearSpeed(work->field_3D4, 0x190, 0xa);
}
extern int  s19b_jeep_gls_800CEDFC(int arg0, int arg1);
extern void s19b_jlamp_800D0FE4(int arg0);
extern void s19b_jeep_mrl_800D3928(Work *work);
extern int  s19b_dword_800C39CC;

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D2E78.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D32B4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D368C.s")
void s19b_jeep_mrl_800D36A4(Work *work)
{
    CONTROL *ctl = &work->control;

    s19b_jeep_mrl_800D2CE8(work);
    s19b_jeep_mrl_800D2D3C(work);
    switch (work->field_3DC)
    {
    case 0:
        work->field_3C8 = GV_NearSpeed(work->field_3C8, 750, 50);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, 2000) == 10)
        {
            work->field_3DC = 1;
            s19b_jlamp_800D0FE4(3);
            GM_SeSet(NULL, 0xC2);
        }
        break;
    case 1:
        work->field_3C8 = GV_NearSpeed(work->field_3C8, 1500, 50);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, 3000) == 12)
        {
            work->field_3DC = 2;
            s19b_jlamp_800D0FE4(1);
            GM_SeSet(NULL, 0xC2);
        }
        break;
    case 2:
        work->field_3C8 = GV_NearSpeed(work->field_3C8, 750, 50);
        if (work->field_3C8 == 750)
        {
            work->field_3F8 = (void *)s19b_jeep_mrl_800D2E78;
            work->field_3DC = 0;
        }
        break;
    }
}
void s19b_jeep_mrl_800D37D0(Work *work)
{
    CONTROL *ctl = &work->control;

    s19b_jeep_mrl_800D2CE8(work);
    s19b_jeep_mrl_800D2D3C(work);
    switch (work->field_3DC)
    {
    case 0:
        work->field_3C8 = GV_NearSpeed(work->field_3C8, -750, 50);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, 2000) == 11)
        {
            work->field_3DC = 1;
            s19b_jlamp_800D0FE4(4);
        }
        break;
    case 1:
        work->field_3C8 = GV_NearSpeed(work->field_3C8, -1350, 50);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, 3000) == 13)
        {
            work->field_3DC = 2;
            s19b_jlamp_800D0FE4(1);
        }
        if (++s19b_dword_800C39CC >= 10)
        {
            s19b_dword_800C39CC = 0;
            GM_SeSet(NULL, 0xC1);
        }
        break;
    case 2:
        work->field_3C8 = GV_NearSpeed(work->field_3C8, -750, 50);
        if (work->field_3C8 == -750)
        {
            work->field_3F8 = (void *)s19b_jeep_mrl_800D3928;
            work->field_3DC = 0;
        }
        break;
    }
}

void s19b_jeep_mrl_800D3928(Work *work)
{
    s19b_jeep_mrl_800D2CE8(work);
    s19b_jeep_mrl_800D2D3C(work);
    if ((work->field_3CC & 0x3F) == 0)
    {
        work->field_3CA = (rand() * 60 >> 15) - 0x258;
    }
    work->field_3C8 = GV_NearSpeed(work->field_3C8, work->field_3CA, 0x1E);
}

int s19b_jeep_mrl_800D399C(void)
{
    return s19b_dword_800DE64C->field_3D0;
}
int s19b_jeep_mrl_800D39B4(SVECTOR *dst)
{
    *dst = s19b_dword_800DE64C->control.mov;
    return s19b_dword_800DE64C->field_3C8;
}
extern CONTROL *GM_WhereList[96];
extern int      GM_N_WhereList;

int s19b_jeep_mrl_800D39F0(void)
{
    CONTROL **where = GM_WhereList;
    MAP      *map   = (*where)->map;
    int       count = 0;
    int       n;

    for (n = GM_N_WhereList; n > 0; n--)
    {
        CONTROL *control = *where;
        if ((control->radar_atr & 1) && control->map == map)
        {
            count++;
        }
        where++;
    }
    return count;
}

void s19b_jeep_mrl_800D3A54(SVECTOR *pos, short *ang, int scale, short offs)
{
    SVECTOR v10;
    SVECTOR v18;
    SVECTOR probe;
    SVECTOR off;
    MATRIX  m;
    long    flag;

    probe = *(SVECTOR *)s19b_dword_800DDDC4;
    off = DG_ZeroVector;
    off.vz = offs;
    m = DG_ZeroMatrix;
    RotMatrixY(*ang, &m);
    SetRotMatrix(&m);
    SetTransMatrix(&m);
    RotTransSV(&probe, &probe, &flag);
    RotTransSV(&off, &v18, &flag);
    v18.vx = v18.vx * rcos(scale) / 4096;
    v18.vz = v18.vz * rcos(scale) / 4096;
    GV_AddVec3(pos, &v18, pos);
    m = DG_ZeroMatrix;
    RotMatrixY(scale, &m);
    SetRotMatrix(&m);
    RotTransSV(&off, &v10, &flag);
    GV_AddVec3(&probe, &v10, &v10);
    GV_SubVec3(&v10, &v18, &probe);
    *ang = ratan2(probe.vx, probe.vz);
}
extern SVECTOR s19b_dword_800C39D0[];
extern int s19b_dword_800C399C;
extern int s19b_dword_800C3994;
extern void *NewPadVibration(unsigned char *, int);

void s19b_jeep_mrl_800D3CA8(Work *work, int arg1)
{
    DG_SetPos2(&work->control.mov, &work->control.rot);
    DG_PutVector(&s19b_dword_800C39D0[arg1], &work->target2.center, 1);
    work->target2.vital = 8;
    if (GM_PowerTarget(&work->target2) == 0)
    {
        return;
    }
    NewPadVibration((unsigned char *)&s19b_dword_800C399C, 1);
    NewPadVibration((unsigned char *)&s19b_dword_800C3994, 0);
}
