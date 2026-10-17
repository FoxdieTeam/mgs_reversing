#include "snake_e1.h"
#include "lens_fl2.h"
#include "sn_in_ef.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "takabe/fadeio.h"

/*---------------------------------------------------------------------------*/
// VR: Snake appearing in a column of rising light particles (CHARA_VR_SNAKE)

#define EXEC_LEVEL      GV_ACTOR_USER

#define PARTICLE_COUNT  32
#define PARTICLE_SIZE   80      // half size of a particle sprite (verts[].pad)
#define DEFAULT_TIME    30
#define DEFAULT_COLOR   255
#define START_HEIGHT    5000

// particle state (rots[].pad)
enum
{
    PARTICLE_WAIT,              // waiting for a random delay
    PARTICLE_RISE,              // moving, fading out
    PARTICLE_RESET              // restart from the top
};

typedef struct _Work
{
    GV_ACT    actor;
    int       map;                          // 0x020
    MATRIX    world;                        // 0x024
    SVECTOR   flare_pos;                    // 0x044
    SVECTOR   flare_speed;                  // 0x04C
    int       field_54;                     // 0x054
    DG_PRIM  *prim;                         // 0x058
    SVECTOR   verts[PARTICLE_COUNT];        // 0x05C (pad: sprite size)
    SVECTOR   pos;                          // 0x15C
    SVECTOR   color;                        // 0x164
    char      pad_16C[8];                   // 0x16C
    DG_TEX   *tex;                          // 0x174
    int       field_178;                    // 0x178
    int       height;                       // 0x17C
    int       done;                         // 0x180 (read by the sn_in_ef actors)
    int       time;                         // 0x184
    int       time_max;                     // 0x188
    void     *fade;                         // 0x18C
    SVECTOR   rots[PARTICLE_COUNT];         // 0x190 (pad: PARTICLE_* state)
    SVECTOR   offsets[PARTICLE_COUNT];      // 0x290 (vz: height, pad: delay/speed)
} Work;

/*---------------------------------------------------------------------------*/

static int GetSvecs(char *opt, SVECTOR *svec)
{
    int   count;
    char *result;

    count = 0;

    while ((result = GCL_NextStr()) != NULL)
    {
        GCL_StrToSV(result, (short *)svec);
        svec++;
        count++;
    }

    return count;
}

// screen position of a vertex as left in the scratchpad by the prim channel
typedef struct _SCRN_POS
{
    short x, y;
    long  z;
} SCRN_POS;

static void *PrimHandler(DG_PRIM *prim, POLY_FT4 *packs, int n_packs)
{
    SVECTOR  *verts;
    SCRN_POS *in;
    int      screen;
    int      size;
    int      zdiv;
    int      x, y;

    size = 0;
    verts = prim->pos;
    in = (SCRN_POS *)getScratchAddr(0);
    screen = DG_Chanls[1].screen;

    while (--n_packs >= 0)
    {
        zdiv = in->z;

        if (zdiv != 0)
        {
            size = (verts->pad * screen) / zdiv;
        }

        SSTOREL(zdiv, &packs->tag);

        x = in->x;
        y = in->y;

        packs->x0 = x - size;
        packs->y0 = y - size;
        packs->x1 = x + size;
        packs->y1 = y - size;
        packs->x2 = x - size;
        packs->y2 = y + size;
        packs->x3 = x + size;
        packs->y3 = y + size;

        in++;
        packs++;
        verts++;
    }

    return packs;
}

static void Act(Work *work)
{
    SVECTOR   color;
    SVECTOR  *vert;
    SVECTOR  *rot;
    SVECTOR  *offset;
    POLY_FT4 *poly;
    int       i;

    GM_SetCurrentMap(work->map);

    vert = work->verts;
    rot = work->rots;
    offset = work->offsets;
    poly = work->prim->packs[GV_Clock];

    // FIXME: pointers instead of indexing steer gcc's induction variables to the original
    for (i = 0; i < PARTICLE_COUNT; i++, vert++, rot++, offset++, poly++)
    {
        switch (rot->pad)
        {
        case PARTICLE_WAIT:
            if (offset->pad > 0)
            {
                offset->pad--;
            }
            else
            {
                setRGB0(poly, work->color.vx, work->color.vy, work->color.vz);
                offset->pad = GV_RandS(64);
                rot->pad++;
            }
            break;

        case PARTICLE_RISE:
            rot->vx += offset->pad;
            rot->vy += offset->pad;
            rot->vz += offset->pad;
            offset->vz = offset->vz * 7 / 8 - 5;

            DG_SetPos2(&work->pos, rot);
            DG_PutVector(offset, vert, 1);

            if (offset->vz < 0)
            {
                rot->pad++;
            }

            color.vx = (work->color.vx * offset->vz) / work->height;
            color.vy = (work->color.vy * offset->vz) / work->height;
            color.vz = (work->color.vz * offset->vz) / work->height;
            setRGB0(poly, color.vx, color.vy, color.vz);
            break;

        case PARTICLE_RESET:
            offset->vx = 0;
            offset->vy = 0;
            offset->vz = work->height + 100;
            offset->pad = 0;

            rot->vx = -GV_RandU(1024);
            rot->vy = GV_RandU(4096);
            rot->vz = 0;
            rot->pad = PARTICLE_WAIT;

            DG_SetPos2(&work->pos, rot);
            DG_PutVector(offset, vert, 1);
            rot->pad = PARTICLE_WAIT;   // (sic) set twice
            break;
        }
    }

    if (work->time == work->time_max)
    {
        NewSnakeInEffect(&work->world, work->height, &work->done, work->map, &work->color);
        work->fade = NewFadeInOut(FADEIO_MODE_TOWHITE, work->time_max * 4);
    }

    if (work->time == (work->time_max * 2) / 3)
    {
        NewSnakeInEffect(&work->world, (work->height * 2) / 3, &work->done, work->map, &work->color);
    }

    if (work->time == work->time_max / 2)
    {
        NewSnakeInEffect(&work->world, work->height / 2, &work->done, work->map, &work->color);
    }

    if (work->time < 0)
    {
        work->done = 1;

        if (work->fade)
        {
            GV_DestroyOtherActor(work->fade);
        }

        NewFadeInOut(FADEIO_MODE_FROMWHITE, 15);
        GV_DestroyActor(&work->actor);
    }

    work->time--;
}

static void SetPackets(POLY_FT4 *poly, int count, DG_TEX *tex)
{
    while (--count >= 0)
    {
        setPolyFT4(poly);
        setSemiTrans(poly, 1);
        setRGB0(poly, 0, 0, 0);
        DG_SetPacketTexture4(poly, tex);
        poly->tpage |= 0x20;
        poly++;
    }
}

static int GetResources(Work *work, int name, int where)
{
    char    *opt;
    DG_PRIM *prim;
    DG_TEX  *tex;
    SVECTOR *vert;
    SVECTOR *rot;
    SVECTOR *offset;
    int      i;
    int      size;

    work->map = where;
    work->height = START_HEIGHT;
    work->world = GM_PlayerBody->objs->objs[0].world;

    work->pos.vx = work->world.t[0];
    work->pos.vy = work->world.t[1];
    work->pos.vz = work->world.t[2];

    opt = GCL_GetOption('t');
    if (opt)
    {
        work->time = GCL_StrToInt(opt);
    }
    else
    {
        work->time = DEFAULT_TIME;
    }

    work->time_max = work->time;

    opt = GCL_GetOption('c');
    if (opt)
    {
        GetSvecs(opt, &work->color);
    }
    else
    {
        work->color.vx = DEFAULT_COLOR;
        work->color.vy = DEFAULT_COLOR;
        work->color.vz = DEFAULT_COLOR;
    }

    // FIXME: chained assignments (prim, tex) and the size variable steer register allocation
    work->prim = prim = GM_MakePrim(DG_PRIM_FREEPACKS | DG_PRIM_POLY_FT4, PARTICLE_COUNT, work->verts, NULL);
    if (prim == NULL)
    {
        return -1;
    }

    prim->callback = PrimHandler;
    prim->n_prims = PARTICLE_COUNT;
    prim->userdata = work->rots;
    prim->raise = 0;

    size = PARTICLE_SIZE;
    for (i = PARTICLE_COUNT - 1; i >= 0; i--)
    {
        work->verts[i].pad = size;
    }

    work->tex = tex = DG_GetTexture(GV_StrCode("rcm_l"));
    if (tex == NULL)
    {
        return -1;
    }

    SetPackets(prim->packs[0], PARTICLE_COUNT, tex);
    SetPackets(prim->packs[1], PARTICLE_COUNT, tex);

    vert = work->verts;
    rot = work->rots;
    offset = work->offsets;

    for (i = 0; i < PARTICLE_COUNT; i++, vert++, rot++, offset++)
    {
        offset->vx = 0;
        offset->vy = 0;
        offset->vz = work->height + 100;
        offset->pad = GV_RandU(32);

        rot->vx = -GV_RandU(1024);
        rot->vy = GV_RandU(4096);
        rot->vz = 0;
        rot->pad = PARTICLE_WAIT;

        DG_SetPos2(&work->pos, rot);
        DG_PutVector(offset, vert, 1);
    }

    work->field_178 = 0;
    work->done = 0;

    work->flare_pos.vx = work->world.t[0];
    work->flare_pos.vy = work->world.t[1];
    work->flare_pos.vz = work->world.t[2];

    work->flare_speed.vx = GV_RandS(512);
    work->flare_speed.vy = 0;
    work->flare_speed.vz = GV_RandS(512);

    NewLensFlare2(&work->flare_pos, &work->flare_speed, work->time);
    return 0;
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

/*---------------------------------------------------------------------------*/

void *NewVrSnake(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "snake_e1.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
