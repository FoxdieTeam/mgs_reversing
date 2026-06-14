#include "game/game.h"
#include "libgcl/libgcl.h"
#include "libfs/libfs.h"
#include "mts/mts.h"

#include <stdio.h>

// FIXME: it's the same struct as in change.c (in change overlay)
typedef struct _Unknown
{
    SPRT  text_sprt[2];
    SPRT  text_sprt_outline[2][4];
    SPRT  text_sprt2[2];
    SPRT  text_sprt_outline2[2][4];
    SPRT  text_sprt3[2];
    SPRT  text_sprt4[2];
    char *string;
    short num;
    short num2;
    RECT  rect;
    short unk1;
    short unk2;
    short x0;
    short y0;
    short cx;
    short cy;
    short unk3;
    short unk4;
    short x1;
    short y1;
} Unknown;

// FIXME: it's the same struct (but without num) as in preope.c (in preope overlay)
typedef struct _Unknown2
{
    short x, y;
    int   color;
} Unknown2;

typedef struct _AbstRes
{
    int id;
    int file;
    int size;
} AbstRes;

typedef struct _Work
{
    GV_ACT   actor;
    int      end_proc;
    GV_PAD  *pad;
    DG_PRIM *prim1;
    DG_PRIM *prim2;
    POLY_FT4 polys1[6];
    POLY_FT4 polys2[9];
    int      attrs1[6]; /* new name needed */
    int      attrs2[9]; /* new name needed */
    int      field_2C4;
    KCB      kcb[12];
    char     pad1[0x14];
    DR_TPAGE tpage[6];
    Unknown  field_51C[12];
    int      font_x;
    int      font_y;
    int      clut_x;
    int      clut_y;
    int      field_1D5C;
    char     pad3[0x4];
    int      field_1D64;
    int      field_1D68;
    char     pad4[0x20];
    MenuPrim primbuf;
    char     field_1DA0[0x2000];
    char     field_3DA0[0x2000];
    int      field_5DA0;
    int      field_5DA4;
} Work;

Unknown2 D_800C3238[] =
{
    {88, 0x00B4, 0x6739},
    {16, 0x0023, 0},
    {16, 0x0036, 0},
    {16, 0x0049, 0},
    {16, 0x005C, 0},
    {16, 0x006F, 0},
    {16, 0x0082, 0},
    {16, 0x0095, 0},
    {16, 0x00A8, 0},
    {16, 0x00BB, 0},
    {16, 0x00CE, 0},
    {16, 0x00E1, 0},
};

signed char D_800C3298[] = {-1, 0, 1, 0, 0, 1, 0, -1};

// TODO: give these proper names
AbstRes abst_resources_800C32A0[] =
{
    {0x00000FD3, 0x00000837, 0x00002657},
    {0x00000FD9, 0x0000083C, 0x00002E07},
    {0x000061D1, 0x00000842, 0x000017D6},
    {0x000061D7, 0x00000845, 0x00002478},
    {0x000088D4, 0x0000084A, 0x0000276E},
    {0x000088DA, 0x0000084F, 0x00000544},
    {0x000035A6, 0x00000850, 0x000021E8},
    {0x000035AC, 0x00000855, 0x000025DB},
    {0x000059BF, 0x0000085A, 0x00002D5A},
    {0x000059C5, 0x00000860, 0x000006DF},
    {0x0000D1AF, 0x00000861, 0x000026FD},
    {0x0000D1B5, 0x00000866, 0x000026C0},
    {0x0000AD18, 0x0000086B, 0x00002467},
    {0x0000AD1E, 0x00000870, 0x00001890},
    {0x00000F8F, 0x00000874, 0x0000188C},
    {0x00000F95, 0x00000878, 0x00002CC3},
    {0x0000335B, 0x0000087E, 0x0000255C},
    {0x00003361, 0x00000883, 0x000021BE},
    {0x000093D1, 0x00000888, 0x000026D9},
    {0x000093D7, 0x0000088D, 0x00002824},
    {0x000094D4, 0x00000893, 0x000024D9},
    {0x000094DA, 0x00000898, 0x0000304C},
    {0x0000494D, 0x0000089F, 0x00001AB5},
    {0x00004953, 0x000008A3, 0x00002546},
    {0x00004DBE, 0x000008A8, 0x000027B1},
    {0x00004DC4, 0x000008AD, 0x00001D11},
    {0x000018A3, 0x000008B1, 0x00001928},
    {0x000018A9, 0x000008B5, 0x00002EB7},
    {0x000086E7, 0x000008BB, 0x0000209B},
    {0x000086ED, 0x000008C0, 0x000021AA},
    {0x00005E14, 0x000008C5, 0x00002CD1},
    {0x00005E1A, 0x000008CB, 0x000029B9},
    {0x000069AB, 0x000008D1, 0x000031FB},
    {0x000069B1, 0x000008D8, 0x000034F1},
    {0x00008115, 0x000008DF, 0x00002CCC},
    {0x0000811B, 0x000008E5, 0x000020D7},
    {0x0000CE7C, 0x000008EA, 0x000020BD},
    {0x0000CE82, 0x000008EF, 0x00002345},
    {0x00007990, 0x000008F4, 0x000029C8},
    {0x00007996, 0x000008FA, 0x0000221E},
    {0x0000B0A2, 0x000008FF, 0x00001E4A},
    {0x0000B0A8, 0x00000903, 0x00002848},
    {0x00009166, 0x00000909, 0x00001AE9},
    {0x0000916C, 0x0000090D, 0x00002EA3},
    {0x00004B62, 0x00000913, 0x000028A1},
    {0x00004B68, 0x00000919, 0x00000E9B},
    {0x0000AFBE, 0x0000091B, 0x00001F90},
    {0x0000AFC4, 0x0000091F, 0x00001770},
    {0x0000104B, 0x00000922, 0x000027E7},
    {0x00001051, 0x00000927, 0x000012C2},
    {0x0000A854, 0x0000092A, 0x00001B64},
    {0x0000A85A, 0x0000092E, 0x00001777},
    {0x0000844F, 0x00000931, 0x00002DB4},
    {0x00008455, 0x00000937, 0x00002931},
    {0x00008DFD, 0x0000093D, 0x0000278A},
    {0x00008E03, 0x00000942, 0x000021A7},
    {0x0000B2D9, 0x00000947, 0x0000199D},
    {0x0000B2DF, 0x0000094B, 0x00002A45},
    {0x00008B76, 0x00000951, 0x000027C5},
    {0x00008B7C, 0x00000956, 0x00000F3C},
    {0x0000C2B0, 0x00000958, 0x00001E66},
    {0x0000C2B6, 0x0000095C, 0x00001F25},
    {0x0000D28A, 0x00000960, 0x00002DDE},
    {0x0000D290, 0x00000966, 0x000015CB},
    {0x00001695, 0x00000969, 0x000020EE},
    {0x0000169B, 0x0000096E, 0x00000D3D},
    {0x00007F45, 0x00000970, 0x000014B9},
    {0x00007F4B, 0x00000973, 0x00002D84},
    {0x0000CBCC, 0x00000979, 0x00002011},
    {0x0000CBD2, 0x0000097E, 0x00002044},
    {0x0000A02C, 0x00000983, 0x000028CF},
    {0x0000A032, 0x00000989, 0x000028EB},
    {0x00009664, 0x0000098F, 0x00002D22},
    {0x0000966A, 0x00000995, 0x000020C4},
    {0x00001953, 0x0000099A, 0x000028E7},
    {0x00001959, 0x000009A0, 0x00003932},
    {0x00006B08, 0x000009A8, 0x000030AD},
    {0x00006B0E, 0x000009AF, 0x0000252C},
    {0x0000876C, 0x000009B4, 0x00001EB8},
    {0x00008772, 0x000009B8, 0x00002582},
    {0x0000FC00, 0x000009BD, 0x00002AD0},
    {0x0000FC06, 0x000009C3, 0x00002631},
    {0x00006975, 0x000009C8, 0x00002B8E},
    {0x0000697B, 0x000009CE, 0x00002DAE},
    {0x0000783A, 0x000009D4, 0x0000260B},
    {0x00007840, 0x000009D9, 0x000024FD},
    {0x00009181, 0x000009DE, 0x00001CBF},
    {0x00009187, 0x000009E2, 0x000029C6},
    {0x00009295, 0x000009E8, 0x0000232F},
    {0x0000929B, 0x000009ED, 0x00001AF0},
    {0x00007953, 0x000009F1, 0x00002862},
    {0x00007959, 0x000009F7, 0x000006F8},
    {0x00005083, 0x000009F8, 0x00002902},
    {0x00005089, 0x000009FE, 0x00001801},
    {0x0000F1E2, 0x00000A02, 0x00000F72},
    {0x0000F1E8, 0x00000A04, 0x000025C2},
    {0x00002EC5, 0x00000A09, 0x00002DE5},
    {0x00002ECB, 0x00000A0F, 0x00001EAC},
    {0x00002F87, 0x00000A13, 0x00003148},
    {0x00002F8D, 0x00000A1A, 0x00001FA1},
};

void func_800C464C(Work *work, int index)
{
    RECT  rect;
    KCB  *kcb;
    void *buf;

    kcb = &work->kcb[index];
    
    rect.x = work->font_x;
    rect.y = work->font_y;
    rect.w = 128;
    rect.h = 21;
    
    work->field_51C[index].x0 = work->font_x;
    work->field_51C[index].y0 = work->font_y;

    work->field_51C[index].x1 = work->font_x + 64;
    work->field_51C[index].y1 = work->font_y;
    work->font_y += 21;

    font_init_kcb(kcb, &rect, work->clut_x, work->clut_y);
    
    work->field_51C[index].cx = work->clut_x;
    work->field_51C[index].cy = work->clut_y;
    work->clut_y += 21;

    font_set_kcb(kcb, -1, -1, 0, 6, 2, 0);

    buf = GV_AllocMemory(GV_NORMAL_MEMORY, font_get_buffer_size(kcb));
    font_set_buffer(kcb, buf);

    font_set_color(kcb, 0, D_800C3238[index].color, 0);
    font_clut_update(kcb);
}

void func_800C47A8(Work *work, int index)
{
    KCB *kcb;

    if (work->field_51C[index].string)
    {
        kcb = &work->kcb[index];
        font_print_string(kcb, work->field_51C[index].string);
        font_update(kcb);
        font_clut_update(kcb);

        work->field_51C[index].unk1 = 256;
        work->field_51C[index].unk2 = kcb->max_height;
        
        work->field_51C[index].rect.x = D_800C3238[index].x;
        work->field_51C[index].rect.y = D_800C3238[index].y;

        work->field_51C[index].unk3 = 256;
        work->field_51C[index].unk4 = kcb->max_height;
        
        work->field_51C[index].rect.w = D_800C3238[index].x + 256;
        work->field_51C[index].rect.h = D_800C3238[index].y;

        work->field_51C[index].string = NULL;
        work->field_51C[index].num = 1;
    }
}

void func_800C4890(Work *work, u_long *ot, int arg2)
{
    int       i, j;
    SPRT     *sprt;
    DR_TPAGE *tpage;
    int       index;
    SPRT     *sprt1;
    SPRT     *sprt2;

    index = 0;
    for (i = 0; i < work->field_2C4 + 3; i++)
    {
        if (work->field_51C[index].num == 1)
        {
            sprt = &work->field_51C[index].text_sprt[GV_Clock];
            setSprt(sprt);
            setRGB0(sprt, 128, 128, 128);
            setSemiTrans(sprt, 1);
            LCOPY(&work->field_51C[index].rect.x, &sprt->x0);
            LCOPY(&work->field_51C[index].unk1, &sprt->w);
            setUV0(sprt, 0, work->field_51C[index].y0);
            setClut(sprt, work->field_51C[index].cx, work->field_51C[index].cy);
            addPrim(ot, sprt);
            index++;
        }
    }

    tpage = &work->tpage[0];
    setDrawTPage(tpage, 1, 0, getTPage(0, 1, 704, 256));
    addPrim(ot, tpage);

    index = 0;
    for (i = 0; i < work->field_2C4 + 3; i++)
    {
        if (work->field_51C[index].num == 1)
        {
            sprt = &work->field_51C[index].text_sprt2[GV_Clock];
            setSprt(sprt);
            setRGB0(sprt, 128, 128, 128);
            setSemiTrans(sprt, 1);
            LCOPY(&work->field_51C[index].rect.w, &sprt->x0);
            LCOPY(&work->field_51C[index].unk3, &sprt->w);
            setUV0(sprt, 0, work->field_51C[index].y1);
            setClut(sprt, work->field_51C[index].cx, work->field_51C[index].cy);
            addPrim(ot, sprt);
            index++;
        }
    }

    tpage = &work->tpage[1];
    setDrawTPage(tpage, 1, 0, getTPage(0, 1, 768, 256));
    addPrim(ot, tpage);

    index = 0;
    for (i = 0; i < work->field_2C4 + 3; i++)
    {
        if (work->field_51C[index].num == 1)
        {        
            sprt = &work->field_51C[index].text_sprt3[GV_Clock];
            setSprt(sprt);
            setRGB0(sprt, 128, 128, 128);
            setSemiTrans(sprt, 1);
            LCOPY(&work->field_51C[index].rect.x, &sprt->x0);
            LCOPY(&work->field_51C[index].unk1, &sprt->w);
            setUV0(sprt, 0, work->field_51C[index].y0);
            setClut(sprt, work->field_51C[index].cx, work->field_51C[index].cy);
            addPrim(ot, sprt);
            index++;
        }
    }

    tpage = &work->tpage[4];
    setDrawTPage(tpage, 1, 0, getTPage(0, 2, 704, 256));
    addPrim(ot, tpage);

    index = 0;
    for (i = 0; i < work->field_2C4 + 3; i++)
    {
        if (work->field_51C[index].num == 1)
        {        
            sprt = &work->field_51C[index].text_sprt4[GV_Clock];
            setSprt(sprt);
            setRGB0(sprt, 128, 128, 128);
            setSemiTrans(sprt, 1);
            LCOPY(&work->field_51C[index].rect.w, &sprt->x0);
            LCOPY(&work->field_51C[index].unk3, &sprt->w);
            setUV0(sprt, 0, work->field_51C[index].y1);
            setClut(sprt, work->field_51C[index].cx, work->field_51C[index].cy);
            addPrim(ot, sprt);
            index++;
        }
    }

    tpage = &work->tpage[5];
    setDrawTPage(tpage, 1, 0, getTPage(0, 2, 768, 256));
    addPrim(ot, tpage);
    
    if (arg2 == 1)
    {
        index = 0;
        for (i = 0; i < work->field_2C4 + 3; i++)
        {
            if (work->field_51C[index].num == 1)
            {
                sprt2 = work->field_51C[index].text_sprt_outline[GV_Clock];
                sprt1 = &work->field_51C[index].text_sprt[GV_Clock];

                for (j = 0; j < 8; j += 2)
                {
                    *sprt2 = *sprt1;
                    setSprt(sprt2);
                    setRGB0(sprt2, 128, 128, 128);
                    setSemiTrans(sprt2, 1);
                    sprt2->x0 += D_800C3298[j];
                    sprt2->y0 += D_800C3298[j + 1];
                    addPrim(ot, sprt2);
                    sprt2++;
                }

                index++;
            }
        }

        tpage = &work->tpage[2];
        setDrawTPage(tpage, 1, 0, getTPage(0, 2, 704, 256));
        addPrim(ot, tpage);

        index = 0;
        for (i = 0; i < work->field_2C4 + 3; i++)
        {
            if (work->field_51C[index].num == 1)
            {
                sprt2 = work->field_51C[index].text_sprt_outline2[GV_Clock];
                sprt1 = &work->field_51C[index].text_sprt2[GV_Clock];

                for (j = 0; j < 8; j += 2, sprt++)
                {
                    *sprt2 = *sprt1;
                    setSprt(sprt2);
                    setRGB0(sprt2, 128, 128, 128);
                    setSemiTrans(sprt2, 1);
                    sprt2->x0 += D_800C3298[j];
                    sprt2->y0 += D_800C3298[j + 1];
                    addPrim(ot, sprt2);
                    sprt2++;
                }
                
                index++;
            }
        }
        
        tpage = &work->tpage[3];
        setDrawTPage(tpage, 1, 0, getTPage(0, 2, 768, 256));
        addPrim(ot, tpage);
    }
}

void abst_800C5198(Work *work, int index, int col)
{
    font_set_color(&work->kcb[index], 0, col, 0);
    font_clut_update(&work->kcb[index]);
}

void *abst_800C51E8(KCB *kcb)
{
    return kcb->cbuffer;
}

void abst_800C51F4(Work *work)
{
    POLY_FT4 *src;
    POLY_FT4 *dst;
    int       i;

    src = work->polys1;
    dst = (POLY_FT4 *)work->prim1->packs[GV_Clock];
    for (i = 0; i < 6; i++)
    {
        *dst = *src;
        SSTOREL(work->attrs1[i], dst);
        src++;
        dst++;
    }

    src = work->polys2;
    dst = (POLY_FT4 *)work->prim2->packs[GV_Clock];
    for (i = 0; i < 9; i++)
    {
        *dst = *src;
        SSTOREL(work->attrs2[i], dst);
        src++;
        dst++;
    }
}

void abst_800C5318(MenuPrim *prim, int x, int y, int w, int h)
{
    TILE *pTile;

    _NEW_PRIM(pTile, prim);

    LSTORE(0x72A452, &pTile->r0);
    setTile(pTile);
    pTile->x0 = x;
    pTile->y0 = y;
    pTile->w = w;
    pTile->h = h;
    setSemiTrans(pTile, 0);
    addPrim(prim->ot, pTile);

    radio_draw_face_frame(prim, x, y, w, h);
    radio_draw_face_frame(prim, x, y, w, h);
}

void func_800C5410(Work *work)
{
    int       press;
    int       i;
    int       r, g, b;
    POLY_FT4 *poly;
    int       shade;
    int       col;

    press = work->pad->press;

    work->primbuf.next = work->primbuf.buf[GV_Clock];
    work->primbuf.ot = DG_Chanl(1)->ot[GV_Clock];

    switch (work->field_1D64)
    {
    case 0:
        if (work->field_1D5C < 5)
        {
            MENU_Locate(90, 90, 0x10);
            MENU_Color(192, 192, 192);
            MENU_Printf("READ MISSION LOG?");

            abst_800C5318(&work->primbuf, 92, 85, 130, 15);
        }
        else if (work->field_1D5C < 10)
        {
            MENU_Locate(90, 90 - (work->field_1D5C - 4) * 8, 0x10);
            MENU_Color(192, 192, 192);
            MENU_Printf("READ MISSION LOG?");

            abst_800C5318(&work->primbuf, 92, 85, 130, 15);
        }
        else if (work->field_1D5C == 10)
        {
            MENU_Locate(90, 50, 0x10);
            MENU_Color(86, 137, 116);
            MENU_Printf("READ MISSION LOG?");

            MENU_Locate(100, 105, 0x10);
            MENU_Color(192, 192, 192);
            MENU_Printf("YES");

            MENU_Locate(200, 105, 0x10);
            MENU_Color(46, 72, 61);
            MENU_Printf("NO");

            abst_800C5318(&work->primbuf, 92, 85, 130, 15);
        }
        else if (work->field_1D5C < 14)
        {
            MENU_Locate(90, 50, 0x10);
            MENU_Color(86, 137, 116);
            MENU_Printf("READ MISSION LOG?");

            MENU_Locate(100, 105, 0x10);
            MENU_Color(192, 192, 192);
            MENU_Printf("YES");

            MENU_Locate(200, 105, 0x10);
            MENU_Color(46, 72, 61);
            MENU_Printf("NO");

            abst_800C5318(&work->primbuf, 92, (work->field_1D5C - 10) * 5 + 85, 130 - (work->field_1D5C - 10) * 30, 15);
        } else {
            MENU_Locate(90, 50, 0x10);
            MENU_Color(86, 137, 116);
            MENU_Printf("READ MISSION LOG?");

            MENU_Locate(100, 105, 0x10);
            if (work->field_1D68 == 0)
            {
                MENU_Color(192, 192, 192);
            }
            else
            {
                MENU_Color(46, 72, 61);
            }
            MENU_Printf("YES");

            MENU_Locate(200, 105, 0x10);
            if (work->field_1D68 == 1)
            {
                MENU_Color(192, 192, 192);
            }
            else
            {
                MENU_Color(46, 72, 61);
            }
            MENU_Printf("NO");

            if (work->field_1D68 == 0)
            {
                abst_800C5318(&work->primbuf, 92, 100, 40, 15);
            }
            else
            {
                abst_800C5318(&work->primbuf, 188, 100, 40, 15);
            }

            if (press & (PAD_START | PAD_CIRCLE))
            {
                if (work->field_1D68 == 0)
                {
                    GM_SeSet2(0, 63, SE_MENU_SELECT);

                    work->field_1D64 = 1;

                    for (i = 0; i < 6; i++)
                    {
                        work->attrs1[i] = 0x100;
                    }
                    
                    work->field_1D5C = 0;

                    r = 86;
                    g = 137;
                    b = 116;
                    poly = work->polys1;
                    setRGB0(&poly[2], r, g, b);
                    setRGB0(&poly[3], r, g, b);
                    setRGB0(&poly[4], r, g, b);
                    setRGB0(&poly[5], r, g, b);

                    for (i = 0; i < 1; i++)
                    {
                        abst_800C5198(work, i, 0);
                    }

                    for (i = 0; i < 9; i++)
                    {
                        work->attrs2[i] = 0x200;
                    }

                    poly = work->polys2;
                    for (i = 0; i < 9; i++)
                    {
                        setRGB0(poly, 0, 0, 0);
                        poly++;
                    }
                }
                else
                {
                    GM_SeSet2(0, 63, SE_MENU_EXIT);
                    GCL_ExecProc(work->end_proc, NULL);
                    GV_DestroyActor(work);
                }
            }
            else if (press & PAD_CROSS)
            {
                GM_SeSet2(0, 63, SE_MENU_EXIT);
                GCL_ExecProc(work->end_proc, NULL);
                GV_DestroyActor(work);
            }
            else if (press & PAD_UDLR)
            {
                GM_SeSet2(0, 63, SE_MENU_CURSOR);

                if (work->field_1D68 == 0)
                {
                    work->field_1D68 = 1;
                }
                else
                {
                    work->field_1D68 = 0;
                }
            }

            work->field_5DA0 = 1;
        }

        work->field_1D5C++;
        break;
    case 1:
        if (work->field_1D5C < 9)
        {
            poly = work->polys2;
            shade = (work->field_1D5C * 255) / 8;
            for (i = 0; i < 9; i++)
            {
                setRGB0(poly, shade, shade, shade);
                poly++;
            }

            poly = work->polys1;
            r = (work->field_1D5C * 86) / 64;
            g = (work->field_1D5C * 137) / 64;
            b = (work->field_1D5C * 116) / 64;
            for (i = 0; i < 2; i++)
            {
                setRGB0(poly, r, g, b);
                poly++;
            }

            col = 0;
            for (i = 1; i < work->field_2C4 + 1; i++)
            {
                abst_800C5198(work, i, col);
            }

            work->field_1D5C++;
        }
        else if (work->field_1D5C < 65)
        {
            poly = work->polys1;
            r = (work->field_1D5C * 86) / 64;
            g = (work->field_1D5C * 137) / 64;
            b = (work->field_1D5C * 116) / 64;
            for (i = 0; i < 2; i++)
            {
                setRGB0(poly, r, g, b);
                poly++;
            }

            col = 0;
            for (i = 1; i < work->field_2C4 + 1; i++)
            {
                abst_800C5198(work, i, col);
            }

            work->field_1D5C++;
        }
        else if (work->field_1D5C < 81)
        {
            poly = work->polys1;
            r = 86;
            g = 137;
            b = 116;
            for (i = 0; i < 6; i++)
            {
                setRGB0(poly, r, g, b);
                poly++;
            }

            col = 0;
            for (i = 1; i < work->field_2C4 + 1; i++)
            {
                abst_800C5198(work, i, col);
            }

            work->field_1D5C++;
        }
        else if (work->field_1D5C < 145)
        {
            poly = work->polys1;
            r = 86;
            g = 137;
            b = 116;
            for (i = 0; i < 6; i++)
            {
                setRGB0(poly, r, g, b);
                poly++;
            }

            shade = ((work->field_1D5C - 80) * 25) / 64;
            col = (shade << 10) | (shade << 5) | shade;
            for (i = 1; i < work->field_2C4 + 1; i++)
            {
                abst_800C5198(work, i, col);
            }

            if (++work->field_1D5C < 89)
            {
                work->field_5DA0 = 0;
            }
            else
            {
                work->field_5DA0 = 1;
            }
        }
        else
        {
            work->field_1D64 = 2;
            work->field_5DA0 = 1;
        }
        break;

    case 2:
        if (press & PAD_SELECT)
        {
            if (work->field_5DA4 == 0)
            {
                work->field_5DA4 = 1;
                for (i = 1; i < work->field_2C4 + 1; i++)
                {
                    abst_800C5198(work, i, 0);
                }
            }
            else 
            {
                work->field_5DA4 = 0;
                for (i = 1; i < work->field_2C4 + 1; i++)
                {
                    abst_800C5198(work, i, 0x6739);
                }
            }
        }
        else if (press & (PAD_CROSS | PAD_CIRCLE))
        {
            GM_SeSet2(0, 63, SE_MENU_EXIT);
            work->field_1D64 = 3;
            work->field_1D5C = 0;
        }
        break;
    case 3:        
        if (work->field_1D5C < 97)
        {
            if (work->field_1D5C < 9)
            {
                poly = work->polys2;
                shade = 255 - (work->field_1D5C * 255) / 8;
                for (i = 0; i < 9; i++)
                {
                    setRGB0(poly, shade, shade, shade);
                    poly++;
                }
            }

            poly = work->polys1;
            r = 86 - (work->field_1D5C * 86) / 96;
            g = 137 - (work->field_1D5C * 137) / 96;
            b = 116 - (work->field_1D5C * 116) / 96;
            for (i = 0; i < 6; i++)
            {
                setRGB0(poly, r, g, b);
                poly++;
            }

            shade = 25 - (work->field_1D5C * 25) / 96;
            col = (shade << 10) | (shade << 5) | shade;
            for (i = 1; i < work->field_2C4 + 1; i++)
            {
                abst_800C5198(work, i, col);
            }

            if (work->field_5DA4 == 1)
            {
                for (i = 1; i < work->field_2C4 + 1; i++)
                {
                    abst_800C5198(work, i, 0);
                }
            }

            work->field_1D5C++;
        }
        else
        {
            GCL_ExecProc(work->end_proc, NULL);
            GV_DestroyActor(work);
        }
        break;
    }

    func_800C4890(work, DG_Chanl(1)->ot[GV_Clock], work->field_5DA0);
    abst_800C51F4(work);
}

void func_800C5F8C(Work *work)
{
    int   i;
    void *buf;

    GM_FreePrim(work->prim1);
    GM_FreePrim(work->prim2);
    
    for (i = 0; i < 12; i++)
    {
        buf = abst_800C51E8(&work->kcb[i]);
        GV_FreeMemory(GV_NORMAL_MEMORY, buf);
    }
}

void abst_800C6028(Work *work, int opt)
{
    AbstRes *res;
    int      i;
    int      found;
    int      file;
    int      size;
    void    *buf;

    found = -1;
    file = 0;
    size = 0;
    for (i = 0; i < 100; i++)
    {
        res = &abst_resources_800C32A0[i];
        if (opt == res->id)
        {
            found = i;
            file = res->file;
            size = res->size;
        }
    }

    if (found != -1)
    {
        buf = GV_Malloc(size);
        FS_LoadFileRequest(6, file, size, buf);
        while (FS_LoadFileSync() > 0)
        {
            mts_wait_vbl(1);
        }

        DG_LoadInitPcx(buf, opt);
        printf("Texture LoadImage Finish!\n");
        GV_Free(buf);
    }
    else
    {
        printf("Cannot Find Texture\n");
    }
}

void func_800C6114(void *work, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe)
{
    setPolyFT4(poly);
    setRGB0(poly, 0, 0, 0);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);
}

static inline void InitTex(POLY_FT4 *poly, DG_TEX *tex, int x, int y)
{
    int x0, x1, y0, y1;

    x0 = tex->off_x;
    x1 = x0 + tex->w + x;
    y0 = tex->off_y;
    y1 = y0 + tex->h + y;

    setUV4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}

static void Init_Res(void *work, int name, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe, int mode)
{
    DG_TEX *tex;
    
    func_800C6114(work, poly, x0, y0, x1, y1, abe);
    tex = DG_GetTexture(name);

    if (mode == 0)
    {
        InitTex(poly, tex, 1, 1);
    }
    else if (mode == 1)
    {
        InitTex(poly, tex, 1, 0);
    }
    else if (mode == 2)
    {
        InitTex(poly, tex, 0, 1);
    }
    else if (mode == 3)
    {
        InitTex(poly, tex, 0, 0);
    }
}

static int GetResources(Work *work, int where)
{
    char     *opt;
    POLY_FT4 *poly;
    int       i;

    GM_CurrentMap = where;

    work->font_x = 704;
    work->font_y = 256;
    work->clut_x = 704;
    work->clut_y = 276;

    work->prim1 = GM_MakePrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 6, NULL, NULL);
    work->prim2 = GM_MakePrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 9, NULL, NULL);

    poly = work->polys1;
    i = 0;
    
    opt = GCL_GetOption('l');
    if (opt)
    {
        abst_800C6028(work, GCL_StrToInt(opt));
        Init_Res(work, GCL_StrToInt(opt), poly, -160, -82, 0, 82, 0, 0);
    }
    else
    {
        printf("Cannot Set Texture!!\n");
    }

    poly++;
    work->attrs1[i] = 0;
    i++;
    
    opt = GCL_GetOption('r');
    if (opt)
    {
        abst_800C6028(work, GCL_StrToInt(opt));
        Init_Res(work, GCL_StrToInt(opt), poly, 0, -82, 160, 82, 0, 0);
    }
    else
    {
        printf("Cannot Set Texture!!\n");
    }

    poly++;
    work->attrs1[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("abst_u_l"), poly, -160, -112, 0, -82, 0, 0);

    poly++;
    work->attrs1[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("abst_u_r"), poly, 0, -112, 160, -82, 0, 0);

    poly++;
    work->attrs1[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("abst_d_l"), poly, -160, 82, 0, 112, 1, 0);

    poly++;
    work->attrs1[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("abst_d_r"), poly, 0, 82, 160, 112, 1, 0);

    work->attrs1[i] = 0;

    poly = work->polys2;
    i = 0;

    Init_Res(work, GV_StrCode("cur_lu"), poly, -33, 81, -25, 89, 0, 0);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("cur_ru"), poly, 25, 81, 33, 89, 0, 0);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("cur_ld"), poly, -33, 97, -25, 105, 0, 0);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("cur_rd"), poly, 25, 97, 33, 105, 0, 0);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;
    
    Init_Res(work, GV_StrCode("cur_u"), poly, -25, 81, 25, 89, 0, 2);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("cur_d"), poly, -25, 97, 25, 105, 0, 2);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("cur_l"), poly, -33, 89, -25, 97, 0, 1);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("cur_r"), poly, 25, 89, 33, 97, 0, 1);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("cur_c"), poly, -25, 89, 25, 97, 0, 3);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    if (GCL_GetOption('e'))
    {
        work->end_proc = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->end_proc = -1;
    }

    if (GCL_GetOption('i'))
    {
        work->field_2C4 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->field_2C4 = 12;
    }

    for (i = 0; i < work->field_2C4 + 1; i++)
    {
        work->field_51C[i].string = GCL_GetString(GCL_NextStr());
        work->field_51C[i].num = 0;
        func_800C464C(work, i);
    }

    for (i = 0; i < work->field_2C4 + 1; i++)
    {
        func_800C47A8(work, i);
    }
    
    work->pad = &GV_PadData[2];
    work->field_1D5C = 0;
    work->field_1D64 = 0;
    work->field_1D68 = 0;

    for (i = 0; i < 1; i++)
    {
        abst_800C5198(work, i, 0x6739);
    }

    for (i = 1; i < work->field_2C4 + 1; i++)
    {
        abst_800C5198(work, i, 0);
    }

    work->primbuf.buf[0] = work->field_1DA0;
    work->primbuf.buf[1] = work->field_3DA0;

    sub_80048124();
    work->field_5DA4 = 0;
    return 0;
}

void *NewAbstract(int name, int where)
{
    Work *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = GV_NewActor(GV_ACTOR_MANAGER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, func_800C5410, func_800C5F8C, "abst.c");
        if (GetResources(work, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}
