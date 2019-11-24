#include "linker.h"

struct TextConfig
{
    int xpos;
    int ypos;
    int flags;
    int colour;
};
extern struct TextConfig gMenuTextConfig_8009E2E4; 

void MENU_Color_80038B4C(int r, int g, unsigned short b)
{
	unsigned int newColour;
	unsigned int unknown;
	struct TextConfig* pTextConfig = &gMenuTextConfig_8009E2E4;
	
	if ((pTextConfig->flags & 0x20) != 0) 
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
