#include "game/game.h"

typedef struct _DemocameUnk
{
    int     f0;
    int     f4;
    int     f8;
    SVECTOR fC;
    SVECTOR f14;
    int     f1C;
} DemocameUnk;

typedef int  (*DemocameFn1)(int, int, int);
typedef void (*DemocameFn2)(SVECTOR *, SVECTOR *, int);

typedef struct _Work
{
    GV_ACT       actor;
    SVECTOR      eye;
    SVECTOR      center;
    SVECTOR      rotate;
    int          track;
    int          type;
    SVECTOR     *field_40;
    SVECTOR     *field_44;
    SVECTOR     *field_48;
    int         *field_4C;
    SVECTOR      field_50;
    SVECTOR      field_58;
    SVECTOR      field_60;
    int          field_68;
    int          field_6C;
    int          field_70;
    int          field_74;
    DemocameFn1  field_78;
    DemocameFn2  field_7C;
    DemocameFn2  field_80;
    DemocameUnk *field_84;
    int          field_88;
    int          field_8C;
    int          field_90;
    char         pad1[0x18];
} Work;

extern GM_CAMERA        GM_Camera;
extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;

#define EXEC_LEVEL 6

void s19b_democame_800DB578(SVECTOR *in, SVECTOR *out, SVECTOR *angle, int *length);
void s19b_democame_800DB5C4(SVECTOR *out, SVECTOR *in, SVECTOR *angle, int *length);

void s19b_democame_800DB470(Work *work)
{
    switch (work->type)
    {
    case 0:
        break;
    case 1:
        s19b_democame_800DB578(&work->eye, &work->center, &work->rotate, &work->track);
        break;
    case 2:
        s19b_democame_800DB5C4(&work->eye, &work->center, &work->rotate, &work->track);
        break;
    }
}

void s19b_democame_800DB4E0(SVECTOR *from, SVECTOR *to, SVECTOR *out, int *length)
{
    SVECTOR diff;

    GV_SubVec3(to, from, &diff);
    *length = GV_VecLen3(&diff);

    out->vz = 0;
    out->vy = GV_VecDir2(&diff);
    out->vx = ratan2(-diff.vy, SquareRoot0(diff.vx * diff.vx + diff.vz * diff.vz));
}

void s19b_democame_800DB578(SVECTOR *in, SVECTOR *out, SVECTOR *angle, int *length)
{
    SVECTOR dir;

    GV_DirVec3(angle, *length, &dir);
    GV_AddVec3(in, &dir, out);
}

void s19b_democame_800DB5C4(SVECTOR *out, SVECTOR *in, SVECTOR *angle, int *length)
{
    SVECTOR dir;

    GV_DirVec3(angle, *length, &dir);
    GV_SubVec3(in, &dir, out);
}

int s19b_democame_800DB610(int from, int to, int interp)
{
    return GV_NearExp2(from, to);
}

int s19b_democame_800DB630(int from, int to, int interp)
{
    return GV_NearExp4(from, to);
}

int s19b_democame_800DB650(int from, int to, int interp)
{
    return GV_NearExp8(from, to);
}

int s19b_democame_800DB670(int from, int to, int interp)
{
    return GV_NearTime(from, to, interp);
}

void s19b_democame_800DB690(SVECTOR *from, SVECTOR *to, int interp)
{
    GV_NearExp2V((short *)from, (short *)to, 3);
}

void s19b_democame_800DB6B0(SVECTOR *from, SVECTOR *to, int interp)
{
    GV_NearExp4V((short *)from, (short *)to, 3);
}

void s19b_democame_800DB6D0(SVECTOR *from, SVECTOR *to, int interp)
{
    GV_NearExp8V((short *)from, (short *)to, 3);
}

void s19b_democame_800DB6F0(SVECTOR *from, SVECTOR *to, int interp)
{
    GV_NearTimeV((short *)from, (short *)to, interp, 3);
}

void s19b_democame_800DB710(SVECTOR *from, SVECTOR *to, int interp)
{
    GV_NearExp2PV((short *)from, (short *)to, 3);
}

void s19b_democame_800DB730(SVECTOR *from, SVECTOR *to, int interp)
{
    GV_NearExp4PV((short *)from, (short *)to, 3);
}

void s19b_democame_800DB750(SVECTOR *from, SVECTOR *to, int interp)
{
    GV_NearExp8PV((short *)from, (short *)to, 3);
}

void s19b_democame_800DB770(SVECTOR *from, SVECTOR *to, int interp)
{
    GV_NearTimePV((short *)from, (short *)to, interp, 3);
}

DemocameFn1 s19b_dword_800C3AE0[] = {
    s19b_democame_800DB610,
    s19b_democame_800DB630,
    s19b_democame_800DB650,
    s19b_democame_800DB670
};

DemocameFn2 s19b_dword_800C3AF0[4] = {
    s19b_democame_800DB690,
    s19b_democame_800DB6B0,
    s19b_democame_800DB6D0,
    s19b_democame_800DB6F0
};

DemocameFn2 s19b_dword_800C3B00[4] = {
    s19b_democame_800DB710,
    s19b_democame_800DB730,
    s19b_democame_800DB750,
    s19b_democame_800DB770
};

void s19b_democame_800DB790(Work *work, DemocameUnk *unk)
{
    int index;

    switch (unk->f8)
    {
    case 0:
        work->field_50 = unk->fC;
        work->field_58 = unk->f14;
        s19b_democame_800DB4E0(&work->field_50, &work->field_58, &work->field_60, &work->field_68);
        work->type = 0;
        break;

    case 1:
        work->field_50 = unk->fC;
        work->field_60.vx = unk->f14.vx;
        work->field_60.vy = unk->f14.vy;
        work->field_60.vz = 0;
        work->field_68 = unk->f14.vz;
        s19b_democame_800DB578(&work->field_50, &work->field_58, &work->field_60, &work->field_68);
        work->type = 1;
        break;

    case 2:
        work->field_58 = unk->fC;
        work->field_60.vx = unk->f14.vx;
        work->field_60.vy = unk->f14.vy;
        work->field_60.vz = 0;
        work->field_68 = unk->f14.vz;
        s19b_democame_800DB5C4(&work->field_50, &work->field_58, &work->field_60, &work->field_68);
        work->type = 2;
        break;
    }

    work->field_6C = unk->f0;
    work->field_70 = unk->f4;
    work->field_74 = unk->f1C;

    index = work->field_6C;
    work->field_78 = s19b_dword_800C3AE0[index];
    work->field_7C = s19b_dword_800C3AF0[index];
    work->field_80 = s19b_dword_800C3B00[index];
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_democame_800DB968.s")
void s19b_democame_800DB968(Work *);

void s19b_democame_800DBD38(void)
{
    /* do nothing */
}

void *NewDemoCamera(DemocameUnk *unk)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(work, s19b_democame_800DB968, s19b_democame_800DBD38, "democame.c");

        work->eye = gUnkCameraStruct2_800B7868.eye;
        work->center = gUnkCameraStruct2_800B7868.center;
        work->rotate = gUnkCameraStruct2_800B7868.rotate;
        work->track = gUnkCameraStruct2_800B7868.track;
        work->type = gUnkCameraStruct2_800B7868.type;

        s19b_democame_800DB470(work);
        s19b_democame_800DB790(work, unk);

        work->field_84 = unk + 1;
        work->field_8C = 1;
    }

    return work;
}
