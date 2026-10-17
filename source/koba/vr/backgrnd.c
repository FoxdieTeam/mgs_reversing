#include "backgrnd.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "koba/vr/vr.h"

/*---------------------------------------------------------------------------*/
// VR-DISC scrolling background (the "op_back" panels behind the VR stages)

#define N_PANELS        3
#define PANEL_W         160
#define PANEL_H         224
#define PANEL_Y         -112
#define PANEL_OTZ       0xE800

#define FADE_TIME       60
#define N_COLORS        14

// A DR_TPAGE and a SPRT in one packet (sorted by DG_PRIM_SORTONLY:
// the low halfword of the tag holds the sort depth)
typedef struct _BG_PACK
{
    union {
        u_long  tag;
        u_short otz;
    } hdr;              // 0x00
    u_long  tpage;      // 0x04
    u_char  r0, g0, b0, code;   // 0x08
    short   x0, y0;     // 0x0C
    u_char  u0, v0;     // 0x10
    u_short clut;       // 0x12
    short   w, h;       // 0x14
} BG_PACK;

typedef struct _Work
{
    GV_ACT   actor;
    DG_PRIM *prim;              // 0x20
    BG_PACK  packs[N_PANELS];   // 0x24
    int      timer;             // 0x6C
    int      side;              // 0x70: next panel texture (0: left, 1: right)
    int      next;              // 0x74: next panel to wrap around
    char     pad78[0x8];        // 0x78
    int      color;             // 0x80
    char     pad84[0x14];       // 0x84
    int      fade;              // 0x98
} Work;

/*---------------------------------------------------------------------------*/

static CVECTOR backgrnd_colors[N_COLORS] = {
    {   0, 110, 200, 0 },
    {   0, 120,  70, 0 },
    {  80,  90,   0, 0 },
    {   0,  80, 100, 0 },
    {   0, 100, 100, 0 },
    {  90,  90,   0, 0 },
    {  60, 120,  10, 0 },
    {  45, 100, 100, 0 },
    { 120,  90,  60, 0 },
    {  12,  79,  60, 0 },
    {  12,  79,  60, 0 },
    {   0, 110, 200, 0 },
    {   0, 120,  70, 0 },
    {  80,  90,   0, 0 },
};

/*---------------------------------------------------------------------------*/

// SetPanel does not byte-match from C (7 words differ: scheduling of the w/h constants), so the original code is
// kept as RELOCATABLE asm (symbolic, from build/symbolize_asm.py) which keeps this object shareable between overlays.
void BackgrndSetPanel(Work *work, int name, BG_PACK *pack, int x, int y);
#pragma INCLUDE_ASM_RELOC("source/koba/vr/reloc/BackgrndSetPanel.s")

#if 0 /* NON_MATCHING best C attempt */
// NON_MATCHING: 7 words differ (scheduling of the w/h constants and v0)
static void SetPanel(Work *work, int name, BG_PACK *pack, int x, int y)
{
    DG_TEX *tex;

    tex = DG_GetTexture(name);

    pack->tpage = _get_mode(0, 1, tex->tpage);
    pack->hdr.tag = 5 << 24;
    pack->code = 0x64;  // SPRT
    pack->u0 = tex->off_x;
    pack->y0 = y;
    pack->v0 = tex->off_y;
    pack->x0 = x;
    pack->w = PANEL_W;
    pack->h = PANEL_H;
    pack->clut = tex->clut;
}
#endif

static void Scroll(Work *work)
{
    int      i;
    int      id;
    BG_PACK *pack;

    pack = work->packs;
    for (i = 0; i < N_PANELS; i++, pack++)
    {
        pack->x0--;
    }

    if (work->timer == PANEL_W)
    {
        pack = &work->packs[work->next];
        if (work->side)
        {
            id = GV_StrCode("op_back_r");
        }
        else
        {
            id = GV_StrCode("op_back_l");
        }

        BackgrndSetPanel(work, id, pack, PANEL_W, PANEL_Y);

        work->timer = 0;
        work->side = (work->side + 1) & 1;
        work->next = (work->next + 1) % N_PANELS;
    }
}

static void Act(Work *work)
{
    BG_PACK *src;
    BG_PACK *dst;
    DG_PRIM *prim;
    int      i;

    Scroll(work);

    src = work->packs;
    dst = work->prim->packs[GV_Clock];
    for (i = 0; i < N_PANELS; dst++, i++, src++)
    {
        *dst = *src;
        dst->hdr.otz = PANEL_OTZ;
    }

    work->timer++;

    if (VR_Status == VR_STATUS_4 || work->color == 9 || work->color > 10)
    {
        if (work->fade != 0)
        {
            if (work->fade == FADE_TIME)
            {
                // FIXME: treats the prim as an array of DG_PRIMs (original bug?)
                prim = work->prim;
                for (i = 0; i < N_PANELS; i++, prim++)
                {
                    DG_VisiblePrim(prim);
                }
            }

            work->fade--;

            src = work->packs;
            for (i = 0; i < N_PANELS; i++, src++)
            {
                src->r0 = (backgrnd_colors[work->color].r * (FADE_TIME - work->fade)) / FADE_TIME;
                src->g0 = (backgrnd_colors[work->color].g * (FADE_TIME - work->fade)) / FADE_TIME;
                src->b0 = (backgrnd_colors[work->color].b * (FADE_TIME - work->fade)) / FADE_TIME;
            }
        }
    }
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, int map)
{
    DG_PRIM *prim;
    char    *opt;
    int      i;
    BG_PACK *pack;

    GM_CurrentMap = map;

    DG_SetFreePrimParam(sizeof(BG_PACK), 2, 12, 0);
    prim = DG_MakePrim(DG_PRIM_SORTONLY | DG_PRIM_INVISIBLE | DG_PRIM_FREE, N_PANELS, 0, NULL, NULL);
    if (prim)
    {
        DG_QueuePrim(prim);
        DG_GroupPrim(prim, GM_CurrentMap);
    }
    work->prim = prim;

    // FIXME: treats the prim as an array of DG_PRIMs (original bug?)
    for (i = 0; i < N_PANELS; i++, prim++)
    {
        prim->raise -= 2000;
    }

    opt = GCL_GetOption('t');
    if (opt)
    {
        work->color = GCL_StrToInt(opt);
        if (work->color >= N_COLORS)
        {
            work->color = N_COLORS - 1;
        }
    }
    else
    {
        work->color = 0;
    }

    work->fade = FADE_TIME;

    pack = &work->packs[0];
    BackgrndSetPanel(work, GV_StrCode("op_back_l"), pack, -PANEL_W, PANEL_Y);
    setRGB0(pack, 0, 0, 0);

    pack = &work->packs[1];
    BackgrndSetPanel(work, GV_StrCode("op_back_r"), pack, 0, PANEL_Y);
    setRGB0(pack, 0, 0, 0);

    pack = &work->packs[2];
    BackgrndSetPanel(work, GV_StrCode("op_back_l"), pack, PANEL_W, PANEL_Y);
    setRGB0(pack, 0, 0, 0);

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewBackground(int name, int where, int argc, char **argv)
{
    Work *work;

    VR_Status = VR_STATUS_0;

    work = GV_NewActor(GV_ACTOR_PREV2, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "backgrnd.c");

        if (GetResources(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
