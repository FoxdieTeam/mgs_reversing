#include "Game/game.h"
#include "libdg/libdg.h"
#include "libgcl/hash.h"
#include "libgv/libgv.h"

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

extern int DG_FrameRate_8009D45C;
extern int GV_Clock_800AB920;

extern short met_logo_lines_800C32E8[];

#define EXEC_LEVEL 1

char * MetLogo_800C5060( char *buffer, short x, short y, int texture, unsigned int color, char *ot )
{
    DG_TEX   *tex;
    SPRT     *sprt;
    DR_TPAGE *tpage;

    tex = DG_GetTexture_8001D830( texture );
    sprt = (SPRT *)buffer;
    tpage = (DR_TPAGE *)(buffer + sizeof(SPRT));

    sprt->x0 = x;
    sprt->y0 = y;
    sprt->u0 = tex->field_8_offx;
    sprt->v0 = tex->field_9_offy;
    sprt->w = tex->field_A_width + 1;
    sprt->h = tex->field_B_height + 1;
    sprt->clut = tex->field_6_clut;
    LSTORE( color, &sprt->r0 );
    setSprt( sprt );
    addPrim( ot, sprt );

    setDrawTPage( tpage, 1, 0, tex->field_4_tPage );
    addPrim( ot, tpage );

    return buffer + sizeof(SPRT) + sizeof(DR_TPAGE);
}

int MetLogo_800C5190( int shade, int step )
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

void MetLogo_800C51F4( Work *work, char *ot )
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
    line = work->lines[ GV_Clock_800AB920 ];
    poly = work->polys[ GV_Clock_800AB920 ];

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

    tpage = &work->tpages[ GV_Clock_800AB920 ];
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
        MetLogo_800C5060( (char *)work->polys[ GV_Clock_800AB920 ], 106, 126, PCX_MG_SOLID, color3, ot );
    }
}

void MetLogo_800C570C( Work *work, char *ot, int shade )
{
    TILE     *tile;
    DR_TPAGE *tpage;

    tile = &work->tiles[ GV_Clock_800AB920 ];
    LSTORE( shade << 16 | shade << 8 | shade, &tile->r0 );
    setTile( tile );
    setSemiTrans( tile, 1 );
    tile->y0 = tile->x0 = 0;
    tile->w = 320;
    tile->h = 240;
    addPrim( ot, tile );

    tpage = &work->tpages2[ GV_Clock_800AB920 ];
    setDrawTPage( tpage, 1, 1, getTPage( 0, 2, 0, 0 ) );
    addPrim( ot, tpage );
}

void MetLogoAct_800C57E8( Work *work )
{
    char *ot;
    int   shade;

    DG_FrameRate_8009D45C = 3;

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
            GM_SeSet2_80032968( 0, 63, 123 ); // Change hymn
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

            if ( GM_StreamStatus_80037CD8() == -1 )
            {
                GV_DestroyActor_800151C8( &( work->actor ) );
            }
        }
    }
}

void MetLogoDie_800C5988( Work *work )
{
    DG_FrameRate_8009D45C = 2;
}

void MetLogoGetResources_800C5998( Work *work )
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

GV_ACT * NewMetLogo_800C5A90( int *arg0 )
{
    Work *work;

    work = (Work *)GV_NewActor_800150E4( EXEC_LEVEL,  sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor_8001514C( &( work->actor ), (TActorFunction)MetLogoAct_800C57E8, (TActorFunction)MetLogoDie_800C5988, "met_logo.c" );

        work->step = 1;
        work->sequence = 0;
        work->gradient = 0;

        work->f1658 = 0;
        work->f165C = arg0;

        DG_FrameRate_8009D45C = 3;

        GM_Sound_80032C48( -0xFFFF02, 0 );
        GM_Sound_80032C48( 0x01FFFF0B, 0 );
        GM_SeSet2_80032968( 0, 63, 15 ); // Game over sound

        MetLogoGetResources_800C5998( work );
    }

    return &( work->actor );
}
