#include "menuMan.h"

extern MenuGlue gMenuPrimBuffer_8009E2D0;

MenuGlue* MENU_GetPrimInfo_80038D68(void)
{
  return &gMenuPrimBuffer_8009E2D0;
}