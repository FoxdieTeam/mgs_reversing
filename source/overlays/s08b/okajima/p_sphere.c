#include "mgstype.h"
#include "game/game.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"

// Two glowing balls ("nja_ball") on the hands of the cyborg ninja which throw plasma bolts (NewPlasmaL) around.

#define P_SPHERE_NUM_BALLS 2

// Values of the state word shared with the ninja (Work->state)
enum
{
    P_SPHERE_SHRINK = -1, // fade out, die when small enough
    P_SPHERE_BUSY = 0,
    P_SPHERE_GROW_0 = 1,  // request: big first ball
    P_SPHERE_GROW_1 = 2,  // request: big second ball
    P_SPHERE_FADE = 3     // request: shrink and die
};

typedef struct _Work
{
    GV_ACT   actor;                        /* 0x000 */
    OBJECT   objs[P_SPHERE_NUM_BALLS];     /* 0x020, 0x104 */
    MATRIX   light[P_SPHERE_NUM_BALLS][2]; /* 0x1E8 */
    DG_OBJ  *parent[P_SPHERE_NUM_BALLS];   /* 0x268 */
    SVECTOR  pos[P_SPHERE_NUM_BALLS];      /* 0x270 */
    SVECTOR  rot[P_SPHERE_NUM_BALLS];      /* 0x280 */
    int      scale[P_SPHERE_NUM_BALLS];    /* 0x290 */
    int      target[P_SPHERE_NUM_BALLS];   /* 0x298 */
    int      angle[P_SPHERE_NUM_BALLS];    /* 0x2A0 */
    int      angle2[P_SPHERE_NUM_BALLS];   /* 0x2A8 */
    int      field_2B0[P_SPHERE_NUM_BALLS]; /* 0x2B0 */
    int      field_2B8;                    /* 0x2B8 */
    int      field_2BC;                    /* 0x2BC */
    int     *state;                        /* 0x2C0 */
    SVECTOR  jitter[2];                    /* 0x2C4 */
    SVECTOR  bolt_end[2];                  /* 0x2D4 */
} Work;

int s08b_dword_800C3614 = 0x00000000;
int s08b_dword_800C3618 = 0x00000000;
int s08b_dword_800C361C = 0x00000000;

const char s08b_aNjaball_800E40B8[] = "nja_ball";
const char s08b_aBallhlf_800E40C4[] = "ballhlf";

extern void *NewPlasmaL(SVECTOR *from, SVECTOR *to, int life);

void s08b_p_sphere_800D8F20(void *unused, MATRIX **m, int scale)
{
    VECTOR v;

    (void)unused;
    v.vx = scale;
    v.vy = scale;
    v.vz = scale;
    ScaleMatrix(*m, &v);
}

// FIXME: NON_MATCHING attempt in C below. The structure is right but gcc's register allocation / spills of the loop
// pointers differ (the original keeps rot->vy/vz in a separate induction pointer, see GetResources). The VR build
// pastes the original code as relocatable asm so that the object stays shareable.
#if 0 /* NON_MATCHING */
void s08b_p_sphere_800D8F50(Work *work)
{
    OBJECT  *obj;
    SVECTOR *rot;
    short   *rotz;
    int     *scale;
    int     *target;
    SVECTOR  vec;
    int      i;
    int      j;
    int      amount;
    int      half;
    int      quarter;
    int      bx, by, bz;

    obj = work->objs;
    rot = work->rot;
    scale = work->scale;
    target = work->target;

    GM_CurrentMap = GM_PlayerMap;

    if (*work->state != P_SPHERE_SHRINK)
    {
        switch (*work->state)
        {
        case P_SPHERE_GROW_0:
            *work->state = P_SPHERE_BUSY;
            work->scale[0] = 0x800;
            work->target[0] = 0x1000;
            work->scale[1] = 0x800;
            work->target[1] = 0x800;
            break;

        case P_SPHERE_GROW_1:
            *work->state = P_SPHERE_BUSY;
            work->scale[0] = 0x1000;
            work->target[0] = 0x800;
            work->scale[1] = 0x800;
            work->target[1] = 0x800;
            break;

        case P_SPHERE_FADE:
            *work->state = P_SPHERE_SHRINK;
            work->target[0] = 0;
            work->target[1] = 0;
            break;
        }
    }

    for (i = 0, rotz = &rot->vz; i < P_SPHERE_NUM_BALLS; i++)
    {
        work->angle[i]++;
        work->angle2[i]++;

        work->pos[i].vx = work->parent[i]->world.t[0];
        work->pos[i].vy = work->parent[i]->world.t[1];
        work->pos[i].vz = work->parent[i]->world.t[2];

        rot->vx += 0x20;
        rotz[-1] += 0x7B;
        rotz[0] += 0x127;

        if (*target < *scale)
        {
            *scale = *scale * 31 / 32;
        }
        else
        {
            *scale = *target;
        }

        amount = *scale;

        if (*work->state == P_SPHERE_SHRINK && amount < 500)
        {
            GV_DestroyActor(&work->actor);
            return;
        }

        bx = DG_Chanls[1].eye.m[0][2];
        by = DG_Chanls[1].eye.m[1][2];
        bz = DG_Chanls[1].eye.m[2][2];

        if (i == 0)
        {
            for (j = 0; j < 2; j++)
            {
                if ((GV_Time + j) % 2 == j)
                {
                    work->jitter[j].vx += GV_RandU(0x80) + 0x80;
                    work->jitter[j].vy += GV_RandU(0x80) + 0x80;
                    work->jitter[j].vz += GV_RandU(0x80) + 0x80;

                    vec.vx = 0;
                    vec.vy = 0;
                    vec.vz = amount * 1000 / 4096;

                    DG_SetPos2(&work->pos[i], &work->jitter[j]);
                    DG_PutVector(&vec, &vec, 1);

                    NewPlasmaL(&work->bolt_end[j], &vec, 2);
                    work->bolt_end[j] = vec;
                }
            }
        }

        DG_SetPos2(&work->pos[i], rot);
        GM_ActObject2(obj);
        s08b_p_sphere_800D8F20(work, (MATRIX **)obj, amount);

        if (amount > 0x1000)
        {
            amount = 0x1000;
        }

        half = amount / 8;
        quarter = amount / 4;

        work->light[i][0].m[0][0] = bx + rsin(work->angle[i] * 0x40) / 8;
        work->light[i][0].m[0][1] = by + rsin(work->angle[i] * 0x9A) / 8;
        work->light[i][0].m[0][2] = bz + rsin(work->angle[i] * 0x14E) / 8;
        work->light[i][1].m[0][0] = half;
        work->light[i][1].m[1][0] = half;
        work->light[i][1].m[2][0] = quarter;
        work->light[i][0].m[1][0] = bx + rsin(work->angle[i] * 0xA4) / 2;
        work->light[i][0].m[1][1] = by + rsin(work->angle[i] * 0xFE) / 2;
        work->light[i][0].m[1][2] = bz + rsin(work->angle[i] * 0x180) / 2;
        work->light[i][1].m[0][1] = half;
        work->light[i][1].m[1][1] = half;
        work->light[i][1].m[2][1] = quarter;
        work->light[i][0].m[2][0] = bx + rsin(work->angle[i] * 0x108);
        work->light[i][0].m[2][1] = by + rsin(work->angle[i] * 0x162);
        work->light[i][0].m[2][2] = bz + rsin(work->angle[i] * 0x1B2);
        work->light[i][1].m[0][2] = half;
        work->light[i][1].m[1][2] = half;
        work->light[i][1].m[2][2] = quarter;

        obj++;
        rot++;
        rotz += 4;
        scale++;
        target++;
    }
}
#endif

#ifdef VR_EXE
#pragma INCLUDE_ASM_RELOC("source/overlays/s08b/okajima/reloc/p_sphere_act.s")
#else
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_p_sphere_800D8F50.s")
#endif

void s08b_p_sphere_800D9574(Work *work)
{
    int i;

    for (i = 0; i < 2; i++)
    {
        GM_FreeObject(&work->objs[i]);
    }
    s08b_dword_800C361C = 0;
}

// FIXME: NON_MATCHING attempt in C below (21 words differ: the order in which gcc emits the setup of the loop's
// induction variables and the scheduling of the first stores). The VR build pastes the original code as relocatable
// asm so that the object stays shareable.
#if 0 /* NON_MATCHING */
int s08b_p_sphere_800D95CC(Work *work, DG_OBJS **pobjs, int *state)
{
    OBJECT  *obj;
    SVECTOR *pos;
    SVECTOR *rot;
    int     *scale;
    short   *rotz;
    short   *posz;
    int      i;
    int      j;
    DG_TEX  *tex;

    obj = work->objs;
    pos = work->pos;
    rot = work->rot;
    scale = work->scale;
    // FIXME: y/z of the rotation and position are reached through second pointers (steers gcc's induction variables)
    rotz = &work->rot[0].vz;
    posz = &work->pos[0].vz;

    work->state = state;
    work->parent[0] = &(*pobjs)->objs[0];
    work->field_2B8 = 0;
    work->field_2BC = 8;
    work->parent[1] = &(*pobjs)->objs[4];

    for (i = 0; i < P_SPHERE_NUM_BALLS; i++)
    {
        work->light[i][0].t[0] = 0;
        work->light[i][0].t[1] = 0;
        work->light[i][0].t[2] = 0;

        GM_InitObject(obj, GV_StrCode(s08b_aNjaball_800E40B8), 0x16D, 0);
        GM_ConfigObjectJoint(obj);
        GM_ConfigObjectLight(obj, work->light[i]);

        pos->vx = work->parent[i]->world.t[0];
        posz[-1] = work->parent[i]->world.t[1];
        posz[0] = work->parent[i]->world.t[2];

        rot->vx = GV_RandU(0x1000);
        rotz[-1] = GV_RandU(0x1000);
        rotz[0] = GV_RandU(0x1000);

        *scale = 0x80;
        work->angle[i] = GV_RandU(0x1000);
        work->angle2[i] = 0;
        work->field_2B0[i] = 0;

        if (i == 0)
        {
            for (j = 0; j < 2; j++)
            {
                work->jitter[j].vx = GV_RandU(0x1000);
                work->jitter[j].vy = GV_RandU(0x1000);
                work->jitter[j].vz = GV_RandU(0x1000);
                work->bolt_end[j] = *pos;
            }
        }

        obj++;
        posz += 4;
        pos++;
        rotz += 4;
        rot++;
        scale++;
    }

    tex = DG_GetTexture(GV_StrCode(s08b_aBallhlf_800E40C4));
    if (tex == NULL)
    {
        return -1;
    }

    tex->tpage = (tex->tpage & 0xFF9F) | 0x20;
    return 0;
}
#endif

#ifdef VR_EXE
#pragma INCLUDE_ASM_RELOC("source/overlays/s08b/okajima/reloc/p_sphere_res.s")
#else
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_p_sphere_800D95CC.s")
#endif

const char s08b_aPspherec_800E40CC[] = "p_sphere.c";

extern void s08b_p_sphere_800D8F50(Work *work);
extern int  s08b_p_sphere_800D95CC(Work *work, DG_OBJS **pobjs, int *state);

void *s08b_p_sphere_800D9834(DG_OBJS **pobjs, int *state)
{
    Work *work;

    if (s08b_dword_800C361C == 1)
    {
        return NULL;
    }

    work = GV_NewActor(4, sizeof(Work));
    if (work != NULL)
    {
        s08b_dword_800C361C = 1;
        GV_SetNamedActor(work, s08b_p_sphere_800D8F50, s08b_p_sphere_800D9574,
                         s08b_aPspherec_800E40CC);

        if (s08b_p_sphere_800D95CC(work, pobjs, state) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}
