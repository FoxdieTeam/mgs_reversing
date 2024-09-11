#include <stddef.h> // for NULL
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"

typedef struct _PlasmaWork
{
    GV_ACT   actor;
    int      map;
    int      name;
    MATRIX  *f28;
    MATRIX  *f2C;
    DG_PRIM *prim;
    SVECTOR  f34;
    SVECTOR  f3C;
    int      f44;
    int      f48;
    SVECTOR  f4C[17];
    SVECTOR  verts[68];
    SVECTOR  f2F4;
    SVECTOR  f2FC;
    SVECTOR  f304;
    SVECTOR  f30C;
    char     pad2[0x8];
    short    f31C[17];
    short    f33E[17];
    int      f360[17];
    int      f3A4;
    int      f3A8;
    int      f3AC;
    int      f3B0;
    int      f3B4;
    int      f3B8;
    int      f3BC;
} PlasmaWork;

extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GV_Clock_800AB920;
extern int     GM_CurrentMap_800AB9B0;

#define EXEC_LEVEL 4

// Identical to UjiGetSvecs_800C39E8
int PlasmaGetSvecs_800CBBEC(char *opt, SVECTOR *svec)
{
    int   count;
    char *result;

    count = 0;

    while ((result = GCL_GetParamResult()) != NULL)
    {
        GCL_StrToSV(result, svec);
        svec++;
        count++;
    }

    return count;
}

// Identical to d03a_red_alrt_800C437C
int Plasma_800CBC40(unsigned short name, int nhashes, unsigned short *hashes)
{
    GV_MSG *msg;
    int     nmsgs;
    int     found;
    int     hash;
    int     i;

    nmsgs = GV_ReceiveMessage(name, &msg);
    found = -1;

    for (; nmsgs > 0; nmsgs--, msg++)
    {
        hash = msg->message[0];

        for (i = 0; i < nhashes; i++)
        {
            if (hash == hashes[i])
            {
                found = i;
            }
        }
    }

    return found;
}

void PlasmaShadePacks_800CBCD8(POLY_FT4 *packs, int shade)
{
    setRGB0(packs, shade, shade, shade);
}

void PlasmaTexPacks_800CBCE8(PlasmaWork *work, POLY_FT4 *packs, int n_packs, DG_TEX *tex)
{
    int x, y, w, h;

    while (--n_packs >= 0)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);

        if (work->f3BC == 1)
        {
            setRGB0(packs, 150, 150, 250);
        }
        else
        {
            setRGB0(packs, 80, 80, 80);
        }

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;
        setUVWH(packs, x, y, w, h);

        packs->tpage = tex->tpage;

        packs->clut = tex->clut;
        packs->tpage |= 0x20;

        packs++;
    }
}

void Plasma_800CBDA8(PlasmaWork *work, SVECTOR *arg1, SVECTOR *arg2)
{
    int i;

    if (work->f3BC == 1)
    {
        for (i = 0; i < 5; i++)
        {
            work->f31C[i * 4] = work->f3B8 + GV_RandS(32);
            work->f33E[i * 4] = GV_RandU(4096);
            work->f360[i * 4] = GV_RandU(4096);
        }
    }
    else
    {
        for (i = 0; i < 5; i++)
        {
            work->f31C[i * 4] = GV_RandU(4096);
            work->f33E[i * 4] = GV_RandU(4096);
            work->f360[i * 4] = GV_RandU(4096);
        }
    }

    if (work->f33E[8] < work->f33E[4])
    {
        work->f33E[4] = work->f33E[8];
    }

    if (work->f33E[12] < work->f33E[4])
    {
        work->f33E[4] = work->f33E[12];
    }

    if (work->f33E[12] < work->f33E[8])
    {
        work->f33E[8] = work->f33E[12];
    }

    work->f2F4 = *arg1;
    work->f2FC = *arg2;

    work->f4C[0] = work->f2F4;
    work->f4C[16] = work->f2FC;

    work->f33E[0] = 0;
    work->f33E[16] = 4096;

    work->f360[0] = 0;
    work->f360[16] = 0;
}

void Plasma_800CBF8C(PlasmaWork *work)
{
    int rnd;

    rnd = GV_RandU(256);
    work->f2F4.vx = work->f34.vx + (((work->f3C.vx - work->f34.vx) * rnd) >> 8);
    work->f2F4.vy = work->f34.vy + ((work->f44 * GV_RandU(256)) >> 8);
    work->f2F4.vz = work->f34.vz + (((work->f3C.vz - work->f34.vz) * rnd) >> 8);

    rnd = GV_RandU(256);
    work->f2FC.vx = work->f34.vx + (((work->f3C.vx - work->f34.vx) * rnd) >> 8);
    work->f2FC.vy = work->f34.vy + ((work->f44 * GV_RandU(256)) >> 8);
    work->f2FC.vz = work->f34.vz + (((work->f3C.vz - work->f34.vz) * rnd) >> 8);

    work->f304 = work->f2F4;
    work->f30C = work->f2FC;
    Plasma_800CBDA8(work, &work->f304, &work->f30C);
}

void Plasma_800CC104(PlasmaWork *work)
{
    work->f31C[4] = (work->f31C[4] + GV_RandU(32)) & 0xFFF;
    work->f33E[4] = (work->f33E[4] + GV_RandS(64)) & 0xFFF;
    work->f360[4] = (work->f360[4] + GV_RandS(128)) & 0x7FF;

    work->f31C[8] = (work->f31C[8] + GV_RandU(32)) & 0xFFF;
    work->f33E[8] = (work->f33E[8] + GV_RandS(64)) & 0xFFF;
    work->f360[8] = (work->f360[8] + GV_RandS(128)) & 0x7FF;

    work->f31C[12] = (work->f31C[12] + GV_RandU(32)) & 0xFFF;
    work->f33E[12] = (work->f33E[12] + GV_RandS(64)) & 0xFFF;
    work->f360[12] = (work->f360[12] + GV_RandS(128)) & 0x7FF;

    if (work->f33E[8] < work->f33E[4])
    {
        work->f33E[4] = work->f33E[8];
    }

    if (work->f33E[12] < work->f33E[4])
    {
        work->f33E[4] = work->f33E[12];
    }

    if (work->f33E[12] < work->f33E[8])
    {
        work->f33E[8] = work->f33E[12];
    }
}

void Plasma_800CC258(PlasmaWork *work)
{
    SVECTOR   pos;
    SVECTOR   rot;
    POLY_FT4 *packs;

    packs = &work->prim->packs[GV_Clock_800AB920]->poly_ft4;

    if ((work->f3AC > 3) && (work->f3AC < 6))
    {
        if (work->f3AC == 4)
        {
            work->f2F4.vx += GV_RandS(128);
            work->f2F4.vy += GV_RandS(128);
            work->f2F4.vz += GV_RandS(128);
        }

        pos.vx = 0;
        pos.vy = work->f3B4;
        pos.vz = 0;

        if (work->f3BC == 1)
        {
            rot.vx = 0;
            rot.vy = work->f3B8;
        }
        else
        {
            rot.vx = GV_RandU(4096);
            rot.vy = GV_RandU(4096);
        }

        rot.vz = 0;

        DG_SetPos2(&DG_ZeroVector_800AB39C, &rot);
        DG_PutVector(&pos, &pos, 1);

        GV_AddVec3(&work->f2FC, &pos, &work->f2FC);
    }
    else if ((GV_RandS(32) == 0) && (work->f3AC != 0xFF))
    {
        PlasmaShadePacks_800CBCD8(packs, 128);

        work->f2F4.vx += GV_RandS(128);
        work->f2F4.vy += GV_RandS(128);
        work->f2F4.vz += GV_RandS(128);

        work->f2FC.vx += GV_RandS(1024);
        work->f2FC.vy += GV_RandS(1024);
        work->f2FC.vz += GV_RandS(1024);
    }
    else
    {
        PlasmaShadePacks_800CBCD8(packs, 80);
    }

    if (work->f3BC == 1)
    {
        work->f31C[4] += GV_RandS(64);
        work->f33E[4] += GV_RandS(32);
        work->f360[4] += GV_RandS(32);

        work->f31C[8] += GV_RandS(64);
        work->f33E[8] += GV_RandS(32);
        work->f360[8] += GV_RandS(32);

        work->f31C[12] += GV_RandS(64);
        work->f33E[12] += GV_RandS(32);
        work->f360[12] += GV_RandS(32);
    }
    else
    {
        work->f31C[4] = work->f31C[0] + GV_RandU(512);
        work->f33E[4] = GV_RandU(4096);
        work->f360[4] = GV_RandU(4096) >> 2;

        work->f31C[8] = work->f31C[4] + GV_RandU(512);
        work->f33E[8] = GV_RandU(4096);
        work->f360[8] = GV_RandU(4096);

        work->f31C[12] = work->f31C[8] + GV_RandU(512);
        work->f33E[12] = GV_RandU(4096);
        work->f360[12] = GV_RandU(4096) >> 1;
    }

    if (work->f33E[8] < work->f33E[4])
    {
        work->f33E[4] = work->f33E[8];
    }

    if (work->f33E[12] < work->f33E[4])
    {
        work->f33E[4] = work->f33E[12];
    }

    if (work->f33E[12] < work->f33E[8])
    {
        work->f33E[8] = work->f33E[12];
    }
}

void Plasma_800CC5E4(PlasmaWork *work, int arg1, int arg2)
{
    int idx1, idx2;

    idx1 = arg1 - arg2;
    idx2 = arg1 + arg2;

    work->f33E[arg1] = work->f33E[idx1] + (((work->f33E[idx2] - work->f33E[idx1]) * 3) >> 2);
    work->f360[arg1] = work->f360[idx1] + ((work->f360[idx2] - work->f360[idx1]) >> 1);
    work->f31C[arg1] = work->f31C[idx1] + ((work->f31C[idx2] - work->f31C[idx1]) >> 1);
}

void PlasmaAct_800CC67C(PlasmaWork *work)
{
    SVECTOR        sp10;
    SVECTOR        sp18;
    SVECTOR        sp20;
    SVECTOR        sp28;
    SVECTOR        sp30;
    unsigned short sp38[2];
    int            dx, dy, dz;
    int            ang;
    int            len;
    int            i;
    SVECTOR       *base;
    SVECTOR       *verts;

    GM_CurrentMap_800AB9B0 = work->map;

    if (work->f3AC != 255)
    {
        if (work->f3A4 > work->f3A8)
        {
            GV_DestroyActor(&work->actor);
        }

        if (work->f3AC != 5)
        {
            work->f2F4.vx = work->f28->t[0];
            work->f2F4.vy = work->f28->t[1];
            work->f2F4.vz = work->f28->t[2];

            work->f2FC.vx = work->f2C->t[0];
            work->f2FC.vy = work->f2C->t[1];
            work->f2FC.vz = work->f2C->t[2];
        }
    }

    work->f3A4++;

    if (GV_RandU(512) == 0)
    {
        work->f3B0 = GV_RandS(32);
    }

    switch (work->f3AC)
    {
    case 0:
    case 4:
    case 5:
        Plasma_800CC258(work);
        break;

    case 1:
        Plasma_800CC104(work);
        break;

    case 2:
        if ((work->f3A4 % 70) < (work->f3B0 + 35))
        {
            Plasma_800CC258(work);
        }
        else
        {
            Plasma_800CC104(work);
        }
        break;

    case 255:
        sp38[0] = GV_StrCode("はじめ");
        sp38[1] = GV_StrCode("やめ");

        switch (Plasma_800CBC40(work->name, 2, sp38))
        {
        case 0:
            work->f48 = 1;
            Plasma_800CBF8C(work);
            break;

        case 1:
            work->f48 = 0;
            break;
        }

        work->f2F4 = work->f304;
        work->f2FC = work->f30C;

        if (work->f48 == 0)
        {
            return;
        }

        if (GV_RandU(16) == 0)
        {
            Plasma_800CBF8C(work);
        }

        if ((work->f3A4 % 50) < (work->f3B0 + 35))
        {
            Plasma_800CC258(work);
        }
        else
        {
            Plasma_800CC104(work);
        }

        if (GV_RandU(16) == 0)
        {
            GM_SeSetMode_800329C4(&work->f2F4, 179, GM_SEMODE_BOMB);
        }
        break;
    }

    dx = work->f2FC.vx - work->f2F4.vx;
    dz = work->f2FC.vz - work->f2F4.vz;
    dy = work->f2FC.vy - work->f2F4.vy;

    ang = SquareRoot0(dx * dx + dz * dz);
    len = GV_DiffVec3(&work->f2F4, &work->f2FC);

    sp18.vx = ratan2(ang, dy);
    sp18.vy = ratan2(dx, dz);
    sp18.vz = 0;

    Plasma_800CC5E4(work, 2, 2);
    Plasma_800CC5E4(work, 6, 2);
    Plasma_800CC5E4(work, 10, 2);
    Plasma_800CC5E4(work, 14, 2);

    for (i = 0; i < 8; i++)
    {
        Plasma_800CC5E4(work, i * 2 + 1, 1);
    }

    sp20.vx = 0;
    sp20.vz = 0;

    sp10.vx = 0;

    for (i = 0; i < 17; i++)
    {
        sp10.vy = (len * work->f33E[i]) >> 12;
        sp10.vz = (len * work->f360[i]) >> 12;

        sp20.vy = work->f31C[i];

        DG_SetPos2(&DG_ZeroVector_800AB39C, &sp20);
        DG_PutVector(&sp10, &work->f4C[i], 1);
    }

    DG_SetPos2(&work->f2F4, &sp18);
    DG_PutVector(work->f4C, work->f4C, 17);

    len >>= 7;
    sp10.vx = len + GV_RandS(16);
    sp10.vy = len + GV_RandS(16);
    sp10.vz = len;

    sp28 = work->f4C[0];

    base = &work->f4C[1];
    verts = work->verts;

    GV_AddVec3(&work->f4C[0], &sp10, &sp30);

    for (i = 0; i < 16; i++)
    {
        *verts++ = sp28;
        *verts = *base;
        sp28 = *verts++;
        *verts++ = sp30;

        GV_AddVec3(base, &sp10, verts);

        sp30 = *verts++;
        base++;
    }
}

void PlasmaDie_800CCC64(PlasmaWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

int Plasma_800CCCA0(PlasmaWork *work)
{
    DG_TEX  *tex;
    DG_PRIM *prim;

    tex = DG_GetTexture(GV_StrCode("plasma"));
    if (tex == NULL)
    {
        return -1;
    }

    prim = DG_GetPrim(DG_PRIM_POLY_FT4, 17, 0, work->verts, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 200;

    PlasmaTexPacks_800CBCE8(work, &prim->packs[0]->poly_ft4, 17, tex);
    PlasmaTexPacks_800CBCE8(work, &prim->packs[1]->poly_ft4, 17, tex);

    return 0;
}

int PlasmaGetResources_800CCD6C(PlasmaWork *work, int name, int map)
{
    char *opt;

    work->f3AC = 255;
    work->f3B0 = 0;
    work->f48 = 0;

    work->name = name;

    work->map = map;
    GM_CurrentMap_800AB9B0 = map;

    opt = GCL_GetOption('b');
    if (opt == NULL)
    {
        return -1;
    }

    PlasmaGetSvecs_800CBBEC(opt, &work->f34);

    opt = GCL_GetOption('h');
    if (opt != NULL)
    {
        work->f44 = GCL_StrToInt(opt);
    }
    else
    {
        work->f44 = 0;
    }

    if (Plasma_800CCCA0(work) < 0)
    {
        return -1;
    }

    return 0;
}

int PlasmaGetResources_800CCE08(PlasmaWork *work, OBJECT *parent, int arg2, int arg3, int arg4, int arg5, int arg6)
{
    SVECTOR sp10;
    SVECTOR sp18;

    work->f3BC = 0;
    work->f3B0 = 0;

    work->map = GM_CurrentMap_800AB9B0;

    work->f3B4 = arg6;
    work->f3A8 = arg4 + GV_RandU(16);

    work->f28 = &parent->objs->objs[arg2].world;
    work->f2C = &parent->objs->objs[arg3].world;

    work->f3AC = arg5;

    if (Plasma_800CCCA0(work) < 0)
    {
        return -1;
    }

    sp10.vx = work->f28->t[0];
    sp10.vy = work->f28->t[1];
    sp10.vz = work->f28->t[2];

    sp18.vx = work->f2C->t[0];
    sp18.vy = work->f2C->t[1];
    sp18.vz = work->f2C->t[2];

    Plasma_800CBDA8(work, &sp10, &sp18);

    work->f3A4 = 0;
    return 0;
}

int PlasmaGetResources_800CCF78(PlasmaWork *work, SVECTOR *arg1, SVECTOR *arg2, int arg3)
{
    work->f3A8 = 1;
    work->f3B0 = 0;
    work->f3A4 = 0;
    work->map = GM_CurrentMap_800AB9B0;
    work->f2F4 = *arg1;
    work->f2FC = *arg2;
    work->f3B4 = arg3;
    work->f3BC = 0;
    work->f3AC = 5;

    if (Plasma_800CCCA0(work) < 0)
    {
        return -1;
    }

    Plasma_800CBDA8(work, arg1, arg2);
    return 0;
}

int PlasmaGetResources_800CD040(PlasmaWork *work, SVECTOR *arg1, SVECTOR *arg2, int arg3, int arg4)
{
    work->map = GM_CurrentMap_800AB9B0;

    work->f3B0 = 0;
    work->f3A4 = 0;
    work->f3A8 = 1;
    work->f2F4 = *arg1;
    work->f2FC = *arg2;

    work->f3B4 = arg4;
    work->f3B8 = arg3;
    work->f3BC = 1;
    work->f3AC = 5;

    if (Plasma_800CCCA0(work) < 0)
    {
        return -1;
    }

    Plasma_800CBDA8(work, arg1, arg2);
    return 0;
}

GV_ACT *NewPlasma_800CD110(int name, int where)
{
    PlasmaWork *work;

    work = (PlasmaWork *)GV_NewActor(EXEC_LEVEL, sizeof(PlasmaWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)PlasmaAct_800CC67C,
                         (TActorFunction)PlasmaDie_800CCC64, "plasma.c");

        if (PlasmaGetResources_800CCD6C(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

GV_ACT *NewPlasma_800CD1A4(OBJECT *parent, int arg1, int arg2, int arg3, int arg4, int arg5)
{
    PlasmaWork *work;

    work = (PlasmaWork *)GV_NewActor(EXEC_LEVEL, sizeof(PlasmaWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)PlasmaAct_800CC67C,
                         (TActorFunction)PlasmaDie_800CCC64, "plasma.c");

        if (PlasmaGetResources_800CCE08(work, parent, arg1, arg2, arg3, arg4, arg5) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

GV_ACT *NewPlasma_800CD268(SVECTOR *arg0, SVECTOR *arg1, int arg2)
{
    PlasmaWork *work;

    work = (PlasmaWork *)GV_NewActor(EXEC_LEVEL, sizeof(PlasmaWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)PlasmaAct_800CC67C,
                         (TActorFunction)PlasmaDie_800CCC64, "plasma.c");

        if (PlasmaGetResources_800CCF78(work, arg0, arg1, arg2) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

GV_ACT *NewPlasma_800CD30C(SVECTOR *arg0, SVECTOR *arg1, int arg2, int arg3)
{
    PlasmaWork *work;

    work = (PlasmaWork *)GV_NewActor(EXEC_LEVEL, sizeof(PlasmaWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)PlasmaAct_800CC67C,
                         (TActorFunction)PlasmaDie_800CCC64, "plasma.c");

        if (PlasmaGetResources_800CD040(work, arg0, arg1, arg2, arg3) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
