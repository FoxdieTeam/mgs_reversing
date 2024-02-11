#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Font/font.h"
#include "Menu/menuman.h"

typedef struct _OpenWork
{
    GV_ACT   actor;
    DG_PRIM *prim[4];
    char     pad[0xA44];
    int      fA74;
    char     pad2[0xD4];
    KCB      kcb[24];
    char     pad3[0x1574];
    int      f24E0;
    char     pad4[0xC];
    int      f24F0;
    int      f24F4;
    char     pad5[0xC];
} OpenWork;

extern int GM_GameStatus_800AB3CC;

extern int title_dword_800D92D0;

extern const char title_aMemorycardslot_800D8FAC[];      // = "MEMORY CARD SLOT 1  :  "
extern const char title_aFull_800D8FC4[];                // = "   FULL"
extern const char title_aNocard_800D8FCC[];              // = "NO CARD"
extern const char title_aMemorycardslot_800D8FD4[];      // = "MEMORY CARD SLOT 2  :  "
extern const char title_aDoyouwanttocontinue_800D8FEC[]; // = "DO YOU WANT TO CONTINUE\n"
extern const char title_aYourgamelikethis_800D9008[];    // = "YOUR GAME LIKE THIS?"
extern const char title_aYes_800D9020[];                 // = "YES"
extern const char title_aNo_800D9024[];                  // = "NO"
extern const char aOpenC[];                              // = "open.c"

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

#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C4F1C.s")
void title_open_800C4F1C(OpenWork *, int, int, int, int, int, int);

#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5200.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5238.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5360.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C53E0.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5620.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5750.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5760.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C593C.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5CB8.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5CF0.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5D10.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5D30.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C61E0.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C628C.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CCDC8.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CD074.s")
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
