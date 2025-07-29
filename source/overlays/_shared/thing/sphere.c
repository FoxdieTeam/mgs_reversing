#include "sphere.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_AFTER2

typedef struct _Work
{
    GV_ACT   actor;
    DG_PRIM *prim;
    DG_IMG  *img;
    DG_TEX  *textures[16];
    short    f68;
    char     pad[0x2];
} Work;

/*---------------------------------------------------------------------------*/

static short SECTION("overlay.bss") sphere_image_width;
static short SECTION("overlay.bss") sphere_image_height;
static short SECTION("overlay.bss") sphere_visible_tiles_x;
static short SECTION("overlay.bss") sphere_visible_tiles_y;
static short SECTION("overlay.bss") sphere_tiles_x;
static short SECTION("overlay.bss") sphere_tiles_y;
static short SECTION("overlay.bss") sphere_tile_width;
static short SECTION("overlay.bss") sphere_tile_height;
static short SECTION("overlay.bss") sphere_elevation;
static short SECTION("overlay.bss") sphere_word;

static void Sphere_800C60E0(MATRIX *eye, SVECTOR *out)
{
    SVECTOR sp10;
    int     m12;
    int     length;
    int     yaw;

    m12 = eye->m[1][2];
    length = MAX(4096 * 4096 - m12 * m12, 1);
    out->vy = (-m12 * 285) / SquareRoot0(length);

    sp10.vx = eye->m[0][2];
    sp10.vz = eye->m[2][2];

    yaw = (GV_VecDir2(&sp10) * sphere_image_width) / 4096 + 1;
    out->vx = sphere_image_width - yaw;
    out->vy -= sphere_elevation;
}

static void Act(Work *work)
{
    POLY_FT4      *poly;
    SVECTOR        svec;
    int            x0_orig;
    int            x_tile_iter_orig, tag, x, y, y_tile_iter, var_a2, map_idx, x_tile_iter, last_tile, last_texid;
    short          xoff, yoff, tpage, clut, u0, v0, x1, y1;
    int            x0;
    char          *tilemap;
    DG_IMG_ATTRIB *attribs, *attrib;
    DG_TEX       **textures;
    unsigned short y0;
    unsigned short u1, v1;
    short         *poly_tag;
    long           tile_height, tile_width;

    Sphere_800C60E0(&DG_Chanl(0)->field_30_eye, &svec);

    if (work->f68 > 0)
    {
        svec.vx += (sphere_image_width - 1) & (sphere_word++ & 0xFFFF) / work->f68;
    }
    else if (work->f68 < 0)
    {
        svec.vx += (sphere_image_width - 1) & -work->f68 * (sphere_word++ & 0xFFFF);
    }

    if (svec.vx >= sphere_image_width)
    {
        svec.vx -= sphere_image_width;
    }

    x_tile_iter = svec.vx - 160;
    if (x_tile_iter < 0)
    {
        x_tile_iter += sphere_image_width;
    }

    y_tile_iter = svec.vy + (sphere_image_height >> 1) - 112;
    var_a2 = 0;
    if (y_tile_iter < 0)
    {
        var_a2 = -y_tile_iter;
        y_tile_iter = 0;
    }

    x0 = -(x_tile_iter % sphere_tile_width) - 160;
    y0 = var_a2 - 112 - y_tile_iter % sphere_tile_height;
    x_tile_iter = x_tile_iter / sphere_tile_width;
    if (x_tile_iter >= sphere_tiles_x)
    {
        x_tile_iter = 0;
    }

    y_tile_iter = y_tile_iter / sphere_tile_height;
    if (y_tile_iter >= sphere_tiles_y)
    {
        y_tile_iter = sphere_tiles_y - 1;
    }

    last_texid = -1;
    last_tile = -1;

    x0_orig = x0;
    x_tile_iter_orig = x_tile_iter;

    attribs = work->img->attribs;
    tilemap = work->img->tilemap;
    textures = work->textures;

    poly = &work->prim->packs[GV_Clock]->poly_ft4;
    for (y = 0; y < sphere_visible_tiles_y; y++)
    {
        x0 = x0_orig;
        x_tile_iter = x_tile_iter_orig;

        map_idx = y_tile_iter * sphere_tiles_x + x_tile_iter;

        for (x = 0; x < sphere_visible_tiles_x; x++)
        {
            tag = 63000;
            if (last_tile != tilemap[map_idx])
            {
                last_tile = tilemap[map_idx];
                attrib = &attribs[last_tile];
                if (last_texid != attrib->texid)
                {
                    last_texid = attrib->texid;

                    tpage = textures[attrib->texid]->tpage;
                    clut = textures[attrib->texid]->clut;
                    xoff = textures[attrib->texid]->off_x;
                    yoff = textures[attrib->texid]->off_y;
                }

                u0 = attrib->xoff + xoff;
                u1 = u0 + sphere_tile_width;
                v0 = attrib->yoff + yoff;
                v1 = v0 + sphere_tile_height;
                if (u1 > 255)
                {
                    u1 = 255;
                }
                if (v1 > 255)
                {
                    v1 = 255;
                }
            }

            x_tile_iter++;

            x1 = sphere_tile_width + x0;
            y1 = sphere_tile_height + y0;

            poly->tpage = tpage;
            poly->clut = clut;

            poly->x0 = poly->x2 = x0;
            poly->y0 = poly->y1 = y0;
            poly->x1 = poly->x3 = x1;
            poly->y2 = poly->y3 = y1;

            poly->u0 = poly->u2 = u0;
            poly->u1 = poly->u3 = u1;
            poly->v0 = poly->v1 = v0;
            poly->v2 = poly->v3 = v1;

            poly_tag = (short *)poly;
            *poly_tag = tag;

            tile_width = sphere_tile_width;
            x0 += tile_width;

            map_idx++;
            if (x_tile_iter >= sphere_tiles_x)
            {
                map_idx -= sphere_tiles_x;
                x_tile_iter = 0;
            }
            poly++;
        }
        tile_height = sphere_tile_height;
        y0 += tile_height;
        if (++y_tile_iter >= sphere_tiles_y)
        {
            y_tile_iter--;
        }
    }
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, int map)
{
    SVECTOR   color;
    char     *opt;
    int       model;
    DG_TEX  **textures;
    int       i;
    int       name;
    int       n_prims;
    DG_PRIM  *prim;
    int       index;
    POLY_FT4 *poly;

    GM_CurrentMap = map;

    opt = GCL_GetOption('c');
    GCL_StrToSV(opt, &color);

    opt = GCL_GetOption('y');
    sphere_elevation = GCL_StrToInt(opt);

    opt = GCL_GetOption('m');
    model = GCL_StrToInt(opt);
    work->img = GV_GetCache(GV_CacheID(model, 'i'));
    if (work->img == NULL)
    {
        return -1;
    }

    sphere_image_width = work->img->image_width;
    sphere_image_height = work->img->image_height;
    sphere_tile_width = work->img->tile_width;
    sphere_tile_height = work->img->tile_height;
    sphere_tiles_x = sphere_image_width / sphere_tile_width;
    sphere_tiles_y = sphere_image_height / sphere_tile_height;

    textures = work->textures;
    for (i = 0; i < work->img->textures[0]; i++)
    {
        name = work->img->textures[i + 1];
        *textures++ = DG_GetTexture(name);
    }

    sphere_visible_tiles_x = (320 / sphere_tile_width) + 1;
    sphere_visible_tiles_y = (224 / sphere_tile_height) + 1;
    n_prims = sphere_visible_tiles_y * sphere_visible_tiles_x;

    prim = DG_GetPrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, n_prims, 0, NULL, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    for (index = 0; index < 2; index++)
    {
        poly = &work->prim->packs[index]->poly_ft4;
        for (i = 0; i < n_prims; i++)
        {
            setRGB0(poly, color.vx, color.vy, color.vz);
            setPolyFT4(poly);
            poly++;
        }
    }

    if (GCL_GetOption('s'))
    {
        opt = GCL_GetOption('s');
        work->f68 = GCL_StrToInt(opt);
    }
    else
    {
        work->f68 = 0;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewSphere(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "sphere.c");

        if (GetResources(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        sphere_word = 0;
    }

    return (void *)work;
}
