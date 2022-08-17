#include "Font/font.h"
#include "menuman.h"

extern Actor_MenuMan gMenuMan_800BD360;
extern KCB font_800BD968;

void menu_font_kill_8003FC0C(void)
{
  void *ptr;
  
  gMenuMan_800BD360.field_2B &= ~2;
  menu_font_kill_helper_8003F50C();
  ptr = font_get_buffer_ptr_80044FE8(&font_800BD968);
  GV_Free_80016230(ptr);
}
