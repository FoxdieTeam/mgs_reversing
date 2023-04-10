#include "linker.h"
#include "menuman.h"
#include "radio.h"
#include "unknown.h"
#include "libdg/libdg.h"

int SECTION(".sdata") dword_800AB63C = 0; // declared

extern int dword_800ABB04;
int        SECTION(".sbss") dword_800ABB04;

extern int dword_800ABB08;
int        SECTION(".sbss") dword_800ABB08;

extern short word_800ABB0C;
short SECTION(".sbss") word_800ABB0C;

extern int dword_800ABB10;
int        SECTION(".sbss") dword_800ABB10; // declared

extern unsigned char dword_800ABB20;
unsigned char        SECTION(".sbss") dword_800ABB20;

extern short word_800ABB22;
short        SECTION(".sbss") word_800ABB22;

extern DG_TEX *dword_800ABB24;
DG_TEX *SECTION(".sbss") dword_800ABB24;

extern int gRadioClut_800ABAFC;
int        SECTION(".sbss") gRadioClut_800ABAFC;

extern int GV_Time_800AB330;
extern void *dword_8009E75C[];

extern DG_TEX gTextureRecs_800B1F50[512];

extern PANEL_TEXTURE dword_800BDA10;
extern PANEL_TEXTURE dword_800BDA30;
extern RadioIncomingCall gRadioIncomingCall_8009E708;
extern int GV_PadMask_800AB374;

extern const char aCall[]; // = "call"

void menu_radio_codec_helper_helper16_8003FC54(Actor_MenuMan *pActor, unsigned char *pOt, int colour)
{
    TILE     *tile;
    DR_TPAGE *tpage;

    tile = (TILE *)pActor->field_20_otBuf->mPrimBuf.mFreeLocation;
    pActor->field_20_otBuf->mPrimBuf.mFreeLocation += sizeof(TILE);

    if (colour > 255)
    {
        colour = 255;
    }
    if (colour < 0)
    {
        colour = 0;
    }
    LSTORE(colour << 0x10 | colour << 8 | colour, &tile->r0);

    setTile(tile);
    setSemiTrans(tile, 1);

    tile->x0 = 0;
    tile->y0 = 0;
    tile->w = 320;
    tile->h = 224;
    addPrim(pOt, tile);

    tpage = (DR_TPAGE *)pActor->field_20_otBuf->mPrimBuf.mFreeLocation;
    pActor->field_20_otBuf->mPrimBuf.mFreeLocation += sizeof(DR_TPAGE);

    setDrawTPage(tpage, 1, 0, getTPage(0, 2, 960, 256));
    addPrim(pOt, tpage);
}

#pragma INCLUDE_ASM("asm/Menu/sub_8003FD50.s") // 608 bytes

void menu_init_sprt_8003D0D0(SPRT *pPrim, PANEL_TEXTURE *pUnk, int offset_x, int offset_y);

void sub_8003FFB0(MenuGlue *pGlue, short x0, short y0, int rgb)
{
    TILE *pPrim;

    pPrim = (TILE *)pGlue->mPrimBuf.mFreeLocation;
    pGlue->mPrimBuf.mFreeLocation += sizeof(TILE);

    pPrim->w = 2;
    pPrim->h = 2;
    *(int *)&pPrim->r0 = rgb;
    pPrim->x0 = x0 + 11;
    pPrim->y0 = y0 + 15;

    setTile(pPrim);
    addPrim(pGlue->mPrimBuf.mOt, pPrim);
}

#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_helper_80040034.s") // 376 bytes
#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_helper2_800401AC.s") // 244 bytes
#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_helper5_800402A0.s") // 324 bytes

void menu_RadioCall_helper_800403E4(void)
{
    int        id;
    ResHeader *pRes;
    RECT       clut_rect;
    char      *buf;
    RECT      *pRect;

    id = GV_CacheID2_800152FC(aCall, 'r');
    pRes = GV_GetCache_8001538C(id);

    clut_rect.x = 960;
    clut_rect.y = 371;
    clut_rect.w = 16;
    clut_rect.h = 1;

    LoadImage_8008FB10(&clut_rect, (char *)pRes->field_14);

    buf = (char *)&pRes->field_14[pRes->field_8 >> 1];
    pRect = (RECT *)(buf - 8);

    gRadioClut_800ABAFC = getClut(clut_rect.x, clut_rect.y);

    pRect->x = 960;
    pRect->y = 372;

    LoadImage_8008FB10(pRect, buf);
}

void menu_radio_update_helper3_80040498(MenuGlue *pGlue)
{
    SPRT     *pPrim;
    DR_TPAGE *tpage;

    pPrim = (SPRT *)pGlue->mPrimBuf.mFreeLocation;
    pGlue->mPrimBuf.mFreeLocation += sizeof(SPRT);

    LSTORE(0x80808080, &pPrim->r0);
    pPrim->u0 = 0;
    pPrim->v0 = 116;
    pPrim->x0 = 130;
    pPrim->y0 = 49;
    pPrim->w = 60;
    pPrim->h = 12;
    pPrim->clut = gRadioClut_800ABAFC;

    setSprt(pPrim);
    setSemiTrans(pPrim, 1);
    addPrim(pGlue->mPrimBuf.mOt, pPrim);

    tpage = (DR_TPAGE *)pGlue->mPrimBuf.mFreeLocation;
    pGlue->mPrimBuf.mFreeLocation += sizeof(DR_TPAGE);

    setDrawTPage(tpage, 1, 0, getTPage(0, 1, 960, 256));

    addPrim(pGlue->mPrimBuf.mOt, tpage);
}

#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_helper3_80040590.s") // 188 bytes

extern RadioCoordsStru_8009E6FC gRadioCoords_8009E6FC[];

static inline RadioCoordsStru_8009E6FC *get_gRadioCoords(int idx)
{
    return &gRadioCoords_8009E6FC[idx];
}

void menu_radio_codec_helper_helper14_helper6_helper_8004064C(MenuGlue *pGlue, int xpos, int ypos, int colour, int idx)
{
    short                     coord;
    POLY_F3                  *pPoly;
    LINE_F4                  *pLine;
    RadioCoordsStru_8009E6FC *radioCoords;

    pPoly = (POLY_F3 *)pGlue->mPrimBuf.mFreeLocation;
    (pGlue->mPrimBuf).mFreeLocation += sizeof(POLY_F3);

    pLine = (LINE_F4 *)pGlue->mPrimBuf.mFreeLocation;
    (pGlue->mPrimBuf).mFreeLocation += sizeof(LINE_F4);

    LSTORE(colour, &pPoly->r0);
    LSTORE(colour, &pLine->r0);

    setPolyF3(pPoly);
    setLineF4(pLine);

    radioCoords = get_gRadioCoords(idx);
    coord = radioCoords->field_0 + xpos;
    pLine->x0 = coord;
    pPoly->x0 = coord;
    pLine->x3 = coord;
    coord = radioCoords->field_1 + ypos;
    pLine->y0 = coord;
    pPoly->y0 = coord;
    pLine->y3 = coord;
    coord = radioCoords->field_2 + xpos;
    pLine->x1 = coord;
    pPoly->x1 = coord;
    coord = radioCoords->field_3 + ypos;
    pLine->y1 = coord;
    pPoly->y1 = coord;
    coord = radioCoords->field_4 + xpos;
    pLine->x2 = coord;
    pPoly->x2 = coord;
    coord = radioCoords->field_5 + ypos;
    pLine->y2 = coord;
    pPoly->y2 = coord;

    addPrim(pGlue->mPrimBuf.mOt, pPoly);
    addPrim(pGlue->mPrimBuf.mOt, pLine);
}

extern char aP3t3t[];  // = "P#3T#3T";
extern char aMemory[]; // = "MEMORY";

void menu_radio_codec_helper_helper14_helper6_800407A4(MenuGlue *pGlue, int xpos, int ypos, int flags)
{
    unsigned colour;

    if (flags < 0)
    {
        flags = 0xf; // Go into all branches below
        colour = 0x3d472e;
    }
    else
    {
        colour = 0x3d472e;
    }

    if (flags & 1)
    {
        TextConfig conf;
        conf.xpos = xpos + 0x90;
        conf.ypos = ypos + 0x28;
        conf.colour = 0x64000000 | colour;
        conf.flags = 0;
        menu_number_draw_string2_80043220(pGlue, &conf, aP3t3t);
    }
    if (flags & 2)
    {
        TextConfig conf;
        conf.xpos = xpos + 0x86;
        conf.ypos = ypos + 0x77;
        conf.colour = 0x64000000 | colour;
        conf.flags = 0;
        menu_number_draw_string2_80043220(pGlue, &conf, aMemory);
    }
    if (flags & 4)
    {
        menu_radio_codec_helper_helper14_helper6_helper_8004064C(pGlue, xpos, ypos, colour, 0);
    }
    if (flags & 8)
    {
        menu_radio_codec_helper_helper14_helper6_helper_8004064C(pGlue, xpos, ypos, colour, 1);
    }
    return;
}

#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_helper4_800408BC.s") // 720 bytes

extern int GV_Clock_800AB920;

void menu_radio_codec_helper_helper15_80040B8C(MenuGlue *pGlue)
{
    DR_TPAGE *tpage1, *tpage1_copy;
    DR_TPAGE *tpage2;
    SPRT     *sprt1;
    SPRT     *sprt2;
    int       time;
    short     w, w_2;
    short     u0, u0_2;

    time = (GV_Time_800AB330 / 2) % 128;

    tpage1_copy = (DR_TPAGE *)pGlue->mPrimBuf.mFreeLocation;
    pGlue->mPrimBuf.mFreeLocation += sizeof(DR_TPAGE);
    tpage1 = tpage1_copy;

    tpage2 = (DR_TPAGE *)pGlue->mPrimBuf.mFreeLocation;
    pGlue->mPrimBuf.mFreeLocation += sizeof(DR_TPAGE);

    if (GV_Clock_800AB920 == 0)
    {
        setDrawTPage(tpage1, 0, 1, getTPage(2, 1, 0, 0));
        setDrawTPage(tpage2, 0, 1, getTPage(2, 1, 256, 0));

        u0 = 0;
        w = 256;
        u0_2 = 0;
        w_2 = 64;
    }
    else
    {
        setDrawTPage(tpage1, 0, 1, getTPage(2, 1, 256, 0));
        setDrawTPage(tpage2, 0, 1, getTPage(2, 1, 512, 0));

        u0 = 64;
        w = 192;
        u0_2 = 0;
        w_2 = 128;
    }

    sprt1 = (SPRT *)pGlue->mPrimBuf.mFreeLocation;
    pGlue->mPrimBuf.mFreeLocation += sizeof(SPRT);

    LSTORE(0x181818, &sprt1->r0);
    sprt1->y0 = time;
    sprt1->x0 = 0;
    sprt1->w = w;
    sprt1->u0 = u0;
    sprt1->h = 8;
    sprt1->v0 = time;

    setSprt(sprt1);
    setSemiTrans(sprt1, 1);

    addPrim(pGlue->mPrimBuf.mOt, sprt1);
    addPrim(pGlue->mPrimBuf.mOt, tpage1);

    sprt2 = (SPRT *)pGlue->mPrimBuf.mFreeLocation;
    pGlue->mPrimBuf.mFreeLocation += sizeof(SPRT);

    *sprt2 = *sprt1;
    sprt2->x0 = w;
    sprt2->w = w_2;
    sprt2->u0 = u0_2;

    addPrim(pGlue->mPrimBuf.mOt, sprt2);
    addPrim(pGlue->mPrimBuf.mOt, tpage2);
}

extern int dword_800ABB00;
int        SECTION(".sbss") dword_800ABB00;

extern int dword_800ABAF8;
int        SECTION(".sbss") dword_800ABAF8;

extern int dword_8009E664;

void menu_radio_codec_helper_helper14_80040DC4(Actor_MenuMan *pActor, int param_2)
{
    DR_TPAGE *tpage;
    DR_STP   *stp;
    MenuGlue *pGlue;

    if (pActor->field_210 != 11 && pActor->field_210 != 14)
    {
        pGlue = pActor->field_20_otBuf;
        menu_radio_codec_helper_helper14_helper4_800408BC(pGlue, 0, 128, 140, 89, 90, 30);
        menu_radio_codec_helper_helper14_helper6_800407A4(pGlue, -90, 90, dword_800ABB00);
        menu_radio_codec_helper_helper14_helper_80040034(pGlue, 51, 178, param_2);
        menu_radio_codec_helper_helper14_helper5_800402A0(pGlue, 32, 149, dword_800ABAF8);
        menu_radio_codec_helper_helper14_helper6_800407A4(pGlue, 0, -8, -1);
        menu_radio_codec_helper_helper14_helper2_800401AC(pGlue, 141, 80);
        menu_radio_codec_helper_helper14_helper5_800402A0(pGlue, 122, 51, -1);
        menu_radio_codec_helper_helper14_helper3_80040590(pGlue, &dword_8009E664, 19, 0, -8);

        stp = (DR_STP *)pGlue->mPrimBuf.mFreeLocation;
        pGlue->mPrimBuf.mFreeLocation += sizeof(DR_STP);
        SetDrawStp_800924D8(stp, 1);
        addPrim(pGlue->mPrimBuf.mOt, stp);

        tpage = (DR_TPAGE *)pGlue->mPrimBuf.mFreeLocation;
        pGlue->mPrimBuf.mFreeLocation += sizeof(DR_TPAGE);
        setDrawTPage(tpage, 1, 0, getTPage(0, 0, 960, 256));
        addPrim(pGlue->mPrimBuf.mOt, tpage);
    }
}

extern RECT rect_800AB630;
RECT        SECTION(".sdata") rect_800AB630;

void init_radio_message_board_80040F74(Actor_MenuMan *pActor)
{
    KCB  local_kcb;
    KCB *allocated_kcb;

    if (pActor->field_214_font == NULL)
    {
        KCB *ptr_local_kcb = &local_kcb;

        GV_ZeroMemory_8001619C(ptr_local_kcb, sizeof(KCB));
        ClearImage(&rect_800AB630, 0, 0, 0);

        font_init_kcb_80044BE0(ptr_local_kcb, &rect_800AB630, 960, 510);
        font_set_kcb_80044C90(ptr_local_kcb, -1, -1, 0, 6, 2, 0);

        allocated_kcb = (KCB *)GV_AllocMemory_80015EB8(0, font_get_buffer_size_80044F38(ptr_local_kcb) + sizeof(KCB));
        font_set_buffer_80044FD8(ptr_local_kcb, allocated_kcb + 1);
        font_set_color_80044DC4(ptr_local_kcb, 0, 0x6739, 0);
        font_set_color_80044DC4(ptr_local_kcb, 1, 0x3bef, 0);
        font_set_color_80044DC4(ptr_local_kcb, 2, 0x3a4b, 0);
        font_set_color_80044DC4(ptr_local_kcb, 3, 0x1094, 0);
        font_clut_update_80046980(ptr_local_kcb);

        pActor->field_214_font = allocated_kcb;
        memcpy(allocated_kcb, ptr_local_kcb, sizeof(KCB));

        dword_800ABB04 = 0;
    }
}

void menu_radio_codec_helper__helper13_800410E4(Actor_MenuMan *pActor, int param_2)
{
    KCB *kcb = pActor->field_214_font;
    dword_800ABB04 = param_2;
    sub_800469A4(kcb, (char *)param_2);
    font_update_8004695C(kcb);
}

void sub_80041118(Actor_MenuMan *pActor)
{
    KCB *kcb = pActor->field_214_font;
    dword_800ABB04 = 0;
    font_clear_800468FC(kcb);
    font_update_8004695C(kcb);
}

int draw_radio_message_8004114C(Actor_MenuMan *pActor, unsigned char *pOt)
{
    KCB  *kcb;
    SPRT *pPrim;

    if (dword_800ABB04 == 0)
    {
        return 0;
    }

    kcb = pActor->field_214_font;

    pPrim = (SPRT *)pActor->field_20_otBuf->mPrimBuf.mFreeLocation;
    pActor->field_20_otBuf->mPrimBuf.mFreeLocation += sizeof(SPRT);

    setRGB0(pPrim, 128, 128, 128);

    pPrim->u0 = (rect_800AB630.x % 64) * 65536 >> 0xe; // FIXME
    pPrim->v0 = rect_800AB630.y;
    pPrim->w = 252;
    pPrim->h = 76;
    pPrim->clut = 32700;
    pPrim->x0 = (320 - kcb->char_arr[7]) / 2;
    pPrim->y0 = 132;

    setSprt(pPrim);
    addPrim(pOt, pPrim);
    return 1;
}

void sub_8004124C(Actor_MenuMan *pActor)
{
    GV_FreeMemory_80015FD0(0, pActor->field_214_font);
    pActor->field_214_font = NULL;
    dword_800ABB04 = 0;
}

#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper12_80041280.s") // 444 bytes

void draw_radio_wait_mark_8004143C(Actor_MenuMan *pActor, unsigned int *pOt)
{
    MenuGlue *pOtBuffer; // $v1
    POLY_F3 *pPrim; // $a0

    if ( GV_Time_800AB330 % 16 >= 4 )
    {
        pOtBuffer = pActor->field_20_otBuf;
        pPrim = (POLY_F3 *)pOtBuffer->mPrimBuf.mFreeLocation;
        pOtBuffer->mPrimBuf.mFreeLocation += sizeof(POLY_F3);
        pPrim->x1 = 288;
        pPrim->y1 = 210;

        pPrim->x0 = pPrim->x1 - 4;
        pPrim->x2 = pPrim->x1 + 4;

        pPrim->y0 = pPrim->y2 = pPrim->y1 - 4;

         *(int *)&pPrim->r0 = 0x80808080;
        setPolyF3(pPrim);
        addPrim(pOt, pPrim);
    }
}

extern short word_800ABB0C;
short        SECTION(".sbss") word_800ABB0C;

extern short word_800ABB0E;
short        SECTION(".sbss") word_800ABB0E;

extern int dword_800AB638;
int        SECTION(".sbss") dword_800AB638;

void menu_radio_codec_helper_helper11_8004150C(Actor_MenuMan *pActor)
{
    int   pRadioCode;
    short dword_800AB638_copy;

    init_radio_message_board_80040F74(pActor);
    pActor->field_212 = 0x1e;
    GM_Sound_80032968(0, 0x3f, 0x56);
    pRadioCode = menu_GetRadioCode_800497C4(dword_800AB638);
    if (pRadioCode >= 0)
    {
        sub_80047D70(pActor, dword_800AB638, pRadioCode);
        dword_800AB638_copy = dword_800AB638;
        pActor->field_210 = 2;
        word_800ABB0C = 0;
        word_800ABB0E = dword_800AB638_copy;
        return;
    }

    pActor->field_210 = 9;
}

#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_8004158C.s") // 3028 bytes

void menu_radio_update_helper5_80042160(Actor_MenuMan *menuMan)
{
    dword_800AB63C = 0;
    dword_800ABB10 = 0;
    menuMan->field_212 = 8;
    menuMan->field_210 = 0;
    menu_radio_codec_create_state_80047CE4(menuMan);
}

void menu_radio_init_nullsub_80042190(void)
{
}

#pragma INCLUDE_ASM("asm/Menu/menu_radio_update_80042198.s") // 1384 bytes

void menu_radio_init_80042700(Actor_MenuMan *pMenu)
{
    pMenu->field_2C_modules[MENU_RADIO] = (TMenuUpdateFn)menu_radio_update_80042198;
    pMenu->field_28_flags |= 0x10u;
}

void menu_radio_kill_8004271C(Actor_MenuMan *pMenu)
{
    pMenu->field_28_flags &= ~0x10u;
}

void menu_RadioCall_80042730(int param_1, int param_2, int time)
{
    gRadioIncomingCall_8009E708.field_0 = param_1;
    gRadioIncomingCall_8009E708.field_4 = param_2;

    if (time == 0)
    {
        gRadioIncomingCall_8009E708.field_2_timer = 360;
        gRadioIncomingCall_8009E708.field_8 = 0;
        menu_RadioCall_helper_800403E4();
    }

    else
    {
        if (time >= 5)
        {
            menu_RadioCall_helper_800403E4();
            gRadioIncomingCall_8009E708.field_8 = 1;
            gRadioIncomingCall_8009E708.field_2_timer = 40;
            GV_PadMask_800AB374 = 0x100;
            GM_GameStatus_800AB3CC |= 0x8000000;
        }
        else
        {
            gRadioIncomingCall_8009E708.field_2_timer = -time;
            gRadioIncomingCall_8009E708.field_8 = 0;
        }

        GM_GameStatus_800AB3CC |= 0x80000;
    }
}

void menu_SetLoad_800427E8(int param_1, int param_2, short param_3)
{
    gRadioIncomingCall_8009E708.field_0 = param_3;
    gRadioIncomingCall_8009E708.field_2_timer = -1;
    gRadioIncomingCall_8009E708.field_4 = param_2;
    dword_800ABB08 = param_1;
    word_800ABB0C = 1;
}

void menu_ResetCall_80042814()
{
    gRadioIncomingCall_8009E708.field_0 = 0;
    gRadioIncomingCall_8009E708.field_4 = 0;
    gRadioIncomingCall_8009E708.field_2_timer = 0;
    gRadioIncomingCall_8009E708.field_8 = 0;

    dword_800ABB08 = -1;
}

void menu_SetRadioCallbackProc_8004283C(int param_1)
{
    dword_800ABB08 = param_1;
    return;
}

// TODO: Functions from this point forward don't belong to radio.c!

void menu_set_string2_80043138();

extern RECT       rect_800AB64C[];
extern const char aNum[]; // = "num";
extern SPRT       gRadioNumberSprt_800bd9b0;
extern SPRT       gRadioNumberSprt2_800bd9d0;

void menu_number_init_80042848(Actor_MenuMan *pActor)
{
    RECT       rect1, rect2;
    ResHeader *pRes;
    SPRT      *pSprt;

    rect1 = rect_800AB64C[0];

    // Loads "num.res" (c70e.r) file:
    pRes = GV_GetCache_8001538C(GV_CacheID2_800152FC(aNum, 'r'));

    pRes->field_14[0] = 0; // TODO: Why zero out the first pixel of image?

    rect2.x = 960;
    rect2.y = 511;
    rect2.w = 16;
    rect2.h = 1;

    LoadImage_8008FB10(&rect2, (char *)pRes->field_14);
    LoadImage_8008FB10(&rect1, (char *)&pRes->field_14[pRes->field_8 >> 1]);

    pSprt = &gRadioNumberSprt_800bd9b0;
    setSprt(pSprt);
    pSprt->r0 = 128;
    pSprt->g0 = 128;
    pSprt->b0 = 128;
    pSprt->u0 = 0x9c;
    pSprt->v0 = 0xe8;
    pSprt->w = 6;
    pSprt->h = 7;
    pSprt->clut = 0x7ffc;

    pSprt = &gRadioNumberSprt2_800bd9d0;
    setSprt(pSprt);
    pSprt->r0 = 128;
    pSprt->g0 = 128;
    pSprt->b0 = 128;
    pSprt->u0 = 0;
    pSprt->v0 = 0xed;
    pSprt->w = 6;
    pSprt->h = 5;
    pSprt->clut = 0x7ffc;
    menu_set_string2_80043138();
}

void menu_number_kill_80042980(void)
{
}

#pragma INCLUDE_ASM("asm/Menu/menu_number_draw_80042988.s") // 476 bytes

int menu_draw_number_draw_helper_80042B64(SPRT *pPrim, char *pFreeLocation, int arg2, int arg3, int arg4)
{
    int offset_x0;

    if (pPrim != 0 && (char*)pPrim < pFreeLocation)
    {
        switch (arg4 & 0xF)
        {
        case 0:
        default:
            offset_x0 = arg2;
            arg2 = arg3 + offset_x0;
            break;

        case 1:
            arg2 -= arg3;
            offset_x0 = arg2;
            break;

        case 2:
            offset_x0 = arg2 - arg3 / 2;
            arg2 = arg3;
            break;

        }

        while ((char*)pPrim < pFreeLocation)
        {
            pPrim->x0 += offset_x0;
            pPrim++;
        }
    }

    return arg2;
}

#pragma INCLUDE_ASM("asm/Menu/menu_number_draw_string_80042BF4.s") // 580 bytes

void menu_number_draw_magazine_80042E38(Actor_MenuMan *pActor, unsigned int *pOt, int xoff, int yoff, int pMagSize,
                                        int pAmmo, int pSubCnt2)
{
    SPRT *sprt;
    SPRT *sprt_copy;
    int   i;

    for (i = 0; i < pAmmo; i++)
    {
        sprt_copy = (SPRT *)pActor->field_20_otBuf->mPrimBuf.mFreeLocation;
        pActor->field_20_otBuf->mPrimBuf.mFreeLocation += sizeof(SPRT);

        sprt = sprt_copy;
        xoff = xoff - 3;
        *sprt = gRadioNumberSprt2_800bd9d0;
        sprt->x0 = xoff;
        sprt->y0 = yoff;

        if (i < pMagSize)
        {
            if (i < pSubCnt2)
            {
                sprt->r0 = 128;
                sprt->g0 = 32;
                sprt->b0 = 32;
            }
            sprt->u0 = 0xD8;
            sprt->v0 = 0xE8;
        }
        else
        {
            sprt->u0 = 0xDC;
            sprt->v0 = 0xE8;
        }

        sprt->w = 4;
        sprt->h = 9;
        addPrim(pOt, sprt);
    }
}

int menu_number_draw_80042F78(Actor_MenuMan *pActor, unsigned int *pOt, int xpos, int ypos, int number, int flags)
{
    TextConfig textConfig; // [sp+10h] [-10h] BYREF

    textConfig.xpos = xpos;
    textConfig.ypos = ypos;
    textConfig.colour = 0x64808080;
    textConfig.flags = flags;
    menu_number_draw_80042988(pActor->field_20_otBuf, &textConfig, number);
    return textConfig.xpos;
}

extern SPRT gRadioNumberSprt_800bd9b0;

int menu_number_draw_number2_80042FC0(Actor_MenuMan *pActor, int xpos, int ypos, int current, int total)
{
    SPRT      *pPrim;
    TextConfig textConfig;

    textConfig.xpos = xpos;
    textConfig.ypos = ypos;
    textConfig.flags = 0;
    textConfig.colour = (current == 0 ? 0x64002080 : 0x64575757);
    menu_number_draw_80042988(pActor->field_20_otBuf, &textConfig, current);

    pPrim = (SPRT *)pActor->field_20_otBuf->mPrimBuf.mFreeLocation;
    pActor->field_20_otBuf->mPrimBuf.mFreeLocation += sizeof(SPRT);

    *pPrim = gRadioNumberSprt_800bd9b0;
    LSTORE(textConfig.colour, &pPrim->r0);
    pPrim->x0 = textConfig.xpos;
    pPrim->y0 = textConfig.ypos;
    pPrim->u0 = 224;

    addPrim(pActor->field_20_otBuf->mPrimBuf.mOt, pPrim);

    textConfig.xpos = textConfig.xpos + 6;
    menu_number_draw_80042988(pActor->field_20_otBuf, &textConfig, total);
    return textConfig.xpos;
}

int menu_number_draw_string_800430F0(Actor_MenuMan *pActor, unsigned int *pOt, int xpos, int ypos, const char *str, int flags)
{
    TextConfig textConfig;

    textConfig.xpos = xpos;
    textConfig.ypos = ypos;
    textConfig.colour = 0x64808080;
    textConfig.flags = flags;
    menu_number_draw_string_80042BF4(pActor->field_20_otBuf, &textConfig, str);
    return textConfig.xpos;
}

extern RECT gRadioStringRect_800AB658;
RECT        SECTION(".sdata") gRadioStringRect_800AB658;

extern SPRT gRadioStringSprt_800BD9F0;

void menu_set_string2_80043138()
{
    PANEL_TEXTURE pPanelTex;
    RECT          rect;

    menu_init_rpk_item_8003DDCC(&pPanelTex, 45, 44);

    gRadioStringRect_800AB658.w = pPanelTex.field_10_w / 4;
    gRadioStringRect_800AB658.h = pPanelTex.field_12_h;
    LoadImage_8008FB10(&gRadioStringRect_800AB658, pPanelTex.field_0_pixels);

    rect.x = 976;
    rect.y = 511;
    rect.w = 16;
    rect.h = 1;

    LoadImage_8008FB10(&rect, pPanelTex.field_4_word_ptr_pixels);

    gRadioStringSprt_800BD9F0.u0 = 0;
    LSTORE(0x80808080, &gRadioStringSprt_800BD9F0.r0);
    gRadioStringSprt_800BD9F0.v0 = 242;
    gRadioStringSprt_800BD9F0.w = 8;
    gRadioStringSprt_800BD9F0.h = 6;
    setSprt(&gRadioStringSprt_800BD9F0);
    setClut(&gRadioStringSprt_800BD9F0, rect.x, rect.y);
}

#pragma INCLUDE_ASM("asm/Menu/menu_number_draw_string2_80043220.s") // 592 bytes

void menu_restore_nouse_80043470()
{
    sub_8003CFE0(&dword_800BDA10, 2);
    sub_8003CFE0(&dword_800BDA30, 3);
}

void menu_init_nouse_800434A8()
{
    dword_800BDA10.field_8_bufid = 0;
    menu_init_rpk_item_8003DDCC(&dword_800BDA10, 40, 39);
    menu_init_rpk_item_8003DDCC(&dword_800BDA30, 48, 39);
    menu_restore_nouse_80043470();
}

void sub_800434F4(MenuGlue *pGlue, int offset_x, int offset_y, PANEL_TEXTURE *pUnk)
{
    SPRT *pPrim;

    pPrim = (SPRT *)pGlue->mPrimBuf.mFreeLocation;
    pGlue->mPrimBuf.mFreeLocation += sizeof(SPRT);

    *(int *)&pPrim->r0 = 0x80808080;
    menu_init_sprt_8003D0D0(pPrim, pUnk, offset_x - 2, offset_y + 6);

    setSprt(pPrim);
    addPrim(pGlue->mPrimBuf.mOt, pPrim);
}

void menu_draw_nouse_800435A4(MenuGlue *pGlue, int offset_x, int offset_y)
{
    sub_800434F4(pGlue, offset_x, offset_y, &dword_800BDA10);
}

void menu_draw_frozen_800435C8(MenuGlue *pGlue, int offset_x, int offset_y)
{
    sub_800434F4(pGlue, offset_x, offset_y, &dword_800BDA30);
}

void menu_draw_triangle_800435EC(MenuGlue *pGlue, Menu_Triangle *pTriangle)
{
    POLY_F3 *pPrim;

    pPrim = (POLY_F3 *)pGlue->mPrimBuf.mFreeLocation;
    pGlue->mPrimBuf.mFreeLocation += sizeof(POLY_F3);

    LCOPY(&pTriangle->field_0_x0, &pPrim->x0);
    LCOPY(&pTriangle->field_4_x1, &pPrim->x1);
    LCOPY(&pTriangle->field_8_x2, &pPrim->x2);
    LCOPY(&pTriangle->field_C_rgb, &pPrim->r0);

    setPolyF3(pPrim);
    addPrim(pGlue->mPrimBuf.mOt, pPrim);
}

#pragma INCLUDE_ASM("asm/Menu/sub_80043678.s") // 940 bytes
#pragma INCLUDE_ASM("asm/Menu/sub_80043A24.s") // 1452 bytes

int sub_80043FD0(Actor_MenuMan *pMenuMan, unsigned int *pOt)
{
    u_char       *chnlOt;
    int           numOTEntries;
    u_char       *otMin;
    u_char       *curPrim;
    int           primCount;
    int           totalprimCount;

    LINE_F2      *lineF2;
    LINE_G4      *lineG4;
    int           ff00;
    int           ff0000;
    int           x_0_1;
    int           y_0_1;
    int           x_2_3;
    int           y_2_3;

    int           i;

    unsigned char *nextFreeLocation;
    unsigned char *nextFreeLocation2;

    int           returnVal;

    totalprimCount = 0;
    returnVal = 0;
    y_0_1 = 0xa8;
    y_2_3 = 0xa8;

    chnlOt = DG_Chanl(0)->mOrderingTables[1 - GV_Clock_800AB920];
    numOTEntries = DG_Chanl(0)->word_6BC374_8 - 4;

    lineF2 = (LINE_F2 *)pMenuMan->field_20_otBuf->mPrimBuf.mFreeLocation;
    pMenuMan->field_20_otBuf->mPrimBuf.mFreeLocation += sizeof(LINE_F2);

    setXY2(lineF2, 0x20, 0x76, 0x110, 0x76);
    *(int *)&lineF2->r0 = 0x800000;
    setLineF2(lineF2);
    addPrim(pOt, lineF2);

    for (i = 0; i < 16; i++)
    {
        otMin = chnlOt + ((i << numOTEntries) * 4);
        for (curPrim = chnlOt + (((i + 1) << numOTEntries) * 4), primCount = 0;
             (otMin < curPrim) || (curPrim < chnlOt); curPrim = nextPrim(curPrim))
        {
            if (getlen(curPrim) != 0)
            {
                primCount++;
            }
        }

        totalprimCount += primCount;
        x_0_1 = i * 15;
        x_2_3 = x_0_1 + 13;
        x_0_1 += 32;
        x_2_3 += 32;

        if (primCount > 0)
        {
            primCount = primCount / 2;

            if (primCount > 176)
            {
                primCount = 176;
            }

            ff00 = 0xff00;
            nextFreeLocation = pMenuMan->field_20_otBuf->mPrimBuf.mFreeLocation + (sizeof(LINE_G4));
            lineG4 = (LINE_G4 *)pMenuMan->field_20_otBuf->mPrimBuf.mFreeLocation;
            pMenuMan->field_20_otBuf->mPrimBuf.mFreeLocation = nextFreeLocation;
            setXY4(lineG4, x_0_1, y_0_1, x_0_1, y_0_1 - primCount, x_2_3, y_2_3 - primCount, x_2_3, y_2_3);
            *(int *)&lineG4->r0 = 0;
            *(int *)&lineG4->r1 = ff00;
            returnVal++;
            *(int *)&lineG4->r2 = ff00;
            *(int *)&lineG4->r3 = 0;
            setLineG4(lineG4);
            addPrim(pOt, lineG4);
        }
        else
        {
            nextFreeLocation2 = pMenuMan->field_20_otBuf->mPrimBuf.mFreeLocation + (sizeof(LINE_G4));
            ff0000 = 0xff0000;
            lineG4 = (LINE_G4 *)pMenuMan->field_20_otBuf->mPrimBuf.mFreeLocation;
            pMenuMan->field_20_otBuf->mPrimBuf.mFreeLocation = nextFreeLocation2;
            setXY4(lineG4, x_0_1, y_0_1, x_0_1, y_0_1, x_2_3, y_2_3, x_2_3, y_2_3);
            *(int *)&lineG4->r0 = 0;
            *(int *)&lineG4->r1 = ff0000;
            *(int *)&lineG4->r2 = ff0000;
            *(int *)&lineG4->r3 = 0;
            setLineG4(lineG4);
            addPrim(pOt, lineG4);
        }
    }

    menu_number_draw_80042F78(pMenuMan, pOt, 0x110, 0x9c, totalprimCount, 1);

    return returnVal;
}

#pragma INCLUDE_ASM("asm/Menu/sub_800442E4.s") // 788 bytes

extern GV_PAD GV_PadData_800B05C0[4];
extern char   aNoD[];  // = "No %d\n";
extern char   aIdD[];  // = "ID %d\n";
extern char   aColD[]; // = "COL %d\n";
extern char   aXDYD[]; // = "x %d y %d\n";
extern char   aWDHD[]; // = "w %d h %d\n";

int sub_800445F8(Actor_MenuMan *pActor, unsigned int *pOt)
{
    const int textureRecsCount = sizeof(gTextureRecs_800B1F50) / sizeof(gTextureRecs_800B1F50[0]);
    short     x0, y0;
    int       i;
    DG_TEX   *iterTex;
    POLY_FT4 *pPoly;
    int       width, height;
    int       offx, offy;
    int       direction;

    iterTex = dword_800ABB24;
    direction = 0;
    if (GV_PadData_800B05C0[0].status & PAD_RIGHT)
    {
        direction = 1;
    }
    else if (GV_PadData_800B05C0[0].status & PAD_LEFT)
    {
        direction = -1;
    }
    else
    {
        word_800ABB22 = -1;
    }
    if (direction != 0)
    {
        if (word_800ABB22 <= 0)
        {
            for (i = textureRecsCount; i > 0; i--)
            {
                iterTex += direction;
                if (iterTex == &gTextureRecs_800B1F50[textureRecsCount])
                {
                    iterTex -= textureRecsCount;
                }
                if (iterTex < &gTextureRecs_800B1F50[0])
                {
                    iterTex = &gTextureRecs_800B1F50[textureRecsCount - 1];
                }
                if (iterTex->field_0_hash != 0)
                {
                    break;
                }
            }
            if (word_800ABB22 < 0)
            {
                word_800ABB22 = 10;
            }
            else if (word_800ABB22 == 0)
            {
                word_800ABB22 = 2;
            }
        }
        word_800ABB22--;
    }

    if (iterTex->field_0_hash == 0)
    {
        return 0;
    }

    dword_800ABB24 = iterTex;

    menu_Text_XY_Flags_80038B34(300, 128, 1);
    menu_Text_80038C38(aNoD, iterTex - gTextureRecs_800B1F50);
    menu_Text_80038C38(aIdD, iterTex->field_0_hash);
    menu_Text_80038C38(aColD, iterTex->field_2_bUsed.c[1]);
    menu_Text_80038C38(aXDYD, iterTex->field_8_offx, iterTex->field_9_offy);
    menu_Text_80038C38(aWDHD, iterTex->field_A_width + 1, iterTex->field_B_height + 1);

    pPoly = (POLY_FT4 *)pActor->field_20_otBuf->mPrimBuf.mFreeLocation;
    pActor->field_20_otBuf->mPrimBuf.mFreeLocation += sizeof(POLY_FT4);

    LSTORE(0x808080, &pPoly->r0);

    setPolyFT4(pPoly);

    pPoly->clut = iterTex->field_6_clut;
    pPoly->tpage = iterTex->field_4_tPage;

    width = iterTex->field_A_width;
    height = iterTex->field_B_height;
    offx = iterTex->field_8_offx;
    offy = iterTex->field_9_offy;

    x0 = (319 - width) / 2;
    y0 = (239 - height) / 2;

    pPoly->x0 = x0;
    pPoly->y0 = y0;
    pPoly->y1 = y0;
    pPoly->x1 = x0 + width;
    pPoly->x2 = x0;
    pPoly->y2 = y0 + height;
    pPoly->y3 = y0 + height;
    pPoly->x3 = x0 + width;
    pPoly->u0 = offx;
    pPoly->v0 = offy;
    pPoly->u1 = offx + width;
    pPoly->v1 = offy;
    pPoly->u2 = offx;
    pPoly->v2 = offy + height;
    pPoly->u3 = offx + width;
    pPoly->v3 = offy + height;

    addPrim(pOt, pPoly);
    return 1;
}

#pragma INCLUDE_ASM("asm/Menu/sub_800448C0.s") // 432 bytes

void menu_viewer_init_80044A70(Actor_MenuMan *param_1)
{
    dword_800ABB20 = 0;
    dword_800ABB24 = gTextureRecs_800B1F50;
    word_800ABB22 = -1;
}

void menu_viewer_kill_80044A90(Actor_MenuMan *pActor)
{
    dword_800ABB20 = 0;
    return;
}
