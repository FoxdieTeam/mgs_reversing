#include "tobcnt.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "strcode.h"

extern GV_PAD GV_PadData_800B05C0[4];

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_DAEMON

#define NUM_LINES       166 // ((countof(tobcnt_logo_data)-1)/4)

#define PCX_COMING_SOON 0x0abb  // GV_StrCode("COMING_SOON")

#define FLARE_COLOR     MAKE_RGB0(0,64,128)

typedef struct _Work
{
    GV_ACT   actor;
    short    state;
    short    time;
    short    timeout;
    short    gradient;
    int      vox;
    POLY_G4  polys[2][12];
    LINE_G2  lines[2][NUM_LINES];
    DR_TPAGE tpage[2];
    TILE     tile[2];
    DR_TPAGE tpage2[2];
    DVECTOR  directions[NUM_LINES];
} Work;

/*---------------------------------------------------------------------------*/

static short tobcnt_logo_data[] = {
    NUM_LINES,
/*-- X0   Y0   X1   Y1 --*/
     19,  93,  39,  93, /* 0 */
     19,  93,  18,  98, /* 1 */
     39,  93,  38,  98, /* 2 */
     31,  98,  38,  98, /* 3 */
     31,  98,  25, 129, /* 4 */
     25, 129,  19, 129, /* 5 */
     42,  93,  60,  93, /* 6 */
     42,  93,  41,  98, /* 7 */
     60,  93,  59,  98, /* 8 */
     41,  98,  59,  98, /* 9 */
     40, 102,  37, 117, /* 10 */
     37, 117,  55, 117, /* 11 */
     55, 117,  58, 102, /* 12 */
     40, 102,  46, 102, /* 13 */
     52, 102,  58, 102, /* 14 */
     44, 112,  46, 102, /* 15 */
     44, 112,  50, 112, /* 16 */
     52, 102,  50, 112, /* 17 */
     18,  98,  25,  98, /* 18 */
     25,  98,  19, 129, /* 19 */
     68,  98,  69,  93, /* 20 */
     69,  93,  85,  93, /* 21 */
     68,  98,  80,  98, /* 22 */
     77, 102,  67, 102, /* 23 */
     67, 102,  64, 117, /* 24 */
     64, 117,  79, 117, /* 25 */
     79, 117,  84, 113, /* 26 */
     85, 109,  82, 105, /* 27 */
     87,  98,  85,  93, /* 28 */
     87,  98,  82, 105, /* 29 */
     80,  98,  77, 102, /* 30 */
     71, 112,  76, 112, /* 31 */
     76, 112,  79, 110, /* 32 */
     71, 112,  72, 107, /* 33 */
     72, 107,  77, 107, /* 34 */
     79, 110,  77, 107, /* 35 */
     85, 109,  84, 113, /* 36 */
     86, 117, 102, 117, /* 37 */
     91,  93, 107,  93, /* 38 */
     90,  98, 106,  98, /* 39 */
     89, 102, 105, 102, /* 40 */
     89, 102,  86, 117, /* 41 */
     91,  93,  90,  98, /* 42 */
    107,  93, 106,  98, /* 43 */
    104, 107,  94, 107, /* 44 */
    105, 102, 104, 107, /* 45 */
     93, 112, 103, 112, /* 46 */
    103, 112, 102, 117, /* 47 */
     93, 112,  94, 107, /* 48 */
    122,  93, 135,  93, /* 49 */
    122,  93, 112, 105, /* 50 */
    130, 117, 116, 117, /* 51 */
    125,  98, 134,  98, /* 52 */
    135,  93, 134,  98, /* 53 */
    125,  98, 119, 105, /* 54 */
    119, 105, 121, 112, /* 55 */
    121, 112, 131, 112, /* 56 */
    131, 112, 130, 117, /* 57 */
    112, 105, 116, 117, /* 58 */
    157,  93, 139,  93, /* 59 */
    134, 117, 152, 117, /* 60 */
    138, 98,  156,  98, /* 61 */
    143, 102, 141, 112, /* 62 */
    141, 112, 147, 112, /* 63 */
    149, 102, 147, 112, /* 64 */
    137, 102, 143, 102, /* 65 */
    149, 102, 155, 102, /* 66 */
    139,  93, 138,  98, /* 67 */
    137, 102, 134, 117, /* 68 */
    155, 102, 152, 117, /* 69 */
    157,  93, 156,  98, /* 70 */
    161,  93, 160,  98, /* 71 */
    161,  93, 167,  93, /* 72 */
    170, 102, 172, 106, /* 73 */
    174,  98, 175,  93, /* 74 */
    175,  93, 181,  93, /* 75 */
    179, 102, 176, 117, /* 76 */
    156, 117, 162, 117, /* 77 */
    162, 117, 165, 103, /* 78 */
    165, 103, 171, 117, /* 79 */
    171, 117, 176, 117, /* 80 */
    160,  98, 169,  98, /* 81 */
    167,  93, 169,  98, /* 82 */
    159, 102, 170, 102, /* 83 */
    159, 102, 156, 117, /* 84 */
    174,  98, 180,  98, /* 85 */
    173, 102, 172, 106, /* 86 */
    173, 102, 179, 102, /* 87 */
    180,  98, 181,  93, /* 88 */
    184,  93, 183,  98, /* 89 */
    204,  93, 184,  93, /* 90 */
    204,  93, 203,  98, /* 91 */
    203,  98, 183,  98, /* 92 */
    189, 102, 186, 117, /* 93 */
    195, 102, 192, 117, /* 94 */
    186, 117, 192, 117, /* 95 */
    189, 102, 195, 102, /* 96 */
    205, 102, 202, 117, /* 97 */
    207,  93, 213,  93, /* 98 */
    211, 102, 208, 117, /* 99 */
    202, 117, 208, 117, /* 100 */
    206,  98, 212,  98, /* 101 */
    205, 102, 211, 102, /* 102 */
    207,  93, 206,  98, /* 103 */
    213,  93, 212,  98, /* 104 */
    215, 102, 212, 117, /* 105 */
    212, 117, 218, 117, /* 106 */
    218, 117, 221, 103, /* 107 */
    217,  93, 223,  93, /* 108 */
    223,  93, 225,  98, /* 109 */
    225,  98, 216,  98, /* 110 */
    215, 102, 226, 102, /* 111 */
    226, 102, 228, 106, /* 112 */
    221, 103, 227, 117, /* 113 */
    227, 117, 232, 117, /* 114 */
    228, 106, 229, 102, /* 115 */
    229, 102, 235, 102, /* 116 */
    235, 102, 232, 117, /* 117 */
    217,  93, 216,  98, /* 118 */
    230,  98, 236,  98, /* 119 */
    230,  98, 231,  93, /* 120 */
    236,  98, 237,  93, /* 121 */
    231,  93, 237,  93, /* 122 */
    239, 102, 236, 117, /* 123 */
    241,  93, 247,  93, /* 124 */
    236, 117, 254, 117, /* 125 */
    254, 117, 257, 102, /* 126 */
    243, 112, 249, 112, /* 127 */
    243, 112, 245, 102, /* 128 */
    249, 112, 251, 102, /* 129 */
    240,  98, 246,  98, /* 130 */
    252,  98, 258,  98, /* 131 */
    239, 102, 245, 102, /* 132 */
    251, 102, 257, 102, /* 133 */
    253,  93, 259,  93, /* 134 */
    241,  93, 240,  98, /* 135 */
    247,  93, 246,  98, /* 136 */
    253,  93, 252,  98, /* 137 */
    259,  93, 258,  98, /* 138 */
    258, 117, 274, 117, /* 139 */
    258, 117, 261, 102, /* 140 */
    263,  93, 279,  93, /* 141 */
    277, 102, 276, 107, /* 142 */
    262,  98, 278,  98, /* 143 */
    261, 102, 277, 102, /* 144 */
    263,  93, 262,  98, /* 145 */
    279,  93, 278,  98, /* 146 */
    266, 107, 276, 107, /* 147 */
    275, 112, 265, 112, /* 148 */
    266, 107, 265, 112, /* 149 */
    275, 112, 274, 117, /* 150 */
    281, 102, 278, 117, /* 151 */
    283,  93, 298,  93, /* 152 */
    298,  93, 302, 104, /* 153 */
    302, 104, 293, 117, /* 154 */
    293, 117, 278, 117, /* 155 */
    282,  98, 293,  98, /* 156 */
    293,  98, 295, 104, /* 157 */
    295, 104, 289, 112, /* 158 */
    289, 112, 285, 112, /* 159 */
    285, 112, 287, 102, /* 160 */
    281, 102, 287, 102, /* 161 */
    283,  93, 282,  98, /* 162 */
     30, 120,  28, 129, /* 163 */
     30, 120, 291, 120, /* 164 */
     28, 129, 285, 129  /* 165 */
};

short s01a_dword_800C381A = 0x800C;

/*---------------------------------------------------------------------------*/

static char *SetOptionPrim( char *buf, int x, int y, int name, unsigned int color, u_long *ot )
{
    DG_TEX   *tex;
    SPRT     *sprt;
    DR_TPAGE *tpage;

    tex = DG_GetTexture( name );

    sprt = (SPRT *)buf;
    setXY0( sprt, x, y );
    setUV0( sprt, tex->off_x, tex->off_y );
    setWH( sprt, tex->w + 1, tex->h + 1 );
    sprt->clut = tex->clut;
    LSTORE( color, &sprt->r0 );
    setSprt( sprt );
    addPrim( ot, sprt );

    tpage = (DR_TPAGE *)(buf + sizeof(SPRT));
    setDrawTPage( tpage, 1, 0, tex->tpage );
    addPrim( ot, tpage );

    return (buf + sizeof(SPRT) + sizeof(DR_TPAGE));
}

static int GetLineColor( int shade, int step )
{
    int r, gb;

    if ( step < 8 )
    {
        r = 128;
        gb = 255;
    }
    else
    {
        step = MIN( step - 8, 8 );
        r = 128 - step * 16;
        gb = 255 - ((255 - shade) * step) / 8;
    }

    return (r | gb << 8 | gb << 16);
}

/*---------------------------------------------------------------------------*/

static void Tobcnt_800C4204( Work *work, u_long *ot )
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
    lines = tobcnt_logo_data;
    count = tobcnt_logo_data[0];

    directions = work->directions;
    line = work->lines[GV_Clock];
    poly = work->polys[GV_Clock];

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

        setXY2(line, x0, y0, x1, y1);

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

        LSTORE(GetLineColor(color1, state), &line->r0);

        if (count < 3)
        {
            LSTORE(COLOR_BLACK, &line->r1);
        }
        else
        {
            LSTORE(GetLineColor(color2, state), &line->r1);
        }

        setLineG2(line);
        addPrim(ot, line);
        line++;

        if (state >= 8 && state <= 13)
        {
            width = -(directions->vy >> (state - 6));
            height = directions->vx >> (state - 6);

            setXY4(poly,
                x1 - width, y1 - height,
                x0 - width, y0 - height,
                (x0 + x1) / 2,
                (y0 + y1) / 2,
                x0 + width, y0 + height);

            LSTORE(COLOR_BLACK, &poly->r0);
            LSTORE(COLOR_BLACK, &poly->r1);
            LSTORE(FLARE_COLOR, &poly->r2);
            LSTORE(COLOR_BLACK, &poly->r3);

            setPolyG4(poly);
            setSemiTrans(poly, 1);
            addPrim(ot, poly);
            poly++;

            setXY4(poly,
                x1 - width, y1 - height,
                x1 + width, y1 + height,
                (x0 + x1) / 2,
                (y0 + y1) / 2,
                x0 + width, y0 + height);

            LSTORE(COLOR_BLACK, &poly->r0);
            LSTORE(COLOR_BLACK, &poly->r1);
            LSTORE(FLARE_COLOR, &poly->r2);
            LSTORE(COLOR_BLACK, &poly->r3);

            setPolyG4(poly);
            setSemiTrans(poly, 1);
            addPrim(ot, poly);
            poly++;
        }

        lines += 4;
        directions++;
    }

    tpage = &work->tpage[GV_Clock];
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
        SetOptionPrim( (char *)work->polys[GV_Clock], 114, 121, PCX_COMING_SOON, color3, ot );
    }
}

static void Tobcnt_800C4750(Work *work, u_long *ot, int shade)
{
    TILE     *tile;
    DR_TPAGE *tpage;

    tile = &work->tile[GV_Clock];
    LSTORE((shade << 16) | (shade << 8) | shade, &tile->r0);
    setTile(tile);
    setSemiTrans(tile, 1);
    setXY0(tile, 0, 0);
    setWH(tile, 320, 240);
    addPrim(ot, tile);

    tpage = &work->tpage2[GV_Clock];
    setDrawTPage(tpage, 1, 1, getTPage(0, 2, 0, 0));
    addPrim(ot, tpage);
}

/*---------------------------------------------------------------------------*/

static void Act( Work *work )
{
    u_long *ot;
    GV_PAD *pad;
    int     shade;

    ot = (u_long *)DG_ChanlOTag(1);

    if (work->time < 256)
    {
        Tobcnt_800C4204(work, ot);
        Tobcnt_800C4750(work, ot, work->time);

        if ((work->time == 120) && (work->vox >= 0))
        {
            GM_StreamPlayStart();
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

                GV_PauseLevel |= 1;
                DG_FreeObjectQueue();
                GM_GameStatus |= STATE_ALL_OFF;
            }
        }
    }
    else if (work->time == 256)
    {
        Tobcnt_800C4204(work, ot);

        pad = &GV_PadData_800B05C0[0];
        GM_GameStatus &= ~(STATE_PADRELEASE | STATE_PADMASK);

        if ((pad->press & (PAD_START | PAD_CIRCLE | PAD_TRIANGLE)) || (--work->timeout < 0))
        {
            /* did the user press skip? */
            if (work->timeout > 0)
            {
                GM_SeSet3(0, 63, SE_MENU_EXIT);
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
        shade = MIN(work->time - 256, 255);
        Tobcnt_800C4750(work, ot, shade);
        Tobcnt_800C4204(work, ot);

        work->time += 4;
        if (work->time > 542)
        {
            work->time = 542;

            if (GM_StreamStatus() == -1)
            {
                GV_DestroyActor(&work->actor);
            }
        }
    }
}

static void Die( Work *work )
{
    char *stage_name;

    stage_name = "title";

    GV_PauseLevel &= ~1;
    DG_RestartMainChanlSystem();
    GM_StreamPlayStop();

    GM_SetArea(GV_StrCode(stage_name), stage_name);
    GM_LoadRequest = 0x81;
    GM_GameOverTimer = 0;
}

static void GetResources( Work *work )
{
    int      i;
    short   *lines;
    DVECTOR *directions;
    SVECTOR *scratch;

    i = tobcnt_logo_data[0];
    lines = tobcnt_logo_data + 1;
    directions = work->directions;

    ((SVECTOR *)getScratchAddr(0))->vz = 0;

    for (; i > 0; lines += 4, directions++, i--)
    {
        scratch = (SVECTOR *)getScratchAddr(0);
        scratch[0].vx = lines[0] - lines[2];
        scratch[0].vy = lines[1] - lines[3];

        VectorNormalSS(&scratch[0], &scratch[1]);

        directions->vx = -scratch[1].vx / 8;
        directions->vy = -scratch[1].vy / 8;
    }
}

/*---------------------------------------------------------------------------*/

void *NewToBeContinued(int name, int where, int argc, char **argv)
{
    Work *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "tobcnt.c");

        work->state = 1;
        work->time = 0;

        if (GCL_GetOption('v'))
        {
            work->vox = GCL_StrToInt(GCL_GetParamResult());
        }
        else
        {
            work->vox = -1;
        }

        GetResources(work);
    }

    GM_SetSound(0xff0000fe, SD_ASYNC);
    GM_SetSound(0x01ffff0b, SD_ASYNC);
    GM_SeSet3(0, 63, SE_GAMEOVER);

    if (work->vox >= 0)
    {
        GM_VoxStream(work->vox, 0x40000000);
    }

    GM_GameStatus |= STATE_GAME_OVER;

    return (void *)work;
}
