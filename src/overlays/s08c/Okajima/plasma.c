#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"

typedef struct _PlasmaWork
{
    GV_ACT   actor;
    int      map;
    char     pad[0xC];
    DG_PRIM *prim;
    char     pad2[0xA0];
    SVECTOR  verts[68];
    SVECTOR  f2F4;
    SVECTOR  f2FC;
    char     pad4[0xA0];
    int      f3A4;
    int      f3A8;
    int      f3AC;
    int      f3B0;
    SVECTOR *f3B4;
    int      f3B8;
    int      f3BC;
} PlasmaWork;

#define EXEC_LEVEL 4

extern int GM_CurrentMap_800AB9B0;

// Identical to UjiGetSvecs_800C39E8
int PlasmaGetSvecs_800CBBEC(int opt, SVECTOR *svec)
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

#pragma INCLUDE_ASM("asm/overlays/s08c/s08c_plasma_800CBCE8.s")
void s08c_plasma_800CBCE8(PlasmaWork *, POLY_FT4 *, int, DG_TEX *);

#pragma INCLUDE_ASM("asm/overlays/s08c/s08c_plasma_800CBDA8.s")
void s08c_plasma_800CBDA8(PlasmaWork *, void *, void *);

#pragma INCLUDE_ASM("asm/overlays/s08c/s08c_plasma_800CBF8C.s")
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

extern char s08c_aPlasma_800D1C14[];

int Plasma_800CCCA0(PlasmaWork *work, SVECTOR *unused)
{
    DG_TEX  *tex;
    DG_PRIM *prim;

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC(s08c_aPlasma_800D1C14));
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

    s08c_plasma_800CBCE8(work, &prim->field_40_pBuffers[0]->poly_ft4, 17, tex);
    s08c_plasma_800CBCE8(work, &prim->field_40_pBuffers[1]->poly_ft4, 17, tex);

    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s08c/s08c_plasma_800CCD6C.s")
int s08c_plasma_800CCD6C(PlasmaWork *, int, int); // PlasmaGetResources_800CCD6C

#pragma INCLUDE_ASM("asm/overlays/s08c/s08c_plasma_800CCE08.s")
int s08c_plasma_800CCE08(PlasmaWork *, int, int, int, int, int, int); // PlasmaGetResources_800CCE08

int PlasmaGetResources_800CCF78(PlasmaWork *arg0, SVECTOR *arg1, SVECTOR *arg2, SVECTOR *arg3)
{
    arg0->f3A8 = 1;
    arg0->f3B0 = 0;
    arg0->f3A4 = 0;
    arg0->map = GM_CurrentMap_800AB9B0;
    arg0->f2F4 = *arg1;
    arg0->f2FC = *arg2;
    arg0->f3B4 = arg3;
    arg0->f3BC = 0;
    arg0->f3AC = 5;

    if (Plasma_800CCCA0(arg0, arg1) < 0)
    {
        return -1;
    }
    s08c_plasma_800CBDA8(arg0, arg1, arg2);
    return 0;
}

int PlasmaGetResources_800CD040(PlasmaWork *work, SVECTOR *arg1, SVECTOR *arg2, int arg3, SVECTOR *arg4)
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

    do {} while (0);
    if (Plasma_800CCCA0(work, arg4) < 0)
    {
        return -1;
    }

    s08c_plasma_800CBDA8(work, arg1, arg2);
    return 0;
}

extern char s08c_dword_800D1C1C[];

GV_ACT *NewPlasma_800CD110(int arg0, int arg1)
{
    PlasmaWork *work;

    work = (PlasmaWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(PlasmaWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s08c_plasma_800CC67C,
                                  (TActorFunction)PlasmaDie_800CCC64, s08c_dword_800D1C1C);

        if (s08c_plasma_800CCD6C(work, arg0, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

GV_ACT *NewPlasma_800CD1A4(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5)
{
    PlasmaWork *work;

    work = (PlasmaWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(PlasmaWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s08c_plasma_800CC67C,
                                  (TActorFunction)PlasmaDie_800CCC64, s08c_dword_800D1C1C);

        if (s08c_plasma_800CCE08(work, arg0, arg1, arg2, arg3, arg4, arg5) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

GV_ACT *NewPlasma_800CD268(SVECTOR *arg0, SVECTOR *arg1, SVECTOR *arg2)
{
    PlasmaWork *work;

    work = (PlasmaWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(PlasmaWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s08c_plasma_800CC67C,
                                  (TActorFunction)PlasmaDie_800CCC64, s08c_dword_800D1C1C);

        if (PlasmaGetResources_800CCF78(work, arg0, arg1, arg2) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

GV_ACT *NewPlasma_800CD30C(SVECTOR *arg0, SVECTOR *arg1, int arg2, SVECTOR *arg3)
{
    PlasmaWork *work;

    work = (PlasmaWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(PlasmaWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s08c_plasma_800CC67C,
                                  (TActorFunction)PlasmaDie_800CCC64, s08c_dword_800D1C1C);

        if (PlasmaGetResources_800CD040(work, arg0, arg1, arg2, arg3) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
