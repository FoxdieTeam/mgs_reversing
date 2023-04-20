#include "menuman.h"
#include "libdg/libdg.h"

extern int GV_PauseLevel_800AB928;
extern UnkJimakuStruct gUnkJimakuStruct_800BDA70;

void NewJimakuStr_8004955C(char *str, int int_1)
{
  menu_JimakuWrite_800494E8(str, -1);
  GV_PauseLevel_800AB928 |= 1;
  gUnkJimakuStruct_800BDA70.field_3C = int_1;
  DG_FreeObjectQueue_800183D4();
}
