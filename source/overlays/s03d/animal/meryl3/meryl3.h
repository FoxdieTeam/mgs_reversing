#ifndef _S03D_MERYL3_H
#define _S03D_MERYL3_H

#include "common.h"
#include "game/game.h"
#include "game/motion.h"
#include "libdg/libdg.h"

typedef struct _Meryl3Work
{
    GV_ACT          actor;          /* 0x000 */
    CONTROL         control;        /* 0x020 */
    OBJECT          body;           /* 0x09C */
    MOTION_CONTROL  m_ctrl;         /* 0x180 */
    MOTION_SEGMENT  m_segs1[17];    /* 0x1D0 */
    MOTION_SEGMENT  m_segs2[17];    /* 0x434 */
    SVECTOR         rots[16];       /* 0x698 */
    SVECTOR         adjust[16];     /* 0x718 */
    MATRIX          light[2];       /* 0x798 */
    char            pad_7D8[0x7DC - 0x7D8];
    OBJECT          weapon;         /* 0x7DC */
    int             lod;            /* 0x8C0 */
    DG_DEF         *models[2];      /* 0x8C4 */
    TARGET         *target;         /* 0x8CC */
    char            pad_8D0[0x920 - 0x8D0];
    int             field_920;      /* 0x920 */
    char            pad_924[0x954 - 0x924];
    void          (*field_954)(struct _Meryl3Work *, int);  /* 0x954 */
    int             field_958;      /* 0x958 */
    int             field_95C;      /* 0x95C */
    int             field_960;      /* 0x960 */
    int             field_964;      /* 0x964 */
    int             field_968;      /* 0x968 */
    int             field_96C;      /* 0x96C */
    char            pad_970[0x974 - 0x970];
    int             field_974;      /* 0x974 */
    int             field_978;      /* 0x978 */
    char            pad_97C[0x990 - 0x97C];
    int             field_990;      /* 0x990 */
    char            pad_994[0x9A4 - 0x994];
    int             field_9A4;      /* 0x9A4 */
    int             field_9A8;      /* 0x9A8 */
    char            pad_9AC[0x9B0 - 0x9AC];
    void           *shadow;         /* 0x9B0 */
    void           *glight;         /* 0x9B4 */
    char            pad_9B8[0xC00 - 0x9B8];
} Meryl3Work;

static inline void SetMode(Meryl3Work *work, void (*action)(struct _Meryl3Work *, int))
{
    work->field_954 = action;
    work->field_95C = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

#endif // _S03D_MERYL3_H
