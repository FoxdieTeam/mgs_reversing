#include "game/game.h"
#include <stdio.h>

/* Pan/zoom state of one of the three zoomable views */
typedef struct
{
    int x;
    int y;
    int scale;
} BrfView;

typedef struct _Work
{
    GV_ACT     actor;                     /* 0x000 */
    DG_PRIM   *f4_prim;                   /* 0x020: f4_polys */
    DG_PRIM   *prim_24;                   /* 0x024: two POLY_FT4 written in place */
    DG_PRIM   *main_prim;                 /* 0x028: polys */
    DG_PRIM   *small_prim;                /* 0x02C: small_polys */
    DG_PRIM   *sub_prim;                  /* 0x030: sub_polys */
    POLY_FT4   small_polys[15];           /* 0x034 */
    POLY_FT4   polys[840];                /* 0x28C */
    POLY_FT4   sub_polys[200];            /* 0x85CC */
    POLY_FT4  *poly_buf;                  /* 0xA50C */
    POLY_F4    f4_polys[5];               /* 0xA510 */
    int        index;                     /* 0xA588: briefing index (selected item) */
    char       pad_A58C[0x4];             /* 0xA58C */
    /* per-poly visibility flags (shifted into the poly tag before drawing) */
    u_char     f4_flags[5];               /* 0xA590 */
    u_char     prim_24_flags[2];          /* 0xA595 */
    u_char     poly_flags[840];           /* 0xA597 */
    u_char     sub_flags[200];            /* 0xA8DF */
    u_char     small_flags[15];           /* 0xA9A7 */
    u_char     glyph_flags[840];          /* 0xA9B6: 1 if the text poly shows a glyph (not a space) */
    char       pad_ACFE[0x2];             /* 0xACFE */
    GV_PAD    *pad;                       /* 0xAD00 */
    int        map;                       /* 0xAD04 */
    DG_TEX    *textures;                  /* 0xAD08 */
    int       *tex_ids;                   /* 0xAD0C */
    int        n_textures;                /* 0xAD10 */
    int        n_images;                  /* 0xAD14 */
    int       *image_ids;                 /* 0xAD18 */
    DG_IMAGE **images;                    /* 0xAD1C */
    int        scene;                     /* 0xAD20 */
    char       pad_AD24[0x4];             /* 0xAD24 */
    int        time;                      /* 0xAD28 */
    int        field_AD2C;                /* 0xAD2C */
    int        field_AD30;                /* 0xAD30: per-scene animation counter */
    int        field_AD34;                /* 0xAD34: per-scene animation counter */
    int        field_AD38;                /* 0xAD38 */
    int        field_AD3C;                /* 0xAD3C */
    int        field_AD40;                /* 0xAD40 */
    int        mouth;                     /* 0xAD44: last lip-sync state */
    int        mouth_changed;             /* 0xAD48 */
    char       pad_AD4C[0x4];             /* 0xAD4C */
    int        key_index;                 /* 0xAD50 */
    int        key_time;                  /* 0xAD54 */
    int        key_scene;                 /* 0xAD58 */
    int        scene_changed;             /* 0xAD5C */
    int        lipsync;                   /* 0xAD60: jimctrl_helper_80037F68() result */
    char       pad_AD64[0x8];             /* 0xAD64 */
    int        lipsync2;                  /* 0xAD6C */
    int        mouth2;                    /* 0xAD70 */
    int        field_AD74;                /* 0xAD74 */
    BrfView    view[3];                   /* 0xAD78 */
    int        move_dir;                  /* 0xAD9C: 0 right, 1 left, 2 up, 3 down */
    int        move_state;                /* 0xADA0 */
    int        view_mode;                 /* 0xADA4 */
    int        zoom_dir;                  /* 0xADA8: 4 triangle (scale up), 5 square (scale down) */
    int        zoom_state;                /* 0xADAC */
    int        zoom_count;                /* 0xADB0 */
    char       pad_ADB4[0x4];             /* 0xADB4 */
    int        field_ADB8;                /* 0xADB8: polys are drawn from poly_buf while < 5 */
    int        field_ADBC;                /* 0xADBC */
    int        field_ADC0;                /* 0xADC0 */
    char       no_skip;                   /* 0xADC4 */
    char       pad_ADC5[0x3];             /* 0xADC5 */
} Work;

typedef struct
{
    short field_0;
    short field_2;
} BrfKeyframe;

#define BRF_SET_UV(poly, tex)                                                       \
    {                                                                               \
        int offx, offx2, offx3;                                                     \
        int offy, offy2;                                                            \
                                                                                    \
        offx = (tex)->off_x;                                                        \
        offx2 = offx + (tex)->w;                                                    \
        offy = (tex)->off_y;                                                        \
        offx3 = offx2 + 1;                                                          \
        offy2 = offy + (tex)->h + 1;                                                \
                                                                                    \
        setUV4((poly), offx, offy, offx3, offy, offx, offy2, offx3, offy2);        \
        (poly)->tpage = (tex)->tpage;                                               \
        (poly)->clut = (tex)->clut;                                                 \
    }

void brf_800CCBD4();
void brf_800CB23C();
void brf_800CAE84();
void brf_800CB5F4();
void brf_800D1BDC();
void brf_800CC5E4();
void brf_800CF4E0();
void brf_800CF5A8();
DG_TEX *brf_800CABF4();
extern const char brf_dword_800E1BF0[];

DG_TEX *brf_800CABF4(work, id)
Work *work;
int id;
{
    int i;
    int found = 0;
    for (i = 0; i < work->n_textures; i++)
    {
        if (work->tex_ids[i] == id)
        {
            return &work->textures[i];
        }
    }
    if (!found)
    {
        printf((char *)brf_dword_800E1BF0, id);
    }
    return 0;
}
void brf_800CAC7C(Work *work, int id)
{
    int i;
    int found = 0;
    DG_IMAGE *result = 0;
    for (i = 0; i < work->n_images; i++)
    {
        if (work->image_ids[i] == id)
        {
            result = work->images[i];
            found = 1;
        }
    }
    if (found)
    {
        LoadImage(&result[0].dim, (u_long *)result[0].data);
        LoadImage(&result[1].dim, (u_long *)result[1].data);
    }
    else
    {
        printf((char *)brf_dword_800E1BF0, id);
    }
}
extern const char brf_dword_800E1C14[];
int jimctrl_helper_80037F68();
extern int brf_dword_800C5094;

void brf_800CAD24(Work *work, POLY_FT4 *dest, int a2, int a3, int a4)
{
    DG_TEX *g;
    int u, uw, v, vh;

    work->mouth_changed = a2;
    g = brf_800CABF4(work, ((unsigned short *)((int *)&brf_dword_800C5094)[a4])[a3]);
    u = g->off_x;
    uw = u + g->w + 1;
    v = g->off_y;
    vh = v + g->h + 1;

    dest->u0 = u;
    dest->v0 = v;
    dest->u1 = uw;
    dest->v1 = v;
    dest->u2 = u;
    dest->v2 = vh;
    dest->u3 = uw;
    dest->v3 = vh;
    dest->tpage = g->tpage;
    dest->clut = g->clut;
}

void brf_800CADD4(Work *work, void *a1, int a2)
{
    int v0 = jimctrl_helper_80037F68(GV_StrCode(brf_dword_800E1C14));
    int s0 = v0 & 0xFF;

    work->lipsync = v0;
    if (work->mouth != s0)
    {
        brf_800CAD24(work, a1, 0, s0, a2);
    }
    else if (work->mouth_changed != 0)
    {
        brf_800CAD24(work, a1, 1, s0, a2);
    }
    work->mouth = s0;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CAE84.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CB23C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CB5F4.s")
extern int brf_dword_800C50DC;

void brf_800CBA84(Work *work, POLY_FT4 *dest, int idx)
{
    DG_TEX *g = brf_800CABF4(work, ((unsigned short *)((int *)&brf_dword_800C50DC)[idx])[(work->field_AD40 - 1) / 2]);
    int u = g->off_x;
    int uw = u + g->w + 1;
    int v = g->off_y;
    int vh = v + g->h + 1;

    dest->u0 = u;
    dest->v0 = v;
    dest->u1 = uw;
    dest->v1 = v;
    dest->u2 = u;
    dest->v2 = vh;
    dest->u3 = uw;
    dest->v3 = vh;
    dest->tpage = g->tpage;
    dest->clut = g->clut;

    work->field_AD40++;
    if (work->field_AD40 >= 7)
    {
        work->field_AD40 = 0;
    }
}
extern const char brf_dword_800E1C90[];

void brf_800CBB68(Work *work, void *a1, int a2)
{
    if (work->lipsync >> 8)
    {
        if (work->field_AD40)
        {
            printf((char *)brf_dword_800E1C90);
        }
        else
        {
            work->field_AD40 = 1;
        }
    }
    if (work->field_AD40)
    {
        brf_800CBA84(work, a1, a2);
    }
}
extern int brf_dword_800C50E8;
extern int brf_dword_800C50F4;

void brf_800CBC04(Work *work, POLY_FT4 *dest, int idx)
{
    unsigned short *tbl = (unsigned short *)&brf_dword_800C50E8;
    DG_TEX *g = brf_800CABF4(work, tbl[idx / 3]);
    int u = g->off_x;
    int uw = u + g->w + 1;
    int v = g->off_y;
    int vh = v + g->h + 1;

    dest->u0 = u;
    dest->v0 = v;
    dest->u1 = uw;
    dest->v1 = v;
    dest->u2 = u;
    dest->v2 = vh;
    dest->u3 = uw;
    dest->v3 = vh;
    dest->tpage = g->tpage;
    dest->clut = g->clut;
}
void brf_800CBCB0(Work *work, POLY_FT4 *dest, int idx)
{
    unsigned short *tbl = (unsigned short *)&brf_dword_800C50F4;
    DG_TEX *g = brf_800CABF4(work, tbl[idx / 3]);
    int u = g->off_x;
    int uw = u + g->w + 1;
    int v = g->off_y;
    int vh = v + g->h + 1;

    dest->u0 = u;
    dest->v0 = v;
    dest->u1 = uw;
    dest->v1 = v;
    dest->u2 = u;
    dest->v2 = vh;
    dest->u3 = uw;
    dest->v3 = vh;
    dest->tpage = g->tpage;
    dest->clut = g->clut;
}

void brf_800CBD5C(Work *work, void *a1)
{
    if (work->field_AD34 % 3 == 2)
    {
        brf_800CBC04(work, a1, work->field_AD34);
    }
    work->field_AD34++;
}
void brf_800CBDC8(Work *work, void *a1)
{
    if (work->field_AD34 % 3 == 2)
    {
        brf_800CBCB0(work, a1, work->field_AD34);
    }
    work->field_AD34++;
}
const char brf_dword_800E13BC[28] = "      GROUP, AS AN ADVISOR.";
const char brf_dword_800E13D8[28] = "      ABOLITION PROPOSAL";
const char brf_dword_800E13F4[24] = "      NUCLEAR WEAPON";
const char brf_dword_800E140C[24] = "      NATIONALLY HOSTED";
const char brf_dword_800E1424[20] = "      WORLD'S FIRST";
const char brf_dword_800E1438[24] = "      COMMITTEE, THE";
const char brf_dword_800E1450[28] = "1996  ATTENDS THE CANBERRA";
const char brf_dword_800E146C[20] = "      MAGAZINES.";
const char brf_dword_800E1480[20] = "      INFORMATION";
const char brf_dword_800E1494[20] = "      AND US NAVAL";
const char brf_dword_800E14A8[28] = "      INFORMATION MAGAZINES";
const char brf_dword_800E14C4[28] = "      WRITES FOR ASSORTED";
const char brf_dword_800E14E0[16] = "      ANALYST.";
const char brf_dword_800E14F0[28] = "      TO BECOME A FREELANCE";
const char brf_dword_800E150C[24] = "1995  LEAVES THE BUREAU";
const char brf_dword_800E1524[16] = "      AGENCY).";
const char brf_dword_800E1534[28] = "      (DEFENSE INTELLIGENCE";
const char brf_dword_800E1550[20] = "1992  JOINS THE DIA";
const char brf_dword_800E1564[28] = "      SHE MOVES TO THE US.";
const char brf_dword_800E1580[28] = "      CLEANUP AT CHERNOBYL,";
const char brf_dword_800E159C[28] = "      PARTICIPATED IN THE";
const char brf_dword_800E15B8[20] = "      PARENTS,WHO";
const char brf_dword_800E15CC[24] = "1990  AFTER LOSING HER";
const char brf_dword_800E15E4[20] = "      CHERNOBYL).";
const char brf_dword_800E15F8[28] = "      3 KILOMETERS NORTH OF";
const char brf_dword_800E1614[28] = "      IN PRYPIAT  (A CITY ";
const char brf_dword_800E1630[28] = "      POWER PLANT DISASTER";
const char brf_dword_800E164C[24] = "      CHERNOBYL NUCLEAR";
const char brf_dword_800E1664[28] = "      RADIATION FROM THE";
const char brf_dword_800E1680[28] = "      WERE SHOWERED BY THE";
const char brf_dword_800E169C[28] = "1986  SHE AND HER FAMILY";
const char brf_dword_800E16B8[24] = "1970s BORN IN UKRAINE.";
const char brf_dword_800E16D0[8] = "PROFILE";
const char brf_dword_800E16D8[16] = "HEIGHT: 166 CM";
const char brf_dword_800E16E8[24] = "NATIONALITY: UKRAINIAN";
const char brf_dword_800E1700[8] = "AGE: 30";
const char brf_dword_800E1708[12] = "SEX: FEMALE";
const char brf_dword_800E1714[28] = "NAME: NASTASHA ROMANENKO";
const char brf_dword_800E1730[12] = "ROMANENKO";
const char brf_dword_800E173C[12] = "NASTASHA";
const char brf_dword_800E1748[28] = "THOSE OF THE OPPOSITE SEX.";
const char brf_dword_800E1764[24] = "NOT TO BE ATTRACTED TO";
const char brf_dword_800E177C[28] = "HAS RECEIVED PSYCHOTHERAPY";
const char brf_dword_800E1798[20] = "COMBAT TRAINING.";
const char brf_dword_800E17AC[24] = "THROUGH VR SIMULATION";
const char brf_dword_800E17C4[28] = "EXPERIENCE, BUT HAS GONE";
const char brf_dword_800E17E0[24] = "SHE HAS NO REAL COMBAT";
const char brf_dword_800E17F8[20] = "     AS A NOVICE.";
const char brf_dword_800E180C[28] = "2005 JOINS THIS EXERCISE ";
const char brf_dword_800E1828[16] = "HEIGHT: 175 CM";
const char brf_dword_800E1838[20] = "NATIONALITY: USA";
const char brf_dword_800E184C[8] = "AGE: 18";
const char brf_dword_800E1854[24] = "NAME: MERYL SILVERBURGH";
const char brf_dword_800E186C[12] = "SILVERBURGH";
const char brf_dword_800E1878[8] = "MERYL";
const char brf_dword_800E1880[16] = "AT PRESIDENT";
const char brf_dword_800E1890[8] = "DARPA";
const char brf_dword_800E1898[16] = "OFFICE CHIEF";
const char brf_dword_800E18A8[12] = "BIG BOSS";
const char brf_dword_800E18B4[8] = "OCELOT";
const char brf_dword_800E18BC[12] = "REVOLVER";
const char brf_dword_800E18C8[16] = "VULCAN RAVEN";
const char brf_dword_800E18D8[8] = "OCTOPUS";
const char brf_dword_800E18E0[8] = "DECOY";
const char brf_dword_800E18E8[12] = "SNIPER WOLF";
const char brf_dword_800E18F4[8] = "MANTIS";
const char brf_dword_800E18FC[8] = "PSYCHO";
const char brf_dword_800E1904[12] = "A NATIVE.";
const char brf_dword_800E1910[20] = "SPEAKS ARABIC LIKE";
const char brf_dword_800E1924[20] = "FRENCH, MALAY, ETC.";
const char brf_dword_800E1938[28] = "SUCH AS ENGLISH, SPANISH,";
const char brf_dword_800E1954[24] = "FLUENT IN 7 LANGUAGES";
const char brf_dword_800E196C[20] = "HAS AN IQ OF 180.";
const char brf_dword_800E1980[20] = "      FOX-HOUND.";
const char brf_dword_800E1994[24] = "      LEADER OF THE NEW";
const char brf_dword_800E19AC[24] = "      BECOMES BATTLE";
const char brf_dword_800E19C4[28] = "2000  JOINS FOX-HOUND and";
const char brf_dword_800E19E0[16] = "      COUNTRY.";
const char brf_dword_800E19F0[24] = "      RETURNS TO HIS";
const char brf_dword_800E1A08[24] = "      GOVERNMENT AND";
const char brf_dword_800E1A20[24] = "1994  RESCUED BY THE US";
const char brf_dword_800E1A38[16] = "      A MIA.   ";
const char brf_dword_800E1A48[28] = "      IRAQ AND WAS DECLARED";
const char brf_dword_800E1A64[28] = "      HE BECOMES A POW OF";
const char brf_dword_800E1A80[28] = "      DURING THE MISSION";
const char brf_dword_800E1A9C[20] = "      THE GULF WAR.";
const char brf_dword_800E1AB0[28] = "      MISSILE LANCHERS IN";
const char brf_dword_800E1ACC[28] = "      THE MOBILE SCUD     ";
const char brf_dword_800E1AE8[28] = "      FORCE SAS TO DESTROY";
const char brf_dword_800E1B04[24] = "      BRITISH SPECIAL";
const char brf_dword_800E1B1C[20] = "1990  WORKS FOR THE";
const char brf_dword_800E1B30[20] = "      UPON BIRTH.";
const char brf_dword_800E1B44[24] = "      MOVED TO ENGLAND";
const char brf_dword_800E1B5C[24] = "1970s BORN IN THE US.";
const char brf_dword_800E1B74[16] = "HEIGHT: 183 CM";
const char brf_dword_800E1B84[28] = "NATIONALITY: BRITISH(USA)";
const char brf_dword_800E1BA0[12] = "AGE: 30s";
const char brf_dword_800E1BAC[12] = "SEX: MALE";
const char brf_dword_800E1BB8[16] = "NAME: UNKNOWN";
const char brf_dword_800E1BC8[24] = "CODE NAME: LIQUID SNAKE";
const char brf_dword_800E1BE0[16] = "LIQUID SNAKE";
const char brf_dword_800E1BF0[36] = "ERROR! Cannot Find Texture id = %d\n";
const char brf_dword_800E1C14[12] = "\xa5\xb9\xa5\xcd\xa1\xbc\xa5\xaf"; /* "スネーク" (Snake) */
const char brf_dword_800E1C20[16] = "a_fog_normal_3";
const char brf_dword_800E1C30[16] = "a_fog_normal_1";
const char brf_dword_800E1C40[16] = "a_fog_normal_4";
const char brf_dword_800E1C50[16] = "a_fog_normal_2";
const char brf_dword_800E1C60[16] = "a_fog_haku_3";
const char brf_dword_800E1C70[16] = "a_fog_haku_2";
const char brf_dword_800E1C80[16] = "a_fog_haku_1";
const char brf_dword_800E1C90[16] = "MePati Renzoku\n";
const char brf_dword_800E1CA0[16] = "b_face_open_u";
const char brf_dword_800E1CB0[20] = "b_face_angry_piku";

void brf_800CBE34(Work *work, POLY_FT4 *dest)
{
    DG_TEX *g;

    switch (work->field_AD30 % 128)
    {
    case 0:
    case 6:
    case 12:
    case 18:
    case 24:
        g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1CA0));
        break;
    case 3:
    case 9:
    case 15:
    case 21:
        g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1CB0));
        break;
    default:
        goto skip;
    }

    {
        int u = g->off_x;
        int uw = u + g->w + 1;
        int v = g->off_y;
        int vh = v + g->h + 1;

        dest->u0 = u;
        dest->v0 = v;
        dest->u1 = uw;
        dest->v1 = v;
        dest->u2 = u;
        dest->v2 = vh;
        dest->u3 = uw;
        dest->v3 = vh;
        dest->tpage = g->tpage;
        dest->clut = g->clut;
    }
skip:
    work->field_AD30++;
}
const char brf_dword_800E1D28[12] = "b_eye_open";
const char brf_dword_800E1D34[12] = "b_eye_half";
const char brf_dword_800E1D40[12] = "b_eye_close";
const char brf_dword_800E1D4C[12] = "b_eye_down";
const char brf_dword_800E1D58[4] = "abc";
const char brf_dword_800E1D5C[8] = "0123";
const char brf_dword_800E1D64[8] = "0123s";
extern const char brf_dword_800E1D28[];
extern const char brf_dword_800E1D34[];
extern const char brf_dword_800E1D40[];
extern const char brf_dword_800E1D4C[];

void brf_800CBF48(Work *work, POLY_FT4 *dest)
{
    DG_TEX *g;

    switch (work->field_AD30)
    {
    case 0:
        g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1D28));
        break;
    case 4:
        g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1D34));
        break;
    case 7:
        g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1D40));
        break;
    case 10:
        g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1D4C));
        break;
    default:
        goto skip;
    }

    {
        int u = g->off_x;
        int uw = u + g->w + 1;
        int v = g->off_y;
        int vh = v + g->h + 1;

        dest->u0 = u;
        dest->v0 = v;
        dest->u1 = uw;
        dest->v1 = v;
        dest->u2 = u;
        dest->v2 = vh;
        dest->u3 = uw;
        dest->v3 = vh;
        dest->tpage = g->tpage;
        dest->clut = g->clut;
    }
skip:
    work->field_AD30++;
}
extern const char brf_dword_800E1D58[];
extern const char brf_dword_800E1D64[];

void brf_800CC070(Work *work, int idx)
{
    POLY_FT4 *p = &work->small_polys[2];
    DG_TEX *tex = DG_GetTexture(GV_StrCode(brf_dword_800E1D58));
    int w1 = tex->w + 1;
    int ul = tex->off_x + w1 * idx / 3;
    int ur = tex->off_x + w1 * (idx + 1) / 3;
    int vt = tex->off_y;
    int h1 = tex->h + 1;
    int vb = tex->off_y + h1;

    p->u0 = ul;
    p->v0 = vt;
    p->u1 = ur;
    p->v1 = vt;
    p->u2 = ul;
    p->v2 = vb;
    p->u3 = ur;
    p->v3 = vb;
    p->tpage = tex->tpage;
    p->clut = tex->clut;
}
void brf_800CC150(Work *work)
{
    int i;

    work->prim_24_flags[0] = 0;
    work->small_flags[0] = 0;

    for (i = 1; i < 15; i++)
    {
        work->small_flags[i] = 2;
    }
}
void brf_800CC070();
extern int brf_dword_800C3508;

void brf_800CC190(Work *work)
{
    int i;

    work->scene_changed = 0;
    work->field_AD2C = 0;
    work->mouth = 0;
    work->mouth_changed = 0;
    work->field_ADB8 = 0;
    work->field_ADBC = 0;

    for (i = 1; i < 15; i++)
    {
        work->small_flags[i] = 2;
    }

    brf_800CC070(work, 0);
    GM_SeSet2(0, 0x3F, 0xC1);

    {
        short *tbl = (short *)&brf_dword_800C3508;
        for (i = 0; i < tbl[work->index]; i++)
        {
            work->poly_flags[i] = 0;
        }
    }

    work->field_ADC0 = GV_RandU(8) + 8;
}

void brf_800CC28C(Work *work)
{
    int i;

    work->scene_changed = 0;
    work->field_AD40 = 0;
    work->mouth = 0;
    work->mouth_changed = 0;
    work->field_ADB8 = 0;
    work->field_ADBC = 0;

    for (i = 1; i < 15; i++)
    {
        work->small_flags[i] = 2;
    }

    brf_800CC070(work, 1);
    GM_SeSet2(0, 0x3F, 0xC1);

    {
        short *tbl = (short *)&brf_dword_800C3508;
        for (i = 0; i < tbl[work->index]; i++)
        {
            work->poly_flags[i] = 0;
        }
    }

    work->field_ADC0 = GV_RandU(8) + 8;
}

void brf_800CC388(Work *work)
{
    int i;

    work->scene_changed = 0;
    work->mouth = 0;
    work->mouth_changed = 0;
    work->field_ADB8 = 0;
    work->field_ADBC = 0;

    for (i = 1; i < 15; i++)
    {
        work->small_flags[i] = 2;
    }

    brf_800CC070(work, 2);
    GM_SeSet2(0, 0x3F, 0xC1);

    {
        short *tbl = (short *)&brf_dword_800C3508;
        for (i = 0; i < tbl[work->index]; i++)
        {
            work->poly_flags[i] = 0;
        }
    }

    work->field_ADC0 = GV_RandU(8) + 8;
}

void brf_800CC480(Work *work)
{
    int i;

    work->scene_changed = 0;
    work->field_ADB8 = 0;
    work->field_ADBC = 0;

    for (i = 1; i < 15; i++)
    {
        work->small_flags[i] = 0;
    }

    GM_SeSet2(0, 0x3F, 0xC1);

    {
        short *tbl = (short *)&brf_dword_800C3508;
        for (i = 0; i < tbl[work->index]; i++)
        {
            work->poly_flags[i] = 0;
        }
    }

    work->field_ADC0 = GV_RandU(8) + 8;
}

void brf_800CC560(Work *work)
{
    int i;

    work->scene_changed = 0;

    for (i = 0; i < ((short *)&brf_dword_800C3508)[work->index]; i++)
    {
        work->poly_flags[i] = 0;
    }
}
int brf_800CC5CC(int a)
{
    if (a < 0 || a > 9)
    {
        a = 0;
    }

    return a;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CC5E4.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CCBD4.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CD164.s")
int brf_800CD734(unsigned char c)
{
    int idx;

    if ((unsigned char)(c - '0') < 10)
    {
        idx = c;
        idx -= '0';
    }
    else if (c == ':')
    {
        idx = 10;
    }
    else if (c == '.')
    {
        idx = 11;
    }
    else if (c == ',')
    {
        idx = 12;
    }
    else if (c == '(')
    {
        idx = 13;
    }
    else if (c == ')')
    {
        idx = 14;
    }
    else if (c == '\'')
    {
        idx = 15;
    }
    else if (c == '-')
    {
        idx = 16;
    }
    else if (c == ' ')
    {
        idx = 26;
    }
    else
    {
        idx = c - 'A';
    }

    return idx;
}

DG_TEX *brf_800CD7DC(Work *work, unsigned char c)
{
    if ((unsigned char)(c - '0') < 11 || c == '.' || c == ',' || c == '(' || c == ')' || c == '\'' || c == '-')
    {
        return brf_800CABF4(work, GV_StrCode(brf_dword_800E1D64));
    }
    return brf_800CABF4(work, GV_StrCode(brf_dword_800E1D58));
}
void brf_800CD870(Work *work, int idx)
{
    POLY_FT4 *base = work->polys;

    base[idx].y0 -= 12;
    base[idx].y1 -= 12;
    base[idx].y2 -= 12;
    base[idx].y3 -= 12;
}
void brf_800CD8B8(Work *work, int a1, int a2, int a3)
{
    POLY_FT4 *base = work->polys;
    int v = work->field_AD30;

    if (a1 >= v)
    {
        int q = v * 128 / a1;
        int c = 128 - q;

        setRGB0(&base[a2], c, c, c);
        setRGB0(&base[a3], q, q, q);
    }

    work->field_AD30++;
}
void brf_800CD958(Work *work, int a1, int a2, int a3)
{
    int n = work->field_AD30;
    if (n < 0x11)
    {
        POLY_FT4 *base = work->polys;
        int c3 = n * 8;
        int c1 = base[a1].r0 * (0x10 - n) / 16;
        int c2 = base[a2].r0 * (0x10 - n) / 16;
        setRGB0(&base[a1], c1, c1, c1);
        setRGB0(&base[a2], c2, c2, c2);
        setRGB0(&base[a3], c3, c3, c3);
    }
}
void brf_800CDA10(Work *work, int a1, int a2)
{
    POLY_FT4 *base = work->polys;
    int v = work->field_AD30;

    if (v < 17)
    {
        int c1 = base[a1].r0 * (16 - v) / 16;
        int c2 = base[a2].r0 * (16 - v) / 16;

        setRGB0(&base[a1], c1, c1, c1);
        setRGB0(&base[a2], c2, c2, c2);
    }
}
void brf_800CDAA8(Work *work, int idx)
{
    int v = work->field_AD30;
    POLY_FT4 *base = work->polys;

    if (v < 0x11)
    {
        v <<= 3;
        setRGB0(&base[idx], v, v, v);
    }
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CDAEC.s")
void brf_800CDC8C(Work *work, POLY_FT4 *poly)
{
    int n = work->field_AD2C;
    int mul = n * 2 + 5;
    int dx = n * 2 + 3;
    int rx0 = poly->x0 * mul / dx;
    int rx1 = poly->x1 * mul / dx;
    int my = 3 - n;
    int dy = my + 1;
    int ry0 = poly->y0 * my / dy;
    int ry2 = poly->y2 * my / dy;

    poly->x0 = rx0;
    poly->x2 = rx0;
    poly->x1 = rx1;
    poly->x3 = rx1;
    poly->y0 = ry0;
    poly->y1 = ry0;
    poly->y2 = ry2;
    poly->y3 = ry2;
}

void brf_800CDDD4(Work *work, int code, int idx)
{
    POLY_FT4 *base = work->polys;
    int       v;
    int       s;

    v = jimctrl_helper_80037F68(code);
    work->lipsync2 = v;
    s = v & 0xFF;
    if (work->mouth2 != s)
    {
        work->mouth_changed = 1;
        switch (s)
        {
        case 1:
            base[idx].y0 += 2;
            base[idx].y1 += 2;
            base[idx].y2 += 2;
            base[idx].y3 += 2;
            break;
        case 2:
            base[idx].y0 -= 2;
            base[idx].y1 -= 2;
            base[idx].y2 -= 2;
            base[idx].y3 -= 2;
            break;
        case 0:
            break;
        }
    }
    else if (work->mouth_changed != 0)
    {
        work->mouth_changed = 0;
        switch (s)
        {
        case 1:
            base[idx].y0 += 2;
            base[idx].y1 += 2;
            base[idx].y2 += 2;
            base[idx].y3 += 2;
            break;
        case 2:
            base[idx].y0 -= 2;
            base[idx].y1 -= 2;
            base[idx].y2 -= 2;
            base[idx].y3 -= 2;
            break;
        case 0:
            break;
        }
    }
    work->mouth2 = s;
}
void brf_800CDF34(Work *work)
{
    switch (work->view_mode)
    {
    case 1:
    case 4:
        work->view_mode = 2;
        brf_800CC28C(work);
        GM_SeSet2(0, 0x3f, 0xb0);
        break;
    case 2:
    case 5:
        work->view_mode = 3;
        brf_800CC388(work);
        GM_SeSet2(0, 0x3f, 0xb0);
        break;
    case 3:
    case 6:
        work->view_mode = 1;
        brf_800CC190(work);
        GM_SeSet2(0, 0x3f, 0xb0);
        break;
    }
}
const int brf_dword_800E1D84 = 0x800CE04C;
const int brf_dword_800E1D88 = 0x800CE110;
const int brf_dword_800E1D8C = 0x800CE13C;
const int brf_dword_800E1D90 = 0x800CE04C;
const int brf_dword_800E1D94 = 0x800CE110;
const int brf_dword_800E1D98 = 0x800CE13C;
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CDFE4.s")
extern int brf_dword_800C35F4, brf_dword_800C360C, brf_dword_800C3690;
void brf_800CDAEC();

void brf_800CE1C4(Work *work)
{
    POLY_FT4 *base = work->polys;
    int x = work->view[0].x;
    int y = work->view[0].y;
    int m = work->view[0].scale;

    brf_800CDAEC(base, 2, &brf_dword_800C35F4, x, y, m, 0xc8);
    brf_800CDAEC(base, 0xb, &brf_dword_800C360C, x * 12 / 10, y, m, 0xc8);
    brf_800CDAEC(base, 2, &brf_dword_800C3690, x * 15 / 10, y, m, 0xc8);
    if (work->zoom_count & 3)
    {
        GM_SeSet2(0, 0x30, 0x24);
    }
}
extern int brf_dword_800C36A8, brf_dword_800C36C0, brf_dword_800C372C;

void brf_800CE2F8(Work *work)
{
    POLY_FT4 *base = work->polys;
    int x = work->view[0].x;
    int y = work->view[0].y;
    int m = work->view[0].scale;

    brf_800CDAEC(base, 2, &brf_dword_800C36A8, x, y, m, 0xc8);
    brf_800CDAEC(base, 9, &brf_dword_800C36C0, x * 12 / 10, y, m, 0xc8);
    brf_800CDAEC(base, 2, &brf_dword_800C372C, x * 15 / 10, y, m, 0xc8);
    if (work->zoom_count && (work->zoom_count & 3))
    {
        GM_SeSet2(0, 0x30, 0x24);
    }
}
void brf_800CE430(work)
Work *work;
{
    unsigned short status = work->pad->status;

    if (work->move_state == 1 || work->move_state == 2)
    {
        switch (work->move_dir)
        {
        case 0:
            if (status & PAD_R) work->move_state++;
            else { work->move_state--; work->field_ADB8 = 0; work->field_ADBC = 1; }
            break;
        case 1:
            if (status & PAD_L) work->move_state++;
            else { work->move_state--; work->field_ADB8 = 0; work->field_ADBC = 1; }
            break;
        case 2:
            if (status & PAD_U) work->move_state++;
            else { work->move_state--; work->field_ADB8 = 0; work->field_ADBC = 1; }
            break;
        case 3:
            if (status & PAD_D) work->move_state++;
            else { work->move_state--; work->field_ADB8 = 0; work->field_ADBC = 1; }
            break;
        }
    }
    else if (work->move_state == 3)
    {
        switch (work->move_dir)
        {
        case 0:
            if (!(status & PAD_R)) { work->move_state = 2; work->field_ADB8 = 0; work->field_ADBC = 1; }
            break;
        case 1:
            if (!(status & PAD_L)) { work->move_state = 2; work->field_ADB8 = 0; work->field_ADBC = 1; }
            break;
        case 2:
            if (!(status & PAD_U)) { work->move_state--; work->field_ADB8 = 0; work->field_ADBC = 1; }
            break;
        case 3:
            if (!(status & PAD_D)) { work->move_state--; work->field_ADB8 = 0; work->field_ADBC = 1; }
            break;
        }
    }

    if (work->zoom_state == 1 || work->zoom_state == 2)
    {
        switch (work->zoom_dir)
        {
        case 4:
            if (status & PAD_X) { work->zoom_state++; work->zoom_count++; return; }
            work->zoom_state--; work->zoom_count = 0; work->field_ADB8 = 0; work->field_ADBC = 1;
            break;
        case 5:
            if (status & PAD_Y) { work->zoom_state++; work->zoom_count++; return; }
            work->zoom_state--; work->zoom_count = 0; work->field_ADB8 = 0; work->field_ADBC = 1;
            break;
        }
    }
    else if (work->zoom_state == 3)
    {
        switch (work->zoom_dir)
        {
        case 4:
            if (status & PAD_X) return;
            work->zoom_state = 2; work->zoom_count = 0; work->field_ADB8 = 0; work->field_ADBC = 1;
            break;
        case 5:
            if (status & PAD_Y) return;
            work->zoom_state = 2; work->zoom_count = 0; work->field_ADB8 = 0; work->field_ADBC = 1;
            break;
        }
    }
}
void brf_800CE648(work, idx, mode, delta)
Work *work;
int idx;
int mode;
int delta;
{
    if (work->polys[idx].x0 < -127)
    {
        switch (mode)
        {
        case 1:
            work->view[0].x += delta;
            break;
        case 2:
            work->view[1].x += delta;
            break;
        case 3:
            work->view[2].x += delta;
            break;
        }
    }
}

void brf_800CE6F0(work, idx, mode, delta)
Work *work;
int idx;
int mode;
int delta;
{
    if (work->polys[idx].x1 >= 0x80)
    {
        switch (mode)
        {
        case 1:
            work->view[0].x -= delta;
            break;
        case 2:
            work->view[1].x -= delta;
            break;
        case 3:
            work->view[2].x -= delta;
            break;
        }
    }
}

void brf_800CE798(work, a1, a2, a3)
Work *work;
int a1;
int a2;
int a3;
{
    POLY_FT4 *base = work->polys;
    if (base[a1 + 1].y2 < 0x59)
    {
        return;
    }
    switch (a2)
    {
    case 1:
        work->view[0].y -= a3;
        break;
    case 2:
        work->view[1].y -= a3;
        break;
    case 3:
        work->view[2].y -= a3;
        break;
    }
}

void brf_800CE840(work, idx, mode, delta)
Work *work;
int idx;
int mode;
int delta;
{
    if (work->polys[idx].y0 < -104)
    {
        switch (mode)
        {
        case 1:
            work->view[0].y += delta;
            break;
        case 2:
            work->view[1].y += delta;
            break;
        case 3:
            work->view[2].y += delta;
            break;
        }
    }
}
void brf_800CE8E8(work, which, amount)
Work *work;
int which;
int amount;
{
    switch (which)
    {
    case 1:
        if (work->view[0].scale < 391)
        {
            work->view[0].scale += amount;
        }
        else if (work->zoom_count)
        {
            work->zoom_count = 0;
        }
        break;
    case 2:
        if (work->view[1].scale < 391)
        {
            work->view[1].scale += amount;
        }
        else if (work->zoom_count)
        {
            work->zoom_count = 0;
        }
        break;
    case 3:
        if (work->view[2].scale < 391)
        {
            work->view[2].scale += amount;
        }
        else if (work->zoom_count)
        {
            work->zoom_count = 0;
        }
        break;
    }
}

void brf_800CE9A0(work, which, amount)
Work *work;
int which;
int amount;
{
    switch (which)
    {
    case 1:
        if (work->view[0].scale >= 202)
        {
            work->view[0].scale -= amount;
        }
        else if (work->zoom_count)
        {
            work->zoom_count = 0;
        }
        break;
    case 2:
        if (work->view[1].scale >= 202)
        {
            work->view[1].scale -= amount;
        }
        else if (work->zoom_count)
        {
            work->zoom_count = 0;
        }
        break;
    case 3:
        if (work->view[2].scale >= 202)
        {
            work->view[2].scale -= amount;
        }
        else if (work->zoom_count)
        {
            work->zoom_count = 0;
        }
        break;
    }
}

void brf_800CE798();

void brf_800CEA58(Work *work, int a1, int a2, int a3)
{
    switch (work->move_dir)
    {
    case 1:
        brf_800CE648(work);
        break;
    case 0:
        brf_800CE6F0(work);
        break;
    case 2:
        brf_800CE840(work);
        break;
    case 3:
        brf_800CE798(work);
        break;
    }
}
void brf_800CE2F8(Work *work);

void brf_800CEAF4(work)
Work *work;
{
    switch (work->zoom_dir)
    {
    case 4:
        brf_800CE8E8(work);
        break;
    case 5:
        brf_800CE9A0(work);
        break;
    }
}
void brf_800CE430();

void brf_800CEB4C(Work *work, int a1, int a2)
{
    brf_800CE430(work, a2);

    switch (work->zoom_state)
    {
    case 0:
        break;
    case 1:
        brf_800CEAF4(work, a2, 1);
        break;
    case 2:
        brf_800CEAF4(work, a2, 2);
        break;
    default:
        brf_800CEAF4(work, a2, 3);
        break;
    }

    switch (work->move_state)
    {
    case 0:
        break;
    case 1:
        brf_800CEA58(work, a1, a2, 1);
        break;
    case 2:
        brf_800CEA58(work, a1, a2, 2);
        break;
    default:
        brf_800CEA58(work, a1, a2, 3);
        break;
    }
}
void brf_800CEC68(Work *work)
{
    switch (work->view_mode)
    {
    case 1:
    case 4:
        brf_800CEB4C(work, 0, 1);
        break;
    case 2:
    case 5:
        brf_800CEB4C(work, 6, 2);
        break;
    case 3:
    case 6:
        brf_800CEB4C(work, 8, 3);
        break;
    }
}
const char brf_dword_800E1DB4[16] = "a_up_close_u";
const char brf_dword_800E1DC4[16] = "b_face_close_u";
const char brf_dword_800E1DD4[16] = "b_face_close_d";
const char brf_dword_800E1DE4[12] = "c_face_d";
const char brf_dword_800E1DF0[20] = "c_face_open_u";
const int brf_dword_800E1E04 = 0x800CEE28;
const int brf_dword_800E1E08 = 0x800CEEF8;
const int brf_dword_800E1E0C = 0x800CF03C;
const int brf_dword_800E1E10 = 0x800CF180;
const int brf_dword_800E1E14 = 0x800CF1A0;
const int brf_dword_800E1E18 = 0x800CF1E4;
const char brf_dword_800E1E1C[8] = "stop";
const char brf_dword_800E1E24[8] = "eject";
const char brf_dword_800E1E2C[12] = "b_eye_angry";
const char brf_dword_800E1E38[12] = "b_face_left";
const char brf_dword_800E1E44[12] = "a_up_left";
const char brf_dword_800E1E50[8] = "a_back";
const char brf_dword_800E1E58[12] = "a_up_close";
const char brf_dword_800E1E64[12] = "a_up_half";
const char brf_dword_800E1E70[12] = "a_up_open";
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CECE4.s")
void brf_800CE1C4(Work *work);

void brf_800CF22C(Work *work, int a1)
{
    unsigned short press = work->pad->press;

    if (press & PAD_R)
    {
        work->move_dir = 0;
        work->move_state = 1;
    }
    else if (press & PAD_L)
    {
        work->move_dir = 1;
        work->move_state = 1;
    }
    else if (press & PAD_U)
    {
        work->move_dir = 2;
        work->move_state = 1;
    }
    else if (press & PAD_D)
    {
        work->move_dir = 3;
        work->move_state = 1;
    }

    if (press & PAD_X)
    {
        work->zoom_dir = 4;
        work->zoom_state = 1;
    }
    else if (press & PAD_Y)
    {
        work->zoom_dir = 5;
        work->zoom_state = 1;
    }

    if (work->move_state != 0 || work->zoom_state != 0)
    {
        brf_800CEB4C(work, 0, 1);
    }

    if (a1 == 2)
    {
        brf_800CE1C4(work);
    }
    else if (a1 == 3)
    {
        brf_800CE2F8(work);
    }
}

void brf_800CF354(Work *work, int a1)
{
    if (work->pad->press != 0)
    {
        work->view_mode = 1;
        brf_800CF22C(work, a1);
    }
}
void brf_800CC190(Work *work);
void brf_800CC388(Work *work);
void brf_800CECE4(Work *work);

void brf_800CF394(Work *work, int a1)
{
    unsigned short press = work->pad->press;

    if (a1)
    {
        if (press & PAD_A)
        {
            work->view_mode = 1;
            brf_800CC190(work);
            GM_SeSet2(0, 0x3F, 0xB0);
        }
        else if (press & 0xFFFF)
        {
            work->view_mode = 3;
            brf_800CECE4(work);
        }
    }
    else
    {
        if (press & PAD_A)
        {
            work->view_mode = 3;
            brf_800CC388(work);
            GM_SeSet2(0, 0x3F, 0xB0);
        }
        else if (press & 0xFFFF)
        {
            work->view_mode = 2;
            brf_800CECE4(work);
        }
    }
}
void brf_800CC28C(Work *work);

void brf_800CF430(Work *work)
{
    unsigned short press = work->pad->press;

    if (press & PAD_A)
    {
        work->view_mode = 2;
        brf_800CC28C(work);
        GM_SeSet2(0, 0x3F, 0xB0);
    }
    else if (press & 0xFFFF)
    {
        work->view_mode = 1;
        brf_800CECE4(work);
    }
}
void brf_800CDAEC();

void brf_800CF4A0(Work *work, int a, int b, int c, int d, int e, void *f)
{
    brf_800CDAEC(work->polys, e, f, a, b, d, c);
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CF4E0.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CF5A8.s")
extern int brf_dword_800C3744;

void brf_800CF984(Work *work)
{
    POLY_FT4 *base = work->polys;
    DG_TEX *g;

    switch (work->scene)
    {
    case 1:
        if (work->scene_changed != 0)
        {
            GM_StreamPlayStart();
            brf_800CC150(work);
            brf_800CC388(work);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 8;
        }
        brf_800CCBD4(work, &base[0]);
        brf_800CADD4(work, &base[1], 10);
        break;
    case 2:
        if (work->scene_changed != 0)
        {
            brf_800CC28C(work);
            work->poly_flags[2] = 10;
            work->poly_flags[3] = 8;
            work->poly_flags[4] = 8;
        }
        brf_800CCBD4(work, &base[2]);
        brf_800CADD4(work, &base[4], 7);
        brf_800CBB68(work, &base[3], 2);
        break;
    case 3:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1E2C));
            BRF_SET_UV(&base[3], g);
            work->poly_flags[2] = 10;
            work->poly_flags[3] = 8;
            work->poly_flags[4] = 8;
        }
        brf_800CCBD4(work, &base[2]);
        brf_800CADD4(work, &base[4], 7);
        break;
    case 4:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1D28));
            BRF_SET_UV(&base[3], g);
            work->poly_flags[2] = 10;
            work->poly_flags[3] = 8;
            work->poly_flags[4] = 8;
        }
        brf_800CCBD4(work, &base[2]);
        brf_800CADD4(work, &base[4], 7);
        brf_800CBB68(work, &base[3], 2);
        break;
    case 5:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            brf_800CAC7C(work, GV_StrCode(brf_dword_800E1E38));
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1E38));
            BRF_SET_UV(&base[7], g);
            work->field_AD30 = 0;
            work->poly_flags[2] = 10;
            work->poly_flags[5] = 10;
        }
        brf_800CCBD4(work, &base[2]);
        brf_800CD8B8(work, 4, 2, 5);
        break;
    case 6:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            brf_800CAC7C(work, GV_StrCode(brf_dword_800E1E44));
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1E44));
            BRF_SET_UV(&base[8], g);
            work->field_AD30 = 0;
            work->poly_flags[5] = 10;
            work->poly_flags[6] = 10;
        }
        brf_800CCBD4(work, &base[5]);
        brf_800CD8B8(work, 8, 5, 6);
        break;
    case 7:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            brf_800CAC7C(work, GV_StrCode(brf_dword_800E1E50));
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1E50));
            BRF_SET_UV(&base[10], g);
            work->field_AD30 = 0;
            work->poly_flags[6] = 10;
            work->poly_flags[7] = 10;
        }
        brf_800CCBD4(work, &base[6]);
        brf_800CD8B8(work, 4, 6, 7);
        break;
    case 8:
        if (work->scene_changed != 0)
        {
            brf_800CC190(work);
            brf_800CAC7C(work, GV_StrCode(brf_dword_800E1E58));
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1E58));
            BRF_SET_UV(&base[9], g);
            brf_800CF4A0(work, 0, 0x5F, 0x64, 0xC8, 3, &brf_dword_800C3744);
            work->poly_flags[8] = 10;
            work->poly_flags[10] = 12;
        }
        brf_800CCBD4(work, &base[8]);
        break;
    case 9:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->field_AD30 = 0;
            brf_800CAC7C(work, GV_StrCode(brf_dword_800E1E64));
            work->poly_flags[8] = 10;
            work->poly_flags[9] = 10;
            work->poly_flags[10] = 12;
        }
        brf_800CCBD4(work, &base[8]);
        brf_800CD8B8(work, 16, 8, 9);
        break;
    case 10:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            brf_800CAC7C(work, GV_StrCode(brf_dword_800E1E70));
            work->poly_flags[9] = 10;
            work->poly_flags[10] = 12;
        }
        brf_800CCBD4(work, &base[9]);
        brf_800CADD4(work, &base[9], 0);
        break;
    case -1:
    case 11:
        brf_800CF5A8(work);
        break;
    }
}
const char brf_dword_800E1EB0[16] = "a_smoke_haku";
const char brf_dword_800E1EC0[12] = "a_smoke_up";
const char brf_dword_800E1ECC[16] = "a_smoke_half";
const char brf_dword_800E1EDC[20] = "a_smoke_down_close";
const char brf_dword_800E1EF0[12] = "a_smoke_suu";
const int brf_dword_800E1EFC = 0x800D1744;
const int brf_dword_800E1F00 = 0x800D174C;
const int brf_dword_800E1F04 = 0x800D034C;
const int brf_dword_800E1F08 = 0x800D042C;
const int brf_dword_800E1F0C = 0x800D04A4;
const int brf_dword_800E1F10 = 0x800D0500;
const int brf_dword_800E1F14 = 0x800D0604;
const int brf_dword_800E1F18 = 0x800D067C;
const int brf_dword_800E1F1C = 0x800D0780;
const int brf_dword_800E1F20 = 0x800D07DC;
const int brf_dword_800E1F24 = 0x800D08D8;
const int brf_dword_800E1F28 = 0x800D0AA4;
const int brf_dword_800E1F2C = 0x800D0B2C;
const int brf_dword_800E1F30 = 0x800D0C28;
const int brf_dword_800E1F34 = 0x800D0DE8;
const int brf_dword_800E1F38 = 0x800D0FB4;
const int brf_dword_800E1F3C = 0x800D1010;
const int brf_dword_800E1F40 = 0x800D10FC;
const int brf_dword_800E1F44 = 0x800D1158;
const int brf_dword_800E1F48 = 0x800D125C;
const int brf_dword_800E1F4C = 0x800D13B4;
const int brf_dword_800E1F50 = 0x800D14B0;
const int brf_dword_800E1F54 = 0x800D167C;
const int brf_dword_800E1F58 = 0x800D1744;
extern int brf_dword_800C3768, brf_dword_800C3798;

void brf_800D00C4(Work *work)
{
    POLY_FT4 *base = work->polys;

    switch (work->scene)
    {
    case 1:
        if (work->scene_changed != 0)
        {
            GM_StreamPlayStart();
            brf_800CC150(work);
            brf_800CC190(work);
            brf_800CF4A0(work, 0, 0x5A, 0x1C2, 0x44C, 4, &brf_dword_800C3768);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 12;
            work->field_AD38 = 0;
            work->field_AD30 = 0;
            work->poly_flags[2] = 8;
            work->poly_flags[3] = 8;
        }
        brf_800CF4E0(work, 0, 0, 0, 0x5A, 0x1C2, 1, &brf_dword_800C3798);
        brf_800CCBD4(work, &base[1]);
        brf_800CADD4(work, &base[0], 0);
        brf_800CADD4(work, &base[4], 0);
        break;
    case 2:
    case -1:
        brf_800CF5A8(work);
        break;
    case 0:
        break;
    }
}
void brf_800D0234(Work *work)
{
    if (work->field_AD34 < 0xF0)
    {
        brf_800CE6F0(work, 0, 1, 1);
    }
    else if (work->field_AD34 == 0xF0)
    {
        work->field_ADB8 = 0;
        work->field_ADBC = 1;
    }
    else if (work->field_AD34 >= 0x2BC)
    {
        if (work->field_AD34 < 0x348)
        {
            brf_800CE648(work, 0, 1, 1);
        }
        else if (work->field_AD34 == 0x348)
        {
            work->field_ADB8 = 0;
            work->field_ADBC = 1;
        }
    }
    brf_800CE1C4(work);
    work->field_AD34++;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D02F4.s")
void brf_800D1764(Work *work)
{
    if (work->field_AD34 < 0xBE)
    {
        brf_800CE8E8(work, 1, 1);
    }
    else if (work->field_AD34 == 0xBE)
    {
        work->field_ADB8 = 0;
        work->field_ADBC = 1;
    }
    brf_800CE2F8(work);
    work->field_AD34++;
}
void brf_800D17E8(Work *work, int idx1, int idx2)
{
    POLY_FT4 *base = work->polys;
    int v = work->field_AD3C << 2;

    setRGB0(&base[idx1], v, v, v);
    setRGB0(&base[idx2], v, v, v);
}
void brf_800D1838(Work *work)
{
    int n = work->field_AD3C - 0x20;
    int i;

    for (i = 0; i < n; i++)
    {
        work->poly_flags[i + 0xF] = 2;
        if (work->glyph_flags[i + 0xF] != 0)
        {
            GM_SeSet2(0, 0x30, 0xB6);
        }
    }
}
void brf_800D18D8(Work *work, int a1, int a2, int a3)
{
    int diff = work->field_AD3C - a1;
    int i;

    for (i = 0; i < 0x334; i++)
    {
        work->poly_flags[i + 0xF] = 0;
    }

    for (i = 0; i < 0x11; i++)
    {
        work->poly_flags[i + 0xF] = 2;
    }

    for (i = a2; i < a3; i++)
    {
        work->poly_flags[i] = 2;
    }

    for (i = 0; i < diff; i++)
    {
        work->poly_flags[i + a3] = 2;
        if (work->glyph_flags[i + a3] != 0)
        {
            GM_SeSet2(0, 0x30, 0xB6);
        }
    }
}
void brf_800D1A04(Work *work, int a1, int a2)
{
    int i;

    for (i = 0; i < 0x335; i++)
    {
        work->poly_flags[i + 0xF] = 0;
    }

    for (i = 0; i < 0x11; i++)
    {
        work->poly_flags[i + 0xF] = 2;
    }

    for (i = a1; i < a2; i++)
    {
        work->poly_flags[i] = 2;
        brf_800CD870(work, i);
    }
}
void brf_800D1AD8(Work *work)
{
    int v = work->field_AD3C;
    int i;

    if (v < 0x3E9)
    {
        return;
    }

    if (v < 0x409)
    {
        POLY_FT4 *base = work->polys;
        int c = 0x80 - ((v - 0x3E8) << 2);

        for (i = 0; i < 0x335; i++)
        {
            work->poly_flags[i + 0xF] = 0;
        }

        for (i = 0xD; i < 0x20; i++)
        {
            work->poly_flags[i] = 2;
            setRGB0(&base[i], c, c, c);
        }

        for (i = 0x2E6; i < 0x344; i++)
        {
            work->poly_flags[i] = 2;
            setRGB0(&base[i], c, c, c);
        }
    }
    else
    {
        for (i = 0; i < 0x335; i++)
        {
            work->poly_flags[i + 0xF] = 0;
        }
    }
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D1BDC.s")
void brf_800D26E4(Work *work)
{
    POLY_FT4 *base = work->polys;
    DG_TEX *g;

    switch (work->scene)
    {
    case 1:
        if (work->scene_changed != 0)
        {
            GM_StreamPlayStart();
            brf_800CC150(work);
            brf_800CC190(work);
            work->view[0].x = -0x50;
            work->view[0].y = 0x64;
            work->field_AD38 = 0;
            work->field_AD34 = 0;
            work->view_mode = 0;
            work->move_dir = 0;
            work->move_state = 0;
            work->view[0].scale = 0xC8;
            brf_800CE2F8(work);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 12;
            work->poly_flags[2] = 10;
            work->poly_flags[6] = 9;
            work->poly_flags[7] = 9;
            work->poly_flags[10] = 8;
            work->poly_flags[11] = 8;
            work->poly_flags[12] = 11;
        }
        brf_800CADD4(work, &base[2], 1);
        brf_800CB23C(work, 6, 7);
        brf_800CC5E4(work, &base[0], &base[1]);
        if (work->view_mode == 0)
        {
            brf_800CF354(work, 3);
            brf_800D1764(work);
        }
        else
        {
            brf_800CF22C(work, 3);
        }
        break;
    case 2:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 12;
            work->poly_flags[2] = 10;
            work->poly_flags[3] = 10;
            work->poly_flags[6] = 9;
            work->poly_flags[7] = 9;
            work->poly_flags[10] = 8;
            work->poly_flags[11] = 8;
            work->field_AD30 = 0;
            work->poly_flags[12] = 11;
        }
        brf_800CD8B8(work, 16, 2, 3);
        brf_800CDA10(work, 6, 7);
        brf_800CC5E4(work, &base[0], &base[1]);
        if (work->view_mode == 0)
        {
            brf_800CF354(work, 3);
            brf_800D1764(work);
        }
        else
        {
            brf_800CF22C(work, 3);
        }
        break;
    case 3:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->field_AD30 = 0;
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1EB0));
            BRF_SET_UV(&base[2], g);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 12;
            work->poly_flags[2] = 10;
            work->poly_flags[3] = 10;
            work->poly_flags[10] = 8;
            work->poly_flags[11] = 8;
            work->poly_flags[12] = 11;
        }
        brf_800CD8B8(work, 16, 3, 2);
        brf_800CC5E4(work, &base[0], &base[1]);
        if (work->view_mode == 0)
        {
            brf_800CF354(work, 3);
            brf_800D1764(work);
        }
        else
        {
            brf_800CF22C(work, 3);
        }
        break;
    case 4:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->field_AD30 = 0;
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1EC0));
            BRF_SET_UV(&base[3], g);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 12;
            work->poly_flags[2] = 10;
            work->poly_flags[3] = 10;
            work->poly_flags[4] = 9;
            work->poly_flags[10] = 8;
            work->poly_flags[11] = 8;
            work->poly_flags[12] = 11;
        }
        brf_800CD8B8(work, 16, 2, 3);
        brf_800CDAA8(work, 4);
        brf_800CC5E4(work, &base[0], &base[1]);
        if (work->view_mode == 0)
        {
            brf_800CF354(work, 3);
            brf_800D1764(work);
        }
        else
        {
            brf_800CF22C(work, 3);
        }
        break;
    case 5:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 12;
            work->poly_flags[3] = 10;
            work->poly_flags[4] = 9;
            work->poly_flags[5] = 9;
            work->field_AD3C = 0;
            work->field_AD38 = 0;
            work->poly_flags[10] = 8;
            work->poly_flags[11] = 8;
            work->poly_flags[12] = 11;
            work->poly_flags[13] = 8;
            work->poly_flags[14] = 8;
        }
        brf_800CAE84(work, 4, 5);
        brf_800D1BDC(work);
        brf_800CC5E4(work, &base[0], &base[1]);
        if (work->view_mode == 0)
        {
            brf_800CF354(work, 3);
            brf_800D1764(work);
        }
        else
        {
            brf_800CF22C(work, 3);
        }
        break;
    case 6:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->field_AD30 = 0;
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1EF0));
            BRF_SET_UV(&base[2], g);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 12;
            work->poly_flags[2] = 10;
            work->poly_flags[3] = 10;
            work->poly_flags[4] = 9;
            work->poly_flags[5] = 9;
            work->poly_flags[10] = 8;
            work->poly_flags[11] = 8;
            work->poly_flags[12] = 11;
            work->poly_flags[13] = 8;
            work->poly_flags[14] = 8;
        }
        brf_800CD8B8(work, 16, 3, 2);
        brf_800CAE84(work, 4, 5);
        brf_800D1BDC(work);
        brf_800CC5E4(work, &base[0], &base[1]);
        if (work->view_mode == 0)
        {
            brf_800CF354(work, 3);
            brf_800D1764(work);
        }
        else
        {
            brf_800CF22C(work, 3);
        }
        break;
    case 7:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 12;
            work->poly_flags[2] = 10;
            work->poly_flags[4] = 9;
            work->poly_flags[5] = 9;
            work->poly_flags[10] = 8;
            work->poly_flags[11] = 8;
            work->poly_flags[12] = 11;
            work->poly_flags[13] = 8;
            work->poly_flags[14] = 8;
        }
        brf_800CAE84(work, 4, 5);
        brf_800D1BDC(work);
        brf_800CC5E4(work, &base[0], &base[1]);
        if (work->view_mode == 0)
        {
            brf_800CF354(work, 3);
            brf_800D1764(work);
        }
        else
        {
            brf_800CF22C(work, 3);
        }
        break;
    case 8:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->field_AD30 = 0;
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1EB0));
            BRF_SET_UV(&base[3], g);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 12;
            work->poly_flags[2] = 10;
            work->poly_flags[3] = 10;
            work->poly_flags[4] = 9;
            work->poly_flags[5] = 9;
            work->poly_flags[8] = 9;
            work->poly_flags[10] = 8;
            work->poly_flags[11] = 8;
            work->poly_flags[12] = 11;
            work->poly_flags[13] = 8;
            work->poly_flags[14] = 8;
        }
        brf_800CD8B8(work, 16, 2, 3);
        brf_800CD958(work, 4, 5, 8);
        brf_800D1BDC(work);
        brf_800CC5E4(work, &base[0], &base[1]);
        if (work->view_mode == 0)
        {
            brf_800CF354(work, 3);
            brf_800D1764(work);
        }
        else
        {
            brf_800CF22C(work, 3);
        }
        break;
    case 9:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 12;
            work->poly_flags[3] = 10;
            work->poly_flags[8] = 9;
            work->poly_flags[9] = 9;
            work->field_AD38 = 0;
            work->poly_flags[10] = 8;
            work->poly_flags[11] = 8;
            work->poly_flags[12] = 11;
            work->poly_flags[13] = 8;
            work->poly_flags[14] = 8;
        }
        brf_800CB5F4(work, 8, 9);
        brf_800D1BDC(work);
        brf_800CC5E4(work, &base[0], &base[1]);
        if (work->view_mode == 0)
        {
            brf_800CF354(work, 3);
            brf_800D1764(work);
        }
        else
        {
            brf_800CF22C(work, 3);
        }
        break;
    case -1:
    case 15:
        brf_800CF5A8(work);
        break;
    }
}
const char brf_dword_800E1FA0[16] = "b_eye_r_tyoi";
const char brf_dword_800E1FB0[16] = "b_eye_l_tyou";
const char brf_dword_800E1FC0[16] = "b_eye_l_tyoi";
const char brf_dword_800E1FD0[12] = "\xa5\xad\xa5\xe3\xa5\xf3\xa5\xd9\xa5\xeb"; /* "キャンベル" (Campbell) */
const char brf_dword_800E1FDC[16] = "b_eye_r_tyou";
void brf_800D2E70(Work *work)
{
    POLY_FT4 *base = work->polys;
    int x = 0x7F - work->field_AD34 * 3;

    base[3].y0 = -0x96;
    base[3].y1 = -0x96;
    base[3].y2 = 0x69;
    base[3].y3 = 0x69;
    base[3].x0 = x;
    base[3].x1 = x + 0xFE;
    base[3].x2 = x;
    base[3].x3 = x + 0xFE;
    work->field_AD34++;
}
extern const char brf_dword_800E1FA0[];

void brf_800D2ED0(Work *work)
{
    POLY_FT4 *base = work->polys;
    int       t = work->field_AD38;
    DG_TEX   *g;

    if (t < 3)
    {
        base[3].x0 -= 3;
        base[3].x1 -= 3;
        base[3].x2 -= 3;
        base[3].x3 -= 3;
    }
    else if (t < 6)
    {
        base[3].x0 -= 2;
        base[3].x1 -= 2;
        base[3].x2 -= 2;
        base[3].x3 -= 2;
    }
    else if (t < 9)
    {
        base[3].x0 -= 1;
        base[3].x1 -= 1;
        base[3].x2 -= 1;
        base[3].x3 -= 1;
    }
    else if (t >= 12)
    {
        base[3].x0 += 3;
        base[3].x1 += 3;
        base[3].x2 += 3;
        base[3].x3 += 3;
    }

    if (work->field_AD38 == 0x12)
    {
        g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1FA0));
        {
            int u = g->off_x;
            int uw = u + g->w + 1;
            int v = g->off_y;
            int vh = v + g->h + 1;

            base[1].u0 = u;
            base[1].v0 = v;
            base[1].u1 = uw;
            base[1].v1 = v;
            base[1].u2 = u;
            base[1].v2 = vh;
            base[1].u3 = uw;
            base[1].v3 = vh;
            base[1].tpage = g->tpage;
            base[1].clut = g->clut;
        }
    }
    else if (work->field_AD38 == 0x18)
    {
        g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1D28));
        {
            int u = g->off_x;
            int uw = u + g->w + 1;
            int v = g->off_y;
            int vh = v + g->h + 1;

            base[1].u0 = u;
            base[1].v0 = v;
            base[1].u1 = uw;
            base[1].v1 = v;
            base[1].u2 = u;
            base[1].v2 = vh;
            base[1].u3 = uw;
            base[1].v3 = vh;
            base[1].tpage = g->tpage;
            base[1].clut = g->clut;
        }
    }

    work->field_AD38++;
}
void brf_800D30A0(Work *work)
{
    switch (work->time)
    {
    case 0x40:
        GM_SeSet2(0x1F, 0x30, 0xB4);
        break;
    case 0x60:
        GM_SeSet2(0x1F, 0x3F, 0xB5);
        break;
    case 0x80:
        GM_SeSet2(0x19, 0x3F, 0xB4);
        break;
    case 0xA0:
        GM_SeSet2(0x10, 0x3F, 0xB5);
        break;
    case 0xB4:
        GM_SeSet2(0xA, 0x3F, 0xB4);
        break;
    case 0x118:
        GM_SeSet2(0xA, 0x3F, 0xB5);
        break;
    case 0x140:
        GM_SeSet2(0xFA, 0x3F, 0xB4);
        break;
    case 0x258:
        GM_SeSet2(0xFA, 0x3F, 0xBF);
        break;
    case 0x278:
        GM_SeSet2(0xA, 0x3F, 0xB4);
        break;
    case 0x298:
        GM_SeSet2(0x14, 0x3F, 0xB5);
        break;
    case 0x2B8:
        GM_SeSet2(0x1E, 0x3F, 0xB4);
        break;
    case 0x2D8:
        GM_SeSet2(0x1F, 0x30, 0xB5);
        break;
    }
}
void brf_800D3220(Work *work)
{
    POLY_FT4 *base = work->polys;
    DG_TEX *g;

    switch (work->scene)
    {
    case 1:
        if (work->scene_changed != 0)
        {
            GM_StreamPlayStart();
            brf_800CC150(work);
            brf_800CC28C(work);
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1FB0));
            BRF_SET_UV(&base[1], g);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 10;
            work->poly_flags[2] = 10;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CCBD4(work, &base[0]);
        brf_800D30A0(work);
        break;
    case 2:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1FC0));
            BRF_SET_UV(&base[1], g);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 10;
            work->poly_flags[2] = 10;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CCBD4(work, &base[0]);
        brf_800D30A0(work);
        break;
    case 3:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1D28));
            BRF_SET_UV(&base[1], g);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 10;
            work->poly_flags[2] = 10;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CBB68(work, &base[1], 2);
        brf_800CCBD4(work, &base[0]);
        brf_800D30A0(work);
        break;
    case 4:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1FA0));
            BRF_SET_UV(&base[1], g);
            setRGB0(&base[3], 0x80, 0xC0, 0xC0);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 10;
            work->poly_flags[2] = 10;
            work->field_AD34 = 0;
            work->poly_flags[3] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800D2E70(work);
        brf_800CCBD4(work, &base[0]);
        brf_800D30A0(work);
        break;
    case 5:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 10;
            work->poly_flags[2] = 10;
            work->poly_flags[3] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CDDD4(work, GV_StrCode(brf_dword_800E1FD0), 3);
        brf_800CCBD4(work, &base[0]);
        brf_800D30A0(work);
        break;
    case 6:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1FDC));
            BRF_SET_UV(&base[1], g);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 10;
            work->poly_flags[2] = 10;
            work->poly_flags[3] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800D2E70(work);
        brf_800CCBD4(work, &base[0]);
        brf_800D30A0(work);
        break;
    case 7:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 10;
            work->poly_flags[2] = 10;
            work->field_AD38 = 0;
            work->poly_flags[3] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CDDD4(work, GV_StrCode(brf_dword_800E1FD0), 3);
        brf_800CCBD4(work, &base[0]);
        brf_800D30A0(work);
        break;
    case 8:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 10;
            work->poly_flags[2] = 10;
            work->field_AD38 = 0;
            work->poly_flags[3] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800D2ED0(work);
        brf_800CCBD4(work, &base[0]);
        brf_800D30A0(work);
        break;
    case 9:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 10;
            work->poly_flags[2] = 10;
            work->poly_flags[3] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CBB68(work, &base[1], 2);
        brf_800CCBD4(work, &base[0]);
        brf_800D30A0(work);
        break;
    case 10:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1E2C));
            BRF_SET_UV(&base[1], g);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 10;
            work->poly_flags[2] = 10;
            work->poly_flags[3] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CCBD4(work, &base[0]);
        break;
    case 11:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1D28));
            BRF_SET_UV(&base[1], g);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 10;
            work->poly_flags[2] = 10;
            work->poly_flags[3] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CBB68(work, &base[1], 2);
        brf_800CCBD4(work, &base[0]);
        break;
    case -1:
    case 12:
        brf_800CF5A8(work);
        break;
    }
}
void brf_800D39F0(Work *work, POLY_FT4 *a1, POLY_FT4 *a2)
{
    int v = work->field_AD30 << 2;

    setRGB0(a1, v, v, v);
    setRGB0(a2, v, v, v);
    work->field_AD30++;
}
void brf_800D3A30(Work *work)
{
    POLY_FT4 *base = work->polys;
    int c = 0x80 - (work->field_AD30 << 2);
    int i;

    setRGB0(&base[4], c, c, c);
    setRGB0(&base[5], c, c, c);
    for (i = 6; i < 22; i++)
    {
        work->poly_flags[i] = 2;
        setRGB0(&base[i], c, c, c);
    }
    for (i = 180; i < 291; i++)
    {
        work->poly_flags[i] = 2;
        setRGB0(&base[i], c, c, c);
    }
    work->field_AD30++;
}
void brf_800D3AF0(Work *work)
{
    int n = work->field_AD3C;
    int i;

    for (i = 0; i < n; i++)
    {
        work->poly_flags[i + 6] = 2;
        if (work->glyph_flags[i + 6] != 0)
        {
            GM_SeSet2(0, 0x30, 0xB6);
        }
    }
}
void brf_800D3B8C(Work *work, int a1, int a2, int a3)
{
    int diff = work->field_AD3C - a1;
    int i;

    for (i = 0; i < 0x11D; i++)
    {
        work->poly_flags[i + 6] = 0;
    }

    for (i = 0; i < 0x10; i++)
    {
        work->poly_flags[i + 6] = 2;
    }

    for (i = a2; i < a3; i++)
    {
        work->poly_flags[i] = 2;
    }

    for (i = 0; i < diff; i++)
    {
        work->poly_flags[i + a3] = 2;
        if (work->glyph_flags[i + a3] != 0)
        {
            GM_SeSet2(0, 0x30, 0xB6);
        }
    }
}
void brf_800D3CB8(Work *work, int a1, int a2)
{
    int i;

    for (i = 0; i < 0x11D; i++)
    {
        work->poly_flags[i + 6] = 0;
    }

    for (i = 0; i < 0x10; i++)
    {
        work->poly_flags[i + 6] = 2;
    }

    for (i = a1; i < a2; i++)
    {
        work->poly_flags[i] = 2;
        brf_800CD870(work, i);
    }
}
void brf_800D3D8C(Work *work)
{
    int i;
    int n = work->field_AD3C;

    if (n < 0x11)
    {
        brf_800D3AF0(work);
    }
    else if (n < 0x14)
    {
        for (i = 0; i < 16; i++)
        {
            work->poly_flags[i + 6] = 2;
        }
    }
    else if (n < 0x2B)
    {
        brf_800D3B8C(work, 0x13, 0x16, 0x16);
    }
    else if (n == 0x2D)
    {
        brf_800D3CB8(work, 0x16, 0x2D);
    }
    else if (n < 0x39)
    {
        brf_800D3B8C(work, 0x2D, 0x16, 0x2D);
    }
    else if (n == 0x3B)
    {
        brf_800D3CB8(work, 0x16, 0x38);
    }
    else if (n < 0x43)
    {
        brf_800D3B8C(work, 0x3B, 0x16, 0x38);
    }
    else if (n == 0x45)
    {
        brf_800D3CB8(work, 0x16, 0x3F);
    }
    else if (n < 0x56)
    {
        brf_800D3B8C(work, 0x45, 0x16, 0x3F);
    }
    else if (n == 0x58)
    {
        brf_800D3CB8(work, 0x16, 0x4F);
    }
    else if (n < 0x67)
    {
        brf_800D3B8C(work, 0x58, 0x16, 0x4F);
    }
    else if (n == 0x69)
    {
        brf_800D3CB8(work, 0x16, 0x5D);
    }
    else if (n == 0x6C)
    {
        brf_800D3CB8(work, 0x2D, 0x5D);
    }
    else if (n < 0x85)
    {
        brf_800D3B8C(work, 0x6C, 0x2D, 0x5D);
    }
    else if (n == 0x87)
    {
        brf_800D3CB8(work, 0x38, 0x75);
    }
    else if (n < 0x99)
    {
        brf_800D3B8C(work, 0x87, 0x38, 0x75);
    }
    else if (n == 0x9B)
    {
        brf_800D3CB8(work, 0x3F, 0x86);
    }
    else if (n == 0x9E)
    {
        brf_800D3CB8(work, 0x4F, 0x86);
    }
    else if (n < 0xB5)
    {
        brf_800D3B8C(work, 0x9E, 0x4F, 0x86);
    }
    else if (n == 0xB7)
    {
        brf_800D3CB8(work, 0x5D, 0x9C);
    }
    else if (n < 0xD0)
    {
        brf_800D3B8C(work, 0xB7, 0x5D, 0x9C);
    }
    else if (n == 0xD2)
    {
        brf_800D3CB8(work, 0x5D, 0xB4);
    }
    else if (n < 0xE8)
    {
        brf_800D3B8C(work, 0xD2, 0x5D, 0xB4);
    }
    else if (n == 0xEA)
    {
        brf_800D3CB8(work, 0x75, 0xC9);
    }
    else if (n < 0xFB)
    {
        brf_800D3B8C(work, 0xEA, 0x75, 0xC9);
    }
    else if (n == 0xFD)
    {
        brf_800D3CB8(work, 0x86, 0xD9);
    }
    else if (n < 0x118)
    {
        brf_800D3B8C(work, 0xFD, 0x86, 0xD9);
    }
    else if (n == 0x11A)
    {
        brf_800D3CB8(work, 0x86, 0xF3);
    }
    else if (n < 0x131)
    {
        brf_800D3B8C(work, 0x11A, 0x86, 0xF3);
    }
    else if (n == 0x133)
    {
        brf_800D3CB8(work, 0x9C, 0x109);
    }
    else if (n < 0x14E)
    {
        brf_800D3B8C(work, 0x133, 0x9C, 0x109);
    }
    else if (n == 0x150)
    {
        brf_800D3CB8(work, 0xB4, 0x123);
    }
    work->field_AD3C++;
}
extern int brf_dword_800C37A4;
void brf_800D3D8C(Work *work);

void brf_800D41A4(Work *work)
{
    POLY_FT4 *base = work->polys;
    int i;

    switch (work->scene)
    {
    case 1:
        if (work->scene_changed != 0)
        {
            GM_StreamPlayStart();
            brf_800CC150(work);
            brf_800CC28C(work);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 10;
        }
        brf_800CADD4(work, &base[1], 5);
        brf_800CBB68(work, &base[0], 0);
        brf_800CC5E4(work, &base[0], &base[1]);
        break;
    case 2:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 10;
            work->poly_flags[4] = 8;
            work->field_AD30 = 0;
            work->poly_flags[5] = 9;
            GM_SeSet2(0, 0x3F, 0xBC);
        }
        brf_800CADD4(work, &base[1], 5);
        brf_800CBB68(work, &base[0], 0);
        brf_800D39F0(work, &base[4], &base[5]);
        brf_800CC5E4(work, &base[0], &base[1]);
        break;
    case 3:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 10;
            work->poly_flags[4] = 8;
            work->field_AD34 = 0;
            work->field_AD3C = 0;
            work->poly_flags[5] = 9;
        }
        brf_800CADD4(work, &base[1], 5);
        brf_800CBB68(work, &base[0], 0);
        brf_800D3D8C(work);
        brf_800CC5E4(work, &base[0], &base[1]);
        break;
    case 4:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 10;
            work->poly_flags[4] = 8;
            work->field_AD30 = 0;
            work->field_AD38 = 0;
            work->poly_flags[5] = 9;
            for (i = 6; i < 22; i++)
            {
                work->poly_flags[i] = 7;
            }
        }
        brf_800CADD4(work, &base[1], 5);
        brf_800CBB68(work, &base[0], 0);
        brf_800D3A30(work);
        brf_800CF4E0(work, 1, 0x140, -0x1E, -0x1E, 0x1F4, 4, &brf_dword_800C37A4);
        brf_800CC5E4(work, &base[0], &base[1]);
        break;
    case 5:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 10;
        }
        brf_800CADD4(work, &base[1], 5);
        brf_800CBB68(work, &base[0], 0);
        brf_800CF4E0(work, 1, 0x140, -0x1E, -0x1E, 0x1F4, 4, &brf_dword_800C37A4);
        brf_800CC5E4(work, &base[0], &base[1]);
        break;
    case 6:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->field_AD30 = 0;
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 10;
            work->poly_flags[2] = 10;
            work->poly_flags[3] = 10;
        }
        brf_800CADD4(work, &base[1], 5);
        brf_800CBB68(work, &base[0], 0);
        brf_800CF4E0(work, 1, 0x140, -0x1E, -0x1E, 0x1F4, 4, &brf_dword_800C37A4);
        brf_800CD8B8(work, 16, 0, 2);
        brf_800CD8B8(work, 16, 1, 3);
        brf_800CC5E4(work, &base[0], &base[1]);
        break;
    case -1:
    case 7:
        brf_800CF5A8(work);
        break;
    }
}
const char brf_dword_800E2048[4] = "";
extern int brf_dword_800C37D4;

void brf_800D45C4(Work *work)
{
    if (work->field_AD38 < 0x1f4)
    {
        int mul = 0x2ee - work->field_AD38;
        brf_800CDAEC(work->polys, 6, &brf_dword_800C37D4, 0, 0x5a, mul, 0xfa);
    }
    else if (work->field_AD38 == 0x1f4)
    {
        work->field_ADB8 = 0;
        work->field_ADBC = 1;
    }
    work->field_AD38++;
}
void brf_800D4664(Work *work)
{
    POLY_FT4 *base = work->polys;

    switch (work->scene)
    {
    case 1:
        if (work->scene_changed != 0)
        {
            GM_StreamPlayStart();
            brf_800CC150(work);
            brf_800CC388(work);
            work->poly_flags[5] = 10;
            work->poly_flags[6] = 10;
        }
        brf_800CADD4(work, &base[5], 8);
        brf_800CC5E4(work, &base[5], &base[6]);
        break;
    case 2:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->field_AD30 = 0;
            work->poly_flags[5] = 10;
            work->poly_flags[6] = 10;
            work->poly_flags[7] = 10;
        }
        brf_800CD8B8(work, 16, 5, 7);
        brf_800CC5E4(work, &base[5], &base[6]);
        break;
    case 3:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->field_AD30 = 0;
            work->poly_flags[6] = 10;
            work->poly_flags[7] = 10;
        }
        brf_800CADD4(work, &base[7], 9);
        brf_800CC5E4(work, &base[6], &base[7]);
        break;
    case 4:
        if (work->scene_changed != 0)
        {
            brf_800CC190(work);
            work->poly_flags[0] = 8;
            work->poly_flags[1] = 8;
            work->field_AD38 = 0;
            work->poly_flags[2] = 12;
            work->poly_flags[3] = 10;
            work->poly_flags[4] = 10;
            work->poly_flags[8] = 12;
        }
        brf_800CADD4(work, &base[3], 2);
        brf_800D45C4(work);
        brf_800CC5E4(work, &base[2], &base[8]);
        break;
    case -1:
    case 5:
        brf_800CF5A8(work);
        break;
    }
}
const char brf_dword_800E2068[4] = "";
void brf_800D486C(Work *work, POLY_FT4 *a1, POLY_FT4 *a2)
{
    int v = work->field_AD30 << 2;

    setRGB0(a1, v, v, v);
    setRGB0(a2, v, v, v);
    work->field_AD30++;
}
void brf_800D48AC(Work *work)
{
    POLY_FT4 *base = work->polys;
    int c = 0x80 - (work->field_AD30 << 2);
    int i;

    setRGB0(&base[2], c, c, c);
    setRGB0(&base[3], c, c, c);
    setRGB0(&base[7], c, c, c);
    setRGB0(&base[8], c, c, c);
    for (i = 9; i < 38; i++)
    {
        setRGB0(&base[i], c, c, c);
    }
    work->field_AD30++;
}
void brf_800D493C(Work *work)
{
    work->poly_flags[work->field_AD34 + 9] = 2;
    if (work->glyph_flags[work->field_AD34 + 9] != 0)
    {
        GM_SeSet2(0, 0x30, 0xB6);
    }
    work->field_AD34++;
}
void brf_800D49B8(Work *work)
{
    work->poly_flags[work->field_AD34 + 0x1A] = 2;
    if (work->glyph_flags[work->field_AD34 + 0x1A] != 0)
    {
        GM_SeSet2(0, 0x30, 0xB6);
    }
    work->field_AD34++;
}
extern int brf_dword_800C381C;

void brf_800D4A34(Work *work)
{
    POLY_FT4 *base = work->polys;
    int i;

    switch (work->scene)
    {
    case 1:
        if (work->scene_changed != 0)
        {
            brf_800CC150(work);
            brf_800CC190(work);
            GM_StreamPlayStart();
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 12;
            work->poly_flags[5] = 7;
            work->poly_flags[6] = 7;
            work->field_AD38 = 0;
            work->poly_flags[38] = 14;
            work->poly_flags[39] = 14;
        }
        brf_800CF4E0(work, 0, 0, 0, 0x5F, 0x17C, 7, &brf_dword_800C381C);
        brf_800CADD4(work, &base[0], 4);
        brf_800CC5E4(work, &base[38], &base[39]);
        break;
    case 2:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 12;
            work->poly_flags[5] = 7;
            work->poly_flags[6] = 7;
            work->poly_flags[38] = 14;
            work->poly_flags[39] = 14;
        }
        brf_800CF4E0(work, 0, 0, 0, 0x5F, 0x17C, 7, &brf_dword_800C381C);
        brf_800CADD4(work, &base[0], 4);
        brf_800CC5E4(work, &base[38], &base[39]);
        break;
    case 3:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 12;
            work->poly_flags[3] = 8;
            work->poly_flags[5] = 7;
            work->poly_flags[6] = 7;
            work->poly_flags[8] = 10;
            work->field_AD30 = 0;
            work->poly_flags[38] = 14;
            work->poly_flags[39] = 14;
            GM_SeSet2(0, 0x3F, 0xBC);
        }
        brf_800CF4E0(work, 0, 0, 0, 0x5F, 0x17C, 7, &brf_dword_800C381C);
        brf_800D486C(work, &base[3], &base[8]);
        brf_800CADD4(work, &base[0], 4);
        brf_800CC5E4(work, &base[38], &base[39]);
        break;
    case 4:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 12;
            work->poly_flags[2] = 8;
            work->poly_flags[3] = 8;
            work->poly_flags[5] = 7;
            work->poly_flags[6] = 7;
            work->poly_flags[7] = 10;
            work->poly_flags[8] = 10;
            work->field_AD30 = 0;
            work->field_AD34 = 0;
            work->poly_flags[38] = 14;
            work->poly_flags[39] = 14;
            GM_SeSet2(0, 0x3F, 0xBC);
        }
        brf_800CF4E0(work, 0, 0, 0, 0x5F, 0x17C, 7, &brf_dword_800C381C);
        brf_800D486C(work, &base[2], &base[7]);
        brf_800D493C(work);
        brf_800CADD4(work, &base[0], 4);
        brf_800CC5E4(work, &base[38], &base[39]);
        break;
    case 5:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 12;
            work->poly_flags[2] = 8;
            work->poly_flags[3] = 8;
            work->poly_flags[5] = 7;
            work->poly_flags[6] = 7;
            work->poly_flags[7] = 10;
            work->poly_flags[8] = 10;
            for (i = 9; i < 26; i++)
            {
                work->poly_flags[i] = 2;
            }
            work->poly_flags[38] = 14;
            work->poly_flags[39] = 14;
        }
        brf_800CF4E0(work, 0, 0, 0, 0x5F, 0x17C, 7, &brf_dword_800C381C);
        brf_800D486C(work, &base[2], &base[7]);
        brf_800CADD4(work, &base[0], 4);
        brf_800CC5E4(work, &base[38], &base[39]);
        break;
    case 6:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 12;
            work->poly_flags[2] = 8;
            work->poly_flags[3] = 8;
            work->poly_flags[5] = 7;
            work->poly_flags[6] = 7;
            work->field_AD34 = 0;
            work->poly_flags[7] = 10;
            work->poly_flags[8] = 10;
            for (i = 9; i < 26; i++)
            {
                work->poly_flags[i] = 2;
            }
            work->poly_flags[38] = 14;
            work->poly_flags[39] = 14;
        }
        brf_800CF4E0(work, 0, 0, 0, 0x5F, 0x17C, 7, &brf_dword_800C381C);
        brf_800D49B8(work);
        brf_800CADD4(work, &base[0], 4);
        brf_800CC5E4(work, &base[38], &base[39]);
        break;
    case 7:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 12;
            work->poly_flags[2] = 8;
            work->poly_flags[3] = 8;
            work->poly_flags[5] = 7;
            work->poly_flags[6] = 7;
            work->field_AD34 = 0;
            work->poly_flags[7] = 10;
            work->poly_flags[8] = 10;
            for (i = 9; i < 38; i++)
            {
                work->poly_flags[i] = 2;
            }
            work->poly_flags[38] = 14;
            work->poly_flags[39] = 14;
        }
        brf_800CF4E0(work, 0, 0, 0, 0x5F, 0x17C, 7, &brf_dword_800C381C);
        brf_800CADD4(work, &base[0], 4);
        brf_800CC5E4(work, &base[38], &base[39]);
        break;
    case 8:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 12;
            work->poly_flags[2] = 8;
            work->poly_flags[3] = 8;
            work->poly_flags[5] = 7;
            work->poly_flags[6] = 7;
            work->field_AD30 = 0;
            work->poly_flags[7] = 10;
            work->poly_flags[8] = 10;
            for (i = 9; i < 38; i++)
            {
                work->poly_flags[i] = 2;
            }
            work->poly_flags[38] = 14;
            work->poly_flags[39] = 14;
        }
        brf_800CF4E0(work, 0, 0, 0, 0x5F, 0x17C, 7, &brf_dword_800C381C);
        brf_800D48AC(work);
        brf_800CADD4(work, &base[0], 4);
        brf_800CC5E4(work, &base[38], &base[39]);
        break;
    case 9:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 12;
            work->poly_flags[5] = 7;
            work->poly_flags[6] = 7;
            work->poly_flags[38] = 14;
            work->poly_flags[39] = 14;
        }
        brf_800CF4E0(work, 0, 0, 0, 0x5F, 0x17C, 7, &brf_dword_800C381C);
        brf_800CADD4(work, &base[0], 4);
        brf_800CC5E4(work, &base[38], &base[39]);
        break;
    case 10:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 10;
            work->poly_flags[4] = 10;
            work->poly_flags[5] = 7;
            work->poly_flags[6] = 7;
            work->field_AD30 = 0;
            work->poly_flags[38] = 14;
            work->poly_flags[39] = 14;
        }
        brf_800CF4E0(work, 0, 0, 0, 0x5F, 0x17C, 7, &brf_dword_800C381C);
        brf_800CD8B8(work, 16, 0, 4);
        brf_800CC5E4(work, &base[38], &base[39]);
        break;
    case 11:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[1] = 10;
            work->poly_flags[4] = 10;
            work->poly_flags[5] = 7;
            work->poly_flags[6] = 7;
            work->poly_flags[38] = 14;
            work->poly_flags[39] = 14;
        }
        brf_800CF4E0(work, 0, 0, 0, 0x5F, 0x17C, 7, &brf_dword_800C381C);
        brf_800CC5E4(work, &base[38], &base[39]);
        break;
    case -1:
    case 12:
        brf_800CF5A8(work);
        break;
    }
}
extern int brf_dword_800C3870, brf_dword_800C3888;

void brf_800D52F0(Work *work)
{
    POLY_FT4 *base = work->polys;
    DG_TEX *g;

    switch (work->scene)
    {
    case 1:
        if (work->scene_changed != 0)
        {
            GM_StreamPlayStart();
            brf_800CC150(work);
            brf_800CC388(work);
            work->view[0].y = 0x1E;
            work->view[1].y = 0x1E;
            work->view[1].scale = 0xF0;
            work->view[2].y = 0x1E;
            work->view[0].scale = 0xF0;
            work->view[2].scale = 0xF0;
            work->view_mode = 0;
            work->move_dir = 0;
            work->move_state = 0;
            work->view[0].x = 0;
            work->view[1].x = 0;
            work->view[2].x = 0;
            brf_800CF4A0(work, work->view[1].x, work->view[1].y, 0xC8, work->view[1].scale, 2, &brf_dword_800C3870);
            brf_800CF4A0(work, work->view[2].x, work->view[2].y, 0xC8, work->view[2].scale, 2, &brf_dword_800C3888);
            brf_800CAC7C(work, GV_StrCode(brf_dword_800E1DE4));
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1DF0));
            BRF_SET_UV(&base[8], g);
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1DE4));
            BRF_SET_UV(&base[9], g);
            work->poly_flags[8] = 10;
            work->poly_flags[9] = 10;
        }
        if (work->view_mode == 0)
        {
            brf_800CF394(work, 1);
            brf_800CADD4(work, &base[8], 8);
            brf_800CC5E4(work, &base[8], &base[9]);
        }
        else
        {
            brf_800CECE4(work);
        }
        break;
    case 2:
        if (work->scene_changed != 0)
        {
            if (work->view_mode == 0)
            {
                brf_800CC28C(work);
                work->view[1].y = 0x1E;
                work->view[1].x = 0;
                work->view[1].scale = 0x118;
                brf_800CAC7C(work, GV_StrCode(brf_dword_800E1DC4));
                g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1CA0));
                BRF_SET_UV(&base[6], g);
                g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1DD4));
                BRF_SET_UV(&base[7], g);
                brf_800CF4A0(work, work->view[1].x, work->view[1].y, 0xC8, work->view[1].scale, 2, &brf_dword_800C3870);
                brf_800CF4A0(work, work->view[2].x, work->view[2].y, 0xC8, work->view[2].scale, 2, &brf_dword_800C3888);
                work->poly_flags[6] = 10;
                work->poly_flags[7] = 10;
            }
            else
            {
                goto call_cece4;
            }
        }
        if (work->view_mode == 0)
        {
            brf_800CF394(work, 0);
            brf_800CADD4(work, &base[7], 5);
            brf_800CBB68(work, &base[6], 0);
            brf_800CC5E4(work, &base[6], &base[7]);
        }
        else
        {
call_cece4:
            brf_800CECE4(work);
        }
        break;
    case -1:
    case 3:
        brf_800CF5A8(work);
        break;
    case 0:
        break;
    }
}
const char brf_dword_800E20B8[4] = "";

extern int brf_dword_800C38A0;

void brf_800D5780(Work *work)
{
    POLY_FT4 *base = work->polys;
    DG_TEX *g;

    switch (work->scene)
    {
    case 1:
        if (work->scene_changed != 0)
        {
            GM_StreamPlayStart();
            brf_800CC150(work);
            brf_800CC28C(work);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CBB68(work, &base[1], 2);
        brf_800CCBD4(work, &base[0]);
        break;
    case 2:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1E2C));
            BRF_SET_UV(&base[1], g);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CCBD4(work, &base[0]);
        break;
    case 3:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1D28));
            BRF_SET_UV(&base[1], g);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CBB68(work, &base[1], 2);
        brf_800CCBD4(work, &base[0]);
        break;
    case 4:
        if (work->scene_changed != 0)
        {
            brf_800CC190(work);
            brf_800CF4A0(work, 0, 0x50, 0x64, 0xA0, 6, &brf_dword_800C38A0);
            work->poly_flags[3] = 10;
            work->poly_flags[5] = 10;
            work->poly_flags[6] = 8;
            work->poly_flags[7] = 8;
            work->poly_flags[8] = 12;
        }
        brf_800CADD4(work, &base[3], 4);
        brf_800CCBD4(work, &base[8]);
        break;
    case 5:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[3] = 10;
            work->poly_flags[4] = 10;
            work->poly_flags[5] = 10;
            work->poly_flags[6] = 8;
            work->poly_flags[7] = 8;
            work->field_AD30 = 0;
            work->poly_flags[8] = 12;
        }
        brf_800CD8B8(work, 16, 3, 4);
        brf_800CCBD4(work, &base[8]);
        break;
    case 6:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[3] = 10;
            work->poly_flags[4] = 10;
            work->poly_flags[5] = 10;
            work->poly_flags[6] = 8;
            work->poly_flags[7] = 8;
            work->field_AD30 = 0;
            work->poly_flags[8] = 12;
        }
        brf_800CD8B8(work, 16, 4, 3);
        brf_800CCBD4(work, &base[8]);
        break;
    case 7:
        if (work->scene_changed != 0)
        {
            brf_800CC28C(work);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CBB68(work, &base[1], 1);
        brf_800CCBD4(work, &base[0]);
        break;
    case 8:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 10;
            work->field_AD34 = 0;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
        }
        brf_800CBDC8(work, &base[1]);
        brf_800CCBD4(work, &base[0]);
        break;
    case 9:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
        }
        brf_800CBB68(work, &base[1], 2);
        brf_800CCBD4(work, &base[0]);
        break;
    case 10:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 10;
            work->field_AD34 = 0;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
        }
        brf_800CBD5C(work, &base[1]);
        brf_800CCBD4(work, &base[0]);
        break;
    case 11:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 10;
            work->field_AD34 = 0;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
        }
        brf_800CBB68(work, &base[1], 1);
        brf_800CCBD4(work, &base[0]);
        break;
    case -1:
    case 12:
        brf_800CF5A8(work);
        break;
    }
}
const char brf_dword_800E20F4[16] = "b_mar_eye_open";
const char brf_dword_800E2104[16] = "c_face_half_u";
const char brf_dword_800E2114[16] = "c_face_close_u";
void brf_800D5CC4(Work *work)
{
    POLY_FT4 *base = work->polys;
    int v = work->field_AD30;

    if (v < 0x11)
    {
        int c;
        v <<= 3;
        c = 0x80 - v;
        setRGB0(&base[0], c, c, c);
        setRGB0(&base[1], c, c, c);
        setRGB0(&base[2], c, c, c);
        setRGB0(&base[3], v, v, v);
    }
    work->field_AD30++;
}
void brf_800D5D30(Work *work)
{
    POLY_FT4 *base = work->polys;
    int v = work->field_AD30;

    if (v < 0x11)
    {
        int c;
        v <<= 3;
        c = 0x80 - v;
        setRGB0(&base[3], c, c, c);
        setRGB0(&base[4], v, v, v);
        setRGB0(&base[5], v, v, v);
        setRGB0(&base[6], v, v, v);
    }
    work->field_AD30++;
}
void brf_800D5D9C(Work *work, POLY_FT4 *a1, POLY_FT4 *a2)
{
    int v = work->field_AD30 << 2;

    setRGB0(a1, v, v, v);
    setRGB0(a2, v, v, v);
    work->field_AD30++;
}
void brf_800D5DDC(Work *work)
{
    POLY_FT4 *base = work->polys;
    int c = 0x80 - (work->field_AD30 << 2);
    int i;

    setRGB0(&base[10], c, c, c);
    setRGB0(&base[11], c, c, c);
    for (i = 12; i < 20; i++)
    {
        setRGB0(&base[i], c, c, c);
    }
    work->field_AD30++;
}
void brf_800D5E54(Work *work)
{
    work->poly_flags[work->field_AD34 + 0xC] = 2;
    if (work->glyph_flags[work->field_AD34 + 0xC] != 0)
    {
        GM_SeSet2(0, 0x30, 0xB6);
    }
    work->field_AD34++;
}
extern int brf_dword_800C38E8;

void brf_800D5ED0(Work *work)
{
    POLY_FT4 *base = work->polys;
    DG_TEX *g;
    int i;

    switch (work->scene)
    {
    case 1:
        if (work->scene_changed != 0)
        {
            GM_StreamPlayStart();
            brf_800CC150(work);
            brf_800CC28C(work);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CBB68(work, &base[1], 1);
        brf_800CCBD4(work, &base[0]);
        break;
    case 2:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 10;
            work->field_AD30 = 0;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
            work->poly_flags[3] = 8;
        }
        brf_800D5CC4(work);
        brf_800CCBD4(work, &base[0]);
        break;
    case 3:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[3] = 10;
            work->poly_flags[4] = 10;
            work->field_AD30 = 0;
            work->poly_flags[5] = 8;
            work->poly_flags[6] = 8;
        }
        brf_800D5D30(work);
        brf_800CCBD4(work, &base[3]);
        break;
    case 4:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[4] = 10;
            work->poly_flags[5] = 8;
            work->poly_flags[6] = 8;
        }
        brf_800CADD4(work, &base[6], 6);
        brf_800CCBD4(work, &base[4]);
        break;
    case 5:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E20F4));
            BRF_SET_UV(&base[5], g);
            work->poly_flags[4] = 10;
            work->poly_flags[5] = 8;
            work->poly_flags[6] = 8;
        }
        brf_800CADD4(work, &base[6], 6);
        brf_800CCBD4(work, &base[4]);
        break;
    case 6:
        if (work->scene_changed != 0)
        {
            brf_800CC388(work);
            work->poly_flags[7] = 12;
            work->poly_flags[9] = 12;
            work->poly_flags[10] = 8;
            work->field_AD38 = 0;
            work->poly_flags[11] = 10;
            GM_SeSet2(0, 0x3F, 0xBC);
        }
        brf_800D5D9C(work, &base[10], &base[11]);
        brf_800CADD4(work, &base[7], 9);
        brf_800CF4E0(work, 1, 0x258, 0, 0x55, 0x190, 3, &brf_dword_800C38E8);
        brf_800CC5E4(work, &base[7], &base[9]);
        break;
    case 7:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            brf_800CAC7C(work, GV_StrCode(brf_dword_800E2104));
            brf_800CAC7C(work, GV_StrCode(brf_dword_800E2114));
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E2114));
            BRF_SET_UV(&base[8], g);
            work->poly_flags[7] = 12;
            work->poly_flags[9] = 12;
            work->poly_flags[10] = 8;
            work->field_AD34 = 0;
            work->poly_flags[11] = 10;
        }
        brf_800D5E54(work);
        brf_800CADD4(work, &base[7], 9);
        brf_800CF4E0(work, 1, 0x258, 0, 0x55, 0x190, 3, &brf_dword_800C38E8);
        brf_800CC5E4(work, &base[7], &base[9]);
        break;
    case 8:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            brf_800CAC7C(work, GV_StrCode(brf_dword_800E1DF0));
            work->poly_flags[7] = 12;
            work->poly_flags[9] = 12;
            work->poly_flags[10] = 8;
            work->poly_flags[11] = 10;
            for (i = 12; i < 20; i++)
            {
                work->poly_flags[i] = 2;
            }
        }
        brf_800CADD4(work, &base[7], 9);
        brf_800CF4E0(work, 1, 0x258, 0, 0x55, 0x190, 3, &brf_dword_800C38E8);
        brf_800CC5E4(work, &base[7], &base[9]);
        break;
    case 9:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[7] = 12;
            work->poly_flags[8] = 12;
            work->poly_flags[9] = 12;
            work->poly_flags[10] = 8;
            work->field_AD30 = 0;
            work->poly_flags[11] = 10;
            for (i = 12; i < 20; i++)
            {
                work->poly_flags[i] = 2;
            }
        }
        brf_800CD8B8(work, 16, 7, 8);
        brf_800CF4E0(work, 1, 0x258, 0, 0x55, 0x190, 3, &brf_dword_800C38E8);
        brf_800CC5E4(work, &base[7], &base[9]);
        break;
    case 10:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[8] = 12;
            work->poly_flags[9] = 12;
            work->poly_flags[10] = 8;
            work->poly_flags[11] = 10;
            for (i = 12; i < 20; i++)
            {
                work->poly_flags[i] = 2;
            }
        }
        brf_800CADD4(work, &base[8], 8);
        brf_800CF4E0(work, 1, 0x258, 0, 0x55, 0x190, 3, &brf_dword_800C38E8);
        brf_800CC5E4(work, &base[8], &base[9]);
        break;
    case 11:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[8] = 12;
            work->poly_flags[9] = 12;
            work->poly_flags[10] = 8;
            work->field_AD30 = 0;
            work->poly_flags[11] = 10;
            for (i = 12; i < 20; i++)
            {
                work->poly_flags[i] = 2;
            }
        }
        brf_800CADD4(work, &base[8], 8);
        brf_800D5DDC(work);
        brf_800CF4E0(work, 1, 0x258, 0, 0x55, 0x190, 3, &brf_dword_800C38E8);
        brf_800CC5E4(work, &base[8], &base[9]);
        break;
    case 12:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[8] = 12;
            work->poly_flags[9] = 12;
        }
        brf_800CADD4(work, &base[8], 8);
        brf_800CF4E0(work, 1, 0x258, 0, 0x55, 0x190, 3, &brf_dword_800C38E8);
        brf_800CC5E4(work, &base[8], &base[9]);
        break;
    case 13:
        if (work->scene_changed != 0)
        {
            brf_800CC28C(work);
            setRGB0(&base[0], 0x80, 0x80, 0x80);
            setRGB0(&base[1], 0x80, 0x80, 0x80);
            setRGB0(&base[2], 0x80, 0x80, 0x80);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CBB68(work, &base[1], 1);
        brf_800CCBD4(work, &base[0]);
        break;
    case 14:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 10;
            work->field_AD34 = 0;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CBDC8(work, &base[1]);
        brf_800CCBD4(work, &base[0]);
        break;
    case 15:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CBB68(work, &base[1], 2);
        brf_800CCBD4(work, &base[0]);
        break;
    case 16:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 10;
            work->field_AD30 = 0;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
        }
        brf_800CBF48(work, &base[1]);
        brf_800CADD4(work, &base[2], 7);
        brf_800CCBD4(work, &base[0]);
        break;
    case -1:
    case 17:
        brf_800CF5A8(work);
        break;
    }
}
const char brf_dword_800E2170[4] = "";
extern int brf_dword_800C390C;

void brf_800D674C(Work *work)
{
    POLY_FT4 *base = work->polys;

    switch (work->scene)
    {
    case 1:
        if (work->scene_changed != 0)
        {
            GM_StreamPlayStart();
            brf_800CC150(work);
            brf_800CC190(work);
            work->view_mode = 0;
            work->move_dir = 0;
            work->move_state = 0;
            work->view[0].x = 0;
            work->view[0].y = 0x1E;
            work->view[0].scale = 0xF0;
            work->view[1].x = 0;
            work->view[1].y = 0x1E;
            work->view[1].scale = 0xF0;
            work->view[2].x = 0;
            work->view[2].y = 0x1E;
            work->view[2].scale = 0xF0;
            brf_800CF4A0(work, 0, 0x1E, 0xC8, 0xF0, 6, &brf_dword_800C390C);
            work->poly_flags[0] = 12;
            work->poly_flags[1] = 12;
            work->poly_flags[2] = 8;
            work->poly_flags[3] = 8;
            work->poly_flags[4] = 10;
            work->poly_flags[5] = 10;
        }
        if (work->view_mode == 0)
        {
            brf_800CF430(work);
            brf_800CADD4(work, &base[4], 4);
            brf_800CC5E4(work, &base[0], &base[1]);
        }
        else
        {
            brf_800CECE4(work);
        }
        break;
    case 2:
    case -1:
        brf_800CF5A8(work);
        break;
    case 0:
        break;
    }
}
void brf_800D68D0(Work *work)
{
    POLY_FT4 *base = work->polys;
    int v = work->field_AD30;

    if (v < 0x11)
    {
        int c;
        v <<= 3;
        c = 0x80 - v;
        setRGB0(&base[0], c, c, c);
        setRGB0(&base[1], c, c, c);
        setRGB0(&base[2], c, c, c);
        setRGB0(&base[3], v, v, v);
    }
    work->field_AD30++;
}
void brf_800D693C(Work *work)
{
    POLY_FT4 *base = work->polys;
    int v, w;

    if (work->field_AD30 < 0x11)
    {
        v = work->field_AD30 * 8;
        w = 0x80 - v;
        setRGB0(&base[3], w, w, w);
        setRGB0(&base[4], v, v, v);
        setRGB0(&base[5], v, v, v);
        setRGB0(&base[6], v, v, v);
    }
    work->field_AD30++;
}
void brf_800D69A8(Work *work)
{
    POLY_FT4 *base = work->polys;
    DG_TEX *g;

    switch (work->scene)
    {
    case 1:
        if (work->scene_changed != 0)
        {
            GM_StreamPlayStart();
            brf_800CC150(work);
            brf_800CC28C(work);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CBB68(work, &base[1], 2);
        brf_800CCBD4(work, &base[0]);
        break;
    case 2:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 10;
            work->field_AD34 = 0;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
        }
        brf_800CBD5C(work, &base[1]);
        brf_800CCBD4(work, &base[0]);
        break;
    case 3:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CBB68(work, &base[1], 1);
        brf_800CCBD4(work, &base[0]);
        break;
    case 5:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[3] = 10;
            work->poly_flags[4] = 10;
            work->field_AD30 = 0;
            work->poly_flags[5] = 8;
            work->poly_flags[6] = 8;
        }
        brf_800D693C(work);
        brf_800CCBD4(work, &base[4]);
        break;
    case 7:
        if (work->scene_changed != 0)
        {
            brf_800CC388(work);
            work->poly_flags[8] = 10;
            work->poly_flags[9] = 10;
        }
        brf_800CC5E4(work, &base[7], &base[8]);
        break;
    case 8:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->field_AD30 = 0;
            work->poly_flags[7] = 10;
            work->poly_flags[8] = 10;
            work->poly_flags[9] = 10;
        }
        brf_800CD8B8(work, 16, 9, 7);
        brf_800CC5E4(work, &base[7], &base[8]);
        break;
    case 10:
        if (work->scene_changed != 0)
        {
            brf_800CC28C(work);
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E1D28));
            BRF_SET_UV(&base[1], g);
            setRGB0(&base[0], 0x80, 0x80, 0x80);
            setRGB0(&base[1], 0x80, 0x80, 0x80);
            setRGB0(&base[2], 0x80, 0x80, 0x80);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CBB68(work, &base[1], 2);
        brf_800CCBD4(work, &base[0]);
        break;
    case 11:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 10;
            work->field_AD34 = 0;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
        }
        brf_800CBD5C(work, &base[1]);
        brf_800CCBD4(work, &base[0]);
        break;
    case 12:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
        }
        brf_800CADD4(work, &base[2], 7);
        brf_800CBB68(work, &base[1], 1);
        brf_800CCBD4(work, &base[0]);
        break;
    case 4:
    case 13:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[0] = 10;
            work->field_AD30 = 0;
            work->poly_flags[1] = 8;
            work->poly_flags[2] = 8;
            work->poly_flags[3] = 8;
        }
        brf_800D68D0(work);
        brf_800CCBD4(work, &base[0]);
        break;
    case 14:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[3] = 10;
            work->poly_flags[4] = 10;
            work->field_AD30 = 0;
            work->poly_flags[5] = 8;
            work->poly_flags[6] = 8;
        }
        brf_800D693C(work);
        brf_800CCBD4(work, &base[4]);
        break;
    case 6:
    case 15:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[4] = 10;
            work->poly_flags[5] = 8;
            work->poly_flags[6] = 8;
        }
        brf_800CADD4(work, &base[6], 6);
        brf_800CCBD4(work, &base[4]);
        break;
    case 16:
        if (work->scene_changed != 0)
        {
            brf_800CC388(work);
            setRGB0(&base[9], 0x80, 0x80, 0x80);
            work->poly_flags[8] = 10;
            work->poly_flags[9] = 10;
        }
        brf_800CC5E4(work, &base[8], &base[9]);
        break;
    case 17:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->field_AD30 = 0;
            work->poly_flags[7] = 10;
            work->poly_flags[8] = 10;
            work->poly_flags[9] = 10;
        }
        brf_800CD8B8(work, 16, 9, 7);
        brf_800CC5E4(work, &base[8], &base[9]);
        break;
    case 9:
    case 18:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[7] = 10;
            work->poly_flags[8] = 10;
        }
        brf_800CADD4(work, &base[7], 8);
        brf_800CC5E4(work, &base[7], &base[8]);
        break;
    case -1:
    case 19:
        brf_800CF5A8(work);
        break;
    }
}
const char brf_dword_800E21C8[12] = "a_back_u";
const char brf_dword_800E21D4[8] = "a_naomi";
const char brf_dword_800E21DC[8] = "\xa5\xca\xa5\xaa\xa5\xdf"; /* "ナオミ" (Naomi) */
void brf_800D6F98(Work *work)
{
    POLY_FT4 *base = work->polys;
    int xl, xr;
    int t;

    if (work->field_AD34 < 0xC9)
    {
        t = work->field_AD34 * 3;
        xr = t - 0x28a;
        xl = t - 0x388;
    }
    else
    {
        xr = -0x32;
        xl = -0x130;
    }
    base[8].y0 = -0x96;
    base[8].y1 = -0x96;
    base[8].y2 = 0x69;
    base[8].y3 = 0x69;
    base[8].x0 = xl;
    base[8].x1 = xr;
    base[8].x2 = xl;
    base[8].x3 = xr;
    switch (work->field_AD34)
    {
    case 0x88:
        GM_SeSet2(0xe0, 0x30, 0xb1);
        break;
    case 0xA8:
        GM_SeSet2(0xe0, 0x3f, 0xb2);
        break;
    case 0xC8:
        GM_SeSet2(0xeb, 0x3f, 0xb1);
        break;
    }
    work->field_AD34++;
}
extern int brf_dword_800C3954, brf_dword_800C3978;

void brf_800D70A4(Work *work)
{
    POLY_FT4 *base = work->polys;
    DG_TEX *g;

    switch (work->scene)
    {
    case 1:
        if (work->scene_changed != 0)
        {
            GM_StreamPlayStart();
            brf_800CC150(work);
            brf_800CC388(work);
            brf_800CF4A0(work, 0x32, 0x5A, 0x12C, 0x1C2, 3, &brf_dword_800C3954);
            work->poly_flags[1] = 10;
            work->poly_flags[2] = 10;
        }
        brf_800CADD4(work, &base[2], 9);
        brf_800CC5E4(work, &base[1], &base[2]);
        break;
    case 2:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->field_AD30 = 0;
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 10;
            work->poly_flags[2] = 10;
        }
        brf_800CD8B8(work, 16, 2, 0);
        brf_800CC5E4(work, &base[1], &base[2]);
        break;
    case 3:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            brf_800CAC7C(work, GV_StrCode(brf_dword_800E21C8));
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E21C8));
            BRF_SET_UV(&base[6], g);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 10;
        }
        brf_800CADD4(work, &base[0], 8);
        brf_800CC5E4(work, &base[0], &base[1]);
        break;
    case 4:
        if (work->scene_changed != 0)
        {
            brf_800CC190(work);
            brf_800CF4A0(work, 0x28, 0x5A, 0x12C, 0x2EE, 5, &brf_dword_800C3978);
            work->field_AD34 = 0;
            brf_800CAC7C(work, GV_StrCode(brf_dword_800E21D4));
            g = brf_800CABF4(work, GV_StrCode(brf_dword_800E21D4));
            BRF_SET_UV(&base[8], g);
            setRGB0(&base[8], 0x80, 0xC0, 0xC0);
            work->poly_flags[3] = 10;
            work->poly_flags[4] = 10;
            work->poly_flags[6] = 12;
            work->poly_flags[7] = 12;
            work->poly_flags[8] = 8;
        }
        brf_800CADD4(work, &base[3], 4);
        brf_800CC5E4(work, &base[6], &base[7]);
        brf_800D6F98(work);
        break;
    case 5:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[3] = 10;
            work->poly_flags[4] = 10;
            work->poly_flags[5] = 10;
            work->poly_flags[6] = 12;
            work->poly_flags[7] = 12;
            work->field_AD30 = 0;
            work->poly_flags[8] = 8;
        }
        brf_800CD8B8(work, 16, 3, 5);
        brf_800CC5E4(work, &base[6], &base[7]);
        break;
    case 6:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[4] = 10;
            work->poly_flags[5] = 10;
            work->poly_flags[6] = 12;
            work->poly_flags[7] = 12;
            work->poly_flags[8] = 8;
        }
        brf_800CADD4(work, &base[5], 3);
        brf_800CC5E4(work, &base[6], &base[7]);
        brf_800CDDD4(work, GV_StrCode(brf_dword_800E21DC), 8);
        break;
    case 7:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[3] = 10;
            work->poly_flags[4] = 10;
            work->poly_flags[5] = 10;
            work->poly_flags[6] = 12;
            work->poly_flags[7] = 12;
            work->field_AD30 = 0;
            work->poly_flags[8] = 8;
        }
        brf_800CD8B8(work, 16, 5, 3);
        brf_800CC5E4(work, &base[6], &base[7]);
        break;
    case 8:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->poly_flags[3] = 10;
            work->poly_flags[4] = 10;
            work->poly_flags[6] = 12;
            work->poly_flags[7] = 12;
            work->poly_flags[8] = 8;
        }
        brf_800CADD4(work, &base[3], 4);
        brf_800CC5E4(work, &base[6], &base[7]);
        break;
    case -1:
    case 9:
        brf_800CF5A8(work);
        break;
    }
}
const char brf_dword_800E2210[4] = "";
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D75F0.s")
extern int brf_dword_800C39B4;
void brf_800D75F0(Work *work);

void brf_800D8060(Work *work)
{
    POLY_FT4 *base = work->polys;

    switch (work->scene)
    {
    case 1:
        if (work->scene_changed != 0)
        {
            GM_StreamPlayStart();
            brf_800CC150(work);
            brf_800CC28C(work);
            brf_800CF4A0(work, 0, 0, 0xFA, 0x190, 2, &brf_dword_800C39B4);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 10;
        }
        brf_800CADD4(work, &base[1], 5);
        brf_800CBB68(work, &base[0], 0);
        brf_800CC5E4(work, &base[0], &base[1]);
        break;
    case 2:
        if (work->scene_changed != 0)
        {
            brf_800CC480(work);
            work->field_AD30 = 0x23F;
            work->field_AD38 = 0;
            work->poly_flags[2] = 12;
        }
        brf_800D75F0(work);
        break;
    case 3:
        if (work->scene_changed != 0)
        {
            brf_800CC28C(work);
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 10;
        }
        brf_800CADD4(work, &base[1], 5);
        brf_800CBB68(work, &base[0], 0);
        brf_800CC5E4(work, &base[0], &base[1]);
        break;
    case 4:
        if (work->scene_changed != 0)
        {
            brf_800CC560(work);
            work->field_AD30 = 0;
            work->poly_flags[0] = 10;
            work->poly_flags[1] = 10;
        }
        brf_800CADD4(work, &base[1], 5);
        brf_800CBE34(work, &base[0]);
        brf_800CC5E4(work, &base[0], &base[1]);
        break;
    case -1:
    case 5:
        brf_800CF5A8(work);
        break;
    }
}
const char brf_dword_800E2230[12] = "c_photo_4";
const char brf_dword_800E223C[12] = "c_photo_5";
const char brf_dword_800E2248[12] = "c_photo_6";
const char brf_dword_800E2254[16] = "b_face_wo";
const int brf_dword_800E2264 = 0x800DA028;
const int brf_dword_800E2268 = 0x800DA030;
const int brf_dword_800E226C = 0x800D9450;
const int brf_dword_800E2270 = 0x800D94B4;
const int brf_dword_800E2274 = 0x800D957C;
const int brf_dword_800E2278 = 0x800D963C;
const int brf_dword_800E227C = 0x800D96B8;
const int brf_dword_800E2280 = 0x800D9740;
const int brf_dword_800E2284 = 0x800D983C;
const int brf_dword_800E2288 = 0x800D988C;
const int brf_dword_800E228C = 0x800D98D0;
const int brf_dword_800E2290 = 0x800D99A0;
const int brf_dword_800E2294 = 0x800D9A70;
const int brf_dword_800E2298 = 0x800D9B58;
const int brf_dword_800E229C = 0x800D9C04;
const int brf_dword_800E22A0 = 0x800D9CE0;
const int brf_dword_800E22A4 = 0x800D9D1C;
const int brf_dword_800E22A8 = 0x800D9DE0;
const int brf_dword_800E22AC = 0x800D9E2C;
const int brf_dword_800E22B0 = 0x800D9EEC;
const int brf_dword_800E22B4 = 0x800D9FBC;
const int brf_dword_800E22B8 = 0x800DA028;
const char brf_dword_800E22BC[8] = "b_face";
const char brf_dword_800E22C4[8] = "c_inj_u";
const char brf_dword_800E22CC[8] = "c_inj_d";
const char brf_dword_800E22D4[20] = "c_inj_naomi_open_u";
const char brf_dword_800E22E8[20] = "c_inj_naomi_on_u";
const char brf_dword_800E22FC[20] = "c_inj_naomi_half_u";
const char brf_dword_800E2310[20] = "c_inj_naomi_close_u";
const char brf_dword_800E2324[16] = "b_eye_r_down";
const char brf_dword_800E2334[12] = "c_inj_on_u";
const char brf_dword_800E2340[4] = "map";
const int brf_dword_800E2344 = 0x800DCA84;
const int brf_dword_800E2348 = 0x800DCA8C;
const int brf_dword_800E234C = 0x800DBAD8;
const int brf_dword_800E2350 = 0x800DBB70;
const int brf_dword_800E2354 = 0x800DBBEC;
const int brf_dword_800E2358 = 0x800DBC68;
const int brf_dword_800E235C = 0x800DBE28;
const int brf_dword_800E2360 = 0x800DBD3C;
const int brf_dword_800E2364 = 0x800DBE28;
const int brf_dword_800E2368 = 0x800DBE84;
const int brf_dword_800E236C = 0x800DBF44;
const int brf_dword_800E2370 = 0x800DC134;
const int brf_dword_800E2374 = 0x800DC234;
const int brf_dword_800E2378 = 0x800DC338;
const int brf_dword_800E237C = 0x800DC37C;
const int brf_dword_800E2380 = 0x800DC46C;
const int brf_dword_800E2384 = 0x800DC4FC;
const int brf_dword_800E2388 = 0x800DC5C4;
const int brf_dword_800E238C = 0x800DC62C;
const int brf_dword_800E2390 = 0x800DC680;
const int brf_dword_800E2394 = 0x800DC75C;
const int brf_dword_800E2398 = 0x800DC7B0;
const int brf_dword_800E239C = 0x800DC89C;
const int brf_dword_800E23A0 = 0x800DC8E8;
const int brf_dword_800E23A4 = 0x800DC9A8;
const int brf_dword_800E23A8 = 0x800DCA84;
const int brf_dword_800E23AC = 0x800DD620;
const int brf_dword_800E23B0 = 0x800DD628;
const int brf_dword_800E23B4 = 0x800DD014;
const int brf_dword_800E23B8 = 0x800DD0A4;
const int brf_dword_800E23BC = 0x800DD110;
const int brf_dword_800E23C0 = 0x800DD170;
const int brf_dword_800E23C4 = 0x800DD1CC;
const int brf_dword_800E23C8 = 0x800DD27C;
const int brf_dword_800E23CC = 0x800DD320;
const int brf_dword_800E23D0 = 0x800DD450;
const int brf_dword_800E23D4 = 0x800DD4C4;
const int brf_dword_800E23D8 = 0x800DD538;
const int brf_dword_800E23DC = 0x800DD59C;
const int brf_dword_800E23E0 = 0x800DD620;
const char brf_dword_800E23E4[36] = "Memory for Texture Free Finish!\n";
const char brf_dword_800E2408[12] = "colorbar";
const char brf_dword_800E2414[12] = "scanline";
const char brf_dword_800E2420[8] = "play";
const char brf_dword_800E2428[8] = "camera";
const char brf_dword_800E2430[4] = "x";
const char brf_dword_800E2434[4] = "dot";
const char brf_dword_800E2438[4] = "y";
const char brf_dword_800E243C[4] = "z";
const char brf_dword_800E2440[8] = "b_line1";
const char brf_dword_800E2448[12] = "a_back_d";
const char brf_dword_800E2454[16] = "b_face_angry_u";
const char brf_dword_800E2464[24] = "liquid_simon_waku";
const int brf_dword_800E247C = 0x800DEDBC;
const int brf_dword_800E2480 = 0x800DEDDC;
const int brf_dword_800E2484 = 0x800DEE04;
const int brf_dword_800E2488 = 0x800DEE34;
const int brf_dword_800E248C = 0x800DF000;
const int brf_dword_800E2490 = 0x800DF1CC;
const int brf_dword_800E2494 = 0x800DF404;
const int brf_dword_800E2498 = 0x800DF490;
const int brf_dword_800E249C = 0x800DF980;
void brf_800D8274(Work *work)
{
    int v = work->field_AD3C;
    POLY_FT4 *base = work->polys;

    if (v < 0x258)
    {
        if ((v & 3) == 0)
        {
            base[4].x0--;
            base[4].x1--;
            base[4].x2--;
            base[4].x3--;
        }
        if (work->field_AD3C % 3 == 0)
        {
            base[5].x0--;
            base[5].x1--;
            base[5].x2--;
            base[5].x3--;
        }
    }
    else if (v == 0x258)
    {
        work->field_ADB8 = 0;
        work->field_ADBC = 1;
    }
    else if (v < 0x320)
    {
    }
    else if (v < 0x578)
    {
        if ((v & 3) == 0)
        {
            base[4].x0++;
            base[4].x1++;
            base[4].x2++;
            base[4].x3++;
        }
        if (work->field_AD3C % 3 == 0)
        {
            base[5].x0++;
            base[5].x1++;
            base[5].x2++;
            base[5].x3++;
        }
    }
    else if (v == 0x578)
    {
        work->field_ADB8 = 0;
        work->field_ADBC = 1;
    }
    else if (v == 0x640)
    {
        work->field_AD3C = 0;
    }

    work->field_AD3C++;
}
void brf_800D8420(Work *work)
{
    POLY_FT4 *base = work->polys;
    int v = work->field_AD38;

    if (v < 0x21)
    {
        int c = v << 2;
        setRGB0(&base[8], c, c, c);
        setRGB0(&base[9], c, c, c);
        setRGB0(&base[10], c, c, c);
        setRGB0(&base[11], c, c, c);
        setRGB0(&base[12], c, c, c);
        setRGB0(&base[13], c, c, c);
    }
    work->field_AD38++;
}
void brf_800D849C(Work *work)
{
    POLY_FT4 *base = work->polys;
    int v = work->field_AD38;

    if (v < 0x21)
    {
        int c = 0x80 - (v << 2);
        int i;
        for (i = 8; i < 14; i++)
        {
            setRGB0(&base[i], c, c, c);
        }
        for (i = 16; i < 28; i++)
        {
            setRGB0(&base[i], c, c, c);
            work->poly_flags[i] = 2;
        }
    }
    work->field_AD38++;
}
void brf_800D853C(Work *work)
{
    POLY_FT4 *base = work->polys;
    int v = work->field_AD30;

    if (v < 0x11)
    {
        int c;
        v <<= 3;
        c = 0x80 - v;
        setRGB0(&base[0], c, c, c);
        setRGB0(&base[1], c, c, c);
        setRGB0(&base[2], c, c, c);
        setRGB0(&base[3], v, v, v);
    }
    work->field_AD30++;
}
void brf_800D85A8(Work *work)
{
    POLY_FT4 *base = work->polys;
    int v = work->field_AD30;

    if (v < 0x11)
    {
        int v8 = v << 3;
        int c = 0x80 - v8;
        setRGB0(&base[0], v8, v8, v8);
        setRGB0(&base[1], v8, v8, v8);
        setRGB0(&base[2], v8, v8, v8);
        setRGB0(&base[3], c, c, c);
    }
    work->field_AD30++;
}
void brf_800D8614(Work *work)
{
    POLY_FT4 *base = work->polys;
    int v = work->field_AD30;

    if (v < 0xD)
    {
        int q = (v << 7) / 12;
        int c = 0x80 - q;
        setRGB0(&base[14], c, c, c);
        setRGB0(&base[15], c, c, c);
        setRGB0(&base[7], q, q, q);
    }
    work->field_AD30++;
}
void brf_800D8690(Work *work)
{
    int n = work->field_AD38;
    int i;

    for (i = 0; i < n; i++)
    {
        work->poly_flags[i + 0x10] = 2;
        if (work->glyph_flags[i + 0x10] != 0)
        {
            GM_SeSet2(0, 0x30, 0xB6);
        }
    }
}
void brf_800D872C(Work *work, int a1, int a2, int a3)
{
    int diff = work->field_AD38 - a1;
    int i;

    for (i = 0; i < 0x29C; i++)
    {
        work->poly_flags[i + 0x10] = 0;
    }

    for (i = 0; i < 0xC; i++)
    {
        work->poly_flags[i + 0x10] = 2;
    }

    for (i = a2; i < a3; i++)
    {
        work->poly_flags[i] = 2;
    }

    for (i = 0; i < diff; i++)
    {
        work->poly_flags[i + a3] = 2;
        if (work->glyph_flags[i + a3] != 0)
        {
            GM_SeSet2(0, 0x30, 0xB6);
        }
    }
}
void brf_800D8858(Work *work, int a1, int a2)
{
    int i;

    for (i = 0; i < 0x29C; i++)
    {
        work->poly_flags[i + 0x10] = 0;
    }

    for (i = 0; i < 0xC; i++)
    {
        work->poly_flags[i + 0x10] = 2;
    }

    for (i = a1; i < a2; i++)
    {
        work->poly_flags[i] = 2;
        brf_800CD870(work, i);
    }
}
void brf_800D892C(Work *work)
{
    POLY_FT4 *base = work->polys;
    int i;

    for (i = 0; i < 0x29C; i++)
    {
        work->poly_flags[i + 0x10] = 0;
    }

    for (i = 0; i < 0xC; i++)
    {
        work->poly_flags[i + 0x10] = 2;
    }

    if (work->field_AD38 < 0x385)
    {
        for (i = 0x250; i < 0x2AC; i++)
        {
            work->poly_flags[i] = 2;
        }
    }
    else if (work->field_AD38 < 0x3A5)
    {
        int c = 0x80 - ((work->field_AD38 - 0x384) << 2);

        for (i = 0x250; i < 0x2AC; i++)
        {
            setRGB0(&base[i], c, c, c);
            work->poly_flags[i] = 2;
        }
    }
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D8A24.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D93F4.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DA04C.s")
void brf_800DA3A8(Work *work, POLY_FT4 *poly)
{
    int xl, xr, yt, yb;
    if (work->field_AD34 < 0x21)
    {
        int t = -(work->field_AD34 * 12);
        xl = t + 0x7f;
        yt = -0x11c;
        xr = t + 0x27b;
        yb = 0x64;
    }
    else if (work->field_AD34 < 0x31)
    {
        xl = -0x101;
        yt = -0x11c;
        xr = 0xfb;
        yb = 0x64;
    }
    else
    {
        int t = -((work->field_AD34 - 0x10) * 12);
        xl = t + 0x7f;
        yt = -0x11c;
        xr = t + 0x27b;
        yb = 0x64;
    }
    poly->x1 = xr;
    poly->x3 = xr;
    poly->x0 = xl;
    poly->y0 = yt;
    poly->y1 = yt;
    poly->x2 = xl;
    poly->y2 = yb;
    poly->y3 = yb;
    switch (work->field_AD34)
    {
    case 0x10:
        GM_SeSet2(0x19, 0x3f, 0xb4);
        break;
    case 0x20:
        GM_SeSet2(0, 0x3f, 0xb5);
        break;
    case 0x30:
        break;
    case 0x40:
        GM_SeSet2(0, 0x3f, 0xb4);
        break;
    case 0x50:
        GM_SeSet2(0xe6, 0x3f, 0xb5);
        break;
    }
    work->field_AD34++;
}
void brf_800DA4E8(Work *work, POLY_FT4 *poly)
{
    int xl, xr, yt, yb;
    int i, f;

    f = work->field_AD34;

    if (f < 0x30)
    {
        int t = -(f * 12);
        xl = t + 0x7f;
        yt = -0x11c;
        xr = t + 0x27b;
        yb = 0x64;
    }
    else if (f < 0x3D)
    {
        xl = -0x1b5;
        for (i = 0; i < work->field_AD34 - 0x30; i++)
        {
            int t = xl - 12;
            xl = t + i;
        }
        yt = -0x11c;
        xr = xl + 0x1fc;
        yb = 0x64;
    }
    else
    {
        xl = -0x203;
        yt = -0x11c;
        xr = -7;
        yb = 0x64;
    }
    poly->x1 = xr;
    poly->x3 = xr;
    poly->x0 = xl;
    poly->y0 = yt;
    poly->y1 = yt;
    poly->x2 = xl;
    poly->y2 = yb;
    poly->y3 = yb;
    switch (work->field_AD34)
    {
    case 0xC:
        GM_SeSet2(0x19, 0x3f, 0xb1);
        break;
    case 0x18:
        GM_SeSet2(0, 0x3f, 0xb2);
        break;
    case 0x24:
        GM_SeSet2(0xeb, 0x3f, 0xb1);
        break;
    }
    work->field_AD34++;
}
void brf_800DA638(Work *work, POLY_FT4 *poly)
{
    if (work->field_AD34 % 4 == 0)
    {
        poly->y0 += 12;
        poly->y1 += 12;
    }
    else if (work->field_AD34 % 4 == 1)
    {
        poly->y0 -= 12;
        poly->y1 -= 12;
    }
    else if (work->field_AD34 % 4 == 2)
    {
        poly->y0 -= 12;
        poly->y1 -= 12;
    }
    else if (work->field_AD34 % 4 == 3)
    {
        poly->y0 += 12;
        poly->y1 += 12;
    }
    work->field_AD34++;
}
void brf_800DA6E4(int a, POLY_FT4 *poly)
{
    poly->y0 += 12;
    poly->y1 += 12;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DA700.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DBA7C.s")
void brf_800DCAA8(Work *work)
{
    if (work->field_AD34 % 3 == 0)
    {
        POLY_FT4 *base = work->polys;
        int i;
        for (i = 0; i < 8; i++)
        {
            base[i].y0++;
            base[i].y1++;
            base[i].y2++;
            base[i].y3++;
        }
    }
    work->field_AD34++;
}
void brf_800DCB44(Work *work, POLY_FT4 *poly)
{
    int xl, xr;
    int t;

    if (work->field_AD34 < 0xB)
    {
        t = -(work->field_AD34 * 8);
        xl = t + 0x7f;
        xr = t + 0x27b;
        poly->y0 = -0x11c;
        poly->y1 = -0x11c;
        poly->x0 = xl;
        poly->x1 = xr;
        poly->x2 = xl;
        poly->y2 = 0x64;
        poly->x3 = xr;
        poly->y3 = 0x64;
    }
    else if (work->field_AD34 >= 0x3B)
    {
        if (work->field_AD34 < 0x91)
        {
            t = -((work->field_AD34 - 0x30) * 8);
            xl = t + 0x7f;
            xr = t + 0x27b;
            poly->y0 = -0x11c;
            poly->y1 = -0x11c;
            poly->x0 = xl;
            poly->x1 = xr;
            poly->x2 = xl;
            poly->y2 = 0x64;
            poly->x3 = xr;
            poly->y3 = 0x64;
        }
        else if (work->field_AD34 >= 0xF1)
        {
            if (work->field_AD34 < 0x121)
            {
                t = (work->field_AD34 - 0xF0) * 8;
                xr = t - 0x7f;
                xl = t - 0x27b;
                poly->y0 = -0x11c;
                poly->y1 = -0x11c;
                poly->x0 = xl;
                poly->x1 = xr;
                poly->x2 = xl;
                poly->y2 = 0x64;
                poly->x3 = xr;
                poly->y3 = 0x64;
            }
            else if (work->field_AD34 >= 0x151)
            {
                if (work->field_AD34 < 0x181)
                {
                    t = (work->field_AD34 - 0x120) * 8;
                    xr = t - 0x7f;
                    xl = t - 0x27b;
                    poly->y0 = -0x11c;
                    poly->y1 = -0x11c;
                    poly->x0 = xl;
                    poly->x1 = xr;
                    poly->x2 = xl;
                    poly->y2 = 0x64;
                    poly->x3 = xr;
                    poly->y3 = 0x64;
                }
            }
        }
    }
    switch (work->field_AD34)
    {
    case 0xA:
        GM_SeSet2(0x1f, 0x3f, 0xb4);
        break;
    case 0x3A:
        GM_SeSet2(0x1f, 0x3f, 0xb5);
        break;
    case 0x58:
        GM_SeSet2(0xa, 0x3f, 0xb4);
        break;
    case 0x76:
        GM_SeSet2(0xf5, 0x3f, 0xb5);
        break;
    case 0x90:
        GM_SeSet2(0xe0, 0x3f, 0xb4);
        break;
    case 0xF0:
        GM_SeSet2(0xe0, 0x3f, 0xbf);
        break;
    case 0x108:
        GM_SeSet2(0xf5, 0x3f, 0xb4);
        break;
    case 0x120:
        GM_SeSet2(0, 0x3f, 0xb5);
        break;
    case 0x150:
        GM_SeSet2(0, 0x3f, 0xbf);
        break;
    case 0x168:
        GM_SeSet2(0xa, 0x3f, 0xb5);
        break;
    case 0x180:
        GM_SeSet2(0x1f, 0x3f, 0xb4);
        break;
    }
    work->field_AD34++;
}
void brf_800DCD70(Work *work, POLY_FT4 *poly)
{
    int c;
    int k;
    int x0, x1;

    c = work->field_AD34;
    if (c < 0x47)
    {
        k = -(c * 8);
        x0 = k + 0x7F;
        x1 = k + 0x27B;
    }
    else if (c < 0x81)
    {
        goto skip;
    }
    else if (c < 0xA1)
    {
        k = -((c - 0x3A) * 8);
        x0 = k + 0x7F;
        x1 = k + 0x27B;
    }
    else
    {
        goto skip;
    }
    setXY4(poly, x0, -0x11C, x1, -0x11C, x0, 0x64, x1, 0x64);

skip:
    switch (work->field_AD34)
    {
    case 0x00:
        GM_SeSet2(0x1F, 0x3F, 0xB4);
        break;
    case 0x19:
        GM_SeSet2(0x0A, 0x3F, 0xB5);
        break;
    case 0x32:
        GM_SeSet2(0xF5, 0x3F, 0xB4);
        break;
    case 0x46:
        GM_SeSet2(0xE6, 0x3F, 0xB5);
        break;
    case 0x80:
        GM_SeSet2(0xE6, 0x3F, 0xB4);
        break;
    case 0xA0:
        GM_SeSet2(0xE0, 0x3F, 0xB5);
        break;
    }
    work->field_AD34++;
}
void brf_800DCED4(Work *work, POLY_FT4 *poly)
{
    int xl, xr;
    int t;

    if (work->field_AD34 >= 0x29)
    {
        if (work->field_AD34 < 0x3D)
        {
            t = (work->field_AD34 - 0x28) * 8;
            xl = t - 0x27b;
            xr = t - 0x7f;
            setXY4(poly, xl, -0x11c, xr, -0x11c, xl, 0x64, xr, 0x64);
        }
    }
    switch (work->field_AD34)
    {
    case 0x28:
        GM_SeSet2(0xe0, 0x3f, 0xb4);
        break;
    case 0x3C:
        GM_SeSet2(0xeb, 0x3f, 0xb5);
        break;
    }
    work->field_AD34++;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DCFB4.s")
void brf_800DD648(Work *work)
{
    switch (work->scene)
    {
    case 0:
        break;
    case 1:
        if (work->scene_changed != 0)
        {
            GM_StreamPlayStart();
            work->scene_changed = 0;
        }
        break;
    case 2:
    case -1:
        work->prim_24_flags[0] = 0;
        brf_800CF5A8(work);
        break;
    }
}
extern int brf_dword_800C4CB0;

void brf_800DD6DC(Work *work)
{
    work->time++;
    if (work->time != work->key_time)
    {
        return;
    }
    if (work->scene == -1)
    {
        return;
    }

    work->scene_changed = 1;
    work->scene = work->key_scene;
    work->key_time = ((BrfKeyframe **)&brf_dword_800C4CB0)[work->index][work->key_index].field_0;
    work->key_scene = ((BrfKeyframe **)&brf_dword_800C4CB0)[work->index][work->key_index].field_2;
    work->key_index++;
}
void brf_800DD77C(Work *work)
{
    int press = work->pad->press;

    if (work->no_skip != 1 && (press & PAD_B) && work->time >= 0x33)
    {
        work->scene = -1;
        work->scene_changed = 1;
    }
}
void brf_800DD7C8(POLY_FT4 *p, int scale)
{
    p->r0 = p->r0 * scale / 128;
    p->g0 = p->g0 * scale / 128;
    p->b0 = p->b0 * scale / 128;
}
void brf_800DD830(Work *work)
{
    int       i;
    POLY_FT4 *src;
    POLY_FT4 *dst;
    POLY_F4  *src4;
    POLY_F4  *dst4;
    int       k;
    int       v;
    short    *tbl;

    src = work->prim_24->packs[GV_Clock];
    for (i = 0; i < 2; i++)
    {
        *(unsigned short *)src = work->prim_24_flags[i] << 8;
        src++;
    }

    src = work->sub_polys;
    dst = work->sub_prim->packs[GV_Clock];
    for (i = 0; i < 200; i++)
    {
        *dst = *src;
        *(unsigned short *)src = work->sub_flags[i] << 8;
        work->sub_flags[i] = 0;
        src++;
        dst++;
    }

    dst = work->main_prim->packs[GV_Clock];
    if (work->field_ADB8 < 5)
    {
        work->poly_buf = (POLY_FT4 *)(PACK_ADDR0 + 50 * 1024);
        src = (POLY_FT4 *)(PACK_ADDR0 + 50 * 1024);
    }
    else
    {
        src = work->polys;
    }
    for (i = 0; i < (tbl = (short *)&brf_dword_800C3508)[work->index]; i++) /* required for the match */
    {
        *dst = *src;
        k = work->time % 16;
        if (k >= 9)
        {
            k = 16 - k;
        }
        v = k * 2;
        brf_800DD7C8(dst, 128 - v);
        *(unsigned short *)dst = work->poly_flags[i] << 8;
        src++;
        dst++;
    }

    src4 = work->f4_polys;
    dst4 = work->f4_prim->packs[GV_Clock];
    for (i = 0; i < 5; i++)
    {
        *dst4 = *src4;
        *(unsigned short *)dst4 = work->f4_flags[i] << 8;
        src4++;
        dst4++;
    }

    src = work->small_polys;
    dst = work->small_prim->packs[GV_Clock];
    for (i = 0; i < 15; i++)
    {
        *dst = *src;
        *(unsigned short *)dst = work->small_flags[i] << 8;
        src++;
        dst++;
    }
}
extern const char brf_dword_800E23E4[];

void brf_800DDBC8(Work *work)
{
    int i;

    for (i = 0; i < work->n_images; i++)
    {
        GV_Free(work->images[i]);
    }
    printf((char *)brf_dword_800E23E4);
}

#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DDC40.s")
void brf_800DDC40(Work *work); // Act

void brf_800DDCA8(Work *work)
{
    GM_FreePrim(work->main_prim);
    GM_FreePrim(work->small_prim);
    GM_FreePrim(work->f4_prim);
    GM_FreePrim(work->prim_24);
    GM_FreePrim(work->sub_prim);
    brf_800DDBC8(work);
}
void brf_800DDCA8(Work *work); // Die

void brf_800DDD78(int a0, POLY_FT4 *poly, int x0, int y0, int x1, int y2, int abe)
{
    setPolyFT4(poly);
    setRGB0(poly, 0x80, 0x80, 0x80);
    poly->x0 = x0;
    poly->y0 = y0;
    poly->y1 = y0;
    poly->x2 = x0;
    poly->x1 = x1;
    poly->y2 = y2;
    poly->x3 = x1;
    poly->y3 = y2;
    SetSemiTrans(poly, abe);
}
void brf_800DDDE8(Work *work, POLY_FT4 *poly, int x0, int y0, int x1, int y2, int abe)
{
    setPolyFT4(poly);
    setRGB0(poly, 0xFF, 0xD0, 0xD0);
    poly->x0 = x0;
    poly->y0 = y0;
    poly->y1 = y0;
    poly->x2 = x0;
    poly->x1 = x1;
    poly->y2 = y2;
    poly->x3 = x1;
    poly->y3 = y2;
    SetSemiTrans(poly, abe);
}
void brf_800DDE5C(int prim, int tex_id, POLY_FT4 *poly, int x0, int y0, int x1, int y2, int abe, int orient, int use_dg)
{
    DG_TEX *tex;

    brf_800DDD78(prim, poly, x0, y0, x1, y2, abe);
    if (!use_dg)
    {
        tex = (DG_TEX *)brf_800CABF4(prim, tex_id);
    }
    else
    {
        tex = DG_GetTexture(tex_id);
    }

    switch (orient)
    {
    case 0:
        {
            int u = tex->off_x, w = tex->w, v = tex->off_y, h = tex->h;
            poly->u0 = u;
            poly->v0 = v;
            poly->u1 = u + w + 1;
            poly->v1 = v;
            poly->u2 = u;
            poly->v2 = v + h + 1;
            poly->u3 = u + w + 1;
            poly->v3 = v + h + 1;
        }
        break;
    case 1:
        {
            int u = tex->off_x, w = tex->w, v = tex->off_y, h = tex->h;
            poly->u0 = u;
            poly->v0 = v;
            poly->u1 = u + w + 1;
            poly->v1 = v;
            poly->u2 = u;
            poly->v2 = v + h;
            poly->u3 = u + w + 1;
            poly->v3 = v + h;
        }
        break;
    case 2:
        {
            int u = tex->off_x, w = tex->w, v = tex->off_y, h = tex->h;
            poly->u0 = u;
            poly->v0 = v;
            poly->u1 = u + w;
            poly->v1 = v;
            poly->u2 = u;
            poly->v2 = v + h + 1;
            poly->u3 = u + w;
            poly->v3 = v + h + 1;
        }
        break;
    default:
        return;
    }

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}
void brf_800DE004(int prim, int tex_id, POLY_FT4 *poly, int x0, int y0, int x1, int y2, int abe, int div)
{
    DG_TEX *tex;
    int     u, v, w, h;
    int     unused[2];

    (void)unused;
    brf_800DDD78(prim, poly, x0, y0, x1, y2, abe);
    tex = DG_GetTexture(tex_id);
    w = (tex->w + 1) / div;
    v = u = tex->off_y;
    h = tex->h + 1;
    u = tex->off_x;
    poly->v0 = v;
    poly->v1 = v;
    poly->v2 = v + h;
    poly->v3 = v + h;
    poly->u0 = u;
    poly->u2 = u;
    poly->u1 = u + w;
    poly->u3 = u + w;
    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}
void brf_800DE0F4(Work *work, unsigned char c, POLY_FT4 *poly, int x0, int y0, int x1, int y2, int abe, int slot)
{
    DG_TEX *tex;
    int     idx;
    int     u, v, w, h;
    int     u0, u1;

    idx = brf_800CD734(c);
    tex = brf_800CD7DC(work, c);
    if (c == ' ')
    {
        work->glyph_flags[slot] = 0;
    }
    else
    {
        work->glyph_flags[slot] = 1;
    }
    brf_800DDDE8(work, poly, x0, y0, x1, y2, abe);
    w = tex->w + 1;
    v = tex->off_y;
    h = tex->h + 1;
    u = tex->off_x;
    poly->v0 = v;
    poly->v1 = v;
    poly->v2 = v + h;
    poly->v3 = v + h;
    u0 = u + w * idx / 27;
    u1 = u + w * (idx + 1) / 27;
    poly->u0 = u0;
    poly->u1 = u1;
    poly->u2 = u0;
    poly->u3 = u1;
    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}
void brf_800DE270(int a0, POLY_F4 *poly, int x0, int y0, int x1, int y2, int abe, int gray)
{
    setPolyF4(poly);
    poly->x0 = x0;
    poly->y0 = y0;
    poly->y1 = y0;
    poly->x2 = x0;
    setRGB0(poly, gray, gray, gray);
    poly->x1 = x1;
    poly->y2 = y2;
    poly->x3 = x1;
    poly->y3 = y2;
    SetSemiTrans(poly, abe);
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DE2E0.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DECF8.s")

void brf_800DE2E0(Work *work);
void brf_800DECF8(Work *work, int a1);

int brf_800DFCF8(Work *work, int map, int n_textures, int *tex_ids, DG_TEX *textures, int index, int arg6,
                 int n_images, int *image_ids, DG_IMAGE **images) // GetResources
{
    work->n_textures = n_textures;
    work->tex_ids = tex_ids;
    work->pad = &GV_PadData[2];
    work->map = map;
    work->time = 0;
    work->scene_changed = 0;
    work->zoom_count = 0;
    work->field_ADB8 = 100;
    work->no_skip = 0;
    GM_CurrentMap = map;
    work->index = index;
    work->textures = textures;
    work->n_images = n_images;
    work->image_ids = image_ids;
    work->images = images;
    brf_800DE2E0(work);
    brf_800DECF8(work, index);
    return 0;
}

void *NewBriefingGraph(int map, int n_textures, int *tex_ids, DG_TEX *textures, int index, int arg5, int n_images,
                       int *image_ids, DG_IMAGE **images)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, brf_800DDC40, brf_800DDCA8, "b_graph.c");
        if (brf_800DFCF8(work, map, n_textures, tex_ids, textures, index, arg5, n_images, image_ids, images) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}
