#include "bg3.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "koba/vr/vr.h"
#include "koba/vr/backgrnd.h"

/*---------------------------------------------------------------------------*/
// VR-DISC background 3: four "op_back" quarters in front of the scrolling
// background (koba/vr/backgrnd.c) that open from the centre and cycle colours


#define N_POLYS             4
#define N_COLOR_SETS        14
#define N_PHASES            4

#define QUARTER_W           160
#define QUARTER_H           112
#define QUARTER_U_MAX       (QUARTER_W - 1)
#define QUARTER_V_MAX       (QUARTER_H - 1)

#define OPEN_TIME           177     // timer period
#define FADE_TIME           30
#define BLEND_TIME          150

#define BG3_OTZ             0xe7ff

// The sort depth of a DG_PRIM_SORTONLY packet is the low halfword of its tag
#define SetPackOtz(p, z)    (*(u_short *)&(p)->tag = (z))

typedef struct _Work
{
    GV_ACT    actor;
    DG_PRIM  *prim;             // 0x20
    POLY_FT4  polys[N_POLYS];   // 0x24
    DG_TEX   *tex_l;            // 0xC4
    DG_TEX   *tex_r;            // 0xC8
    int       timer;            // 0xCC
    int       blend;            // 0xD0
    int       color_set;        // 0xD4
    int       rgb[3];           // 0xD8
    int       phase;            // 0xE4
    short     started;          // 0xE8
    short     hidden;           // 0xEA: start invisible ('a' option)
} Work;

/*---------------------------------------------------------------------------*/

static u_char bg3_colors[N_COLOR_SETS][3][4] = {
    {{ 30, 155, 170}, {  0, 110, 200}, { 60,  90, 190}},
    {{ 50, 100,  10}, {  0, 120,  70}, {  0, 100, 120}},
    {{100,  80,  20}, { 80,  90,   0}, { 60, 100,   0}},
    {{  0, 100,  40}, {  0,  80, 100}, { 30,  50,  90}},
    {{ 40, 100,  35}, {  0, 100, 100}, {  0,  80, 120}},
    {{110,  60,   0}, { 90,  90,   0}, { 80, 130,   0}},
    {{ 90, 120,   0}, { 60, 120,  10}, { 10, 120,  80}},
    {{ 70, 100,  80}, { 45, 100, 100}, {  0, 140,  70}},
    {{ 80,  60, 100}, {120,  90,  60}, {120, 140,   0}},
    {{ 34,  40,  13}, {  8,  45,  71}, { 23,  60,  14}},
    {{ 34,  40,  13}, {  8,  45,  71}, { 23,  60,  14}},
    {{ 30, 155, 170}, {  0, 110, 200}, { 60,  90, 190}},
    {{ 50, 100,  10}, {  0, 120,  70}, {  0, 100, 120}},
    {{100,  80,  20}, { 80,  90,   0}, { 60, 100,   0}},
};

static int bg3_phases[N_PHASES] = {0, 1, 2, 1};

/*---------------------------------------------------------------------------*/

static void UpdateColor(Work *work)
{
    int cur, next;
    int i;

    cur = bg3_phases[work->phase];
    next = bg3_phases[(work->phase + 1) % N_PHASES];

    for (i = 0; i < 3; i++)
    {
        work->rgb[i] = (bg3_colors[work->color_set][cur][i] * (BLEND_TIME - work->blend) +
                        bg3_colors[work->color_set][next][i] * work->blend) / BLEND_TIME;

        if (work->timer < FADE_TIME)
        {
            work->rgb[i] = (work->rgb[i] * work->timer) / FADE_TIME;
        }
        else if (work->timer >= (OPEN_TIME - FADE_TIME + 1))
        {
            work->rgb[i] = (work->rgb[i] * (OPEN_TIME - work->timer)) / FADE_TIME;
        }
    }

    if (++work->blend > BLEND_TIME)
    {
        work->blend = 0;
        work->phase = (work->phase + 1) % N_PHASES;
    }
}

static void Update(Work *work)
{
    int       d;
    int       r, g, b;
    int       u1, v2;
    int       u3, v3;
    POLY_FT4 *poly;

    d = work->timer / 2;
    UpdateColor(work);

    r = work->rgb[0];
    g = work->rgb[1];
    b = work->rgb[2];

    poly = &work->polys[0];
    poly->u0 = poly->u2 = work->tex_l->off_x + d;
    poly->v0 = poly->v1 = work->tex_l->off_y + d;
    u1 = work->tex_l->off_x + QUARTER_U_MAX;
    v2 = work->tex_l->off_y + QUARTER_V_MAX;
    setRGB0(poly, r, g, b);
    poly->u1 = poly->u3 = u1;
    poly->v2 = poly->v3 = v2;

    poly = &work->polys[1];
    poly->u0 = poly->u2 = work->tex_l->off_x + d;
    poly->v0 = poly->v1 = QUARTER_H;
    v3 = (QUARTER_H + QUARTER_V_MAX) - d;
    poly->u1 = poly->u3 = work->tex_l->off_x + QUARTER_U_MAX;
    poly->v2 = poly->v3 = v3;
    setRGB0(poly, r, g, b);

    poly = &work->polys[2];
    poly->u0 = poly->u2 = 0;
    poly->v0 = poly->v1 = work->tex_r->off_y + d;
    u3 = QUARTER_U_MAX - d;
    poly->v2 = poly->v3 = work->tex_r->off_y + QUARTER_V_MAX;
    poly->u1 = poly->u3 = u3;
    setRGB0(poly, r, g, b);

    poly = &work->polys[3];
    poly->u0 = poly->u2 = 0;
    poly->v0 = poly->v1 = QUARTER_H;
    poly->u1 = poly->u3 = u3;
    poly->v2 = poly->v3 = v3;
    setRGB0(poly, r, g, b);

    if (work->timer == OPEN_TIME)
    {
        work->timer = 0;
    }
}

static void Act(Work *work)
{
    int       i;
    DG_PRIM  *prim;
    POLY_FT4 *poly;
    POLY_FT4 *pack;

    if (work->color_set >= N_COLOR_SETS)
    {
        work->color_set = N_COLOR_SETS - 1;
    }

    if (VR_Status == VR_STATUS_4 || work->color_set >= 11)
    {
        if (!work->started)
        {
            work->started = TRUE;
            prim = work->prim;
            poly = work->polys;

            for (i = 0; i < N_POLYS; poly++, i++, prim++)
            {
                setSemiTrans(poly, 1);

                if (work->hidden)
                {
                    work->timer = 0;
                    // FIXME: the original steps through DG_PRIMs (there is only one)
                    prim->type &= ~DG_PRIM_INVISIBLE;
                }
            }
        }
    }

    Update(work);

    poly = work->polys;
    pack = work->prim->packs[GV_Clock];
    for (i = 0; i < N_POLYS; i++)
    {
        *pack = *poly;
        SetPackOtz(pack, BG3_OTZ);
        pack++;
        poly++;
    }

    work->timer++;
}

static void Die(Work *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

// not static: called by the relocatable asm of VrBg3GetResources
void VrBg3InitPoly(Work *work, DG_TEX *tex, POLY_FT4 *poly, int u, int v, int w, int h, int x, int y)
{
    int u1, v2;

    setPolyFT4(poly);
    poly->u0 = poly->u2 = tex->off_x + u;
    poly->v0 = poly->v1 = tex->off_y + v;
    u1 = u + tex->off_x + w;
    v2 = v + tex->off_y + h;
    poly->x0 = poly->x2 = x;
    poly->y0 = poly->y1 = y;
    setRGB0(poly, 0, 0, 0);
    poly->x1 = poly->x3 = x + QUARTER_W;
    poly->y2 = poly->y3 = y + QUARTER_H;
    poly->u1 = poly->u3 = u1;
    poly->v2 = poly->v3 = v2;
    poly->clut = tex->clut;
    poly->tpage = tex->tpage;
    setSemiTrans(poly, 0);
}

// GetResources does not byte-match from C (final copy loop), so the original code is kept as RELOCATABLE asm
// (symbolic, from build/symbolize_asm.py) which keeps this object shareable between overlays.
int VrBg3GetResources(Work *work, int where);
#pragma INCLUDE_ASM_RELOC("source/koba/vr/reloc/VrBg3GetResources.s")

#if 0 /* NON_MATCHING best C attempt */
// NON_MATCHING: only the final copy loop differs (the original strength-reduces
// &work->polys[i] into its own register initialised to work->polys, which frees s0
// for the constants; here gcc keeps one more saved register)
static int GetResources(Work *work, int where)
{
    char     *opt;
    DG_PRIM  *prim;
    POLY_FT4 *poly;
    POLY_FT4 *pack;
    int       i;

    GM_CurrentMap = where;

    opt = GCL_GetOption('t');
    if (opt)
    {
        work->color_set = GCL_StrToInt(opt);
    }
    else
    {
        work->color_set = 0;
    }

    if (work->color_set >= N_COLOR_SETS)
    {
        work->color_set = N_COLOR_SETS - 1;
    }

    opt = GCL_GetOption('a');
    if (opt)
    {
        work->hidden = GCL_StrToInt(opt);
    }
    else
    {
        work->hidden = 0;
    }

    prim = DG_MakePrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, N_POLYS, 0, NULL, NULL);
    if (prim)
    {
        DG_QueuePrim(prim);
        DG_GroupPrim(prim, GM_CurrentMap);
    }

    poly = work->polys;
    work->prim = prim;

    work->tex_l = DG_GetTexture(GV_StrCode("op_back_l"));
    work->tex_r = DG_GetTexture(GV_StrCode("op_back_r"));

    VrBg3InitPoly(work, work->tex_l, poly, 0, 0,          QUARTER_U_MAX, QUARTER_V_MAX, -QUARTER_W, -QUARTER_H);
    VrBg3InitPoly(work, work->tex_l, &work->polys[1], 0, QUARTER_H,  QUARTER_U_MAX, QUARTER_V_MAX, -QUARTER_W, 0);
    VrBg3InitPoly(work, work->tex_r, &work->polys[2], 0, 0,          QUARTER_U_MAX, QUARTER_V_MAX, 0,          -QUARTER_H);
    VrBg3InitPoly(work, work->tex_r, &work->polys[3], 0, QUARTER_H,  QUARTER_U_MAX, QUARTER_V_MAX, 0,          0);

    work->timer = 0;

    pack = work->prim->packs[GV_Clock];
    for (i = 0; i < N_POLYS; i++)
    {
        pack[i] = work->polys[i];
        SetPackOtz(&pack[i], BG3_OTZ);

        // FIXME: the original steps through DG_PRIMs (there is only one)
        prim[i].raise -= 1000;
        if (work->hidden)
        {
            prim[i].type |= DG_PRIM_INVISIBLE;
        }
    }

    return 0;
}
#endif

/*---------------------------------------------------------------------------*/

void *NewVrBg3(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_PREV2, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "bg3.c");

        if (VrBg3GetResources(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    NewBackground(name, where, argc, argv);
    return (void *)work;
}
