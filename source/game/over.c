#include "over.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "linkvar.h"

extern GV_PAD           *GM_CurrentPadData;
GV_PAD *SECTION(".sbss") GM_CurrentPadData;

int GM_GameOverVox = -1;

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_DAEMON

#define NUM_LINES           120 // ((countof(over_logo_data)-1)/4)

#define OPTION_CONTINUE     0
#define OPTION_EXIT         1

#define PCX_GO_CONTINUE     0x669d  // GV_StrCode("GO_CONTINUE")
#define PCX_GO_EXIT         0x4d9a  // GV_StrCode("GO_EXIT")

#define FLARE_COLOR         MAKE_RGB0(0,64,128)

typedef struct _Work
{
    GV_ACT   actor;
    short    step;          // Step value controlling GAME OVER animation
    short    count;         // Count value controlling when animations/inputs are enabled
    short    option;        // 0 = CONTINUE, 1 = EXIT
    short    gradient;      // 64-step sweep controlling color of CONTINUE and EXIT buttons
    short    can_continue;  // Disables the CONTINUE option (e.g. when Snake dies during the torture sequence)
    POLY_G4  polys[2][12];
    LINE_G2  lines[2][NUM_LINES];
    DR_TPAGE anim_tpage[2];
    TILE     tiles[2];
    DR_TPAGE fade_tpage[2];
    DVECTOR  directions[NUM_LINES];
} Work;

/*---------------------------------------------------------------------------*/

STATIC short over_logo_data[] = {
    NUM_LINES,
/*-- X0   Y0   X1   Y1 --*/
     37,  88,  25, 104, /* 0 */
     25, 104,  31, 121, /* 1 */
     31, 121,  40, 121, /* 2 */
     40, 121,  32, 135, /* 3 */
     32, 135,  42, 135, /* 4 */
     69,  88,  37,  88, /* 5 */
     64,  96,  41,  96, /* 6 */
     41,  96,  35, 104, /* 7 */
     35, 104,  38, 113, /* 8 */
     38, 113,  45, 113, /* 9 */
     62, 100,  45, 100, /* 10 */
     45, 100,  40, 108, /* 11 */
     40, 108,  48, 108, /* 12 */
     48, 108,  45, 113, /* 13 */
     69,  88,  64,  96, /* 14 */
     55, 121,  65, 121, /* 15 */
     74,  88,  84,  88, /* 16 */
     67, 100,  85, 100, /* 17 */
     69,  96,  85,  96, /* 18 */
     67, 100,  55, 121, /* 19 */
     69,  96,  74,  88, /* 20 */
     84,  88,  85,  96, /* 21 */
     85, 100,  87, 121, /* 22 */
     87, 121,  78, 121, /* 23 */
     73, 108,  77, 108, /* 24 */
     78, 121,  77, 108, /* 25 */
     73, 108,  65, 121, /* 26 */
     62, 100,  42, 135, /* 27 */
     89, 121,  98, 121, /* 28 */
     97,  88, 108,  88, /* 29 */
    118,  88, 130,  88, /* 30 */
    122, 121, 113, 121, /* 31 */
    113, 121, 117, 104, /* 32 */
    117, 104, 108, 121, /* 33 */
    108, 121, 103, 121, /* 34 */
    103, 121, 102, 104, /* 35 */
    102, 104,  98, 121, /* 36 */
     95,  96, 108,  96, /* 37 */
    114,  96, 128,  96, /* 38 */
     94, 100, 108, 100, /* 39 */
    112, 100, 127, 100, /* 40 */
     97,  88,  95,  96, /* 41 */
     94, 100,  89, 121, /* 42 */
    108,  88, 108,  96, /* 43 */
    108, 100, 108, 108, /* 44 */
    112, 100, 108, 108, /* 45 */
    114,  96, 118,  88, /* 46 */
    127, 100, 122, 121, /* 47 */
    128,  96, 130,  88, /* 48 */
    134,  88, 156,  88, /* 49 */
    126, 121, 148, 121, /* 50 */
    132,  96, 154,  96, /* 51 */
    131, 100, 153, 100, /* 52 */
    138, 107, 151, 107, /* 53 */
    138, 107, 137, 113, /* 54 */
    150, 113, 137, 113, /* 55 */
    134,  88, 132,  96, /* 56 */
    131, 100, 126, 121, /* 57 */
    150, 113, 148, 121, /* 58 */
    151, 107, 153, 100, /* 59 */
    154,  96, 156,  88, /* 60 */
    173, 121, 199, 121, /* 61 */
    181,  88, 207,  88, /* 62 */
    179,  96, 205,  96, /* 63 */
    187, 100, 184, 113, /* 64 */
    184, 113, 192, 113, /* 65 */
    195, 100, 192, 113, /* 66 */
    207,  88, 205,  96, /* 67 */
    204, 100, 199, 121, /* 68 */
    181,  88, 179,  96, /* 69 */
    178, 100, 173, 121, /* 70 */
    178, 100, 187, 100, /* 71 */
    195, 100, 204, 100, /* 72 */
    213, 121, 224, 121, /* 73 */
    241,  88, 231,  88, /* 74 */
    210,  88, 219,  88, /* 75 */
    211,  96, 220,  96, /* 76 */
    211, 100, 220, 100, /* 77 */
    225, 100, 235, 100, /* 78 */
    227,  96, 237,  96, /* 79 */
    225, 100, 221, 108, /* 80 */
    231,  88, 227,  96, /* 81 */
    235, 100, 224, 121, /* 82 */
    237,  96, 241,  88, /* 83 */
    211, 100, 213, 121, /* 84 */
    210,  88, 211,  96, /* 85 */
    219,  88, 220,  96, /* 86 */
    220, 100, 221, 108, /* 87 */
    244,  88, 266,  88, /* 88 */
    236, 121, 258, 121, /* 89 */
    242,  96, 264,  96, /* 90 */
    241, 100, 263, 100, /* 91 */
    247, 113, 260, 113, /* 92 */
    248, 108, 261, 108, /* 93 */
    248, 108, 247, 113, /* 94 */
    244,  88, 242,  96, /* 95 */
    241, 100, 236, 121, /* 96 */
    263, 100, 261, 108, /* 97 */
    260, 113, 258, 121, /* 98 */
    266,  88, 264,  96, /* 99 */
    270,  88, 292,  88, /* 100 */
    268,  96, 286,  96, /* 101 */
    292,  88, 295,  97, /* 102 */
    267, 100, 282, 100, /* 103 */
    275, 107, 277, 107, /* 104 */
    262, 121, 272, 121, /* 105 */
    275, 107, 272, 121, /* 106 */
    277, 107, 285, 135, /* 107 */
    285, 135, 295, 135, /* 108 */
    286, 106, 295, 135, /* 109 */
    286, 106, 288, 106, /* 110 */
    288, 106, 295,  97, /* 111 */
    282, 100, 286,  96, /* 112 */
    267, 100, 262, 121, /* 113 */
    268,  96, 270,  88, /* 114 */
     67, 100,  55, 121, /* 115 */
     53, 125,  47, 135, /* 116 */
     53, 125, 279, 125, /* 117 */
    282, 135,  47, 135, /* 118 */
    282, 135, 279, 125  /* 119 */
};

/*---------------------------------------------------------------------------*/

static char *SetOptionPrim( char *buffer, short x, short y, int texture_id, unsigned int color, u_long *ot )
{
    DG_TEX   *tex;
    SPRT     *sprt;
    DR_TPAGE *tpage;

    tex = DG_GetTexture( texture_id );
    sprt = (SPRT *)buffer;
    tpage = (DR_TPAGE *)(buffer + sizeof(SPRT));

    setXY0( sprt, x, y );
    setUV0( sprt, tex->off_x, tex->off_y );
    setWH( sprt, tex->w + 1, tex->h + 1 );
    sprt->clut = tex->clut;
    LSTORE( color, &sprt->r0 );
    setSprt( sprt );
    addPrim( ot, sprt );

    setDrawTPage( tpage, 1, 0, tex->tpage );
    addPrim( ot, tpage );

    return (buffer + sizeof(SPRT) + sizeof(DR_TPAGE));
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

static void DrawAnimation(Work *work, u_long *ot)
{
    int       x0, y0;
    int       x1, y1;
    int       width, height;
    int       step;
    int       count;
    int       color1, color2, color3, color4, color5;
    DR_TPAGE *tpage;
    short    *lines;
    int       flag;
    void     *polys;
    DVECTOR  *directions;
    POLY_G4  *poly;
    LINE_G2  *line;

    step = work->step;

    lines = over_logo_data;
    count = over_logo_data[0];

    directions = work->directions;
    line = work->lines[GV_Clock];
    poly = work->polys[GV_Clock];

    lines++;

    if (step > 0)
    {
        if (step < count + 16)
        {
            work->step = step + 2;
        }
        else
        {
            work->step = 0;
        }
    }

    flag = 1;
    if (step == 0)
    {
        flag = 0;
        step = 16;
    }

    for (; count > 0; lines += 4, directions++, count--)
    {
        height = 0;
        width = 0;
        if (flag)
        {
            if (step < 8)
            {
                width = directions->vx >> step;
                height = directions->vy >> step;
                if (count % 4 == 2)
                {
                    width = -width;
                    height = -height;
                }
            }
            if (--step < 0)
            {
                break;
            }
        }

        x0 = lines[0];
        x1 = lines[2];
        x0 += width;
        color1 = x0 - 160;
        x1 += width * 2;
        color2 = x1 - 160;
        y0 = lines[1] + height;
        y1 = lines[3] + height * 2;

        setXY2(line, x0, y0, x1, y1);

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

        LSTORE(GetLineColor(color1, step), &line->r0);
        LSTORE(GetLineColor(color2, step), &line->r1);

        setLineG2(line);
        addPrim(ot, line);
        line++;

        if (step >= 8 && step <= 13)
        {
            width = -(directions->vy >> (step - 6));
            height = directions->vx >> (step - 6);

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
    }

    tpage = &work->anim_tpage[GV_Clock];
    setDrawTPage(tpage, 1, 1, getTPage(0, 1, 0, 0));
    addPrim(ot, tpage);

    if (work->step == 0)
    {
        if (work->gradient > 32)
        {
            color3 = 48 + (64 - work->gradient) * 4;
        }
        else
        {
            color3 = 48 + work->gradient * 4;
        }

        polys = work->polys[GV_Clock];

        if (work->can_continue)
        {
            if (work->option == OPTION_CONTINUE)
            {
                color4 = color3 << 8 | color3 << 16;
                color5 = 0x303000;
            }
            else
            {
                color4 = 0x303000;
                color5 = color3 << 8 | color3 << 16;
            }

            polys = SetOptionPrim(polys, 70, 126, PCX_GO_CONTINUE, color4, ot);
            SetOptionPrim(polys, 199, 126, PCX_GO_EXIT, color5, ot);
        }
        else
        {
            work->option = OPTION_EXIT;
            color5 = color3 << 8 | color3 << 16;
            SetOptionPrim(polys, 128, 126, PCX_GO_EXIT, color5, ot);
        }
    }
}

static void DrawBackgroundFade(Work *work, u_long *ot, int shade)
{
    TILE     *tile;
    DR_TPAGE *tpage;

    if (shade > 0xff)
    {
        shade = 0xff;
    }

    tile = &work->tiles[GV_Clock];
    LSTORE((shade << 16) | (shade << 8) | shade, &tile->r0);
    setTile(tile);
    setSemiTrans(tile, 1);
    setXY0(tile, 0, 0);
    setWH(tile, 320, 240);
    addPrim(ot, tile);

    tpage = &work->fade_tpage[GV_Clock];
    setDrawTPage(tpage, 1, 1, getTPage(0, 2, 0, 0));
    addPrim(ot, tpage);
}

/*---------------------------------------------------------------------------*/

static void Act( Work *work )
{
    u_long *ot;
    GV_PAD *pad;
    u_short press;
    int     shade;

    ot = (u_long *)DG_ChanlOTag(1);

    if (GV_PauseLevel & 8)
    {
        return;
    }

    if (work->count < 256)
    {
        DrawAnimation(work, ot);
        DrawBackgroundFade(work, ot, work->count * 2);

        if (work->count == NUM_LINES)
        {
            if (GM_GameOverVox >= 0)
            {
                GM_StreamPlayStart();
            }

            DG_ReloadPalette();
        }

        work->count += 3;

        if (work->count >= 256)
        {
            if (work->step > 0)
            {
                work->count = 255;
                return;
            }

            GV_PauseLevel |= 1;
            DG_FreeObjectQueue();
            DG_ReloadPalette();
            DG_SetRGB(0, 0, 0);
            DG_FrameRate = 2;
            work->count = 256;
            GM_GameStatus |= STATE_ALL_OFF;
        }
    }
    else if (work->count == 256)
    {
        pad = &GM_CurrentPadData[2];
        DrawAnimation(work, ot);
        GM_GameStatus &= ~(STATE_PADMASK | STATE_PADRELEASE | STATE_PADDEMO);
        press = pad->press;

        if (press & (PAD_START | PAD_CIRCLE))
        {
            work->count = 257;
            work->gradient = 32;

            if (work->option == OPTION_CONTINUE)
            {
                GM_SeSet3(0, 0x3f, SE_MENU_GUNSHOT);
            }
            else
            {
                GM_SeSet3(0, 0x3f, SE_MENU_EXIT);
            }

            return;
        }

        if (work->can_continue)
        {
            if ((work->option == OPTION_CONTINUE) && (press & PAD_RIGHT))
            {
                GM_SeSet3(0, 0x3f, SE_MENU_CURSOR);
                work->option = OPTION_EXIT;
                work->gradient = 0;
            }
            else if ((work->option == OPTION_EXIT) && (press & PAD_LEFT))
            {
                GM_SeSet3(0, 0x3f, SE_MENU_CURSOR);
                work->option = OPTION_CONTINUE;
                work->gradient = 0;
            }
        }

        work->gradient = (work->gradient + 1) % 64;
    }
    else
    {
        shade = MIN(work->count - 256, 255);
        DrawBackgroundFade(work, ot, shade);
        DrawAnimation(work, ot);

        work->count += 4;

        if (work->count > 542)
        {
            work->count = 542;

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

    GV_PauseLevel &= ~1;
    DG_RestartMainChanlSystem();
    GM_StreamPlayStop();
    GM_GameOverTimer = 0;
    if ( work->option == OPTION_CONTINUE )
    {
        GM_ContinueStart();
        return;
    }
    if ( ( GM_GameStatusFlag & 0x20 ) || ( GM_DifficultyFlag == DIFFICULTY_VERY_EASY ) )
    {
        GV_InitResidentMemory();
        GV_InitCacheSystem();
        DG_ClearResidentTexture();
        stage_name = "init";
        GM_GameStatusFlag &= ~0x20;
    }
    else
    {
        stage_name = "title";
    }
    GM_SetArea( GV_StrCode( stage_name ), stage_name );
    GM_LoadRequest = 0x81;
}

static void GetResources( Work *work )
{
    int     i;
    short   *lines;
    DVECTOR *directions;
    SVECTOR *scratch;

    i = over_logo_data[0];
    lines = &over_logo_data[1];
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

void *NewGameOver(int can_continue)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, &Act, &Die, "over.c");

        work->step = 1;
        work->count = 0;
        work->can_continue = can_continue;

        GetResources(work);

        if (GM_GameOverVox >= 0)
        {
            GM_VoxStream(GM_GameOverVox, 0x40000000);
        }
    }

    GM_SetSound(0xff000008, SD_ASYNC);
    GM_SetSound(0xff0000fe, SD_ASYNC);
    GM_SetSound(0x01ffff0b, SD_ASYNC);

    GM_SeSet3(0, 0x3f, SE_GAMEOVER);

    DG_FrameRate = 3;
    GM_GameStatus |= STATE_GAME_OVER;

    return (void *)work;
}
