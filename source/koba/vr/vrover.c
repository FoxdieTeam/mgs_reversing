#include "vrover.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "sound/sd_cli.h"

/*---------------------------------------------------------------------------*/
// VR-DISC revision of game/over.c: the "GAME OVER" screen of the VR missions

// The game over voice of the VR missions (set by koba/vr/vr.c); the main executable has its own GM_GameOverVox
int GM_VrGameOverVox = -1;

/*---------------------------------------------------------------------------*/

#define NUM_LINES           161 // ((countof(vrover_logo_data)-1)/4)

#define OPTION_CONTINUE     0
#define OPTION_EXIT         1

#define PCX_GO_TRY          0x33db  // GV_StrCode("go_try")
#define PCX_GO_EXIT         0x4d9a  // GV_StrCode("GO_EXIT")

#define FLARE_COLOR         MAKE_RGB0(0,64,128)

// The VR-DISC has its own sound effect table
#define VROVER_SE_GAMEOVER  15
#define VROVER_SE_CURSOR    31
#define VROVER_SE_EXIT      33
#define VROVER_SE_CONTINUE  102
#define VROVER_SE_BIKKURI1  128     // see BIKKURI_FLAG_* (exact meaning not known yet)
#define VROVER_SE_BIKKURI2  130

typedef struct _Work
{
    GV_ACT   actor;
    short    step;          // Step value controlling GAME OVER animation
    short    count;         // Count value controlling when animations/inputs are enabled
    short    option;        // 0 = CONTINUE, 1 = EXIT
    short    gradient;      // 64-step sweep controlling color of CONTINUE and EXIT buttons
    short    exit_only;     // 1: only the EXIT option is offered
    char    *retry_var;     // GCL variable that keeps its value when the mission is retried
    POLY_G4  polys[2][12];
    LINE_G2  lines[2][NUM_LINES];
    DR_TPAGE anim_tpage[2];
    TILE     tiles[2];
    DR_TPAGE fade_tpage[2];
    DVECTOR  directions[NUM_LINES];
} Work;

/*---------------------------------------------------------------------------*/

STATIC short vrover_logo_data[] = {
    NUM_LINES,
/*-- X0   Y0   X1   Y1 --*/
     32,  93,  24, 132, /* 0 */
     32,  93,  40,  93, /* 1 */
     40,  93,  41, 107, /* 2 */
     41, 107,  50,  93, /* 3 */
     50,  93,  57,  93, /* 4 */
     45, 118,  52, 118, /* 5 */
     57,  93,  52, 118, /* 6 */
     45, 118,  47, 108, /* 7 */
     41, 118,  37, 118, /* 8 */
     41, 118,  47, 108, /* 9 */
     37, 118,  36, 108, /* 10 */
     36, 108,  31, 132, /* 11 */
     31, 132,  24, 132, /* 12 */
     58, 102,  55, 118, /* 13 */
     60,  93,  67,  93, /* 14 */
     65, 102,  62, 118, /* 15 */
     62, 118,  55, 118, /* 16 */
     58, 102,  65, 102, /* 17 */
     67,  93,  66,  99, /* 18 */
     60,  93,  59,  99, /* 19 */
     59,  99,  66,  99, /* 20 */
     71,  93,  68,  97, /* 21 */
     69, 102,  70, 108, /* 22 */
     71,  93,  87,  93, /* 23 */
     87,  93,  86,  99, /* 24 */
     86,  99,  68,  99, /* 25 */
     68,  97,  68,  99, /* 26 */
     69, 102,  76, 102, /* 27 */
     76, 102,  77, 104, /* 28 */
     77, 104,  84, 104, /* 29 */
     84, 104,  86, 111, /* 30 */
     86, 111,  81, 118, /* 31 */
     81, 118,  66, 118, /* 32 */
     66, 118,  67, 112, /* 33 */
     67, 112,  78, 112, /* 34 */
     78, 112,  79, 111, /* 35 */
     79, 111,  78, 108, /* 36 */
     78, 108,  70, 108, /* 37 */
     88,  99, 106,  99, /* 38 */
     88,  99,  88,  97, /* 39 */
     88,  97,  91,  93, /* 40 */
     91,  93, 107,  93, /* 41 */
    107,  93, 106,  99, /* 42 */
     89, 102,  96, 102, /* 43 */
     89, 102,  90, 108, /* 44 */
     96, 102,  97, 104, /* 45 */
     97, 104, 104, 104, /* 46 */
    104, 104, 106, 111, /* 47 */
    106, 111, 101, 118, /* 48 */
    101, 118,  86, 118, /* 49 */
     86, 118,  87, 112, /* 50 */
     90, 108,  98, 108, /* 51 */
     98, 108,  99, 111, /* 52 */
     99, 111,  98, 112, /* 53 */
     98, 112,  87, 112, /* 54 */
    109, 102, 106, 118, /* 55 */
    111,  93, 118,  93, /* 56 */
    116, 102, 113, 118, /* 57 */
    113, 118, 106, 118, /* 58 */
    110,  99, 117,  99, /* 59 */
    109, 102, 116, 102, /* 60 */
    110,  99, 111,  93, /* 61 */
    117,  99, 118,  93, /* 62 */
    119, 102, 116, 118, /* 63 */
    121,  93, 141,  93, /* 64 */
    139, 102, 136, 118, /* 65 */
    116, 118, 136, 118, /* 66 */
    120,  99, 140,  99, /* 67 */
    119, 102, 126, 102, /* 68 */
    126, 102, 124, 112, /* 69 */
    124, 112, 130, 112, /* 70 */
    130, 112, 132, 102, /* 71 */
    132, 102, 139, 102, /* 72 */
    141,  93, 140,  99, /* 73 */
    121,  93, 120,  99, /* 74 */
    142, 102, 139, 118, /* 75 */
    144,  93, 152,  93, /* 76 */
    152,  93, 153,  99, /* 77 */
    143,  99, 153,  99, /* 78 */
    142, 102, 154, 102, /* 79 */
    154, 102, 155, 106, /* 80 */
    155, 106, 156, 102, /* 81 */
    157,  99, 158,  93, /* 82 */
    158,  93, 165,  93, /* 83 */
    165,  93, 164,  99, /* 84 */
    164,  99, 157,  99, /* 85 */
    156, 102, 163, 102, /* 86 */
    163, 102, 160, 118, /* 87 */
    139, 118, 146, 118, /* 88 */
    146, 118, 149, 103, /* 89 */
    149, 103, 153, 118, /* 90 */
    153, 118, 160, 118, /* 91 */
    143,  99, 144,  93, /* 92 */
    179,  93, 178,  99, /* 93 */
    179,  93, 197,  93, /* 94 */
    197,  93, 196,  99, /* 95 */
    196,  99, 178,  99, /* 96 */
    177, 102, 174, 118, /* 97 */
    177, 102, 195, 102, /* 98 */
    195, 102, 194, 108, /* 99 */
    194, 108, 182, 108, /* 100 */
    182, 108, 180, 118, /* 101 */
    180, 118, 174, 118, /* 102 */
    200, 102, 191, 118, /* 103 */
    205,  93, 212,  93, /* 104 */
    212,  93, 213,  99, /* 105 */
    191, 118, 199, 118, /* 106 */
    199, 118, 204, 108, /* 107 */
    204, 108, 207, 108, /* 108 */
    207, 108, 208, 118, /* 109 */
    208, 118, 215, 118, /* 110 */
    202,  99, 213,  99, /* 111 */
    200, 102, 213, 102, /* 112 */
    202,  99, 205,  93, /* 113 */
    213, 102, 215, 118, /* 114 */
    222,  93, 221,  99, /* 115 */
    222,  93, 229,  93, /* 116 */
    229,  93, 228,  99, /* 117 */
    224, 118, 217, 118, /* 118 */
    221,  99, 228,  99, /* 119 */
    220, 102, 227, 102, /* 120 */
    220, 102, 217, 118, /* 121 */
    227, 102, 224, 118, /* 122 */
    230, 102, 227, 118, /* 123 */
    232,  93, 239,  93, /* 124 */
    239,  93, 238,  99, /* 125 */
    227, 118, 245, 118, /* 126 */
    245, 118, 246, 112, /* 127 */
    246, 112, 235, 112, /* 128 */
    252,  99, 253,  93, /* 129 */
    253,  93, 271,  93, /* 130 */
    231,  99, 238,  99, /* 131 */
    230, 102, 237, 102, /* 132 */
    232,  93, 231,  99, /* 133 */
    237, 102, 235, 112, /* 134 */
    257, 108, 256, 112, /* 135 */
    270,  99, 252,  99, /* 136 */
    251, 102, 269, 102, /* 137 */
    269, 102, 268, 108, /* 138 */
    268, 108, 257, 108, /* 139 */
    248, 118, 266, 118, /* 140 */
    266, 118, 267, 112, /* 141 */
    267, 112, 256, 112, /* 142 */
    251, 102, 248, 118, /* 143 */
    274,  93, 273,  99, /* 144 */
    274,  93, 288,  93, /* 145 */
    288,  93, 293, 104, /* 146 */
    293, 104, 283, 118, /* 147 */
    269, 118, 283, 118, /* 148 */
    272, 102, 279, 102, /* 149 */
    279, 102, 277, 112, /* 150 */
    277, 112, 279, 112, /* 151 */
    279, 112, 285, 104, /* 152 */
    273,  99, 283,  99, /* 153 */
    283,  99, 285, 104, /* 154 */
    272, 102, 269, 118, /* 155 */
     36, 122,  34, 132, /* 156 */
    247, 122,  36, 122, /* 157 */
    247, 122, 280, 122, /* 158 */
     34, 132, 240, 132, /* 159 */
    240, 132, 273, 132  /* 160 */
};

/*---------------------------------------------------------------------------*/

// Defined by enemy/command.c (VR revision): flags of the enemies' "!" (bikkuri) reactions
extern int bikkuri_flag;

// When BIKKURI_FLAG_SE is set the game over screen plays VROVER_SE_BIKKURI1 (BIKKURI_FLAG_SE1)
// or VROVER_SE_BIKKURI2 (BIKKURI_FLAG_SE2) after 10 frames
#define BIKKURI_FLAG_SE         0x1000
#define BIKKURI_FLAG_SE1        0x10
#define BIKKURI_FLAG_SE2        0xe0

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

    return MAKE_RGB(r, gb, gb);
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

    lines = vrover_logo_data;
    count = vrover_logo_data[0];

    directions = work->directions;
    line = work->lines[GV_Clock];
    poly = work->polys[GV_Clock];

    lines++;

    if (step > 0)
    {
        if (step < count + 16)
        {
            work->step = step + 3;
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
        x1 += width * 2;
        color1 = x0 - 160;
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

        if (count == 1 || count == 3)
        {
            LSTORE(COLOR_BLACK, &line->r1);
        }
        else
        {
            LSTORE(GetLineColor(color2, step), &line->r1);
        }

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

        polys = work->polys[GV_Clock];

        if (work->exit_only != 1)
        {
            polys = SetOptionPrim(polys, 66, 123, PCX_GO_TRY, color4, ot);
            SetOptionPrim(polys, 191, 123, PCX_GO_EXIT, color5, ot);
        }
        else
        {
            SetOptionPrim(polys, 135, 123, PCX_GO_EXIT, color5, ot);
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
    setWH(tile, SCREEN_WIDTH, SCREEN_HEIGHT);
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

    GM_GameOverTimer = 2;

    ot = DG_ChanlOTag(1);

    if (work->count < 256)
    {
        DrawAnimation(work, ot);
        DrawBackgroundFade(work, ot, work->count * 2);

        if (work->count == 120)
        {
            if (GM_VrGameOverVox >= 0)
            {
                GM_StreamPlayStart();
            }

            GM_SetSound(0x01000003, SD_ASYNC);
        }

        if (work->count == 30 && (bikkuri_flag & BIKKURI_FLAG_SE))
        {
            if (bikkuri_flag & BIKKURI_FLAG_SE1)
            {
                GM_SeSet3(0, 0x3f, VROVER_SE_BIKKURI1);
            }
            else if (bikkuri_flag & BIKKURI_FLAG_SE2)
            {
                GM_SeSet3(0, 0x3f, VROVER_SE_BIKKURI2);
            }
        }

        work->count += 3;

        if (work->count >= 256)
        {
            if (work->step > 0)
            {
                work->count = 255;
                return;
            }

            GV_PauseLevel |= GV_PAUSE_STOP;
            DG_StopMainChanlSystem();
            DG_ReloadPalette();
            DG_SetBackGroundColor(0, 0, 0);
            DG_FrameRate = 2;
            work->count = 256;
            GM_GameStatus |= STATE_ALL_OFF;
        }
    }
    else if (work->count == 256)
    {
        DrawAnimation(work, ot);
        pad = &GV_PadData[2];
        GM_GameStatus &= ~(STATE_PADMASK | STATE_PADRELEASE | STATE_PADDEMO);
        press = pad->press;

        if (press & (PAD_START | PAD_CIRCLE))
        {
            work->count = 257;
            work->gradient = 32;

            if (work->option == OPTION_CONTINUE)
            {
                GM_SeSet3(0, 0x3f, VROVER_SE_CONTINUE);
            }
            else
            {
                GM_SeSet3(0, 0x3f, VROVER_SE_EXIT);
            }

            return;
        }

        if (work->exit_only != 1)
        {
            if ((work->option == OPTION_CONTINUE) && (press & PAD_RIGHT))
            {
                GM_SeSet3(0, 0x3f, VROVER_SE_CURSOR);
                work->option = OPTION_EXIT;
                work->gradient = 0;
            }
            else if ((work->option == OPTION_EXIT) && (press & PAD_LEFT))
            {
                GM_SeSet3(0, 0x3f, VROVER_SE_CURSOR);
                work->option = OPTION_CONTINUE;
                work->gradient = 0;
            }
        }
        else
        {
            work->option = OPTION_EXIT;
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
    int value;

    GV_PauseLevel &= ~GV_PAUSE_STOP;
    DG_RestartMainChanlSystem();
    GM_StreamPlayStop();
    GM_GameOverTimer = 0;

    if ( work->option == OPTION_CONTINUE )
    {
        if ( work->retry_var )
        {
            value = GCL_StrToInt( work->retry_var );
            GM_ContinueStart();
            GCL_SetVar( work->retry_var, value );
            return;
        }
    }
    else
    {
        GM_SetArea( GV_StrCode( "selectvr" ), "selectvr" );
    }

    GM_LoadRequest = 0x81;
}

static void GetResources( Work *work )
{
    int     i;
    short   *lines;
    DVECTOR *directions;
    SVECTOR *scratch;

    i = vrover_logo_data[0];
    lines = &vrover_logo_data[1];
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

void *NewVrOver(int exit_only, char *retry_var)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_DAEMON, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, &Act, &Die, "vrover.c");

        work->step = 1;
        work->count = 0;
        work->exit_only = exit_only;
        work->retry_var = retry_var;

        GetResources(work);

        if (GM_VrGameOverVox >= 0)
        {
            GM_VoxStream(GM_VrGameOverVox, 0x40000000);
        }
    }

    GM_SetSound(0xff0000fe, SD_ASYNC);
    GM_SetSound(0x01ffff0a, SD_ASYNC);

    GM_SeSet3(0, 0x3f, VROVER_SE_GAMEOVER);

    DG_FrameRate = 3;
    GM_GameStatus |= STATE_GAME_OVER;

    return (void *)work;
}
