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
    DG_PRIM *prim;       // 30
    SVECTOR  f34;        // 34
    SVECTOR  f3C;        // 3C
    int      f44;        // 44
    int      f48;        // 48
    char     pad2[0x88]; // 4C
    SVECTOR  verts[68];  // D4
    SVECTOR  f2F4;
    SVECTOR  f2FC;
    SVECTOR  f304;
    SVECTOR  f30C;
    char     pad4[0x90];
    int      f3A4;
    int      f3A8;
    int      f3AC;
    int      f3B0;
    int      f3B4;
    int      f3B8;
    int      f3BC;
} PlasmaWork;

#define EXEC_LEVEL 4

extern int GM_CurrentMap_800AB9B0;

// Identical to UjiGetSvecs_800C39E8
int PlasmaGetSvecs_800CBBEC(char *opt, SVECTOR *svec)
{
    int   count;
    char *result;

    count = 0;

    while ((result = GCL_Get_Param_Result_80020AA4()) != NULL)
    {
        GCL_StrToSV_80020A14(result, svec);
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

    nmsgs = GV_ReceiveMessage_80016620(name, &msg);
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

        x = tex->field_8_offx;
        w = tex->field_A_width;
        y = tex->field_9_offy;
        h = tex->field_B_height;
        setUVWH(packs, x, y, w, h);

        packs->tpage = tex->field_4_tPage;

        packs->clut = tex->field_6_clut;
        packs->tpage |= 0x20;

        packs++;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s08c/s08c_plasma_800CBDA8.s")
void s08c_plasma_800CBDA8(PlasmaWork *, SVECTOR *, SVECTOR *);

void s08c_plasma_800CBF8C(PlasmaWork *work)
{
    int rnd;

    rnd = GV_RandU_80017090(256);
    work->f2F4.vx = work->f34.vx + (((work->f3C.vx - work->f34.vx) * rnd) >> 8);
    work->f2F4.vy = work->f34.vy + ((work->f44 * GV_RandU_80017090(256)) >> 8);
    work->f2F4.vz = work->f34.vz + (((work->f3C.vz - work->f34.vz) * rnd) >> 8);

    rnd = GV_RandU_80017090(256);
    work->f2FC.vx = work->f34.vx + (((work->f3C.vx - work->f34.vx) * rnd) >> 8);
    work->f2FC.vy = work->f34.vy + ((work->f44 * GV_RandU_80017090(256)) >> 8);
    work->f2FC.vz = work->f34.vz + (((work->f3C.vz - work->f34.vz) * rnd) >> 8);

    work->f304 = work->f2F4;
    work->f30C = work->f2FC;
    s08c_plasma_800CBDA8(work, &work->f304, &work->f30C);
}

#pragma INCLUDE_ASM("asm/overlays/s08c/s08c_plasma_800CC104.s")
#pragma INCLUDE_ASM("asm/overlays/s08c/s08c_plasma_800CC258.s")
#pragma INCLUDE_ASM("asm/overlays/s08c/s08c_plasma_800CC5E4.s")

#pragma INCLUDE_ASM("asm/overlays/s08c/s08c_plasma_800CC67C.s")
void s08c_plasma_800CC67C(PlasmaWork *); // PlasmaAct_800CC67C

void PlasmaDie_800CCC64(PlasmaWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

int Plasma_800CCCA0(PlasmaWork *work)
{
    DG_TEX  *tex;
    DG_PRIM *prim;

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("plasma"));
    if (tex == NULL)
    {
        return -1;
    }

    prim = DG_GetPrim(0x12, 17, 0, work->verts, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 200;

    PlasmaTexPacks_800CBCE8(work, &prim->field_40_pBuffers[0]->poly_ft4, 17, tex);
    PlasmaTexPacks_800CBCE8(work, &prim->field_40_pBuffers[1]->poly_ft4, 17, tex);

    return 0;
}

int PlasmaGetResources_800CCD6C(PlasmaWork *work, int name, int map)
{
    int opt;

    work->f3AC = 255;
    work->f3B0 = 0;
    work->f48 = 0;

    work->name = name;

    work->map = map;
    GM_CurrentMap_800AB9B0 = map;

    opt = GCL_GetOption_80020968('b');
    if (opt == NULL)
    {
        return -1;
    }

    PlasmaGetSvecs_800CBBEC((char *)opt, &work->f34);

    opt = GCL_GetOption_80020968('h');
    if (opt != NULL)
    {
        work->f44 = GCL_StrToInt_800209E8((char *)opt);
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
    work->f3A8 = arg4 + GV_RandU_80017090(16);

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

    s08c_plasma_800CBDA8(work, &sp10, &sp18);

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

    s08c_plasma_800CBDA8(work, arg1, arg2);
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

    s08c_plasma_800CBDA8(work, arg1, arg2);
    return 0;
}

GV_ACT *NewPlasma_800CD110(int name, int where)
{
    PlasmaWork *work;

    work = (PlasmaWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(PlasmaWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s08c_plasma_800CC67C,
                                  (TActorFunction)PlasmaDie_800CCC64, "plasma.c");

        if (PlasmaGetResources_800CCD6C(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

GV_ACT *NewPlasma_800CD1A4(OBJECT *parent, int arg1, int arg2, int arg3, int arg4, int arg5)
{
    PlasmaWork *work;

    work = (PlasmaWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(PlasmaWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s08c_plasma_800CC67C,
                                  (TActorFunction)PlasmaDie_800CCC64, "plasma.c");

        if (PlasmaGetResources_800CCE08(work, parent, arg1, arg2, arg3, arg4, arg5) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

GV_ACT *NewPlasma_800CD268(SVECTOR *arg0, SVECTOR *arg1, int arg2)
{
    PlasmaWork *work;

    work = (PlasmaWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(PlasmaWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s08c_plasma_800CC67C,
                                  (TActorFunction)PlasmaDie_800CCC64, "plasma.c");

        if (PlasmaGetResources_800CCF78(work, arg0, arg1, arg2) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

GV_ACT *NewPlasma_800CD30C(SVECTOR *arg0, SVECTOR *arg1, int arg2, int arg3)
{
    PlasmaWork *work;

    work = (PlasmaWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(PlasmaWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s08c_plasma_800CC67C,
                                  (TActorFunction)PlasmaDie_800CCC64, "plasma.c");

        if (PlasmaGetResources_800CD040(work, arg0, arg1, arg2, arg3) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
