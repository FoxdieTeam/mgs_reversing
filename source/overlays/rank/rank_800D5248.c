#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct _Work
{
    GV_ACT   actor;
    int      field_20;
    DG_PRIM *prim1;
    DG_PRIM *prim2;
    POLY_FT4 polys1[16];
    POLY_FT4 polys2[9];
    int      field_414;
    int      field_418;
    int      attrs1[16];
    int      attrs2[9];
} Work;

void rank_800D5248(Work *work)
{
    POLY_FT4 *src;
    POLY_FT4 *dst;
    int       i;

    src = work->polys1;
    dst = (POLY_FT4 *)work->prim1->packs[GV_Clock];
    for (i = 0; i < 16; i++)
    {
        *dst = *src;
        SSTOREL(work->attrs1[i], dst);
        src++;
        dst++;
    }

    src = work->polys2;
    dst = (POLY_FT4 *)work->prim2->packs[GV_Clock];
    for (i = 0; i < 9; i++)
    {
        *dst = *src;
        SSTOREL(work->attrs2[i], dst);
        src++;
        dst++;
    }
}
