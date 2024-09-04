#include "libdg/libdg.h"
#include "libgv/libgv.h"

typedef struct _SubRoomWork
{
    GV_ACT   actor;
    DG_PRIM *prim1;
    SVECTOR  verts1[2][4];
    DG_PRIM *prim2;
    SVECTOR  verts2[2][16][4];
    DG_PRIM *prim3;
    SVECTOR  verts3[5][4];
    SVECTOR  f50C[5];
    SVECTOR  f534[5];
    int      f55C[2][5];
    DG_PRIM *prim4;
    SVECTOR  verts4[2][4];
    SVECTOR  f5C8[2];
    int      f5D8;
    int      map;
    GV_ACT  *txtscn;
} SubRoomWork;

extern int     GV_Time_800AB330;
extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GV_Clock_800AB920;
extern int     GM_CurrentMap_800AB9B0;

GV_ACT * NewOpTxtScn_800CD29C(void);

#define EXEC_LEVEL 4

void SubRoomShadePacks_800C729C(POLY_FT4 *packs, int n_packs, DG_TEX *tex, SVECTOR *color)
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
        packs->tpage |= 0x60;

        packs++;
    }
}

void SubRoomShadePacks_800C7340(POLY_FT4 *packs, int n_packs, DG_TEX *tex, SVECTOR *color)
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

void SubRoom_800C73E4(SubRoomWork *work)
{
    int       last;
    int       mod;
    POLY_FT4 *poly;
    int       i, j;
    int       shade;

    last = 0;
    mod = work->f5D8 % 16;

    poly = &work->prim2->packs[GV_Clock_800AB920]->poly_ft4;

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 16; j++)
        {
            shade = 16 - mod + j;
            if (shade >= 16)
            {
                shade -= 16;
            }
            else
            {
                last = j;
            }

            shade = shade * shade;
            setRGB0(poly, shade, shade, shade);
            poly++;
        }

        work->verts1[i][0] = work->verts2[i][last][0];
        work->verts1[i][1] = work->verts2[i][last][1];
        work->verts1[i][2] = work->verts2[i][last][2];
        work->verts1[i][3] = work->verts2[i][last][3];
    }
}

void SubRoom_800C751C(SubRoomWork *work)
{
    SVECTOR verts[4];

    int i;

    int vx;
    int vy0, vy1, vy2, vy3, vy4, vy5; // temporaries related to Y coordinate

    for (i = 0; i < 5; i++)
    {
        vy0 = work->f55C[1][i];

        vy1 = vy0 / 2;
        vy4 = vy0 * 9 / 8;
        vy5 = vy0 / 8;
        vy2 = vy4 * (work->f5D8 % 64) / 64;
        vy3 = vy5;
        vy3 = vy2 - vy3;

        if (vy0 < vy2)
        {
            vy2 = vy0;
        }

        if (vy3 < 0)
        {
            vy3 = 0;
        }

        if (vy0 < vy3)
        {
            vy3 = vy0;
        }

        vx = work->f55C[0][i];

        verts[0].vx = -(vx / 2);
        verts[0].vy = vy1 - vy2;
        verts[1].vy = vy1 - vy2;

        verts[1].vx = vx / 2;
        verts[0].vz = 0;
        verts[1].vz = 0;

        verts[2].vx = -(vx / 2);
        verts[2].vy = vy1 - vy3;
        verts[2].vz = 0;

        verts[3].vx = vx / 2;
        verts[3].vy = vy1 - vy3;
        verts[3].vz = 0;

        DG_SetPos2(&work->f50C[i], &work->f534[i]);
        DG_PutVector(verts, work->verts3[i], 4);
    }
}

void SubRoom_800C7678(SubRoomWork *work)
{
    SVECTOR   color;
    POLY_FT4 *poly;
    int       i;

    poly = &work->prim4->packs[GV_Clock_800AB920]->poly_ft4;

    for (i = 0; i < 2; i++)
    {
        color = work->f5C8[i];
        color.vx += GV_RandS(32);
        color.vy += GV_RandS(32);
        color.vz += GV_RandS(32);

        setRGB0(poly, color.vx, color.vy, color.vz);
        poly++;
    }
}

void SubRoomAct_800C7750(SubRoomWork *work)
{
    GM_CurrentMap_800AB9B0 = work->map;

    SubRoom_800C73E4(work);
    SubRoom_800C751C(work);
    SubRoom_800C7678(work);

    if ((GV_Time_800AB330 % 3) == 0)
    {
        work->f5D8++;
    }
}

void SubRoomDie_800C77D0(SubRoomWork *work)
{
    DG_PRIM *prim;

    prim = work->prim2;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    prim = work->prim1;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    prim = work->prim3;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    prim = work->prim4;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    GV_DestroyOtherActor(work->txtscn);
}

void SubRoom_800C7884(SubRoomWork *work, int index, SVECTOR *position, SVECTOR *rotation, int inc)
{
    SVECTOR  rot;
    SVECTOR  pos;
    SVECTOR  verts[4];
    int      i;
    SVECTOR *iter;
    int      x, y;

    i = 0;
    iter = (SVECTOR *)work->verts2[index];

    pos = *position;
    pos.vx -= 22000;
    pos.vy -= 22000;
    pos.vz += 22000;

    rot = *rotation;

    for (; i < 16; i++)
    {
        x = (i * (inc / 2)) / 16;
        y = (x * 20) / 16;

        rot.vz = 0;

        verts[0].vx = -x;
        verts[0].vy = -y;
        verts[0].vz = 0;

        verts[1].vx = x;
        verts[1].vy = -y;
        verts[1].vz = 0;

        verts[2].vx = -x;
        verts[2].vy = y;
        verts[2].vz = 0;

        verts[3].vx = x;
        verts[3].vy = y;
        verts[3].vz = 0;

        DG_SetPos2(&pos, &rot);
        DG_PutVector(verts, iter, 4);
        iter += 4;
    }
}

void SubRoom_800C79D4(SubRoomWork *work, int index, SVECTOR *position, SVECTOR *rotation, int arg4, int arg5)
{
    SVECTOR pos;

    pos = *position;
    pos.vx -= 22000;
    pos.vy -= 22000;
    pos.vz += 22000;

    work->f50C[index] = pos;
    work->f534[index] = *rotation;

    work->f55C[0][index] = arg4;
    work->f55C[1][index] = arg5;
}

void SubRoom_800C7A84(SubRoomWork *work, int index, SVECTOR *position, SVECTOR *rotation, int arg4, SVECTOR *color)
{
    SVECTOR pos;
    SVECTOR rot;
    SVECTOR verts[4];
    int     coord;

    pos = *position;
    pos.vx -= 22000;
    pos.vy -= 22000;
    pos.vz += 22000;

    rot.vz = 0;

    coord = arg4 / 2;

    verts[0].vx = -coord;
    verts[0].vy = -coord;
    verts[0].vz = 0;

    verts[1].vx = coord;
    verts[1].vy = -coord;
    verts[1].vz = 0;

    verts[2].vx = -coord;
    verts[2].vy = coord;
    verts[2].vz = 0;

    verts[3].vx = coord;
    verts[3].vy = coord;
    verts[3].vz = 0;

    DG_SetPos2(&pos, rotation);
    DG_PutVector(verts, work->verts4[index], 4);

    work->f5C8[index] = *color;
}

int SubRoomGetResources_800C7B94(SubRoomWork *work)
{
    SVECTOR  pos;
    SVECTOR  rot;
    SVECTOR  color;
    DG_PRIM *prim;
    DG_TEX  *tex;
    int      off1, off2;

    work->f5D8 = 0;
    work->map = GM_CurrentMap_800AB9B0;

    prim = DG_GetPrim(0x12, 2, 0, (SVECTOR *)work->verts1, NULL);
    work->prim1 = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 250;

    tex = DG_GetTexture(GV_StrCode("sub_sn1"));
    if (tex == NULL)
    {
        return -1;
    }

    color.vx = 255;
    color.vy = 255;
    color.vz = 255;

    SubRoomShadePacks_800C729C(&prim->packs[0]->poly_ft4, 2, tex, &color);
    SubRoomShadePacks_800C729C(&prim->packs[1]->poly_ft4, 2, tex, &color);

    prim = DG_GetPrim(0x12, 32, 0, (SVECTOR *)work->verts2, NULL);
    work->prim2 = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 250;

    tex = DG_GetTexture(GV_StrCode("sub_sn2"));
    if (tex == NULL)
    {
        return -1;
    }

    color = DG_ZeroVector_800AB39C;

    SubRoomShadePacks_800C729C(&prim->packs[0]->poly_ft4, 32, tex, &color);
    SubRoomShadePacks_800C729C(&prim->packs[1]->poly_ft4, 32, tex, &color);

    prim = DG_GetPrim(0x12, 5, 0, (SVECTOR *)work->verts3, NULL);
    work->prim3 = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 250;

    tex = DG_GetTexture(GV_StrCode("sub_sline"));
    if (tex == NULL)
    {
        return -1;
    }

    color.vx = 32;
    color.vy = 32;
    color.vz = 32;

    SubRoomShadePacks_800C7340(&prim->packs[0]->poly_ft4, 5, tex, &color);
    SubRoomShadePacks_800C7340(&prim->packs[1]->poly_ft4, 5, tex, &color);

    prim = DG_GetPrim(0x12, 2, 0, (SVECTOR *)work->verts4, NULL);
    work->prim4 = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 250;

    tex = DG_GetTexture(GV_StrCode("rcm_l"));
    if (tex == NULL)
    {
        return -1;
    }

    color = DG_ZeroVector_800AB39C;

    SubRoomShadePacks_800C729C(&prim->packs[0]->poly_ft4, 2, tex, &color);
    SubRoomShadePacks_800C729C(&prim->packs[1]->poly_ft4, 2, tex, &color);

    // Inline crap i'd imagine
    off1 = 470;
    off2 = 400;

    rot.vz = 0;

    pos.vx = -2374;
    pos.vy = 874;
    pos.vz = 1374;

    rot.vx = 770;
    rot.vy = -1024;

    SubRoom_800C7884(work, 0, &pos, &rot, off1);

    pos.vx = -2374;
    pos.vy = 874;
    pos.vz = 125;

    rot.vx = 770;
    rot.vy = -1024;

    SubRoom_800C7884(work, 1, &pos, &rot, off1);

    off1 = 625;

    pos.vx = -1779;
    pos.vy = 2000;
    pos.vz = 2492;

    rot.vx = 0;
    rot.vy = -512;

    SubRoom_800C79D4(work, 0, &pos, &rot, off1, off2);

    off1 = 800;
    off2 = 550;

    pos.vx = -2750;
    pos.vy = 1374;
    pos.vz = 125;

    rot.vx = 0;
    rot.vy = 1024;

    SubRoom_800C79D4(work, 1, &pos, &rot, off1, off2);

    off1 = 1250;
    off2 = 1000;

    pos.vx = -375;
    pos.vy = 1625;
    pos.vz = -3000;

    rot.vx = 0;
    rot.vy = 0;

    SubRoom_800C79D4(work, 2, &pos, &rot, off1, off2);

    off1 = 950;
    off2 = 850;

    pos.vx = 2374;
    pos.vy = 2124;
    pos.vz = -874;

    rot.vx = -512;
    rot.vy = 1024;

    SubRoom_800C79D4(work, 3, &pos, &rot, off1, off2);

    pos.vx = 2374;
    pos.vy = 2124;
    pos.vz = 1374;

    rot.vx = -512;
    rot.vy = 1024;

    SubRoom_800C79D4(work, 4, &pos, &rot, off1, off2);

    off1 = 80;

    pos.vx = -2374;
    pos.vy = 874;
    pos.vz = 1374;

    rot.vx = 770;
    rot.vy = -1024;

    color.vx = 255;
    color.vy = 255;
    color.vz = 255;

    SubRoom_800C7A84(work, 0, &pos, &rot, off1, &color);

    pos.vx = -2374;
    pos.vy = 874;
    pos.vz = 125;

    rot.vx = 770;
    rot.vy = -1024;

    color.vx = 255;
    color.vy = 255;
    color.vz = 255;

    SubRoom_800C7A84(work, 1, &pos, &rot, off1, &color);

    work->txtscn = NewOpTxtScn_800CD29C();
    return 0;
}

GV_ACT * NewSubRoom_800C815C(void)
{
    SubRoomWork *work;

    work = (SubRoomWork *)GV_NewActor(EXEC_LEVEL, sizeof(SubRoomWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)SubRoomAct_800C7750, (TActorFunction)SubRoomDie_800C77D0, "sub_room.c");

        if (SubRoomGetResources_800C7B94(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
