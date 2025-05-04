#include "sepia.h"

#include "common.h"
#include "takabe/goggle.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"

typedef struct SepiaPrims
{
    DR_TPAGE tpage[2];
    TILE     tile[2];
} SepiaPrims;

typedef struct _SepiaWork
{
    GV_ACT      actor;
    SepiaPrims *prims;
} SepiaWork;

extern u_long DG_PaletteBuffer_800B3818[256];

RECT rect_800C3258 = {768, 226, 256, 2};
RECT rect_800C3260 = {768, 196, 256, 2};
RECT rect_800C3268 = {768, 226, 256, 2};
RECT rect_800C3270 = {768, 196, 256, 2};

#define EXEC_LEVEL GV_ACTOR_AFTER2

u_short s16b_800C4C60(u_short color)
{
    int r, g, b, a;

    if ((color & 0x7FFF) == 0)
    {
        return color;
    }

    r = color & 0x1F;
    g = (color & 0x3E0) >> 5;
    b = (color & 0x7C00) >> 10;

    r = r + g;
    r = r + b;
    r = (r * 85) >> 9;

    a = color & 0x8000;
    color = r;

    r = color | color << 5 | color << 10 | a;

    if (r == 0)
    {
        r = 0x8000;
    }

    return r;
}

void s16b_800C4CD0(void)
{
    int      i, j;
    u_short *iter;

    rect_800C3258.y = 226;
    rect_800C3260.y = 196;

    for (i = 15; i > 0; i--)
    {
        DrawSync(0);
        StoreImage2(&rect_800C3260, DG_PaletteBuffer_800B3818);
        DrawSync(0);

        iter = (short *)DG_PaletteBuffer_800B3818;
        for (j = 512; j > 0; j--)
        {
            *iter++ = s16b_800C4C60(*iter);
        }

        LoadImage2(&rect_800C3258, DG_PaletteBuffer_800B3818);

        rect_800C3260.y += 2;
        rect_800C3258.y += 2;
    }
}

void SepiaAct_800C4DC4(SepiaWork *work)
{
    char *ot;

    ot = DG_ChanlOTag(0);
    addPrim(ot, &work->prims->tile[GV_Clock]);
    addPrim(ot, &work->prims->tpage[GV_Clock]);
}

void SepiaDie_800C4E70(SepiaWork *work)
{
    DG_ResetExtPaletteMakeFunc();

    if (work->prims)
    {
        GV_DelayedFree(work->prims);
    }
}

int s16b_800C4EAC(SepiaWork *work, short r, short g, short b)
{
    SepiaPrims *prims;

    DG_SetExtPaletteMakeFunc(s16b_800C4CD0, s16b_800C4C60);

    work->prims = (SepiaPrims *)GV_Malloc(sizeof(SepiaPrims));
    prims = work->prims;

    setDrawTPage(&prims->tpage[0], 0, 1, getTPage(0, 1, 0, 0));
    setDrawTPage(&prims->tpage[1], 0, 1, getTPage(0, 1, 0, 0));

    setTile(&prims->tile[0]);
    setSemiTrans(&prims->tile[0], 1);

    prims->tile[0].x0 = -128;
    prims->tile[0].y0 = -15;
    prims->tile[0].w = 256;
    prims->tile[0].h = 30;

    prims->tile[1] = prims->tile[0];

    prims->tile[0].r0 = r;
    prims->tile[0].g0 = g;
    prims->tile[0].b0 = b;

    prims->tile[1].r0 = r;
    prims->tile[1].g0 = g;
    prims->tile[1].b0 = b;

    return 0;
}

void *NewSepia_800C4F9C(int r, int g, int b)
{
    SepiaWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(SepiaWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, SepiaAct_800C4DC4, SepiaDie_800C4E70, "sepia.c");

        if (s16b_800C4EAC(work, r, g, b) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}

void *NewSepia2_800C504C(void)
{
    return NewSepia_800C4F9C(64, 32, 0);
}

u_short s16b_800C5074(u_short arg0)
{
    int     r, g, b, a;
    u_short color;

    if (arg0 == 0)
    {
        return 0;
    }

    r = arg0 & 0x1F;
    g = (arg0 & 0x3E0) >> 5;
    b = (arg0 & 0x7C00) >> 10;

    r = (r + g + b) / 3;

    a = arg0 & 0x8000;
    color = r | (r << 5) | (r << 10) | a;

    if (color == 0)
    {
        color = 0x8000;
    }

    return color;
}

void s16b_800C50EC(void)
{
    int      i, j;
    u_short *iter;

    rect_800C3268.y = 226;
    rect_800C3270.y = 196;

    for (i = 15; i > 0; i--)
    {
        DrawSync(0);
        StoreImage2(&rect_800C3270, DG_PaletteBuffer_800B3818);
        DrawSync(0);

        iter = (short *)DG_PaletteBuffer_800B3818;
        for (j = 512; j > 0; j--)
        {
            *iter++ = s16b_800C5074(*iter);
        }

        LoadImage2(&rect_800C3268, DG_PaletteBuffer_800B3818);

        rect_800C3270.y += 2;
        rect_800C3268.y += 2;
    }
}

void SepiaAct_800C51E0(SepiaWork *work)
{
}

int SepiaGetResources_800C51E8(SepiaWork *work)
{
    DG_SetExtPaletteMakeFunc(s16b_800C50EC, s16b_800C5074);
    return 0;
}

void *NewSepia_800C5214(void)
{
    SepiaWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(SepiaWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, SepiaAct_800C51E0, SepiaDie_800C4E70, "sepia.c");

        if (SepiaGetResources_800C51E8(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
