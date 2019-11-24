#include "linker.h"
#include "data.h"

void MENU_Text_XY_Flags_80038B34(int xpos, int ypos, int flags)
{
	TextConfig* pTextConfig = &gMenuTextConfig_8009E2E4;
	
	pTextConfig->xpos = xpos;
	pTextConfig->ypos = ypos;
	pTextConfig->flags = flags;
}

void MENU_Color_80038B4C(int r, int g, int b)
{
	unsigned int newColour;
	unsigned int unknown;
	TextConfig* pTextConfig = &gMenuTextConfig_8009E2E4;
	
	if ((pTextConfig->flags & TextConfig_Flags_eSemiTransparent_20) != 0) 
	{
		newColour = r | g << 8 | b << 0x10;
		unknown = 0x66000000;
	}
	else 
	{
		newColour = r | g << 8 | b << 0x10;
		unknown = 0x64000000;
	}
  
	pTextConfig->colour = newColour | unknown;
}


void MENU_Text_Init_80038b98(void)
{
	TextConfig* pTextConfig = &gMenuTextConfig_8009E2E4;
	pTextConfig->colour = 0x64808080;
	pTextConfig->flags = 0;
}
