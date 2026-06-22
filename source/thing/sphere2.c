#include "sphere2.h"

#include "libgcl/libgcl.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

typedef struct _Work
{
    GV_ACT   actor;
    DG_PRIM *prim;
    DG_IMG  *img;
    DG_TEX  *tex[16];
    int      speed;
} Work;

/*---------------------------------------------------------------------------*/

static u_short SECTION(".bss") sphere_image_width;
static u_short SECTION(".bss") sphere_image_height;
static u_short SECTION(".bss") sphere_visible_tiles_x;
static u_short SECTION(".bss") sphere_visible_tiles_y;
static u_short SECTION(".bss") sphere_tiles_x;
static u_short SECTION(".bss") sphere_tiles_y;
static u_short SECTION(".bss") sphere_tile_width;
static u_short SECTION(".bss") sphere_tile_height;
static u_short SECTION(".bss") sphere_elevation;
static u_short SECTION(".bss") sphere_scroll;

/*---------------------------------------------------------------------------*/

static void GetViewDir(MATRIX *eye, SVECTOR *out)
{
    SVECTOR sp10;
    int     m12;
    int     length;

    m12 = eye->m[1][2];
    length = MAX(4096 * 4096 - m12 * m12, 1);
    out->vy = (-m12 * 285) / SquareRoot0(length);

    sp10.vx = eye->m[0][2];
    sp10.vy = 0;
    sp10.vz = eye->m[2][2];

    out->vx = sphere_image_width - 1 - (GV_VecDir2(&sp10) * sphere_image_width) / 4096;
    out->vy -= sphere_elevation;
}

static void Act(Work *work)
{
    SVECTOR        dir;
    POLY_FT4      *poly;
    int            x0_orig;
    int            tx_orig, z, x, y, ty, map_idx, tx, last_tile, last_texid;
    int            x0, y0, x1, y1;
    short          u0, v0;
    short          xoff, yoff, tpage, clut;
    char          *tilemap;
    DG_IMG_ATTRIB *attribs, *attrib;
    DG_TEX       **tex;
    unsigned short u1, v1;
    long           tile_height, tile_width;

    GetViewDir(&DG_Chanl(0)->eye, &dir);

    if (work->speed > 0)
    {
        dir.vx += (sphere_image_width - 1) & (sphere_scroll++ / work->speed);
    }
    else if (work->speed < 0)
    {
        dir.vx += (sphere_image_width - 1) & (-work->speed * sphere_scroll++);
    }

    if (dir.vx >= sphere_image_width)
    {
        dir.vx -= sphere_image_width;
    }

    tx = dir.vx - 160;
    if (tx < 0)
    {
        tx += sphere_image_width;
    }

    ty = dir.vy + sphere_image_height / 2 - 112;
    if (ty < 0)
    {
        ty = 0;
    }

    x0 = -(tx % sphere_tile_width) - 160;
    y0 = -(ty % sphere_tile_height) - 112;

    tx /= sphere_tile_width;
    if (tx >= sphere_tiles_x)
    {
        tx = 0;
    }

    ty /= sphere_tile_height;
    if (ty >= sphere_tiles_y)
    {
        ty = sphere_tiles_y - 1;
    }

    last_texid = -1;
    last_tile = -1;

    x0_orig = x0;
    tx_orig = tx;

    attribs = work->img->attribs;
    tilemap = work->img->tilemap;
    tex = work->tex;

    poly = work->prim->packs[GV_Clock];
    for (y = 0; y < sphere_visible_tiles_y; y++)
    {
        x0 = x0_orig;
        tx = tx_orig;

        map_idx = ty * sphere_tiles_x + tx;

        for (x = 0; x < sphere_visible_tiles_x; x++)
        {
            z = 63000;
            if (last_tile != tilemap[map_idx])
            {
                last_tile = tilemap[map_idx];
                attrib = &attribs[last_tile];
                if (last_texid != attrib->texid)
                {
                    last_texid = attrib->texid;

                    tpage = tex[attrib->texid]->tpage;
                    clut = tex[attrib->texid]->clut;
                    xoff = tex[attrib->texid]->off_x;
                    yoff = tex[attrib->texid]->off_y;
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

            tx++;

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

            SSTOREL(z, poly);

            tile_width = sphere_tile_width;
            x0 += tile_width;

            map_idx++;
            if (tx >= sphere_tiles_x)
            {
                map_idx -= sphere_tiles_x;
                tx = 0;
            }
            poly++;
        }
        tile_height = sphere_tile_height;
        y0 += tile_height;
        if (++ty >= sphere_tiles_y)
        {
            ty--;
        }
    }
}

void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, int map)
{
    SVECTOR   color;
    int       model;
    DG_TEX  **tex;
    int       name;
    int       i, j;
    int       n_prims;
    POLY_FT4 *pack;

    GM_CurrentMap = map;

    GCL_StrToSV(GCL_GetOption('c'), (short *)&color);
    sphere_elevation = GCL_StrToInt(GCL_GetOption('y'));

    model = GCL_StrToInt(GCL_GetOption('m'));
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

    tex = work->tex;
    for (i = 0; i < work->img->textures[0]; i++)
    {
        name = work->img->textures[i + 1];
        *tex = DG_GetTexture(name);
        tex++;
    }

    sphere_visible_tiles_x = 320 / sphere_tile_width + 1;
    sphere_visible_tiles_y = 224 / sphere_tile_height + 1;
    n_prims = sphere_visible_tiles_y * sphere_visible_tiles_x;

    work->prim = GM_MakePrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, n_prims, NULL, NULL);
    if (work->prim == NULL)
    {
        return -1;
    }

    for (j = 0; j < 2; j++)
    {
        pack = work->prim->packs[j];
        for (i = 0; i < n_prims; i++)
        {
            setRGB0(pack, color.vx, color.vy, color.vz);
            setPolyFT4(pack);
            pack++;
        }
    }

    if (GCL_GetOption('s'))
    {
        work->speed = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->speed = 0;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewSphere2(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_AFTER2, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "sphere2.c");
        if (GetResources(work, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
        sphere_scroll = 0;
    }
    return (void *)work;
}
