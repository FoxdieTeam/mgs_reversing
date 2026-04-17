#include "game/game.h"

#define EXEC_LEVEL 5

// TODO: This type of struct is seen in other places that make use of HZD_FLR.
typedef struct _BULLET_VECS
{
    SVECTOR vecs[4];
} BULLET_VECS;

typedef struct _Work
{
    /* 0x000 */ GV_ACT      actor;
    /* 0x020 */ int         map;
    /* 0x024 */ MATRIX      world;
    /* 0x044 */ TARGET      target;
    /* 0x08C */ DG_PRIM    *prim;
    /* 0x090 */ SVECTOR     vertices[8];
    /* 0x0D0 */ BULLET_VECS field_D0[2];
    /* 0x110 */ SVECTOR     field_110;
    /* 0x118 */ char        pad118[0x8];
    /* 0x120 */ SVECTOR     field_120;
    /* 0x128 */ char        pad128[0xC];
    /* 0x134 */ int         field_134;
    /* 0x138 */ int         field_138;
    /* 0x13C */ int         field_13C;
    /* 0x140 */ char        pad140[4];
    /* 0x144 */ int         field_144;
    /* 0x148 */ int         side;
    /* 0x14C */ int         field_14C;
    /* 0x150 */ int         field_150;
    /* 0x154 */ int         life;
    /* 0x158 */ int         field_158;
    /* 0x15C */ int         field_15C;
    /* 0x160 */ int         field_160;
    /* 0x164 */ int         field_164;
    /* 0x168 */ int         field_168;
    /* 0x16C */ char        pad16C[0x4];
} Work;

extern SVECTOR s19b_dword_800C3380[4];
extern SVECTOR s19b_dword_800C33C0;
extern SVECTOR s19b_dword_800C33C8;
extern SVECTOR s19b_dword_800C33D0;

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C4F54.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C4FD4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5010.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5258.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5278.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5348.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C53C0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C543C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C54D0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5560.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5654.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5714.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C57E8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C58CC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C598C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5C50.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5D18.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5E40.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5E60.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5F2C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5F7C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C5FB0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C63DC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C6404.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C6428.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C645C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C649C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C6524.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C65A8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C666C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C66BC.s")

// file split

void s19b_jbullet_800C6734(SVECTOR *vecs, int scale)
{
    s19b_dword_800C3380[0].vx = scale;
    s19b_dword_800C3380[1].vx = -scale;
    s19b_dword_800C3380[2].vz = scale;
    s19b_dword_800C3380[3].vz = -scale;

    DG_PutVector(s19b_dword_800C3380, vecs, 4);
}

void s19b_jbullet_800C6778(Work *work)
{
    BULLET_VECS *vecs;
    int          i;

    s19b_jbullet_800C6734(work->field_D0[0].vecs, work->field_150);

    vecs = &work->field_D0[0];
    for (i = 1; i > 0; i--)
    {
        vecs[1] = vecs[0];
        vecs++;
    }
}

void s19b_jbullet_800C6834(Work *work)
{
    BULLET_VECS *vecs;
    int          i;

    vecs = &work->field_D0[1];
    for (i = 1; i > 0; i--)
    {
        if (work->field_134 != 2)
        {
            vecs[0] = vecs[-1];
        }

        vecs--;
    }

    s19b_jbullet_800C6734(vecs->vecs, work->field_150);
}

void s19b_jbullet_800C6904(Work *work)
{
    int          i;
    BULLET_VECS *vecs;
    SVECTOR     *verts;

    vecs = &work->field_D0[0];
    verts = work->vertices;
    for (i = 1; i > 0; i--)
    {
        verts[0] = vecs[0].vecs[0];
        verts[1] = vecs[0].vecs[1];
        verts[2] = vecs[1].vecs[0];
        verts[3] = vecs[1].vecs[1];
        verts[4] = vecs[0].vecs[2];
        verts[5] = vecs[0].vecs[3];
        verts[6] = vecs[1].vecs[2];
        verts[7] = vecs[1].vecs[3];
        verts += 8;
        vecs++;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C6A30.s")
void s19b_jbullet_800C6A30(POLY_FT4 *packs, DG_TEX *tex, int n_packs);

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C6B7C.s")
int s19b_jbullet_800C6B7C(Work *work, MATRIX *world, int arg3);

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jbullet_800C6EA0.s")
void s19b_jbullet_800C6EA0(Work *work);

void s19b_jbullet_800C7138(Work *work)
{
    GM_FreePrim(work->prim);
}

int s19b_jbullet_800C7174(Work *work, int side)
{
    SVECTOR scale;
    TARGET *trg;

    trg = &work->target;
    GM_SetTarget(trg, TARGET_POWER, side, &s19b_dword_800C33C0);

    scale.vx = work->field_120.vx >> 3;
    scale.vy = work->field_120.vy >> 3;
    scale.vz = work->field_120.vz >> 3;

    if (side == PLAYER_SIDE)
    {
        GM_Target_8002DCCC(trg, 3, 1, work->life, 0, &scale);
    }
    else
    {
        GM_Target_8002DCCC(trg, 3, 1, (work->life * 2) / 3, 0, &scale);
    }

    return 0;
}

int s19b_jbullet_800C726C(Work *work, MATRIX *world, int arg2, int arg3, int side)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->field_164 = 0;
    work->map = GM_CurrentMap;
    work->world = *world;

    DG_SetPos(world);
    DG_PutVector(&s19b_dword_800C33D0, &work->field_110, 1);

    s19b_dword_800C33C8.vy = -work->field_15C;
    DG_RotVector(&s19b_dword_800C33C8, &work->field_120, 1);

    work->field_138 = s19b_jbullet_800C6B7C(work, world, arg3);
    work->field_13C = 0;

    if (work->field_160 != 0)
    {
        work->field_15C = (work->field_15C * work->field_160) >> 12;
    }

    if (arg2 == 0)
    {
        return 0;
    }

    if (arg2 >= 0)
    {
        if (arg2 < 3)
        {
            work->prim = prim = GM_MakePrim(DG_PRIM_POLY_FT4, 2, work->vertices, NULL);
            if (prim == NULL)
            {
                return -1;
            }

            tex = DG_GetTexture(GV_StrCode("bullet"));
            if (tex == NULL)
            {
                return -1;
            }

            s19b_jbullet_800C6A30(prim->packs[0], tex, arg2);
            s19b_jbullet_800C6A30(prim->packs[1], tex, arg2);

            s19b_jbullet_800C6778(work);
        }
    }

    return 0;
}

void *NewJeepBullet(MATRIX *world, int side, int arg2, int arg3)
{
    SVECTOR vec;
    Work   *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jbullet_800C6EA0, s19b_jbullet_800C7138, "jbullet.c");

        vec.vx = world->m[0][0];
        vec.vy = world->m[1][0];
        vec.vz = world->m[2][0];

        work->field_160 = GV_VecLen3(&vec);
        work->field_150 = 10;
        work->life = 64;

        if (arg3 == 2)
        {
            work->field_158 = 100000;
            work->field_15C = 5000;
        }
        else
        {
            work->field_158 = 15000;
            work->field_15C = 750;
        }

        work->field_168 = 1;

        if (s19b_jbullet_800C726C(work, world, arg2, arg3, side) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }

        if (s19b_jbullet_800C7174(work, side) < 0)
        {
            GV_DestroyActor(work);
        }

        work->field_14C = 256;
        work->field_144 = arg3;
        work->field_134 = arg2;
        work->side = side;
    }

    return work;
}

void *NewJeepBullet2(MATRIX *world, int side, int arg2, int arg3)
{
    SVECTOR vec;
    Work   *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jbullet_800C6EA0, s19b_jbullet_800C7138, "jbullet.c");

        vec.vx = world->m[0][0];
        vec.vy = world->m[1][0];
        vec.vz = world->m[2][0];

        work->field_160 = GV_VecLen3(&vec);
        work->field_150 = 10;
        work->life = 64;

        if (arg3 == 2)
        {
            work->field_158 = 100000;
            work->field_15C = 5000;
        }
        else
        {
            work->field_158 = 15000;
            work->field_15C = 750;
        }

        work->field_168 = 0;

        if (s19b_jbullet_800C726C(work, world, arg2, arg3, side) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }

        if (s19b_jbullet_800C7174(work, side) < 0)
        {
            GV_DestroyActor(work);
        }

        work->field_14C = 256;
        work->field_144 = arg3;
        work->field_134 = arg2;
        work->side = side;
    }

    return work;
}
