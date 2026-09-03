#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/item.h"
#include "linkvar.h"

extern DG_OBJS *Takabe_MakePreshade(int model, DG_LITS *lit);

extern int s15c_dword_800E345C[4];

const char s15c_aPan_800E2D70[] = "pan1";
const char s15c_aPan_800E2D78[] = "pan2";
const char s15c_aNikitamissile_800E2D80[] = "NIKITA MISSILE * 4";
const char s15c_aC_800E2D94[] = "C4 * 2";
const char s15c_aRation_800E2D9C[] = "RATION";
const char s15c_aConall_800E2DA4[] = "con_all";
const char s15c_dword_800E2DAC[] = {0x0, 0x0, 0x0, 0x0};
const int s15c_dword_800E2DB0 = 0x800D6F34;
const int s15c_dword_800E2DB4 = 0x800D733C;
const int s15c_dword_800E2DB8 = 0x800D741C;
const int s15c_dword_800E2DBC = 0x800D7440;
const int s15c_dword_800E2DC0 = 0x800D76FC;
const int s15c_dword_800E2DC4 = 0x800D78DC;
const char s15c_aConuf_800E2DC8[] = "con_uf0";
const char s15c_aConten_800E2DD0[] = "con_ten";
const char s15c_aConub_800E2DD8[] = "con_ub0";
const char s15c_aContf_800E2DE0[] = "con_tf";
const char s15c_aContb_800E2DE8[] = "con_tb";
const char s15c_aConuf_800E2DF0[] = "con_uf1";
const char s15c_aConuf_800E2DF8[] = "con_uf2";
const char s15c_aConuf_800E2E00[] = "con_uf3";
const char s15c_aBr_800E2E08[] = "br5";
const char s15c_aBr_800E2E0C[] = "br6";
const char s15c_aConub_800E2E10[] = "con_ub1";
const char s15c_aConub_800E2E18[] = "con_ub2";
const char s15c_aConub_800E2E20[] = "con_ub3";
const char s15c_aBr_800E2E28[] = "br7";
const char s15c_aBr_800E2E2C[] = "br8";
const char s15c_dword_800E2E30[] = {'d', 'y', 'n', 'c'};
const char s15c_dword_800E2E34[] = {'o', 'n', '.', 'c'};

typedef struct _Container
{
    TARGET        *target;   /* 0x00 */
    OBJECT_NO_ROTS objs[2];  /* 0x04, 0x28 */
    SVECTOR        mov;      /* 0x4C */
    SVECTOR        rot;      /* 0x54 */
    char           pad_5C[0x9C - 0x5C];
} Container;

typedef struct _DynObj
{
    OBJECT_NO_ROTS obj;      /* 0x00 */
    char           pad_24[0x64 - 0x24];
} DynObj;

typedef struct _DynPan
{
    OBJECT_NO_ROTS obj;      /* 0x00 */
    char           pad_24[0x74 - 0x24];
} DynPan;

typedef struct _DynBlock
{
    OBJECT_NO_ROTS obj;      /* 0x00 */
    SVECTOR       *mov;      /* 0x24 - points at a container's mov */
    SVECTOR       *rot;      /* 0x28 - points at the same container's rot */
    SVECTOR        field_2C; /* 0x2C */
    SVECTOR        field_34; /* 0x34 */
    MATRIX         light[2]; /* 0x3C */
    int            field_7C; /* 0x7C */
} DynBlock;

typedef struct _DynCon
{
    GV_ACT  actor;           /* 0x00 */
    int     map;             /* 0x20 */
    Container containers[72]; /* 0x24 - runs to 0x2C04 exactly */
    int     field_2C04[144]; /* 0x2C04 - one flag per container object */
    DynPan   field_2E44[8];  /* 0x2E44 */
    int      field_31E4[8];  /* 0x31E4 - one flag per pan object */
    DynObj   field_3204[4];  /* 0x3204 */
    DynBlock field_3394[4];  /* 0x3394 - runs up to field_3594 */
    int     field_3594[5][2];/* 0x3594 */
    HZD_SEG segs[4][2][4];   /* 0x35BC - four HZD_SEG per [i][j] */
    char    pad_37BC[0x383C - 0x37BC];
    HZD_FLR floors[4][2][2]; /* 0x383C - two HZD_FLR per [i][j] */
    char    pad_3B3C[0x3C0C - 0x3B3C];
    SVECTOR field_3C0C[4];   /* 0x3C0C */
    int     field_3C2C[36];  /* 0x3C2C */
    int     field_3CBC[36];  /* 0x3CBC */
    int     field_3D4C[36];  /* 0x3D4C - the three run up to field_3DDC */
    int     field_3DDC;      /* 0x3DDC */
    int     field_3DE0[3][12];/* 0x3DE0 - model name codes */
    int     field_3E70[36];  /* 0x3E70 */
    int     field_3F00[4];   /* 0x3F00 */
    int     field_3F10[4];   /* 0x3F10 - countdown, reset to 32 (800D6004/603C) */
    int     field_3F20[4];   /* 0x3F20 - cycle counter (800D6004/603C) */
    int     field_3F30[4];   /* 0x3F30 */
    SVECTOR field_3F40[4];   /* 0x3F40 */
    SVECTOR field_3F60[4];   /* 0x3F60 */
    short   field_3F80[4][4];/* 0x3F80 - bounds [min_x, min_z, max_x, max_z] per row */
    HZD_SEG slots[4][2];     /* 0x3FA0 - two HZD_SEG per row */
    int     field_4020[4];   /* 0x4020 - flag per row */
    char    pad_4030[0x4040 - 0x4030];
    int     field_4040[4];   /* 0x4040 */
    int     field_4050;      /* 0x4050 - mode/state (1 or 3) */
    int     field_4054;      /* 0x4054 - GCL proc ids, -1 when unset */
    int     field_4058;      /* 0x4058 */
    int     field_405C;      /* 0x405C */
    int     field_4060[40];  /* 0x4060 - the two bytes of each option word */
    char    pad_4100[0x4160 - 0x4100];
    int     field_4160[4];   /* 0x4160 */
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
void s15c_dyncon_800D5910(DynCon *work, int row, int col, int unused)
{
    row += col * 3;
    row <<= 2;

    if (work->field_3CBC[row] >= 6)
    {
        work->field_3CBC[row] = 5;
    }
    if (work->field_3CBC[row + 1] >= 6)
    {
        work->field_3CBC[row + 1] = 5;
    }
    if (work->field_3CBC[row + 2] >= 6)
    {
        work->field_3CBC[row + 2] = 5;
    }
    if (work->field_3CBC[row + 3] >= 6)
    {
        work->field_3CBC[row + 3] = 5;
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
void s15c_dyncon_800D5A3C(DynCon *work, int code, int i, int mode, int rz, int rx,
                          int ax, int ay, int az, int bx, int by, int bz)
{
    SVECTOR vec;

    if ((code & 1) == 0)
    {
        work->containers[i + 4].rot.vz += rz;
    }
    else
    {
        work->containers[i + 4].rot.vz -= rz;
    }

    work->containers[i + 4].rot.vx += rx;

    vec.vx = ax;
    vec.vy = ay;
    vec.vz = az;
    s15c_dyncon_800D59C0(&vec, code);

    if (mode == 5)
    {
        switch (code)
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

    work->field_3F40[code] = vec;

    vec.vx = bx;
    vec.vy = by;
    vec.vz = bz;
    s15c_dyncon_800D59C0(&vec, code);

    work->containers[i + 4].mov.vx += vec.vx;
    work->containers[i + 4].mov.vy += vec.vy;
    work->containers[i + 4].mov.vz += vec.vz;
}
void s15c_dyncon_800D5C38(DynCon *work, int i, int j)
{
    OBJECT_NO_ROTS *obj;
    SVECTOR         rot;

    obj = &work->field_2E44[i * 2].obj;
    rot = work->containers[j].rot;
    DG_SetPos2(&work->containers[j].mov, &rot);
    s15c_dyncon_800D3EBC(obj, GV_StrCode(s15c_aPan_800E2D70),
                         DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS | DG_FLAG_ONEPIECE);
    obj->objs->objs[0].raise = -250;
    work->field_31E4[i * 2] = 1;
    GM_ActObject2((OBJECT *)obj);

    if (i % 2 == 1)
    {
        rot.vy += 0x800;
    }

    obj = &work->field_2E44[i * 2 + 1].obj;
    DG_SetPos2(&work->containers[j].mov, &rot);
    s15c_dyncon_800D3EBC(obj, GV_StrCode(s15c_aPan_800E2D78),
                         DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS | DG_FLAG_ONEPIECE);
    obj->objs->objs[0].raise = -250;
    work->field_31E4[i * 2 + 1] = 1;
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
void s15c_dyncon_800D61E0(DynCon *work)
{
    OBJECT_NO_ROTS *obj;
    SVECTOR        *vec;
    int             i;

    obj = &work->field_3394[0].obj;
    vec = &work->field_3394[0].field_34;
    work->field_3394[0].field_2C = DG_ZeroVector;
    vec->vx = -250;
    vec->vy = 0x708;
    vec->vz = -250;
    GM_InitObjectNoRots(obj, 0x4D62,
                        DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND |
                            DG_FLAG_ONEPIECE | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE,
                        0);
    GM_ConfigObjectLight((OBJECT *)obj, work->field_3394[0].light);
    work->field_3394[0].obj.objs->objs[0].raise = 250;

    obj = &work->field_3394[1].obj;
    vec = &work->field_3394[1].field_34;
    work->field_3394[1].field_2C = DG_ZeroVector;
    vec->vx = 250;
    vec->vy = 0x708;
    vec->vz = -250;
    GM_InitObjectNoRots(obj, 0x4D5F,
                        DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND |
                            DG_FLAG_ONEPIECE | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE,
                        0);
    GM_ConfigObjectLight((OBJECT *)obj, work->field_3394[1].light);
    work->field_3394[1].obj.objs->objs[0].raise = 250;

    obj = &work->field_3394[2].obj;
    vec = &work->field_3394[2].field_34;
    work->field_3394[2].field_2C = DG_ZeroVector;
    vec->vx = -250;
    vec->vy = 0x708;
    vec->vz = -250;
    GM_InitObjectNoRots(obj, 0x4D5F,
                        DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND |
                            DG_FLAG_ONEPIECE | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE,
                        0);
    GM_ConfigObjectLight((OBJECT *)obj, work->field_3394[2].light);
    work->field_3394[2].obj.objs->objs[0].raise = 0;

    obj = &work->field_3394[3].obj;
    vec = &work->field_3394[3].field_34;
    work->field_3394[3].field_2C = DG_ZeroVector;
    vec->vx = 250;
    vec->vy = 0x708;
    vec->vz = -250;
    GM_InitObjectNoRots(obj, 0x4D63,
                        DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND |
                            DG_FLAG_ONEPIECE | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE,
                        0);
    GM_ConfigObjectLight((OBJECT *)obj, work->field_3394[3].light);
    work->field_3394[3].obj.objs->objs[0].raise = 250;

    for (i = 0; i < 4; i++)
    {
        int n = work->field_3F00[i] / 4 * 8 + work->field_3F00[i] % 4 + 4;

        work->field_3394[i].mov = &work->containers[n].mov;
        work->field_3394[i].rot = &work->containers[n].rot;
        work->field_3394[i].field_7C = 0;
    }
}
extern void *NewItemPut(SVECTOR *pos, SVECTOR *step, Item_Info *info);

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
int s15c_dyncon_800D7AB4(DynCon *work)
{
    SVECTOR size;
    SVECTOR pos;
    TARGET *target;
    int     n;
    int     p;
    int     j;
    int     i;
    int     k;
    int     l;
    int     m;

    size.vx = 0x3F2;
    size.vy = 0x375;
    size.vz = 0x2F8;

    n = 0;
    p = 0;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            for (k = 0; k < 2; k++)
            {
                for (l = 0; l < 2; l++)
                {
                    for (m = 0; m < 2; m++)
                    {
                        if (k == 0)
                        {
                            if (work->field_4050 == 1)
                            {
                                target = GM_AllocTarget();
                                work->containers[p].target = target;
                                if (target != NULL)
                                {
                                    GM_SetTarget(target, TARGET_POWER | TARGET_SEEK, PLAYER_SIDE, &size);
                                }
                                pos = work->containers[n].mov;
                                pos.vy += 0x1B5;
                                GM_MoveTarget(target, &pos);
                            }
                            work->field_3C2C[p] = 0;
                            work->field_3CBC[p] = 0;
                            work->field_3D4C[p] = 0;
                            work->field_3E70[p] = (m == l) ? 2 : 3;
                            p++;
                        }
                        n++;
                    }
                }
            }
        }
    }

    work->field_3F00[0] = 3;
    work->field_3F00[1] = 0x15;
    work->field_3F00[2] = 0x18;
    work->field_3F00[3] = 0x22;

    for (m = 0; m < 4; m++)
    {
        work->field_3F10[m] = 0;
        work->field_3F20[m] = 0;
        work->field_3F30[m] = 1;
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
void s15c_dyncon_800D7E30(DynCon *work, int j, int i, int model)
{
    SVECTOR         mov;
    OBJECT_NO_ROTS *obj;

    mov = work->containers[i].mov;
    mov.vy += 0x6D5;
    obj = &work->field_3204[j].obj;

    DG_SetPos2(&mov, &work->containers[i].rot);
    s15c_dyncon_800D3EBC(obj, model,
                         DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS | DG_FLAG_ONEPIECE);
    obj->objs->objs[0].raise = -250;
    GM_ActObject2((OBJECT *)obj);
}
void s15c_dyncon_800D7EF4(DynCon *work, int i, int model)
{
    Container      *con = &work->containers[i];
    OBJECT_NO_ROTS *obj = &con->objs[0];

    DG_SetPos2(&con->mov, &con->rot);
    s15c_dyncon_800D3EBC(obj, model,
                         DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS | DG_FLAG_ONEPIECE);
    work->field_2C04[i * 2] = 1;
    GM_ActObject2((OBJECT *)obj);
}

void s15c_dyncon_800D7F88(DynCon *work)
{
    int n;
    int p;
    int i;
    int j;
    int k;
    int l;
    int m;

    n = 0;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            for (k = 0; k < 2; k++)
            {
                for (l = 0; l < 2; l++)
                {
                    for (m = 0; m < 2; m++)
                    {
                        int dx = m * 2000 - 8000;

                        work->containers[n].mov.vx = j * 7000 + dx;
                        work->containers[n].mov.vy = k * 1750;
                        work->containers[n].mov.vz = (i * 6000 - 5250) + l * 1500;
                        work->containers[n].rot.vx = 0;
                        work->containers[n].rot.vy = (1 - l) * 2048;
                        work->containers[n].rot.vz = 0;
                        n++;
                    }
                }
            }
        }
    }

    n = 0;
    p = 0;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (j == 1 && i == 2)
            {
                s15c_dyncon_800D7EF4(work, n, GV_StrCode(s15c_aConuf_800E2DC8));
                s15c_dyncon_800D7E30(work, p, n, GV_StrCode(s15c_aConten_800E2DD0));
                p++;
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode(s15c_aConub_800E2DD8));
                s15c_dyncon_800D7E30(work, p, n, GV_StrCode(s15c_aConten_800E2DD0));
                p++;
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode(s15c_aConub_800E2DD8));
                s15c_dyncon_800D7E30(work, p, n, GV_StrCode(s15c_aConten_800E2DD0));
                p++;
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode(s15c_aConuf_800E2DC8));
                s15c_dyncon_800D7E30(work, p, n, GV_StrCode(s15c_aConten_800E2DD0));
                p++;
                n += 5;
            }
            else
            {
                s15c_dyncon_800D7EF4(work, n, GV_StrCode(s15c_aConuf_800E2DC8));
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode(s15c_aConub_800E2DD8));
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode(s15c_aConub_800E2DD8));
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode(s15c_aConuf_800E2DC8));
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode(s15c_aContf_800E2DE0));
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode(s15c_aContb_800E2DE8));
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode(s15c_aContb_800E2DE8));
                n++;
                s15c_dyncon_800D7EF4(work, n, GV_StrCode(s15c_aContf_800E2DE0));
                n++;
            }
        }
    }
}
void s15c_dyncon_800D82FC(DynCon *work)
{
    int i;
    int j;

    for (i = 0; i < 72; i++)
    {
        if (work->field_2C04[i * 2] == 1)
        {
            GM_FreeObject((OBJECT *)&work->containers[i].objs[0]);
            work->field_2C04[i * 2] = 0;
        }

        if (work->field_2C04[i * 2 + 1] == 1)
        {
            GM_FreeObject((OBJECT *)&work->containers[i].objs[1]);
            work->field_2C04[i * 2 + 1] = 0;
        }
    }

    for (i = 0; i < 8; i++)
    {
        if (work->field_31E4[i] == 1)
        {
            GM_FreeObject((OBJECT *)&work->field_2E44[i].obj);
            work->field_31E4[i] = 0;
        }
    }

    for (i = 0; i < 4; i++)
    {
        GM_FreeObject((OBJECT *)&work->field_3204[i].obj);
    }

    if (work->field_4050 != 0)
    {
        for (i = 0; i < 5; i++)
        {
            for (j = 0; j < 2; j++)
            {
                if (i != 4 && j == 0 && work->field_4040[i] == 0)
                {
                    s15c_dyncon_800D5354(work, i, j);
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
            GM_FreeTarget(work->containers[i].target);
        }

        GM_FreeObject((OBJECT *)&work->field_3394[0].obj);
        GM_FreeObject((OBJECT *)&work->field_3394[1].obj);
        GM_FreeObject((OBJECT *)&work->field_3394[2].obj);
        GM_FreeObject((OBJECT *)&work->field_3394[3].obj);
    }
}
int s15c_dyncon_800D8510(DynCon *work)
{
    int i;

    for (i = 143; i >= 0; i--)
    {
        work->field_2C04[i] = 0;
    }

    for (i = 7; i >= 0; i--)
    {
        work->field_31E4[i] = 0;
    }

    for (i = 0; i < 4; i++)
    {
        work->field_4020[i] = 0;
        s15c_dword_800E345C[i] = 0;
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

    work->field_3DE0[0][0] = GV_StrCode(s15c_aConuf_800E2DC8);
    work->field_3DE0[0][1] = GV_StrCode(s15c_aConuf_800E2DF0);
    work->field_3DE0[0][2] = GV_StrCode(s15c_aConuf_800E2DF8);
    work->field_3DE0[0][3] = GV_StrCode(s15c_aConuf_800E2E00);
    work->field_3DE0[0][4] = GV_StrCode(s15c_aBr_800E2E08);
    work->field_3DE0[0][5] = GV_StrCode(s15c_aBr_800E2E0C);
    work->field_3DE0[0][6] = GV_StrCode(s15c_aConub_800E2DD8);
    work->field_3DE0[0][7] = GV_StrCode(s15c_aConub_800E2E10);
    work->field_3DE0[0][8] = GV_StrCode(s15c_aConub_800E2E18);
    work->field_3DE0[0][9] = GV_StrCode(s15c_aConub_800E2E20);
    work->field_3DE0[0][10] = GV_StrCode(s15c_aBr_800E2E28);
    work->field_3DE0[0][11] = GV_StrCode(s15c_aBr_800E2E2C);

    work->field_3DE0[1][0] = GV_StrCode(s15c_aConuf_800E2DC8);
    work->field_3DE0[1][1] = GV_StrCode(s15c_aConuf_800E2DF0);
    work->field_3DE0[1][2] = GV_StrCode(s15c_aConuf_800E2DF8);
    work->field_3DE0[1][3] = GV_StrCode(s15c_aConuf_800E2E00);
    work->field_3DE0[1][4] = GV_StrCode(s15c_aConuf_800E2E00);
    work->field_3DE0[1][5] = GV_StrCode(s15c_aConuf_800E2E00);
    work->field_3DE0[1][6] = GV_StrCode(s15c_aConub_800E2DD8);
    work->field_3DE0[1][7] = GV_StrCode(s15c_aConub_800E2E10);
    work->field_3DE0[1][8] = GV_StrCode(s15c_aConub_800E2E18);
    work->field_3DE0[1][9] = GV_StrCode(s15c_aConub_800E2E20);
    work->field_3DE0[1][10] = GV_StrCode(s15c_aConub_800E2E20);
    work->field_3DE0[1][11] = GV_StrCode(s15c_aConub_800E2E20);

    work->field_3DE0[2][0] = GV_StrCode(s15c_aConuf_800E2DC8);
    work->field_3DE0[2][1] = GV_StrCode(s15c_aConuf_800E2DF0);
    work->field_3DE0[2][2] = GV_StrCode(s15c_aConuf_800E2DF8);
    work->field_3DE0[2][3] = GV_StrCode(s15c_aConuf_800E2E00);
    work->field_3DE0[2][4] = GV_StrCode(s15c_aConuf_800E2E00);
    work->field_3DE0[2][5] = GV_StrCode(s15c_aConuf_800E2E00);
    work->field_3DE0[2][6] = GV_StrCode(s15c_aConub_800E2DD8);
    work->field_3DE0[2][7] = GV_StrCode(s15c_aConub_800E2E10);
    work->field_3DE0[2][8] = GV_StrCode(s15c_aConub_800E2E18);
    work->field_3DE0[2][9] = GV_StrCode(s15c_aConub_800E2E20);
    work->field_3DE0[2][10] = GV_StrCode(s15c_aConub_800E2E20);
    work->field_3DE0[2][11] = GV_StrCode(s15c_aConub_800E2E20);

    s15c_dyncon_800D7F88(work);

    if (work->field_4050 == 0)
    {
        return 1;
    }

    if (s15c_dyncon_800D7D44(work) >= 0)
    {
        if (s15c_dyncon_800D7AB4(work) < 0)
        {
            return -1;
        }

        return 1;
    }

    return -1;
}
void s15c_dyncon_800D88C8(DynCon *work)
{
    GCL_ARGS args;
    long     data[20];
    long    *p;
    u_char  *b;
    int      i;

    p = data;

    for (i = 0; i < 20; i++)
    {
        *p++ = ((u_char)work->field_3CBC[i << 1] << 8) | (u_char)work->field_3CBC[(i << 1) + 1];
    }

    /* Both of these write one word past data[], and read past the end of the
       overlay's bss: dead code in the original, reproduced literally. */
    b = (u_char *)s15c_dword_800E345C;
    *p = (b[i << 2] << 8) | b[(i + 1) << 2];
    *p = (b[(i + 2) << 2] << 8) | b[(i + 3) << 2];

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
int s15c_dyncon_800D8A9C(DynCon *work, int map)
{
    short buf[20];
    char *opt;
    int   i;

    if ((opt = GCL_GetOption('s')) != NULL)
    {
        work->field_4050 = GCL_StrToInt(opt);
    }
    else
    {
        work->field_4050 = 1;
    }

    if ((opt = GCL_GetOption('c')) == NULL || (work->field_3DDC = GCL_StrToInt(opt)) <= 0)
    {
        work->field_3DDC = 1;
    }

    work->map = map;
    GM_CurrentMap = map;

    if (s15c_dyncon_800D8510(work) < 0)
    {
        return -1;
    }

    if (work->field_4050 == 1)
    {
        if ((opt = GCL_GetOption('f')) != NULL)
        {
            work->field_4054 = GCL_StrToInt(opt);
        }
        else
        {
            work->field_4054 = -1;
        }

        if ((opt = GCL_GetOption('g')) != NULL)
        {
            work->field_4058 = GCL_StrToInt(opt);
        }
        else
        {
            work->field_4058 = -1;
        }

        if ((opt = GCL_GetOption('h')) != NULL)
        {
            work->field_405C = GCL_StrToInt(opt);
        }
        else
        {
            work->field_405C = -1;
        }

        s15c_dyncon_800D61E0(work);
    }

    if ((u_int)(work->field_4050 - 2) < 2)
    {
        if ((opt = GCL_GetOption('l')) != NULL)
        {
            s15c_dyncon_800D8A34(opt, &buf[0], 8);
        }

        if ((opt = GCL_GetOption('m')) != NULL)
        {
            s15c_dyncon_800D8A34(opt, &buf[8], 8);
        }

        if ((opt = GCL_GetOption('n')) != NULL)
        {
            s15c_dyncon_800D8A34(opt, &buf[16], 4);
        }

        for (i = 0; i < 20; i++)
        {
            work->field_4060[i * 2] = (u_short)buf[i] >> 8;
            work->field_4060[i * 2 + 1] = *(u_char *)&buf[i];
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
extern void s15c_dyncon_800D6528(void *work);

GV_ACT *s15c_dyncon_800D8C9C(int name, int where)
{
    DynCon *work;


    work = (DynCon *)GV_NewActor(GV_ACTOR_USER, sizeof(DynCon));
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
