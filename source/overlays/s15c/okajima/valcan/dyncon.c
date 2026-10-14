#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/item.h"
#include "strcode.h"
#include "game/vibrate.h"

extern DG_OBJS *Takabe_MakePreshade(int model, DG_LITS *lit);

#define KMD_BOX_04 0x4d62 // GV_StrCode("box_04")
#define KMD_BOX_05 0x4d63 // GV_StrCode("box_05")

// One container: 72 of them form a 3x3 grid (z, x) of 2 layers (y) of
// 2x2 containers. The 36 containers of the bottom layer are the ones
// that can be shot (they have a target and a damage state).
typedef struct _DynConBox
{
    TARGET        *target;   /* 0x00 */
    OBJECT_NO_ROTS obj[2];   /* 0x04 - intact / damaged model */
    SVECTOR        pos;      /* 0x4C */
    SVECTOR        rot;      /* 0x54 */
    MATRIX         light[2]; /* 0x5C */
} DynConBox;

typedef struct _DynConPan
{
    OBJECT_NO_ROTS obj;      /* 0x00 */
    MATRIX         light[2]; /* 0x24 */
    char           pad[0x10];
} DynConPan;

typedef struct _DynConTent
{
    OBJECT_NO_ROTS obj;      /* 0x00 */
    MATRIX         light[2]; /* 0x24 */
} DynConTent;

typedef struct _DynConItem
{
    OBJECT_NO_ROTS obj;      /* 0x00 */
    SVECTOR       *pos;      /* 0x24 */
    SVECTOR       *rot;      /* 0x28 */
    SVECTOR        rot2;     /* 0x2C */
    SVECTOR        ofs;      /* 0x34 */
    MATRIX         light[2]; /* 0x3C */
    int            state;    /* 0x7C */
} DynConItem;

typedef struct _DynCon
{
    GV_ACT     actor;            /* 0x0000 */
    int        map;              /* 0x0020 */
    DynConBox  boxes[72];        /* 0x0024 */
    int        box_flags[144];   /* 0x2C04 - boxes[i / 2].obj[i % 2] is initialized */
    DynConPan  pans[8];          /* 0x2E44 */
    int        pan_flags[8];     /* 0x31E4 */
    DynConTent tents[4];         /* 0x3204 */
    DynConItem items[4];         /* 0x3394 */
    int        field_3594[5][2]; /* 0x3594 - box index */
    HZD_SEG    segs[5][2][4];    /* 0x35BC */
    HZD_FLR    floors[5][2][2];  /* 0x383C */
    char       pad_3BFC[0x10];   /* 0x3BFC */
    SVECTOR    field_3C0C[4];    /* 0x3C0C */
    int        field_3C2C[36];   /* 0x3C2C - hit counter */
    int        field_3CBC[36];   /* 0x3CBC - damage state */
    int        field_3D4C[36];   /* 0x3D4C - previous damage state */
    int        field_3DDC;       /* 0x3DDC - hits per damage state */
    int        field_3DE0[6][6]; /* 0x3DE0 - models */
    int        field_3E70[36];   /* 0x3E70 - model set */
    int        field_3F00[4];    /* 0x3F00 - special box */
    int        field_3F10[4];    /* 0x3F10 - countdown, reset to 32 (800D6004/603C) */
    int        field_3F20[4];    /* 0x3F20 - cycle counter (800D6004/603C) */
    int        field_3F30[4];    /* 0x3F30 */
    SVECTOR    field_3F40[4];    /* 0x3F40 */
    SVECTOR    field_3F60[4];    /* 0x3F60 */
    short      field_3F80[4][4]; /* 0x3F80 - bounds [min_x, min_z, max_x, max_z] per row */
    HZD_SEG    slots[4][2];      /* 0x3FA0 - two HZD_SEG per row */
    int        field_4020[4];    /* 0x4020 - flag per row */
    char       pad_4030[0x10];   /* 0x4030 */
    int        field_4040[4];    /* 0x4040 */
    int        field_4050;       /* 0x4050 - mode/state (1 or 3) */
    int        field_4054;       /* 0x4054 - GCL proc */
    int        field_4058;       /* 0x4058 - GCL proc */
    int        field_405C;       /* 0x405C - GCL proc */
    int        field_4060[40];   /* 0x4060 */
    char       pad_4100[0x60];   /* 0x4100 */
    int        field_4160[4];    /* 0x4160 */
} DynCon;

void s15c_dyncon_800D61E0(DynCon *work);
void s15c_dyncon_800D6528(DynCon *work);
void s15c_dyncon_800D7F88(DynCon *work);
int  s15c_dyncon_800D7AB4(DynCon *work);
int  s15c_dyncon_800D8510(DynCon *work);

extern int     valcan_dead_800E3468;
extern SVECTOR valcan_pos_800E3470;

unsigned char dyncon_vibration1_800C35CC[] = {0x00, 0x04, 0x7F, 0x04, 0x00, 0x00};
unsigned char dyncon_vibration2_800C35D4[] = {0x55, 0x04, 0x87, 0x08, 0x64, 0x0A, 0x41, 0x0C, 0x00, 0x00};

int SECTION(".bss") dyncon_800E3448[4];
int SECTION(".bss") dyncon_800E3458[4];

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
    MATRIX  mtx;
    SVECTOR pos;
    SVECTOR rot;
    SVECTOR a;
    SVECTOR b;

    pos = work->boxes[work->field_3594[s1][s2]].pos;
    rot = DG_ZeroVector;

    switch (code)
    {
    case 1:
        a = work->field_3C0C[0];
        b = work->field_3C0C[1];
        rot.vy = work->boxes[work->field_3594[s1][s2]].rot.vy;
        break;
    case 2:
        a = work->field_3C0C[2];
        b = work->field_3C0C[3];
        rot.vy = work->boxes[work->field_3594[s1][s2]].rot.vz + 0x800;
        break;
    case 3:
        a = work->field_3C0C[2];
        b = work->field_3C0C[3];
        rot.vy = work->boxes[work->field_3594[s1][s2]].rot.vz - 0x400;
        break;
    }

    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&mtx);
    s15c_dyncon_800D3F24(&work->segs[s1][s2][0], &work->floors[s1][s2][0],
                         &mtx, &a, &b);
}
void s15c_dyncon_800D5910(DynCon *work, int i, int j, int hit)
{
    i += j * 3;
    i <<= 2;

    if (work->field_3CBC[i] > 5)
    {
        work->field_3CBC[i] = 5;
    }

    if (work->field_3CBC[i + 1] > 5)
    {
        work->field_3CBC[i + 1] = 5;
    }

    if (work->field_3CBC[i + 2] > 5)
    {
        work->field_3CBC[i + 2] = 5;
    }

    if (work->field_3CBC[i + 3] > 5)
    {
        work->field_3CBC[i + 3] = 5;
    }
}
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
void s15c_dyncon_800D5A3C(DynCon *work, int i, int index, int state, int drz, int drx,
                          int ax, int ay, int az, int bx, int by, int bz)
{
    SVECTOR vec;

    if (!(i & 1))
    {
        work->boxes[index + 4].rot.vz += drz;
    }
    else
    {
        work->boxes[index + 4].rot.vz -= drz;
    }

    work->boxes[index + 4].rot.vx += drx;

    vec.vx = ax;
    vec.vy = ay;
    vec.vz = az;
    s15c_dyncon_800D59C0(&vec, i);

    if (state == 5)
    {
        switch (i)
        {
        case 0:
            vec.vz = 0;
            break;
        case 1:
            vec.vx = 0;
            break;
        case 2:
            vec.vx = 0;
            break;
        case 3:
            vec.vz = 0;
            break;
        }
    }

    work->field_3F40[i] = vec;

    vec.vx = bx;
    vec.vy = by;
    vec.vz = bz;
    s15c_dyncon_800D59C0(&vec, i);

    work->boxes[index + 4].pos.vx += vec.vx;
    work->boxes[index + 4].pos.vy += vec.vy;
    work->boxes[index + 4].pos.vz += vec.vz;
}
void s15c_dyncon_800D5C38(DynCon *work, int i, int index)
{
    SVECTOR         rot;
    OBJECT_NO_ROTS *obj;
    SVECTOR        *pos;

    obj = &work->pans[i * 2].obj;
    pos = &work->boxes[index].pos;
    rot = work->boxes[index].rot;

    DG_SetPos2(pos, &rot);
    s15c_dyncon_800D3EBC(obj, GV_StrCode("pan1"), 0x47);
    obj->objs->objs[0].raise = -250;
    work->pan_flags[i * 2] = 1;
    GM_ActObject2((OBJECT *)obj);

    if (i % 2 == 1)
    {
        rot.vy += 0x800;
    }

    obj = &work->pans[i * 2 + 1].obj;
    DG_SetPos2(pos, &rot);
    s15c_dyncon_800D3EBC(obj, GV_StrCode("pan2"), 0x47);
    obj->objs->objs[0].raise = -250;
    work->pan_flags[i * 2 + 1] = 1;
    GM_ActObject2((OBJECT *)obj);
}
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
    work->boxes[index].rot.vx += (short)a3_val;
    work->boxes[index].rot.vy += (short)sp28;

    work->boxes[index].rot.vz += (short)sp2c;
    work->boxes[index].pos.vx += (short)sp30;

    work->boxes[index].pos.vy += (short)sp34;
    work->boxes[index].pos.vz += (short)sp38;

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
    work->boxes[row].pos.vx += (work->field_3F40[idx].vx * work->field_3F10[idx]) / 128;
    work->boxes[row].pos.vy += (work->field_3F40[idx].vy * work->field_3F10[idx]) / 128;
    work->boxes[row].pos.vz += (work->field_3F40[idx].vz * work->field_3F10[idx]) / 128;
}

void s15c_dyncon_800D6128(DynCon *work, SVECTOR *pos, int range)
{
    int  i;
    int *out;

    out = dyncon_800E3448;
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
void s15c_dyncon_800D61E0(DynCon *work)
{
    OBJECT_NO_ROTS *obj;
    SVECTOR        *ofs;
    DynConBox      *box;
    int             i;
    int             index;

    obj = &work->items[0].obj;
    ofs = &work->items[0].ofs;
    work->items[0].rot2 = DG_ZeroVector;
    ofs->vx = -250;
    ofs->vy = 1800;
    ofs->vz = -250;
    GM_InitObjectNoRots(obj, KMD_BOX_04, 0x36D, 0);
    GM_ConfigObjectLight((OBJECT *)obj, work->items[0].light);
    work->items[0].obj.objs->objs[0].raise = 250;

    obj = &work->items[1].obj;
    ofs = &work->items[1].ofs;
    work->items[1].rot2 = DG_ZeroVector;
    ofs->vx = 250;
    ofs->vy = 1800;
    ofs->vz = -250;
    GM_InitObjectNoRots(obj, KMD_BOX_01, 0x36D, 0);
    GM_ConfigObjectLight((OBJECT *)obj, work->items[1].light);
    work->items[1].obj.objs->objs[0].raise = 250;

    obj = &work->items[2].obj;
    ofs = &work->items[2].ofs;
    work->items[2].rot2 = DG_ZeroVector;
    ofs->vx = -250;
    ofs->vy = 1800;
    ofs->vz = -250;
    GM_InitObjectNoRots(obj, KMD_BOX_01, 0x36D, 0);
    GM_ConfigObjectLight((OBJECT *)obj, work->items[2].light);
    work->items[2].obj.objs->objs[0].raise = 0;

    obj = &work->items[3].obj;
    ofs = &work->items[3].ofs;
    work->items[3].rot2 = DG_ZeroVector;
    ofs->vx = 250;
    ofs->vy = 1800;
    ofs->vz = -250;
    GM_InitObjectNoRots(obj, KMD_BOX_05, 0x36D, 0);
    GM_ConfigObjectLight((OBJECT *)obj, work->items[3].light);
    work->items[3].obj.objs->objs[0].raise = 250;

    for (i = 0; i < 4; i++)
    {
        index = work->field_3F00[i] / 4 * 8 + work->field_3F00[i] % 4 + 4;
        box = &work->boxes[index];
        work->items[i].pos = &box->pos;
        work->items[i].rot = &box->rot;
        work->items[i].state = 0;
    }
}
extern void *NewItemPut(SVECTOR *pos, SVECTOR *step, ITEM_INFO *info);

void *s15c_dyncon_800D6434(DynCon *work, SVECTOR *pos, SVECTOR *step, int item_type)
{
    ITEM_INFO item;

    switch (item_type)
    {
    case 0:
        item.message = "NIKITA MISSILE * 4";
        item.type    = 3;
        item.id      = WP_Nikita;
        item.num     = 4;
        break;
    case 1:
        item.message = "C4 * 2";
        item.id      = WP_C4;
        item.type    = 0;
        item.num     = 2;
        break;
    case 2:
        item.message = "C4 * 2";
        item.type    = 0;
        item.id      = WP_C4;
        item.num     = 2;
        break;
    case 3:
        item.message = "RATION";
        item.type    = 4;
        item.id      = IT_Ration;
        item.num     = 1;
        break;
    }
    item.time = -1;
    return NewItemPut(pos, step, &item);
}
// FIXME: rdata of the INCLUDE_ASM function below, remove once it is decompiled
const char dyncon_aConall_800E2DA4[] = "con_all";
const int  dyncon_jtbl_800E2DB0[] __attribute__((aligned(8))) = {
    0x800D6F34, 0x800D733C, 0x800D741C, 0x800D7440, 0x800D76FC, 0x800D78DC};
#if 0 /* NON_MATCHING */
void s15c_dyncon_800D6528(DynCon *work)
{
    MATRIX  rot1;
    MATRIX  rot2;
    SVECTOR diff;
    SVECTOR pos;
    int     i, j, k;
    int     a, b, c;
    int     hit;
    int     index;
    int     state;
    int     time;
    int     half;
    DynConBox      *box;
    OBJECT_NO_ROTS *obj;

    GM_CurrentMap = work->map;

    if (work->field_4050 == 1)
    {
        for (i = 0; i < 4; i++)
        {
            switch (work->items[i].state)
            {
            case 0:
                work->items[i].rot2.vx = 0;
                work->items[i].rot2.vz = 0;
                work->items[i].rot2.vy -= 90;
                DG_SetPos2(work->items[i].pos, work->items[i].rot);
                DG_PutVector(&work->items[i].ofs, &pos, 1);
                DG_SetPos2(&pos, &work->items[i].rot2);
                GM_ActObject2((OBJECT *)&work->items[i].obj);
                DG_GetLightMatrix2(&pos, work->items[i].light);
                break;

            case 1:
                work->items[i].rot2.vx = 0;
                work->items[i].rot2.vz = 0;
                work->items[i].rot2.vy -= 90;
                DG_SetPos2(&DG_ZeroVector, work->items[i].rot);
                ReadRotMatrix(&rot1);
                DG_SetPos2(work->items[i].pos, work->items[i].rot);
                DG_PutVector(&work->items[i].ofs, &pos, 1);
                DG_SetPos2(&pos, &work->items[i].rot2);
                ReadRotMatrix(&rot2);
                CompMatrix(&rot1, &rot2, &rot1);
                SetRotMatrix(&rot1);
                GM_ActObject2((OBJECT *)&work->items[i].obj);
                DG_GetLightMatrix2(&pos, work->items[i].light);
                break;

            case 2:
                DG_SetPos2(&DG_ZeroVector, work->items[i].rot);
                ReadRotMatrix(&rot1);
                DG_SetPos2(work->items[i].pos, work->items[i].rot);
                work->items[i].ofs.vy += 300;
                DG_PutVector(&work->items[i].ofs, &pos, 1);
                work->items[i].obj.objs->flag |= DG_FLAG_INVISIBLE;
                s15c_dyncon_800D6434(work, &pos, &DG_ZeroVector, i);
                work->items[i].state = 3;
                break;
            }
        }
    }

    if (valcan_dead_800E3468 == 1)
    {
        GV_DestroyActor(&work->actor);
    }

    if (work->field_4050 == 1)
    {
        for (i = 3; i >= 0; i--)
        {
            work->field_3F30[i] = 1;
        }

        s15c_dyncon_800D6128(work, &valcan_pos_800E3470, 10000);
        s15c_dyncon_800D6128(work, &GM_PlayerPosition, 5000);
    }

    c = 0;
    for (j = 0; j < 3; j++)
    {
        for (i = 0; i < 3; i++)
        {
            hit = 0xFF;

            for (a = 0; a < 2; a++)
            {
                for (b = 0; b < 2; b++, c++)
                {
                    if ((c == 3 && work->field_3F30[0] == 0) ||
                        (c == 21 && work->field_3F30[1] == 0) ||
                        (c == 24 && work->field_3F30[2] == 0) ||
                        (c == 34 && work->field_3F30[3] == 0))
                    {
                        continue;
                    }

                    if (work->field_4050 == 1 && (work->boxes[c].target->damaged & TARGET_POWER))
                    {
                        work->boxes[c].target->damaged &= ~TARGET_POWER;

                        GV_SubVec3(&work->boxes[c].pos, &GM_PlayerPosition, &diff);
                        pos.vx = GM_PlayerPosition.vx + diff.vx / 8;
                        pos.vy = work->boxes[c].pos.vy;
                        pos.vz = GM_PlayerPosition.vz + diff.vz / 8;

                        if (work->field_4050 == 1)
                        {
                            GM_SeSet(&pos, 0xBD);
                        }

                        if (++work->field_3C2C[c] >= work->field_3DDC)
                        {
                            hit = a * 2 + b;
                            work->field_3C2C[c] = 0;
                            work->field_3CBC[c]++;
                        }
                    }

                    if (work->field_4050 >= 2 && work->field_4050 <= 3 && work->field_3CBC[c] < work->field_4060[c])
                    {
                        if (++work->field_3C2C[c] >= work->field_3DDC)
                        {
                            hit = a * 2 + b;
                            work->field_3C2C[c] = 0;
                            work->field_3CBC[c]++;
                        }
                    }
                }
            }

            if (hit != 0xFF)
            {
                s15c_dyncon_800D5910(work, i, j, hit);
            }
        }
    }

    for (c = 0; c < 36; c++)
    {
        if (work->field_3CBC[c] == work->field_3D4C[c])
        {
            continue;
        }

        index = c / 4 * 8 + c % 4;
        box = &work->boxes[index];

        GV_SubVec3(&box->pos, &GM_PlayerPosition, &diff);
        pos.vx = GM_PlayerPosition.vx + diff.vx / 8;
        pos.vy = work->boxes[index].pos.vy;
        pos.vz = GM_PlayerPosition.vz + diff.vz / 8;

        work->field_3D4C[c] = work->field_3CBC[c];

        if (work->field_4050 == 1)
        {
            GM_SeSet(&pos, 0xB4);
        }

        state = 1 - work->field_3CBC[c] % 2;
        GM_FreeObject((OBJECT *)&box->obj[state]);
        work->box_flags[index * 2 + state] = 0;

        state = work->field_3CBC[c] % 2;
        obj = &box->obj[state];
        work->box_flags[index * 2 + state] = 1;

        if ((c == 21 || c == 34) && work->field_3CBC[c] >= 4 && work->field_3CBC[c] <= 5)
        {
            work->boxes[index].rot.vy += 0x800;
            DG_SetPos2(&box->pos, &box->rot);
            work->boxes[index].rot.vy -= 0x800;
        }
        else
        {
            DG_SetPos2(&work->boxes[index].pos, &work->boxes[index].rot);
        }

        s15c_dyncon_800D3EBC(obj, work->field_3DE0[work->field_3E70[c]][work->field_3CBC[c]], 0x47);
        GM_ActObject2((OBJECT *)obj);

        for (k = 0; k < 4; k++)
        {
            if (c != work->field_3F00[k])
            {
                continue;
            }

            if (work->field_3CBC[c] == 4)
            {
                work->field_3F10[k] = 32;
                s15c_dyncon_800D5A3C(work, k, index, work->field_3CBC[c], -80, 112, -48, -24, -48, -48, -212, -48);
                s15c_dyncon_800D5C38(work, k, index);

                box = &work->boxes[index + 4];
                GM_FreeObject((OBJECT *)&box->obj[0]);
                work->box_flags[(index + 4) * 2] = 0;
                DG_SetPos2(&box->pos, &box->rot);
                s15c_dyncon_800D3EBC(&box->obj[1], GV_StrCode("con_all"), 0x47);
                work->box_flags[(index + 4) * 2 + 1] = 1;
            }

            if (work->field_3CBC[c] == 5)
            {
                work->field_3F10[k] = 32;
                s15c_dyncon_800D5A3C(work, k, index, work->field_3CBC[c], -112, 32, -80, -52, -80, -80, -240, -80);
                if (k == 2)
                {
                    work->field_3F40[2].vx = -work->field_3F40[2].vx;
                }
            }
        }
    }

    for (k = 0; k < 4; k++)
    {
        if (work->field_3F10[k] == 0 || work->field_4160[k] != 0)
        {
            continue;
        }

        index = work->field_3F00[k] / 4 * 8 + work->field_3F00[k] % 4;

        GV_SubVec3(&work->boxes[index].pos, &GM_PlayerPosition, &diff);
        pos.vx = GM_PlayerPosition.vx + diff.vx / 8;
        pos.vy = work->boxes[index].pos.vy;
        pos.vz = GM_PlayerPosition.vz + diff.vz / 8;

        switch (work->field_3F20[k])
        {
        case 0:
            if (work->field_4050 == 2)
            {
                switch (k)
                {
                case 0:
                    work->boxes[12].pos.vx = -4000;
                    work->boxes[12].pos.vy = 749;
                    work->boxes[12].pos.vz = -3500;
                    work->boxes[12].rot.vx = 1023;
                    work->boxes[12].rot.vy = 1023;
                    work->boxes[12].rot.vz = -511;
                    s15c_dyncon_800D5EDC(work, 0, 2);
                    s15c_dyncon_800D5354(work, 0, 0);
                    work->field_4040[k] = 1;
                    break;
                case 1:
                    work->boxes[45].pos.vx = 8000;
                    work->boxes[45].pos.vy = 749;
                    work->boxes[45].pos.vz = -750;
                    work->boxes[45].rot.vx = 1023;
                    work->boxes[45].rot.vy = 2048;
                    work->boxes[45].rot.vz = -511;
                    s15c_dyncon_800D5EDC(work, 1, 3);
                    s15c_dyncon_800D5354(work, 1, 0);
                    work->field_4040[k] = 1;
                    break;
                case 2:
                    work->boxes[52].pos.vx = -7999;
                    work->boxes[52].pos.vy = 749;
                    work->boxes[52].pos.vz = 4999;
                    work->boxes[52].rot.vx = 1023;
                    work->boxes[52].rot.vy = 1024;
                    work->boxes[52].rot.vz = -511;
                    s15c_dyncon_800D5EDC(work, 2, 2);
                    s15c_dyncon_800D5354(work, 2, 0);
                    work->field_4040[k] = 1;
                    break;
                case 3:
                    work->boxes[70].pos.vx = 4000;
                    work->boxes[70].pos.vy = 749;
                    work->boxes[70].pos.vz = 8000;
                    work->boxes[70].rot.vx = 1023;
                    work->boxes[70].rot.vy = -1023;
                    work->boxes[70].rot.vz = 511;
                    s15c_dyncon_800D5EDC(work, 3, 2);
                    s15c_dyncon_800D5354(work, 3, 0);
                    work->field_4040[k] = 1;
                    break;
                }
                work->field_4160[k] = 1;
            }
            else if (work->field_4050 == 3)
            {
                switch (k)
                {
                case 0:
                    work->boxes[12].pos.vx = -10000;
                    work->boxes[12].pos.vy = -10000;
                    work->boxes[12].pos.vz = -10000;
                    work->boxes[12].rot.vx = 0;
                    work->boxes[12].rot.vy = 0;
                    work->boxes[12].rot.vz = 0;
                    s15c_dyncon_800D5EDC(work, 0, 2);
                    work->boxes[index + 4].obj[0].objs->flag |= DG_FLAG_INVISIBLE;
                    s15c_dyncon_800D5354(work, 0, 0);
                    work->field_4040[k] = 1;
                    break;
                case 1:
                    work->boxes[45].pos.vx = 10000;
                    work->boxes[45].pos.vy = -10000;
                    work->boxes[45].pos.vz = -10000;
                    work->boxes[45].rot.vx = 0;
                    work->boxes[45].rot.vy = 0;
                    work->boxes[45].rot.vz = 0;
                    s15c_dyncon_800D5EDC(work, 1, 3);
                    work->boxes[index + 4].obj[0].objs->flag |= DG_FLAG_INVISIBLE;
                    s15c_dyncon_800D5354(work, 1, 0);
                    work->field_4040[k] = 1;
                    break;
                case 2:
                    work->boxes[52].pos.vx = -10000;
                    work->boxes[52].pos.vy = -10000;
                    work->boxes[52].pos.vz = 10000;
                    work->boxes[52].rot.vx = 0;
                    work->boxes[52].rot.vy = 0;
                    work->boxes[52].rot.vz = 0;
                    s15c_dyncon_800D5EDC(work, 2, 2);
                    work->boxes[index + 4].obj[0].objs->flag |= DG_FLAG_INVISIBLE;
                    s15c_dyncon_800D5354(work, 2, 0);
                    work->field_4040[k] = 1;
                    break;
                case 3:
                    work->boxes[70].pos.vx = 10000;
                    work->boxes[70].pos.vy = -10000;
                    work->boxes[70].pos.vz = 10000;
                    work->boxes[70].rot.vx = 0;
                    work->boxes[70].rot.vy = 0;
                    work->boxes[70].rot.vz = 0;
                    s15c_dyncon_800D5EDC(work, 3, 2);
                    work->boxes[index + 4].obj[0].objs->flag |= DG_FLAG_INVISIBLE;
                    s15c_dyncon_800D5354(work, 3, 0);
                    work->field_4040[k] = 1;
                    break;
                }
                work->field_4160[k] = 1;
            }
            else
            {
                if (work->field_4050 == 1)
                {
                    work->items[k].state = 1;
                    if (work->field_4050 == 1 && GV_RandU(2) == 0)
                    {
                        GM_SeSet(&pos, 0xB2);
                    }
                }

                s15c_dyncon_800D6070(work, index + 4, k);
                s15c_dyncon_800D603C(work, k);
            }
            break;

        case 1:
            if (work->field_4050 == 1 && GV_RandU(2) == 0)
            {
                GM_SeSet(&pos, 0xB2);
            }

            if (work->field_3F10[k] == 32)
            {
                s15c_dyncon_800D5428(work, k, 0);
            }
            else
            {
                s15c_dyncon_800D5114(work, k);
                s15c_dyncon_800D5428(work, k, (32 - work->field_3F10[k]) * 4);
            }

            s15c_dyncon_800D5090(work, k);

            if (k == 0 || k == 1)
            {
                work->boxes[index + 4].rot.vy += 16;
            }
            else
            {
                work->boxes[index + 4].rot.vy -= 16;
            }

            s15c_dyncon_800D6070(work, index + 4, k);

        case 2:
            s15c_dyncon_800D6004(work, k);
            s15c_dyncon_800D5EDC(work, k, 1);
            break;

        case 3:
            time = 32 - work->field_3F10[k];

            if (work->field_4050 == 1 && GV_RandU(2) == 0)
            {
                GM_SeSet(&pos, 0xB2);
            }

            half = time / 2;
            switch (k)
            {
            case 0:
                s15c_dyncon_800D5F68(work, index + 4, 0, time, time, -half, time, -half, -half, 2);
                break;
            case 1:
                s15c_dyncon_800D5F68(work, index + 4, 1, time, time, half, -half, -half, -time * 2, 3);
                break;
            case 2:
                s15c_dyncon_800D5F68(work, index + 4, 2, time * 2, -half, -half, time, -half, -time * 2, 3);
                break;
            case 3:
                s15c_dyncon_800D5F68(work, index + 4, 3, time, -time, half, -time, -half, half, 2);
                break;
            }

            s15c_dyncon_800D6070(work, index + 4, k);

            if (--work->field_3F10[k] == 0)
            {
                work->field_3F10[k] = 8;
                work->field_3F20[k]++;

                switch (k)
                {
                case 0:
                    s15c_dyncon_800D5EA8(work, 0, 0x380, 0x400, -0x200, -4000, 750, -3500);
                    break;
                case 1:
                    s15c_dyncon_800D5EA8(work, 1, 0x380, 0x800, -0x200, 8000, 750, -750);
                    break;
                case 2:
                    s15c_dyncon_800D5EA8(work, 2, 0x380, 0x400, -0x200, -8000, 750, 5000);
                    break;
                case 3:
                    s15c_dyncon_800D5EA8(work, 3, 0x380, -0x400, 0x200, 4000, 750, 8000);
                    break;
                }

                if (work->field_4050 == 1)
                {
                    GM_SeSet(&work->boxes[index + 4].pos, 0x29);
                }
            }
            break;

        case 4:
            if (work->field_4050 == 1 && GV_RandU(2) == 0)
            {
                GM_SeSet(&pos, 0xB2);
            }

            box = &work->boxes[index + 4];
            work->field_3F10[k]--;
            s15c_dyncon_800D5DC0(&box->pos, &work->field_3F40[k], 2);
            s15c_dyncon_800D5DC0(&box->rot, &work->field_3F60[k], 2);

            switch (k)
            {
            case 0:
                s15c_dyncon_800D5EDC(work, 0, 2);
                break;
            case 1:
                s15c_dyncon_800D5EDC(work, 1, 3);
                break;
            case 2:
                s15c_dyncon_800D5EDC(work, 2, 2);
                break;
            case 3:
                s15c_dyncon_800D5EDC(work, 3, 2);
                break;
            }

            if (work->field_3F10[k] == 0)
            {
                work->field_3F10[k] = 8;
                work->field_3F20[k]++;
                work->field_3F60[k].vx = 0x400;

                if (work->field_4050 == 1)
                {
                    GM_SeSet(&pos, 0xB1);
                }

                GM_SetNoise(255, 32, &work->boxes[index + 4].pos);
                NewPadVibration(dyncon_vibration1_800C35CC, 1);
                NewPadVibration(dyncon_vibration2_800C35D4, 2);
            }
            break;

        case 5:
            box = &work->boxes[index + 4];
            work->field_3F10[k]--;
            s15c_dyncon_800D5DC0(&box->pos, &work->field_3F40[k], 2);
            s15c_dyncon_800D5DC0(&box->rot, &work->field_3F60[k], 2);

            if (work->field_3F10[k] == 0)
            {
                s15c_dyncon_800D5354(work, k, 0);
                work->field_4040[k] = 1;
                s15c_dyncon_800D5114(work, k);

                if (work->field_4050 == 1)
                {
                    GM_SeSet(&pos, 0xB1);
                }

                GM_SetNoise(255, 32, &work->boxes[index + 4].pos);
                work->field_3F10[k] = 32;
                work->field_3F20[k]++;

                if (work->field_4050 == 1)
                {
                    work->items[k].state = 2;
                }
            }
            break;
        }

        DG_SetPos2(&work->boxes[index + 4].pos, &work->boxes[index + 4].rot);
        GM_ActObject2((OBJECT *)&work->boxes[index + 4].obj[1]);
        dyncon_800E3458[k] = work->field_3F20[k];
    }
}
#else
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D6528.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D7A84.s")
#endif
#if 0 /* NON_MATCHING */
int s15c_dyncon_800D7AB4(DynCon *work)
{
    SVECTOR size;
    SVECTOR pos;
    TARGET *target;
    int     n, c;
    int     i, j, k;
    int     a, b;

    n = 0;
    c = 0;

    size.vx = 1010;
    size.vy = 885;
    size.vz = 760;

    for (j = 0; j < 3; j++)
    {
        for (i = 0; i < 3; i++)
        {
            for (k = 0; k < 2; k++)
            {
                for (a = 0; a < 2; a++)
                {
                    for (b = 0; b < 2; b++)
                    {
                        if (k == 0)
                        {
                            if (work->field_4050 == 1)
                            {
                                target = GM_AllocTarget();
                                work->boxes[c].target = target;
                                if (target)
                                {
                                    GM_SetTarget(target, TARGET_SEEK | TARGET_POWER, PLAYER_SIDE, &size);
                                }

                                pos = work->boxes[n].pos;
                                pos.vy += 437;
                                GM_MoveTarget(target, &pos);
                            }

                            work->field_3C2C[c] = 0;
                            work->field_3CBC[c] = 0;
                            work->field_3D4C[c] = 0;

                            if (b == a)
                            {
                                work->field_3E70[c] = 2;
                            }
                            else
                            {
                                work->field_3E70[c] = 3;
                            }

                            c++;
                        }

                        n++;
                    }
                }
            }
        }
    }

    work->field_3F00[0] = 3;
    work->field_3F00[1] = 21;
    work->field_3F00[2] = 24;
    work->field_3F00[3] = 34;

    for (i = 0; i < 4; i++)
    {
        work->field_3F10[i] = 0;
        work->field_3F20[i] = 0;
        work->field_3F30[i] = 1;
    }

    work->field_3E70[work->field_3F00[0]] = 0;
    work->field_3E70[work->field_3F00[1]] = 1;
    work->field_3E70[work->field_3F00[2]] = 0;
    work->field_3E70[work->field_3F00[3]] = 1;

    work->field_3E70[28] = 4;
    work->field_3E70[29] = 5;
    work->field_3E70[30] = 5;
    work->field_3E70[31] = 4;

    return 1;
}
#else
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D7AB4.s")
#endif
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
void s15c_dyncon_800D7E30(DynCon *work, int tent, int index, int model)
{
    SVECTOR         pos;
    OBJECT_NO_ROTS *obj;

    pos = work->boxes[index].pos;
    pos.vy += 1749;

    obj = &work->tents[tent].obj;
    DG_SetPos2(&pos, &work->boxes[index].rot);
    s15c_dyncon_800D3EBC(obj, model, 0x47);
    obj->objs->objs[0].raise = -250;
    GM_ActObject2((OBJECT *)obj);
}

void s15c_dyncon_800D7EF4(DynCon *work, int index, int model)
{
    DynConBox      *box;
    OBJECT_NO_ROTS *obj;

    box = &work->boxes[index];
    obj = &box->obj[0];
    DG_SetPos2(&box->pos, &box->rot);
    s15c_dyncon_800D3EBC(obj, model, 0x47);
    work->box_flags[index * 2] = 1;
    GM_ActObject2((OBJECT *)obj);
}

void s15c_dyncon_800D7F88(DynCon *work)
{
    int n, t;
    int i, j, k;
    int a, b;
    int x, y, z;
    int dx, dz;

    n = 0;
    for (j = 0; j < 3; j++)
    {
        for (i = 0; i < 3; i++)
        {
            for (k = 0; k < 2; k++)
            {
                for (a = 0; a < 2; a++)
                {
                    for (b = 0; b < 2; b++)
                    {
                        dx = b * 2000 - 8000;
                        x = i * 7000;
                        y = k * 1750;
                        work->boxes[n].pos.vx = x + dx;
                        z = j * 6000;
                        dz = a * 1500 - 5250;
                        work->boxes[n].pos.vz = z + dz;
                        work->boxes[n].pos.vy = y;
                        work->boxes[n].rot.vx = 0;
                        work->boxes[n].rot.vy = (1 - a) * 2048;
                        work->boxes[n].rot.vz = 0;
                        n++;
                    }
                }
            }
        }
    }

    n = 0;
    t = 0;
    for (j = 0; j < 3; j++)
    {
        for (i = 0; i < 3; i++)
        {
            if (i == 1 && j == 2)
            {
                s15c_dyncon_800D7EF4(work, n, GV_StrCode("con_uf0"));
                s15c_dyncon_800D7E30(work, t, n, GV_StrCode("con_ten"));
                t++;
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode("con_ub0"));
                s15c_dyncon_800D7E30(work, t, n, GV_StrCode("con_ten"));
                t++;
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode("con_ub0"));
                s15c_dyncon_800D7E30(work, t, n, GV_StrCode("con_ten"));
                t++;
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode("con_uf0"));
                s15c_dyncon_800D7E30(work, t, n, GV_StrCode("con_ten"));
                t++;
                n += 5;
            }
            else
            {
                s15c_dyncon_800D7EF4(work, n, GV_StrCode("con_uf0"));
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode("con_ub0"));
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode("con_ub0"));
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode("con_uf0"));
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode("con_tf"));
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode("con_tb"));
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode("con_tb"));
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode("con_tf"));
                n++;
            }
        }
    }
}

void s15c_dyncon_800D82FC(DynCon *work)
{
    int i, j;

    for (i = 0; i < 72; i++)
    {
        if (work->box_flags[i * 2] == 1)
        {
            GM_FreeObject((OBJECT *)&work->boxes[i].obj[0]);
            work->box_flags[i * 2] = 0;
        }

        if (work->box_flags[i * 2 + 1] == 1)
        {
            GM_FreeObject((OBJECT *)&work->boxes[i].obj[1]);
            work->box_flags[i * 2 + 1] = 0;
        }
    }

    for (i = 0; i < 8; i++)
    {
        if (work->pan_flags[i] == 1)
        {
            GM_FreeObject((OBJECT *)&work->pans[i].obj);
            work->pan_flags[i] = 0;
        }
    }

    for (i = 0; i < 4; i++)
    {
        GM_FreeObject((OBJECT *)&work->tents[i].obj);
    }

    if (work->field_4050 != 0)
    {
        for (i = 0; i < 5; i++)
        {
            for (j = 0; j < 2; j++)
            {
                if (i != 4 && j == 0 && work->field_4040[i] == 0)
                {
                    s15c_dyncon_800D5354(work, i, 0);
                }
            }
        }

        for (i = 0; i < 4; i++)
        {
            if (work->field_4020[i] == 1)
            {
                s15c_dyncon_800D5114(work, i);
            }
        }
    }

    if (work->field_4050 == 1)
    {
        for (i = 0; i < 36; i++)
        {
            GM_FreeTarget(work->boxes[i].target);
        }

        GM_FreeObject((OBJECT *)&work->items[0].obj);
        GM_FreeObject((OBJECT *)&work->items[1].obj);
        GM_FreeObject((OBJECT *)&work->items[2].obj);
        GM_FreeObject((OBJECT *)&work->items[3].obj);
    }
}
int s15c_dyncon_800D8510(DynCon *work)
{
    int i;

    for (i = 143; i >= 0; i--)
    {
        work->box_flags[i] = 0;
    }

    for (i = 7; i >= 0; i--)
    {
        work->pan_flags[i] = 0;
    }

    for (i = 0; i < 4; i++)
    {
        work->field_4020[i] = 0;
        dyncon_800E3458[i] = 0;
        work->field_3F20[i] = 0;
    }

    work->field_3C0C[0].vx = -1000;
    work->field_3C0C[0].vy = 0;
    work->field_3C0C[0].vz = -750;
    work->field_3C0C[1].vx = 1000;
    work->field_3C0C[1].vy = 1750;
    work->field_3C0C[1].vz = 750;
    work->field_3C0C[2].vx = -1000;
    work->field_3C0C[2].vy = -750;
    work->field_3C0C[2].vz = 0;
    work->field_3C0C[3].vx = 1000;
    work->field_3C0C[3].vy = 750;
    work->field_3C0C[3].vz = 1750;

    work->field_3F80[0][0] = -5000;
    work->field_3F80[0][1] = -5500;
    work->field_3F80[0][2] = -2000;
    work->field_3F80[0][3] = -3000;
    work->field_3F80[1][0] = 5000;
    work->field_3F80[1][1] = -3000;
    work->field_3F80[1][2] = 9000;
    work->field_3F80[1][3] = 500;
    work->field_3F80[2][0] = -9000;
    work->field_3F80[2][1] = 3000;
    work->field_3F80[2][2] = -5000;
    work->field_3F80[2][3] = 6000;
    work->field_3F80[3][0] = 2000;
    work->field_3F80[3][1] = 6000;
    work->field_3F80[3][2] = 5000;
    work->field_3F80[3][3] = 9000;

    work->field_3DE0[0][0] = GV_StrCode("con_uf0");
    work->field_3DE0[0][1] = GV_StrCode("con_uf1");
    work->field_3DE0[0][2] = GV_StrCode("con_uf2");
    work->field_3DE0[0][3] = GV_StrCode("con_uf3");
    work->field_3DE0[0][4] = GV_StrCode("br5");
    work->field_3DE0[0][5] = GV_StrCode("br6");
    work->field_3DE0[1][0] = GV_StrCode("con_ub0");
    work->field_3DE0[1][1] = GV_StrCode("con_ub1");
    work->field_3DE0[1][2] = GV_StrCode("con_ub2");
    work->field_3DE0[1][3] = GV_StrCode("con_ub3");
    work->field_3DE0[1][4] = GV_StrCode("br7");
    work->field_3DE0[1][5] = GV_StrCode("br8");
    work->field_3DE0[2][0] = GV_StrCode("con_uf0");
    work->field_3DE0[2][1] = GV_StrCode("con_uf1");
    work->field_3DE0[2][2] = GV_StrCode("con_uf2");
    work->field_3DE0[2][3] = GV_StrCode("con_uf3");
    work->field_3DE0[2][4] = GV_StrCode("con_uf3");
    work->field_3DE0[2][5] = GV_StrCode("con_uf3");
    work->field_3DE0[3][0] = GV_StrCode("con_ub0");
    work->field_3DE0[3][1] = GV_StrCode("con_ub1");
    work->field_3DE0[3][2] = GV_StrCode("con_ub2");
    work->field_3DE0[3][3] = GV_StrCode("con_ub3");
    work->field_3DE0[3][4] = GV_StrCode("con_ub3");
    work->field_3DE0[3][5] = GV_StrCode("con_ub3");
    work->field_3DE0[4][0] = GV_StrCode("con_uf0");
    work->field_3DE0[4][1] = GV_StrCode("con_uf1");
    work->field_3DE0[4][2] = GV_StrCode("con_uf2");
    work->field_3DE0[4][3] = GV_StrCode("con_uf3");
    work->field_3DE0[4][4] = GV_StrCode("con_uf3");
    work->field_3DE0[4][5] = GV_StrCode("con_uf3");
    work->field_3DE0[5][0] = GV_StrCode("con_ub0");
    work->field_3DE0[5][1] = GV_StrCode("con_ub1");
    work->field_3DE0[5][2] = GV_StrCode("con_ub2");
    work->field_3DE0[5][3] = GV_StrCode("con_ub3");
    work->field_3DE0[5][4] = GV_StrCode("con_ub3");
    work->field_3DE0[5][5] = GV_StrCode("con_ub3");

    s15c_dyncon_800D7F88(work);

    if (work->field_4050 != 0)
    {
        if (s15c_dyncon_800D7D44(work) < 0)
        {
            return -1;
        }

        if (s15c_dyncon_800D7AB4(work) < 0)
        {
            return -1;
        }
    }

    return 1;
}
void s15c_dyncon_800D88C8(DynCon *work)
{
    GCL_ARGS args;
    long     data[20];
    long    *out;
    int      i;

    out = data;
    for (i = 0; i < 20; i++)
    {
        *out++ = ((unsigned char)work->field_3CBC[i * 2] << 8) | (unsigned char)work->field_3CBC[i * 2 + 1];
    }

    // BUG: these overflow data[] (and are read from the wrong place)
    *out = ((unsigned char)dyncon_800E3458[i] << 8) | (unsigned char)dyncon_800E3458[i + 1];
    *out = ((unsigned char)dyncon_800E3458[i + 2] << 8) | (unsigned char)dyncon_800E3458[i + 3];

    if (work->field_4054 >= 0)
    {
        args.argc = 8;
        args.argv = &data[0];
        GCL_ForceExecProc(work->field_4054, &args);
    }

    if (work->field_4058 >= 0)
    {
        args.argc = 8;
        args.argv = &data[8];
        GCL_ForceExecProc(work->field_4058, &args);
    }

    if (work->field_405C >= 0)
    {
        args.argc = 4;
        args.argv = &data[16];
        GCL_ForceExecProc(work->field_405C, &args);
    }
}

void s15c_dyncon_800D89F8(DynCon *work)
{
    s15c_dyncon_800D82FC(work);
    if (work->field_4050 == 1)
    {
        s15c_dyncon_800D88C8(work);
    }
}
void s15c_dyncon_800D8A34(char *opt, unsigned short *out, int count)
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
int s15c_dyncon_800D8A9C(DynCon *work, int where)
{
    unsigned short data[20];
    char          *opt;
    int            i;

    opt = GCL_GetOption('s');
    if (opt)
    {
        work->field_4050 = GCL_StrToInt(opt);
    }
    else
    {
        work->field_4050 = 1;
    }

    opt = GCL_GetOption('c');
    if (!opt || (work->field_3DDC = GCL_StrToInt(opt)) <= 0)
    {
        work->field_3DDC = 1;
    }

    work->map = where;
    GM_CurrentMap = where;

    if (s15c_dyncon_800D8510(work) < 0)
    {
        return -1;
    }

    if (work->field_4050 == 1)
    {
        opt = GCL_GetOption('f');
        if (opt)
        {
            work->field_4054 = GCL_StrToInt(opt);
        }
        else
        {
            work->field_4054 = -1;
        }

        opt = GCL_GetOption('g');
        if (opt)
        {
            work->field_4058 = GCL_StrToInt(opt);
        }
        else
        {
            work->field_4058 = -1;
        }

        opt = GCL_GetOption('h');
        if (opt)
        {
            work->field_405C = GCL_StrToInt(opt);
        }
        else
        {
            work->field_405C = -1;
        }

        s15c_dyncon_800D61E0(work);
    }

    if (work->field_4050 >= 2 && work->field_4050 <= 3)
    {
        opt = GCL_GetOption('l');
        if (opt)
        {
            s15c_dyncon_800D8A34(opt, &data[0], 8);
        }

        opt = GCL_GetOption('m');
        if (opt)
        {
            s15c_dyncon_800D8A34(opt, &data[8], 8);
        }

        opt = GCL_GetOption('n');
        if (opt)
        {
            s15c_dyncon_800D8A34(opt, &data[16], 4);
        }

        for (i = 0; i < 20; i++)
        {
            work->field_4060[i * 2] = data[i] >> 8;
            work->field_4060[i * 2 + 1] = data[i] & 0xFF;
        }
    }

    work->field_4160[0] = 0;
    work->field_4160[1] = 0;
    work->field_4160[2] = 0;
    work->field_4160[3] = 0;
    work->field_4040[0] = 0;
    work->field_4040[1] = 0;
    work->field_4040[2] = 0;
    work->field_4040[3] = 0;
    return 0;
}

GV_ACT *s15c_dyncon_800D8C9C(int name, int where)
{
    DynCon *work;


    work = (DynCon *)GV_NewActor(GV_ACTOR_USER, 0x4170);
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, s15c_dyncon_800D6528, s15c_dyncon_800D89F8, "dyncon.c");
        if (s15c_dyncon_800D8A9C(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
