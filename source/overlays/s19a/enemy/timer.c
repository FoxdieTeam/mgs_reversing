#include <stdio.h>
#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"

/* countdown timer (CHARA_COUNTDOWN): draws "MM:SS" with digits from the "0123" texture */

typedef struct _Work
{
    GV_ACT   actor;
    DG_PRIM *prim;      // 0x20
    int      visible;   // 0x24
    int      field_28;  // 0x28
    int      field_2C;  // 0x2C
    int      field_30;  // 0x30
    int      field_34;  // 0x34
    int      field_38;  // 0x38
    int      field_3C;  // 0x3C
    int      field_40;  // 0x40
    int      u;         // 0x44
    int      w;         // 0x48
    int      v;         // 0x4C
    int      h;         // 0x50
    int      field_54;  // 0x54
    int      field_58;  // 0x58
    int      time;      // 0x5C
    int      proc_sec;  // 0x60: called every second with the time left
    int      proc_end;  // 0x64: called when the time is up
} Work;

#define EXEC_LEVEL GV_ACTOR_USER

#define TPAGE_TP(t)  (((t) >> 7) & 3)
#define TPAGE_ABR(t) (((t) >> 5) & 3)
#define TPAGE_X(t)   (((t) << 6) & 0x7C0)
#define TPAGE_Y(t)   ((((t) << 4) & 0x100) + (short)(((t) >> 2) & 0x200))

#define DIGIT_Y0 -100
#define DIGIT_Y1 -82

/* one digit of the "0123" texture (initialized to show 0) */
#define INIT_DIGIT(poly, tex, x0, x1)                                   \
{                                                                       \
    int u0, u1, v0, v1, h;                                              \
                                                                        \
    setPolyFT4(poly);                                                   \
    u0 = tex->off_x;                                                    \
    u1 = u0 + (tex->w + 1) / 10;                                        \
    v0 = tex->off_y;                                                    \
    h = tex->h + 1;                                                     \
    v1 = v0 + h;                                                        \
    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);                       \
    printf("u0:%d u1:%d v0:%d v1:%d\n", u0, u1, v0, v1);                \
    poly->tpage = tex->tpage;                                           \
    poly->clut = tex->clut;                                             \
    printf("tpage: (%d,%d,%d,%d)\n", TPAGE_TP((short)poly->tpage), TPAGE_ABR((short)poly->tpage), \
           TPAGE_X((short)poly->tpage), TPAGE_Y((short)poly->tpage));                             \
    setRGB0(poly, 255, 208, 208);                                       \
    setXY4(poly, x0, DIGIT_Y0, x1, DIGIT_Y0, x0, DIGIT_Y1, x1, DIGIT_Y1); \
    SetSemiTrans(poly, 1);                                              \
}

/* the colon between the minutes and the seconds */
#define INIT_DOT(poly, tex, x0, x1)                                     \
{                                                                       \
    int u0, u1, v0, v1;                                                 \
                                                                        \
    u0 = tex->off_x;                                                    \
    u1 = u0 + tex->w;                                                   \
    v0 = tex->off_y;                                                    \
    v1 = v0 + tex->h;                                                   \
    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);                       \
    poly->tpage = tex->tpage;                                           \
    poly->clut = tex->clut;                                             \
    printf("u0:%d u1:%d v0:%d v1:%d\n", u0, u1, v0, v1);                \
    printf("tpage: (%d,%d,%d,%d)\n", TPAGE_TP((short)poly->tpage), TPAGE_ABR((short)poly->tpage), \
           TPAGE_X((short)poly->tpage), TPAGE_Y((short)poly->tpage));                             \
    setRGB0(poly, 255, 208, 208);                                       \
    setXY4(poly, x0, DIGIT_Y0, x1, DIGIT_Y0, x0, DIGIT_Y1, x1, DIGIT_Y1); \
    SetSemiTrans(poly, 1);                                              \
}

/* shows digit (0-9) in poly */
void Timer_800C4320(Work *work, POLY_FT4 *poly, int digit, int n_digits)
{
    int u0, u1;
    int u, v, h;

    u0 = (work->w * digit) / n_digits;
    u1 = (work->w * (digit + 1)) / n_digits;

    u = work->u;
    v = work->v;
    h = work->h;

    poly->v0 = v;
    poly->v1 = v;
    v += h;
    poly->v2 = v;
    poly->v3 = v;

    poly->u0 = u + u0;
    poly->u2 = u + u0;
    poly->u1 = u + u1;
    poly->u3 = u + u1;
}

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800C43E4.s")
void s19a_800C43E4(Work *work); /* Act */

#if 0 /* NON_MATCHING: register allocation (time, work and the final loop pointer) */
static void Act(Work *work)
{
    POLY_FT4 *poly0, *poly1;
    int       time;
    int       sec, min;
    int       sec1, sec10, min10;
    int       i;

    time = work->time;
    poly0 = work->prim->packs[0];
    poly1 = work->prim->packs[1];
    sec = time / 30;

    if (time == sec * 30 && work->proc_sec >= 0)
    {
        GCL_ARGS args;
        long     data;

        args.argc = 1;
        data = time;
        args.argv = &data;
        GCL_ExecProc(work->proc_sec, &args);
    }

    if (sec == 0 && work->proc_end >= 0)
    {
        GCL_ExecProc(work->proc_end, NULL);
        work->proc_end = -1;
    }

    min = sec / 60;
    sec1 = sec % 60;
    sec10 = sec1 / 10;
    sec1 = sec1 % 10;
    min10 = min / 10;
    min = min % 10;

    Timer_800C4320(work, poly0++, sec1, 10);
    Timer_800C4320(work, poly1, sec1, 10);
    poly1++;
    Timer_800C4320(work, poly0, sec10, 10);
    Timer_800C4320(work, poly1, sec10, 10);
    poly0 += 2;
    poly1 += 2;
    Timer_800C4320(work, poly0, min, 10);
    Timer_800C4320(work, poly1, min, 10);
    poly1++;
    Timer_800C4320(work, poly0 + 1, min10, 10);
    Timer_800C4320(work, poly1, min10, 10);

    work->time--;

    poly0 = work->prim->packs[GV_Clock];
    for (i = 0; i < 5; i++)
    {
        *(short *)poly0 = work->visible;
        poly0++;
    }
}
#endif

void TimerDie(Work *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

static int GetResources(Work *work)
{
    char     *opt;
    DG_PRIM  *prim;
    DG_TEX   *tex;
    POLY_FT4 *poly0, *poly1;

    opt = GCL_GetOption('t');
    if (opt)
    {
        work->time = GCL_StrToInt(opt) + 29;
    }
    else
    {
        work->time = 180 * 30 + 29;
    }

    if (GCL_GetOption('e'))
    {
        work->proc_sec = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->proc_sec = -1;
    }

    if (GCL_GetOption('z'))
    {
        work->proc_end = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->proc_end = -1;
    }

    prim = GM_MakePrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 5, NULL, NULL);
    work->prim = prim;

    poly0 = prim->packs[0];
    poly1 = prim->packs[1];

    tex = DG_GetTexture(GV_StrCode("0123"));

    INIT_DIGIT(poly0, tex, 134, 150);
    INIT_DIGIT(poly1, tex, 134, 150);
    poly0++;
    poly1++;
    INIT_DIGIT(poly0, tex, 118, 134);
    INIT_DIGIT(poly1, tex, 118, 134);
    poly0++;
    poly1++;

    tex = DG_GetTexture(GV_StrCode("dot2"));
    printf("offset [%d]\n", tex->off_x);
    setPolyFT4(poly0);
    printf("dot init [%d]\n", GV_StrCode("dot"));
    INIT_DOT(poly0, tex, 102, 118);
    setPolyFT4(poly1);
    INIT_DOT(poly1, tex, 102, 118);
    poly0++;
    poly1++;

    tex = DG_GetTexture(GV_StrCode("0123"));
    work->u = tex->off_x;
    work->w = tex->w + 1;
    work->v = tex->off_y;
    work->h = tex->h + 1;

    INIT_DIGIT(poly0, tex, 86, 102);
    INIT_DIGIT(poly1, tex, 86, 102);
    poly0++;
    poly1++;
    INIT_DIGIT(poly0, tex, 70, 86);
    INIT_DIGIT(poly1, tex, 70, 86);

    work->visible = 1;
    work->field_28 = 0;
    work->field_2C = 0;
    work->field_30 = 0;
    work->field_34 = 0;
    work->field_38 = 0;
    work->field_3C = 0;
    work->field_40 = 0;
    work->field_54 = 0;
    return 0;
}

void *NewTimer(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, s19a_800C43E4, TimerDie, "timer.c");
        if (GetResources(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
