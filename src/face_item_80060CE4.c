#include <util/idaTypes.h>

extern void face_item_helper_80060CB8(WORD *in, WORD *out);
extern int GV_StrCode_80016CCC(const char* string );
extern WORD* DG_FindTexture_8001D830(int);

void face_item_80060CE4(const char* itemName1, const char* itemName2)
{
  int uVar1;
  WORD* pTexture1;
  WORD* pTexture2;
  WORD bufferHolder [5];
  
  uVar1 = GV_StrCode_80016CCC(itemName1);
  pTexture1 = DG_FindTexture_8001D830(uVar1);
  uVar1 = GV_StrCode_80016CCC(itemName2);
  pTexture2 = DG_FindTexture_8001D830(uVar1);

  face_item_helper_80060CB8(pTexture1 + 1,bufferHolder);
  face_item_helper_80060CB8(pTexture2 + 1,pTexture1 + 1);
  face_item_helper_80060CB8(bufferHolder,pTexture2 + 1);
}

