#include "demosel.h"

#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libcd.h>

#include "common.h"
#include "mts/mts.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"
#include "font/font.h"
#include "game/game.h"
#include "sd/g_sound.h"

#include "../change/met_logo.h" // for NewMetalGearLogo

extern int    FS_DiskNum;

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_MANAGER

// FIXME: it's the same struct as in change.c (in change overlay)
typedef struct _Unknown
{
    SPRT  text_sprt[2];
    SPRT  text_outline_sprt[2][4]; // there's a subtle black outline around the text
    char *string;
    short num;
    short num2;
    RECT  rect;
    short f0;
    short f2;
    short f4;
    short f6;
} Unknown;

typedef struct _Work
{
    GV_ACT   actor;
    GV_PAD  *pad;
    DG_PRIM *f24;
    DG_PRIM *f28;
    POLY_FT4 f2C[8];
    POLY_FT4 f16C[9];
    int      f2D4[8];
    int      f2F4[9];
    int      f318;
    int      f31C;
    int      f320;
    KCB      kcb[10];
    char     pad4DC[0x14];
    DR_TPAGE tpage;
    Unknown  f5D0[10];
    int      fDB8;
    int      fDBC;
    int      clut_x;
    int      clut_y;
    int      fDC8;
    int      fDCC;
    int      fDD0;
    int      fDD4;
    int      fDD8;
    int      fDDC;
    int      fDE0;
    int      fDE4;
    int      fDE8;
    int      fDEC;
    int      fDF0;
    GV_ACT  *mgslogo_actor;
    int      fDF8;
    long     argv[3];
} Work;

// FIXME: it's the same struct (but different data) as in change.c (in change overlay)
typedef struct _Unknown2
{
    int   num;
    short x;
    short y;
    int   color;
} Unknown2;

// Similar to get_color, get_shade inlines in pre_met1.c
#define GET_COLOR(s) (((s) << 10) | ((s) << 5) | (s))
#define GET_SHADE(s) ((s) * 25 / 64)

static Unknown2 dword_800C3218[10] = {
    {1, 160, 190, GET_COLOR(GET_SHADE(64))},
    {1, 160, 190, GET_COLOR(GET_SHADE(64))},
    {1, 160, 210, GET_COLOR(GET_SHADE(64))},
    {1, 160, 190, GET_COLOR(GET_SHADE(64))},
    {1, 160, 190, GET_COLOR(GET_SHADE(64))},
    {1, 160, 190, GET_COLOR(GET_SHADE(64))},
    {1, 160, 195, GET_COLOR(GET_SHADE(64))},
    {1, 160, 195, GET_COLOR(GET_SHADE(64))},
    {1, 160, 195, GET_COLOR(GET_SHADE(64))},
    {1, 160, 195, GET_COLOR(GET_SHADE(64))},
};

// Same as byte_800C3260 in change overlay
static signed char text_outline_direction_offsets_800C3290[] = {
    -1,  0,
     1,  0,
     0,  1,
     0, -1,
};

/*---------------------------------------------------------------------------*/

static void demosel_800C35FC(Work *work, int index)
{
    RECT rect;
    KCB *kcb;

    kcb = &work->kcb[index];

    rect.x = work->fDB8;
    rect.y = work->fDBC;
    rect.w = 64;
    rect.h = 21;

    work->f5D0[index].f0 = work->fDB8;
    work->f5D0[index].f2 = work->fDBC;
    work->fDBC += 21;

    font_init_kcb(kcb, &rect, work->clut_x, work->clut_y);

    work->f5D0[index].f4 = work->clut_x;
    work->f5D0[index].f6 = work->clut_y;
    work->clut_y += 21;

    font_set_kcb(kcb, -1, -1, 0, 6, 2, 0);

    font_set_buffer(kcb, GV_AllocMemory(GV_NORMAL_MEMORY, font_get_buffer_size(kcb)));
    font_set_color(kcb, 0, dword_800C3218[index].color, 0);
    font_clut_update(kcb);
}

static void demosel_800C373C(Work *work, int index)
{
    char     *string;
    KCB      *kcb;
    Unknown2 *unknown;

    string = work->f5D0[index].string;

    if (string)
    {
        kcb = &work->kcb[index];

        font_print_string(kcb, string);
        font_update(kcb);
        font_clut_update(kcb);

        work->f5D0[index].rect.w = kcb->max_width;
        work->f5D0[index].rect.h = kcb->short3 - 1;

        unknown = &dword_800C3218[index];

        if (unknown->num == 0)
        {
            work->f5D0[index].rect.x = unknown->x;
            work->f5D0[index].rect.y = unknown->y;
        }
        else if (unknown->num == 1)
        {
            work->f5D0[index].rect.x = unknown->x - kcb->max_width / 2;
            work->f5D0[index].rect.y = unknown->y - kcb->short3 / 2;
        }

        work->f5D0[index].string = NULL;
        work->f5D0[index].num = 1;
    }
}

static void demosel_800C3880(Work *work, char *ot)
{
    int       found;
    int       index;
    int       i;
    SPRT     *text_sprt;
    SPRT     *text_outline_sprt;
    int       j;
    DR_TPAGE *tpage;

    found = 0;

    index = 0;
    for (i = 0; i < 10; i++)
    {
        // BUG: The index doesn't increment on continue
        if (work->f5D0[index].num != 1)
        {
            continue;
        }

        found = 1;

        text_sprt = &work->f5D0[index].text_sprt[GV_Clock];
        LSTORE(COLOR_GRAY, &text_sprt->r0);
        LCOPY(&work->f5D0[index].rect.x, &text_sprt->x0);
        LCOPY(&work->f5D0[index].rect.w, &text_sprt->w);
        text_sprt->u0 = 0;
        text_sprt->v0 = work->f5D0[index].f2;
        text_sprt->clut = getClut(work->f5D0[index].f4, work->f5D0[index].f6);
        setSprt(text_sprt);
        addPrim(ot, text_sprt);

        // There's a subtle black outline around the text (the sprite added a couple lines above).
        // To display it there's a neat trick here: just display the same text sprite but
        // black and shifted by a ~pixel in each direction.
        text_outline_sprt = work->f5D0[index].text_outline_sprt[GV_Clock];
        for (j = 0; j < 8; j += 2)
        {
            *text_outline_sprt = *text_sprt;
            LSTORE(0x64000000, &text_outline_sprt->r0);
            text_outline_sprt->x0 += text_outline_direction_offsets_800C3290[j];
            text_outline_sprt->y0 += text_outline_direction_offsets_800C3290[j + 1];
            addPrim(ot, text_outline_sprt);
            text_outline_sprt++;
        }

        index++;
    }

    if (found != 0)
    {
        tpage = &work->tpage;
        setDrawTPage(tpage, 1, 0, getTPage(0, 0, 832, 256));
        addPrim(ot, tpage);
    }
}

static void demosel_800C3AE4(Work *work, int index, int fore)
{
    KCB *kcb;

    kcb = &work->kcb[index];
    font_set_color(kcb, 0, fore, 0);
    font_clut_update(kcb);
}

static void demosel_800C3B34(Work *work)
{
    int i;
    int shade;

    for (i = 0; i < 10; i++)
    {
        demosel_800C3AE4(work, i, GET_COLOR(GET_SHADE(0)));
    }

    if (work->fDD8 != 0)
    {
        if (work->fDE4 <= 64)
        {
            shade = 25 - GET_SHADE(work->fDE4);
            demosel_800C3AE4(work, 4, GET_COLOR(shade));
        }
    }
    else if (work->fDDC != 0)
    {
        switch(work->fDD4)
        {
        case 0:
        case 1:
        case 2:
            demosel_800C3AE4(work, 0, GET_COLOR(GET_SHADE(64)));
            break;

        case 3:
        case 4:
            demosel_800C3AE4(work, 1, GET_COLOR(GET_SHADE(64)));
            demosel_800C3AE4(work, 2, GET_COLOR(GET_SHADE(64)));
            break;

        case 5:
        case 6:
        case 7:
        case 8:
            demosel_800C3AE4(work, 3, GET_COLOR(GET_SHADE(64)));
            break;

        case 9:
            demosel_800C3AE4(work, 4, GET_COLOR(GET_SHADE(64)));
            break;

        case 10:
            demosel_800C3AE4(work, 5, GET_COLOR(GET_SHADE(64)));
            break;
        }
    }
}

static void demosel_800C3C74(Work *work)
{
    char   result[8];
    char   result2[8];
    CdlLOC loc;
    char   param[8];
    int    press;
    int    status;
    int    intr;
    int    error;
    void  *alloc;

    press = work->pad->press;

    switch ( work->fDD4 )
    {
    case 0:
        param[ 0 ] = 0;
        CdControlB( CdlNop, param, result );

        if ( result[ 0 ] & CdlStatShellOpen )
        {
            work->fDD4 = 3;
            printf( "CD CASE OPEN!!\n" );
            mts_wait_vbl( 3 );
            break;
        }

        param[ 0 ] = 0;
        status = CdControlB( CdlSetmode, param, result );

        if ( status == 0 )
        {
            printf( "CD NORMAL SPEED SET FAILED!!\n" );
            work->fDEC++;
        }
        else if ( status == 1 )
        {
            work->fDD4 = 1;
            printf( "CD NORMAL SPEED SET SUCCESS!!\n" );
            mts_wait_vbl( 3 );
            work->fDEC = 0;
        }
        else
        {
            printf( "???????\n" );
        }

        if ( work->fDEC >= 300 )
        {
            work->fDD4 = 10;
            work->fDE8 = 0;
            printf( "THIS IS NOT PS DISC!!\n" );
        }
        break;

    case 1:
        param[ 0 ] = 0;
        CdControlB( CdlNop, param, result );

        if ( result[ 0 ] & CdlStatShellOpen )
        {
            work->fDD4 = 3;
            printf( "CD CASE OPEN!!\n" );
            mts_wait_vbl( 3 );
            break;
        }

        param[ 0 ] = 0;
        status = CdControlB( CdlStop, param, result );

        if ( status == 0 )
        {
            printf( "CD STOP FAILED!!\n" );
            work->fDEC++;
        }
        else if ( status == 1 )
        {
            work->fDD4 = 2;
            printf( "CD STOP SUCCESS!!\n" );
            work->fDEC = 0;
        }
        else
        {
            printf( "???????\n" );
        }

        if ( work->fDEC >= 300 )
        {
            work->fDD4 = 10;
            work->fDE8 = 0;
            printf( "THIS IS NOT PS DISC!!\n" );
        }
        break;

    case 2:
        param[ 0 ] = 0;
        CdControlB( CdlNop, param, result );

        if ( !( result[ 0 ] & CdlStatShellOpen ) )
        {
            printf( "CD CASE CLOSE!!\n" );
        }
        else
        {
            work->fDD4 = 3;
            printf( "CD CASE OPEN!!\n" );
        }
        break;

    case 3:
        param[ 0 ] = 0;
        CdControlB( CdlNop, param, result );

        if ( !( result[ 0 ] & CdlStatShellOpen ) )
        {
            work->fDD4 = 4;
            printf( "CD CASE CLOSE!!\n" );
        }
        else
        {
            printf( "CD CASE OPEN!!\n" );
        }
        break;

    case 4:
        if ( work->fDDC != 0 && ( press & PAD_START ) )
        {
            work->fDD4 = 5;
            printf( "START BUTTON PUSH!!\n" );

            GM_SeSet2( 0, 63, SE_MENU_SELECT );

            work->fDEC = 0;
        }
        break;

    case 5:
        param[ 0 ] = 0;
        CdControlB( CdlNop, param, result );

        work->fDEC++;

        if ( result[ 0 ] & CdlStatStandby )
        {
            work->fDD4 = 6;
            printf( "CD SPIN START!!\n" );
            work->fDEC = 0;
        }
        else
        {
            printf( "CD NOT SPIN!!\n" );
        }

        if ( work->fDEC >= 300 )
        {
            work->fDD4 = 10;
            work->fDE8 = 0;
            printf( "THIS IS NOT PS DISC!!\n" );
        }
        break;

    case 6:
        param[ 0 ] = 0;
        status = CdControlB( CdlGetTN, param, result );

        if ( status == 0 )
        {
            printf( "CD TOC READ NOT FINISH!!\n" );
            work->fDEC++;
        }
        else if ( status == 1 )
        {
            work->fDD4 = 7;
            printf( "CD TOC READ SUCCESS!!\n" );
            work->fDEC = 0;
        }
        else
        {
            printf( "???????\n" );
        }

        if ( work->fDEC >= 300 )
        {
            work->fDD4 = 10;
            work->fDE8 = 0;
            printf( "THIS IS NOT PS DISC!!\n" );
        }
        break;

    case 7:
        param[ 0 ] = CdlModeSpeed | CdlModeSize1;
        status = CdControlB( CdlSetmode, param, result );

        if ( status == 0 )
        {
            printf( "CD SPEED INIT FAILED!!\n" );
            work->fDEC++;
        }
        else if ( status == 1 )
        {
            work->fDD4 = 8;
            work->fDEC = 0;
            printf( "CD SPEED INIT SUCCESS!!\n" );
            mts_wait_vbl( 3 );
        }
        else
        {
            printf( "???????\n" );
        }

        if ( work->fDEC >= 300 )
        {
            work->fDD4 = 10;
            work->fDE8 = 0;
            printf( "THIS IS NOT PS DISC!!\n" );
        }
        break;

    case 8:
        CdIntToPos( 16, &loc );
        status = CdControlB( CdlReadN, (char *)&loc, result );

        if ( status == 0 )
        {
            printf( "CD CHECK FAILED!!\n" );
            work->fDEC++;

            if ( result[ 0 ] & CdlStatError && result[ 1 ] & CdlStatSeek )
            {
                work->fDD4 = 10;
                work->fDE8 = 0;
                printf( "THIS IS NOT PS DISC!!\n" );
            }

            if ( work->fDEC >= 300 )
            {
                work->fDD4 = 10;
                work->fDE8 = 0;
                printf( "THIS IS NOT PS DISC!!\n" );
            }
            break;
        }
        else if ( status == 1 )
        {
            intr = CdReady( 0, result2 );

            error = 0;
            if ( intr == CdlDataReady )
            {
                printf( "CD CHECK OK!!\n" );

                if ( result[ 0 ] & CdlStatError && result[ 1 ] & CdlStatSeek )
                {
                    error = 1;
                    printf( "THIS IS NOT PS DISC!!!\n" );
                    work->fDD4 = 10;
                    work->fDE8 = 0;
                }
            }
            else if ( intr == CdlDiskError )
            {
                error = 1;
                printf( "CD CHECK ERROR!!\n" );
            }

            if ( error )
            {
                break;
            }

            printf( "THIS IS PS DISC!!\n" );

            alloc = GV_Malloc( 8192 );
            status = FS_ResetCdFilePosition( alloc );

            if ( status == 0 )
            {
                printf( "THIS IS DISC 1!!\n" );
                work->fDD4 = 9;
                FS_DiskNum = 0;
            }
            else
            {
                printf( "THIS IS NOT DISC 1!!!\n" );
                work->fDD4 = 10;
                work->fDE8 = 0;
            }

            GV_Free( alloc );
        }
        else
        {
            printf( "???????\n" );
        }
        break;

    case 9:
        param[ 0 ] = 0;
        status = CdControlB( CdlPause, param, result );

        work->fDD8 = 1;
        work->fDF8 = 1;
        printf( "OK! OK!\n" );
        break;

    case 10:
        work->fDE8++;
        printf( "NOT OK! NOT OK!\n" );

        if ( work->fDE8 >= 30 )
        {
            work->fDD4 = 0;
        }
        break;
    }
}

static void demosel_800C4214(Work *work)
{
    GCL_ARGS args;
    long     data[3];

    args.argc = 3;
    args.argv = data;

    if (work->fDD8 != 0)
    {
        work->fDE4++;
    }

    demosel_800C3B34(work);
    demosel_800C3C74(work);

    if (work->fDDC == 0 && work->fDE0 >= 160)
    {
        work->fDDC = 1;
    }

    work->fDE0++;

    if (work->fDE4 >= 72)
    {
        switch (work->fDF0)
        {
        case 7:
            data[0] = 0;
            data[1] = 0;
            data[2] = work->fDCC;
            break;

        case 8:
            data[0] = 1;
            data[1] = 0;
            data[2] = work->fDCC;
            break;

        case 9:
            data[0] = 0;
            data[1] = 3;
            data[2] = work->fDCC;
            break;

        case 10:
            data[0] = 1;
            data[1] = 3;
            data[2] = work->fDCC;
            break;
        }

        GCL_ExecProc(work->f31C, &args);
        GV_DestroyActor(&work->actor);
    }
}

static void demosel_800C434C(Work *work)
{
    int i;

    for (i = 7; i >= 0; i--)
    {
        work->f2D4[i] = 0;
    }
}

static void demosel_800C436C(Work *work)
{
    int i;

    for (i = 8; i >= 0; i--)
    {
        work->f2F4[i] = 0;
    }
}

static void demosel_800C438C(Work *work)
{
    int i;

    for (i = 0; i < 10; i++)
    {
        demosel_800C3AE4(work, i, GET_COLOR(GET_SHADE(0)));
    }
}

static void demosel_800C43D8(Work *work, int x0, int y0, int x1, int y1, int shade, int type)
{
    POLY_FT4 *poly;
    int       i;

    poly = work->f16C;

    for (i = 0; i < 9; i++)
    {
        work->f2F4[i] = 512;
        setRGB0(&poly[i], shade, shade, shade);
    }

    if (type == 0)
    {
        setXY4(&poly[0], x0 - 8, y0 - 8, x0, y0 - 8, x0 - 8, y0, x0, y0);
        setXY4(&poly[1], x0 + x1, y0 - 8, x0 + x1 + 8, y0 - 8, x0 + x1, y0, x0 + x1 + 8, y0);
        setXY4(&poly[2], x0 - 8, y0 + y1, x0, y0 + y1, x0 - 8, y0 + y1 + 8, x0, y0 + y1 + 8);
        setXY4(&poly[3], x0 + x1, y0 + y1, x0 + x1 + 8, y0 + y1, x0 + x1, y0 + y1 + 8, x0 + x1 + 8, y0 + y1 + 8);
        setXY4(&poly[4], x0, y0 - 8, x0 + x1, y0 - 8, x0, y0, x0 + x1, y0);
        setXY4(&poly[5], x0, y0 + y1, x0 + x1, y0 + y1, x0, y0 + y1 + 8, x0 + x1, y0 + y1 + 8);
        setXY4(&poly[6], x0 - 8, y0, x0, y0, x0 - 8, y0 + y1, x0, y0 + y1);
        setXY4(&poly[7], x0 + x1, y0, x0 + x1 + 8, y0, x0 + x1, y0 + y1, x0 + x1 + 8, y0 + y1);
        setXY4(&poly[8], x0, y0, x0 + x1, y0, x0, y0 + y1, x0 + x1, y0 + y1);
    }
    else if (type == 1)
    {
        setXY4(&poly[0], x0 - 6, y0 - 6, x0 + 2, y0 - 6, x0 - 6, y0 + 2, x0 + 2, y0 + 2);
        setXY4(&poly[1], x0 + x1 - 2, y0 - 6, x0 + x1 + 6, y0 - 6, x0 + x1 - 2, y0 + 2, x0 + x1 + 6, y0 + 2);
        setXY4(&poly[2], x0 - 6, y0 + y1 - 2, x0 + 2, y0 + y1 - 2, x0 - 6, y0 + y1 + 6, x0 + 2, y0 + y1 + 6);
        setXY4(&poly[3], x0 + x1 - 2, y0 + y1 - 2, x0 + x1 + 6, y0 + y1 - 2, x0 + x1 - 2, y0 + y1 + 6, x0 + x1 + 6, y0 + y1 + 6);
        setXY4(&poly[4], x0 + 2, y0 - 6, x0 + x1 - 2, y0 - 6, x0 + 2, y0 + 2, x0 + x1 - 2, y0 + 2);
        setXY4(&poly[5], x0 + 2, y0 + y1 - 2, x0 + x1 - 2, y0 + y1 - 2, x0 + 2, y0 + y1 + 6, x0 + x1 - 2, y0 + y1 + 6);
        setXY4(&poly[6], x0 - 6, y0 + 2, x0 + 2, y0 + 2, x0 - 6, y0 + y1 - 2, x0 + 2, y0 + y1 - 2);
        setXY4(&poly[7], x0 + x1 - 2, y0 + 2, x0 + x1 + 6, y0 + 2, x0 + x1 - 2, y0 + y1 - 2, x0 + x1 + 6, y0 + y1 - 2);
        setXY4(&poly[8], x0 + 2, y0 + 2, x0 + x1 - 2, y0 + 2, x0 + 2, y0 + y1 - 2, x0 + x1 - 2, y0 + y1 - 2);
    }
}

static void demosel_800C46BC(Work *work)
{
    POLY_FT4 *src;
    POLY_FT4 *dst;
    int       i;
    int       r0, g0, b0;

    src = work->f2C;
    dst = &work->f24->packs[GV_Clock]->poly_ft4;

    for (i = 0; i < 8; dst++, src++, i++)
    {
        *dst = *src;

        if (work->f320 > 5 && work->f320 < 11)
        {
            r0 = dst->r0;
            g0 = dst->g0;
            b0 = dst->b0;

            dst->r0 = r0 - r0 * work->fDC8 / 16;
            dst->g0 = g0 - g0 * work->fDC8 / 16;
            dst->b0 = b0 - b0 * work->fDC8 / 16;
        }

        SSTOREL(work->f2D4[i], dst);
    }

    src = work->f16C;
    dst = &work->f28->packs[GV_Clock]->poly_ft4;

    for (i = 0; i < 9; dst++, src++, i++)
    {
        *dst = *src;
        SSTOREL(work->f2F4[i], dst);
    }
}

static void demosel_800C4880(Work *work)
{
    GCL_ARGS args;
    POLY_FT4 *polys;
    unsigned short press;

    args.argc = 3;
    args.argv = work->argv;

    press = work->pad->press;
    polys = work->f2C;
    switch (work->f320)
    {
    case 0:
        switch (work->fDCC)
        {
        case 1:
            work->f320 = 1;

            work->f2D4[0] = 0x300;
            work->f2D4[1] = 0x300;
            work->f2D4[2] = 0x100;
            work->f2D4[3] = 0x100;
            work->f2D4[4] = 0;
            work->f2D4[5] = 0;
            work->f2D4[6] = 0;
            work->f2D4[7] = 0x100;

            polys[3].x0 = -28;
            polys[3].y0 = -15;
            polys[3].x1 = 28;
            polys[3].y1 = -15;
            polys[3].x2 = -28;
            polys[3].y2 = -9;
            polys[3].x3 = 28;
            polys[3].y3 = -9;

            demosel_800C43D8(work, -28, -15, 56, 6, 255, 1);
            demosel_800C3AE4(work, 6, GET_COLOR(GET_SHADE(64)));
            break;

        case 2:
            work->f320 = 2;

            work->f2D4[0] = 0x300;
            work->f2D4[1] = 0x300;
            work->f2D4[2] = 0x100;
            work->f2D4[4] = 0x100;
            work->f2D4[7] = 0x100;
            work->f2D4[3] = 0;
            work->f2D4[5] = 0;
            work->f2D4[6] = 0;

            polys[4].x0 = -28;
            polys[4].y0 = -15;
            polys[4].x1 = 28;
            polys[4].y1 = -15;
            polys[4].x2 = -28;
            polys[4].y2 = -9;
            polys[4].x3 = 28;
            polys[4].y3 = -9;

            demosel_800C43D8(work, -28, -15, 56, 6, 255, 1);
            demosel_800C3AE4(work, 7, GET_COLOR(GET_SHADE(64)));
            break;

        case 3:
            work->f320 = 1;

            work->f2D4[0] = 0x300;
            work->f2D4[1] = 0x300;
            work->f2D4[2] = 0x100;
            work->f2D4[3] = 0x100;
            work->f2D4[4] = 0x100;
            work->f2D4[5] = 0;
            work->f2D4[6] = 0;
            work->f2D4[7] = 0x100;

            polys[3].x0 = -28;
            polys[3].y0 = -42;
            polys[3].x1 = 28;
            polys[3].y1 = -42;
            polys[3].x2 = -28;
            polys[3].y2 = -36;
            polys[3].x3 = 28;
            polys[3].y3 = -36;

            polys[4].x0 = -28;
            polys[4].y0 = 1;
            polys[4].x1 = 28;
            polys[4].y1 = 1;
            polys[4].x2 = -28;
            polys[4].y2 = 7;
            polys[4].x3 = 28;
            polys[4].y3 = 7;

            demosel_800C43D8(work, -28, -42, 56, 6, 255, 1);
            demosel_800C3AE4(work, 6, GET_COLOR(GET_SHADE(64)));
            break;

        case 4:
            work->f320 = 1;
            work->f2D4[0] = 0x300;
            work->f2D4[1] = 0x300;
            work->f2D4[2] = 0x100;
            work->f2D4[3] = 0x100;
            work->f2D4[4] = 0x100;
            work->f2D4[5] = 0x100;
            work->f2D4[6] = 0;
            work->f2D4[7] = 0x100;
            demosel_800C43D8(work, -28, -58, 56, 6, 255, 1);
            demosel_800C3AE4(work, 6, GET_COLOR(GET_SHADE(64)));
            break;

        case 5:
            work->f320 = 1;
            work->f2D4[0] = 0x300;
            work->f2D4[1] = 0x300;
            work->f2D4[2] = 0x100;
            work->f2D4[3] = 0x100;
            work->f2D4[4] = 0x100;
            work->f2D4[5] = 0;
            work->f2D4[6] = 0x100;
            work->f2D4[7] = 0x100;

            demosel_800C43D8(work, -28, -58, 56, 6, 255, 1);
            demosel_800C3AE4(work, 6, GET_COLOR(GET_SHADE(64)));
            break;

        case 6:
            work->f320 = 1;
            work->f2D4[0] = 0x300;
            work->f2D4[1] = 0x300;
            work->f2D4[2] = 0x100;
            work->f2D4[3] = 0x100;
            work->f2D4[4] = 0x100;
            work->f2D4[5] = 0x100;
            work->f2D4[6] = 0x100;
            work->f2D4[7] = 0x100;
            demosel_800C43D8(work, -28, -58, 56, 6, 255, 1);
            demosel_800C3AE4(work, 6, GET_COLOR(GET_SHADE(64)));
            break;
        }
        break;

    case 1:
        if (press & PAD_DOWN)
        {
            switch (work->fDCC)
            {
            case 1:
                work->f320 = 5;

                demosel_800C43D8(work, -28, 56, 56, 12, 255, 1);
                demosel_800C3AE4(work, 6, GET_COLOR(GET_SHADE(0)));

                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;

            case 3:
                work->f320 = 2;

                demosel_800C43D8(work, -28, 1, 56, 6, 255, 1);
                demosel_800C3AE4(work, 6, GET_COLOR(GET_SHADE(0)));
                demosel_800C3AE4(work, 7, GET_COLOR(GET_SHADE(64)));

                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;

            case 4:
                work->f320 = 2;

                demosel_800C43D8(work, -28, -32, 56, 6, 255, 1);
                demosel_800C3AE4(work, 6, GET_COLOR(GET_SHADE(0)));
                demosel_800C3AE4(work, 7, GET_COLOR(GET_SHADE(64)));

                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;

            case 5:
                work->f320 = 2;

                demosel_800C43D8(work, -28, -32, 56, 6, 255, 1);
                demosel_800C3AE4(work, 6, GET_COLOR(GET_SHADE(0)));
                demosel_800C3AE4(work, 7, GET_COLOR(GET_SHADE(64)));

                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;

            case 6:
                work->f320 = 2;

                demosel_800C43D8(work, -28, -32, 56, 6, 255, 1);
                demosel_800C3AE4(work, 6, GET_COLOR(GET_SHADE(0)));
                demosel_800C3AE4(work, 7, GET_COLOR(GET_SHADE(64)));

                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;
            }
        }
        else if (!(press & PAD_CROSS))
        {
            if (press & PAD_CIRCLE)
            {
                work->f320 = 7;
                work->fDC8 = 0;
                demosel_800C436C(work);
                demosel_800C438C(work);
                GM_SeSet2(0, 0x3F, SE_MENU_SELECT);
                work->argv[0] = 0;
                work->argv[1] = 0;
                work->argv[2] = work->fDCC;
            }
        }
        else
        {
            work->f320 = 6;
            work->fDC8 = 0;
            demosel_800C436C(work);
            demosel_800C438C(work);
            GM_SeSet2(0, 0x3F, SE_MENU_EXIT);
        }
        break;

    case 2:
        if (press & PAD_DOWN)
        {
            switch (work->fDCC)
            {
            case 2:
                work->f320 = 5;
                demosel_800C43D8(work, -28, 56, 56, 12, 255, 1);
                demosel_800C3AE4(work, 7, GET_COLOR(GET_SHADE(0)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;

            case 3:
                work->f320 = 5;
                demosel_800C43D8(work, -28, 56, 56, 12, 255, 1);
                demosel_800C3AE4(work, 7, GET_COLOR(GET_SHADE(0)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;

            case 4:
                work->f320 = 3;
                demosel_800C43D8(work, -28, -6, 56, 6, 255, 1);
                demosel_800C3AE4(work, 7, GET_COLOR(GET_SHADE(0)));
                demosel_800C3AE4(work, 8, GET_COLOR(GET_SHADE(64)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;

            case 5:
                work->f320 = 4;
                demosel_800C43D8(work, -28, 20, 56, 6, 255, 1);
                demosel_800C3AE4(work, 7, GET_COLOR(GET_SHADE(0)));
                demosel_800C3AE4(work, 9, GET_COLOR(GET_SHADE(64)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;

            case 6:
                work->f320 = 3;
                demosel_800C43D8(work, -28, -6, 56, 6, 255, 1);
                demosel_800C3AE4(work, 7, GET_COLOR(GET_SHADE(0)));
                demosel_800C3AE4(work, 8, GET_COLOR(GET_SHADE(64)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;
            }
        }
        else if (press & PAD_UP)
        {
            switch (work->fDCC)
            {
            case 3:
                work->f320 = 1;
                demosel_800C43D8(work, -28, -42, 56, 6, 255, 1);
                demosel_800C3AE4(work, 7, GET_COLOR(GET_SHADE(0)));
                demosel_800C3AE4(work, 6, GET_COLOR(GET_SHADE(64)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;

            case 4:
                work->f320 = 1;
                demosel_800C43D8(work, -28, -58, 56, 6, 255, 1);
                demosel_800C3AE4(work, 7, GET_COLOR(GET_SHADE(0)));
                demosel_800C3AE4(work, 6, GET_COLOR(GET_SHADE(64)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;

            case 5:
                work->f320 = 1;
                demosel_800C43D8(work, -28, -58, 56, 6, 255, 1);
                demosel_800C3AE4(work, 7, GET_COLOR(GET_SHADE(0)));
                demosel_800C3AE4(work, 6, GET_COLOR(GET_SHADE(64)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;

            case 6:
                work->f320 = 1;
                demosel_800C43D8(work, -28, -58, 56, 6, 255, 1);
                demosel_800C3AE4(work, 7, GET_COLOR(GET_SHADE(0)));
                demosel_800C3AE4(work, 6, GET_COLOR(GET_SHADE(64)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;
            }
        }
        else if (!(press & PAD_CROSS))
        {
            if (press & PAD_CIRCLE)
            {
                work->f320 = 8;
                work->fDC8 = 0;
                demosel_800C436C(work);
                demosel_800C438C(work);
                GM_SeSet2(0, 0x3F, SE_MENU_SELECT);
                work->argv[0] = 1;
                work->argv[1] = 0;
                work->argv[2] = work->fDCC;
            }
        }
        else
        {
            work->f320 = 6;
            work->fDC8 = 0;
            demosel_800C436C(work);
            demosel_800C438C(work);
            GM_SeSet2(0, 0x3F, SE_MENU_EXIT);
        }
        break;

    case 3:
        if (press & PAD_DOWN)
        {
            switch (work->fDCC)
            {
            case 4:
                work->f320 = 5;
                demosel_800C43D8(work, -28, 56, 56, 12, 255, 1);
                demosel_800C3AE4(work, 8, GET_COLOR(GET_SHADE(0)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;

            case 6:
                work->f320 = 4;
                demosel_800C43D8(work, -28, 20, 56, 6, 255, 1);
                demosel_800C3AE4(work, 8, GET_COLOR(GET_SHADE(0)));
                demosel_800C3AE4(work, 9, GET_COLOR(GET_SHADE(64)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;
            }
        }
        else if (press & PAD_UP)
        {
            switch (work->fDCC)
            {
            case 4:
                work->f320 = 2;
                demosel_800C43D8(work, -28, -32, 56, 6, 255, 1);
                demosel_800C3AE4(work, 8, GET_COLOR(GET_SHADE(0)));
                demosel_800C3AE4(work, 7, GET_COLOR(GET_SHADE(64)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;

            case 6:
                work->f320 = 2;
                demosel_800C43D8(work, -28, -32, 56, 6, 255, 1);
                demosel_800C3AE4(work, 8, GET_COLOR(GET_SHADE(0)));
                demosel_800C3AE4(work, 7, GET_COLOR(GET_SHADE(64)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;
            }
        }
        else if (!(press & PAD_CROSS))
        {
            if (press & PAD_CIRCLE)
            {
                work->f320 = 9;
                work->fDC8 = 0;
                demosel_800C436C(work);
                demosel_800C438C(work);
                GM_SeSet2(0, 0x3F, SE_MENU_SELECT);
                work->argv[0] = 0;
                work->argv[1] = 3;
                work->argv[2] = work->fDCC;
            }
        }
        else
        {
            work->f320 = 6;
            work->fDC8 = 0;
            demosel_800C436C(work);
            demosel_800C438C(work);
            GM_SeSet2(0, 0x3F, SE_MENU_EXIT);
        }
        break;

    case 4:
        if (press & PAD_DOWN)
        {
            switch (work->fDCC)
            {
            case 5:
                work->f320 = 5;
                demosel_800C43D8(work, -28, 56, 56, 12, 255, 1);
                demosel_800C3AE4(work, 9, GET_COLOR(GET_SHADE(0)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;

            case 6:
                work->f320 = 5;
                demosel_800C43D8(work, -28, 56, 56, 12, 255, 1);
                demosel_800C3AE4(work, 9, GET_COLOR(GET_SHADE(0)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;
            }
        }
        else if (press & PAD_UP)
        {
            switch (work->fDCC)
            {
            case 5:
                work->f320 = 2;
                demosel_800C43D8(work, -28, -32, 56, 6, 255, 1);
                demosel_800C3AE4(work, 9, GET_COLOR(GET_SHADE(0)));
                demosel_800C3AE4(work, 7, GET_COLOR(GET_SHADE(64)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;

            case 6:
                work->f320 = 3;
                demosel_800C43D8(work, -28, -6, 56, 6, 255, 1);
                demosel_800C3AE4(work, 9, GET_COLOR(GET_SHADE(0)));
                demosel_800C3AE4(work, 8, GET_COLOR(GET_SHADE(64)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;
            }
        }
        else if (!(press & PAD_CROSS))
        {
            if (press & PAD_CIRCLE)
            {
                work->f320 = 10;
                work->fDC8 = 0;
                demosel_800C436C(work);
                demosel_800C438C(work);
                GM_SeSet2(0, 0x3F, SE_MENU_SELECT);
                work->argv[0] = 1;
                work->argv[1] = 3;
                work->argv[2] = work->fDCC;
            }
        }
        else
        {
            work->f320 = 6;
            work->fDC8 = 0;
            demosel_800C436C(work);
            demosel_800C438C(work);
            GM_SeSet2(0, 0x3F, SE_MENU_EXIT);
        }
        break;

    case 5:
        if (press & PAD_UP)
        {
            switch (work->fDCC)
            {
            case 1:
                work->f320 = 1;
                demosel_800C43D8(work, -28, -15, 56, 6, 255, 1);
                demosel_800C3AE4(work, 6, GET_COLOR(GET_SHADE(64)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;

            case 2:
                work->f320 = 2;
                demosel_800C43D8(work, -28, -15, 56, 6, 255, 1);
                demosel_800C3AE4(work, 7, GET_COLOR(GET_SHADE(64)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;

            case 3:
                work->f320 = 2;
                demosel_800C43D8(work, -28, 1, 56, 6, 255, 1);
                demosel_800C3AE4(work, 7, GET_COLOR(GET_SHADE(64)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;

            case 4:
                work->f320 = 3;
                demosel_800C43D8(work, -28, -6, 56, 6, 255, 1);
                demosel_800C3AE4(work, 8, GET_COLOR(GET_SHADE(64)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;

            case 5:
            case 6:
                work->f320 = 4;
                demosel_800C43D8(work, -28, 20, 56, 6, 255, 1);
                demosel_800C3AE4(work, 9, GET_COLOR(GET_SHADE(64)));
                GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
                break;
            }
        }
        else if (press & (PAD_CROSS | PAD_CIRCLE))
        {
            work->f320 = 6;
            work->fDC8 = 0;
            demosel_800C436C(work);
            demosel_800C438C(work);
            GM_SeSet2(0, 0x3F, SE_MENU_EXIT);
        }
        break;

    case 6:
        if (work->fDC8 >= 17)
        {
            GCL_ExecProc(work->f318, NULL);
            GV_DestroyActor(&work->actor);
        }
        break;

    case 7:
    case 8:
    case 9:
    case 10:
        if (work->fDC8 >= 17)
        {
            demosel_800C434C(work);
            if (FS_DiskNum == 0)
            {
                printf("flag %d %d %d\n", (int)work->argv[0], (int)work->argv[1], (int)work->argv[2]);
                GCL_ExecProc(work->f31C, &args);
                GV_DestroyActor(&work->actor);
            }
            else
            {
                work->fDD0 = 1;
                work->fDD4 = 0;
                work->fDE0 = 0;
                work->fDE4 = 0;
                work->fDE8 = 0;
                work->fDD8 = 0;
                work->fDDC = 0;
                work->fDF0 = work->f320;
                work->f320 = 11;
            }
        }
        break;

    case 11:
        if (work->fDD0)
        {
            demosel_800C434C(work);
            work->fDD0 = 0;
            work->fDF8 = 0;
            work->mgslogo_actor = NewMetalGearLogo(&work->fDF8);
        }
        demosel_800C4214(work);
        break;
    }
}

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    demosel_800C4880(work);
    demosel_800C3880(work, DG_ChanlOTag(1));
    demosel_800C46BC(work);
    work->fDC8++;
}

static void Die(Work *work)
{
    GM_FreePrim(work->f24);
    GM_FreePrim(work->f28);
}

/*---------------------------------------------------------------------------*/

static void demosel_800C5884(Work *work, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe)
{
    setPolyFT4(poly);
    setRGB0(poly, 128, 128, 128);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);
}

static inline void demosel_helper_800C58F4(POLY_FT4 *poly, DG_TEX *tex, int uo, int vo)
{
    int u0, u1;
    int v0, v1;

    u0 = tex->off_x;
    u1 = u0 + tex->w + uo;
    v0 = tex->off_y;
    v1 = v0 + tex->h + vo;
    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}

static void demosel_800C58F4(Work *work, int name, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe, int type)
{
    DG_TEX *tex;

    demosel_800C5884(work, poly, x0, y0, x1, y1, abe);

    tex = DG_GetTexture(name);
    if (type == 0)
    {
        demosel_helper_800C58F4(poly, tex, 1, 1);
    }
    else if (type == 1)
    {
        demosel_helper_800C58F4(poly, tex, 1, 0);
    }
    else if (type == 2)
    {
        demosel_helper_800C58F4(poly, tex, 0, 1);
    }
    else if (type == 3)
    {
        demosel_helper_800C58F4(poly, tex, 0, 0);
    }
}

static int GetResources(Work *work, int map)
{
    POLY_FT4 *poly;
    int       i;
    POLY_FT4 *poly2;

    GM_CurrentMap = map;

    work->fDB8 = 832;
    work->fDBC = 256;
    work->clut_x = 832;
    work->clut_y = 276;

    work->f24 = DG_GetPrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 8, 0, NULL, NULL);
    work->f28 = DG_GetPrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 9, 0, NULL, NULL);

    poly = work->f2C;
    i = 0;

    demosel_800C58F4(work, GV_StrCode("demo_back_l"), poly, -160, -112, 0, 112, 0, 0);
    setRGB0(poly, 128, 128, 128);
    poly++;
    work->f2D4[i] = 768;
    i++;

    demosel_800C58F4(work, GV_StrCode("demo_back_r"), poly, 0, -112, 160, 112, 0, 0);
    setRGB0(poly, 128, 128, 128);
    poly++;
    work->f2D4[i] = 768;
    i++;

    demosel_800C58F4(work, GV_StrCode("demo_demo"), poly, -56, -100, 56, -88, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->f2D4[i] = 256;
    i++;

    demosel_800C58F4(work, GV_StrCode("demo_ra"), poly, -28, -58, 28, -52, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->f2D4[i] = 0;
    i++;

    demosel_800C58F4(work, GV_StrCode("demo_rb"), poly, -28, -32, 28, -26, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->f2D4[i] = 0;
    i++;

    demosel_800C58F4(work, GV_StrCode("demo_roll_c"), poly, -28, -6, 28, 0, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->f2D4[i] = 0;
    i++;

    demosel_800C58F4(work, GV_StrCode("demo_roll_d"), poly, -28, 20, 28, 26, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->f2D4[i] = 0;
    i++;

    demosel_800C58F4(work, GV_StrCode("demo_exit"), poly, -28, 56, 28, 68, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->f2D4[i] = 0;
    i++;

    poly2 = work->f16C;
    i = 0;

    demosel_800C58F4(work, GV_StrCode("cur_lu"), poly2, 0, 0, 0, 0, 1, 0);
    poly2++;
    work->f2F4[i] = 0;
    i++;

    demosel_800C58F4(work, GV_StrCode("cur_ru"), poly2, 0, 0, 0, 0, 1, 0);
    poly2++;
    work->f2F4[i] = 0;
    i++;

    demosel_800C58F4(work, GV_StrCode("cur_ld"), poly2, 0, 0, 0, 0, 1, 0);
    poly2++;
    work->f2F4[i] = 0;
    i++;

    demosel_800C58F4(work, GV_StrCode("cur_rd"), poly2, 0, 0, 0, 0, 1, 0);
    poly2++;
    work->f2F4[i] = 0;
    i++;

    demosel_800C58F4(work, GV_StrCode("cur_u"), poly2, 0, 0, 0, 0, 1, 2);
    poly2++;
    work->f2F4[i] = 0;
    i++;

    demosel_800C58F4(work, GV_StrCode("cur_d"), poly2, 0, 0, 0, 0, 1, 2);
    poly2++;
    work->f2F4[i] = 0;
    i++;

    demosel_800C58F4(work, GV_StrCode("cur_l"), poly2, 0, 0, 0, 0, 1, 1);
    poly2++;
    work->f2F4[i] = 0;
    i++;

    demosel_800C58F4(work, GV_StrCode("cur_r"), poly2, 0, 0, 0, 0, 1, 1);
    poly2++;
    work->f2F4[i] = 0;
    i++;

    demosel_800C58F4(work, GV_StrCode("cur_c"), poly2, 0, 0, 0, 0, 1, 3);
    poly2++;
    work->f2F4[i] = 0;
    i++;

    if (GCL_GetOption('e'))
    {
        work->f318 = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->f318 = -1;
    }

    if (GCL_GetOption('d'))
    {
        work->f31C = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->f31C = -1;
    }

    if (GCL_GetOption('g'))
    {
        work->fDCC = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->fDCC = -1;
    }

    printf("demorank = %d\n", work->fDCC);

    if (work->fDCC >= 3)
    {
        work->fDCC = 3;
    }

    for (i = 0; i < 10; i++)
    {
        work->f5D0[i].string = GCL_ReadString(GCL_GetParamResult());
        work->f5D0[i].num = 0;
        demosel_800C35FC(work, i);
    }

    for (i = 0; i < 10; i++)
    {
        demosel_800C373C(work, i);
    }

    for (i = 0; i < 10; i++)
    {
        demosel_800C3AE4(work, i, GET_COLOR(GET_SHADE(0)));
    }

    work->pad = &GV_PadData[2];

    work->f320 = 0;
    work->fDC8 = 0;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewDemoSelect(int arg0, int arg1)
{
    Work *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "demosel.c");

        if (GetResources(work, arg1) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
