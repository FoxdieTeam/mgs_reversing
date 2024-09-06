#include "common.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Takabe/thing.h"

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
extern int     GV_PauseLevel_800AB928;
extern int     GM_CurrentMap_800AB9B0;

unsigned short gas_efct_msgs[] = {0xD182, 0x006B};

#define EXEC_LEVEL 3

void d11c_800C4FFC(GasEfctWork *work);
void d11c_800C5094(GasEfctWork *work, int arg1);

void d11c_800C49A4(GasEfctWork *work, POLY_G4 *packs)
{
    int x1, y1, sin1, cos1;
    int x2, y2, sin2, cos2;
    int i;

    y1 = 230;
    y2 = (y1 * work->f64) / 4096;

    x1 = work->f5C;
    x2 = (x1 * work->f64) / 4096;

    sin1 = rsin(0);
    cos1 = rcos(0);

    for (i = 0; i < 16; i++)
    {
        setPolyG4(packs);
        setSemiTrans(packs, 1);

        sin2 = rsin((i + 1) * 256);
        cos2 = rcos((i + 1) * 256);

        packs->x0 = (cos1 * x1) / 4096;
        packs->y0 = (sin1 * x2) / 4096;

        packs->x1 = (cos2 * x1) / 4096;
        packs->y1 = (sin2 * x2) / 4096;

        packs->x2 = (cos1 * y1) / 4096;
        packs->y2 = (sin1 * y2) / 4096;

        packs->x3 = (cos2 * y1) / 4096;
        packs->y3 = (sin2 * y2) / 4096;

        sin1 = sin2;
        cos1 = cos2;

        setRGB0(packs, 30, 30, 0);
        setRGB1(packs, 30, 30, 0);
        setRGB2(packs, 100, 100, 60);
        setRGB3(packs, 100, 100, 60);
        packs++;
    }
}

void GasEffectAct_800C4BBC(GasEfctWork *work_copy)
{
    GasEfctWork *work;
    int          found;
    int          message;
    int          state;

    work = work_copy;

    if (GV_PauseLevel_800AB928 == 0)
    {
        found = THING_Msg_CheckMessage(work->name, 2, gas_efct_msgs);
        message = THING_Msg_GetResult();

        switch (found)
        {
        case 0:
            state = 1;
            work->f48 = message;
            break;

        case 1:
            state = 3;
            work->f48 = message;
            break;

        default:
            state = work->f3C;
            break;
        }

        if (GV_PauseLevel_800AB928 == 0)
        {
            switch (state)
            {
            case 1:
                if (work->f3C == 0)
                {
                    if (work->f40 == 0)
                    {
                        work->f40 = state;
                        d11c_800C4FFC(work);
                    }

                    work->f4C = 0;
                }

                if (GV_PauseLevel_800AB928 == 0)
                {
                    work->f4C = sub_8002646C(work->f4C, 4096, work->f48);
                }

                if (work->f4C == 4096)
                {
                    state = 2;
                }

                work->f3C = state;
                break;

            case 2:
                work->f3C = state;
                break;

            case 3:
                work->f4C = sub_8002646C(work->f4C, 0, work->f48);

                if (work->f4C == 0)
                {
                    state = 0;

                    if (work->f40 != 0)
                    {
                        GV_DelayedFree(work->prims);
                        work->f40 = 0;
                    }
                }

                work->f3C = state;
                break;

            case 0:
                work->f40 = 0;
                /* fallthrough */

            default:
                work->f3C = state;
                break;
            }
        }
    }

    if (work->f40 != 0)
    {
        d11c_800C5094(work, work->f4C);
    }

    work->f44++;
}

void GasEffectDie_800C4D64(GasEfctWork *work)
{
    if (work->f40 != 0)
    {
        GV_DelayedFree(work->prims);
    }
}

int GasEffectGetResources_800C4D98(GasEfctWork *work, int name, int where)
{
    if (GCL_GetOption('c'))
    {
        GCL_StrToSV(GCL_GetParamResult(), &work->f2C);
        GCL_StrToSV(GCL_GetParamResult(), &work->f34);
    }

    work->f48 = THING_Gcl_GetIntDefault('s', 4096);
    work->f50 = THING_Gcl_GetIntDefault('w', 410);
    work->f54 = THING_Gcl_GetIntDefault('f', 128);
    work->f58 = THING_Gcl_GetIntDefault('b', 1);
    work->f5C = THING_Gcl_GetInt('r');
    work->f64 = THING_Gcl_GetIntDefault('a', 3205);
    work->f40 = 0;
    work->f44 = 0;
    work->f3C = 0;

    return 0;
}

GV_ACT * NewGasEffect_800C4E5C(int name, int where, int argc, char **argv)
{
    GasEfctWork *work;

    work = (GasEfctWork *)GV_NewActor(EXEC_LEVEL, sizeof(GasEfctWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)GasEffectAct_800C4BBC, (TActorFunction)GasEffectDie_800C4D64, "gas_efct.c");

        if (GasEffectGetResources_800C4D98(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->map = where;
        work->name = name;
    }

    return &work->actor;
}

GV_ACT * NewGasEffect_800C4EF8(SVECTOR *arg0, int arg1, int arg2)
{
    GasEfctWork *work;

    work = (GasEfctWork *)GV_NewActor(EXEC_LEVEL, sizeof(GasEfctWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)GasEffectAct_800C4BBC, (TActorFunction)GasEffectDie_800C4D64, "gas_efct.c");
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

    work->prims = prims = GV_Malloc(sizeof(GasEfctPrims));
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
    SetLightMatrix(&sp10);

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

    if (!(GM_GameStatus_800AB3CC & STATE_THERMG))
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
