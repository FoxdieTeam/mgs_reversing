#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"

typedef struct _GasEfctPrims
{
    DR_TPAGE tpage[2];
    POLY_G4  poly[2][16];
} GasEfctPrims;

typedef struct _GasEfctWork
{
    GV_ACT        actor;
    int           map;
    int           name;
    GasEfctPrims *prims;
    SVECTOR       f2C;
    SVECTOR       f34;
    int           f3C;
    int           f40;
    int           f44;
    int           f48;
    int           f4C;
    int           f50;
    int           f54;
    int           f58;
    int           f5C;
    int           f60;
    int           f64;
    char          pad[0x20];
} GasEfctWork;

extern MATRIX  DG_ZeroMatrix_8009D430;
extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GM_GameStatus_800AB3CC;
extern int     GV_Clock_800AB920;
extern int     GM_CurrentMap_800AB9B0;

extern const char d11c_dword_800C6748[]; // = "gas_efct.c"

#define EXEC_LEVEL 3

int GetParamOrDefault_800C5318(char param, int def);
int THING_Gcl_GetInt_800D8808(char param);

void psyq_SetLightMatrix(MATRIX *m);

#pragma INCLUDE_ASM("asm/overlays/d11c/d11c_800C49A4.s")
void d11c_800C49A4(GasEfctWork *work, POLY_G4 *packs);

#pragma INCLUDE_ASM("asm/overlays/d11c/d11c_800C4BBC.s")
void d11c_800C4BBC(GasEfctWork *work);


void d11c_800C4D64(GasEfctWork *work)
{
    if (work->f40 != 0)
    {
        GV_DelayedFree_80016254(work->prims);
    }
}

int d11c_800C4D98(GasEfctWork *work, int name, int where)
{
    if (GCL_GetOption_80020968('c'))
    {
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &work->f2C);
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &work->f34);
    }

    work->f48 = GetParamOrDefault_800C5318('s', 4096);
    work->f50 = GetParamOrDefault_800C5318('w', 410);
    work->f54 = GetParamOrDefault_800C5318('f', 128);
    work->f58 = GetParamOrDefault_800C5318('b', 1);
    work->f5C = THING_Gcl_GetInt_800D8808('r');
    work->f64 = GetParamOrDefault_800C5318('a', 3205);
    work->f40 = 0;
    work->f44 = 0;
    work->f3C = 0;

    return 0;
}

GV_ACT *d11c_800C4E5C(int name, int where)
{
    GasEfctWork *work;

    work = (GasEfctWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(GasEfctWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)d11c_800C4BBC, (TActorFunction)d11c_800C4D64, d11c_dword_800C6748);

        if (d11c_800C4D98(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        work->map = where;
        work->name = name;
    }

    return &work->actor;
}

GV_ACT *d11c_800C4EF8(SVECTOR *arg0, int arg1, int arg2)
{
    GasEfctWork *work;

    work = (GasEfctWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(GasEfctWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)d11c_800C4BBC, (TActorFunction)d11c_800C4D64, d11c_dword_800C6748);
        work->f48 = 4096;
        work->f50 = 410;
        work->f2C = DG_ZeroVector_800AB39C;
        work->f34 = *arg0;
        work->f64 = 3205;
        work->f50 = 0;
        work->f58 = arg2;
        work->f5C = arg1;
        work->f40 = 0;
        work->f44 = 0;
        work->f3C = 0;
        work->name = 0x3B8E;
        work->map = GM_CurrentMap_800AB9B0;
    }

    return &work->actor;
}

void d11c_800C4FFC(GasEfctWork *work)
{
    GasEfctPrims *prims;

    work->prims = prims = GV_Malloc_8001620C(sizeof(GasEfctPrims));
    if (prims == NULL)
    {
        work->f40 = 0;
        return;
    }

    setDrawTPage(&prims->tpage[0], 0, 1, work->f58 << 5);
    setDrawTPage(&prims->tpage[1], 0, 1, work->f58 << 5);

    d11c_800C49A4(work, prims->poly[0]);
    d11c_800C49A4(work, prims->poly[1]);
}

void d11c_800C5094(GasEfctWork *work, int arg1)
{
    MATRIX   sp10;
    SVECTOR  sp30;
    char    *ot;
    POLY_G4 *poly;
    int      factor;
    int      angle;
    int      scale;
    int      col0, col1;
    int      i;

    ot = DG_ChanlOTag(0);
    poly = work->prims->poly[GV_Clock_800AB920];

    sp10 = DG_ZeroMatrix_8009D430;

    factor = (arg1 * work->f50) >> 12;
    angle = rsin(work->f44 * work->f54);
    scale = arg1 + ((angle * factor) >> 12);

    sp10.m[2][2] = scale;
    sp10.m[1][1] = scale;
    sp10.m[0][0] = scale;
    psyq_SetLightMatrix(&sp10);

    gte_ldv0(&work->f2C);
    gte_ll();
    gte_stsv(&sp30);
    gte_ldv0(&work->f34);
    gte_ll();
    poly->r0 = sp30.vx;
    poly->g0 = sp30.vy;
    poly->b0 = sp30.vz;
    gte_stsv(&sp30);
    poly->r1 = sp30.vx;
    poly->g1 = sp30.vy;
    poly->b1 = sp30.vz;

    col0 = LLOAD(&poly->r0);
    col1 = LLOAD(&poly->r1);

    if (!(GM_GameStatus_800AB3CC & 0x8))
    {
        for (i = 0; i < 16; poly++, i++)
        {
            LSTORE(col0, &poly->r0);
            LSTORE(col0, &poly->r1);
            LSTORE(col1, &poly->r2);
            LSTORE(col1, &poly->r3);
            addPrim(ot, poly);
        }

        addPrim(ot, &work->prims->tpage[GV_Clock_800AB920]);
    }
}
