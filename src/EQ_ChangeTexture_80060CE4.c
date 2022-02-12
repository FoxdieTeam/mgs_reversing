#include <util/idaTypes.h>

extern void		face_item_helper_80060CB8(WORD *in, WORD *out);
extern int		GV_Strcode_80016CCC(const char* string );
extern WORD		*DG_FindTexture_8001D830(int);

void EQ_ChangeTexture_80060CE4(const char* itemName1, const char* itemName2)
{
	WORD*	pTexture1;
	WORD*	pTexture2;
	WORD	buff[5];
  
	pTexture1 = DG_FindTexture_8001D830(GV_Strcode_80016CCC(itemName1));
	pTexture2 = DG_FindTexture_8001D830(GV_Strcode_80016CCC(itemName2));

	face_item_helper_80060CB8(pTexture1 + 1, buff);
	face_item_helper_80060CB8(pTexture2 + 1, pTexture1 + 1);
	face_item_helper_80060CB8(buff, pTexture2 + 1);
}

