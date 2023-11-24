#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"

typedef struct _WsurfaceWork
{
    GV_ACT   actor;
    int      map;
    int      name;
    DG_PRIM *prim;
    DG_TEX  *tex;
    SVECTOR *ptr;
    DVECTOR *ptr2;
    DVECTOR *ptr3;
    DVECTOR  f3C[16];
    DVECTOR  f7C[16];
    DVECTOR  fBC[16];
    short    fFC;
    short    fFE;
    short    f100;
    short    f102;
    short    f104;
    char     pad2[0x2];
} WsurfaceWork;

extern int GV_Clock_800AB920;
extern int GM_CurrentMap_800AB9B0;

int            THING_Msg_CheckMessage(unsigned short name, int hash_count, unsigned short *hashes);
void           THING_Gcl_GetSVector(char param, SVECTOR *vec);
void           THING_Gcl_GetSVectorDefault(char param, short x, short y, short z, SVECTOR *vec);
unsigned short THING_Gcl_GetShortDefault(char param, unsigned short def);

#define EXEC_LEVEL 5

void Wsurface_800DAC14(POLY_GT4 *poly, DG_TEX *tex, WsurfaceWork *work)
{
    int i, j;
    int x, y, w, h;

    for (i = 0; i < work->fFE; i++)
    {
        for (j = 0; j < work->fFC; j++)
        {
            setPolyGT4(poly);
            setSemiTrans(poly, 1);

            x = tex->field_8_offx;
            w = tex->field_A_width + 1;

            poly->u0 = poly->u2 = x + ((w * j) / work->fFC);
            poly->u1 = poly->u3 = x + ((w * (j + 1)) / work->fFC) - 1;

            y = tex->field_9_offy;
            h = tex->field_B_height + 1;

            poly->v0 = poly->v1 = y + ((h * i) / work->fFE);
            poly->v2 = poly->v3 = y + ((h * (i + 1)) / work->fFE) - 1;

            poly->tpage = tex->field_4_tPage;
            poly->clut = tex->field_6_clut;

            LSTORE((LLOAD(&poly->r0) & 0xFF000000) | 0x808080, &poly->r0);
            LSTORE((LLOAD(&poly->r1) & 0xFF000000) | 0x808080, &poly->r1);
            LSTORE((LLOAD(&poly->r2) & 0xFF000000) | 0x808080, &poly->r2);
            LSTORE((LLOAD(&poly->r3) & 0xFF000000) | 0x808080, &poly->r3);

            poly++;
        }
    }
}

void Wsurface_800DAE3C(POLY_GT4 *packs, int shade, WsurfaceWork *work)
{
    int       fFC, inc;
    int       fFE;
    int       color;
    POLY_GT4 *iter;
    int       i;

    color = shade | (shade << 8) | (shade << 16);

    iter = packs;
    fFC = work->fFC;
    for (i = 0; i < fFC; i++)
    {
        LSTORE((LLOAD(&iter->r0) & 0xFF000000) | color, &iter->r0);
        LSTORE((LLOAD(&iter->r1) & 0xFF000000) | color, &iter->r1);
        iter++;
    }

    inc = work->fFC * (work->fFE - 1);

    fFC = work->fFC;
    iter = packs + inc;
    for (i = 0; i < fFC; i++)
    {
        LSTORE((LLOAD(&iter->r2) & 0xFF000000) | color, &iter->r2);
        LSTORE((LLOAD(&iter->r3) & 0xFF000000) | color, &iter->r3);
        iter++;
    }

    fFE = work->fFE;

    iter = packs;
    inc = work->fFC;
    for (i = 0; i < fFE; i++)
    {
        LSTORE((LLOAD(&iter->r0) & 0xFF000000) | color, &iter->r0);
        LSTORE((LLOAD(&iter->r2) & 0xFF000000) | color, &iter->r2);
        iter += inc;
    }

    fFC = work->fFC - 1;
    fFE = work->fFE;

    inc = fFC;
    iter = packs + inc;

    inc = work->fFC;
    for (i = 0; i < fFE; i++)
    {
        LSTORE((LLOAD(&iter->r1) & 0xFF000000) | color, &iter->r1);
        LSTORE((LLOAD(&iter->r3) & 0xFF000000) | color, &iter->r3);
        iter += inc;
    }
}

void Wsurface_800DAFE8(POLY_GT4 *poly, DVECTOR *in, WsurfaceWork *work)
{
    int      i, j;
    DVECTOR *vec0;
    DVECTOR *vec1;
    DVECTOR *vec2;
    DVECTOR *vec3;

    for (i = 0; i < work->fFE; i++)
    {
        vec0 = in + i * (work->fFC + 1);
        vec1 = vec0 + 1;
        vec2 = vec0 + work->fFC + 1;
        vec3 = vec0 + work->fFC + 2;

        for (j = 0; j < work->fFC; j++)
        {
            poly->u0 = vec0->vx;
            poly->v0 = vec0->vy;
            poly->u1 = vec1->vx;
            poly->v1 = vec1->vy;
            poly->u2 = vec2->vx;
            poly->v2 = vec2->vy;
            poly->u3 = vec3->vx;
            poly->v3 = vec3->vy;

            vec0++;
            vec1++;
            vec2++;
            vec3++;
            poly++;
        }
    }
}

void Wsurface_800DB0C4(DVECTOR *vec, DG_TEX *tex, WsurfaceWork *work)
{
    int i, j;
    int xoff, yoff;

    for (i = 0; i <= work->fFE; i++)
    {
        yoff = i & 7;

        if (yoff >= 5)
        {
            yoff = 8 - yoff;
        }

        for (j = 0; j <= work->fFC; j++)
        {
            xoff = j & 7;

            if (xoff >= 5)
            {
                xoff = 8 - xoff;
            }

            vec->vx = tex->field_8_offx + (xoff * 5 + 22 + GV_RandS_800170BC(8));
            vec->vy = tex->field_9_offy + (yoff * 5 + 22 + GV_RandS_800170BC(8));
            vec++;
        }
    }
}

void Wsurface_800DB1E4(DVECTOR *in, DVECTOR *out, WsurfaceWork *work)
{
    DVECTOR *f3C;
    DVECTOR *f7C;
    DVECTOR *fBC;
    int      i, j;
    int      count;

    f3C = work->f3C;
    f7C = work->f7C;
    fBC = work->fBC;

    for (i = 0; i < 16; i++)
    {
        f3C->vx += f7C->vx;
        f3C->vy += f7C->vy;
        f7C->vx += fBC->vx;
        f7C->vy += fBC->vy;

        if (f7C->vx > 0)
        {
            fBC->vx--;
        }
        else if (f7C->vx < 0)
        {
            fBC->vx++;
        }

        if (f7C->vy > 0)
        {
            fBC->vy--;
        }
        else if (f7C->vy < 0)
        {
            fBC->vy++;
        }

        f3C++;
        f7C++;
        fBC++;
    }

    count = work->f102 & 0xFFF0;
    for (i = 0; i < count; i += 16)
    {
        f3C = work->f3C;

        for (j = 0; j < 16; j++)
        {
            out->vx = in->vx + (f3C->vx >> 5);
            out->vy = in->vy + (f3C->vy >> 5);

            in++;
            out++;
            f3C++;
        }
    }

    f3C = work->f3C;

    count = work->f102 & 0xF;
    for (i = 0; i < count; i++)
    {
        out->vx = in->vx + (f3C->vx >> 5);
        out->vy = in->vy + (f3C->vy >> 5);

        in++;
        out++;
        f3C++;
    }
}

void Wsurface_800DB3B8(WsurfaceWork *work, SVECTOR *arg1, int x, int z)
{
    SVECTOR  sp0;
    SVECTOR  sp8;
    SVECTOR  sp10;
    int      i, j;
    SVECTOR *vec;

    sp0.vx = arg1->vx - ((x * work->fFC) >> 1);
    sp0.vz = arg1->vz - ((z * work->fFE) >> 1);
    sp0.vy = arg1->vy;

    sp8.vx = x;
    sp8.vz = z;
    sp8.vy = 0;

    vec = work->ptr;

    for (i = 0; i < work->fFE; i++)
    {
        sp10 = sp0;

        for (j = 0; j < work->fFC; j++)
        {
            *vec = sp10;
            vec++;

            *vec = sp10;
            vec->vx += x;
            vec++;

            *vec = sp10;
            vec->vz += z;
            vec++;

            *vec = sp10;
            vec->vx += x;
            vec->vz += z;
            vec++;

            sp10.vx += x;
        }

        sp0.vz += z;
    }
}

void WsurfaceAct_800DB564(WsurfaceWork *work)
{
    unsigned short hashes[2];

    GM_CurrentMap_800AB9B0 = work->map;

    hashes[0] = GV_StrCode_80016CCC("実行");
    hashes[1] = GV_StrCode_80016CCC("停止");

    switch (THING_Msg_CheckMessage(work->name, 2, hashes))
    {
    case 0:
        work->f104 = 1;
        break;

    case 1:
        work->f104 = 0;
        break;
    }

    if (work->f104 == 1)
    {
        Wsurface_800DB1E4(work->ptr2, work->ptr3, work);
        Wsurface_800DAFE8(&work->prim->field_40_pBuffers[GV_Clock_800AB920]->poly_gt4, work->ptr3, work);
    }
}

void WsurfaceDie_800DB630(WsurfaceWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    GV_Free_80016230(work->ptr);
}

int WsurfaceGetResources_800DB684(WsurfaceWork *work, int name, int map)
{
    SVECTOR  sp18;
    SVECTOR  sp20;
    SVECTOR  sp28;
    SVECTOR  sp30;
    SVECTOR  sp38;
    int      texid;
    DG_TEX  *tex, *tex2;
    int      svec_count, svecs_size;
    int      dvec_count, dvecs_size;
    SVECTOR *ptr;
    DG_PRIM *prim;
    int      i;

    GM_CurrentMap_800AB9B0 = map;

    THING_Gcl_GetSVector('p', &sp18);

    texid = THING_Gcl_GetShortDefault('t', GV_StrCode_80016CCC("lsight"));
    tex2 = DG_GetTexture_8001D830(texid);
    work->tex = tex = tex2;

    THING_Gcl_GetSVectorDefault('n', 20, 20, 0, &sp28);
    THING_Gcl_GetSVectorDefault('s', 500, 500, 0, &sp20);

    if (GCL_GetOption_80020968('b'))
    {
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &sp38);
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &sp30);

        sp18.vx = (sp30.vx + sp38.vx) / 2;
        sp18.vy = (sp30.vy + sp38.vy) / 2;
        sp18.vz = (sp30.vz + sp38.vz) / 2;

        sp20.vx = (sp30.vx - sp38.vx) / sp28.vx;
        sp20.vy = (sp30.vz - sp38.vz) / sp28.vy;
    }

    work->fFC = sp28.vx;
    work->fFE = sp28.vy;
    work->f100 = work->fFC * work->fFE;
    work->f102 = (work->fFC + 1) * (work->fFE + 1);

    svec_count = work->f100 * 4;
    svecs_size = svec_count * sizeof(SVECTOR);
    dvec_count = work->f102;
    dvecs_size = dvec_count * sizeof(DVECTOR);

    // ptr is:
    // struct {
    //     SVECTOR[svec_count];
    //     DVECTOR[dvec_count];
    //     DVECTOR[dvec_count];
    // }
    ptr = GV_Malloc_8001620C(svecs_size + dvecs_size * 2);
    if (ptr == NULL)
    {
        return -1;
    }
    work->ptr = ptr;
    work->ptr2 = (DVECTOR *)((char *)ptr + svecs_size);
    work->ptr3 = (DVECTOR *)((char *)ptr + svecs_size + dvecs_size);

    prim = DG_GetPrim(0x14, work->f100, 0, work->ptr, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }
    if (tex == NULL)
    {
        return -1;
    }

    Wsurface_800DAC14(&work->prim->field_40_pBuffers[0]->poly_gt4, tex, work);
    Wsurface_800DAC14(&work->prim->field_40_pBuffers[1]->poly_gt4, tex, work);

    Wsurface_800DAE3C(&work->prim->field_40_pBuffers[0]->poly_gt4, 0, work);
    Wsurface_800DAE3C(&work->prim->field_40_pBuffers[1]->poly_gt4, 0, work);

    Wsurface_800DB3B8(work, &sp18, sp20.vx, sp20.vy);

    Wsurface_800DB0C4(work->ptr2, tex, work);

    for (i = 0; i < 16; i++)
    {
        work->f3C[i].vx = 0;
        work->f3C[i].vy = 0;
        work->f7C[i].vx = 0;
        work->f7C[i].vy = 0;
        work->fBC[i].vx = GV_RandS_800170BC(8);
        work->fBC[i].vy = GV_RandS_800170BC(8);
    }

    return 0;
}

GV_ACT *NewWsurface_800DB9BC(int name, int where)
{
    WsurfaceWork *work;

    work = (WsurfaceWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(WsurfaceWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)WsurfaceAct_800DB564,
                                  (TActorFunction)WsurfaceDie_800DB630, "wsurface.c");

        if (WsurfaceGetResources_800DB684(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        work->map = where;
        work->name = name;
        work->f104 = 1;
    }

    return &work->actor;
}
