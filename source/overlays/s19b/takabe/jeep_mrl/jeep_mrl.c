#include "common.h"
#include <libgte.h>
#include <rand.h>
#include "game/game.h"

typedef struct _Work
{
    GV_ACT   actor;                                    /* 0x000 */
    int      field_20;                                 /* 0x020 */
    int      field_24;                                 /* 0x024 */
    CONTROL  control;                                  /* 0x028 */
    OBJECT   body;                                     /* 0x0A4 */
    char     pad_3C8[0x3C8 - 0xA4 - sizeof(OBJECT)];
    short    field_3C8;                                /* 0x3C8 */
    short    field_3CA;                                /* 0x3CA */
    int      field_3CC;                                /* 0x3CC */
    int      field_3D0;                                /* 0x3D0 */
    int      field_3D4;                                /* 0x3D4 */
    char     pad_3E0[0x3E0 - 0x3D4 - sizeof(int)];
    int      field_3E0;                                /* 0x3E0 */
    char     pad_7E8[0x7E8 - 0x3E0 - sizeof(int)];
    TARGET  *target;                                   /* 0x7E8 */
} Work;

extern Work *s19b_dword_800DE64C;

void s19b_jeep_mrl_800D2CE8(Work *work)
{
    if (work->field_3E0 == 0)
    {
        work->field_3D0 = GV_NearSpeed(work->field_3D0, work->field_3D4, 5);
    }
    else
    {
        work->field_3D0 = GV_NearSpeed(work->field_3D0, work->field_3D4, 10);
    }
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D2D3C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D2E78.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D32B4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D368C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D36A4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D37D0.s")
extern void s19b_jeep_mrl_800D2D3C(Work *work);

void s19b_jeep_mrl_800D3928(Work *work)
{
    s19b_jeep_mrl_800D2CE8(work);
    s19b_jeep_mrl_800D2D3C(work);
    if ((work->field_3CC & 0x3F) == 0)
    {
        work->field_3CA = (rand() * 60 >> 15) - 0x258;
    }
    work->field_3C8 = GV_NearSpeed(work->field_3C8, work->field_3CA, 0x1E);
}
int s19b_jeep_mrl_800D399C(void)
{
    return s19b_dword_800DE64C->field_3D0;
}
int s19b_jeep_mrl_800D39B4(SVECTOR *dst)
{
    *dst = s19b_dword_800DE64C->control.mov;
    return s19b_dword_800DE64C->field_3C8;
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D39F0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D3A54.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D3CA8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D3D30.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D3E98.s")
void s19b_jeep_mrl_800D4098(Work *work)
{
    GM_FreeTarget(work->target);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
}
extern void s19b_jeep_mrl_800D3D30(Work *work);
extern int  s19b_jeep_mrl_800D3E98(Work *work, int name, int arg2);
extern const char s19b_dword_800DDDF8[];
extern const char s19b_aMeryl_800DDDCC[];

void *s19b_jeep_mrl_800D40D4(int arg0, int arg1, int arg2)
{
    Work *work = GV_NewActor(GV_ACTOR_AFTER, 0x820);

    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jeep_mrl_800D3D30, s19b_jeep_mrl_800D4098,
                         s19b_dword_800DDDF8);
        work->field_20 = arg0;
        work->field_24 = arg1;
        if (s19b_jeep_mrl_800D3E98(work, GV_StrCode(s19b_aMeryl_800DDDCC), arg2) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return work;
}
