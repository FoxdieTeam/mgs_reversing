#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Okajima/stngrnd.h"

typedef struct _Inverlt2Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim[8];
    RECT     rect[8];
    SVECTOR  vec[8];
    int      fC4;
    int      fC8;
    int      fCC;
    int      fD0;
    int      fD4;
    int      fD8;
    int      fDC;
    SVECTOR  fE0;
    int      fE8;
} Inverlt2Work;

extern int     GM_CurrentMap_800AB9B0;
extern DG_CHNL DG_Chanls_800B1800[3];

#define EXEC_LEVEL 5

void Inverlt2Act_800D1580(Inverlt2Work *work);
void Inverlt2Die_800D1858(Inverlt2Work *work);
void Inverlt2InitRects_800D18D4(Inverlt2Work *work, int scale);

GV_ACT * NewInverlt2_800D0FF4(SVECTOR *arg0, int arg1, int arg2, int arg3, int r, int g, int b, int arg7, int arg8)
{
    Inverlt2Work *work;
    DG_TEX       *tex;
    int           i;
    int           x, y, w, h;
    int           x2, y2, w2, h2;

    work = (Inverlt2Work *)GV_NewActor(EXEC_LEVEL, sizeof(Inverlt2Work));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, (TActorFunction)Inverlt2Act_800D1580, (TActorFunction)Inverlt2Die_800D1858, "inverlt2.c");

    work->fC4 = r;
    work->fC8 = g;
    work->fCC = b;

    work->fD0 = arg1;
    work->fD4 = arg1;
    work->fD8 = arg2;
    work->fDC = arg3;

    work->map = GM_CurrentMap_800AB9B0;

    work->fE0 = *arg0;

    if (work->fC4 < 5)
    {
        work->fC4 = 5;
    }

    if (work->fC8 < 5)
    {
        work->fC8 = 5;
    }

    if (work->fCC < 5)
    {
        work->fCC = 5;
    }

    if (work->fD8 <= 0)
    {
        work->fD8 = 1;
    }

    work->rect[0].w = arg7 / 6;
    work->rect[0].h = arg7 / 6;
    work->rect[1].w = arg7 / 3;
    work->rect[1].h = arg7 / 3;
    work->rect[2].w = arg7 / 2;
    work->rect[2].h = arg7 / 2;
    work->rect[3].w = (arg7 * 4) / 6;
    work->rect[3].h = (arg7 * 4) / 6;
    work->rect[4].w = (arg7 * 5) / 6;
    work->rect[4].h = (arg7 * 5) / 6;
    work->rect[5].w = arg7;
    work->rect[5].h = arg7;
    work->rect[6].w = arg8 / 2;
    work->rect[6].h = arg8 / 2;
    work->rect[7].w = arg8;
    work->rect[7].h = arg8;

    work->vec[0].vz = 320;
    work->vec[1].vz = 320;
    work->vec[2].vz = 320;
    work->vec[3].vz = 320;
    work->vec[4].vz = 320;
    work->vec[5].vz = 320;
    work->vec[6].vz = 320;
    work->vec[7].vz = 320;

    Inverlt2InitRects_800D18D4(work, 100);

    tex = DG_GetTexture(GV_StrCode("refrection6"));

    for (i = 0; i < 8; i++)
    {
        work->prim[i] =  DG_GetPrim(DG_PRIM_OFFSET | DG_PRIM_SCREEN | DG_PRIM_POLY_FT4, 1, 0, &work->vec[i], &work->rect[i]);

        work->prim[i]->field_2E_k500 = 320;

#define POLY ((POLY_FT4 *)work->prim[i]->packs[0])
        setPolyFT4(&POLY[0]);
        setPolyFT4(&POLY[1]);
        setRGB0(&POLY[0], work->fC4, work->fC8, work->fCC);
        setRGB0(&POLY[1], work->fC4 - 5, work->fC8 - 5, work->fCC - 5);

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;
        setUVWH(&POLY[0], x, y, w, h);
        POLY[0].tpage = tex->tpage;
        POLY[0].clut = tex->clut;

        x2 = tex->off_x;
        w2 = tex->w;
        y2 = tex->off_y;
        h2 = tex->h;
        setUVWH(&POLY[1], x2, y2, w2, h2);
        POLY[1].tpage = tex->tpage;
        POLY[1].clut = tex->clut;

        setSemiTrans(&POLY[0], 1);
        setSemiTrans(&POLY[1], 1);
#undef POLY
    }

    return &work->actor;
}

// Can't match below function without this macro
#define EXIT_IF(cond)                           \
do                                              \
{                                               \
    if (cond)                                   \
    {                                           \
        GV_DestroyActor(&work->actor);          \
        return;                                 \
    }                                           \
}                                               \
while (0)

void Inverlt2Act_800D1580(Inverlt2Work *work)
{
    int temp_s3;
    int temp_lo;
    int temp_a1;
    int r, g, b;
    int i;

    EXIT_IF(work->fD0 <= 0);

    temp_s3 = work->fD4 - work->fD0;
    temp_lo = ((work->fD8 - temp_s3) * 100) / work->fD8;

    GM_CurrentMap_800AB9B0 = work->map;

    if ((temp_lo == 0) && (work->fE8 == 0))
    {
        work->fE8 = 1;
        AN_Stn_G_Sonic_80074CA4(&work->fE0);
        AN_Stn_G_Center_80074D28(&work->fE0);
        sub_800790E8();
    }
    else if (work->fE8 == 1)
    {
        work->fE8 = 2;
        sub_8007913C();
    }

    Inverlt2InitRects_800D18D4(work, temp_lo);

    if (work->fDC < temp_s3)
    {
        temp_a1 = work->fD4 - work->fDC;
        if (temp_a1 <= 0)
        {
            temp_lo = 0;
        }
        else
        {
            temp_lo = ((work->fD4 - temp_s3) * 100) / temp_a1;
        }

        r = (work->fC4 * temp_lo) / 100;
        g = (work->fC8 * temp_lo) / 100;
        b = (work->fCC * temp_lo) / 100;

        if (r < 5)
        {
            r = 5;
        }

        if (g < 5)
        {
            g = 5;
        }

        if (b < 5)
        {
            b = 5;
        }

        for (i = 0; i < 8; i++)
        {
            ((POLY_FT4 *)work->prim[i]->packs[0])[0].r0 = r;
            ((POLY_FT4 *)work->prim[i]->packs[0])[0].g0 = g;
            ((POLY_FT4 *)work->prim[i]->packs[0])[0].b0 = b;

            ((POLY_FT4 *)work->prim[i]->packs[0])[1].r0 = r - 5;
            ((POLY_FT4 *)work->prim[i]->packs[0])[1].g0 = g - 5;
            ((POLY_FT4 *)work->prim[i]->packs[0])[1].b0 = b - 5;
        }
    }

    work->fD0--;
}

void Inverlt2Die_800D1858(Inverlt2Work *work)
{
    int      i;
    DG_PRIM *prim;

    if (work->fE8 == 1)
    {
        sub_8007913C();
    }

    for (i = 0; i < 8; i++)
    {
        prim = work->prim[i];
        if (prim != NULL)
        {
            DG_DequeuePrim(prim);
            DG_FreePrim(prim);
        }
    }
}

void Inverlt2InitRects_800D18D4(Inverlt2Work *work, int scale)
{
    SVECTOR sxy;
    SVECTOR sp18;
    long    p;
    long    flag;
    short   screen;


    SetRotMatrix(&DG_Chanl(0)->field_10_eye_inv);
    SetTransMatrix(&DG_Chanl(0)->field_10_eye_inv);
    RotTransPers(&work->fE0, (long *)&sxy, &p, &flag);

    if (sxy.vy == 0)
    {
        sp18.vx = 0;
    }
    else
    {
        screen = abs((sxy.vx * 112) / sxy.vy);
        sp18.vx = (screen * scale) / 100;
    }

    if (sxy.vx == 0)
    {
        sp18.vy = 0;
    }
    else
    {
        screen = abs((sxy.vy * 160) / sxy.vx);
        sp18.vy = (screen * scale) / 100;
    }

    if (sxy.vx <= 0)
    {
        sp18.vx *= -1;
    }

    if (sxy.vy <= 0)
    {
        sp18.vy *= -1;
    }

    work->rect[0].x = (work->rect[0].w / 2) - sxy.vx + (sp18.vx / 6);
    work->rect[0].y = (work->rect[0].h / 2) - sxy.vy + (sp18.vy / 6);

    work->rect[1].x = (work->rect[1].w / 2) - sxy.vx + (sp18.vx / 3);
    work->rect[1].y = (work->rect[1].h / 2) - sxy.vy + (sp18.vy / 3);

    work->rect[2].x = (work->rect[2].w / 2) - sxy.vx + (sp18.vx / 2);
    work->rect[2].y = (work->rect[2].h / 2) - sxy.vy + (sp18.vy / 2);

    work->rect[3].x = (work->rect[3].w / 2) - sxy.vx + ((sp18.vx * 4) / 6);
    work->rect[3].y = (work->rect[3].h / 2) - sxy.vy + ((sp18.vy * 4) / 6);

    work->rect[4].x = (work->rect[4].w / 2) - sxy.vx + ((sp18.vx * 5) / 6);
    work->rect[4].y = (work->rect[4].h / 2) - sxy.vy + ((sp18.vy * 5) / 6);

    work->rect[5].x = (work->rect[5].w / 2) - sxy.vx + sp18.vx;
    work->rect[5].y = (work->rect[5].h / 2) - sxy.vy + sp18.vy;

    sp18.vx >>= 1;
    sp18.vy >>= 1;

    work->rect[6].x = (work->rect[6].w / 2) - sxy.vx + (-sp18.vx / 2);
    work->rect[6].y = (work->rect[6].h / 2) - sxy.vy + (-sp18.vy / 2);

    work->rect[7].x = (work->rect[7].w / 2) - sxy.vx - sp18.vx;
    work->rect[7].y = (work->rect[7].h / 2) - sxy.vy - sp18.vy;
}
