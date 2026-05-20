#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "font/font.h"
#include "menu/menuman.h"
#include "game/game.h"
#include "sound/sd_cli.h"
#include "sound/g_sound.h"

#include "openwork.h"

extern void  title_open_800C5644(OpenWork *work, int index);
extern void  title_open_800C5CB8(OpenWork *work);
extern void  title_open_800C5CF0(OpenWork *work);
extern void  title_open_800C5D10(OpenWork *work);
extern void  title_open_800C53E0(OpenWork *work);
extern int   title_open_800C628C(OpenWork *work);
extern void  title_open_800CCDC8(OpenWork *work);
extern void  title_open_800CD074(OpenWork *work);
extern void  title_open_800CD23C(OpenWork *work, int index, int arg3);
extern void  title_open_800CD320(OpenWork *work, int index);
extern void  title_open_800CD3B8(OpenWork *work, int index);
extern void  title_open_800CD800(OpenWork *work, int index);
extern void  title_open_800CDE44(OpenWork *work, int index);
extern void  title_open_800CE378(OpenWork *work, int index);
extern void  title_open_800CE4A8(OpenWork *work, int index);
extern void  title_open_800CE544(OpenWork *work, int index);
extern void  title_open_800CE5F8(OpenWork *work, int index);
extern void  title_open_800CE6AC(OpenWork *work, int index);
extern void  title_open_800CE748(OpenWork *work, int index);
extern void  title_open_800CEB14(OpenWork *work, int index);
extern void  title_open_800CEF54(OpenWork *work, int index);
extern void  title_open_800CF504(OpenWork *work, int index);
extern void  title_open_800CF610(OpenWork *work, int index);
extern void  title_open_800CF794(OpenWork *work);
extern void  title_open_800D1CB4(OpenWork *work);
extern void  title_open_800D2A00(OpenWork *work);
extern void  title_open_800D2AFC(OpenWork *work);
extern void  title_open_800D2CA8(OpenWork *work, u_long *ot);
extern void  title_open_800D2E44(OpenWork *work, u_long *ot);
extern void  title_open_800D3500(OpenWork *work, u_long *ot);
extern void *NewMetalGearLogo(int *exit);
extern void *title_open_800C4B20(KCB *kcb);
extern int   title_dword_800D92D0;
extern const char aOpenC[];

#define EXEC_LEVEL GV_ACTOR_MANAGER

/* The strings that previously lived at 0x800D8848..0x800D9024 in overlay3.c
 * are moved here so openact.obj's rdata fills the gap up to 0x800D9028,
 * where gcc's emitted switch jump tables for OpenAct's switch then land. */

const char title_aThisisnotpsdisc_800D8D58[] = "THIS IS NOT PS DISC!!\n";
const char title_aCdstopfailed_800D8D70[] = "CD STOP FAILED!!\n";
const char title_aCdstopsuccess_800D8D84[] = "CD STOP SUCCESS!!\n";
const char title_aCdcaseclose_800D8D98[] = "CD CASE CLOSE!!\n";
const char title_aStartbuttonpush_800D8DAC[] = "START BUTTON PUSH!!\n";
const char title_aCdspinstart_800D8DC4[] = "CD SPIN START!!\n";
const char title_aCdnotspin_800D8DD8[] = "CD NOT SPIN!!\n";
const char title_aCdtocreadnotfinish_800D8DE8[] = "CD TOC READ NOT FINISH!!\n";
const char title_aCdtocreadsuccess_800D8E04[] = "CD TOC READ SUCCESS!!\n";
const char title_aCdspeedinitfailed_800D8E1C[] = "CD SPEED INIT FAILED!!\n";
const char title_aCdspeedinitsuccess_800D8E34[] = "CD SPEED INIT SUCCESS!!\n";
const char title_aCdcheckfailed_800D8E50[] = "CD CHECK FAILED!!\n";
const char title_aCdcheckok_800D8E64[] = "CD CHECK OK!!\n";
const char title_aThisisnotpsdisc_800D8E74[] = "THIS IS NOT PS DISC!!!\n";
const char title_aCdcheckerror_800D8E8C[] = "CD CHECK ERROR!!\n";
const char title_aThisispsdisc_800D8EA0[] = "THIS IS PS DISC!!\n";
const char title_aThisisdisc_800D8EB4[] = "THIS IS DISC 1!!\n";
const char title_aThisisnotdisc_800D8EC8[] = "THIS IS NOT DISC 1!!!\n";
const char title_aOkok_800D8EE0[] = "OK! OK!\n";
const char title_aNotoknotok_800D8EEC[] = "NOT OK! NOT OK!\n";
const int title_dword_800D8F00 = 0x800D24AC;
const int title_dword_800D8F04 = 0x800D254C;
const int title_dword_800D8F08 = 0x800D25F0;
const int title_dword_800D8F0C = 0x800D2620;
const int title_dword_800D8F10 = 0x800D2678;
const int title_dword_800D8F14 = 0x800D26B8;
const int title_dword_800D8F18 = 0x800D2708;
const int title_dword_800D8F1C = 0x800D2754;
const int title_dword_800D8F20 = 0x800D27BC;
const int title_dword_800D8F24 = 0x800D2984;
const int title_dword_800D8F28 = 0x800D29B8;
const char title_dword_800D8F2C[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D8F30 = 0x800D2E20;
const int title_dword_800D8F34 = 0x800D2D18;
const int title_dword_800D8F38 = 0x800D2D24;
const int title_dword_800D8F3C = 0x800D2D30;
const int title_dword_800D8F40 = 0x800D2D94;
const int title_dword_800D8F44 = 0x800D2D48;
const int title_dword_800D8F48 = 0x800D2D3C;
const int title_dword_800D8F4C = 0x800D2D88;
const int title_dword_800D8F50 = 0x800D2E20;
const char title_dword_800D8F54[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D8F58 = 0x800D2E20;
const int title_dword_800D8F5C = 0x800D2DDC;
const int title_dword_800D8F60 = 0x800D2DEC;
const int title_dword_800D8F64 = 0x800D2DFC;
const int title_dword_800D8F68 = 0x800D2E0C;
const char title_aVeryeasy_800D8F6C[] = "VERY EASY";
const char title_aEasy_800D8F78[] = "EASY";
const char title_aNormal_800D8F80[] = "NORMAL";
const char title_aHard_800D8F88[] = "HARD";
const char title_aExtreme_800D8F90[] = "EXTREME";
const int title_dword_800D8F98 = 0x800D2ED8;
const int title_dword_800D8F9C = 0x800D3024;
const int title_dword_800D8FA0 = 0x800D3170;
const int title_dword_800D8FA4 = 0x800D32B4;
const int title_dword_800D8FA8 = 0x800D33C4;
const char title_aMemorycardslot_800D8FAC[] = "MEMORY CARD SLOT 1  :  ";
const char title_aFull_800D8FC4[] = "   FULL";
const char title_aNocard_800D8FCC[] = "NO CARD";
const char title_aMemorycardslot_800D8FD4[] = "MEMORY CARD SLOT 2  :  ";
const char title_aDoyouwanttocontinue_800D8FEC[] = "DO YOU WANT TO CONTINUE\n";
const char title_aYourgamelikethis_800D9008[] = "YOUR GAME LIKE THIS?";
const char title_aYes_800D9020[] = "YES";
const char title_aNo_800D9024[] = "NO";

/* Top-level title-screen state machine. Dispatches on work->fA74; each case
 * runs its one-time init when work->fB0C is set, then renders this frame. */
void OpenAct_800D37F4(OpenWork *work)
{
    u_long   *ot;
    POLY_FT4 *packs;

    ot = DG_ChanlOTag(1);
    packs = work->f18C_polys;

    title_open_800C628C(work);

    if (work->f24D4 == 0)
    {
        title_open_800D1CB4(work);
    }

    switch (work->fA74)
    {
    case 4:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            work->fB0C = 0;

            work->f30[0] = 1792;
            work->f30[1] = 1792;
            work->f30[2] = 1792;
            work->f30[3] = 1536;
            work->f30[4] = 1280;
            work->f30[5] = 1280;
            work->f30[6] = 1280;
            work->f30[7] = 256;

            GM_SetSound(0x1000001, 0);
        }

        title_open_800CD3B8(work, 0);
        title_open_800CD800(work, 3);
        title_open_800CDE44(work, 4);
        title_open_800CE378(work, 7);

        work->f164++;
        work->f168++;
        work->f16C++;
        work->f170++;
        work->f178++;
        work->f17C++;
        work->f180++;
        work->f184++;
        work->f188++;

        if (work->f164 >= 192)
        {
            work->fA74 = 5;
            work->fB0C = 1;
        }
        break;

    case 5:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            work->fB0C = 0;

            work->f30[0] = 1792;
            work->f30[1] = 1792;
            work->f30[2] = 1792;
            work->f30[3] = 1536;
            work->f30[4] = 1280;
            work->f30[5] = 1280;
            work->f30[6] = 1280;
            work->f30[7] = 256;
            work->f30[8] = 256;
            work->f30[9] = 768;
            work->f30[10] = 512;
            work->f30[11] = 1024;
            work->f30[12] = 256;
        }

        title_open_800CCDC8(work);
        title_open_800CD074(work);
        title_open_800CE748(work, 0);
        title_open_800CEB14(work, 3);
        title_open_800CEF54(work, 4);
        title_open_800CE378(work, 7);
        title_open_800CE4A8(work, 8);
        title_open_800CE544(work, 9);
        title_open_800CE5F8(work, 12);
        title_open_800CE6AC(work, 11);

        work->f164++;
        work->f168++;
        work->f16C++;
        work->f170++;
        work->f174++;
        work->f178++;
        work->f17C++;
        work->f180++;
        work->f184++;
        work->f188++;

        if (work->f164 > 407)
        {
            work->fA74 = 6;
            work->fA98 = 2;
            work->f184 = 0;
            work->fB0C = 1;
        }
        break;

    case 6:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            work->fB0C = 0;

            work->f30[0] = 1792;
            work->f30[1] = 1792;
            work->f30[2] = 1792;
            work->f30[3] = 1536;
            work->f30[4] = 1280;
            work->f30[5] = 1280;
            work->f30[6] = 1280;
            work->f30[7] = 256;
            work->f30[8] = 256;
            work->f30[9] = 768;
            work->f30[10] = 512;
            work->f30[11] = 1024;
            work->f30[12] = 256;

            setRGB0(&packs[7], 128, 128, 128);
            setRGB0(&packs[8], 128, 128, 128);
            setRGB0(&packs[9], 128, 128, 128);
            setRGB0(&packs[10], 128, 128, 128);
            setRGB0(&packs[11], 128, 128, 128);
            setRGB0(&packs[12], 128, 128, 128);

            if (work->fA7C == 0)
            {
                work->fA7C = 1;
            }

            if (work->fA80 == 0)
            {
                work->fA80 = 1;
                work->f170 = 0;
            }

            if (work->fA84 == 0)
            {
                work->fA84 = 1;
                work->f170 = 0;
            }

            work->fA98 = 2;
            work->f184 = 0;
            work->fB00 = 0;

            GM_SetSound(0x1000001, 0);
        }

        title_open_800CCDC8(work);
        title_open_800CD074(work);
        title_open_800CE748(work, 0);
        title_open_800CEB14(work, 3);
        title_open_800CEF54(work, 4);
        title_open_800CF504(work, 12);
        title_open_800C5644(work, 10);

        work->f164++;
        work->f168++;
        work->f16C++;
        work->f170++;
        work->f174++;
        work->f184++;
        break;

    case 7:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            work->fB0C = 0;

            work->f30[0] = 1792;
            work->f30[1] = 1792;
            work->f30[2] = 1792;
            work->f30[3] = 1536;
            work->f30[4] = 1280;
            work->f30[5] = 1280;
            work->f30[6] = 1280;
            work->f30[7] = 256;
            work->f30[8] = 256;
            work->f30[9] = 768;
            work->f30[10] = 512;
            work->f30[11] = 1024;

            if (!sd_sng_play())
            {
                GM_SetSound(0x1000001, 0);
            }

            switch (work->fA78)
            {
            case 0:
                work->fE0[0] = 256;
                work->fE0[1] = 256;
                work->fE0[2] = 0;
                work->fE0[3] = 0;
                work->fE0[4] = 256;
                work->fE0[5] = 0;
                break;

            case 1:
                work->fE0[0] = 256;
                work->fE0[1] = 256;
                work->fE0[2] = 256;
                work->fE0[3] = 0;
                work->fE0[4] = 0;
                work->fE0[5] = 0;
                break;

            case 2:
                work->fE0[0] = 0;
                work->fE0[1] = 256;
                work->fE0[2] = 256;
                work->fE0[3] = 256;
                work->fE0[4] = 0;
                work->fE0[5] = 0;
                break;

            case 3:
                work->fE0[0] = 0;
                work->fE0[1] = 0;
                work->fE0[2] = 256;
                work->fE0[3] = 256;
                work->fE0[4] = 256;
                work->fE0[5] = 0;
                break;

            case 4:
                work->fE0[0] = 256;
                work->fE0[1] = 0;
                work->fE0[2] = 0;
                work->fE0[3] = 256;
                work->fE0[4] = 256;
                work->fE0[5] = 0;
                break;

            case 5:
                work->fE0[0] = 256;
                work->fE0[1] = 0;
                work->fE0[2] = 0;
                work->fE0[3] = 0;
                work->fE0[4] = 256;
                work->fE0[5] = 256;
            }
        }

        title_open_800CCDC8(work);
        title_open_800CD074(work);
        title_open_800CE748(work, 0);
        title_open_800CEB14(work, 3);
        title_open_800CEF54(work, 4);

        switch (work->fA78)
        {
        case 0:
            title_open_800CF610(work, 0);
            break;

        case 1:
            title_open_800CF610(work, 1);
            break;

        case 2:
            title_open_800CF610(work, 2);
            break;

        case 3:
            title_open_800CF610(work, 3);
            break;

        case 4:
            title_open_800CF610(work, 4);
            break;

        case 5:
            title_open_800CF610(work, 5);
            break;
        }

        title_open_800C5644(work, 10);
        title_open_800CF794(work);

        work->f164++;
        work->f168++;
        work->f16C++;
        work->f170++;
        work->f174++;
        work->f184++;
        break;

    case 9:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            title_open_800C5CF0(work);
            title_open_800C5D10(work);

            work->fB0C = 0;
            work->f24C4 = 0;
            work->mg_logo = NewMetalGearLogo(&work->f24C4);
        }

        title_open_800D2A00(work);
        break;

    case 16:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            title_open_800C5CF0(work);
            title_open_800C5D10(work);

            work->fB0C = 0;
            work->f24C4 = 0;
            work->mg_logo = NewMetalGearLogo(&work->f24C4);
        }

        title_open_800D2AFC(work);
        break;

    case 13:
        work->fB00 = 0;
        title_open_800D2CA8(work, ot);
        break;

    case 18:
    case 19:
        work->fB00 = 0;
        title_open_800D3500(work, ot);
        break;

    case 21:
        work->fB00 = 0;
        title_open_800D2E44(work, ot);
        break;

    case 0:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            title_open_800C5CF0(work);
            work->fB0C = 0;
            work->f30[18] = 256;
            work->f30[19] = 256;
        }

        title_open_800CD23C(work, 18, 1);
        work->f164++;
        break;

    case 1:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            work->fB0C = 0;
            work->f30[20] = 256;
            work->f30[21] = 256;
        }

        title_open_800CD23C(work, 20, 15);
        work->fB00 = 0;
        work->f164++;
        break;

    case 2:
        title_open_800CD320(work, 18);
        work->fB00 = 0;
        work->f164++;
        break;

    case 3:
        title_open_800CD320(work, 20);
        work->fB00 = 0;
        work->f164++;
        break;
    }

    title_open_800C53E0(work);
}

/* Actor destructor: frees the four DG primitives and each font character
 * block's backing buffer. */
void OpenDie_800D4098(OpenWork *work)
{
    int      i;
    void    *buf;

    GM_FreePrim(work->prim[0]);
    GM_FreePrim(work->prim[2]);
    GM_FreePrim(work->prim[3]);
    GM_FreePrim(work->prim[1]);

    for (i = 0; i < 24; i++)
    {
        buf = title_open_800C4B20(&work->kcb[i]);
        GV_FreeMemory(GV_NORMAL_MEMORY, buf);
    }
}

/* Build a flat-shaded textured quad at neutral brightness (128,128,128 = no
 * tint) with the given vertex rectangle and semi-transparency mode. UV/tpage
 * are filled in later by the caller (typically via the helper below). */
void title_open_800D4174(OpenWork *work, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe)
{
    setPolyFT4(poly);
    setRGB0(poly, 128, 128, 128);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);
}

/* Bind tex to poly's UV/tpage/clut. uo/vo (0 or 1) extend the U/V range past
 * the texture's nominal w/h to compensate for PS1's UV truncation when the
 * sampler clips on the right/bottom edge. */
static inline void title_open_helper_800D41E4(POLY_FT4 *poly, DG_TEX *tex, int uo, int vo)
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

void title_open_800D41E4(OpenWork *work, int name, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe, int type)
{
    DG_TEX *tex;

    title_open_800D4174(work, poly, x0, y0, x1, y1, abe);

    tex = DG_GetTexture(name);
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

/* Like title_open_800D41E4 but with RGB0 set to (0,0,0). On a textured poly
 * an all-zero RGB darkens the texture to black — used as a fade overlay. */
void title_open_800D4368(OpenWork *work, int name, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe)
{
    DG_TEX *tex;
    int     u0, u1;
    int     v0, v1;

    tex = DG_GetTexture(name);

    setPolyFT4(poly);

    u0 = tex->off_x;
    u1 = u0 + tex->w + 1;
    v0 = tex->off_y;
    v1 = v0 + tex->h + 1;
    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;

    setRGB0(poly, 0, 0, 0);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);
}

/* Gouraud variant of title_open_800D4368: same black-tint textured quad but
 * as POLY_GT4, so the per-vertex colors can be ramped later for a gradient. */
void title_open_800D4464(OpenWork *work, int name, POLY_GT4 *poly, int x0, int y0, int x1, int y1, int abe)
{
    DG_TEX *tex;
    int     u0, u1;
    int     v0, v1;

    tex = DG_GetTexture(name);

    setPolyGT4(poly);

    u0 = tex->off_x;
    u1 = u0 + tex->w + 1;
    v0 = tex->off_y;
    v1 = v0 + tex->h + 1;
    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;

    setRGB0(poly, 0, 0, 0);
    setRGB1(poly, 0, 0, 0);
    setRGB2(poly, 0, 0, 0);
    setRGB3(poly, 0, 0, 0);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);
}

#pragma INCLUDE_ASM("asm/overlays/title/OpenGetResources_800D4584.s")
int  OpenGetResources_800D4584(OpenWork *work, int);

/* Actor constructor for the title screen. Allocates the OpenWork, registers
 * the act/die pair, then loads resources; on resource failure the actor is
 * destroyed and NULL is returned. */
void *NewOpen(int arg0, int arg1)
{
    OpenWork *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = GV_NewActor(EXEC_LEVEL, sizeof(OpenWork));
    title_dword_800D92D0 = 0;

    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, OpenAct_800D37F4, OpenDie_800D4098, aOpenC);

        if (OpenGetResources_800D4584(work, arg1) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
