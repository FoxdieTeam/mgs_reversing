#include "common.h"
#include "game/game.h"
#include "libdg/libdg.h"

typedef struct _Work
{
    GV_ACT          actor;          /* 0x000 */
    CONTROL         control;        /* 0x020 */
    OBJECT          field_9C;       /* 0x09C */
    OBJECT          field_180;      /* 0x180 */
    char            pad_264[0x728 - 0x264];
    short           field_728;      /* 0x728 */
    char            pad_72A[0x734 - 0x72A];
    short           field_734;      /* 0x734 */
    char            pad_736[0x748 - 0x736];
    short           field_748;      /* 0x748 */
    char            pad_74A[0x750 - 0x74A];
    short           field_750;      /* 0x750 */
    char            pad_752[0x954 - 0x752];
    void          (*field_954)(struct _Work *);  /* 0x954 */
    char            pad_958[0x95C - 0x958];
    int             field_95C;      /* 0x95C */
    char            pad_960[0x96C - 0x960];
    int             field_96C;      /* 0x96C */
    char            pad_970[0x974 - 0x970];
    int             field_974;      /* 0x974 */
    char            pad_978[0x9A4 - 0x978];
    int             field_9A4;      /* 0x9A4 */
    int             field_9A8;      /* 0x9A8 */
    char            pad_9AC[0xC00 - 0x9AC];
} Work;

extern int s03d_dword_800C3988;
extern int s03d_dword_800C3990;

extern void NewBlood(MATRIX *, int);

void s03d_800CBE2C(Work *work);
void s03d_800CBEF4(Work *work);
void s03d_800CC05C(Work *work);
void s03d_800CC374(Work *work);
void Zako_800CCA64(Work *work);

int Zako_800CB9E8(Work *work)
{
    int flags = work->field_974;

    if (flags & 1)
    {
        work->field_954 = s03d_800CC05C;
        work->field_95C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (flags & 4)
    {
        work->field_954 = s03d_800CBE2C;
        work->field_95C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (flags & 8)
    {
        work->field_954 = s03d_800CBEF4;
        work->field_95C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    return 0;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CBA60.s")
void Zako_800CBAEC(Work *work)
{
    int v = work->field_96C;

    work->field_728 = v;
    work->field_748 = v;
    if (v < 0)
    {
        work->field_750 = v * 3;
    }
    else
    {
        work->field_750 = v * 3 / 2;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CBB2C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CBC10.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CBE2C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CBEF4.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CC05C.s")
void Zako_800CC244(Work *work, int index, int count)
{
    MATRIX m;

    DG_SetPos(&work->field_9C.objs->objs[index].world);
    DG_MovePos((SVECTOR *)&s03d_dword_800C3988);
    DG_RotatePos((SVECTOR *)&s03d_dword_800C3990);
    ReadRotMatrix(&m);
    NewBlood(&m, count);
    work->control.step = DG_ZeroVector;
}

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CC2E8.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CC374.s")
void Zako_800CC430(Work *work)
{
    SVECTOR vec;

    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &vec);
    vec.vy = 0;
    work->field_9A4 = GV_VecDir2(&vec);
    work->field_9A8 = GV_VecLen3(&vec);
}
void Zako_800CC480(Work *work)
{
    Zako_800CC430(work);
    Zako_800CCA64(work);
    s03d_800CC374(work);
}
