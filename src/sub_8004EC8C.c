#include "sna_init.h"

extern Sna_E1 e1_800AB7C4;
Sna_E1 SECTION(".sdata") e1_800AB7C4;

extern short dword_800B7800[];

extern void  sna_init_set_flags_8004E2F4(Actor_SnaInit *snake, unsigned int flag);
extern void  sd_set_cli_800887EC(int code, int unused);
extern void  sub_8004E330(Actor_SnaInit *snake, unsigned int flag);
extern void  GM_ClearPlayerStatusFlag_8004E2D4(unsigned int flag);

void sub_8004EC8C(Actor_SnaInit *snake)
{
    ushort sVar0;
    
    sna_init_set_flags_8004E2F4(snake, 0x800);
    snake->field_A28 = 0x1cc;
    dword_800B7800[5] = 1;
    sVar0 = *(ushort*)&e1_800AB7C4.field_4;
    snake->field_A20 = -6;
    snake->field_9D4 = 0x140;
    snake->field_9D8 = sVar0;
    snake->field_9DC = sVar0;
    sd_set_cli_800887EC(0x1ffff20, 0);
    sub_8004E330(snake,0x10);
    GM_ClearPlayerStatusFlag_8004E2D4(1);
}