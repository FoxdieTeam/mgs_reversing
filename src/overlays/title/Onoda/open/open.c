#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Font/font.h"
#include "Menu/menuman.h"
#include "SD/sd.h"
#include "Game/game.h"

typedef struct _OpenWork
{
    GV_ACT   actor;
    DG_PRIM *prim[4]; 
    char     pad[0x110];
    int      f140[9];
    char     pad2[0x668];
    POLY_FT4 f7CC_polys[9];
    char     pad3[0x140]; // 934
    int      fA74;
    char     pad4[0x30]; // A78
    char     fAA8; // Could be array or part of some struct (KCB?)
    char     fAA9;
    char     fAAA;
    char     fAAB;
    char     fAAC;
    char     fAAD;
    char     fAAE;
    char     fAAF;
    char     pad5[0x5C]; // AB0
    int      fB0C;
    char     pad6[0x3C]; // B10
    KCB      kcb[24]; // B4C
    char     pad7[0x1540]; // F6C
    int      f24AC;
    int      f24B0;
    int      f24B4;
    int      f24B8;
    int      f24BC;
    int      f24C0;
    int      f24C4;
    int      f24C8;
    int      f24CC;
    int      f24D0;
    int      f24D4;
    int      f24D8;
    int      f24DC;
    int      f24E0;
    int      f24E4;
    int      f24E8;
    int      f24EC;
    int      f24F0;
    int      f24F4;
    int      f24F8_proc;
    char     pad8[8];
} OpenWork;

extern int title_dword_800D92D0;
extern int title_dword_800C33D4;

extern const char title_aMemorycardslot_800D8FAC[];      // = "MEMORY CARD SLOT 1  :  "
extern const char title_aFull_800D8FC4[];                // = "   FULL"
extern const char title_aNocard_800D8FCC[];              // = "NO CARD"
extern const char title_aMemorycardslot_800D8FD4[];      // = "MEMORY CARD SLOT 2  :  "
extern const char title_aDoyouwanttocontinue_800D8FEC[]; // = "DO YOU WANT TO CONTINUE\n"
extern const char title_aYourgamelikethis_800D9008[];    // = "YOUR GAME LIKE THIS?"
extern const char title_aYes_800D9020[];                 // = "YES"
extern const char title_aNo_800D9024[];                  // = "NO"
extern const char aOpenC[];                              // = "open.c"

extern int GM_GameStatus_800AB3CC;
extern int gDiskNum_800ACBF0;

#define EXEC_LEVEL 1

#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C4500.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C4674.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C47B8.s")
void title_open_800C47B8(OpenWork *, int);

void title_open_800C4AD0(OpenWork *work, int index, int color)
{
    KCB *kcb;

    kcb = &work->kcb[index];
    font_set_color_80044DC4(kcb, 0, color, 0);
    font_clut_update_80046980(kcb);
}

void * title_open_800C4B20(KCB *kcb)
{
    return kcb->font_clut_buffer;
}

#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C4B2C.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C4B94.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C4BD4.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C4C38.s")

void title_open_800C4F1C(OpenWork *work, int x0, int y0, int xsize, int ysize, int color, int mode)
{
    POLY_FT4 *polys;
    int i;

    polys = work->f7CC_polys;
    for (i = 0; i < 9; i++)
    {
        work->f140[i] = 0x100;
        setRGB0(&polys[i], color, color, color);
    }

    if (mode == 0)
    {
        setXY4(&polys[0], x0 - 8, y0 - 8, x0, y0 - 8, x0 - 8, y0, x0, y0);
        setXY4(&polys[1], x0 + xsize, y0 - 8, x0 + xsize + 8, y0 - 8, x0 + xsize, y0, x0 + xsize + 8, y0);
        setXY4(&polys[2], x0 - 8, y0 + ysize, x0, y0 + ysize, x0 - 8, y0 + ysize + 8, x0, y0 + ysize + 8);
        setXY4(&polys[3], x0 + xsize, y0 + ysize, x0 + xsize + 8, y0 + ysize, x0 + xsize, y0 + ysize + 8, x0 + xsize + 8, y0 + ysize + 8);
        setXY4(&polys[4], x0, y0 - 8, x0 + xsize, y0 - 8, x0, y0, x0 + xsize, y0);
        setXY4(&polys[5], x0, y0 + ysize, x0 + xsize, y0 + ysize, x0, y0 + ysize + 8, x0 + xsize, y0 + ysize + 8);
        setXY4(&polys[6], x0 - 8, y0, x0, y0, x0 - 8, y0 + ysize, x0, y0 + ysize);
        setXY4(&polys[7], x0 + xsize, y0, x0 + xsize + 8, y0, x0 + xsize, y0 + ysize, x0 + xsize + 8, y0 + ysize);
        setXY4(&polys[8], x0, y0, x0 + xsize, y0, x0, y0 + ysize, x0 + xsize, y0 + ysize);
    }
    else if (mode == 1)
    {
        setXY4(&polys[0], x0 - 6, y0 - 6, x0 + 2, y0 - 6, x0 - 6, y0 + 2, x0 + 2, y0 + 2);
        setXY4(&polys[1], x0 + xsize - 2, y0 - 6, x0 + xsize + 6, y0 - 6, x0 + xsize - 2, y0 + 2, x0 + xsize + 6, y0 + 2);
        setXY4(&polys[2], x0 - 6, y0 + ysize - 2, x0 + 2, y0 + ysize - 2, x0 - 6, y0 + ysize + 6, x0 + 2, y0 + ysize + 6);
        setXY4(&polys[3], x0 + xsize - 2, y0 + ysize - 2, x0 + xsize + 6, y0 + ysize - 2, x0 + xsize - 2, y0 + ysize + 6, x0 + xsize + 6, y0 + ysize + 6);
        setXY4(&polys[4], x0 + 2, y0 - 6, x0 + xsize - 2, y0 - 6, x0 + 2, y0 + 2, x0 + xsize - 2, y0 + 2);
        setXY4(&polys[5], x0 + 2, y0 + ysize - 2, x0 + xsize - 2, y0 + ysize - 2, x0 + 2, y0 + ysize + 6, x0 + xsize - 2, y0 + ysize + 6);
        setXY4(&polys[6], x0 - 6, y0 + 2, x0 + 2, y0 + 2, x0 - 6, y0 + ysize - 2, x0 + 2, y0 + ysize - 2);
        setXY4(&polys[7], x0 + xsize - 2, y0 + 2, x0 + xsize + 6, y0 + 2, x0 + xsize - 2, y0 + ysize - 2, x0 + xsize + 6, y0 + ysize - 2);
        setXY4(&polys[8], x0 + 2, y0 + 2, x0 + xsize - 2, y0 + 2, x0 + 2, y0 + ysize - 2, x0 + xsize - 2, y0 + ysize - 2);
    }
}

#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5200.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5238.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5360.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C53E0.s")

int title_open_800C4B2C();

int title_open_800C5620()
{
    return title_open_800C4B2C() == 1;
}

#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5644.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5750.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5760.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C593C.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5CB8.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5CF0.s")

void title_open_800C5D10(OpenWork *work)
{
    int i;

    for (i = 0; i < 9; i++)
    {
        work->f140[i] = 0;
    }
}

#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5D30.s")

void title_open_800C61E0(OpenWork *work, GCL_ARGS *args)
{
    GM_SeSet2_80032968(0, 0x3F, 0x66);
    if (gDiskNum_800ACBF0 == 0)
    {
        if (SD_800886F4() == 0)
        {
            GCL_ExecProc_8001FF2C(work->f24F8_proc, args);
            GV_DestroyActor_800151C8(&work->actor);
        }
    }
    else
    {
        work->fB0C = 1;
        work->fA74 = 9;
        work->f24EC = 0;
        work->f24AC = 0;
        work->f24B0 = 0;
        work->f24B4 = 0; 
        work->f24B8 = 0;
        work->f24BC = 0;
        title_dword_800C33D4 = work->f24F8_proc;
    }
}

#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C628C.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CCDC8.s")

void title_open_800CD074(OpenWork *work)
{
    int sqrt1, sqrt2;
    int val1, val2, val3;
    int val1_2, val2_2, val3_2;

    val1 = work->fAA8;
    val2 = work->fAA9;
    val3 = work->fAAA;
    sqrt1 = SquareRoot0(val1 * val1 + val2 * val2 + val3 * val3);
    
    val1_2 = 0xFF - val1;
    val2_2 = 0xFF - val2;
    val3_2 = 0xFF - val3; 
    sqrt2 = SquareRoot0(val1_2 * val1_2 + val2_2 * val2_2 + val3_2 * val3_2);
    
    if (sqrt2 != 0)
    {
        val1_2 = (val1_2 * sqrt1) / sqrt2;
        if (val1_2 > 0xFF)
        {
            val1_2 = 0xFF;
        }
        val2_2 = (val2_2 * sqrt1) / sqrt2;
        if (val2_2 > 0xFF)
        {
            val2_2 = 0xFF;
        }
        val3_2 = (val3_2 * sqrt1) / sqrt2;
        if (val3_2 > 0xFF)
        {
            val3_2 = 0xFF;
        }
    }
    else
    {
        val1_2 = 0xFF;
        val2_2 = 0xFF;
        val3_2 = 0xFF;
    }

    work->fAAC = val1_2;
    work->fAAD = val2_2;
    work->fAAE = val3_2;
}

#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CD23C.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CD320.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CD3B8.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CD800.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CDB4C.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CDB9C.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CDBF8.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CDE44.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CE378.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CE4A8.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CE544.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CE5F8.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CE6AC.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CE748.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CEB14.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CF794.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D1B74.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D1CB4.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D2374.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D2460.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D2E44.s")

void title_open_800D3500(OpenWork *work, int arg1)
{
    int i;

    for (i = 0; i < 24; i++)
    {
        title_open_800C4AD0(work, i, 0);
    }

    if (work->fA74 >= 18 && work->fA74 <= 19)
    {
        title_open_800C4AD0(work, 21, 0x6739);

        MENU_Locate_80038B34(54, 60, 0x10);
        MENU_Color_80038B4C(100, 160, 135);
        MENU_Printf_80038C38(title_aMemorycardslot_800D8FAC);

        if (work->f24F0 == 3)
        {
            MENU_Locate_80038B34(223, 60, 0x10);
            MENU_Color_80038B4C(181, 85, 42);
            MENU_Printf_80038C38(title_aFull_800D8FC4);
        }
        else
        {
            MENU_Locate_80038B34(223, 60, 0x10);
            MENU_Color_80038B4C(181, 85, 42);
            MENU_Printf_80038C38(title_aNocard_800D8FCC);
        }

        MENU_Locate_80038B34(54, 75, 0x10);
        MENU_Color_80038B4C(100, 160, 135);
        MENU_Printf_80038C38(title_aMemorycardslot_800D8FD4);

        if (work->f24F4 == 3)
        {
            MENU_Locate_80038B34(223, 75, 0x10);
            MENU_Color_80038B4C(181, 85, 42);
            MENU_Printf_80038C38(title_aFull_800D8FC4);
        }
        else
        {
            MENU_Locate_80038B34(223, 75, 0x10);
            MENU_Color_80038B4C(181, 85, 42);
            MENU_Printf_80038C38(title_aNocard_800D8FCC);
        }

        MENU_Locate_80038B34(70, 100, 0x10);
        MENU_Color_80038B4C(100, 160, 135);
        MENU_Printf_80038C38(title_aDoyouwanttocontinue_800D8FEC);

        MENU_Locate_80038B34(85, 115, 0x10);
        MENU_Color_80038B4C(100, 160, 135);
        MENU_Printf_80038C38(title_aYourgamelikethis_800D9008);

        if (work->f24E0 == 0)
        {
            MENU_Locate_80038B34(100, 150, 0x10);
            MENU_Color_80038B4C(192, 192, 192);
            MENU_Printf_80038C38(title_aYes_800D9020);

            MENU_Locate_80038B34(200, 150, 0x10);
            MENU_Color_80038B4C(46, 72, 61);
            MENU_Printf_80038C38(title_aNo_800D9024);

            title_open_800C4F1C(work, -68, 33, 40, 15, 255, 1);
        }
        else
        {
            MENU_Locate_80038B34(100, 150, 0x10);
            MENU_Color_80038B4C(46, 72, 61);
            MENU_Printf_80038C38(title_aYes_800D9020);

            MENU_Locate_80038B34(200, 150, 0x10);
            MENU_Color_80038B4C(192, 192, 192);
            MENU_Printf_80038C38(title_aNo_800D9024);

            title_open_800C4F1C(work, 28, 33, 40, 15, 255, 1);
        }
    }

    title_open_800C47B8(work, arg1);
}

#pragma INCLUDE_ASM("asm/overlays/title/OpenAct_800D37F4.s")
void OpenAct_800D37F4(OpenWork *work);

void OpenDie_800D4098(OpenWork *work)
{
    DG_PRIM *prim;
    int      i;
    void    *buf;

    prim = work->prim[0];
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    prim = work->prim[2];
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    prim = work->prim[3];
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    prim = work->prim[1];
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    for (i = 0; i < 24; i++)
    {
        buf = title_open_800C4B20(&work->kcb[i]);
        GV_FreeMemory_80015FD0(2, buf);
    }
}

void title_open_800D4174(OpenWork *work, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe)
{
    setPolyFT4(poly);
    setRGB0(poly, 128, 128, 128);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);
}

static inline void title_open_helper_800D41E4(POLY_FT4 *poly, DG_TEX *tex, int uo, int vo)
{
    int u0, u1;
    int v0, v1;

    u0 = tex->field_8_offx;
    u1 = u0 + tex->field_A_width + uo;
    v0 = tex->field_9_offy;
    v1 = v0 + tex->field_B_height + vo;
    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);

    poly->tpage = tex->field_4_tPage;
    poly->clut = tex->field_6_clut;
}

void title_open_800D41E4(OpenWork *work, int name, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe, int type)
{
    DG_TEX *tex;

    title_open_800D4174(work, poly, x0, y0, x1, y1, abe);

    tex = DG_GetTexture_8001D830(name);
    if (type == 0)
    {
        title_open_helper_800D41E4(poly, tex, 1, 1);
    }
    else if (type == 1)
    {
        title_open_helper_800D41E4(poly, tex, 1, 0);
    }
    else if (type == 2)
    {
        title_open_helper_800D41E4(poly, tex, 0, 1);
    }
    else if (type == 3)
    {
        title_open_helper_800D41E4(poly, tex, 0, 0);
    }
}

void title_open_800D4368(OpenWork *work, int name, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe)
{
    DG_TEX *tex;
    int     u0, u1;
    int     v0, v1;

    tex = DG_GetTexture_8001D830(name);

    setPolyFT4(poly);

    u0 = tex->field_8_offx;
    u1 = u0 + tex->field_A_width + 1;
    v0 = tex->field_9_offy;
    v1 = v0 + tex->field_B_height + 1;
    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);

    poly->tpage = tex->field_4_tPage;
    poly->clut = tex->field_6_clut;

    setRGB0(poly, 0, 0, 0);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);
}

void title_open_800D4464(OpenWork *work, int name, POLY_GT4 *poly, int x0, int y0, int x1, int y1, int abe)
{
    DG_TEX *tex;
    int     u0, u1;
    int     v0, v1;

    tex = DG_GetTexture_8001D830(name);

    setPolyGT4(poly);

    u0 = tex->field_8_offx;
    u1 = u0 + tex->field_A_width + 1;
    v0 = tex->field_9_offy;
    v1 = v0 + tex->field_B_height + 1;
    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);

    poly->tpage = tex->field_4_tPage;
    poly->clut = tex->field_6_clut;

    setRGB0(poly, 0, 0, 0);
    setRGB1(poly, 0, 0, 0);
    setRGB2(poly, 0, 0, 0);
    setRGB3(poly, 0, 0, 0);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);
}

#pragma INCLUDE_ASM("asm/overlays/title/OpenGetResources_800D4584.s")
int  OpenGetResources_800D4584(OpenWork *work, int);

GV_ACT * NewOpen_800D6814(int arg0, int arg1)
{
    OpenWork *work;

    GM_GameStatus_800AB3CC |= 0x4A6000;

    work = (OpenWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(OpenWork));
    title_dword_800D92D0 = 0;

    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)OpenAct_800D37F4, (TActorFunction)OpenDie_800D4098, aOpenC);

        if (OpenGetResources_800D4584(work, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
