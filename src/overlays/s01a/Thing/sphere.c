#include "common.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"

typedef struct _SphereWork
{
    GV_ACT   actor;
    DG_PRIM *prim;
    DG_IMG  *img;
    DG_TEX  *textures[16];
    short    f68;
    char     pad[0x2];
} SphereWork;

extern int GM_CurrentMap_800AB9B0;

extern short sphere_image_width_800E4B28;
extern short sphere_image_height_800E4B2A;
extern short sphere_visible_tiles_x_800E4B2C;
extern short sphere_visible_tiles_y_800E4B2E;
extern short sphere_tiles_x_800E4B30;
extern short sphere_tiles_y_800E4B32;
extern short sphere_tile_width_800E4B34;
extern short sphere_tile_height_800E4B36;
extern short sphere_elevation_800E4B38;
extern short sphere_word_800E4B3A;

#define EXEC_LEVEL 7

void Sphere_800C60E0(MATRIX *eye, SVECTOR *out)
{
    SVECTOR sp10;
    int     m12;
    int     length;
    int     yaw;

    m12 = eye->m[1][2];
    length = __max(4096 * 4096 - m12 * m12, 1);
    out->vy = (-m12 * 285) / SquareRoot0(length);

    sp10.vx = eye->m[0][2];
    sp10.vz = eye->m[2][2];

    yaw = (GV_YawVec3_80016EF8(&sp10) * sphere_image_width_800E4B28) / 4096 + 1;
    out->vx = sphere_image_width_800E4B28 - yaw;
    out->vy -= sphere_elevation_800E4B38;
}

#pragma INCLUDE_ASM("asm/overlays/s01a/SphereAct_800C61F0.s")
void SphereAct_800C61F0(SphereWork *work);

void SphereDie_800C6658(SphereWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

int SphereGetResources_800C6694(SphereWork *work, int map)
{
    SVECTOR   color;
    int       opt;
    int       model;
    DG_TEX  **textures;
    int       i;
    int       name;
    int       n_prims;
    DG_PRIM  *prim;
    int       index;
    POLY_FT4 *poly;

    GM_CurrentMap_800AB9B0 = map;

    opt = GCL_GetOption_80020968('c');
    GCL_StrToSV_80020A14((char *)opt, &color);

    opt = GCL_GetOption_80020968('y');
    sphere_elevation_800E4B38 = GCL_StrToInt_800209E8((char *)opt);

    opt = GCL_GetOption_80020968('m');
    model = GCL_StrToInt_800209E8((char *)opt);
    work->img = GV_GetCache_8001538C(GV_CacheID_800152DC(model, 'i'));
    if (work->img == NULL)
    {
        return -1;
    }

    sphere_image_width_800E4B28 = work->img->image_width;
    sphere_image_height_800E4B2A = work->img->image_height;
    sphere_tile_width_800E4B34 = work->img->tile_width;
    sphere_tile_height_800E4B36 = work->img->tile_height;
    sphere_tiles_x_800E4B30 = sphere_image_width_800E4B28 / sphere_tile_width_800E4B34;
    sphere_tiles_y_800E4B32 = sphere_image_height_800E4B2A / sphere_tile_height_800E4B36;

    textures = work->textures;
    for (i = 0; i < work->img->textures[0]; i++)
    {
        name = work->img->textures[i + 1];
        *textures++ = DG_GetTexture_8001D830(name);
    }

    sphere_visible_tiles_x_800E4B2C = (320 / sphere_tile_width_800E4B34) + 1;
    sphere_visible_tiles_y_800E4B2E = (224 / sphere_tile_height_800E4B36) + 1;
    n_prims = sphere_visible_tiles_y_800E4B2E * sphere_visible_tiles_x_800E4B2C;

    prim = DG_GetPrim(0x812, n_prims, 0, NULL, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    for (index = 0; index < 2; index++)
    {
        poly = &work->prim->field_40_pBuffers[index]->poly_ft4;
        for (i = 0; i < n_prims; i++)
        {
            setRGB0(poly, color.vx, color.vy, color.vz);
            setPolyFT4(poly);
            poly++;
        }
    }

    if (GCL_GetOption_80020968('s'))
    {
        opt = GCL_GetOption_80020968('s');
        work->f68 = GCL_StrToInt_800209E8((char *)opt);
    }
    else
    {
        work->f68 = 0;
    }

    return 0;
}

GV_ACT * NewSphere_800C69C0(int name, int where)
{
    SphereWork *work;

    work = (SphereWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(SphereWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)SphereAct_800C61F0, (TActorFunction)SphereDie_800C6658, "sphere.c");

        if (SphereGetResources_800C6694(work, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        sphere_word_800E4B3A = 0;
    }

    return &work->actor;
}
