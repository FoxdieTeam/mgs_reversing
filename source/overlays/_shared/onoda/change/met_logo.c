#include "common.h"
#include "game/game.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "sd/g_sound.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_MANAGER

typedef struct _Work
{
    GV_ACT   actor;
    short    step;
    short    sequence;
    short    gradient;
    POLY_G4  polys[2][12];
    LINE_G2  lines[2][108];
    DR_TPAGE tpages[2];
    TILE     tiles[2];
    DR_TPAGE tpages2[2];
    DVECTOR  directions[108];
    int      f1658;
    int     *f165C;
} Work;

/*---------------------------------------------------------------------------*/

static short met_logo_lines_800C32E8[] = {
    108, // table length
    0x0023, 0x0058, 0x0019, 0x0087, 0x0019, 0x0087, 0x0021,
    0x0087, 0x0023, 0x0058, 0x002e, 0x0058, 0x002e, 0x0058,
    0x002e, 0x006b, 0x002e, 0x006b, 0x0038, 0x0058, 0x0038,
    0x0058, 0x0043, 0x0058, 0x0043, 0x0058, 0x003b, 0x0079,
    0x003b, 0x0079, 0x0033, 0x0079, 0x0033, 0x0079, 0x0037,
    0x0068, 0x0037, 0x0068, 0x002f, 0x0079, 0x002f, 0x0079,
    0x0028, 0x0079, 0x0028, 0x0079, 0x0028, 0x0068, 0x0028,
    0x0068, 0x0021, 0x0087, 0x0047, 0x0058, 0x0045, 0x0060,
    0x0044, 0x0064, 0x003f, 0x0079, 0x0055, 0x0079, 0x0057,
    0x0071, 0x0057, 0x0071, 0x004a, 0x0071, 0x004a, 0x0071,
    0x004b, 0x006c, 0x004b, 0x006c, 0x0058, 0x006c, 0x0058,
    0x006c, 0x005a, 0x0064, 0x005a, 0x0064, 0x0044, 0x0064,
    0x0045, 0x0060, 0x005b, 0x0060, 0x005b, 0x0060, 0x005d,
    0x0058, 0x005d, 0x0058, 0x0047, 0x0058, 0x003f, 0x0079,
    0x0055, 0x0079, 0x0060, 0x0058, 0x007a, 0x0058, 0x007a,
    0x0058, 0x0078, 0x0060, 0x005e, 0x0060, 0x0067, 0x0060,
    0x0078, 0x0060, 0x0070, 0x0060, 0x0067, 0x0060, 0x0062,
    0x0079, 0x0070, 0x0060, 0x006b, 0x0079, 0x006b, 0x0079,
    0x0062, 0x0079, 0x0060, 0x0058, 0x005e, 0x0060, 0x007b,
    0x0064, 0x006f, 0x0079, 0x006f, 0x0079, 0x0079, 0x0079,
    0x0079, 0x0079, 0x0081, 0x006b, 0x0081, 0x006b, 0x0085,
    0x006b, 0x0085, 0x006b, 0x0086, 0x0079, 0x0086, 0x0079,
    0x008f, 0x0079, 0x008f, 0x0079, 0x008d, 0x0064, 0x007b,
    0x0064, 0x008d, 0x0064, 0x007d, 0x0060, 0x008d, 0x0060,
    0x008d, 0x0060, 0x008c, 0x0058, 0x007d, 0x0060, 0x0082,
    0x0058, 0x0082, 0x0058, 0x008c, 0x0058, 0x0091, 0x0079,
    0x00a7, 0x0079, 0x0091, 0x0079, 0x0098, 0x0058, 0x0098,
    0x0058, 0x00a1, 0x0058, 0x00a1, 0x0058, 0x009c, 0x0071,
    0x009c, 0x0071, 0x00a9, 0x0071, 0x00a9, 0x0071, 0x00a7,
    0x0079, 0x00ba, 0x0058, 0x00ad, 0x0068, 0x00ad, 0x0068,
    0x00b3, 0x0079, 0x00b3, 0x0079, 0x00c8, 0x0079, 0x00c8,
    0x0079, 0x00cd, 0x0064, 0x00cd, 0x0064, 0x00bd, 0x0064,
    0x00bd, 0x0064, 0x00bb, 0x006c, 0x00bb, 0x006c, 0x00c2,
    0x006c, 0x00c2, 0x006c, 0x00c1, 0x0071, 0x00c1, 0x0071,
    0x00ba, 0x0071, 0x00ba, 0x0071, 0x00b7, 0x0068, 0x00b7,
    0x0068, 0x00bd, 0x0060, 0x00bd, 0x0060, 0x00ce, 0x0060,
    0x00ce, 0x0060, 0x00d0, 0x0058, 0x00d0, 0x0058, 0x00ba,
    0x0058, 0x00d4, 0x0058, 0x00d2, 0x0060, 0x00d1, 0x0064,
    0x00cc, 0x0079, 0x00cc, 0x0079, 0x00e2, 0x0079, 0x00d1,
    0x0064, 0x00e7, 0x0064, 0x00d2, 0x0060, 0x00e8, 0x0060,
    0x00d4, 0x0058, 0x00ea, 0x0058, 0x00ea, 0x0058, 0x00e8,
    0x0060, 0x00e7, 0x0064, 0x00e5, 0x006c, 0x00e5, 0x006c,
    0x00d8, 0x006c, 0x00e2, 0x0079, 0x00e4, 0x0071, 0x00e4,
    0x0071, 0x00d7, 0x0071, 0x00d8, 0x006c, 0x00d7, 0x0071,
    0x00e4, 0x0079, 0x00ee, 0x0079, 0x00ee, 0x0079, 0x00f6,
    0x006c, 0x00f6, 0x006c, 0x00fa, 0x006c, 0x00fa, 0x006c,
    0x00fb, 0x0079, 0x00fb, 0x0079, 0x0104, 0x0079, 0x0104,
    0x0079, 0x0102, 0x0064, 0x0102, 0x0064, 0x00f0, 0x0064,
    0x00f2, 0x0060, 0x0102, 0x0060, 0x0102, 0x0060, 0x0101,
    0x0058, 0x0101, 0x0058, 0x00f7, 0x0058, 0x00f2, 0x0060,
    0x00f7, 0x0058, 0x00f0, 0x0064, 0x00e4, 0x0079, 0x0106,
    0x0079, 0x0110, 0x0079, 0x010e, 0x0058, 0x0124, 0x0058,
    0x0124, 0x0058, 0x0127, 0x0061, 0x0127, 0x0061, 0x0120,
    0x006a, 0x011e, 0x006a, 0x0127, 0x0087, 0x0127, 0x0087,
    0x011d, 0x0087, 0x011d, 0x0087, 0x0115, 0x006b, 0x0115,
    0x006b, 0x0113, 0x006b, 0x0113, 0x006b, 0x0110, 0x0079,
    0x010b, 0x0064, 0x011a, 0x0064, 0x011a, 0x0064, 0x011e,
    0x0060, 0x011e, 0x0060, 0x010c, 0x0060, 0x010e, 0x0058,
    0x010c, 0x0060, 0x010b, 0x0064, 0x0106, 0x0079, 0x011e,
    0x006a, 0x0120, 0x006a, 0x0026, 0x007d, 0x0024, 0x0087,
    0x0117, 0x007d, 0x011a, 0x0087, 0x0117, 0x007d, 0x0026,
    0x007d, 0x0024, 0x0087, 0x011a, 0x0087
};

/*---------------------------------------------------------------------------*/

static char *MetLogo_800C5060( char *buffer, short x, short y, int texture, unsigned int color, char *ot )
{
    DG_TEX   *tex;
    SPRT     *sprt;
    DR_TPAGE *tpage;

    tex = DG_GetTexture( texture );
    sprt = (SPRT *)buffer;
    tpage = (DR_TPAGE *)(buffer + sizeof(SPRT));

    sprt->x0 = x;
    sprt->y0 = y;
    sprt->u0 = tex->off_x;
    sprt->v0 = tex->off_y;
    sprt->w = tex->w + 1;
    sprt->h = tex->h + 1;
    sprt->clut = tex->clut;
    LSTORE( color, &sprt->r0 );
    setSprt( sprt );
    addPrim( ot, sprt );

    setDrawTPage( tpage, 1, 0, tex->tpage );
    addPrim( ot, tpage );

    return buffer + sizeof(SPRT) + sizeof(DR_TPAGE);
}

static int MetLogo_800C5190( int shade, int step )
{
    int r, gb;

    if ( step < 8 )
    {
        r = 128;
        gb = 255;
    }
    else
    {
        step -= 8;

        if ( step > 8 )
        {
            step = 8;
        }

        r = 128 - step * 16;
        gb = 255 - ( ( 255 - shade ) * step ) / 8;
    }

    return r | gb << 8 | gb << 16;
}

static void MetLogo_800C51F4( Work *work, char *ot )
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
    lines = met_logo_lines_800C32E8;
    count = met_logo_lines_800C32E8[ 0 ];

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

        line->x0 = x0;
        line->y0 = y0;
        line->x1 = x1;
        line->y1 = y1;

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

        LSTORE( MetLogo_800C5190( color1, step ), &line->r0 );
        LSTORE( MetLogo_800C5190( color2, step ), &line->r1 );

        setLineG2( line );
        addPrim( ot, line );
        line++;

        if ( step >= 8 && step <= 13 )
        {
            width = -( directions->vy >> ( step - 6 ) );
            height = directions->vx >> ( step - 6 );

            poly->x0 = x1 - width;
            poly->y0 = y1 - height;
            poly->x1 = x0 - width;
            poly->y1 = y0 - height;
            poly->x2 = ( x0 + x1 ) / 2;
            poly->y2 = ( y0 + y1 ) / 2;
            poly->x3 = x0 + width;
            poly->y3 = y0 + height;

            LSTORE( 0, &poly->r0 );
            LSTORE( 0, &poly->r1 );
            LSTORE( 0x804000, &poly->r2 );
            LSTORE( 0, &poly->r3 );

            setPolyG4( poly );
            setSemiTrans( poly, 1 );
            addPrim( ot, poly );
            poly++;

            poly->x0 = x1 - width;
            poly->y0 = y1 - height;
            poly->x1 = x1 + width;
            poly->y1 = y1 + height;
            poly->x2 = ( x0 + x1 ) / 2;
            poly->y2 = ( y0 + y1 ) / 2;
            poly->x3 = x0 + width;
            poly->y3 = y0 + height;

            LSTORE( 0, &poly->r0 );
            LSTORE( 0, &poly->r1 );
            LSTORE( 0x804000, &poly->r2 );
            LSTORE( 0, &poly->r3 );

            setPolyG4( poly );
            setSemiTrans( poly, 1 );
            addPrim( ot, poly );
            poly++;
        }
    }

    tpage = &work->tpages[ GV_Clock ];
    setDrawTPage( tpage, 1, 1, getTPage( 0, 1, 0, 0 ) );
    addPrim( ot, tpage );

    if ( work->step == 0 )
    {
        // Unused but asm doesn't match without it
        gradient = work->gradient;

        if ( work->f1658 == 0 )
        {
            shade = work->gradient * 4;
        }
        else
        {
            shade = 160;
        }

        if ( work->gradient == 40 )
        {
            work->f1658 = 1;
        }

        color3 = ( shade << 8 ) | ( shade << 16 );
        MetLogo_800C5060( (char *)work->polys[ GV_Clock ], 106, 126, PCX_MG_SOLID, color3, ot );
    }
}

static void MetLogo_800C570C( Work *work, char *ot, int shade )
{
    TILE     *tile;
    DR_TPAGE *tpage;

    tile = &work->tiles[ GV_Clock ];
    LSTORE( shade << 16 | shade << 8 | shade, &tile->r0 );
    setTile( tile );
    setSemiTrans( tile, 1 );
    tile->y0 = tile->x0 = 0;
    tile->w = 320;
    tile->h = 240;
    addPrim( ot, tile );

    tpage = &work->tpages2[ GV_Clock ];
    setDrawTPage( tpage, 1, 1, getTPage( 0, 2, 0, 0 ) );
    addPrim( ot, tpage );
}

/*---------------------------------------------------------------------------*/

static void Act( Work *work )
{
    char *ot;
    int   shade;

    DG_FrameRate = 3;

    ot = DG_ChanlOTag(1);

    if ( work->sequence < 256 )
    {
        MetLogo_800C51F4( work, ot );
        MetLogo_800C570C( work, ot, work->sequence );

        work->sequence += 3;
        if ( work->sequence >= 256 )
        {
            if ( work->step > 0 )
            {
                work->sequence = 255;
                return;
            }

            work->sequence = 256;
            GM_SeSet2( 0, 63, SE_LOGO_CHOIR );
        }
    }
    else if ( work->sequence == 256 )
    {
        MetLogo_800C51F4( work, ot );

        if ( work->f1658 == 0 )
        {
            work->gradient++;
        }

        if ( *work->f165C == 1 )
        {
            work->sequence = 257;
            work->gradient = 32;
        }
    }
    else
    {
        shade = work->sequence - 256;

        if ( shade > 255 )
        {
            shade = 255;
        }

        MetLogo_800C570C( work, ot, shade );
        MetLogo_800C51F4( work, ot );

        work->sequence += 4;
        if ( work->sequence > 542 )
        {
            work->sequence = 542;

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
    SVECTOR *scratchpad;

    ((SVECTOR *)getScratchAddr(0))->vz = 0;

    i = met_logo_lines_800C32E8[0];
    lines = &met_logo_lines_800C32E8[1];
    directions = work->directions;

    for (; i > 0; lines += 4, directions++, i--)
    {
        scratchpad = (SVECTOR *)getScratchAddr(0);
        scratchpad[0].vx = lines[0] - lines[2];
        scratchpad[0].vy = lines[1] - lines[3];

        VectorNormalSS(&scratchpad[0], &scratchpad[1]);

        directions->vx = -scratchpad[1].vx / 8;
        directions->vy = -scratchpad[1].vy / 8;
    }
}

/*---------------------------------------------------------------------------*/

void *NewMetalLogo( int *arg0 )
{
    Work *work;

    work = GV_NewActor( EXEC_LEVEL, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( &( work->actor ), Act, Die, "met_logo.c" );

        work->step = 1;
        work->sequence = 0;
        work->gradient = 0;

        work->f1658 = 0;
        work->f165C = arg0;

        DG_FrameRate = 3;

        GM_SetSound( 0xff0000fe, SD_ASYNC );
        GM_SetSound( 0x01ffff0b, SD_ASYNC );
        GM_SeSet2( 0, 63, SE_GAMEOVER );

        GetResources( work );
    }

    return (void *)work;
}
