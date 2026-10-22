#ifndef _OPEN_H
#define _OPEN_H

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "menu/menuman.h"

typedef struct _Unknown
{
    SPRT  sprt[2];
    SPRT  sprt2[2][4];
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
    DG_PRIM *prim[4];
    int      f30[22];
    int      f88[22];
    int      fE0[6];
    int      fF8[18];
    int      f140[9];
    int      f164;     /* main per-state frame counter; case 4/5 transitions trigger when f164 crosses thresholds */
    int      f168;
    int      f16C;
    int      f170;
    int      f174;
    int      f178;
    int      f17C;
    int      f180;
    int      f184;
    int      f188;
    POLY_FT4 f18C_polys[22];
    POLY_FT4 f4FC_polys[18];
    POLY_FT4 f7CC_polys[9];
    POLY_GT4 f934_polys[6];
    GV_PAD  *pad;
    int      fA70;
    int      fA74;     /* OpenAct state (drives the top-level switch) */
    int      fA78;     /* sub-state for case 7 (difficulty 0..5) */
    int      fA7C;
    int      fA80;
    int      fA84;
    int      fA88;
    int      fA8C;
    int      fA90;
    int      fA94;
    int      fA98;
    int      fA9C;
    int      fAA0;
    int      fAA4;
    CVECTOR  fAA8;
    u_char   fAAC;
    u_char   fAAD;
    u_char   fAAE;
    char     fAAF;
    CVECTOR  fAB0;
    CVECTOR  fAB4;
    int      fAB8;
    int      fABC;
    int      fAC0;
    int      fAC4;
    int      fAC8;
    int      fACC;
    int      end_proc;
    int      fAD4;
    int      fAD8;
    int      fADC;
    int      fAE0;
    int      fAE4;
    int      fAE8;
    int      fAEC;
    int      fAF0;
    int      fAF4;
    int      fAF8;
    int      fAFC;
    int      fB00;
    int      fB04;
    int      start_flag;
    int      fB0C;     /* set on every state transition; the new state's case re-runs its one-time init then clears this back to 0 */
    int      fB10;
    int      fB14;
    int      fB18;
    int      fB1C;
    int      save_flag;
    int      photo_flag;
    int      vr_flag;
    int      fB2C[4];
    int      fB3C;
    int      spe_rank;
    int      fB44;
    int      demo_rank;
    KCB      kcb[24];
    char     pad2[0x14];
    DR_TPAGE tpage[2];
    char     pad3[0x8];
    Unknown  unk[24];
    int      f2498;
    int      f249C;
    int      f24A0;
    int      f24A4;
    void    *mg_logo;
    int      f24AC;
    int      f24B0;
    int      f24B4;
    int      f24B8;
    int      f24BC;
    int      f24C0;
    int      f24C4;
    int      f24C8;
    int      f24CC;
    int      mem_flag;
    int      f24D4;
    int      f24D8;
    int      f24DC;
    int      f24E0;
    int      f24E4;
    int      f24E8;
    int      f24EC;
    int      f24F0;
    int      f24F4;
    int      sound_proc;
    int      clear_proc;
    int      f2500;
} Work;

#endif
