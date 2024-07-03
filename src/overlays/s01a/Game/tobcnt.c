#include "common.h"
#include "libdg/libdg.h"
#include "libgcl/hash.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/game.h"

typedef struct _TobcntWork
{
    GV_ACT   actor;
    short    state;
    short    time;
    short    timeout;
    short    gradient;
    int      vox;
    POLY_G4  polys[2][12];
    LINE_G2  lines[2][166];
    DR_TPAGE tpage[2];
    TILE     tile[2];
    DR_TPAGE tpage2[2];
    DVECTOR  directions[166];
} TobcntWork;

extern int    GM_GameStatus_800AB3CC;
extern int    GM_LoadRequest_800AB3D0;
extern int    GM_GameOverTimer_800AB3D4;
extern int    GV_Clock_800AB920;
extern int    GV_PauseLevel_800AB928;
extern GV_PAD GV_PadData_800B05C0[4];

short tobcnt_lines[] = {
    166, // table length
    19,  93,  39,  93,  19,  93,  18,  98,  39,  93,  38,  98,  31,  98,  38,  98,
    31,  98,  25,  129, 25,  129, 19,  129, 42,  93,  60,  93,  42,  93,  41,  98,
    60,  93,  59,  98,  41,  98,  59,  98,  40,  102, 37,  117, 37,  117, 55,  117,
    55,  117, 58,  102, 40,  102, 46,  102, 52,  102, 58,  102, 44,  112, 46,  102,
    44,  112, 50,  112, 52,  102, 50,  112, 18,  98,  25,  98,  25,  98,  19,  129,
    68,  98,  69,  93,  69,  93,  85,  93,  68,  98,  80,  98,  77,  102, 67,  102,
    67,  102, 64,  117, 64,  117, 79,  117, 79,  117, 84,  113, 85,  109, 82,  105,
    87,  98,  85,  93,  87,  98,  82,  105, 80,  98,  77,  102, 71,  112, 76,  112,
    76,  112, 79,  110, 71,  112, 72,  107, 72,  107, 77,  107, 79,  110, 77,  107,
    85,  109, 84,  113, 86,  117, 102, 117, 91,  93,  107, 93,  90,  98,  106, 98,
    89,  102, 105, 102, 89,  102, 86,  117, 91,  93,  90,  98,  107, 93,  106, 98,
    104, 107, 94,  107, 105, 102, 104, 107, 93,  112, 103, 112, 103, 112, 102, 117,
    93,  112, 94,  107, 122, 93,  135, 93,  122, 93,  112, 105, 130, 117, 116, 117,
    125, 98,  134, 98,  135, 93,  134, 98,  125, 98,  119, 105, 119, 105, 121, 112,
    121, 112, 131, 112, 131, 112, 130, 117, 112, 105, 116, 117, 157, 93,  139, 93,
    134, 117, 152, 117, 138, 98,  156, 98,  143, 102, 141, 112, 141, 112, 147, 112,
    149, 102, 147, 112, 137, 102, 143, 102, 149, 102, 155, 102, 139, 93,  138, 98,
    137, 102, 134, 117, 155, 102, 152, 117, 157, 93,  156, 98,  161, 93,  160, 98,
    161, 93,  167, 93,  170, 102, 172, 106, 174, 98,  175, 93,  175, 93,  181, 93,
    179, 102, 176, 117, 156, 117, 162, 117, 162, 117, 165, 103, 165, 103, 171, 117,
    171, 117, 176, 117, 160, 98,  169, 98,  167, 93,  169, 98,  159, 102, 170, 102,
    159, 102, 156, 117, 174, 98,  180, 98,  173, 102, 172, 106, 173, 102, 179, 102,
    180, 98,  181, 93,  184, 93,  183, 98,  204, 93,  184, 93,  204, 93,  203, 98,
    203, 98,  183, 98,  189, 102, 186, 117, 195, 102, 192, 117, 186, 117, 192, 117,
    189, 102, 195, 102, 205, 102, 202, 117, 207, 93,  213, 93,  211, 102, 208, 117,
    202, 117, 208, 117, 206, 98,  212, 98,  205, 102, 211, 102, 207, 93,  206, 98,
    213, 93,  212, 98,  215, 102, 212, 117, 212, 117, 218, 117, 218, 117, 221, 103,
    217, 93,  223, 93,  223, 93,  225, 98,  225, 98,  216, 98,  215, 102, 226, 102,
    226, 102, 228, 106, 221, 103, 227, 117, 227, 117, 232, 117, 228, 106, 229, 102,
    229, 102, 235, 102, 235, 102, 232, 117, 217, 93,  216, 98,  230, 98,  236, 98,
    230, 98,  231, 93,  236, 98,  237, 93,  231, 93,  237, 93,  239, 102, 236, 117,
    241, 93,  247, 93,  236, 117, 254, 117, 254, 117, 257, 102, 243, 112, 249, 112,
    243, 112, 245, 102, 249, 112, 251, 102, 240, 98,  246, 98,  252, 98,  258, 98,
    239, 102, 245, 102, 251, 102, 257, 102, 253, 93,  259, 93,  241, 93,  240, 98,
    247, 93,  246, 98,  253, 93,  252, 98,  259, 93,  258, 98,  258, 117, 274, 117,
    258, 117, 261, 102, 263, 93,  279, 93,  277, 102, 276, 107, 262, 98,  278, 98,
    261, 102, 277, 102, 263, 93,  262, 98,  279, 93,  278, 98,  266, 107, 276, 107,
    275, 112, 265, 112, 266, 107, 265, 112, 275, 112, 274, 117, 281, 102, 278, 117,
    283, 93,  298, 93,  298, 93,  302, 104, 302, 104, 293, 117, 293, 117, 278, 117,
    282, 98,  293, 98,  293, 98,  295, 104, 295, 104, 289, 112, 289, 112, 285, 112,
    285, 112, 287, 102, 281, 102, 287, 102, 283, 93,  282, 98,  30,  120, 28,  129,
    30,  120, 291, 120, 28,  129, 285, 129
};

short s01a_dword_800C381A = 0x800C;

#define EXEC_LEVEL 0

char * Tobcnt_800C4070(char *buf, int x, int y, int name, unsigned int color, char *ot)
{
    DG_TEX   *tex;
    SPRT     *sprt;
    DR_TPAGE *tpage;

    tex = DG_GetTexture_8001D830(name);

    sprt = (SPRT *)buf;
    setXY0(sprt, x, y);
    setUV0(sprt, tex->off_x, tex->off_y);
    setWH(sprt, tex->w + 1, tex->h + 1);
    sprt->clut = tex->clut;
    LSTORE( color, &sprt->r0 );
    setSprt(sprt);
    addPrim(ot, sprt);

    tpage = (DR_TPAGE *)(buf + sizeof(SPRT));
    setDrawTPage(tpage, 1, 0, tex->tpage);
    addPrim(ot, tpage);

    return buf + sizeof(SPRT) + sizeof(DR_TPAGE);
}

int Tobcnt_800C41A0(int shade, int state)
{
    int r, gb;

    if (state < 8)
    {
        r = 128;
        gb = 255;
    }
    else
    {
        state = __min(state - 8, 8);
        r = 128 - state * 16;
        gb = 255 - ((255 - shade) * state) / 8;
    }

    return r | gb << 8 | gb << 16;
}

void Tobcnt_800C4204( TobcntWork *work, char *ot )
{
    int       x0, y0;
    int       x1, y1;
    int       width, height;
    int       state;
    int       count;
    int       color1, color2, color3;
    DR_TPAGE *tpage;
    short    *lines;
    int       flag;
    DVECTOR  *directions;
    LINE_G2  *line;
    POLY_G4  *poly;
    int       shade;

    state = work->state;
    lines = tobcnt_lines;
    count = tobcnt_lines[0];

    directions = work->directions;
    line = work->lines[GV_Clock_800AB920];
    poly = work->polys[GV_Clock_800AB920];

    lines++;

    if ( state > 0 )
    {
        if ( state < count + 16 )
        {
            work->state = state + 2;
        }
        else
        {
            work->state = 0;
        }
    }

    flag = 1;
    if ( state == 0 )
    {
        flag = 0;
        state = 16;
    }

    for ( ; count > 0; count-- )
    {
        height = 0;
        width = 0;

        if ( flag )
        {
            if ( state < 8 )
            {
                width = directions->vx >> state;
                height = directions->vy >> state;

                if ( (count % 4) == 2 )
                {
                    width = -width;
                    height = -height;
                }
            }

            if ( --state < 0 )
            {
                break;
            }
        }

        x0 = lines[0];
        x1 = lines[2];

        x0 += width;
        x1 += width * 2;

        y0 = lines[1] + height;
        y1 = lines[3] + height * 2;

        line->x0 = x0;
        line->y0 = y0;
        line->x1 = x1;
        line->y1 = y1;

        color1 = x0 - 160;
        color2 = x1 - 160;

        if (color1 < 0)
        {
            color1 = -color1;
        }
        if (color2 < 0)
        {
            color2 = -color2;
        }

        color1 = 255 - color1;
        color2 = 255 - color2;

        if (color1 > 255)
        {
            color1 = 255;
        }

        if (color2 > 255)
        {
            color2 = 255;
        }

        LSTORE(Tobcnt_800C41A0(color1, state), &line->r0);

        if (count < 3)
        {
            LSTORE(0, &line->r1);
        }
        else
        {
            LSTORE(Tobcnt_800C41A0(color2, state), &line->r1);
        }

        setLineG2(line);
        addPrim(ot, line);
        line++;

        if (state >= 8 && state <= 13)
        {
            width = -(directions->vy >> (state - 6));
            height = directions->vx >> (state - 6);

            poly->x0 = x1 - width;
            poly->y0 = y1 - height;
            poly->x1 = x0 - width;
            poly->y1 = y0 - height;
            poly->x2 = (x0 + x1) / 2;
            poly->y2 = (y0 + y1) / 2;
            poly->x3 = x0 + width;
            poly->y3 = y0 + height;

            LSTORE(0, &poly->r0);
            LSTORE(0, &poly->r1);
            LSTORE(0x804000, &poly->r2);
            LSTORE(0, &poly->r3);

            setPolyG4(poly);
            setSemiTrans(poly, 1);
            addPrim(ot, poly);
            poly++;

            poly->x0 = x1 - width;
            poly->y0 = y1 - height;
            poly->x1 = x1 + width;
            poly->y1 = y1 + height;
            poly->x2 = (x0 + x1) / 2;
            poly->y2 = (y0 + y1) / 2;
            poly->x3 = x0 + width;
            poly->y3 = y0 + height;

            LSTORE(0, &poly->r0);
            LSTORE(0, &poly->r1);
            LSTORE(0x804000, &poly->r2);
            LSTORE(0, &poly->r3);

            setPolyG4(poly);
            setSemiTrans(poly, 1);
            addPrim(ot, poly);
            poly++;
        }

        lines += 4;
        directions++;
    }

    tpage = &work->tpage[GV_Clock_800AB920];
    setDrawTPage( tpage, 1, 1, getTPage( 0, 1, 0, 0 ) );
    addPrim( ot, tpage );

    if ( work->state == 0 )
    {
        if (work->gradient > 32)
        {
            shade = (64 - work->gradient) * 2 + 100;
        }
        else
        {
            shade = work->gradient * 2 + 100;
        }

        color3 = (shade << 8) | (shade << 16);
        Tobcnt_800C4070( (char *)work->polys[GV_Clock_800AB920], 114, 121, PCX_COMING_SOON, color3, ot );
    }
}

void Tobcnt_800C4750(TobcntWork *work, char *ot, int shade)
{
    TILE     *tile;
    DR_TPAGE *tpage;

    tile = &work->tile[GV_Clock_800AB920];
    LSTORE((shade << 16) | (shade << 8) | shade, &tile->r0);
    setTile(tile);
    setSemiTrans(tile, 1);
    setXY0(tile, 0, 0);
    setWH(tile, 320, 240);
    addPrim(ot, tile);

    tpage = &work->tpage2[GV_Clock_800AB920];
    setDrawTPage(tpage, 1, 1, getTPage(0, 2, 0, 0));
    addPrim(ot, tpage);
}

void TobcntAct_800C482C(TobcntWork *work)
{
    char   *ot;
    GV_PAD *pad;
    int     shade;

    ot = DG_ChanlOTag(1);

    if (work->time < 256)
    {
        Tobcnt_800C4204(work, ot);
        Tobcnt_800C4750(work, ot, work->time);

        if ((work->time == 120) && (work->vox >= 0))
        {
            GM_StreamPlayStart_80037D1C();
        }

        work->time += 3;
        if (work->time >= 256)
        {
            if (work->state > 0)
            {
                work->time = 255;
            }
            else
            {
                work->time = 256;
                work->timeout = 300;

                GV_PauseLevel_800AB928 |= 1;
                DG_FreeObjectQueue_800183D4();
                GM_GameStatus_800AB3CC |= 0x4A6000;
            }
        }
    }
    else if (work->time == 256)
    {
        Tobcnt_800C4204(work, ot);

        pad = &GV_PadData_800B05C0[0];
        GM_GameStatus_800AB3CC &= ~(GAME_FLAG_BIT_29 | GAME_FLAG_BIT_28);

        if ((pad->press & (PAD_START | PAD_CIRCLE | PAD_TRIANGLE)) || (--work->timeout < 0))
        {
            if (work->timeout > 0)
            {
                sub_80032AEC(0, 63, 33);
            }

            work->time = 257;
            work->timeout = 0;
            work->gradient = 32;
        }
        else
        {
            work->gradient = (work->gradient + 1) % 64;
        }
    }
    else
    {
        shade = __min(work->time - 256, 255);
        Tobcnt_800C4750(work, ot, shade);
        Tobcnt_800C4204(work, ot);

        work->time += 4;
        if (work->time > 542)
        {
            work->time = 542;

            if (GM_StreamStatus_80037CD8() == -1)
            {
                GV_DestroyActor_800151C8(&work->actor);
            }
        }
    }
}

void TobcntDie_800C4A64(TobcntWork *work)
{
    char *stage_name;

    stage_name = "title";
    GV_PauseLevel_800AB928 &= ~1;

    DG_ResetObjectQueue_8001844C();
    GM_StreamPlayStop_80037D64();

    GM_SetArea_8002A7D8(GV_StrCode_80016CCC(stage_name), stage_name);

    GM_LoadRequest_800AB3D0 = 0x81;
    GM_GameOverTimer_800AB3D4 = 0;
}

void TobcntGetResources_800C4AD0(TobcntWork *work)
{
    int      count;
    short   *in;
    DVECTOR *out;
    SVECTOR *vecs;

    count = tobcnt_lines[0];
    in = tobcnt_lines + 1;
    out = work->directions;

    *(short *)0x1F800004 = 0;

    for (; count > 0; count--)
    {
        vecs = (SVECTOR *)0x1F800000;
        vecs[0].vx = in[0] - in[2];
        vecs[0].vy = in[1] - in[3];

        VectorNormalSS((SVECTOR *)0x1F800000, (SVECTOR *)0x1F800008);

        out->vx = -vecs[1].vx / 8;
        out->vy = -vecs[1].vy / 8;

        in += 4;
        out++;
    }
}

GV_ACT * NewTobcnt_800C4BC8(int name, int where, int argc, char **argv)
{
    TobcntWork *work;

    GM_GameStatus_800AB3CC |= 0x4A6000;

    work = (TobcntWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(TobcntWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)TobcntAct_800C482C, (TActorFunction)TobcntDie_800C4A64, "tobcnt.c");

        work->state = 1;
        work->time = 0;

        if (GCL_GetOption_80020968('v'))
        {
            work->vox = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        }
        else
        {
            work->vox = -1;
        }

        TobcntGetResources_800C4AD0(work);
    }

    GM_Sound_80032C48(-0xFFFF02, 0);
    GM_Sound_80032C48(0x01FFFF0B, 0);
    sub_80032AEC(0, 63, 15);

    if (work->vox >= 0)
    {
        GM_VoxStream_80037E40(work->vox, 0x40000000);
    }

    GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_27;

    return &work->actor;
}
