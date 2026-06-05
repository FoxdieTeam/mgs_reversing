#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/item.h"
#include "game/map.h"
#include "linkvar.h"

extern DG_OBJS *Takabe_MakePreshade(int model, LIT *lit);

typedef struct _DynCon
{
    GV_ACT  actor;           /* 0x00 */
    int     map;             /* 0x20 */
    char    pad_24[0x3594 - 0x24];
    int     field_3594[5][2];/* 0x3594 */
    HZD_SEG segs[4][2][4];   /* 0x35BC - four HZD_SEG per [i][j] */
    char    pad_37BC[0x383C - 0x37BC];
    HZD_FLR floors[4][2][2]; /* 0x383C - two HZD_FLR per [i][j] */
    char    pad_3B3C[0x3C0C - 0x3B3C];
    SVECTOR field_3C0C[4];   /* 0x3C0C */
    char    pad_3C2C[0x3F00 - 0x3C2C];
    int     field_3F00[4];   /* 0x3F00 */
    int     field_3F10[4];   /* 0x3F10 - countdown, reset to 32 (800D6004/603C) */
    int     field_3F20[4];   /* 0x3F20 - cycle counter (800D6004/603C) */
    int     field_3F30[4];   /* 0x3F30 */
    SVECTOR field_3F40[4];   /* 0x3F40 */
    SVECTOR field_3F60[4];   /* 0x3F60 */
    short   field_3F80[4][4];/* 0x3F80 - bounds [min_x, min_z, max_x, max_z] per row */
    HZD_SEG slots[4][2];     /* 0x3FA0 - two HZD_SEG per row */
    int     field_4020[4];   /* 0x4020 - flag per row */
    char    pad_4030[0x4050 - 0x4030];
    int     field_4050;      /* 0x4050 - mode/state (1 or 3) */
} DynCon;

typedef struct _DynStack
{
    char  pad[0x70];
    short val_70;
    short val_72;
    short val_74;
    short pad2;
    short val_78;
    short val_7A;
    short val_7C;
    char  pad3[156 - 0x7E];
} DynStack;

void s15c_dyncon_800D3EBC(OBJECT_NO_ROTS *obj, int model, int flag)
{
    GV_ZeroMemory(obj, sizeof(*obj));
    obj->flag = flag;
    obj->map_name = GM_CurrentMap;
    obj->objs = Takabe_MakePreshade(model, GM_GetMap(GM_CurrentMap)->lit);
}
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D3F24.s")
void s15c_dyncon_800D5090(DynCon *work, int i)
{
    HZD_HDL *hzd = GM_GetMap(work->map)->hzd;

    HZD_QueueDynamicSegment2(hzd, &work->slots[i][0], 0x80);
    HZD_QueueDynamicSegment2(hzd, &work->slots[i][1], 0x80);

    work->field_4020[i] = 1;
}

void s15c_dyncon_800D5114(DynCon *work, int i)
{
    HZD_HDL *hzd = GM_GetMap(work->map)->hzd;

    HZD_DequeueDynamicSegment(hzd, &work->slots[i][0]);
    HZD_DequeueDynamicSegment(hzd, &work->slots[i][1]);

    work->field_4020[i] = 0;
}
void s15c_dyncon_800D518C(DynCon *work, int i, int j)
{
    HZD_HDL *hzd = GM_GetMap(work->map)->hzd;

    HZD_QueueDynamicSegment2(hzd, &work->segs[i][j][0], 0x180);
    HZD_QueueDynamicSegment2(hzd, &work->segs[i][j][1], 0x180);
    HZD_QueueDynamicSegment2(hzd, &work->segs[i][j][2], 0x180);
    HZD_QueueDynamicSegment2(hzd, &work->segs[i][j][3], 0x180);

    HZD_QueueDynamicFloor(hzd, &work->floors[i][j][0]);
    HZD_QueueDynamicFloor(hzd, &work->floors[i][j][1]);
}
void s15c_dyncon_800D5270(DynCon *work, int i, int j)
{
    HZD_HDL *hzd = GM_GetMap(work->map)->hzd;

    HZD_QueueDynamicSegment2(hzd, &work->segs[i][j][0], 0x100);
    HZD_QueueDynamicSegment2(hzd, &work->segs[i][j][1], 0x100);
    HZD_QueueDynamicSegment2(hzd, &work->segs[i][j][2], 0x100);
    HZD_QueueDynamicSegment2(hzd, &work->segs[i][j][3], 0x100);

    HZD_QueueDynamicFloor(hzd, &work->floors[i][j][0]);
    HZD_QueueDynamicFloor(hzd, &work->floors[i][j][1]);
}
void s15c_dyncon_800D5354(DynCon *work, int i, int j)
{
    HZD_HDL *hzd = GM_GetMap(work->map)->hzd;

    HZD_DequeueDynamicSegment(hzd, &work->segs[i][j][0]);
    HZD_DequeueDynamicSegment(hzd, &work->segs[i][j][1]);
    HZD_DequeueDynamicSegment(hzd, &work->segs[i][j][2]);
    HZD_DequeueDynamicSegment(hzd, &work->segs[i][j][3]);

    HZD_DequeueDynamicFloor(hzd, &work->floors[i][j][0]);
    HZD_DequeueDynamicFloor(hzd, &work->floors[i][j][1]);
}
void s15c_dyncon_800D5428(DynCon *work, int i, int depth)
{
    SVECTOR a = DG_ZeroVector;
    SVECTOR b = DG_ZeroVector;
    int     flag = 0;

    switch (i)
    {
    case 0:
        a.vx = -0xDAC;
        a.vz = -0x109A;
        break;
    case 1:
        flag = 1;
        a.vx = 0x1B58;
        a.vz = -0x5DC;
        break;
    case 2:
        flag = 1;
        a.vx = -0x1B58;
        a.vz = 0x1194;
        break;
    case 3:
        a.vx = 0xDAC;
        a.vz = 0x1D4C;
        break;
    }

    (void)b;

    work->slots[i][0].p1.y = 0;
    work->slots[i][0].p1.h = 0xDAC;
    work->slots[i][0].p2.y = 0;
    work->slots[i][0].p2.h = 0xDAC;
    work->slots[i][1].p1.y = 0;
    work->slots[i][1].p1.h = 0xDAC;
    work->slots[i][1].p2.y = 0;
    work->slots[i][1].p2.h = 0xDAC;

    if (flag == 0)
    {
        int div = depth * 1500 / 128;

        work->slots[i][0].p1.x = a.vx - 0x9C4;
        work->slots[i][0].p1.z = a.vz - div;
        work->slots[i][0].p2.x = a.vx + 0x9C4;
        work->slots[i][0].p2.z = a.vz - div;
        work->slots[i][1].p1.x = a.vx - 0x9C4;
        work->slots[i][1].p1.z = a.vz + div;
        work->slots[i][1].p2.x = a.vx + 0x9C4;
        work->slots[i][1].p2.z = a.vz + div;
    }
    else
    {
        int div = depth * 2000 / 128;

        work->slots[i][0].p1.x = a.vx - div;
        work->slots[i][0].p1.z = a.vz - 0x9C4;
        work->slots[i][0].p2.x = a.vx - div;
        work->slots[i][0].p2.z = a.vz + 0x9C4;
        work->slots[i][1].p1.x = a.vx + div;
        work->slots[i][1].p1.z = a.vz - 0x9C4;
        work->slots[i][1].p2.x = a.vx + div;
        work->slots[i][1].p2.z = a.vz + 0x9C4;
    }
}
extern void s15c_dyncon_800D3F24(HZD_SEG *segs, HZD_FLR *floors, MATRIX *mtx,
                                 SVECTOR *a, SVECTOR *b);

void s15c_dyncon_800D567C(DynCon *work, int s1, int s2, int code)
{
    MATRIX    mtx;
    SVECTOR   pos;
    SVECTOR   rot;
    SVECTOR   a;
    SVECTOR   b;
    DynStack *ds;

    ds  = (DynStack *)work + work->field_3594[s1][s2];
    pos = *(SVECTOR *)&ds->val_70;
    rot = DG_ZeroVector;

    switch (code)
    {
    case 1:
        a = work->field_3C0C[0];
        b = work->field_3C0C[1];
        ds = (DynStack *)work + work->field_3594[s1][s2];
        rot.vy = ds->val_7A;
        break;
    case 2:
        a = work->field_3C0C[2];
        b = work->field_3C0C[3];
        ds = (DynStack *)work + work->field_3594[s1][s2];
        rot.vy = ds->val_7C + 0x800;
        break;
    case 3:
        a = work->field_3C0C[2];
        b = work->field_3C0C[3];
        ds = (DynStack *)work + work->field_3594[s1][s2];
        rot.vy = ds->val_7C - 0x400;
        break;
    }

    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&mtx);
    s15c_dyncon_800D3F24(&work->segs[s1][s2][0], &work->floors[s1][s2][0],
                         &mtx, &a, &b);
}
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5910.s")
void s15c_dyncon_800D59C0(SVECTOR *vec, int code)
{
    switch (code)
    {
    case 0:
        {
            int x = vec->vx;
            int z = vec->vz;
            vec->vx = -x;
            vec->vz = -z;
        }
        break;
    case 1:
        {
            int x = vec->vx;
            vec->vx = -x;
        }
        break;
    case 3:
        {
            int z = vec->vz;
            vec->vz = -z;
        }
        break;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5A3C.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5C38.s")
void s15c_dyncon_800D5DC0(SVECTOR *vec, SVECTOR *target, int len)
{
    vec->vx = (vec->vx * (len - 1) + target->vx) / len;
    vec->vy = (vec->vy * (len - 1) + target->vy) / len;
    vec->vz = (vec->vz * (len - 1) + target->vz) / len;
}

void s15c_dyncon_800D5EA8(DynCon *work, int i,
                          short ax, short ay, short az,
                          short bx, short by, short bz)
{
    work->field_3F60[i].vx = ax;
    work->field_3F60[i].vy = ay;
    work->field_3F60[i].vz = az;
    work->field_3F40[i].vx = bx;
    work->field_3F40[i].vy = by;
    work->field_3F40[i].vz = bz;
}

void s15c_dyncon_800D5EDC(DynCon *work, int a1, int a2)
{
    if (a1 == 4)
    {
        return;
    }
    s15c_dyncon_800D5354(work, a1, 1);
    s15c_dyncon_800D567C(work, a1, 1, a2);
    if (work->field_4050 == 3)
    {
        s15c_dyncon_800D518C(work, a1, 1);
    }
    else
    {
        s15c_dyncon_800D5270(work, a1, 1);
    }
}

void s15c_dyncon_800D5F68(DynCon *work, int index, int arg2, int a3_val,
                          int sp28, int sp2c, int sp30, int sp34,
                          int sp38, int sp3c)
{
    DynStack *item = (DynStack *)work + index;

    item->val_78 += (short)a3_val;
    item->val_7A += (short)sp28;

    item->val_7C += (short)sp2c;
    item->val_70 += (short)sp30;

    item->val_72 += (short)sp34;
    item->val_74 += (short)sp38;

    s15c_dyncon_800D5EDC(work, arg2, sp3c);
}
void s15c_dyncon_800D6004(DynCon *work, int i)
{
    work->field_3F10[i] = work->field_3F10[i] - 1;
    if (work->field_3F10[i] == 0)
    {
        work->field_3F10[i] = 32;
        work->field_3F20[i] = work->field_3F20[i] + 1;
    }
}
void s15c_dyncon_800D603C(DynCon *work, int i)
{
    work->field_3F10[i] = work->field_3F10[i] - 1;
    if (work->field_3F10[i] == 0)
    {
        work->field_3F20[i] = work->field_3F20[i] + 1;
    }
}
void s15c_dyncon_800D6070(DynCon *work, int row, int idx)
{
    DynStack *item = (DynStack *)work + row;

    item->val_70 += (work->field_3F40[idx].vx * work->field_3F10[idx]) / 128;
    item->val_72 += (work->field_3F40[idx].vy * work->field_3F10[idx]) / 128;
    item->val_74 += (work->field_3F40[idx].vz * work->field_3F10[idx]) / 128;
}
extern int s15c_dword_800E344C;

void s15c_dyncon_800D6128(DynCon *work, SVECTOR *pos, int range)
{
    int  i;
    int *out;

    out = &s15c_dword_800E344C;
    for (i = 0; i < 4; i++)
    {
        if (work->field_3F20[i] > 0)
        {
            if (work->field_3F80[i][0] - range < pos->vx &&
                pos->vx < work->field_3F80[i][2] + range &&
                work->field_3F80[i][1] - range < pos->vz &&
                pos->vz < work->field_3F80[i][3] + range)
            {
                work->field_3F30[i] = 0;
            }
        }
        else if (work->field_3F10[i] != 0)
        {
            work->field_3F30[i] = 0;
        }
        out[i] = work->field_3F30[i];
    }
}
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D61E0.s")
extern void *NewItemPut(SVECTOR *pos, SVECTOR *step, Item_Info *info);
extern const char s15c_aNikitamissile_800E2D80[];
extern const char s15c_aC_800E2D94[];
extern const char s15c_aRation_800E2D9C[];

void *s15c_dyncon_800D6434(DynCon *work, SVECTOR *pos, SVECTOR *step, int item_type)
{
    Item_Info item;

    switch (item_type)
    {
    case 0:
        item.message = s15c_aNikitamissile_800E2D80;
        item.type    = 3;
        item.id      = WP_Nikita;
        item.num     = 4;
        break;
    case 1:
        item.message = s15c_aC_800E2D94;
        item.id      = WP_C4;
        item.type    = 0;
        item.num     = 2;
        break;
    case 2:
        item.message = s15c_aC_800E2D94;
        item.type    = 0;
        item.id      = WP_C4;
        item.num     = 2;
        break;
    case 3:
        item.message = s15c_aRation_800E2D9C;
        item.type    = 4;
        item.id      = IT_Ration;
        item.num     = 1;
        break;
    }
    item.time = -1;
    return NewItemPut(pos, step, &item);
}
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D6528.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D7A84.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D7AB4.s")
int s15c_dyncon_800D7D44(DynCon *work)
{
    int i, j;

    work->field_3594[0][0] = 3;
    work->field_3594[0][1] = 7;
    work->field_3594[1][0] = 41;
    work->field_3594[1][1] = 45;
    work->field_3594[2][0] = 48;
    work->field_3594[2][1] = 52;
    work->field_3594[3][0] = 66;
    work->field_3594[3][1] = 70;
    work->field_3594[4][0] = 37;
    work->field_3594[4][1] = 39;

    GM_CurrentMap = work->map;

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 2; j++)
        {
            if (i != 4)
            {
                s15c_dyncon_800D567C(work, i, j, 1);
                s15c_dyncon_800D518C(work, i, j);
            }
        }
    }

    return 1;
}
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D7E30.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D7EF4.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D7F88.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D82FC.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D8510.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D88C8.s")
extern void s15c_dyncon_800D82FC(void *work);
extern void s15c_dyncon_800D88C8(void *work);

void s15c_dyncon_800D89F8(DynCon *work)
{
    s15c_dyncon_800D82FC(work);
    if (work->field_4050 == 1)
    {
        s15c_dyncon_800D88C8(work);
    }
}
void s15c_dyncon_800D8A34(char *opt, short *out, int count)
{
    int   i;
    char *s;

    for (i = 0; i < count; i++)
    {
        s = GCL_NextStr();
        if (s == NULL)
        {
            break;
        }
        *out = GCL_StrToInt(s);
        out++;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D8A9C.s")
extern void s15c_dyncon_800D6528(void *work);
extern int  s15c_dyncon_800D8A9C(DynCon *work, int arg);
extern const char s15c_dword_800E2E30[];

GV_ACT *s15c_dyncon_800D8C9C(int name, int where)
{
    DynCon *work;


    work = (DynCon *)GV_NewActor(GV_ACTOR_USER, 0x4170);
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, s15c_dyncon_800D6528, s15c_dyncon_800D89F8, s15c_dword_800E2E30);
        if (s15c_dyncon_800D8A9C(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
