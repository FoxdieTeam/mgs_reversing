#include "game/game.h"
#include "linkvar.h"

typedef struct _M1e1
{
    char pad_000[0xD54];
    int  field_D54;   /* 0xD54 */
    int  field_D58;   /* 0xD58 */
    char pad_D5C[0xDB8 - 0xD5C];
    int  field_DB8;   /* 0xDB8 */
    char pad_DBC[0xEBC - 0xDBC];
    int  field_EBC;   /* 0xEBC */
    char pad_EC0[0xED0 - 0xEC0];
    int  field_ED0;   /* 0xED0 */
    char pad_ED4[0xF48 - 0xED4];
    int  field_F48;   /* 0xF48 */
} M1e1;

typedef struct _Work
{
    GV_ACT  actor;       /* 0x000 */
    CONTROL control;     /* 0x020 */
    char    pad_9C[0xDC - 0x9C];
    OBJECT  body;        /* 0x0DC */
    char    pad_1C0[0x1EC - 0x1C0];
    M1e1   *field_1EC;   /* 0x1EC */
    char    pad_1F0[0x1F8 - 0x1F0];
    unsigned short field_1F8; /* 0x1F8 */
    unsigned short field_1FA; /* 0x1FA */
    unsigned short field_1FC; /* 0x1FC */
} Work;

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DD1C8.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DD440.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DD6B8.s")

void s05a_800DDC14(Work *work)
{
    if (work->field_1EC->field_ED0 == 2)
    {
        if (work->field_1EC->field_D58 == 0)
        {
            work->field_1EC->field_D54 = work->field_1EC->field_ED0;
        }
        else
        {
            work->field_1EC->field_D54 = 7;
        }
        work->field_1EC->field_ED0 = 1;
        work->field_1EC->field_F48 = work->field_1EC->field_DB8;
        GM_CurrentWeaponId = work->field_1F8;
        GM_CurrentItemId = work->field_1FC;
    }

    work->field_1EC->field_EBC = 0;
    GM_FreeObject(&work->body);
    GM_FreeControl(&work->control);
}
