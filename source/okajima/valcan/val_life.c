#include "valcan.h"

#include "mts/mts.h"
#include "libgcl/libgcl.h"

char SECTION(".bss") valcan_name_800E3478[8]; // could be smaller, it only has to be 6 bytes large

void Valcan_800D990C(Work *work)
{
    int rest;
    int now;

    now = (work->field_900 << 10) / work->field_6A8 / 8 * 8;
    if (now < 0)
    {
        now = 0;
        work->field_664->vital = 0;
        work->field_900 = 0;
    }

    rest = work->field_904;
    if (rest < now)
    {
        rest = now;
    }
    if (now < rest)
    {
        work->field_904 -= 8;
    }

    if (rest < 8 || now < 8)
    {
        rest = 8;
        now = 8;
    }

    MENU_DrawBar2(28, rest, now, 1024, &work->lifebar_8F4);
}

void Valcan_800D99F0(Work *work)
{
    MENU_BAR_CONF *bar;

    work->field_904 = (work->field_900 << 10) / work->field_6A8 / 8 * 8;
    memcpy(valcan_name_800E3478, "RAVEN", 6); // 6 == strlen("RAVEN") + 1
    work->lifebar_8F4.name = valcan_name_800E3478;

    // Set the left and right RGB values for the health bar gradient
    bar = &work->lifebar_8F4;
    bar->left[0] = 16;
    bar->left[1] = 111;
    bar->left[2] = 159;
    bar->right[0] = 31;
    bar->right[1] = 223;
    bar->right[2] = 127;
}

