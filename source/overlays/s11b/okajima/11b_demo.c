#include "bullet/blast.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "okajima/red_alrt.h"
#include "takabe/fadeio.h"

#define N_OBJECTS       16
#define N_SEGMENTS      40
#define N_PACKS         (N_OBJECTS * N_SEGMENTS)

typedef struct _Work
{
    /* 0x0000 */ GV_ACT   actor;
    /* 0x0020 */ int      name;
    /* 0x0024 */ int      map;
    /* 0x0028 */ DG_PRIM *prim;
    /* 0x002C */ SVECTOR  vertices[N_PACKS * 4];
    /* 0x502C */ int      trail_count[N_OBJECTS];
    /* 0x506C */ OBJECT   objects[N_OBJECTS];
    /* 0x5EAC */ MATRIX   light[2];
    /* 0x5EEC */ int      state[N_OBJECTS];
    /* 0x5F2C */ SVECTOR  pos[N_OBJECTS];
    /* 0x5FAC */ SVECTOR  speed[N_OBJECTS];
    /* 0x602C */ int      rot1[N_OBJECTS];
    /* 0x606C */ int      rot2[N_OBJECTS];
    /* 0x60AC */ int      shade[N_PACKS];
    /* 0x6AAC */ SVECTOR  start;
    /* 0x6AB4 */ SVECTOR  goal;
    /* 0x6ABC */ SVECTOR  eye_goal;
    /* 0x6AC4 */ SVECTOR  center_goal;
    /* 0x6ACC */ SVECTOR  eye;
    /* 0x6AD4 */ SVECTOR  center;
    /* 0x6ADC */ char     pad6ADC[8];
    /* 0x6AE4 */ int      mode;
    /* 0x6AE8 */ int      timer;
    /* 0x6AEC */ int      f6AEC;
    /* 0x6AF0 */ int      f6AF0;
    /* 0x6AF4 */ char     pad6AF4[8];
    /* 0x6AFC */ int      count;
    /* 0x6B00 */ int      proc_id;
    /* 0x6B04 */ int      vibration;
    /* 0x6B08 */ int      se_index;
} Work;

#define BODY_DATA   GV_StrCode("stn_fr")
#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

VECTOR body_scale = {4096, 4096, 4096};

void  NewAnime_8005E774(SVECTOR *pos);
void *NewBlastLine(int arg0, int arg1, int arg2, SVECTOR *arg3, SVECTOR *arg4);

#pragma INCLUDE_ASM("asm/overlays/s11b/s11b_800CAAEC.s")
#pragma INCLUDE_ASM("asm/overlays/s11b/s11b_800CAB84.s")
#pragma INCLUDE_ASM("asm/overlays/s11b/s11b_800CAC10.s")
#pragma INCLUDE_ASM("asm/overlays/s11b/s11b_800CACDC.s")
#pragma INCLUDE_ASM("asm/overlays/s11b/s11b_800CAD58.s")
#pragma INCLUDE_ASM("asm/overlays/s11b/s11b_800CAE40.s")
#pragma INCLUDE_ASM("asm/overlays/s11b/s11b_800CAED8.s")
#pragma INCLUDE_ASM("asm/overlays/s11b/s11b_800CAF34.s")
#pragma INCLUDE_ASM("asm/overlays/s11b/s11b_800CAF54.s")
#pragma INCLUDE_ASM("asm/overlays/s11b/s11b_800CB080.s")
#pragma INCLUDE_ASM("asm/overlays/s11b/s11b_800CBB18.s")
#pragma INCLUDE_ASM("asm/overlays/s11b/s11b_800CBBAC.s")
#pragma INCLUDE_ASM("asm/overlays/s11b/s11b_800CC144.s")

const char s11b_dword_800DB00C[] = "plasma";
const char s11b_dword_800DB014[] = "stn_fr";
const char s11b_dword_800DB01C[] = "11b_demo.c";
