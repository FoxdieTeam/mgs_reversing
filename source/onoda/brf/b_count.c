#include "game/game.h"

typedef struct _Work
{
    GV_ACT   actor;
    DG_PRIM *prim;
    char     z[15];
    int      unk34;
    int      unk38;
    int      unk3C;
    int      unk40;
    int      unk44;
    int      unk48;
    int      unk4C;
    int      unk50;
    int      off_x;
    int      width;
    int      off_y;
    int      height;
    char     pad64[4];
    POLY_FT4 poly[15];
    GV_PAD  *pad;
    int      unk2C4;
    int      unk2C8;
    int      unk2CC;
    int      unk2D0;
    int      unk2D4;
    int      unk2D8;
    int      unk2DC;
    int      unk2E0;
    int      unk2E4;
    int      unk2E8;
} Work;

static void brf_800DFE7C(Work *work)
{
    int press;

    press = work->pad->press;
    if (work->unk34 > 50 && work->unk2CC == 0 && (press & PAD_CROSS))
    {
        work->unk2C4 = 0;
        work->unk2CC = 1;
        work->unk2E8 = 0;
        work->z[11] = 0;
        work->z[12] = 0;
        work->z[13] = 0;
        work->z[14] = 0;
    }
}

static void InitTex(Work *work, POLY_FT4 *poly, int num, int div)
{
    int x, y, w, h;

    x = work->off_x;
    y = work->off_y;
    w = work->width;
    h = work->height;

    poly->u0 = x + w * num / div;
    poly->v0 = y;
    poly->u1 = x + w * (num + 1) / div;
    poly->v1 = y;
    poly->u2 = x + w * num / div;
    poly->v2 = y + h;
    poly->u3 = x + w * (num + 1) / div;
    poly->v3 = y + h;
}

static void brf_800DFF94(Work *work)
{
    POLY_FT4 *pack, *poly;
    int i, shade;

    pack = work->prim->packs[GV_Clock];
    poly = work->poly;

    for (i = 0; i < 15; i++)
    {
        *pack = *poly;

        if (work->unk2CC != 0 && work->unk2E8 >= 64)
        {
            if (work->unk2E8 < 96)
            {
                shade = 128 - (work->unk2E8 - 63) * 4;
                setRGB0(pack, shade, shade, shade);
            }
            else
            {
                setRGB0(pack, 0, 0, 0);
            }
        }

        SSTOREL(work->z[i] * 256, pack);
        pack++;
        poly++;
    }
}

static void brf_800E0084(Work *work, POLY_FT4 *poly)
{
    poly->y0++;
    poly->y1++;
    poly->y2++;
    poly->y3++;

    if (poly->y0 >= 128)
    {
        poly->y0 = -154;
        poly->y1 = -154;
        poly->y2 = -104;
        poly->y3 = -104;
    }
}

static void brf_800E00E0(Work *work, POLY_FT4 *poly)
{
    if (work->unk34 & 1)
    {
        poly->y0 += 2;
        poly->y1 += 2;
        poly->y2 += 2;
        poly->y3 += 2;
    }
    else
    {
        poly->y0++;
        poly->y1++;
        poly->y2++;
        poly->y3++;
    }

    if (poly->y0 >= 128)
    {
        poly->y0 = -128;
        poly->y1 = -128;
        poly->y2 = -127;
        poly->y3 = -127;
    }
}

static void brf_800E0180(Work *work, int index)
{
    POLY_FT4 *poly;
    int c1, c2;

    poly = work->poly;

    if (work->unk34 >= 50)
    {
        switch (work->unk2DC)
        {
        case 0:
            setRGB0(&poly[index], 255, 208, 208);

            if (work->unk2E0 >= 40)
            {
                work->unk2DC = 1;
                work->unk2E0 = 0;
            }
            break;
        case 1:
            c1 = ~(work->unk2E0 * 6);
            c2 = 208 - work->unk2E0 * 6;
            setRGB0(&poly[index], c1, c2, c2);

            if (work->unk2E0 >= 32)
            {
                work->unk2DC = 2;
                work->unk2E0 = 0;
            }
            break;
        case 2:
            c1 = work->unk2E0 * 6 + 63;
            c2 = work->unk2E0 * 6 + 16;
            setRGB0(&poly[index], c1, c2, c2);

            if (work->unk2E0 >= 32)
            {
                work->unk2DC = 0;
                work->unk2E0 = 0;
            }
            break;
        }

        work->unk2E0++;
    }
}

static void Act(Work *work)
{
    POLY_FT4 *p;
    int mod, div;

    if (++work->unk34 == 50)
    {
        work->unk2C4 = 1;

        if (work->unk2D0 != 0)
        {
            work->z[11] = 6;
            work->z[12] = 6;
        }

        if (work->unk2D4 != 0)
        {
            work->z[13] = 1;
            work->unk2E0 = 0;
            work->unk2DC = 0;
        }

        if (work->unk2D8 != 0)
        {
            work->z[14] = 1;
            work->unk2E0 = 0;
            work->unk2DC = 0;
        }
    }

    if (work->unk2CC == 0 && work->unk34 >= work->unk2C8)
    {
        work->unk2C4 = 0;
        work->unk2CC = 1;
        work->unk2E8 = 0;
        work->z[11] = 0;
        work->z[12] = 0;
        work->z[13] = 0;
        work->z[14] = 0;
    }

    brf_800DFE7C(work);
    p = work->poly;

    if (work->unk2D4 != 0)
    {
        brf_800E0180(work, 13);
    }

    if (work->unk2D8 != 0)
    {
        brf_800E0180(work, 14);
    }

    if (work->unk2C4 != 0)
    {
        brf_800E0084(work, &work->poly[11]);
        brf_800E00E0(work, &work->poly[12]);
    }

    if (work->unk2CC != 0)
    {
        div = work->unk38 / 10;
        mod = work->unk38 % 10;
        work->unk2E8++;
    }
    else
    {
        div = work->unk38 / 10;
        mod = work->unk38 % 10;
        work->unk38++;
    }

    InitTex(work, p, mod, 10);
    p++;

    InitTex(work, p, div, 10);
    p += 2;

    if (work->unk38 == 30)
    {
        work->unk3C++;
        work->unk38 = 2;

        InitTex(work, p, work->unk3C, 10);

        if (work->unk3C == 10)
        {
            work->unk38 = 0;
            work->unk3C = 0;

            InitTex(work, p, 0, 10);
            p++;

            work->unk40++;
            InitTex(work, p, work->unk40, 10);

            if (work->unk40 == 6)
            {
                work->unk40 = 0;

                InitTex(work, p, 0, 10);
                p += 2;

                work->unk44++;
                InitTex(work, p, work->unk44, 10);

                if (work->unk44 == 10)
                {
                    work->unk44 = 0;

                    InitTex(work, p, 0, 10);
                    p++;

                    work->unk48++;
                    InitTex(work, p, work->unk48, 10);

                    if (work->unk48 == 6)
                    {
                        work->unk48 = 0;

                        InitTex(work, p, 0, 10);
                        p += 2;

                        work->unk4C++;
                        InitTex(work, p, work->unk4C, 10);

                        if (work->unk4C == 10)
                        {
                            work->unk4C = 0;

                            InitTex(work, p, 0, 10);
                            p++;

                            work->unk50++;
                            InitTex(work, p, work->unk50, 10);
                        }
                    }
                }
            }
        }
    }

    brf_800DFF94(work);
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static void Init_Res(int name, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe, int mode)
{
    DG_TEX *tex;

    tex = DG_GetTexture(name);

    setPolyFT4(poly);
    setRGB0(poly, 255, 208, 208);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);

    if (mode == 0)
    {
        int x, y, w, h;

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;

        poly->u0 = x;
        poly->v0 = y;
        poly->u1 = x + w + 1;
        poly->v1 = y;
        poly->u2 = x;
        poly->v2 = y + h + 1;
        poly->u3 = x + w + 1;
        poly->v3 = y + h + 1;

        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
    }
    else if (mode == 1)
    {
        int x, y, w, h;

        x = tex->off_x;
        w = (tex->w + 1) / 10;
        y = tex->off_y;
        h = tex->h + 1;

        poly->u0 = x;
        poly->v0 = y;
        poly->u1 = x + w;
        poly->v1 = y;
        poly->u2 = x;
        poly->v2 = y + h;
        poly->u3 = x + w;
        poly->v3 = y + h;

        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
    }
    else if (mode == 2)
    {
        int x, y, w, h;

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;

        poly->u0 = x;
        poly->v0 = y;
        poly->u1 = x + w + 1;
        poly->v1 = y;
        poly->u2 = x;
        poly->v2 = y + h;
        poly->u3 = x + w + 1;
        poly->v3 = y + h;

        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
    }
}

static int GetResources(Work *work, int map, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8)
{
    POLY_FT4 *p;
    DG_TEX *tex;

    GM_CurrentMap = map;
    work->prim = GM_MakePrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 15, NULL, NULL);

    p = work->poly;

    Init_Res(GV_StrCode("0123"), p, -0x1E, -0x64, -0x12, -0x57, 1, 1);
    work->z[0] = 1;
    p++;

    Init_Res(GV_StrCode("0123"), p, -0x2A, -0x64, -0x1E, -0x57, 1, 1);
    work->z[1] = 1;
    p++;

    Init_Res(GV_StrCode("dot"), p, -0x36, -0x64, -0x2A, -0x57, 1, 0);
    work->z[2] = 1;
    p++;

    Init_Res(GV_StrCode("0123"), p, -0x42, -0x64, -0x36, -0x57, 1, 1);
    work->z[3] = 1;
    p++;

    Init_Res(GV_StrCode("0123"), p, -0x4E, -0x64, -0x42, -0x57, 1, 1);
    work->z[4] = 1;
    p++;

    Init_Res(GV_StrCode("dot"), p, -0x5A, -0x64, -0x4E, -0x57, 1, 0);
    work->z[5] = 1;
    p++;

    Init_Res(GV_StrCode("0123"), p, -0x66, -0x64, -0x5A, -0x57, 1, 1);
    work->z[6] = 1;
    p++;

    Init_Res(GV_StrCode("0123"), p, -0x72, -0x64, -0x66, -0x57, 1, 1);
    work->z[7] = 1;
    p++;

    Init_Res(GV_StrCode("dot"), p, -0x7E, -0x64, -0x72, -0x57, 1, 0);
    work->z[8] = 1;
    p++;

    Init_Res(GV_StrCode("0123"), p, -0x8A, -0x64, -0x7E, -0x57, 1, 1);
    work->z[9] = 1;
    p++;

    Init_Res(GV_StrCode("0123"), p, -0x96, -0x64, -0x8A, -0x57, 1, 1);
    work->z[10] = 1;
    p++;

    tex = DG_GetTexture(GV_StrCode("0123"));
    work->off_x = tex->off_x;
    work->width = tex->w + 1;
    work->off_y = tex->off_y;
    work->height = tex->h + 1;

    p = work->poly + 11;

    Init_Res(GV_StrCode("b_line1"), p, -0xA0, -0x68, 0xA0, -0x36, 1, 2);
    setRGB0(p, 15, 15, 15);
    work->z[11] = 0;
    p++;

    Init_Res(GV_StrCode("b_line1"), p, -0xA0, -0x68, 0xA0, -0x67, 1, 2);
    setRGB0(p, 15, 15, 15);
    work->z[12] = 0;
    p++;

    Init_Res(GV_StrCode("c_free"), p, 0x24, -0x50, 0x78, -0x45, 1, 0);
    setRGB0(p, 255, 208, 208);
    work->z[13] = 0;
    p++;

    Init_Res(GV_StrCode("c_change"), p, 0x14, -0x41, 0x78, -0x36, 1, 0);
    setRGB0(p, 255, 208, 208);
    work->z[14] = 0;
    p++;

    work->unk34 = 0;
    work->unk38 = 1;
    work->unk40 = arg4 / 10;
    work->unk3C = arg4 % 10;
    work->unk48 = arg3 / 10;
    work->unk44 = arg3 % 10;
    work->unk50 = arg2 / 10;
    work->unk4C = arg2 % 10;

    InitTex(work, &work->poly[0], 0, 10);
    InitTex(work, &work->poly[1], 0, 10);
    InitTex(work, &work->poly[3], work->unk3C, 10);
    InitTex(work, &work->poly[4], work->unk40, 10);
    InitTex(work, &work->poly[6], work->unk44, 10);
    InitTex(work, &work->poly[7], work->unk48, 10);
    InitTex(work, &work->poly[9], work->unk4C, 10);
    InitTex(work, &work->poly[10], work->unk50, 10);

    work->pad = &GV_PadData[2];
    work->unk2C4 = 0;
    work->unk2C8 = arg5;
    work->unk2CC = 0;
    work->unk2E8 = 0;
    work->unk2D0 = arg6;
    work->unk2D4 = arg7;
    work->unk2D8 = arg8;
    work->unk2E4 = 0;
    return 0;
}

void *NewBriefingCount(int map, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "b_count.c");
        if (GetResources(work, map, arg1, arg2, arg3, arg4, arg5, arg6, arg7) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}
