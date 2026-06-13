#include "game/game.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"
#include "mts/mts.h"

#include <libcd.h>
#include <stdio.h>

// FIXME: it's the same struct (but different data) as in change.c (in change overlay)
typedef struct _Unknown2
{
    int   num;
    short x;
    short y;
    int   color;
} Unknown2;

// FIXME: it's the same struct as in change.c (in change overlay)
typedef struct _Unknown
{
    SPRT  text_sprt2[2];
    SPRT  text_outline_sprt2[2][4]; // there's a subtle black outline around the text
    char *string;
    short num;
    short num2;
    RECT  rect;
    short font_x;
    short font_y;
    short clut_x;
    short clut_y;
} Unknown;

typedef struct _Work
{
    GV_ACT   actor;
    GV_PAD  *pad;
    int      end_proc;
    KCB      kcb[8];
    char     pad1[0x14];
    DR_TPAGE tpage;
    Unknown  field_1A4[8];
    int      font_x;
    int      font_y;
    int      clut_x;
    int      clut_y;
    void    *logo;
    int      field_8B8;
    int      field_8BC;
    int      field_8C0;
    int      field_8C4;
    int      field_8C8;
    int      logo_enable;
    int      field_8D0;
    int      disc_no;
    int      field_8D8;
} Work;

Unknown2 D_800C3750[] = 
{
    {1, 160, 190, 0x6739},
    {1, 160, 190, 0x6739},
    {1, 160, 190, 0x6739},
    {1, 160, 190, 0x6739},
    {1, 160, 210, 0x6739},
    {1, 160, 190, 0x6739},
    {1, 160, 190, 0x6739},
    {1, 160, 190, 0x6739},
};

signed char D_800C37B0[] = {-1, 0, 1, 0, 0, 1, 0, -1};

extern int FS_DiskNum;

void *NewMetalGearLogo( int *exit );

static void func_800C6B1C(Work *work, int index)
{
    RECT     rect;
    KCB     *kcb;
    Unknown *unk;
    void    *buf;

    kcb = &work->kcb[index];

    rect.x = work->font_x;
    rect.y = work->font_y;
    rect.w = 64;
    rect.h = 21;

    unk = &work->field_1A4[index];

    work->field_1A4[index].font_x = work->font_x;
    work->field_1A4[index].font_y = work->font_y;
    work->font_y += 21;

    font_init_kcb(kcb, &rect, work->clut_x, work->clut_y);

    work->field_1A4[index].clut_x = work->clut_x;
    work->field_1A4[index].clut_y = work->clut_y;
    work->clut_y += 21;

    font_set_kcb(kcb, -1, -1, 0, 6, 2, 0);

    buf = GV_AllocMemory(GV_NORMAL_MEMORY, font_get_buffer_size(kcb));
    font_set_buffer(kcb, buf);

    font_set_color(kcb, 0, D_800C3750[index].color, 0);
    font_clut_update(kcb);
}

static void func_800C6C5C(Work *work, int index)
{
    KCB *kcb;

    if (work->field_1A4[index].string)
    {
        kcb = &work->kcb[index];
        font_print_string(kcb, work->field_1A4[index].string);
        font_update(kcb);
        font_clut_update(kcb);

        work->field_1A4[index].rect.w = kcb->max_width;
        work->field_1A4[index].rect.h = kcb->max_height;

        if (D_800C3750[index].num == 0)
        {
            work->field_1A4[index].rect.x = D_800C3750[index].x;
            work->field_1A4[index].rect.y = D_800C3750[index].y;
        }
        else if (D_800C3750[index].num == 1)
        {
            work->field_1A4[index].rect.x = D_800C3750[index].x - kcb->max_width / 2;
            work->field_1A4[index].rect.y = D_800C3750[index].y - kcb->max_height / 2;
        }

        work->field_1A4[index].string = NULL;
        work->field_1A4[index].num = 1;
    }
}

static void func_800C6D9C(Work *work, u_long *ot)
{
    int       i, j;
    int       drawn;
    int       index;
    SPRT     *sprt1;
    SPRT     *sprt2;
    DR_TPAGE *tpage;

    drawn = 0;
    index = 0;
    for (i = 0; i < 8; i++)
    {
        // BUG: The index doesn't increment on continue
        if (work->field_1A4[index].num != 1)
        {
            continue;
        }

        drawn = 1;

        sprt1 = &work->field_1A4[index].text_sprt2[GV_Clock];
        LSTORE(0x808080, &sprt1->r0);
        LCOPY(&work->field_1A4[index].rect.x, &sprt1->x0);
        LCOPY(&work->field_1A4[index].rect.w, &sprt1->w);
        setUV0(sprt1, 0, work->field_1A4[index].font_y);
        setClut(sprt1, work->field_1A4[index].clut_x, work->field_1A4[index].clut_y);
        setSprt(sprt1);
        addPrim(ot, sprt1);

        sprt2 = work->field_1A4[index].text_outline_sprt2[GV_Clock];
        for (j = 0; j < 8; j += 2)
        {
            *sprt2 = *sprt1;
            LSTORE(0x64000000, &sprt2->r0);
            sprt2->x0 += D_800C37B0[j];
            sprt2->y0 += D_800C37B0[j + 1];

            addPrim(ot, sprt2);
            sprt2++;
        }

        index++;
    }

    if (drawn != 0)
    {
        tpage = &work->tpage;
        setDrawTPage(tpage, 1, 0, getTPage(0, 0, 832, 256));
        addPrim(ot, tpage);
    }
}

static void func_800C7000(Work *work, int index, int col)
{
    KCB *kcb;

    kcb = &work->kcb[index];
    font_set_color(kcb, 0, col, 0);
    font_clut_update(kcb);
}

static void func_800C7050(Work *work)
{
    int i;
    int shade;

    for (i = 0; i < 8; i++)
    {
        func_800C7000(work, i, 0); 
    }

    if (work->field_8C4 != 0)
    {
        if (work->field_8BC <= 64)
        {
            shade = 25 - (work->field_8BC * 25) / 64;
            func_800C7000(work, 6, (shade << 10) | (shade << 5) | shade);
        }
    }
    else if (work->field_8D8 != 0)
    {
        switch (work->field_8C8)
        {
        case 0:
        case 1:
        case 2:
            if (work->disc_no == 1)
            {
                func_800C7000(work, 0, 0x6739);
            }
            else if (work->disc_no == 2)
            {
                func_800C7000(work, 2, 0x6739);
            }
            break;
        case 3:
        case 4:
            if (work->disc_no == 1)
            {
                func_800C7000(work, 1, 0x6739);
            }
            else if (work->disc_no == 2)
            {
                func_800C7000(work, 3, 0x6739);
            }

            func_800C7000(work, 4, 0x6739);
            break;
        case 5:
        case 6:
        case 7:
        case 8:
            func_800C7000(work, 5, 0x6739);
            break;
        case 9:
            func_800C7000(work, 6, 0x6739);
            break;
        case 10:
            func_800C7000(work, 7, 0x6739);
            break;
        }
    }
}

static void func_800C71D0(Work *work)
{
    char   result[8];
    char   result2[8];
    CdlLOC loc;
    char   param[8];
    int    press;
    int    status;
    int    intr;
    int    error;
    int    check;
    void  *alloc;

    press = work->pad->press;

    switch ( work->field_8C8 )
    {
    case 0:
        param[ 0 ] = 0;
        CdControlB( CdlNop, param, result );

        if ( result[ 0 ] & CdlStatShellOpen )
        {
            work->field_8C8 = 3;
            printf( "CD CASE OPEN!!\n" );
            mts_wait_vbl( 3 );
            break;
        }

        param[ 0 ] = 0;
        status = CdControlB( CdlSetmode, param, result );

        if ( status == 0 )
        {
            printf( "CD NORMAL SPEED SET FAILED!!\n" );
            work->field_8C0++;
        }
        else if ( status == 1 )
        {
            work->field_8C8 = 1;
            printf( "CD NORMAL SPEED SET SUCCESS!!\n" );
            mts_wait_vbl( 3 );
            work->field_8C0 = 0;
        }
        else
        {
            printf( "???????\n" );
        }

        if ( work->field_8C0 >= 300 )
        {
            work->field_8C8 = 10;
            work->field_8D0 = 0;
            printf( "THIS IS NOT PS DISC!!\n" );
        }
        break;

    case 1:
        param[ 0 ] = 0;
        CdControlB( CdlNop, param, result );

        if ( result[ 0 ] & CdlStatShellOpen )
        {
            work->field_8C8 = 3;
            printf( "CD CASE OPEN!!\n" );
            mts_wait_vbl( 3 );
            break;
        }

        param[ 0 ] = 0;
        status = CdControlB( CdlStop, param, result );

        if ( status == 0 )
        {
            printf( "CD STOP FAILED!!\n" );
            work->field_8C0++;
        }
        else if ( status == 1 )
        {
            work->field_8C8 = 2;
            printf( "CD STOP SUCCESS!!\n" );
            work->field_8C0 = 0;
        }
        else
        {
            printf( "???????\n" );
        }

        if ( work->field_8C0 >= 300 )
        {
            work->field_8C8 = 10;
            work->field_8D0 = 0;
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
            work->field_8C8 = 3;
            printf( "CD CASE OPEN!!\n" );
        }
        break;

    case 3:
        param[ 0 ] = 0;
        CdControlB( CdlNop, param, result );

        if ( !( result[ 0 ] & CdlStatShellOpen ) )
        {
            work->field_8C8 = 4;
            printf( "CD CASE CLOSE!!\n" );
        }
        else
        {
            printf( "CD CASE OPEN!!\n" );
        }
        break;

    case 4:
        if ( work->field_8D8 != 0 && ( press & PAD_START ) )
        {
            work->field_8C8 = 5;
            printf( "START BUTTON PUSH!!\n" );

            GM_SeSet2( 0, 63, SE_MENU_SELECT );

            work->field_8C0 = 0;
        }
        break;

    case 5:
        param[ 0 ] = 0;
        CdControlB( CdlNop, param, result );

        work->field_8C0++;

        if ( result[ 0 ] & CdlStatStandby )
        {
            work->field_8C8 = 6;
            printf( "CD SPIN START!!\n" );
            work->field_8C0 = 0;
        }
        else
        {
            printf( "CD NOT SPIN!!\n" );
        }

        if ( work->field_8C0 >= 300 )
        {
            work->field_8C8 = 10;
            work->field_8D0 = 0;
            printf( "THIS IS NOT PS DISC!!\n" );
        }
        break;

    case 6:
        param[ 0 ] = 0;
        status = CdControlB( CdlGetTN, param, result );

        if ( status == 0 )
        {
            printf( "CD TOC READ NOT FINISH!!\n" );
            work->field_8C0++;
        }
        else if ( status == 1 )
        {
            work->field_8C8 = 7;
            printf( "CD TOC READ SUCCESS!!\n" );
            work->field_8C0 = 0;
        }
        else
        {
            printf( "???????\n" );
        }

        if ( work->field_8C0 >= 300 )
        {
            work->field_8C8 = 10;
            work->field_8D0 = 0;
            printf( "THIS IS NOT PS DISC!!\n" );
        }
        break;

    case 7:
        param[ 0 ] = CdlModeSpeed | CdlModeSize1;
        status = CdControlB( CdlSetmode, param, result );

        if ( status == 0 )
        {
            printf( "CD SPEED INIT FAILED!!\n" );
            work->field_8C0++;
        }
        else if ( status == 1 )
        {
            work->field_8C8 = 8;
            work->field_8C0 = 0;
            printf( "CD SPEED INIT SUCCESS!!\n" );
            mts_wait_vbl( 3 );
        }
        else
        {
            printf( "???????\n" );
        }

        if ( work->field_8C0 >= 300 )
        {
            work->field_8C8 = 10;
            work->field_8D0 = 0;
            printf( "THIS IS NOT PS DISC!!\n" );
        }
        break;

    case 8:
        CdIntToPos( 16, &loc );
        status = CdControlB( CdlReadN, (char *)&loc, result );

        if ( status == 0 )
        {
            printf( "CD CHECK FAILED!!\n" );
            work->field_8C0++;

            if ( result[ 0 ] & CdlStatError && result[ 1 ] & CdlStatSeek )
            {
                work->field_8C8 = 10;
                work->field_8D0 = 0;
                printf( "THIS IS NOT PS DISC!!\n" );
            }

            if ( work->field_8C0 >= 300 )
            {
                work->field_8C8 = 10;
                work->field_8D0 = 0;
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
                    work->field_8C8 = 10;
                    work->field_8D0 = 0;
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
            check = FS_ResetCdFilePosition( alloc );

            printf( "check = %d  disc_no = %d\n", check, work->disc_no );

            if ( work->disc_no == 1 )
            {
                if ( check == 0 )
                {
                    printf( "THIS IS DISC 1!!\n" );
                    work->field_8C8 = 9;
                    FS_DiskNum = 0;
                }
                else
                {
                    printf( "THIS IS NOT DISC 1!!!\n" );
                    work->field_8C8 = 10;
                    work->field_8D0 = 0;
                }
            }
            else if ( work->disc_no == 2 )
            {
                if ( check == 1 )
                {
                    printf( "THIS IS DISC 2!!\n" );
                    work->field_8C8 = 9;
                    FS_DiskNum = 1;
                }
                else
                {
                    printf( "THIS IS NOT DISC 2!!!\n" );
                    work->field_8C8 = 10;
                    work->field_8D0 = 0;
                }
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
        CdControlB( CdlPause, param, result );

        work->field_8C4 = 1;
        work->logo_enable = 1;
        printf( "OK! OK!\n" );
        break;

    case 10:
        work->field_8D0++;
        printf( "NOT OK! NOT OK!\n" );

        if ( work->field_8D0 >= 30 )
        {
            work->field_8C8 = 0;
        }
        break;
    }
}

static void Act(Work *work)
{    
    if (work->field_8C4 != 0)
    {
        work->field_8BC++;
    }

    func_800C7050(work);
    func_800C6D9C(work, DG_Chanl(1)->ot[GV_Clock]);
    func_800C71D0(work);

    if (work->field_8D8 == 0 && work->field_8B8 >= 160)
    {
        work->field_8D8 = 1;
    }

    work->field_8B8++;

    if (work->field_8BC >= 72)
    {
        GCL_ExecProc(work->end_proc, NULL);
        GV_DestroyActor(work);
    }
}

static void Die(Work *work)
{
    /* do nothing */
}

static int GetResources(Work *work, int where)
{
    int i;

    GM_CurrentMap = where;

    work->pad = &GV_PadData[2];
    work->font_x = 832;
    work->font_y = 256;
    work->clut_x = 832;
    work->clut_y = 276;

    if (GCL_GetOption('a'))
    {
        work->disc_no = GCL_StrToInt(GCL_NextStr());
        printf("disc_no = %d\n", work->disc_no);

        if (work->disc_no != 1 && work->disc_no != 2)
        {
            printf("error disc no!!\n");
        }
    }
    else
    {
        work->disc_no = -1;
    }

    if (GCL_GetOption('e'))
    {
        work->end_proc = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->end_proc = -1;
    }

    for (i = 0; i < 8; i++)
    {
        work->field_1A4[i].string = GCL_GetString(GCL_NextStr());
        work->field_1A4[i].num = 0;
        func_800C6B1C(work, i);
    }

    for (i = 0; i < 8; i++)
    {
        func_800C6C5C(work, i);
    }

    work->logo_enable = 0;
    work->logo = NewMetalGearLogo(&work->logo_enable);

    work->field_8B8 = 0;
    work->field_8C4 = 0;
    work->field_8BC = 0;
    work->field_8C8 = 0;
    work->field_8D8 = 0;
    return 0;
}

void *NewAbstractChange(int name, int where)
{
    Work *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = GV_NewActor(GV_ACTOR_MANAGER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "ab_ch.c");
        if (GetResources(work, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}
