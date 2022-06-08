#include "libdg.h"

// @todo(Voxel): Replace param_1 with Prim_Union and use the correct members. Fine for now.
void rcm_loader_helper_80066AF8(int param_1, DG_TEX *texture)
{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  char cVar6;

  *((char *) (param_1 + 3)) = 9;
  *((char *) (param_1 + 7)) = 0x2e;

  cVar1 = texture->field_8_offx;
  cVar5 = cVar1 + texture->field_A_width;
  *((char *) (param_1 + 7)) = 0x2e;

  cVar2 = texture->field_B_height;
  cVar3 = texture->field_9_offy;

  *((char *) (param_1 + 0xd)) = cVar3;
  *((char *) (param_1 + 0x15)) = cVar3;
  cVar6 = cVar3 + cVar2;

  *((char *) (param_1 + 0xc)) = cVar1;
  *((char *) (param_1 + 0x14)) = cVar5;
  *((char *) (param_1 + 0x1c)) = cVar1;
  *((char *) (param_1 + 0x1d)) = cVar6;
  *((char *) (param_1 + 0x24)) = cVar5;
  *((char *) (param_1 + 0x25)) = cVar6;
  *((short *) (param_1 + 0x16)) = texture->field_4_tPage;
  *((short *) (param_1 + 0xe)) = texture->field_6_clut;
}