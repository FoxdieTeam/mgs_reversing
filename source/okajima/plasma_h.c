#include "plasma_h.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

/*----------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL4

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    char     pad1[0x4];
    DG_PRIM *prim;
    int      terminal_len;
    SVECTOR  f30[17];
    SVECTOR  verts[68];
    SVECTOR  pos_terminal[2];
    SVECTOR  terminal_rot;
    int      ang_l[17];
    int      len_g[17];
    int      len_l[17];
    int      count;
    int      time;
} Work;

/*----------------------------------------------------------------*/

static int DirVecXY( SVECTOR *from, SVECTOR *to, SVECTOR *rot )
{
    int dx, dy, dz;
    int dis;
    int vec_vx, vec_vy, vec_vz;

    dx = (from->vx - to->vx) / 16;
    dy = (from->vy - to->vy) / 16;
    dz = (from->vz - to->vz) / 16;
    dis = SquareRoot0(dx * dx + dy * dy + dz * dz) * 16;
// clang-format off

    vec_vx  = (long)(to->vx - from->vx);
    vec_vy  = (long)(to->vy - from->vy);
    vec_vz  = (long)(to->vz - from->vz);
    rot->vy = ( 4095 & ratan2( vec_vx, vec_vz ) ) ;
    rot->vx = ( 4095 & ratan2( dis, vec_vy ) ) ;
    rot->vz = 0;

    return  dis;

}

/*----------------------------------------------------------------*/
static void InitPacks( Work *work, POLY_FT4 *packs, int n_packs, DG_TEX *tex )
{
    while ( -- n_packs >= 0 ) {
        setPolyFT4( packs ) ;
        setSemiTrans( packs, 1 ) ;
        setRGB0( packs, 100, 100, 250 );
        DG_SetPacketTexture4( packs, tex ) ;
        packs->tpage|=1<<5; /* 半透明属性を設定(libgpu.hを参照) */
        packs ++ ;
    }
}

static void PlasmaEdgeInit( Work *work, SVECTOR *pos1, SVECTOR *pos2 )
{
    int limit;

    work->pos_terminal[0] = *pos1;
    work->pos_terminal[1] = *pos2;
    work->terminal_len=DirVecXY( &work->pos_terminal[0], &work->pos_terminal[1], &work->terminal_rot );

    limit=work->terminal_len/4;
    work->ang_l[0]  = GV_RandU(4096);
    work->ang_l[4]  = GV_RandU(512);
    work->len_g[4]  = GV_RandU(1024);
    work->len_l[4]  = (limit * GV_RandU(4096)) / 4096;
    work->ang_l[8]  = work->ang_l[4] + GV_RandS(512);
    work->len_g[8]  = GV_RandU(1024) + 1024;
    work->len_l[8]  = (limit * 2 * GV_RandU(4096)) / 4096;
    work->ang_l[12] = work->ang_l[8] + GV_RandS(512);
    work->len_g[12] = GV_RandU(1024) + 2048;
    work->len_l[12] = (limit * GV_RandU(4096)) / 4096;
    work->ang_l[16] = work->ang_l[12] + GV_RandS(512);
// clang-format on

    if (work->len_g[8] < work->len_g[4])
    {
        work->len_g[4] = work->len_g[8];
    }

    if (work->len_g[12] < work->len_g[4])
    {
        work->len_g[4] = work->len_g[12];
    }

    if (work->len_g[12] < work->len_g[8])
    {
        work->len_g[8] = work->len_g[12];
    }

    work->f30[0] = work->pos_terminal[0];
    work->f30[16] = work->pos_terminal[1];

    work->len_g[0] = 0;
    work->len_g[16] = 4096;
    work->len_l[0] = 0;
    work->len_l[16] = 0;
}

static void s08a_plasma_h_800D13B4(Work *work)
{
    int len;
    int tmp;

    len = work->terminal_len / 4;

    work->ang_l[0] = work->ang_l[0] + GV_RandS(128);
    work->ang_l[4] = work->ang_l[4] + GV_RandS(64);
    work->len_g[4] = work->len_g[4] + GV_RandS(32);

    work->len_l[4] += GV_RandS(32);

    if (work->len_l[4] < 0)
    {
        work->len_l[4] = 0;
    }

    if (work->len_l[4] > len)
    {
        work->len_l[4] = len;
    }

    work->ang_l[8] += GV_RandS(64);

    if (work->ang_l[8] > (work->ang_l[4] + 512))
    {
        work->ang_l[8] = work->ang_l[4] + GV_RandS(512);
    }

    if (work->ang_l[8] < (work->ang_l[4] - 512))
    {
        work->ang_l[8] = work->ang_l[4] + GV_RandS(512);
    }

    work->len_g[8] += GV_RandS(32);
    work->len_l[8] += GV_RandS(64) + 16;

    if (work->len_l[8] < 0)
    {
        work->len_l[8] = 0;
    }

    if (work->len_l[8] > len)
    {
        work->len_l[8] = len;
    }

    work->ang_l[12] += GV_RandS(64);

    if (work->ang_l[12] > (work->ang_l[8] + 512))
    {
        work->ang_l[12] = work->ang_l[8] + GV_RandS(512);
    }

    if (work->ang_l[12] < (work->ang_l[8] - 512))
    {
        work->ang_l[12] = work->ang_l[8] + GV_RandS(512);
    }

    work->len_g[12] += GV_RandS(32);
    work->len_l[12] += GV_RandS(32);

    if (work->len_l[12] < 0)
    {
        work->len_l[12] = 0;
    }

    if (work->len_l[12] > (len * 2))
    {
        work->len_l[12] = len * 2;
    }

    if (work->len_g[8] < work->len_g[4])
    {
        tmp = work->len_g[4];
        work->len_g[4] = work->len_g[8];
        work->len_g[8] = tmp;
    }

    if (work->len_g[12] < work->len_g[4])
    {
        tmp = work->len_g[4];
        work->len_g[4] = work->len_g[12];
        work->len_g[12] = tmp;
    }

    if (work->len_g[12] < work->len_g[8])
    {
        tmp = work->len_g[8];
        work->len_g[8] = work->len_g[12];
        work->len_g[12] = tmp;
    }
}

static void s08a_plasma_h_800D1638(Work *work, int a, int b)
{
    int m, p;

    m = a - b;
    p = a + b;

    work->len_g[a] = work->len_g[m] + ((work->len_g[p] - work->len_g[m]) * 3) / 4;
    work->len_l[a] = work->len_l[m] + (work->len_l[p] - work->len_l[m]) / 2;
    work->ang_l[a] = work->ang_l[m] + (work->ang_l[p] - work->ang_l[m]) / 2;
}

static void Act(Work *work)
{
    SVECTOR  sp10;
    SVECTOR  rot;
    SVECTOR  sp20;
    SVECTOR  sp28;
    int      i;
    SVECTOR *verts;
    int     *var_s5;
    int     *var_s4;
    int     *var_s2;
    int      len;
    SVECTOR *iter;

    GM_SetCurrentMap(work->map);

    if (work->count > work->time)
    {
        GV_DestroyActor(&work->actor);
    }

    work->count++;

    s08a_plasma_h_800D13B4(work);

    s08a_plasma_h_800D1638(work, 2, 2);
    s08a_plasma_h_800D1638(work, 6, 2);
    s08a_plasma_h_800D1638(work, 10, 2);
    s08a_plasma_h_800D1638(work, 14, 2);

    for (i = 0; i < 8; i++)
    {
        s08a_plasma_h_800D1638(work, i * 2 + 1, 1);
    }

    rot.vx = 0;
    rot.vz = 0;

    sp10.vx = 0;

    verts = work->f30;
    var_s5 = work->len_g;
    var_s4 = work->len_l;
    var_s2 = work->ang_l;
    for (i = 0; i < 17;)
    {
        sp10.vy = (*var_s5 * work->terminal_len) / 4096;
        sp10.vz = *var_s4;

        rot.vy = *var_s2;

        DG_SetPos2(&DG_ZeroVector, &rot);
        DG_PutVector(&sp10, verts, 1);

        i++;
        verts++;
        var_s5++;
        var_s4++;
        var_s2++;
    }

    DG_SetPos2(&work->pos_terminal[0], &work->terminal_rot);
    DG_PutVector(work->f30, work->f30, 17);

    len = work->terminal_len / 128;
    sp10.vx = len + GV_RandS(16);
    sp10.vy = len + GV_RandS(16);
    sp10.vz = len;

    iter = work->f30 + 1;
    verts = work->verts;

    sp20 = work->f30[0];
    GV_AddVec3(work->f30, &sp10, &sp28);

    for (i = 0; i < 16; i++)
    {
        *verts++ = sp20;
        *verts = *iter;
        sp20 = *verts++;
        *verts++ = sp28;
        GV_AddVec3(iter, &sp10, verts);
        sp28 = *verts++;
        iter++;
    }
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int s08a_plasma_h_800D19F0(Work *work)
{
    DG_TEX  *tex;
    DG_PRIM *prim;

    tex = DG_GetTexture(GV_StrCode("plasma"));
    if (tex == NULL)
    {
        return -1;
    }

    prim = GM_MakePrim(DG_PRIM_POLY_FT4, 17, work->verts, NULL);
    work->prim = prim;

    if (prim == NULL)
    {
        return -1;
    }

    prim->raise = 200;

    InitPacks(work, prim->packs[0], 17, tex);
    InitPacks(work, prim->packs[1], 17, tex);

    return 0;
}

static int GetResources(Work *work, SVECTOR *pos1, SVECTOR *pos2, int time)
{
    work->map = GM_CurrentMap;
    work->time = time;

    if (s08a_plasma_h_800D19F0(work) < 0)
    {
        return -1;
    }

    PlasmaEdgeInit(work, pos1, pos2);

    work->count = 0;
    return 0;
}

/*----------------------------------------------------------------*/

void *NewPlasmaH(SVECTOR *pos1, SVECTOR *pos2, int time)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "plasma_h.c");

        if (GetResources(work, pos1, pos2, time) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
