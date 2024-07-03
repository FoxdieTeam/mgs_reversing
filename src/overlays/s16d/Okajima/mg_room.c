#include "libdg/libdg.h"
#include "libgv/libgv.h"

typedef struct _MgRoom
{
    GV_ACT   actor;
    DG_PRIM *prim1;
    SVECTOR  vec1[1][4];
    SVECTOR  f44[1];
    SVECTOR  f4C[1];
    int      f54[1];
    int      f58[1];
    DG_PRIM *prim2;
    SVECTOR  vec2[1][4];
    SVECTOR  color[1];
    int      f88;
    int      map;
} MgRoom;

extern int     GV_Time_800AB330;
extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GV_Clock_800AB920;
extern int     GM_CurrentMap_800AB9B0;

#define EXEC_LEVEL 4

void MgRoom_800DAC98(POLY_FT4 *packs, int n_packs, DG_TEX *tex, SVECTOR *color)
{
    int x, y, w, h;

    while (--n_packs >= 0)
    {
        setPolyFT4(packs);
        setRGB0(packs, color->vx, color->vy, color->vz);

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;
        setUVWH(packs, x, y, w, h);

        packs->tpage = tex->tpage;
        packs->clut = tex->clut;

        packs++;
    }
}

void MgRoom_800DAD38(POLY_FT4 *packs, int n_packs, DG_TEX *tex, SVECTOR *color)
{
    int x, y, w, h;

    while (--n_packs >= 0)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);
        setRGB0(packs, color->vx, color->vy, color->vz);

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;
        setUVWH(packs, x, y, w, h);

        packs->tpage = tex->tpage;
        packs->clut = tex->clut;

        packs->tpage |= 0x40;

        packs++;
    }
}

void MgRoom_800DADDC(MgRoom *work)
{
    SVECTOR sp10[4];
    int     i;
    int     temp_a0;
    int     temp_t0;
    int     temp_lo;
    int     temp;
    int     var_a2;
    int     var_a3;
    int     x;

    for (i = 0; i < 1; i++)
    {
        temp_a0 = work->f58[i];

        temp_t0 = temp_a0 / 2;
        temp_lo = (temp_a0 * 9) / 8;
        temp = temp_a0 / 8;

        temp_lo = (temp_lo * (work->f88 % 64)) / 64;
        var_a3 = temp_lo;
        var_a2 = temp_lo - temp;

        if (temp_a0 < var_a3)
        {
            var_a3 = temp_a0;
        }

        if (var_a2 < 0)
        {
            var_a2 = 0;
        }

        if (temp_a0 < var_a2)
        {
            var_a2 = temp_a0;
        }

        x = work->f54[i];

        sp10[0].vx = -(x / 2);
        sp10[0].vz = 0;
        sp10[0].vy = temp_t0 - var_a3;

        sp10[1].vx = x / 2;
        sp10[1].vy = temp_t0 - var_a3;
        sp10[1].vz = 0;

        sp10[2].vx = -(x / 2);
        sp10[2].vy = temp_t0 - var_a2;
        sp10[2].vz = 0;

        sp10[3].vx = x / 2;
        sp10[3].vy = temp_t0 - var_a2;
        sp10[3].vz = 0;

        DG_SetPos2_8001BC8C(&work->f44[i], &work->f4C[i]);
        DG_PutVector_8001BE48(sp10, work->vec1[i], 4);
    }
}

void MgRoom_800DAF34(MgRoom *work)
{
    SVECTOR   color;
    POLY_FT4 *poly;
    int       i;

    poly = &work->prim2->packs[GV_Clock_800AB920]->poly_ft4;
    for (i = 0; i < 1; i++)
    {
        color = work->color[i];
        setRGB0(poly, color.vx, color.vy, color.vz);
        poly++;
    }
}

void MgRoomAct_800DAFAC(MgRoom *work)
{
    GM_CurrentMap_800AB9B0 = work->map;

    MgRoom_800DADDC(work);
    MgRoom_800DAF34(work);

    if ((GV_Time_800AB330 % 3) == 0)
    {
        work->f88++;
    }
}

void MgRoomDie_800DB024(MgRoom *work)
{
    DG_PRIM *prim;

    prim = work->prim1;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    prim = work->prim2;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

void MgRoom_800DB08C(MgRoom *work, int index, SVECTOR *pos, SVECTOR *rot, int x, int y)
{
    SVECTOR pos2;

    pos2 = *pos;
    work->f44[index] = pos2;
    work->f4C[index] = *rot;
    work->f54[index] = x;
    work->f58[index] = y;
}

void MgRoom_800DB118(MgRoom *work, int index, SVECTOR *pos, SVECTOR *rot, int x, int y, SVECTOR *color)
{
    SVECTOR pos2;
    SVECTOR sp18;
    SVECTOR sp20[4];

    pos2 = *pos;

    sp18.vz = 0;

    sp20[0].vz = 0;
    sp20[1].vz = 0;
    sp20[2].vz = 0;
    sp20[3].vz = 0;

    sp20[0].vx = x / 2;
    sp20[0].vy = y / 2;

    sp20[1].vx = -(x / 2);
    sp20[1].vy = y / 2;

    sp20[2].vx = x / 2;
    sp20[2].vy = -(y / 2);

    sp20[3].vx = -(x / 2);
    sp20[3].vy = -(y / 2);

    DG_SetPos2_8001BC8C(&pos2, rot);
    DG_PutVector_8001BE48(sp20, work->vec2[index], 4);

    work->color[index] = *color;
}

int MgRoomGetResources_800DB218(MgRoom *work)
{
    SVECTOR  sp20;
    SVECTOR  sp28;
    SVECTOR  color;
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->f88 = 0;
    work->map = GM_CurrentMap_800AB9B0;

    prim = DG_GetPrim(0x12, 1, 0, work->vec1[0], NULL);
    work->prim1 = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 250;
    prim->field_2E_k500 *= 4;

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("sub_sline"));
    if (tex == NULL)
    {
        return -1;
    }

    color.vx = 32;
    color.vy = 32;
    color.vz = 32;

    MgRoom_800DAD38(&prim->packs[0]->poly_ft4, 1, tex, &color);
    MgRoom_800DAD38(&prim->packs[1]->poly_ft4, 1, tex, &color);

    prim = DG_GetPrim(0x12, 1, 0, work->vec2[0], NULL);
    work->prim2 = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 50;
    prim->field_2E_k500 *= 15;

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("m16d_snake"));
    if (tex == NULL)
    {
        return -1;
    }

    color = DG_ZeroVector_800AB39C;

    MgRoom_800DAC98(&prim->packs[0]->poly_ft4, 1, tex, &color);
    MgRoom_800DAC98(&prim->packs[1]->poly_ft4, 1, tex, &color);

    sp20.vx = 1150;
    sp20.vy = 2480;
    sp20.vz = 10040;

    sp28.vz = 0;
    sp28.vx = 300;
    sp28.vy = 0;

    MgRoom_800DB08C(work, 0, &sp20, &sp28, 500, 430);

    color.vx = 128;
    color.vy = 128;
    color.vz = 128;

    MgRoom_800DB118(work, 0, &sp20, &sp28, 500, 430, &color);

    return 0;
}

GV_ACT * NewMgRoom_800DB458(void)
{
    MgRoom *work;

    work = (MgRoom *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(MgRoom));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)MgRoomAct_800DAFAC, (TActorFunction)MgRoomDie_800DB024, "mg_room.c");

        if (MgRoomGetResources_800DB218(work) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
