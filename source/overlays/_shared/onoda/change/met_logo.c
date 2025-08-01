#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "sd/g_sound.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_MANAGER

#define NUM_LINES       108 // ((countof(mgs_logo_data)-1)/4)

#define PCX_MG_SOLID    0x3f37  // GV_StrCode("MG_SOLID")

#define FLARE_COLOR     MAKE_RGB0(0,64,128)

typedef struct _Work
{
    GV_ACT   actor;
    short    step;
    short    count;
    short    gradient;
    POLY_G4  polys[2][12];
    LINE_G2  lines[2][NUM_LINES];
    DR_TPAGE anim_tpage[2];
    TILE     tiles[2];
    DR_TPAGE fade_tpage[2];
    DVECTOR  directions[NUM_LINES];
    int      gradient_max;
    int     *exit;
} Work;

/*---------------------------------------------------------------------------*/

static short mgs_logo_data[] = {
    NUM_LINES,
/*--- X0     Y0     X1     Y1 ---*/
    0x0023,0x0058,0x0019,0x0087,    /* 0 */
    0x0019,0x0087,0x0021,0x0087,    /* 1 */
    0x0023,0x0058,0x002e,0x0058,    /* 2 */
    0x002e,0x0058,0x002e,0x006b,    /* 3 */
    0x002e,0x006b,0x0038,0x0058,    /* 4 */
    0x0038,0x0058,0x0043,0x0058,    /* 5 */
    0x0043,0x0058,0x003b,0x0079,    /* 6 */
    0x003b,0x0079,0x0033,0x0079,    /* 7 */
    0x0033,0x0079,0x0037,0x0068,    /* 8 */
    0x0037,0x0068,0x002f,0x0079,    /* 9 */
    0x002f,0x0079,0x0028,0x0079,    /* 10 */
    0x0028,0x0079,0x0028,0x0068,    /* 11 */
    0x0028,0x0068,0x0021,0x0087,    /* 12 */
    0x0047,0x0058,0x0045,0x0060,    /* 13 */
    0x0044,0x0064,0x003f,0x0079,    /* 14 */
    0x0055,0x0079,0x0057,0x0071,    /* 15 */
    0x0057,0x0071,0x004a,0x0071,    /* 16 */
    0x004a,0x0071,0x004b,0x006c,    /* 17 */
    0x004b,0x006c,0x0058,0x006c,    /* 18 */
    0x0058,0x006c,0x005a,0x0064,    /* 19 */
    0x005a,0x0064,0x0044,0x0064,    /* 20 */
    0x0045,0x0060,0x005b,0x0060,    /* 21 */
    0x005b,0x0060,0x005d,0x0058,    /* 22 */
    0x005d,0x0058,0x0047,0x0058,    /* 23 */
    0x003f,0x0079,0x0055,0x0079,    /* 24 */
    0x0060,0x0058,0x007a,0x0058,    /* 25 */
    0x007a,0x0058,0x0078,0x0060,    /* 26 */
    0x005e,0x0060,0x0067,0x0060,    /* 27 */
    0x0078,0x0060,0x0070,0x0060,    /* 28 */
    0x0067,0x0060,0x0062,0x0079,    /* 29 */
    0x0070,0x0060,0x006b,0x0079,    /* 30 */
    0x006b,0x0079,0x0062,0x0079,    /* 31 */
    0x0060,0x0058,0x005e,0x0060,    /* 32 */
    0x007b,0x0064,0x006f,0x0079,    /* 33 */
    0x006f,0x0079,0x0079,0x0079,    /* 34 */
    0x0079,0x0079,0x0081,0x006b,    /* 35 */
    0x0081,0x006b,0x0085,0x006b,    /* 36 */
    0x0085,0x006b,0x0086,0x0079,    /* 37 */
    0x0086,0x0079,0x008f,0x0079,    /* 38 */
    0x008f,0x0079,0x008d,0x0064,    /* 39 */
    0x007b,0x0064,0x008d,0x0064,    /* 40 */
    0x007d,0x0060,0x008d,0x0060,    /* 41 */
    0x008d,0x0060,0x008c,0x0058,    /* 42 */
    0x007d,0x0060,0x0082,0x0058,    /* 43 */
    0x0082,0x0058,0x008c,0x0058,    /* 44 */
    0x0091,0x0079,0x00a7,0x0079,    /* 45 */
    0x0091,0x0079,0x0098,0x0058,    /* 46 */
    0x0098,0x0058,0x00a1,0x0058,    /* 47 */
    0x00a1,0x0058,0x009c,0x0071,    /* 48 */
    0x009c,0x0071,0x00a9,0x0071,    /* 49 */
    0x00a9,0x0071,0x00a7,0x0079,    /* 50 */
    0x00ba,0x0058,0x00ad,0x0068,    /* 51 */
    0x00ad,0x0068,0x00b3,0x0079,    /* 52 */
    0x00b3,0x0079,0x00c8,0x0079,    /* 53 */
    0x00c8,0x0079,0x00cd,0x0064,    /* 54 */
    0x00cd,0x0064,0x00bd,0x0064,    /* 55 */
    0x00bd,0x0064,0x00bb,0x006c,    /* 56 */
    0x00bb,0x006c,0x00c2,0x006c,    /* 57 */
    0x00c2,0x006c,0x00c1,0x0071,    /* 58 */
    0x00c1,0x0071,0x00ba,0x0071,    /* 59 */
    0x00ba,0x0071,0x00b7,0x0068,    /* 60 */
    0x00b7,0x0068,0x00bd,0x0060,    /* 61 */
    0x00bd,0x0060,0x00ce,0x0060,    /* 62 */
    0x00ce,0x0060,0x00d0,0x0058,    /* 63 */
    0x00d0,0x0058,0x00ba,0x0058,    /* 64 */
    0x00d4,0x0058,0x00d2,0x0060,    /* 65 */
    0x00d1,0x0064,0x00cc,0x0079,    /* 66 */
    0x00cc,0x0079,0x00e2,0x0079,    /* 67 */
    0x00d1,0x0064,0x00e7,0x0064,    /* 68 */
    0x00d2,0x0060,0x00e8,0x0060,    /* 69 */
    0x00d4,0x0058,0x00ea,0x0058,    /* 70 */
    0x00ea,0x0058,0x00e8,0x0060,    /* 71 */
    0x00e7,0x0064,0x00e5,0x006c,    /* 72 */
    0x00e5,0x006c,0x00d8,0x006c,    /* 73 */
    0x00e2,0x0079,0x00e4,0x0071,    /* 74 */
    0x00e4,0x0071,0x00d7,0x0071,    /* 75 */
    0x00d8,0x006c,0x00d7,0x0071,    /* 76 */
    0x00e4,0x0079,0x00ee,0x0079,    /* 77 */
    0x00ee,0x0079,0x00f6,0x006c,    /* 78 */
    0x00f6,0x006c,0x00fa,0x006c,    /* 79 */
    0x00fa,0x006c,0x00fb,0x0079,    /* 80 */
    0x00fb,0x0079,0x0104,0x0079,    /* 81 */
    0x0104,0x0079,0x0102,0x0064,    /* 82 */
    0x0102,0x0064,0x00f0,0x0064,    /* 83 */
    0x00f2,0x0060,0x0102,0x0060,    /* 84 */
    0x0102,0x0060,0x0101,0x0058,    /* 85 */
    0x0101,0x0058,0x00f7,0x0058,    /* 86 */
    0x00f2,0x0060,0x00f7,0x0058,    /* 87 */
    0x00f0,0x0064,0x00e4,0x0079,    /* 88 */
    0x0106,0x0079,0x0110,0x0079,    /* 89 */
    0x010e,0x0058,0x0124,0x0058,    /* 90 */
    0x0124,0x0058,0x0127,0x0061,    /* 91 */
    0x0127,0x0061,0x0120,0x006a,    /* 92 */
    0x011e,0x006a,0x0127,0x0087,    /* 93 */
    0x0127,0x0087,0x011d,0x0087,    /* 94 */
    0x011d,0x0087,0x0115,0x006b,    /* 95 */
    0x0115,0x006b,0x0113,0x006b,    /* 96 */
    0x0113,0x006b,0x0110,0x0079,    /* 97 */
    0x010b,0x0064,0x011a,0x0064,    /* 98 */
    0x011a,0x0064,0x011e,0x0060,    /* 99 */
    0x011e,0x0060,0x010c,0x0060,    /* 100 */
    0x010e,0x0058,0x010c,0x0060,    /* 101 */
    0x010b,0x0064,0x0106,0x0079,    /* 102 */
    0x011e,0x006a,0x0120,0x006a,    /* 103 */
    0x0026,0x007d,0x0024,0x0087,    /* 104 */
    0x0117,0x007d,0x011a,0x0087,    /* 105 */
    0x0117,0x007d,0x0026,0x007d,    /* 106 */
    0x0024,0x0087,0x011a,0x0087     /* 107 */
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

static void DrawAnimation( Work *work, u_long *ot )
{
    int       x0, y0;
    int       x1, y1;
    int       width, height;
    int       step;
    int       count;
    int       color1, color2, color3;
    DR_TPAGE *tpage;
    short    *lines;
    int       flag;
    DVECTOR  *directions;
    LINE_G2  *line;
    POLY_G4  *poly;
    int       gradient;
    int       shade;

    step = work->step;
    lines = mgs_logo_data;
    count = mgs_logo_data[ 0 ];

    directions = work->directions;
    line = work->lines[ GV_Clock ];
    poly = work->polys[ GV_Clock ];

    lines++;

    if ( step > 0 )
    {
        if ( step < count + 16 )
        {
            work->step = step + 2;
        }
        else
        {
            work->step = 0;
        }
    }

    flag = 1;
    if ( step == 0 )
    {
        flag = 0;
        step = 16;
    }

    for ( ; count > 0; lines += 4, directions++, count-- )
    {
        height = 0;
        width = 0;

        if ( flag )
        {
            if ( step < 8 )
            {
                width = directions->vx >> step;
                height = directions->vy >> step;

                if ( ( count % 4 ) == 2 )
                {
                    width = -width;
                    height = -height;
                }
            }

            if ( --step < 0 )
            {
                break;
            }
        }

        x0 = lines[ 0 ];
        x1 = lines[ 2 ];

        x0 += width;
        color1 = x0 - 160;

        x1 += width * 2;
        color2 = x1 - 160;

        y0 = lines[ 1 ] + height;
        y1 = lines[ 3 ] + height * 2;

        setXY2(line, x0, y0, x1, y1);

        if ( color1 < 0 )
        {
            color1 = -color1;
        }

        if ( color2 < 0 )
        {
            color2 = -color2;
        }

        color1 = 255 - color1;
        color2 = 255 - color2;

        if ( color1 > 255 )
        {
            color1 = 255;
        }

        if ( color2 > 255 )
        {
            color2 = 255;
        }

        LSTORE( GetLineColor( color1, step ), &line->r0 );
        LSTORE( GetLineColor( color2, step ), &line->r1 );

        setLineG2( line );
        addPrim( ot, line );
        line++;

        if ( step >= 8 && step <= 13 )
        {
            width = -( directions->vy >> ( step - 6 ) );
            height = directions->vx >> ( step - 6 );

            setXY4( poly,
                x1 - width, y1 - height,
                x0 - width, y0 - height,
                ( x0 + x1 ) / 2,
                ( y0 + y1 ) / 2,
                x0 + width, y0 + height );

            LSTORE( COLOR_BLACK, &poly->r0 );
            LSTORE( COLOR_BLACK, &poly->r1 );
            LSTORE( FLARE_COLOR, &poly->r2 );
            LSTORE( COLOR_BLACK, &poly->r3 );

            setPolyG4( poly );
            setSemiTrans( poly, 1 );
            addPrim( ot, poly );
            poly++;

            setXY4( poly,
                x1 - width, y1 - height,
                x1 + width, y1 + height,
                ( x0 + x1 ) / 2,
                ( y0 + y1 ) / 2,
                x0 + width, y0 + height );

            LSTORE( COLOR_BLACK, &poly->r0 );
            LSTORE( COLOR_BLACK, &poly->r1 );
            LSTORE( FLARE_COLOR, &poly->r2 );
            LSTORE( COLOR_BLACK, &poly->r3 );

            setPolyG4( poly );
            setSemiTrans( poly, 1 );
            addPrim( ot, poly );
            poly++;
        }
    }

    tpage = &work->anim_tpage[ GV_Clock ];
    setDrawTPage( tpage, 1, 1, getTPage( 0, 1, 0, 0 ) );
    addPrim( ot, tpage );

    if ( work->step == 0 )
    {
        // Unused but asm doesn't match without it
        gradient = work->gradient;

        if ( work->gradient_max == 0 )
        {
            shade = work->gradient * 4;
        }
        else
        {
            shade = 160;
        }

        if ( work->gradient == 40 )
        {
            work->gradient_max = 1;
        }

        color3 = ( shade << 8 ) | ( shade << 16 );
        SetOptionPrim( (char *)work->polys[ GV_Clock ], 106, 126, PCX_MG_SOLID, color3, ot );
    }
}

static void DrawBackgroundFade( Work *work, u_long *ot, int shade )
{
    TILE     *tile;
    DR_TPAGE *tpage;

    tile = &work->tiles[ GV_Clock ];
    LSTORE( shade << 16 | shade << 8 | shade, &tile->r0 );
    setTile( tile );
    setSemiTrans( tile, 1 );
    setXY0( tile, 0, 0 );
    setWH( tile, 320, 240 );
    addPrim( ot, tile );

    tpage = &work->fade_tpage[ GV_Clock ];
    setDrawTPage( tpage, 1, 1, getTPage( 0, 2, 0, 0 ) );
    addPrim( ot, tpage );
}

/*---------------------------------------------------------------------------*/

static void Act( Work *work )
{
    u_long *ot;
    int     shade;

    DG_FrameRate = 3;

    ot = (u_long *)DG_ChanlOTag(1);

    if ( work->count < 256 )
    {
        DrawAnimation( work, ot );
        DrawBackgroundFade( work, ot, work->count );

        work->count += 3;
        if ( work->count >= 256 )
        {
            if ( work->step > 0 )
            {
                work->count = 255;
                return;
            }

            work->count = 256;
            GM_SeSet2( 0, 63, SE_LOGO_CHOIR );
        }
    }
    else if ( work->count == 256 )
    {
        DrawAnimation( work, ot );

        if ( work->gradient_max == 0 )
        {
            work->gradient++;
        }

        if ( *work->exit == 1 )
        {
            work->count = 257;
            work->gradient = 32;
        }
    }
    else
    {
        shade = MIN( work->count - 256, 255 );
        DrawBackgroundFade( work, ot, shade );
        DrawAnimation( work, ot );

        work->count += 4;
        if ( work->count > 542 )
        {
            work->count = 542;

            if ( GM_StreamStatus() == -1 )
            {
                GV_DestroyActor( &( work->actor ) );
            }
        }
    }
}

static void Die( Work *work )
{
    DG_FrameRate = 2;
}

static void GetResources( Work *work )
{
    int      i;
    short   *lines;
    DVECTOR *directions;
    SVECTOR *scratch;

    i = mgs_logo_data[0];
    lines = &mgs_logo_data[1];
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

void *NewMetalGearLogo( int *exit )
{
    Work *work;

    work = GV_NewActor( EXEC_LEVEL, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( &( work->actor ), Act, Die, "met_logo.c" );

        work->step = 1;
        work->count = 0;
        work->gradient = 0;

        work->gradient_max = 0;
        work->exit = exit;

        DG_FrameRate = 3;

        GM_SetSound( 0xff0000fe, SD_ASYNC );
        GM_SetSound( 0x01ffff0b, SD_ASYNC );
        GM_SeSet2( 0, 63, SE_GAMEOVER );

        GetResources( work );
    }

    return (void *)work;
}
