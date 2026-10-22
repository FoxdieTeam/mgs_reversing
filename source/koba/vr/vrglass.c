// VR-DISC only: vrglass.c
// A breakable glass pane.  The pane is a textured quad (two halves, upper and lower) of which one of three
// vertical strips of the texture is shown more and more broken after each hit.  Three hits (or a strong one)
// shatter it into pieces (NewSplashVr).  Two thin hazard segments in front of and behind the pane stop the
// player until it is broken.

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "takabe/thing.h"
#include "koba/vr/splashvr.h"

/*---------------------------------------------------------------------------*/

#define GLASS_HITS          3       // hits that break the pane
#define GLASS_PIECES        0x40
#define GLASS_PIECE_SIZE    0x80
#define MIN_HAZARD_SIZE     150     // minimum size of the box that is rotated into the pane's frame

#define SE_GLASS_CRACK      0x3E
#define SE_GLASS_BREAK      0x3F

typedef struct _Work
{
    GV_ACT    actor;
    MATRIX    world;
    DG_PRIM  *prim;
    DG_TEX   *tex;
    SVECTOR   vertices[8];      // 0x48 two quads: upper half, lower half
    TARGET   *target;
    SVECTOR   pos;              // 0x8C
    SVECTOR   rot;              // 0x94
    SVECTOR   size;             // 0x9C half extents (x: width, y: height)
    short     f_a4;             // 0xA4 options 'f' and 'b' (kept, not used by the code)
    short     f_a6;             // 0xA6
    int       n_pieces;         // 0xA8 option 'n'
    int       map;              // 0xAC
    int       hits_left;        // 0xB0
    short     queued;           // 0xB4 hazard segments are in the map
    HZD_HDL  *hzd;              // 0xB8
    HZD_SEG   segs[2];          // 0xBC
    int       splash_arg;       // 0xDC passed to NewSplashVr
    short     tex_name;         // 0xE0
} Work;

/*---------------------------------------------------------------------------*/

// Shows the strip number "index" (0 - 2) of the glass texture on both halves of the quad
#if 0 /* NON_MATCHING: register allocation of the temporaries differs (t0-t4 / v1 / a3 swapped) */
static void InitPoly(POLY_FT4 *poly, DG_TEX *tex, int index)
{
    int          width;
    int          height;
    unsigned int uheight;
    int          u, v;

    // upper half
    setPolyFT4(poly);
    setSemiTrans(poly, 1);
    setRGB0(poly, 128, 128, 128);

    width = tex->w + 1;
    u = tex->off_x;
    poly->u0 = poly->u2 = u + (width * index) / 3;
    poly->u1 = poly->u3 = u + (width * (index + 1)) / 3 - 1;

    height = tex->h + 1;
    v = tex->off_y;
    poly->v0 = poly->v1 = v;
    poly->v2 = poly->v3 = v + (height >> 1) - 1;

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;

    poly++;

    // lower half
    setPolyFT4(poly);
    setSemiTrans(poly, 1);
    setRGB0(poly, 128, 128, 128);

    width = tex->w + 1;
    u = tex->off_x;
    poly->u0 = poly->u2 = u + (width * index) / 3;
    poly->u1 = poly->u3 = u + (width * (index + 1)) / 3 - 1;

    // FIXME: unsigned height steers the shift (srl instead of sra) like the original
    uheight = tex->h + 1;
    v = tex->off_y;
    poly->v0 = poly->v1 = v + (uheight >> 1);
    poly->v2 = poly->v3 = v + uheight - 1;

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}
#else
void VrGlassInitPoly(POLY_FT4 *poly, DG_TEX *tex, int index);
#pragma INCLUDE_ASM_RELOC("source/koba/vr/reloc/VrGlassInitPoly.s")
#define InitPoly VrGlassInitPoly
#endif

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    TARGET *target;
    int     hit;
    int     strip;

    target = work->target;
    GM_CurrentMap = work->map;

    if (target->damaged & TARGET_POWER)
    {
        target->damaged &= ~TARGET_POWER;

        hit = 0;
        switch (target->a_mode)
        {
        case 1:
            hit = 1;
            work->hits_left--;
            break;

        case 2:
            work->hits_left = 0;
            hit = 1;
            break;
        }

        if (hit)
        {
            if (work->hits_left <= 0)
            {
                GM_SeSetMode(&work->pos, SE_GLASS_BREAK, GM_SEMODE_BOMB);
                NewSplashVr(&work->world, &work->size, GLASS_PIECES, (short)work->splash_arg, work->tex_name, GLASS_PIECE_SIZE);
                THING_Hzd_800C4874(2, work->segs, 0, NULL);
                GV_DestroyActor(&work->actor);
                return;
            }

            GM_SeSetMode(&work->pos, SE_GLASS_CRACK, GM_SEMODE_BOMB);
            strip = GLASS_HITS - work->hits_left;
            InitPoly(work->prim->packs[0], work->tex, strip);
            InitPoly(work->prim->packs[1], work->tex, strip);
        }
    }

    GM_MoveTarget(target, &work->pos);
    GM_PushTarget(target);
    target->damaged &= ~TARGET_PUSH;
}

static void Die(Work *work)
{
    DG_PRIM *prim;

    if (work->queued)
    {
        HZD_DequeueDynamicSegment(work->hzd, &work->segs[0]);
        HZD_DequeueDynamicSegment(work->hzd, &work->segs[1]);
    }

    GM_FreeTarget(work->target);

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

void VrGlassInitTarget(Work *work, SVECTOR *size)
{
    TARGET *target;

    target = GM_AllocTarget();
    work->target = target;
    GM_SetTarget(target, 0x14, 0, size);
    GM_SetPowerTarget(target, 1, -1, 0, 0, &DG_ZeroVector);
}

#if 0 /* NON_MATCHING: register allocation / stack layout of the temporaries differs */
static int GetResources(Work *work, int name, int where)
{
    SVECTOR   size;
    SVECTOR  *psize;
    SVECTOR   seg_a;
    SVECTOR   seg_b;
    SVECTOR  *v;
    DG_PRIM  *prim;
    DG_TEX   *tex;
    int       sx, sy;
    short     x, y, z;
    int       thickness;
    int       seg_flag;

    GM_CurrentMap = where;

    THING_Gcl_GetSVector('p', &work->pos);
    THING_Gcl_GetSVector('d', &work->rot);
    THING_Gcl_GetSVector('s', &size);
    work->size = size;

    work->f_a4 = -THING_Gcl_GetIntDefault('f', work->pos.vy);
    work->f_a6 = -THING_Gcl_GetIntDefault('b', -work->f_a4);
    work->n_pieces = THING_Gcl_GetIntDefault('n', 0x40);
    work->splash_arg = -1;

    thickness = THING_Gcl_GetIntDefault('w', 125);
    seg_flag = THING_Gcl_GetIntDefault('z', 180) & ~4;
    work->tex_name = THING_Gcl_GetShortDefault('t', GV_StrCode("glass") & 0xFFFF);

    tex = DG_GetTexture(work->tex_name);
    work->tex = tex;
    if (tex == NULL)
    {
        return -1;
    }

    prim = DG_MakePrim(0x12, 2, 0, work->vertices, NULL);
    if (prim != NULL)
    {
        DG_QueuePrim(prim);
        prim->group_id = GM_CurrentMap;
    }

    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    RotMatrix(&work->rot, &work->world);
    work->world.t[0] = work->pos.vx;
    work->world.t[1] = work->pos.vy;
    work->world.t[2] = work->pos.vz;
    DG_SetPos(&work->world);
    DG_PutPrim(prim);

    InitPoly(prim->packs[0], tex, 0);
    InitPoly(prim->packs[1], tex, 0);

    sx = work->size.vx;
    sy = work->size.vy;
    v = work->vertices;

    v[0].vx = -sx;
    v[0].vy = sy;
    v[0].vz = 0;
    v[1].vx = sx;
    v[1].vy = sy;
    v[1].vz = 0;
    v[2].vx = -sx;
    v[2].vy = 0;
    v[2].vz = 0;
    v[3].vx = sx;
    v[3].vy = 0;
    v[3].vz = 0;

    v[4].vx = -sx;
    v[4].vy = 0;
    v[4].vz = 0;
    v[5].vx = sx;
    v[5].vy = 0;
    v[5].vz = 0;
    v[6].vx = -sx;
    v[6].vy = -sy;
    v[6].vz = 0;
    v[7].vx = sx;
    v[7].vy = -sy;
    v[7].vz = 0;

    psize = &size;
    DG_RotVector(&work->size, psize, 1);
    x = size.vx;
    if (x < 0)
    {
        x = -x;
    }
    y = psize->vy;
    if (y < 0)
    {
        y = -y;
    }
    size.vx = x;
    z = psize->vz;
    psize->vy = y;
    if (z < 0)
    {
        z = -z;
    }
    psize->vz = z;
    if (x < MIN_HAZARD_SIZE)
    {
        size.vx = MIN_HAZARD_SIZE;
    }
    if (y < MIN_HAZARD_SIZE)
    {
        psize->vy = MIN_HAZARD_SIZE;
    }
    if (z < MIN_HAZARD_SIZE)
    {
        psize->vz = MIN_HAZARD_SIZE;
    }
    VrGlassInitTarget(work, &size);

    seg_a = work->vertices[1];
    seg_b = work->vertices[6];
    seg_a.vz += thickness;
    seg_b.vz += thickness;
    THING_Hzd_800C45C4(&work->segs[0], &work->world, &seg_a, &seg_b);
    THING_Hzd_800C49AC(&work->segs[0]);

    seg_a = work->vertices[1];
    seg_b = work->vertices[6];
    seg_a.vz -= thickness;
    seg_b.vz -= thickness;
    THING_Hzd_800C45C4(&work->segs[1], &work->world, &seg_a, &seg_b);
    THING_Hzd_800C49AC(&work->segs[1]);

    work->hzd = GM_GetMap(where)->hzd;
    HZD_QueueDynamicSegment2(work->hzd, &work->segs[0], seg_flag);
    HZD_QueueDynamicSegment2(work->hzd, &work->segs[1], seg_flag);
    work->queued = 1;
    return 0;
}

#else
int VrGlassGetResources(Work *work, int name, int where);
#pragma INCLUDE_ASM_RELOC("source/koba/vr/reloc/VrGlassGetResources.s")
#define GetResources VrGlassGetResources
#endif

void *NewVrGlass(int name, int where)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "vrglass.c");
        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->hits_left = GLASS_HITS;
        work->map = where;
    }

    return (void *)work;
}
