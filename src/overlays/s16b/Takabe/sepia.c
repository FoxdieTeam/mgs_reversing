#include "Takabe/goggle.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"

typedef struct _SepiaWork
{
    GV_ACT actor;
    void  *ptr;
} SepiaWork;

extern const char s16b_dword_800C5898[]; // = "sepia.c"

#define EXEC_LEVEL 7

#pragma INCLUDE_ASM("asm/overlays/s16b/s16b_800C4C60.s");

void s16b_800C4E70(SepiaWork *work)
{
    DG_ResetExtPaletteMakeFunc_800791E4();

    if (work->ptr)
    {
        GV_DelayedFree_80016254(work->ptr);
    }
}

#pragma INCLUDE_ASM("asm/overlays/s16b/s16b_800C4EAC.s");
#pragma INCLUDE_ASM("asm/overlays/s16b/s16b_800C4F9C.s");

unsigned short s16b_800C5074(int arg0)
{
    unsigned short arg0_copy;
    unsigned short color;

    int r, g, b, a;

    arg0_copy = arg0;

    r = arg0_copy & 0x1F;

    if (arg0_copy == 0)
    {
        return 0;
    }

    g = (arg0_copy & 0x3E0) >> 5;
    b = (arg0_copy & 0x7C00) >> 10;

    r = (r + g + b) / 3;

    a = arg0_copy & 0x8000;
    color = r | (r << 5) | (r << 10) | a;

    if (color == 0)
    {
        color = 0x8000;
    }

    return color;
}

#pragma INCLUDE_ASM("asm/overlays/s16b/s16b_800C50EC.s");
void s16b_800C50EC(void);

void s16b_800C51E0(SepiaWork *work)
{
}

int SepiaGetResources_800C51E8(SepiaWork *work)
{
    set_pal_effect_fns_80079194(s16b_800C50EC, s16b_800C5074);
    return 0;
}

GV_ACT *NewSepia_800C5214(void)
{
    SepiaWork *work;

    work = (SepiaWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(SepiaWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s16b_800C51E0, (TActorFunction)s16b_800C4E70, s16b_dword_800C5898);

        if (SepiaGetResources_800C51E8(work) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
